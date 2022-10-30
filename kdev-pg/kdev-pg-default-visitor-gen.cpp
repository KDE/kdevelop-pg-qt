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
    O("Prefix" + sym->mCapitalizedName)
    O("Postfix" + sym->mCapitalizedName)
    O("Binary" + sym->mCapitalizedName)
    O("Ternary" + sym->mCapitalizedName)
  }
  else
    O(sym->mCapitalizedName)
    
  #undef O
}

}
