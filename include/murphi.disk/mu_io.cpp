/**CFile***********************************************************************

  FileName    [mu_io.cpp]

  Synopsis    [File for input/output]

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

/****************************************
  There are 4 groups of implementations:
  0) local #define switches
  1) Error_handler class implementation
  2) argclass implementation
  3) general printing routine (not belong to any class)
  4) trace info file
  
  to set default options, set parameter at
  argclass::argclass(...)
  ****************************************/

/****************************************
  #defines for switches to the program.
  ****************************************/

#include <ctype.h>
#include <time.h>

// General
#define HELP_FLAG       "-h"	/* for help list. */
#define LICENSE_FLAG "-l"	/*  print license. */

// Verification Strategy
#define SIMULATE_FLAG   "-s"	/* simulate instead of verifying. */
#define VERIFY_FLAG     "-v"	/* verify with breadth-first search. */
#define VERIFY_BFS_FLAG "-vbfs"	/* Ditto. */
#define VERIFY_DFS_FLAG "-vdfs"	/* verify with depth-first search. */

// main options
#define MEM_MEG_PREFIX  "-m"	/* Memory allotment in Meg. */
#define MEM_K_PREFIX    "-k"	/* Memory allotment in K. */
#define LOOPMAX_PREFIX  "-loop"	/* number of times you can go around a loop. */

// progress
#define VERBOSE_FLAG    "-p"	/* Print every time, with lots of detail. */
#define PRINT_10_FLAG   "-p1"	/* Print progress reports every ten events. */
#define PRINT_100_FLAG  "-p2"	/* Print every hundred. */
#define PRINT_1000_FLAG "-p3"	/* Print every thousand. */
#define PRINT_10000_FLAG "-p4"	/* Every ten thousand. */
#define PRINT_100000_FLAG "-p5"	/* Guess, just guess. */
#define PRINT_NONE_FLAG  "-pn"	/* Don't print progress reports at all. */

// error detection
#define NO_DEADLOCK_FLAG "-ndl"	/* verify without deadlock checking */
#define CONTINUE_AFTER_ERROR_FLAG "-finderrors"	/* verify without stopping at error */
#define MAX_NUM_ERRORS_PREFIX "-errorsmax"	/* verify without stopping at error */

// error trace handling
#define TRACE_VIOLATE_FLAG "-tv"	/* Print a violating trace. */
#define TRACE_DIFF_FLAG  "-td"	/* Print state differences instead of full states. */
#define TRACE_FULL_FLAG "-tf"	/* print full states in traces. */
#define TRACE_ALL_FLAG  "-ta"	/* Print traces containing all states. */
#define TRACE_NONE_FLAG "-tn"	/* no traces. */

// #define TRACE_LONGEST_FLAG "-tl"/* Print the longest trace. */
// I don\'t know that -tl is for (Norris)

// analysis of state space
#define PRINT_RULE_FLAG "-pr"	/* Print out rule information. */
#define PRINT_HASH_FLAG "-ph"	/* Print out hash table. */
// #define PRINT_STATE_FLAG "-ps"  /* "Print start, progress, and final state. "*/

// symmetry
#define NO_SYM_FLAG "-nosym"	/* do not use symmmetry reduction technique */
#define SYMMETRY_PREFIX "-sym"	/* use symmetry reduction technique */
#define NO_MULTISET_FLAG "-nomultiset"	/* do not use multiset reduction technique */
#define PERM_LIMIT "-permlimit"	/* maximum number of permutations wasted on canon */

// debug symmetry
#define TEST1_PREFIX "-testa"	/* use to enter testing parameter */
#define TEST2_PREFIX "-testb"	/* use to enter testing parameter */
#define DEBUG_SYM_FLAG "-debugsym"	/* use to enter testing parameter */

// Uli: hash compaction options
#ifdef HASHC
#if __WORDSIZE == 64
#define NUM_BITS_PREFIX_INFO "-binfo"	// number of bits to store
#endif
#define NUM_BITS_PREFIX     "-b"	// number of bits to store
#define TRACE_DIR_PREFIX    "-d"	// directory for error trace info file
#endif

// just for your information
#define DEFAULT_FLAGS   VERIFY_FLAG PRINT_100_FLAG TRACE_VIOLATE_FLAG

//gdp: Disk Murphi options
#define MAX_LEVEL_PREFIX "-maxl"

/****************************************
  Implementation for the Error class.
  ****************************************/

// make sure that you have executed fflush(stdout) when
// you change from printf to cout, and cout.flush() when
// you change from cout to printf.

// on second thought, I am rewriting everything to only use cout.
// We may well be placing ourselves wholly within the hands of
// flaky ostreams, but we won\'t have weirdnesses with not flushing
// things properly. RLM 7/23/93

