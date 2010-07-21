#include "kdev-pg-default-visitor.h"

#include <QHash>

namespace KDevPG
{

class BnfVisitor : public DefaultVisitor
{
private:
  KDevPG::Allocator<char> localMemoryPool;
  
  template <class _Tp>
  _Tp *localCreateNode()
  {
    _Tp *node = new (localMemoryPool.allocate(sizeof(_Tp)))_Tp();
    node->kind = _Tp::NodeKind;
    return node;
  }
  
  inline Model::Node *createArray(qint64 size)
  {
    return reinterpret_cast<_Tp*>(localMemoryPool.allocate(size * sizeof(Model::Node)));
  }
  
  template <class _Tp>
  inline _Tp * getSubArray(Model::Node *arr, qint64 beg, qint64 end)
  {
    for(qint64 i = beg; i != end; ++i)
      arr[i].kind = _Tp::NodeKind;
    return arr + beg;
  }
    
protected:
  virtual void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node)
  {
    Model::NonTerminalItem *tmp = createNode<Model::NonTerminalItem>();
    visitNonTerminal(tmp);
    
    copy(&tmp, node);
  }
  virtual void visitPlus(Model::PlusItem *node)
  {
    Model::StarItem tmps;
    tmps.kind = Model::NodeKindStar;
    tmps.mItem = node->mItem;
    Model::ConsItem tmp;
    tmp.kind = Model::NodeKindCons;
    tmp.mLeft = node->mItem;
    tmp.mRight = tmps;
    visitCons(&tmp);
    
    copy(&tmp, node);
  }
  
  QHash<Model::OperatorItem*, QPair<int, Model::Node*> > mOpStuff;
  
  virtual void visitOperator(Model::OperatorItem *node)
  {
    // Does this really work with first/follow-set generation? TODO
    // Is it okay, when some rules are only temporary (NextFirst gets called multiple times, of course)
    // However: It should not be too difficult to store them permanently
    Model::ConsItem tmpPre[node->mPre.size()];
    Model::ConsItem tmpBinRight[node->mBin.size()];
    Model::ConsItem tmpBin[node->mBin.size()];
    Model::ConsItem tmpPost[node->mPost.size()];
    Model::ConsItem tmpParenRight[node->mParen.size()];
    Model::ConsItem tmpParen[node->mParen.size()];
    Model::ConsItem tmpTern3[node->mTern.size()];
    Model::ConsItem tmpTern2[node->mTern.size()];
    Model::ConsItem tmpTern1[node->mTern.size()];
    Model::ConsItem tmpTern[node->mTern.size()];
    int i = node->mPre.size() + node->mPost.size() + node->mBin.size() + node->mTern.size() + node->mParen.size();
    Model::AlternativeItem tmp[i];
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
    
    DefaultVisitor::visitNode(last);
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