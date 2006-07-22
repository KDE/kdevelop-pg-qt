/*****************************************************************************
 * This file is part of KDevelop.                                            *
 * Copyright (c) 2005-2006 Jakob Petsovits <jpetso@gmx.at>                   *
 *                                                                           *
 * This program is free software; you can redistribute it and/or             *
 * modify it under the terms of the GNU Library General Public               *
 * License as published by the Free Software Foundation; either              *
 * version 2 of the License, or (at your option) any later version.          *
 *                                                                           *
 * This grammar is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Lesser General Public License for more details.                           *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public License *
 * along with this library; see the file COPYING.LIB.  If not, write to      *
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,      *
 * Boston, MA 02110-1301, USA.                                               *
 *****************************************************************************/

#include "csharp_lookahead.h"


namespace csharp
{

lookahead::lookahead(parser* parser)
: _M_parser(parser), _M_count(1)
{
    _M_token = _M_parser->yytoken;
    _M_ltCounter = 0;
}

void lookahead::fetch_next_token()
{
    _M_count++;
    _M_token = _M_parser->LA(_M_count).kind;
}



// All the following methods are adapted from the corresponding
// parse*() methods of the autogenerated parser class.
// Most of them are only adapted to simply work with the lookahead
// class (by replacing fetch_next_token() with fetch_next_token(),
// parse*() with is*(), parser::Token_* with parser::Token_*, and so on).
// Some of the methods are modified to check only parts of the rule
// for simplicity and efficiency reasons.



//////////////////////
// Modified methods //
//////////////////////


// modified to return true already on the first comma inside "<" and ">"
bool lookahead::is_unbound_type_name()
{
  if (_M_token == parser::Token_ADD
      || _M_token == parser::Token_ALIAS
      || _M_token == parser::Token_GET
      || _M_token == parser::Token_GLOBAL
      || _M_token == parser::Token_PARTIAL
      || _M_token == parser::Token_REMOVE
      || _M_token == parser::Token_SET
      || _M_token == parser::Token_VALUE
      || _M_token == parser::Token_WHERE
      || _M_token == parser::Token_YIELD
      || _M_token == parser::Token_ASSEMBLY
      || _M_token == parser::Token_IDENTIFIER)
    {
      if ((_M_token == parser::Token_ADD
          || _M_token == parser::Token_ALIAS
          || _M_token == parser::Token_GET
          || _M_token == parser::Token_GLOBAL
          || _M_token == parser::Token_PARTIAL
          || _M_token == parser::Token_REMOVE
          || _M_token == parser::Token_SET
          || _M_token == parser::Token_VALUE
          || _M_token == parser::Token_WHERE
          || _M_token == parser::Token_YIELD
          || _M_token == parser::Token_ASSEMBLY
          || _M_token == parser::Token_IDENTIFIER)
          && (_M_parser->LA(_M_count + 1).kind == parser::Token_SCOPE))
        {
          if (!is_identifier())
            {
              return false;
            }
          if (_M_token != parser::Token_SCOPE)
            return false;
          fetch_next_token();
        }
      else if (true /*epsilon*/)
      {}

      if (_M_token == parser::Token_ADD
          || _M_token == parser::Token_ALIAS
          || _M_token == parser::Token_GET
          || _M_token == parser::Token_GLOBAL
          || _M_token == parser::Token_PARTIAL
          || _M_token == parser::Token_REMOVE
          || _M_token == parser::Token_SET
          || _M_token == parser::Token_VALUE
          || _M_token == parser::Token_WHERE
          || _M_token == parser::Token_YIELD
          || _M_token == parser::Token_ASSEMBLY
          || _M_token == parser::Token_IDENTIFIER)
        {
          if (!is_identifier())
            {
              return false;
            }
          if (_M_token == parser::Token_LESS_THAN)
            {
              if (_M_token != parser::Token_LESS_THAN)
                return false;
              fetch_next_token();

              if (_M_token == parser::Token_GREATER_THAN)
                {
                  return true; // only unbound type names have empty "<>" lists
                }
              while (_M_token == parser::Token_COMMA)
                {
                  return true; // when there's a comma, there's no doubt
                               // that this should be an unbound type name
                }

              if (_M_token != parser::Token_GREATER_THAN)
                return false;
              fetch_next_token();
            }
          else if (true /*epsilon*/)
          {}
          else
            {
              return false;
            }
        }
      else
        {
          return false;
        }
      while (_M_token == parser::Token_DOT)
        {
          if (_M_token == parser::Token_ADD
              || _M_token == parser::Token_ALIAS
              || _M_token == parser::Token_GET
              || _M_token == parser::Token_GLOBAL
              || _M_token == parser::Token_PARTIAL
              || _M_token == parser::Token_REMOVE
              || _M_token == parser::Token_SET
              || _M_token == parser::Token_VALUE
              || _M_token == parser::Token_WHERE
              || _M_token == parser::Token_YIELD
              || _M_token == parser::Token_ASSEMBLY
              || _M_token == parser::Token_IDENTIFIER)
            {
              if (!is_identifier())
                {
                  return false;
                }
              if (_M_token == parser::Token_LESS_THAN)
                {
                  if (_M_token != parser::Token_LESS_THAN)
                    return false;
                  fetch_next_token();
                  while (_M_token == parser::Token_COMMA)
                    {
                      return true; // when there's a comma, there's no doubt
                                   // that this should be an unbound type name
                    }
                  if (_M_token != parser::Token_GREATER_THAN)
                    return false;
                  fetch_next_token();
                }
              else if (true /*epsilon*/)
              {}
              else
                {
                  return false;
                }
            }
          else
            {
              return false;
            }
        }
    }
  else
    {
      return false;
    }

  return true;
}


// modified to only verify on (type identifier) instead of the full rule.
bool lookahead::is_local_variable_declaration_start()
{
  if (_M_token == parser::Token_BOOL
      || _M_token == parser::Token_BYTE
      || _M_token == parser::Token_CHAR
      || _M_token == parser::Token_DECIMAL
      || _M_token == parser::Token_DOUBLE
      || _M_token == parser::Token_FLOAT
      || _M_token == parser::Token_INT
      || _M_token == parser::Token_LONG
      || _M_token == parser::Token_OBJECT
      || _M_token == parser::Token_SBYTE
      || _M_token == parser::Token_SHORT
      || _M_token == parser::Token_STRING
      || _M_token == parser::Token_UINT
      || _M_token == parser::Token_ULONG
      || _M_token == parser::Token_USHORT
      || _M_token == parser::Token_VOID
      || _M_token == parser::Token_ADD
      || _M_token == parser::Token_ALIAS
      || _M_token == parser::Token_GET
      || _M_token == parser::Token_GLOBAL
      || _M_token == parser::Token_PARTIAL
      || _M_token == parser::Token_REMOVE
      || _M_token == parser::Token_SET
      || _M_token == parser::Token_VALUE
      || _M_token == parser::Token_WHERE
      || _M_token == parser::Token_YIELD
      || _M_token == parser::Token_ASSEMBLY
      || _M_token == parser::Token_IDENTIFIER)
    {
      if (!is_type())
        {
          return false;
        }
      if (!is_identifier())
        {
          return false;
        }

      return true;
    }
  else
    {
      return false;
    }

  return true;
}


// modified to only check until the first token after the parentheses
bool lookahead::is_cast_expression_start()
{
  if (_M_token == parser::Token_LPAREN)
    {
      if (_M_token != parser::Token_LPAREN)
        return false;
      fetch_next_token();
      if (!is_type())
        {
          return false;
        }
      if (_M_token != parser::Token_RPAREN)
        return false;
      fetch_next_token();

      if (_M_token == parser::Token_BASE
          || _M_token == parser::Token_BOOL
          || _M_token == parser::Token_BYTE
          || _M_token == parser::Token_CHAR
          || _M_token == parser::Token_CHECKED
          || _M_token == parser::Token_DECIMAL
          || _M_token == parser::Token_DEFAULT
          || _M_token == parser::Token_DELEGATE
          || _M_token == parser::Token_DOUBLE
          || _M_token == parser::Token_FLOAT
          || _M_token == parser::Token_INT
          || _M_token == parser::Token_LONG
          || _M_token == parser::Token_NEW
          || _M_token == parser::Token_OBJECT
          || _M_token == parser::Token_SBYTE
          || _M_token == parser::Token_SHORT
          || _M_token == parser::Token_SIZEOF
          || _M_token == parser::Token_STRING
          || _M_token == parser::Token_THIS
          || _M_token == parser::Token_TYPEOF
          || _M_token == parser::Token_UINT
          || _M_token == parser::Token_ULONG
          || _M_token == parser::Token_UNCHECKED
          || _M_token == parser::Token_USHORT
          || _M_token == parser::Token_ADD
          || _M_token == parser::Token_ALIAS
          || _M_token == parser::Token_GET
          || _M_token == parser::Token_GLOBAL
          || _M_token == parser::Token_PARTIAL
          || _M_token == parser::Token_REMOVE
          || _M_token == parser::Token_SET
          || _M_token == parser::Token_VALUE
          || _M_token == parser::Token_WHERE
          || _M_token == parser::Token_YIELD
          || _M_token == parser::Token_ASSEMBLY
          || _M_token == parser::Token_LPAREN
          || _M_token == parser::Token_BANG
          || _M_token == parser::Token_TILDE
          || _M_token == parser::Token_INCREMENT
          || _M_token == parser::Token_DECREMENT
          //|| _M_token == parser::Token_PLUS  // I think the probability
          //|| _M_token == parser::Token_MINUS // of normal expressions
          //|| _M_token == parser::Token_STAR  // is higher in this case
          || _M_token == parser::Token_BIT_AND
          || _M_token == parser::Token_TRUE
          || _M_token == parser::Token_FALSE
          || _M_token == parser::Token_NULL
          || _M_token == parser::Token_INTEGER_LITERAL
          || _M_token == parser::Token_REAL_LITERAL
          || _M_token == parser::Token_CHARACTER_LITERAL
          || _M_token == parser::Token_STRING_LITERAL
          || _M_token == parser::Token_IDENTIFIER)
        {
          return true;
        }
      else
        {
          return false;
        }
    }
  else
    {
      return false;
    }

  return true;
}

// This is directly is_unmanaged_type, as is_type just redirects
bool lookahead::is_type()
{
  if (_M_token == parser::Token_BOOL
      || _M_token == parser::Token_BYTE
      || _M_token == parser::Token_CHAR
      || _M_token == parser::Token_DECIMAL
      || _M_token == parser::Token_DOUBLE
      || _M_token == parser::Token_FLOAT
      || _M_token == parser::Token_INT
      || _M_token == parser::Token_LONG
      || _M_token == parser::Token_OBJECT
      || _M_token == parser::Token_SBYTE
      || _M_token == parser::Token_SHORT
      || _M_token == parser::Token_STRING
      || _M_token == parser::Token_UINT
      || _M_token == parser::Token_ULONG
      || _M_token == parser::Token_USHORT
      || _M_token == parser::Token_ADD
      || _M_token == parser::Token_ALIAS
      || _M_token == parser::Token_GET
      || _M_token == parser::Token_GLOBAL
      || _M_token == parser::Token_PARTIAL
      || _M_token == parser::Token_REMOVE
      || _M_token == parser::Token_SET
      || _M_token == parser::Token_VALUE
      || _M_token == parser::Token_WHERE
      || _M_token == parser::Token_YIELD
      || _M_token == parser::Token_ASSEMBLY
      || _M_token == parser::Token_IDENTIFIER)
    {
      if (!is_managed_type())
        {
          return false;
        }
    }
  else if (_M_token == parser::Token_VOID)
    {
      if (_M_token != parser::Token_VOID)
        return false;
      fetch_next_token();
      if (_M_token != parser::Token_STAR)
        return false;
      fetch_next_token();
    }
  else
    {
      return false;
    }
  while (_M_token == parser::Token_STAR)
    {
      if (_M_token != parser::Token_STAR)
        return false;
      fetch_next_token();
    }

  return true;
}

bool lookahead::is_managed_type()
{
  if (_M_token == parser::Token_BOOL
      || _M_token == parser::Token_BYTE
      || _M_token == parser::Token_CHAR
      || _M_token == parser::Token_DECIMAL
      || _M_token == parser::Token_DOUBLE
      || _M_token == parser::Token_FLOAT
      || _M_token == parser::Token_INT
      || _M_token == parser::Token_LONG
      || _M_token == parser::Token_OBJECT
      || _M_token == parser::Token_SBYTE
      || _M_token == parser::Token_SHORT
      || _M_token == parser::Token_STRING
      || _M_token == parser::Token_UINT
      || _M_token == parser::Token_ULONG
      || _M_token == parser::Token_USHORT
      || _M_token == parser::Token_ADD
      || _M_token == parser::Token_ALIAS
      || _M_token == parser::Token_GET
      || _M_token == parser::Token_GLOBAL
      || _M_token == parser::Token_PARTIAL
      || _M_token == parser::Token_REMOVE
      || _M_token == parser::Token_SET
      || _M_token == parser::Token_VALUE
      || _M_token == parser::Token_WHERE
      || _M_token == parser::Token_YIELD
      || _M_token == parser::Token_ASSEMBLY
      || _M_token == parser::Token_IDENTIFIER)
    {
      if (!is_non_array_type())
        {
          return false;
        }
      while (_M_token == parser::Token_LBRACKET)
        {
          if (_M_parser->LA(_M_count + 1).kind != parser::Token_COMMA
              && _M_parser->LA(_M_count + 1).kind != parser::Token_RBRACKET)
            {
              break;
            }
          if (!is_rank_specifier())
            {
              return false;
            }
        }
    }
  else
    {
      return false;
    }

  return true;
}

bool lookahead::is_non_array_type()
{
  if (_M_token == parser::Token_BOOL
      || _M_token == parser::Token_BYTE
      || _M_token == parser::Token_CHAR
      || _M_token == parser::Token_DECIMAL
      || _M_token == parser::Token_DOUBLE
      || _M_token == parser::Token_FLOAT
      || _M_token == parser::Token_INT
      || _M_token == parser::Token_LONG
      || _M_token == parser::Token_OBJECT
      || _M_token == parser::Token_SBYTE
      || _M_token == parser::Token_SHORT
      || _M_token == parser::Token_STRING
      || _M_token == parser::Token_UINT
      || _M_token == parser::Token_ULONG
      || _M_token == parser::Token_USHORT
      || _M_token == parser::Token_ADD
      || _M_token == parser::Token_ALIAS
      || _M_token == parser::Token_GET
      || _M_token == parser::Token_GLOBAL
      || _M_token == parser::Token_PARTIAL
      || _M_token == parser::Token_REMOVE
      || _M_token == parser::Token_SET
      || _M_token == parser::Token_VALUE
      || _M_token == parser::Token_WHERE
      || _M_token == parser::Token_YIELD
      || _M_token == parser::Token_ASSEMBLY
      || _M_token == parser::Token_IDENTIFIER)
    {
      if (_M_token == parser::Token_OBJECT
          || _M_token == parser::Token_STRING)
        {
          if (!is_builtin_class_type())
            {
              return false;
            }
        }
      else if (_M_token == parser::Token_BOOL
               || _M_token == parser::Token_BYTE
               || _M_token == parser::Token_CHAR
               || _M_token == parser::Token_DECIMAL
               || _M_token == parser::Token_DOUBLE
               || _M_token == parser::Token_FLOAT
               || _M_token == parser::Token_INT
               || _M_token == parser::Token_LONG
               || _M_token == parser::Token_SBYTE
               || _M_token == parser::Token_SHORT
               || _M_token == parser::Token_UINT
               || _M_token == parser::Token_ULONG
               || _M_token == parser::Token_USHORT
               || _M_token == parser::Token_ADD
               || _M_token == parser::Token_ALIAS
               || _M_token == parser::Token_GET
               || _M_token == parser::Token_GLOBAL
               || _M_token == parser::Token_PARTIAL
               || _M_token == parser::Token_REMOVE
               || _M_token == parser::Token_SET
               || _M_token == parser::Token_VALUE
               || _M_token == parser::Token_WHERE
               || _M_token == parser::Token_YIELD
               || _M_token == parser::Token_ASSEMBLY
               || _M_token == parser::Token_IDENTIFIER)
        {
          if (!is_optionally_nullable_type())
            {
              return false;
            }
        }
      else
        {
          return false;
        }
    }
  else
    {
      return false;
    }

  return true;
}

bool lookahead::is_optionally_nullable_type()
{
  if (_M_token == parser::Token_BOOL
      || _M_token == parser::Token_BYTE
      || _M_token == parser::Token_CHAR
      || _M_token == parser::Token_DECIMAL
      || _M_token == parser::Token_DOUBLE
      || _M_token == parser::Token_FLOAT
      || _M_token == parser::Token_INT
      || _M_token == parser::Token_LONG
      || _M_token == parser::Token_SBYTE
      || _M_token == parser::Token_SHORT
      || _M_token == parser::Token_UINT
      || _M_token == parser::Token_ULONG
      || _M_token == parser::Token_USHORT
      || _M_token == parser::Token_ADD
      || _M_token == parser::Token_ALIAS
      || _M_token == parser::Token_GET
      || _M_token == parser::Token_GLOBAL
      || _M_token == parser::Token_PARTIAL
      || _M_token == parser::Token_REMOVE
      || _M_token == parser::Token_SET
      || _M_token == parser::Token_VALUE
      || _M_token == parser::Token_WHERE
      || _M_token == parser::Token_YIELD
      || _M_token == parser::Token_ASSEMBLY
      || _M_token == parser::Token_IDENTIFIER)
    {
      if (!is_non_nullable_type())
        {
          return false;
        }
      if ((_M_token == parser::Token_QUESTION)
          && ( _M_parser->compatibility_mode() >= parser::csharp20_compatibility ))
        {
          if (_M_token != parser::Token_QUESTION)
            return false;
          fetch_next_token();
        }
      else if (true /*epsilon*/)
      {}
    }
  else
    {
      return false;
    }

  return true;
}

bool lookahead::is_non_nullable_type()
{
  if (_M_token == parser::Token_BOOL
      || _M_token == parser::Token_BYTE
      || _M_token == parser::Token_CHAR
      || _M_token == parser::Token_DECIMAL
      || _M_token == parser::Token_DOUBLE
      || _M_token == parser::Token_FLOAT
      || _M_token == parser::Token_INT
      || _M_token == parser::Token_LONG
      || _M_token == parser::Token_SBYTE
      || _M_token == parser::Token_SHORT
      || _M_token == parser::Token_UINT
      || _M_token == parser::Token_ULONG
      || _M_token == parser::Token_USHORT
      || _M_token == parser::Token_ADD
      || _M_token == parser::Token_ALIAS
      || _M_token == parser::Token_GET
      || _M_token == parser::Token_GLOBAL
      || _M_token == parser::Token_PARTIAL
      || _M_token == parser::Token_REMOVE
      || _M_token == parser::Token_SET
      || _M_token == parser::Token_VALUE
      || _M_token == parser::Token_WHERE
      || _M_token == parser::Token_YIELD
      || _M_token == parser::Token_ASSEMBLY
      || _M_token == parser::Token_IDENTIFIER)
    {
      if (_M_token == parser::Token_ADD
          || _M_token == parser::Token_ALIAS
          || _M_token == parser::Token_GET
          || _M_token == parser::Token_GLOBAL
          || _M_token == parser::Token_PARTIAL
          || _M_token == parser::Token_REMOVE
          || _M_token == parser::Token_SET
          || _M_token == parser::Token_VALUE
          || _M_token == parser::Token_WHERE
          || _M_token == parser::Token_YIELD
          || _M_token == parser::Token_ASSEMBLY
          || _M_token == parser::Token_IDENTIFIER)
        {
          if (!is_type_name())
            {
              return false;
            }
        }
      else if (_M_token == parser::Token_BOOL
               || _M_token == parser::Token_BYTE
               || _M_token == parser::Token_CHAR
               || _M_token == parser::Token_DECIMAL
               || _M_token == parser::Token_DOUBLE
               || _M_token == parser::Token_FLOAT
               || _M_token == parser::Token_INT
               || _M_token == parser::Token_LONG
               || _M_token == parser::Token_SBYTE
               || _M_token == parser::Token_SHORT
               || _M_token == parser::Token_UINT
               || _M_token == parser::Token_ULONG
               || _M_token == parser::Token_USHORT)
        {
          if (!is_simple_type())
            {
              return false;
            }
        }
      else
        {
          return false;
        }
    }
  else
    {
      return false;
    }

  return true;
}

// this is actually is_namespace_or_type_name, which type_name links directly to
bool lookahead::is_type_name()
{
  if (_M_token == parser::Token_ADD
      || _M_token == parser::Token_ALIAS
      || _M_token == parser::Token_GET
      || _M_token == parser::Token_GLOBAL
      || _M_token == parser::Token_PARTIAL
      || _M_token == parser::Token_REMOVE
      || _M_token == parser::Token_SET
      || _M_token == parser::Token_VALUE
      || _M_token == parser::Token_WHERE
      || _M_token == parser::Token_YIELD
      || _M_token == parser::Token_ASSEMBLY
      || _M_token == parser::Token_IDENTIFIER)
    {
      if ((_M_token == parser::Token_ADD
          || _M_token == parser::Token_ALIAS
          || _M_token == parser::Token_GET
          || _M_token == parser::Token_GLOBAL
          || _M_token == parser::Token_PARTIAL
          || _M_token == parser::Token_REMOVE
          || _M_token == parser::Token_SET
          || _M_token == parser::Token_VALUE
          || _M_token == parser::Token_WHERE
          || _M_token == parser::Token_YIELD
          || _M_token == parser::Token_ASSEMBLY
          || _M_token == parser::Token_IDENTIFIER)
          && (_M_parser->LA(_M_count + 1).kind == parser::Token_SCOPE))
        {
          if (!is_identifier())
            {
              return false;
            }
          if (_M_token != parser::Token_SCOPE)
            return false;
          fetch_next_token();
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      if (!is_namespace_or_type_name_part())
        {
          return false;
        }
      while (_M_token == parser::Token_DOT)
        {
          if (_M_token != parser::Token_DOT)
            return false;
          fetch_next_token();
          if (!is_namespace_or_type_name_part())
            {
              return false;
            }
        }
    }
  else
    {
      return false;
    }

  return true;
}

bool lookahead::is_namespace_or_type_name_part()
{
  if (_M_token == parser::Token_ADD
      || _M_token == parser::Token_ALIAS
      || _M_token == parser::Token_GET
      || _M_token == parser::Token_GLOBAL
      || _M_token == parser::Token_PARTIAL
      || _M_token == parser::Token_REMOVE
      || _M_token == parser::Token_SET
      || _M_token == parser::Token_VALUE
      || _M_token == parser::Token_WHERE
      || _M_token == parser::Token_YIELD
      || _M_token == parser::Token_ASSEMBLY
      || _M_token == parser::Token_IDENTIFIER)
    {
      if (!is_identifier())
        {
          return false;
        }
      if ((_M_token == parser::Token_LESS_THAN)
          && ( _M_parser->compatibility_mode() >= parser::csharp20_compatibility ))
        {
          if (!is_type_arguments())
            {
              return false;
            }
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
    }
  else
    {
      return false;
    }

  return true;
}

bool lookahead::is_simple_type()
{
  if (_M_token == parser::Token_BOOL
      || _M_token == parser::Token_BYTE
      || _M_token == parser::Token_CHAR
      || _M_token == parser::Token_DECIMAL
      || _M_token == parser::Token_DOUBLE
      || _M_token == parser::Token_FLOAT
      || _M_token == parser::Token_INT
      || _M_token == parser::Token_LONG
      || _M_token == parser::Token_SBYTE
      || _M_token == parser::Token_SHORT
      || _M_token == parser::Token_UINT
      || _M_token == parser::Token_ULONG
      || _M_token == parser::Token_USHORT)
    {
      if (_M_token == parser::Token_BYTE
          || _M_token == parser::Token_CHAR
          || _M_token == parser::Token_DECIMAL
          || _M_token == parser::Token_DOUBLE
          || _M_token == parser::Token_FLOAT
          || _M_token == parser::Token_INT
          || _M_token == parser::Token_LONG
          || _M_token == parser::Token_SBYTE
          || _M_token == parser::Token_SHORT
          || _M_token == parser::Token_UINT
          || _M_token == parser::Token_ULONG
          || _M_token == parser::Token_USHORT)
        {
          if (!is_numeric_type())
            {
              return false;
            }
        }
      else if (_M_token == parser::Token_BOOL)
        {
          if (_M_token != parser::Token_BOOL)
            return false;
          fetch_next_token();
        }
      else
        {
          return false;
        }
    }
  else
    {
      return false;
    }

  return true;
}

bool lookahead::is_numeric_type()
{
  if (_M_token == parser::Token_BYTE
      || _M_token == parser::Token_CHAR
      || _M_token == parser::Token_DECIMAL
      || _M_token == parser::Token_DOUBLE
      || _M_token == parser::Token_FLOAT
      || _M_token == parser::Token_INT
      || _M_token == parser::Token_LONG
      || _M_token == parser::Token_SBYTE
      || _M_token == parser::Token_SHORT
      || _M_token == parser::Token_UINT
      || _M_token == parser::Token_ULONG
      || _M_token == parser::Token_USHORT)
    {
      if (_M_token == parser::Token_BYTE
          || _M_token == parser::Token_CHAR
          || _M_token == parser::Token_INT
          || _M_token == parser::Token_LONG
          || _M_token == parser::Token_SBYTE
          || _M_token == parser::Token_SHORT
          || _M_token == parser::Token_UINT
          || _M_token == parser::Token_ULONG
          || _M_token == parser::Token_USHORT)
        {
          if (!is_integral_type())
            {
              return false;
            }
        }
      else if (_M_token == parser::Token_DOUBLE
               || _M_token == parser::Token_FLOAT)
        {
          if (!is_floating_point_type())
            {
              return false;
            }
        }
      else if (_M_token == parser::Token_DECIMAL)
        {
          if (_M_token != parser::Token_DECIMAL)
            return false;
          fetch_next_token();
        }
      else
        {
          return false;
        }
    }
  else
    {
      return false;
    }

  return true;
}

bool lookahead::is_floating_point_type()
{
  if (_M_token == parser::Token_DOUBLE
      || _M_token == parser::Token_FLOAT)
    {
      if (_M_token == parser::Token_FLOAT)
        {
          if (_M_token != parser::Token_FLOAT)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_DOUBLE)
        {
          if (_M_token != parser::Token_DOUBLE)
            return false;
          fetch_next_token();
        }
      else
        {
          return false;
        }
    }
  else
    {
      return false;
    }

  return true;
}

bool lookahead::is_integral_type()
{
  if (_M_token == parser::Token_BYTE
      || _M_token == parser::Token_CHAR
      || _M_token == parser::Token_INT
      || _M_token == parser::Token_LONG
      || _M_token == parser::Token_SBYTE
      || _M_token == parser::Token_SHORT
      || _M_token == parser::Token_UINT
      || _M_token == parser::Token_ULONG
      || _M_token == parser::Token_USHORT)
    {
      if (_M_token == parser::Token_SBYTE)
        {
          if (_M_token != parser::Token_SBYTE)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_BYTE)
        {
          if (_M_token != parser::Token_BYTE)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_SHORT)
        {
          if (_M_token != parser::Token_SHORT)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_USHORT)
        {
          if (_M_token != parser::Token_USHORT)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_INT)
        {
          if (_M_token != parser::Token_INT)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_UINT)
        {
          if (_M_token != parser::Token_UINT)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_LONG)
        {
          if (_M_token != parser::Token_LONG)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_ULONG)
        {
          if (_M_token != parser::Token_ULONG)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_CHAR)
        {
          if (_M_token != parser::Token_CHAR)
            return false;
          fetch_next_token();
        }
      else
        {
          return false;
        }
    }
  else
    {
      return false;
    }

  return true;
}

bool lookahead::is_builtin_class_type()
{
  if (_M_token == parser::Token_OBJECT
      || _M_token == parser::Token_STRING)
    {
      if (_M_token == parser::Token_OBJECT)
        {
          if (_M_token != parser::Token_OBJECT)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_STRING)
        {
          if (_M_token != parser::Token_STRING)
            return false;
          fetch_next_token();
        }
      else
        {
          return false;
        }
    }
  else
    {
      return false;
    }

  return true;
}

bool lookahead::is_rank_specifier()
{
  if (_M_token == parser::Token_LBRACKET)
    {
      if (_M_token != parser::Token_LBRACKET)
        return false;
      fetch_next_token();
      while (_M_token == parser::Token_COMMA)
        {
          if (_M_token != parser::Token_COMMA)
            return false;
          fetch_next_token();
        }
      if (_M_token != parser::Token_RBRACKET)
        return false;
      fetch_next_token();
    }
  else
    {
      return false;
    }

  return true;
}

// modified to accept almost anything within <...>
bool lookahead::is_type_arguments()
{
  if (_M_token == parser::Token_LESS_THAN)
    {
      fetch_next_token();

      int currentLtLevel = _M_ltCounter;
      _M_ltCounter++;

      if (!is_type())
        {
          return false;
        }
      while (_M_token == parser::Token_COMMA)
        {
          fetch_next_token();
          if (!is_type())
            {
              return false;
            }
        }
      if (_M_token == parser::Token_GREATER_THAN
          || _M_token == parser::Token_RSHIFT)
        {
          if (!is_type_arguments_or_parameters_end())
            {
              return false;
            }
        }
      else if (true /*epsilon*/)
      {}

      if ( currentLtLevel == 0 && _M_ltCounter > currentLtLevel )
        {
          return false;
        }
    }
  else
    {
      return false;
    }

  return true;
}

bool lookahead::is_type_arguments_or_parameters_end()
{
  if (_M_token == parser::Token_GREATER_THAN
      || _M_token == parser::Token_RSHIFT)
    {
      if (_M_token == parser::Token_GREATER_THAN)
        {
          if (_M_token != parser::Token_GREATER_THAN)
            return false;
          fetch_next_token();
          _M_ltCounter -= 1;
        }
      else if (_M_token == parser::Token_RSHIFT)
        {
          if (_M_token != parser::Token_RSHIFT)
            return false;
          fetch_next_token();
          _M_ltCounter -= 2;
        }
      else
        {
          return false;
        }
    }
  else
    {
      return false;
    }

  return true;
}


bool lookahead::is_identifier()
{
  if (_M_token == parser::Token_ADD
      || _M_token == parser::Token_ALIAS
      || _M_token == parser::Token_GET
      || _M_token == parser::Token_GLOBAL
      || _M_token == parser::Token_PARTIAL
      || _M_token == parser::Token_REMOVE
      || _M_token == parser::Token_SET
      || _M_token == parser::Token_VALUE
      || _M_token == parser::Token_WHERE
      || _M_token == parser::Token_YIELD
      || _M_token == parser::Token_ASSEMBLY
      || _M_token == parser::Token_IDENTIFIER)
    {
      if (_M_token == parser::Token_IDENTIFIER)
        {
          if (_M_token != parser::Token_IDENTIFIER)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_ADD)
        {
          if (_M_token != parser::Token_ADD)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_ALIAS)
        {
          if (_M_token != parser::Token_ALIAS)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_GET)
        {
          if (_M_token != parser::Token_GET)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_GLOBAL)
        {
          if (_M_token != parser::Token_GLOBAL)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_PARTIAL)
        {
          if (_M_token != parser::Token_PARTIAL)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_REMOVE)
        {
          if (_M_token != parser::Token_REMOVE)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_SET)
        {
          if (_M_token != parser::Token_SET)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_VALUE)
        {
          if (_M_token != parser::Token_VALUE)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_WHERE)
        {
          if (_M_token != parser::Token_WHERE)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_YIELD)
        {
          if (_M_token != parser::Token_YIELD)
            return false;
          fetch_next_token();
        }
      else if (_M_token == parser::Token_ASSEMBLY)
        {
          if (_M_token != parser::Token_ASSEMBLY)
            return false;
          fetch_next_token();
        }
      else
        {
          return false;
        }
    }
  else
    {
      return false;
    }

  return true;
}


} // end of namespace csharp

