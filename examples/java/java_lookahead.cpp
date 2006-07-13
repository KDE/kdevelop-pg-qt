/*****************************************************************************
 * This file is part of KDevelop.                                            *
 * Copyright (c) 2005 Jakob Petsovits <jpetso@gmx.at>                        *
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

#include "java_lookahead.h"


java_lookahead::java_lookahead(java* parser)
: _M_parser(parser), _M_count(1)
{
	_M_token = _M_parser->yytoken;
}

void java_lookahead::fetch_next_token()
{
	_M_count++;
	_M_token = _M_parser->LA(_M_count).kind;
}



// All the following methods are adapted from the corresponding
// is_*() methods of the autogenerated java class.
// Most of them are only adapted to simply work with the java_lookahead
// class (by replacing fetch_next_token() with fetch_next_token(),
// is_*(&node) with is_*(), Token_* with java::Token_*, and so on).
// Some of the methods are modified to check only parts of the rule
// for simplicity and efficiency reasons.



//////////////////////
// Modified methods //
//////////////////////


// modified to require only the tokens up to the variable name
// (the identifier after the type specification)
bool java_lookahead::is_parameter_declaration_start()
{
  if (_M_token == java::Token_AT
      || _M_token == java::Token_FINAL
      || _M_token == java::Token_VOID
      || _M_token == java::Token_BOOLEAN
      || _M_token == java::Token_BYTE
      || _M_token == java::Token_CHAR
      || _M_token == java::Token_SHORT
      || _M_token == java::Token_INT
      || _M_token == java::Token_FLOAT
      || _M_token == java::Token_LONG
      || _M_token == java::Token_DOUBLE
      || _M_token == java::Token_IDENTIFIER)
    {
      if (!is_optional_parameter_modifiers())
        {
          return false;
        }

      if (!is_type())
        {
          return false;
        }

      if (!is_identifier())
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


// modified to require only the tokens up to "package"
bool java_lookahead::is_package_declaration_start()
{
  if (_M_token == java::Token_PACKAGE
      || _M_token == java::Token_AT)
    {
      if (_M_token == java::Token_AT)
        {
          while (_M_token == java::Token_AT)
            {
              if (!is_annotation())
                {
                  return false;
                }
            }
        }

      else if (true /*epsilon*/)
      {}

      if (_M_token != java::Token_PACKAGE)
        return false;

      fetch_next_token();
    }

  else
    {
      return false;
    }

  return true;
}


