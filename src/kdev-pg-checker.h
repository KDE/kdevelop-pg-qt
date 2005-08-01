/* This file is part of kdev-pg
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>

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
   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#ifndef KDEV_PG_CHECKER_H
#define KDEV_PG_CHECKER_H

#include "kdev-pg.h"
#include "kdev-pg-default-visitor.h"

struct empty_FIRST_checker: protected default_visitor
{
  void operator()(model::node *node);

protected:
  virtual void visit_symbol(model::symbol_item *node);
};

struct FIRST_FIRST_conflict_checker: protected default_visitor
{
  void operator()(model::node *node);

protected:
  void check(model::node *left, model::node *right);

  virtual void visit_evolve(model::evolve_item *node);
  virtual void visit_alternative(model::alternative_item *node);

private:
  model::node *_M_toplevel;
};

struct FIRST_FOLLOW_conflict_checker: protected default_visitor
{
  void operator()(model::node *node);

protected:
  void check(model::node *node, model::node *sym = 0);

  virtual void visit_evolve(model::evolve_item *node);
  virtual void visit_alternative(model::alternative_item *node);
  virtual void visit_cons(model::cons_item *node);
};

struct undefined_symbol_checker: protected default_visitor
{
  void operator()(model::node *node);

protected:
  virtual void visit_symbol(model::symbol_item *node);
};

#endif // KDEV_PG_CHECKER_H

