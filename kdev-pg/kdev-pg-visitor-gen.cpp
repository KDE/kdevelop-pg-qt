/* This file is part of kdev-pg
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

#include "kdev-pg-visitor-gen.h"
#include "kdev-pg.h"
#include <iostream>

namespace KDevPG
{

void GenerateVisitor::operator()()
{
  out << "class " << globalSystem.exportMacro << " Visitor {" << endl
      << "typedef void (Visitor::*ParserFuncType)(AstNode *);" << endl
      << "static ParserFuncType sParserTable[];" << endl
      << endl
      << "public:" << endl
      << "virtual ~Visitor() {}" << endl;

  out << "virtual void visitNode(AstNode *node) { "
      << "if (node) (this->*sParserTable[node->kind - 1000])(node); "
      << "}" << endl;

  for (QMap<QString, Model::SymbolItem*>::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it)
    {
      Model::SymbolItem *sym = (*it);
      #define O(str) \
          out << "virtual void visit" << str << "(" << str << "Ast *) {}" << endl;
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

  out << "};" << endl;
}

}
