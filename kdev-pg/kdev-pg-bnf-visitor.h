/* This file is part of kdev-pg-qt
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

#ifndef KDEV_PG_BNF_VISITOR_H
#define KDEV_PG_BNF_VISITOR_H

#include "kdev-pg-default-visitor.h"

#include "kdev-pg.h"

#include <QHash>

namespace KDevPG
{

class BnfVisitor : public DefaultVisitor
{
public:
  static bool isInternal(Model::Node* item);
private:
  static KDevPG::Allocator<char> localMemoryPool;
  
  static QHash<Model::OperatorItem*, Model::Node*> mOpStuff;
  static QHash<Model::StarItem*, Model::Node*> mStarStuff;
  static QHash<Model::PlusItem*, Model::Node*> mPlusStuff;
  
  template <class _Tp>
  inline _Tp *localCreateNode();
  
  template <class _Tp>
  inline _Tp *createArray(qint64 size);
  
  template <class _Tp>
  inline _Tp * getSubArray(void *mem, qint64 s);
    
protected:
  void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node) override;
  void visitNonTerminal(Model::NonTerminalItem *node) override;
  void visitPlus(Model::PlusItem *node) override;
  void visitStar(Model::StarItem *node) override;
  void visitOperator(Model::OperatorItem *node) override;
  void visitTryCatch(Model::TryCatchItem *node) override;
  void visitAnnotation(Model::AnnotationItem *node) override;
  void visitCondition(Model::ConditionItem *node) override;
  void visitEvolve(Model::EvolveItem *node) override;
  void visitAction(Model::ActionItem *node) override;

  /// Should be reimplemented by first- and follow-set-generators
  virtual void copy(Model::Node *from, Model::Node *to)
  {
    Q_UNUSED(from);
    Q_UNUSED(to);
  }
  virtual void preCopy(Model::Node *from, Model::Node *to)
  {
    Q_UNUSED(from);
    Q_UNUSED(to);
  }
  
  virtual void finished();
  ~BnfVisitor() override
  {
    finished();
  }
};

}

#endif