void
 Error_handler::Error(const char *fmt ...)
{
  // Uli: assumptions: 
  // - curstate points to the state whose successors are currently being
  //  generated
  // - NumCurState is set to the number of curstate in the trace info file
  // - curstate may not point to workingstate buffer
  // - an error occurred during the generation of one of the successors
  // - for startstates: what_startstate is set correctly

  // we regenerate the trace; this is necessary
  // with symmetry extension, since
  // [s1] -[a]-> [s2] in the hash table does not imply s1-a->s2

  // there are two phases for error reporting with trace printing
  // phase 1) first call to Error(...); error detected and regenerate
  //          trace from the rules recorded in state set.
  //          print trace until the last state
  // phase 2) second call to Error(...); error detected again when 
  //          regenerate the error state; print the last state and
  //          print summary 

  // Uli: in simulation mode call "notrace" version
  if (args->main_alg.mode == argmain_alg::Simulate) {
    cout << "\nStatus:\n\n";
    cout << "\t" << Rules->NumRulesFired()
	<< " rules fired in simulation in " << SecondsSinceStart() <<
	"s.\n";
    // Call to Notrace below originally called Notrace(fmt)
    // without including including the variable argument list of values
    // to be formatted.  We format the error message here in a local
    // buffer (the class variable buffer is reused by Notrace) and pass
    // that to Notrace instead.
    // Thanks to Mark Tuttle
    char buf[1024];
    va_list argp;
    va_start(argp, fmt);
    vsprintf(buf, fmt, argp);
    va_end(argp);
    Notrace(buf);
  }

  static int phase = 1;

  //  unsigned last_rule = what_rule;   // Uli: unsigned short -> unsigned

  // set up error statement in buffer.
  va_list argp;
  va_start(argp, fmt);
  vsprintf(buffer, fmt, argp);
  va_end(argp);

  if (args->print_trace.value) {
    // please print trace

    if (curstate == NULL) {
      // Error when generating startstate

      // header
      cout <<
	  "\nThe following is the error occured during the construction of a startstate:\n\n\t";
      cout << buffer << "\n\n";

      // print fragment of startstate created so far
      cout << "Fragment of startstate " << StartState->LastStateName()
	  << " obtained when the error is found is:\n";
      theworld.print();
      cout << "----------\n\n";

    } else {
      // Error when firing the rule "what_rule"
      // spit into two phases Error reporting

      if (phase == 1) {
	// phase 1 of Error reporting with trace
	phase = 2;

	// header
	cout << "\nThe following is the error trace for the error:\n\n\t";
	cout << buffer << "\n\n";

	// print violate trace
	// the procedure will not return; in fact, it will execute
	// the same rule again and call Error(...) again and enter
	// phase 2 of trace generation
	Reporter->print_trace_with_theworld();
      } else {
	// phase 2 of Error reporting with trace

	if (category == CONDITION) {
	  // print last state
	  cout << "Guard of the rule\n\t" << Rules->LastRuleName()
	      << "\nchecked and caused Error.\n";
	  cout << "----------\n\n";
	} else {
	  // print last state
	  cout << "Rule " << Rules->LastRuleName()
	      << " fired.\n";
	  cout << "The last state of the trace (in full) is:\n";
	  theworld.print();
	  cout << "----------\n\n";
	}

      }
    }

    // print end of trace
    cout << "End of the error trace.\n";

  }
  // section separator 
  cout << "\n====================================="
      << "=====================================\n";

  // print summary of result
  cout << "\nResult:\n\n\t";
  cout << buffer << '\n';
  Reporter->print_summary(FALSE);
  cout.flush();
#ifdef HASHC
  if (TraceFile != NULL)
    delete TraceFile;
#endif

  delete Algorithm;		//gdp: cleanup before error stop. Needed to remove temporary files.
  //maybe I can add this also to std and cached maurphi.


  exit(1);
}

void Error_handler::Deadlocked(const char *fmt ...)
{
  // Uli: assumptions:
  // - curstate points to the state that exposes the error
  // - NumCurState is set to the number of the error state in the trace 
  //  info file
  // - curstate may not point to workingstate buffer

  // set up error statement fmt in argp.
  va_list argp;
  va_start(argp, fmt);
  vsprintf(buffer, fmt, argp);
  va_end(argp);

  // print violate trace
  if (args->print_trace.value) {
    // header
    cout << "\nThe following is the error trace for the error:\n\n\t";
    cout << buffer << "\n\n";

    // trace
    Reporter->print_trace_with_curstate();

    // print end of trace
    cout << "End of the error trace.\n";
  }
  // section separator 
  cout << "\n====================================="
      << "=====================================\n";

  // print summary of result
  cout << "\nResult:\n\n\t";
  cout << buffer << '\n';
  Reporter->print_summary(FALSE);
  cout.flush();
#ifdef HASHC
  if (TraceFile != NULL)
    delete TraceFile;
#endif

  delete Algorithm;		//gdp: cleanup before error stop. Needed to remove temporary files.
  //maybe I can add this also to std and cached maurphi.
  exit(1);
}

void Error_handler::Notrace(const char *fmt ...)
{
  // set up error statement fmt in argp.
  va_list argp;
  va_start(argp, fmt);
  vsprintf(buffer, fmt, argp);
  va_end(argp);

  // print error 
  cout << "\nError:\n\n\t";
  cout << buffer << "\n\n";
  va_end(argp);

  // print progress upto point of error
  if (StateSet != NULL) {	/* queue has been declared */
    Reporter->print_progress(true);	//gdp: force printing
    cout << "\n\n";
  }
  cout.flush();
#ifdef HASHC
  if (TraceFile != NULL)
    delete TraceFile;
#endif

  delete Algorithm;		//gdp: cleanup before error stop. Needed to remove temporary files.
  //maybe I can add this also to std and cached maurphi.

  exit(1);
}

/****************************************
  Implementation for the argclass class for handling runtime arguments.
  ****************************************/

argclass::argclass(int ac, char **av)
:argc(ac),
argv(av),
print_trace(FALSE, "trace printing"),
full_trace(FALSE, "printing diff/full states in trace"),
trace_all(FALSE, "printing all states"),
find_errors(FALSE, "continuing after error"),
max_errors(DEFAULT_MAX_ERRORS, "maximium number of errors"),
mem(DEFAULT_MEM, "memory allocation"),
progress_count(1000, "progress count"),
print_progress(TRUE, "progress printing"),
main_alg(argmain_alg::Verify_bfs, "main algorithm"),
loopmax(DEF_LOOPMAX, "maximium loop count"),
verbose(FALSE, "verbose (whether to print out every action"),
no_deadlock(FALSE, "deadlock detection"), print_options(FALSE, "options printing"), print_license(FALSE, "license printing"),
#if __WORDSIZE == 64
print_64bit_info(FALSE, "64bit hash compaction printing"),
#endif
print_rule(FALSE, "rule information printing"),
print_hash(FALSE, "hashtable information printing"),
symmetry_reduction(TRUE, "symmetry option"),
sym_alg(argsym_alg::Heuristic_Small_Mem_Canonicalize,
	"symmetry algorithm"), perm_limit(10, "permutation limit"),
multiset_reduction(TRUE, "multiset option"), test_parameter1(100,
							     "testing parameter1"),
