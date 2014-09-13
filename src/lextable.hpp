/**CHeaderFile*****************************************************************

  FileName    [lextable.hpp]

  Synopsis    [Header file for lexical handling]

  Author      [Igor Melatti]

  Copyright   [
  This file is part of the compiler package of CMurphi. 
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

#ifndef __LEXTABLE_H__
#define __LEXTABLE_H__

/********************
  constants
  ********************/
#define LEXTABLESIZE 1024	/* must be a power of two. */
#define RESERVETABLESIZE 512	/* must be a power of two. */

/********************
  class lextable
         -- hash table with open chaining for lex's name table. 
  ********************/
class lextable {
  lexid *table[LEXTABLESIZE];	// table for user defined words
  lexid *rtable[RESERVETABLESIZE];	// table for reserved words
  int hash(const char *str) const;	// hash a string into an integer. 
  int rehash(int h) const;	// if table[h] is taken, compute a new value. 
public:
  // initializer
   lextable(void);

  // supporting routines
  lexid *enter(const char *str, int lextype = ID);
  // return a pointer to the id lexid associated with str, creating the
  // lexid if necessary.
  bool reserved(const char *str);	// check to see if it is a reserved word
  lexid *enter_reserved(const char *str, int lextype = ID);
  // return a pointer to the id lexid associated with str, creating the
  // lexid if necessary.
};

/********************
  extern variables
  ********************/
extern lextable ltable;

#endif
