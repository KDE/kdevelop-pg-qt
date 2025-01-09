/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
        O(QLatin1String("Prefix") + sym->mCapitalizedName)
        O(QLatin1String("Postfix") + sym->mCapitalizedName)
        O(QLatin1String("Binary") + sym->mCapitalizedName)
        O(QLatin1String("Ternary") + sym->mCapitalizedName)
      }
      else
        O(sym->mCapitalizedName)
      #undef O
    }

  out << "};" << Qt::endl;
}

}
