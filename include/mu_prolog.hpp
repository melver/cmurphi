/**CHeaderFile*****************************************************************

  FileName    [mu_prolog.hpp]

  Synopsis    [Header file for headers includes]

  Author      [Igor Melatti]

  Copyright   [
  This file is part of the verifier package of CMurphi. 
  Copyright (C) 2009-2012 by Sapienza University of Rome. 

  CMurphi is free software; you can redistribute it and/or 
  modify it under the terms of the GNU Lesser General Public 
  License as published by the Free Software Foundation; either 
  of the License, or (at your option) any later version.

  CMurphi is distributed in the hope that it will be useful, 
  but WITHOUT ANY WARRANTY; without even the implied warranty of 
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public 
  License along with this library; if not, write to the Free Software 
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA.

  To contact the CMurphi development board, email to <melatti@di.uniroma1.it>. ]

******************************************************************************/

#ifdef MTRACE_CHECK
#include <mcheck.h>
#endif

#ifdef __CYGWIN__
#include <bits/wordsize.h>
#endif

/*  Define this macro for pre 2.x G++ versions.
    It controls whether delete has a size argument,
    which is required by old g++ and generates a
    warning in new g++ compilers */

#ifdef OLDGPP
// g++ 1.x
#define OLD_GPP(arg) arg
#else
// g++ 2.x
#define OLD_GPP(arg)
#endif

/****************************************
  Default Value or Constant that can be set by user
 ****************************************/

/* number of times you can go around a while loop. */
#define DEF_LOOPMAX     1000

/* Default memory for Unix. */
#define DEFAULT_MEM     8000000

// Uli: default number of bits for hash compaction and
//      suffix of trace info file
#ifdef HASHC
#define DEFAULT_BITS   40
#define TRACE_FILE     ".trace"
#endif

/* Default Maximum number of error to search when -finderrors is used */
#define DEFAULT_MAX_ERRORS 100

/* the size of search queues as a percentage
   of the maximum number of states */

#if defined(PMURPHIK)
#ifndef gPercentActiveStates
#define gPercentActiveStates 0.5
#endif
#else
#define gPercentActiveStates 0.1
#endif

// for use in tsprintf
#define BUFFER_SIZE 1024

/****************************************
  Release information
 ****************************************/
/* last update */
#define INCLUDE_FILE_DATE "Jul 12 2011"

/* Murphi Version Number */
#define INCLUDE_FILE_VERSION "Caching Murphi Release 5.4.9"

/****************************************
  Cached Murphi constants
 ****************************************/
/* gdp: max length of collision chain in cache */
#define MAX_HT_CHAIN_LENGTH 20
/* gdp: max length of collision chain in cache when hash compaction is used */
#define MAX_HT_CHAIN_LENGTH_HC 13
/* gdp: length of split file segments */
#define SPLITFILE_LEN (1024 * 0x100000L)

/****************************************
  main headers
  ****************************************/

#if defined(PMURPHIK)
#include "murphi.bpctl/mu_verifier.hpp"
#else
#include "murphi.original/mu_verifier.hpp"
#endif

/****************************************
  other headers
  ****************************************/
#ifdef HASHC
#include "murphi.original/mu_hash.hpp"
#endif

#include "murphi.original/mu_sym.hpp"


#if defined(DISK_MURPHI)
#include "murphi.disk/mu_util.hpp"
#elif defined(CACHED_MURPHI)
#include "murphi.cache/mu_util.hpp"
#else
#include "murphi.original/mu_util.hpp"
#endif

#if defined(DISK_MURPHI)
#include "murphi.disk/mu_io.hpp"
#else
#if defined(CACHED_MURPHI)
#include "murphi.cache/mu_io.hpp"
#else
#if defined(PMURPHIK)
#include "murphi.bpctl/mu_io.hpp"
#else
#if defined(NO_HT)
#include "murphi.noht/mu_io.hpp"
#else
#include "murphi.original/mu_io.hpp"
#endif
#endif
#endif
#endif

#if defined(DISK_MURPHI)
#include "murphi.disk/mu_state.hpp"
#include "murphi.disk/splitFile.hpp"
#include "murphi.disk/mu_filterqueue.hpp"
#include "murphi.disk/mu_system.hpp"
#else
#if defined(CACHED_MURPHI)
#include "murphi.disk/splitFile.hpp"
#include "murphi.cache/mu_state.hpp"
#include "murphi.cache/mu_system.hpp"
#else
#if defined(PMURPHIK)
#include "murphi.disk/splitFile.hpp"
#include "murphi.bpctl/mu_state.hpp"
#include "murphi.bpctl/mu_probstack.hpp"
#include "murphi.bpctl/mu_system.hpp"
#else
#if defined(NO_HT)
#include "murphi.noht/mu_state.hpp"
#include "murphi.noht/mu_system.hpp"
#else
#if defined(TRACE_DFS)
#include "murphi.trace_dfs/mu_state.hpp"
#include "murphi.trace_dfs/mu_system.hpp"
#else
#include "murphi.original/mu_state.hpp"
#include "murphi.original/mu_system.hpp"
#endif
#endif
#endif
#endif
#endif

/****************************************
  real numbers extension
  ****************************************/
#include "murphi.original/mu_real.hpp"	//im