test_parameter2(100, "testing parameter2"),
#ifdef HASHC
num_bits(DEFAULT_BITS, "stored bits"),	// added by Uli
trace_file(FALSE, "trace info file"),
#endif
debug_sym(FALSE, "debug symmetry"), max_level(0, "max bfs level")	//gdp: initialize disk murphi options
{
  string_iterator *temp = NULL;

  temp = new arg_iterator(ac, av);
  ProcessOptions(temp);
  delete temp;
  temp = NULL;

#ifdef HASHC
  // Uli: do not use trace info file in dfs case
  if (main_alg.mode == argmain_alg::Verify_dfs) {
    if (trace_file.value) {
      delete TraceFile;
      trace_file.reset(FALSE);
    }
  }
  // Uli: check if trace is wanted but cannot be generated
  if (main_alg.mode == argmain_alg::Verify_bfs)
    if (print_trace.value && !trace_file.value)
      Error.Notrace
	  ("Cannot print error trace if you do not specify trace info file.");

  // Uli: set number of bytes in trace info file
  //      cannot be done earlier since number of bits may be unknown
  if (trace_file.value) {
    TraceFile->setBytes(int (num_bits.value));
    print_trace.reset(TRUE);
  }
#endif

  // avoid mixing verbose and progress report
  if (verbose.value)
    print_progress.set(FALSE);

  if (main_alg.mode != argmain_alg::Verify_bfs && find_errors.value)
    // changed by Uli
  {
    Error.Notrace
	("Please use -vbfs for finding multiple errors in single run.");
  }

  if (sym_alg.mode != argsym_alg::Heuristic_Small_Mem_Canonicalize
      && perm_limit.value != 0) {
    perm_limit.set(0);
  }

  if (debug_sym.value)
    symmetry_reduction.reset(FALSE);

  //gdp: how can we redefine gPercentActiveStates here?

  PrintInfo();
}

void argclass::PrintInfo(void)
{
  if (print_license.value)
    PrintLicense();

  cout << "This program should be regarded as a DEBUGGING aid, not as a \n"
      << "certifier of correctness.\n";

  if (!print_license.value)
    cout << "Call with the -l flag or read the license file for terms\n"
	<< "and conditions of use.\n";

  if (!print_options.value)
    cout << "Run this program with \"-h\" for the list of options.\n";

  cout << "\nBugs, questions, and comments should be directed to\n"
      << "\"melatti@di.uniroma1.it\".\n"
      << "\n"
      << "CMurphi compiler last modified date: " << MURPHI_DATE << '\n'
      << "Include files last modified date:    " << INCLUDE_FILE_DATE <<
      '\n' << "=====================================" <<
      "=====================================\n";
  // cout.flush();

  if (print_options.value)
    PrintOptions();
}

