/*
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEVPG_INLINE_CHECKER_H
#define KDEVPG_INLINE_CHECKER_H

#include "kdev-pg-default-visitor.h"

#include <QSet>

namespace KDevPG
{

class InlineChecker : public DefaultVisitor
{
public:
    void operator()(Model::EvolveItem* node);
protected:
    void visitNonTerminal(Model::NonTerminalItem* node) override;
    void visitInlinedNonTerminal(Model::InlinedNonTerminalItem* node) override;
private:
    QSet<Model::Node*> mVisited, mCurrentlyVisiting;
};

}

#endif // KDEVPG_INLINE_CHECKER_H
