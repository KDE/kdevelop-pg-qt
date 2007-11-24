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

#include "kdev-pg-default-visitor-bits-gen.h"
#include "kdev-pg.h"
#include <iostream>

namespace KDevPG
{

void GenerateDefaultVisitorBitsRule::operator()(std::pair<std::string,Model::SymbolItem*> const &__it)
{
  mNames.clear();
  mVariableDeclarations.clear();

  Model::SymbolItem *sym = __it.second;

  bool has_members = false;
  HasMemberNodes hms(has_members);
  hms(sym);

  out << "void DefaultVisitor::visit_" << sym->mName
      << "(" << sym->mName << "_ast *" << (has_members ? "node" : "")
      << ") {" << std::endl;

  World::Environment::iterator it = globalSystem.env.find(sym);
  while (it != globalSystem.env.end())
    {
      Model::EvolveItem *e = (*it).second;
      if ((*it).first != sym)
        break;

      ++it;

      visitNode(e);
    }

  out << "}" << std::endl << std::endl;
}

void GenerateDefaultVisitorBitsRule::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  do
  {
    if (node->mStorageType != Model::VariableDeclarationItem::StorageAstMember)
      break;

    if (node->mVariableType != Model::VariableDeclarationItem::TypeNode)
      break; // nothing to do

    if (mNames.find(node->mName) != mNames.end())
      break;

    std::string base_type = std::string(node->mType) + "_ast*";

    if (node->mIsSequence)
      {
        out << "if (" << "node->" << node->mName << "_sequence" << ") {"
            << "const list_node<" << base_type << "> *__it = "
            << "node->" << node->mName << "_sequence" << "->to_front()"
            << ", *__end = __it;" << std::endl
            << "do {" << std::endl
            << "visitNode(__it->element);" << std::endl
            << "__it = __it->next;" << std::endl
            << "} while (__it != __end);" << std::endl
            << "}" << std::endl;
      }
    else
      {
        out << "visitNode(" << "node->" << node->mName << ")" << ";" << std::endl;
      }

    mNames.insert(node->mName);
    mVariableDeclarations.push_back(node);

  } while(false);

  DefaultVisitor::visitVariableDeclaration(node);
}


void HasMemberNodes::operator()(Model::SymbolItem *sym)
{
  has_members = false;

  World::Environment::iterator it = globalSystem.env.find(sym);
  while (it != globalSystem.env.end())
    {
      Model::EvolveItem *e = (*it).second;
      if ((*it).first != sym)
        break;

      ++it;

      visitNode(e);
    }
}

void HasMemberNodes::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  if (node->mStorageType == Model::VariableDeclarationItem::StorageAstMember
      && node->mVariableType == Model::VariableDeclarationItem::TypeNode)
    {
      has_members = true;
    }
}

}
