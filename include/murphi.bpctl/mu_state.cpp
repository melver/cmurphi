/**CFile***********************************************************************

  FileName    [mu_state.cpp]

  Synopsis    [File for queue and hash table]

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

/****************************************
  There are 3 groups of implementations:
  1) bit vector
  2) class StatePtr and state related stuff
  3) state queue and stack
  4) state set
  ****************************************/

void
 state::print()
{
  theworld.print();
};

/****************************************
  Bit vector - copied straight from Andreas. 
  ****************************************/
dynBitVec::dynBitVec(unsigned long nBits)
:numBits(nBits)
{
  v = new unsigned char[NumBytes()];	/* Allocate and clear vector. */
  ErrAlloc(v);
  memset(v, 0, NumBytes());
};

dynBitVec::~dynBitVec()
{
  delete[OLD_GPP(NumBytes())]v;	// should be delete[].
}


/****************************************
  class StatePtr and state related stuff.
  ****************************************/

inline void
 StatePtr::sCheck()
{
#ifdef HASHC
  if (args->trace_file.value)
    Error.Notrace("Internal: Illegal Access to StatePtr.");
#endif
}

inline void StatePtr::lCheck()
{
#ifdef HASHC
  if (!args->trace_file.value)
    Error.Notrace("Internal: Illegal Access to StatePtr.");
#endif
}

StatePtr::StatePtr(state * s)
{
  sCheck();
  sp = s;
}

StatePtr::StatePtr(unsigned long l)
{
  lCheck();
  lv = l;
}

void
 StatePtr::set(state * s)
{
  sCheck();
  sp = s;
}

void StatePtr::set(unsigned long l)
{
  lCheck();
  lv = l;
}

void StatePtr::clear()
{
#ifdef HASHC
  if (args->trace_file.value)
    lv = 0;
  else
#endif
    sp = NULL;
}

state *StatePtr::sVal()
{
  sCheck();
  return sp;
}

unsigned long StatePtr::lVal()
{
  lCheck();
  return lv;
}

StatePtr StatePtr::previous()
{				// return StatePtr to previous state
#ifdef HASHC
  if (args->trace_file.value)
    return TraceFile->read(lv)->previous;
  else
#endif
    return sp->previous.sp;
}

bool StatePtr::isStart()
{				// check if I point to a startstate
#ifdef HASHC
  if (args->trace_file.value) {
    if (TraceFile->read(lv)->previous == 0)
      return TRUE;
    return FALSE;
  } else
#endif
  {
    if (sp->previous.sp == NULL)
      return TRUE;
    return FALSE;
  }
}

bool StatePtr::compare(state * s)
{				// compare the state I point to with s
#ifdef HASHC
  if (args->trace_file.value) {
    unsigned long *key = h3->hash(s, FALSE);
    unsigned long
	c1 = key[1] &
	((~0UL) <<
	 (args->num_bits.value > 32 ? 0 : 32 - args->num_bits.value));
    unsigned long c2 =
	key[2] & (args->num_bits.value >
		  32 ? (~0UL) << (64 - args->num_bits.value) : 0UL);

    return (c1 == TraceFile->read(lv)->c1
	    && c2 == TraceFile->read(lv)->c2);
  } else
#endif
    return (StateCmp(sp, s) == 0);
}


void StateCopy(state * l, state * r)
// Uli: uses default assignment operator
{
  *l = *r;
}

int StateCmp(state * l, state * r)
{
  int i = BLOCKS_IN_WORLD / 4;
  register int *d = (int *) l->bits, *s = (int *) r->bits;

  while (i--)
    if (*d > *s)
      return 1;
    else if (*d++ < *s++)
      return -1;
  return 0;
}

void copy_state(state * &s)
{
  state *h;

  if ((h = new state) == NULL)
    Error.Notrace
	("New failed. Swap space probably too small for state queue.");
  *h = *s;
  s = h;
}

bool StateEquivalent(state * l, StatePtr r)
{
  return match(l, r);
}

/****************************************
  class state_queue for searching the state space.
  ****************************************/
state_queue::state_queue(unsigned long mas)
:  max_active_states(mas), num_elts(0), front(0), rear(0)
{
  stateArray = new state *[max_active_states];

  for (long i = 0; i < max_active_states; i++)	// Uli: avoid bzero
    stateArray[i] = NULL;
};

state_queue::~state_queue()
{
  delete[OLD_GPP(max_active_states)] stateArray;	// Should be delete[].
}

