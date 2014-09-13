#**MakefileFile***********************************************************************
#
#  FileName    [Makefile]
#
#  Author      [Igor Melatti]
#
#  Copyright   [
#  This file contains the Makefile of toy CMurphi example.
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

all: down lin pingpong sets sort5 down.cache lin.cache pingpong.cache sets.cache sort5.cache down.disk lin.disk pingpong.disk sets.disk sort5.disk 
splitfile: lin.cache.splitfile pingpong.cache.splitfile sets.cache.splitfile sort5.cache.splitfile lin.disk.splitfile pingpong.disk.splitfile sets.disk.splitfile sort5.disk.splitfile

# rules for compiling
down: down.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o down down.cpp -I${INCLUDEPATH} -lm

lin: lin.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o lin lin.cpp -I${INCLUDEPATH} -lm

pingpong: pingpong.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o pingpong pingpong.cpp -I${INCLUDEPATH} -lm

sets: sets.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sets sets.cpp -I${INCLUDEPATH} -lm

sort5: sort5.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sort5 sort5.cpp -I${INCLUDEPATH} -lm

down.cache: down.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o down.cache down.cache.cpp -I${INCLUDEPATH} -lm

lin.cache: lin.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o lin.cache lin.cache.cpp -I${INCLUDEPATH} -lm

pingpong.cache: pingpong.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o pingpong.cache pingpong.cache.cpp -I${INCLUDEPATH} -lm

sets.cache: sets.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sets.cache sets.cache.cpp -I${INCLUDEPATH} -lm

sort5.cache: sort5.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sort5.cache sort5.cache.cpp -I${INCLUDEPATH} -lm

down.cache.splitfile: down.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o down.cache.splitfile down.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

lin.cache.splitfile: lin.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o lin.cache.splitfile lin.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

pingpong.cache.splitfile: pingpong.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o pingpong.cache.splitfile pingpong.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

sets.cache.splitfile: sets.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sets.cache.splitfile sets.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

sort5.cache.splitfile: sort5.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sort5.cache.splitfile sort5.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

down.disk.splitfile: down.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o down.disk.splitfile down.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

lin.disk.splitfile: lin.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o lin.disk.splitfile lin.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

pingpong.disk.splitfile: pingpong.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o pingpong.disk.splitfile pingpong.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

sets.disk.splitfile: sets.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sets.disk.splitfile sets.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

sort5.disk.splitfile: sort5.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sort5.disk.splitfile sort5.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

down.disk: down.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o down.disk down.disk.cpp -I${INCLUDEPATH} -lm

lin.disk: lin.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o lin.disk lin.disk.cpp -I${INCLUDEPATH} -lm

pingpong.disk: pingpong.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o pingpong.disk pingpong.disk.cpp -I${INCLUDEPATH} -lm

sets.disk: sets.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sets.disk sets.disk.cpp -I${INCLUDEPATH} -lm

sort5.disk: sort5.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o sort5.disk sort5.disk.cpp -I${INCLUDEPATH} -lm

# rules for C files
down.cpp: down.m
	${SRCPATH}mu ${MURPHIOPTS} down.m

lin.cpp: lin.m
	${SRCPATH}mu ${MURPHIOPTS} lin.m

pingpong.cpp: pingpong.m
	${SRCPATH}mu ${MURPHIOPTS} pingpong.m

sets.cpp: sets.m
	${SRCPATH}mu ${MURPHIOPTS} sets.m

sort5.cpp: sort5.m
	${SRCPATH}mu ${MURPHIOPTS} sort5.m

down.cache.cpp: down.m
	${SRCPATH}mu --cache -b -c down.m
	mv down.cpp down.cache.cpp

lin.cache.cpp: lin.m
	${SRCPATH}mu --cache -b -c lin.m
	mv lin.cpp lin.cache.cpp

pingpong.cache.cpp: pingpong.m
	${SRCPATH}mu --cache -b -c pingpong.m
	mv pingpong.cpp pingpong.cache.cpp

sets.cache.cpp: sets.m
	${SRCPATH}mu --cache -b -c sets.m
	mv sets.cpp sets.cache.cpp

sort5.cache.cpp: sort5.m
	${SRCPATH}mu --cache -b -c sort5.m
	mv sort5.cpp sort5.cache.cpp

down.disk.cpp: down.m
	${SRCPATH}mu --disk  down.m
	mv down.cpp down.disk.cpp

lin.disk.cpp: lin.m
	${SRCPATH}mu --disk  lin.m
	mv lin.cpp lin.disk.cpp

pingpong.disk.cpp: pingpong.m
	${SRCPATH}mu --disk  pingpong.m
	mv pingpong.cpp pingpong.disk.cpp

sets.disk.cpp: sets.m
	${SRCPATH}mu --disk  sets.m
	mv sets.cpp sets.disk.cpp

sort5.disk.cpp: sort5.m
	${SRCPATH}mu --disk  sort5.m
	mv sort5.cpp sort5.disk.cpp

clean:
	rm -f *.cpp down lin pingpong sets sort5 down.cache lin.cache pingpong.cache sets.cache sort5.cache down.disk lin.disk pingpong.disk sets.disk sort5.disk lin.cache.splitfile pingpong.cache.splitfile sets.cache.splitfile sort5.cache.splitfile lin.disk.splitfile pingpong.disk.splitfile sets.disk.splitfile sort5.disk.splitfile


