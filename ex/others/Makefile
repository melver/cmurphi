#**MakefileFile***********************************************************************
#
#  FileName    [Makefile]
#
#  Author      [Igor Melatti]
#
#  Copyright   [
#  This file contains the Makefile of others CMurphi example.
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

all: abp arbiter cache3 dp4 dpnew newcache3 abp.disk arbiter.disk cache3.disk dp4.disk dpnew.disk newcache3.disk abp.cache arbiter.cache cache3.cache dp4.cache dpnew.cache newcache3.cache 
splitfile: abp.cache.splitfile arbiter.cache.splitfile cache3.cache.splitfile dp4.cache.splitfile dpnew.cache.splitfile newcache3.cache.splitfile abp.disk.splitfile arbiter.disk.splitfile cache3.disk.splitfile dp4.disk.splitfile dpnew.disk.splitfile newcache3.disk.splitfile 

# rules for compiling
abp: abp.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o abp abp.cpp -I${INCLUDEPATH} -lm

arbiter: arbiter.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o arbiter arbiter.cpp -I${INCLUDEPATH} -lm

cache3: cache3.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3 cache3.cpp -I${INCLUDEPATH} -lm

dp4: dp4.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dp4 dp4.cpp -I${INCLUDEPATH} -lm

dpnew: dpnew.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dpnew dpnew.cpp -I${INCLUDEPATH} -lm

newcache3: newcache3.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newcache3 newcache3.cpp -I${INCLUDEPATH} -lm

abp.cpp: abp.m
	${SRCPATH}mu abp.m

arbiter.cpp: arbiter.m
	${SRCPATH}mu arbiter.m

cache3.cpp: cache3.m 
	${SRCPATH}mu cache3.m

dp4.cpp: dp4.m
	${SRCPATH}mu dp4.m

dpnew.cpp: dpnew.m
	${SRCPATH}mu dpnew.m

newcache3.cpp: newcache3.m
	${SRCPATH}mu newcache3.m

abp.cache: abp.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o abp.cache abp.cache.cpp -I${INCLUDEPATH} -lm

arbiter.cache: arbiter.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o arbiter.cache arbiter.cache.cpp -I${INCLUDEPATH} -lm

cache3.cache: cache3.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3.cache cache3.cache.cpp -I${INCLUDEPATH} -lm

dp4.cache: dp4.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dp4.cache dp4.cache.cpp -I${INCLUDEPATH} -lm

dpnew.cache: dpnew.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dpnew.cache dpnew.cache.cpp -I${INCLUDEPATH} -lm

newcache3.cache: newcache3.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newcache3.cache newcache3.cache.cpp -I${INCLUDEPATH} -lm

abp.cache.splitfile: abp.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o abp.cache.splitfile abp.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

arbiter.cache.splitfile: arbiter.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o arbiter.cache.splitfile arbiter.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

cache3.cache.splitfile: cache3.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3.cache.splitfile cache3.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

dp4.cache.splitfile: dp4.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dp4.cache.splitfile dp4.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

dpnew.cache.splitfile: dpnew.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dpnew.cache.splitfile dpnew.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

newcache3.cache.splitfile: newcache3.cache.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newcache3.cache.splitfile newcache3.cache.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

abp.disk.splitfile: abp.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o abp.disk.splitfile abp.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

arbiter.disk.splitfile: arbiter.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o arbiter.disk.splitfile arbiter.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

cache3.disk.splitfile: cache3.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3.disk.splitfile cache3.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

dp4.disk.splitfile: dp4.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dp4.disk.splitfile dp4.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

dpnew.disk.splitfile: dpnew.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dpnew.disk.splitfile dpnew.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

newcache3.disk.splitfile: newcache3.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newcache3.disk.splitfile newcache3.disk.cpp -I${INCLUDEPATH} -lm -DSPLITFILE

abp.disk: abp.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o abp.disk abp.disk.cpp -I${INCLUDEPATH} -lm

arbiter.disk: arbiter.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o arbiter.disk arbiter.disk.cpp -I${INCLUDEPATH} -lm

cache3.disk: cache3.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o cache3.disk cache3.disk.cpp -I${INCLUDEPATH} -lm

dp4.disk: dp4.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dp4.disk dp4.disk.cpp -I${INCLUDEPATH} -lm

dpnew.disk: dpnew.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o dpnew.disk dpnew.disk.cpp -I${INCLUDEPATH} -lm

newcache3.disk: newcache3.disk.cpp
	${CXX} ${CFLAGS} ${OFLAGS} -o newcache3.disk newcache3.disk.cpp -I${INCLUDEPATH} -lm

abp.cache.cpp: abp.m
	${SRCPATH}mu --cache -b -c abp.m
	mv abp.cpp abp.cache.cpp

arbiter.cache.cpp: arbiter.m
	${SRCPATH}mu --cache -b -c arbiter.m
	mv arbiter.cpp arbiter.cache.cpp

cache3.cache.cpp: cache3.m 
	${SRCPATH}mu --cache -b -c cache3.m
	mv cache3.cpp cache3.cache.cpp

dp4.cache.cpp: dp4.m
	${SRCPATH}mu --cache -b -c dp4.m
	mv dp4.cpp dp4.cache.cpp

dpnew.cache.cpp: dpnew.m
	${SRCPATH}mu --cache -b -c dpnew.m
	mv dpnew.cpp dpnew.cache.cpp

newcache3.cache.cpp: newcache3.m
	${SRCPATH}mu --cache -b -c newcache3.m
	mv newcache3.cpp newcache3.cache.cpp

abp.disk.cpp: abp.m
	${SRCPATH}mu --disk abp.m
	mv abp.cpp abp.disk.cpp

arbiter.disk.cpp: arbiter.m
	${SRCPATH}mu --disk arbiter.m
	mv arbiter.cpp arbiter.disk.cpp

cache3.disk.cpp: cache3.m 
	${SRCPATH}mu --disk cache3.m
	mv cache3.cpp cache3.disk.cpp

dp4.disk.cpp: dp4.m
	${SRCPATH}mu --disk dp4.m
	mv dp4.cpp dp4.disk.cpp

dpnew.disk.cpp: dpnew.m
	${SRCPATH}mu --disk dpnew.m
	mv dpnew.cpp dpnew.disk.cpp

newcache3.disk.cpp: newcache3.m
	${SRCPATH}mu --disk newcache3.m
	mv newcache3.cpp newcache3.disk.cpp

clean : 
	rm -f *.cpp abp arbiter cache3 dp4 dpnew newcache3 abp.disk arbiter.disk cache3.disk dp4.disk dpnew.disk newcache3.disk abp.cache arbiter.cache cache3.cache dp4.cache dpnew.cache newcache3.cache abp.cache.splitfile arbiter.cache.splitfile cache3.cache.splitfile dp4.cache.splitfile dpnew.cache.splitfile newcache3.cache.splitfile abp.disk.splitfile arbiter.disk.splitfile cache3.disk.splitfile dp4.disk.splitfile dpnew.disk.splitfile newcache3.disk.splitfile 

