/**CFile***********************************************************************

  FileName    [mu_splitFile.cpp]

  Synopsis    [File for file splitting]

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

/*
 * This file handling class was designed to fix a problem with
 * Linux EXT2 filesystem, that does not handle by default files
 * larger that 1Gb. This problem could also appear on other
 * filesystems, so I decided to write a file class that handles
 * very large "virtual" files storing them on many smaller files.
 * The splitFile class has methods to handle all the normal file
 * operations. Moreover, all the disk-access routines specify
 * lengths (i.e. number of bytes to read, position to seek...)
 * using two unsigned long integers: size and count. The number
 * of bytes requested, e.g. the position to seek to in the file,
 * is size*count.
 *
 * WARNING: the class has been tested in disk murphi only.
 * Some minor functions can still contain bugs.
 * 
 */

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

//Max # of parts handled by the splitFile class
//Adjust to match your needs
#define MAX_PARTS 200

/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
*/

#include "murphi.disk/splitFile.hpp"

bool splitFile::sizechecks = false;

/*
 * Creates (but not opens) a spliFile.
 * The file will be subdivided in several files,
 * each with a length <= slitsize.
 * If permanent is false, the split file will be
 * deleted when closed.
 *
 */
splitFile::splitFile(unsigned long splitsize,
		     bool permanent):_splitsize(splitsize), maxpart(-1),
curpart(-1), _eof(true), _permanent(permanent)
{

  if (sizechecks == false) {
    if (sizeof(char) != 1) {
      fprintf(stderr, "splitFile: error: sizeof(char) != 8");
      exit(10);
    }

    if (sizeof(unsigned long) > sizeof(size_t)) {
      fprintf(stderr,
	      "splitFile: waning: size_t type is smaller than unsigned long!");
    }

    sizechecks = true;
  }

  memset(parts, 0, sizeof(FILE *) * MAX_PARTS);
}

splitFile::~splitFile()
{
  close();
}

/* watch out - works only for splitFile; for generic use don't extend with 00 */
const char *splitFile::make_unique_filename(const char *basepathname)
{
  static char filenamebuffer[500];
  char filename[505];
  FILE *h;

  srand((unsigned) time(NULL));

  char *tmp, *prev, buffer[4096];
  strcpy(buffer, PROTOCOL_NAME);
  tmp = strtok(buffer, "/");
  while (tmp != NULL) {
    prev = tmp;
    tmp = strtok(NULL, "/");
  }

  do {
    sprintf(filenamebuffer, "%s_%s_%d.swp",
	    basepathname, prev, rand());

    //append the splitFile extension
    sprintf(filename, "%s.00", filenamebuffer);
    h = fopen(filename, "rb");
    if (h != NULL)
      fclose(h);

  } while (h != NULL);

  return filenamebuffer;
}

void splitFile::CreateNextPart()
{
  char filename[1024];
  sprintf(filename, "%s.%02d", _filename, maxpart + 1);

  if (maxpart >= MAX_PARTS) {
    fprintf(stderr, "splitFile: file %s has too many sections", filename);
    exit(10);
  }

  if ((parts[++maxpart] = fopen(filename, _access)) == NULL) {
    fprintf(stderr, "splitFile: error creating next section of file: %s",
	    filename);
    exit(10);
  }
  curpart = maxpart;
  partsize[curpart] = 0;
}

bool splitFile::OpenNextPart()
{
  char filename[1024];
  sprintf(filename, "%s.%02d", _filename, maxpart + 1);
  unsigned long thispartsize;


  FILE *dummy;

  if ((dummy = fopen(filename, "r")) == NULL)
    return false;
  fseek(dummy, 0, SEEK_END);
  thispartsize = ftell(dummy);
  fclose(dummy);

  if (maxpart >= MAX_PARTS) {
    fprintf(stderr, "splitFile: file %s has too many sections", filename);
    exit(10);
  }

  if ((parts[++maxpart] = fopen(filename, _access)) == NULL) {
    fprintf(stderr, "splitFile: error opening next section of file: %s",
	    filename);
    exit(10);
  }

  curpart = maxpart;
  partsize[curpart] = thispartsize;
  return true;
}


