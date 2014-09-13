/**CFile***********************************************************************

  FileName    [mu.cpp]

  Synopsis    [File with main]

  Author      [Igor Melatti]

  Copyright   [
  This file is part of the compiler package of CMurphi. 
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

#include "mu.hpp"
#include <string.h>
#include <new>
#include <cstdlib>
using namespace std;

/********************
  variable declarations
  ********************/
program *theprog = NULL;
symboltable *symtab = NULL;
FILE *codefile;

/********************
  void err_new_handler()
  ********************/
void err_new_handler()
{
  Error.FatalError("Unable to allocate enough memory.");
}

/********************
  void init_globals()
  -- initialize all global variables
  ********************/
void init_globals()
{
  set_new_handler(&err_new_handler);
  booltype = new enumtypedecl(0, 1);
  booltype->declared = TRUE;
  booltype->mu_name = tsprintf("mu_0_boolean");
  inttype = new enumtypedecl(0, 10000);
  inttype->declared = TRUE;
  realtype = new realtypedecl(6, 2);
  realtype->declared = TRUE;

  /* An enum, not a subrange, because an integer is a primitive type. */
  /* The upper bound doesn\'t really matter; it doesn\'t get used. MAXINT
   * seems like a logical value, but that causes an overflow in the
   * arithmetic used to calculate the number of bits it requires. I\'ve
   * chosen a value that shouldn\'t create any problems, even with small
   * ints. */
  errortype = new errortypedecl((char *) "ERROR");
  voidtype = new typedecl((char *) "VOID_TYPE");
  errorparam = new param(errortype);
  errordecl = new error_decl((char *) "ERROR_DECL");
  error_expr = new expr(0, errortype);
  true_expr = new expr(TRUE, booltype);
  false_expr = new expr(FALSE, booltype);
  error_designator = new designator(NULL, errortype, FALSE, FALSE, FALSE);
  nullstmt = new stmt;
  error_rule = new simplerule(NULL, NULL, NULL, NULL, 0);
  symtab = new symboltable;
  theprog = new program;
  typedecl::origin = NULL;
}

/********************
  void setup_infile(char *filename)
  -- setup input file handler
  ********************/
void setup_infile(char *filename)
{
  /* pre-checking on filename. */
  int len = strlen(filename);
  if (filename[len - 2] != '.' || filename[len - 1] != 'm') {
    Error.FatalError("Murphi only handles files ending in \".m\"");
  } else {
    gFileName = filename;
    yyin = fopen(filename, "r");	// yyin is flex\'s global for the input file
    if (yyin == NULL) {
      Error.FatalError("%s:No such file or directory.", filename);
    }
  }
}

/********************
  FILE *setup_outfile(char *infilename)
  -- setup output file handler
  ********************/
FILE *setup_outfile(char *infilename)
{
  char outfilename[1024];
  FILE *outfile;
  int len = strlen(infilename);

  if (Error.CondError(len >= 1021, "Model file name %s must have at most 1021 characters", infilename))
    exit(10);
  strcpy(outfilename, infilename);
  outfilename[len - 1] = 'c';
  outfilename[len] = 'p';
  outfilename[len + 1] = 'p';
  outfilename[len + 2] = '\0';
  outfile = fopen(outfilename, "w");
  if (outfile == NULL) {
    Error.FatalError("Unable to open/create %s", outfilename);
  };
  return outfile;
}

/********************
  class argclass
  ********************/
bool Sw(char *a, int ac, char **av)
{
  for (int i = 1; i < ac; i++)
    if (strcmp(av[i], a) == 0)
      return TRUE;
  return FALSE;
}

