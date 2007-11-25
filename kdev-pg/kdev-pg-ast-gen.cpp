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

#include <QtCore/QMap>

namespace KDevPG
{
void GenerateAst::operator()()
{
  for (QMap<QString, Model::SymbolItem*>::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it)
    {
      Model::SymbolItem *sym = *it;
      out << "struct " << sym->mCapitalizedName << "Ast;" << endl;
    }

  out << endl;

  for (World::NamespaceSet::iterator it = globalSystem.namespaces.begin();
       it != globalSystem.namespaces.end(); ++it)
    {
      out << "namespace " << it.key()
          << "{" << (*it) << "}" << endl << endl;
    }

  out << endl;

  out << "struct " << globalSystem.exportMacro << " AstNode";

  out << "{" << endl
      << "enum AstNodeKind {" << endl;

  int node_id = 1000;
  for (QMap<QString, Model::SymbolItem*>::iterator it = globalSystem.symbols.begin();
       it != globalSystem.symbols.end(); ++it)
    {
      Model::SymbolItem *sym = (*it);
      out << sym->mCapitalizedName << "Kind" << " = " << node_id++ << "," << endl;
    }

  out << "AST_NODE_KIND_COUNT" << endl
      << "};" << endl << endl
      << "int kind;" << endl
      << "qint64 startToken;" << endl
      << "qint64 endToken;" << endl
      << "};" << endl
      << endl;

  GenerateAstRule gen(out);
  for( World::SymbolSet::const_iterator it = globalSystem.symbols.begin(); it != globalSystem.symbols.end(); it++ )
  {
    gen(qMakePair( it.key(), *it ));
  }
  out << endl;
}

void GenerateAstRule::operator()(QPair<QString, Model::SymbolItem*> const &__it)
{
  mNames.clear();
  mInAlternative = false;
  mInCons = false;

  Model::SymbolItem *sym = __it.second;
  out << "struct " << globalSystem.exportMacro << " " << sym->mCapitalizedName << "Ast: public AstNode"
      << "{" << endl
      << "enum { KIND = " << sym->mCapitalizedName << "Kind };" << endl << endl;

  World::Environment::iterator it = globalSystem.env.find(sym);
  while (it != globalSystem.env.end())
    {
      Model::EvolveItem *e = *it;
      if (it.key() != sym)
        break;

      ++it;

      visitNode(e);
    }

  out << "};" << endl << endl;
}

void GenerateAstRule::visitVariableDeclaration(Model::VariableDeclarationItem *node)
{
  GenerateVariableDeclaration gen_var_decl(out);
  if (node->mStorageType != Model::VariableDeclarationItem::StorageTemporary
      && mNames.find(node->mName) == mNames.end())
    {
      gen_var_decl(node);

      out << ";" << endl;

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
      out << "union" << endl
          << "{" << endl
          << "AstNode *__nodeCast;" << endl
          << "qint64 __token_cast;" << endl
          << endl;
    }
#endif

  DefaultVisitor::visitAlternative(node);

#if defined(AST_OPT_BRANCH)
  if (!in_alternative)
    out << "}; // union" << endl;
#endif

  switchAlternative(in_alternative);
}

void GenerateAstRule::visitCons(Model::ConsItem *node)
{
  bool in_cons = switchCons(true);

#if defined(AST_OPT_BRANCH)
  if (!in_cons)
    {
      out << "struct" << endl
          << "{" << endl;
    }
#endif

  DefaultVisitor::visitCons(node);

#if defined(AST_OPT_BRANCH)
  if (!in_cons)
    {
      out << "}; // struct" << endl;
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
