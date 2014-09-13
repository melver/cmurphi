/**CFile***********************************************************************

  FileName    [mu_system.cpp]

  Synopsis    [File for visiting procedures]

  Author      [Igor Melatti]

  Copyright   [
  This file is part of the disk verifier package of CMurphi. 
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

#ifdef HASHC
#define min(a,b) (((a)<(b))?(a):(b))
#endif

/************************************************************/
/* StateManager */
/************************************************************/
StateManager::StateManager(bool createqueue, unsigned long NumStates)
:NumStates(NumStates),
num_elts(0),
statesCurrentLevel(0), statesNextLevel(0), currentLevel(0), pno(1.0)
{
  unsigned long qsize;

  if (createqueue) {
    queue = new state_filtering_queue(NumStates);
  } else {
    //queue = new state_stack((unsigned long) (gPercentActiveStates * NumStates) );
    Error.Notrace("Sorry, Disk Murphi can only be used with BFS");
  }
}

StateManager::~StateManager()
{

  if (queue != NULL)
    delete queue;
}

bool StateManager::Add(state * s, bool valid, bool permanent)
{
  bool waspresent = queue->enqueue(s);
  unsigned long deleted = queue->deletedstates();
  statesNextLevel -= deleted;
  num_elts -= deleted;

  if (waspresent) {
    num_elts++;

    // Uli: invariant check moved here
    if (!Properties->CheckInvariants()) {
      curstate = s;
#ifdef HASHC
      if (args->trace_file.value)
	NumCurState = TraceFile->numLast();
#endif
      Error.Deadlocked("Invariant \"%s\" failed.",
		       Properties->LastInvariantName());
    }

    if (args->trace_all.value)
      Reporter->print_trace_all();

    statesNextLevel++;
    Reporter->print_progress();
    return TRUE;
  } else
    return FALSE;
}

bool StateManager::QueueIsEmpty()
{
  return queue->isempty();
}

state *StateManager::QueueTop()
{
  return queue->top();
}

state *StateManager::QueueDequeue()
{
  return queue->dequeue();
}

unsigned StateManager::NextRuleToTry()	// Uli: unsigned short -> unsigned
{
  return queue->NextRuleToTry();
}

void StateManager::NextRuleToTry(unsigned r)
{
  queue->NextRuleToTry(r);
}



// -------------------------------------------------------------------------
// Uli: added omission probability calculation & printing


#include <math.h>

double StateManager::harmonic(double n)
// return harmonic number H_n
{
  return (n <
	  1) ? 0 : log(n) + 0.577215665 + 1 / (2 * n) - 1 / (12 * n * n);
}


int StateManager::CheckLevel()
// check if we are done with the level currently expanded
{

#ifdef HASHC
  static double p = 1.0;	// current bound on state omission probability
  static double l = pow(2, double (args->num_bits.value));	// l=2^b
  static double k = -1;		// sum of the number of states - 1
  static double m = NumStates;	// size of the state table
#endif

#if (DBG>10)
//fprintf(stderr, "**CheckLevel(): statesCurrentLevel=%d, statesNextLevel=%d \n",statesCurrentLevel-1, statesNextLevel);
#endif

  if (--statesCurrentLevel <= 0)
    // all the states of the current level have been expanded
  {

    //filter the level states & load the queue
    queue->CheckTable();
    unsigned long deleted = queue->deletedstates();
    statesNextLevel -= deleted;
    num_elts -= deleted;

    // proceed to next level
    statesCurrentLevel = statesNextLevel;
    statesNextLevel = 0;

    // check if there are states in the following level
    if (statesCurrentLevel != 0) {
      currentLevel++;

      //gdp: added to print begin level infos
      Reporter->print_level();

/* gdp: the following two test added for disk murphi */

      if ((args->max_level.value > 0)
	  && (currentLevel > args->max_level.value))
	// stop exploration
      {
	Error.Notrace
	    ("Reached depth %u exceedes max depth %u.\n\tStopping exploration",
	     currentLevel, args->max_level.value);
	return (1);
      }
#ifdef HASHC
      // calculate p_k with equation (2) from FORTE/PSTV paper for
      // the following level
      //k += statesCurrentLevel;
      k = min(m, k + statesCurrentLevel);	//gdp: approx cached algorithm

      double pk = 1 - 2 / l * (harmonic(m + 1) - harmonic(m - k))
	  + ((2 * m) + k * (m - k)) / (m * l * (m - k + 1));
      pno *= pk;
#endif

    }
  }

  return (0);

}				/*  CheckLevel()  */


