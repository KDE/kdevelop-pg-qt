/***************************************************************************
 *   Copyright (C) 2006 by Jakob Petsovits                                 *
 *   jpetso@gmx.at                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "csharp_pp_scope.h"


csharp_pp_scope::csharp_pp_scope( csharp* parser )
 : _M_type(csharp_pp_scope::type_root), _M_parser(parser),
   _M_child(0), _M_parent(0)
{
  _M_is_active = true;
  _M_waiting_for_active_section = true;
}

csharp_pp_scope::csharp_pp_scope( csharp_pp_scope::scope_type _type,
                                  csharp* _parser, bool active )
 : _M_type(_type), _M_parser(_parser),  _M_child(0)
{
  if (active == true)
    {
      _M_waiting_for_active_section = true;
      _M_is_active = true;
    }
  else
    {
      _M_waiting_for_active_section = false;
      _M_is_active = false;
    }
}

csharp_pp_scope::~csharp_pp_scope()
{
  if (_M_child != 0)
    delete _M_child;
  if (_M_parent != 0)
    _M_parent->_M_child = 0;
}

csharp_pp_scope* csharp_pp_scope::current_scope()
{
  if (_M_child == 0)
    return this;
  else
    return _M_child->current_scope();
}

csharp_pp_scope::scope_type csharp_pp_scope::type()
{
  return _M_type;
}

bool csharp_pp_scope::is_active()
{
  return _M_is_active;
}

bool csharp_pp_scope::is_waiting_for_active_section()
{
  return _M_waiting_for_active_section;
}

void csharp_pp_scope::set_activated( bool active )
{
  if (_M_type != csharp_pp_scope::type_if)
    return;
  else if (_M_waiting_for_active_section == false)
    _M_is_active = false;
  else
    {
      _M_is_active = active;

      if (active == true)
        _M_waiting_for_active_section = false;
    }
}

bool csharp_pp_scope::push_scope (csharp_pp_scope::scope_type type, csharp_pp_scope** new_current )
{
  if (_M_child != 0) {
    *new_current = _M_child->current_scope();
    return false; // only the deepest nested scope shall create children
  }

  _M_child = new csharp_pp_scope(type, _M_parser, _M_is_active);
  _M_child->set_parent(this);
  *new_current = _M_child;
  return true;
}

bool csharp_pp_scope::pop_scope(
  csharp_pp_scope::scope_type type, csharp_pp_scope** new_current )
{
  if (_M_parent == 0 || type != _M_type) {
    *new_current = this->current_scope();
    return false;
  }

  *new_current = _M_parent;
  delete this;
  return true;
}

void csharp_pp_scope::set_parser( csharp* parser )
{
  _M_parser = parser;
}

csharp* csharp_pp_scope::parser()
{
  return _M_parser;
}

void csharp_pp_scope::set_parent( csharp_pp_scope* parent )
{
  _M_parent = parent;
}

csharp_pp_scope* csharp_pp_scope::parent()
{
  return _M_parent;
}