void argclass::ProcessOptions(string_iterator * options)
{
  char *option;
  bool no_verification = FALSE;
  unsigned long temp;
  char temp_str[256];

  for (options->start(); !options->done(); options->next()) {
    option = options->value();

//gdp: disk murphi options begin

    if (strncmp(option, MAX_LEVEL_PREFIX, strlen(MAX_LEVEL_PREFIX)) == 0) {
      if (strlen(option) <= strlen(MAX_LEVEL_PREFIX)) {	/* We cannot have a space before the number */
	sscanf(options->nextvalue(), "%s", temp_str);
	if (isdigit(temp_str[0])) {
	  sscanf(temp_str, "%lu", &temp);
	  options->next();
	} else
	  Error.Notrace
	      ("Unrecognized bfs level limit.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      } else {
	sscanf(options->value() + strlen(MAX_LEVEL_PREFIX), "%s",
	       temp_str);
	if (isdigit(temp_str[0]))
	  sscanf(temp_str, "%lu", &temp);
	else
	  Error.Notrace
	      ("Unrecognized bfs level limit.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      }
      max_level.set(temp);
      continue;
    };


//gdp: disk murphi options end

    /* we have to handle memory as a special case. */
    if (strncmp(option, MEM_MEG_PREFIX, 2) == 0) {
      if (strlen(option) <= strlen(MEM_MEG_PREFIX)) {	/* We cannot have a space before the number */
	sscanf(options->nextvalue(), "%s", temp_str);
	if (isdigit(temp_str[0])) {
	  sscanf(temp_str, "%lu", &temp);
	  options->next();
	} else
	  Error.Notrace
	      ("Unrecognized memory size.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      } else {
	sscanf(options->value() + strlen(MEM_MEG_PREFIX), "%s", temp_str);
	if (isdigit(temp_str[0]))
	  sscanf(temp_str, "%lu", &temp);
	else
	  Error.Notrace
	      ("Unrecognized memory size.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      }
      mem.set(temp * 0x100000L);	/* times 1 Meg. */
      continue;
    };
    if (strncmp(option, MEM_K_PREFIX, strlen(MEM_K_PREFIX)) == 0) {
      if (strlen(option) <= strlen(MEM_K_PREFIX)) {	/* We cannot have a space before the number */
	sscanf(options->nextvalue(), "%s", temp_str);
	if (isdigit(temp_str[0])) {
	  sscanf(temp_str, "%lu", &temp);
	  options->next();
	} else
	  Error.Notrace
	      ("Unrecognized memory size.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      } else {
	sscanf(options->value() + strlen(MEM_K_PREFIX), "%s", temp_str);
	if (isdigit(temp_str[0]))
	  sscanf(temp_str, "%lu", &temp);
	else
	  Error.Notrace
	      ("Unrecognized memory size.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      }
      mem.set(temp * 0x400L);	/* times 1 Kilobyte. */
      continue;
    };

#ifdef HASHC
    // added by Uli
    if (strncmp(option, NUM_BITS_PREFIX, strlen(NUM_BITS_PREFIX)) == 0) {
      if (strlen(option) <= strlen(NUM_BITS_PREFIX))
	// there is a space before the number
      {
	sscanf(options->nextvalue(), "%s", temp_str);
	if (isdigit(temp_str[0])) {
	  sscanf(temp_str, "%lu", &temp);
	  options->next();
	} else
	  Error.Notrace("Unrecognized number of bits.", argv[0]);
      } else			// no space
      {
	sscanf(options->value() + strlen(NUM_BITS_PREFIX), "%s", temp_str);
	if (isdigit(temp_str[0]))
	  sscanf(temp_str, "%lu", &temp);
	else
	  Error.Notrace("Unrecognized number of bits.", argv[0]);
      }
      if (temp > 64 || temp < 1)
	Error.Notrace("Number of bits not allowed.");
      num_bits.set(temp);
      continue;
    };

    // added by Uli
    if (strncmp(option, TRACE_DIR_PREFIX, strlen(TRACE_DIR_PREFIX)) == 0) {
      if (strlen(option) <= strlen(TRACE_DIR_PREFIX))
	// there is a space before the filename
      {
	sscanf(options->nextvalue(), "%s", temp_str);
	options->next();
      } else			// no space
      {
	sscanf(options->value() + strlen(NUM_BITS_PREFIX), "%s", temp_str);
      }
      TraceFile = new TraceFileManager(temp_str);
      trace_file.set(TRUE);
      continue;
    };
#if __WORDSIZE == 64
    if (strcmp(option, NUM_BITS_PREFIX_INFO) == 0) {
      print_64bit_info.set(TRUE);
      continue;
    }
#endif
#endif

    if (strncmp(option, LOOPMAX_PREFIX, strlen(LOOPMAX_PREFIX)) == 0) {
      if (strlen(option) <= strlen(LOOPMAX_PREFIX)) {	/* We cannot have a space before the number */
	sscanf(options->nextvalue(), "%s", temp_str);
	if (isdigit(temp_str[0])) {
	  sscanf(temp_str, "%lu", &temp);
	  options->next();
	} else
	  Error.Notrace
	      ("Unrecognized iterations number.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      } else {
	sscanf(options->value() + strlen(LOOPMAX_PREFIX), "%s", temp_str);
	if (isdigit(temp_str[0]))
	  sscanf(temp_str, "%lu", &temp);
	else
	  Error.Notrace
	      ("Unrecognized iterator number.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      }
      loopmax.set(temp);
      continue;
    };
    if (strncmp(option, PERM_LIMIT, strlen(PERM_LIMIT)) == 0) {
      if (strlen(option) <= strlen(PERM_LIMIT)) {	/* We cannot have a space before the number */
	sscanf(options->nextvalue(), "%s", temp_str);
	if (isdigit(temp_str[0])) {
	  sscanf(temp_str, "%lu", &temp);
	  options->next();
	} else
	  Error.Notrace
	      ("Unrecognized permutation limit number.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      } else {
	sscanf(options->value() + strlen(PERM_LIMIT), "%s", temp_str);
	if (isdigit(temp_str[0]))
	  sscanf(temp_str, "%lu", &temp);
	else
	  Error.Notrace
	      ("Unrecognized permutation limit number.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      }
      perm_limit.set(temp);
      continue;
    };
    if (strncmp(option, TEST1_PREFIX, strlen(TEST1_PREFIX)) == 0) {
      if (strlen(option) <= strlen(TEST1_PREFIX))	/* We cannot have a space before the number */
	Error.Notrace
	    ("Unrecognized test parameter 1.  Do '%s -h' for list of valid arguments.",
	     argv[0]);
      else {
	sscanf(options->value() + strlen(TEST1_PREFIX), "%s", temp_str);
	if (isdigit(temp_str[0]))
	  sscanf(temp_str, "%lu", &temp);
	else
	  Error.Notrace
	      ("Unrecognized test parameter 1.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      }
      test_parameter1.set(temp);
      continue;
    };
    if (strncmp(option, TEST2_PREFIX, strlen(TEST2_PREFIX)) == 0) {
      if (strlen(option) <= strlen(TEST2_PREFIX))	/* We cannot have a space before the number */
	Error.Notrace
	    ("Unrecognized test parameter 2.  Do '%s -h' for list of valid arguments.",
	     argv[0]);
      else {
	sscanf(options->value() + strlen(TEST2_PREFIX), "%s", temp_str);
	if (isdigit(temp_str[0]))
	  sscanf(temp_str, "%lu", &temp);
	else
	  Error.Notrace
	      ("Unrecognized test parameter 2.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      }
      test_parameter2.set(temp);
      continue;
    };
    if (strcmp(option, SIMULATE_FLAG) == 0) {
      //gdp: disk murphi is based on the bfs visit!
      Error.Notrace
	  ("Disk can only be used with BFS in this release -- sorry!");
      //main_alg.set(argmain_alg::Simulate);
      //continue;
    }
    if (strcmp(option, VERIFY_FLAG) == 0) {
      main_alg.set(argmain_alg::Verify_bfs);
      continue;
    }
    if (strcmp(option, VERIFY_BFS_FLAG) == 0) {
      main_alg.set(argmain_alg::Verify_bfs);
      continue;
    }
    if (strcmp(option, VERIFY_DFS_FLAG) == 0) {
      //gdp: disk murphi is based on the bfs visit!
      Error.Notrace
	  ("Disk can only be used with BFS in this release -- sorry!");
      //main_alg.set(argmain_alg::Verify_dfs);
      //continue;
    }
    if (strcmp(option, NO_DEADLOCK_FLAG) == 0) {
      no_deadlock.set(TRUE);
      continue;
    }
    if (strcmp(option, CONTINUE_AFTER_ERROR_FLAG) == 0) {
      find_errors.set(TRUE);
      continue;
    }
    if (strncmp
	(option, MAX_NUM_ERRORS_PREFIX,
	 strlen(MAX_NUM_ERRORS_PREFIX)) == 0) {
      if (strlen(option) <= strlen(MAX_NUM_ERRORS_PREFIX)) {
	sscanf(options->nextvalue(), "%s", temp_str);
	if (isdigit(temp_str[0])) {
	  sscanf(temp_str, "%lu", &temp);
	  options->next();
	} else
	  Error.Notrace
	      ("Unrecognized maximum number of errors.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      } else {
	sscanf(options->value() + strlen(MAX_NUM_ERRORS_PREFIX), "%s",
	       temp_str);
	if (isdigit(temp_str[0]))
	  sscanf(temp_str, "%lu", &temp);
	else
	  Error.Notrace
	      ("Unrecognized maximum number of errors.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      }
      max_errors.set(temp);	/* times 1 Meg. */
      continue;
    };
    /* control frequency of printouts. */
    if (strcmp(option, VERBOSE_FLAG) == 0) {
      verbose.set(TRUE);
      continue;
    }
    if (strcmp(option, PRINT_10_FLAG) == 0) {
      progress_count.set(10);
      print_progress.set(TRUE);
      continue;
    }
    if (strcmp(option, PRINT_100_FLAG) == 0) {
      progress_count.set(100);
      print_progress.set(TRUE);
      continue;
    }
    if (strcmp(option, PRINT_1000_FLAG) == 0) {
      progress_count.set(1000);
      print_progress.set(TRUE);
      continue;
    }
    if (strcmp(option, PRINT_10000_FLAG) == 0) {
      progress_count.set(10000);
      print_progress.set(TRUE);
      continue;
    }
    if (strcmp(option, PRINT_100000_FLAG) == 0) {
      progress_count.set(100000);
      print_progress.set(TRUE);
      continue;
    }
    if (strcmp(option, PRINT_NONE_FLAG) == 0) {
      print_progress.set(FALSE);
      continue;
    }
    /* handle trace types. */
    if (strcmp(option, TRACE_VIOLATE_FLAG) == 0) {
      print_trace.set(TRUE);
      continue;
    }
    if (strcmp(option, TRACE_DIFF_FLAG) == 0) {
      print_trace.set(TRUE);
      full_trace.set(FALSE);
      continue;
    }
    if (strcmp(option, TRACE_FULL_FLAG) == 0) {
      print_trace.set(TRUE);
      full_trace.set(TRUE);
      continue;
    }
    if (strcmp(option, TRACE_ALL_FLAG) == 0) {
      print_trace.set(TRUE);
      trace_all.set(TRUE);
      continue;
    }
    if (strcmp(option, TRACE_NONE_FLAG) == 0) {
      print_trace.set(FALSE);
      continue;
    }
    if (strcmp(option, HELP_FLAG) == 0) {
      print_options.set(TRUE);
      no_verification = TRUE;
      continue;
    }
    if (strcmp(option, LICENSE_FLAG) == 0) {
      print_license.set(TRUE);
      continue;
    }
    if (strcmp(option, PRINT_RULE_FLAG) == 0) {
      print_rule.set(TRUE);
      continue;
    }
//       if( strcmp( option, PRINT_HASH_FLAG ) == 0 )
//         {
//        print_hash.set(TRUE);
//           continue;
//         }
//       if( strcmp( option, DEBUG_SYM_FLAG ) == 0 )
//         {
//        debug_sym.set(TRUE);
//           continue;
//         }
    if (strcmp(option, NO_SYM_FLAG) == 0) {
      symmetry_reduction.set(FALSE);
      continue;
    }
    if (strcmp(option, NO_MULTISET_FLAG) == 0) {
      multiset_reduction.set(FALSE);
      continue;
    }
    if (strncmp(option, SYMMETRY_PREFIX, strlen(SYMMETRY_PREFIX)) == 0) {
      if (strlen(option) <= strlen(SYMMETRY_PREFIX))	/* We cannot have a space before the number */
	temp = 1;
      else {
	sscanf(options->value() + strlen(SYMMETRY_PREFIX), "%s", temp_str);
	if (isdigit(temp_str[0]))
	  sscanf(temp_str, "%lu", &temp);
	else
	  Error.Notrace
	      ("Unrecognized symmetry algorithm.  Do '%s -h' for list of valid arguments.",
	       argv[0]);
      }

      symmetry_reduction.set(TRUE);
      switch (temp) {
      case 1:
	sym_alg.set(argsym_alg::Exhaustive_Fast_Canonicalize);
	break;
      case 2:
	sym_alg.set(argsym_alg::Heuristic_Fast_Canonicalize);
	break;
      case 3:
	sym_alg.set(argsym_alg::Heuristic_Small_Mem_Canonicalize);
	break;
      case 4:
	sym_alg.set(argsym_alg::Heuristic_Fast_Normalize);
	break;
      default:
	Error.Notrace
	    ("Unrecognized symmetry algorithm %u.  Do '%s -h' for list of valid arguments.",
	     temp, argv[0]);
      }
      continue;
    };

//       if ( StrStr( ALLOWED_FLAGS, option ) == NULL )
    /* strstr isn\'t in std.h.  Sheesh. And likewise bleah. */
//         {
    Error.Notrace
	("Unrecognized flag %s.  Do '%s -h' for list of valid arguments.",
	 option, argv[0]);
    continue;
//        }
  }
  if (no_verification)
    main_alg.set(argmain_alg::Nothing);
}

void
 argclass::PrintOptions(void)	// changes by Uli
{
  cout << "Options:\n"
      << "1) General:\n"
      << "\t-h            help.\n"
      << "\t-l            print license.\n"
      << "2) Verification Strategy: (default: -v)\n"
      << "\t-s            simulate.\n"
      << "\t-v or -vbfs   verify with breadth-first search.\n"
      << "\t-vdfs         verify with depth-first search.\n"
      << "\t-ndl          do not check for deadlock.\n"
      << "3) Others Options: (default: -m8, -p3, -loop1000)\n"
      << "\t-m<n>         amount of memory for closed hash table in Mb.\n"
      << "\t-k<n>         same, but in Kb.\n"
      << "\t-loop<n>      allow loops to be executed at most n times.\n"
      << "\t-p            make simulation or verification verbose.\n"
      << "\t-p<n>         report progress every 10^n events, n in 1..5.\n"
      << "\t-pn           print no progress reports.\n"
      << "\t-pr           print out rule information.\n"
      << "4) Error Trace Handling: (default: -tn)\n"
      << "\t-tv           write a violating trace (with default -td).\n"
      <<
      "\t-td           write only state differences from the previous states.\n"
      <<
      "\t              (in simulation mode, write only state differences in\n"
      << "\t               verbose mode.)\n" <<
      "\t-tf           write full states in trace.\n" <<
      "\t              (in simulation mode, write full states in verbose mode.)\n"
      << "\t-ta           write all generated states at least once.\n" <<
      "\t-tn           write no trace (default).\n" <<
      "5) Reduction Technique: (default: -sym3 with -permlimit 10 and multiset\n"
      << "                                  reduction)\n" <<
      "\t-nosym        no symmetry reduction (multiset reduction still effective)\n"
      << "\t-nomultiset   no multiset reduction\n" <<
      "\t-sym<n>       reduction by symmetry\n" <<
      "\t-permlimit<n> max num of permutation checked in alg 3\n" <<
      "\t              (for canonicalization, set it to zero)" << "\n" <<
      "\t              n | methods\n" <<
      "\t              -----------------------------------\n" <<
      "\t              1 | exhaustive canonicalize\n" <<
      "\t              2 | heuristic fast canonicalization\n" <<
      "\t                  (can be slower or faster than alg 3 canonicalization)\n"
      <<
      "\t                  (use a lot of auxiliary memory for large scalarsets)\n"
      <<
      "\t              3 | heuristic small mem canonicalization/normalization\n"
      << "\t                  (depends on -permlimit)\n" <<
      "\t              4 | heuristic fast normalization (alg 3 with -permlimit 1)\n"
#ifdef HASHC
      << "6) Hash Compaction: (default: hash compaction with " <<
      DEFAULT_BITS << " bits)\n" <<
      "\t-b<n>         number of bits to store.\n"
#if __WORDSIZE == 64
      <<
      "\t-binfo        maximum available value for -b within the given memory.\n"
#endif
      << "\t-d dir        write trace info into file dir/"
      << PROTOCOL_NAME << TRACE_FILE << ".\n"
#endif
//gdp: disk murphi options begin
      << "7) Disk Usage:\n"
      <<
      "\t-maxl<n>      maximum reachable bfs level. Zero for no limit.\n"
      << "\t              (default is no limit).\n"
//gdp: disk murphi options end
      << "\n";
//  cout.flush();
/*
<< "8) Debug :"
<< "\t-ph           print out hashtable information.\n"
<< "\t-debugsym     run two hashtable in parallel.\n"
<< "\t-test1 <n>    enter test parameter 1.\n"
<< "\t\test2 <n>    enter test parameter 2.\n"
*/
}

void argclass::PrintLicense(void)
{
  cout << "License Notice:\n\n";
  cout << "\
CMurphi is free software; you can redistribute it and/or \n\
modify it under the terms of the GNU Lesser General Public \n\
License as published by the Free Software Foundation; either \n\
of the License, or (at your option) any later version.\n\
\n\
CMurphi is distributed in the hope that it will be useful, \n\
but WITHOUT ANY WARRANTY; without even the implied warranty of \n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU \n\
Lesser General Public License for more details.\n\
\n\
You should have received a copy of the GNU Lesser General Public \n\
License along with this library; if not, write to the Free Software \n\
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA.\n\
\n\
To contact the CMurphi development board, email to <melatti@di.uniroma1.it>\n\
Copyright (C) 2009-2012 by Sapienza University of Rome. \n\
\n\
===========================================================================\n\
";

}

/************************************************************/
/* ReportManager */
/************************************************************/

ReportManager::ReportManager()
{
  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(2);
}

void
 ReportManager::print_algorithm()
{
  switch (args->main_alg.mode) {
  case argmain_alg::Verify_bfs:
    cout << "\nAlgorithm:\n";
    cout << "\tVerification by breadth first search.\n";
#ifdef HASHC
//      cout << "\tWarning: the trace cannot be printed when using\n"
//         << "\thash compression and breadth first search.\n";
#endif
    break;
  case argmain_alg::Verify_dfs:
    cout << "\nAlgorithm:\n";
    cout << "\tVerification by depth first search.\n";
    break;
  case argmain_alg::Simulate:
    cout << "\nAlgorithm:\n";
    cout << "\tSimulation.\n";
    break;
  default:
    break;
  }

  if (args->symmetry_reduction.value
      && (args->main_alg.mode == argmain_alg::Verify_dfs
	  || args->main_alg.mode == argmain_alg::Verify_bfs)) {
    cout << "\twith symmetry algorithm ";
    switch (args->sym_alg.mode) {
    case argsym_alg::Exhaustive_Fast_Canonicalize:
      cout << "1 -- Exhaustive Fast Canonicalization.\n";
      break;
    case argsym_alg::Heuristic_Fast_Canonicalize:
      cout << "2 -- Heuristic Fast Canonicalization.\n";
      break;
    case argsym_alg::Heuristic_Small_Mem_Canonicalize:
      if (args->perm_limit.value == 0) {
	cout << "3 -- Heuristic Small Memory Canonicalization.\n";
	break;
      } else {
	cout << "3 -- Heuristic Small Memory Normalization\n"
	    << "\twith permutation trial limit "
	    << args->perm_limit.value << ".\n";
	break;
      }
    case argsym_alg::Heuristic_Fast_Normalize:
      cout << "4 -- Heuristic Small Memory/Fast Normalization.\n";
      break;
    default:
      cout << "??.\n";
      break;
    }
  }
  if (args->max_level.value > 0) {
    cout << "\tThe maximum bfs level depth is " << args->
	max_level.value << ".\n" <<
	"\t   * Use option \"-maxl\" to increase this, if necessary.\n";
  }
}

// added by Uli
void ReportManager::print_warning()
{
  if ((args->main_alg.mode == argmain_alg::Verify_bfs ||
       args->main_alg.mode == argmain_alg::Verify_dfs) &&
      !args->print_trace.value)
    cout << "\nWarning: No trace will not be printed "
	<< "in the case of protocol errors!\n"
	<<
	"         Check the options if you want to have error traces.\n";
}

void ReportManager::CheckConsistentVersion()
{
  if (strcmp(MURPHI_VERSION, INCLUDE_FILE_VERSION) != 0) {
    cout << "\nWarning:\n\n\t";
    cout << "Different versions of include files and mu are used\n";
  }
}

void ReportManager::StartSimulation()
{
  cout << "Start Simulation :\n\n";
}

/****************************************
  Printing functions.

  Coordinated by class ReportManager
  ****************************************/

/************************************************************/
void ReportManager::print_header(void)	// changes by Uli
{
  cout << "\n====================================="
      << "=====================================\n"
      << MURPHI_VERSION << "\n"
      << "Finite-state Concurrent System Verifier.\n"
      << "\n"
      << MURPHI_VERSION << " is based on various versions of Murphi.\n"
      << MURPHI_VERSION << " :\n"
      <<
      "Copyright (C) 2009-2012 by Sapienza University of Rome.\n"
      << "Murphi release 3.1 :\n" <<
      "Copyright (C) 1992 - 1999 by the Board of Trustees of\n" <<
      "Leland Stanford Junior University.\n" <<
      "\n=====================================" <<
      "=====================================\n" << "\nProtocol: " <<
      PROTOCOL_NAME << "\n";

  // cout.flush(); // flushing cout had seemed to cause some weirdnesses.
}


// since we may use symmetry, which permute entries in the state,
// the pointer in the state set doesn`t exactly point to its
// parent, but to a permutation of its parent.
//
// therefore we have to regenerate the trace from the rules used to
// generate the states

/************************************************************/
/* Norris: to be moved to state set */
void ReportManager::print_trace_with_theworld()	// changes by Uli
{
#ifdef HASHC
  if (args->main_alg.mode == argmain_alg::Verify_bfs &&
      !args->trace_file.value)
    return;
  if (args->trace_file.value)
    StateSet->print_trace_aux(NumCurState);
  else
#endif
    StateSet->print_trace_aux(curstate);

  // execute the last rule to call 
  // Error_handler::Error(...) again, so that
  // variable "theworld" will have the fragment of the last state.
  //StateCopy(workingstate, curstate);
  (void) Rules->AllNextStates();
  Error.Notrace
      ("Internal: The error assertion associated with the last state disappeared.");
}

/************************************************************/
/* Norris: to be moved to state set */
void ReportManager::print_trace_with_curstate()	// changes by Uli
{
#ifdef HASHC
  if (args->main_alg.mode == argmain_alg::Verify_bfs &&
      !args->trace_file.value)
    return;
  if (args->trace_file.value)
    StateSet->print_trace(NumCurState);
  else
#endif
    StateSet->print_trace(curstate);
}

/************************************************************/
/* gdp: When a fatal error occurs, Error_handler::Notrace tries
   to print the progress status just before the error. This is
   useful... but it never prints anything! Why?
   Simply look at the comments on the following lines... this
   function prints a report only every <args->progress_count> 
   new states!!
   Fix: added an optional boolean parameter. When the parameter
   is true, the progress is printed in any case. So Notrace 
   has to call this function with a true parameter and that's all.
*/

void ReportManager::print_progress(bool forceprint)
{
  static bool initialized = FALSE;

  // pring progress report every <args->progress_count> new states found
  if ((forceprint) || (args->print_progress.value
		       && StateSet->NumElts() %
		       args->progress_count.value == 0)) {
    if (!initialized) {
      cout << "\nProgress Report:\n\n";
      initialized = TRUE;
    }
    cout << "\t"
	<< StateSet->NumElts() << " states explored in "
	<< SecondsSinceStart() << "s, with "
	<< Rules->NumRulesFired() << " rules fired and "
	<< StateSet->QueueNumElts() <<
	" states in the queue, states read from disk " << StateSet->
	DiskAlpha() *
	100 << "%" << ", current level " << StateSet->
	CurrentLevel() << ".\n";
    cout.flush();
  }
}

void ReportManager::print_level()
{
  static bool initialized = FALSE;

  if (!initialized) {
    cout << "\nProgress Report:\n\n";
    initialized = TRUE;
  }
  cout << "\n---- begin bfs level " << StateSet->CurrentLevel() << ". "
/*	   
           << StateSet->NumElts() << " states explored in "
	   << SecondsSinceStart() << "s, with "
           << Rules->NumRulesFired() << " rules fired, "
           << StateSet->QueueNumElts() << " states in the queue, collision rate "
           << ((double)StateSet->NumOverwrites() / (double)StateSet->NumElts()) << "."
*/
      << "\n";
  cout.flush();
}



/************************************************************/
void ReportManager::print_no_error(void)
{
  cout << "\n====================================="
      << "=====================================\n"
      << "\nStatus:\n" << "\n\tNo error found.\n";
}

/************************************************************/
void ReportManager::print_summary(bool prob)
{
  bool exist = FALSE;

  time_t finish;
  time(&finish);
  double elapsed_time = difftime(finish, Algorithm->start_time);

  cout << "\nState Space Explored:\n\n"
      << "\t" << StateSet->NumElts() << " states, "
      // Uli: do not print 'reduced states' in official release
      // << StateSet->NumEltsReduced() << " reduced states, "
      << Rules->NumRulesFired() << " rules fired in "
      << SecondsSinceStart() << "s.\n"
      << "\tClock time elapsed (includes disk accesses): " << elapsed_time
      << "s.\n" << "\tLevels Explored: " << StateSet->CurrentLevel() -
      1 << "\n\n";


  if (prob) {
#ifdef HASHC
    // Uli: print omission probabilities
    StateSet->PrintProb();
#endif
  }

  Rules->print_rules_information();
  theworld.print_statistic();


}

// for bfs only -- curstate valid
/************************************************************/
void ReportManager::print_curstate(void)
{
  StateCopy(workingstate, curstate);
  cout << "------------------------------\n"
      << "Unpacking state from queue:\n";
  theworld.print();
  cout << "\nThe following next states are obtained:\n" << '\n';
}

// for dfs only
/************************************************************/
void ReportManager::print_dfs_deadlock(void)
{
  cout << "------------------------------\n"
      << "No more rule can be fired.\n" <<
      "------------------------------\n";
}

// for dfs only
/************************************************************/
void ReportManager::print_retrack(void)
{
  if (!StateSet->QueueIsEmpty()) {
    curstate = StateSet->QueueTop();
    StateCopy(workingstate, curstate);
    cout << "------------------------------\n";
    cout <<
	"No more rule can be fired. Backup one state from the stack:\n";
    theworld.print();
    cout << '\n';
  }
}

/************************************************************/
void ReportManager::print_fire_startstate()
{
  cout << "Firing startstate " << StartState->LastStateName()
      << "\n" << "Obtained state:\n";
  theworld.print();
  cout << '\n';
}

/************************************************************/
void ReportManager::print_fire_rule()
{
  cout << "Firing rule " << Rules->LastRuleName()
      << '\n' << "Obtained state:\n";
  theworld.print();
  cout << '\n';
}

/************************************************************/
void ReportManager::print_fire_rule_diff(state * s)
{
  cout << "Firing rule " << Rules->LastRuleName()
      << '\n' << "Obtained state:\n";
  theworld.print_diff(s);
  cout << '\n';
}

/************************************************************/
void ReportManager::print_trace_all()
{
  static unsigned long statenum = 1;
  cout << "State " << statenum++ << ":\n";
  theworld.print();
  cout << '\n';
}

/************************************************************/
void ReportManager::print_verbose_header()
{
  cout << "\n====================================="
      << "=====================================\n"
      <<
      "Verbose option selected.  The following is the detailed progress.\n\n";
}

/************************************************************/
void ReportManager::print_hashtable()
{
  StateSet->print_all_states();
}

/************************************************************/
void ReportManager::print_final_report()
{
  print_no_error();
  print_summary(TRUE);
  if (args->print_hash.value)
    print_hashtable();
}


/****************************************   // added by Uli
  trace info file
  ****************************************/

#ifdef HASHC
TraceFileManager::TraceFileManager(char *s)
:inBuf(0), last(0)
{
  //assert(sizeof(unsigned long) == 4);	// the implementation is pretty
  // dependent on the 4 bytes

  // check directory
  if (strlen(s) == 0)
    Error.Notrace("No directory for trace info file specified.");
  if (strlen(s) + strlen(PROTOCOL_NAME) + strlen(TRACE_FILE) > 254)
    Error.Notrace("Filename for trace info file too long.");

  // set filename
  strcpy(name, s);
  if (name[strlen(name) - 1] != '/')
    strcat(name, "/");
  char *tmp, *prev, buffer[4096];
  strcpy(buffer, PROTOCOL_NAME);
  tmp = strtok(buffer, "/");
  while (tmp != NULL) {
    prev = tmp;
    tmp = strtok(NULL, "/");
  }
  strcat(name, prev);
  strcat(name, TRACE_FILE);

  // open file
  if ((fp = fopen(name, "w+b")) == NULL)
    Error.Notrace("Problems opening trace info file %s.", name);
}

TraceFileManager::~TraceFileManager()
{
  // delete file
  remove(name);
}

void
 TraceFileManager::setBytes(int bits)
{
  numBytes = (bits - 1) / 8 + 1;
}

unsigned long TraceFileManager::numLast()
{
  return last;
}

// routines for reading and writing
// remarks:
// - format: 4 bytes   for the number of the previous state
//           numBytes  for the compressed value
// - states are numbered beginning with 1

#if __WORDSIZE == 32
void TraceFileManager::writeLong(unsigned long l, int bytes)
#else
void TraceFileManager::writeLong(unsigned int l, int bytes)
#endif
{
  for (int i = 0; i < bytes; i++)
    if (fputc(int (l >> (3 - i) * 8 & 0xffUL), fp) == EOF)
      Error.Notrace("Problems writing to trace info file %s.", name);
}

#if __WORDSIZE == 32
void TraceFileManager::write(unsigned long c1, unsigned long c2,
			     unsigned long previous)
#else
void TraceFileManager::write(unsigned int c1, unsigned int c2,
			     unsigned long previous)
#endif
{
#if __WORDSIZE == 32		/* could also use __WORDSIZE/8 */
  writeLong(previous, 4);
#else
  writeLong((unsigned int)(previous >> 32), 4);
  writeLong((unsigned int)(previous & 0xffffffffUL), 4);
#endif
  writeLong(c1, numBytes > 4 ? 4 : numBytes);
  if (numBytes > 4)
    writeLong(c2, numBytes - 4);
  last++;
}

unsigned long TraceFileManager::readLong(int bytes)
{
  unsigned long ret = 0;
  int g;

  for (int i = 0; i < bytes; i++)
    if ((g = fgetc(fp)) == EOF)
      Error.Notrace("Problems reading from trace info file %s.", name);
    else
#if __WORDSIZE == 32
      ret |= ((unsigned int) g & 0xffUL) << (3 - i) * 8;
#else
      ret |= ((unsigned int) g & 0xffUL) << ((bytes == 8 ? 7 : 3) - i) * 8;
#endif

  return ret;
}

const TraceFileManager::Buffer *
    TraceFileManager::read(unsigned long number)
{
  if (number != inBuf) {
#if __WORDSIZE == 32
    if (fseek(fp, (number - 1) * (4 + numBytes), SEEK_SET))
#else
    if (fseek(fp, (number - 1) * (8 + numBytes), SEEK_SET))
#endif
      Error.Notrace("Problems during seek in trace info file %s.", name);

#if __WORDSIZE == 32
    buf.previous = readLong(4);
    buf.c1 = readLong(numBytes > 4 ? 4 : numBytes);
    if (numBytes > 4)
      buf.c2 = readLong(numBytes - 4);
#else
    buf.previous = readLong(8);
    buf.c1 = (unsigned int) readLong(numBytes > 4 ? 4 : numBytes);
    if (numBytes > 4)
      buf.c2 = (unsigned int) readLong(numBytes - 4);
#endif

    inBuf = number;
  }

  return &buf;
}
#endif
