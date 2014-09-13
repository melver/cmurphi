/**CFile***********************************************************************

  FileName    [mu_verifier.cpp]

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

/****************************************
  There are 3 groups of implementations:
  None of them belong to any class
  1) verifying invariants
  2) transition sets generation
  3) verification and simulaiton supporting routines
  4) BFS algorithm supporting -- generate next stateset
  5) BFS algorithm main routine
  6) DFS algorithm main routine
  7) simulation
  8) global variables
  9) main function
  ****************************************/


/****************************************
  Global variables:
  void set_up_globals(int argc, char **argv)
  ****************************************/

// why exists? (Norris)
// saved value for the old new handler.
// void (*oldnh)() = NULL;       


/****************************************
  The Main() function:
  int main(int argc, char **argv)
  ****************************************/

#ifdef MY_MTRACE_CHECK
#ifndef MY_MTRACE_CHECK_FILE
#error "Please define constant MY_MTRACE_CHECK_FILE"
#endif
/* Prototypes for __malloc_hook, __free_hook */
#include <malloc.h>

/* Prototypes for our hooks.  */
static void my_init_hook(void);
static void *my_malloc_hook(size_t, const void *);
static void my_free_hook(void *, const void *);

/* Variables to save original hooks. */
static void *(*old_malloc_hook)(size_t, const void *);
static void (*old_free_hook)(void *, const void *);

/* Override initializing hook from the C library. */
void (*__malloc_initialize_hook) (void) = my_init_hook;
FILE *stream_dbg;

static void
my_init_hook(void)
{
  stream_dbg = fopen("./malloc_dbg", "w");
  old_malloc_hook = __malloc_hook;
  __malloc_hook = my_malloc_hook;
  old_free_hook = __free_hook;
  __free_hook = my_free_hook;
}

static void *
my_malloc_hook(size_t size, const void *caller)
{
  void *result;

  /* Restore all old hooks */
  __malloc_hook = old_malloc_hook;

  /* Call recursively */
  result = malloc(size);

  /* Save underlying hooks */
  old_malloc_hook = __malloc_hook;

  /* printf() might call malloc(), so protect it too. */
  fprintf(stream_dbg, "malloc(%u) called from %p returns %p\n", (unsigned int) size, caller, result);
  fflush(stream_dbg);

  /* Restore our own hooks */
  __malloc_hook = my_malloc_hook;

  return result;
}

static void
my_free_hook(void *ptr, const void *caller)
{
  /* Restore all old hooks */
  __free_hook = old_free_hook;

  /* Call recursively */
  free(ptr);

  /* Save underlying hooks */
  old_free_hook = __free_hook;

  /* printf() might call free(), so protect it too. */
  fprintf(stream_dbg, "free( %p ) called from %p\n", ptr, caller);
  fflush(stream_dbg);

  /* Restore our own hooks */
  __free_hook = my_free_hook;
}
#endif

int main(int argc, char **argv)
{
#ifdef MTRACE_CHECK
  mtrace();
#endif
  args = new argclass(argc, argv);
  Algorithm = new AlgorithmManager();

  if (!args->print_options.value) {
    if (!args->int_simulate_prob.value && args->simulate_prob.value == 0) {
      if (args->safety.value) {
	if (!Algorithm->IsSafety()) {
	  cerr <<
	      "-safety is usable only with a finite horizon safety property"
	      << endl;
	  exit(1);
	}
	Algorithm->verify_bfs();
      } else
	Algorithm->verify_bpmc();
    } else
      Algorithm->simulate();
  }

  cout.flush();
  delete Algorithm;		//gdp: fix: begin destruction chain
  exit(0);
}
