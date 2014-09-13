/**CFile***********************************************************************

  FileName    [cpp_code.cpp]

  Synopsis    [File for code generation]

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

/* NOTE: 

   Beware of declarations introduced not at the beginnings
   of scopes.

   Why are expressions all handled with switches instead of
   virtual functions? 
*/

/*
 * Each generate_code() member function outputs to stdout the code
 * necessary to evaluate that thing, and returns a string with
 * what is necessary to use it as a value.
 *
 * Some examples:
 *
 * The statement "A := foo" sends this to stdout:
 *   A = foo;
 * And returns the null string.
 *
 * the expression "A[i]" sends nothing to stdout and returns
 * the string "A[i]".
 *
 * A more complicated example, the real motivation for this scheme:
 * The expression "FORALL i : 0..1 DO boolarray[i] END;"
 * sends something like the following to stdout, which is what is
 * required to compute the forall:
 * 
 *   mu__forall_1 = TRUE;
 *   {
 *     for(i = 0; i <= 1; i++)
 *       {
 *	 if ( !(boolarray[i]) )
 *       {
 *	 mu__forall_1 = FALSE;
 *	 break;
 *       }
 *       }
 *   }
 *
 * and then it returns "mu__forall_1", which is what\'s necessary to
 * use the value of the forall.
 *
 */

/*
 * Standard hack:
 * in many cases, we have to generate a list of things separated by commas.
 * Usually, we do this by sprintf-ing ", x" into a buffer for each x,
 * and then using (buffer + 1) as the value to use, so we skip the
 * comma at the betginning.
 */

/*
 * Debugging hint: to check whether all the parentheses and braces
 * this generating match, open the generated code in emacs in
 * c++-mode, put set the mark at one end and point at the other, and
 * do C-M-\ (indent-region) to reindent all the lines.  If the last
 * line of the generated code doesn\'t end in column 1, your braces
 * or parentheses don\'t match up somewhere.
 */

/********************
  code related to decl
  --
  -- typedecl
  -- -- enumtypedecl
  -- -- subrangetypedecl
  -- -- arraytypedecl
  -- -- recordtypedecl
  -- -- scalarsettypedecl
  -- -- uniontypedecl
  -- constdecl
  -- vardecl
  -- aliasdecl
  -- quantdecl
  -- parameter
  -- -- param
  -- -- varparam
  -- -- valparam
  -- -- constparam
  -- procdecl
  -- funcdecl 
  ********************/

/********************
  code for decl
  ********************/
const char *decl::generate_decl()
{
  Error.Error
      ("Internal:  decl::generate_decl() should not have been called.");
  return "ERROR!";
}

const char *decl::generate_code()
{
  return mu_name;
}

/********************
  code for typedecl
 ********************/
const char *typedecl::generate_decl()
{
  Error.Error
      ("Internal:  typedecl::generate_code() should never have been called.");
  return "ERROR!";
}

void typedecl::generate_all_decl()
{
  if (next != NULL) {
    next->generate_all_decl();
  }
  generate_decl();
}

/* AP: code for realtypedecl */
const char *realtypedecl::generate_decl()
{
  if (!declared) {
    /* Invent a name for the object, and a "mu_name" for
       the declaration of the object in the generated code. */
    if (name == NULL) {
      name = tsprintf("_real_%d", tNum);
      mu_name = tsprintf("mu_%s", name);
    }
    /* class name */
    fprintf(codefile, "class %s: public %s\n" "{\n" " public:\n" "  inline double operator=(double val) { return %s::operator=(val); };\n" "  inline double operator=(const %s& val) { return %s::operator=((double) val); };\n" "  %s (const char *name, int os): %s(%d,%d,%d,name, os) {};\n" "  %s (void): %s(%d,%d,%d) {};\n" "  %s (double val): %s(%d,%d,%d,\"Parameter or function result.\", 0)\n" "  {\n" "    operator=(val);\n" "  };\n" "  char * Name() { return tsprintf(\"%%le\",value()); };\n", mu_name, mu_type,	/* class name */
	    mu_type, mu_name, mu_type, mu_name, mu_type, accuracy, exponent_value, numbits,	//IM: fixed, exponent_value instead of exponent
	    mu_name, mu_type, accuracy, exponent_value, numbits,	//IM: fixed, exponent_value instead of exponent
	    mu_name, mu_type, accuracy, exponent_value, numbits	//IM: fixed, exponent_value instead of exponent
	);
    theprog->symmetry.generate_symmetry_function_decl();
    fprintf(codefile,
	    "  virtual void MultisetSort() {};\n"
	    "  void print_statistic() {};\n" "};\n\n");
    fprintf(codefile, "/*** end of real decl ***/\n");
    fprintf(codefile, "%s %s_undefined_var;\n\n", mu_name, mu_name);
    declared = TRUE;
  }
  /* Should never use this as a return value expression in the code gen */
  return "ERROR!";
}

/********************
  code for enumtypedecl
  Dill: I think this is bogusly ending each elt with ",", necessitating
   a "NULL" element at the end of the list.  
 ********************/
void make_enum_idvalues(ste * idvalues, typedecl * thistype)
{
  if (idvalues != NULL &&
      idvalues->getvalue()->getclass() == decl::Const &&
      type_equal(idvalues->getvalue()->gettype(), thistype)) {
    make_enum_idvalues(idvalues->getnext(), thistype);
    fprintf(codefile, "\"%s\",", idvalues->getname()->getname());
  }
}

const char *enumtypedecl::generate_decl()
{
  if (!declared) {
    /* Invent a name for the object, and a "mu_name" for
       the declaration of the object in the generated code. */
    if (name == NULL) {
      name = tsprintf("_enum_%d", tNum);
      mu_name = tsprintf("mu_%s", name);
    }

    /* class name */
    fprintf(codefile,
	    "class %s: public %s\n"
	    "{\n"
	    " public:\n"
	    "  inline int operator=(int val) { return value(val); };\n"
	    // Uli: return added
	    "  inline int operator=(const %s& val)"
	    " { return value(val.value()); };\n"
	    "  static const char *values[];\n"
	    "  friend ostream& operator<< (ostream& s, %s& val)\n"
	    "  {\n"
	    "    if (val.defined())\n"
	    "      return ( s << %s::values[ int(val) - %d] );\n"
	    "    else return ( s << \"Undefined\" );\n"
	    "  };\n\n"
	    "  %s (const char *name, int os): %s(%d, %d, %d, name, os) {};\n"
	    "  %s (void): %s(%d, %d, %d) {};\n"
	    "  %s (int val): %s(%d, %d, %d, \"Parameter or function result.\", 0)\n"
	    "  {\n"
	    "     operator=(val);\n"
	    "  };\n"
	    "  const char * Name() { return values[ value() -%d]; };\n"
//      "  inline int operator=(int val) { return %s::operator=(val); };\n"
//      "  inline int operator=(const %s& val) { return %s::operator=((int) val); };\n"
	    , mu_name, mu_type,	/* class name */
	    mu_name, mu_name,	/* type name for second arg to << */
	    mu_name, left,	/* class preceding values in body of <<, and offset */
	    mu_name, mu_type, left, right, numbits,	/* args for first constructor */
	    mu_name, mu_type, left, right, numbits,	/* args for second constructor */
	    mu_name, mu_type, left, right, numbits,	/* args for third constructor */
	    left		/* name */
	);
    theprog->symmetry.generate_symmetry_function_decl();
    fprintf(codefile, "  virtual void MultisetSort() {};\n" "  void print_statistic() {};\n" "  virtual void print()\n" "  {\n" "    if (defined())\n" "      cout << name << \":\" << values[ value() -%d] << '\\n';\n" "    else\n" "      cout << name << \":Undefined\\n\";\n" "  };\n" "};\n\n" "const char *%s::values[] = {", left,	/* print() */
	    mu_name);		/* for values array near the end */

    make_enum_idvalues(idvalues, this);
    // Dill: an extra NULL in case the enum has only one element.
    //       ? Why is this necessary? Because of printing "," after last element?
    fprintf(codefile, "NULL };\n\n");
    fprintf(codefile, "/*** end of enum declaration ***/\n");
    fprintf(codefile, "%s %s_undefined_var;\n\n", mu_name, mu_name);
    declared = TRUE;
  }
  /* Should never use this as a return value expression in the code gen */
  return "ERROR!";
}

/********************
  code for subrangetypedecl
 ********************/

const char *subrangetypedecl::generate_decl()
{
  /* if decl has not already been generated... */
  if (!declared) {
    /* make up a name for a new class, and a mu_name to be output. */
    if (name == NULL) {
      name = tsprintf("_subrange_%d", tNum);
      mu_name = tsprintf("mu_%s", name);
    }

    fprintf(codefile,
	    /* Indented so we can see what the output looks like: */
	    /* (adjacent strings are concatenated in C++!) */
	    "class %s: public %s\n"
	    "{\n"
	    " public:\n"
	    "  inline int operator=(int val) { return %s::operator=(val); };\n"
	    "  inline int operator=(const %s& val) { return %s::operator=((int) val); };\n"
	    /* three initializers */
	    "  %s (const char *name, int os): %s(%d, %d, %d, name, os) {};\n" "  %s (void): %s(%d, %d, %d) {};\n" "  %s (int val): %s(%d, %d, %d, \"Parameter or function result.\", 0)\n" "  {\n" "    operator=(val);\n" "  };\n" "  char * Name() { return tsprintf(\"%%d\",value()); };\n", mu_name, mu_type,	/* class name */
	    mu_type,
	    mu_name, mu_type, mu_name, mu_type, left, right, numbits,
	    /* args for first constructor */
	    mu_name, mu_type, left, right, numbits,
	    /* args for second constructor */
	    mu_name, mu_type, left, right, numbits);
    theprog->symmetry.generate_symmetry_function_decl();
    fprintf(codefile,
	    "  virtual void MultisetSort() {};\n"
	    "  void print_statistic() {};\n" "};\n\n");
    fprintf(codefile, "/*** end of subrange decl ***/\n");
    fprintf(codefile, "%s %s_undefined_var;\n\n", mu_name, mu_name);

    declared = TRUE;
  }
  return "ERROR!";
}



/********************
  code for arraytypedecl
  Dill:  HERE IS ONE OF THE EVIL TSPRINTFS!
 ********************/
int make_elt_ref_by_union(stelist * unionmembers)
{
  int base = 0;
  if (unionmembers->next != NULL)
    base = make_elt_ref_by_union(unionmembers->next);
  typedecl *t = (typedecl *) unionmembers->s->getvalue();
  fprintf(codefile,
	  "    if ( ( index >= %d ) && ( index <= %d ) )\n"
	  "      return array[ index - (%d) ];\n",
	  t->getleft(), t->getright(), t->getleft() - base);
  return base + t->getsize();
}

void make_elt_with_scalarset(ste * idvalues, int size, int numbits)
{
  if (size > 1)
    make_elt_with_scalarset(idvalues->next, size - 1, numbits);
  fprintf(codefile,
	  "if (n) array[i].set_self_ar(n,\"%s\", i * %d + os); else array[i].set_self_ar(NULL, NULL, 0); i++;\n",
	  idvalues->getname()->getname(), numbits);
}

void make_elt_with_enum(ste * idvalues, int size, int numbits)
{
  if (idvalues == NULL & size == 2) {
    fprintf(codefile,
	    "if (n) array[i].set_self_ar(n,\"false\", i * %d + os); else array[i].set_self_ar(NULL, NULL, 0); i++;\n",
	    numbits);
    fprintf(codefile,
	    "if (n) array[i].set_self_ar(n,\"true\", i * %d + os); else array[i].set_self_ar(NULL, NULL, 0); i++;\n",
	    numbits);
  } else if (idvalues != NULL) {
    if (size > 1)
      make_elt_with_enum(idvalues->next, size - 1, numbits);
    fprintf(codefile,
	    "if (n) array[i].set_self_ar(n,\"%s\", i * %d + os); else array[i].set_self_ar(NULL, NULL, 0); i++;\n",
	    idvalues->getname()->getname(), numbits);
  } else
    Error.Error("Internal Error: make_elt_with_enum");
}

void make_elt_with_union(stelist * unionmembers, int numbits)
{
  if (unionmembers->next != NULL)
    make_elt_with_union(unionmembers->next, numbits);
  if (((typedecl *) unionmembers->s->getvalue())->gettypeclass() ==
      typedecl::Scalarset)
    make_elt_with_scalarset(((scalarsettypedecl *) unionmembers->
			     s->getvalue())->getidvalues(),
			    unionmembers->s->getvalue()->getsize(),
			    numbits);
  else if (((typedecl *) unionmembers->s->getvalue())->gettypeclass() ==
	   typedecl::Enum)
    make_elt_with_enum(((enumtypedecl *) unionmembers->s->
			getvalue())->getidvalues(),
		       unionmembers->s->getvalue()->getsize(), numbits);
  else
    Error.Error("funny element in union");
}

const char *arraytypedecl::generate_decl()
{
  if (!declared) {
    if (name == NULL) {
      name = tsprintf("_array_%d", tNum);
      mu_name = tsprintf("mu_%s", name);
    }

    /* declare class with set_self, constructor and destructor */
    fprintf(codefile, "class %s\n" "{\n" " public:\n" "  %s array[ %d ];\n" " public:\n" "  char *name;\n" "  char longname[BUFFER_SIZE/4];\n" "  void set_self( const char *n, int os);\n" "  void set_self_2( const char *n, const char *n2, int os);\n" "  void set_self_ar( const char *n, const char *n2, int os);\n" "  %s (const char *n, int os) { set_self(n, os); };\n" "  %s ( void ) {};\n" "  virtual ~%s ();\n", mu_name,	/* class name */
	    elementtype->generate_code(),	/* array elt type */
	    indextype->getsize(),	/* array size */
	    mu_name,		/* name for first constructor */
	    mu_name,		/* name for second constructor */
	    mu_name);		/* destructor name */

    /* declare range-checked operator [] */
    fprintf(codefile,
	    "  %s& operator[] (int index) /* const */\n"
	    "  {\n", elementtype->generate_code());
    switch (indextype->gettypeclass()) {
    case typedecl::Enum:
    case typedecl::Range:
      fprintf(codefile, "#ifndef NO_RUN_TIME_CHECKING\n" "    if ( ( index >= %d ) && ( index <= %d ) )\n" "      return array[ index - %d ];\n" "    else {\n" "      if (index==UNDEFVAL) \n" "	Error.Error(\"Indexing to %%s using an undefined value.\", name);\n" "      else\n" "	Error.Error(\"%%d not in index range of %%s.\", index, name);\n" "      return array[0];\n" "    }\n" "#else\n" "    return array[ index - %d ];\n" "#endif\n" "  };\n", indextype->getleft(),	/* lower bound of range (2nd line of format) */
	      indextype->getright(),	/* upper bound */
	      indextype->getleft(),	/* index adjust (3rd line) */
	      indextype->getleft());	/* index adjust (after #else) */
      break;
    case typedecl::Scalarset:
      fprintf(codefile, "#ifndef NO_RUN_TIME_CHECKING\n" "    if ( ( index >= %d ) && ( index <= %d ) )\n" "      return array[ index - %d ];\n" "    else\n" "      {\n" "	if (index==UNDEFVAL) \n" "	  Error.Error(\"Indexing to %%s using an undefined value.\", name);\n" "	else\n" "	  Error.Error(\"Funny index value %%d for %%s: %s is internally represented from %d to %d.\\n" "Internal Error in Type checking.\",index, name);\n" "	return array[0];\n" "      }\n" "#else\n" "    return array[ index - %d ];\n" "#endif\n" "  };\n", indextype->getleft(),	/* lower bound of range (2nd line of format) */
	      indextype->getright(),	/* upper bound */
	      indextype->getleft(),	/* index adjust (3rd line) */
	      indextype->name, indextype->getright(), indextype->getleft(), indextype->getleft());	/* index adjust (after #else) */
      break;
    case typedecl::Union:
      (void)
	  make_elt_ref_by_union(((uniontypedecl *)
				 indextype)->getunionmembers());
      fprintf(codefile,
	      "    if (index==UNDEFVAL) \n"
	      "      Error.Error(\"Indexing to %%s using an undefined value.\", name);\n"
	      "    else\n"
	      "      Error.Error(\"Funny index value %%d for %%s. (Internal Error in Type Checking.\",index, name);\n"
	      "    return array[0];\n" "  }\n");
      break;
    case typedecl::Array:
    case typedecl::Record:
    case typedecl::Error_type:
    default:
      // the error should already be flagged. 

      // On the other hand, if this error happened, it should never
      // have gotten here. Therefore, we will put an error here, because
      // redundant error-checking is never a waste. --RLM
      Error.Error("Internal: Odd value for arraydecl::elementtype;");
      break;
    }

    /* and an operator =. */
    generate_assign();
//    if (elementtype->issimple()) 
//      fprintf(codefile, 
//      "  %s& operator= (const %s& from)\n"
//      "  {\n"
//      "    for (int i = 0; i < %d; i++)\n"
//      "      if (from.array[i].isundefined() )\n"
//      "       array[i].undefine();\n"
//      "      else\n"
//      "       array[i] = from.array[i];\n"
//      "    return *this;\n"
//      "  }\n\n",
//      mu_name,
//      mu_name,
//      indextype->getsize());
//   else
//      fprintf(codefile, 
//      "  %s& operator= (const %s& from)\n"
//      "  {\n"
//      "    for (int i = 0; i < %d; i++)\n"
//      "      array[i] = from.array[i];\n"
//      "    return *this;\n"
//      "  }\n\n",
//      mu_name,
//      mu_name,
//      indextype->getsize());

    /* comparsion function */
    if (indextype->getstructure() == typedecl::ScalarsetVariable)
      fprintf(codefile,
	      "friend int CompareWeight(%s& a, %s& b)\n"
	      "  {\n" "    return 0;\n" "  }\n", mu_name, mu_name);
    else
      fprintf(codefile,
	      "friend int CompareWeight(%s& a, %s& b)\n"
	      "  {\n"
	      "    int w;\n"
	      "    for (int i=0; i<%d; i++) {\n"
	      "      w = CompareWeight(a.array[i], b.array[i]);\n"
	      "      if (w!=0) return w;\n"
	      "    }\n"
	      "    return 0;\n"
	      "  }\n", mu_name, mu_name, indextype->getsize()
	  );

    /* comparsion function */
    fprintf(codefile,
	    "friend int Compare(%s& a, %s& b)\n"
	    "  {\n"
	    "    int w;\n"
	    "    for (int i=0; i<%d; i++) {\n"
	    "      w = Compare(a.array[i], b.array[i]);\n"
	    "      if (w!=0) return w;\n"
	    "    }\n"
	    "    return 0;\n"
	    "  }\n", mu_name, mu_name, indextype->getsize()
	);

    /* declare permute() */
    theprog->symmetry.generate_symmetry_function_decl();
    fprintf(codefile,
	    "  virtual void MultisetSort()\n"
	    "  {\n"
	    "    for (int i=0; i<%d; i++)\n"
	    "      array[i].MultisetSort();\n" "  }\n",
	    indextype->getsize()
	);
    fprintf(codefile,
	    "  void print_statistic()\n"
	    "  {\n"
	    "    for (int i=0; i<%d; i++)\n"
	    "      array[i].print_statistic();\n"
	    "  }\n", indextype->getsize()
	);

    /* standard functions:
     * clear(), undefine(), to_state() */
    fprintf(codefile,
	    "  void clear() { for (int i = 0; i < %d; i++) array[i].clear(); };\n\n"
	    "  void undefine() { for (int i = 0; i < %d; i++) array[i].undefine(); };\n\n"
	    "  void reset() { for (int i = 0; i < %d; i++) array[i].reset(); };\n\n"
	    "  void to_state(state *thestate)\n"
	    "  {\n"
	    "    for (int i = 0; i < %d; i++)\n"
	    "      array[i].to_state(thestate);\n" "  };\n\n",
//      "  void from_state(state *thestate)\n"
//      "  {\n"
//      "    for (int i = 0; i < %d; i++)\n"
//      "      array[i].from_state(thestate);\n"
//      "  };\n\n",
	    indextype->getsize(),	/* body of clear */
	    indextype->getsize(),	/* body of undefine */
	    indextype->getsize(),	/* body of reset */
	    indextype->getsize()	/* body of to_state */
	    //      indextype->getsize()  /* body of from_state */
	);

    /* compact print function */
    // Uli: print() function has to be used because of Undefined value
    if (FALSE)			// (elementtype->issimple())
      fprintf(codefile,
	      "  void print()\n"
	      "  {\n"
	      "    cout << name << \"[]: \\t\";\n"
	      "    for (int i = 0; i < %d; i++)\n"
	      "      cout << array[i] << '\\t';\n"
	      "  cout << \"\\n\";\n" "  }\n\n", indextype->getsize());
    else
      fprintf(codefile,
	      "  void print()\n"
	      "  {\n"
	      "    for (int i = 0; i < %d; i++)\n"
	      "      array[i].print(); };\n\n", indextype->getsize());

    fprintf(codefile,
	    "  void print_diff(state *prevstate)\n"
	    "  {\n"
	    "    for (int i = 0; i < %d; i++)\n"
	    "      array[i].print_diff(prevstate);\n"
	    "  };\n", indextype->getsize());
    /*
       "  void print_diff(state *prevstate)\n"
       "  {\n"
       "    bool diff = FALSE;\n"
       "    for (int i = 0; i < %d; i++)\n"
       "      if (array[i] != array[i].get_value_from_state(prevstate))\n"
       "   diff = TRUE;\n"
       "    if (diff) {\n"
       "      cout << name << \":\\t\";\n"
       "      for (int i = 0; i < %d; i++)\n"
       "   cout << array[i] << '\\t';\n"
       "      cout << \"\\n\";\n"
       "    }\n"
       "  }\n",
       indextype->getright() - indextype->getleft() + 1, 
       indextype->getright() - indextype->getleft() + 1, 
       indextype->getright() - indextype->getleft() + 1);
     */

    /* end class definition */
    fprintf(codefile, "};\n\n");

    /* write the set_self function. */
    fprintf(codefile,
	    "  void %s::set_self_ar( const char *n1, const char *n2, int os ) {\n"
	    "    if (n1 == NULL) {set_self(NULL, 0); return;}\n"
	    "    int l1 = strlen(n1), l2 = strlen(n2);\n"
	    "    strcpy( longname, n1 );\n"
	    "    longname[l1] = '[';\n"
	    "    strcpy( longname+l1+1, n2 );\n"
	    "    longname[l1+l2+1] = ']';\n"
	    "    longname[l1+l2+2] = 0;\n"
	    "    set_self( longname, os );\n"
	    "  };\n"
	    "  void %s::set_self_2( const char *n1, const char *n2, int os ) {\n"
	    "    if (n1 == NULL) {set_self(NULL, 0); return;}\n"
	    "    strcpy( longname, n1 );\n"
	    "    strcat( longname, n2 );\n"
	    "    set_self( longname, os );\n" "  };\n", mu_name, mu_name);
    switch (indextype->gettypeclass()) {
    case typedecl::Enum:
      fprintf(codefile,
	      "  void %s::set_self( const char *n, int os)\n"
	      "  {\n" "    int i=0;\n"
	      "    name = (char *)n;\n\n", mu_name);
      make_elt_with_enum(((enumtypedecl *) indextype)->getidvalues(),
			 indextype->getsize(),
			 elementtype->getbitsalloc());
      fprintf(codefile, "  }\n");
      break;
    case typedecl::Range:
      fprintf(codefile,
	      "void %s::set_self( const char *n, int os)\n"
	      "{\n"
	      "  char* s;\n"
	      "  name = (char *)n;\n"
	      "  for(int i = 0; i < %d; i++) {\n"
	      /* ANOTHER EVIL TSPRINTF! */
	      // Uli: I don't know who made the above comment, but it's 
	      //      really evil since the allocated memory is in many
	      //      cases hard to free (LABEL1)
              "    array[i].set_self_ar(n, s=tsprintf(\"%%d\",i + %d), i * %d + os);\n"
              "    delete[] s;\n"
              "  }\n"
              "};\n",
 
          mu_name,  /* first line of format */
	      indextype->getsize(),	/* for loop bound */
	      indextype->getleft(),	/* 3rd arg to tsprintf */
	      elementtype->getbitsalloc());	/* second arg to set_self */
      break;
    case typedecl::Scalarset:
      fprintf(codefile,
	      "void %s::set_self( const char *n, int os)\n"
	      "  {\n" "    int i=0;\n"
	      "    name = (char *)n;\n\n", mu_name);
      make_elt_with_scalarset(((scalarsettypedecl *)
			       indextype)->getidvalues(),
			      indextype->getsize(),
			      elementtype->getbitsalloc());
      fprintf(codefile, "}\n");
      break;
    case typedecl::Union:
      fprintf(codefile,
	      "void %s::set_self( const char *n, int os)\n"
	      "  {\n" "    int i=0;\n"
	      "    name = (char *)n;\n\n", mu_name);
      make_elt_with_union(((uniontypedecl *) indextype)->getunionmembers(),
			  elementtype->getbitsalloc());
      fprintf(codefile, "}\n");
      break;
    case typedecl::Array:
    case typedecl::Record:
    case typedecl::Error_type:
    default:
      // the error should already be flaged. 
      break;
    }

    fprintf(codefile,
	    /* DELETE PROBLEM */// Uli: no delete since there in no new
	    "%s::~%s()\n" "{\n"
//	    "  if (name) delete [] name;\n"
	    // "  for(int i = 0; i < %d; i++)\n"
	    // "    delete[ OLD_GPP(strlen(array[i].name) +1) ] array[i].name; // Should be delete[] \n"
	    "}\n", mu_name, mu_name, indextype->getsize());

    fprintf(codefile, "/*** end array declaration ***/\n");
    fprintf(codefile, "%s %s_undefined_var;\n\n", mu_name, mu_name);
    declared = TRUE;
  }
  return "ERROR!";
}

