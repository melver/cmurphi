/**CHeaderFile*****************************************************************

  FileName    [mu_util_dep.hpp]

  Synopsis    [Header file class setofrules]

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
  There are 2 groups of declarations:
  1) setofrule and sleepset
  2) rule_matrix
  ****************************************/

/****************************************
  class setofrule and sleepset
  require RULES_IN_WORLD
  ****************************************/

#define BLOCKS_IN_SETOFRULES ( (RULES_IN_WORLD + BITS( BIT_BLOCK ) - 1 ) / \
			  BITS( BIT_BLOCK ))

/* RULES_IN_WORLD gets defined by the generated code. */
/* The extra addition is there so that we round up to the greater block. */

class setofrules {
protected:
  BIT_BLOCK bits[BLOCKS_IN_SETOFRULES];
  unsigned NumRules;		// Uli: unsigned short -> unsigned

  int Index(int i) const {
    return i / BITS(BIT_BLOCK);
  };
  int Shift(int i) const {
    return i % BITS(BIT_BLOCK);
  };
  int Get1(int i) const {
    return (bits[Index(i)] >> Shift(i)) & 1;
  };
  void Set1(int i, int val) {	/* Set bit i to the low bit of val. */
    if ((val & 1) != 0)
      bits[Index(i)] |= (1 << Shift(i));
    else
      bits[Index(i)] &= ~(1 << Shift(i));
  };

public:

  // set of rules manipulation
  friend setofrules interset(setofrules rs1, setofrules rs2);
  friend setofrules different(setofrules rs1, setofrules rs2);
  friend bool subset(setofrules rs1, setofrules rs2);

  // conflict set manipulation
  friend setofrules conflict(unsigned rule);

  setofrules()
:    NumRules(0) {
    for (int i = 0; i < BLOCKS_IN_SETOFRULES; i++)
      bits[i] = 0;
  };

  virtual ~ setofrules() {
  };

  bool in(int rule) const {
    return (bool) Get1(rule);
  };
  void add(int rule) {
    if (!in(rule)) {
      Set1(rule, TRUE);
      NumRules++;
    }
  };
  void remove(int rule) {
    if (in(rule)) {
      Set1(rule, FALSE);
      NumRules--;
    }
  }
  bool nonempty() {
    return (NumRules != 0);
  };
  int size() {
    return NumRules;
  };
  void print() {
    cout << "The set of rules =\t";
    for (int i = 0; i < RULES_IN_WORLD; i++)
      cout << (Get1(i) ? 1 : 0) << ',';
    cout << "\n";
  };

  // for simulation 
  void removeall() {
    for (int i = 0; i < RULES_IN_WORLD; i++)
      Set1(i, FALSE);
    NumRules = 0;
  };

  // for simulation 
  void includeall() {
    for (int i = 0; i < RULES_IN_WORLD; i++)
      Set1(i, TRUE);
    NumRules = RULES_IN_WORLD;
  };
  unsigned getnthrule(unsigned rule) {
    unsigned r = 0;
    int i = 0;
    while (1)
      if (Get1(i) && r == rule) {
	Set1(i, FALSE);
	NumRules--;
	return (unsigned) i;
      } else if (Get1(i)) {
	i++;
	r++;
      } else {
	i++;
      }
  };
};
