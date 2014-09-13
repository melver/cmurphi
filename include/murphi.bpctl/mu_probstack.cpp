/**CFile***********************************************************************

  FileName    [mu_probstack.cpp]

  Synopsis    [File for stack]

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

#include "murphi.bpctl/mu_probstack.hpp"
#include <math.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#define DBG 0
#define SPLITFILE_LEN (1024 * 0x100000L)	/* 100MB */
#define SFS_PAGING_FILE "SFS_PAGING_FILE"

char *make_unique_filename(char *basepathname)
{
  static char filenamebuffer[500];

  char *tmp, *prev, buffer[4096];
  strcpy(buffer, PROTOCOL_NAME);
  tmp = strtok(buffer, "/");
  while (tmp != NULL) {
    prev = tmp;
    tmp = strtok(NULL, "/");
  }

  //Maybe I can add a random seed...
  sprintf(filenamebuffer, "%s_%s.swp", basepathname, prev);

  return filenamebuffer;
}

state_prob_rule_stack::state_prob_rule_stack(unsigned long memory,
					     unsigned long bound)
:  
max_active_states(bound), front(0), disk2stack_cnt(0),
stack2disk_cnt(0), num_elts(0), mem_used(0)
{
  if (memory >= max_active_states * sizeof(state_prob_rule)) {
    size = size_2 = max_active_states;
    paging_file = NULL;
  } else {
    size = (unsigned) (memory / sizeof(state_prob_rule));
    if (size % 2 == 1)
      size--;
    size_2 = size / 2;

#ifndef SPLITFILE
    if ((paging_file = tmpfile()) == NULL) {
      Error.Notrace("Internal: Error creating top paging file.");
    }
#else
    paging_file = new splitFile(SPLITFILE_LEN, false);
    mem_used += sizeof(splitFile);

    if (!(paging_file->open(make_unique_filename(SFS_PAGING_FILE), "w+b")))
      Error.Notrace("Internal: Error creating paging file for s_f_s.");
#endif
  }

  stateArray = new state_prob_rule[size];
  mem_used += size * sizeof(state_prob_rule);
}

state_prob_rule_stack::~state_prob_rule_stack()
{
  delete[]stateArray;

  if (paging_file != NULL) {
#ifndef SPLITFILE
    fclose(paging_file);
#else
    paging_file->close();

    delete paging_file;
#endif
  }
}

int
 state_prob_rule_stack::BytesForOneState(void)
{
  return sizeof(state_prob_rule);
}

void state_prob_rule_stack::Print(void)
{
  unsigned long i;

  for (i = 0; i < front; i++)
    cout << "ProbReach at " << i << ": " << stateArray[i].
	_prob_reach << "\n";
}

void state_prob_rule_stack::push(state * e, double p_r, double p_f)
{
  if (Stack2Disk_needed())
    Stack2Disk();
  stateArray[front]._state = *e;
  stateArray[front]._prob_reach = p_r;
  stateArray[front]._prob_f = p_f;
  stateArray[front]._rule = 0;
#ifdef BPCTL_PROB_ORD
  if (NUMRULES_DEFINE != 1)
    /* not ordered */
    stateArray[front]._rules_ord[0] = stateArray[front]._rules_ord[1] = 0;
#endif
  front++;
  num_elts++;
}

#ifdef BPCTL_PROB_ORD
unsigned state_prob_rule_stack::stack_rules(unsigned i, double &p_ret)
{
  if (Disk2Stack_needed())
    Disk2Stack();

  p_ret = stateArray[front - 1]._prob_ord[i];
  return stateArray[front - 1]._rules_ord[i];
}

void state_prob_rule_stack::set_stack_rules(unsigned *v, double *p,
					    int dim)
{
  if (Disk2Stack_needed())
    Disk2Stack();

  for (int i = 0; i < dim; i++) {
    stateArray[front - 1]._rules_ord[i] = v[i];
    stateArray[front - 1]._prob_ord[i] = p[i];
  }
  if (dim != NUMRULES_DEFINE)
    stateArray[front - 1]._rules_ord[dim] = NUMRULES_DEFINE;	/* delimiter; effective rule numbers are from 0 to NUMRULES_DEFINE - 1 */
}
#endif