/********************
  code for multisettypedecl
 ********************/
const char *multisetidtypedecl::generate_decl()
{
  return "ERROR!";
}

const char *multisettypedecl::generate_decl()
{
  if (!declared) {

    /* make up a name for a new class, and a mu_name to be output. */
    if (name == NULL) {
      name = tsprintf("_multiset_%d", tNum);
      mu_name = tsprintf("mu_%s", name);
    }

    fprintf(codefile, "/*** begin multiset declaration ***/\n");

    // declare multiest id
    fprintf(codefile, "class %s_id: public %s\n" "{\n" " public:\n" "  inline int operator=(int val) { return value(val); };\n" "  inline int operator=(const %s_id& val) {" " return value(val.value()); };\n"	// Uli: return added
	    "  inline operator int() const { return value(); };\n" "  %s_id () : %s(0,%d,0) {};\n" "  %s_id (int val) : %s(0,%d,0, \"Parameter or function result.\",0) {operator=(val); };\n" "  char * Name() { return tsprintf(\"%%d\", value()); };\n" "};\n", mu_name, mu_type,	// class
	    mu_name,		// operator=
	    mu_name, mu_type, maximum_size - 1,	// constructor
	    mu_name, mu_type, maximum_size - 1	// constructor
	);

    /* declare class with set_self, constructor and destructor */
    fprintf(codefile, "class %s\n" "{\n" " public:\n" "  %s array[ %d ];\n" "  int max_size;\n" "  int current_size;\n" " public:\n" "  mu_0_boolean valid[ %d ];\n" "  char *name;\n" "  char longname[BUFFER_SIZE/4];\n" "  void set_self( const char *n, int os);\n" "  void set_self_2( const char *n, const char *n2, int os);\n" "  void set_self_ar( const char *n, const char *n2, int os);\n" "  %s (const char *n, int os): current_size(0), max_size(0) { set_self(n, os); };\n" "  %s ( void ): current_size(0), max_size(0) {};\n" "  virtual ~%s ();\n", mu_name,	/* class name */
	    elementtype->generate_code(),	/* array elt type */
	    maximum_size,	/* array size */
	    maximum_size,	/* array size */
	    mu_name,		/* name for first constructor */
	    /* maximum_size,  /* max current size */
	    /* CeilLog2(maximum_size+2),  /* max current size */
	    mu_name,		/* name for second constructor */
	    /* maximum_size,  /* max current size */
	    /* CeilLog2(maximum_size+2),  /* max current size */
	    mu_name);		/* destructor name */

    /* no range-checked operator [] */
    fprintf(codefile,
	    "  %s& operator[] (int index) /* const */\n"
	    "  {\n"
	    "    if ((index >= 0) && (index <= %d) && valid[index].value())\n"
	    "      return array[ index ];\n"
	    "    else {\n"
	    "      Error.Error(\"Internal Error::%%d not in index range of %%s.\", index, name);\n"
	    "      return array[0];\n"
	    "    }\n"
	    "  };\n", elementtype->generate_code(), maximum_size - 1);

    /* and an operator =. */
    generate_assign();
/*    if (elementtype->issimple()) 
      fprintf(codefile, 
	  "  %s& operator= (const %s& from)\n"
	  "  {\n"
	  "    int i;\n"
	  "    for (i = 0; i < %d; i++)\n"
	  "      if (from.array[i].isundefined() )\n"
	  "	array[i].undefine();\n"
	  "      else\n"
	  "	array[i] = from.array[i];\n"
	  "    for (i = 0; i < %d; i++)\n"
	  "      valid[i].value(from.valid[i].value());\n"
	  "    current_size = from.get_current_size();\n"
	  "    return *this;\n"
	  "  }\n\n",
	  mu_name,
	  mu_name,
	  maximum_size,
	  maximum_size);
    else
      fprintf(codefile, 
	  "  %s& operator= (const %s& from)\n"
	  "  {\n"
	  "    for (int i = 0; i < %d; i++)\n"
	  "      {\n"
	  "	array[i] = from.array[i];\n"
	  "	valid[i] = from.valid[i];\n"
	  "      }\n"
	  "    current_size = from.get_current_size();\n"
	  "    return *this;\n"
	  "  }\n\n",
	  mu_name,
	  mu_name,
	  maximum_size); 
*/

    /* comparsion function */
    fprintf(codefile,
	    "friend int CompareWeight(%s& a, %s& b)\n"
	    "  {\n"
	    "    return 0;\n" "  }\n", mu_name, mu_name, maximum_size);

    /* comparsion function */
    fprintf(codefile,
	    "friend int Compare(%s& a, %s& b)\n"
	    "  {\n"
	    "    int w;\n"
	    "    for (int i=0; i<%d; i++) {\n"
	    "      w = Compare(a.array[i], b.array[i]);\n"
	    "      if (w!=0) return w;\n"
	    "    }\n"
	    "    return 0;\n" "  }\n", mu_name, mu_name, maximum_size);

    /* declare permute() */
    theprog->symmetry.generate_symmetry_function_decl();

    /* standard functions:
     * clear(), undefine(), to_state(), from_state(). */
    fprintf(codefile,
	    "  void clear() { for (int i = 0; i < %d; i++) { array[i].undefine(); valid[i].value(FALSE); } current_size = 0; };\n\n"
	    "  void undefine() { for (int i = 0; i < %d; i++) { array[i].undefine(); valid[i].value(FALSE); } current_size = 0; };\n\n"
	    "  void reset() { for (int i = 0; i < %d; i++) { array[i].undefine(); valid[i].value(FALSE); } current_size = 0; };\n\n"
	    "  void to_state(state *thestate)\n"
	    "  {\n"
	    "    for (int i = 0; i < %d; i++)\n"
	    "     {\n"
	    "       array[i].to_state(thestate);\n"
	    "       valid[i].to_state(thestate);\n" "     }\n" "  };\n\n"
//       "  void from_state(state *thestate)\n"
//       "  {\n"
//       "    int i;\n"
//       "    for (i = 0; i < %d; i++)\n"
//       "     {\n"
//       "      array[i].from_state(thestate);\n"
//       "      valid[i].from_state(thestate);\n"
//       "     }\n"
//       "  };\n\n"
	    "  int get_current_size() const" "  {\n" "    int tmp = 0;\n" "    for (int i = 0; i < %d; i++)\n" "      if (valid[i].value()) tmp++;\n" "    return tmp;\n" "  };\n\n " "  void update_size()\n" "  {\n" "    current_size = 0;\n" "    for (int i = 0; i < %d; i++)\n" "      if (valid[i].value()) current_size++;\n" "    if (max_size<current_size) max_size = current_size;\n" "  };\n\n ", maximum_size,	/* body of clear */
	    maximum_size,	/* body of undefine */
	    maximum_size,	/* body of reset */
	    maximum_size,	/* body of to_state */
//       maximum_size, /* body of from_state */
	    maximum_size,	/* body of get_current_size */
	    maximum_size	/* body of update_size */
	);

    fprintf(codefile, "  inline bool in(const %s_id& id)\n"
	    // "  { if (current_size>id) return TRUE; else return FALSE; }\n",
	    "  { return valid[(int)id].value(); }\n",	// Uli 10-98
	    mu_name);

    /* compact print function */
    // Uli: print() function has to be used because of Undefined value
    if (FALSE)			// (elementtype->issimple())
      fprintf(codefile, "  void print()\n" "  {\n" "    cout << name << \"[]: \\t\";\n" "    for (int i = 0; i < %d; i++)\n" "      if (valid[i].value())\n" "	cout << array[i] << '\\t';\n" "      else\n" "	cout << '-' << '\\t';\n" "  cout << \"\\n\";\n" "  }\n\n", maximum_size	/* for */
	  );
    else
      fprintf(codefile, "  void print()\n" "  {\n" "    for (int i = 0; i < %d; i++)\n" "      if (valid[i].value())\n" "	array[i].print();\n" "  };\n\n", maximum_size	/* for */
	  );

    fprintf(codefile,
	    "  void print_statistic()\n"
	    "  {\n"
	    "    cout << \"\tThe maximum size for the multiset \\\"\" \n"
	    "	 << name << \"\\\" is: \" << max_size << \".\\n\"; \n"
	    "  };\n");
    fprintf(codefile,
	    "  void print_diff(state *prevstate)\n"
	    "  {\n"
	    "    bool prevvalid;\n"
	    "    static state temp;\n"
	    "    StateCopy(&temp, workingstate);\n"
	    "    for (int i = 0; i < %d; i++)\n"
	    "      {\n"
	    "	StateCopy(workingstate, prevstate);\n"
	    "	prevvalid = valid[i].value();\n"
	    "	StateCopy(workingstate, &temp);\n"
	    "	if (prevvalid && !valid[i].value())\n"
	    "	  array[i].print();\n"
	    "	if (!prevvalid && valid[i].value())\n"
	    "	  array[i].print();\n"
	    "	if (prevvalid && valid[i].value())\n"
	    "	  array[i].print_diff(prevstate);\n"
	    "      }\n" "  };\n", maximum_size);

    fprintf(codefile,
	    "  int multisetadd(const %s &element)\n"
	    "  {\n"
	    "    update_size();\n"
	    "    if (current_size >= %d) Error.Error(\"Maximum size of MultiSet (%%s) exceeded.\",name);\n"
	    "    int i;\n"
	    "    for (i = 0; i < %d; i++)\n"
	    "      if (!valid[i].value())\n"
	    "	{\n"
	    "	  array[i] = element;\n"
	    "	  valid[i].value(TRUE);\n"
	    "	  break;\n"
	    "	}\n"
	    "    current_size++;\n"
	    "    return i;\n"
	    "  };\n",
	    elementtype->generate_code(), maximum_size, maximum_size);
    fprintf(codefile, "  void multisetremove(const %s_id &id)\n" "  {\n" "    update_size();\n" "    if (!valid[(int)id].value()) Error.Error(\"Internal Error: Illegal Multiset element selected.\");\n"	// Uli 10-98
	    "    valid[(int)id].value(FALSE);\n"
	    "    array[(int)id].undefine();\n" "    current_size--;\n"
	    // "    id.undefine();\n"   // Uli: not necessary since valid[]
	    //      is checked
	    "  };\n", mu_name);

    fprintf(codefile,
	    "  void MultisetSort()\n"
	    "  {\n"
	    "    static %s temp;\n"
	    "\n"
	    "    // compact\n"
	    "    int i,j;\n"
	    "    for (i = 0, j = 0; i < %d; i++)\n"
	    "      if (valid[i].value())\n"
	    "	{\n"
	    "	  if (j!=i)\n"
	    "	    array[j++] = array[i];\n"
	    "	  else\n"
	    "	    j++;\n"
	    "	}\n"
	    "    if (j != current_size) current_size = j;\n"
	    "    for (i = j; i < %d; i++)\n"
	    "      array[i].undefine();\n"
	    "    for (i = 0; i < j; i++)\n"
	    "      valid[i].value(TRUE);\n"
	    "    for (i = j; i < %d; i++)\n"
	    "      valid[i].value(FALSE);\n"
	    "\n"
	    "    // bubble sort\n"
	    "    for (i = 0; i < current_size; i++)\n"
	    "      for (j = i+1; j < current_size; j++)\n"
	    "	if (Compare(array[i],array[j])>0)\n"
	    "	  {\n"
	    "	    temp = array[i];\n"
	    "	    array[i] = array[j];\n"
	    "	    array[j] = temp;\n"
	    "	  }\n"
	    "  }\n",
	    elementtype->generate_code
	    (), maximum_size, maximum_size, maximum_size);


    // declare procedures for all multisetcount
    if (msclist != NULL)
      msclist->generate_decl(this);

    // declare procedures for all multisetremove
    if (msrlist != NULL)
      msrlist->generate_decl(this);


    /* end class definition */
    fprintf(codefile, "};\n\n");

    /* write the set_self functions. */
    fprintf(codefile,
	    "  void %s::set_self_ar( const char *n1, const char *n2, int os ) {\n"
	    "    if (n1 == NULL) {set_self(NULL, 0); return;}\n"
	    "    int l1 = strlen(n1), l2 = strlen(n2);\n"
	    "    strcpy( longname, n1 );\n"
	    "    longname[l1] = '[';\n"
	    "    strcpy( longname+l1+1, n2 );\n"
	    "    longname[l1+l2+1] = ']';\n"
	    "    longname[l1+l2+2] = 0;\n"
	    "    set_self( longname, os );\n"
	    "  };\n"
	    "  void %s::set_self_2( const char *n1, const char *n2, int os ) {\n"
	    "    if (n1 == NULL) {set_self(NULL, 0); return;}\n"
	    "    strcpy( longname, n1 );\n"
	    "    strcat( longname, n2 );\n"
	    "    set_self( longname, os );\n" "  };\n", mu_name, mu_name);
    fprintf(codefile,
	    "void %s::set_self( const char *n, int os)\n"
	    "{\n"
	    "  int i,k;\n" 
	    "  name = (char *)n;\n" 
	    "  for(i = 0; i < %d; i++)\n"
	    /* ANOTHER EVIL TSPRINTF! */
	    // Uli: this might have to be changed in a similar fashion as
	    //      at LABEL1
	    "    if (n) array[i].set_self(tsprintf(\"%%s{%%d}\", n,i), i * %d + os); else array[i].set_self(NULL, 0);\n" "  k = os + i * %d;\n" "  for(i = 0; i < %d; i++)\n", mu_name,	/* first line of format */
	    maximum_size,	/* for loop bound */
	    elementtype->getbitsalloc(),	/* second arg to set_self */
	    elementtype->getbitsalloc(),	/* second arg to set_self */
	    maximum_size);	/* for loop bound */
    if (!args->no_compression)
      fprintf(codefile,
	      "    valid[i].set_self(\"\", i * 2 + k);\n" "};\n");
    else
      fprintf(codefile,
	      "    valid[i].set_self(\"\", i * 8 + k);\n" "};\n");

    fprintf(codefile,
	    /* DELETE PROBLEM */// Uli: no delete since there in no new
	    "%s::~%s()\n" "{\n"
//	    "  if (name) delete [] name;\n"
	    // "  for(int i = 0; i < %d; i++)\n"
	    // "    delete[ OLD_GPP(strlen(array[i].name) +1) ] array[i].name; // Should be delete[] \n"
	    // "  delete[ OLD_GPP(strlen(current_size[i].name) +1) ] current_size.name; // Should be delete[] \n"
	    "}\n", mu_name, mu_name, maximum_size);

    // declare procedures for all multisetcount
    if (msclist != NULL)
      msclist->generate_procedure();

    // declare procedures for all multisetremove
    if (msrlist != NULL)
      msrlist->generate_procedure();

    fprintf(codefile, "/*** end multiset declaration ***/\n");
    fprintf(codefile, "%s %s_undefined_var;\n\n", mu_name, mu_name);
    declared = TRUE;
  }
  return "ERROR!";
}