bool splitFile::GotoNextPart(bool write_mode)
{
  if (parts[curpart + 1] == NULL) {
    if (write_mode)
      CreateNextPart();
    else
      return false;
  } else {
    curpart += 1;
    fseek(parts[curpart], 0, SEEK_SET);
  }
  return true;
}


unsigned long splitFile::curfilepos()
{
  return ftell(parts[curpart]);
}


unsigned long splitFile::getpartsize(int npart)
{
  /*
     if (npart == curpart)
     return max(ftell(parts[curpart]),partsize[curpart]));
     else 
   */
  return partsize[npart];
}


bool splitFile::open(const char *filename, const char *access)
{
  strcpy(_access, access);
  strcpy(_filename, filename);
  if (strchr(access, 'r'))
    while (OpenNextPart());
  if (maxpart < 0)
    CreateNextPart();
  curpart = 0;

  //if the file was opened with read as primary mode (r+)
  //then ignore the user specified permanent flag and do not delete
  //the opened file!
  if (strchr(access, 'r'))
    setPermanent(true);
  return true;
}

void splitFile::close()
{
  //all the file parts are opened and registered in the parts array
  char filename[1024];
  for (int i = 0; i <= maxpart; i++) {
    if (parts[i] != NULL) {
      fclose(parts[i]);
      if (!_permanent) {
	sprintf(filename, "%s.%02d", _filename, i);
	remove(filename);
      }
    }
  }

  memset(parts, 0, sizeof(FILE *) * MAX_PARTS);
  maxpart = -1;
  curpart = -1;
  _eof = true;
}

/*
 * splitFile read and write routines are identical to the
 * corresponding FILE* versions.
 * 
 */

unsigned long splitFile::writebytes(void *buffer, unsigned long size)
{
  unsigned long inthispart, towrite, totalwritten = 0, reminder = 0;
  unsigned long pp = 0;

  while (size > 0) {
    inthispart = (_splitsize - curfilepos());
    //fprintf(stderr,"writebytes: curpart=%d, _splitize=%d, curfilepos=%d, size=%d, inthispart=%d\n",curpart,_splitsize,curfilepos(),size,inthispart);
    towrite = min(size, inthispart);
    fwrite(((char *) buffer) + pp, 1, towrite, parts[curpart]);
    size -= towrite;
    totalwritten += towrite;
    pp += towrite;

    if (ftell(parts[curpart]) > partsize[curpart])
      partsize[curpart] = ftell(parts[curpart]);

    if (size > 0)
      GotoNextPart(true);
  }

  return totalwritten;
}



unsigned long
    splitFile::write(void *buffer, unsigned long size, unsigned long count)
{
  unsigned long totalwritten = 0;
  unsigned long pp = 0;

  _eof = false;

  while (count > totalwritten) {
    writebytes(((char *) buffer) + pp, size);
    pp += size;
    totalwritten++;
  }

  return totalwritten;
}

unsigned long
 splitFile::readbytes(void *buffer, unsigned long size)
{
  unsigned long inthispart, toread, read, totalread = 0, reminder = 0;
  unsigned long pp = 0;

  while (size > 0) {
    inthispart = (partsize[curpart] - curfilepos());
    toread = min(size, inthispart);
    read = fread(((char *) buffer) + pp, 1, toread, parts[curpart]);
    size -= read;
    totalread += read;
    pp += read;
    if (size > 0) {
      if (read == toread) {
	if (!GotoNextPart(false)) {
	  _eof = true;
	  break;
	}
      } else {
	_eof = true;
	break;
      }
    }
  }

  return totalread;
}

unsigned long
    splitFile::read(void *buffer, unsigned long size, unsigned long count)
{
  unsigned long read, totalread = 0;
  unsigned long pp = 0;

  while (count > totalread) {
    read = readbytes(((char *) buffer) + pp, size);
    pp += read;
    if (read != size)
      break;			//eof
    totalread++;
  }

  return totalread;
}

