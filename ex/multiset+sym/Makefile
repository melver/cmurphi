#**MakefileFile***********************************************************************
#
#  FileName    [Makefile]
#
#  Author      [Igor Melatti]
#
#  Copyright   [
#  This file contains the Makefile of multiset+sym CMurphi example.
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

all: cache3multi newcache3 newlist6 cache3multi.cache newcache3.cache newlist6.cache cache3multi.disk newcache3.disk newlist6.disk

splitfile: cache3multi.cache.splitfile newcache3.cache.splitfile newlist6.cache.splitfile cache3multi.disk.splitfile newcache3.disk.splitfile newlist6.disk.splitfile

# rules for compiling
cache3multi: cache3multi.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3multi cache3multi.cpp -I${INCLUDEPATH} -lm

newcache3: newcache3.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newcache3 newcache3.cpp -I${INCLUDEPATH} -lm

newlist6: newlist6.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newlist6 newlist6.cpp -I${INCLUDEPATH} -lm

cache3multi.cpp: cache3multi.m
	${SRCPATH}mu cache3multi.m

newcache3.cpp: newcache3.m 
	${SRCPATH}mu newcache3.m

newlist6.cpp: newlist6.m
	${SRCPATH}mu newlist6.m

cache3multi.cache: cache3multi.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3multi.cache cache3multi.cache.cpp -I${INCLUDEPATH} -lm

newcache3.cache: newcache3.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newcache3.cache newcache3.cache.cpp -I${INCLUDEPATH} -lm

newlist6.cache: newlist6.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newlist6.cache newlist6.cache.cpp -I${INCLUDEPATH} -lm

cache3multi.cache.splitfile: cache3multi.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3multi.cache.splitfile cache3multi.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

newcache3.cache.splitfile: newcache3.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newcache3.cache.splitfile newcache3.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

newlist6.cache.splitfile: newlist6.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newlist6.cache.splitfile newlist6.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

cache3multi.disk.splitfile: cache3multi.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3multi.disk.splitfile cache3multi.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

newcache3.disk.splitfile: newcache3.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newcache3.disk.splitfile newcache3.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

newlist6.disk.splitfile: newlist6.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newlist6.disk.splitfile newlist6.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

cache3multi.cache.cpp: cache3multi.m
	${SRCPATH}mu --cache -b -c cache3multi.m
	mv cache3multi.cpp cache3multi.cache.cpp

newcache3.cache.cpp: newcache3.m 
	${SRCPATH}mu --cache -b -c newcache3.m
	mv newcache3.cpp newcache3.cache.cpp

newlist6.cache.cpp: newlist6.m
	${SRCPATH}mu --cache -b -c newlist6.m
	mv newlist6.cpp newlist6.cache.cpp

cache3multi.disk: cache3multi.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3multi.disk cache3multi.disk.cpp -I${INCLUDEPATH} -lm

newcache3.disk: newcache3.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newcache3.disk newcache3.disk.cpp -I${INCLUDEPATH} -lm

newlist6.disk: newlist6.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newlist6.disk newlist6.disk.cpp -I${INCLUDEPATH} -lm

cache3multi.disk.cpp: cache3multi.m
	${SRCPATH}mu --disk -b -c cache3multi.m
	mv cache3multi.cpp cache3multi.disk.cpp

newcache3.disk.cpp: newcache3.m 
	${SRCPATH}mu --disk -b -c newcache3.m
	mv newcache3.cpp newcache3.disk.cpp

newlist6.disk.cpp: newlist6.m
	${SRCPATH}mu --disk -b -c newlist6.m
	mv newlist6.cpp newlist6.disk.cpp

clean : 
	rm -f *.cpp cache3multi newcache3 newlist6 cache3multi.cache newcache3.cache newlist6.cache cache3multi.disk newcache3.disk newlist6.disk cache3multi.cache.splitfile newcache3.cache.splitfilenewlist6.cache.splitfile cache3multi.disk.splitfile newcache3.disk.splitfilenewlist6.disk.splitfile

