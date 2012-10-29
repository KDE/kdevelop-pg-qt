/* This file is part of kdev-pg-qt
   Copyright (C) 2011 Jonathan Schmidt-Dominé <devel@the-user.org>

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

#include "kdev-pg-token-type-gen.h"

#include "kdev-pg.h"

namespace KDevPG
{

class GenerateToken
{
public:
  QTextStream& out;
  int mTokenValue;

public:
  GenerateToken(QTextStream& o): out(o), mTokenValue(1001)
  {}

  void operator()(QPair<QString, Model::TerminalItem*> const &__it);
};

void GenerateToken::operator()(QPair<QString, Model::TerminalItem*> const &__it)
{
  Model::TerminalItem *t = __it.second;
  out << "Token_" << t->mName << " = ";
  if(t->mName == "EOF")
  {
    out << 1000;
  }
  else
  {
    out << mTokenValue;
    ++mTokenValue;
  }
  out << "," << endl;
}

void GenerateTokenType::operator()()
{
  out << "struct TokenTypeWrapper // to be imported by using inheritance\n"
         "{\n"
         "enum TokenType\n{\n";
  GenerateToken gen(out);
  for(World::TerminalSet::iterator it = globalSystem.terminals.begin(); it != globalSystem.terminals.end(); ++it )
  {
    gen(qMakePair(it.key(), *it));
  }
  out << "TokenTypeSize\n"
         "}; // TokenType\n"
         "}; // TokenTypeWrapper\n"
         "\ntypedef TokenTypeWrapper::TokenType TokenType;\n";
}

}