void multisetcountlist::generate_decl(multisettypedecl * mset)
{
  if (next != NULL)
    next->generate_decl(mset);
  mscount->generate_decl(mset);
}

void multisetremovelist::generate_decl(multisettypedecl * mset)
{
  if (next != NULL)
    next->generate_decl(mset);
  msremove->generate_decl(mset);
}

void multisetcountlist::generate_procedure()
{
  if (next != NULL)
    next->generate_procedure();
  mscount->generate_procedure();
}

void multisetremovelist::generate_procedure()
{
  if (next != NULL)
    next->generate_procedure();
  msremove->generate_procedure();
}

 /********************
   code for recordtypedecl
  ********************/
const char *recordtypedecl::generate_decl()
{
  ste *f;
  if (!declared) {
    if (name == NULL) {
      name = tsprintf("_record_%d", tNum);
      mu_name = tsprintf("%s", name);
    }
    fprintf(codefile, "class %s\n" "{\n" " public:\n" "  char *name;\n" "  char longname[BUFFER_SIZE/4];\n" "  void set_self_2( const char *n, const char *n2, int os);\n" "  void set_self_ar( const char *n, const char *n2, int os);\n" "  void set_self(const char *n, int os);\n", mu_name);	/* class name */

    /* Generate members for record fields. */
    for (f = fields; f != NULL; f = f->getnext()) {
      /* f->getvalue()->generate_decl(); */
      /* Not right--it tells members the wrong names. */
      fprintf(codefile, "  %s %s;\n",
	      f->getvalue()->gettype()->generate_code(),
	      f->getvalue()->generate_code());
    };

    /* Two constructors and a destructor */
    fprintf(codefile, "  %s ( const char *n, int os ) { set_self(n,os); };\n" "  %s ( void ) {};\n\n" "  virtual ~%s(); \n", mu_name, mu_name, mu_name);	/* constructor and destructor names */

    /* comparsion function */
    fprintf(codefile,
	    "friend int CompareWeight(%s& a, %s& b)\n"
	    "  {\n" "    int w;\n", mu_name, mu_name);
    for (f = fields; f != NULL; f = f->getnext())
      fprintf(codefile,
	      "    w = CompareWeight(a.%s, b.%s);\n"
	      "    if (w!=0) return w;\n",
	      f->getvalue()->generate_code(),
	      f->getvalue()->generate_code()
	  );
    fprintf(codefile, "  return 0;\n" "}\n");

    /* comparsion function */
    fprintf(codefile,
	    "friend int Compare(%s& a, %s& b)\n"
	    "  {\n" "    int w;\n", mu_name, mu_name);
    for (f = fields; f != NULL; f = f->getnext())
      fprintf(codefile,
	      "    w = Compare(a.%s, b.%s);\n"
	      "    if (w!=0) return w;\n",
	      f->getvalue()->generate_code(),
	      f->getvalue()->generate_code()
	  );
    fprintf(codefile, "  return 0;\n" "}\n");

    /* declare permute() */
    theprog->symmetry.generate_symmetry_function_decl();

    /* comparsion function */
    fprintf(codefile, "  virtual void MultisetSort()\n" "  {\n");
    for (f = fields; f != NULL; f = f->getnext())
      fprintf(codefile,
	      "    %s.MultisetSort();\n", f->getvalue()->generate_code()
	  );
    fprintf(codefile, "  }\n");

    /* statistic */
    fprintf(codefile, "  void print_statistic()\n" "  {\n");
    for (f = fields; f != NULL; f = f->getnext())
      fprintf(codefile,
	      "    %s.print_statistic();\n", f->getvalue()->generate_code()
	  );
    fprintf(codefile, "  }\n");

    /* standard functions:
     * clear(), undefine(), print(), print_diff(), to_state(), from_state(). 
     * And now, operator = ()! */
    fprintf(codefile, "  void clear() {\n");
    for (f = fields; f != NULL; f = f->getnext())
      fprintf(codefile, "    %s.clear();\n",
	      f->getvalue()->generate_code());
    fprintf(codefile, " };\n");

    fprintf(codefile, "  void undefine() {\n");
    for (f = fields; f != NULL; f = f->getnext())
      fprintf(codefile, "    %s.undefine();\n",
	      f->getvalue()->generate_code());
    fprintf(codefile, " };\n");

    fprintf(codefile, "  void reset() {\n");
    for (f = fields; f != NULL; f = f->getnext())
      fprintf(codefile, "    %s.reset();\n",
	      f->getvalue()->generate_code());
    fprintf(codefile, " };\n");

    fprintf(codefile, "  void print() {\n");
    for (f = fields; f != NULL; f = f->getnext())
      fprintf(codefile, "    %s.print();\n",
	      f->getvalue()->generate_code());
    fprintf(codefile, "  };\n");

    fprintf(codefile, "  void print_diff(state *prevstate) {\n");
    for (f = fields; f != NULL; f = f->getnext())
      fprintf(codefile, "    %s.print_diff(prevstate);\n",
	      f->getvalue()->generate_code());
    fprintf(codefile, "  };\n");

    fprintf(codefile, "  void to_state(state *thestate) {\n");
    for (f = fields; f != NULL; f = f->getnext())
      fprintf(codefile, "    %s.to_state(thestate);\n",
	      f->getvalue()->generate_code());
    fprintf(codefile, "  };\n");

//       fprintf(codefile,"  void from_state(state *thestate) {\n");
//       for( f = fields; f != NULL; f = f->getnext() )
//   fprintf(codefile,"    %s.from_state(thestate);\n", f->getvalue()->generate_code() );
//       fprintf(codefile,"  };\n");

    /* isundefined : this should not be called in a well-formed program */
    fprintf(codefile,
	    "virtual bool isundefined() { Error.Error(\"Checking undefinedness of a non-base type\"); return TRUE;}\n");

    /* ismember : this should not be called in a well-formed program */
    fprintf(codefile,
	    "virtual bool ismember() { Error.Error(\"Checking membership for a non-base type\"); return TRUE;}\n");

    generate_assign();
/*       fprintf(codefile,
	  "  %s& operator= (const %s& from) {\n",
	  mu_name,
	  mu_name);
       for( f = fields; f != NULL; f = f->getnext() ) {
    if (f->getvalue()->gettype()->issimple())
      fprintf(codefile,
	"   if ( from.%s.isundefined() )\n"
	"     %s.undefine();\n"
	"   else\n"
	"     %s = from.%s;\n",
	f->getvalue()->generate_code(),
	f->getvalue()->generate_code(),
	f->getvalue()->generate_code(),
	f->getvalue()->generate_code());
    else
      fprintf(codefile,
	"   %s = from.%s;\n",
	f->getvalue()->generate_code(),
	f->getvalue()->generate_code());
       }
 
       fprintf(codefile,"    return *this;\n");
       fprintf(codefile,"  };\n"); 
*/

    /* end class definition */
    fprintf(codefile, "};\n\n");

    fprintf(codefile,
	    "  void %s::set_self_ar( const char *n1, const char *n2, int os ) {\n"
	    "    if (n1 == NULL) {set_self(NULL, 0); return;}\n"
	    "    int l1 = strlen(n1), l2 = strlen(n2);\n"
	    "    strcpy( longname, n1 );\n"
	    "    longname[l1] = '[';\n"
	    "    strcpy( longname+l1+1, n2 );\n"
	    "    longname[l1+l2+1] = ']';\n"
	    "    longname[l1+l2+2] = 0;\n"
	    "    set_self( longname, os );\n"
	    "  };\n"
	    "  void %s::set_self_2( const char *n1, const char *n2, int os ) {\n"
	    "    if (n1 == NULL) {set_self(NULL, 0); return;}\n"
	    "    strcpy( longname, n1 );\n"
	    "    strcat( longname, n2 );\n"
	    "    set_self( longname, os );\n" "  };\n", mu_name, mu_name);
    fprintf(codefile,
	    "void %s::set_self(const char *n, int os)\n"
	    "{\n" 
	    "  name = (char *)n;\n\n", mu_name);
    for (f = fields; f != NULL; f = f->getnext()) {
      fprintf(codefile,
	      "  if (name) %s.set_self_2(name, \"%s\", os + %d ); else %s.set_self_2(NULL, NULL, 0);\n",
	      f->getvalue()->generate_code(),
	      tsprintf(".%s", f->getvalue()->name),
	      ((vardecl *) f->getvalue())->getoffset(),
	      f->getvalue()->generate_code());
    }
    fprintf(codefile, "}\n\n");

    /* destructor def */
    fprintf(codefile,		// Uli: no delete since there in no new
	    "%s::~%s()\n{\n" 
//	    "  if (name) delete [] name;\n"
	    , mu_name, mu_name);

    // for(f = fields; f != NULL; f = f->getnext() ) {
    //   fprintf(codefile,"  delete[ OLD_GPP(strlen(%s.name) + 1)] %s.name; // Should be delete[] \n",
    //     f->getvalue()->generate_code(),
    //     f->getvalue()->generate_code());
    // }
    fprintf(codefile, "}\n\n");

    fprintf(codefile, "/*** end record declaration ***/\n");
    fprintf(codefile, "%s %s_undefined_var;\n\n", mu_name, mu_name);

    declared = TRUE;
  }
  return "ERROR!";
}

 /********************
   code for scalarsettypedecl
   ********************/
void make_scalarset_idvalues(ste * idvalues, int size, bool named)
{
  if (size > 1)
    make_scalarset_idvalues(idvalues->next, size - 1, named);
  if (named) {
    fprintf(codefile, "\"%s\",", idvalues->getname()->getname());
  } else {
    char *c = idvalues->getname()->getname();
    while (*c != '_')
      c++;
    c++;
    fprintf(codefile, ",\"%s\"", c);
  }
}

const char *scalarsettypedecl::generate_decl()
{
  if (!declared) {
    if (name == NULL) {
      name = tsprintf("_scalarset_%d", tNum);
      mu_name = tsprintf("mu_%s", name);
    }

    /* declare class, <<, initializers, and destructor */
    fprintf(codefile, "class %s: public %s\n" "{\n" " public:\n" "  inline int operator=(int val) { return value(val); };\n" "  inline int operator=(const %s& val){" " return value(val.value());};\n" "  inline operator int() const { return value(); };\n" "  static const char *values[];\n" "  friend ostream& operator<< (ostream& s, %s& val)\n" "    {\n" "      if (val.defined())\n" "	return ( s << %s::values[ int(val) - %d ] );\n" "      else\n" "	return ( s << \"Undefined\" );\n" "    };\n\n" "  %s (const char *name, int os): %s(%d, %d, %d, name, os) {};\n" "  %s (void): %s(%d, %d, %d) {};\n" "  %s (int val): %s(%d, %d, %d, \"Parameter or function result.\", 0)\n" "    { operator=(val); };\n", mu_name, mu_type,	/* class name */
	    mu_name, mu_name,	/* type name for second arg to << */
	    mu_name,		/* class preceding values in body of << */
	    left,		/* lower bound for scalarset value */
	    mu_name, mu_type, left, right, numbits,
	    /* args for first constructor */
	    mu_name, mu_type, left, right, numbits,
	    /* args for second constructor */
	    mu_name, mu_type, left, right, numbits);
    /* args for third constructor */

    /* declare operator= and print */
    fprintf(codefile,
	    "  const char * Name() { return values[ value() -%d]; };\n"
//       "  inline int operator=(int val) { return %s::operator=(val); };\n"
//       "  inline int operator=(const %s& val) { return %s::operator=((int) val); };\n"
	    "  virtual void print()\n" "    {\n" "      if (defined()) cout << name << ':' << values[ value() - %d] << '\\n';\n" "      else cout << name << \":Undefined\\n\";\n" "    };\n", left, left);	/* lower bound for values array reference */

    fprintf(codefile, "  void print_statistic() {};\n");

    /* comparsion function */
    fprintf(codefile,
	    "friend int CompareWeight(%s& a, %s& b)\n"
	    "{\n"
	    "  if (!a.defined() && b.defined())\n"
	    "    return -1;\n"
	    "  else if (a.defined() && !b.defined())\n"
	    "    return 1;\n"
	    "  else\n" "    return 0;\n" "}\n", mu_name, mu_name);

    /* declare permute() */
    theprog->symmetry.generate_symmetry_function_decl();

    /* end class definition */
    fprintf(codefile, "};\n");

    /* create the values array. */
    fprintf(codefile, "const char *%s::values[] =\n" "  { ", mu_name);
    make_scalarset_idvalues(idvalues, getsize(), named);
    fprintf(codefile, "NULL };\n\n");
    fprintf(codefile, "/*** end scalarset declaration ***/\n");
    fprintf(codefile, "%s %s_undefined_var;\n\n", mu_name, mu_name);

    declared = TRUE;
  }
  return "ERROR!";
}

/********************
  code for uniontypedecl
  ********************/
void make_union_idvalues(stelist * unionmembers)
{
  if (unionmembers->next != NULL)
    make_union_idvalues(unionmembers->next);

  if (((typedecl *) unionmembers->s->getvalue())->gettypeclass() ==
      typedecl::Scalarset)
    make_scalarset_idvalues(((scalarsettypedecl *)
			     unionmembers->s->getvalue())->getidvalues(),
			    unionmembers->s->getvalue()->getsize(), TRUE);
  else if (((typedecl *) unionmembers->s->getvalue())->gettypeclass() ==
	   typedecl::Enum)
    make_enum_idvalues(((enumtypedecl *)
			unionmembers->s->getvalue())->getidvalues(),
		       (typedecl *) unionmembers->s->getvalue());
  else
    Error.Error("funny element in union");
}

// int make_assign_union_values(stelist * unionmembers)
// {
//   int base = 0;
//   if (unionmembers->next != NULL)
//       base = make_assign_union_values(unionmembers->next);
//   
//   typedecl *t= (typedecl *) unionmembers->s->getvalue();
//   fprintf(codefile,
//      "    if ( ( val >= %d ) && ( val <= %d ) ) {\n"
//   //       "      defined = TRUE;\n"
//      "      initialized = TRUE;\n"
//      "      return value(val - %d);\n"
//      "    }\n",
//      t->getleft(),
//      t->getright(),
//      t->getleft() - base);
//   return base + t->getsize();
// }  

int make_union_indexval(stelist * unionmembers)
{
  int base = 0;
  if (unionmembers->next != NULL)
    base = make_union_indexval(unionmembers->next);

  typedecl *t = (typedecl *) unionmembers->s->getvalue();
  fprintf(codefile,
	  "    if ((value() >= %d) && (value() <= %d))"
	  " return (value() - %d);\n",
	  t->getleft(), t->getright(), t->getleft() - base);
  return base + t->getsize();
}

int make_bit_compacted_value_assign(stelist * unionmembers)
{
  int base = 0;
  if (unionmembers->next != NULL)
    base = make_bit_compacted_value_assign(unionmembers->next);

  typedecl *t = (typedecl *) unionmembers->s->getvalue();
  fprintf(codefile,
	  "    if ((val >= %d) && (val <= %d))"
	  " return (mu__byte::value(val-%d)+%d);\n",
	  t->getleft(),
	  t->getright(), t->getleft() - base, t->getleft() - base);
  return base + t->getsize();
}

int make_union_unionassign(stelist * unionmembers)
{
  int base = 0;
  if (unionmembers->next != NULL)
    base = make_union_unionassign(unionmembers->next);

  typedecl *t = (typedecl *) unionmembers->s->getvalue();
  fprintf(codefile,
	  "    if (val >= %d && val <= %d) return value(val+%d);\n",
	  // Uli: return added
	  base, base + t->getsize() - 1, t->getleft() - base);
  return base + t->getsize();
}

int make_bit_compacted_value(stelist * unionmembers)
{
  int base = 0;
  if (unionmembers->next != NULL)
    base = make_bit_compacted_value(unionmembers->next);

  typedecl *t = (typedecl *) unionmembers->s->getvalue();
  fprintf(codefile,
	  "    if (val <= %d) return val+%d;\n",
	  base + t->getsize() - 1, t->getleft() - base);
  return base + t->getsize();
}

// int make_reference_union_values(stelist * unionmembers)
// {
//   int base = 0;
//   if (unionmembers->next != NULL)
//       base = make_reference_union_values(unionmembers->next);
//   typedecl *t= (typedecl *) unionmembers->s->getvalue();
//   fprintf(codefile,
//      "    if ( ( val >= %d ) && ( val <= %d ) )\n"
//      "      return val + %d;\n",
//      base,
//      base + t->getsize() - 1,
//      t->getleft() - base);
//   return base + t->getsize();
// }  