state *state_prob_rule_stack::pop(double &p_r, double &p_f)
{
  if (Disk2Stack_needed())
    Disk2Stack();

  front--;
  p_r = stateArray[front]._prob_reach;
  p_f = stateArray[front]._prob_f;
  num_elts--;

  return &(stateArray[front]._state);
}

state *state_prob_rule_stack::top()
{
  if (Disk2Stack_needed())
    Disk2Stack();

  return &(stateArray[front - 1]._state);
}

void state_prob_rule_stack::Stack2Disk()
{
  stack2disk_cnt++;

#ifndef SPLITFILE
  fwrite(&stateArray[0], sizeof(state_prob_rule), size_2, paging_file);
#else
  paging_file->write(&stateArray[0], sizeof(state_prob_rule), size_2);
#endif

  memmove(stateArray, &stateArray[size_2],
	  size_2 * sizeof(state_prob_rule));

  front = size_2;
}

void state_prob_rule_stack::Disk2Stack()
{
  disk2stack_cnt++;

  memmove(&stateArray[size_2], stateArray, size_2 * sizeof(state_prob_rule));	//  IM: probably useless

#ifndef SPLITFILE
  fseek(paging_file,
	(stack2disk_cnt -
	 disk2stack_cnt) * sizeof(state_prob_rule) * size_2, SEEK_SET);
  fread(stateArray, sizeof(state_prob_rule), size_2, paging_file);
  fseek(paging_file,
	(stack2disk_cnt -
	 disk2stack_cnt) * sizeof(state_prob_rule) * size_2, SEEK_SET);
#else
  //paging_file->seek(sizeof(state_prob_rule), size_2, SEEK_CUR, BACKWARD);
  paging_file->seek((stack2disk_cnt - disk2stack_cnt) *
		    sizeof(state_prob_rule) * size_2, SEEK_SET);
  paging_file->read(stateArray, sizeof(state_prob_rule), size_2);
  //paging_file->seek(sizeof(state_prob_rule), size_2, SEEK_CUR, BACKWARD);
  paging_file->seek((stack2disk_cnt - disk2stack_cnt) *
		    sizeof(state_prob_rule) * size_2, SEEK_SET);
#endif

  front = size_2;
}

unsigned state_prob_rule_stack::NextRuleToTry()
{
  if (Disk2Stack_needed())
    Disk2Stack();

  return stateArray[front - 1]._rule;
}

void state_prob_rule_stack::NextRuleToTry(unsigned r)
{
  if (Disk2Stack_needed())
    Disk2Stack();

  stateArray[front - 1]._rule = r;
}

/* Assumption: the slot to update corresponds to front - 1 */
double state_prob_rule_stack::update_prob(double p)
{
  if (Disk2Stack_needed())
    Disk2Stack();

  stateArray[front - 1]._prob_f += p;

  return stateArray[front - 1]._prob_f;
}

/* only reliable if there are no nested DFSs */
void state_prob_rule_stack::print_probability_so_far()
{
  double prob;

  while (front > 0) {
    if (Disk2Stack_needed())
      Disk2Stack();

    front--;
    prob = stateArray[front]._prob_reach * stateArray[front]._prob_f;
    /*if (stateArray[front]._prob_reach > 0 && stateArray[front]._prob_f > 0) { */
    if (prob > 0)
      stateArray[front - 1]._prob_f += prob;
    /*else {
       cout << setprecision (6) << setiosflags (ios::scientific)
       << stateArray[front]._prob_f << setprecision (3) << resetiosflags (ios::scientific) << " * ";
       } */
  }
  cout << setprecision(10) << setiosflags(ios::scientific)
      << stateArray[0]._prob_f << setprecision(3) << resetiosflags
      (ios::scientific) << "\n";
}