argclass::argclass(int ac, char **av)
:  
argc(ac), argv(av), print_license(FALSE), help(FALSE), checking(TRUE),
no_compression(TRUE), hash_compression(FALSE), hash_disk(FALSE),
hash_cache(FALSE), pmurphik(FALSE), bpctl(FALSE), noht(FALSE), trace_dfs(FALSE)
{
  bool initialized_filename = FALSE;
  int i;

  if (ac == 1) {		// if there is no argument, print help
    help = TRUE;
    PrintInfo();
    exit(1);
  }
  for (i = 1; i < ac; i++) {
    if (strcmp(av[i], "-l") == 0) {
      print_license = TRUE;
      continue;
    }
    if (strcmp(av[i], "-b") == 0) {
      no_compression = FALSE;
      continue;
    }
    if (strcmp(av[i], "-c") == 0) {
      hash_compression = TRUE;
      continue;
    }
//gdp: disk murphi
    if (strcmp(av[i], "--disk") == 0) {
      if (hash_cache == TRUE) {
	fprintf(stderr, "Option --disk cannot be used with --cache.\n");
	exit(1);
      }
      if (bpctl == TRUE) {
	fprintf(stderr, "Option --disk cannot be used with --bpctl.\n");
	exit(1);
      }
      if (bpctl_prob_ord == TRUE) {
	fprintf(stderr,
		"Option --disk cannot be used with --bpctl-prob-ord.\n");
	exit(1);
      }
      if (noht == TRUE) {
	fprintf(stderr, "Option --disk cannot be used with --noht.\n");
	exit(1);
      }
      if (trace_dfs == TRUE) {
	fprintf(stderr, "Option --disk cannot be used with --trace-dfs.\n");
	exit(1);
      }
      hash_disk = TRUE;
      continue;
    }
//gdp: cached murphi
    if (strcmp(av[i], "--cache") == 0) {
      if (hash_disk == TRUE) {
	fprintf(stderr, "Option --cache cannot be used with --disk.\n");
	exit(1);
      }
      if (bpctl == TRUE) {
	fprintf(stderr, "Option --cache cannot be used with --bpctl.\n");
	exit(1);
      }
      if (bpctl_prob_ord == TRUE) {
	fprintf(stderr,
		"Option --cache cannot be used with --bpctl-prob-ord.\n");
	exit(1);
      }
      if (noht == TRUE) {
	fprintf(stderr, "Option --cache cannot be used with --noht.\n");
	exit(1);
      }
      if (trace_dfs == TRUE) {
	fprintf(stderr, "Option --cache cannot be used with --trace-dfs.\n");
	exit(1);
      }
      hash_cache = TRUE;
      continue;
    }
//im: normal verification algorithm, but probabilistic rules
    if (strcmp(av[i], "--prob") == 0) {
      if (bpctl == TRUE) {
	fprintf(stderr, "Option --prob cannot be used with --bpctl.\n");
	exit(1);
      }
      if (bpctl_prob_ord == TRUE) {
	fprintf(stderr,
		"Option --prob cannot be used with --bpctl-prob-ord.\n");
	exit(1);
      }
      if (noht == TRUE) {
	fprintf(stderr, "Option --prob cannot be used with --noht.\n");
	exit(1);
      }
      if (trace_dfs == TRUE) {
	fprintf(stderr, "Option --prob cannot be used with --trace-dfs.\n");
	exit(1);
      }
      prob_rules = TRUE;
      continue;
    }
//im: bounded probabilistic model checking
    if (strcmp(av[i], "--bpctl") == 0) {
      if (hash_cache == TRUE) {
	fprintf(stderr, "Option --bpctl cannot be used with --cache.\n");
	exit(1);
      }
      if (hash_disk == TRUE) {
	fprintf(stderr, "Option --bpctl cannot be used with --disk.\n");
	exit(1);
      }
      if (prob_rules == TRUE) {
	fprintf(stderr, "Option --bpctl cannot be used with --prob.\n");
	exit(1);
      }
      if (noht == TRUE) {
	fprintf(stderr, "Option --bpctl cannot be used with --noht.\n");
	exit(1);
      }
      if (trace_dfs == TRUE) {
	fprintf(stderr, "Option --bpctl cannot be used with --trace-dfs.\n");
	exit(1);
      }
      bpctl = TRUE;
      continue;
    }
//im: bounded probabilistic model checking
    if (strcmp(av[i], "--bpctl-prob-ord") == 0) {
      if (hash_cache == TRUE) {
	fprintf(stderr,
		"Option --bpctl-prob-ord cannot be used with --cache.\n");
	exit(1);
      }
      if (hash_disk == TRUE) {
	fprintf(stderr,
		"Option --bpctl-prob-ord cannot be used with --disk.\n");
	exit(1);
      }
      if (prob_rules == TRUE) {
	fprintf(stderr,
		"Option --bpctl-prob-ord cannot be used with --prob.\n");
	exit(1);
      }
      if (bpctl == TRUE) {
	fprintf(stderr,
		"Option --bpctl-prob-ord cannot be used with --bpctl.\n");
	exit(1);
      }
      if (noht == TRUE) {
	fprintf(stderr, "Option --bpctl-prob-ord cannot be used with --noht.\n");
	exit(1);
      }
      if (trace_dfs == TRUE) {
	fprintf(stderr, "Option --bpctl-prob-ord cannot be used with --trace-dfs.\n");
	exit(1);
      }
      bpctl = TRUE;
      bpctl_prob_ord = TRUE;
      continue;
    }
//im: test driver
    if (strcmp(av[i], "--noht") == 0) {
      if (hash_cache == TRUE) {
	fprintf(stderr, "Option --noht cannot be used with --cache.\n");
	exit(1);
      }
      if (hash_disk == TRUE) {
	fprintf(stderr, "Option --noht cannot be used with --disk.\n");
	exit(1);
      }
      if (bpctl == TRUE) {
	fprintf(stderr, "Option --noht cannot be used with --bpctl.\n");
	exit(1);
      }
      if (prob_rules == TRUE) {
	fprintf(stderr, "Option --noht cannot be used with --prob.\n");
	exit(1);
      }
      noht = TRUE;
      continue;
    }
//im: DFS trace on stack
    if (strcmp(av[i], "--trace-dfs") == 0) {
      if (hash_cache == TRUE) {
	fprintf(stderr, "Option --trace-dfs cannot be used with --cache.\n");
	exit(1);
      }
      if (hash_disk == TRUE) {
	fprintf(stderr, "Option --trace-dfs cannot be used with --disk.\n");
	exit(1);
      }
      if (bpctl == TRUE) {
	fprintf(stderr, "Option --trace-dfs cannot be used with --bpctl.\n");
	exit(1);
      }
      if (prob_rules == TRUE) {
	fprintf(stderr, "Option --trace-dfs cannot be used with --prob.\n");
	exit(1);
      }
      trace_dfs = TRUE;
      continue;
    }

    if (strcmp(av[i], "-h") == 0) {
      help = TRUE;
      PrintInfo();
      exit(1);
    }
//       if ( strncmp(av[i], "-sym", strlen("-sym") ) == 0 )
//       {
//        // we should change it to check whether the number after prefix
//        // is really a number
//         if ( strlen(av[i]) <= strlen("-sym") ) /* We have a space before the number,
//                                     * so it\'s in the next argument. */
//           sscanf( av[++i], "%d", &symmetry_algorithm_number);
//         else
//           sscanf( av[i] + strlen("-sym"), "%d", &symmetry_algorithm_number);
//         continue;
//       }

    if (av[i][0] != '-' && !initialized_filename) {
      initialized_filename = TRUE;
      filename = av[i];
      continue;
    } else if (av[i][0] != '-' && initialized_filename) {
      fprintf(stderr, "Duplicated input filename.\n");
      exit(1);
    }
    fprintf(stderr,
	    "Unrecognized flag. Do '%s -h' for a list of valid arguments.\n",
	    av[0]);
    exit(1);
  }

  if (!initialized_filename) {	// print help
    help = TRUE;
    PrintInfo();
    exit(0);
  }

  if (hash_disk && (no_compression || (!hash_compression))) {
    fprintf(stderr,
	    "\nWarning: option --disk automatically enables -b and -c.\n\n");
    no_compression = FALSE;
    hash_compression = TRUE;
  }

  if (bpctl && hash_compression) {
    fprintf(stderr,
	    "\nWarning: option --bpctl automatically disables -c.\n\n");
    hash_compression = FALSE;
  }

  if (noht && trace_dfs) {
    /*fprintf(stderr,
	    "\nWarning: option --noht automatically enables --trace_dfs.\n\n");*/
    trace_dfs = FALSE; /* automatically enforced inside murphi.noht */
  }

  if (bpctl || prob_rules)
    pmurphik = TRUE;

  PrintInfo();
}

