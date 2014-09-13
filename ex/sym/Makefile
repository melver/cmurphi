#**MakefileFile***********************************************************************
#
#  FileName    [Makefile]
#
#  Author      [Igor Melatti]
#
#  Copyright   [
#  This file contains the Makefile of sym CMurphi example.
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

all: adash adashbug cache3 eadash ldash list6 list6too mcslock1 mcslock2 n_peterson adash.cache adashbug.cache cache3.cache eadash.cache ldash.cache list6.cache list6too.cache mcslock1.cache mcslock2.cache n_peterson.cache adash.disk adashbug.disk cache3.disk eadash.disk ldash.disk list6.disk list6too.disk mcslock1.disk mcslock2.disk n_peterson.disk
splitfile: adash.cache.splitfile adashbug.cache.splitfile cache3.cache.splitfile eadash.cache.splitfile ldash.cache.splitfile list6.cache.splitfile list6too.cache.splitfile mcslock1.cache.splitfile mcslock2.cache.splitfile n_peterson.cache.splitfile adash.disk.splitfile adashbug.disk.splitfile cache3.disk.splitfile eadash.disk.splitfile ldash.disk.splitfile list6.disk.splitfile list6too.disk.splitfile mcslock1.disk.splitfile mcslock2.disk.splitfile n_peterson.disk.splitfile 

# rules for compiling
adash: adash.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adash adash.cpp -I${INCLUDEPATH} -lm

adashbug: adashbug.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adashbug adashbug.cpp -I${INCLUDEPATH} -lm

cache3: cache3.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3 cache3.cpp -I${INCLUDEPATH} -lm

eadash: eadash.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o eadash eadash.cpp -I${INCLUDEPATH} -lm

ldash: ldash.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ldash ldash.cpp -I${INCLUDEPATH} -lm

list6: list6.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o list6 list6.cpp -I${INCLUDEPATH} -lm

list6too: list6too.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o list6too list6too.cpp -I${INCLUDEPATH} -lm

mcslock1: mcslock1.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock1 mcslock1.cpp -I${INCLUDEPATH} -lm

mcslock2: mcslock2.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock2 mcslock2.cpp -I${INCLUDEPATH} -lm

n_peterson: n_peterson.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o n_peterson n_peterson.cpp -I${INCLUDEPATH} -lm

adash.cache: adash.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adash.cache adash.cache.cpp -I${INCLUDEPATH} -lm

adashbug.cache: adashbug.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adashbug.cache adashbug.cache.cpp -I${INCLUDEPATH} -lm

cache3.cache: cache3.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3.cache cache3.cache.cpp -I${INCLUDEPATH} -lm

eadash.cache: eadash.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o eadash.cache eadash.cache.cpp -I${INCLUDEPATH} -lm

ldash.cache: ldash.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ldash.cache ldash.cache.cpp -I${INCLUDEPATH} -lm

list6.cache: list6.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o list6.cache list6.cache.cpp -I${INCLUDEPATH} -lm

list6too.cache: list6too.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o list6too.cache list6too.cache.cpp -I${INCLUDEPATH} -lm

mcslock1.cache: mcslock1.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock1.cache mcslock1.cache.cpp -I${INCLUDEPATH} -lm

mcslock2.cache: mcslock2.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock2.cache mcslock2.cache.cpp -I${INCLUDEPATH} -lm

n_peterson.cache: n_peterson.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o n_peterson.cache n_peterson.cache.cpp -I${INCLUDEPATH} -lm

adash.cache.splitfile: adash.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adash.cache.splitfile adash.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

adashbug.cache.splitfile: adashbug.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adashbug.cache.splitfile adashbug.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

cache3.cache.splitfile: cache3.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3.cache.splitfile cache3.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

eadash.cache.splitfile: eadash.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o eadash.cache.splitfile eadash.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

ldash.cache.splitfile: ldash.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ldash.cache.splitfile ldash.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

list6.cache.splitfile: list6.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o list6.cache.splitfile list6.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

list6too.cache.splitfile: list6too.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o list6too.cache.splitfile list6too.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

mcslock1.cache.splitfile: mcslock1.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock1.cache.splitfile mcslock1.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

mcslock2.cache.splitfile: mcslock2.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock2.cache.splitfile mcslock2.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

n_peterson.cache.splitfile: n_peterson.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o n_peterson.cache.splitfile n_peterson.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

adash.disk.splitfile: adash.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adash.disk.splitfile adash.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

adashbug.disk.splitfile: adashbug.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adashbug.disk.splitfile adashbug.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

cache3.disk.splitfile: cache3.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3.disk.splitfile cache3.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

eadash.disk.splitfile: eadash.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o eadash.disk.splitfile eadash.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

ldash.disk.splitfile: ldash.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ldash.disk.splitfile ldash.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

list6.disk.splitfile: list6.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o list6.disk.splitfile list6.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

list6too.disk.splitfile: list6too.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o list6too.disk.splitfile list6too.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

mcslock1.disk.splitfile: mcslock1.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock1.disk.splitfile mcslock1.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

mcslock2.disk.splitfile: mcslock2.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock2.disk.splitfile mcslock2.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

n_peterson.disk.splitfile: n_peterson.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o n_peterson.disk.splitfile n_peterson.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

adash.disk: adash.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adash.disk adash.disk.cpp -I${INCLUDEPATH} -lm

adashbug.disk: adashbug.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adashbug.disk adashbug.disk.cpp -I${INCLUDEPATH} -lm

cache3.disk: cache3.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3.disk cache3.disk.cpp -I${INCLUDEPATH} -lm

eadash.disk: eadash.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o eadash.disk eadash.disk.cpp -I${INCLUDEPATH} -lm

