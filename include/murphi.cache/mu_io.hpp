/**CHeaderFile*****************************************************************

  FileName    [mu_io.hpp]

  Synopsis    [Header file for input/output]

  Author      [Igor Melatti]

  Copyright   [
  This file is part of the caching verifier package of CMurphi. 
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
  There are 3 groups of declarations:
  1) Error_handler
  2) argclass
  3) general printing routine (not belong to any class)
  4) trace info file
 ****************************************/

/****************************************
  Error handler
 ****************************************/

class Error_handler {
  char buffer[BUFFER_SIZE];	// for vsprintf'ing error messages prior to cout'ing them.

  int num_errors;
  int phase;
  int oldphase;
  bool has_error;
  int num_error_curstate;
  int phase_2_done;

public:
   Error_handler()
  :num_errors(0), phase(1) {
  };
  ~Error_handler() {
  };

  void StartCountingCurstate() {
    num_error_curstate = 0;
  }
  int ErrorNumCurstate() {
    return num_error_curstate;
  }
  bool Phase2Done() {
    return phase_2_done;
  }

  void SpecialPhase() {
    oldphase = phase;
    phase = 3;
  };
  void NormalPhase() {
    phase = oldphase;
  };

  void ResetErrorFlag() {
    phase = 3;
    has_error = FALSE;
  }
  bool NoError() {
    return !has_error;
  };

  int NumError() {
    return num_errors;
  };

  void Error(const char *fmt, ...);	/* called like printf. */
  void Deadlocked(const char *fmt, ...);	/* When we\'re not in a rule.
						   currently only in deadlock */
  void Notrace(const char *fmt, ...);	/* Doesn\'t print a trace. */
};

/****************************************
  iterator for argument class
 ****************************************/

/* abstract class for mapping over a list of strings. */
class string_iterator {
  /* restrictions:
   * Also, you can\'t have more than one of these going at a time. */
public:
  virtual char *value() = 0;
  virtual const char *nextvalue() = 0;
  virtual string_iterator & next() = 0;
  virtual bool done() = 0;
  virtual void start() = 0;
};

class arg_iterator:public string_iterator {
  int argc;
  char **argv;
  int index;
public:
   arg_iterator(int argc, char **argv)
  :argc(argc), argv(argv), index(1) {
  };				/* index(1) to skip the program name. */
  virtual char *value() {
    return argv[index];
  };
  virtual const char *nextvalue() {
    if (index + 1 >= argc)
      return "";
    else
      return argv[index + 1];
  };
  virtual string_iterator & next() {
    index++;
    return *this;
  }
  virtual bool done() {
    return (index >= argc);
  }
  virtual void start() {
  };
};

class strtok_iterator:public string_iterator
/* uses strtok() to break up into strings. */
{
  char *old;
  char *current;
public:
   strtok_iterator(char *s)
  :old(s), current(NULL) {
    start();
  };
  virtual char *value() {
    return current;
  };
  virtual string_iterator & next() {
    current = strtok(NULL, " ");
    return *this;
  }
  virtual bool done() {
    return (current == NULL);
  }
  virtual void start() {
    if (old != NULL)
      current = strtok(tsprintf("%s", old), " ");
  };
  /* we can\'t count on strdup() being there, unfortunately. */
};

/****************************************
  argument class
 ****************************************/
class argmain_alg {
public:
  enum MainAlgorithmtype { Nothing, Simulate, Verify_bfs, Verify_dfs };
  MainAlgorithmtype mode;	/* What to do. */
private:
   bool initialized;
  char *name;
public:
   argmain_alg(MainAlgorithmtype t, const char *n):mode(t),
      initialized(FALSE) {
    if (n != NULL) {
      name = new char[strlen(n) + 1];
       strcpy(name, n);
    } else
       name = NULL;
  };
  ~argmain_alg() {
  };
  void set(MainAlgorithmtype t) {
    if (!initialized) {
      initialized = TRUE;
      mode = t;
    } else if (mode != t)
      Error.Notrace("Conflicting options to %s.", name);
  };
};

class argsym_alg {
public:
  enum SymAlgorithmType { Exhaustive_Fast_Canonicalize,
    Heuristic_Fast_Canonicalize,
    Heuristic_Small_Mem_Canonicalize,
    Heuristic_Fast_Normalize
  };
  SymAlgorithmType mode;	/* What to do. */
private:
   bool initialized;
  char *name;
public:
   argsym_alg(SymAlgorithmType t, const char *n):mode(t),
      initialized(FALSE) {
    if (n != NULL) {
      name = new char[strlen(n) + 1];
       strcpy(name, n);
    } else
       name = NULL;
  };
  ~argsym_alg() {
  };
  void set(SymAlgorithmType t) {
    if (!initialized) {
      initialized = TRUE;
      mode = t;
    } else if (mode != t)
      Error.Notrace("Conflicting options to %s.", name);
  };
};