const char *uniontypedecl::generate_decl()
{
  if (!declared) {
    if (name == NULL) {
      name = tsprintf("_union_%d", tNum);
      mu_name = tsprintf("mu_%s", name);
    }

    /* declare class, <<, initializers, and destructor */
    fprintf(codefile,
	    "class %s: public %s\n"
	    "{\n"
	    " public:\n"
	    "  inline int operator=(int val) { return value(val); };\n"
	    // Uli: return added
	    "  inline int operator=(const %s& val) {" " return value(val.value()); };\n" "  inline operator int() const { return value(); };\n" "  static const char *values[];\n" "  friend ostream& operator<< (ostream& s, %s& val)\n" "    {\n" "      if (val.defined())\n" "	return ( s << %s::values[ val.indexvalue() ] );\n" "      else\n" "	return ( s << \"Undefined\" );\n" "    };\n\n" "  // note thate lb and ub are not used if we have byte compacted state.\n" "  %s (const char *name, int os): %s(%d, %d, %d, name, os) {};\n" "  %s (void): %s(%d, %d, %d) {};\n" "  %s (int val): %s(%d, %d, %d, \"Parameter or function result.\", 0)\n" "    { operator=(val); };\n", mu_name, mu_type,	/* class name */
	    mu_name,		/* operator= */
	    mu_name,		/* type name for second arg to << */
	    mu_name,		/* class preceding values in body of << */
	    mu_name, mu_type, 0, size - 1, numbits,
	    /* args for first constructor */
	    mu_name, mu_type, 0, size - 1, numbits,
	    /* args for second constructor */
	    mu_name, mu_type, 0, size - 1, numbits);
    /* args for third constructor */

    //
    if (args->no_compression) {
      fprintf(codefile, "  int indexvalue()\n" "  {\n");
      make_union_indexval(unionmembers);
      fprintf(codefile, "  return 0;\n  };\n");

      fprintf(codefile, "  inline int unionassign(int val)\n" "  {\n");
      make_union_unionassign(unionmembers);
      fprintf(codefile, "  return 0;\n  };\n");
    } else {
      fprintf(codefile,
	      "  int value() const\n"
	      "  {\n"
	      "    int val = mu__byte::value();\n"
	      "    // val == -1 if value undefined\n"
	      "    // we can return it since no enum/scalarsetid will have value -1\n"
	      "    if (val == -1) return -1;\n");
      make_bit_compacted_value(unionmembers);
      fprintf(codefile,
	      "  }\n"
	      "  inline int value(int val)\n"
	      "  {\n" "    if (val == -1) { undefine(); return -1; }\n");
      make_bit_compacted_value_assign(unionmembers);
      fprintf(codefile,
	      "  }\n"
	      "  inline int indexvalue() const\n"
	      "  {\n" "    return mu__byte::value();\n" "  };\n");
      fprintf(codefile,
	      "  inline int unionassign(int val)\n"
	      "  {\n" "    return mu__byte::value(val);\n" "  };\n");
    }


    /* operator=() */
//       fprintf(codefile, 
//      "  inline int operator=(int val)\n"
//      "  {\n");
//       make_assign_union_values(unionmembers);
//       fprintf(codefile, 
//      "    Error.Error(\"Funny values being assigned to %%s \\n\", name);\n"
//      "    return 0;\n"
//      " };\n");


//      fprintf(codefile, 
//      "  inline void unionassign(int val)\n"
//      "  {\n"
//          "    defined = TRUE;\n"
//      "    initialized = TRUE;\n"
//      "    value(val);\n"
//      "  }\n"
//      );

//       fprintf(codefile, 
//          "  int operator=(const %s& val)\n"
//          "  {\n",
//      mu_name
//      );
//       make_assign_union_values(unionmembers);
//       fprintf(codefile, 
//          "    Error.Error(\"Funny values being assigned to %%s \\n\", name);\n"
//          "    return 0;\n"
//          " };\n",
//      mu_name);

    /* operator int() */
//       fprintf(codefile, 
//          "operator int() const\n  {\n"
//          "  int val = %s::operator int();\n",
//      mu_type
//      );
//       make_reference_union_values(unionmembers);
//       fprintf(codefile, 
//          "    Error.Error(\"Funny values being assigned to %%s \\n\", name);\n"
//          "    return 0;\n"
//          "  };\n");

    fprintf(codefile,
	    "  const char * Name() { return values[ indexvalue() ]; };\n");

    fprintf(codefile,
	    "friend int CompareWeight(%s& a, %s& b)\n"
	    "{\n"
	    "  if (!a.defined() && b.defined())\n"
	    "    return -1;\n"
	    "  else if (a.defined() && !b.defined())\n"
	    "    return 1;\n"
	    "  else\n" "    return 0;\n" "}\n", mu_name, mu_name);

    /* declare permute() */
    theprog->symmetry.generate_symmetry_function_decl();

    /* print() */
    fprintf(codefile,
	    "  virtual void print()\n"
	    "    {\n"
	    "      if (defined()) cout << name << ':' << "
	    "values[ indexvalue() ] << '\\n';\n"
	    "      else cout << name << \":Undefined\\n\";\n" "    };\n");
    fprintf(codefile, "  void print_statistic() {};\n");


    /* end class definition */
    fprintf(codefile, "};\n");

    /* create the values array. */
    fprintf(codefile, "const char *%s::values[] = {", mu_name);
    make_union_idvalues(unionmembers);
    fprintf(codefile, "NULL };\n\n");

    fprintf(codefile, "/*** end union declaration ***/\n");
    fprintf(codefile, "%s %s_undefined_var;\n\n", mu_name, mu_name);

    declared = TRUE;
  }
  return "ERROR!";
}

/********************
  code for constdecl
 ********************/
const char *constdecl::generate_decl()
{
  if (!declared) {
    if (type_equal(type, realtype))	// AP: real constant's declaration
      fprintf(codefile, "const double %s = %+le;\n", mu_name, rvalue);
    else
      fprintf(codefile, "const int %s = %d;\n", mu_name, value);
    declared = TRUE;
  }
  return "ERROR!";
}


/********************
  code for vardecl
 ********************/
const char *vardecl::generate_decl()
{
  if (!declared) {
    fprintf(codefile,
	    "/*** Variable declaration ***/\n"
	    "%s %s(\"%s\",%d);\n\n",
	    type->generate_code(), mu_name, name, offset);
    declared = TRUE;
  }
  return "ERROR!";
}

/********************
  code for aliasdecl
 ********************/

const char *aliasdecl::generate_decl()
{
  if (!declared) {
    if (!ref->islvalue() && ref->gettype()->issimple()) {
      if (type_equal(ref->gettype(), realtype))
	fprintf(codefile,
		"  const double %s = %s;\n", mu_name,
		ref->generate_code());
      else
	fprintf(codefile,
		/* BUG: BOGUS CONST INT */
		/* is this fixed adding  ref->gettype()->issimple() */
		"  const int %s = %s;\n", mu_name, ref->generate_code());
    } else {
      fprintf(codefile, "  %s& %s = %s;\n",
	      ref->gettype()->generate_code(),
	      mu_name, ref->generate_code());
    }
  }
  return "ERROR!";
}

/********************
  code for choosedecl
 ********************/
const char *choosedecl::generate_decl()
/* Should never actually get called. */
{
  Error.Error
      ("Internal: choosedecl::generate_decl() should not have been called.");
  return "ERROR!";
}

/********************
  code for quantdecl
 ********************/
const char *quantdecl::generate_decl()
/* Should never actually get called. */
{
  Error.Error
      ("Internal: quantdecl::generate_decl() should not have been called.");
  return "ERROR!";
}

void quantdecl::make_for()
/* generates a _for_
 * statement that could serve as a wrapper for a FOR or FORALL.
 * However, this won\'t cut it for rulesets, which will have to
 * do it themselves. */
/* BUG:  There seem to be a lot of special cases here.  Why is the
   loop variable "mu_name"? */
{
  // fprintf(codefile,"int %s;\n",mu_name);
  /* I think it\'s better to declare the index in the loop. */
  if (left == NULL) {
    if (type->gettypeclass() == typedecl::Union) {
      stelist *t;
      typedecl *d;
      int minleft, maxright;

      // find max right and min left
      t = ((uniontypedecl *) type)->getunionmembers();
      d = (typedecl *) t->s->getvalue();
      minleft = d->getleft();
      maxright = d->getright();
      t = t->next;
      for (; t != NULL; t = t->next) {
	d = (typedecl *) t->s->getvalue();
	if (d->getleft() < minleft)
	  minleft = d->getleft();
	if (d->getright() > maxright)
	  maxright = d->getright();
      }

      fprintf(codefile,
	      "for(int %s = %d; %s <= %d; %s++)\n"
	      "  if (", mu_name, minleft, mu_name, maxright, mu_name);

      // check each element
      t = ((uniontypedecl *) type)->getunionmembers();
      d = (typedecl *) t->s->getvalue();
      fprintf(codefile,
	      "( ( %s >= %d ) && ( %s <= %d ) )",
	      mu_name, d->getleft(), mu_name, d->getright()
	  );
      t = t->next;
      for (; t != NULL; t = t->next) {
	d = (typedecl *) t->s->getvalue();
	fprintf(codefile,
		"|| ( ( %s >= %d ) && ( %s <= %d ) )",
		mu_name, d->getleft(), mu_name, d->getright()
	    );
      }
      fprintf(codefile, ") {\n");
    } else
      fprintf(codefile, "for(int %s = %d; %s <= %d; %s++) {\n", mu_name, type->getleft(),	/* change here */
	      mu_name, type->getright(), mu_name);
  } else {
    /* Dill: Why is this name needed? */
    /* Ip: upbound is used as a new local variable which does not clash with other */
    char *upbound = tsprintf("mu__ub%d", new_int());
    if (type_equal(right->gettype(), realtype))
      fprintf(codefile, "double %s = %s;\n", upbound,
	      right->generate_code());
    else
      fprintf(codefile, "int %s = %s;\n", upbound, right->generate_code());
    if (by > 0) {
      if (type_equal(left->gettype(), realtype))
	fprintf(codefile,
		"for (double %s = %s; %s <= %s; %s += %le) {\n",
		mu_name,
		left->generate_code(), mu_name, upbound, mu_name, byR);
      else
	fprintf(codefile,
		"for (int %s = %s; %s <= %s; %s += %d) {\n",
		mu_name,
		left->generate_code(), mu_name, upbound, mu_name, by);
    } else {
      if (type_equal(left->gettype(), realtype))
	fprintf(codefile,
		"for (double %s = %s; %s >= %s; %s += %+le) {\n",
		mu_name,
		left->generate_code(), mu_name, upbound, mu_name, byR);
      else
	fprintf(codefile,
		"for (int %s = %s; %s >= %s; %s += %d) {\n",
		mu_name,
		left->generate_code(), mu_name, upbound, mu_name, by);
    }
  }
  declared = TRUE;
}

/********************
  code for parameter
 ********************/
const char *param::generate_decl()
{
  Error.Error("Internal: param::generate_decl()");
  return "ERROR!";
}

const char *varparam::generate_decl()
{
  if (!declared) {
    fprintf(codefile, "%s& %s", type->generate_code(), mu_name);
    declared = TRUE;
  }
  return "ERROR!";
}

const char *valparam::generate_decl()
{
  if (!declared) {
    fprintf(codefile, "%s %s", type->generate_code(), mu_name);
    declared = TRUE;
  }
  return "ERROR!";
}

/* We have to do some skanky workarounds here;
 * CC won't let us declare our smart operator [] as
 * const, but if we don't, we can't use operator [] for
 * for a constant array.  So we work around this by
 * dropping the constant for a const array parameter.
 *
 * Furthermore, since a const record can include a const
 * array, we need to drop the const for records, too.
 * This is okay, since we\'ve checked in the Murphi
 * semantic-checking, and we know that this array isn\'t
 * modified, and we know that no conversion will be involved,
 * since Murphi doesn\'t allow conversion among aggregate
 * types.
 *
 * We do need the const for simple types, since otherwise,
 * we won\'t get any automatic conversion from C++.
 */
const char *constparam::generate_decl()
{
  if (!declared) {
    if (type->issimple())
      fprintf(codefile, "const %s& %s", type->generate_code(), mu_name);
    else
      fprintf(codefile, "%s& %s", type->generate_code(), mu_name);

    declared = TRUE;
  }
  return "ERROR!";
}

/********************
  code for procdecl
 ********************/
const char *procdecl::generate_decl()
{
  if (!declared) {
    if (!extern_def) {
      /* the declaration. */
      fprintf(codefile, "void %s(", mu_name);

      /* formal parameter list */
      for (ste * p = params; p != NULL; p = p->getnext()) {
	p->getvalue()->generate_decl();
	if (p->getnext() == NULL)
	  break;
	fprintf(codefile, ", ");
      }
      fprintf(codefile, ")\n" "{\n");

      /* the locals. */
      decls->generate_decls();

      /* the statements. */
      for (stmt * s = body; s != NULL; s = s->next) {
	s->generate_code();
      }

      fprintf(codefile, "};\n");

      fprintf(codefile, "/*** end procedure declaration ***/\n\n");

      declared = TRUE;
    } else if (include_file_ext != NULL)
      fprintf(codefile, "\n#include \"%s\"\n\n", include_file_ext);
  }
  return "ERROR!";
}

/********************
  code for funcdecl
 ********************/

/* BUG: check for return everywhere? */
/* Norris: fixed by adding an error at the very end... so that user will
   know and go back and fix the function */

const char *funcdecl::generate_decl()
{
  if (!declared) {
    if (!extern_def) {
      /* the declaration. */
      fprintf(codefile, "%s %s(", returntype->generate_code(), mu_name);
      /* formal parameters */
      for (ste * p = params; p != NULL; p = p->getnext()) {
	p->getvalue()->generate_decl();
	if (p->getnext() == NULL)
	  break;
	fprintf(codefile, ",");
      }
      fprintf(codefile, ")\n" "{\n");

      /* the locals. */
      decls->generate_decls();

      /* the statements. */
      for (stmt * s = body; s != NULL; s = s->next) {
	s->generate_code();
      }

      fprintf(codefile,
	      "	Error.Error(\"The end of function %s reached without returning values.\");\n",
	      name);

      fprintf(codefile, "};\n");

      fprintf(codefile, "/*** end function declaration ***/\n\n");

      declared = TRUE;
    } else if (include_file_ext != NULL)
      fprintf(codefile, "\n#include \"%s\"\n\n", include_file_ext);
  }
  return "ERROR!";
}

/********************
  code related to expression
  -- 
  -- expr
  -- boolexpr
  -- -- notexpr
  -- -- equalexpr
  -- -- compexpr
  -- arithexpr
  -- -- unexpr
  -- -- mulexpr
  -- condexpr
  -- quantexpr
  -- designator
  -- exprlist
  -- funccall
 ********************/

/********************
  code for expr
 ********************/
const char *expr::generate_code()
{
  if (constval)
    if (type_equal(type, realtype))
      return tsprintf("%le", rvalue);	// AP: value of a real constant
    else
      return tsprintf("%d", value);
  else {
    Error.Error
	("Internal: a basic expression that wasn't a constant called expr::generate_code().");
    return "ERROR!";
  }
}

//IM: for math functions
const char *mathexpr::generate_code()
{
  if (constval)
    return tsprintf("%le", rvalue);
  switch (getfuntype()) {
  case mylog:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", log(arg1->getrvalue()));
	else
	  return tsprintf("%le", log(arg1->getvalue()));
      } else
	return tsprintf("log((double)%s)", arg1->generate_code());
      break;
    }
  case mylog10:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", log10(arg1->getrvalue()));
	else
	  return tsprintf("%le", log10(arg1->getvalue()));
      } else
	return tsprintf("log10((double)%s)", arg1->generate_code());
      break;
    }
  case myexp:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", exp(arg1->getrvalue()));
	else
	  return tsprintf("%le", exp(arg1->getvalue()));
      } else
	return tsprintf("exp((double)%s)", arg1->generate_code());
      break;
    }
  case mysin:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", sin(arg1->getrvalue()));
	else
	  return tsprintf("%le", sin(arg1->getvalue()));
      } else
	return tsprintf("sin((double)%s)", arg1->generate_code());
      break;
    }
  case mycos:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", cos(arg1->getrvalue()));
	else
	  return tsprintf("%le", cos(arg1->getvalue()));
      } else
	return tsprintf("cos((double)%s)", arg1->generate_code());
      break;
    }
  case mytan:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", tan(arg1->getrvalue()));
	else
	  return tsprintf("%le", tan(arg1->getvalue()));
      } else
	return tsprintf("tan((double)%s)", arg1->generate_code());
      break;
    }
  case myfabs:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", fabs(arg1->getrvalue()));
	else
	  return tsprintf("%le", fabs(arg1->getvalue()));
      } else
	return tsprintf("fabs((double)%s)", arg1->generate_code());
      break;
    }
  case myfloor:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", floor(arg1->getrvalue()));
	else
	  return tsprintf("%le", floor(arg1->getvalue()));
      } else
	return tsprintf("floor((double)%s)", arg1->generate_code());
      break;
    }
  case myceil:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", ceil(arg1->getrvalue()));
	else
	  return tsprintf("%le", ceil(arg1->getvalue()));
      } else
	return tsprintf("ceil((double)%s)", arg1->generate_code());
      break;
    }
  case mysqrt:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", sqrt(arg1->getrvalue()));
	else
	  return tsprintf("%le", sqrt(arg1->getvalue()));
      } else
	return tsprintf("sqrt((double)%s)", arg1->generate_code());
      break;
    }
  case myfmod:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype)) {
	  if (type_equal(arg2->gettype(), realtype))
	    return tsprintf("%le",
			    fmod(arg1->getrvalue(), arg2->getrvalue()));
	  else
	    return tsprintf("%le",
			    fmod(arg1->getrvalue(), arg2->getvalue()));
	} else {
	  if (type_equal(arg2->gettype(), realtype))
	    return tsprintf("%le",
			    fmod(arg1->getvalue(), arg2->getrvalue()));
	  else
	    return tsprintf("%le",
			    fmod(arg1->getvalue(), arg2->getvalue()));
	}
      } else
	return tsprintf("fmod((double)%s,(double)%s)",
			arg1->generate_code(), arg2->generate_code());
      break;
    }
  case mypow:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype)) {
	  if (type_equal(arg2->gettype(), realtype))
	    return tsprintf("%le",
			    pow(arg1->getrvalue(), arg2->getrvalue()));
	  else
	    return tsprintf("%le",
			    pow(arg1->getrvalue(), arg2->getvalue()));
	} else {
	  if (type_equal(arg2->gettype(), realtype))
	    return tsprintf("%le",
			    pow(arg1->getvalue(), arg2->getrvalue()));
	  else
	    return tsprintf("%le",
			    pow(arg1->getvalue(), arg2->getvalue()));
	}
      } else
	return tsprintf("pow((double)%s,(double)%s)",
			arg1->generate_code(), arg2->generate_code());
      break;
    }
  case myasin:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", asin(arg1->getrvalue()));
	else
	  return tsprintf("%le", asin(arg1->getvalue()));
      } else
	return tsprintf("asin((double)%s)", arg1->generate_code());
      break;
    }
  case myacos:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", acos(arg1->getrvalue()));
	else
	  return tsprintf("%le", acos(arg1->getvalue()));
      } else
	return tsprintf("acos((double)%s)", arg1->generate_code());
      break;
    }
  case myatan:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", atan(arg1->getrvalue()));
	else
	  return tsprintf("%le", atan(arg1->getvalue()));
      } else
	return tsprintf("atan((double)%s)", arg1->generate_code());
      break;
    }
  case mysinh:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", sinh(arg1->getrvalue()));
	else
	  return tsprintf("%le", sinh(arg1->getvalue()));
      } else
	return tsprintf("sinh((double)%s)", arg1->generate_code());
      break;
    }
  case mycosh:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", cosh(arg1->getrvalue()));
	else
	  return tsprintf("%le", cosh(arg1->getvalue()));
      } else
	return tsprintf("cosh((double)%s)", arg1->generate_code());
      break;
    }
  case mytanh:
    {
      if (constval) {
	if (type_equal(arg1->gettype(), realtype))
	  return tsprintf("%le", tanh(arg1->getrvalue()));
	else
	  return tsprintf("%le", tanh(arg1->getvalue()));
      } else
	return tsprintf("tanh((double)%s)", arg1->generate_code());
      break;
    }
  }
}

/********************
  code for boolexpr
 ********************/
