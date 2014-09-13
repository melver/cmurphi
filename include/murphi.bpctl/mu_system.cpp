/**CFile***********************************************************************

  FileName    [mu_system.cpp]

  Synopsis    [File for visiting procedures]

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
/* StateManager */
/************************************************************/
StateManager::StateManager(double fraction, unsigned long memory,
			   unsigned horizon)
:NumStates(0), stack(NULL)
{
  if (args->simulate_prob.value) {
    curr_path = new path;
    the_paths = new path_set(memory / (DIM_ACT * PATH_LENGTH));
  } else {
    if (args->safety.value) {
      NumStates = memory;
      queue = new state_probability_queue(NumStates);
      stack = NULL;
    } else {
      /* horizon is the number of transitions, here we need the number of states */
      stack =
	  new state_prob_rule_stack((unsigned long) (fraction * memory),
				    horizon + 1);
      subf_cache =
	  new aux_cache(memory - stack->memory_used(), 4 * horizon);
      queue = NULL;
    }
  }
}

StateManager::~StateManager()
{
  if (args->simulate_prob.value) {
    delete curr_path;
    delete the_paths;
  } else {
    if (stack != NULL) {
      delete stack;
      delete subf_cache;
    }
    if (queue != NULL)
      delete queue;
  }
}

short
 StateManager::AddPath()
{
  return the_paths->was_present(curr_path);
}

unsigned StateManager::Add(state * s, double p, bool valid, bool permanent)
{
  if (Properties->CheckInvariants()) {
    E_p += p;
    /* even if the max depth has not been reached, there cases in which we can terminate */
    if ((mu_pctl_formula.ord == PCTL_G && E_p > mu_pctl_formula.prob_bound)
	|| (mu_pctl_formula.ord == PCTL_GEQ
	    && (E_p > mu_pctl_formula.prob_bound
		|| double_equal(E_p, mu_pctl_formula.prob_bound))))
      return 5;			/* formula is valid, level not completed */
    else if ((mu_pctl_formula.ord == PCTL_L
	      && (E_p > mu_pctl_formula.prob_bound
		  || double_equal(E_p, mu_pctl_formula.prob_bound))
	      || (mu_pctl_formula.ord == PCTL_LEQ
		  && E_p > mu_pctl_formula.prob_bound)))
      return 6;			/* formula is not valid, level not completed */
    return 0;			//state not added
  }

  bool notpresent = queue->enqueue(s, p);

  if (notpresent) {
    num_elts++;

    if (args->trace_all.value)
      Reporter->print_trace_all();

    statesNextLevel++;
    if (args->safety.value)
      Reporter->print_progress(currentLevel);
    return 1;
  } else
    return 0;
}

bool StateManager::QueueIsEmpty()
{
  if (stack)
    return stack->isempty();
  else
    return queue->isempty();
}

state *StateManager::QueueTop(double &p)
{
  if (stack)
    return stack->top();
  else
    return queue->top(p);
}

state *StateManager::QueueDequeue(double &p_r, double &p_f)
{
  return stack->pop(p_r, p_f);
}

state *StateManager::QueueDequeue(double &p)
{
  return queue->dequeue(p);
}

state *StateManager::ResetQueue(long level)
{
  stack->reset(level);
}

void StateManager::QueuePush(state * s, double p_r, double p_f)
{
  return stack->push(s, p_r, p_f);
}

double StateManager::QueueFinalProb()
{
  return stack->final_prob();
}

double StateManager::QueueGetProb()
{
  return stack->get_prob();
}

unsigned StateManager::NextRuleToTry()	// Uli: unsigned short -> unsigned
{
  return stack->NextRuleToTry();
}

void StateManager::NextRuleToTry(unsigned r)
{
  stack->NextRuleToTry(r);
}

double StateManager::QueueUpdateProb(double p)
{
  return stack->update_prob(p);
}

void StateManager::PrintProbabilitySoFar()
{
  return stack->print_probability_so_far();
}

void StateManager::PathAddAction(unsigned act)
{
  curr_path->add_action(act, curr_act++);
}

