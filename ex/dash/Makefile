#**MakefileFile***********************************************************************
#
#  FileName    [Makefile]
#
#  Author      [Igor Melatti]
#
#  Copyright   [
#  This file contains the Makefile of dash CMurphi example.
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

all: adash.cache eadash.cache ldash.cache adash.disk eadash.disk ldash.disk adash eadash ldash 
splitfile: adash.cache.splitfile eadash.cache.splitfile ldash.cache.splitfile adash.disk.splitfile eadash.disk.splitfile ldash.disk.splitfile 

# rules for compiling
adash: adash.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adash adash.cpp -I${INCLUDEPATH} -lm

eadash: eadash.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o eadash eadash.cpp -I${INCLUDEPATH} -lm

ldash: ldash.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ldash ldash.cpp -I${INCLUDEPATH} -lm

adash.cpp: adash.m
	${SRCPATH}mu adash.m

eadash.cpp: eadash.m 
	${SRCPATH}mu eadash.m

ldash.cpp: ldash.m
	${SRCPATH}mu ldash.m

adash.cache: adash.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adash.cache adash.cache.cpp -I${INCLUDEPATH} -lm

eadash.cache: eadash.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o eadash.cache eadash.cache.cpp -I${INCLUDEPATH} -lm

ldash.cache: ldash.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ldash.cache ldash.cache.cpp -I${INCLUDEPATH} -lm

adash.cache.splitfile: adash.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adash.cache.splitfile adash.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

eadash.cache.splitfile: eadash.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o eadash.cache.splitfile eadash.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

ldash.cache.splitfile: ldash.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ldash.cache.splitfile ldash.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

adash.disk.splitfile: adash.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adash.disk.splitfile adash.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

eadash.disk.splitfile: eadash.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o eadash.disk.splitfile eadash.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

ldash.disk.splitfile: ldash.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ldash.disk.splitfile ldash.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

adash.cache.cpp: adash.m
	${SRCPATH}mu --cache -b -c adash.m
	mv adash.cpp adash.cache.cpp

eadash.cache.cpp: eadash.m 
	${SRCPATH}mu --cache -b -c eadash.m
	mv eadash.cpp eadash.cache.cpp

ldash.cache.cpp: ldash.m
	${SRCPATH}mu --cache -b -c ldash.m
	mv ldash.cpp ldash.cache.cpp

adash.disk: adash.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o adash.disk adash.disk.cpp -I${INCLUDEPATH} -lm

eadash.disk: eadash.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o eadash.disk eadash.disk.cpp -I${INCLUDEPATH} -lm

ldash.disk: ldash.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o ldash.disk ldash.disk.cpp -I${INCLUDEPATH} -lm

adash.disk.cpp: adash.m
	${SRCPATH}mu --disk -b -c adash.m
	mv adash.cpp adash.disk.cpp

eadash.disk.cpp: eadash.m 
	${SRCPATH}mu --disk -b -c eadash.m
	mv eadash.cpp eadash.disk.cpp

ldash.disk.cpp: ldash.m
	${SRCPATH}mu --disk -b -c ldash.m
	mv ldash.cpp ldash.disk.cpp

clean : 
	rm -f *.cpp adash eadash ldash adash.cache eadash.cache ldash.cache adash.disk eadash.disk ldash.disk adash.cache.splitfile eadash.cache.splitfile ldash.cache.splitfile adash.disk.splitfile eadash.disk.splitfile ldash.disk.splitfile 

