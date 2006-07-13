/***************************************************************************
 *   Copyright (C) 2006 by Jakob Petsovits                                 *
 *   jpetso@gmx.at                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

// This file is meant to be specific to the framework in which the parser
// operates, and is likely to be adapted for different environments.
// For example, the text source in KDevelop might be different to the one in
// a command line parser, and error output might not always go to std::cerr.


#include "csharp.h"
#include "csharp_pp.h"

#include <iostream>

extern char *_G_contents;
std::size_t _G_token_begin, _G_token_end;
extern char* yytext;

int yylex();
void lexer_restart(csharp* parser);


void csharp::tokenize()
{
  ::lexer_restart(this);

  int kind = csharp::Token_EOF;
  do
    {
      kind = ::yylex();
      //std::cerr << yytext << std::endl; //" "; // debug output

      if (!kind) // when the lexer returns 0, the end of file is reached
        kind = csharp::Token_EOF;

      csharp::token_type &t = this->token_stream->next();
      t.kind = kind;
      t.begin = _G_token_begin;
      t.end = _G_token_end;
      t.text = _G_contents;
    }
  while (kind != csharp::Token_EOF);

  this->yylex(); // produce the look ahead token
}


void csharp::report_problem( csharp::problem_type type, std::string message )
{
  report_problem( type, message.c_str() );
}

void csharp::report_problem( csharp::problem_type type, const char* message )
{
  if (type == error)
    std::cerr << "** ERROR: " << message << std::endl;
  else if (type == warning)
    std::cerr << "** WARNING: " << message << std::endl;
  else if (type == info)
    std::cerr << "** Info: " << message << std::endl;
}


bool csharp_pp::tokenize()
{
  int kind = csharp_pp::Token_EOF;
  do
    {
      kind = ::yylex();
      //std::cerr << "pp: " << yytext << std::endl; //" "; // debug output

      csharp_pp::token_type &t = this->token_stream->next();
      t.kind = kind;
      t.begin = _G_token_begin;
      t.end = _G_token_end;
      t.text = _G_contents;

      if (kind == csharp_pp::Token_EOF)
        return false; // we neither want nor expect this in a preprocessor line
    }
  while (kind != csharp_pp::Token_PP_NEW_LINE);

  csharp::token_type &t = this->token_stream->next();
  t.kind = csharp_pp::Token_EOF;
  t.begin = _G_token_begin;
  t.end = _G_token_end;
  t.text = _G_contents;

  this->yylex(); // produce the look ahead token
}

void csharp_pp::add_token( csharp_pp::token_type_enum token_kind )
{
  //std::cerr << "pp: " << yytext << std::endl; //" "; // debug output
  csharp_pp::token_type &t = this->token_stream->next();
  t.kind = token_kind;
  t.begin = _G_token_begin;
  t.end = _G_token_end;
  t.text = _G_contents;
}
