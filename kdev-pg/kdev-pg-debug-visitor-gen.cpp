/* This file is part of kdev-pg
   Copyright (C) 2006 Alexander Dymo <adymo@kdevelop.org>

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

#include "kdev-pg-debug-visitor-gen.h"
#include "kdev-pg.h"
#include <iostream>

namespace KDevPG
{

void GenerateDebugVisitor::operator()()
{
  out << "class " << globalSystem.exportMacro << " DebugVisitor: public DefaultVisitor {" << endl
      << "public:" << endl;


  for( World::SymbolSet::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); it++ )
  {
    GenerateDebugVisitorRule gen(out);
    gen(qMakePair(it.key(), *it));
  }

  out << "};" << endl;
}

void GenerateDebugVisitorRule::operator()(QPair<QString,
                                          Model::SymbolItem*> const &__it)
{
  Model::SymbolItem *sym = __it.second;

  bool has_members = false;
  HasMemberNodes hms(has_members);
  hms(sym);

  out << "virtual void visit" << sym->mCapitalizedName
      << "(" << sym->mCapitalizedName << "Ast *" << "node"
      << ") {" << endl;

  out << "qDebug() << \"" << sym->mName << "\" << endl; " << endl;

  out << "DefaultVisitor::visit" << sym->mCapitalizedName
      << "(" << "node"
      << ");" << endl;

  out << "}" << endl << endl;
}

}
