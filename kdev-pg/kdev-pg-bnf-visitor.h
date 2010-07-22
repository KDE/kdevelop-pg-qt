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
  inline _Tp *localCreateNode()
  {
    _Tp *node = new (localMemoryPool.allocate(sizeof(_Tp)))_Tp();
    node->kind = _Tp::NodeKind;
    return node;
  }
  
  template <class _Tp>
  inline _Tp *createArray(qint64 size)
  {
    return reinterpret_cast<_Tp*>(localMemoryPool.allocate(size * sizeof(_Tp)));
  }
  
  template <class _Tp = Model::ConsItem>
  inline _Tp * getSubArray(void *mem, qint64 s)
  {
    _Tp *arr = reinterpret_cast<_Tp*>(mem);
    for(qint64 i = 0; i != s; ++i)
      arr[i].kind = _Tp::NodeKind;
    return arr;
  }
    
protected:
  virtual void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node)
  {
    visitNonTerminalDirectly
    
    copy(rule, node);
  }
  virtual void visitNonTerminal(Model::NonTerminalItem *node)
  {
    visitNonTerminalDirectly
    
    copy(rule, node);
  }
  virtual void visitPlus(Model::PlusItem *node)
  {
    if(mStarStuff.contains(node))
    {
      DefaultVisitor::visitNode(mPlusStuff[node]);
      copy(mPlusStuff[node], node);
    }
    Model::ConsItem *c = localCreateNode<Model::ConsItem>();
    Model::AlternativeItem *a = localCreateNode<Model::AlternativeItem>();
    c->mLeft = node->mItem;
    c->mRight = a;
    a->mLeft = globalSystem.zero();
    a->mRight = c;
    
    DefaultVisitor::visitNode(c);
    
    mPlusStuff[node] = c;
    
    copy(a, node);
  }
  virtual void visitStar(Model::StarItem *node)
  {
    if(mStarStuff.contains(node))
    {
      DefaultVisitor::visitNode(mStarStuff[node]);
      copy(mStarStuff[node], node);
    }
    Model::ConsItem *c = localCreateNode<Model::ConsItem>();
    Model::AlternativeItem *a = localCreateNode<Model::AlternativeItem>();
    c->mLeft = node->mItem;
    c->mRight = a;
    a->mLeft = globalSystem.zero();
    a->mRight = c;
    
    DefaultVisitor::visitNode(a);
    
    mStarStuff[node] = a;
    
    copy(a, node);
  }
  
  virtual void visitOperator(Model::OperatorItem *node)
  {
    if(mOpStuff.contains(node))
    {
      DefaultVisitor::visitNode(mOpStuff[node]);
      copy(mOpStuff[node], node);
    }
    else
    {
      void *mem = localMemoryPool.allocate(
        node->mPre.size() * 2
        + node->mBin.size() * 3
        + node->mPost.size() * 2
        + node->mParen.size() * 3
        + node->mTern.size() * 5
      );
      Model::ConsItem *tmpPre = getSubArray<>(mem, node->mPre.size());
      Model::ConsItem *tmpBinRight = getSubArray<>(tmpPre + node->mPre.size(), node->mBin.size());
      Model::ConsItem *tmpBin = getSubArray<>(tmpBinRight + node->mBin.size(), node->mBin.size());
      Model::ConsItem *tmpPost = getSubArray<>(tmpBin + node->mBin.size(), node->mPost.size());
      Model::ConsItem *tmpParenRight = getSubArray<>(tmpPost + node->mPost.size(), node->mParen.size());
      Model::ConsItem *tmpParen = getSubArray<>(tmpParenRight + node->mParen.size(), node->mParen.size());
      Model::ConsItem *tmpTern3 = getSubArray<>(tmpParen + node->mParen.size(), node->mTern.size());
      Model::ConsItem *tmpTern2 = getSubArray<>(tmpTern3 + node->mTern.size(), node->mTern.size());
      Model::ConsItem *tmpTern1 = getSubArray<>(tmpTern2 + node->mTern.size(), node->mTern.size());
      Model::ConsItem *tmpTern = getSubArray<>(tmpTern1 + node->mTern.size(), node->mTern.size());
      int i = node->mPre.size() + node->mPost.size() + node->mBin.size() + node->mTern.size() + node->mParen.size();
      Model::AlternativeItem *tmp = getSubArray<Model::AlternativeItem>(tmpTern + node->mTern.size(), i);
      Model::Node *last = node->mBase;
      for(int j = 0; j != node->mPre.size(); ++j)
      {
        tmpPre[j].mLeft = node->mPre[j].op.mTok;
        tmpPre[j].mRight = tmp+0;
        tmpPre[j].kind = Model::NodeKindCons;
        
        --i;
        tmp[i].kind = Model::NodeKindAlternative;
        tmp[i].mRight = last;
        tmp[i].mLeft = tmpPre+j;
        last = tmp+i;
      }
      for(int j = 0; j != node->mPost.size(); ++j)
      {
        tmpPost[j].mLeft = tmp+0;
        tmpPost[j].mRight = node->mPost[j].op.mTok;
        tmpPost[j].kind = Model::NodeKindCons;
        
        --i;
        tmp[i].kind = Model::NodeKindAlternative;
        tmp[i].mRight = last;
        tmp[i].mLeft = tmpPost+j;
        last = tmp+i;
      }
      for(int j = 0; j != node->mBin.size(); ++j)
      {
        tmpBinRight[j].mLeft = node->mBin[j].op.mTok;
        tmpBinRight[j].mRight = tmp+0;
        tmpBinRight[j].kind = Model::NodeKindCons;
        tmpBin[j].mLeft = tmp+0;
        tmpBin[j].mRight = tmpBinRight+j;
        tmpBin[j].kind = Model::NodeKindCons;
        
        --i;
        tmp[i].kind = Model::NodeKindAlternative;
        tmp[i].mRight = last;
        tmp[i].mLeft = tmpBin+j;
        last = tmp+i;
      }
      for(int j = 0; j != node->mTern.size(); ++j)
      {
        tmpTern3[j].mLeft = node->mTern[j].second.mTok;
        tmpTern3[j].mRight = tmp+0;
        tmpTern3[j].kind = Model::NodeKindCons;
        tmpTern2[j].mLeft = tmp+0;
        tmpTern2[j].mRight = tmpTern3+j;
        tmpTern2[j].kind = Model::NodeKindCons;
        tmpTern1[j].mLeft = node->mTern[j].first.mTok;
        tmpTern1[j].mRight = tmpTern2+j;
        tmpTern1[j].kind = Model::NodeKindCons;
        tmpTern[j].mLeft = tmp+0;
        tmpTern[j].mRight = tmpTern1+j;
        tmpTern[j].kind = Model::NodeKindCons;
        
        --i;
        tmp[i].kind = Model::NodeKindAlternative;
        tmp[i].mRight = last;
        tmp[i].mLeft = tmpTern+j;
        last = tmp+i;
      }
      for(int j = 0; j != node->mParen.size(); ++j)
      {
        tmpParenRight[j].mLeft = tmp+0;
        tmpParenRight[j].mRight = node->mParen[j].second;
        tmpParenRight[j].kind = Model::NodeKindCons;
        tmpParen[j].mLeft = node->mParen[j].first;
        tmpParen[j].mRight = tmpParenRight+j;
        tmpParen[j].kind = Model::NodeKindCons;

        --i;
        tmp[i].kind = Model::NodeKindAlternative;
        tmp[i].mRight = last;
        tmp[i].mLeft = tmpParen+j;
        last = tmp+i;
      }
      
      mOpStuff[node] = last;
      
      DefaultVisitor::visitNode(last);
      
      copy(last, node);
    }
  }

  /// Should be reimplemented by first- and follow-set-generators
  virtual void copy(Model::Node *from, Model::Node *to) {}
  virtual void finished()
  {
    
  }
  virtual ~BnfVisitor()
  {
    finished();
  }
};

}