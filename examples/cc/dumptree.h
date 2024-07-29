/*
    SPDX-FileCopyrightText: 2009 Jonathan Schmidt-Dominé <devel@the-user.org>
    Derived from the KDevelop-Java-Parser

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef DUMPTREE_H
#define DUMPTREE_H

#include "ccdefaultvisitor.h"

namespace cc
{

class DumpTree : public cc::DefaultVisitor
{
public:
  DumpTree();
  virtual ~DumpTree();

  void dump(cc::AstNode *node);

protected:
  virtual void visitNode(cc::AstNode *node);

private:
  int indent;
};

}

#endif // DUMPTREE_H

