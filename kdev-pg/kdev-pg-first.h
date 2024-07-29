/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2010 Jonathan Schmidt-Dominé <devel@the-user.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef KDEV_PG_FIRST_H
#define KDEV_PG_FIRST_H

#include "kdev-pg.h"
#include "kdev-pg-bnf-visitor.h"

#include <QSet>

namespace KDevPG
{

/**
 * Adds first-sets for terminals and zeros.
 */
void initializeFirst ();

/**
 * Recursively merge first-sets.
 */
class NextFirst: protected BnfVisitor
{
public:
  NextFirst(bool &changed);

  void operator ()(Model::Node *node);

protected:
  bool blockZeroMerge(bool block);
  void merge(Model::Node *__dest, Model::Node *__source, int K = 1);

  void visitNode(Model::Node *node) override;
  void visitAlternative(Model::AlternativeItem *node) override;
  void visitCons(Model::ConsItem *node) override;
  
  void copy(Model::Node *from, Model::Node *to) override { merge(to, from); }

private:
  bool mMergeZeroBlocked;
  bool &mChanged;
  QSet<Model::Node*> mVisited;
};

/**
 * This method computes the first-set for all symbols.
 * The algorithm: The function starts with InitializeFirst. As long as possible NextFirst will merge first-sets.
 */
void computeFirst();

}

#endif // KDEV_PG_FIRST_H
