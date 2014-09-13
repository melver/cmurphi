/**CFile***********************************************************************

  FileName    [error.cpp]

  Synopsis    [File for errors]

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
#include <stdarg.h>
#include <iostream>
using namespace std;

/********************
  class Error_handler
  ********************/
Error_handler::Error_handler(void)
:numerrors(0), numwarnings(0)
{
}

void Error_handler::vError(const char *fmt, va_list argp)
{
  cout.flush();
  fprintf(stderr, "%s:%d:", gFileName, gLineNum);
  vfprintf(stderr, fmt, argp);
  fprintf(stderr, "\n");
  numerrors++;
}

void Error_handler::Error(const char *fmt, ...)
{
  va_list argp;
  va_start(argp, fmt);
  vError(fmt, argp);
  va_end(argp);
}

bool Error_handler::CondError(const bool test, const char *fmt, ...)
{
  if (test) {
    va_list argp;
    va_start(argp, fmt);
    vError(fmt, argp);
    va_end(argp);
  }
  return test;
}

void Error_handler::FatalError(const char *fmt, ...)
{
  cout.flush();
  va_list argp;
  va_start(argp, fmt);
  vfprintf(stderr, fmt, argp);
  fprintf(stderr, "\n");
  fflush(stderr);
  va_end(argp);			/* This doesn\'t matter much, does it? */
  exit(1);
}

void Error_handler::vWarning(const char *fmt, va_list argp)
{
  cout.flush();
  fprintf(stderr, "%s:%d: warning: ", gFileName, gLineNum);
  vfprintf(stderr, fmt, argp);
  fprintf(stderr, "\n");
  numwarnings++;
}

void Error_handler::Warning(const char *fmt, ...)
{
  va_list argp;
  va_start(argp, fmt);
  vWarning(fmt, argp);
  va_end(argp);
}

bool Error_handler::CondWarning(const bool test, const char *fmt, ...)
{
  if (test) {
    va_list argp;
    va_start(argp, fmt);
    vWarning(fmt, argp);
    va_end(argp);
  }
  return test;
}

/********************
  declare Error_handler instances
  ********************/
Error_handler Error;

