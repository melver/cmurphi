#**MakefileFile***********************************************************************
#
#  FileName    [Makefile]
#
#  Author      [Igor Melatti]
#
#  Copyright   [
#  This file contains the Makefile of probturbogas CMurphi example.
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

INCLUDEPATH = ../../../include
SRCPATH = ../../../src/

CXX = g++

CFLAGS = 

# optimization
OFLAGS = -ggdb
#OFLAGS = -O2

# could be --bpctl or --bpctl-prob-ord
BPCTL_OPT=--bpctl

all : prob_turbogas 

# rules for compiling
prob_turbogas : prob_turbogas.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o prob_turbogas prob_turbogas.cpp -I${INCLUDEPATH} -lm

prob_turbogas.cpp : prob_turbogas.m
	${SRCPATH}mu ${BPCTL_OPT} prob_turbogas.m

clean : 
	rm -f *.cpp prob_turbogas 



