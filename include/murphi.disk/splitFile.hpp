/**CHeaderFile*****************************************************************

  FileName    [mu_splitFile.hpp]

  Synopsis    [Header file for file splitting]

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

#ifndef _SPLITFILE_
#define _SPLITFILE_

#define DEFAULTDIR 0
#define FORWARD 1
#define BACKWARD 2

class splitFile {
public:
  splitFile(unsigned long splitsize, bool permanent = true);
  ~splitFile();
  bool open(const char *filename, const char *access);
  void close();
  unsigned long read(void *buffer, unsigned long size,
		     unsigned long count);
  unsigned long write(void *buffer, unsigned long size,
		      unsigned long count);
  unsigned long tell(unsigned long size = 1);
  void seek(unsigned long size, unsigned long count, int from,
	    int direction = DEFAULTDIR);
  void seek(unsigned long count, int from);
  bool eof();
  char *getBaseFileName() {
    return _filename;
  } void setPermanent(bool perm) {
    _permanent = perm;
  }
  const char *make_unique_filename(const char *basepathname);

protected:
  void CreateNextPart();
  bool OpenNextPart();
  bool GotoNextPart(bool write_mode);
  inline unsigned long curfilepos();
  inline unsigned long getpartsize(int npart);
  unsigned long writebytes(void *buffer, unsigned long size);
  unsigned long readbytes(void *buffer, unsigned long size);
  bool seekbytes(unsigned long size, int direction, int &part,
		 unsigned long &skip);

private:
  char _access[10];
  char _filename[1020];
  bool _permanent;
  FILE *parts[100];
  unsigned long partsize[100];
  int maxpart, curpart;
  unsigned long _splitsize;
  bool _eof;

  /* check for type size invariants only once */
  static bool sizechecks;
};

#endif
