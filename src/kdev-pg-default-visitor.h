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

#ifndef KDEV_PG_DEFAULT_VISITOR_H
#define KDEV_PG_DEFAULT_VISITOR_H

#include "kdev-pg-visitor.h"

struct default_visitor: public visitor
{
protected:
  virtual void visit_zero(model::zero_item *node);
  virtual void visit_symbol(model::symbol_item *node);
  virtual void visit_terminal(model::terminal_item *node);
  virtual void visit_bang(model::bang_item *node);
  virtual void visit_action(model::action_item *node);
  virtual void visit_alternative(model::alternative_item *node);
  virtual void visit_cons(model::cons_item *node);
  virtual void visit_evolve(model::evolve_item *node);
  virtual void visit_alias(model::alias_item *node);
  virtual void visit_annotation(model::annotation_item *node);
  virtual void visit_condition(model::condition_item *node);
};

#endif // KDEV_PG_DEFAULT_VISITOR_H