state *state_prob_rule_stack::reset(long level)
{
  if (stack2disk_cnt != disk2stack_cnt) {
    for (long i = level - 1; i >= -1; i--) {
      if (Disk2Stack_needed())
	Disk2Stack();

      front--;
      num_elts--;
    }
  } else {
    front -= level + 1;
    num_elts -= level + 1;
  }
  return &(stateArray[front]._state);
}

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#define DBG 0
#define SPLITFILE_LEN (1024 * 0x100000L)	/* 100MB */
#define SFS_PAGING_FILE "SFS_PAGING_FILE"

#ifdef MAX_HT_CHAIN_LENGTH
#undef MAX_HT_CHAIN_LENGTH
#endif
#define MAX_HT_CHAIN_LENGTH 20


#define SFQ_PAGING_FILE_TOP "SFQ_PAGING_FILE_1"
#define SFQ_PAGING_FILE_BOTTOM "SFQ_PAGING_FILE_2"
#define SSQ_PAGING_FILE_TOP "SSQ_PAGING_FILE_1"
#define SSQ_PAGING_FILE_BOTTOM "SSQ_PAGING_FILE_2"
#define SFQ_HISTORY_FILE "SFQ_HISTORY_FILE"

state_probability_queue::state_probability_queue(unsigned long mas)
:  max_active_states((unsigned long) (mas * gPercentActiveStates))
{

  stateArray = new state_and_probability_pair[max_active_states];

  hashtable_size = NextPrime((unsigned long) mas);

  table = new state_and_probability_pair[hashtable_size];

  Full = new dynBitVec(hashtable_size);

#ifndef SPLITFILE
  if ((paging_file_top = tmpfile()) == NULL) {
    Error.Notrace("Internal: Error creating top paging file.");
  }

  if ((paging_file_bottom = tmpfile()) == NULL) {
    Error.Notrace("Internal: Error creating bottom paging file.");
  }
#else
  paging_file_top = new splitFile(SPLITFILE_LEN, false);
  paging_file_bottom = new splitFile(SPLITFILE_LEN, false);

  if (!
      (paging_file_top->open
       (make_unique_filename(SFQ_PAGING_FILE_TOP), "w+b"))) {
    Error.Notrace("Internal: Error creating top paging file for s_f_q.");
  }

  if (!
      (paging_file_bottom->open
       (make_unique_filename(SFQ_PAGING_FILE_BOTTOM), "w+b"))) {
    Error.Notrace("Internal: Error creating bottom paging file.");
  }
#endif

  num_elts_head = num_elts_tail = 0;

  head_begin = 0;
  tail_begin = max_active_states / 2;

  head_size = max_active_states / 2;
  tail_size = max_active_states - head_size;

  global_front = global_rear = front = rear = 0;
}


state_probability_queue::~state_probability_queue()
{
  delete[]stateArray;
  delete[]table;
  delete Full;

#ifndef SPLITFILE
  fclose(paging_file_top);	//rmtmp();
  fclose(paging_file_bottom);	//rmtmp();
#else

  paging_file_top->close();	//rmtmp();
  paging_file_bottom->close();	//rmtmp();

  delete paging_file_top;
  delete paging_file_bottom;
#endif
}

bool state_probability_queue::isempty(void)
{
#if (DBG > 0)
  fprintf(stderr,
	  "isempty(): num_elts_head=%d num_elts_tail=%d global_rear=%d global_front=%d",
	  num_elts_head, num_elts_tail, global_rear, global_front);
#endif
  return num_elts_head + num_elts_tail + global_rear + global_front +
      hashtable_num_elts == 0;
}

int state_probability_queue::BytesForOneState(void)
{
  return sizeof(state_and_probability_pair);
}

int state_probability_queue::BytesForOneState_hashtable(void)
{
  return sizeof(state_and_probability_pair);
}



