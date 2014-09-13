#**MakefileFile***********************************************************************
#
#  FileName    [Makefile]
#
#  Author      [Igor Melatti]
#
#  Copyright   [
#  This file contains the Makefile of secur CMurphi example.
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

all: ns ns-old ns.cache ns-old.cache ns.disk ns-old.disk
splitfile: ns.cache.splitfile ns-old.cache.splitfile ns.disk.splitfile ns-old.disk.splitfile 

# rules for compiling
ns: ns.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ns ns.cpp -I${INCLUDEPATH} -lm

ns-old: ns-old.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ns-old ns-old.cpp -I${INCLUDEPATH} -lm

ns.cache: ns.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ns.cache ns.cache.cpp -I${INCLUDEPATH} -lm

ns-old.cache: ns-old.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ns-old.cache ns-old.cache.cpp -I${INCLUDEPATH} -lm

ns.cache.splitfile: ns.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ns.cache.splitfile ns.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

ns-old.cache.splitfile: ns-old.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ns-old.cache.splitfile ns-old.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

ns.disk.splitfile: ns.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ns.disk.splitfile ns.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

ns-old.disk.splitfile: ns-old.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ns-old.disk.splitfile ns-old.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

ns.disk: ns.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ns.disk ns.disk.cpp -I${INCLUDEPATH} -lm

ns-old.disk: ns-old.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ns-old.disk ns-old.disk.cpp -I${INCLUDEPATH} -lm

ns.cpp: ns.m
	${SRCPATH}mu ns.m

ns-old.cpp: ns-old.m
	${SRCPATH}mu ns-old.m

ns.cache.cpp: ns.m
	${SRCPATH}mu --cache -b -c ns.m
	mv ns.cpp ns.cache.cpp

ns-old.cache.cpp: ns-old.m
	${SRCPATH}mu --cache -b -c ns-old.m
	mv ns-old.cpp ns-old.cache.cpp

ns.disk.cpp: ns.m
	${SRCPATH}mu --disk ns.m
	mv ns.cpp ns.disk.cpp

ns-old.disk.cpp: ns-old.m
	${SRCPATH}mu --disk ns-old.m
	mv ns-old.cpp ns-old.disk.cpp

clean:
	rm -f *.cpp ns ns-old ns.cache ns-old.cache ns.disk ns-old.disk ns.cache.splitfile ns-old.cache.splitfile ns.disk.splitfile ns-old.disk.splitfile 
