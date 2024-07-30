/*
    SPDX-FileCopyrightText: 2011 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
  out << "," << Qt::endl;
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
