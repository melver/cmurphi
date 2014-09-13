/**CHeaderFile*****************************************************************

  FileName    [mu_hash.hpp]

  Synopsis    [Header file for hashing functions]

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

class hash_function {
public:
  hash_function(int vec_size);
  ~hash_function();
#if __WORDSIZE == 32
  unsigned long *hash(state * s, bool valid);
#else
  unsigned int *hash(state * s, bool valid);
#endif
private:
#if __WORDSIZE == 32
  unsigned long *hashmatrix;
#else
  unsigned int *hashmatrix;
#endif
  int vec_size;
  unsigned char *oldvec;
#if __WORDSIZE == 32
  unsigned long key[3];
#else
  unsigned int key[3];
#endif
};
