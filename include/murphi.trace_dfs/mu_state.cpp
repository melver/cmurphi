/**CFile***********************************************************************

  FileName    [mu_state.cpp]

  Synopsis    [File for queue and hash table]

  Author      [Igor Melatti]

  Copyright   [
  This file is part of the original verifier package of CMurphi. 
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

#define BITUNSIGNED 32		//sizeof(Unsigned32)*CHAR_BIT

bool StatePtr::compare(state * s)
{				// compare the state I point to with s
#ifdef HASHC
  if (args->trace_file.value) {
#if __WORDSIZE == 32
    unsigned long *
#else
    unsigned int *
#endif
	key = h3->hash(s, FALSE);
#if __WORDSIZE == 32
    unsigned long
#else
    unsigned int
#endif
	c1 = key[1] &
#if __WORDSIZE == 32
	((~0UL) <<
	 (args->num_bits.value >
	  BITUNSIGNED ? 0UL : BITUNSIGNED - args->num_bits.value));
#else
	((~0) <<
	 (args->num_bits.value >
	  BITUNSIGNED ? 0 : BITUNSIGNED - args->num_bits.value));
#endif
#if __WORDSIZE == 32
    unsigned long
#else
    unsigned int
#endif
	c2 = key[2] & (args->num_bits.value >
#if __WORDSIZE == 32
		       BITUNSIGNED ? (~0UL) << (2 * BITUNSIGNED -
						args->num_bits.
						value) : 0UL);
#else
		       BITUNSIGNED ? (~0) << (2 * BITUNSIGNED -
					      args->num_bits.value) : 0);
#endif

    return (c1 == TraceFile->read(lv)->c1 &&
	    c2 == TraceFile->read(lv)->c2);
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
  stateArray = new state [max_active_states];
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
    stateArray[ind].print();
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
    retval = &stateArray[front];
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
    return &stateArray[front];
  } else {
    Error.Notrace("Internal: Attempt to top() empty state queue.", "", "");
    return NULL;
  }
}

void state_stack::enqueue(state * e)
{
  if (num_elts < max_active_states) {
    front = front == 0 ? max_active_states - 1 : front - 1;
    stateArray[front] = *e;
    nextrule_to_try[front] = 0;
    num_elts++;
  } else {
    Error.Notrace("Internal: Too many active states.");
  }
}

void state_stack::print_trace_dfs(NextStateGenerator *generator)
{
  unsigned long i;
  cout << "Starting from state:\n";
  StateCopy(workingstate, &stateArray[max_active_states - 1]);
  theworld.print();
  cout << "----------\n\n";
  for (i = max_active_states - 2; i > front; i--) {
    StateCopy(workingstate, &stateArray[i]);
    cout << "Rule "
	<< generator->Name(nextrule_to_try[i + 1] - 1)
	<< " fired.\n";
    if (args->full_trace.value)
      theworld.print();
    else
      theworld.print_diff(&stateArray[i + 1]);
    cout << "----------\n\n";
  }
  cout << "The last state of the trace (in full) is:\n";
  StateCopy(workingstate, &stateArray[front]);
  stateArray[front].print();
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

#if __WORDSIZE == 32
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
#else				// 64 bit version
#include <math.h>
state_set::state_set(unsigned long table_size)
:  
table_size(table_size), num_elts(0), num_elts_reduced(0), num_collisions(0)
{
#ifndef HASHC
  table = new state[table_size];
#else
  assert(sizeof(Unsigned32) == 4);	// the implementation is pretty depen-
  // dent on the 32 bits for 1 integer
  unsigned long size =
      (unsigned long) ((double) table_size * args->num_bits.value /
		       BITUNSIGNED) + 3;
  bits_for_size =
      (unsigned int) floor(log((double) table_size) / log((double) 2)) + 1;
  if (args->print_64bit_info.value) {
    int amount = 3 * sizeof(Unsigned32) * CHAR_BIT - bits_for_size;
    printf
	("With %lu bytes of RAM, you can use at most %d bits (option -b) for the hash compaction\n",
	 args->mem.value, amount > 64 ? 64 : amount);
    printf("Value for bits_for_size: %d\n", bits_for_size);
    /* copied from Notrace */
    if (TraceFile != NULL)
      delete TraceFile;
    exit(1);
  }
  // higher precision necessary to avoid overflow
  // two extra elements needed in table
  if (bits_for_size >
      3 * sizeof(Unsigned32) * CHAR_BIT - args->num_bits.value)
    // in order to address an hash table entry, we may use the whole first int + what
    // remains of the other 2 ints when args->num_bits.value bits are subtracted
    Error.
	Notrace
	("Too many bits for the hash compaction (option -b); may be at most %d",
	 3 * sizeof(Unsigned32) * CHAR_BIT - bits_for_size);
  bits_for_size =
      bits_for_size <= BITUNSIGNED ? BITUNSIGNED : bits_for_size;

  table = new Unsigned32[size];
  for (unsigned long i = 0; i < size; i++)
    table[i] = (Unsigned32) 0;