class argnum {
public:
  unsigned long value;
private:
   bool initialized;
  char *name;
public:
   argnum(unsigned long val, const char *n):value(val), initialized(FALSE) {
    if (n != NULL) {
      name = new char[strlen(n) + 1];
       strcpy(name, n);
    } else
       name = NULL;
  };
  ~argnum() {
  };
  void set(unsigned long val) {
    if (!initialized) {
      initialized = TRUE;
      value = val;
    } else if (val != value)
      Error.Notrace("Conflicting options to %s.", name);
  };
};

class argbool {
public:
  bool value;
private:
  bool initialized;
  char *name;
public:
   argbool(bool val, const char *n):value(val), initialized(FALSE) {
    if (n != NULL) {
      name = new char[strlen(n) + 1];
       strcpy(name, n);
    } else
       name = NULL;
  };
  ~argbool() {
  };
  void reset(bool val) {
    initialized = TRUE;
    value = val;
  }
  void set(bool val) {
    if (!initialized) {
      initialized = TRUE;
      value = val;
    } else if (val != value)
      Error.Notrace("Conflicting options to %s.", name);
  };
};

/* Argclass inspired by Andreas\' code. */
class argclass {
  int argc;
  char **argv;
public:

  // trace options
   argbool print_trace;
  argbool full_trace;
  argbool trace_all;
  argbool find_errors;
  argnum max_errors;

  // memory options
  argnum mem;

  // progress report options
  argnum progress_count;
  argbool print_progress;

  // main algorithm options
  argmain_alg main_alg;

  // symmetry option
  argbool symmetry_reduction;
  argbool multiset_reduction;
  argsym_alg sym_alg;
  argnum perm_limit;
  argbool debug_sym;

  // Uli: hash compaction options
#ifdef HASHC
  argnum num_bits;
  argbool trace_file;
#endif

  // testing parameter
  argnum test_parameter1;
  argnum test_parameter2;

  // miscelleneous
  argnum loopmax;
  argbool verbose;
  argbool no_deadlock;
  argbool print_options;
#if __WORDSIZE == 64
  argbool print_64bit_info;
#endif
  argbool print_license;
  argbool print_rule;
  argbool print_hash;

  //gdp: cached murphi options
  argnum max_collrate;		// percent value: 90 -> 90% -> 0.9
  argnum max_level;		//maximum bfs level

  // supporting routines
   argclass(int ac, char **av);
  ~argclass() {
  };
  void ProcessOptions(string_iterator * options);
  bool Flag(char *arg);
  void PrintInfo(void);
  void PrintOptions(void);
  void PrintLicense(void);

};

/****************************************
  Printing functions.
 ****************************************/

class ReportManager {
  void print_trace_aux(StatePtr p);	// changed by Uli
public:
   ReportManager();
  void CheckConsistentVersion();
  void StartSimulation();

  void print_algorithm();
  void print_warning();
  void print_header(void);
  void print_trace_with_theworld();
  void print_trace_with_curstate();
  void print_progress(bool forceprint = false);
  void print_level();
  void print_no_error(void);
  void print_summary(bool);	// print omission probabilities only if true
  void print_curstate(void);
  void print_dfs_deadlock(void);
  void print_retrack(void);
  void print_fire_startstate();
  void print_fire_rule();
  void print_fire_rule_diff(state * s);
  void print_trace_all();
  void print_verbose_header();
  void print_hashtable();
  void print_final_report();
};

/****************************************   // added by Uli
  trace info file.
 ****************************************/

#ifdef HASHC
class TraceFileManager {
public:
  struct Buffer {		// buffer for read
    unsigned long previous;
#if __WORDSIZE == 32
    unsigned long c1;
    unsigned long c2;
#else
    unsigned int c1;
    unsigned int c2;
#endif
  };

private:
  int numBytes;			// number of bytes for compressed values
  char name[256];		// filename for trace info file
  FILE *fp;			// file pointer
  Buffer buf;			// buffer for read
  unsigned long inBuf;		// number of state in buffer (0: empty)
  unsigned long last;		// number of last state written
#if __WORDSIZE == 32
  void writeLong(unsigned long l, int bytes);
#else
  void writeLong(unsigned int l, int bytes);
#endif
  unsigned long readLong(int bytes);

public:
   TraceFileManager(char *);
  ~TraceFileManager();
  void setBytes(int bits);
#if __WORDSIZE == 32
  void write(unsigned long c1, unsigned long c2, unsigned long previous);
#else
  void write(unsigned int c1, unsigned int c2, unsigned long previous);
#endif
  const Buffer *read(unsigned long number);
  unsigned long numLast();
};
#endif