const char *boolexpr::generate_code()
{
  if (constval)
    return tsprintf("%d", value);
  else {
    int num = new_int();
    char *temp = tsprintf("mu__boolexpr%d", num);
    fprintf(codefile, "bool %s;\n", temp);

    switch (op) {
    case IMPLIES:
      fprintf(codefile, "  if (!(%s)) %s = TRUE ;\n"
	      "  else {\n", left->generate_code(), temp);
      fprintf(codefile, "  %s = (%s) ; \n}\n", temp,
	      right->generate_code());
      return temp;
      break;
    case '|':
      fprintf(codefile, "  if (%s) %s = TRUE ;\n"
	      "  else {\n", left->generate_code(), temp);
      fprintf(codefile, "  %s = (%s) ; \n}\n", temp,
	      right->generate_code());
      return temp;
      break;
    case '&':
      fprintf(codefile, "  if (!(%s)) %s = FALSE ;\n"
	      "  else {\n", left->generate_code(), temp);
      fprintf(codefile, "  %s = (%s) ; \n}\n", temp,
	      right->generate_code());
      return temp;
      break;
    default:
      Error.Error
	  ("Internal: funky value for op in boolexpr::generate_code()");
      return "ERROR!";
      break;
    }
  }
}

/********************
  code for notexpr
 ********************/
const char *notexpr::generate_code()
{
  return tsprintf("!(%s)", left->generate_code());
}

/********************
  code for equalexpr
 ********************/
const char *equalexpr::generate_code()
{
  if (constval)
    return tsprintf("%d", value);
  else {
    switch (op) {
    case '=':
      return tsprintf("(%s) == (%s)",
		      left->generate_code(), right->generate_code());
      break;
    case NEQ:
      return tsprintf("(%s) != (%s)",
		      left->generate_code(), right->generate_code());
      break;
    default:
      Error.Error
	  ("Internal: exciting value for op in equalexpr::generate_code().");
      return "ERROR!";
      break;
    }
  }
}

/********************
  code for compexpr
 ********************/
const char *compexpr::generate_code()
{
  if (constval)
    return tsprintf("%d", value);
  else {
    switch (op) {
    case '<':
      return tsprintf("(%s) < (%s)",
		      left->generate_code(), right->generate_code());
    case LEQ:
      return tsprintf("(%s) <= (%s)",
		      left->generate_code(), right->generate_code());
    case '>':
      return tsprintf("(%s) > (%s)",
		      left->generate_code(), right->generate_code());
    case GEQ:
      return tsprintf("(%s) >= (%s)",
		      left->generate_code(), right->generate_code());
    default:
      Error.Error("Internal: odd value in compexpr::generate_code()");
      return "ERROR!";
    }
  }
}

/********************
  code for arithexpr
 ********************/
const char *arithexpr::generate_code()
{
  if (constval)
    if (type_equal(type, realtype))
      return tsprintf("%le", rvalue);	// AP: value of a real arithmetic expression (+,-)
    else
      return tsprintf("%d", value);
  else {
    switch (op) {
    case '+':
      return tsprintf("(%s) + (%s)",
		      left->generate_code(), right->generate_code());
    case '-':
      return tsprintf("(%s) - (%s)",
		      left->generate_code(), right->generate_code());
    default:
      Error.Error("Internal: bad operator in arithexpr::generate_code()");
      return "ERROR!";
    }
  }
};

/********************
  code for unexpr
 ********************/
const char *unexpr::generate_code()
{
  if (constval)
    if (type_equal(type, realtype))
      return tsprintf("%le", rvalue);	// AP: value of a real unary expression
    else
      return tsprintf("%d", value);
  else {
    switch (op) {
    case '+':
      return left->generate_code();
    case '-':
      return tsprintf(" - (%s)", left->generate_code());
    default:
      Error.Error("Internal: bad operator in arithexpr::generate_code()");
      return "ERROR!";
    }
  }
};

/********************
  code for mulexpr
 ********************/
const char *mulexpr::generate_code()
{
  if (constval)
    if (type_equal(type, realtype))
      return tsprintf("%le", rvalue);	// AP: value of a real arithmetic expression (*,/)
    else
      return tsprintf("%d", value);
  else {
    switch (op) {
    case '*':
      return tsprintf("(%s) * (%s)",
		      left->generate_code(), right->generate_code());
    case '/':
      return tsprintf("(%s) / (%s)",
		      left->generate_code(), right->generate_code());
    case '%':
      return tsprintf("(%s) %% (%s)",	/* doubled % to accomodate printf. */
		      left->generate_code(), right->generate_code());
    default:
      Error.Error("Internal: bad operator in mulexpr::generate_code()");
      return "ERROR!";
    }
  }
}

/********************
  code for condexpr
 ********************/
const char *condexpr::generate_code()
{
  return tsprintf("(%s) ? (%s) : (%s)",
		  test->generate_code(),
		  left->generate_code(), right->generate_code());
}

/********************
  code for quantexpr
 ********************/

void make_quant_fors(ste * quants)
{
  if (quants != NULL && quants->getvalue()->getclass() == decl::Quant) {
    make_quant_fors(quants->getnext());
    ((quantdecl *) quants->getvalue())->make_for();
  }
}

void make_quant_closes(ste * quants)
{
  if (quants != NULL && quants->getvalue()->getclass() == decl::Quant) {
    make_quant_closes(quants->getnext());
    fprintf(codefile, "};\n");
  }
}

const char *quantexpr::generate_code()
{
  int num = new_int();
  char *temp = tsprintf("mu__quant%d", num);
  bool isforall = ((op == FORALL) ? TRUE : FALSE);

  // Uli: initialization in the declaration not allowed in this case
  fprintf(codefile, "bool %s; \n%s = %s;\n",
	  temp, temp, (isforall ? "TRUE" : "FALSE"));
  fprintf(codefile, "{\n");
  make_quant_fors(parameter);
  /* so the new parameter doesn\'t conflict with others if it\'s reused. */
  fprintf(codefile,
	  "if ( %s(%s) )\n", (isforall ? "!" : ""), left->generate_code());
  // Uli: a "goto" to exit the for loop seemed to cause problems on some
  //      compilers when there were local variables
  fprintf(codefile,
	  "  { %s = %s; break; }\n", temp, (isforall ? "FALSE" : "TRUE"));
  make_quant_closes(parameter);
  fprintf(codefile, "};\n");

  return temp;
}


/********************
  code for designator
 ********************/
const char *designator::generate_code()
{
  switch (dclass) {
  case Base:
    return origin->getvalue()->generate_code();
  case ArrayRef:
    return tsprintf("%s[%s]",
		    left->generate_code(), arrayref->generate_code());
    break;
  case FieldRef:
    return tsprintf("%s.%s",
		    left->generate_code(), fieldref->getvalue()->mu_name);
    break;
  default:
    Error.Error
	("Internal: Strange and mysterious values for designator::dclass.");
    return "ERROR!";
    break;
  }
}


/********************
  code for exprlist
 ********************/
const char *exprlist::generate_code(const char *name, ste * formals)
{
  exprlist *ex = this;
  if (this == NULL) {
    // exprlist_buffer_end = exprlist_buffer;
    return "ERROR!";
  } else {
    char *exprlist_buffer = new char[BUFFER_SIZE];
    char *exprlist_buffer_end = exprlist_buffer;
    for (ex = this; formals != NULL && ex != NULL;
	 formals = formals->getnext(), ex = ex->next) {
      param *f = (param *) formals->getvalue();
      if (!ex->undefined) {
	if (f->gettype() != ex->e->gettype() &&
	    ((ex->e->gettype()->gettypeclass() == typedecl::Range
	      && ((f->gettype()->gettype() == ex->e->gettype()->gettype())
		  || (type_equal(f->gettype(), realtype)))
	     )
	     ||
	     ((ex->e->gettype()->gettypeclass() == typedecl::Scalarset
	       || ex->e->gettype()->gettypeclass() == typedecl::Enum)
	      && f->gettype()->gettypeclass() == typedecl::Union)
	     ||
	     (ex->e->gettype()->gettypeclass() == typedecl::Union
	      && (f->gettype()->gettypeclass() == typedecl::Scalarset
		  || f->gettype()->gettypeclass() == typedecl::Enum))
	    )
	    )
	  sprintf(exprlist_buffer_end, ", (int)%s",
		  ex->e->generate_code());
	else if (f->gettype() != ex->e->gettype()
		 && (type_equal(ex->e->gettype(), realtype)
		     && f->gettype()->gettype() ==
		     ex->e->gettype()->gettype()))
	  sprintf(exprlist_buffer_end, ", (double)%s",
		  ex->e->generate_code());
	else
	  sprintf(exprlist_buffer_end, ", %s", ex->e->generate_code());
      } else {
	sprintf(exprlist_buffer_end, ", %s_undefined_var",
		f->gettype()->generate_code());
      }
      exprlist_buffer_end += strlen(exprlist_buffer_end);
    }
    if (strlen(exprlist_buffer) > BUFFER_SIZE)
      Error.Error("Internal: Buffer size for expression list overflow.\n"
		  "	  Please increase BUFFER_SIZE in /src/mu.h");
    return (exprlist_buffer + 2);	// + 2 to skip the leading comma and space
    /* BUG: Aargh! We can\'t delete the buffer! */
  }
}

// char *exprlist::generate_code()
// {
//   exprlist *ex = this;
//   if (this == NULL ) {
//     // exprlist_buffer_end = exprlist_buffer;
//     return "ERROR!";
//   }
//   else {
//     char *exprlist_buffer = new char[BUFFER_SIZE];
//     char *exprlist_buffer_end = exprlist_buffer;
//     for (ex = this; ex != NULL; ex = ex->next) {
//       sprintf(exprlist_buffer_end, ", %s", ex->e->generate_code() );
//       exprlist_buffer_end += strlen(exprlist_buffer_end);
//     }
//     return ( exprlist_buffer + 2); // + 2 to skip the leading comma and space
//     /* BUG: Aargh! We can\'t delete the buffer! */
//     }
// }

/********************
  code for funccall
 ********************/
/* BUG: Caution: is there any way the generated statement can end up in
   the middle of an expression? */

const char *funccall::generate_code()
{
  funcdecl *f = (funcdecl *) func->getvalue();
  return tsprintf("%s( %s )",
		  //im: for imported functions, "mu_" does not have to be prefixed to the function name
		  f->extern_def ? &(func->
				    getvalue()->generate_code())[3] :
		  func->getvalue()->generate_code(),
		  actuals !=
		  NULL ? actuals->generate_code(func->getname()->getname(),
						f->params) : "");
}

// char *funccall::generate_code()
// {
//   return tsprintf("%s( %s )",
//      func->getvalue()->generate_code(),
//      actuals != NULL ? actuals->generate_code() : "");
// }

/********************
  code for isundefined
  ********************/
const char *isundefined::generate_code()
{
  return tsprintf("%s.isundefined()", left->generate_code());
}

/********************
  code for ismember
  ********************/
const char *ismember::generate_code()
{
  return tsprintf("(%s>=%d && %s<=%d)",
		  left->generate_code(), t->getleft(),
		  left->generate_code(), t->getright());
}

/********************
  code for multisetcount
  ********************/
void multisetcount::generate_decl(multisettypedecl * mset)
{
/*
  if (mset == set->gettype())
    {
      fprintf(codefile,"int multisetcount%d();\n",
	  multisetcount_num
	  );
    }
    */
}

void multisetcount::generate_procedure()
{
}

const char *multisetcount::generate_code()
{
  /* set->gettype()->getelementtype()->generate_code(), /* element type */
  /* set->gettype()->generate_code(), /* multiset type */
  /*  multisetcount_num,               /* procedure number */
  int num = new_int();
  char *temp = tsprintf("mu__intexpr%d", num);
  fprintf(codefile, "/*** begin multisetcount %d declaration ***/\n",
	  multisetcount_num);
  fprintf(codefile, "  int %s = 0;\n", temp);

  fprintf(codefile, "  {\n" "  %s_id %s;\n" "  for (%s = 0; ; %s=%s+1)\n" "    {\n" "      if (%s.valid[(int)%s].value())\n"	// Uli 10-98
	  "	{\n", set->gettype()->generate_code(),	/* multiset type */
	  index->getvalue()->generate_code(),	/* index name */
	  index->getvalue()->generate_code(),	/* index name */
	  index->getvalue()->generate_code(),	/* index name */
	  index->getvalue()->generate_code(),	/* index name */
	  set->generate_code(),	/* multiset variable name */
	  index->getvalue()->generate_code()	/* index name */
      );
  fprintf(codefile, "	  if ( %s ) %s++;\n" "	}\n" "      if (%s == %d-1) break;\n" "    }\n" "  }\n", filter->generate_code(),	/* bool expression */
	  temp, index->getvalue()->generate_code(),	/* index name */
	  ((multisettypedecl *) set->gettype())->getindexsize()	/* max size */
      );
  fprintf(codefile, "/*** end multisetcount %d declaration ***/\n",
	  multisetcount_num);
  return tsprintf("%s", temp);
}

/********************
  code related to stmt
  --
  -- stmt
  -- assignment
  -- whilestmt
  -- ifstmt
  -- caselist
  -- switchstmt
  -- forstmt
  -- proccall
  -- clearstmt
  -- errorstmt
  -- assertstmt
  -- putstmt
  -- alias
  -- aliasstmt
  -- returnstmt
 ********************/

/********************
  code for stmt
 ********************/
const char *stmt::generate_code()
{
  /* There now is the null statement--
   * it is legal to call stmt::generate_code();
   * it must be the null statement, so it just does nothing.
   */
  /*  Error.Error("Internal: stmt::generate_code() should never have been called."); */
  return "ERROR!";
}

/********************
  code for assignment
 ********************/
const char *assignment::generate_code()
{
  if (src->isdesignator()
      && src->gettype()->issimple()
      && src->checkundefined())
//       && src->gettype()->getclass() != decl::Quant
//       && src->gettype()->getclass() != decl::Const
//       && src->gettype()->getclass() != decl::Type
//       && src->gettype()->gettype()->issimple() )
  {
    fprintf(codefile,
	    "if (%s.isundefined())\n"
	    "  %s.undefine();\n"
	    "else\n"
	    "  %s = %s;\n",
	    src->generate_code(),
	    target->generate_code(),
	    target->generate_code(), src->generate_code());
  } else {
    fprintf(codefile, "%s = %s;\n",
	    target->generate_code(), src->generate_code());
  }
  return "ERROR!";
}

/********************
  code for whilestmt
 ********************/
const char *whilestmt::generate_code()
{
  char *counter = tsprintf("mu__counter_%d", new_int());
  char *while_expr = tsprintf("mu__while_expr_%d", new_int());

  // Uli: a "goto" to exit the while loop seemed to cause problems on some
  //      compilers when there were local variables

  // set mu__while_expr<n> to the value of the expr
  fprintf(codefile,
	  "{\n"
	  "  bool %s;"
	  "  %s = %s;\n", while_expr, while_expr, test->generate_code());

  fprintf(codefile,
	  "int %s = 0;\n"
	  "while (%s) {\n"
	  "if ( ++%s > args->loopmax.value )\n"
	  "  Error.Error(\"Too many iterations in while loop.\");\n",
	  counter, while_expr, counter);

  // nest a block so that the code within the loop
  // can generate variables if it needs to.
  fprintf(codefile, "{\n");

  for (stmt * s = body; s != NULL; s = s->next)
    s->generate_code();

  fprintf(codefile, "};\n");

  // set mu__while_expr<n> to the value of the expr
  // before the C++ while checks the variable.
  fprintf(codefile, "%s = %s;\n", while_expr, test->generate_code());

  fprintf(codefile, "}\n" "};\n");

  return "ERROR!";
}

/********************
  code for ifstmt
 ********************/
const char *ifstmt::generate_code()
{
  fprintf(codefile, "if ( %s )\n" "{\n", test->generate_code());

  for (stmt * s = body; s != NULL; s = s->next)
    s->generate_code();
  fprintf(codefile, "}\n");
  if (elsecode != NULL) {
    fprintf(codefile, "else\n" "{\n");
    for (stmt * s = elsecode; s != NULL; s = s->next)
      s->generate_code();

    fprintf(codefile, "}\n");
  }
  return "ERROR!";
}

/********************
  code for caselist
 ********************/
const char *caselist::generate_code()
{
  for (exprlist * v = values; v != NULL; v = v->next)
    fprintf(codefile, "case %s:\n", v->e->generate_code());

  for (stmt * b = body; b != NULL; b = b->next)
    b->generate_code();
  fprintf(codefile, "break;\n");
  return "ERROR!";
}

/********************
  code for switchstmt
 ********************/
const char *switchstmt::generate_code()
{
  fprintf(codefile, "switch ((int) %s) {\n", switchexpr->generate_code());
  /* The explicit cast seems to be necessary to allow things like
   * switch arr[i]... */
  for (caselist * c = cases; c != NULL; c = c->next)
    c->generate_code();
  if (elsecode != NULL) {
    fprintf(codefile, "default:\n");

    for (stmt * b = elsecode; b != NULL; b = b->next)
      b->generate_code();

    fprintf(codefile, "break;\n");
  }
  fprintf(codefile, "}\n");
  return "ERROR!";
}

/********************
  code for forstmt
 ********************/
const char *forstmt::generate_code()
{
  fprintf(codefile, "{\n");
  make_quant_fors(index);
  for (stmt * b = body; b != NULL; b = b->next)
    b->generate_code();
  make_quant_closes(index);
  fprintf(codefile, "};\n");
  return "ERROR!";
}

/********************
  code for proccall
 ********************/
const char *proccall::generate_code()
{
  procdecl *p = (procdecl *) procedure->getvalue();
  fprintf(codefile, "%s ( %s );\n",
	  //im: for imported procedures, "mu_" does not have to be prefixed to the function name
	  p->extern_def ? &(procedure->
			    getvalue()->generate_code())[3] : procedure->
	  getvalue()->generate_code(),
	  actuals !=
	  NULL ? actuals->generate_code(procedure->getname()->getname(),
					p->params) : "");
  return "ERROR!";
}

// char *proccall::generate_code()
// {
//   fprintf(codefile,"%s ( %s );\n",
//    procedure->getvalue()->generate_code(),
//    actuals != NULL ? actuals->generate_code() : "" );
//   return "ERROR!";
// }

/********************
  code for clearstmt
 ********************/
const char *clearstmt::generate_code()
{
  // Gotta figure this one out--
  // current best idea: give every object a clear method.
  fprintf(codefile, "%s.clear();\n", target->generate_code());
  return "ERROR!";
}

/********************
  code for undefinestmt
  ********************/
const char *undefinestmt::generate_code()
{
  fprintf(codefile, "%s.undefine();\n", target->generate_code());
  return "ERROR!";
}

/********************
  code for multisetaddstmt
  ********************/
const char *multisetaddstmt::generate_code()
{
  fprintf(codefile, "%s.multisetadd(%s);\n",
	  target->generate_code(), element->generate_code());
  return "ERROR!";
}

/********************
  code for multisetremovestmt
  ********************/
void multisetremovestmt::generate_decl(multisettypedecl * mset)
{
/*
  if (mset == target->gettype())
    {
      fprintf(codefile,"void multisetremove%d();\n",
	  multisetremove_num
	  );
    }
    */
}

void multisetremovestmt::generate_procedure()
{
}

