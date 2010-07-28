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
    if(node->mSymbol == 0)
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
        node->mSymbol = 0; // avoid it in future
        return;
    }
    mCurrentlyVisiting.remove(node->mSymbol);
}

