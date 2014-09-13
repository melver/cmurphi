#**MakefileFile***********************************************************************
#
#  FileName    [Makefile]
#
#  Author      [Igor Melatti]
#
#  Copyright   [
#  This file contains the Makefile of sci CMurphi example.
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

INCLUDEPATH = ../../include
SRCPATH = ../../src/

CXX = g++

CFLAGS = 

# optimization
OFLAGS = -ggdb
#OFLAGS = -O2

#Murphi options
MURPHIOPTS = -b -c

all: sci scierr sci.disk scierr.disk sci.cache scierr.cache
splitfile: sci.cache.splitfile scierr.cache.splitfile sci.disk.splitfile scierr.disk.splitfile

# rules for compiling
sci: sci.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sci sci.cpp -I${INCLUDEPATH}

scierr: scierr.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o scierr scierr.cpp -I${INCLUDEPATH}

sci.cache: sci.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sci.cache sci.cache.cpp -I${INCLUDEPATH}

scierr.cache: scierr.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o scierr.cache scierr.cache.cpp -I${INCLUDEPATH}

sci.cache.splitfile: sci.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sci.cache.splitfile sci.cache.cpp -I${INCLUDEPATH} -DSPLITFILE

scierr.cache.splitfile: scierr.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o scierr.cache.splitfile scierr.cache.cpp -I${INCLUDEPATH} -DSPLITFILE

sci.disk: sci.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sci.disk sci.disk.cpp -I${INCLUDEPATH}

scierr.disk: scierr.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o scierr.disk scierr.disk.cpp -I${INCLUDEPATH}

sci.disk.splitfile: sci.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sci.disk.splitfile sci.disk.cpp -I${INCLUDEPATH} -DSPLITFILE

scierr.disk.splitfile: scierr.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o scierr.disk.splitfile scierr.disk.cpp -I${INCLUDEPATH} -DSPLITFILE

sci.cpp: sci.m
	${SRCPATH}mu sci.m

scierr.cpp: scierr.m
	${SRCPATH}mu -b -c scierr.m

sci.cache.cpp: sci.m
	${SRCPATH}mu --cache -b -c sci.m
	mv sci.cpp sci.cache.cpp

scierr.cache.cpp: scierr.m
	${SRCPATH}mu --cache -b -c scierr.m
	mv scierr.cpp scierr.cache.cpp

sci.disk.cpp: sci.m
	${SRCPATH}mu --disk sci.m
	mv sci.cpp sci.disk.cpp

scierr.disk.cpp: scierr.m
	${SRCPATH}mu --disk scierr.m
	mv scierr.cpp scierr.disk.cpp

clean: 
	rm -f *.cpp sci scierr sci.disk scierr.disk sci.cache scierr.cache sci.cache.splitfile scierr.cache.splitfile sci.disk.splitfile scierr.disk.splitfile