#ifdef HASHC

void StateManager::PrintProb()
{
  // calculate Pr(not even one omission) with equation (12) from CHARME
  //  paper
  double l = pow(2, double (args->num_bits.value));
  double m = NumStates;
  double n = min(m, /*the_states-> */ NumElts());	//gdp: approx cached algorithm      
  double exp = (m + 1) * (harmonic(m + 1) - harmonic(m - n + 1)) - n;
  double pNO =
      pow(1 - 1 / l,
	  (m + 1) * (harmonic(m + 1) - harmonic(m - n + 1)) - n);



  // print omission probabilities
  cout.precision(6);
  cout << "Omission Probabilities (caused by Hash Compaction):\n\n"
      << "\tPr[even one omitted state]    <= " << 1 - pNO << "\n";
  if (args->main_alg.mode == argmain_alg::Verify_bfs)
    cout << "\tPr[even one undetected error] <= " << 1 - pno << "\n"
	<< "\tDiameter of reachability graph: " << currentLevel -
	1 << "\n\n";
  // remark: startstates had incremented the currentLevel counter
  else
    cout << "\n";
}

#endif

// -------------------------------------------------------------------------

void StateManager::print_capacity()
{
  if (args->main_alg.mode == argmain_alg::Verify_dfs
      || args->main_alg.mode == argmain_alg::Verify_bfs) {
    cout << "\nMemory usage:\n\n";
    cout << "\t* The size of each state is " << BITS_IN_WORLD << " bits "
	<< "(rounded up to " << BLOCKS_IN_WORLD << " bytes).\n";
    //the_states->print_capacity();
    queue->print_capacity();
  }
}

void StateManager::print_all_states()
{
  //the_states->print();
}

unsigned long StateManager::NumElts()
{
  return queue->HistoryLength() + statesNextLevel;	//approx! gdp 
}

unsigned long StateManager::NumEltsReduced()
{
  return queue->HistoryLength();	//gdp
}


void StateManager::print_trace_aux(StatePtr p)	// changes by Uli
{
  state original;
  char *s;

  if (p.isStart()) {
    // this is a startstate
    // expand it into global variable `theworld`
    // StateCopy(workingstate, s);   // Uli: workingstate is set in 
    //      StateName()

    // output startstate
    cout << "Startstate " << (s = StartState->StateName(p))
	<< " fired.\n";
    delete[]s;			// Uli: avoid memory leak
    theworld.print();
    cout << "----------\n\n";
  } else {
    // print the prefix
    print_trace_aux(p.previous());

    // print the next state, which should be equivalent to state s
    // and set theworld to that state.
    // FALSE: no need to print full state
    Rules->print_world_to_state(p, FALSE);
  }
}

void StateManager::print_trace(StatePtr p)
{
  // print the prefix 
  if (p.isStart()) {
    print_trace_aux(p);
  } else {
    print_trace_aux(p.previous());

    // print the next state, which should be equivalent to state s
    // and set theworld to that state.
    // TRUE: print full state please;
    Rules->print_world_to_state(p, TRUE);
  }
}


/************************************************************/
/* StartStateManager */
/************************************************************/
StartStateManager::StartStateManager()
{
  generator = new StartStateGenerator;
}

state *StartStateManager::RandomStartState()
{
  what_startstate = (unsigned short) (random.next() % numstartstates);
  return StartState();
}

void StartStateManager::AllStartStates()
{
  state *nextstate = NULL;

  for (what_startstate = 0; what_startstate < numstartstates;
       what_startstate++) {
    nextstate = StartState();	// nextstate points to internal data at theworld.getstate()
    (void) StateSet->Add(nextstate, FALSE, TRUE);
  }
}

state *StartStateManager::NextStartState()
{
  static int next_startstate = 0;
  if (next_startstate >= numstartstates)
    return NULL;
  what_startstate = next_startstate++;
  return StartState();
}

state *StartStateManager::StartState()
{
  state *next_state = NULL;

  category = STARTSTATE;

  // preparation
  theworld.reset();

  // fire state rule
  generator->Code(what_startstate);

  // print verbose message
  if (args->verbose.value)
    Reporter->print_fire_startstate();

  // Uli: invariant check moved

  // Uli: mark as startstate
  workingstate->previous.clear();

  return workingstate;
}

