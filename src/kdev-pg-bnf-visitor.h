/*
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
