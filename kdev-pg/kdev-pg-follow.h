/* This file is part of kdev-pg
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>
   Copyright (C) 2006 Jakob Petsovits <jpetso@gmx.at>
   Copyright (C) 2006 Alexander Dymo <adymo@kdevelop.org>

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
#include "kdev-pg-default-visitor.h"


namespace KDevPG
{

class InitializeFollow: protected DefaultVisitor
{
public:
  void operator()(Model::Node *node);
protected:
  virtual void visitSymbol(Model::SymbolItem *node);
};

class NextFollow: protected DefaultVisitor
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

  virtual void visitPlus(Model::PlusItem *node);
  virtual void visitStar(Model::StarItem *node);
  virtual void visitAction(Model::ActionItem *node);
  virtual void visitAlternative(Model::AlternativeItem *node);
  virtual void visitCons(Model::ConsItem *node);
  virtual void visitEvolve(Model::EvolveItem *node);
  virtual void visitTryCatch(Model::TryCatchItem *node);
  virtual void visitAnnotation(Model::AnnotationItem *node);
  virtual void visitCondition(Model::ConditionItem *node);
  virtual void visitNonTerminal(Model::NonTerminalItem *node);
  virtual void visitCode(Model::CodeItem *node);

private:
  bool &mChanged;
  Model::SymbolItem *mSymbol;
};

void computeFollow();

}

#endif // KDEV_PG_FOLLOW_H
