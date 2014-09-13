/**CHeaderFile*****************************************************************

  FileName    [expr.hpp]

  Synopsis    [Header file for expressions]

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

#ifndef __EXPR_H__
#define __EXPR_H__

/********************
  In each class there are 4 sections
  1) initializer --> declaration in expr.C
  2) supporting routines --> declaration in expr.C
  3) code generation --> declaration in cpp_code.C
  ********************/

/********************
  class expr
  ********************/
class expr:public TNode {
protected:
  // variables
  int value;			/* value if it has one. */
  double rvalue;		// AP: real value
  typedecl *type;		/* type of expression. */
  bool constval, sideeffects;

  // initializer used by subclasses. 
   expr(void);
   expr(typedecl * type, bool constval, bool sideeffects)
  :type(type), constval(constval), sideeffects(sideeffects) {
  };

public:

  // initializer
  expr(const int value, typedecl * const type);
  expr(const double value, typedecl * const type);	// AP: new constructor

  // supporting routines
  typedecl *gettype() const {
    return type;
  };
  virtual bool isquant() const {
    return FALSE;
  };
  virtual bool hasvalue() const {
    return constval;
  };
  double getrvalue() const {
    return rvalue;
  };				// AP: getrvalue() is similar to getvalue()
  virtual int getvalue() const {
    return value;
  };
  virtual bool islvalue() const {
    return FALSE;
  };
  virtual bool has_side_effects() const {
    return sideeffects;
  };
  virtual bool isdesignator() const {
    return FALSE;
  };
  virtual bool checkundefined() const {
    return FALSE;
  };

  virtual stecoll *used_stes() const {
    return new stecoll;
  };

  // code generation
  virtual const char *generate_code();
};

// AP: mathematical functions 
class mathexpr:public expr {
  expr *arg1;
  expr *arg2;

public:
  enum mathexprtype
      { mylog, mylog10, myexp, mysin, mycos, mytan, myfabs, myfloor,
myceil,
    mysqrt, myfmod, mypow, myasin, myacos,
    myatan, mysinh, mycosh, mytanh
  };
  mathexprtype funtype;

   mathexpr(expr * arg1, expr * arg2, int arg3);

  mathexprtype getfuntype() {
    return funtype;
  };
  virtual const char *generate_code();
};

/********************
  class unaryexpr
  -- class for all unary expression 
  ********************/
class unaryexpr:public expr {
protected:
  int op;			/* the operator value. */
  expr *left;			/* the arguments. */

public:
  // initializer
   unaryexpr(typedecl * type, int op, expr * left);
   unaryexpr(typedecl * type, expr * left);

  virtual stecoll *used_stes() const {
    return (left ? left->used_stes() : new stecoll);
  }
  // code generation virtual const char *generate_code() = 0;
};

/********************
  class binaryexpr
  -- class for all binary expression
  ********************/
class binaryexpr:public expr {
protected:
  int op;			/* the operator value. */
  expr *left, *right;		/* the arguments. */

public:
  // initializer
   binaryexpr(typedecl * type, int op, expr * left, expr * right);

  virtual stecoll *used_stes() const {
    stecoll *l = left ? left->used_stes() : new stecoll;
    stecoll *r = right ? right->used_stes() : new stecoll;

     l->append(r);

     return l;
  }
  // code generation virtual const char *generate_code() = 0;
};

/********************
  class boolexpr
  -- a binary expression of two boolean arguments.
  ********************/
class boolexpr:public binaryexpr {
public:
  // initializer
  boolexpr(int op, expr * left, expr * right);

  // code generation
  virtual const char *generate_code();
};

/********************
  class notexpr
  -- boolean not
  ********************/
class notexpr:public unaryexpr {
public:
  // initializer
  notexpr(expr * left);

  // code generation
  virtual const char *generate_code();
};

/********************
  class equalexpr
  -- A = B or A != B.
  ********************/
class equalexpr:public binaryexpr {
public:
  // initializer
  equalexpr(int op, expr * left, expr * right);

  // code generation
  virtual const char *generate_code();
};

/********************
  class compexpr
  -- A < B, etc.
  ********************/
class compexpr:public binaryexpr {
public:
  // initializer
  compexpr(int op, expr * left, expr * right);

  // code generation
  virtual const char *generate_code();
};

/********************
  class arithexpr
  -- an arithmetic expression.
  ********************/
class arithexpr:public binaryexpr {
public:
  // initializer
  arithexpr(int op, expr * left, expr * right);

  // code generation
  virtual const char *generate_code();
};

/********************
  class unexpr
  -- an unary arithmetic expression.
  -- +expr or -expr.
  ********************/
class unexpr:public unaryexpr {
public:
  // initializer
  unexpr(int op, expr * left);

  // code generation
  virtual const char *generate_code();
};

/********************
  class mulexpr
  -- a multiplication or division.
  ********************/
class mulexpr:public arithexpr {
public:
  // initializer
  mulexpr(int op, expr * left, expr * right);

  // code generation
  virtual const char *generate_code();
};

/********************
  class quantexpr
  -- a quantified expression.
  ********************/
