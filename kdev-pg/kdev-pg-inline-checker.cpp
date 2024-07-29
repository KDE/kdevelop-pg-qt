/*
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg-inline-checker.h"

#include "kdev-pg-checker.h"

#include <QTextStream>

namespace KDevPG { extern QTextStream checkOut; }

using namespace KDevPG;

void InlineChecker::operator()(Model::EvolveItem* node)
{
    if(!mVisited.contains(node->mSymbol))
      visitEvolve(node);
}

void InlineChecker::visitNonTerminal(Model::NonTerminalItem* node)
{
    Q_UNUSED(node);
}

void InlineChecker::visitInlinedNonTerminal(Model::InlinedNonTerminalItem* node)
{
    if(node->mSymbol == nullptr)
        return;
    if(mCurrentlyVisiting.contains(node->mSymbol))
    {
        checkOut << "** ERROR Cyclic inlining of ``" << node->mSymbol->mName << "''\n";
        ProblemSummaryPrinter::reportError();
        throw node->mSymbol;
    }
    if(mVisited.contains(node))
        return;
    if(isOperatorSymbol(node->mSymbol))
    {
        checkOut << "** ERROR Inlining of an operator expression ``" << node->mSymbol->mName << "''\n";
        ProblemSummaryPrinter::reportError();
    }
    mVisited.insert(node);
    mCurrentlyVisiting.insert(node->mSymbol);
    try
    {
        DefaultVisitor::visitInlinedNonTerminal(node);
    }
    catch(Model::SymbolItem* thrown)
    {
        checkOut << "\t\tinlined from ``" << node->mSymbol->mName << "''\n";
        mCurrentlyVisiting.remove(node->mSymbol);
        if(node->mSymbol != thrown)
            throw;
        node->mSymbol = nullptr; // avoid it in future
        return;
    }
    mCurrentlyVisiting.remove(node->mSymbol);
}

