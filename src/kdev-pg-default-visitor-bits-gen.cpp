/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-default-visitor-bits-gen.h"
#include "kdev-pg.h"
#include <iostream>

namespace KDevPG
{

void GenerateDefaultVisitorBitsRule::operator()(QPair<QString,Model::SymbolItem*> const &__it)
{
  mNames.clear();
  mVariableDeclarations.clear();

  Model::SymbolItem *sym = __it.second;

  bool has_members = false;
  HasMemberNodes hms(has_members);
  hms(sym);

  #define O(ast) \
      out << "void " << name << "::visit" << ast \
      << "(" << ast << "Ast *" << (has_members ? "node" : "") \
      << ") {" << Qt::endl;
      
  if(isOperatorSymbol(sym))
  {
    O(QLatin1String("Prefix") + sym->mCapitalizedName)
    out << "visitNode(node->first);" << Qt::endl << "}" << Qt::endl << Qt::endl;
    O(QLatin1String("Postfix") + sym->mCapitalizedName)
    out << "visitNode(node->first);" << Qt::endl << "}" << Qt::endl << Qt::endl;
    O(QLatin1String("Binary") + sym->mCapitalizedName)
    out << "visitNode(node->first);" << Qt::endl << "visitNode(node->second); }" << Qt::endl << Qt::endl;
    O(QLatin1String("Ternary") + sym->mCapitalizedName)
    out << "visitNode(node->first);" << Qt::endl << "visitNode(node->second);" << Qt::endl << "visitNode(node->third);";
  }
  else
  {
    O(sym->mCapitalizedName)

    World::Environment::iterator it = globalSystem.env.find(sym);
    while (it != globalSystem.env.end())
      {
        Model::EvolveItem *e = (*it);
        if (it.key() != sym)
          break;

        ++it;

        visitNode(e);
      }
  }

  out << "}" << Qt::endl << Qt::endl;
  
  #undef O
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

    QString base_type = node->mCapitalizedType + QLatin1String("Ast*");

    if (node->mIsSequence)
      {
        out << "if (" << "node->" << node->mName << "Sequence" << ") {"
            << "const KDevPG::ListNode<" << base_type << "> *__it = "
            << "node->" << node->mName << "Sequence" << "->front()"
            << ", *__end = __it;" << Qt::endl
            << "do {" << Qt::endl
            << "visitNode(__it->element);" << Qt::endl
            << "__it = __it->next;" << Qt::endl
            << "} while (__it != __end);" << Qt::endl
            << "}" << Qt::endl;
      }
    else
      {
        out << "visitNode(" << "node->" << node->mName << ")" << ";" << Qt::endl;
      }

    mNames.insert(node->mName);
    mVariableDeclarations.push_back(node);

  } while(false);

  DefaultVisitor::visitVariableDeclaration(node);
}


void HasMemberNodes::operator()(Model::SymbolItem *sym)
{
  if(isOperatorSymbol(sym))
  {
    has_members = true;
    return;
  }
  
  has_members = false;

  World::Environment::iterator it = globalSystem.env.find(sym);
  while (it != globalSystem.env.end())
    {
      Model::EvolveItem *e = (*it);
      if (it.key() != sym)
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