void state_probability_queue::Print(void)
{
  unsigned long i;

  for (i = 0; i < num_elts_head; i++) {
    // convert to print in unsigned long format?
    cout << "State " << i << " [" << head_begin + i << "]:\n";
    stateArray[head_begin + i]._state.print();
  }

  for (i = 0; i < num_elts_tail; i++) {
    // convert to print in unsigned long format?
    cout << "State " << i << " [" << tail_begin + i << "]:\n";
    stateArray[tail_begin + i]._state.print();
  }
}


bool state_probability_queue::enqueue(state * &e, double p)
{
  if (hashtable_num_elts >= hashtable_size)
    CheckTable();

  state_and_probability_pair pair(e, p);
  state_and_probability_pair *ppair = &pair;


  if (!hashtable_lookup(ppair)) {
    ppair->_probability = p;
    e = &(ppair->_state);
    return true;
  } else {
    ppair->_probability += p;
    e = &(ppair->_state);
    return false;
  }
}


void state_probability_queue::enqueue_commit(state_and_probability_pair *
					     e)
{

  if (num_elts_tail >= tail_size) {	//memory full: reclaim more space by swapping out the current queue
    ReclaimFreeSpace();
  }

  /*
     at this point, ReclaimFreeSpace has obtained new space in the queue and
     set the offsets (front, rear, ...) accordingly; so we proceed with
     the insertion without checking...
   */


  stateArray[tail_begin + rear] = *e;
  rear++;
  num_elts_tail++;
}

state *state_probability_queue::dequeue(double &prob)
{
#if (DBG > 0)
  fprintf(stderr, "dequeue(): num_elts_head=%d", num_elts_head);
#endif

  state *retval;

  if (num_elts_head <= 0) {
    QueueEmptyFault();
  }

  retval = &(stateArray[head_begin + front]._state);
  prob = stateArray[head_begin + front]._probability;

  front++;
  num_elts_head--;


#if (DBG > 0)
  fprintf(stderr, "dequeue(): prob=%f", prob);
#endif


  return retval;
}


state *state_probability_queue::top(double &prob)
{
  if (num_elts_head <= 0) {
    QueueEmptyFault();
  }

  prob = stateArray[head_begin + front]._probability;
  return &(stateArray[head_begin + front]._state);
}


void state_probability_queue::ReclaimFreeSpace()
{
#if (DBG > 0)
  fprintf(stderr,
	  "\nReclaimFreeSpace(sfq): writing %d states (%d bytes each) to disk",
	  tail_size, sizeof(state_and_probability_pair));
#endif

#ifndef SPLITFILE
  global_rear +=
      fwrite(&stateArray[tail_begin], sizeof(state_and_probability_pair),
	     tail_size, paging_file_bottom);

#else
  global_rear +=
      paging_file_bottom->write(&stateArray[tail_begin],
				sizeof(state_and_probability_pair),
				tail_size);
#endif

  num_elts_tail = 0;
  rear = 0;
}


