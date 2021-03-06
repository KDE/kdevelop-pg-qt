/* This file is part of kdev-pg-qt
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>
   Copyright (C) 2006 Jakob Petsovits <jpetso@gmx.at>
   Copyright (C) 2006 Alexander Dymo <adymo@kdevelop.org>
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
