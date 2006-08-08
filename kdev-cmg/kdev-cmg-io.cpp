/* This file is part of kdev-cmg
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>
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
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "kdev-cmg.h"

#include <iostream>
#include "kdev-cmg-decoder.h"

std::size_t _G_token_begin, _G_token_end;
extern char* yytext;

int yylex();
void lexer_restart(kdevcmg::parser* parser);
void print_token_environment(kdevcmg::parser* parser);


namespace kdevcmg
{

void parser::tokenize()
{
  ::lexer_restart(this);

  int kind = parser::Token_EOF;
  do
    {
      kind = ::yylex();
      //std::cerr << yytext << std::endl; //" "; // debug output

      if (!kind) // when the lexer returns 0, the end of file is reached
        kind = parser::Token_EOF;

      parser::token_type &t = this->token_stream->next();
      t.kind = kind;
      t.begin = _G_token_begin;
      t.end = _G_token_end;
      t.text = _G_system.contents;
    }
  while (kind != parser::Token_EOF);

  this->yylex(); // produce the look ahead token
}


void parser::report_problem( parser::problem_type type, std::string message )
{
  report_problem( type, message.c_str() );
}

void parser::report_problem( parser::problem_type type, const char* message )
{
  if (type == error)
    std::cerr << "** ERROR: " << message << std::endl;
  else if (type == warning)
    std::cerr << "** WARNING: " << message << std::endl;
  else if (type == info)
    std::cerr << "** Info: " << message << std::endl;
}


// custom error recovery
void parser::yy_expected_token(int /*expected*/, std::size_t where, char const *name)
{
  print_token_environment(this);
  report_problem(
    parser::error,
    std::string("Expected token ``") + name
      //+ "'' instead of ``" + current_token_text
      + "''"
  );
}

void parser::yy_expected_symbol(int /*expected_symbol*/, char const *name)
{
  print_token_environment(this);
  report_problem(
    parser::error,
    std::string("Expected symbol ``") + name
      //+ "'' instead of ``" + current_token_text
      + "''"
  );
}

} // end of namespace kdevcmg

