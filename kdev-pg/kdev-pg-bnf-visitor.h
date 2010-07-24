#ifndef KDEV_PG_BNF_VISITOR_H
#define KDEV_PG_BNF_VISITOR_H

#include "kdev-pg-default-visitor.h"

#include "kdev-pg.h"

#include <QHash>

namespace KDevPG
{

class BnfVisitor : public DefaultVisitor
{
private:
  KDevPG::Allocator<char> localMemoryPool;
  
  QHash<Model::OperatorItem*, Model::Node*> mOpStuff;
  QHash<Model::StarItem*, Model::Node*> mStarStuff;
  QHash<Model::PlusItem*, Model::Node*> mPlusStuff;
  
  template <class _Tp>
  inline _Tp *localCreateNode();
  
  template <class _Tp>
  inline _Tp *createArray(qint64 size);
  
  template <class _Tp>
  inline _Tp * getSubArray(void *mem, qint64 s);
    
protected:
  virtual void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node);
  virtual void visitNonTerminal(Model::NonTerminalItem *node);
  virtual void visitPlus(Model::PlusItem *node);
  virtual void visitStar(Model::StarItem *node);
  virtual void visitOperator(Model::OperatorItem *node);
  virtual void visitTryCatch(Model::TryCatchItem *node);
  virtual void visitAnnotation(Model::AnnotationItem *node);
  virtual void visitCondition(Model::ConditionItem *node);
  virtual void visitEvolve(Model::EvolveItem *node);

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
  virtual ~BnfVisitor()
  {
    finished();
  }
};

}

#endif