int
 state_queue::BytesForOneState(void)
{

#ifdef VER_PSEUDO
  // Pseudo ver: ptr + malloced state + approx. malloc&new overhead.
  return sizeof(state *) + sizeof(state) + 8;
#else
  return sizeof(state *);	/* Full ver: only a ptr to state. */
#endif
}

void state_queue::Print(void)
{
  unsigned long i;
  unsigned long ind = front;
  for (i = 1; i < num_elts; i++) {
    // convert to print in unsigned long format?
    cout << "State " << i << " [" << ind << "]:\n";
    stateArray[ind]->print();
    ind = (ind + 1) % max_active_states;
  }
}

void state_queue::enqueue(state * e)
{
  if (num_elts < max_active_states) {
    stateArray[rear] = e;
    rear = (rear + 1) % max_active_states;
    num_elts++;
  } else {
    Error.Notrace("Internal Error: Too many active states.");
  }
}

state *state_queue::dequeue(void)
{
  state *retval;
  if (num_elts > 0) {
    retval = stateArray[front];
    front = (front + 1) % max_active_states;
    num_elts--;
  } else {
    Error.Notrace("Internal: Attempt to dequeue from empty state queue.",
		  "", "");
  }
  return retval;
}

state *state_queue::top(void)
{
  if (num_elts > 0) {
    return stateArray[front];
  } else {
    Error.Notrace("Internal: Attempt to top() empty state queue.", "", "");
    return NULL;
  }
}

void state_stack::enqueue(state * e)
{
  if (num_elts < max_active_states) {
    front = front == 0 ? max_active_states - 1 : front - 1;
    stateArray[front] = e;
    nextrule_to_try[front] = 0;
    num_elts++;
  } else {
    Error.Notrace("Internal: Too many active states.");
  }
}

/****************************************   // changes by Uli
  The Stateset implementation for recording all the states found.
  ****************************************/

int state_set::bits_per_state()
{
#ifndef HASHC
  return 8 * sizeof(state);
#else
  return args->num_bits.value;
#endif
}

state_set::state_set(unsigned long table_size)
:  
table_size(table_size), num_elts(0), num_elts_reduced(0), num_collisions(0)
{
#ifndef HASHC
  table = new state[table_size];
#else
  assert(sizeof(Unsigned32) == 4);	// the implementation is pretty depen-
  // dent on the 32 bits
  unsigned long size =
      (unsigned long) ((double) table_size * args->num_bits.value / 32) +
      3;
  // higher precision necessary to avoid overflow
  // two extra elements needed in table
  table = new Unsigned32[size];
  for (unsigned long i = 0; i < size; i++)
    table[i] = 0UL;
#endif
  Full = new dynBitVec(table_size);
}

state_set::~state_set()
{
  delete[]table;		// only works for newer g++ versions
  delete Full;
}

// Uli: the two following routines were deleted because they were not called
//      any more and required changes
//void state_set::clear_state_set()
//void copy_state_set( state_set * set1, state_set * set2)

bool state_set::simple_was_present(state * &in, bool valid, bool permanent)
/* changes in to point to the first state found with that pattern. */
/* returns true iff the state was present in the hash table;
 * Otherwise, returns false and inserts the state. */