char *StartStateManager::LastStateName()
{
  return generator->Name(what_startstate);
}

char *StartStateManager::StateName(StatePtr p)
{
  state nextstate;
  if (!p.isStart())
    Error.Notrace
	("Internal: Cannot find startstate name for non startstate");
  for (what_startstate = 0; what_startstate < numstartstates;
       what_startstate++) {
    StartState();
    StateCopy(&nextstate, workingstate);

    if (StateEquivalent(&nextstate, p))
      return LastStateName();
  }

//  Norris: it is very funny, but the following code is supposed to work, but it doesn't
//
//   state * nextstate;
//   for(what_startstate=0; what_startstate<numstartstates; what_startstate++)
//     {
//       nextstate = StartState();                  // nextstate points to internal data at theworld.getstate()
//       if (p.compare(nextstate))
//      return LastStateName();
//     }

  Error.Notrace
      ("Internal: Cannot find startstate name for funny startstate");
  return NULL;
}

/************************************************************/
/* RuleManager */
/************************************************************/
RuleManager::RuleManager():rules_fired(0)
{
  NumTimesFired = new unsigned long[RULES_IN_WORLD];
  generator = new NextStateGenerator;

  // initialize check timesfired
  for (int i = 0; i < RULES_IN_WORLD; i++)
    NumTimesFired[i] = 0;
};

RuleManager::~RuleManager()
{
  delete[OLD_GPP(RULES_IN_WORLD)] NumTimesFired;
}

void
 RuleManager::ResetRuleNum()
{
  what_rule = 0;
}

void RuleManager::SetRuleNum(unsigned r)
{
  what_rule = r;
}

state *RuleManager::SeqNextState()
{
  state *ret;

  what_rule = StateSet->NextRuleToTry();

  generator->SetNextEnabledRule(what_rule);

  if (what_rule < numrules) {
    ret = NextState();
    StateSet->NextRuleToTry(what_rule + 1);
    return ret;
  } else
    return NULL;
}

// Uli: un-commented, fixed memory leak
state *RuleManager::RandomNextState()
{
  unsigned PickARule;
  setofrules rulesleft;
  static state *originalstate = new state;	// buffer, for deadlock checking

  // save workingstate
  StateCopy(originalstate, workingstate);

  // setup set of rules to be checked
  rulesleft.includeall();

  // nondeterministically fire rules until a different state is obtained
  // or no rule available
  category = CONDITION;

  while (StateCmp(originalstate, curstate) == 0 && rulesleft.size() != 0) {
    PickARule = (unsigned) (random.next() % rulesleft.size());
    what_rule = rulesleft.getnthrule(PickARule);
    if (generator->Condition(what_rule)) {
      category = RULE;
      generator->Code(what_rule);
    }
    curstate = workingstate;
  }

  // if deadlock occurs
  if (!args->no_deadlock.value && StateCmp(originalstate, curstate) == 0) {
    cout << "\nStatus:\n\n";
    cout << "\t" << rules_fired << " rules fired in simulation in "
	<< SecondsSinceStart() << "s.\n";
    Error.Notrace("Deadlocked state found.");
  }

  rules_fired++;

  // print verbose message
  if (args->verbose.value & !args->full_trace.value)
    Reporter->print_fire_rule_diff(originalstate);
  if (args->verbose.value & args->full_trace.value)
    Reporter->print_fire_rule();

  if (!Properties->CheckInvariants()) {
    cout << "\nStatus:\n\n";
    cout << "\t" << rules_fired << " rules fired in simulation in "
	<< SecondsSinceStart() << "s.\n";
    Error.Notrace("Invariant %s failed.", Properties->LastInvariantName());
  }
  // progress report
  if (!args->verbose.value
      && rules_fired % args->progress_count.value == 0) {
    cout << "\t" << rules_fired << " rules fired in simulation in " <<
	SecondsSinceStart() << "s.\n";
    cout.flush();
  }
  return curstate;
}

bool RuleManager::AllNextStates()
{
  setofrules *fire;

  // get set of rules to fire
  fire = EnabledTransition();

  // generate the set of next states
  return AllNextStates(fire);
}

/****************************************
  Generate set of transitions to be made:
  setofrules transitionset_enabled()
  -- future extension
  -- setofrules transitionset_sleepset_rr(sleepset s)
  -- setofrules transitionset_gode_dl(setofrules rs)
  ****************************************/
