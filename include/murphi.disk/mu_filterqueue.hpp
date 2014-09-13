/**CHeaderFile*****************************************************************

  FileName    [mu_filterqueue.hpp]

  Synopsis    [Header file for queue filtering]

  Author      [Igor Melatti]

  Copyright   [
  This file is part of the disk verifier package of CMurphi. 
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

#ifndef _FILTERQUEUE_
#define _FILTERQUEUE_

#define NEUTRAL_ZONE_HI_BOUND 0.5
#define NEUTRAL_ZONE_LO_BOUND 0.3

#define MIN_FILTER_ALPHA 0.1
#define INITIAL_ALPHA 0.5
#define CRITICAL_ALPHA 0.95
#define ALPHA_DELAY_FACTOR 1

#define BLOCK_MIN_SIZE 10000
#define BLOCK_MAX_NUMBER 100
#define BLOCK_SIZE_STEP 50

#define CALIBRATION_FREQ 10

#define AREA0_PERCENT_SIZE 0.40
#define AREA1_PERCENT_SIZE 0.30
#define AREA0_MAX_PROB 0.4
#define AREA1_MAX_PROB 0.6

#define AGING 2.0

/***********************************************
  Pair containing a state and its hash signature.
  Used by the unchecked queue.
 ***********************************************/
struct state_and_signature_pair {
  state _state;
#if __WORDSIZE == 32
  unsigned long _signature[2];
#else
  unsigned int _signature[2];
#endif

#if __WORDSIZE == 32
   state_and_signature_pair(state * s, unsigned long c1, unsigned long c2)
#else
   state_and_signature_pair(state * s, unsigned int c1, unsigned int c2)
#endif
  {
    _state = *s;
    _signature[0] = c1;
    _signature[1] = c2;
  } state_and_signature_pair() {
  };
};

/**************************************************
  Queue containing states and their hash signature.
  (The "unchecked" queue)
 **************************************************/
class state_and_signature_queue {
protected:
  state_and_signature_pair * stateArray;	/* The actual array. */
  const unsigned long max_active_states;	/* max size of queue */
  unsigned long front;		/* index of first active state. */
  unsigned long rear;		/* index of next free slot. */

  unsigned long global_rear, global_front;
  unsigned long num_elts_head, num_elts_tail;
  unsigned long head_begin, tail_begin;
  unsigned long head_size, tail_size;

  /* Disk paging files */
#ifndef SPLITFILE
  FILE *paging_file_top, *paging_file_bottom;
#else
  splitFile *paging_file_top, *paging_file_bottom;
#endif

public:
  // initializers
   state_and_signature_queue(unsigned long mas);

  // destructor
   virtual ~ state_and_signature_queue();

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
  virtual void enqueue(state_and_signature_pair * &e);
  virtual state_and_signature_pair *dequeue(void);
  virtual state_and_signature_pair *top(void);

  virtual void ReclaimFreeSpace();
  virtual void QueueEmptyFault();

  virtual unsigned NextRuleToTry() {
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



/****************************************
  The disk-filtered state queue.
  (The "checked" queue)
 ****************************************/
class state_filtering_queue {
#ifdef HASHC
#if __WORDSIZE == 32
  typedef unsigned long Unsigned32;	// basic building block of the hash
  // table, slots may have different size
#else
  typedef unsigned int Unsigned32;
#endif
#endif


protected:
   state * stateArray;		/* The actual array. */
  const unsigned long max_active_states;	/* max size of queue */
  unsigned long front;		/* index of first active state. */
  unsigned long rear;		/* index of next free slot. */

  unsigned long global_rear, global_front;
  unsigned long num_elts_head, num_elts_tail;
  unsigned long head_begin, tail_begin;
  unsigned long head_size, tail_size;

  unsigned long history_len;
  double filter_alpha;

#ifndef SPLITFILE
  FILE *paging_file_top, *paging_file_bottom;
  FILE *history_file;
#else
  /* Disk paging files */
  splitFile *paging_file_top, *paging_file_bottom;
  splitFile *history_file;
#endif

  state_and_signature_queue *uncheckedQueue;

#if __WORDSIZE == 64
  unsigned int bits_for_size;	/* number of bits to address the whole table */
#endif
  Unsigned32 *filterTable;
#if __WORDSIZE == 32
  bool hashtable_lookup(unsigned long, unsigned long, bool, bool);
  unsigned long signature_hash(unsigned long t1, unsigned long t2);
#else
  bool hashtable_lookup(unsigned int, unsigned int, bool, bool);
  unsigned long signature_hash(unsigned int t1, unsigned int t2);
#endif
  dynBitVec *Full, *Removed;

  unsigned long hashtable_size;
  unsigned long hashtable_num_elts;

  bool enqueue_checked(state * e);
  state *dequeue_checked(void);
  state *top_checked(void);

  bool enqueue_unchecked(state * &e);
  state_and_signature_pair *dequeue_unchecked(void);

  char *QueryReadFront();
  bool QueryCalibration();
  void Calibrate(unsigned long deleted_a, unsigned long deleted_b);
  unsigned long FilterTable(unsigned long states, unsigned long *_totread =
			    NULL);

  double SelectionP(unsigned long block);

  void DefineBlocks();
  void CheckTable_full();
  void CheckTable_simple();

  randomGen random;
  unsigned long history_blocks;
  unsigned long history_block_len;
  unsigned long last_deleted_states;

  bool hashtable_first_full;

public:
  // initializers
   state_filtering_queue(unsigned long mas);

  // destructor
   virtual ~ state_filtering_queue();

  // information interface
  inline unsigned long MaxElts(void) {
    return max_active_states;
  } unsigned long NumElts(void) {
    return num_elts_head + num_elts_tail + global_rear + global_front;
  }
  unsigned long HistoryLength(void) {
    return history_len;
  }
  double DiskAlpha(void) {
    return filter_alpha;
  }
  inline bool isempty(void);

  //to avoid problems with table lookup, declare it full a bit before it is really full
  //inline bool tableisfull( void ) {return (hashtable_num_elts >= hashtable_size);}
  inline bool tableisfull(void) {
    return (hashtable_num_elts >= hashtable_size - 3);
  }

  inline unsigned long deletedstates() {
    unsigned long temp = last_deleted_states;
    last_deleted_states = 0;
    return temp;
  }

  inline static int BytesForOneState_checked(void);
  inline static int BytesForOneState_unchecked(void);
  inline static int BytesForOneState_hashtable(void);

  // storing and removing elements
  virtual bool enqueue(state * &e) {
    return enqueue_unchecked(e);
  }
  virtual state *dequeue(void) {
    return dequeue_checked();
  }
  virtual state *top(void) {
    return top_checked();
  }

  virtual void ReclaimFreeSpace();
  virtual void QueueEmptyFault();

  inline void CheckTable();

  virtual unsigned NextRuleToTry() {
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
    cout << "\t* Capacity in queue for breadth-first search:\n"
	<< "\t  -" << max_active_states << " checked (old) states.\n"
	<< "\t  -" << (int) max_active_states <<
	" unchecked (new) states.\n" << "\t  -" << (int) (max_active_states
							  /
							  gPercentActiveStates)
	<< " states in the new state buffer.\n" <<
	"\t   * Change the constant gPercentActiveStates in mu_prolog.inc\n"
	<< "\t     to increase this, if necessary.\n";
  }
};

#endif