#endif
  Full = new dynBitVec(table_size);
}
#endif

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
#if __WORDSIZE == 32
  unsigned long *key = h3->hash(in, valid);
  unsigned long h1 = key[0] % table_size;
  unsigned long h2;
  register unsigned long h = h1;
  register unsigned long num_bits = args->num_bits.value;
  register unsigned long mask1 =
      (~0UL) << (num_bits > 32 ? 0 : 32 - num_bits);
  register unsigned long mask2 =
      num_bits > 32 ? (~0UL) << (64 - num_bits) : 0UL;
  register unsigned long addr, offset;
  register unsigned long c1 = key[1] & mask1;
  register unsigned long c2 = key[2] & mask2;
  register unsigned long t1, t2;
#else
  unsigned int *key = h3->hash(in, valid);
  unsigned long h;
  unsigned long h2;
  register unsigned int num_bits = args->num_bits.value;
  register unsigned int
      mask1 =
      (~0) << (num_bits > BITUNSIGNED ? 0 : BITUNSIGNED - num_bits);
  register unsigned int mask2 =
      num_bits > BITUNSIGNED ? (~0) << (2 * BITUNSIGNED - num_bits) : 0;
  register unsigned long addr, offset;
  register unsigned int c1 = key[1] & mask1;
  register unsigned int c2 = key[2] & mask2;
  register unsigned int t1, t2;
#endif
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

#if __WORDSIZE == 32
  h2 = 1 + c1 % (table_size - 1);	// calculation uses compressed value
#else
  if (bits_for_size == BITUNSIGNED) {
    h = key[0] % table_size;
    h2 = 1 + c1 % (table_size - 1);	// calculation uses compressed value
  } else {			// bits_for_size > BITUNSIGNED
    /* LSB is at the right
       key[2]   key[1]   key[0]
       hhzzzzzz hhhhhhhh xxxxxxxx

       h =  00zzzzzzxxxxxxxx
       (not taking into account % table_size)
     */
    h = ((unsigned long) key[0] +
	 (((unsigned long) (key[2] %
			    (1 << (bits_for_size - BITUNSIGNED)))) <<
	  BITUNSIGNED)) % table_size;
    /* LSB is at the right
       c2       c1
       xx000000 yyyyyyyy

       h2 = 000000xxyyyyyyyy
       (not taking into account % (table_size - 1) and the initial 1 +)
     */
    h2 = 1 + (((unsigned long) c1) + (((unsigned long) (c2 >> (2 * BITUNSIGNED - num_bits))) << BITUNSIGNED)) % (table_size - 1);	// calculation uses compressed value
  }
#endif
  // search - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  do {
#if __WORDSIZE == 32
    // calculate address and offset in table
    // 32 bit arithmetic not sufficient and may cause overflow
    // addr = (h*num_bits) / 32
    // offset = (h*num_bits) % 32
    // Thus, h*num_bits is first done on the least 16 bits, and then on the
    // remaining 16 bits; since we have to divide by 32, we ignore the least 5
    // bits of the result
    offset = (h & 0xffffUL) * num_bits;
    addr = (((h >> 16) * num_bits) << 11) + (offset >> 5);
    offset &= 0x1fUL;
#else
    // 64 bit arithmetic should always be sufficient (the limit should be
    // 2^64/2^6 = 2^58, that can address a table with 2^58*4 = 2^60 bytes,
    // that is to say 1 EB (exabyte) of RAM!)
    addr = (h * num_bits) / BITUNSIGNED;
    offset = (h * num_bits) % BITUNSIGNED;
#endif

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
#if __WORDSIZE == 32
    offset = (h & 0xffffUL) * num_bits;
    addr = (((h >> 16) * num_bits) << 11) + (offset >> 5);
    offset &= 0x1fUL;
#else
    // 64 bit arithmetic should always be sufficient
    addr = (h * num_bits) / BITUNSIGNED;
    offset = (h * num_bits) % BITUNSIGNED;
#endif
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