setofrules *RuleManager::EnabledTransition()
{
  static setofrules ret;
  int p;			// Priority of the current rule

  ret.removeall();

  // record what kind of analysis is currently carried out
  category = CONDITION;

  // Minimum priority among all rules
  minp = INT_MAX;
  // get enabled
  for (what_rule = 0; what_rule < numrules; what_rule++) {
    generator->SetNextEnabledRule(what_rule);
    if (what_rule < numrules) {
      ret.add(what_rule);

      // Compute minimum priority
      if ((p = generator->Priority(what_rule)) < minp)
	minp = p;
    }
  }
  return &ret;
}

/****************************************
  The BFS verification supporting routines:
  void generate_startstateset()
  bool generate_nextstateset_standard(setofrules fire)
  -- future extension
  -- bool generate_nextstateset_sym() 
  -- bool generate_nextstateset_gode_dl() 
  -- bool generate_nextstateset_sleepset_rr(setofrules fire, sleepset cursleepset)
  -- bool generate_nextstateset_gode_sleepset_dl(sleepset cursleepset)
  ****************************************/

// Uli: corrected a memory-leak, improved performance
bool RuleManager::AllNextStates(setofrules * fire)
{
  // this will unconditionally fire rule in "fire"
  // please make sure the conditions are true for the rules in "fire"
  // before calling this function.

  static state *originalstate = new state;	// buffer for workingstate
  state *nextstate;
  bool deadlocked_so_far = TRUE;
  bool permanent;

  StateCopy(originalstate, workingstate);	// make copy of workingstate

  /*
     for ( what_rule=0; what_rule<numrules; what_rule++)
     {
     if (generator->Condition(what_rule) !=
     fire->in(what_rule)) {
     if (!fire->in(what_rule)) {
     cout << "Condition for rule " << what_rule << " is true ";
     cout << "but it is not in fire!\n";
     exit(89);
     }
     else {
     cout << "Rule " << what_rule << " is in fire ";
     cout << "but its condition is false!\n";
     exit(99);
     }
     }
     }
   */

  for (what_rule = 0; what_rule < numrules; what_rule++) {
    if (fire->in(what_rule) && generator->Priority(what_rule) <= minp)
      // if (fire->in(what_rule) )
    {
      //get the state reached by the rule what_rule
      nextstate = NextState();

      //if we are not looping, try to add the new state to the bfs queue
      if (StateCmp(curstate, nextstate) != 0) {
	deadlocked_so_far = FALSE;
	permanent = (generator->Priority(what_rule) < 50);	// Uli
	(void) StateSet->Add(nextstate, TRUE, permanent);
	StateCopy(workingstate, originalstate);	// restore workingstate
      }
    }
  }
  return deadlocked_so_far;
}

// the following global variables have been set:
// theworld, curstate and what_rule
state *RuleManager::NextState()
{

  category = RULE;

  // fire rule
  generator->Code(what_rule);
  rules_fired++;

  // update timesfired record
  NumTimesFired[what_rule]++;

  // print verbose message
  if (args->verbose.value)
    Reporter->print_fire_rule();

  // Uli: invariant check moved
//  if (!Properties->CheckInvariants())
//    {
//      Error.Error("Invariant \"%s\" failed.",Properties->LastInvariantName());
//    }

  // get next state
#ifdef HASHC
  if (args->trace_file.value)
    workingstate->previous.set(NumCurState);
  else
#endif
    workingstate->previous.set(curstate);
  return workingstate;
}

void RuleManager::print_world_to_state(StatePtr p, bool fullstate)
{
  state original;
  state nextstate;
  char *s;

  // save last state
  StateCopy(&original, workingstate);

  // generate next state
  for (what_rule = 0; what_rule < numrules; what_rule++) {
    category = CONDITION;
    if (generator->Condition(what_rule)) {
      category = RULE;
      generator->Code(what_rule);
      StateCopy(&nextstate, workingstate);

      if (StateEquivalent(&nextstate, p)) {
	// output the name of the rule and the last state in full
	cout << "Rule "
	    // << rules[ what_rule ].name
	    << (s = generator->Name(what_rule))
	    << " fired.\n";
	delete[]s;		// Uli: avoid memory leak
	if (fullstate)
	  cout << "The last state of the trace (in full) is:\n";
	if (args->full_trace.value || fullstate)
	  theworld.print();
	else
	  theworld.print_diff(&original);
	cout << "----------\n\n";
	return;
      } else
	StateCopy(workingstate, &original);
    }
  }
  Error.Notrace("Internal Error:print_world_to_state().");
}