/* Algorithms directly from Andreas\' code. He cites CLR 235, 236. */
// Uli: pitfall: shift operators yield undefined values if the right
//               operand is equal to the length in bits of the left
//               operand (see ARM, pg.74)
// Uli: table_size must be prime
{
#ifndef HASHC
  unsigned long key = in->hashkey();
  unsigned long h1 = key % table_size;
  unsigned long h2 = 1 + key % (table_size - 1);
  unsigned long h = h1;
#else
  unsigned long *key = h3->hash(in, valid);
  unsigned long h1 = key[0] % table_size;
  unsigned long h2;
  register unsigned long h = h1;
  register unsigned long num_bits = args->num_bits.value;
  register unsigned long
      mask1 = (~0UL) << (num_bits > 32 ? 0 : 32 - num_bits);
  register unsigned long
      mask2 = num_bits > 32 ? (~0UL) << (64 - num_bits) : 0UL;
  register unsigned long addr, offset;
  register unsigned long c1 = key[1] & mask1;
  register unsigned long c2 = key[2] & mask2;
  register unsigned long t1, t2;
#endif

#ifdef VER_PSEUDO
  if (is_empty(h)) {
    Full->set(h);
    num_elts++;
    return FALSE;
  }
  return TRUE;

#else
  unsigned long probe = 0;

#ifndef HASHC
// no hash compaction, uses double hashing

  bool empty, equal = FALSE;

  while (!(empty = is_empty(h)) &&
	 !(equal = (*in == table[h])) && (probe < table_size)) {
    h = (h1 + probe * h2) % table_size;	// double hashing
    num_collisions++;
    probe++;
  }
  if (empty) {			/* Go ahead and insert the element. */
    table[h] = *in;
    in = &table[h];
    Full->set(h);
    num_elts++;
    return FALSE;
  } else if (equal) {
    in = &table[h];
    return TRUE;
  } else {
    Error.Notrace("Closed hash table full.");
    return FALSE;		/* it doesn\'t matter, but it shuts up g++. */
  }

#else
// hash compaction, uses ordered hashing
// the state-insertion is done in two steps: search and insertion

  // search - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  h2 = 1 + c1 % (table_size - 1);	// calculation uses compressed value

  do {
    // calculate address and offset in table
    // 32 bit arithmetic not sufficient and may cause overflow
    // addr = (h*num_bits) / 32
    // offset = (h*num_bits) % 32
    offset = (h & 0xffffUL) * num_bits;
    addr = (((h >> 16) * num_bits) << 11) + (offset >> 5);
    offset &= 0x1fUL;

    if (is_empty(h))
      break;			// search unsuccessful

    // read compressed value from table
    t1 = (table[addr] << offset |
	  (offset == 0 ? 0 : table[addr + 1] >> (32 - offset)))
	& mask1;
    t2 = (table[addr + 1] << offset |
	  (offset == 0 ? 0 : table[addr + 2] >> (32 - offset)))
	& mask2;

    if (t1 == c1 ? t2 < c2 : t1 < c1)
      break;			// search unsuccessful

    if (t1 == c1 && t2 == c2)
      return TRUE;		// search successful

    h = (h + h2) % table_size;
    num_collisions++;
    probe++;
    if (probe == table_size)
      Error.Notrace("Closed hash table full.");
  } while (TRUE);

  // write trace info
  if (args->trace_file.value)
    TraceFile->write(c1, c2, in->previous.lVal());

  // insertion - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  if (num_elts == table_size)
    Error.Notrace("Closed hash table full.");

  while (!is_empty(h))		// until empty slot found
  {
    if (t1 == c1 ? t2 < c2 : t1 < c1) {
      table[addr] ^= (c1 ^ t1) >> offset;
      table[addr + 1] ^= (offset == 0 ? 0 : (c1 ^ t1) << (32 - offset))
	  | (c2 ^ t2) >> offset;
      table[addr + 2] ^= (offset == 0 ? 0 : (c2 ^ t2) << (32 - offset));
      c1 = t1;
      c2 = t2;
    }

    h = (h + 1 + c1 % (table_size - 1)) % table_size;
    offset = (h & 0xffffUL) * num_bits;
    addr = (((h >> 16) * num_bits) << 11) + (offset >> 5);
    offset &= 0x1fUL;
    t1 = (table[addr] << offset |
	  (offset == 0 ? 0 : table[addr + 1] >> (32 - offset)))
	& mask1;
    t2 = (table[addr + 1] << offset |
	  (offset == 0 ? 0 : table[addr + 2] >> (32 - offset)))
	& mask2;
  }

  table[addr] |= c1 >> offset;	// insertion
  table[addr + 1] |=
      (offset == 0 ? 0 : c1 << (32 - offset)) | c2 >> offset;
  table[addr + 2] |= (offset == 0 ? 0 : c2 << (32 - offset));

  copy_state(in);		// make copy of state
  Full->set(h);
  num_elts++;
  if (permanent)
    num_elts_reduced++;
  return FALSE;

#endif

#endif
};

bool state_set::was_present(state * &in, bool valid, bool permanent)
{
  if (args->symmetry_reduction.value)
    in->Normalize();
  if (args->multiset_reduction.value && !args->symmetry_reduction.value)
    in->MultisetSort();
  return simple_was_present(in, valid, permanent);
}

