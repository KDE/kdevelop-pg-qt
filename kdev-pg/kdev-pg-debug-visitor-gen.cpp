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
  out << "class " << globalSystem.exportMacro << " DebugVisitor: public DefaultVisitor {" << std::endl
      << "public:" << std::endl;

  std::for_each(globalSystem.symbols.begin(), globalSystem.symbols.end(),
                GenerateDebugVisitorRule(out));

  out << "};" << std::endl;
}

void GenerateDebugVisitorRule::operator()(std::pair<std::string,
                                          Model::SymbolItem*> const &__it)
{
  Model::SymbolItem *sym = __it.second;

  bool has_members = false;
  HasMemberNodes hms(has_members);
  hms(sym);

  out << "virtual void visit" << sym->mName
      << "(" << sym->mName << "Ast *" << "node"
      << ") {" << std::endl;

  out << "std::cout << \"" << sym->mName << "\" << std::endl; " << std::endl;

  out << "DefaultVisitor::visit" << sym->mName
      << "(" << "node"
      << ");" << std::endl;

  out << "}" << std::endl << std::endl;
}

}