char *RuleManager::LastRuleName()
{
  return generator->Name(what_rule);
}

unsigned long RuleManager::NumRulesFired()
{
  return rules_fired;
}

void RuleManager::print_rules_information()
{
  bool exist;

  if (args->print_rule.value) {

    cout << "Rules Information:\n\n";
    for (int i = 0; i < RULES_IN_WORLD; i++)
      cout << "\tFired " << NumTimesFired[i] << " times\t- Rule \""
	  << generator->Name(i)
	  << "\"\n";
  } else {
    for (int i = 0; i < RULES_IN_WORLD; i++)
      if (NumTimesFired[i] == 0)
	exist = TRUE;
    if (exist)
      cout << "Analysis of State Space:\n\n"
	  << "\tThere are rules that are never fired.\n"
	  <<
	  "\tIf you are running with symmetry, this may be why.  Otherwise,\n"
	  <<
	  "\tplease run this program with \"-pr\" for the rules information.\n";
  }
}

/************************************************************/
/* PropertyManager */
/************************************************************/
PropertyManager::PropertyManager()
{
}

bool PropertyManager::CheckInvariants()
{
  category = INVARIANT;
  for (what_invariant = 0; what_invariant < numinvariants;
       what_invariant++) {
    if (!(*invariants[what_invariant].condition) ())
      /* Uh oh, invariant blown. */
    {
      return FALSE;
    }
  }
  return TRUE;
}

const char *PropertyManager::LastInvariantName()
{
  return invariants[what_invariant].name;
}

/************************************************************/
/* SymmetryManager */
/************************************************************/
SymmetryManager::SymmetryManager()
{
}

/************************************************************/
/* POManager */
/************************************************************/
POManager::POManager()
{
}

/************************************************************/
/* AlgorithmManager */
/************************************************************/
AlgorithmManager::AlgorithmManager()
{
  // why exists? (Norris)
  // oldnh = set_new_handler(&err_new_handler);

  // create managers
  StartState = new StartStateManager;
  Rules = new RuleManager;
  Properties = new PropertyManager;
  Symmetry = new SymmetryManager;
  PO = new POManager;
  Reporter = new ReportManager;

#ifdef HASHC
  h3 = new hash_function(BLOCKS_IN_WORLD);
#endif

  Reporter->CheckConsistentVersion();
  if (args->main_alg.mode != argmain_alg::Nothing)
    Reporter->print_header();
  Reporter->print_algorithm();

  switch (args->main_alg.mode) {
  case argmain_alg::Verify_bfs:
    StateSet =
	new StateManager(TRUE, NumStatesGivenBytes(args->mem.value));
    StateSet->print_capacity();
    break;
  case argmain_alg::Verify_dfs:
    StateSet =
	new StateManager(FALSE, NumStatesGivenBytes(args->mem.value));
    StateSet->print_capacity();
    break;
  case argmain_alg::Simulate:
    StateSet = NULL;
    break;
  default:
    break;
  }

  Reporter->print_warning();

  signal(SIGFPE, &catch_div_by_zero);

};

//gdp: Added AlgorithmManager destructor 
AlgorithmManager::~AlgorithmManager()
{
  delete StartState;
  delete Rules;
  delete Properties;
  delete Symmetry;
  delete PO;
  delete Reporter;

#ifdef HASHC
  delete h3;
#endif

  if (StateSet != NULL)
    delete StateSet;
};


/****************************************
  The BFS verification main routines:
  void verify_bfs_standard()
  -- future extension:
  -- void verify_bfs_gode_dl()
  -- void verify_bfs_sleepset_rr()
  -- void verify_bfs_gode_sleepset_dl()
  ****************************************/
void
 AlgorithmManager::verify_bfs()
{
  // Use Global Variables: what_rule, curstate, theworld, queue, the_states
  setofrules fire;		// set of rule to be fired
  bool deadlocked;		// boolean for checking deadlock

  // print verbose message
  if (args->verbose.value)
    Reporter->print_verbose_header();

  cout.flush();
  time(&start_time);

  theworld.to_state(NULL);	// trick : marks variables in world

  // Generate all start state
  StartState->AllStartStates();

  // omission probability calculation 
  //gdp: ...and level monitoring 
  StateSet->CheckLevel();

  // search state space
  while (!StateSet->QueueIsEmpty()) {
    // get and remove a state from the queue
    // please make sure that global variable curstate does not change 
    // throughout the iteration 
    curstate = StateSet->QueueDequeue();
    NumCurState++;
    StateCopy(workingstate, curstate);

    // print verbose message
    if (args->verbose.value)
      Reporter->print_curstate();

    // generate all next state 
    deadlocked = Rules->AllNextStates();

    // check deadlock 
    if (deadlocked && !args->no_deadlock.value)
      Error.Deadlocked("Deadlocked state found.");

    // omission probability calculation
    //gdp: ...and level monitoring
    if (StateSet->CheckLevel() != 0)
      /* stop visit */
    {
      break;
    }
  }				// while


  Reporter->print_final_report();


}

