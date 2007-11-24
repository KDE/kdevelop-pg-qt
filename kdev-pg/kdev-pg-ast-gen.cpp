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

#include "kdev-pg-ast-gen.h"
#include "kdev-pg-code-gen.h"
#include "kdev-pg.h"
#include <iostream>

namespace KDevPG
{
void GenerateAst::operator()()
{
  for (std::map<std::string, Model::SymbolItem*>::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it)
    {
      Model::SymbolItem *sym = (*it).second;
      out << "struct " << sym->mName << "_ast;" << std::endl;
    }

  out << std::endl;

  for (World::NamespaceSet::iterator it = globalSystem.namespaces.begin();
       it != globalSystem.namespaces.end(); ++it)
    {
      out << "namespace " << (*it).first
          << "{" << (*it).second << "}" << std::endl << std::endl;
    }

  out << std::endl;

  out << "struct " << globalSystem.exportMacro << " ast_node";

  out << "{" << std::endl
      << "enum ast_node_kind_enum {" << std::endl;

  int node_id = 1000;
  for (std::map<std::string, Model::SymbolItem*>::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it)
    {
      Model::SymbolItem *sym = (*it).second;
      out << "Kind_" << sym->mName << " = " << node_id++ << "," << std::endl;
    }

  out << "AST_NODE_KIND_COUNT" << std::endl
      << "};" << std::endl << std::endl
      << "int kind;" << std::endl
      << "std::size_t start_token;" << std::endl
      << "std::size_t end_token;" << std::endl
      << "};" << std::endl
      << std::endl;

  std::for_each(globalSystem.symbols.begin(), globalSystem.symbols.end(), GenerateAstRule(out));
  out << std::endl;
}

void GenerateAstRule::operator()(std::pair<std::string, Model::SymbolItem*> const &__it)
{
  mNames.clear();
  mInAlternative = false;
  mInCons = false;

  Model::SymbolItem *sym = __it.second;
  out << "struct " << globalSystem.exportMacro << " " << sym->mName << "_ast: public ast_node"
      << "{" << std::endl
      << "enum { KIND = Kind_" << sym->mName << "};" << std::endl << std::endl;

  World::Environment::iterator it = globalSystem.env.find(sym);
  while (it != globalSystem.env.end())
    {
      Model::EvolveItem *e = (*it).second;
      if ((*it).first != sym)
        break;

      ++it;

      visitNode(e);
    }

  out << "};" << std::endl << std::endl;
}

void GenerateAstRule::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  if (node->mStorageType != Model::VariableDeclarationItem::StorageTemporary
      && mNames.find(node->mName) == mNames.end())
    {
      GenerateVariableDeclaration gen_var_decl(out);
      gen_var_decl(node);

      out << ";" << std::endl;

      mNames.insert(node->mName);
    }

  DefaultVisitor::visitVariableDeclaration(node);
}

void GenerateAstRule::visitAlternative(Model::AlternativeItem *node)
{
  bool in_alternative = switchAlternative(true);

#if defined(AST_OPT_BRANCH)
  if (!in_alternative)
    {
      out << "union" << std::endl
          << "{" << std::endl
          << "ast_node *__nodeCast;" << std::endl
          << "std::size_t __token_cast;" << std::endl
          << std::endl;
    }
#endif

  DefaultVisitor::visitAlternative(node);

#if defined(AST_OPT_BRANCH)
  if (!in_alternative)
    out << "}; // union" << std::endl;
#endif

  switchAlternative(in_alternative);
}

void GenerateAstRule::visitCons(Model::ConsItem *node)
{
  bool in_cons = switchCons(true);

#if defined(AST_OPT_BRANCH)
  if (!in_cons)
    {
      out << "struct" << std::endl
          << "{" << std::endl;
    }
#endif

  DefaultVisitor::visitCons(node);

#if defined(AST_OPT_BRANCH)
  if (!in_cons)
    {
      out << "}; // struct" << std::endl;
      mNames.clear();
    }
#endif

  switchCons(in_cons);
}

bool GenerateAstRule::switchAlternative(bool alt)
{
  bool old = mInAlternative;
  mInAlternative = alt;
  return old;
}

bool GenerateAstRule::switchCons(bool c)
{
  bool old = mInCons;
  mInCons = c;
  return old;
}

}
