/* This file is part of kdev-pg-qt
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>
   Copyright (C) 2006 Jakob Petsovits <jpetso@gmx.at>
   Copyright (C) 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

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

#include "kdev-pg-visitor-gen.h"
#include "kdev-pg.h"
#include <iostream>

namespace KDevPG
{

void GenerateVisitor::operator()()
{
  out << "class " << globalSystem.exportMacro << " Visitor {" << Qt::endl;
  if (globalSystem.visitorTable)
  {
    out << "typedef void (Visitor::*ParserFuncType)(AstNode *);" << Qt::endl
        << "static ParserFuncType sParserTable[];" << Qt::endl
        << Qt::endl;
  }
  out << "public:" << Qt::endl
      << "virtual ~Visitor() {}" << Qt::endl;

  out << "virtual void visitNode(AstNode *node);" << Qt::endl;

  for (QMap<QString, Model::SymbolItem*>::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it)
    {
      Model::SymbolItem *sym = (*it);
      #define O(str) \
          out << "virtual void visit" << str << "(" << str << "Ast *) {}" << Qt::endl;
      if(isOperatorSymbol(sym))
      {
        O("Prefix" + sym->mCapitalizedName)
        O("Postfix" + sym->mCapitalizedName)
        O("Binary" + sym->mCapitalizedName)
        O("Ternary" + sym->mCapitalizedName)
      }
      else
        O(sym->mCapitalizedName)
      #undef O
    }

  out << "};" << Qt::endl;
}

}