const char *multisetremovestmt::generate_code()
{
  if (matchingchoose) {
    fprintf(codefile, "%s.multisetremove(%s);\n",
	    target->generate_code(), criterion->generate_code());
  } else {
    int num = new_int();
    char *temp = tsprintf("mu__idexpr%d", num);
    fprintf(codefile, "/*** end multisetremove %d declaration ***/\n",
	    multisetremove_num);
    fprintf(codefile, "  %s_id %s;\n", target->gettype()->generate_code(),	/* multiset type */
	    temp);

    fprintf(codefile, "  %s_id %s;\n" "  for (%s = 0; ; %s=%s+1)\n" "    {\n" "      if (%s.valid[(int)%s].value())\n"	// Uli 01-99
	    "	{\n", target->gettype()->generate_code(),	/* multiset type */
	    index->getvalue()->generate_code(),	/* index name */
	    index->getvalue()->generate_code(),	/* index name */
	    index->getvalue()->generate_code(),	/* index name */
	    index->getvalue()->generate_code(),	/* index name */
	    target->generate_code(),	/* multiset variable name */
	    index->getvalue()->generate_code()	/* index name */
	);
    fprintf(codefile, "	  if ( %s ) { %s = %s; %s.multisetremove(%s); };\n" "	}\n" "      if (%s == %d-1) break;\n" "    }\n", criterion->generate_code(),	/* bool expression */
	    temp, index->getvalue()->generate_code(),	/* index name */
	    target->generate_code(),	/* multiset variable name */
	    temp, index->getvalue()->generate_code(),	/* index name */
	    ((multisettypedecl *) target->gettype())->getindexsize()	/* max size */
	);
    fprintf(codefile, "/*** end multisetremove %d declaration ***/\n",
	    multisetremove_num);
  }

  return "ERROR!";
}

/********************
  code for errorstmt
 ********************/
const char *errorstmt::generate_code()
{
  fprintf(codefile, "Error.Error(\"Error: %s\");\n", string);
  return "ERROR!";
}

/********************
  code for assertstmt
 ********************/
const char *assertstmt::generate_code()
{
  fprintf(codefile,
	  "if ( !(%s) ) Error.Error(\"Assertion failed: %s\");\n",
	  test->generate_code(), string);
  return "ERROR!";
}

/********************
  code for putstmt
 ********************/
const char *putstmt::generate_code()
{
  if (putexpr != NULL) {
    if (putexpr->islvalue())
      fprintf(codefile, "%s.print();\n", putexpr->generate_code());
    else
      fprintf(codefile, "cout << ( %s );\n", putexpr->generate_code());
  } else {
    fprintf(codefile, "cout << \"%s\";\n", putstring);
  }
  return "ERROR!";
}

/********************
  code for alias
 ********************/
const char *alias::generate_code()
     /* not used right now. */
{
  return "ERROR!";
}

/********************
  code for aliasstmt
 ********************/
const char *aliasstmt::generate_code()
{
  fprintf(codefile, "{\n");
  aliases->generate_decls();
  for (stmt * b = body; b != NULL; b = b->next)
    b->generate_code();
  fprintf(codefile, "}\n");
  return "ERROR!";
}

/********************
  code for returnstmt
 ********************/
const char *returnstmt::generate_code()
{
  // Uli: the return expression is not converted to int. Therefore, the
  // copy constructor is used to create a temporary object for the return
  // expression. Advantage: complex types can be returned.
  // (no change in this routine)
  fprintf(codefile, "return %s;\n",
	  retexpr != NULL ? retexpr->generate_code() : "");

//  if (retexpr) fprintf(codefile,"return %s;\n", retexpr->generate_code());
//  else fprintf(codefile, "return;\n");
  return "ERROR!";
}

/********************
  code related to rules
 ********************/
static char rule_param_buffer[BUFFER_SIZE];
static ste *stequants[MAXSCOPES];	/* We can\'t have more enclosing rulesets than scopes. */
static int numquants = 0;
static char namequants[BUFFER_SIZE];
static char quantactuals[BUFFER_SIZE];

/********************
  aux_generate_rule_params
  -- extract "Quant" from enclosure and generate the string for it
  -- i.e. the string to be placed in condition/rule function 
  -- formal
 ********************/
// no longer used
static char *aux_generate_rule_params(ste * enclosures)
/* returns a pointer to the '\0' at the end of the string in
 * rule_param_buffer. */
{
  char *temp;
  if (enclosures != NULL &&
      (enclosures->getvalue()->getclass() == decl::Quant ||
       enclosures->getvalue()->getclass() == decl::Alias)) {
    temp = aux_generate_rule_params(enclosures->getnext());
    if (enclosures->getvalue()->getclass() == decl::Quant)
      sprintf(temp,
	      ", const %s &%s",
	      enclosures->getvalue()->gettype()->generate_code(),
	      enclosures->getvalue()->generate_code());
    return (temp + strlen(temp));
  } else
    return rule_param_buffer;
}

/********************
  generate_rule_params
  -- initialize buffer "rule_param_buffer
  -- and call aux_generate_rule_params
  -- to return the appropriate string
  -- i.e. the string to be placed in condition/rule function 
  -- formal
 ********************/

static char *generate_rule_params(ste * enclosures)
/* assumes that enclosures is a pointer to a list of ste\'s,
 * with ruleset parameters and aliases at the front. */
{
  int i = 0;
  for (i = 0; rule_param_buffer[i] != '\0' && i < BUFFER_SIZE; i++)
    rule_param_buffer[i] = '\0';
  aux_generate_rule_params(enclosures);
  return (rule_param_buffer + 1);	/* skip the leading comma. */
}

/********************
  generate_rule_params_assignment
 ********************/
// void generate_rule_params_assignment_union(ste *enclosures)
// {
//         stelist * t;
//         typedecl * d;  
//         int thisright = enclosures->getvalue()->gettype()->getsize()-1;
//         int thisleft;
// 
//         for(t=((uniontypedecl *)indextype)->getunionmembers();
//             t!= NULL; t=t->next)
//           {
//             d = (typedecl *)t->s->getvalue();
//             thisleft = thisright - d->getsize() + 1;
// 
//   fprintf(codefile,
//    "    if (int_
//    "    %s_id %s = (r %% %d) + %d;\n"
//    ((multisetidtypedecl *)enclosures->getvalue()->gettype())
//    ->getparenttype()->generate_code(),
//    enclosures->getvalue()->gettype()->getleft(),
//    );
// 
// 
// 
// //       for (i=thisleft; i<=thisright; i++)
//      for (i=d->getleft(); i<=d->getright(); i++)
//      for (e = elt; e!=NULL; e=e->next)
//        ret = new charlist(tsprintf("[%d]%s",i, e->string), e->e, ret);
//             thisright= thisleft - 1;
//           }
//   
// }

void generate_rule_params_assignment(ste * enclosures)
/* assumes that enclosures is a pointer to a list of ste\'s,
 * with ruleset parameters and aliases at the front. */
{
  if (enclosures != NULL &&
      (enclosures->getvalue()->getclass() == decl::Quant ||
       enclosures->getvalue()->getclass() == decl::Alias ||
       enclosures->getvalue()->getclass() == decl::Choose)) {
    generate_rule_params_assignment(enclosures->getnext());
    if (enclosures->getvalue()->gettype()->gettypeclass() ==
	typedecl::Union) {
//    if ( enclosures->getvalue()->getclass() == decl::Choose )
//      {
//      fprintf(codefile,
//          "    int int_%s =  (r %% %d);\n"
//          enclosures->getvalue()->generate_code(),
//          enclosures->getvalue()->gettype()->getsize()
//          );
//      generate_rule_params_assignment_union(enclosures);
//      fprintf(codefile,
//        "    r = r / %d;\n",
//        enclosures->getvalue()->gettype()->getsize()
//        );
//      }
      if (enclosures->getvalue()->getclass() == decl::Choose)
	fprintf(codefile,
		"    static %s_id %s;\n"
		"    %s.unionassign( r %% %d );\n"
		"    r = r / %d;\n",
		((multisetidtypedecl *) enclosures->getvalue()->gettype())
		->getparenttype()->generate_code(),
		enclosures->getvalue()->generate_code(),
		enclosures->getvalue()->generate_code(),
		enclosures->getvalue()->gettype()->getsize(),
		enclosures->getvalue()->gettype()->getsize()
	    );
      if (enclosures->getvalue()->getclass() == decl::Quant)
	fprintf(codefile,
		"    static %s %s;\n"
		"    %s.unionassign(r %% %d);\n"
		"    r = r / %d;\n",
		enclosures->getvalue()->gettype()->generate_code(),
		enclosures->getvalue()->generate_code(),
		enclosures->getvalue()->generate_code(),
		enclosures->getvalue()->gettype()->getsize(),
		enclosures->getvalue()->gettype()->getsize()
	    );
    } else {
      if (enclosures->getvalue()->getclass() == decl::Choose)
	fprintf(codefile,
		"    static %s_id %s;\n"
		"    %s.value((r %% %d) + %d);\n"
		"    r = r / %d;\n",
		((multisetidtypedecl *) enclosures->getvalue()->gettype())
		->getparenttype()->generate_code(),
		enclosures->getvalue()->generate_code(),
		enclosures->getvalue()->generate_code(),
		enclosures->getvalue()->gettype()->getsize(),
		enclosures->getvalue()->gettype()->getleft(),
		enclosures->getvalue()->gettype()->getsize()
	    );
      if (enclosures->getvalue()->getclass() == decl::Quant)
	fprintf(codefile,
		"    static %s %s;\n"
		"    %s.value((r %% %d) + %d);\n"
		"    r = r / %d;\n",
		enclosures->getvalue()->gettype()->generate_code(),
		enclosures->getvalue()->generate_code(),
		enclosures->getvalue()->generate_code(),
		enclosures->getvalue()->gettype()->getsize(),
		enclosures->getvalue()->gettype()->getleft(),
		enclosures->getvalue()->gettype()->getsize()
	    );
    }
  }
}

void generate_rule_params_simple_assignment(ste * enclosures)
/* assumes that enclosures is a pointer to a list of ste\'s,
 * with ruleset parameters and aliases at the front. */
{
  if (enclosures != NULL &&
      (enclosures->getvalue()->getclass() == decl::Quant ||
       enclosures->getvalue()->getclass() == decl::Alias ||
       enclosures->getvalue()->getclass() == decl::Choose)) {
    generate_rule_params_simple_assignment(enclosures->getnext());
    if (enclosures->getvalue()->gettype()->gettypeclass() ==
	typedecl::Union) {
      if (enclosures->getvalue()->getclass() == decl::Choose)
	fprintf(codefile,
		"    %s.unionassign( r %% %d );\n"
		"    r = r / %d;\n",
		enclosures->getvalue()->generate_code(),
		enclosures->getvalue()->gettype()->getsize(),
		enclosures->getvalue()->gettype()->getsize()
	    );
      if (enclosures->getvalue()->getclass() == decl::Quant)
	fprintf(codefile,
		"    %s.unionassign(r %% %d);\n"
		"    r = r / %d;\n",
		enclosures->getvalue()->generate_code(),
		enclosures->getvalue()->gettype()->getsize(),
		enclosures->getvalue()->gettype()->getsize()
	    );
    } else {
      if (enclosures->getvalue()->getclass() == decl::Choose)
	fprintf(codefile,
		"    %s.value((r %% %d) + %d);\n"
		"    r = r / %d;\n",
		enclosures->getvalue()->generate_code(),
		enclosures->getvalue()->gettype()->getsize(),
		enclosures->getvalue()->gettype()->getleft(),
		enclosures->getvalue()->gettype()->getsize()
	    );
      if (enclosures->getvalue()->getclass() == decl::Quant)
	fprintf(codefile,
		"    %s.value((r %% %d) + %d);\n"
		"    r = r / %d;\n",
		enclosures->getvalue()->generate_code(),
		enclosures->getvalue()->gettype()->getsize(),
		enclosures->getvalue()->gettype()->getleft(),
		enclosures->getvalue()->gettype()->getsize()
	    );
    }
  }
}

void generate_rule_params_choose(ste * enclosures)
/* assumes that enclosures is a pointer to a list of ste\'s,
 * with ruleset parameters and aliases at the front. */
{
  if (enclosures != NULL &&
      (enclosures->getvalue()->getclass() == decl::Quant ||
       enclosures->getvalue()->getclass() == decl::Alias ||
       enclosures->getvalue()->getclass() == decl::Choose)) {
    generate_rule_params_choose(enclosures->getnext());
    if (enclosures->getvalue()->getclass() == decl::Choose)
      fprintf(codefile, "  if (!%s.in(%s)) { return FALSE; }\n",
	      ((multisetidtypedecl *) enclosures->getvalue()->gettype())
	      ->getparentname(), enclosures->getvalue()->mu_name);
  }
}

void generate_rule_params_choose_exist(ste * enclosures)
/* assumes that enclosures is a pointer to a list of ste\'s,
 * with ruleset parameters and aliases at the front. */
{
  if (enclosures != NULL &&
      (enclosures->getvalue()->getclass() == decl::Quant ||
       enclosures->getvalue()->getclass() == decl::Alias ||
       enclosures->getvalue()->getclass() == decl::Choose)) {
    generate_rule_params_choose_exist(enclosures->getnext());
    if (enclosures->getvalue()->getclass() == decl::Choose)
      fprintf(codefile, "&& %s.value()<%d ",
	      enclosures->getvalue()->mu_name,
	      enclosures->getvalue()->gettype()->getsize()
	  );
  }
}


void generate_rule_params_choose_next(ste * enclosures, unsigned end)
// Uli: unsigned short -> unsigned
/* assumes that enclosures is a pointer to a list of ste\'s,
 * with ruleset parameters and aliases at the front. */
{
  if (enclosures != NULL &&
      (enclosures->getvalue()->getclass() == decl::Quant ||
       enclosures->getvalue()->getclass() == decl::Alias ||
       enclosures->getvalue()->getclass() == decl::Choose)) {
    generate_rule_params_choose(enclosures->getnext());
    if (enclosures->getvalue()->getclass() == decl::Choose)
      fprintf(codefile, "	    if (!%s.in(%s)) { return %d; }\n",
	      ((multisetidtypedecl *) enclosures->getvalue()->gettype())
	      ->getparentname(), enclosures->getvalue()->mu_name, end);
  }
}

void generate_rule_params_choose_all_in(ste * enclosures)
/* assumes that enclosures is a pointer to a list of ste\'s,
 * with ruleset parameters and aliases at the front. */
{
  if (enclosures != NULL &&
      (enclosures->getvalue()->getclass() == decl::Quant ||
       enclosures->getvalue()->getclass() == decl::Alias ||
       enclosures->getvalue()->getclass() == decl::Choose)) {
    generate_rule_params_choose_all_in(enclosures->getnext());
    if (enclosures->getvalue()->getclass() == decl::Choose)
      fprintf(codefile, "&& %s.in(%s)",
	      ((multisetidtypedecl *) enclosures->getvalue()->gettype())
	      ->getparentname(), enclosures->getvalue()->mu_name);
  }
}

void generate_rule_params_printf(ste * enclosures)
/* assumes that enclosures is a pointer to a list of ste\'s,
 * with ruleset parameters and aliases at the front. */
{
  if (enclosures != NULL &&
      (enclosures->getvalue()->getclass() == decl::Quant ||
       enclosures->getvalue()->getclass() == decl::Alias ||
       enclosures->getvalue()->getclass() == decl::Choose)) {
    generate_rule_params_printf(enclosures->getnext());
    if (enclosures->getvalue()->getclass() == decl::Quant ||
	enclosures->getvalue()->getclass() == decl::Choose)
      fprintf(codefile, ", %s:%%s", enclosures->getvalue()->name);
  }
}



void generate_rule_params_name(ste * enclosures)
/* assumes that enclosures is a pointer to a list of ste\'s,
 * with ruleset parameters and aliases at the front. */
{
  if (enclosures != NULL &&
      (enclosures->getvalue()->getclass() == decl::Quant ||
       enclosures->getvalue()->getclass() == decl::Alias ||
       enclosures->getvalue()->getclass() == decl::Choose)) {
    generate_rule_params_name(enclosures->getnext());
    if (enclosures->getvalue()->getclass() == decl::Quant ||
	enclosures->getvalue()->getclass() == decl::Choose)
      fprintf(codefile,
	      ", %s.Name()", enclosures->getvalue()->generate_code()
	  );
  }
}

/********************
  generate_rule_aliases
  -- extract "Alias" from enclosure and generate the code for it
 ********************/
static const char *generate_rule_aliases(ste * enclosures)
/* generate alias declarations for the rule. */
{
  if (enclosures != NULL &&
      (enclosures->getvalue()->getclass() == decl::Quant ||
       enclosures->getvalue()->getclass() == decl::Alias ||
       enclosures->getvalue()->getclass() == decl::Choose)) {
    generate_rule_aliases(enclosures->getnext());
    if (enclosures->getvalue()->getclass() == decl::Alias)
      enclosures->getvalue()->generate_decl();
    return "ERROR!";
  } else
    return "ERROR!";
}

/********************
  enroll_quants
  -- enter each "Quant" enclosure, i.e. ruleset, into
  -- the list "stequants" for easy recursion to find every
  -- instance of a ruleset
 ********************/
static void enroll_quants(ste * enclosures)
{
  if (enclosures != NULL &&
      (enclosures->getvalue()->getclass() == decl::Quant ||
       enclosures->getvalue()->getclass() == decl::Alias ||
       enclosures->getvalue()->getclass() == decl::Choose)) {
    enroll_quants(enclosures->getnext());
    if (enclosures->getvalue()->getclass() == decl::Quant ||
	enclosures->getvalue()->getclass() == decl::Choose) {
      if (numquants >= MAXSCOPES) {
	Error.FatalError
	    ("Current implementation only allows %d nested rulesets.",
	     MAXSCOPES);
      }
      stequants[numquants] = enclosures;
      numquants++;
    }
  } else {
    numquants = 0;
  }
}

/********************
  static void generate_rules_aux(...)
  -- called by generate_rules
  --
  -- generate every instance of a ruleset, by recursively
  -- going down the list of enclosure
  -- 
  -- done recursively because the cost of this program isn\'t that huge,
  -- and recursion is much easier for me to understand. 
 ********************/
