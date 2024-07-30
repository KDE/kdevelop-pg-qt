/*
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-bnf-visitor.h"

using namespace KDevPG;

bool BnfVisitor::isInternal(Model::Node* item)
{
  return localMemoryPool.contains(item);
}

template<typename _Tp>
inline _Tp* BnfVisitor::localCreateNode()
{
  _Tp *node = new (localMemoryPool.allocate(sizeof(_Tp)))_Tp();
  node->kind = _Tp::NodeKind;
  return node;
}

template<typename _Tp>
inline _Tp* BnfVisitor::createArray(qint64 size)
{
  return reinterpret_cast<_Tp*>(localMemoryPool.allocate(size * sizeof(_Tp)));
}

template<typename _Tp>
inline _Tp* BnfVisitor::getSubArray(void* mem, qint64 s)
{
  _Tp *arr = reinterpret_cast<_Tp*>(mem);
  for(qint64 i = 0; i != s; ++i)
    arr[i].kind = _Tp::NodeKind;
  return arr;
}

KDevPG::Allocator<char> KDevPG::BnfVisitor::localMemoryPool;

QHash<Model::OperatorItem*, Model::Node*> KDevPG::BnfVisitor::mOpStuff;
QHash<Model::StarItem*, Model::Node*> KDevPG::BnfVisitor::mStarStuff;
QHash<Model::PlusItem*, Model::Node*> KDevPG::BnfVisitor::mPlusStuff;

void KDevPG::BnfVisitor::visitInlinedNonTerminal(Model::InlinedNonTerminalItem* node)
{
  Model::EvolveItem *rule = globalSystem.searchRule(node->mSymbol);
  
  preCopy(rule, node);
  preCopy(node->mSymbol, node);
  
//   visitNode(rule);
  
  copy(node->mSymbol, node);
  copy(rule, node);
}

void KDevPG::BnfVisitor::visitNonTerminal(Model::NonTerminalItem* node)
{
  Model::EvolveItem *rule = globalSystem.searchRule(node->mSymbol);
  
  preCopy(rule, node);
  preCopy(node->mSymbol, node);
  
//   visitNode(rule);
  
  copy(node->mSymbol, node);
  copy(rule, node);
}

void KDevPG::BnfVisitor::visitPlus(Model::PlusItem* node)
{
  if(mPlusStuff.contains(node))
  {
    preCopy(mPlusStuff[node], node);
    DefaultVisitor::visitNode(mPlusStuff[node]);
    copy(mPlusStuff[node], node);
    return;
  }
  Model::ConsItem *c = localCreateNode<Model::ConsItem>();
  Model::AlternativeItem *a = localCreateNode<Model::AlternativeItem>();
  c->mLeft = node->mItem;
  c->mRight = a;
  a->mLeft = globalSystem.zero();
  a->mRight = c;
  
  preCopy(c, node);
  
  DefaultVisitor::visitNode(c);
  
  mPlusStuff[node] = c;
  
  copy(c, node);
}

void KDevPG::BnfVisitor::visitStar(Model::StarItem* node)
{
  if(mStarStuff.contains(node))
  {
    preCopy(mStarStuff[node], node);
    DefaultVisitor::visitNode(mStarStuff[node]);
    copy(mStarStuff[node], node);
    return;
  }
  Model::ConsItem *c = localCreateNode<Model::ConsItem>();
  Model::AlternativeItem *a = localCreateNode<Model::AlternativeItem>();
  c->mLeft = node->mItem;
  c->mRight = a;
  a->mLeft = globalSystem.zero();
  a->mRight = c;
  
  preCopy(a, node);
  
  DefaultVisitor::visitNode(a);
  
  mStarStuff[node] = a;
  
  copy(a, node);
}

void KDevPG::BnfVisitor::visitOperator(Model::OperatorItem* node)
{
  if(mOpStuff.contains(node))
  {
    preCopy(mOpStuff[node], node);
    DefaultVisitor::visitNode(mOpStuff[node]);
    copy(mOpStuff[node], node);
  }
  else
  {
    void *mem = localMemoryPool.allocate(
      (node->mPre.size() * 1
      + node->mBin.size() * 2
      + node->mPost.size() * 1
      + node->mParen.size() * 2
      + node->mTern.size() * 4) * sizeof(Model::ConsItem)
      + (node->mPre.size() * 1
      + node->mBin.size() * 1
      + node->mPost.size() * 1
      + node->mParen.size() * 1
      + node->mTern.size() * 1) * sizeof(Model::AlternativeItem)
    );
    Model::ConsItem *tmpPre = getSubArray<Model::ConsItem>(mem, node->mPre.size());
    Model::ConsItem *tmpBinRight = getSubArray<Model::ConsItem>(tmpPre + node->mPre.size(), node->mBin.size());
    Model::ConsItem *tmpBin = getSubArray<Model::ConsItem>(tmpBinRight + node->mBin.size(), node->mBin.size());
    Model::ConsItem *tmpPost = getSubArray<Model::ConsItem>(tmpBin + node->mBin.size(), node->mPost.size());
    Model::ConsItem *tmpParenRight = getSubArray<Model::ConsItem>(tmpPost + node->mPost.size(), node->mParen.size());
    Model::ConsItem *tmpParen = getSubArray<Model::ConsItem>(tmpParenRight + node->mParen.size(), node->mParen.size());
    Model::ConsItem *tmpTern3 = getSubArray<Model::ConsItem>(tmpParen + node->mParen.size(), node->mTern.size());
    Model::ConsItem *tmpTern2 = getSubArray<Model::ConsItem>(tmpTern3 + node->mTern.size(), node->mTern.size());
    Model::ConsItem *tmpTern1 = getSubArray<Model::ConsItem>(tmpTern2 + node->mTern.size(), node->mTern.size());
    Model::ConsItem *tmpTern = getSubArray<Model::ConsItem>(tmpTern1 + node->mTern.size(), node->mTern.size());
    int i = node->mPre.size() + node->mPost.size() + node->mBin.size() + node->mTern.size() + node->mParen.size();
    Model::AlternativeItem *tmp = getSubArray<Model::AlternativeItem>(tmpTern + node->mTern.size(), i);
    Model::Node *last = node->mBase;
    for(size_t j = 0; j != node->mPre.size(); ++j)
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
    for(size_t j = 0; j != node->mPost.size(); ++j)
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
    for(size_t j = 0; j != node->mBin.size(); ++j)
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
    for(size_t j = 0; j != node->mTern.size(); ++j)
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
    for(size_t j = 0; j != node->mParen.size(); ++j)
    {
      tmpParenRight[j].mLeft = tmp+0;
      tmpParenRight[j].mRight = node->mParen[j].second.mTok;
      tmpParenRight[j].kind = Model::NodeKindCons;
      tmpParen[j].mLeft = node->mParen[j].first.mTok;
      tmpParen[j].mRight = tmpParenRight+j;
      tmpParen[j].kind = Model::NodeKindCons;

      --i;
      tmp[i].kind = Model::NodeKindAlternative;
      tmp[i].mRight = last;
      tmp[i].mLeft = tmpParen+j;
      last = tmp+i;
    }
    
    mOpStuff[node] = last;
    
    preCopy(last, node);
    
    DefaultVisitor::visitNode(last);
    
    copy(last, node);
  }
}

void BnfVisitor::visitAnnotation(Model::AnnotationItem* node)
{
    preCopy(node->mItem, node);
  
    KDevPG::DefaultVisitor::visitAnnotation(node);
    
    copy(node->mItem, node);
}

void BnfVisitor::visitCondition(Model::ConditionItem* node)
{
    preCopy(node->mItem, node);
  
    KDevPG::DefaultVisitor::visitCondition(node);
    
    copy(node->mItem, node);
}

void BnfVisitor::visitAction(Model::ActionItem* node)
{
    preCopy(node->mItem, node);
  
    KDevPG::DefaultVisitor::visitNode(node->mItem);
    
    copy(node->mItem, node);
}

void BnfVisitor::visitTryCatch(Model::TryCatchItem* node)
{
    if(node->mCatchItem == nullptr)
    {
        preCopy(node->mTryItem, node);
      
        DefaultVisitor::visitNode(node->mTryItem);
        
        copy(node->mTryItem, node);
    }
    else    // A little bit dirty, please do not change the layout ;)
        visitAlternative(reinterpret_cast<Model::AlternativeItem*>(node));
}

void BnfVisitor::visitEvolve(Model::EvolveItem* node)
{
    preCopy(node, node->mSymbol);
    preCopy(node->mItem, node);
  
    visitNode(node->mItem);
    
    copy(node->mItem, node);
    copy(node, node->mSymbol);
}

void KDevPG::BnfVisitor::finished()
{
//   localMemoryPool.~Allocator();
//   new (&localMemoryPool) Allocator<char>;
}
