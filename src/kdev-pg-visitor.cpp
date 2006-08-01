/* This file is part of kdev-pg
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>
   Copyright (C) 2006 Jakob Petsovits <jpetso@gmx.at>

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

#include "kdev-pg-visitor.h"

visitor::visitor_fun_ptr visitor::_S_table[model::node_kind_LAST] = {
  0,
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_zero),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_plus),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_star),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_symbol),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_action),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_alternative),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_cons),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_evolve),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_try_catch),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_alias),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_terminal),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_nonterminal),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_annotation),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_condition),
  reinterpret_cast<visitor::visitor_fun_ptr>(&visitor::visit_variable_declaration),
};
