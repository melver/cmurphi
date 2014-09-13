/**CHeaderFile*****************************************************************

  FileName    [mu_verifier.hpp]

  Synopsis    [Header file for main]

  Author      [Igor Melatti]

  Copyright   [
  This file is part of the BPCTL verifier package of CMurphi. 
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
  Include library
 ****************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>
//#include <values.h> /* for BITSPERBYTE and BITS() */
// Uli: values.h is obsolete, replaced by limits.h
#include <limits.h>
#include <signal.h>		/* To trap division by zero. */
#include <assert.h>
#include <float.h>		//AP: included for FP information
#include <math.h>		//IM: for floating point functions
#include <sys/times.h>
using namespace std;

#if 0
/****************************************   // added by Uli
  C Objects
 ****************************************/

extern "C" int remove(const char *filename);
#endif

// GDP, ET : Needed for Red Hat 7.1
#ifdef SYSCONF_RDCL
extern "C" long sysconf(int name);
#endif


/****************************************
  General Constants
 ****************************************/

#define FALSE 0
#define TRUE 1
#define mu_false 0
#define mu_true 1
#define BIT_BLOCK unsigned char	/* type of an element for a bit vector. */

// Uli: replace the BITS() macro from values.h
#ifndef BITS
#define BITS(type) ((int)sizeof (type) * CHAR_BIT)
#endif

//typedef char bool;
typedef void (*proc) (void);
typedef bool(*boolfunc) (void);

struct tms aux_time;

struct rulerec {
  const char *name;
  boolfunc condition;
  proc code;
  bool unfair;
  double prob_bound;		//AP: probability bound on neverclaim
};

/* IM: type definitions for PCTL formulas */
enum pctl_type
    { UNTIL_PCTL, NEXT_PCTL, AP_PCTL, AND_PCTL, OR_PCTL, IMPL_PCTL,
NOT_PCTL };

enum pctl_ord { PCTL_L, PCTL_LEQ, PCTL_G, PCTL_GEQ };

struct pctlformrec {		//IM: record for PCTL formula
  pctl_type type;
  boolfunc condition;
  pctl_ord ord;
  double prob_bound;
  unsigned until_bound;
  const struct pctlformrec *subf1, *subf2;
};

#ifndef ALIGN
typedef struct {
  int longoffset;		/* offset in the state vector, on long boundary */
  unsigned int mask1, mask2;	/* masks for fast access */
  int shift1, shift2;		/* shift values for fast access */
} position;
#endif

/****************************************
  For Liveness
 ****************************************/
enum space { PRE, LEFT, RIGHT };
enum live_type { E, AE, EA, U, AIE, AIU };
struct liverec {
  char *name;
  boolfunc condition_pre;
  boolfunc condition_left;
  boolfunc condition_right;
  live_type livetype;
};


/****************************************
  class declaration
 ****************************************/

// declared in mu_util.h
class mu__int;			/* a base for a value */
class mu_boolean;		/* a base for a boolean */
class world_class;		/* class for variables in expanded state */
class state_queue;		/* class for search queue for bfs */
class state_stack;		/* class for search queue for dfs */
class state_set;		/* hash table for storing state examined */

// declared in mu_io.h
class Error_handler;		/* class for error handling */
class argclass;			/* class for handling command line argument */

// declared in here
class dynBitVec;		/* class for bit vector , state */

// declared in mu_dep.h
class state;			/* a state in the state graph -- a bit vector */
class state_L;			/* a state in the state graph for liveness -- with more info */
class setofrules;		/* class to store a set of rules */
class sleepset;			/* sleepset for partial order reduction technique */
class rule_matrix;		/* class for square matrix of dimension numrules */

/****************************************
  external variables
 ****************************************/

// from murphi code
// extern const rulerec rules[];
extern const unsigned numrules;	// Uli: unsigned short -> unsigned
extern const rulerec startstates[];
extern const unsigned short numstartstates;
extern const rulerec invariants[];
extern const unsigned short numinvariants;
extern const rulerec fairnesses[];
extern const unsigned short numfairnesses;
extern const liverec livenesses[];
extern const unsigned short numlivenesses;

#define STARTSTATE 0
#define CONDITION 1
#define RULE 2
#define INVARIANT 3

class StartStateManager;
class RuleManager;
class PropertyManager;
class StateManager;
class SymmetryManager;
class POManager;
class ReportManager;
class AlgorithmManager;

extern StartStateManager *StartState;	// manager for all startstate related operation
extern RuleManager *Rules;	// manager for all rule related operation
extern PropertyManager *Properties;	// manager for all property related operation
extern StateManager *StateSet;	// manager for all state related information
extern SymmetryManager *Symmetry;	// manager for all symmetry information
extern POManager *PO;		// manager for all symmetry information
extern ReportManager *Reporter;	// manager for all diagnostic messages
extern AlgorithmManager *Algorithm;	// manager for all algorithm related issue

extern Error_handler Error;	// general error handler.
extern argclass *args;		// the record of the arguments.
extern state *curstate;		// current state at the beginning of the rule-firing
extern state *const workingstate;	// Uli: this pointer points to a working-
				    //      buffer
extern world_class theworld;	// the set of global variables.
extern int category;		// working on startstate, rule or invariant