/*
 * splitFile seek takes two unsigned parameters to specify
 * the position - like read and write.
 * The two-argument version assumes that the size is 1 byte
 * (so actually it works like the FILE* seek function)
 * To specify the seek direction, you can use the optional fourth
 * parameter and set it to FORWARD or BACKWARD (default is DEFAULDIR, see below).
 * WARNING: by default seeking from SEEK_END assumes backward direction
 * (i.e. you should not write seek(-5,SEEK_END) to move backward, but
 * seek(5,SEEK_END)), whileas SEEK_SET and SEEK_CUR assume FORWARD direction.
 *
 */
void
 splitFile::seek(unsigned long count, int from)
{
  seek(1, count, from);
}



bool splitFile::seekbytes(unsigned long size, int direction, int &part,
			  unsigned long &skip)
{
  int i;

//    fprintf(stderr,"seekbytes-call: part=%d, skip=%d\n",part,skip);                    

  while (size > 0) {
    if (getpartsize(part) - skip > size) {
      skip += size;
//        fprintf(stderr,"seekbytes: part=%d, skip=%d, TRUE\n",part,skip);                
      return true;
    } else {
      size -= (getpartsize(part) - skip);
      if (direction == FORWARD) {
	if (part < maxpart) {
	  skip = 0;
	  part++;
	} else {
	  skip = getpartsize(part);
//        fprintf(stderr,"seekbytes: part=%d, skip=%d, FALSE\n",part,skip);                    
	  return false;
	}
      } else if (direction == BACKWARD) {
	if (part > 0) {
	  skip = 0;
	  part--;
	} else {
	  skip = 0;
//        fprintf(stderr,"seekbytes: part=%d, skip=%d, FALSE\n",part,skip);                                        
	  return false;
	}
      }
    }
  }

//       fprintf(stderr,"seekbytes: part=%d, skip=%d, TRUE\n",part,skip);                
  return true;
}

void splitFile::seek(unsigned long size, unsigned long count, int from,
		     int direction)
{
  int part, i;
  unsigned long skip = 0;
  bool result = true;

  if (from == SEEK_SET) {
    part = 0;
    if (direction == DEFAULTDIR)
      direction = FORWARD;
    skip = 0;
  } else if (from == SEEK_END) {
    part = maxpart;
    if (direction == DEFAULTDIR)
      direction = BACKWARD;
    skip = 0;
  } else {			//SEEK_CUR
    part = curpart;
    if (direction == DEFAULTDIR)
      direction = FORWARD;
    if (direction == FORWARD)
      skip = curfilepos();
    else
      skip = getpartsize(part) - curfilepos();
  }

  for (i = 0; (i < count) && result; i++)
    result = seekbytes(size, direction, part, skip);


  curpart = part;

  if (direction == FORWARD) {
    fseek(parts[curpart], skip, SEEK_SET);
  } else if (direction == BACKWARD) {
    fseek(parts[curpart], -skip, SEEK_END);
  }
//      fprintf(stderr,"seek: part=%d, skip=%d, result=%d, curfilepos=%d\n",part,skip,result,curfilepos());                

  _eof = false;
}

/*
 * splitFile tell returns the number of blocks of the sepcified size
 * that precede the current file pointer. If size is not specified,
 * the default is 1 byte, so tell acts like the standard ftell
 * WARNING: if size is too small, the returned value may overflow
 * WARNING: if the current file pointer is not a multiple of size,
 * the returned value is rounded at the previous block.
 *
 */
unsigned long splitFile::tell(unsigned long size)
{
  unsigned long total = 0, skip = 0;
  for (int i = 0; i < curpart; i++) {
    total += (getpartsize(i) + skip) / size;
    skip = (getpartsize(i) + skip) % size;
  }

  return total + ((curfilepos() + skip) / size);
}


bool splitFile::eof()
{
  return _eof;
}
