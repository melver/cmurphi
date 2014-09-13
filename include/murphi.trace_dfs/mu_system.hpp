/**CHeaderFile*****************************************************************

  FileName    [mu_system.hpp]

  Synopsis    [Header file for visiting procedures]

  Author      [Igor Melatti]

  Copyright   [
  This file is part of the original verifier package of CMurphi. 
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

/************************************************************/

// Uli: added omission probability calculation & printing

class StateManager {
  state_set *the_states;	// the set of states found.
  state_queue *queue;		// the queue for active states.
  unsigned long NumStates;

  // Uli: for omission probability calculation
  long statesCurrentLevel;	// number of states in the level that
  //  is currently expanded
  long statesNextLevel;		// number of states in the next level
  long currentLevel;		// level that is currently expanded
  //  (startstates: level 0)
  double pno;			// Pr(particular state not omitted)

  double harmonic(double n);	// return harmonic number H_n

public:
   StateManager(bool createqueue, unsigned long NumStates);
  ~StateManager();

  bool Add(state * s, bool valid, bool permanent);
  bool QueueIsEmpty();
  state *QueueTop();
  state *QueueDequeue();
  unsigned NextRuleToTry();	// Uli: unsigned short -> unsigned
  void NextRuleToTry(unsigned r);

  // Uli: routines for omission probability calculation & printing
  void CheckLevel();
  void PrintProb();

  void print_capacity();
  void print_all_states();
  void print_trace(StatePtr p);	// changes by Uli
  void print_trace_aux(StatePtr p);
  unsigned long NumElts();
  unsigned long NumEltsReduced();	// Uli
  unsigned long QueueNumElts();

};

// extern class StartStateGenerator;
class StartStateGenerator;

/************************************************************/
class StartStateManager {
  static unsigned short numstartstates;
  unsigned short what_startstate;	// for info at Error
  StartStateGenerator *generator;
  randomGen random;		// Uli: random number generator
public:
   StartStateManager();
  state *RandomStartState();
  void AllStartStates();
  state *NextStartState();
  state *StartState();
  char *LastStateName();
  char *StateName(StatePtr p);	// changes by Uli
};

// extern class NextStateGenerator;
class NextStateGenerator;

/************************************************************/
class RuleManager {
  unsigned what_rule;		// for execution and info at Error
  unsigned long rules_fired;
  unsigned long *NumTimesFired;	/* array for storing the number
				   of times fired for each rule */
  NextStateGenerator *generator;

  setofrules *EnabledTransition();
  bool AllNextStates(setofrules * fire);
  state *NextState();
  randomGen random;		// Uli: random number generator

  // Vitaly's additions
  int minp;			// Minimum priority among all rules applicable
  // in the current state
  // End of Vitaly's additions

public:
   RuleManager();
  ~RuleManager();
  state *RandomNextState();
  state *SeqNextState();
  bool AllNextStates();
  void ResetRuleNum();
  void SetRuleNum(unsigned r);
  char *LastRuleName();
  unsigned long NumRulesFired();
  void print_rules_information();
  void print_world_to_state(StatePtr p, bool fullstate);
  NextStateGenerator *get_generator() { return generator; }
  // changes by Uli
};

/************************************************************/
class PropertyManager {
  unsigned short what_invariant;	// for info at Error
public:
   PropertyManager();
  bool CheckInvariants();
  const char *LastInvariantName();
};

/************************************************************/
class SymmetryManager {
  state_set *debug_sym_the_states;	// the set of states found without sym.
public:
   SymmetryManager();
};

/************************************************************/
class POManager			// Partial Order
{
  rule_matrix *conflict_matrix;
public:
   POManager();
};

/************************************************************/
class AlgorithmManager {
public:
  AlgorithmManager();
  void verify_bfs();
  void verify_dfs();
  void simulate();
};

/************************************************************/
StartStateManager *StartState;	// manager for all startstate related operation
RuleManager *Rules;		// manager for all rule related operation
PropertyManager *Properties;	// manager for all property related operation
StateManager *StateSet;		// manager for all state related information
SymmetryManager *Symmetry;	// manager for all symmetry information
POManager *PO;			// manager for all symmetry information
ReportManager *Reporter;	// manager for all diagnostic messages
AlgorithmManager *Algorithm;	// manager for all algorithm related issue

Error_handler Error;		// general error handler.
argclass *args;			// the record of the arguments.
state *curstate;		// current state at the beginning of the rule-firing
state *const workingstate = new state;	// Uli: buffer for doing all state
					 //      manipulation
world_class theworld;		// the set of global variables.
int category;			// working on startstate, rule or invariant

#ifdef HASHC
TraceFileManager *TraceFile;	// Uli: manager for trace info file
#endif
unsigned long NumCurState;	// Uli: number of the current state for trace 
			       //      info file