void argclass::PrintInfo(void)
{
  if (print_license)
    PrintLicense();

  if (!print_license) {
    printf("Call with the -l flag or read the license file for terms\n");
    printf("and conditions of use.\n");
  }

  if (!help)
    printf("Run this program with \"-h\" for the list of options.\n");

  printf("Bugs, questions, and comments should be directed to\n");
  printf("\"melatti@di.uniroma1.it\".\n\n");

  printf("CMurphi compiler last compiled date: %s\n", __DATE__);
  printf("\
===========================================================================\n");

  if (help)
    PrintOptions();
  fflush(stdout);
}

void argclass::PrintOptions(void)
{
  printf("The options are shown as follows:\n\
\n\
\t-h          \t\t   \thelp\n\
\t-l          \t\t   \tprint license\n\
\t-b          \t\t   \tuse bit-compacted states\n\
\t-c          \t\t   \tuse hash compaction\n\
\t--cache     \t\t   \tuse simple state caching\n\
\t--disk      \t\t   \tuse disk based caching\n\
\t--prob      \t\t   \tuse standard verification starting from probabilistic rules\n\
\t--bpctl     \t\t   \tbounded probabilistic model checking\n\
\t--bpctl-prob-ord\t \tbounded probabilistic model checking considering outgoing probabilities order\n\
\t--noht      \t\t   \tdo not store visited states (all states will be considered new)\n\
\t--trace-dfs \t\t   \tif DFS is used, counterexample will be generated directly from stack\n\
\n\
An argument without a leading '-' is taken to be the input filename,\n\
\twhich must end with '.m'\n\
");
// \t-sym <num> \t\tsymmetry reduction algorithm <num>\n
}

