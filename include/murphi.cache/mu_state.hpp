/**CHeaderFile*****************************************************************

  FileName    [mu_state.hpp]

  Synopsis    [Header file for queue and hash table]

  Author      [Igor Melatti]

  Copyright   [
  This file is part of the caching verifier package of CMurphi. 
  Copyright (C) 2009-2012 by Sapienza University of Rome. 

  CMurphi is free software; you can redistribute it and/or 
  modify it under the terms of the GNU Lesser General Public 
  License as published by the Free Software Foundation; either 
  of the License, or (at your option) any later version.

  CMurphi is distributed in the hope that it will be useful, 
  but WITHOUT ANY WARRANTY; without even the implied warranty of 
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public 
  License along with this library; if not, write to the Free Software 
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA.

  To contact the CMurphi development board, email to <melatti@di.uniroma1.it>. ]

******************************************************************************/

#ifndef _STATE_
#define _STATE_

/****************************************
  There are three different declarations:
  1) state
  2) dynBitVec
  3) state queue
  4) state set
 ****************************************/

/****************************************
  The record for a single state.
  require : BITS_IN_WORLD in parameter file
 ****************************************/

/* BITS_IN_WORLD gets defined by the generated code. */
/* The extra addition is there so that we round up to the greater block. */

/****************************************
  Bit vector - copied straight from Andreas. 
 ****************************************/
class dynBitVec {
  // data
  unsigned long numBits;
  unsigned char *v;

  // Inquiries
  inline unsigned int Index(unsigned long index) {
    return index / 8;
  } inline unsigned int Shift(unsigned long index) {
    return index % 8;
  }

public:
  // initializer
  dynBitVec(unsigned long nBits);
  // destructor
  virtual ~ dynBitVec();

  // interface
  inline int NumBits(void) {
    return numBits;
  }
  inline int NumBytes(void) {
    return 1 + (numBits - 1) / 8;
  }
  inline void clear(unsigned long i) {
    v[Index(i)] &= ~(1 << Shift(i));
  }
  inline void set(unsigned long i) {
    v[Index(i)] |= (1 << Shift(i));
  }
  inline int get(unsigned long i) {
    return (v[Index(i)] >> Shift(i)) & 1;
  }
};

class statelist {
  state *s;
  statelist *next;
public:
   statelist(state * s, statelist * next)
  :s(s), next(next) {
  };
};

/****************************************
  The state queue.
 ****************************************/
class state_queue {
protected:
  state * stateArray;		/* The actual array. */
  const unsigned long max_active_states;	/* max size of queue */
  unsigned long front;		/* index of first active state. */
  unsigned long rear;		/* index of next free slot. */

  unsigned long global_rear, global_front;
  unsigned long num_elts_head, num_elts_tail;
  unsigned long head_begin, tail_begin;
  unsigned long head_size, tail_size;

#ifndef SPLITFILE
  FILE *paging_file_top, *paging_file_bottom;
#else
  splitFile *paging_file_top, *paging_file_bottom;
#endif

public:
  // initializers
   state_queue(unsigned long mas);

  // destructor
   virtual ~ state_queue();

  // information interface
  inline unsigned long MaxElts(void) {
    return max_active_states;
  } unsigned long NumElts(void) {
    return num_elts_head + num_elts_tail + global_rear + global_front;
  }
  inline bool isempty(void) {
    return num_elts_head + num_elts_tail + global_rear + global_front == 0;
  }

  inline static int BytesForOneState(void);


  // storing and removing elements
  virtual void enqueue(state * &e);
  virtual state *dequeue(void);
  virtual state *top(void);

  virtual void ReclaimFreeSpace();
  virtual void QueueEmptyFault();

  virtual unsigned NextRuleToTry()	// Uli: unsigned short -> unsigned
  {
    Error.Notrace
	("Internal: Getting next rule to try from a state queue instead of a state stack.");
    return 0;
  }
  virtual void NextRuleToTry(unsigned r) {
    Error.Notrace
	("Internal: Setting next rule to try from a state queue instead of a state stack.");
  }

