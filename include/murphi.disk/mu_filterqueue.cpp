/**CFile***********************************************************************

  FileName    [mu_filterqueue.cpp]

  Synopsis    [File for queue filtering]

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

#include <math.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#define DBG 0

#define SFQ_PAGING_FILE_TOP "SFQ_PAGING_FILE_1"
#define SFQ_PAGING_FILE_BOTTOM "SFQ_PAGING_FILE_2"
#define SSQ_PAGING_FILE_TOP "SSQ_PAGING_FILE_1"
#define SSQ_PAGING_FILE_BOTTOM "SSQ_PAGING_FILE_2"
#define SFQ_HISTORY_FILE "SFQ_HISTORY_FILE"

#define BITUNSIGNED 32		//sizeof(Unsigned32)*CHAR_BIT

state_filtering_queue::state_filtering_queue(unsigned long mas)
:max_active_states((unsigned long) (mas * gPercentActiveStates))
{
  stateArray = new state[max_active_states];

  uncheckedQueue =
      new
      state_and_signature_queue((unsigned long) (mas *
						 gPercentActiveStates));
  hashtable_size = NextPrime((unsigned long) mas);

  assert(sizeof(Unsigned32) == 4);
  unsigned long size =
      (unsigned long) ((double) (hashtable_size) * args->num_bits.value /
		       BITUNSIGNED) + 3;
#if __WORDSIZE == 64
  bits_for_size =
      (unsigned int) floor(log((double) hashtable_size) /
			   log((double) 2)) + 1;
  if (args->print_64bit_info.value) {
    int amount = 3 * sizeof(Unsigned32) * CHAR_BIT - bits_for_size;
    printf
	("With %lu bytes of RAM, you can use at most %d bits (option -b) for the hash compaction\n",
	 args->mem.value, amount > 64 ? 64 : amount);
    printf("Value for bits_for_size: %d\n", bits_for_size);
    exit(1);
  }
  if (bits_for_size >
      3 * sizeof(Unsigned32) * CHAR_BIT - args->num_bits.value)
    // in order to address an hash table entry, we may use the whole first int + what
    // remains of the other 2 ints when args->num_bits.value bits are subtracted
    Error.
	Notrace
	("Too many bits for the hash compaction (option -b); may be at most %d",
	 3 * sizeof(Unsigned32) * CHAR_BIT - bits_for_size);
  bits_for_size =
      bits_for_size <= BITUNSIGNED ? BITUNSIGNED : bits_for_size;
#endif
  filterTable = new Unsigned32[size];
  for (unsigned long i = 0; i < size; i++)
    filterTable[i] = (Unsigned32) 0;

  Full = new dynBitVec(hashtable_size);
  Removed = new dynBitVec(hashtable_size);

#ifndef SPLITFILE
  if ((paging_file_top = tmpfile()) == NULL) {
    Error.Notrace("Internal: Error creating top paging file.");
  }

  if ((paging_file_bottom = tmpfile()) == NULL) {
    Error.Notrace("Internal: Error creating bottom paging file.");
  }

  if ((history_file = tmpfile()) == NULL) {
    Error.Notrace("Internal: Error creating history file.");
  }
#else
  paging_file_top = new splitFile(SPLITFILE_LEN, false);
  paging_file_bottom = new splitFile(SPLITFILE_LEN, false);
  history_file = new splitFile(SPLITFILE_LEN, false);

  if (!
      (paging_file_top->open
       (paging_file_top->make_unique_filename(SFQ_PAGING_FILE_TOP),
	"w+b"))) {
    Error.Notrace("Internal: Error creating top paging file for s_f_q.");
  }

  if (!
      (paging_file_bottom->open
       (paging_file_bottom->make_unique_filename(SFQ_PAGING_FILE_BOTTOM),
	"w+b"))) {
    Error.Notrace("Internal: Error creating bottom paging file.");
  }

  if (!
      (history_file->open
       (history_file->make_unique_filename(SFQ_HISTORY_FILE), "w+b"))) {
    Error.Notrace("Internal: Error creating history file.");
  }
#endif

  num_elts_head = num_elts_tail = 0;

  head_begin = 0;
  tail_begin = max_active_states / 2;

  head_size = max_active_states / 2;
  tail_size = max_active_states - head_size;

  global_front = global_rear = front = rear = 0;

  history_len = 0;
  filter_alpha = INITIAL_ALPHA;

  last_deleted_states = 0;
  hashtable_num_elts = 0;
  hashtable_first_full = false;
}


state_filtering_queue::~state_filtering_queue()
{
  delete[]stateArray;
  delete[]filterTable;
  delete uncheckedQueue;
  delete Full;
  delete Removed;

#ifndef SPLITFILE
  fclose(paging_file_top);	//rmtmp();
  fclose(paging_file_bottom);	//rmtmp();
  fclose(history_file);		//rmtmp();
#else

  paging_file_top->close();
  paging_file_bottom->close();
  history_file->close();

  delete paging_file_top;
  delete paging_file_bottom;
  delete history_file;
#endif
}

bool state_filtering_queue::isempty(void)
{
#if (DBG > 0)
  fprintf(stderr,
	  "isempty(): num_elts_head=%d num_elts_tail=%d global_rear=%d global_front=%d",
	  num_elts_head, num_elts_tail, global_rear, global_front);
#endif
  return num_elts_head + num_elts_tail + global_rear + global_front == 0;
}

int state_filtering_queue::BytesForOneState_checked(void)
{
  return sizeof(state);
}

int state_filtering_queue::BytesForOneState_unchecked(void)
{
  return state_and_signature_queue::BytesForOneState();
}

int state_filtering_queue::BytesForOneState_hashtable(void)
{
  return (int) ceil((double) args->num_bits.value / 8.0);	//gdp: approx
}

void state_filtering_queue::Print(void)
{
  unsigned long i;

  for (i = 0; i < num_elts_head; i++) {
    // convert to print in unsigned long format?
    cout << "State " << i << " [" << head_begin + i << "]:\n";
    stateArray[head_begin + i].print();
  }

  for (i = 0; i < num_elts_tail; i++) {
    // convert to print in unsigned long format?
    cout << "State " << i << " [" << tail_begin + i << "]:\n";
    stateArray[tail_begin + i].print();
  }
}


bool state_filtering_queue::enqueue_unchecked(state * &e)
{
  if (hashtable_num_elts >= hashtable_size)
    CheckTable();

  if (args->symmetry_reduction.value)
    e->Normalize();
  if (args->multiset_reduction.value && !args->symmetry_reduction.value)
    e->MultisetSort();

#if __WORDSIZE == 32
  unsigned long *key = h3->hash(e, FALSE);
  unsigned long
      c1 = key[1] &
      ((~0UL) <<
       (args->num_bits.value > 32 ? 0 : 32 - args->num_bits.value));
  unsigned long c2 =
      key[2] & (args->num_bits.value >
		32 ? (~0UL) << (64 - args->num_bits.value) : 0UL);
#else
  unsigned int *key = h3->hash(e, FALSE);
  unsigned int
      c1 = key[1] &
      ((~0) <<
       (args->num_bits.value >
	BITUNSIGNED ? 0 : BITUNSIGNED - args->num_bits.value));
  unsigned int c2 =
      key[2] & (args->num_bits.value >
		BITUNSIGNED ? (~0) << (2 * BITUNSIGNED -
				       args->num_bits.value) : 0);
#endif

  state_and_signature_pair pair(e, c1, c2);
  state_and_signature_pair *ppair = &pair;


  if (!hashtable_lookup(c1, c2, true, false)) {
    uncheckedQueue->enqueue(ppair);
    e = &(ppair->_state);
    // write trace info
    if (args->trace_file.value)
      TraceFile->write(c1, c2, e->previous.lVal());
    return true;
  } else {
    return false;
  }
}


bool state_filtering_queue::enqueue_checked(state * e)
{

  if (num_elts_tail >= tail_size) {	//memory full: reclaim more space by swapping out the current queue
    ReclaimFreeSpace();
  }

  /*
     at this point, ReclaimFreeSpace has obtained new space in the queue and
     set the offsets (front, rear, ...) accordingly; so we proceed with
     the insertion without checking...
   */


  StateCopy(&stateArray[tail_begin + rear], e);
  rear++;
  num_elts_tail++;

  return true;
}

