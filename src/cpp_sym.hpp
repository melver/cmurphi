/**CHeaderFile*****************************************************************

  FileName    [cpp_sym.hpp]

  Synopsis    [Header file for symmetry reduction]

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

#ifndef __CPP_SYM_H__
#define __CPP_SYM_H__

#define MAX_NUM_SCALARSET 512
#define MAX_NUM_GLOBALS 512
#define TRUNCATE_LIMIT_FOR_LIMIT_FUNCTION 1

class symmetryclass {
  stelist *scalarsetlist;
  stelist *varlist;
  int num_scalarset;
  unsigned long size_of_set;
  int size[MAX_NUM_SCALARSET];
  unsigned long factorialsize[MAX_NUM_SCALARSET];

  bool no_need_for_perm;

  unsigned long factorial(int n);

  void setup();
  void generate_set_class();
  void generate_permutation_class();
  void generate_symmetry_class();

  void generate_exhaustive_fast_canonicalization();
  void generate_heuristic_fast_canonicalization();
  void generate_heuristic_small_mem_canonicalization();
  void generate_heuristic_fast_normalization();

  void generate_symmetry_code();
  void generate_match_function();

  void set_var_list(ste * globals);

public:
   symmetryclass():scalarsetlist(NULL), varlist(NULL),
      no_need_for_perm(TRUE) {
  };
  void add(ste * s) {
    scalarsetlist = new stelist(s, scalarsetlist);
  };
  int getsize() {
    return size_of_set;
  }

  void generate_code(ste * globals);
  void generate_symmetry_function_decl();
};

bool is_simple_scalarset(typedecl * t);

class charlist {
public:
  char *string;
  charlist *next;
  typedecl *e;

   charlist(char *str, charlist * nxt):string(str), next(nxt) {
  } charlist(char *str, typedecl * e, charlist * nxt):string(str),
      next(nxt), e(e) {
  }
  virtual ~ charlist() {
    delete string;
    delete next;
  }

};

#endif