static void
generate_rules_aux(int quantindex,
		   char *namequants_end,
		   char *quantactuals_end, simplerule * therule)
{
  rulerec *rr;
  int rule_int = new_int();
  char *condname;
  char *rulename;
  if (quantindex >= numquants) {
    /* generate the code for the rule. */
    /* and enroll it into appropriate list */
    if (therule->condition != NULL) {
      condname = tsprintf("mu__condition_%d", rule_int);
      fprintf(codefile, "bool %s() // Condition for Rule \"%s%s\"\n" "{\n" "  return %s(%s );\n" "}\n\n", condname, therule->name, namequants, therule->condname, quantactuals + 1);	/* + 1 to skip the leading comma. */
    } else
      condname = NULL;
    if (therule->body != NULL) {
      rulename = tsprintf("mu__rule_%d", rule_int);
      fprintf(codefile, "void %s() // Action for Rule \"%s%s\"\n" "{\n" "  %s(%s );\n" "};\n\n", rulename, therule->name, namequants, therule->rulename, quantactuals + 1);	/* + 1 to skip the leading comma. */
    } else
      rulename = NULL;

    /* install it into the appropriate list. */
    rr = new rulerec(tsprintf("%s%s", therule->name, namequants),
		     condname, rulename);
    switch (therule->getclass()) {
    case rule::Simple:
      rr->next = theprog->rulelist;
      theprog->rulelist = rr;
      break;
    case rule::Startstate:	/* This function seems not to be called on start states! */
      rr->next = theprog->startstatelist;
      theprog->startstatelist = rr;
      break;
    case rule::Invar:
      rr->next = theprog->invariantlist;
      theprog->invariantlist = rr;
      break;
    default:
      Error.Error
	  ("Internal: Exciting value for therule->getclass() in generate_rules_aux.");
      break;
    }
  } else {
    /* do some more recursion. */
    int i;
    char *names_end, *actuals_end;
    quantdecl *quant = (quantdecl *) stequants[quantindex]->getvalue();
    if (quant->left != NULL) {
      for (i = quant->left->getvalue(); i <= quant->right->getvalue();
	   i += quant->by) {
	sprintf(namequants_end, ", %s:%d", quant->name, i);
	names_end = namequants_end + strlen(namequants_end);
	sprintf(quantactuals_end, ", %d", i);
	actuals_end = quantactuals_end + strlen(quantactuals_end);
	generate_rules_aux(quantindex + 1, names_end, actuals_end,
			   therule);
      }
    } else {
// rlm wrote :
//     for( ste *s = ((enumtypedecl *) quant->gettype())->getidvalues();
//      s != NULL;
//      s = s->getnext() )
// spark : ( s!= NULL ) is not reached properly 
//   : ex. OMH.m with ruleset over enum type

      ste *s;
      stelist *t;
      typedecl *d;

      // put value or enum string to the rule name and parameter, according to type 

      // Enum
      if (quant->gettype()->gettypeclass() == typedecl::Enum
	  && quant->gettype() != booltype) {
	s = ((enumtypedecl *) quant->gettype())->getidvalues();
	for (i = quant->gettype()->getleft();
	     i <= quant->gettype()->getright(); i++) {
	  sprintf(namequants_end, ", %s:%s", quant->name,
		  s->getname()->getname());
	  sprintf(quantactuals_end, ", %s",
		  s->getvalue()->generate_code());
	  s = s->getnext();
	  names_end = namequants_end + strlen(namequants_end);
	  actuals_end = quantactuals_end + strlen(quantactuals_end);
	  generate_rules_aux(quantindex + 1, names_end, actuals_end,
			     therule);
	}
      } else if (quant->gettype() == booltype) {
	for (i = 0; i <= 1; i++) {
	  if (i == 0) {
	    sprintf(namequants_end, ", %s:false", quant->name);
	    sprintf(quantactuals_end, ", mu_false");
	  } else {
	    sprintf(namequants_end, ", %s:true", quant->name);
	    sprintf(quantactuals_end, ", mu_true");
	  }
	  names_end = namequants_end + strlen(namequants_end);
	  actuals_end = quantactuals_end + strlen(quantactuals_end);
	  generate_rules_aux(quantindex + 1, names_end, actuals_end,
			     therule);
	}
      }
      // Scalarset
      else if (quant->gettype()->gettypeclass() == typedecl::Scalarset) {
	s = ((scalarsettypedecl *) quant->gettype())->getidvalues();
	for (i = quant->gettype()->getleft();
	     i <= quant->gettype()->getright(); i++) {
	  sprintf(namequants_end, ", %s:%s", quant->name,
		  s->getname()->getname());
	  sprintf(quantactuals_end, ", %s",
		  s->getvalue()->generate_code());
	  s = s->getnext();
	  names_end = namequants_end + strlen(namequants_end);
	  actuals_end = quantactuals_end + strlen(quantactuals_end);
	  generate_rules_aux(quantindex + 1, names_end, actuals_end,
			     therule);
	}
      }
      // Union
      else if (quant->gettype()->gettypeclass() == typedecl::Union) {
	t = ((uniontypedecl *) quant->gettype())->getunionmembers();
	for (; t != NULL; t = t->next) {
	  d = (typedecl *) t->s->getvalue();
	  if (d->gettypeclass() == typedecl::Scalarset)
	    s = ((scalarsettypedecl *) d)->getidvalues();
	  else if (d->gettypeclass() == typedecl::Enum)
	    s = ((enumtypedecl *) d)->getidvalues();
	  else
	    Error.Error("Funny element in union");

	  for (i = d->getleft(); i <= d->getright(); i++) {
	    sprintf(namequants_end, ", %s:%s", quant->name,
		    s->getname()->getname());
	    sprintf(quantactuals_end, ", %s",
		    s->getvalue()->generate_code());
	    s = s->getnext();
	    names_end = namequants_end + strlen(namequants_end);
	    actuals_end = quantactuals_end + strlen(quantactuals_end);
	    generate_rules_aux(quantindex + 1, names_end, actuals_end,
			       therule);
	  }
	}
      }
      // subrange
      else {
	for (i = quant->gettype()->getleft();
	     i <= quant->gettype()->getright(); i++) {
	  sprintf(namequants_end, ", %s:%d", quant->name, i);
	  sprintf(quantactuals_end, ", %d", i);
	  names_end = namequants_end + strlen(namequants_end);
	  actuals_end = quantactuals_end + strlen(quantactuals_end);
	  generate_rules_aux(quantindex + 1, names_end, actuals_end,
			     therule);
	}
      }

    }
  }
}



/********************
  generate_rules
  -- creates the stub procedures for a rule/startstate/invariant/fairness
  -- and enrolls them in the list of rules.
  --
  -- i.e. create instances of rule/startstate/invariant
  -- by calling the main condition function and rule function
  -- corresponding to the rules
 ********************/
static void generate_rules(ste * enclosures, simplerule * therule)
{
  int i = 0;

  // set up quants[] array of quantdecl
  enroll_quants(enclosures);

  // initialize namequants[] and quantactuals[] to all \'\0\'
  for (i = 0; namequants[i] != '\0' && i < BUFFER_SIZE; i++)
    namequants[i] = '\0';
  for (i = 0; quantactuals[i] != '\0' && i < BUFFER_SIZE; i++)
    quantactuals[i] = '\0';

  // generate rules by calling to main rule with quantifier value
  generate_rules_aux(0, namequants, quantactuals, therule);

  fprintf(codefile, "/**** end rule declaration ****/\n\n");
}

/********************
  code for simplerule
  -- rules produce some code,
  -- but also update the rules/startst/invariant list.
 ********************/
const char *rule::generate_code()
{
  return "ERROR!";
}

/********************
  code for simplerule
 ********************/
const char *simplerule::generate_code()
{
  fprintf(codefile,
	  "/******************** RuleBase%d ********************/\n"
	  "class RuleBase%d\n" "{\n" "public:\n", rulenumber, rulenumber);

  // priority function, added by Uli
  fprintf(codefile,
	  "  int Priority()\n" "  {\n" "    return %d;\n" "  }\n",
	  priority);

  // generate Name(r)
  fprintf(codefile, "  char * Name(unsigned r)\n" "  {\n");
  generate_rule_params_assignment(enclosures);
  fprintf(codefile, "    return tsprintf(\"%s", name);
  generate_rule_params_printf(enclosures);
  fprintf(codefile, "\"");
  generate_rule_params_name(enclosures);
  fprintf(codefile, ");\n" "  }\n");

  // generate Condition(r)
  fprintf(codefile, "  bool Condition(unsigned r)\n" "  {\n");
  generate_rule_params_assignment(enclosures);
  generate_rule_params_choose(enclosures);
  generate_rule_aliases(enclosures);

  if (args->pmurphik)		// AP: condition return for probabilistic rules is "return prob > 0"
  {
    if (condition->hasvalue())
      fprintf(codefile, "    return %d;\n", condition->getrvalue() > 0);
    else
      fprintf(codefile,
	      "    return (%s > 0);\n", condition->generate_code());
  } else
    fprintf(codefile, "    return %s;\n", condition->generate_code());
  fprintf(codefile, "  }\n" "\n");

  // generate NextRule(r)
  if (args->pmurphik && !args->prob_rules)
    // IM: it is necessary to have an additional output parameter for the probability of the rule
    fprintf(codefile,
	    "  void NextRule(unsigned & what_rule, double & what_prob)\n"
	    "  {\n"
	    "    unsigned r = what_rule - %d;\n", maxrulenumber - getsize()
	);
  else
    fprintf(codefile,
	    "  void NextRule(unsigned & what_rule)\n"
	    "  {\n"
	    "    unsigned r = what_rule - %d;\n", maxrulenumber - getsize()
	);
  generate_rule_params_assignment(enclosures);
  fprintf(codefile, "    while (what_rule < %d ", maxrulenumber);
  generate_rule_params_choose_exist(enclosures);
  fprintf(codefile, ")\n      {\n");

  // Vitaly's hacks

  // Check if ``dependent'' choose parameters are there
  fprintf(codefile, "	if ( ( TRUE ");
  generate_rule_params_choose_all_in(dep_choose);
  fprintf(codefile, " ) ) {\n");

  // Check condition
  generate_rule_aliases(enclosures);
  if (args->pmurphik) {
    if (condition->hasvalue()) {
      fprintf(codefile,
	      "	      what_prob = %s;\n"
	      "	      if (%d) {\n",
	      condition->generate_code(), condition->getrvalue() > 0);
    } else {
      fprintf(codefile,
	      "    what_prob = %s;\n"
	      "    if ((what_prob < 0) || (what_prob > 1))\n"
	      "    { \n"
	      "      Error.Error(\"Condition of probabilistic rule %%s is not in range [0,1].\", this->Name(what_rule));\n"
	      "      return;\n" "    }\n", condition->generate_code());

      fprintf(codefile, "	      if (what_prob > 0) {\n");
    }
  } else
    fprintf(codefile, "	      if (%s) {\n", condition->generate_code());

  // Check is ``independent'' choose parameters are there
  fprintf(codefile, "		if ( ( TRUE ");
  generate_rule_params_choose_all_in(indep_choose);
  fprintf(codefile, " ) )\n");
  fprintf(codefile, "		  return;\n");
  fprintf(codefile, "		else\n");
  fprintf(codefile, "		  what_rule++;\n");
  fprintf(codefile, "	      }\n");

  fprintf(codefile, "	      else\n");
  fprintf(codefile, "		what_rule += %d;\n", indep_card);
  fprintf(codefile, "	}\n");

  fprintf(codefile, "	else\n");
  fprintf(codefile, "	  what_rule += %d;\n", indep_card);

  // End of Vitaly's hacks


  fprintf(codefile, "    r = what_rule - %d;\n",
	  maxrulenumber - getsize());

  generate_rule_params_simple_assignment(enclosures);
  fprintf(codefile, "    }\n" "  }\n\n");

  // generate Code(r)
  fprintf(codefile, "  void Code(unsigned r)\n" "  {\n");
  generate_rule_params_assignment(enclosures);
  generate_rule_aliases(enclosures);
  locals->generate_decls();
  for (stmt * b = body; b != NULL; b = b->next)
    b->generate_code();
  fprintf(codefile, "  };\n" "\n");

  // end declaration
  fprintf(codefile, "};\n");

  return "ERROR!";
}

/********************
  code for startstate
 ********************/
const char *startstate::generate_code()
{
  fprintf(codefile,
	  "/******************** StartStateBase%d ********************/\n"
	  "class StartStateBase%d\n"
	  "{\n" "public:\n", rulenumber, rulenumber);

  // generate Name(r)
  fprintf(codefile, "  char * Name(unsigned short r)\n" "  {\n");
  generate_rule_params_assignment(enclosures);
  fprintf(codefile, "    return tsprintf(\"%s", name);
  generate_rule_params_printf(enclosures);
  fprintf(codefile, "\"");
  generate_rule_params_name(enclosures);
  fprintf(codefile, ");\n" "  }\n");

  // generate Code(r)
  fprintf(codefile, "  void Code(unsigned short r)\n" "  {\n");
  generate_rule_params_assignment(enclosures);
  generate_rule_aliases(enclosures);
  locals->generate_decls();
  for (stmt * b = body; b != NULL; b = b->next)
    b->generate_code();
  fprintf(codefile, "  };\n" "\n");

  // end declaration
  fprintf(codefile, "};\n");

  return "ERROR!";
}

/********************
  code for invariant
 ********************/
const char *invariant::generate_code()
{
  int rule_int = new_int();
  condname = tsprintf("mu__invariant_%d", rule_int);

  /* generate the parameters to the function for the invariant. */
  /* e.g.  "int pid, int mid" as in "mu__invariant_1(int pid, int mid)" */
  char *params = generate_rule_params(enclosures);

  /* generate the condition function. */
  /* which is called by the different instances of the invariant */
  fprintf(codefile, "int %s(%s) // Invariant \"%s\"\n",
	  condname, params, name);
  fprintf(codefile, "{\n");
  generate_rule_aliases(enclosures);
  fprintf(codefile, "return %s;\n", condition->generate_code());
  fprintf(codefile, "};\n\n");

  /* there is no rule function as it is a invariant */
  /* may be added later */

  /* generate different instances of the rule according the
     ruleset parameter */
  /* currently syntax enforce a single instance only */
  generate_rules(enclosures, this);
  return "ERROR!";
}

/********************
  code for pctl
 ********************/

void pctl::generate_atomic_subformulas(pctl * formula)
{
  if (formula == NULL)
    return;
  if (formula->pctltype == AP_PCTL) {
    fprintf(codefile, "bool mu_pctl_a_p%d()\n{\n", formula->code);
    fprintf(codefile, "return %s;\n}\n",
	    formula->atomic_proposition->generate_code());
  } else {
    generate_atomic_subformulas(formula->subformula1);
    generate_atomic_subformulas(formula->subformula2);
  }
}

const char *pctl::getstring(pctl_type t)
{
  switch (t) {
  case UNTIL_PCTL:
    return "UNTIL_PCTL";
  case NEXT_PCTL:
    return "NEXT_PCTL";
  case AP_PCTL:
    return "AP_PCTL";
  case AND_PCTL:
    return "AND_PCTL";
  case OR_PCTL:
    return "OR_PCTL";
  case IMPL_PCTL:
    return "IMPL_PCTL";
  case NOT_PCTL:
    return "NOT_PCTL";
  }
}

const char *pctl::getstring(pctl_ord o)
{
  switch (o) {
  case PCTL_L:
    return "PCTL_L";
  case PCTL_LEQ:
    return "PCTL_LEQ";
  case PCTL_G:
    return "PCTL_G";
  case PCTL_GEQ:
    return "PCTL_GEQ";
  }
}

void pctl::generate_non_atomic_subformulas(pctl * formula)
{
  if (formula == NULL)
    return;
  generate_non_atomic_subformulas(formula->subformula1);
  generate_non_atomic_subformulas(formula->subformula2);
  if (formula == this)
    fprintf(codefile, "const pctlformrec mu_pctl_formula = {\n");
  else
    fprintf(codefile, "const pctlformrec mu_pctl_formula%d = {\n",
	    formula->code);
  fprintf(codefile, "%s, ", getstring(formula->pctltype));
  if (formula->pctltype != AP_PCTL)
    fprintf(codefile, "NULL, ");
  else
    fprintf(codefile, "&mu_pctl_a_p%d, ", formula->code);
  if (formula->pctltype != NEXT_PCTL && formula->pctltype != UNTIL_PCTL)
    fprintf(codefile, "PCTL_L, 0.0, ");
  else
    fprintf(codefile, "%s, %lf, ", getstring(formula->op),
	    formula->prob_bound);
  fprintf(codefile, "%d, ", formula->until_bound);
  if (formula->subformula1 == NULL)
    fprintf(codefile, "NULL, ");
  else
    fprintf(codefile, "&mu_pctl_formula%d, ", formula->subformula1->code);
  if (formula->subformula2 == NULL)
    fprintf(codefile, "NULL");
  else
    fprintf(codefile, "&mu_pctl_formula%d", formula->subformula2->code);
  fprintf(codefile, "};\n");
}

/* considers top untils only; called only if the top formula is not an until */
unsigned pctl::num_top_untils(pctl * f, int ret)
{
  if (f->pctltype == UNTIL_PCTL)
    return ++ret;
  if (f->subformula1 != NULL)
    ret = num_top_untils(f->subformula1, ret);
  if (f->subformula2 != NULL)
    ret = num_top_untils(f->subformula2, ret);
  return ret;
}

/* considers top untils only; called only if the top formula is not an until */
int pctl::ret_top_untils(pctl * formula, unsigned *ret, int i)
{
  if (formula == NULL)
    return i;
  if (formula->pctltype == UNTIL_PCTL) {
    ret[i++] = formula->code;
    return i;
  }
  i = ret_top_untils(formula->subformula1, ret, i);
  i = ret_top_untils(formula->subformula2, ret, i);
  return i;
}

const char *pctl::generate_code()
{
  generate_atomic_subformulas(this);
  generate_non_atomic_subformulas(this);

  return "ERROR!";
}

/********************
  code for quantrule
 ********************/
const char *quantrule::generate_code()
{
  // generate each rule within the quantifier
  for (rule * r = rules; r != NULL; r = r->next)
    r->generate_code();
  return "ERROR!";
}

/********************
  code for chooserule
 ********************/
const char *chooserule::generate_code()
{
  // generate each rule within the quantifier
  for (rule * r = rules; r != NULL; r = r->next)
    r->generate_code();
  return "ERROR!";
}

/********************
  code for aliasrule
 ********************/
const char *aliasrule::generate_code()
{
  // generate each rule within the alias
  for (rule * r = rules; r != NULL; r = r->next)
    r->generate_code();
  return "ERROR!";
}

/******************************
  From here on is all functions that 'globally' affect the world.
 ******************************/

/* process a list of ste\'s in reverse order. */
const char *ste::generate_decls()
{
  if (this != NULL) {
    if (next != NULL && next->scope == scope)
      next->generate_decls();
    value->generate_decl();
  }
  return "ERROR!";
}

// char *ste::generate_alias_decls()
// {
//   if ( this != NULL ) {
//       value->generate_decl();
//       if ( next != NULL && next->scope == scope )
//  next->generate_decls();
//     }
//   return "ERROR!";
// }

typedef void (*varproc) (vardecl * var);


void map_vars(ste * globals, varproc proc)
/* Calls proc for each variable in the list of declarations. */
{
  ste *next;
  if (globals != NULL) {
    next = globals->getnext();
    if (next != NULL && next->getscope() == globals->getscope())
      map_vars(next, proc);
    if (globals->getvalue()->getclass() == decl::Var) {
      (*proc) ((vardecl *) globals->getvalue());
    }
  }
}


/* The world::print() function prints out the state of every variable.
 * We have to make our own from the variable declarations. */
void make_print_world_aux(vardecl * var)
{
  fprintf(codefile, "  %s.print();\n", var->generate_code());
}

void make_print_world(ste * globals)
     /* done recursively. */
{
  fprintf(codefile,
	  "void world_class::print()\n"
	  "{\n"
	  "  static int num_calls = 0; /* to ward off recursive calls. */\n"
	  "  if ( num_calls == 0 ) {\n" "    num_calls++;\n");
  map_vars(globals, &make_print_world_aux);
  fprintf(codefile, "    num_calls--;\n" "}\n}\n");
}

/* The world::print_statistic() function prints out certain statistic of some variables.
 * We have to make our own from the variable declarations. */
void make_print_statistic_aux(vardecl * var)
{
  fprintf(codefile, "  %s.print_statistic();\n", var->generate_code());
}

void make_print_statistic(ste * globals)
     /* done recursively. */
{
  fprintf(codefile,
	  "void world_class::print_statistic()\n"
	  "{\n"
	  "  static int num_calls = 0; /* to ward off recursive calls. */\n"
	  "  if ( num_calls == 0 ) {\n" "    num_calls++;\n");
  map_vars(globals, &make_print_statistic_aux);
  fprintf(codefile, "    num_calls--;\n" "}\n}\n");
}

/* the world::clear() function clears every variable. */
void make_clear_aux(vardecl * var)
{
  fprintf(codefile, "  %s.clear();\n", var->generate_code());
}

void make_clear(ste * globals)
{
  fprintf(codefile, "void world_class::clear()\n" "{\n");
  map_vars(globals, &make_clear_aux);
  fprintf(codefile, "}\n");
}

/* the world::undefine() function resets every variable to an undefined state. */
void make_undefine_aux(vardecl * var)
{
  fprintf(codefile, "  %s.undefine();\n", var->generate_code());
}