void state_set::print_capacity(void)
{
  cout <<
      "\t* The memory allocated for the hash table and state queue is\n\t  ";
  if (args->mem.value > 1000000)
    cout << (args->mem.value / 1000000) << " Mbytes.\n";
  else
    cout << (args->mem.value / 1000) << " kbytes.\n";

#ifndef HASHC
  cout << "\t  With two words of overhead per state, the maximum size of\n"
      << "\t  the state space is "
      << table_size << " states.\n"
      <<
      "\t   * Use option \"-k\" or \"-m\" to increase this, if necessary.\n";
#else
  cout << "\t  With states hash-compressed to "
      << args->num_bits.value << " bits, the maximum size of\n"
      << "\t  the state space is "
      << table_size << " states.\n"
      <<
      "\t   * Use option \"-k\" or \"-m\" to increase this, if necessary.\n";
#endif
}

void path::add_action(unsigned act, unsigned i)
{
  unsigned mask = 0xff;
  for (int j = 0; j < DIM_ACT; j++) {
    bits[i * DIM_ACT + j] = (unsigned char) (act & mask);
    mask = mask << 8;
  }
  //dim += DIM_ACT;
}

void path::reset()
{
  for (int j = 0; j < PATH_LENGTH * DIM_ACT; j++)
    bits[j] = 0;
  //dim = 0;
}

int path_set::bits_per_state()
{
  return 8 * sizeof(path);
}

path_set::path_set(unsigned long table_size)
:table_size(table_size), num_elts(0)
{
  table = new path[table_size];
  Full = new dynBitVec(table_size);
}

path_set::~path_set()
{
  delete[]table;		// only works for newer g++ versions
  delete Full;
}

bool path_set::was_present(path * in)
{
  unsigned long key = in->hashkey();
  unsigned long h1 = key % table_size;
  unsigned long h2 = 1 + key % (table_size - 1);
  unsigned long h = h1;
  unsigned long probe = 0;

  bool empty, equal = FALSE;

  while (!(empty = is_empty(h)) &&
	 !(equal = in->compare(&table[h])) && (probe < table_size)) {
    h = (h1 + probe * h2) % table_size;	// double hashing
    probe++;
  }
  if (empty) {			/* Go ahead and insert the element. */
    table[h] = *in;
    in = &table[h];
    Full->set(h);
    num_elts++;
    return FALSE;
  } else if (equal) {
    in = &table[h];
    return TRUE;
  } else {
    Error.Notrace("Closed hash table full.");
    return FALSE;		/* it doesn\'t matter, but it shuts up g++. */
  }
};

void path_set::print_capacity(void)
{
}

aux_cache::aux_cache(unsigned long memory_bytes,
		     unsigned max_ht_chain_length)
:num_elts(0),
num_collisions(0),
ht_overwrite(0),
max_ht_chain_length(max_ht_chain_length), num_called(0), num_failed(0)
{
  table_size =
      NextPrime((unsigned long) ((memory_bytes) /
				 sizeof(state_prob_hor_form)));
  table = new state_prob_hor_form[table_size];
  Full = new dynBitVec(table_size);
}

aux_cache::~aux_cache()
{
  delete[]table;		// only works for newer g++ versions
  delete Full;
}


bool aux_cache::try_to_evaluate(state_prob_hor_form * in, unsigned h,
				bool & result)
{
  if (table[h]._horizon < in->_horizon
      && table[h]._probability > in->_subformula->prob_bound) {
    if (in->_subformula->ord == PCTL_G) {
      result = TRUE;
      return TRUE;
    } else if (in->_subformula->ord == PCTL_LEQ) {
      result = FALSE;
      return TRUE;
    }
  } else if (table[h]._horizon < in->_horizon &&
	     (table[h]._probability > in->_subformula->prob_bound ||
	      double_equal(table[h]._probability,
			   in->_subformula->prob_bound))) {
    if (in->_subformula->ord == PCTL_GEQ) {
      result = TRUE;
      return TRUE;
    } else if (in->_subformula->ord == PCTL_L) {
      result = FALSE;
      return TRUE;
    }
  } else if (table[h]._horizon > in->_horizon
	     && table[h]._probability < in->_subformula->prob_bound) {
    if (in->_subformula->ord == PCTL_L) {
      result = TRUE;
      return TRUE;
    } else if (in->_subformula->ord == PCTL_GEQ) {
      result = FALSE;
      return TRUE;
    }
  } else if (table[h]._horizon > in->_horizon &&
	     (table[h]._probability < in->_subformula->prob_bound ||
	      double_equal(table[h]._probability,
			   in->_subformula->prob_bound))) {
    if (in->_subformula->ord == PCTL_LEQ) {
      result = TRUE;
      return TRUE;
    } else if (in->_subformula->ord == PCTL_G) {
      result = FALSE;
      return TRUE;
    }
  }
  return FALSE;
}