  // printing routine
  void Print(void);
  virtual void print_capacity(void) {
    cout << "\t* Capacity in queue for breadth-first search: "
	<< max_active_states << " states.\n"
	<<
	"\t   * Change the constant gPercentActiveStates in mu_prolog.inc\n"
	<< "\t     to increase this, if necessary.\n";
  }
};

class state_stack:public state_queue {
  unsigned *nextrule_to_try;

public:
  // initializers
   state_stack(unsigned long mas)
  :state_queue(mas) {
    unsigned long i;
     nextrule_to_try = new unsigned[mas];
    for (i = 0; i < mas; i++)
       nextrule_to_try[i] = 0;
  };

  // destructor
  virtual ~ state_stack() {
    delete[OLD_GPP(max_active_states)] nextrule_to_try;	// Should be delete[].
  };

  virtual void print_capacity(void) {
    cout << "\t* Capacity in queue for depth-first search: "
	<< max_active_states << " states.\n"
	<<
	"\t   * Change the constant gPercentActiveStates in mu_prolog.inc\n"
	<< "\t     to increase this, if necessary.\n";
  }
  void enqueue(state * e);

  virtual unsigned NextRuleToTry() {
    return nextrule_to_try[front];
  }
  virtual void NextRuleToTry(unsigned r) {
    nextrule_to_try[front] = r;
  }

#ifdef partial_order_opt
  // special interface with sleepset
  void enqueue(state * e, sleepset s);
#endif
};

/****************************************
  The state set
  represented as a large open-addressed hash table.
 ****************************************/

#include <stdint.h>		/* needed for __WORDSIZE, not included by <limits.h> in a
				   64-bit architecture if gcc >= 2 */

class state_set {

  randomGen random;		//gdp: random number generator for random walk  


#ifdef HASHC
#if __WORDSIZE == 32
  typedef unsigned long Unsigned32;	// basic building block of the hash
  // table, slots may have different size
#else
  typedef unsigned int Unsigned32;
#endif
#endif

  // data
  unsigned long table_size;	/* max size of the hash table */
#ifndef HASHC
  state *table;			/* pointer to the hash table */
#else
#if __WORDSIZE == 64
  unsigned int bits_for_size;	/* number of bits to address the whole table */
#endif
  Unsigned32 *table;
#endif
  dynBitVec *Full;		/* whether element table[i] is used. */
  unsigned long num_elts;	/* number of elements in table */
  unsigned long num_elts_reduced;	// Uli
  unsigned long num_collisions;	/* number of collisions in hashing */
  unsigned long ht_overwrite;	/* overwrites in caching. gdp */

  // internal routines
  bool is_empty(unsigned long i) {	/* check if element table[i] is empty */
    return Full->get(i) == 0;
  };

public:
  // constructors
  state_set(unsigned long table_size);
  state_set(void);

  friend void copy_state_set(state_set * set1, state_set * set2);

  void clear_state_set();

  // destructor
  virtual ~ state_set();

  // checking the presence of state "in"
  bool simple_was_present(state * &in, bool, bool);
  /* old was_present without checking -sym */
  bool was_present(state * &in, bool, bool);
  /* checking -sym before calling simple_was_present() */

  // get the size of each state entry
#ifndef VER_PSEUDO
  static int bits_per_state(void);
#endif

  // get the number of elts in the state set
  inline unsigned long NumElts() {
    return num_elts;
  };
  inline unsigned long NumOverwrites() {
    return ht_overwrite;
  };
  inline unsigned long NumEltsReduced() {
    return num_elts_reduced;
  };				// Uli

  // printing information
  void print_capacity(void);

  // print hashtable       
  void print() {
    for (unsigned long i = 0; i < table_size; i++)
      if (!is_empty(i)) {
	cout << "State " << i << "\n";
#ifdef HASHC
	cout << "... compressed\n";
#else
	StateCopy(workingstate, &table[i]);
	theworld.print();
#endif
	cout << "\n";
      }
  }
};

#endif
