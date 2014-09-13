%{ 

/**LexFile*********************************************************************

  FileName    [mu.l]

  Synopsis    [File for flex]

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

#define yywrap() 1
#define YY_SKIP_YYWRAP

%}

%x		comment lrcomment

LETTER		[a-zA-Z_]
DIGIT		[0-9]
ID		({LETTER}({LETTER}|{DIGIT})*)
INTEGER		({DIGIT}+)
STRING	  (\"[^"\n]*\")
REAL		({DIGIT}+"."{DIGIT}+)

%%
[ \t\f]		;
[\n]		{ gLineNum++; }



".."		{ return(DOTDOT); }
"==>"		{ return(LONGARROW); }
":="		{ return(ASSIGN); }
"<="		{ return(LEQ); }
"!="		{ return(NEQ); }
">="		{ return(GEQ); }
"!"		{ return( NOT ); }
"!!"		{ return( PCTLNOT ); }
"->"		{ return( IMPLIES ); }
"->>"		{ return( PCTLIMPLIES ); }
"&&"		{ return( PCTLAND ); }
"||"		{ return( PCTLOR ); }

{ID}		{ /* also catches reserved words. rlm. */ 
		  lexid *temp;
		  if( strlen(yytext) > IDLEN ) {
		    Error.Error( "Identifier %s too long.", yytext);
		  }
		  if( yytext[0] == '_' ) {
		    Error.Error("Identifiers beginning with an underscore are reserved by the system.");
		  }
		  temp = ltable.enter(yytext);
		  yylval.lex = temp;
		  if ( temp->getlextype() == OLDEND )
		    {
		      Error.Error("All types of End* have been replaced with just 'End'.");
		      return (END);
		    }
		  else return( temp->getlextype() );
		}

{INTEGER}	{	
		  sscanf( yytext, "%d", &(yylval.integer) );
		  return(INTCONST);
		}

{STRING}	{
		  yylval.string = new char[ yyleng ];
		  strcpy(yylval.string,yytext + 1); /* Dup w/o leading ". */
		  yylval.string [ yyleng - 2 ] = '\0';
		  return(STRING);
		}

{REAL}		{  
		  sscanf( yytext, "%le", &(yylval.real) );
		  return(REALCONST);
		}
 
[-;,.()\+=:\[\]\"<>*/|&\{\}?\%]	{ return( yytext[0] ); }

"--"		{	
		  BEGIN comment;
		}

<comment>.		;
<comment>\n	{
		  gLineNum++;
		  BEGIN (INITIAL);
		}


"/*"		{	
		  BEGIN lrcomment;
   /* Only active in normal state, because nested comments not allowed. */
   /* Comment-handling code copied from the \'flexdoc\' man page. */
		}


<lrcomment>[^*\n]*	/* eat anything that\'s not a '*' */
<lrcomment>"*"+[^*/\n]* /* eat up *\'s not followed by '/'s */
<lrcomment>\n		{	gLineNum++; }
<lrcomment>"*"+"/"	{	BEGIN(INITIAL);	}


.			{	/* No other rule applies, so it's a bad token */
 		 		Error.Error( "Bad input character `%s'.", yytext);
 			}

%%

void
LexInit( int listingSize ) {
/*  BEGIN norm; */
};