/****************************************
  The DFS verification routine:
  void verify_dfs()
  -- not changed yet 
  ****************************************/

//gdp: NOTE THAT DISK MURPHI CURRENTLY DOES NOT HANDLE DFS VERIFICATION
//     THEREFORE, THIS METHOD WILL BE NEVER CALLED

void AlgorithmManager::verify_dfs()
{
  // use global variables: what_rule, curstate, theworld, queue, the_states
  state *nextstate;
  bool deadlocked_so_far = TRUE;

  // print verbose message
  if (args->verbose.value)
    Reporter->print_verbose_header();

  theworld.to_state(NULL);	// trick : marks variables in world

  // for each startstate start a DFS search
  while ((curstate = StartState->NextStartState()) != NULL) {
    (void) StateSet->Add(curstate, FALSE, TRUE);

    while (!StateSet->QueueIsEmpty()) {
      // get the last state from the stack
      curstate = StateSet->QueueTop();
      StateCopy(workingstate, curstate);

      // l) method:
      // get a different next state by incrementing what_rule
      // until a rule is enabled and the new state is different from the
      // old state or all the rules are exhausted
      // 2) setting of varibles
      // what_rule is set by previous iteration
      // curstate is set at the beginning of the iteration
      // theworld is set at the beginning of the iteration

      // get next rule that is enabled and fire it
      // set global variable what_rule

      nextstate = Rules->SeqNextState();

      if (nextstate != NULL) {
	if (StateCmp(curstate, nextstate) != 0) {
	  // curstate state does not deadlock
	  deadlocked_so_far = FALSE;

	  // check if the next state has been searched or not
	  if (StateSet->Add(nextstate, TRUE, TRUE)) {
	    // curstate state does not deadlock, but the next state might
	    deadlocked_so_far = TRUE;
	  } else {
	    // a rule has been fired and the next state has been searched
	    // ==> check next rule
	    if (args->verbose.value)
	      cout << "This state has been examined, try another rule.\n";
	  }
	} else if (args->verbose.value)
	  cout << "This state has been examined, try another rule.\n";
      } else {
	// check deadlock
	if (deadlocked_so_far && !args->no_deadlock.value) {
	  if (args->verbose.value)
	    Reporter->print_dfs_deadlock();
	  Error.Deadlocked("Deadlocked state found.");
	}
	// remove explored state
	(void) StateSet->QueueDequeue();

	// print verbose message
	if (args->verbose.value)
	  Reporter->print_retrack();

	// previous state does not deadlock, as it gives the state just removed
	deadlocked_so_far = FALSE;


#ifdef HASHC
	delete curstate;
#endif
      }				// if
    }				// while

    // print verbose message
    if (args->verbose.value)
      cout << "------------------------------\n"
	  << "Finished working on one statestate.\n"
	  << "------------------------------\n";
  }				// for
  Reporter->print_final_report();
}

/****************************************
  The simulation main routine:
  void simulate()
  ****************************************/

//gdp: NOTE THAT DISK MURPHI CURRENTLY DOES NOT HANDLE SIMULATION
//     THEREFORE, THIS METHOD WILL BE NEVER CALLED

// Uli: added required call to theworld.to_state()
void AlgorithmManager::simulate()
{
  // progress report must be printed out so as to make sense 
  // otherwise, if there is no bug, the program just run on for ever
  // without any message.

  // print verbose message
  if (args->verbose.value)
    Reporter->print_verbose_header();

  Reporter->StartSimulation();

  theworld.to_state(NULL);	// trick: marks variables in world

  // GetRandomStartState will choose a Startstate randomly
  curstate = StartState->RandomStartState();

  // simulate
  while (1) {
    // SimulateRandomRule always executes a rule that leads to
    // a different state.
    curstate = Rules->RandomNextState();
  }
}
