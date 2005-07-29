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

#ifndef KDEV_PG_UTILS_H
#define KDEV_PG_UTILS_H

#include "kdev-pg.h"
#include "kdev-pg-ast.h"
#include "kdev-pg-default-visitor.h"

#include <list>

struct left_most_items: protected default_visitor
{
  std::list<model::node*> operator()(model::node *node);

protected:
  virtual void visit_symbol(model::symbol_item *node);
  virtual void visit_terminal(model::terminal_item *node);
  virtual void visit_cons(model::cons_item *node);
  virtual void visit_alternative(model::alternative_item *node);
  virtual void visit_evolve(model::evolve_item *node);
  virtual void visit_condition(model::condition_item *node);
  virtual void visit_annotation(model::annotation_item *node);

private:
  std::list<model::node*> _M_symbols;
};

struct right_most_symbols: protected default_visitor
{
  std::set <model::symbol_item*>
  operator()(model::node *node);

protected:
  virtual void visit_cons(model::cons_item *node);
  virtual void visit_alternative(model::alternative_item *node);
  virtual void visit_symbol(model::symbol_item *node);
  virtual void visit_evolve(model::evolve_item *node);
  virtual void visit_condition(model::condition_item *node);
  virtual void visit_annotation(model::annotation_item *node);

private:
  std::set <model::symbol_item*>
  _M_symbols;
};

struct right_tails: protected default_visitor
{
  std::list<model::node*> operator()(model::node *node);

protected:
  virtual void visit_cons(model::cons_item *node);

private:
  std::list<model::node*> _M_tails;
};

#endif // KDEV_PG_UTILS_H

