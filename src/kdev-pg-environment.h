/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_ENVIRONMENT_H
#define KDEV_PG_ENVIRONMENT_H

#include "kdev-pg-default-visitor.h"
#include "kdev-pg.h"

namespace KDevPG
{
class InitializeEnvironment: protected DefaultVisitor
{
public:
  void operator ()(Model::Node *node)
  {
    visitNode(node);
  }
protected:
  void visitEvolve(Model::EvolveItem *node) override
  {
    globalSystem.env.insert(node->mSymbol, node);
  }
  void visitInlinedNonTerminal(Model::InlinedNonTerminalItem *node) override
  {
    Q_UNUSED(node);
  }
};
}
#endif // KDEV_PG_ENVIRONMENT_H
