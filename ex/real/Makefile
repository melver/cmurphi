#**MakefileFile***********************************************************************
#
#  FileName    [Makefile]
#
#  Author      [Igor Melatti]
#
#  Copyright   [
#  This file contains the Makefile of turbogas CMurphi example.
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

all: turbogas turbogas.cache turbogas.disk 
splitfile: turbogas.cache.splitfile turbogas.disk.splitfile 

# rules for compiling
turbogas: turbogas.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o turbogas turbogas.cpp -I${INCLUDEPATH} -lm

turbogas.cache: turbogas.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o turbogas.cache turbogas.cache.cpp -I${INCLUDEPATH} -lm

turbogas.cache.splitfile: turbogas.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o turbogas.cache.splitfile turbogas.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

turbogas.disk.splitfile: turbogas.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o turbogas.disk.splitfile turbogas.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

turbogas.disk: turbogas.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o turbogas.disk turbogas.disk.cpp -I${INCLUDEPATH} -lm

turbogas.cpp: turbogas.m
	${SRCPATH}mu turbogas.m

turbogas.cache.cpp: turbogas.m
	${SRCPATH}mu --cache -b -c turbogas.m
	mv turbogas.cpp turbogas.cache.cpp

turbogas.disk.cpp: turbogas.m
	${SRCPATH}mu --disk turbogas.m
	mv turbogas.cpp turbogas.disk.cpp

clean:
	rm -f *.cpp turbogas turbogas.cache turbogas.disk turbogas.cache.splitfile turbogas.disk.splitfile 
