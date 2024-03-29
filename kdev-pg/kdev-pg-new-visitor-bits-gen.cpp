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

#include "kdev-pg-new-visitor-bits-gen.h"
#include "kdev-pg-default-visitor-bits-gen.h"
#include "kdev-pg.h"

namespace KDevPG
{

void GenerateNewVisitorBitsRule::operator()(QPair<QString,Model::SymbolItem*> const &__it)
{
  bool has_members = false;
  HasMemberNodes hms(has_members);
  hms(__it.second);

  #define O(name) \
    out << "void " << name << "::visit" << name \
        << "(" << name << "Ast *node" \
        << ") {" << Qt::endl << Qt::endl \
        << "DefaultVisitor::visit" << name << "(node)" << Qt::endl \
        << "}" << Qt::endl << Qt::endl;
  
  if(isOperatorSymbol(__it.second))
  {
    O("Prefix" + __it.second->mCapitalizedName)
    O("Postfix" + __it.second->mCapitalizedName)
    O("Binary" + __it.second->mCapitalizedName)
    O("Ternary" + __it.second->mCapitalizedName)
  }
  else if(has_members)
  {
    O(__it.second->mCapitalizedName)
  }
  
  #undef O
}

}