class quantexpr:public expr {
protected:
  int op;			/* FORALL or EXISTS. */
  ste *parameter;		/* the quantified variable. */
  expr *left;			/* the sub-expression. */

public:
  // initializer
   quantexpr(int op, ste * parameter, expr * left);

  // supporting routines
  ste *getparam() const {
    return parameter;
  };
  virtual bool isquant() const {
    return TRUE;
  };
  virtual bool hasvalue() const {
    return FALSE;
  };
  virtual int getvalue() const {
    return FALSE;
  };

  virtual stecoll *used_stes() const {
    // NOTE:  parameter is ignored
    return (left ? left->used_stes() : new stecoll);
  }
  // code generation 
  virtual const char *generate_code();
};

/********************
  class condexpr
  -- a ?: expression.  We need to have a subclass for this
  -- for the extra arg. 
  ********************/
class condexpr:public expr {
protected:
  expr * test, *left, *right;
public:
  // initializer
  condexpr(expr * test, expr * left, expr * right);
  virtual bool hasvalue() const {
    return FALSE;
  };

  virtual stecoll *used_stes() const {

    stecoll *t = test ? test->used_stes() : new stecoll;
    stecoll *l = left ? left->used_stes() : new stecoll;
    stecoll *r = right ? right->used_stes() : new stecoll;

     t->append(l);
     t->append(r);

     return t;
  }
  // code generation 
  virtual const char *generate_code();
};

/********************
  class designator
  -- represented as a left-linear tree.
  ********************/
class designator:public expr {
  // variables
  designator *left;
  ste *origin;			/* an identifier; */
  expr *arrayref;		/* an array reference. */
  ste *fieldref;		/* a field reference. */
  bool lvalue;

  // undefined
  bool maybeundefined;

  // class identifiers
  enum designator_class { Base, ArrayRef, FieldRef };
  designator_class dclass;

public:
  // initializer
   designator(ste * origin,
	      typedecl * type,
	      bool islvalue,
	      bool isconst, bool maybeundefined, int val = 0);
   designator(ste * origin, typedecl * type, bool islvalue, bool isconst, bool maybeundefined, double val);	// AP: this constructor is called by getdesignator() (constdecl)

   designator(designator * left, expr * ar);
   designator(designator * left, lexid * fr);

  // supporting routines
  virtual bool islvalue() const {
    return lvalue;
  };
  ste *getbase(void) const;
  virtual bool isdesignator() const {
    return TRUE;
  };
  virtual bool checkundefined() const {
    return maybeundefined;
  };

  virtual stecoll *used_stes() const;

  // code generation
  virtual const char *generate_code();
};

/********************
  class exprlist
  ********************/
struct exprlist {
  expr *e;
  bool undefined;
  exprlist *next;

  // initializer
   exprlist(expr * e, exprlist * next = NULL);
   exprlist(bool b, exprlist * next = NULL);	// b should be TRUE
  // in current implementation
  exprlist *reverse();		/* reverses it. */
  friend bool matchparams(ste * formals, exprlist * actuals);


  virtual stecoll *used_stes() const {
    stecoll *x = e ? e->used_stes() : new stecoll;
    stecoll *n = next ? next->used_stes() : new stecoll;

     x->append(n);

     return x;
  }
  // code generation
      virtual const char *generate_code(const char *name, ste * formals);
};

/********************
  class funccall
  ********************/
struct funccall:public expr {
  ste *func;
  exprlist *actuals;

  // initializer
   funccall(ste * func, exprlist * actuals);

  virtual stecoll *used_stes() const {
    // NOTE: func is ignored
    return (actuals ? actuals->used_stes() : new stecoll);
  }
  // code generation 
  virtual const char *generate_code();
};

/********************
  class isundefined
  ********************/
struct isundefined:public unaryexpr {
  // initializer
  isundefined(expr * left);

  // code generation
  virtual const char *generate_code();
};

/********************
  class ismember
  ********************/
struct ismember:public unaryexpr {
  // variable
  typedecl *t;

  // initializer
   ismember(expr * left, typedecl * type);

  // code generation
  virtual const char *generate_code();
};

/********************
  class multisetcount
  ********************/
class multisettypedecl;

class multisetcount:public expr {
  static int num_multisetcount;

  // variablea
  ste *index;
  designator *set;
  expr *filter;
  int multisetcount_num;

public:
  // initializer
   multisetcount(ste * index, designator * set, expr * filter);

  virtual stecoll *used_stes() const {
    // NOTE: func is ignored
    stecoll *i = index ? new stecoll(index) : new stecoll;
    stecoll *s = set ? set->used_stes() : new stecoll;
    stecoll *f = filter ? filter->used_stes() : new stecoll;

     i->append(s);
     i->append(f);

     return i;
  }
  // code generation 
  virtual void generate_decl(multisettypedecl * mset);
  virtual void generate_procedure();
  virtual const char *generate_code();
};

/********************
  extern variables
  ********************/
extern designator *error_designator;
extern expr *error_expr;
extern expr *true_expr;
extern expr *false_expr;

#endif
