/**CFile***********************************************************************

  FileName    [rule.cpp]

  Synopsis    [File for rules]

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

#include "mu.hpp"
#include <iostream>

/********************
  class rule
  ********************/
rule::rule(void)
:
next(NULL)
{
}

/********************
  class simplerule and variable simplerulenum
  ********************/
int simplerulenum = 0;
simplerule::simplerule(ste * enclosures,
		       expr * condition,
		       ste * locals, stmt * body, 
		       int priority)
:rule(), name(name), enclosures(enclosures), condition(condition),
locals(locals), body(body), condname(NULL), rulename(NULL), 
priority(priority)
{
  if (condition != NULL && body != NULL) {
    Error.CondError(condition->has_side_effects(),
		    "Rule Condition must not have side effects.");
    if (args->pmurphik) {
      Error.CondError(!type_equal(condition->gettype(), realtype),
		      "Condition for probabilistic rule must be a real expression.");
      if (condition->hasvalue()
	  && ((condition->getrvalue() < 0)
	      || (condition->getrvalue() > 1)))
	Error.Error("Real condition for rule must be >=0 and <=1.");
    } else
      Error.CondError(!type_equal(condition->gettype(), booltype),
		      "Condition for rule must be a boolean expression.");
  }
  NextSimpleRule = SimpleRuleList;
  SimpleRuleList = this;

  size = CountSize(enclosures);

  // Rearrange enclosures so that the ones that are NOT
  // mentioned in the condition go first
  rearrange_enclosures();
}

simplerule *simplerule::SimpleRuleList = NULL;

int
 simplerule::CountSize(ste * enclosures)
{
  int ret;
  if (enclosures != NULL &&
      (enclosures->getvalue()->getclass() == decl::Quant ||
       enclosures->getvalue()->getclass() == decl::Alias ||
       enclosures->getvalue()->getclass() == decl::Choose)) {
    ret = CountSize(enclosures->getnext());
    if (enclosures->getvalue()->getclass() == decl::Quant ||
	enclosures->getvalue()->getclass() == decl::Choose)
      return ret * enclosures->getvalue()->gettype()->getsize();
    else
      return ret;
  } else
    return 1;
}


void simplerule::rearrange_enclosures()
{
  stecoll *us = condition ? condition->used_stes() : NULL;
  ste *front = NULL;
  ste *end = NULL;
  ste *rest = NULL;
  ste *ep = enclosures;

  bool is_dep = FALSE;		// Is the current ste mentioned in rule cond?
  bool is_cp = FALSE;		// Is the current ste a choose parameter?
  ste *cp = NULL;		// Choose parameter

  // Cardinality of parameters not mentioned in the condition
  indep_card = 1;
  // Lists of choose parameters
  dep_choose = indep_choose = NULL;

  if (!us)
    return;

  // Iterate over all relevant ste's in enclosures
  ep = enclosures;
  while (ep != NULL &&
	 (ep->getvalue()->getclass() == decl::Quant ||
	  ep->getvalue()->getclass() == decl::Alias ||
	  ep->getvalue()->getclass() == decl::Choose)) {

    // Create a copy of ep
    ste *ns = new ste(ep->getname(), ep->getscope(), ep->getvalue());
    ns->setnext(NULL);

    // If it's a choose parameter, create another copy
    is_cp = (ep->getvalue()->getclass() == decl::Choose);
    if (is_cp) {
      cp = new ste(ep->getname(), ep->getscope(), ep->getvalue());
      cp->setnext(NULL);
    }

    if (us->includes(ep)) {
      // ep is mentioned in the condition
      is_dep = TRUE;

      if (ep->getvalue()->getclass() == decl::Alias) {
	stecoll *alias_stes = ep->getvalue()->getexpr()->used_stes();
	us->append(alias_stes);
      }
      // if it's a choose parameter,
      // add to the list of ``dependent'' choose parameters
      if (is_cp) {
	cp->setnext(dep_choose);
	dep_choose = cp;
      }
    }

    else {
      // ep is NOT mentioned in the condition
      is_dep = FALSE;

      // Cardinality of Alias is always 1
      if (ep->getvalue()->getclass() != decl::Alias) {
	indep_card *= ns->getvalue()->gettype()->getsize();
      }
      // if it's a choose parameter,
      // add to the list of ``independent'' choose parameters
      if (is_cp) {
	cp->setnext(indep_choose);
	indep_choose = cp;
      }
    }

    // If it's not an alias and it's mentioned in the condition, 
    //    move to the front of the list;
    // otherwise add to the end of the list
    if (!front) {
      front = end = ns;
    } else {
      // if(is_dep) {
      if (is_dep && (ep->getvalue()->getclass() != decl::Alias)) {
	ns->setnext(front);
	front = ns;
      } else {
	end->setnext(ns);
	end = ns;
      }
    }

    ep = ep->getnext();
  }
  // The rest of the enclosures
  rest = ep;

  if (front) {
    enclosures = front;
    end->setnext(rest);
  }

}


/********************
  class startstate and variable startstatenum
  ********************/
int startstatenum = 0;
startstate::startstate(ste * enclosures, ste * locals, stmt * body)
:  simplerule(enclosures, NULL, locals, body, 0)
{
}

/********************
  class invariant and variables invariantnum, has_invar
  ********************/
int invariantnum = 0;
bool has_invar = FALSE;

invariant::invariant(ste * enclosures, expr * test)
:  simplerule(enclosures, test, NULL, NULL, 0)
{
  Error.CondError(!type_equal(test->gettype(), booltype),
		  "Invariant must be a boolean expression.");
  Error.CondError(test->has_side_effects(),
		  "Invariant must not have side effects.");
}

/********************
  class quantrule
  ********************/
quantrule::quantrule(ste * quant, rule * rules)
:  rule(), quant(quant), rules(rules)
{
  quantdecl *q = (quantdecl *) quant->getvalue();
  if (q->left != NULL) {
    Error.CondError(!q->left->hasvalue(),
		    "Bounds for ruleset parameters must be constants.");
    Error.CondError(!q->right->hasvalue(),
		    "Bounds for ruleset parameters must be constants.");
  }
}

/********************
  class chooserule
  ********************/
chooserule::chooserule(ste * index, designator * set, rule * rules)
:  rule(), index(index), set(set), rules(rules)
{
  Error.
      CondError(((multisetidtypedecl *) index->getvalue()->
		 gettype())->getparenttype() != set->gettype(),
		"Internal Error: Parameter for Choose declared in type other than the multiset index");
  Error.CondError(set->gettype()->gettypeclass() != typedecl::MultiSet,
		  "Parameter for choose must be a multiset");
}

/********************
  class aliasrule
  ********************/
aliasrule::aliasrule(ste * aliases, rule * rules)
:  rule(), aliases(aliases), rules(rules)
{
}

/********************
  variable declaration
  ********************/
simplerule *error_rule = NULL;

/*********************
   class pctl
*********************/

pctl::pctl(pctl * subf1, pctl * subf2, expr * ap, pctl_type pctltype,
	   int until_bound, expr * prob_bound)
:subformula1(subf1),
subformula2(subf2),
atomic_proposition(ap),
pctltype(pctltype), code(new_int() + 1), until_bound(until_bound)
{
  Error.CondError(pctltype == AP_PCTL && ap->has_side_effects(),
		  "Atomic propositions in PCTL formulas must not have side effects.");
  if (prob_bound != NULL)
    this->prob_bound = prob_bound->getrvalue();
}