void StateManager::PathReset()
{
  curr_path->reset();
  curr_act = 0;
}

#ifdef BPCTL_PROB_ORD
unsigned StateManager::StackRules(unsigned r, double &p_ret)
{
  return stack->stack_rules(r, p_ret);
}

void StateManager::SetStackRules(unsigned *v, double *p, int dim)
{
  return stack->set_stack_rules(v, p, dim);
}
#endif



// -------------------------------------------------------------------------
// Uli: added omission probability calculation & printing


#include <math.h>

double StateManager::harmonic(double n)
// return harmonic number H_n
{
  return (n <
	  1) ? 0 : log(n) + 0.577215665 + 1 / (2 * n) - 1 / (12 * n * n);
}

// check if we are done with the level currently expanded
int StateManager::CheckLevel()
{
  if (--statesCurrentLevel <= 0)
    // all the states of the current level have been expanded
  {
    //filter the level states & load the queue
    queue->CheckTable();

    // proceed to next level
    statesCurrentLevel = statesNextLevel;
    statesNextLevel = 0;

    // check if there are states in the following level
    if (statesCurrentLevel != 0) {
      currentLevel++;
      if (Algorithm->max_level < currentLevel)
	Algorithm->max_level = currentLevel;
      if (currentLevel > mu_pctl_formula.until_bound) {
	// stop exploration
	if ((mu_pctl_formula.ord == PCTL_G
	     && E_p > mu_pctl_formula.prob_bound)
	    || (mu_pctl_formula.ord == PCTL_GEQ
		&& (E_p > mu_pctl_formula.prob_bound
		    || double_equal(E_p, mu_pctl_formula.prob_bound)))
	    || (mu_pctl_formula.ord == PCTL_L
		&& E_p < mu_pctl_formula.prob_bound)
	    || (mu_pctl_formula.ord == PCTL_LEQ
		&& (E_p < mu_pctl_formula.prob_bound
		    || double_equal(E_p, mu_pctl_formula.prob_bound))))
	  return 3;		/* formula is valid */
	else
	  return 4;		/* formula is not valid */
      }
    }
    Reporter->print_progress(currentLevel, args->fpel.value, true);
  }
  return 0;
}				/*  CheckLevel()  */


#ifdef HASHC
void StateManager::PrintProb()
{
}

#endif

// -------------------------------------------------------------------------

void StateManager::print_capacity()
{
}

void StateManager::print_all_states()
{
}

unsigned long StateManager::NumElts()
{
  if (stack)
    return NumStates;
  else
    return num_elts;		//gdp
}

void StateManager::IncrNumElts()
{
  NumStates++;
}

unsigned long StateManager::NumEltsReduced()
{
  return num_elts - (queue->NumElts() + statesNextLevel);	//gdp
}


void StateManager::print_trace_aux(StatePtr p)	// changes by Uli
{
}

