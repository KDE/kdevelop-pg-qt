/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>
    SPDX-FileCopyrightText: 2006 Alexander Dymo <adymo@kdevelop.org>
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_FOLLOW_H
#define KDEV_PG_FOLLOW_H

#include "kdev-pg.h"
#include "kdev-pg-bnf-visitor.h"



namespace KDevPG
{

class InitializeFollow: protected DefaultVisitor
{
public:
  void operator()(Model::Node *node);
protected:
  void visitSymbol(Model::SymbolItem *node) override;
};

class NextFollow: protected BnfVisitor
{
public:
  NextFollow(bool &changed);

  void operator()(Model::Node *node);

protected:
  void merge(Model::Node *__dest, World::NodeSet const &source);
  /**adds dependency between rule @p dep whose FIRST set is added to
  @p dest FOLLOW set*/
  void addFirstToFollowDep(Model::Node *dest, Model::Node *dep);
  /**adds dependency between rule @p dep whose FOLLOW set is added to
  @p dest FOLLOW set*/
  void addFollowToFollowDep(Model::Node *dest, Model::Node *dep);

  void visitNode(Model::Node *node) override;
  void visitAlternative(Model::AlternativeItem *node) override;
  void visitCons(Model::ConsItem *node) override;
  
  void preCopy(Model::Node *from, Model::Node *to) override;
  void copy(Model::Node *from, Model::Node *to) override;

private:
  bool &mChanged;
  Model::SymbolItem *mSymbol;
  QSet<Model::Node*> mVisited;
};

void computeFollow();

}

#endif // KDEV_PG_FOLLOW_H