void state_probability_queue::QueueEmptyFault()
{
#if (DBG > 0)
  fprintf(stderr, "\nQueueEmptyFault(sfq): ");
#endif
#ifndef SPLITFILE
  size_t read =
      fread(&stateArray[head_begin], sizeof(state_and_probability_pair),
	    min(global_front, head_size),
	    paging_file_top);
#else
  //make sure we do not read garbage after the states
  size_t read = paging_file_top->read(&stateArray[head_begin],
				      sizeof(state_and_probability_pair),
				      min(global_front, head_size));
#endif

  if (read > 0) {		//ok, some states are swapped in

    num_elts_head = read;
    global_front -= read;
#if (DBG > 0)
    fprintf(stderr, " read %d states from bottom", read);
#endif

  } else if (global_rear > 0) {	//paging_file_top is empty, but paging_file_bottom is not

#ifndef SPLITFILE
    fclose(paging_file_top);

    paging_file_top = paging_file_bottom;
    fseek(paging_file_top, 0, SEEK_SET);	//move to the beginning of the queue
    global_front = global_rear;

    if ((paging_file_bottom = tmpfile()) == NULL) {
      Error.Notrace("Internal: Error creating bottom paging file.");
    }
    global_rear = 0;		//bottom file is empty

    size_t read = fread(&stateArray[head_begin], sizeof(state), head_size,
			paging_file_top);

    num_elts_head = read;
    global_front -= read;
#else
    splitFile *fswap;

    //swap files
#if (DBG > 0)
    fprintf(stderr, " swapping top with bottom");
#endif
    fswap = paging_file_top;
    paging_file_top = paging_file_bottom;

    paging_file_bottom = fswap;

    paging_file_top->seek(0, SEEK_SET);	//move to the beginning of the queue
    paging_file_bottom->seek(0, SEEK_SET);	//reset bottom queue

    global_front = global_rear;
    global_rear = 0;		//bottom file is empty

    //now bottom entries are top entries and bottom file is empty. Reload a block!
    size_t read = paging_file_top->read(&stateArray[head_begin],
					sizeof(state_and_probability_pair),
					min(global_front, head_size));
#if (DBG > 0)
    fprintf(stderr, " read %d states from disk", read);
#endif

    num_elts_head = read;
    global_front -= read;
#endif

  } else if (num_elts_tail > 0) {	//paging_file_top AND paging_file_bottom are empty

#if (DBG > 0)
    fprintf(stderr, " using memory tail...");
#endif

    /* the disk queue is ended. this means that the only states we have
       to explore are the ones in the current tail window */
    unsigned long swap = tail_begin;
    tail_begin = head_begin;
    head_begin = swap;

    swap = tail_size;
    tail_size = head_size;
    head_size = swap;

    num_elts_head = num_elts_tail;
    num_elts_tail = 0;
    rear = 0;
  } else {			//no more states in both swap files, and the memory is empty: why do we call again?
    Error.Notrace("Internal: Attempt to read an empty state queue.");
  }

  front = 0;
}


bool state_probability_queue::hashtable_lookup(state_and_probability_pair *
					       &in)
{
  unsigned long key = in->_state.hashkey();
  unsigned long h1 = key % hashtable_size;
  unsigned long h2 = 1 + key % (hashtable_size - 1);
  unsigned long h = h1;

  unsigned long probe = 0;
// no hash compaction, uses double hashing

  bool empty, equal = FALSE;

  while (!(empty = (Full->get(h) == 0)) &&
	 !(equal = (in->_state == table[h]._state)) &&
	 (probe < MAX_HT_CHAIN_LENGTH)) {
    h = (h1 + probe * h2) % hashtable_size;	// double hashing
    probe++;
  }
  if (empty) {			/* Go ahead and insert the element. */

    table[h] = *in;
    in = &table[h];
    Full->set(h);
    hashtable_num_elts++;

    return FALSE;
  } else if (equal) {
    in = &table[h];

    return TRUE;
  } else {
#if (DBG > 0)
    fprintf(stderr, "hashtable_lookup: table is full,clear it!\n");
#endif
    //table is full,clear it!
    CheckTable();
    //the table now is empty: use the first slot available for this state
    h = h1 % hashtable_size;

    table[h] = *in;
    in = &table[h];
    Full->set(h);
    hashtable_num_elts++;

    return FALSE;
  }

  return FALSE;
}


void state_probability_queue::CheckTable()
{
//1. move all the table states in the queue

  unsigned long moved = 0;
  unsigned long i;

#if (DBG > 0)
  fprintf(stderr, "CheckTable(): begin state migration...\n");
#endif

  for (i = 0; i < hashtable_size; i++) {
    if (Full->get(i) == 1) {
      enqueue_commit(&table[i]);
      moved++;			//for dbg only
    }
  }

#if (DBG > 0)
  fprintf(stderr, "CheckTable(): moved %lu states to the queue\n", moved);
#endif

//2. clear the table

  Full->clearall();
  hashtable_num_elts = 0;

}
