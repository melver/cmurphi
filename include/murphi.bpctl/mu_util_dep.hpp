/**CHeaderFile*****************************************************************

  FileName    [mu_util_dep.hpp]

  Synopsis    [Header file for class setofrules]

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
  double probabilities[RULES_IN_WORLD];	//      IM: to manage rules probabilities
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
  void add(int rule, double prob = (double) 1) {
    if (!in(rule)) {
      Set1(rule, TRUE);
      NumRules++;
    }
    probabilities[rule] = prob;	//      IM: added probability
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
  // IM: added prob
  double prob(int rule) {
    return probabilities[rule];
  }
};

#define STRICT_TOLERANCE 1e+1 * DBL_EPSILON
#define LOOSE_TOLERANCE 1e-05

bool
double_equal(double x, double y, bool strict = true, double tolerance =
	     LOOSE_TOLERANCE)
{
  if (strict)
    return (fabs(x - y) < STRICT_TOLERANCE);
  else
    return (fabs(x - y) < tolerance);
}

/* insertion sort (decreasing order by default) */
void Sort(unsigned *v, double *p, int dim)
{
  int i, j;
  double key;
  unsigned key_v;

  for (i = 1; i < dim; i++) {
    key = p[i];
    key_v = v[i];
    j = i;
#ifndef INCR_ORDER
    while ((j > 0) && (p[j - 1] < key)) {
#else
    while ((j > 0) && (p[j - 1] > key)) {
#endif
      v[j] = v[j - 1];
      p[j] = p[j - 1];
      j = j - 1;
    }
    p[j] = key;
    v[j] = key_v;
  }
}