void make_undefine(ste * globals)
{
  fprintf(codefile, "void world_class::undefine()\n" "{\n");
  map_vars(globals, &make_undefine_aux);
  fprintf(codefile, "}\n");
}

/* the world::reset() function resets every variable to an resetd state. */
void make_reset_aux(vardecl * var)
{
  fprintf(codefile, "  %s.reset();\n", var->generate_code());
}

void make_reset(ste * globals)
{
  fprintf(codefile, "void world_class::reset()\n" "{\n");
  map_vars(globals, &make_reset_aux);
  fprintf(codefile, "}\n");
}

/* the world::getstate() function returns a state
 * encoding the state of the world. */
void make_getstate_aux(vardecl * var)
{
  fprintf(codefile, "  %s.to_state( newstate );\n", var->generate_code());
}

void make_getstate(ste * globals)
{
  fprintf(codefile, "void world_class::to_state(state *newstate)\n{\n");
  // fprintf(codefile,"state *newstate = new state;\n");
  /* C++ doesn\'t know what a state looks like yet. Feh. */
  map_vars(globals, &make_getstate_aux);
  // fprintf(codefile,"return newstate;\n");
  fprintf(codefile, "}\n");
}

/* the world::setstate() function sets the world to the state recorded
 * in thestate. */
void make_setstate_aux(vardecl * var)
{
//  fprintf(codefile,"  %s.from_state(thestate);\n",
//    var->generate_code() );
}

void make_setstate(ste * globals)
{
  fprintf(codefile, "void world_class::setstate(state *thestate)\n{\n");
  map_vars(globals, &make_setstate_aux);
  fprintf(codefile, "}\n");
}


void make_print_diff_aux(vardecl * var)
{
  fprintf(codefile, "    %s.print_diff(prevstate);\n",
	  var->generate_code());
}

void make_print_diff(ste * globals)
{
  fprintf(codefile,
	  "void world_class::print_diff( state *prevstate )\n"
	  "{\n" "  if ( prevstate != NULL )\n" "  {\n");
  map_vars(globals, &make_print_diff_aux);
  fprintf(codefile, "  }\n");
  fprintf(codefile, "  else\n" "print();\n");
  fprintf(codefile, "}\n");
}


void make_world(ste * globals)
/* generate the world state. */
{
  make_clear(globals);
  make_undefine(globals);
  make_reset(globals);
  make_print_world(globals);
  make_print_statistic(globals);
  make_print_diff(globals);
  make_getstate(globals);
  make_setstate(globals);
}


/* Generate the global lists of rules.
 * since we can initialize arrays with a list
 * that ends in a comma, we do so here. */

int rulerec::print_rules()
{
  rulerec *r = this;
  int i = 0;
  if (r != NULL) {
    for (; r != NULL; r = r->next) {
      fprintf(codefile, "{\"%s\", ", r->rulename);
      if (r->conditionname == NULL)
	fprintf(codefile, "NULL, ");
      else
	fprintf(codefile, "&%s, ", r->conditionname);
      if (r->bodyname == NULL)
	fprintf(codefile, "NULL, ");
      else
	fprintf(codefile, "&%s, ", r->bodyname);
      fprintf(codefile, "},\n");
      i++;
    }
  } else {
    fprintf(codefile, "{ NULL, NULL, NULL, FALSE }");
  }
  return i;
}

int generate_invariants()
{
  int i, r;
  simplerule *sr;

  r = 0;
  for (sr = simplerule::SimpleRuleList; sr != NULL;
       sr = sr->NextSimpleRule) {
    if (sr->getclass() == rule::Invar) {
      sr->rulenumber = r++;
      sr->generate_code();
    }
  }
  return r;
}

int generate_startstates()
{
  int i, r;
  simplerule *sr;

  r = 0;
  for (sr = simplerule::SimpleRuleList; sr != NULL;
       sr = sr->NextSimpleRule) {
    if (sr->getclass() == rule::Startstate) {
      sr->rulenumber = r++;
      sr->generate_code();
    }
  }
  r = 0;
  fprintf(codefile, "class StartStateGenerator\n" "{\n");
  for (sr = simplerule::SimpleRuleList; sr != NULL;
       sr = sr->NextSimpleRule) {
    if (sr->getclass() == rule::Startstate) {
      fprintf(codefile, "  StartStateBase%d S%d;\n", r, r);
      r++;
    }
  }
  fprintf(codefile, "public:\n");

  // generate Code(r)
  fprintf(codefile, "void Code(unsigned short r)\n" "{\n");
  i = 0;
  r = 0;
  for (sr = simplerule::SimpleRuleList; sr != NULL;
       sr = sr->NextSimpleRule) {
    if (sr->getclass() == rule::Startstate) {
      if (i != 0)
	fprintf(codefile,
		"  if (r>=%d && r<=%d) { S%d.Code(r-%d); return; }\n",
		i, i + sr->getsize() - 1, r, i);
      else
	fprintf(codefile,
		"  if (r<=%d) { S%d.Code(r-%d); return; }\n",
		i + sr->getsize() - 1, r, i);
      r++;
      i += sr->getsize();
    }
  }
  fprintf(codefile, "}\n");

  // generate Name(r)
  fprintf(codefile, "char * Name(unsigned short r)\n" "{\n");
  i = 0;
  r = 0;
  for (sr = simplerule::SimpleRuleList; sr != NULL;
       sr = sr->NextSimpleRule) {
    if (sr->getclass() == rule::Startstate) {
      if (i != 0)
	fprintf(codefile,
		"  if (r>=%d && r<=%d) return S%d.Name(r-%d);\n",
		i, i + sr->getsize() - 1, r, i);
      else
	fprintf(codefile,
		"  if (r<=%d) return S%d.Name(r-%d);\n",
		i + sr->getsize() - 1, r, i);
      r++;
      i += sr->getsize();
    }
  }
  fprintf(codefile, "  return NULL;\n");	// Uli: return added
  fprintf(codefile, "}\n");
  fprintf(codefile, "};\n");
  return i;
}

int generate_ruleset()
{
  int i, r, max_r;
  simplerule *sr;

  r = 0;
  max_r = 0;
  for (sr = simplerule::SimpleRuleList; sr != NULL;
       sr = sr->NextSimpleRule) {
    if (sr->getclass() == rule::Simple && sr != error_rule) {
      sr->rulenumber = r++;
      max_r += sr->getsize();
      sr->maxrulenumber = max_r;
      sr->generate_code();
    }
  }

  r = 0;
  fprintf(codefile, "class NextStateGenerator\n" "{\n");
  for (sr = simplerule::SimpleRuleList; sr != NULL;
       sr = sr->NextSimpleRule) {
    if (sr->getclass() == rule::Simple && sr != error_rule) {
      fprintf(codefile, "  RuleBase%d R%d;\n", r, r);
      r++;
    }
  }
  fprintf(codefile, "public:\n");

  // generate SetNextEnabledRule(r)
  i = 0;
  r = 0;
  if (!args->pmurphik || args->prob_rules)
    //IM: in pmurphik mode, SetNextEnabledRule will return also the probability of the rule
    fprintf(codefile,
	    "void SetNextEnabledRule(unsigned & what_rule)\n"
	    "{\n" "  category = CONDITION;\n");
  else
    fprintf(codefile,
	    "void SetNextEnabledRule(unsigned & what_rule, double & what_prob)\n"
	    "{\n" "  category = CONDITION;\n");
  for (sr = simplerule::SimpleRuleList; sr != NULL;
       sr = sr->NextSimpleRule) {
    if (sr->getclass() == rule::Simple && sr != error_rule) {
      if (args->pmurphik && !args->prob_rules) {
	if (i != 0)
	  fprintf(codefile,
		  "  if (what_rule>=%d && what_rule<%d)\n"
		  "    { R%d.NextRule(what_rule, what_prob);\n"
		  "      if (what_rule<%d) return; }\n",
		  i, i + sr->getsize(), r, i + sr->getsize());
	else
	  fprintf(codefile,
		  "  if (what_rule<%d)\n"
		  "    { R%d.NextRule(what_rule, what_prob);\n"
		  "      if (what_rule<%d) return; }\n",
		  i + sr->getsize(), r, i + sr->getsize());
	r++;
	i += sr->getsize();
      } else {
	if (i != 0)
	  fprintf(codefile,
		  "  if (what_rule>=%d && what_rule<%d)\n"
		  "    { R%d.NextRule(what_rule);\n"
		  "      if (what_rule<%d) return; }\n",
		  i, i + sr->getsize(), r, i + sr->getsize());
	else
	  fprintf(codefile,
		  "  if (what_rule<%d)\n"
		  "    { R%d.NextRule(what_rule);\n"
		  "      if (what_rule<%d) return; }\n",
		  i + sr->getsize(), r, i + sr->getsize());
	r++;
	i += sr->getsize();
      }
    }
  }
  fprintf(codefile, "}\n");

  // generate Condition(r)
  fprintf(codefile,
	  "bool Condition(unsigned r)\n" "{\n"
	  "  category = CONDITION;\n");
  i = 0;
  r = 0;
  for (sr = simplerule::SimpleRuleList; sr != NULL;
       sr = sr->NextSimpleRule) {
    if (sr->getclass() == rule::Simple && sr != error_rule) {
      if (i != 0)
	fprintf(codefile,
		"  if (r>=%d && r<=%d) return R%d.Condition(r-%d);\n",
		i, i + sr->getsize() - 1, r, i);
      else
	fprintf(codefile,
		"  if (r<=%d) return R%d.Condition(r-%d);\n",
		i + sr->getsize() - 1, r, i);
      r++;
      i += sr->getsize();
    }
  }
  fprintf(codefile,
	  "Error.Notrace(\"Internal: NextStateGenerator -- checking condition for nonexisting rule.\");\n"
	  "return 0;}\n");


  // generate Code(r)
  fprintf(codefile, "void Code(unsigned r)\n" "{\n");
  i = 0;
  r = 0;
  for (sr = simplerule::SimpleRuleList; sr != NULL;
       sr = sr->NextSimpleRule) {
    if (sr->getclass() == rule::Simple && sr != error_rule) {
      if (i != 0)
	fprintf(codefile,
		"  if (r>=%d && r<=%d) { R%d.Code(r-%d); return; } \n",
		i, i + sr->getsize() - 1, r, i);
      else
	fprintf(codefile,
		"  if (r<=%d) { R%d.Code(r-%d); return; } \n",
		i + sr->getsize() - 1, r, i);
      r++;
      i += sr->getsize();
    }
  }
  fprintf(codefile, "}\n");

  // generate Priority, added by Uli
  fprintf(codefile, "int Priority(unsigned short r)\n" "{\n");
  i = 0;
  r = 0;
  for (sr = simplerule::SimpleRuleList; sr != NULL;
       sr = sr->NextSimpleRule) {
    if (sr->getclass() == rule::Simple && sr != error_rule) {
      if (i != 0)
	fprintf(codefile,
		"  if (r>=%d && r<=%d) { return R%d.Priority(); } \n",
		i, i + sr->getsize() - 1, r);
      else
	fprintf(codefile,
		"  if (r<=%d) { return R%d.Priority(); } \n",
		i + sr->getsize() - 1, r);
      r++;
      i += sr->getsize();
    }
  }
  fprintf(codefile, "return 0;}\n");

  // generate Name(r)
  fprintf(codefile, "char * Name(unsigned r)\n" "{\n");
  i = 0;
  r = 0;
  for (sr = simplerule::SimpleRuleList; sr != NULL;
       sr = sr->NextSimpleRule) {
    if (sr->getclass() == rule::Simple && sr != error_rule) {
      if (i != 0)
	fprintf(codefile,
		"  if (r>=%d && r<=%d) return R%d.Name(r-%d);\n",
		i, i + sr->getsize() - 1, r, i);
      else
	fprintf(codefile,
		"  if (r<=%d) return R%d.Name(r-%d);\n",
		i + sr->getsize() - 1, r, i);
      r++;
      i += sr->getsize();
    }
  }
  fprintf(codefile, "  return NULL;\n");	// added by Uli
  fprintf(codefile, "}\n");
  fprintf(codefile, "};\n");
  return i;
}

/******************************
  The main program
 ******************************/

const char *program::generate_code()
{
  int count;

  // header  
  fprintf(codefile, "/******************************\n");
  fprintf(codefile, "  Program \"%s\" compiled by \"%s\"\n",
	  args->filename, MURPHI_VERSION);
  fprintf(codefile, "\n");
  fprintf(codefile, "  Murphi Last Compiled date: \"%s\"\n", __DATE__);
  fprintf(codefile, " ******************************/\n");
  fprintf(codefile, "\n");

  // record the date of the compiler.
  fprintf(codefile, "/********************\n  Parameter\n");
  fprintf(codefile, " ********************/\n");
  fprintf(codefile, "#define MURPHI_VERSION \"%s\"\n", MURPHI_VERSION);

  fprintf(codefile, "#define MURPHI_DATE \"%s\"\n", __DATE__);
  fprintf(codefile, "#define PROTOCOL_NAME \"");	// added by Uli
  for (int i = 0, l = strlen(args->filename) - 2; i < l; i++)
    fputc(args->filename[i], codefile);
  fprintf(codefile, "\"\n#define BITS_IN_WORLD %d\n", bits_in_world);
  if (args->no_compression)
    fprintf(codefile, "#define ALIGN\n");
  if (args->hash_compression)
    fprintf(codefile, "#define HASHC\n");
  if (args->hash_disk)
    fprintf(codefile, "#define DISK_MURPHI\n");
  if (args->hash_cache)
    fprintf(codefile, "#define CACHED_MURPHI\n");
  if (args->pmurphik && !args->prob_rules)
    fprintf(codefile, "#define PMURPHIK\n");
  if (args->bpctl_prob_ord)
    fprintf(codefile, "#define BPCTL_PROB_ORD\n");
  if (args->noht)
    fprintf(codefile, "#define NO_HT\n");
  if (args->trace_dfs)
    fprintf(codefile, "#define TRACE_DFS\n");
  fprintf(codefile, "\n");

  // include prolog
  fprintf(codefile, "/********************\n  Include\n");
  fprintf(codefile, " ********************/\n");
  fprintf(codefile, "#include \"mu_prolog.hpp\"\n");

  /* generate dependent stuff. */
  fprintf(codefile, "\n/********************\n  Decl declaration\n");
  fprintf(codefile, " ********************/\n\n");
  if (args->prob_rules)
    fprintf(codefile, "double what_prob;\n\n");
  // typedecl declaration -- added to fixed a bug
  if (typedecl::origin != NULL)
    typedecl::origin->generate_all_decl();
  // globals->generate_decls() gets done by procedures->generate_decls
  procedures->generate_decls();
  fprintf(codefile, "\n\n\n");

  // generate the world
  fprintf(codefile, "\n/********************\n  The world\n");
  fprintf(codefile, " ********************/\n");
  make_world(globals);
  fprintf(codefile, "\n");

  // generate the codes for each rule
  fprintf(codefile, "\n/********************\n  Rule declarations\n");
  fprintf(codefile, " ********************/\n");

//   for ( rule *r = rules;
//  r != NULL;
//  r = r->next )
//     r->generate_code();
//   fprintf(codefile,"\n\n\n");
// 
//   /* generate the lists of rules, startstate, and invariants. */
//   // generate the lists of rules
//   fprintf(codefile,"\n/********************\n  Rule records\n");
//   fprintf(codefile," ********************/\n");
//   fprintf(codefile, "const rulerec rules[] = {\n");
//   count = rulelist->print_rules();
//   fprintf(codefile,"};\n");

  count = generate_ruleset();
  fprintf(codefile, "const unsigned numrules = %d;\n", count);
  if (args->bpctl_prob_ord && count == 1)
    printf
	("Warning: Since there is only one rule, there is no need to sort probabilities\n");

  fprintf(codefile, "\n/********************\n  parameter\n");
  fprintf(codefile, " ********************/\n");
  fprintf(codefile, "#define RULES_IN_WORLD %d\n", count);
  fprintf(codefile, "\n");

  // generate the lists of startstate
  fprintf(codefile, "\n/********************\n  Startstate records\n");
  fprintf(codefile, " ********************/\n");

//  fprintf(codefile, "const rulerec startstates[] = {\n");
//  count = startstatelist->print_rules();
//  fprintf(codefile,"};\n");
  count = generate_startstates();
  fprintf(codefile, "const rulerec startstates[] = {\n");
  simplerule *sr;		/* IM: this is to have probabilities on startstates */
  for (sr = simplerule::SimpleRuleList; sr != NULL;
       sr = sr->NextSimpleRule) {
    if (sr->getclass() == rule::Startstate) {
      if (args->pmurphik && !args->prob_rules)
	fprintf(codefile, "{ NULL, NULL, NULL, FALSE, 1.0},\n");
      else
	fprintf(codefile, "{ NULL, NULL, NULL, FALSE},\n");
    }

  }
  fprintf(codefile, "};\n");
  fprintf(codefile,
	  "unsigned short StartStateManager::numstartstates = %d;\n",
	  count);

  if (!args->bpctl && (!args->pmurphik || args->prob_rules)) {
    // generate the lists of invariants 
    fprintf(codefile, "\n/********************\n  Invariant records\n");
    fprintf(codefile, " ********************/\n");
    (void) generate_invariants();
    fprintf(codefile, "const rulerec invariants[] = {\n");
    count = invariantlist->print_rules();
    fprintf(codefile, "};\n");
    fprintf(codefile, "const unsigned short numinvariants = %d;\n", count);

  } else			//IM: PCTL formula code
  {
    fprintf(codefile,
	    "\n/********************\n  PCTL formulas records\n");
    fprintf(codefile, " ********************/\n");
    (void) theprog->pctl_form->generate_code();
    if (theprog->pctl_form->pctltype == UNTIL_PCTL) {
      fprintf(codefile, "const int mu_pctl_top_untils_form_num = 1;\n");
      fprintf(codefile,
	      "const pctlformrec *mu_pctl_top_untils_form[] = {&mu_pctl_formula,};\n");
    } else {
      int num_top_untils =
	  theprog->pctl_form->num_top_untils(theprog->pctl_form, 0);
      unsigned *indexes_top_untils =
	  (unsigned *) malloc(num_top_untils * sizeof(unsigned));
      theprog->pctl_form->ret_top_untils(theprog->pctl_form,
					 indexes_top_untils, 0);
      fprintf(codefile, "const int mu_pctl_top_untils_form_num = %d;\n",
	      num_top_untils);
      fprintf(codefile,
	      "const pctlformrec *mu_pctl_top_untils_form[] = {\n");
      for (int i = 0; i < num_top_untils; i++) {
	if (indexes_top_untils[i])
	  fprintf(codefile, "&mu_pctl_formula%d,", indexes_top_untils[i]);
	else
	  fprintf(codefile, "&mu_pctl_formula,");
      }
      fprintf(codefile, "};\n");
    }
  }
  // generate normalization/canonicalization function for scalarset
  fprintf(codefile,
	  "\n/********************\n  Normal/Canonicalization for scalarset\n");
  fprintf(codefile, " ********************/\n");
  symmetry.generate_code(globals);

  // include prolog
  fprintf(codefile, "\n/********************\n  Include\n");
  fprintf(codefile, " ********************/\n");

  /* I\'ve decided to just #include it, so that I can foist off the problem
   * of finding the file to be included on the c++ compiler. */
  /* But the filename still should not be hardcoded. */
  fprintf(codefile, "#include \"mu_epilog.hpp\"\n");

  return "ERROR!";
}

