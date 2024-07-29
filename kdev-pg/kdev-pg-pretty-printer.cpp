/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-pretty-printer.h"

#include <QList>
#include <QStack>
#include <iostream>
#include <cassert>


namespace KDevPG
{

void PrettyPrinter::visitZero(Model::ZeroItem *node)
{
  Q_UNUSED(node);
  out << "0";
}

void PrettyPrinter::visitPlus(Model::PlusItem *node)
{
  out << "(";
  visitNode(node->mItem);
  out << ")";
  out << "+";
}

void PrettyPrinter::visitStar(Model::StarItem *node)
{
  out << "(";
  visitNode(node->mItem);
  out << ")";
  out << "*";
}

void PrettyPrinter::visitSymbol(Model::SymbolItem *node)
{
  out << node->mName;
}

void PrettyPrinter::visitAction(Model::ActionItem *node)
{
  visitNode(node->mItem);
}

void PrettyPrinter::visitAlternative(Model::AlternativeItem *node)
{
  QList<Model::Node*> top_level_nodes;

  QStack<Model::Node*> working_list;
  working_list.push(node->mRight);
  working_list.push(node->mLeft);

  while (!working_list.empty())
    {
      Model::Node *n = working_list.top();
      working_list.pop();

      if (Model::AlternativeItem *a = nodeCast<Model::AlternativeItem*>(n))
        {
          working_list.push(a->mRight);
          working_list.push(a->mLeft);
        }
      else
        {
          top_level_nodes.push_back(n);
        }
    }

  bool initial = true;

  out << "(";
  QList<Model::Node*>::iterator it = top_level_nodes.begin();
  while (it != top_level_nodes.end())
    {
      if (!initial)
        out << " | ";

      Model::Node *n = *it++;
      visitNode(n);
      initial = false;
    }
  out << ")";
}

void PrettyPrinter::visitCons(Model::ConsItem *node)
{
  visitNode(node->mLeft);
  out << " ";
  visitNode(node->mRight);
}

void PrettyPrinter::visitEvolve(Model::EvolveItem *node)
{
  visitNode(node->mItem);
  out << " -> ";
  visitNode(node->mSymbol);
}

void PrettyPrinter::visitTryCatch(Model::TryCatchItem *node)
{
  out << "try/" << (node->mCatchItem ? "rollback" : "recover") << "(";
  visitNode(node->mTryItem);
  out << ")";

  if (node->mCatchItem)
    {
      out << " catch(";
      visitNode(node->mCatchItem);
      out << ")";
    }
}

void PrettyPrinter::visitAlias(Model::AliasItem *node)
{
  Q_UNUSED(node);
  assert(0); // ### not implemented yet
}

void PrettyPrinter::visitTerminal(Model::TerminalItem *node)
{
  out << node->mName;
}

void PrettyPrinter::visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node)
{
    visitNode(node->mSymbol);
}

void PrettyPrinter::visitNonTerminal(Model::NonTerminalItem *node)
{
  visitNode(node->mSymbol);
}

void PrettyPrinter::visitAnnotation(Model::AnnotationItem *node)
{
  out << ((node->mDeclaration->mIsSequence) ? "#" : "")
      << node->mDeclaration->mName
      << ((node->mDeclaration->mStorageType
           == Model::VariableDeclarationItem::StorageTemporary) ? ":" : "=");
  visitNode(node->mItem);
}

}
