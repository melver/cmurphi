/**CFile***********************************************************************

  FileName    [cpp_code_as.cpp]

  Synopsis    [File for assignments code generation]

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

void
 arraytypedecl::generate_assign()
{
  char indexstr[3];

  strcpy(indexstr, (indextype->getsize() > 1 ? "i" : "0"));
  fprintf(codefile,
	  "  %s& operator= (const %s& from)\n" "  {\n", mu_name, mu_name);
  if (indextype->getsize() > 1)
    fprintf(codefile,
	    "    for (int i = 0; i < %d; i++)\n", indextype->getsize());
  if (elementtype->issimple())
    fprintf(codefile,
	    "      array[%s].value(from.array[%s].value());\n",
	    indexstr, indexstr);
  else
    fprintf(codefile,
	    "      array[%s] = from.array[%s];\n", indexstr, indexstr);
  fprintf(codefile, "    return *this;\n" "  }\n\n");
};

void multisettypedecl::generate_assign()
{
  char indexstr[3];

  strcpy(indexstr, (maximum_size > 1 ? "i" : "0"));
  fprintf(codefile,
	  "  %s& operator= (const %s& from)\n" "  {\n", mu_name, mu_name);
  if (maximum_size > 1)
    fprintf(codefile, "    for (int i = 0; i < %d; i++)\n", maximum_size);
  if (elementtype->issimple())
    fprintf(codefile,
	    "    {\n"
	    "        array[%s].value(from.array[%s].value());\n"
	    "        valid[%s].value(from.valid[%s].value());\n",
	    indexstr, indexstr, indexstr, indexstr);
  else
    fprintf(codefile,
	    "    {\n"
	    "       array[%s] = from.array[%s];\n"
	    "       valid[%s].value(from.valid[%s].value());\n",
	    indexstr, indexstr, indexstr, indexstr);
  fprintf(codefile,
	  "    };\n"
	  "    current_size = from.get_current_size();\n"
	  "    return *this;\n" "  }\n\n");
};

void recordtypedecl::generate_assign()
{
  ste *f;

  fprintf(codefile,
	  "  %s& operator= (const %s& from) {\n", mu_name, mu_name);
  for (f = fields; f != NULL; f = f->getnext()) {
    if (f->getvalue()->gettype()->issimple())
      fprintf(codefile,
	      "    %s.value(from.%s.value());\n",
	      f->getvalue()->generate_code(),
	      f->getvalue()->generate_code());
    else
      fprintf(codefile,
	      "    %s = from.%s;\n",
	      f->getvalue()->generate_code(),
	      f->getvalue()->generate_code());
  }
  fprintf(codefile, "    return *this;\n" "  };\n");
};