void argclass::PrintLicense(void)
{
  printf("License Notice: \n\n");
  printf("\
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
");
  fflush(stdout);
}

/********************
  variable declarations
  ********************/
argclass *args;

/********************
  various print routines  
  ********************/
void print_header()
{
  printf("\n\
===========================================================================\n");

  printf("%s\nFinite-state Concurrent System Compiler.\n\n",
	 MURPHI_VERSION);
  printf("%s is based on Murphi release 3.1.\n", MURPHI_VERSION);
  printf
      ("%s :\nCopyright (C) 2009 - 2012 by Sapienza University of Rome.\n",
       MURPHI_VERSION);
  printf
      ("Murphi Release 3.1 :\nCopyright (C) 1992 - 1999 by the Board of Trustees of\nLeland Stanford Junior University.\n\
===========================================================================\n");
}

void print_result()
{
  int len = strlen(args->filename);
  args->filename[len - 1] = 'c';
  printf("Code generated in file %spp\n", args->filename);
}

void for_prob_ord()
{
  char buffer[1024], fileC[1024], filetmp[1024];
  int i;

  sprintf(filetmp, "/tmp/%s", args->filename);
  for (i = 1; i < 5; i++) {
    sprintf(filetmp, "%s.tmp", filetmp);
    codefile = fopen(filetmp, "r");
    if (codefile == NULL)
      break;
    fclose(codefile);
  }
  if (codefile != NULL) {
    fprintf(stderr,
	    "Impossible to generate the code, please clean up /tmp\n");
    exit(1);
  }
  strcpy(fileC, args->filename);
  fileC[strlen(args->filename) - 1] = 'c';
  fileC[strlen(args->filename)] = 'p';
  fileC[strlen(args->filename) + 1] = 'p';
  fileC[strlen(args->filename) + 2] = '\0';
  sprintf(buffer,
	  "grep numrules %s | awk '{print $5}' | awk -F';' '{printf(\"#define NUMRULES_DEFINE %%d\\n\", $1)}' > %s; cat %s >> %s; mv %s %s",
	  fileC, filetmp, fileC, filetmp, filetmp, fileC);
  i = system(buffer);		//shuts up the compiler
}

/********************
  main routines
  ********************/
int main(int argc, char *argv[])
{
  int error;
  print_header();
  args = new argclass(argc, argv);

  init_globals();
  setup_infile(args->filename);
  error = yyparse();
  if (!error && Error.getnumerrors() == 0) {
    codefile = setup_outfile(args->filename);
    theprog->generate_code();
    fclose(codefile);
    if (args->bpctl_prob_ord)
      for_prob_ord();
    print_result();
    exit(0);
  } else {
    exit(1);
  }
}

