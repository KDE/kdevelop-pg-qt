/*
   Copyright (C) 2010 Jonathan Schmidt-Dominé <devel@the-user.org>
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
    virtual void visitNonTerminal(Model::NonTerminalItem* node);
    virtual void visitInlinedNonTerminal(Model::InlinedNonTerminalItem* node);
private:
    QSet<Model::Node*> mVisited, mCurrentlyVisiting;
};

}

#endif // KDEVPG_INLINE_CHECKER_H
