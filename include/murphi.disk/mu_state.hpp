/**CHeaderFile*****************************************************************

  FileName    [mu_state.hpp]

  Synopsis    [Header file for queue and hash table]

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

#ifndef _STATE_
#define _STATE_

/****************************************
  There are three different declarations:
  1) state
  2) dynBitVec
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

  inline void clearall() {
    memset(v, 0, NumBytes());
  }
  inline void setall() {
    memset(v, 1, NumBytes());
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

#endif
