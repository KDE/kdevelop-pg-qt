/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-default-visitor-gen.h"
#include "kdev-pg.h"
#include <iostream>


namespace KDevPG
{

void GenerateDefaultVisitor::operator()()
{
  out << "class " << globalSystem.exportMacro << " " << name << ": public Visitor {" << Qt::endl
      << "public:" << Qt::endl;

  GenerateDefaultVisitorRule gen(out);
  for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it )
  {
    gen(qMakePair(it.key(), *it));
  }

  out << "};" << Qt::endl;
}

void GenerateDefaultVisitorRule::operator()(QPair<QString,Model::SymbolItem*> const &__it)
{
  Model::SymbolItem *sym = __it.second;
  
  #define O(name) \
  out << "void visit" << name << "(" << name << "Ast *node) override;" << Qt::endl;
  
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

}