void StateManager::print_trace(StatePtr p)
{
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

unsigned StartStateManager::AllStartStates()
{
  state *nextstate = NULL;
  double sop = (double) 0;	// IM: sum of probability of startstates
  unsigned ret;

  for (what_startstate = 0; what_startstate < numstartstates;
       what_startstate++) {
    sop += startstates[what_startstate].prob_bound;
    nextstate = StartState();	// nextstate points to internal data at theworld.getstate()
    if ((ret =
	 StateSet->Add(nextstate, startstates[what_startstate].prob_bound,
		       FALSE, TRUE)) > 1)
      return ret;
  }
  if (!double_equal(sop, 1.0, false))
    Error.Error("Sum of probability of start states is equal to %le.",
		sop);
  return 0;
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
  if (args->verbose.value > 4 || args->use_verbose_from_state.value)
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

double StartStateManager::LastStateProb()
{
  return startstates[what_startstate].prob_bound;
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
//       nextstate = StartState();                // nextstate points to internal data at theworld.getstate()
//       if (p.compare(nextstate))
//     return LastStateName();
//     }

  Error.Notrace
      ("Internal: Cannot find startstate name for funny startstate");
  return NULL;
}

/************************************************************/
/* RuleManager */
/************************************************************/
RuleManager::RuleManager():rules_fired(0), sim_prob_i(0.0),
sim_prob_tot(0.0)
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

unsigned RuleManager::GetRuleNum()
{
  return what_rule;
}

void RuleManager::IncRuleNum()
{
  what_rule++;
}

void RuleManager::ResetSimProb()
{
  sim_prob_i = 0.0;
}

void RuleManager::ResetSimProbTot()
{
  sim_prob_tot = 0.0;
}

void RuleManager::IncSimProb(double d)
{
  sim_prob_i += d;
}

void RuleManager::IncSimProbTot(double d)
{
  sim_prob_tot += exp(d);
}


state *RuleManager::SeqNextState(double &nextprob)
{
  state *ret;

#ifdef BPCTL_PROB_ORD
  if (numrules == 1) {
#endif
    what_rule = StateSet->NextRuleToTry();	//gets the current rule number from the stack
    //starting from what_rule, finds the next valid rule index (could be also the current one)
    generator->SetNextEnabledRule(what_rule, nextprob);
    if (what_rule < numrules) {
      ret = NextState();
      StateSet->NextRuleToTry(what_rule + 1);	//sets the next rule number on the stack
      return ret;
    } else
      return NULL;
#ifdef BPCTL_PROB_ORD
  } else {			/* more than one rule */
    if (StateSet->StackRules(1, nextprob) == StateSet->StackRules(0, nextprob)) {	/* not ordered */
      /* order and store */
      double ordered_rules_p[numrules], sop = (double) 0;
      unsigned ordered_rules[numrules];
      int i = 0;
      for (what_rule = 0; what_rule < numrules; what_rule++) {
	generator->SetNextEnabledRule(what_rule, nextprob);
	if (what_rule < numrules && nextprob > 0) {
	  ordered_rules_p[i] = nextprob;
	  sop += nextprob;
	  ordered_rules[i++] = what_rule;
	}
      }
      if (!double_equal(sop, 1.0, false)) {
	printf("Starting from state\n");
	theworld.print();
	Error.
	    Error
	    ("Sum of probability of active transitions is equal to %le.",
	     sop);
      }
      Sort(ordered_rules, ordered_rules_p, i);
      StateSet->SetStackRules(ordered_rules, ordered_rules_p, i);
      StateSet->NextRuleToTry(0);	/* probably useless */
    }
    what_rule = StateSet->StackRules(StateSet->NextRuleToTry(), nextprob);
    if (what_rule < numrules) {
      ret = NextState();
      StateSet->NextRuleToTry(StateSet->NextRuleToTry() + 1);
      return ret;
    } else
      return NULL;
  }
#endif
}

state *RuleManager::RandomNextState()
{
  unsigned PickARule;
  setofrules ret;
  static state *originalstate = new state;	// buffer, for deadlock checking
  int i;
  double sop = 0.0;

  // save workingstate
  StateCopy(originalstate, workingstate);

  category = CONDITION;

  what_prob = 0.0;

  ret.removeall();

  // record what kind of analysis is currently carried out
  category = CONDITION;

  // get enabled
  for (what_rule = 0, i = 0; what_rule < numrules; what_rule++) {
    generator->SetNextEnabledRule(what_rule, what_prob);
    if (what_rule < numrules) {
      if (args->int_simulate_prob.value)
	cout << "Rule " << i++ << " with probability " << what_prob <<
	    endl;
      ret.add(what_rule, what_prob);
      sop += what_prob;
    }
  }
  if (!double_equal(sop, 1.0, false)) {
    cout << "Sum of probabilities is " << sop << endl;
    exit(1);
  }

  if (args->int_simulate_prob.value) {
    cout << "Give a number between 0 and " << ret.size() << " (" << ret.
	size() << " to exit): ";
    cout.flush();
    scanf("%u", &PickARule);
    if (PickARule >= ret.size())
      exit(1);
    what_rule = ret.getnthrule(PickARule);
    what_prob = ret.prob(what_rule);
  } else {
    sop = ((double) rand()) / RAND_MAX;
    while (sop >= (double) 0) {
      what_rule = ret.getnthrule(0);
      what_prob = ret.prob(what_rule);
      sop -= what_prob;
    }
  }
  category = RULE;
  generator->Code(what_rule);
  curstate = workingstate;

  rules_fired++;

  if (args->int_simulate_prob.value) {
    // print verbose message
    if (!args->full_trace.value)
      Reporter->print_fire_rule_diff(originalstate, what_prob);
    else
      Reporter->print_fire_rule(what_prob);
  } else if (!args->stat_simulate_prob.value) {
    IncSimProb(log(what_prob));
    StateSet->PathAddAction(what_rule);
  }

  return curstate;
}

unsigned RuleManager::AllNextStates()
{
  setofrules *fire;

  // get set of rules to fire
  fire = EnabledTransition();

  // generate the set of next states
  return AllNextStates(fire);
}

/****************************************
   checks probability sum to be 1, and returns
   next states
  ****************************************/
setofrules *RuleManager::EnabledTransition()
{
  static setofrules ret;
  int p;			// Priority of the current rule
  double sop = (double) 0;	// AP: sum of probability of active transitions

  ret.removeall();

  // record what kind of analysis is currently carried out
  category = CONDITION;

  // get enabled
  for (what_rule = 0; what_rule < numrules; what_rule++) {
    generator->SetNextEnabledRule(what_rule, what_prob);
    if (what_rule < numrules) {
      ret.add(what_rule, what_prob);
      sop += what_prob;
    }
  }
  if (!double_equal(sop, 1.0, false)) {
    printf("Starting from state\n");
    theworld.print();
    Error.
	Error("Sum of probability of active transitions is equal to %le.",
	      sop);
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
unsigned RuleManager::AllNextStates(setofrules * fire)
{
  // this will unconditionally fire rule in "fire"
  // please make sure the conditions are true for the rules in "fire"
  // before calling this function.

  static state *originalstate = new state;	// buffer for workingstate
  state *nextstate;
  unsigned ret = 0;

  StateCopy(originalstate, workingstate);	// make copy of workingstate

  for (what_rule = 0; what_rule < numrules; what_rule++) {
    if (fire->in(what_rule)) {
      /* gdp: save rule probability BEFORE updating the current state
         in NextState(). This is needed since the probability of a rule can be
         a function of the verifier state!
       */
      what_prob = fire->prob(what_rule);
      //get the state reached by the rule what_rule
      nextstate = NextState();

      if ((ret =
	   StateSet->Add(nextstate, curstate_p * what_prob, TRUE,
			 TRUE)) > 1)
	return ret;
      StateCopy(workingstate, originalstate);	// restore workingstate
    }
  }
  return ret;
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
  if (args->verbose.value > 4 || (args->use_verbose_from_state.value &&
				  StateSet->NumElts() >=
				  args->verbose_from_state.value))
    Reporter->print_fire_rule();

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
}

char *RuleManager::LastRuleName()
{
  return generator->Name(what_rule);
}

double RuleManager::LastRuleProb()
{
  return what_prob;
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
	  << "\tThere are rules that are never fired.\n";
    /*<< "\tIf you are running with symmetry, this may be why.  Otherwise,\n"
       << "\tplease run this program with \"-pr\" for the rules information.\n"; */
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
  return mu_pctl_formula.subf2->condition();
}

const char *PropertyManager::LastInvariantName()
{
  return "";
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
  // create managers
  StartState = new StartStateManager;
  Rules = new RuleManager;
  Reporter = new ReportManager;

#ifdef HASHC
  h3 = new hash_function(BLOCKS_IN_WORLD);
#endif

  Reporter->CheckConsistentVersion();
  if (args->main_alg.mode != argmain_alg::Nothing) {
    Reporter->print_header();
    Reporter->print_algorithm();
  }

  if (args->safety.value) {
    StateSet =
	new StateManager(0.0, NumStatesGivenBytes(args->mem.value), 0);
    StateSet->print_capacity();
  } else if (args->int_simulate_prob.value
	     || args->stat_simulate_prob.value) {
    StateSet = NULL;
  } else if (args->simulate_prob.value) {
    StateSet = new StateManager(0.0, args->mem.value, 0);
  }

  Reporter->print_warning();

  signal(SIGFPE, &catch_div_by_zero);

  fin_prob = -1;
  top_fin_prob = 0;
  max_level = 0;
};

//im: Added AlgorithmManager destructor 
AlgorithmManager::~AlgorithmManager()
{
  delete StartState;
  delete Rules;
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
  unsigned ret;
  int clres;

  // print verbose message
  if (args->verbose.value || args->verbose_from_state.value)
    Reporter->print_verbose_header();

  cout.flush();

  theworld.to_state(NULL);	// trick : marks variables in world

  // Generate all start state
  if (ret = StartState->AllStartStates())
    clres = ret;
  else {

    // level monitoring
    StateSet->CheckLevel();

    // search state space
    while (!StateSet->QueueIsEmpty()) {
      // get and remove a state from the queue
      // please make sure that global variable curstate does not change 
      // throughout the iteration 
      curstate = StateSet->QueueDequeue(curstate_p);
      NumCurState++;
      StateCopy(workingstate, curstate);

      // print verbose message
      if (args->verbose.value || args->use_verbose_from_state.value)
	Reporter->print_curstate();

      // generate all next state 
      if ((clres = Rules->AllNextStates()) > 1)
	break;

      // omission probability calculation and level monitoring
      if ((clres = StateSet->CheckLevel()) != 0)
	/* stop visit */
	break;
    }				// while
  }				// else
  printf("The probability of the formula is %.10lg\n", E_p);
  Reporter->print_final_report(clres);
}

/****************************************
  The DFS verification routine:
  void verify_dfs()
  -- not changed yet 
  ****************************************/

void AlgorithmManager::verify_dfs()
{
}

bool AlgorithmManager::IsSafety()
{
  return (mu_pctl_formula.subf2 && mu_pctl_formula.subf2->type == AP_PCTL
	  && mu_pctl_formula.subf1
	  && mu_pctl_formula.subf1->type == AP_PCTL);
}

/****************************************
  The BPMC main verification routine:
  void verify_bpmc()
  ****************************************/

void AlgorithmManager::verify_bpmc()
{
  // print verbose message
  if (args->verbose.value > 4)
    Reporter->print_verbose_header();

  signal(SIGINT, stopped);
  theworld.to_state(NULL);	// trick : marks variables in world

  curstate = StartState->NextStartState();	//only one allowed
  fin_prob = -1;
  bool result = verify_bpmc_rec(curstate, &mu_pctl_formula);
  if (fin_prob != -1)
    printf("The probability of the formula is %.10lg\n", fin_prob);
  if (result)
    Reporter->print_final_report(3);
  else
    Reporter->print_final_report(4);
}

/****************************************
  The BPMC recursive verification routine:
  void verify_bpmc_rec()
  ****************************************/

bool AlgorithmManager::verify_bpmc_rec(state * s, const pctlformrec * f)
{
  switch (f->type) {
  case AP_PCTL:
    StateCopy(workingstate, s);
    return f->condition();
  case AND_PCTL:
    return (verify_bpmc_rec(s, f->subf1) && verify_bpmc_rec(s, f->subf2));
  case OR_PCTL:
    return (verify_bpmc_rec(s, f->subf1) || verify_bpmc_rec(s, f->subf2));
  case IMPL_PCTL:
    return (!verify_bpmc_rec(s, f->subf1) || verify_bpmc_rec(s, f->subf2));
  case NOT_PCTL:
    return (!verify_bpmc_rec(s, f->subf1));
  case NEXT_PCTL:
    return (evalX(s, f));
  case UNTIL_PCTL:
    return (evalU(s, f));
  default:
    Error.Notrace("Internal error: invalid value %d for f->type", f->type);
    return FALSE;
  }
}

bool AlgorithmManager::evalX(state * s, const pctlformrec * f)
{
  setofrules *fire;

  StateCopy(workingstate, s);
  fire = Rules->EnabledTransition();

  static state *originalstate = new state;	// buffer for workingstate
  state *nextstate;

  StateCopy(originalstate, workingstate);	// make copy of workingstate

  double sum = 0.0;
  for (Rules->ResetRuleNum(); Rules->GetRuleNum() < numrules;
       Rules->IncRuleNum()) {
    if (fire->in(Rules->GetRuleNum())) {
      nextstate = Rules->NextState();

      if (verify_bpmc_rec(nextstate, f->subf1))
	sum += fire->prob(Rules->GetRuleNum());

      StateCopy(workingstate, originalstate);	// restore workingstate
    }
  }
  switch (f->ord) {
  case PCTL_L:
    return sum < f->prob_bound;
  case PCTL_LEQ:
    return (sum < f->prob_bound || double_equal(sum, f->prob_bound));
  case PCTL_G:
    return sum > f->prob_bound;
  case PCTL_GEQ:
    return (sum > f->prob_bound || double_equal(sum, f->prob_bound));
  default:
    Error.Notrace("Internal error: invalid value %d for f->ord", f->ord);
    return FALSE;
  }
}

int AlgorithmManager::NumberUntil(const pctlformrec * f, int ret)
{
  if (f->type == UNTIL_PCTL)
    ret++;
  if (f->subf1 != NULL)
    ret = NumberUntil(f->subf1, ret);
  if (f->subf2 != NULL)
    ret = NumberUntil(f->subf2, ret);
  return ret;
}

unsigned AlgorithmManager::stack_size(const pctlformrec * f)
{
  if (f->type != AP_PCTL) {
    unsigned k1 = stack_size(f->subf1);
    unsigned k2 = f->subf2 != NULL ? stack_size(f->subf2) : 0;
    return f->until_bound + (k1 > k2 ? k1 : k2);
  } else
    return 0;
}

double
    AlgorithmManager::update_prob_loc(bool tmp_psi, double globreachprob,
				      double cache_probability)
{
  double mult;

  if (cache_probability != -1.0)
    mult = cache_probability;
  else if (!tmp_psi)
    mult = 0.0;
  else
    mult = 1.0;
  return globreachprob * mult;
}

bool AlgorithmManager::may_exit(const pctlformrec * f, double fin_prob_loc,
				long level)
{
  return (!args->disable_exit.value &&
	  (((f->ord == PCTL_L
	     && (fin_prob_loc > f->prob_bound
		 || double_equal(fin_prob_loc, f->prob_bound)))
	    || (f->ord == PCTL_LEQ && fin_prob_loc > f->prob_bound)
	    || (f->ord == PCTL_G && fin_prob_loc > f->prob_bound)
	    || (f->ord == PCTL_GEQ
		&& (fin_prob_loc > f->prob_bound
		    || double_equal(fin_prob_loc, f->prob_bound)))
	   ) || (level == 0
		 &&
		 ((f->ord == PCTL_L
		   && (fin_prob > f->prob_bound
		       || double_equal(fin_prob_loc, f->prob_bound)))
		  || (f->ord == PCTL_LEQ && fin_prob > f->prob_bound)
		  || (f->ord == PCTL_G && fin_prob > f->prob_bound)
		  || (f->ord == PCTL_GEQ
		      && (fin_prob > f->prob_bound
			  || double_equal(fin_prob_loc, f->prob_bound)))))
	  )
      );
}

bool AlgorithmManager::IsExternalFormula(const pctlformrec * f)
{
  for (int i = 0; i < mu_pctl_top_untils_form_num; i++) {
    if (f == mu_pctl_top_untils_form[i])
      return true;
  }
  return false;
}

/* It works only if there is only one initial state; the final probability of 
the formula will be put in fin_prob */
bool AlgorithmManager::evalU(state * s, const pctlformrec * f)
{
  if (StateSet == NULL) {
    //int number_until = NumberUntil(f, 0);
    double fraction = 1.0 - NumberUntil(f, 0) / 4.0;	/* fraction of memory to be used for the stack */
    //double fraction = 0.7;
    StateSet =
	new StateManager((fraction > 0.5 ? fraction : 0.5),
			 args->mem.value, stack_size(f));
  }
  state_prob_hor_form s_p_h_f(s, 0.0, f->until_bound, f);
  //unsigned ht_chain = 5*f->until_bound;
  bool result;
  if (!StateSet->subf_cache->try_to_evaluate(&s_p_h_f, result)) {
    state *nextstate;

    curstate = s;
    StateCopy(workingstate, curstate);

    if (verify_bpmc_rec(curstate, f->subf2))
      fin_prob = 1.0;
    else if (f->until_bound == 0 || !verify_bpmc_rec(curstate, f->subf1))	/* fixed */
      fin_prob = 0.0;
    else {
      long level = 0;		/* it's long because it refers to the unsigned f->until_bound, but may be -1 */
      double nextprob, globreachprob = 1.0, fin_prob_loc =
	  0.0, globfinprob = 0.0;
      bool tmp_psi, tmp_phi;

      StateSet->IncrNumElts();
      StateSet->QueuePush(s, 1.0, 0.0);

      while (level >= 0) {
	double dummy;

	curstate = StateSet->QueueTop(dummy);
	StateCopy(workingstate, curstate);
	if (args->ctrl_next.value)
	  (void *) Rules->EnabledTransition();
	nextstate = Rules->SeqNextState(nextprob);

	Reporter->print_progress(level, false, false, false, globfinprob);

	/* assumption: it is effectively a Markov Chain */

	if (nextstate != NULL) {
	  s_p_h_f._state = *nextstate;
	  s_p_h_f._horizon = f->until_bound - level - 1;
	  s_p_h_f._subformula = f;
	  s_p_h_f._probability =
	      StateSet->subf_cache->simple_was_present(&s_p_h_f);

	  level++;
	  if (level > Algorithm->max_level && IsExternalFormula(f))
	    Algorithm->max_level = level;
	  globreachprob *= nextprob;
	  if (s_p_h_f._probability == -1.0) {
	    if (!(tmp_psi = verify_bpmc_rec(nextstate, f->subf2))
		&& level != f->until_bound)
	      tmp_phi = verify_bpmc_rec(nextstate, f->subf1);
	    StateSet->QueuePush(nextstate, nextprob, tmp_psi ? 1.0 : 0.0);
	    if (tmp_psi && IsExternalFormula(f)) {
	      globfinprob += globreachprob;
	      top_fin_prob = globfinprob;
	      Reporter->print_progress(level, false, false, true,
				       globfinprob);
	    }
	  } else {
	    StateSet->QueuePush(nextstate, nextprob, s_p_h_f._probability);
	    if (s_p_h_f._probability > (double) 0 && IsExternalFormula(f)) {
	      globfinprob += globreachprob * s_p_h_f._probability;
	      top_fin_prob = globfinprob;
	      Reporter->print_progress(level, false, false, true,
				       globfinprob);
	    }
	  }
	  /* Alternatively, don't push and don't pop below... */
	}

	if (nextstate == NULL
	    || !double_equal(s_p_h_f._probability, -1.0, false)
	    || level == f->until_bound || tmp_psi || !tmp_phi) {
	  double formprob, reachprob;

	  --level;
	  curstate = StateSet->QueueDequeue(reachprob, formprob);
	  fin_prob_loc +=
	      update_prob_loc(tmp_psi, globreachprob,
			      s_p_h_f._probability);
	  globreachprob /= reachprob;
	  if (level != -1) {
	    fin_prob = StateSet->QueueUpdateProb(reachprob * formprob);
	    if (may_exit(f, fin_prob_loc, level)) {
	      curstate = StateSet->ResetQueue(level);
	      StateCopy(workingstate, curstate);	/* to restore nextstate... */
	      fin_prob = fin_prob_loc;
	      return (f->ord == PCTL_G || f->ord == PCTL_GEQ);
	    }
	  }

	  s_p_h_f._probability = formprob;
	  s_p_h_f._state = *curstate;
	  s_p_h_f._horizon = f->until_bound - level - 1;
	  s_p_h_f._subformula = f;
	  if (!StateSet->subf_cache->insert(&s_p_h_f))
	    printf
		("WARNING: Too small cache size, computation may require a lot of time\n");
	  tmp_psi = false;
	  s_p_h_f._probability = -1.0;
	} else
	  StateSet->IncrNumElts();
      }				// while
      fin_prob = StateSet->QueueFinalProb();
      if (args->verbose.value > 1)
	printf("\tThe probability of the formula is %.10lg\n", fin_prob);
    }				// else
    switch (f->ord) {
    case PCTL_L:
      return fin_prob < f->prob_bound;
    case PCTL_LEQ:
      return (fin_prob < f->prob_bound
	      || double_equal(fin_prob, f->prob_bound));
    case PCTL_G:
      return fin_prob > f->prob_bound;
    case PCTL_GEQ:
      return (fin_prob > f->prob_bound
	      || double_equal(fin_prob, f->prob_bound));
    default:
      Error.Notrace("Internal error: invalid value %d for f->ord", f->ord);
      return FALSE;
    }
  }				// try_to_evaluate failed
  else
    return result;		// try_to_evaluate succeeded
}

/****************************************
  The simulation main routine:
  void simulate()
  ****************************************/

// Uli: added required call to theworld.to_state()
void
 AlgorithmManager::simulate()
{
  // progress report must be printed out so as to make sense 
  // otherwise, if there is no bug, the program just run on for ever
  // without any message.

  signal(SIGINT, stopped);

  // print verbose message
  if (args->verbose.value)
    Reporter->print_verbose_header();

  Reporter->StartSimulation();

  BadPathsCounter = 0;

  if (!args->int_simulate_prob.value)
    Rules->ResetSimProbTot();
  for (SimCounter = 1; 1; SimCounter++) {

    theworld.to_state(NULL);	// trick: marks variables in world

    // GetRandomStartState will choose a Startstate randomly
    curstate = StartState->RandomStartState();

    // simulate
    if (args->int_simulate_prob.value) {
      Reporter->print_fire_startstate();
      while (1)
	curstate = Rules->RandomNextState();	/* does exit() when the user has finished */
    } else {
      if (!args->stat_simulate_prob.value) {
	Rules->ResetSimProb();
	StateSet->PathReset();
      }
      for (int i = 1; i < args->simulate_prob.value; i++) {
	curstate = Rules->RandomNextState();	/* the simulation is supposed to be killed */
	if (args->stat_simulate_prob.value) {
	  if (Properties->CheckInvariants()) {
	    BadPathsCounter++;
	    break;
	  }
	} else if (Properties->CheckInvariants() && !StateSet->AddPath()) {
	  Rules->IncSimProbTot(Rules->GetSimProb());
	  break;
	}
      }
      if (SimCounter % 100 == 0) {
	if (!args->stat_simulate_prob.value)
	  cout << "After " << SimCounter << " simulations, probability is "
	      << Rules->GetSimProbTot() << endl;
	else
	  cout << "The probability of the formula is " << ((double)
							   BadPathsCounter)
	      /
	      SimCounter << " basing on " << SimCounter << " simulations"
	      << endl;
	cout.flush();
      }
    }
  }
}

void stopped(int arg)
{
  cout << "Program interrupted.\n";
  if (args->simulate_prob.value) {
    if (!args->stat_simulate_prob.value)
      cout << "After " << Algorithm->
	  SimCounter << " simulations, probability is " << Rules->
	  GetSimProbTot();
    else
      cout << "The probability of the formula is " <<
	  (((double) Algorithm->BadPathsCounter) /
	   Algorithm->SimCounter) << " basing on " << Algorithm->
	  SimCounter << " simulations" << endl;
  } else {
    cout << "The top formula probability so far is ";
    if (Algorithm->IsSafety())
      StateSet->PrintProbabilitySoFar();
    else
      cout << Algorithm->top_fin_prob;
  }
  cout << "\n";
  exit(2);
}
