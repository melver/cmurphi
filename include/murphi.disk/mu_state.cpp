/**CFile***********************************************************************

  FileName    [mu_state.cpp]

  Synopsis    [File for queue and hash table]

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

/****************************************
  There are 3 groups of implementations:
  1) bit vector
  2) class StatePtr and state related stuff
  3) state queue and stack
  4) state set
  ****************************************/

#include <limits.h>

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
