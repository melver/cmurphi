/**CHeaderFile*****************************************************************

  FileName    [rule.hpp]

  Synopsis    [Header file for rules]

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

#ifndef __RULE_H__
#define __RULE_H__

/********************
  In each class there are 4 sections
  1) initializer --> declaration in rule.C
  2) supporting routines --> declaration in rule.C
  3) code generation --> declaration in cpp_code.C
  ********************/

/********************
  class rule
  ********************/
struct rule:public TNode {
  // class identifier
  enum rule_class
      { Simple, Startstate, Invar, Quant, Choose, Alias, Fair, Live };

  // variable
  rule *next;

  // initializer  
   rule(void);

  // supporting routines  
  virtual void set_name(char *name) {
    Error.Error("Internal: rule::set_name(%s)", name);
  };
  virtual rule_class getclass() const = 0;

  // code generation
  virtual const char *generate_code();
};

/********************
  extern variable
  ********************/
extern int simplerulenum;

/********************
  class simplerule
  ********************/
struct simplerule:rule {
  static simplerule *SimpleRuleList;
  simplerule *NextSimpleRule;

  // variable
  char *name;
  char *condname, *rulename;	/* internal names for rule and condition. */
  ste *enclosures;		/* enclosing ruleset params and aliases. */
  expr *condition;		/* condition for execution. */
  ste *locals;			/* things defined within the rule. */
  stmt *body;			/* code. */
  int rulenumber;
  int maxrulenumber;
  int size;

  // Vitaly's additions
  int priority;
  // Cardinality of parameters NOT mentioned in the condition
  int indep_card;
  // List of choose parameters NOT mentioned in the condition
  ste *indep_choose;
  // List of choose parameters mentioned in the condition
  ste *dep_choose;
  // End of Vitaly's additions

  // initializer
   simplerule(ste * enclosures,
	      expr * condition,
	      ste * locals, stmt * body, int priority);

  // supporting routines
  virtual void set_name(char *name) {
    this->name =
	name != NULL ? name : tsprintf("Rule %d", simplerulenum++);
  } virtual rule_class getclass() const {
    return Simple;
  };

  // code generation
  virtual const char *generate_code();

  int CountSize(ste * enclosures);

  void rearrange_enclosures();

  int getsize() {
    return size;
  }
};

/********************
  extern variable
  ********************/
extern int startstatenum;

/********************
  class startstate
  ********************/
struct startstate:simplerule {
  // initializer
  startstate(ste * enclosures, ste * locals, stmt * body);

  // supporting routines
  virtual void set_name(char *name) {
    this->name =
	name != NULL ? name : tsprintf("Startstate %d", startstatenum++);
  } virtual rule_class getclass() const {
    return Startstate;
  };

  // code generation
  virtual const char *generate_code();
};

/********************
  extern variable
  ********************/
extern int invariantnum;
extern bool has_invar;

/********************
  class invariant
  ********************/
struct invariant:simplerule {
  // initializer
  invariant(ste * enclosures, expr * test);

  // supporting routines
  virtual void set_name(char *name) {
    this->name =
	name != NULL ? name : tsprintf("Invariant %d", invariantnum++);
  } virtual rule_class getclass() const {
    return Invar;
  };

  // code generation
  virtual const char *generate_code();
};

/********************
  class quantrule
  ********************/
struct quantrule:rule {
  ste *quant;
  rule *rules;

  // initializer and supporting routines
   quantrule(ste * param, rule * rules);
  virtual rule_class getclass() const {
    return Quant;
  };

  // code generation
  virtual const char *generate_code();
};

/********************
  class chooserule for multiset
  ********************/
struct chooserule:rule {
  ste *index;
  designator *set;
  rule *rules;

  // initializer and supporting routines
   chooserule(ste * index, designator * set, rule * rules);

  virtual rule_class getclass() const {
    return Choose;
  };

  // code generation
  virtual const char *generate_code();
};

/********************
  class aliasrule
  ********************/
struct aliasrule:rule {
  ste *aliases;
  rule *rules;

  // initializer and supporting routines
   aliasrule(ste * aliases, rule * rules);
  virtual rule_class getclass() const {
    return Alias;
  };

  // code generation
  virtual const char *generate_code();
};

/********************
  extern variable
  ********************/
extern simplerule *error_rule;

/********************
  class pctl
  ********************/
struct pctl:public TNode {
  expr *atomic_proposition;
  pctl_type pctltype;
  pctl *subformula1, *subformula2;
  pctl_ord op;			/* comparison operator */
  double prob_bound;
  unsigned until_bound;
  int code;			/* code of the subformula in the PCTL formula synctactic tree */

   pctl(pctl * subf1, pctl * subf2, expr * ap, pctl_type pctltype,
	int until_bound, expr * prob_bound);
  virtual const char *generate_code();
  virtual void generate_atomic_subformulas(pctl *);
  inline const char *getstring(pctl_type);
  inline const char *getstring(pctl_ord);
  virtual void generate_non_atomic_subformulas(pctl *);
  virtual unsigned num_top_untils(pctl *, int);
  inline int ret_top_untils(pctl *, unsigned *, int);
};

#endif
