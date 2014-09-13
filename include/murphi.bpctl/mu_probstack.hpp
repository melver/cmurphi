/**CHeaderFile*****************************************************************

  FileName    [mu_probstack.hpp]

  Synopsis    [Header file for stack]

  Author      [Igor Melatti]

  Copyright   [
  This file is part of the BPCTL verifier package of CMurphi. 
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

#ifndef PROBSTACK
#define PROBSTACK

#include "murphi.disk/splitFile.hpp"

struct state_prob_rule {
  state _state;
  double _prob_reach, _prob_f;
  unsigned _rule;
#ifdef BPCTL_PROB_ORD
  unsigned _rules_ord[NUMRULES_DEFINE];
  double _prob_ord[NUMRULES_DEFINE];
#endif

   state_prob_rule(state * s, double p_r, double p_f, unsigned r
#ifdef BPCTL_PROB_ORD
		   , unsigned *r_ord, double *prob_ord
#endif
      ) {
    _state = *s;
    _prob_reach = p_r;
    _prob_f = p_f;
    _rule = r;
#ifdef BPCTL_PROB_ORD
    for (int i = 0; i < NUMRULES_DEFINE; i++) {
      _rules_ord[i] = r_ord[i];
      _prob_ord[i] = prob_ord[i];
    }
#endif
  } state_prob_rule() {
  };
};


/****************************************
  The state stack.
 ****************************************/
class state_prob_rule_stack {
#ifdef HASHC
  typedef unsigned long Unsigned32;
#endif

protected:
   state_prob_rule * stateArray;	/* The actual array. */

  unsigned long max_active_states;	/* max total entries (RAM + disk) of stack (equal to the verification horizon) */
  unsigned long front;		/* index of the top of the stack */
  unsigned long size;		/* size of the stack in RAM */
  unsigned long size_2;		/* size for the stack cycling */
  unsigned long num_elts;
  unsigned disk2stack_cnt, stack2disk_cnt;
  unsigned long mem_used;

#ifndef SPLITFILE
  FILE *paging_file;
#else
  splitFile *paging_file;
#endif

  virtual void Stack2Disk();
  virtual void Disk2Stack();
  inline bool Stack2Disk_needed() {
    return front >= size;
  };
  inline bool Disk2Stack_needed() {
    return stack2disk_cnt != disk2stack_cnt && front == 0;
  };

public:
  // initializers
  state_prob_rule_stack(unsigned long memory, unsigned long bound);

  // destructor
  virtual ~state_prob_rule_stack();

  inline bool isempty(void) {
    return stack2disk_cnt != disk2stack_cnt && front == 0;
  };

  inline unsigned long NumElts() {
    return num_elts;
  }

  inline static int BytesForOneState(void);

  // storing and removing elements
  virtual void push(state * e, double p_r, double p_f);
  virtual state *pop(double &p_r, double &p_f);
  virtual state *reset(long level);
  virtual state *top();
  virtual double update_prob(double prob);
  virtual void print_probability_so_far();
  inline double final_prob() {
    return stateArray[front]._prob_f;
  };				//hyp: this is called after the last pop
  inline double get_prob() {
    return stateArray[front - 1]._prob_f;
  };
  inline unsigned long memory_used() {
    return mem_used;
  };

  virtual unsigned NextRuleToTry();
  virtual void NextRuleToTry(unsigned r);
#ifdef BPCTL_PROB_ORD
  unsigned stack_rules(unsigned, double &);
  void set_stack_rules(unsigned *, double *, int);
#endif

  // printing routine
  void Print(void);
  virtual void print_capacity(void) {
    /*cout << "\t* Capacity of stack for depth-first search:\n"
       << "\t  * " << max_active_states << " states in the stack.\n"
       << "\t  * Change the constant gPercentActiveStates in mu_prolog.inc\n"
       << "\t     to increase this, if necessary.\n"; */
  }
};

#endif

#ifndef _FILTERQUEUE_
#define _FILTERQUEUE_


struct state_and_probability_pair {
  state _state;
  double _probability;

   state_and_probability_pair(state * s, double p) {
    _state = *s;
    _probability = p;
  } state_and_probability_pair() {
  };
};


/****************************************
  The state queue.
 ****************************************/
class state_probability_queue {
#ifdef HASHC
  typedef unsigned long Unsigned32;
#endif


protected:
   state_and_probability_pair * stateArray;	/* The actual array. */
  state_and_probability_pair *table;

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

  bool hashtable_lookup(state_and_probability_pair * &in);
  void enqueue_commit(state_and_probability_pair * e);

  dynBitVec *Full;

  unsigned long hashtable_size;
  unsigned long hashtable_num_elts;

  randomGen random;

public:
  // initializers
   state_probability_queue(unsigned long mas);

  // destructor
   virtual ~ state_probability_queue();

  // information interface
  inline unsigned long MaxElts(void) {
    return max_active_states;
  } unsigned long NumElts(void) {
    return num_elts_head + num_elts_tail + global_rear + global_front +
	hashtable_num_elts;
  }
  inline bool isempty(void);

  inline static int BytesForOneState(void);
  inline static int BytesForOneState_hashtable(void);

  // storing and removing elements
  virtual bool enqueue(state * &e, double p);
  virtual state *dequeue(double &prob);
  virtual state *top(double &prob);

  virtual void ReclaimFreeSpace();
  virtual void QueueEmptyFault();

  inline void CheckTable();

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
    cout << "\t* Capacity of queue for breadth-first search:\n"
	<< "\t  * " << max_active_states << " states in the queue.\n"
	<< "\t  * " << hashtable_size << " states in the cache.\n"
	<<
	"\t   * Change the constant gPercentActiveStates in mu_prolog.inc\n"
	<< "\t     to increase this, if necessary.\n";
  }
};

#endif
