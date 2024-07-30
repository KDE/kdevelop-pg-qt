/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-clone-tree.h"
#include "kdev-pg.h"

namespace KDevPG
{

void CloneTree::visitZero(Model::ZeroItem *node)
{
  mTemps.push(node);
}

void CloneTree::visitSymbol(Model::SymbolItem *node)
{
  mTemps.push(node);
}

void CloneTree::visitTerminal(Model::TerminalItem *node)
{
  mTemps.push(node);
}

void CloneTree::visitNonTerminal(Model::NonTerminalItem *node)
{
  mTemps.push(KDevPG::nonTerminal(node->mSymbol, node->mArguments));
}

void CloneTree::visitInlinedNonTerminal(Model::InlinedNonTerminalItem* node)
{
  mTemps.push(KDevPG::inlinedNonTerminal(node->mSymbol));
}

void CloneTree::visitPlus(Model::PlusItem *node)
{
  visitNode(node->mItem);

  Model::Node *item = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::plus(item));
}

void CloneTree::visitStar(Model::StarItem *node)
{
  visitNode(node->mItem);

  Model::Node *item = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::star(item));
}

void CloneTree::visitAction(Model::ActionItem *node)
{
  visitNode(node->mItem);

  Model::Node *item = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::action(item, node->mCode));
}

void CloneTree::visitAlternative(Model::AlternativeItem *node)
{
  visitNode(node->mLeft);

  Model::Node *left = mTemps.top();
  mTemps.pop();

  visitNode(node->mRight);

  Model::Node *right = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::alternative(left, right));
}

void CloneTree::visitCons(Model::ConsItem *node)
{
  visitNode(node->mLeft);

  Model::Node *left = mTemps.top();
  mTemps.pop();

  visitNode(node->mRight);

  Model::Node *right = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::cons(left, right));
}

void CloneTree::visitEvolve(Model::EvolveItem *node)
{
  visitNode(node->mItem);

  Model::Node *item = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::evolve(item, node->mSymbol, node->mDeclarations, node->mCode));
}

void CloneTree::visitTryCatch(Model::TryCatchItem *node)
{
  visitNode(node->mTryItem);

  Model::Node *try_item = mTemps.top();
  mTemps.pop();

  Model::Node *catch_item = nullptr;

  if (node->mCatchItem)
    {
      visitNode(node->mCatchItem);

      catch_item = mTemps.top();
      mTemps.pop();
    }

  mTemps.push(KDevPG::tryCatch(try_item, catch_item));
}

void CloneTree::visitAlias(Model::AliasItem *node)
{
  Q_UNUSED(node);
  Q_ASSERT(0); // ### not implemented yet
}

void CloneTree::visitAnnotation(Model::AnnotationItem *node)
{
  visitNode(node->mItem);

  Model::Node *item = mTemps.top();
  mTemps.pop();

  mTemps.push(KDevPG::annotation(node->mDeclaration->mName, item,
                               node->mDeclaration->mIsSequence,
                               node->mDeclaration->mStorageType));
}

void CloneTree::visitOperator(Model::OperatorItem *node)
{
  // Should not be relevant if it gets really copied
  mTemps.push(node);
}

Model::Node *CloneTree::clone(Model::Node *node)
{
  mTemps = QStack<Model::Node*>();
  visitNode(node);
  Model::Node *n = mTemps.top();
  mTemps.pop();
  Q_ASSERT(mTemps.empty());
  return n;
}

}