bool aux_cache::try_to_evaluate(state_prob_hor_form * in, bool & result)
{
  unsigned long key = in->_state.hashkey();
  unsigned long h1 = key % table_size;
  unsigned long h2 = 1 + key % (table_size - 1);
  unsigned long h = h1;

  unsigned long probe = 0;

// no hash compaction, uses double hashing

  bool empty, equal = FALSE;

  while (!(empty = is_empty(h)) &&
	 !(equal = in->compare_st_form(&table[h])) &&
	 (probe < max_ht_chain_length)) {
    h = (h1 + probe * h2) % table_size;	// double hashing
    probe++;
  }
  while (!empty && equal && table[h]._horizon != in->_horizon) {
    if (try_to_evaluate(in, h, result))
      return result;
    h = (h1 + probe * h2) % table_size;	// double hashing
    probe++;
    if (!(empty = is_empty(h)))
      equal = in->compare_st_form(&table[h]);
  }
  if (!empty && equal && table[h]._horizon == in->_horizon) {
    switch (in->_subformula->ord) {
    case PCTL_L:
      result = table[h]._probability < in->_subformula->prob_bound;
      break;
    case PCTL_LEQ:
      result = (table[h]._probability < in->_subformula->prob_bound ||
		double_equal(table[h]._probability,
			     in->_subformula->prob_bound));
      break;
    case PCTL_G:
      result = table[h]._probability > in->_subformula->prob_bound;
      break;
    case PCTL_GEQ:
      result = (table[h]._probability > in->_subformula->prob_bound ||
		double_equal(table[h]._probability,
			     in->_subformula->prob_bound));
      break;
    default:
      Error.Notrace
	  ("Internal error: invalid value %d for in->_subformula->ord",
	   in->_subformula->ord);
      return FALSE;
    }
    return TRUE;
  } else
    return FALSE;
};

double aux_cache::simple_was_present(state_prob_hor_form * in)
{
  unsigned long key = in->_state.hashkey();
  unsigned long h1 = key % table_size;
  unsigned long h2 = 1 + key % (table_size - 1);
  unsigned long h = h1;

  unsigned long probe = 0;

// no hash compaction, uses double hashing

  bool empty, equal = FALSE;

  while (!(empty = is_empty(h)) &&
	 !(equal = in->compare_no_prob(&table[h])) &&
	 (probe < max_ht_chain_length)) {
    h = (h1 + probe * h2) % table_size;	// double hashing
    num_collisions++;
    probe++;
  }
  if (!empty && equal && table[h]._horizon == in->_horizon)
    return table[h]._probability;
  else
    return -1.0;
};

bool aux_cache::insert(state_prob_hor_form * in)
{
  unsigned long key = in->_state.hashkey();
  unsigned long h1 = key % table_size;
  unsigned long h2 = 1 + key % (table_size - 1);
  unsigned long h = h1;

  unsigned long probe = 0;

// no hash compaction, uses double hashing

  bool empty, equal = FALSE;
  const float param = 0.05;

  num_called++;

  while (!(empty = is_empty(h)) &&
	 !(equal = in->compare_no_prob(&table[h])) &&
	 (probe < max_ht_chain_length)) {
    h = (h1 + probe * h2) % table_size;	// double hashing
    num_collisions++;
    probe++;
  }
  if (probe == max_ht_chain_length) {
    num_failed++;
    if (args->verbose.value > 3)
      printf("num_failed:%lu num_called:%lu NumStates:%lu\n", num_failed,
	     num_called, StateSet->NumElts());
  }
  if (num_failed >= param * num_called) {
    max_ht_chain_length *= 2;
    if (args->verbose.value > 3)
      printf("\n\n\nmax_ht_changed from %u to %u\n\n\n\n",
	     max_ht_chain_length / 2, max_ht_chain_length);
    if (max_ht_chain_length >= table_size / 2)
      return FALSE;
    num_failed = num_called = 0;
  }
  if (empty) {			/* Go ahead and insert the element. */
    table[h] = *in;
    Full->set(h);
    num_elts++;
    return TRUE;
  } else if (in->compare_st_form(&table[h])
	     && table[h]._horizon < in->_horizon) {
    table[h] = *in;
    return TRUE;
  }
  return TRUE;
};
