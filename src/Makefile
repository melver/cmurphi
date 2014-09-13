#**MakefileFile***********************************************************************
#
#  FileName    [Makefile]
#
#  Author      [Igor Melatti]
#
#  Copyright   [
#  This file contains the Makefile of CMurphi. 
#  Copyright (C) 2009-2012 by Sapienza University of Rome. 
#
#  CMurphi is free software; you can redistribute it and/or 
#  modify it under the terms of the GNU Lesser General Public 
#  License as published by the Free Software Foundation; either 
#  of the License, or (at your option) any later version.
#
#  CMurphi is distributed in the hope that it will be useful, 
#  but WITHOUT ANY WARRANTY; without even the implied warranty of 
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
#  Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public 
#  License along with this library; if not, write to the Free Software 
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA.
#
#  To contact the CMurphi development board, email to <melatti@di.uniroma1.it>. ]
#
#*************************************************************************************

########################################
#   Please make sure that you have set the 
#   appropriate path for "flex", "byacc" and c++ compiler.
#
#   options:
#   1) "make" or "make mu"  
#      --> compile mu
#   2) "make clean"
#      --> remove all intermediate files
#   3) "make cleanall"
#      --> remove all intermediate files, including byacc and flex ones.
#
########################################

# choice of compilers
CPLUSPLUS = g++
FLEX = flex
BYACC = byacc

# choice of the options
CFLAGS = -O2                               # options for g++

OBJS = \
	lex.yy.o \
	y.tab.o \
	cpp_code.o \
	cpp_code_as.o \
  	cpp_sym.o \
  	cpp_sym_aux.o \
  	cpp_sym_decl.o \
	decl.o \
	error.o \
	expr.o \
	lextable.o \
	mu.o \
	parse.o \
	rule.o \
	stmt.o \
	symtab.o \
	util.o

mu: $(OBJS)
	$(CPLUSPLUS) -o mu $(CFLAGS) $(OBJS)

mu.o: mu.cpp mu.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) mu.cpp

cpp_code.o: cpp_code.cpp mu.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) cpp_code.cpp

cpp_code_as.o: cpp_code_as.cpp mu.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) cpp_code_as.cpp

cpp_sym.o: cpp_sym.cpp mu.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) cpp_sym.cpp

cpp_sym_aux.o: cpp_sym_aux.cpp mu.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) cpp_sym_aux.cpp

cpp_sym_decl.o: cpp_sym_decl.cpp mu.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) cpp_sym_decl.cpp

decl.o: decl.cpp mu.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) decl.cpp

error.o: error.cpp mu.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) error.cpp

expr.o: expr.cpp mu.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) expr.cpp

lextable.o: lextable.cpp mu.hpp lextable.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) lextable.cpp

rule.o: rule.cpp mu.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) rule.cpp

stmt.o: stmt.cpp mu.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) stmt.cpp

symtab.o: symtab.cpp mu.hpp lextable.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) symtab.cpp

util.o: util.cpp mu.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) util.cpp

parse.o: parse.cpp mu.hpp y.tab.h
	$(CPLUSPLUS) -c $(CFLAGS) parse.cpp

lex.yy.o: lex.yy.c mu.hpp lextable.hpp
	$(CPLUSPLUS) -c $(CFLAGS) lex.yy.c

lex.yy.c: mu.l mu.hpp y.tab.h
	$(FLEX) mu.l

y.tab.o: y.tab.c mu.hpp y.tab.h
	$(CPLUSPLUS) -c -DYYDEBUG=0 $(CFLAGS) y.tab.c

y.tab.c + y.tab.h: mu.y
	$(BYACC) -dt mu.y

clean:
	rm -f  *.o

cleanall: clean
	rm -f  y.* lex.yy.c mu

