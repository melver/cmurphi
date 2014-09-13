/**CHeaderFile*****************************************************************

  FileName    [mu_statecl.hpp]

  Synopsis    [Header file for class state]

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

#if __WORDSIZE == 32
#ifndef ALIGN
#define BLOCKS_IN_WORLD (((BITS_IN_WORLD + (4*BITS( BIT_BLOCK )) - 1 ) / (4*BITS(BIT_BLOCK )))*4)
#else
#define BLOCKS_IN_WORLD (((BITS_IN_WORLD + (4*BITS( BIT_BLOCK )) - 1 ) / (4*BITS(BIT_BLOCK )))*4)
#endif
#else
#define BLOCKS_IN_WORLD (((BITS_IN_WORLD + (8*BITS( BIT_BLOCK )) - 1 ) / (8*BITS(BIT_BLOCK )))*8)
#endif

/****************************************   // added by Uli
  class for pointer to previous state
  ****************************************/

class state;

class StatePtr {
private:
  union {
    state *sp;			// real pointer
    unsigned long lv;		// state number used in trace info file
  };

  // StatePtr is a member of the class state, so try to avoid adding
  // data members

  inline void sCheck();
  inline void lCheck();

public:
   StatePtr() {
  } StatePtr(state * s);
  StatePtr(unsigned long l);

  void set(state * s);
  void set(unsigned long l);
  void clear();
  state *sVal();
  unsigned long lVal();

  StatePtr previous();		// return StatePtr to previous state
  bool isStart();		// check if I point to a startstate
  bool compare(state * s);	// compare the state I point to with s

};


/****************************************
  class state.
  ****************************************/
// Warning: DO NOT add member variables to this class unless
// you know exactly what you're doing. Since an instance of the
// state class is created for each table entry during
// initialization, adding stuff here will eat lots of memory.
// Uli: this is only true if one does not use hash compaction

#ifdef HASHC
hash_function *h3;
#endif

class state {
public:
  BIT_BLOCK bits[BLOCKS_IN_WORLD];
  StatePtr previous;		// state from which this state was reached.
#ifdef HASHC
#ifdef ALIGN
#if __WORDSIZE == 32
  // Uli: only in the aligned version the hashkeys are stored with the state
  unsigned long hashkeys[3];
#else
  unsigned int hashkeys[3];
#endif
#endif
#endif

   state()
  :previous() {
    memset((void *) bits, 0, (size_t) BLOCKS_IN_WORLD);	// Uli: avoid bzero
  };
  state(state * s) {
    StateCopy(this, s);
  };

  friend void StateCopy(state * l, state * r);
  friend int StateCmp(state * l, state * r);
  friend void copy_state(state * &s);
#ifdef HASHC
  friend class hash_function;	//gdp: fix for newer g++
#endif
//friend unsigned long* hash_function::hash(state*, bool);
// friend bool StateEquivalent(state * l, state * r);   // Uli: not necessary

  // get it with Horner\'s method. 
  // size  <= the number of bits in an integer - 1
#ifndef ALIGN
  inline int get(const position * w) const {	// Uli: const added
    unsigned int val, *l;
     l = (unsigned int *) (bits + w->longoffset);
     val = (l[0] & w->mask1) >> w->shift1;
    if (w->mask2)
       val |= (l[1] & w->mask2) << w->shift2;
     return (int) val;
  }
#else
  inline int get(int byteloc) const {
    return bits[byteloc];
  };
  inline int getlong(int byteloc) const {
    unsigned int val;
    unsigned char *p = (unsigned char *) &bits[byteloc];
     val = *p++;
     val |= *p++ << 8;
     val |= *p++ << 16;
     val |= *p++ << 24;
     return (int) val;
  }
#endif
  // set a field to value // size  <= the number of bits in an integer - 1
#ifndef ALIGN
  inline void set(position * w, int value) {
    unsigned int val, *l;
    l = (unsigned int *) (bits + w->longoffset);
    val = value << w->shift1;
    l[0] = (l[0] & ~w->mask1) | val;
    if (w->mask2) {
      val = (value >> w->shift2) & w->mask2;
      l[1] = (l[1] & ~w->mask2) | val;
    }
  };
#else
  inline void setlong(int byteloc, int value) {
    unsigned char *p = (unsigned char *) &bits[byteloc];
    *p++ = (unsigned) value & 0xff;
    *p++ = ((unsigned) value & 0xff00) >> 8;
    *p++ = ((unsigned) value & 0xff0000) >> 16;
    *p++ = ((unsigned) value & 0xff000000) >> 24;
  };
#endif

  // key for hash function, changes by Uli

  /* used in hashc with cache murphi */


#if __WORDSIZE == 32
#define LOG2_UL 2
#else
#define LOG2_UL 3
#endif
  unsigned long hashkey(void) const {
    unsigned long sum = 0;
    unsigned long *pt = (unsigned long *) bits;

    for (int i = BLOCKS_IN_WORLD >> LOG2_UL; i > 0; i--) {
      sum += *pt++;
    } return sum;
  }




  // operator== and operator!= only consider the bitvectors,
  // not the other components of a state. 
  inline bool operator ==(state & other) const {
    return (memcmp(&bits, &other.bits, BLOCKS_IN_WORLD) == 0);
  };
  inline bool operator !=(state & other) const {
    return (memcmp(&bits, &other.bits, BLOCKS_IN_WORLD) != 0);
  };

  // scribbles over the current world variables. 
  void print();

  // symmetry reduction
  void Normalize();

  // multiset reduction
  void MultisetSort();

};
