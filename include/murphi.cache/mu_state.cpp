/**CFile***********************************************************************

  FileName    [mu_state.cpp]

  Synopsis    [File for queue and hash table]

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

/****************************************
  There are 3 groups of implementations:
  1) bit vector
  2) class StatePtr and state related stuff
  3) state queue and stack
  4) state set
  ****************************************/

#include <limits.h>

#define SSQ_PAGING_FILE_TOP "SSQ_PAGING_FILE_1"
#define SSQ_PAGING_FILE_BOTTOM "SSQ_PAGING_FILE_2"

//char paging_file_top_name[500], paging_file_bottom_name[500];

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
:  max_active_states(mas)
{
  stateArray = new state[max_active_states];

  //for ( long i = 0; i < max_active_states; i++)   // Uli: avoid bzero
  //stateArray[i] = NULL;

#ifndef SPLITFILE
  /*if ((paging_file_top = fopen(make_unique_filename ("top"), "w+b")) == NULL) {
     Error.Notrace ("Internal: Error creating top paging file.");
     }

     if ((paging_file_bottom = fopen(make_unique_filename ("bottom"), "w+b")) == NULL) {
     Error.Notrace ("Internal: Error creating bottom paging file.");
     } */

  if ((paging_file_top = tmpfile()) == NULL) {
    Error.Notrace("Internal: Error creating top paging file.");
  }

  if ((paging_file_bottom = tmpfile()) == NULL) {
    Error.Notrace("Internal: Error creating bottom paging file.");
  }
#else
  paging_file_top = new splitFile(SPLITFILE_LEN, false);
  paging_file_bottom = new splitFile(SPLITFILE_LEN, false);

  if (!
      (paging_file_top->
       open(paging_file_top->make_unique_filename(SSQ_PAGING_FILE_TOP),
	    "w+b"))) {
    Error.
	Notrace("Internal: Error creating top paging file for the queue.");
  }

  if (!
      (paging_file_bottom->
       open(paging_file_bottom->
	    make_unique_filename(SSQ_PAGING_FILE_BOTTOM), "w+b"))) {
    Error.
	Notrace
	("Internal: Error creating bottom paging file for the queue.");
  }
#endif

  num_elts_head = num_elts_tail = 0;

  head_begin = 0;
  tail_begin = max_active_states / 2;

  head_size = max_active_states / 2;
  tail_size = max_active_states - head_size;

  global_front = global_rear = front = rear = 0;
}


state_queue::~state_queue()
{
  delete[OLD_GPP(max_active_states)] stateArray;	// Should be delete[].

#ifndef SPLITFILE
  fclose(paging_file_top);	//rmtmp();
  fclose(paging_file_bottom);	//rmtmp();
#else

  paging_file_top->close();	//rmtmp();
  paging_file_bottom->close();	//rmtmp();

  delete paging_file_top;
  delete paging_file_bottom;
#endif
}

int
 state_queue::BytesForOneState(void)
{

#ifdef VER_PSEUDO
  // Pseudo ver: ptr + malloced state + approx. malloc&new overhead.
  return sizeof(state *) + sizeof(state) + 8;
#else
#if 0
  /* This is True for our queue, but leads to a wrong NumStates. et */
  return sizeof(state);		/* Our queue contains states, not ptr to states */
#endif

  /* This is FALSE for our queue, but,
     with the adj the queue creation leads to a correct NumStates. et  */
  return sizeof(state *);	/* Full ver: only a ptr to state. */
#endif
}


void state_queue::Print(void)
{
  unsigned long i;

  for (i = 0; i < num_elts_head; i++) {
    // convert to print in unsigned long format?
    cout << "State " << i << " [" << head_begin + i << "]:\n";
    stateArray[head_begin + i].print();
  }

  for (i = 0; i < num_elts_tail; i++) {
    // convert to print in unsigned long format?
    cout << "State " << i << " [" << tail_begin + i << "]:\n";
    stateArray[tail_begin + i].print();
  }
}