state *state_filtering_queue::dequeue_checked(void)
{
  state *retval;

  if (num_elts_head <= 0) {
    QueueEmptyFault();
  }

  retval = &stateArray[head_begin + front];
  front++;
  num_elts_head--;

  return retval;
}

state_and_signature_pair *state_filtering_queue::dequeue_unchecked(void)
{
  return uncheckedQueue->dequeue();
}

state *state_filtering_queue::top_checked(void)
{
  if (num_elts_head <= 0) {
    QueueEmptyFault();
  }

  return &stateArray[head_begin + front];
}


void state_filtering_queue::ReclaimFreeSpace()
{
#ifndef SPLITFILE
  global_rear +=
      fwrite(&stateArray[tail_begin], sizeof(state), tail_size,
	     paging_file_bottom);

#else
  global_rear +=
      paging_file_bottom->write(&stateArray[tail_begin], sizeof(state),
				tail_size);
#endif

  num_elts_tail = 0;
  rear = 0;
}


void state_filtering_queue::QueueEmptyFault()
{
#ifndef SPLITFILE
  size_t read =
      fread(&stateArray[head_begin], sizeof(state),
	    min(global_front, head_size),
	    paging_file_top);
#else
  //make sure we do not read garbage after the states
  size_t read =
      paging_file_top->read(&stateArray[head_begin], sizeof(state),
			    min(global_front, head_size));
#endif

  if (read > 0) {		//ok, some states are swapped in

    num_elts_head = read;
    global_front -= read;

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
    fswap = paging_file_top;
    paging_file_top = paging_file_bottom;
    paging_file_bottom = fswap;

    paging_file_top->seek(0, SEEK_SET);	//move to the beginning of the queue
    paging_file_bottom->seek(0, SEEK_SET);	//reset bottom queue

    global_front = global_rear;
    global_rear = 0;		//bottom file is empty

    //now bottom entries are top entries and bottom file is empty. Reload a block!
    size_t read =
	paging_file_top->read(&stateArray[head_begin], sizeof(state),
			      min(global_front, head_size));

    num_elts_head = read;
    global_front -= read;
#endif

  } else if (num_elts_tail > 0) {	//paging_file_top AND paging_file_bottom are empty

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


bool
#if __WORDSIZE == 32
    state_filtering_queue::hashtable_lookup(unsigned long c1,
					    unsigned long c2,
#else
    state_filtering_queue::hashtable_lookup(unsigned int c1,
					    unsigned int c2,
#endif
					    bool _insert, bool _delete)
{
  unsigned long base = signature_hash(c1, c2);
  unsigned long h1 = base % hashtable_size;
  unsigned long h2 = 1 + base % (hashtable_size - 1);
  register unsigned long h = h1;
  register unsigned long addr, offset;
  register unsigned long t1, t2;
  register unsigned long num_bits = args->num_bits.value;
#if __WORDSIZE == 32
  register unsigned long mask1 =
      (~0UL) << (num_bits > BITUNSIGNED ? 0 : BITUNSIGNED - num_bits);
  register unsigned long mask2 =
      num_bits >
      BITUNSIGNED ? (~0UL) << (2 * BITUNSIGNED - num_bits) : 0UL;
#else
  register unsigned int
   mask1 = (~0) << (num_bits > BITUNSIGNED ? 0 : BITUNSIGNED - num_bits);
  register unsigned int
   mask2 =
      num_bits > BITUNSIGNED ? (~0) << (2 * BITUNSIGNED - num_bits) : 0;
#endif


  unsigned long probe = 0;
  bool saved = FALSE;
  unsigned long saved_h;

  // search - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#if (DBG > 0)
  fprintf(stderr, "\nLookup(): searching for signature %lu,%lu... ", c1,
	  c2);
#endif

  do {

    //can cause errors?
    h = (h1 + probe * h2) % hashtable_size;	// double hashing


#if __WORDSIZE == 32
    // calculate address and offset in table
    // 32 bit arithmetic not sufficient and may cause overflow
    // addr = (h*num_bits) / 32
    // offset = (h*num_bits) % 32
    offset = (h & 0xffffUL) * num_bits;
    addr = (((h >> 16) * num_bits) << 11) + (offset >> 5);
    offset &= 0x1fUL;
#else
    // 64 bit arithmetic should always be sufficient
    addr = (h * num_bits) / BITUNSIGNED;
    offset = (h * num_bits) % BITUNSIGNED;
#endif

    if (Full->get(h) == 0) {
      if (Removed->get(h) == 0) {
	break;			// search unsuccessful
      } else {

#if (DBG > 0)
	fprintf(stderr, "Lookup(): saved hashposition %lu...\n", h);
#endif
	if (!saved) {
	  saved = TRUE;
	  saved_h = h;
	}

      }

    } else {			//slot is full


      // read compressed value from table
      t1 = (filterTable[addr] << offset |
	    (offset == 0 ? 0 : filterTable[addr + 1] >> (32 - offset)))
	  & mask1;
      t2 = (filterTable[addr + 1] << offset |
	    (offset == 0 ? 0 : filterTable[addr + 2] >> (32 - offset)))
	  & mask2;


      if (t1 == c1 && t2 == c2) {
	if (_delete) {
	  Full->clear(h);
	  Removed->set(h);
	  hashtable_num_elts--;
	  //funziona questo reset?? E serve?? No, perche' dopo la pulizia la ht
	  //viene sempre resettata
	  //filterTable[addr]   &= ~(mask1>>offset);   
	  //filterTable[addr+1] &= ~((offset==0 ? 0 : mask1<<(32-offset)) | mask2>>offset);
	  //filterTable[addr+2] &= ~(offset==0 ? 0 : mask2<<(32-offset));

#if (DBG > 0)
	  fprintf(stderr, " ...deleted ");
#endif

	}
#if (DBG > 0)
	fprintf(stderr, " ...found\n");
#endif
	return TRUE;		// search successful
      }

    }				// if Full(h)

    probe++;

    //if (probe >= max(MAX_HT_CHAIN_LENGTH,hashtable_size * filter_alpha * 0.1))
#ifdef PAPER_COMPL
    if (probe >= hashtable_size)
#else
    if (probe >= MAX_HT_CHAIN_LENGTH)
#endif
    {

#if (DBG > 0)
      fprintf(stderr, " ...not found\n");
#endif


      if (_insert) {
	if (!saved) {
	  //Error.Notrace( "Internal: HT is full.");
#if (DBG > 0)
	  fprintf(stderr, " ...table is full in lookup... cleaning...\n");
#endif

	  hashtable_first_full = true;
	  CheckTable();
	  //the table now is empty: use the first slot available for this state
	  h = h1 % hashtable_size;
	  break;
	} else
	  break;
      }

      return FALSE;

    }				//if (probe >= ...)

  } while (TRUE);


  // insertion - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  if (_insert) {
    if (saved)
      h = saved_h;

    Full->set(h);
    Removed->clear(h);

#if __WORDSIZE == 32
    offset = (h & 0xffffUL) * num_bits;
    addr = (((h >> 16) * num_bits) << 11) + (offset >> 5);
    offset &= 0x1fUL;
#else
    // 64 bit arithmetic should always be sufficient
    addr = (h * num_bits) / BITUNSIGNED;
    offset = (h * num_bits) % BITUNSIGNED;
#endif

    /* ++ visited states */
    hashtable_num_elts++;

    filterTable[addr] |= c1 >> offset;	// insertion
    filterTable[addr + 1] |=
	(offset == 0 ? 0 : c1 << (32 - offset)) | c2 >> offset;
    filterTable[addr + 2] |= (offset == 0 ? 0 : c2 << (32 - offset));

#if (DBG > 0)
    fprintf(stderr, " ...inserted");
#endif

  }
#if (DBG > 0)
  fprintf(stderr, " ...not found\n");
#endif

  return FALSE;
}

bool state_filtering_queue::QueryCalibration()
{
  static int countdown = CALIBRATION_FREQ;

#ifdef PAPER_COMPL
  //read always all the history in paper-compliant mode
  return true;
#else
  if (--countdown == 0) {
    countdown = CALIBRATION_FREQ;
    return true;
  } else
    return false;
#endif
}

double state_filtering_queue::SelectionP(unsigned long block)
{
  //block here is zero-based

  unsigned long area0_last =
      (unsigned long) floor((double) history_blocks *
			    (double) AREA0_PERCENT_SIZE), area1_last =
      (unsigned long) floor((double) history_blocks *
			    (double) (AREA0_PERCENT_SIZE +
				      AREA1_PERCENT_SIZE)), area2_last =
      history_blocks;

  double area0_theta =
      (area0_last > 0) ? ((AREA0_MAX_PROB - 0) / (area0_last - 0)) : 0,
      area1_theta =
      (area1_last >
       0) ? ((AREA1_MAX_PROB - AREA0_MAX_PROB) / (area1_last -
						  area0_last)) : 0,
      area2_theta = (1 - AREA1_MAX_PROB) / (area2_last - area1_last);

  if (block + 1 <= area0_last)
    return 0 + (double) (block + 1 - 0) * area0_theta;
  else if (block + 1 <= area1_last)
    return AREA0_MAX_PROB + (double) (block + 1 -
				      area0_last) * area1_theta;
  else
    return AREA1_MAX_PROB + (double) (block + 1 -
				      area1_last) * area2_theta;
}

char *state_filtering_queue::
QueryReadFront( /*unsigned long &states_for_each_block */ )
{
  unsigned long states_to_read =
      (unsigned long) ceil((filter_alpha * (double) history_len));
  unsigned long blocks_to_read =
      (unsigned long) ceil((double) states_to_read /
			   (double) history_block_len);
  //states_for_each_block = (unsigned long) ceil((double)states_to_read / (double)blocks_to_read);
  //unsigned long blocks_to_read = (unsigned long) ceil((filter_alpha * (double) history_blocks));

  unsigned long max_prob = 0;
  unsigned long i, j;
  static char *readvector = NULL;

  if (readvector != NULL)
    delete[]readvector;		//delete old set
  readvector = new char[history_blocks];

  memset(readvector, 0, sizeof(char) * history_blocks);

  for (i = 0; i < history_blocks; i++)
    max_prob += (unsigned long) (SelectionP(i) * 1000);

#if (DBG>10)
  fprintf(stderr,
	  "QueryReadFront(): BEGIN. states_to_read=%lu/%lu, blocks_to_read=%lu/%lu\n",
	  states_to_read, history_len, blocks_to_read, history_blocks);
#endif

  for (i = 0; i < blocks_to_read; i++) {
    unsigned long randseed = (random.next() % max_prob) /*+1 */ ;
    unsigned long sum_prob = 0;

#if (DBG>100)
    fprintf(stderr,
	    "QueryReadFront(): Begin selection loop for block %d. max_prob=%lu. randseed=%lu\n",
	    i, max_prob, randseed);
#endif

    for (j = 0; j < history_blocks; j++) {
      if (readvector[j] == 1)
	continue;		//skip already selected blocks
      if ((sum_prob += (unsigned long) (SelectionP(j) * 1000)) > randseed)
	break;			//this block is our target!
    }

#if (DBG>100)
    fprintf(stderr, "QueryReadFront(): block %d is #%lu with prob=%f\n", i,
	    j, SelectionP(j));
#endif

    readvector[j] = 1;		//mark chosen block
    max_prob -= (unsigned long) (SelectionP(j) * 1000);	//decrement max probability
  }

#if (DBG>10)
  fprintf(stderr, "QueryReadFront(): readvector=[");
  for (i = 0; i < history_blocks; i++)
    fprintf(stderr, "%d,", readvector[i]);
  fprintf(stderr, "]\n");
#endif

  return readvector;
}

void
 state_filtering_queue::DefineBlocks()
{
  unsigned long i;

  if (history_len <= BLOCK_MIN_SIZE) {
    history_blocks = 1;
    history_block_len = history_len;
  } else {
    for (i = BLOCK_MIN_SIZE; ceil(((double) history_len / (double) i)) > BLOCK_MAX_NUMBER; i += BLOCK_SIZE_STEP);	//empty loop

    history_blocks =
	(unsigned long) ceil(((double) history_len / (double) i));
    history_block_len = i;
  }

#if (DBG>100)
  fprintf(stderr,
	  "DefineBlocks(): history_blocks=%lu; history_block_len=%lu\n",
	  history_blocks, history_block_len);
#endif

}

void state_filtering_queue::Calibrate(unsigned long deleted_a,
				      unsigned long deleted_p)
{
  unsigned long i, j, jmax;
  double beta =
      ((double) ((deleted_a + deleted_p) - (deleted_a))) /
      ((double) (deleted_a + deleted_p));

#if (DBG>10)
  fprintf(stderr, "Calibrate(): alpha=%f, beta=%f\n", filter_alpha, beta);
#endif

  if (beta > NEUTRAL_ZONE_HI_BOUND) {
    //now filter_alpha can safely be set to 0
    filter_alpha += (filter_alpha != 0) ? (filter_alpha * 0.15) : (0.1);
  } else if (beta < NEUTRAL_ZONE_LO_BOUND) {
    filter_alpha -= filter_alpha * 0.15;
  }
  //ensure bounds :-)
  filter_alpha = min(max(filter_alpha, 0), 1);

#if (DBG>10)
  fprintf(stderr,
	  "**Calibrate(): deleted_a=%lu, deleted_p=%lu, adjusted alpha=%lg\n",
	  deleted_a, deleted_p, filter_alpha);
#endif

}

unsigned long
    state_filtering_queue::FilterTable(unsigned long states,
				       unsigned long *_totread)
{
#if __WORDSIZE == 32
  unsigned long buffer[4000];	//read 2000 signatures at a time
#else
  unsigned int buffer[4000];	//read 2000 signatures at a time
#endif
  unsigned long read, totread = 0, totdeleted = 0;
  unsigned long i;

#if (DBG > 10)
  fprintf(stderr, "FilterTable(): Progress: ");
#endif


#ifndef SPLITFILE
  while (!feof(history_file) && (totread < states)) {
    read =
#if __WORDSIZE == 32
	fread(buffer, sizeof(unsigned long) * 2, min(2000, states),
#else
	fread(buffer, sizeof(unsigned int) * 2, min(2000, states),
#endif
	      history_file);
#else
  while (!history_file->eof() && (totread < states)) {
    read =
#if __WORDSIZE == 32
	history_file->read(buffer, sizeof(unsigned long) * 2,
#else
	history_file->read(buffer, sizeof(unsigned int) * 2,
#endif
			   min(2000, states));
#endif
    totread += read;

#if (DBG > 10)
    fprintf(stderr, "FilterTable(): buffer read: ");
    for (i = 0; i < read * 2; i++)
      fprintf(stderr, "%lu, ", buffer[i]);
#endif

    for (i = 0; i < read; i++) {
      if (hashtable_lookup(buffer[i * 2], buffer[i * 2 + 1], false, true))
	totdeleted++;

#if (DBG > 10)
      fprintf(stderr, "#%lu", totread - read + i);
#endif


    }
  }

#if (DBG > 0)
  fprintf(stderr,
	  "FilterTable(): read %d states from disk, deleted %d states from memory\n",
	  totread, totdeleted);
#endif

  if (_totread != NULL)
    (*_totread) += totread;
  return totdeleted;
}

void
 state_filtering_queue::CheckTable()
{
#ifdef PAPER_COMPL
  CheckTable_full();
#else
  if (hashtable_first_full)
    CheckTable_full();
  else
    CheckTable_simple();
#endif
}

void state_filtering_queue::CheckTable_full()
{

  unsigned long totdeleted_a = 0, totdeleted_p = 0;
  bool calibrate = TRUE, something_not_in_front = FALSE;
  unsigned long i;
  unsigned long deleted_states[BLOCK_MAX_NUMBER];
  unsigned long read_states = 0;

  memset(deleted_states, 0, sizeof(unsigned long) * BLOCK_MAX_NUMBER);

#if (DBG > 0)
  fprintf(stderr, "******CheckTable_full(): Begin cleaning process...\n");
#endif

  DefineBlocks();

#if (DBG > 0)
  fprintf(stderr,
	  "CheckTable_full(): history_len=%lu, history_blocks=%d, history_block_len=%lu\n",
	  history_len, history_blocks, history_block_len);
#endif

  char *frontvector = QueryReadFront( /*states_for_each_block */ );
  calibrate = QueryCalibration();


//1. filter the state table using the memory history

  bool adjacent = FALSE;

  if (history_block_len > 0) {
    for (i = 0; i < history_blocks; i++) {
      if (calibrate || (frontvector[i] != 0)) {

	if (!adjacent)		//optimize adjacent seeks (not correct if we don't read all states in each block)
#ifndef SPLITFILE
#if __WORDSIZE == 32
	  fseek(history_file,
		(sizeof(unsigned long) * 2 * history_block_len) * i,
#else
	  fseek(history_file,
		(sizeof(unsigned int) * 2 * history_block_len) * i,
#endif
		SEEK_SET);
#else
	  history_file->
#if __WORDSIZE == 32
	      seek((sizeof(unsigned long) * 2 * history_block_len), i,
#else
	      seek((sizeof(unsigned int) * 2 * history_block_len), i,
#endif
		   SEEK_SET);
#endif

#if (DBG > 0)
	fprintf(stderr, "CheckTable_full(): seeking to %lu,%lu\n",
		sizeof(unsigned long) * 2 * history_block_len, i);
#endif

#if (DBG > 0)
	fprintf(stderr,
		"CheckTable_full(): Filtering with block #%lu (probability (usefulness) %0.2f)\n",
		i, SelectionP(i));
#endif
	//we have to remember the number of states deleted with each block to update the usefulness
	deleted_states[i] = FilterTable(history_block_len, &read_states);
	if (frontvector[i] != 0) {
	  totdeleted_a += deleted_states[i];
	} else {		/* (readvector[i]!=0) */

	  totdeleted_p += deleted_states[i];
	  something_not_in_front = TRUE;
	}
	adjacent = TRUE;
      } else {
	adjacent = FALSE;
      }
    }
  } else {
    calibrate = FALSE;
  }

#if (DBG > 0)
  fprintf(stderr, "CheckTable_full(): trying a calibration...\n");
#endif

  //reposition history_file pointer to enqueue new states
#ifndef SPLITFILE
  fseek(history_file, 0, SEEK_END);
#else
  history_file->seek(0, SEEK_END);
#endif

#ifndef PAPER_COMPL
//2. if the other part of the history has been completely read, we can do a calibration

  if (calibrate) {		//calibration requested

    bool in_critical_zone = (filter_alpha >= CRITICAL_ALPHA);

    if ((something_not_in_front) &&	//the front does not include all the blocks
	(totdeleted_a + totdeleted_p > 0)	//something was read!
	)
      Calibrate(totdeleted_a, totdeleted_p);

    if (in_critical_zone && (filter_alpha >= CRITICAL_ALPHA)) {
      //try to reset filter_alpha if it is too high
      filter_alpha =		//gdp: 30% prob of resetting filter_alpha to its initial value
	  ((random.next() % 1000) > 500) ? (INITIAL_ALPHA) : filter_alpha;
    }
  }
#endif

//3. move all the unchecked states that are present in the 
//   (filtered) unchecked table to the checked queue

  state_and_signature_pair *s;
  unsigned long moved = 0, deleted = 0;


#if (DBG > 0)
  fprintf(stderr, "CheckTable_full(): begin state migration...\n");
#endif

  while (!uncheckedQueue->isempty()) {
    s = uncheckedQueue->dequeue();

    if (hashtable_lookup(s->_signature[0], s->_signature[1], false, true)) {
      enqueue_checked(&(s->_state));
      moved++;			//for dbg only

#if (DBG > 10)
      fprintf(stderr, "CheckTable_full(): buffer written: %lu,%lu ",
	      s->_signature[0], s->_signature[1]);
#endif

#ifndef SPLITFILE
#if __WORDSIZE == 32		//Here and in related places, Unsigned32 should be used...
      fwrite(&(s->_signature[0]), sizeof(unsigned long), 1, history_file);
      fwrite(&(s->_signature[1]), sizeof(unsigned long), 1, history_file);
#else
      fwrite(&(s->_signature[0]), sizeof(unsigned int), 1, history_file);
      fwrite(&(s->_signature[1]), sizeof(unsigned int), 1, history_file);
#endif
#else
#if __WORDSIZE == 32
      history_file->write(&(s->_signature[0]), sizeof(unsigned long), 1);
      history_file->write(&(s->_signature[1]), sizeof(unsigned long), 1);
#else
      history_file->write(&(s->_signature[0]), sizeof(unsigned int), 1);
      history_file->write(&(s->_signature[1]), sizeof(unsigned int), 1);
#endif
#endif
      history_len++;

    } else {
      deleted++;
    }
  }

#if (DBG > 0)
  fprintf(stderr,
	  "CheckTable_full(): moved %lu states to the checked queue\n",
	  moved);
#endif

//4. clear the unchecked table (the unchecked queue is already empty)

  unsigned long size =
      (unsigned long) ((double) (hashtable_size) * args->num_bits.value /
		       BITUNSIGNED) + 3;
  for (i = 0; i < size; i++)
    filterTable[i] = (Unsigned32) 0;

  Full->clearall();
  Removed->clearall();
  hashtable_num_elts = 0;

  last_deleted_states += deleted;

#if (DBG > 0)
  fprintf(stderr, "******CheckTable_full(): Complete.\n");
#endif

}

void state_filtering_queue::CheckTable_simple()
{

  unsigned long totdeleted_a = 0, totdeleted_p = 0;
  bool calibrate = TRUE, something_not_in_front = FALSE;
  unsigned long i;

#if (DBG > 0)
  fprintf(stderr,
	  "******CheckTable_simple(): Begin cleaning process...\n");
#endif

//1. move all the unchecked states in the checked queue

  state_and_signature_pair *s;
  unsigned long moved = 0;

#if (DBG > 0)
  fprintf(stderr, "CheckTable_simple(): begin state migration...\n");
#endif

  while (!uncheckedQueue->isempty()) {
    s = uncheckedQueue->dequeue();
    enqueue_checked(&(s->_state));
    moved++;			//for dbg only

#if (DBG > 10)
    fprintf(stderr, "CheckTable_simple(): buffer written: %lu,%lu ",
	    s->_signature[0], s->_signature[1]);
#endif

#ifndef SPLITFILE
#if __WORDSIZE == 32
    fwrite(&(s->_signature[0]), sizeof(unsigned long), 1, history_file);
    fwrite(&(s->_signature[1]), sizeof(unsigned long), 1, history_file);
#else
    fwrite(&(s->_signature[0]), sizeof(unsigned int), 1, history_file);
    fwrite(&(s->_signature[1]), sizeof(unsigned int), 1, history_file);
#endif
#else
#if __WORDSIZE == 32
    history_file->write(&(s->_signature[0]), sizeof(unsigned long), 1);
    history_file->write(&(s->_signature[1]), sizeof(unsigned long), 1);
#else
    history_file->write(&(s->_signature[0]), sizeof(unsigned int), 1);
    history_file->write(&(s->_signature[1]), sizeof(unsigned int), 1);
#endif
#endif
    history_len++;
  }

#if (DBG > 0)
  fprintf(stderr,
	  "CheckTable_simple(): moved %lu states to the checked queue\n",
	  moved);
#endif
}

unsigned long
#if __WORDSIZE == 32
state_filtering_queue::signature_hash(unsigned long t1, unsigned long t2)
#else
state_filtering_queue::signature_hash(unsigned int t1, unsigned int t2)
#endif
{

  unsigned long i, total, base;
#if __WORDSIZE == 32
  char data[sizeof(unsigned long) * 2];

  memcpy(&(data[0]), &t1, sizeof(unsigned long));
  memcpy(&(data[sizeof(unsigned long)]), &t2, sizeof(unsigned long));
#else
  char data[sizeof(unsigned int) * 2];

  memcpy(&(data[0]), &t1, sizeof(unsigned int));
  memcpy(&(data[sizeof(unsigned int)]), &t2, sizeof(unsigned int));
#endif

#if (DBG > 10)
  fprintf(stderr,
	  "signature_hash: creating hashkey from t1=%lu and t2=%lu\n", t1,
	  t2);
#endif

  base = 1u;
  total = data[0] % (hashtable_size);

#if __WORDSIZE == 32
  for (i = 1; i < (sizeof(unsigned long) * 2); i++) {
#else
  for (i = 1; i < (sizeof(unsigned int) * 2); i++) {
#endif
    base =
	(((UINT_MAX % hashtable_size +
	   1) % hashtable_size) * base) % hashtable_size;
    total =
	(total +
	 (base * (data[i] % hashtable_size)) % hashtable_size) %
	hashtable_size;
  }

  return (total);
}

//*****************************************************************************

state_and_signature_queue::state_and_signature_queue(unsigned long mas)
:  max_active_states(mas)
{
  stateArray = new state_and_signature_pair[max_active_states];

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
       (paging_file_top->make_unique_filename(SSQ_PAGING_FILE_TOP),
	"w+b"))) {
    Error.Notrace("Internal: Error creating top paging file for s_s_q.");
  }

  if (!
      (paging_file_bottom->open
       (paging_file_bottom->make_unique_filename(SSQ_PAGING_FILE_BOTTOM),
	"w+b"))) {
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


state_and_signature_queue::~state_and_signature_queue()
{
  delete[OLD_GPP(max_active_states)] stateArray;	// Should be delete[].

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

int
 state_and_signature_queue::BytesForOneState(void)
{
  return sizeof(state_and_signature_pair);
}


void state_and_signature_queue::Print(void)
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


void state_and_signature_queue::enqueue(state_and_signature_pair * &e)
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
  e = &stateArray[tail_begin + rear];

#if (DBG > 1)
  fprintf(stderr, "\nenqueue(ssq): enqueued state %lu,%lu ",
	  e->_signature[0], e->_signature[1]);
#endif

  rear++;
  num_elts_tail++;
}

state_and_signature_pair *state_and_signature_queue::dequeue(void)
{
  state_and_signature_pair *retval;

  if (num_elts_head <= 0) {
    QueueEmptyFault();
#if (DBG > 1)
    fprintf(stderr, "\ndequeue(ssq): queue empty fault");
#endif
  }

  retval = &stateArray[head_begin + front];
  front++;
  num_elts_head--;

#if (DBG > 1)
  fprintf(stderr, "\ndequeue(ssq): dequeued state %lu,%lu ",
	  retval->_signature[0], retval->_signature[1]);
#endif

  return retval;
}

state_and_signature_pair *state_and_signature_queue::top(void)
{
  if (num_elts_head <= 0) {
    QueueEmptyFault();
  }

  return &stateArray[head_begin + front];
}

void state_and_signature_queue::ReclaimFreeSpace()
{
#ifndef SPLITFILE
  global_rear +=
      fwrite(&stateArray[tail_begin], sizeof(state_and_signature_pair), tail_size,
	     paging_file_bottom);

#else
  global_rear +=
      paging_file_bottom->write(&stateArray[tail_begin],
				sizeof(state_and_signature_pair),
				tail_size);
#endif

  num_elts_tail = 0;
  rear = 0;
}


void state_and_signature_queue::QueueEmptyFault()
{
#ifndef SPLITFILE
  size_t read =
      fread(&stateArray[head_begin], sizeof(state_and_signature_pair),
	    min(global_front, head_size),
	    paging_file_top);
#else
  size_t read = paging_file_top->read(&stateArray[head_begin],
				      sizeof(state_and_signature_pair),
				      min(global_front, head_size));
#endif

  if (read > 0) {		//ok, some states are swapped in
    num_elts_head = read;
    global_front -= read;
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

    size_t read = fread(&stateArray[head_begin], sizeof(state_and_signature_pair), head_size,
			paging_file_top);

    num_elts_head = read;
    global_front -= read;
#else
    splitFile *fswap;

    //swap files
    fswap = paging_file_top;
    paging_file_top = paging_file_bottom;
    paging_file_bottom = fswap;

    paging_file_top->seek(0, SEEK_SET);	//move to the beginning of the queue
    paging_file_bottom->seek(0, SEEK_SET);	//reset bottom queue

    global_front = global_rear;
    global_rear = 0;		//bottom file is empty

    //now bottom entries are top entries and bottom file is empty. Reload a block!
    size_t read = paging_file_top->read(&stateArray[head_begin],
					sizeof(state_and_signature_pair),
					min(global_front, head_size));

    num_elts_head = read;
    global_front -= read;
#endif
  } else if (num_elts_tail > 0) {	//paging_file_top AND paging_file_bottom are empty
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