// modified to require only "(type)" and the first token of the casted
// expression. The expression itself is not parsed. Whoever wants to
// do it will have great fun duplicating all expression rule children.
bool java_lookahead::is_cast_expression_start()
{
  if (_M_token == java::Token_LPAREN)
    {
      if (_M_token != java::Token_LPAREN)
        return false;

      fetch_next_token();

      if (_M_token == java::Token_VOID
          || _M_token == java::Token_BOOLEAN
          || _M_token == java::Token_BYTE
          || _M_token == java::Token_CHAR
          || _M_token == java::Token_SHORT
          || _M_token == java::Token_INT
          || _M_token == java::Token_FLOAT
          || _M_token == java::Token_LONG
          || _M_token == java::Token_DOUBLE)
        {
          if (!is_optional_array_builtin_type())
            {
              return false;
            }

          if (_M_token != java::Token_RPAREN)
            return false;

          fetch_next_token();
        }

      else if (_M_token == java::Token_IDENTIFIER)
        {
          if (!is_class_type())
          {
            return false;
          }

          if (_M_token != java::Token_RPAREN)
            return false;

          fetch_next_token();

          if (_M_token == java::Token_LPAREN
              || _M_token == java::Token_LESS_THAN
              || _M_token == java::Token_SUPER
              || _M_token == java::Token_VOID
              || _M_token == java::Token_BOOLEAN
              || _M_token == java::Token_BYTE
              || _M_token == java::Token_CHAR
              || _M_token == java::Token_SHORT
              || _M_token == java::Token_INT
              || _M_token == java::Token_FLOAT
              || _M_token == java::Token_LONG
              || _M_token == java::Token_DOUBLE
                //|| _M_token == java::Token_PLUS  // I think the probability of normal
                //|| _M_token == java::Token_MINUS // expressions is higher in this case
              || _M_token == java::Token_INCREMENT
              || _M_token == java::Token_DECREMENT
              || _M_token == java::Token_TILDE
              || _M_token == java::Token_BANG
              || _M_token == java::Token_THIS
              || _M_token == java::Token_NEW
              || _M_token == java::Token_IDENTIFIER
              || _M_token == java::Token_TRUE
              || _M_token == java::Token_FALSE
              || _M_token == java::Token_NULL
              || _M_token == java::Token_INTEGER_LITERAL
              || _M_token == java::Token_FLOATING_POINT_LITERAL
              || _M_token == java::Token_CHARACTER_LITERAL
              || _M_token == java::Token_STRING_LITERAL)
            {
              return true;
            }
          else
            {
              return false;
            }
        }
      else // not an identifier or builtin type
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


// modified to accept almost anything within the parentheses
bool java_lookahead::is_annotation()
{
  if (_M_token == java::Token_AT)
    {
      if (_M_token != java::Token_AT)
        return false;

      fetch_next_token();

      if (!is_qualified_identifier())
        {
          return false;
        }

      if (_M_token == java::Token_LPAREN)
        {
          if (_M_token != java::Token_LPAREN)
            return false;

          fetch_next_token();

          // This is where the original version is modified.
          // Instead of copying half of the real parser in here,
          // we just count opening and closing parentheses so we know
          // when the annotation parentheses are closed again.
          // The real validation work is done by the real parser.
          // This way the annotation values are not checked at all,
          // but it's nevertheless good enough for look-ahead.

          int parenCount = 0; // amount of opened parentheses

          while (true)
            {
              if (_M_token == java::Token_LPAREN)
                {
                  parenCount++;
                }
              else if (_M_token == java::Token_RPAREN)
                {
                  if (parenCount == 0)
                    {
                      break;
                    }
                  else
                    {
                      parenCount--;
                    }
                }
              else if (_M_token == java::Token_SEMICOLON
                       || _M_token == java::Token_PACKAGE
                       || _M_token == java::Token_EOF)
                {
                  return false;
                   // for performance reasons - otherwise an unclosed LPAREN
                   // can cause the whole file to be read.
                }

              fetch_next_token();
            }

          if (_M_token != java::Token_RPAREN)
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


// modified to accept almost anything within <...>
bool java_lookahead::is_type_arguments()
{
  if (_M_token == java::Token_LESS_THAN)
    {
      if (_M_token != java::Token_LESS_THAN)
        return false;

      int ltCount = 1;

      fetch_next_token();

      while (true)
        {
          if (_M_token == java::Token_LESS_THAN)
            {
              ltCount += 1;
            }

          else if (_M_token == java::Token_GREATER_THAN)
            {
              ltCount -= 1;
            }

          else if (_M_token == java::Token_SIGNED_RSHIFT)
            {
              ltCount -= 2;
            }

          else if (_M_token == java::Token_UNSIGNED_RSHIFT)
            {
              ltCount -= 3;
            }

          else if (_M_token == java::Token_SEMICOLON
                   || _M_token == java::Token_EOF)
            {
              return false;
              // for performance reasons - otherwise an unclosed LESS_THAN
              // can cause the whole file to be read. As neither of them
              // can occur in type arguments, this is also correct.
            }

          fetch_next_token();

          if ( ltCount <= 0 )
            {
              break;
            }

        } // end while loop

    }
  else
    {
      return false;
    }

  return true;
}




////////////////////////////////////
// Original methods, only adapted //
////////////////////////////////////


bool java_lookahead::is_optional_parameter_modifiers()
{
  if (_M_token == java::Token_AT
      || _M_token == java::Token_FINAL
      || _M_token == java::Token_VOID
      || _M_token == java::Token_BOOLEAN
      || _M_token == java::Token_BYTE
      || _M_token == java::Token_CHAR
      || _M_token == java::Token_SHORT
      || _M_token == java::Token_INT
      || _M_token == java::Token_FLOAT
      || _M_token == java::Token_LONG
      || _M_token == java::Token_DOUBLE
      || _M_token == java::Token_IDENTIFIER)
    {
      if (_M_token == java::Token_AT
          || _M_token == java::Token_FINAL)
        {
          while (_M_token == java::Token_AT
                 || _M_token == java::Token_FINAL)
            {
              if (_M_token == java::Token_FINAL)
                {
                  if (_M_token != java::Token_FINAL)
                    return false;

                  fetch_next_token();
                }

              else if (_M_token == java::Token_AT)
                {
                  if (!is_annotation())
                    {
                      return false;
                    }
                }
            }
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


bool java_lookahead::is_optional_modifiers()
{
  if (_M_token == java::Token_STATIC
      || _M_token == java::Token_AT
      || _M_token == java::Token_FINAL
      || _M_token == java::Token_SYNCHRONIZED
      || _M_token == java::Token_PRIVATE
      || _M_token == java::Token_PUBLIC
      || _M_token == java::Token_PROTECTED
      || _M_token == java::Token_TRANSIENT
      || _M_token == java::Token_ABSTRACT
      || _M_token == java::Token_NATIVE
      || _M_token == java::Token_VOLATILE
      || _M_token == java::Token_STRICTFP
      || _M_token == java::Token_CLASS
      || _M_token == java::Token_INTERFACE
      || _M_token == java::Token_ENUM
      || _M_token == java::Token_AT
      || _M_token == java::Token_LESS_THAN
      || _M_token == java::Token_VOID
      || _M_token == java::Token_BOOLEAN
      || _M_token == java::Token_BYTE
      || _M_token == java::Token_CHAR
      || _M_token == java::Token_SHORT
      || _M_token == java::Token_INT
      || _M_token == java::Token_FLOAT
      || _M_token == java::Token_LONG
      || _M_token == java::Token_DOUBLE
      || _M_token == java::Token_IDENTIFIER)
    {
      if (_M_token == java::Token_STATIC
          || _M_token == java::Token_AT
          || _M_token == java::Token_FINAL
          || _M_token == java::Token_SYNCHRONIZED
          || _M_token == java::Token_PRIVATE
          || _M_token == java::Token_PUBLIC
          || _M_token == java::Token_PROTECTED
          || _M_token == java::Token_TRANSIENT
          || _M_token == java::Token_ABSTRACT
          || _M_token == java::Token_NATIVE
          || _M_token == java::Token_VOLATILE
          || _M_token == java::Token_STRICTFP)
        {
          while (_M_token == java::Token_STATIC
                 || _M_token == java::Token_AT
                 || _M_token == java::Token_FINAL
                 || _M_token == java::Token_SYNCHRONIZED
                 || _M_token == java::Token_PRIVATE
                 || _M_token == java::Token_PUBLIC
                 || _M_token == java::Token_PROTECTED
                 || _M_token == java::Token_TRANSIENT
                 || _M_token == java::Token_ABSTRACT
                 || _M_token == java::Token_NATIVE
                 || _M_token == java::Token_VOLATILE
                 || _M_token == java::Token_STRICTFP)
            {
              if (_M_token == java::Token_AT)
                {
                  if (_M_token == java::Token_AT
                      && _M_parser->LA(_M_count + 1).kind == java::Token_INTERFACE)
                    {
                      break;
                    }

                  if (!is_annotation())
                    {
                      return false;
                    }
                }

              else // all other modifiers, single tokens
                {
                  fetch_next_token();
                }
            }
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


bool java_lookahead::is_identifier()
{
  if (_M_token == java::Token_IDENTIFIER)
    {
      if (_M_token != java::Token_IDENTIFIER)
        return false;

      fetch_next_token();
    }

  else
    {
      return false;
    }

  return true;
}

bool java_lookahead::is_qualified_identifier()
{
  if (_M_token == java::Token_IDENTIFIER)
    {
      if (!is_identifier())
        {
          return false;
        }

      if (_M_token == java::Token_DOT)
        {
          while (_M_token == java::Token_DOT)
            {
              if (_M_token != java::Token_DOT)
                return false;

              fetch_next_token();

              if (!is_identifier())
                {
                  return false;
                }
            }
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


bool java_lookahead::is_type()
{
  if (_M_token == java::Token_VOID
      || _M_token == java::Token_BOOLEAN
      || _M_token == java::Token_BYTE
      || _M_token == java::Token_CHAR
      || _M_token == java::Token_SHORT
      || _M_token == java::Token_INT
      || _M_token == java::Token_FLOAT
      || _M_token == java::Token_LONG
      || _M_token == java::Token_DOUBLE
      || _M_token == java::Token_IDENTIFIER)
    {
      if (_M_token == java::Token_IDENTIFIER)
        {
          if (!is_class_type())
            {
              return false;
            }
        }

      else if (_M_token == java::Token_VOID
               || _M_token == java::Token_BOOLEAN
               || _M_token == java::Token_BYTE
               || _M_token == java::Token_CHAR
               || _M_token == java::Token_SHORT
               || _M_token == java::Token_INT
               || _M_token == java::Token_FLOAT
               || _M_token == java::Token_LONG
               || _M_token == java::Token_DOUBLE)
        {
          if (!is_optional_array_builtin_type())
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


bool java_lookahead::is_optional_array_builtin_type()
{
  if (_M_token == java::Token_VOID
      || _M_token == java::Token_BOOLEAN
      || _M_token == java::Token_BYTE
      || _M_token == java::Token_CHAR
      || _M_token == java::Token_SHORT
      || _M_token == java::Token_INT
      || _M_token == java::Token_FLOAT
      || _M_token == java::Token_LONG
      || _M_token == java::Token_DOUBLE)
    {
      if (!is_builtin_type())
        {
          return false;
        }

      if (!is_optional_declarator_brackets())
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


bool java_lookahead::is_builtin_type()
{
  if (_M_token == java::Token_VOID
      || _M_token == java::Token_BOOLEAN
      || _M_token == java::Token_BYTE
      || _M_token == java::Token_CHAR
      || _M_token == java::Token_SHORT
      || _M_token == java::Token_INT
      || _M_token == java::Token_FLOAT
      || _M_token == java::Token_LONG
      || _M_token == java::Token_DOUBLE)
    {
      fetch_next_token();
    }

  else
    {
      return false;
    }

  return true;
}


bool java_lookahead::is_optional_declarator_brackets()
{
  if (_M_token == java::Token_LBRACKET
      || _M_token == java::Token_SEMICOLON
      || _M_token == java::Token_LBRACE
      || _M_token == java::Token_RBRACE
      || _M_token == java::Token_COMMA
      || _M_token == java::Token_LPAREN
      || _M_token == java::Token_RPAREN
      || _M_token == java::Token_EXTENDS
      || _M_token == java::Token_IMPLEMENTS
      || _M_token == java::Token_THROWS
      || _M_token == java::Token_ELLIPSIS
      || _M_token == java::Token_BIT_AND
      || _M_token == java::Token_QUESTION
      || _M_token == java::Token_SUPER
      || _M_token == java::Token_GREATER_THAN
      || _M_token == java::Token_SIGNED_RSHIFT
      || _M_token == java::Token_UNSIGNED_RSHIFT
      || _M_token == java::Token_VOID
      || _M_token == java::Token_BOOLEAN
      || _M_token == java::Token_BYTE
      || _M_token == java::Token_CHAR
      || _M_token == java::Token_SHORT
      || _M_token == java::Token_INT
      || _M_token == java::Token_FLOAT
      || _M_token == java::Token_LONG
      || _M_token == java::Token_DOUBLE
      || _M_token == java::Token_DOT
      || _M_token == java::Token_STAR
      || _M_token == java::Token_LBRACKET
      || _M_token == java::Token_RBRACKET
      || _M_token == java::Token_ASSIGN
      || _M_token == java::Token_COLON
      || _M_token == java::Token_PLUS_ASSIGN
      || _M_token == java::Token_MINUS_ASSIGN
      || _M_token == java::Token_STAR_ASSIGN
      || _M_token == java::Token_SLASH_ASSIGN
      || _M_token == java::Token_BIT_AND_ASSIGN
      || _M_token == java::Token_BIT_OR_ASSIGN
      || _M_token == java::Token_BIT_XOR_ASSIGN
      || _M_token == java::Token_REMAINDER_ASSIGN
      || _M_token == java::Token_LSHIFT_ASSIGN
      || _M_token == java::Token_SIGNED_RSHIFT_ASSIGN
      || _M_token == java::Token_UNSIGNED_RSHIFT_ASSIGN
      || _M_token == java::Token_LOG_OR
      || _M_token == java::Token_LOG_AND
      || _M_token == java::Token_BIT_OR
      || _M_token == java::Token_BIT_XOR
      || _M_token == java::Token_EQUAL
      || _M_token == java::Token_NOT_EQUAL
      || _M_token == java::Token_INSTANCEOF
      || _M_token == java::Token_LESS_THAN
      || _M_token == java::Token_LESS_EQUAL
      || _M_token == java::Token_GREATER_EQUAL
      || _M_token == java::Token_LSHIFT
      || _M_token == java::Token_PLUS
      || _M_token == java::Token_MINUS
      || _M_token == java::Token_SLASH
      || _M_token == java::Token_REMAINDER
      || _M_token == java::Token_INCREMENT
      || _M_token == java::Token_DECREMENT
      || _M_token == java::Token_THIS
      || _M_token == java::Token_IDENTIFIER)
    {
      if (_M_token == java::Token_LBRACKET)
        {
          while (_M_token == java::Token_LBRACKET)
            {
              if (_M_token != java::Token_LBRACKET)
                return false;

              fetch_next_token();

              if (_M_token != java::Token_RBRACKET)
                return false;

              fetch_next_token();
            }
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


bool java_lookahead::is_class_type()
{
  if (_M_token == java::Token_IDENTIFIER)
    {
      if (!is_class_or_interface_type_name())
        {
          return false;
        }

      if (!is_optional_declarator_brackets())
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


bool java_lookahead::is_class_or_interface_type_name()
{
  if (_M_token == java::Token_IDENTIFIER)
    {
      if (!is_class_or_interface_type_name_part())
        {
          return false;
        }

      if (_M_token == java::Token_DOT)
        {
          while (_M_token == java::Token_DOT)
            {
              if (_M_token != java::Token_DOT)
                return false;

              fetch_next_token();

              if (!is_class_or_interface_type_name_part())
                {
                  return false;
                }
            }
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


bool java_lookahead::is_class_or_interface_type_name_part()
{
  if (_M_token == java::Token_IDENTIFIER)
    {
      if (!is_identifier())
        {
          return false;
        }

      if (_M_token == java::Token_LESS_THAN)
        {
          if (!is_type_arguments())
            {
              return false;
            }
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