ldash.disk: ldash.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ldash.disk ldash.disk.cpp -I${INCLUDEPATH} -lm

list6.disk: list6.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o list6.disk list6.disk.cpp -I${INCLUDEPATH} -lm

list6too.disk: list6too.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o list6too.disk list6too.disk.cpp -I${INCLUDEPATH} -lm

mcslock1.disk: mcslock1.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock1.disk mcslock1.disk.cpp -I${INCLUDEPATH} -lm

mcslock2.disk: mcslock2.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o mcslock2.disk mcslock2.disk.cpp -I${INCLUDEPATH} -lm

n_peterson.disk: n_peterson.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o n_peterson.disk n_peterson.disk.cpp -I${INCLUDEPATH} -lm

#######

adash.cpp: adash.m
	${SRCPATH}mu adash.m

adashbug.cpp: adashbug.m
	${SRCPATH}mu adashbug.m

cache3.cpp: cache3.m
	${SRCPATH}mu cache3.m

eadash.cpp: eadash.m
	${SRCPATH}mu eadash.m

ldash.cpp: ldash.m
	${SRCPATH}mu ldash.m

list6.cpp: list6.m
	${SRCPATH}mu list6.m

list6too.cpp: list6too.m
	${SRCPATH}mu list6too.m

mcslock1.cpp: mcslock1.m
	${SRCPATH}mu mcslock1.m

mcslock2.cpp: mcslock2.m
	${SRCPATH}mu mcslock2.m

n_peterson.cpp: n_peterson.m
	${SRCPATH}mu n_peterson.m

adash.cache.cpp: adash.m
	${SRCPATH}mu --cache -b -c adash.m
	mv adash.cpp adash.cache.cpp

adashbug.cache.cpp: adashbug.m
	${SRCPATH}mu --cache -b -c adashbug.m
	mv adashbug.cpp adashbug.cache.cpp

cache3.cache.cpp: cache3.m
	${SRCPATH}mu --cache -b -c cache3.m
	mv cache3.cpp cache3.cache.cpp

eadash.cache.cpp: eadash.m
	${SRCPATH}mu --cache -b -c eadash.m
	mv eadash.cpp eadash.cache.cpp

ldash.cache.cpp: ldash.m
	${SRCPATH}mu --cache -b -c ldash.m
	mv ldash.cpp ldash.cache.cpp

list6.cache.cpp: list6.m
	${SRCPATH}mu --cache -b -c list6.m
	mv list6.cpp list6.cache.cpp

list6too.cache.cpp: list6too.m
	${SRCPATH}mu --cache -b -c list6too.m
	mv list6too.cpp list6too.cache.cpp

mcslock1.cache.cpp: mcslock1.m
	${SRCPATH}mu --cache -b -c mcslock1.m
	mv mcslock1.cpp mcslock1.cache.cpp

mcslock2.cache.cpp: mcslock2.m
	${SRCPATH}mu --cache -b -c mcslock2.m
	mv mcslock2.cpp mcslock2.cache.cpp

n_peterson.cache.cpp: n_peterson.m
	${SRCPATH}mu --cache -b -c n_peterson.m
	mv n_peterson.cpp n_peterson.cache.cpp

adash.disk.cpp: adash.m
	${SRCPATH}mu --disk adash.m
	mv adash.cpp adash.disk.cpp

adashbug.disk.cpp: adashbug.m
	${SRCPATH}mu --disk adashbug.m
	mv adashbug.cpp adashbug.disk.cpp

cache3.disk.cpp: cache3.m
	${SRCPATH}mu --disk cache3.m
	mv cache3.cpp cache3.disk.cpp

eadash.disk.cpp: eadash.m
	${SRCPATH}mu --disk eadash.m
	mv eadash.cpp eadash.disk.cpp

ldash.disk.cpp: ldash.m
	${SRCPATH}mu --disk ldash.m
	mv ldash.cpp ldash.disk.cpp

list6.disk.cpp: list6.m
	${SRCPATH}mu --disk list6.m
	mv list6.cpp list6.disk.cpp

list6too.disk.cpp: list6too.m
	${SRCPATH}mu --disk list6too.m
	mv list6too.cpp list6too.disk.cpp

mcslock1.disk.cpp: mcslock1.m
	${SRCPATH}mu --disk mcslock1.m
	mv mcslock1.cpp mcslock1.disk.cpp

mcslock2.disk.cpp: mcslock2.m
	${SRCPATH}mu --disk mcslock2.m
	mv mcslock2.cpp mcslock2.disk.cpp

n_peterson.disk.cpp: n_peterson.m
	${SRCPATH}mu --disk n_peterson.m
	mv n_peterson.cpp n_peterson.disk.cpp

clean: 
	rm -f *.cpp adash adashbug cache3 eadash ldash list6 list6too mcslock1 mcslock2 n_peterson adash.cache adashbug.cache cache3.cache eadash.cache ldash.cache list6.cache list6too.cache mcslock1.cache mcslock2.cache n_peterson.cache adash.disk adashbug.disk cache3.disk eadash.disk ldash.disk list6.disk list6too.disk mcslock1.disk mcslock2.disk n_peterson.disk adash.cache.splitfile adashbug.cache.splitfile cache3.cache.splitfile eadash.cache.splitfile ldash.cache.splitfile list6.cache.splitfile list6too.cache.splitfile mcslock1.cache.splitfile mcslock2.cache.splitfile n_peterson.cache.splitfile adash.disk.splitfile adashbug.disk.splitfile cache3.disk.splitfile eadash.disk.splitfile ldash.disk.splitfile list6.disk.splitfile list6too.disk.splitfile mcslock1.disk.splitfile mcslock2.disk.splitfile n_peterson.disk.splitfile 
