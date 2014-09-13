/**CHeaderFile*****************************************************************

  FileName    [mu_system.hpp]

  Synopsis    [Header file for visiting procedures]

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

/************************************************************/

// Uli: added omission probability calculation & printing

class StateManager {
  state_set *the_states;	// the set of states found.
  state_probability_queue *queue;	// the queue for active states.
  state_prob_rule_stack *stack;	// the stack for active states.
  path_set *the_paths;
  path *curr_path;
  unsigned curr_act;
  unsigned long NumStates;

  double harmonic(double n);	// return harmonic number H_n

  // Uli: for omission probability calculation
  long statesCurrentLevel;	// number of states in the level that
  //  is currently expanded
  long statesNextLevel;		// number of states in the next level
  long currentLevel;		// level that is currently expanded
  //  (startstates: level 0)
  double pno;			// Pr(particular state not omitted)
  unsigned long num_elts;	//gdp: number of states enququed so far (substitutes the_states->NumElts())

public:
   StateManager(double fraction, unsigned long memory, unsigned horizon);
  ~StateManager();

  aux_cache *subf_cache;	// the cache for already computed subformulas probabilities
  unsigned Add(state * s, double p, bool valid, bool permanent);
  bool QueueIsEmpty();
  state *QueueTop(double &);
  state *QueueDequeue(double &, double &);
  state *QueueDequeue(double &);
  void QueuePush(state *, double, double);
  state *ResetQueue(long);
  double QueueUpdateProb(double);
  double QueueFinalProb();
  double QueueGetProb();
  unsigned NextRuleToTry();	// Uli: unsigned short -> unsigned
  void NextRuleToTry(unsigned r);
  void PrintProbabilitySoFar();
#ifdef BPCTL_PROB_ORD
  unsigned StackRules(unsigned, double &);
  void SetStackRules(unsigned *, double *, int);
#endif

  // Uli: routines for omission probability calculation & printing
  int CheckLevel();
  void PrintProb();

  void print_capacity();
  void print_all_states();
  void print_trace(StatePtr p);	// changes by Uli
  void print_trace_aux(StatePtr p);
  unsigned long NumElts();
  void IncrNumElts();
  unsigned long NumEltsReduced();	// Uli
  unsigned long QueueNumElts() {
    return queue->NumElts();
  } long GetCurrentLevel() {
    return currentLevel;
  }
  void PathAddAction(unsigned act);
  void PathReset();
  short AddPath();
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
  unsigned AllStartStates();
  state *NextStartState();
  state *StartState();
  char *LastStateName();
  double LastStateProb();	//IM: probabilistic counterpart of LastStateName()
  char *StateName(StatePtr p);	// changes by Uli
};

// extern class NextStateGenerator;
class NextStateGenerator;

/************************************************************/
class RuleManager {
  double what_prob;		// IM: probabilistic counterpart of what_rule
  double sim_prob_i, sim_prob_tot;	// IM: for simulation only
  unsigned long rules_fired;
  unsigned long *NumTimesFired;	/* array for storing the number
				   of times fired for each rule */
  unsigned AllNextStates(setofrules * fire);
  randomGen random;		// Uli: random number generator

  unsigned what_rule;		// for execution and info at Error
  NextStateGenerator *generator;

public:
   RuleManager();
  ~RuleManager();
  state *RandomNextState();
  /* moved to the public part */
  setofrules *EnabledTransition();
  state *NextState();
  /* moved to the public part */
  state *SeqNextState(double &);
  unsigned AllNextStates();
  void ResetRuleNum();
  void SetRuleNum(unsigned r);
  void IncRuleNum();
  void ResetSimProb();
  void ResetSimProbTot();
  void IncSimProb(double);
  void IncSimProbTot(double);
  double GetSimProb() {
    return sim_prob_i;
  };
  double GetSimProbTot() {
    return sim_prob_tot;
  };
  unsigned GetRuleNum();
  char *LastRuleName();
  double LastRuleProb();	//IM: double counterpart of LastRuleName()
  unsigned long NumRulesFired();
  void print_rules_information();
  void print_world_to_state(StatePtr p, bool fullstate);
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
private:
  bool verify_bpmc_rec(state *, const pctlformrec *);
  bool evalX(state *, const pctlformrec *);
  bool evalU(state *, const pctlformrec *);
  int NumberUntil(const pctlformrec *, int);
  unsigned stack_size(const pctlformrec *);
  double update_prob_loc(bool, double, double);
  bool may_exit(const pctlformrec *, double, long);
  bool IsExternalFormula(const pctlformrec *);
  double fin_prob;
public:
  double top_fin_prob;
  unsigned SimCounter, BadPathsCounter;
  unsigned max_level;
   AlgorithmManager();
  ~AlgorithmManager();		//im: Added AlgorithmManager destructor 
  void verify_bfs();
  void verify_dfs();
  void simulate();
  void verify_bpmc();
  bool IsSafety();
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
double curstate_p;		// probability of curstate at the beginning of the rule-firing
double E_p = 0;			// probability for error state

state *const workingstate = new state;	// Uli: buffer for doing all state
					 //      manipulation


world_class theworld;		// the set of global variables.
int category;			// working on startstate, rule or invariant

#ifdef HASHC
TraceFileManager *TraceFile;	// Uli: manager for trace info file
#endif
unsigned long NumCurState;	// Uli: number of the current state for trace 
			       //      info file

void stopped(int);		// For CTRL+C
