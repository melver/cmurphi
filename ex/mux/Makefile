#**MakefileFile***********************************************************************
#
#  FileName    [Makefile]
#
#  Author      [Igor Melatti]
#
#  Copyright   [
#  This file contains the Makefile of mux CMurphi example.
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

all: 2_peterson n_peterson dek mcslock1 mcslock2 2_peterson.cache n_peterson.cache dek.cache mcslock1.cache mcslock2.cache 2_peterson.disk n_peterson.disk dek.disk mcslock1.disk mcslock2.disk

splitfile: 2_peterson.cache.splitfile n_peterson.cache.splitfile dek.cache.splitfile mcslock1.cache.splitfile mcslock2.cache.splitfile 2_peterson.disk.splitfile n_peterson.disk.splitfile dek.disk.splitfile mcslock1.disk.splitfile mcslock2.disk.splitfile 

# rules for compiling
2_peterson: 2_peterson.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o 2_peterson 2_peterson.cpp -I${INCLUDEPATH} -lm

dek: dek.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dek dek.cpp -I${INCLUDEPATH} -lm

mcslock1: mcslock1.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock1 mcslock1.cpp -I${INCLUDEPATH} -lm

mcslock2: mcslock2.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock2 mcslock2.cpp -I${INCLUDEPATH} -lm

n_peterson: n_peterson.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o n_peterson n_peterson.cpp -I${INCLUDEPATH} -lm

2_peterson.cpp: 2_peterson.m
	${SRCPATH}mu 2_peterson.m

n_peterson.cpp: n_peterson.m
	${SRCPATH}mu n_peterson.m

dek.cpp: dek.m 
	${SRCPATH}mu dek.m

mcslock1.cpp: mcslock1.m
	${SRCPATH}mu mcslock1.m

mcslock2.cpp: mcslock2.m
	${SRCPATH}mu mcslock2.m

2_peterson.cache: 2_peterson.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o 2_peterson.cache 2_peterson.cache.cpp -I${INCLUDEPATH} -lm

dek.cache: dek.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dek.cache dek.cache.cpp -I${INCLUDEPATH} -lm

mcslock1.cache: mcslock1.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock1.cache mcslock1.cache.cpp -I${INCLUDEPATH} -lm

mcslock2.cache: mcslock2.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock2.cache mcslock2.cache.cpp -I${INCLUDEPATH} -lm

n_peterson.cache: n_peterson.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o n_peterson.cache n_peterson.cache.cpp -I${INCLUDEPATH} -lm

2_peterson.cache.splitfile: 2_peterson.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o 2_peterson.cache.splitfile 2_peterson.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

dek.cache.splitfile: dek.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dek.cache.splitfile dek.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

mcslock1.cache.splitfile: mcslock1.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock1.cache.splitfile mcslock1.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

mcslock2.cache.splitfile: mcslock2.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock2.cache.splitfile mcslock2.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

n_peterson.cache.splitfile: n_peterson.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o n_peterson.cache.splitfile n_peterson.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

2_peterson.disk.splitfile: 2_peterson.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o 2_peterson.disk.splitfile 2_peterson.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

dek.disk.splitfile: dek.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dek.disk.splitfile dek.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

mcslock1.disk.splitfile: mcslock1.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock1.disk.splitfile mcslock1.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

mcslock2.disk.splitfile: mcslock2.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock2.disk.splitfile mcslock2.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

n_peterson.disk.splitfile: n_peterson.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o n_peterson.disk.splitfile n_peterson.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

2_peterson.cache.cpp: 2_peterson.m
	${SRCPATH}mu --cache -b -c 2_peterson.m
	mv 2_peterson.cpp 2_peterson.cache.cpp

n_peterson.cache.cpp: n_peterson.m
	${SRCPATH}mu --cache -b -c n_peterson.m
	mv n_peterson.cpp n_peterson.cache.cpp

dek.cache.cpp: dek.m 
	${SRCPATH}mu --cache -b -c dek.m
	mv dek.cpp dek.cache.cpp

mcslock1.cache.cpp: mcslock1.m
	${SRCPATH}mu --cache -b -c mcslock1.m
	mv mcslock1.cpp mcslock1.cache.cpp

mcslock2.cache.cpp: mcslock2.m
	${SRCPATH}mu --cache -b -c mcslock2.m
	mv mcslock2.cpp mcslock2.cache.cpp

2_peterson.disk: 2_peterson.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o 2_peterson.disk 2_peterson.disk.cpp -I${INCLUDEPATH} -lm

dek.disk: dek.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dek.disk dek.disk.cpp -I${INCLUDEPATH} -lm

mcslock1.disk: mcslock1.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock1.disk mcslock1.disk.cpp -I${INCLUDEPATH} -lm

mcslock2.disk: mcslock2.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock2.disk mcslock2.disk.cpp -I${INCLUDEPATH} -lm

n_peterson.disk: n_peterson.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o n_peterson.disk n_peterson.disk.cpp -I${INCLUDEPATH} -lm

2_peterson.disk.cpp: 2_peterson.m
	${SRCPATH}mu --disk -b -c 2_peterson.m
	mv 2_peterson.cpp 2_peterson.disk.cpp

n_peterson.disk.cpp: n_peterson.m
	${SRCPATH}mu --disk -b -c n_peterson.m
	mv n_peterson.cpp n_peterson.disk.cpp

dek.disk.cpp: dek.m 
	${SRCPATH}mu --disk -b -c dek.m
	mv dek.cpp dek.disk.cpp

mcslock1.disk.cpp: mcslock1.m
	${SRCPATH}mu --disk -b -c mcslock1.m
	mv mcslock1.cpp mcslock1.disk.cpp

mcslock2.disk.cpp: mcslock2.m
	${SRCPATH}mu --disk -b -c mcslock2.m
	mv mcslock2.cpp mcslock2.disk.cpp

clean : 
	rm -f *.cpp 2_peterson n_peterson dek mcslock1 mcslock2 2_peterson.cache n_peterson.cache dek.cache mcslock1.cache mcslock2.cache 2_peterson.disk n_peterson.disk dek.disk mcslock1.disk mcslock2.disk 2_peterson.cache.splitfile n_peterson.cache.splitfile dek.cache.splitfile mcslock1.cache.splitfile mcslock2.cache.splitfile 2_peterson.disk.splitfile n_peterson.disk.splitfile dek.disk.splitfile mcslock1.disk.splitfile mcslock2.disk.splitfile 

