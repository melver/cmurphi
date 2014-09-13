/**CFile***********************************************************************

  FileName    [parse.cpp]

  Synopsis    [File for parsing handling]

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

/********************
  variable declarations
  ********************/
int gLineNum = 1;
char *gFileName;
extern char *yytext;		/* lex\'s token matched. */
int offset = 0;

/********************
  void yyerror(char *s)
  ********************/
void yyerror(const char *s)
{
  Error.Error("%s. Last token read was \'%s\'", s, yytext);
}

/********************
  bool matchparams(char *name, ste *formals, exprlist *actuals)
  -- matching type for the parameters
  ********************/
bool matchparams(char *name, ste * formals, exprlist * actuals)
{
  bool match = TRUE;
  for (;
       formals != NULL && actuals != NULL;
       formals = formals->getnext(), actuals = actuals->next) {
    param *f = (param *) formals->getvalue();
    if (!actuals->undefined) {
      expr *e = actuals->e;
      if (!type_equal(f->gettype(), e->gettype())) {
	if (!(type_equal(f->gettype(), realtype)
	      && type_equal(e->gettype(), inttype))) {
	  Error.Error("Actual parameter to %s has wrong type.", name);
	  match = FALSE;
	}
      }
      if (f->getparamclass() == param::Var) {
	if (Error.CondError(!e->islvalue(),
			    "Non-variable expression can't be passed to VAR parameter of %s.",
			    name))
	  match = FALSE;
	if (Error.CondError(f->gettype() != e->gettype(),
			    "Var parameter to %s has wrong type.", name))
	  match = FALSE;
      }
    } else {
      if (f->getparamclass() == param::Var) {
	Error.Error
	    ("UNDEFINED value can't be passed to VAR parameter of %s.",
	     name);
	match = FALSE;
      }
    }
  }
  if ((formals != NULL && actuals == NULL) ||
      (actuals != NULL && formals == NULL)) {
    Error.Error("Wrong number of parameters to function %s.", name);
    match = FALSE;
  }
  return match;
}

/********************
  bool type_equal(typedecl *a, typedecl *b)
  -- whether two types should be considered compatible.
  ********************/
bool type_equal(typedecl * a, typedecl * b)
{
  stelist *member;

//   if ( ( a->gettypeclass() == typedecl::Error_type ) ||
//        ( b->gettypeclass() == typedecl::Error_type ) )
//     return TRUE;

  // added by Uli
  if (a->gettype()->gettypeclass() == typedecl::MultiSetID
      && b->gettype()->gettypeclass() != typedecl::MultiSetID)
    return FALSE;
  if (a->gettype()->gettypeclass() != typedecl::MultiSetID
      && b->gettype()->gettypeclass() == typedecl::MultiSetID)
    return FALSE;
  if (a->gettype()->gettypeclass() == typedecl::MultiSetID
      && b->gettype()->gettypeclass() == typedecl::MultiSetID)
    return 0 ==
	strcmp(((multisetidtypedecl *) a)->getparentname(),
	       ((multisetidtypedecl *) b)->getparentname());
  // end added by Uli

  if ((a->gettype()->gettypeclass() == typedecl::Enum
       || a->gettype()->gettypeclass() == typedecl::Scalarset)
      && b->gettype()->gettypeclass() == typedecl::Union) {
    for (member = ((uniontypedecl *) b->gettype())->getunionmembers();
	 member != NULL; member = member->next)
      if (a->gettype() == member->s->getvalue())
	return TRUE;
    return FALSE;
  }

  if (a->gettype()->gettypeclass() == typedecl::Union
      && (b->gettype()->gettypeclass() == typedecl::Enum
	  || b->gettype()->gettypeclass() == typedecl::Scalarset)) {
    for (member = ((uniontypedecl *) a->gettype())->getunionmembers();
	 member != NULL; member = member->next)
      if (b->gettype() == member->s->getvalue())
	return TRUE;
    return FALSE;
  }

  return (a->gettype() == b->gettype());
}

