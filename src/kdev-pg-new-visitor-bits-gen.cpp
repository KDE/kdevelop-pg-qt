/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
