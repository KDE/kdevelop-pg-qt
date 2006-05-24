%{
/* This file is part of kdev-pg
   Copyright (C) 2006 Jakob Petsovits <jpetso@gmx.at>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#include <iostream>
#include <cstdio>
#include "kdev-pg.h"
#include "kdev-pg-parser.h"

int inp();
void append_linebuffer();
void newline();
void yyerror(char const *);

#define YY_INPUT(buf, result, max_size) \
  { \
    char c = inp(); \
    result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
  }

#define YY_USER_ACTION  append_linebuffer();

#define COPY_TO_YYLVAL(string, len) \
  yylval.str = (char*) calloc(yyleng+1, sizeof(char)); \
  strcpy(yylval.str, string); \
  yylval.str[len] = '\0';

%}

Whitespace  [ \f\t]
Newline     "\r\n"|\r|\n

%x CODE
%x STRING
%x MEMBER

%%


{Whitespace}*           /* skip */ ;
{Newline}               newline();
"--"[^\r\n]*            /* line comments, skip */ ;

";;"                    return ';';
"->"                    return T_ARROW;

"("                     return '(';
")"                     return ')';
","                     return ',';
"0"                     return '0';
"#"                     return '#';
"."                     return '.';
":"                     return ':';
"="                     return '=';
"+"                     return '+';
"*"                     return '*';
"?"                     return '?';
"@"                     return '@';
"|"                     return '|';

"%token"                return T_TOKEN_DECLARATION;
"%token_stream"         return T_TOKEN_STREAM_DECLARATION;
"%member"               BEGIN(MEMBER); return T_MEMBER_DECLARATION;


<MEMBER>{
{Whitespace}*           /* skip */ ;
{Newline}               newline();
"("                     return '(';
":"                     return ':';
"public"                return T_PUBLIC;
"private"               return T_PRIVATE;
"protected"             return T_PROTECTED;
"declaration"           return T_DECLARATION;
"constructor"           return T_CONSTRUCTOR;
"destructor"            return T_DESTRUCTOR;
[_a-zA-Z0-9]+           COPY_TO_YYLVAL(yytext,yyleng); return T_IDENTIFIER;
")"                     BEGIN(INITIAL); return ')';
.                       BEGIN(INITIAL); REJECT; /* everything else */
}


"[:"                    BEGIN(CODE);
<CODE>{
{Newline}               newline(); yymore();
[^:\n\r]*               yymore(); /* gather everything that's not a colon, and append what comes next */
":"+[^:\]\n\r]*         yymore(); /* also gather colons that are not followed by colons or newlines */
":]" {
    COPY_TO_YYLVAL(yytext,yyleng-2); /* cut off the trailing stuff */
    BEGIN(INITIAL);
    return T_CODE;
}
<<EOF>> {
    BEGIN(INITIAL); // is not set automatically by yyrestart()
    std::cout << "Encountered end of file in an unclosed block comment..." << std::endl;
    yyerror("");
    return 0;
}
}


[_A-Z]+                 COPY_TO_YYLVAL(yytext,yyleng); return T_TERMINAL;
[_a-zA-Z0-9]+           COPY_TO_YYLVAL(yytext,yyleng); return T_IDENTIFIER;


\"([^\r\n\"]|\\[^\r\n])*\" {
   yytext++;                         /* start inside the quotes */
   COPY_TO_YYLVAL(yytext,yyleng-2);  /* cut off the trailing quote */
   return T_STRING;
}
 /*/
\"                      BEGIN(STRING);
<STRING>{
[^\r\n\"]*\" {
   BEGIN(INITIAL);
   COPY_TO_YYLVAL(yytext,yyleng-1);
   return T_STRING;
}
.                       BEGIN(INITIAL); REJECT; /* everything else *
}
 */

. {
  std::cout << "Unexpected character: ``" << yytext[0] << "''" << std::endl;
  yyerror("");
}


%%

extern FILE *file;

int ch = 0;
int yy_line = 1, current_offset = 0;
bool end_of_line = false;
char yy_text_line[256 * 1024];

int inp()
{
  return ch = fgetc(file);
}

void newline()
{
  yy_line++;
  end_of_line = true;
}

/* initialize the line buffer */
void clear_linebuffer()
{
  yy_text_line[0] = '\0';
  current_offset = 0;
  end_of_line = false;
}

 /* add the current token to the current line */
void append_linebuffer()
{
  if (end_of_line == true)
    clear_linebuffer();

  current_offset = strlen(yy_text_line); /* start of current */
  strcpy(yy_text_line+current_offset, yytext); /* append current */
  /* strcpy is faster than strcat */
}

void yyerror(char const *)
{
  std::cerr << "** SYNTAX ERROR at line " << yy_line << " column " << current_offset << std::endl;

  char *current_end = yy_text_line + strlen(yy_text_line);
  char *p;

  /* get the rest of the line if we are not already at the end */
  if(!end_of_line)
    {
      p = current_end;
      int c;

      do {
        c = inp();
        *p++ = c;
      } while(c != '\n');

      *p = 0;
    }

  /* yy_text_line[] now has the whole line, with the current token */
  /* at current_offset */

  /* print error message and current line */
  std::cerr << yy_text_line;

  /* print a ^ under the most recent token */
  for (int i = 0; i < current_offset; i++)
    std::cerr << " ";

  std::cout << "^" << std::endl; /* current_offset spaces, then ^ */

  exit(EXIT_FAILURE);
}

int yywrap() { return 1; }

