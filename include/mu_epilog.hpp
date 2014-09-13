/**CHeaderFile*****************************************************************

  FileName    [mu_epilog.hpp]

  Synopsis    [Header file for bodies includes]

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

/****************************************
  header that depend on constants
  which is generated in the middle of the compiled program:
  RULES_IN_WORLD
  ****************************************/
#if defined(PMURPHIK)
#include "murphi.bpctl/mu_util_dep.hpp"
#else
#include "murphi.original/mu_util_dep.hpp"
#endif

/****************************************
  supporting routines
  ****************************************/
#ifdef HASHC
#include "murphi.original/mu_hash.cpp"
#endif


#if defined(DISK_MURPHI)
#include "murphi.disk/mu_util.cpp"
#else
#if defined(PMURPHIK)
#include "murphi.bpctl/mu_util.cpp"
#else
#if defined(NO_HT)
#include "murphi.noht/mu_util.cpp"
#else
#include "murphi.original/mu_util.cpp"
#endif
#endif
#endif

#if defined(DISK_MURPHI)
#include "murphi.disk/mu_io.cpp"
#else
#if defined(CACHED_MURPHI)
#include "murphi.cache/mu_io.cpp"
#else
#if defined(PMURPHIK)
#include "murphi.bpctl/mu_io.cpp"
#else
#if defined(NO_HT)
#include "murphi.noht/mu_io.cpp"
#else
#if defined(TRACE_DFS)
#include "murphi.trace_dfs/mu_io.cpp"
#else
#include "murphi.original/mu_io.cpp"
#endif
#endif
#endif
#endif
#endif

#include "murphi.original/mu_sym.cpp"

#if defined(DISK_MURPHI)
#include "murphi.disk/mu_state.cpp"
#include "murphi.disk/splitFile.cpp"
#include "murphi.disk/mu_filterqueue.cpp"
#include "murphi.disk/mu_system.cpp"
#else
#if defined(CACHED_MURPHI)
#include "murphi.cache/mu_state.cpp"
#include "murphi.cache/mu_system.cpp"
#include "murphi.disk/splitFile.cpp"
#else
#if defined(PMURPHIK)
#include "murphi.disk/splitFile.cpp"
#include "murphi.bpctl/mu_state.cpp"
#include "murphi.bpctl/mu_probstack.cpp"
#include "murphi.bpctl/mu_system.cpp"
#else
#if defined(NO_HT)
#include "murphi.noht/mu_state.cpp"
#include "murphi.noht/mu_system.cpp"
#else
#if defined(TRACE_DFS)
#include "murphi.trace_dfs/mu_state.cpp"
#include "murphi.trace_dfs/mu_system.cpp"
#else
#include "murphi.original/mu_state.cpp"
#include "murphi.original/mu_system.cpp"
#endif
#endif
#endif
#endif
#endif

/****************************************
  real numbers extension
  ****************************************/
#include "murphi.original/mu_real.cpp"	//im

/****************************************
  main routines
  ****************************************/
#if defined(PMURPHIK)
#include "murphi.bpctl/mu_verifier.cpp"
#else
#include "murphi.original/mu_verifier.cpp"
#endif