void state_queue::enqueue(state * &e)
{

  if (num_elts_tail >= tail_size) {	//memory full: reclaim more space by swapping out the current queue
    ReclaimFreeSpace();
  }

  /*
     at this point, ReclaimFreeSpace has obtained new space in the queue and
     set the offsets (front, rear, ...) accordingly; so we proceed with
     the insertion without checking...
   */


  StateCopy(&stateArray[tail_begin + rear], e);
  e = &stateArray[tail_begin + rear];

  rear++;
  num_elts_tail++;
}

state *state_queue::dequeue(void)
{
  state *retval;

  if (num_elts_head <= 0) {
    QueueEmptyFault();
  }

  retval = &stateArray[head_begin + front];
  front++;
  num_elts_head--;

  return retval;
}

state *state_queue::top(void)
{
  if (num_elts_head <= 0) {
    QueueEmptyFault();
  }

  return &stateArray[head_begin + front];
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++

void state_queue::ReclaimFreeSpace()
{

#ifndef SPLITFILE
  global_rear +=
      fwrite(&stateArray[tail_begin], sizeof(state), tail_size,
	     paging_file_bottom);

#else
  global_rear +=
      paging_file_bottom->write(&stateArray[tail_begin], sizeof(state),
				tail_size);
#endif

  num_elts_tail = 0;
  rear = 0;

  /* too expensive ... may we can do without. et  */
#if 0
  //for ( long i = 0; i < tail_size; i++)   // Uli: avoid bzero
  //stateArray[tail_begin + i] = NULL;
#endif

}

void copy_file(FILE * src, FILE * dest)
{
  char c;
  long curpos = ftell(src);
  fseek(src, 0, SEEK_SET);
  while (fscanf(src, "%c", &c) != EOF)
    fprintf(dest, "%c", c);
  fseek(src, curpos, SEEK_SET);
}


void state_queue::QueueEmptyFault()
{
#ifndef SPLITFILE
  size_t read = fread(&stateArray[head_begin], sizeof(state), head_size,
		      paging_file_top);
#else
  size_t read =
      paging_file_top->read(&stateArray[head_begin], sizeof(state),
			    head_size);
#endif

  if (read > 0 && global_front >= read) {	//ok, some states are swapped in

    num_elts_head = read;
    global_front -= read;
  } else if (read > 0 && global_front > 0 && global_front < read) {
    // same as above, but may have read more than allowed
    num_elts_head = global_front;
    global_front = 0;
  } else if (global_rear > 0) {	//paging_file_top is empty, but paging_file_bottom is not
#ifndef SPLITFILE
    fclose(paging_file_top);

    paging_file_top = paging_file_bottom;
    fseek(paging_file_top, 0, SEEK_SET);	//move to the beginning of the queue
    global_front = global_rear;

    if ((paging_file_bottom = tmpfile()) == NULL) {
      Error.Notrace("Internal: Error creating bottom paging file.");
    }
    global_rear = 0;		//bottom file is empty

    size_t read = fread(&stateArray[head_begin], sizeof(state), head_size,
			paging_file_top);

    num_elts_head = read;
    global_front -= read;
#else
    splitFile *fswap;
    fswap = paging_file_top;
    paging_file_top = paging_file_bottom;
    paging_file_bottom = fswap;
    paging_file_top->seek(0, SEEK_SET);	//move to the beginning of the queue
    paging_file_bottom->seek(0, SEEK_SET);	//reset bottom queue

    global_front = global_rear;
    global_rear = 0;		//bottom file is empty

    //now bottom entries are top entries and bottom file is empty. Reload a block!
    size_t read =
	paging_file_top->read(&stateArray[head_begin], sizeof(state),
			      head_size);

    num_elts_head = read;
    global_front -= read;
#endif
  } else if (num_elts_tail > 0) {	//paging_file_top AND paging_file_bottom are empty

    /* the disk queue is ended. this means that the only states we have
       to explore are the ones in the current tail window */
    int swap = tail_begin;
    tail_begin = head_begin;
    head_begin = swap;

    swap = tail_size;
    tail_size = head_size;
    head_size = swap;

    num_elts_head = num_elts_tail;
    num_elts_tail = 0;
    rear = 0;
  } else {			//no more states in both swap files, and the memory is empty: why do we call again?
    Error.Notrace("Internal: Attempt to read an empty state queue.");
  }

  front = 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++


void state_stack::enqueue(state * e)
{				/*
				   if( num_elts < max_active_states )
				   {
				   front = front == 0 ? max_active_states-1 : front-1;
				   stateArray[ front ] = e;
				   nextrule_to_try[ front ] = 0;
				   num_elts++;
				   }
				   else
				   {
				   Error.Notrace( "Internal: Too many active states." );
				   }
				 */
}

/****************************************   // changes by Uli
  The Stateset implementation for recording all the states found.
  ****************************************/


#if __WORDSIZE == 32
state_set::state_set(unsigned long table_size)
:table_size(table_size), num_elts(0), num_elts_reduced(0),
num_collisions(0), ht_overwrite(0)
{

#ifndef HASHC
  table = new state[table_size];
#else
  assert(sizeof(Unsigned32) == 4);	// the implementation is pretty depen-
  // dent on the 32 bits

  unsigned long size =
      (unsigned long) ((double) table_size * args->num_bits.value /
		       BITUNSIGNED) + 3;
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
:table_size(table_size), num_elts(0), num_elts_reduced(0),
num_collisions(0)
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



/*
**************************
No ordering in keys when using
HASHC

***************************
*/


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

  /* new. et. */
  unsigned long base = in->hashkey();
  unsigned long h1 = base % table_size;
  unsigned long h2 = 1 + base % (table_size - 1);

  register unsigned long h = h1;
  register unsigned long num_bits = args->num_bits.value;
  register unsigned long mask1 =
      (~0UL) << (num_bits > BITUNSIGNED ? 0 : BITUNSIGNED - num_bits);
  register unsigned long mask2 =
      num_bits >
      BITUNSIGNED ? (~0UL) << (2 * BITUNSIGNED - num_bits) : 0UL;
  register unsigned long addr, offset;
  register unsigned long c1 = key[1] & mask1;
  register unsigned long c2 = key[2] & mask2;
  register unsigned long t1, t2;
#else
  unsigned int *key = h3->hash(in, valid);

  unsigned long base = in->hashkey();
  unsigned long h1 = base % table_size;
  unsigned long h2 = 1 + base % (table_size - 1);
  register unsigned long h = h1;

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

#else				/* VER_PSEUD */

  unsigned long probe = 0;


#ifndef HASHC
// no hash compaction, uses double hashing

  bool empty, equal = FALSE;

  while (!(empty = is_empty(h)) &&
	 !(equal = (*in == table[h])) && (probe < MAX_HT_CHAIN_LENGTH)) {
    h = (h1 + probe * h2) % table_size;	// double hashing
    num_collisions++;
    probe++;
  }
  if (empty) {			/* Go ahead and insert the element. */

    table[h] = *in;
    in = &table[h];
    Full->set(h);
    num_elts++;


    //copy_state(in);   // make copy of state

    return FALSE;
  } else if (equal) {
    in = &table[h];

    /*
       no need to make copy of state when returning true !!! et
     */

    return TRUE;
  } else {			/* probe >= table_size here !!! et */



/* 
pick a non busy state for overwriting:
Since max_active_states < table_size
there is at least one such state 
(hyp: gPercentActive <= 0.5)
et
*/

    probe = random.next() % MAX_HT_CHAIN_LENGTH;
    h = (h1 + probe * h2) % table_size;

    table[h] = *in;
    in = &table[h];

/* we use num_elts to count visited states thus ++ ok here */
    num_elts++;

    /* ++ unresolved conflicts. et */
    ht_overwrite++;

    //copy_state(in);   // make copy of state

    return FALSE;


  }

#else				/*  HASHC  */

// hash compaction, uses ordered hashing
// the state-insertion is done in two steps: search and insertion

  // search - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  do {

    h = (h1 + probe * h2) % table_size;	// double hashing


#if __WORDSIZE == 32
    // calculate address and offset in table
    // 32 bit arithmetic not sufficient and may cause overflow
    // addr = (h*num_bits) / 32
    // offset = (h*num_bits) % 32
    offset = (h & 0xffffUL) * num_bits;
    addr = (((h >> 16) * num_bits) << 11) + (offset >> 5);
    offset &= 0x1fUL;
#else
    // 64 bit arithmetic should always be sufficient
    addr = (h * num_bits) / BITUNSIGNED;
    offset = (h * num_bits) % BITUNSIGNED;
#endif

    if (is_empty(h)) {
      Full->set(h);
      break;			// search unsuccessful
    }

    // read compressed value from table
    t1 = (table[addr] << offset |
	  (offset == 0 ? 0 : table[addr + 1] >> (32 - offset)))
	& mask1;
    t2 = (table[addr + 1] << offset |
	  (offset == 0 ? 0 : table[addr + 2] >> (32 - offset)))
	& mask2;


    if (t1 == c1 && t2 == c2) {
      return TRUE;		// search successful
    }

    /* update h */

    num_collisions++;
    probe++;



    if (probe >= MAX_HT_CHAIN_LENGTH_HC)
      /*  overwriting   */
    {
      /* ++ unresolved conflicts. et */
      ht_overwrite++;

      /* pick h at random. et. */
      probe = random.next() % MAX_HT_CHAIN_LENGTH_HC;

      h = (h1 + probe * h2) % table_size;


#if __WORDSIZE == 32
      offset = (h & 0xffffUL) * num_bits;
      addr = (((h >> 16) * num_bits) << 11) + (offset >> 5);
      offset &= 0x1fUL;
#else
      // 64 bit arithmetic should always be sufficient
      addr = (h * num_bits) / BITUNSIGNED;
      offset = (h * num_bits) % BITUNSIGNED;
#endif

      /* reset table */
      table[addr] &= ~(mask1 >> offset);
      table[addr + 1] &=
	  ~((offset == 0 ? 0 : mask1 << (32 - offset)) | mask2 >> offset);
      table[addr + 2] &= ~(offset == 0 ? 0 : mask2 << (32 - offset));



      break;
    }

  } while (TRUE);


  // write trace info
  if (args->trace_file.value)
    TraceFile->write(c1, c2, in->previous.lVal());


  // insertion - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /* probe <= MAX_HT_CHAIN_LENGTH_HC  */


  //copy_state(in);   // make copy of state


  if (permanent)
    num_elts_reduced++;

  /* ++ visited states */
  num_elts++;


  /* insert */


  /* store new value */
  table[addr] |= c1 >> offset;	// insertion
  table[addr + 1] |=
      (offset == 0 ? 0 : c1 << (32 - offset)) | c2 >> offset;
  table[addr + 2] |= (offset == 0 ? 0 : c2 << (32 - offset));


  return FALSE;

#endif				/* HASHC  */

#endif				/* VER_PSEUD */
};

bool state_set::was_present(state * &in, bool valid, bool permanent)
{
  if (args->symmetry_reduction.value)
    in->Normalize();
  if (args->multiset_reduction.value && !args->symmetry_reduction.value)
    in->MultisetSort();
  return simple_was_present(in, valid, permanent);
}


int state_set::bits_per_state()
{
#ifndef HASHC
  return 8 * sizeof(state);
#else
  return args->num_bits.value;
#endif
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


void
 state_set::print_capacity(void)
{
  cout << "\t* A cache memory is used to store the state space.\n  ";
  if (args->max_collrate.value > 0) {
    cout << "\t  The highest acceptable collision rate is "
	<< ((double) args->max_collrate.value / 100) << "\n"
	<< "\t   * Use option \"-maxc\" to increase this, if necessary.\n";
  }
  cout <<
      "\t* The memory allocated for the state cache and state queue is\n\t  ";
  if (args->mem.value > 1000000)
    cout << (args->mem.value / 1000000) << " Mbytes.\n";
  else
    cout << (args->mem.value / 1000) << " kbytes.\n";

#ifndef HASHC
  cout << "\t  With two words of overhead per state, the size of\n"
      << "\t  the state cache is "
      << table_size << " states.\n"
      <<
      "\t   * Use option \"-k\" or \"-m\" to increase this, if necessary.\n";
#else
  cout << "\t  With states hash-compressed to "
      << args->num_bits.value << " bits, the size of\n"
      << "\t  the state cache is "
      << table_size << " states.\n"
      <<
      "\t   * Use option \"-k\" or \"-m\" to increase this, if necessary.\n";
#endif
}
