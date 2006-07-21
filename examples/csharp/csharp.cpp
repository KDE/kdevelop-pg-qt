// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "csharp.h"


#include "csharp_lookahead.h"
void print_token_environment(csharp::parser* parser);


namespace csharp
  {

  parser::csharp_compatibility_mode parser::compatibility_mode()
  {
    return _M_compatibility_mode;
  }
  void parser::set_compatibility_mode( parser::csharp_compatibility_mode mode )
  {
    _M_compatibility_mode = mode;
  }

  void parser::pp_define_symbol( std::string symbol_name )
  {
    _M_pp_defined_symbols.insert(symbol_name);
  }

  void parser::pp_undefine_symbol( std::string symbol_name )
  {
    _M_pp_defined_symbols.erase(symbol_name);
  }

  bool parser::pp_is_symbol_defined( std::string symbol_name )
  {
    return (_M_pp_defined_symbols.find(symbol_name) != _M_pp_defined_symbols.end());
  }


  // lookahead hacks to make up for backtracking or LL(k)
  // which are not yet implemented

  /**
   * This function checks if the next following tokens of the parser class
   * match the beginning of a local variable declaration (that is, a variable
   * declaration without attributes and modifiers). If true is returned then it
   * looks like a variable declaration is coming up. It doesn't have to match the
   * full local_variable_declaration rule (as only the first few tokens are
   * checked), but it is guaranteed that the upcoming tokens are not an
   * expression. The function returns false if the upcoming tokens are (for sure)
   * not the beginning of a local variable declaration.
   */
  bool parser::lookahead_is_local_variable_declaration()
  {
    csharp::lookahead* la = new csharp::lookahead(this);
    bool result = la->is_local_variable_declaration_start();
    delete la;
    return result;
  }

  /**
  * This function checks if the next following tokens of the parser class
  * match the beginning of a cast expression. If true is returned then it
  * looks like a cast expression is coming up. It doesn't have to match the
  * full cast_expression rule (because type arguments are only checked
  * rudimentarily, and expressions are not checked at all), but there's a very
  * high chance that the upcoming tokens are not a primary expression.
  * The function returns false if the upcoming tokens are (for sure) not
  * the beginning of a cast expression.
  */
  bool parser::lookahead_is_cast_expression()
  {
    csharp::lookahead* la = new csharp::lookahead(this);
    bool result = la->is_cast_expression_start();
    delete la;
    return result;
  }

  /**
  * This function checks if the next following tokens of the parser class
  * match the beginning of an unbound type name. If true is returned then it
  * looks like such a type name is coming up. It doesn't have to match the
  * full unbound_type_name rule, because it returns when it's clear that the
  * upcoming tokens are not a standard type_name.
  * The function returns false if the upcoming tokens are not
  * the beginning of an unbound type name.
  */
  bool parser::lookahead_is_unbound_type_name()
  {
    csharp::lookahead* la = new csharp::lookahead(this);
    bool result = la->is_unbound_type_name();
    delete la;
    return result;
  }

  bool parser::lookahead_is_type_arguments()
  {
    if (compatibility_mode() < csharp20_compatibility)
      return false;

    csharp::lookahead* la = new csharp::lookahead(this);
    bool result = la->is_type_arguments();
    delete la;
    return result;
  }

} // end of namespace csharp


namespace csharp
  {

  bool parser::parse_accessor_declarations(accessor_declarations_ast **yynode)
  {
    *yynode = create<accessor_declarations_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_INTERNAL
        || yytoken == Token_PRIVATE
        || yytoken == Token_PROTECTED
        || yytoken == Token_GET
        || yytoken == Token_SET
        || yytoken == Token_LBRACKET)
      {
        while (yytoken == Token_LBRACKET)
          {
            attribute_section_ast *__node_0 = 0;
            if (!parse_attribute_section(&__node_0))
              {
                return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
              }
            (*yynode)->accessor1_attribute_sequence = snoc((*yynode)->accessor1_attribute_sequence, __node_0, memory_pool);
          }
        if (yytoken == Token_INTERNAL
            || yytoken == Token_PRIVATE
            || yytoken == Token_PROTECTED)
          {
            accessor_modifier_ast *__node_1 = 0;
            if (!parse_accessor_modifier(&__node_1))
              {
                return yy_expected_symbol(ast_node::Kind_accessor_modifier, "accessor_modifier");
              }
            (*yynode)->accessor1_modifier = __node_1;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken == Token_GET)
          {
            if (yytoken != Token_GET)
              return yy_expected_token(yytoken, Token_GET, "get");
            yylex();
            if (yytoken == Token_LBRACE)
              {
                block_ast *__node_2 = 0;
                if (!parse_block(&__node_2))
                  {
                    return yy_expected_symbol(ast_node::Kind_block, "block");
                  }
                (*yynode)->accessor1_body = __node_2;
              }
            else if (yytoken == Token_SEMICOLON)
              {
                if (yytoken != Token_SEMICOLON)
                  return yy_expected_token(yytoken, Token_SEMICOLON, ";");
                yylex();
              }
            else
              {
                return false;
              }
            (*yynode)->accessor1_type = accessor_declarations::type_get;
            if (yytoken == Token_INTERNAL
                || yytoken == Token_PRIVATE
                || yytoken == Token_PROTECTED
                || yytoken == Token_SET
                || yytoken == Token_LBRACKET)
              {
                while (yytoken == Token_LBRACKET)
                  {
                    attribute_section_ast *__node_3 = 0;
                    if (!parse_attribute_section(&__node_3))
                      {
                        return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
                      }
                    (*yynode)->accessor2_attribute_sequence = snoc((*yynode)->accessor2_attribute_sequence, __node_3, memory_pool);
                  }
                if (yytoken == Token_INTERNAL
                    || yytoken == Token_PRIVATE
                    || yytoken == Token_PROTECTED)
                  {
                    accessor_modifier_ast *__node_4 = 0;
                    if (!parse_accessor_modifier(&__node_4))
                      {
                        return yy_expected_symbol(ast_node::Kind_accessor_modifier, "accessor_modifier");
                      }
                    (*yynode)->accessor2_modifier = __node_4;
                  }
                else if (true /*epsilon*/)
                {}
                else
                  {
                    return false;
                  }
                if (yytoken != Token_SET)
                  return yy_expected_token(yytoken, Token_SET, "set");
                yylex();
                if (yytoken == Token_LBRACE)
                  {
                    block_ast *__node_5 = 0;
                    if (!parse_block(&__node_5))
                      {
                        return yy_expected_symbol(ast_node::Kind_block, "block");
                      }
                    (*yynode)->accessor2_body = __node_5;
                  }
                else if (yytoken == Token_SEMICOLON)
                  {
                    if (yytoken != Token_SEMICOLON)
                      return yy_expected_token(yytoken, Token_SEMICOLON, ";");
                    yylex();
                  }
                else
                  {
                    return false;
                  }
                (*yynode)->accessor2_type = accessor_declarations::type_set;
              }
            else if (true /*epsilon*/)
              {
                (*yynode)->accessor2_type = accessor_declarations::type_none;
              }
            else
              {
                return false;
              }
          }
        else if (yytoken == Token_SET)
          {
            if (yytoken != Token_SET)
              return yy_expected_token(yytoken, Token_SET, "set");
            yylex();
            if (yytoken == Token_LBRACE)
              {
                block_ast *__node_6 = 0;
                if (!parse_block(&__node_6))
                  {
                    return yy_expected_symbol(ast_node::Kind_block, "block");
                  }
                (*yynode)->accessor1_body = __node_6;
              }
            else if (yytoken == Token_SEMICOLON)
              {
                if (yytoken != Token_SEMICOLON)
                  return yy_expected_token(yytoken, Token_SEMICOLON, ";");
                yylex();
              }
            else
              {
                return false;
              }
            (*yynode)->accessor1_type = accessor_declarations::type_set;
            if (yytoken == Token_INTERNAL
                || yytoken == Token_PRIVATE
                || yytoken == Token_PROTECTED
                || yytoken == Token_GET
                || yytoken == Token_LBRACKET)
              {
                while (yytoken == Token_LBRACKET)
                  {
                    attribute_section_ast *__node_7 = 0;
                    if (!parse_attribute_section(&__node_7))
                      {
                        return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
                      }
                    (*yynode)->accessor2_attribute_sequence = snoc((*yynode)->accessor2_attribute_sequence, __node_7, memory_pool);
                  }
                if (yytoken == Token_INTERNAL
                    || yytoken == Token_PRIVATE
                    || yytoken == Token_PROTECTED)
                  {
                    accessor_modifier_ast *__node_8 = 0;
                    if (!parse_accessor_modifier(&__node_8))
                      {
                        return yy_expected_symbol(ast_node::Kind_accessor_modifier, "accessor_modifier");
                      }
                    (*yynode)->accessor2_modifier = __node_8;
                  }
                else if (true /*epsilon*/)
                {}
                else
                  {
                    return false;
                  }
                if (yytoken != Token_GET)
                  return yy_expected_token(yytoken, Token_GET, "get");
                yylex();
                if (yytoken == Token_LBRACE)
                  {
                    block_ast *__node_9 = 0;
                    if (!parse_block(&__node_9))
                      {
                        return yy_expected_symbol(ast_node::Kind_block, "block");
                      }
                    (*yynode)->accessor2_body = __node_9;
                  }
                else if (yytoken == Token_SEMICOLON)
                  {
                    if (yytoken != Token_SEMICOLON)
                      return yy_expected_token(yytoken, Token_SEMICOLON, ";");
                    yylex();
                  }
                else
                  {
                    return false;
                  }
                (*yynode)->accessor2_type = accessor_declarations::type_get;
              }
            else if (true /*epsilon*/)
              {
                (*yynode)->accessor2_type = accessor_declarations::type_none;
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
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_accessor_modifier(accessor_modifier_ast **yynode)
  {
    *yynode = create<accessor_modifier_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_INTERNAL
        || yytoken == Token_PRIVATE
        || yytoken == Token_PROTECTED)
      {
        if (yytoken == Token_PROTECTED)
          {
            if (yytoken != Token_PROTECTED)
              return yy_expected_token(yytoken, Token_PROTECTED, "protected");
            yylex();
            (*yynode)->modifiers |= modifiers::mod_protected;
            if (yytoken == Token_INTERNAL)
              {
                if (yytoken != Token_INTERNAL)
                  return yy_expected_token(yytoken, Token_INTERNAL, "internal");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_internal;
              }
            else if (true /*epsilon*/)
            {}
            else
              {
                return false;
              }
          }
        else if (yytoken == Token_INTERNAL)
          {
            if (yytoken != Token_INTERNAL)
              return yy_expected_token(yytoken, Token_INTERNAL, "internal");
            yylex();
            (*yynode)->modifiers |= modifiers::mod_internal;
            if (yytoken == Token_PROTECTED)
              {
                if (yytoken != Token_PROTECTED)
                  return yy_expected_token(yytoken, Token_PROTECTED, "protected");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_protected;
              }
            else if (true /*epsilon*/)
            {}
            else
              {
                return false;
              }
          }
        else if (yytoken == Token_PRIVATE)
          {
            if (yytoken != Token_PRIVATE)
              return yy_expected_token(yytoken, Token_PRIVATE, "private");
            yylex();
            (*yynode)->modifiers |= modifiers::mod_private;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_additive_expression(additive_expression_ast **yynode)
  {
    *yynode = create<additive_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        multiplicative_expression_ast *__node_10 = 0;
        if (!parse_multiplicative_expression(&__node_10))
          {
            return yy_expected_symbol(ast_node::Kind_multiplicative_expression, "multiplicative_expression");
          }
        (*yynode)->expression = __node_10;
        while (yytoken == Token_PLUS
               || yytoken == Token_MINUS)
          {
            additive_expression_rest_ast *__node_11 = 0;
            if (!parse_additive_expression_rest(&__node_11))
              {
                return yy_expected_symbol(ast_node::Kind_additive_expression_rest, "additive_expression_rest");
              }
            (*yynode)->additional_expression_sequence = snoc((*yynode)->additional_expression_sequence, __node_11, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_additive_expression_rest(additive_expression_rest_ast **yynode)
  {
    *yynode = create<additive_expression_rest_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_PLUS
        || yytoken == Token_MINUS)
      {
        if (yytoken == Token_PLUS)
          {
            if (yytoken != Token_PLUS)
              return yy_expected_token(yytoken, Token_PLUS, "+");
            yylex();
            (*yynode)->additive_operator = additive_expression_rest::op_plus;
          }
        else if (yytoken == Token_MINUS)
          {
            if (yytoken != Token_MINUS)
              return yy_expected_token(yytoken, Token_MINUS, "-");
            yylex();
            (*yynode)->additive_operator = additive_expression_rest::op_minus;
          }
        else
          {
            return false;
          }
        multiplicative_expression_ast *__node_12 = 0;
        if (!parse_multiplicative_expression(&__node_12))
          {
            return yy_expected_symbol(ast_node::Kind_multiplicative_expression, "multiplicative_expression");
          }
        (*yynode)->expression = __node_12;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_anonymous_method_expression(anonymous_method_expression_ast **yynode)
  {
    *yynode = create<anonymous_method_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_DELEGATE)
      {
        if (yytoken != Token_DELEGATE)
          return yy_expected_token(yytoken, Token_DELEGATE, "delegate");
        yylex();
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        anonymous_method_parameter_ast *__node_13 = 0;
        if (!parse_anonymous_method_parameter(&__node_13))
          {
            return yy_expected_symbol(ast_node::Kind_anonymous_method_parameter, "anonymous_method_parameter");
          }
        (*yynode)->anonymous_method_parameter_sequence = snoc((*yynode)->anonymous_method_parameter_sequence, __node_13, memory_pool);
        while (yytoken == Token_COMMA)
          {
            if (yytoken != Token_COMMA)
              return yy_expected_token(yytoken, Token_COMMA, ",");
            yylex();
            anonymous_method_parameter_ast *__node_14 = 0;
            if (!parse_anonymous_method_parameter(&__node_14))
              {
                return yy_expected_symbol(ast_node::Kind_anonymous_method_parameter, "anonymous_method_parameter");
              }
            (*yynode)->anonymous_method_parameter_sequence = snoc((*yynode)->anonymous_method_parameter_sequence, __node_14, memory_pool);
          }
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        block_ast *__node_15 = 0;
        if (!parse_block(&__node_15))
          {
            return yy_expected_symbol(ast_node::Kind_block, "block");
          }
        (*yynode)->body = __node_15;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_anonymous_method_parameter(anonymous_method_parameter_ast **yynode)
  {
    *yynode = create<anonymous_method_parameter_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_DECIMAL
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_OBJECT
        || yytoken == Token_OUT
        || yytoken == Token_REF
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_STRING
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT
        || yytoken == Token_VOID
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        if (yytoken == Token_OUT
            || yytoken == Token_REF)
          {
            parameter_modifier_ast *__node_16 = 0;
            if (!parse_parameter_modifier(&__node_16))
              {
                return yy_expected_symbol(ast_node::Kind_parameter_modifier, "parameter_modifier");
              }
            (*yynode)->modifier = __node_16;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        type_ast *__node_17 = 0;
        if (!parse_type(&__node_17))
          {
            return yy_expected_symbol(ast_node::Kind_type, "type");
          }
        (*yynode)->type = __node_17;
        identifier_ast *__node_18 = 0;
        if (!parse_identifier(&__node_18))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->variable_name = __node_18;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_argument(argument_ast **yynode)
  {
    *yynode = create<argument_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_OUT
        || yytoken == Token_REF
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        if (yytoken == Token_BASE
            || yytoken == Token_BOOL
            || yytoken == Token_BYTE
            || yytoken == Token_CHAR
            || yytoken == Token_CHECKED
            || yytoken == Token_DECIMAL
            || yytoken == Token_DEFAULT
            || yytoken == Token_DELEGATE
            || yytoken == Token_DOUBLE
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_NEW
            || yytoken == Token_OBJECT
            || yytoken == Token_SBYTE
            || yytoken == Token_SHORT
            || yytoken == Token_SIZEOF
            || yytoken == Token_STRING
            || yytoken == Token_THIS
            || yytoken == Token_TYPEOF
            || yytoken == Token_UINT
            || yytoken == Token_ULONG
            || yytoken == Token_UNCHECKED
            || yytoken == Token_USHORT
            || yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_LPAREN
            || yytoken == Token_BANG
            || yytoken == Token_TILDE
            || yytoken == Token_INCREMENT
            || yytoken == Token_DECREMENT
            || yytoken == Token_PLUS
            || yytoken == Token_MINUS
            || yytoken == Token_STAR
            || yytoken == Token_BIT_AND
            || yytoken == Token_TRUE
            || yytoken == Token_FALSE
            || yytoken == Token_NULL
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_REAL_LITERAL
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_IDENTIFIER)
          {
            expression_ast *__node_19 = 0;
            if (!parse_expression(&__node_19))
              {
                return yy_expected_symbol(ast_node::Kind_expression, "expression");
              }
            (*yynode)->expression = __node_19;
            (*yynode)->argument_type = argument::type_value_parameter;
          }
        else if (yytoken == Token_REF)
          {
            if (yytoken != Token_REF)
              return yy_expected_token(yytoken, Token_REF, "ref");
            yylex();
            expression_ast *__node_20 = 0;
            if (!parse_expression(&__node_20))
              {
                return yy_expected_symbol(ast_node::Kind_expression, "expression");
              }
            (*yynode)->expression = __node_20;
            (*yynode)->argument_type = argument::type_reference_parameter;
          }
        else if (yytoken == Token_OUT)
          {
            if (yytoken != Token_OUT)
              return yy_expected_token(yytoken, Token_OUT, "out");
            yylex();
            expression_ast *__node_21 = 0;
            if (!parse_expression(&__node_21))
              {
                return yy_expected_symbol(ast_node::Kind_expression, "expression");
              }
            (*yynode)->expression = __node_21;
            (*yynode)->argument_type = argument::type_output_parameter;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_array_creation_expression_rest(array_creation_expression_rest_ast **yynode)
  {
    *yynode = create<array_creation_expression_rest_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LBRACE
        || yytoken == Token_LBRACKET)
      {
        if (yytoken == Token_LBRACE)
          {
            array_initializer_ast *__node_22 = 0;
            if (!parse_array_initializer(&__node_22))
              {
                return yy_expected_symbol(ast_node::Kind_array_initializer, "array_initializer");
              }
            (*yynode)->array_initializer = __node_22;
          }
        else if (yytoken == Token_LBRACKET)
          {
            if (yytoken != Token_LBRACKET)
              return yy_expected_token(yytoken, Token_LBRACKET, "[");
            yylex();
            expression_ast *__node_23 = 0;
            if (!parse_expression(&__node_23))
              {
                return yy_expected_symbol(ast_node::Kind_expression, "expression");
              }
            (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_23, memory_pool);
            while (yytoken == Token_COMMA)
              {
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
                expression_ast *__node_24 = 0;
                if (!parse_expression(&__node_24))
                  {
                    return yy_expected_symbol(ast_node::Kind_expression, "expression");
                  }
                (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_24, memory_pool);
              }
            if (yytoken != Token_RBRACKET)
              return yy_expected_token(yytoken, Token_RBRACKET, "]");
            yylex();
            while (yytoken == Token_LBRACKET)
              {
                if (LA(2).kind != Token_COMMA || LA(2).kind != Token_RBRACKET)
                  {
                    break;
                  }
                rank_specifier_ast *__node_25 = 0;
                if (!parse_rank_specifier(&__node_25))
                  {
                    return yy_expected_symbol(ast_node::Kind_rank_specifier, "rank_specifier");
                  }
                (*yynode)->rank_specifier_sequence = snoc((*yynode)->rank_specifier_sequence, __node_25, memory_pool);
              }
            if (yytoken == Token_LBRACE)
              {
                array_initializer_ast *__node_26 = 0;
                if (!parse_array_initializer(&__node_26))
                  {
                    return yy_expected_symbol(ast_node::Kind_array_initializer, "array_initializer");
                  }
                (*yynode)->array_initializer = __node_26;
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
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_array_initializer(array_initializer_ast **yynode)
  {
    *yynode = create<array_initializer_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LBRACE)
      {
        if (yytoken != Token_LBRACE)
          return yy_expected_token(yytoken, Token_LBRACE, "{");
        yylex();
        if (yytoken == Token_BASE
            || yytoken == Token_BOOL
            || yytoken == Token_BYTE
            || yytoken == Token_CHAR
            || yytoken == Token_CHECKED
            || yytoken == Token_DECIMAL
            || yytoken == Token_DEFAULT
            || yytoken == Token_DELEGATE
            || yytoken == Token_DOUBLE
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_NEW
            || yytoken == Token_OBJECT
            || yytoken == Token_SBYTE
            || yytoken == Token_SHORT
            || yytoken == Token_SIZEOF
            || yytoken == Token_STACKALLOC
            || yytoken == Token_STRING
            || yytoken == Token_THIS
            || yytoken == Token_TYPEOF
            || yytoken == Token_UINT
            || yytoken == Token_ULONG
            || yytoken == Token_UNCHECKED
            || yytoken == Token_USHORT
            || yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_LPAREN
            || yytoken == Token_LBRACE
            || yytoken == Token_BANG
            || yytoken == Token_TILDE
            || yytoken == Token_INCREMENT
            || yytoken == Token_DECREMENT
            || yytoken == Token_PLUS
            || yytoken == Token_MINUS
            || yytoken == Token_STAR
            || yytoken == Token_BIT_AND
            || yytoken == Token_TRUE
            || yytoken == Token_FALSE
            || yytoken == Token_NULL
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_REAL_LITERAL
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_IDENTIFIER)
          {
            variable_initializer_ast *__node_27 = 0;
            if (!parse_variable_initializer(&__node_27))
              {
                return yy_expected_symbol(ast_node::Kind_variable_initializer, "variable_initializer");
              }
            (*yynode)->variable_initializer_sequence = snoc((*yynode)->variable_initializer_sequence, __node_27, memory_pool);
            while (yytoken == Token_COMMA)
              {
                if (LA(2).kind == Token_RBRACE)
                  {
                    break;
                  }
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
                variable_initializer_ast *__node_28 = 0;
                if (!parse_variable_initializer(&__node_28))
                  {
                    return yy_expected_symbol(ast_node::Kind_variable_initializer, "variable_initializer");
                  }
                (*yynode)->variable_initializer_sequence = snoc((*yynode)->variable_initializer_sequence, __node_28, memory_pool);
              }
            if (yytoken == Token_COMMA)
              {
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
              }
            else if (true /*epsilon*/)
            {}
            else
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
        if (yytoken != Token_RBRACE)
          return yy_expected_token(yytoken, Token_RBRACE, "}");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_array_type(array_type_ast **yynode)
  {
    *yynode = create<array_type_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_DECIMAL
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_STRING
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        non_array_type_ast *__node_29 = 0;
        if (!parse_non_array_type(&__node_29))
          {
            return yy_expected_symbol(ast_node::Kind_non_array_type, "non_array_type");
          }
        (*yynode)->non_array_type = __node_29;
        do
          {
            rank_specifier_ast *__node_30 = 0;
            if (!parse_rank_specifier(&__node_30))
              {
                return yy_expected_symbol(ast_node::Kind_rank_specifier, "rank_specifier");
              }
            (*yynode)->rank_specifier_sequence = snoc((*yynode)->rank_specifier_sequence, __node_30, memory_pool);
          }
        while (yytoken == Token_LBRACKET);
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_attribute(attribute_ast **yynode)
  {
    *yynode = create<attribute_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        type_name_ast *__node_31 = 0;
        if (!parse_type_name(&__node_31))
          {
            return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
          }
        (*yynode)->name = __node_31;
        if (yytoken == Token_LPAREN)
          {
            attribute_arguments_ast *__node_32 = 0;
            if (!parse_attribute_arguments(&__node_32))
              {
                return yy_expected_symbol(ast_node::Kind_attribute_arguments, "attribute_arguments");
              }
            (*yynode)->arguments = __node_32;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_attribute_arguments(attribute_arguments_ast **yynode)
  {
    *yynode = create<attribute_arguments_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LPAREN)
      {
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        if (yytoken == Token_RPAREN)
          {
            if (yytoken != Token_RPAREN)
              return yy_expected_token(yytoken, Token_RPAREN, ")");
            yylex();
          }
        else if ((yytoken == Token_ADD
                  || yytoken == Token_ALIAS
                  || yytoken == Token_GET
                  || yytoken == Token_GLOBAL
                  || yytoken == Token_PARTIAL
                  || yytoken == Token_REMOVE
                  || yytoken == Token_SET
                  || yytoken == Token_VALUE
                  || yytoken == Token_WHERE
                  || yytoken == Token_YIELD
                  || yytoken == Token_ASSEMBLY
                  || yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_ASSIGN ))
          {
            named_argument_ast *__node_33 = 0;
            if (!parse_named_argument(&__node_33))
              {
                return yy_expected_symbol(ast_node::Kind_named_argument, "named_argument");
              }
            (*yynode)->named_argument_sequence = snoc((*yynode)->named_argument_sequence, __node_33, memory_pool);
            while (yytoken == Token_COMMA)
              {
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
                named_argument_ast *__node_34 = 0;
                if (!parse_named_argument(&__node_34))
                  {
                    return yy_expected_symbol(ast_node::Kind_named_argument, "named_argument");
                  }
                (*yynode)->named_argument_sequence = snoc((*yynode)->named_argument_sequence, __node_34, memory_pool);
              }
            if (yytoken != Token_RPAREN)
              return yy_expected_token(yytoken, Token_RPAREN, ")");
            yylex();
          }
        else if (yytoken == Token_BASE
                 || yytoken == Token_BOOL
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR
                 || yytoken == Token_CHECKED
                 || yytoken == Token_DECIMAL
                 || yytoken == Token_DEFAULT
                 || yytoken == Token_DELEGATE
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_LONG
                 || yytoken == Token_NEW
                 || yytoken == Token_OBJECT
                 || yytoken == Token_SBYTE
                 || yytoken == Token_SHORT
                 || yytoken == Token_SIZEOF
                 || yytoken == Token_STRING
                 || yytoken == Token_THIS
                 || yytoken == Token_TYPEOF
                 || yytoken == Token_UINT
                 || yytoken == Token_ULONG
                 || yytoken == Token_UNCHECKED
                 || yytoken == Token_USHORT
                 || yytoken == Token_ADD
                 || yytoken == Token_ALIAS
                 || yytoken == Token_GET
                 || yytoken == Token_GLOBAL
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_REMOVE
                 || yytoken == Token_SET
                 || yytoken == Token_VALUE
                 || yytoken == Token_WHERE
                 || yytoken == Token_YIELD
                 || yytoken == Token_ASSEMBLY
                 || yytoken == Token_LPAREN
                 || yytoken == Token_BANG
                 || yytoken == Token_TILDE
                 || yytoken == Token_INCREMENT
                 || yytoken == Token_DECREMENT
                 || yytoken == Token_PLUS
                 || yytoken == Token_MINUS
                 || yytoken == Token_STAR
                 || yytoken == Token_BIT_AND
                 || yytoken == Token_TRUE
                 || yytoken == Token_FALSE
                 || yytoken == Token_NULL
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_REAL_LITERAL
                 || yytoken == Token_CHARACTER_LITERAL
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_IDENTIFIER)
          {
            positional_argument_ast *__node_35 = 0;
            if (!parse_positional_argument(&__node_35))
              {
                return yy_expected_symbol(ast_node::Kind_positional_argument, "positional_argument");
              }
            (*yynode)->positional_argument_sequence = snoc((*yynode)->positional_argument_sequence, __node_35, memory_pool);
            while (yytoken == Token_COMMA)
              {
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
                if ((yytoken == Token_ADD
                     || yytoken == Token_ALIAS
                     || yytoken == Token_GET
                     || yytoken == Token_GLOBAL
                     || yytoken == Token_PARTIAL
                     || yytoken == Token_REMOVE
                     || yytoken == Token_SET
                     || yytoken == Token_VALUE
                     || yytoken == Token_WHERE
                     || yytoken == Token_YIELD
                     || yytoken == Token_ASSEMBLY
                     || yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_ASSIGN ))
                  {
                    named_argument_ast *__node_36 = 0;
                    if (!parse_named_argument(&__node_36))
                      {
                        return yy_expected_symbol(ast_node::Kind_named_argument, "named_argument");
                      }
                    (*yynode)->named_argument_sequence = snoc((*yynode)->named_argument_sequence, __node_36, memory_pool);
                    while (yytoken == Token_COMMA)
                      {
                        if (yytoken != Token_COMMA)
                          return yy_expected_token(yytoken, Token_COMMA, ",");
                        yylex();
                        named_argument_ast *__node_37 = 0;
                        if (!parse_named_argument(&__node_37))
                          {
                            return yy_expected_symbol(ast_node::Kind_named_argument, "named_argument");
                          }
                        (*yynode)->named_argument_sequence = snoc((*yynode)->named_argument_sequence, __node_37, memory_pool);
                      }
                    break;
                  }
                else if (yytoken == Token_BASE
                         || yytoken == Token_BOOL
                         || yytoken == Token_BYTE
                         || yytoken == Token_CHAR
                         || yytoken == Token_CHECKED
                         || yytoken == Token_DECIMAL
                         || yytoken == Token_DEFAULT
                         || yytoken == Token_DELEGATE
                         || yytoken == Token_DOUBLE
                         || yytoken == Token_FLOAT
                         || yytoken == Token_INT
                         || yytoken == Token_LONG
                         || yytoken == Token_NEW
                         || yytoken == Token_OBJECT
                         || yytoken == Token_SBYTE
                         || yytoken == Token_SHORT
                         || yytoken == Token_SIZEOF
                         || yytoken == Token_STRING
                         || yytoken == Token_THIS
                         || yytoken == Token_TYPEOF
                         || yytoken == Token_UINT
                         || yytoken == Token_ULONG
                         || yytoken == Token_UNCHECKED
                         || yytoken == Token_USHORT
                         || yytoken == Token_ADD
                         || yytoken == Token_ALIAS
                         || yytoken == Token_GET
                         || yytoken == Token_GLOBAL
                         || yytoken == Token_PARTIAL
                         || yytoken == Token_REMOVE
                         || yytoken == Token_SET
                         || yytoken == Token_VALUE
                         || yytoken == Token_WHERE
                         || yytoken == Token_YIELD
                         || yytoken == Token_ASSEMBLY
                         || yytoken == Token_LPAREN
                         || yytoken == Token_BANG
                         || yytoken == Token_TILDE
                         || yytoken == Token_INCREMENT
                         || yytoken == Token_DECREMENT
                         || yytoken == Token_PLUS
                         || yytoken == Token_MINUS
                         || yytoken == Token_STAR
                         || yytoken == Token_BIT_AND
                         || yytoken == Token_TRUE
                         || yytoken == Token_FALSE
                         || yytoken == Token_NULL
                         || yytoken == Token_INTEGER_LITERAL
                         || yytoken == Token_REAL_LITERAL
                         || yytoken == Token_CHARACTER_LITERAL
                         || yytoken == Token_STRING_LITERAL
                         || yytoken == Token_IDENTIFIER)
                  {
                    positional_argument_ast *__node_38 = 0;
                    if (!parse_positional_argument(&__node_38))
                      {
                        return yy_expected_symbol(ast_node::Kind_positional_argument, "positional_argument");
                      }
                    (*yynode)->positional_argument_sequence = snoc((*yynode)->positional_argument_sequence, __node_38, memory_pool);
                  }
                else
                  {
                    return false;
                  }
              }
            if (yytoken != Token_RPAREN)
              return yy_expected_token(yytoken, Token_RPAREN, ")");
            yylex();
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_attribute_section(attribute_section_ast **yynode)
  {
    *yynode = create<attribute_section_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LBRACKET)
      {
        if (yytoken != Token_LBRACKET)
          return yy_expected_token(yytoken, Token_LBRACKET, "[");
        yylex();
        if ((yytoken == Token_ABSTRACT
             || yytoken == Token_AS
             || yytoken == Token_BASE
             || yytoken == Token_BOOL
             || yytoken == Token_BREAK
             || yytoken == Token_BYTE
             || yytoken == Token_CASE
             || yytoken == Token_CATCH
             || yytoken == Token_CHAR
             || yytoken == Token_CHECKED
             || yytoken == Token_CLASS
             || yytoken == Token_CONST
             || yytoken == Token_CONTINUE
             || yytoken == Token_DECIMAL
             || yytoken == Token_DEFAULT
             || yytoken == Token_DELEGATE
             || yytoken == Token_DO
             || yytoken == Token_DOUBLE
             || yytoken == Token_ELSE
             || yytoken == Token_ENUM
             || yytoken == Token_EVENT
             || yytoken == Token_EXPLICIT
             || yytoken == Token_EXTERN
             || yytoken == Token_FINALLY
             || yytoken == Token_FIXED
             || yytoken == Token_FLOAT
             || yytoken == Token_FOREACH
             || yytoken == Token_FOR
             || yytoken == Token_GOTO
             || yytoken == Token_IF
             || yytoken == Token_IMPLICIT
             || yytoken == Token_IN
             || yytoken == Token_INT
             || yytoken == Token_INTERFACE
             || yytoken == Token_INTERNAL
             || yytoken == Token_IS
             || yytoken == Token_LOCK
             || yytoken == Token_LONG
             || yytoken == Token_NAMESPACE
             || yytoken == Token_NEW
             || yytoken == Token_OBJECT
             || yytoken == Token_OPERATOR
             || yytoken == Token_OUT
             || yytoken == Token_OVERRIDE
             || yytoken == Token_PARAMS
             || yytoken == Token_PRIVATE
             || yytoken == Token_PROTECTED
             || yytoken == Token_PUBLIC
             || yytoken == Token_READONLY
             || yytoken == Token_REF
             || yytoken == Token_RETURN
             || yytoken == Token_SBYTE
             || yytoken == Token_SEALED
             || yytoken == Token_SHORT
             || yytoken == Token_SIZEOF
             || yytoken == Token_STACKALLOC
             || yytoken == Token_STATIC
             || yytoken == Token_STRING
             || yytoken == Token_STRUCT
             || yytoken == Token_SWITCH
             || yytoken == Token_THIS
             || yytoken == Token_THROW
             || yytoken == Token_TRY
             || yytoken == Token_TYPEOF
             || yytoken == Token_UINT
             || yytoken == Token_ULONG
             || yytoken == Token_UNCHECKED
             || yytoken == Token_UNSAFE
             || yytoken == Token_USHORT
             || yytoken == Token_USING
             || yytoken == Token_VIRTUAL
             || yytoken == Token_VOID
             || yytoken == Token_VOLATILE
             || yytoken == Token_WHILE
             || yytoken == Token_ADD
             || yytoken == Token_ALIAS
             || yytoken == Token_GET
             || yytoken == Token_GLOBAL
             || yytoken == Token_PARTIAL
             || yytoken == Token_REMOVE
             || yytoken == Token_SET
             || yytoken == Token_VALUE
             || yytoken == Token_WHERE
             || yytoken == Token_YIELD
             || yytoken == Token_ASSEMBLY
             || yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_COLON ))
          {
            attribute_target_ast *__node_39 = 0;
            if (!parse_attribute_target(&__node_39))
              {
                return yy_expected_symbol(ast_node::Kind_attribute_target, "attribute_target");
              }
            (*yynode)->target = __node_39;
            if (yytoken != Token_COLON)
              return yy_expected_token(yytoken, Token_COLON, ":");
            yylex();
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        attribute_ast *__node_40 = 0;
        if (!parse_attribute(&__node_40))
          {
            return yy_expected_symbol(ast_node::Kind_attribute, "attribute");
          }
        (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_40, memory_pool);
        while (yytoken == Token_COMMA)
          {
            if (LA(2).kind == Token_RBRACKET)
              {
                break;
              }
            if (yytoken != Token_COMMA)
              return yy_expected_token(yytoken, Token_COMMA, ",");
            yylex();
            attribute_ast *__node_41 = 0;
            if (!parse_attribute(&__node_41))
              {
                return yy_expected_symbol(ast_node::Kind_attribute, "attribute");
              }
            (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_41, memory_pool);
          }
        if (yytoken == Token_COMMA)
          {
            if (yytoken != Token_COMMA)
              return yy_expected_token(yytoken, Token_COMMA, ",");
            yylex();
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken != Token_RBRACKET)
          return yy_expected_token(yytoken, Token_RBRACKET, "]");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_attribute_target(attribute_target_ast **yynode)
  {
    *yynode = create<attribute_target_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ABSTRACT
        || yytoken == Token_AS
        || yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BREAK
        || yytoken == Token_BYTE
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_CLASS
        || yytoken == Token_CONST
        || yytoken == Token_CONTINUE
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DO
        || yytoken == Token_DOUBLE
        || yytoken == Token_ELSE
        || yytoken == Token_ENUM
        || yytoken == Token_EVENT
        || yytoken == Token_EXPLICIT
        || yytoken == Token_EXTERN
        || yytoken == Token_FINALLY
        || yytoken == Token_FIXED
        || yytoken == Token_FLOAT
        || yytoken == Token_FOREACH
        || yytoken == Token_FOR
        || yytoken == Token_GOTO
        || yytoken == Token_IF
        || yytoken == Token_IMPLICIT
        || yytoken == Token_IN
        || yytoken == Token_INT
        || yytoken == Token_INTERFACE
        || yytoken == Token_INTERNAL
        || yytoken == Token_IS
        || yytoken == Token_LOCK
        || yytoken == Token_LONG
        || yytoken == Token_NAMESPACE
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_OPERATOR
        || yytoken == Token_OUT
        || yytoken == Token_OVERRIDE
        || yytoken == Token_PARAMS
        || yytoken == Token_PRIVATE
        || yytoken == Token_PROTECTED
        || yytoken == Token_PUBLIC
        || yytoken == Token_READONLY
        || yytoken == Token_REF
        || yytoken == Token_RETURN
        || yytoken == Token_SBYTE
        || yytoken == Token_SEALED
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STACKALLOC
        || yytoken == Token_STATIC
        || yytoken == Token_STRING
        || yytoken == Token_STRUCT
        || yytoken == Token_SWITCH
        || yytoken == Token_THIS
        || yytoken == Token_THROW
        || yytoken == Token_TRY
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_UNSAFE
        || yytoken == Token_USHORT
        || yytoken == Token_USING
        || yytoken == Token_VIRTUAL
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE
        || yytoken == Token_WHILE
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        if (yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_IDENTIFIER)
          {
            identifier_ast *__node_42 = 0;
            if (!parse_identifier(&__node_42))
              {
                return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
              }
            (*yynode)->identifier = __node_42;
          }
        else if (yytoken == Token_ABSTRACT
                 || yytoken == Token_AS
                 || yytoken == Token_BASE
                 || yytoken == Token_BOOL
                 || yytoken == Token_BREAK
                 || yytoken == Token_BYTE
                 || yytoken == Token_CASE
                 || yytoken == Token_CATCH
                 || yytoken == Token_CHAR
                 || yytoken == Token_CHECKED
                 || yytoken == Token_CLASS
                 || yytoken == Token_CONST
                 || yytoken == Token_CONTINUE
                 || yytoken == Token_DECIMAL
                 || yytoken == Token_DEFAULT
                 || yytoken == Token_DELEGATE
                 || yytoken == Token_DO
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_ELSE
                 || yytoken == Token_ENUM
                 || yytoken == Token_EVENT
                 || yytoken == Token_EXPLICIT
                 || yytoken == Token_EXTERN
                 || yytoken == Token_FINALLY
                 || yytoken == Token_FIXED
                 || yytoken == Token_FLOAT
                 || yytoken == Token_FOREACH
                 || yytoken == Token_FOR
                 || yytoken == Token_GOTO
                 || yytoken == Token_IF
                 || yytoken == Token_IMPLICIT
                 || yytoken == Token_IN
                 || yytoken == Token_INT
                 || yytoken == Token_INTERFACE
                 || yytoken == Token_INTERNAL
                 || yytoken == Token_IS
                 || yytoken == Token_LOCK
                 || yytoken == Token_LONG
                 || yytoken == Token_NAMESPACE
                 || yytoken == Token_NEW
                 || yytoken == Token_OBJECT
                 || yytoken == Token_OPERATOR
                 || yytoken == Token_OUT
                 || yytoken == Token_OVERRIDE
                 || yytoken == Token_PARAMS
                 || yytoken == Token_PRIVATE
                 || yytoken == Token_PROTECTED
                 || yytoken == Token_PUBLIC
                 || yytoken == Token_READONLY
                 || yytoken == Token_REF
                 || yytoken == Token_RETURN
                 || yytoken == Token_SBYTE
                 || yytoken == Token_SEALED
                 || yytoken == Token_SHORT
                 || yytoken == Token_SIZEOF
                 || yytoken == Token_STACKALLOC
                 || yytoken == Token_STATIC
                 || yytoken == Token_STRING
                 || yytoken == Token_STRUCT
                 || yytoken == Token_SWITCH
                 || yytoken == Token_THIS
                 || yytoken == Token_THROW
                 || yytoken == Token_TRY
                 || yytoken == Token_TYPEOF
                 || yytoken == Token_UINT
                 || yytoken == Token_ULONG
                 || yytoken == Token_UNCHECKED
                 || yytoken == Token_UNSAFE
                 || yytoken == Token_USHORT
                 || yytoken == Token_USING
                 || yytoken == Token_VIRTUAL
                 || yytoken == Token_VOID
                 || yytoken == Token_VOLATILE
                 || yytoken == Token_WHILE)
          {
            keyword_ast *__node_43 = 0;
            if (!parse_keyword(&__node_43))
              {
                return yy_expected_symbol(ast_node::Kind_keyword, "keyword");
              }
            (*yynode)->keyword = __node_43;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_base_access(base_access_ast **yynode)
  {
    *yynode = create<base_access_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE)
      {
        if (yytoken != Token_BASE)
          return yy_expected_token(yytoken, Token_BASE, "base");
        yylex();
        if (yytoken == Token_DOT)
          {
            if (yytoken != Token_DOT)
              return yy_expected_token(yytoken, Token_DOT, ".");
            yylex();
            identifier_ast *__node_44 = 0;
            if (!parse_identifier(&__node_44))
              {
                return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
              }
            (*yynode)->identifier = __node_44;
            if ((yytoken == Token_LESS_THAN) && ( lookahead_is_type_arguments() == true ))
              {
                type_arguments_ast *__node_45 = 0;
                if (!parse_type_arguments(&__node_45))
                  {
                    return yy_expected_symbol(ast_node::Kind_type_arguments, "type_arguments");
                  }
                (*yynode)->type_arguments = __node_45;
              }
            else if (true /*epsilon*/)
            {}
            else
              {
                return false;
              }
            (*yynode)->access_type = base_access::type_base_member_access;
          }
        else if (yytoken == Token_LBRACKET)
          {
            if (yytoken != Token_LBRACKET)
              return yy_expected_token(yytoken, Token_LBRACKET, "[");
            yylex();
            expression_ast *__node_46 = 0;
            if (!parse_expression(&__node_46))
              {
                return yy_expected_symbol(ast_node::Kind_expression, "expression");
              }
            (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_46, memory_pool);
            while (yytoken == Token_COMMA)
              {
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
                expression_ast *__node_47 = 0;
                if (!parse_expression(&__node_47))
                  {
                    return yy_expected_symbol(ast_node::Kind_expression, "expression");
                  }
                (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_47, memory_pool);
              }
            if (yytoken != Token_RBRACKET)
              return yy_expected_token(yytoken, Token_RBRACKET, "]");
            yylex();
            (*yynode)->access_type = base_access::type_base_indexer_access;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_bit_and_expression(bit_and_expression_ast **yynode)
  {
    *yynode = create<bit_and_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        equality_expression_ast *__node_48 = 0;
        if (!parse_equality_expression(&__node_48))
          {
            return yy_expected_symbol(ast_node::Kind_equality_expression, "equality_expression");
          }
        (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_48, memory_pool);
        while (yytoken == Token_BIT_AND)
          {
            if (yytoken != Token_BIT_AND)
              return yy_expected_token(yytoken, Token_BIT_AND, "&");
            yylex();
            equality_expression_ast *__node_49 = 0;
            if (!parse_equality_expression(&__node_49))
              {
                return yy_expected_symbol(ast_node::Kind_equality_expression, "equality_expression");
              }
            (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_49, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_bit_or_expression(bit_or_expression_ast **yynode)
  {
    *yynode = create<bit_or_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        bit_xor_expression_ast *__node_50 = 0;
        if (!parse_bit_xor_expression(&__node_50))
          {
            return yy_expected_symbol(ast_node::Kind_bit_xor_expression, "bit_xor_expression");
          }
        (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_50, memory_pool);
        while (yytoken == Token_BIT_OR)
          {
            if (yytoken != Token_BIT_OR)
              return yy_expected_token(yytoken, Token_BIT_OR, "|");
            yylex();
            bit_xor_expression_ast *__node_51 = 0;
            if (!parse_bit_xor_expression(&__node_51))
              {
                return yy_expected_symbol(ast_node::Kind_bit_xor_expression, "bit_xor_expression");
              }
            (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_51, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_bit_xor_expression(bit_xor_expression_ast **yynode)
  {
    *yynode = create<bit_xor_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        bit_and_expression_ast *__node_52 = 0;
        if (!parse_bit_and_expression(&__node_52))
          {
            return yy_expected_symbol(ast_node::Kind_bit_and_expression, "bit_and_expression");
          }
        (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_52, memory_pool);
        while (yytoken == Token_BIT_XOR)
          {
            if (yytoken != Token_BIT_XOR)
              return yy_expected_token(yytoken, Token_BIT_XOR, "^");
            yylex();
            bit_and_expression_ast *__node_53 = 0;
            if (!parse_bit_and_expression(&__node_53))
              {
                return yy_expected_symbol(ast_node::Kind_bit_and_expression, "bit_and_expression");
              }
            (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_53, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_block(block_ast **yynode)
  {
    *yynode = create<block_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LBRACE)
      {
        if (yytoken != Token_LBRACE)
          return yy_expected_token(yytoken, Token_LBRACE, "{");
        yylex();
        while (yytoken == Token_BASE
               || yytoken == Token_BOOL
               || yytoken == Token_BREAK
               || yytoken == Token_BYTE
               || yytoken == Token_CHAR
               || yytoken == Token_CHECKED
               || yytoken == Token_CONST
               || yytoken == Token_CONTINUE
               || yytoken == Token_DECIMAL
               || yytoken == Token_DEFAULT
               || yytoken == Token_DELEGATE
               || yytoken == Token_DO
               || yytoken == Token_DOUBLE
               || yytoken == Token_FIXED
               || yytoken == Token_FLOAT
               || yytoken == Token_FOREACH
               || yytoken == Token_FOR
               || yytoken == Token_GOTO
               || yytoken == Token_IF
               || yytoken == Token_INT
               || yytoken == Token_LOCK
               || yytoken == Token_LONG
               || yytoken == Token_NEW
               || yytoken == Token_OBJECT
               || yytoken == Token_RETURN
               || yytoken == Token_SBYTE
               || yytoken == Token_SHORT
               || yytoken == Token_SIZEOF
               || yytoken == Token_STRING
               || yytoken == Token_SWITCH
               || yytoken == Token_THIS
               || yytoken == Token_THROW
               || yytoken == Token_TRY
               || yytoken == Token_TYPEOF
               || yytoken == Token_UINT
               || yytoken == Token_ULONG
               || yytoken == Token_UNCHECKED
               || yytoken == Token_UNSAFE
               || yytoken == Token_USHORT
               || yytoken == Token_USING
               || yytoken == Token_VOID
               || yytoken == Token_WHILE
               || yytoken == Token_ADD
               || yytoken == Token_ALIAS
               || yytoken == Token_GET
               || yytoken == Token_GLOBAL
               || yytoken == Token_PARTIAL
               || yytoken == Token_REMOVE
               || yytoken == Token_SET
               || yytoken == Token_VALUE
               || yytoken == Token_WHERE
               || yytoken == Token_YIELD
               || yytoken == Token_ASSEMBLY
               || yytoken == Token_LPAREN
               || yytoken == Token_LBRACE
               || yytoken == Token_SEMICOLON
               || yytoken == Token_BANG
               || yytoken == Token_TILDE
               || yytoken == Token_INCREMENT
               || yytoken == Token_DECREMENT
               || yytoken == Token_PLUS
               || yytoken == Token_MINUS
               || yytoken == Token_STAR
               || yytoken == Token_BIT_AND
               || yytoken == Token_TRUE
               || yytoken == Token_FALSE
               || yytoken == Token_NULL
               || yytoken == Token_INTEGER_LITERAL
               || yytoken == Token_REAL_LITERAL
               || yytoken == Token_CHARACTER_LITERAL
               || yytoken == Token_STRING_LITERAL
               || yytoken == Token_IDENTIFIER)
          {
            block_statement_ast *__node_54 = 0;
            if (!parse_block_statement(&__node_54))
              {
                return yy_expected_symbol(ast_node::Kind_block_statement, "block_statement");
              }
            (*yynode)->statement_sequence = snoc((*yynode)->statement_sequence, __node_54, memory_pool);
          }
        if (yytoken != Token_RBRACE)
          return yy_expected_token(yytoken, Token_RBRACE, "}");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_block_statement(block_statement_ast **yynode)
  {
    *yynode = create<block_statement_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BREAK
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_CONST
        || yytoken == Token_CONTINUE
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DO
        || yytoken == Token_DOUBLE
        || yytoken == Token_FIXED
        || yytoken == Token_FLOAT
        || yytoken == Token_FOREACH
        || yytoken == Token_FOR
        || yytoken == Token_GOTO
        || yytoken == Token_IF
        || yytoken == Token_INT
        || yytoken == Token_LOCK
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_RETURN
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_SWITCH
        || yytoken == Token_THIS
        || yytoken == Token_THROW
        || yytoken == Token_TRY
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_UNSAFE
        || yytoken == Token_USHORT
        || yytoken == Token_USING
        || yytoken == Token_VOID
        || yytoken == Token_WHILE
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_LBRACE
        || yytoken == Token_SEMICOLON
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        if ((yytoken == Token_ADD
             || yytoken == Token_ALIAS
             || yytoken == Token_GET
             || yytoken == Token_GLOBAL
             || yytoken == Token_PARTIAL
             || yytoken == Token_REMOVE
             || yytoken == Token_SET
             || yytoken == Token_VALUE
             || yytoken == Token_WHERE
             || yytoken == Token_YIELD
             || yytoken == Token_ASSEMBLY
             || yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_COLON ))
          {
            labeled_statement_ast *__node_55 = 0;
            if (!parse_labeled_statement(&__node_55))
              {
                return yy_expected_symbol(ast_node::Kind_labeled_statement, "labeled_statement");
              }
            (*yynode)->labeled_statement = __node_55;
          }
        else if (yytoken == Token_CONST)
          {
            local_constant_declaration_ast *__node_56 = 0;
            if (!parse_local_constant_declaration(&__node_56))
              {
                return yy_expected_symbol(ast_node::Kind_local_constant_declaration, "local_constant_declaration");
              }
            (*yynode)->local_constant_declaration_statement = __node_56;
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
          }
        else if ((yytoken == Token_BOOL
                  || yytoken == Token_BYTE
                  || yytoken == Token_CHAR
                  || yytoken == Token_DECIMAL
                  || yytoken == Token_DOUBLE
                  || yytoken == Token_FLOAT
                  || yytoken == Token_INT
                  || yytoken == Token_LONG
                  || yytoken == Token_OBJECT
                  || yytoken == Token_SBYTE
                  || yytoken == Token_SHORT
                  || yytoken == Token_STRING
                  || yytoken == Token_UINT
                  || yytoken == Token_ULONG
                  || yytoken == Token_USHORT
                  || yytoken == Token_VOID
                  || yytoken == Token_ADD
                  || yytoken == Token_ALIAS
                  || yytoken == Token_GET
                  || yytoken == Token_GLOBAL
                  || yytoken == Token_PARTIAL
                  || yytoken == Token_REMOVE
                  || yytoken == Token_SET
                  || yytoken == Token_VALUE
                  || yytoken == Token_WHERE
                  || yytoken == Token_YIELD
                  || yytoken == Token_ASSEMBLY
                  || yytoken == Token_IDENTIFIER) && ( lookahead_is_local_variable_declaration() == true ))
          {
            local_variable_declaration_ast *__node_57 = 0;
            if (!parse_local_variable_declaration(&__node_57))
              {
                return yy_expected_symbol(ast_node::Kind_local_variable_declaration, "local_variable_declaration");
              }
            (*yynode)->local_variable_declaration_statement = __node_57;
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
          }
        else if (yytoken == Token_BASE
                 || yytoken == Token_BOOL
                 || yytoken == Token_BREAK
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR
                 || yytoken == Token_CHECKED
                 || yytoken == Token_CONTINUE
                 || yytoken == Token_DECIMAL
                 || yytoken == Token_DEFAULT
                 || yytoken == Token_DELEGATE
                 || yytoken == Token_DO
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_FIXED
                 || yytoken == Token_FLOAT
                 || yytoken == Token_FOREACH
                 || yytoken == Token_FOR
                 || yytoken == Token_GOTO
                 || yytoken == Token_IF
                 || yytoken == Token_INT
                 || yytoken == Token_LOCK
                 || yytoken == Token_LONG
                 || yytoken == Token_NEW
                 || yytoken == Token_OBJECT
                 || yytoken == Token_RETURN
                 || yytoken == Token_SBYTE
                 || yytoken == Token_SHORT
                 || yytoken == Token_SIZEOF
                 || yytoken == Token_STRING
                 || yytoken == Token_SWITCH
                 || yytoken == Token_THIS
                 || yytoken == Token_THROW
                 || yytoken == Token_TRY
                 || yytoken == Token_TYPEOF
                 || yytoken == Token_UINT
                 || yytoken == Token_ULONG
                 || yytoken == Token_UNCHECKED
                 || yytoken == Token_UNSAFE
                 || yytoken == Token_USHORT
                 || yytoken == Token_USING
                 || yytoken == Token_WHILE
                 || yytoken == Token_ADD
                 || yytoken == Token_ALIAS
                 || yytoken == Token_GET
                 || yytoken == Token_GLOBAL
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_REMOVE
                 || yytoken == Token_SET
                 || yytoken == Token_VALUE
                 || yytoken == Token_WHERE
                 || yytoken == Token_YIELD
                 || yytoken == Token_ASSEMBLY
                 || yytoken == Token_LPAREN
                 || yytoken == Token_LBRACE
                 || yytoken == Token_SEMICOLON
                 || yytoken == Token_BANG
                 || yytoken == Token_TILDE
                 || yytoken == Token_INCREMENT
                 || yytoken == Token_DECREMENT
                 || yytoken == Token_PLUS
                 || yytoken == Token_MINUS
                 || yytoken == Token_STAR
                 || yytoken == Token_BIT_AND
                 || yytoken == Token_TRUE
                 || yytoken == Token_FALSE
                 || yytoken == Token_NULL
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_REAL_LITERAL
                 || yytoken == Token_CHARACTER_LITERAL
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_IDENTIFIER)
          {
            embedded_statement_ast *__node_58 = 0;
            if (!parse_embedded_statement(&__node_58))
              {
                return yy_expected_symbol(ast_node::Kind_embedded_statement, "embedded_statement");
              }
            (*yynode)->statement = __node_58;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_boolean_expression(boolean_expression_ast **yynode)
  {
    *yynode = create<boolean_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        expression_ast *__node_59 = 0;
        if (!parse_expression(&__node_59))
          {
            return yy_expected_symbol(ast_node::Kind_expression, "expression");
          }
        (*yynode)->expression = __node_59;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_break_statement(break_statement_ast **yynode)
  {
    *yynode = create<break_statement_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BREAK)
      {
        if (yytoken != Token_BREAK)
          return yy_expected_token(yytoken, Token_BREAK, "break");
        yylex();
        if (yytoken != Token_SEMICOLON)
          return yy_expected_token(yytoken, Token_SEMICOLON, ";");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_builtin_class_type(builtin_class_type_ast **yynode)
  {
    *yynode = create<builtin_class_type_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_OBJECT
        || yytoken == Token_STRING)
      {
        if (yytoken == Token_OBJECT)
          {
            if (yytoken != Token_OBJECT)
              return yy_expected_token(yytoken, Token_OBJECT, "object");
            yylex();
            (*yynode)->type = builtin_class_type::type_object;
          }
        else if (yytoken == Token_STRING)
          {
            if (yytoken != Token_STRING)
              return yy_expected_token(yytoken, Token_STRING, "string");
            yylex();
            (*yynode)->type = builtin_class_type::type_string;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_cast_expression(cast_expression_ast **yynode)
  {
    *yynode = create<cast_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LPAREN)
      {
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        type_ast *__node_60 = 0;
        if (!parse_type(&__node_60))
          {
            return yy_expected_symbol(ast_node::Kind_type, "type");
          }
        (*yynode)->type = __node_60;
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        unary_expression_ast *__node_61 = 0;
        if (!parse_unary_expression(&__node_61))
          {
            return yy_expected_symbol(ast_node::Kind_unary_expression, "unary_expression");
          }
        (*yynode)->casted_expression = __node_61;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_catch_clauses(catch_clauses_ast **yynode)
  {
    *yynode = create<catch_clauses_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_CATCH)
      {
        if ((yytoken == Token_CATCH) && ( LA(2).kind != Token_LPAREN ))
          {
            general_catch_clause_ast *__node_62 = 0;
            if (!parse_general_catch_clause(&__node_62))
              {
                return yy_expected_symbol(ast_node::Kind_general_catch_clause, "general_catch_clause");
              }
            (*yynode)->general_catch_clause = __node_62;
          }
        else if (yytoken == Token_CATCH)
          {
            do
              {
                if (LA(2).kind != Token_LPAREN)
                  {
                    break;
                  }
                specific_catch_clause_ast *__node_63 = 0;
                if (!parse_specific_catch_clause(&__node_63))
                  {
                    return yy_expected_symbol(ast_node::Kind_specific_catch_clause, "specific_catch_clause");
                  }
                (*yynode)->specific_catch_clause_sequence = snoc((*yynode)->specific_catch_clause_sequence, __node_63, memory_pool);
              }
            while (yytoken == Token_CATCH);
            if (yytoken == Token_CATCH)
              {
                general_catch_clause_ast *__node_64 = 0;
                if (!parse_general_catch_clause(&__node_64))
                  {
                    return yy_expected_symbol(ast_node::Kind_general_catch_clause, "general_catch_clause");
                  }
                (*yynode)->general_catch_clause = __node_64;
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
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_checked_statement(checked_statement_ast **yynode)
  {
    *yynode = create<checked_statement_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_CHECKED)
      {
        if (yytoken != Token_CHECKED)
          return yy_expected_token(yytoken, Token_CHECKED, "checked");
        yylex();
        block_ast *__node_65 = 0;
        if (!parse_block(&__node_65))
          {
            return yy_expected_symbol(ast_node::Kind_block, "block");
          }
        (*yynode)->body = __node_65;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_class_base(class_base_ast **yynode)
  {
    *yynode = create<class_base_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_COLON)
      {
        if (yytoken != Token_COLON)
          return yy_expected_token(yytoken, Token_COLON, ":");
        yylex();
        if (yytoken == Token_OBJECT
            || yytoken == Token_STRING)
          {
            builtin_class_type_ast *__node_66 = 0;
            if (!parse_builtin_class_type(&__node_66))
              {
                return yy_expected_symbol(ast_node::Kind_builtin_class_type, "builtin_class_type");
              }
            (*yynode)->builtin_class_type = __node_66;
            if (yytoken == Token_COMMA)
              {
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
                type_name_ast *__node_67 = 0;
                if (!parse_type_name(&__node_67))
                  {
                    return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
                  }
                (*yynode)->interface_type_sequence = snoc((*yynode)->interface_type_sequence, __node_67, memory_pool);
                while (yytoken == Token_COMMA)
                  {
                    if (yytoken != Token_COMMA)
                      return yy_expected_token(yytoken, Token_COMMA, ",");
                    yylex();
                    type_name_ast *__node_68 = 0;
                    if (!parse_type_name(&__node_68))
                      {
                        return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
                      }
                    (*yynode)->interface_type_sequence = snoc((*yynode)->interface_type_sequence, __node_68, memory_pool);
                  }
              }
            else if (true /*epsilon*/)
            {}
            else
              {
                return false;
              }
          }
        else if (yytoken == Token_ADD
                 || yytoken == Token_ALIAS
                 || yytoken == Token_GET
                 || yytoken == Token_GLOBAL
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_REMOVE
                 || yytoken == Token_SET
                 || yytoken == Token_VALUE
                 || yytoken == Token_WHERE
                 || yytoken == Token_YIELD
                 || yytoken == Token_ASSEMBLY
                 || yytoken == Token_IDENTIFIER)
          {
            type_name_ast *__node_69 = 0;
            if (!parse_type_name(&__node_69))
              {
                return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
              }
            (*yynode)->base_type_sequence = snoc((*yynode)->base_type_sequence, __node_69, memory_pool);
            while (yytoken == Token_COMMA)
              {
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
                type_name_ast *__node_70 = 0;
                if (!parse_type_name(&__node_70))
                  {
                    return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
                  }
                (*yynode)->base_type_sequence = snoc((*yynode)->base_type_sequence, __node_70, memory_pool);
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_class_body(class_body_ast **yynode)
  {
    *yynode = create<class_body_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LBRACE)
      {
        if (yytoken != Token_LBRACE)
          return yy_expected_token(yytoken, Token_LBRACE, "{");
        yylex();
        while (yytoken == Token_ABSTRACT
               || yytoken == Token_BOOL
               || yytoken == Token_BYTE
               || yytoken == Token_CHAR
               || yytoken == Token_CLASS
               || yytoken == Token_CONST
               || yytoken == Token_DECIMAL
               || yytoken == Token_DELEGATE
               || yytoken == Token_DOUBLE
               || yytoken == Token_ENUM
               || yytoken == Token_EVENT
               || yytoken == Token_EXPLICIT
               || yytoken == Token_EXTERN
               || yytoken == Token_FLOAT
               || yytoken == Token_IMPLICIT
               || yytoken == Token_INT
               || yytoken == Token_INTERFACE
               || yytoken == Token_INTERNAL
               || yytoken == Token_LONG
               || yytoken == Token_NEW
               || yytoken == Token_OBJECT
               || yytoken == Token_OVERRIDE
               || yytoken == Token_PRIVATE
               || yytoken == Token_PROTECTED
               || yytoken == Token_PUBLIC
               || yytoken == Token_READONLY
               || yytoken == Token_SBYTE
               || yytoken == Token_SEALED
               || yytoken == Token_SHORT
               || yytoken == Token_STATIC
               || yytoken == Token_STRING
               || yytoken == Token_STRUCT
               || yytoken == Token_UINT
               || yytoken == Token_ULONG
               || yytoken == Token_UNSAFE
               || yytoken == Token_USHORT
               || yytoken == Token_VIRTUAL
               || yytoken == Token_VOID
               || yytoken == Token_VOLATILE
               || yytoken == Token_ADD
               || yytoken == Token_ALIAS
               || yytoken == Token_GET
               || yytoken == Token_GLOBAL
               || yytoken == Token_PARTIAL
               || yytoken == Token_REMOVE
               || yytoken == Token_SET
               || yytoken == Token_VALUE
               || yytoken == Token_WHERE
               || yytoken == Token_YIELD
               || yytoken == Token_ASSEMBLY
               || yytoken == Token_LBRACKET
               || yytoken == Token_TILDE
               || yytoken == Token_IDENTIFIER)
          {
            class_member_declaration_ast *__node_71 = 0;
            if (!parse_class_member_declaration(&__node_71))
              {
                return yy_expected_symbol(ast_node::Kind_class_member_declaration, "class_member_declaration");
              }
            (*yynode)->member_declaration_sequence = snoc((*yynode)->member_declaration_sequence, __node_71, memory_pool);
          }
        if (yytoken != Token_RBRACE)
          return yy_expected_token(yytoken, Token_RBRACE, "}");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_class_declaration(class_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers, bool partial)
  {
    *yynode = create<class_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->start_token < (*yynode)->start_token)
      (*yynode)->start_token = modifiers->start_token;

    (*yynode)->partial = partial;
    if (yytoken == Token_CLASS)
      {
        if (yytoken != Token_CLASS)
          return yy_expected_token(yytoken, Token_CLASS, "class");
        yylex();
        identifier_ast *__node_72 = 0;
        if (!parse_identifier(&__node_72))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->class_name = __node_72;
        if ((yytoken == Token_LESS_THAN) && ( compatibility_mode() >= csharp20_compatibility ))
          {
            type_parameters_ast *__node_73 = 0;
            if (!parse_type_parameters(&__node_73))
              {
                return yy_expected_symbol(ast_node::Kind_type_parameters, "type_parameters");
              }
            (*yynode)->type_parameters = __node_73;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken == Token_COLON)
          {
            class_base_ast *__node_74 = 0;
            if (!parse_class_base(&__node_74))
              {
                return yy_expected_symbol(ast_node::Kind_class_base, "class_base");
              }
            (*yynode)->class_base = __node_74;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if ((yytoken == Token_WHERE) && ( compatibility_mode() >= csharp20_compatibility ))
          {
            type_parameter_constraints_clauses_ast *__node_75 = 0;
            if (!parse_type_parameter_constraints_clauses(&__node_75))
              {
                return yy_expected_symbol(ast_node::Kind_type_parameter_constraints_clauses, "type_parameter_constraints_clauses");
              }
            (*yynode)->type_parameter_constraints_clauses = __node_75;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        class_body_ast *__node_76 = 0;
        if (!parse_class_body(&__node_76))
          {
            return yy_expected_symbol(ast_node::Kind_class_body, "class_body");
          }
        (*yynode)->body = __node_76;
        if (yytoken == Token_SEMICOLON)
          {
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_class_member_declaration(class_member_declaration_ast **yynode)
  {
    *yynode = create<class_member_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ABSTRACT
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CLASS
        || yytoken == Token_CONST
        || yytoken == Token_DECIMAL
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_EVENT
        || yytoken == Token_EXPLICIT
        || yytoken == Token_EXTERN
        || yytoken == Token_FLOAT
        || yytoken == Token_IMPLICIT
        || yytoken == Token_INT
        || yytoken == Token_INTERFACE
        || yytoken == Token_INTERNAL
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_OVERRIDE
        || yytoken == Token_PRIVATE
        || yytoken == Token_PROTECTED
        || yytoken == Token_PUBLIC
        || yytoken == Token_READONLY
        || yytoken == Token_SBYTE
        || yytoken == Token_SEALED
        || yytoken == Token_SHORT
        || yytoken == Token_STATIC
        || yytoken == Token_STRING
        || yytoken == Token_STRUCT
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNSAFE
        || yytoken == Token_USHORT
        || yytoken == Token_VIRTUAL
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LBRACKET
        || yytoken == Token_TILDE
        || yytoken == Token_IDENTIFIER)
      {
        const list_node<attribute_section_ast *> *attribute_sequence = 0;

        optional_modifiers_ast *modifiers = 0;

        while (yytoken == Token_LBRACKET)
          {
            attribute_section_ast *__node_77 = 0;
            if (!parse_attribute_section(&__node_77))
              {
                return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
              }
            attribute_sequence = snoc(attribute_sequence, __node_77, memory_pool);
          }
        optional_modifiers_ast *__node_78 = 0;
        if (!parse_optional_modifiers(&__node_78))
          {
            return yy_expected_symbol(ast_node::Kind_optional_modifiers, "optional_modifiers");
          }
        modifiers = __node_78;
        if (yytoken == Token_TILDE)
          {
            finalizer_declaration_ast *__node_79 = 0;
            if (!parse_finalizer_declaration(&__node_79, attribute_sequence, modifiers ))
              {
                return yy_expected_symbol(ast_node::Kind_finalizer_declaration, "finalizer_declaration");
              }
            (*yynode)->finalizer_declaration = __node_79;
          }
        else if (yytoken == Token_BOOL
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR
                 || yytoken == Token_CLASS
                 || yytoken == Token_CONST
                 || yytoken == Token_DECIMAL
                 || yytoken == Token_DELEGATE
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_ENUM
                 || yytoken == Token_EVENT
                 || yytoken == Token_EXPLICIT
                 || yytoken == Token_FLOAT
                 || yytoken == Token_IMPLICIT
                 || yytoken == Token_INT
                 || yytoken == Token_INTERFACE
                 || yytoken == Token_LONG
                 || yytoken == Token_OBJECT
                 || yytoken == Token_SBYTE
                 || yytoken == Token_SHORT
                 || yytoken == Token_STRING
                 || yytoken == Token_STRUCT
                 || yytoken == Token_UINT
                 || yytoken == Token_ULONG
                 || yytoken == Token_USHORT
                 || yytoken == Token_VOID
                 || yytoken == Token_ADD
                 || yytoken == Token_ALIAS
                 || yytoken == Token_GET
                 || yytoken == Token_GLOBAL
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_REMOVE
                 || yytoken == Token_SET
                 || yytoken == Token_VALUE
                 || yytoken == Token_WHERE
                 || yytoken == Token_YIELD
                 || yytoken == Token_ASSEMBLY
                 || yytoken == Token_IDENTIFIER)
          {
            class_or_struct_member_declaration_ast *__node_80 = 0;
            if (!parse_class_or_struct_member_declaration(&__node_80, attribute_sequence, modifiers ))
              {
                return yy_expected_symbol(ast_node::Kind_class_or_struct_member_declaration, "class_or_struct_member_declaration");
              }
            (*yynode)->other_declaration = __node_80;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_class_or_struct_member_declaration(class_or_struct_member_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers)
  {
    *yynode = create<class_or_struct_member_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CLASS
        || yytoken == Token_CONST
        || yytoken == Token_DECIMAL
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_EVENT
        || yytoken == Token_EXPLICIT
        || yytoken == Token_FLOAT
        || yytoken == Token_IMPLICIT
        || yytoken == Token_INT
        || yytoken == Token_INTERFACE
        || yytoken == Token_LONG
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_STRING
        || yytoken == Token_STRUCT
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT
        || yytoken == Token_VOID
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        return_type_ast *member_type = 0;

        const list_node<variable_declarator_ast *> *variable_declarator_sequence = 0;

        type_name_safe_ast *member_name_or_interface_type = 0;

        if (yytoken == Token_CONST)
          {
            constant_declaration_ast *__node_81 = 0;
            if (!parse_constant_declaration(&__node_81, attribute_sequence, modifiers ))
              {
                return yy_expected_symbol(ast_node::Kind_constant_declaration, "constant_declaration");
              }
            if (__node_81->start_token < (*yynode)->start_token)
              (*yynode)->start_token = __node_81->start_token;
            (*yynode)->constant_declaration = __node_81;
          }
        else if (yytoken == Token_EVENT)
          {
            event_declaration_ast *__node_82 = 0;
            if (!parse_event_declaration(&__node_82, attribute_sequence, modifiers ))
              {
                return yy_expected_symbol(ast_node::Kind_event_declaration, "event_declaration");
              }
            if (__node_82->start_token < (*yynode)->start_token)
              (*yynode)->start_token = __node_82->start_token;
            (*yynode)->event_declaration = __node_82;
          }
        else if (yytoken == Token_EXPLICIT
                 || yytoken == Token_IMPLICIT)
          {
            conversion_operator_declaration_ast *__node_83 = 0;
            if (!parse_conversion_operator_declaration(&__node_83, attribute_sequence, modifiers ))
              {
                return yy_expected_symbol(ast_node::Kind_conversion_operator_declaration, "conversion_operator_declaration");
              }
            if (__node_83->start_token < (*yynode)->start_token)
              (*yynode)->start_token = __node_83->start_token;
            (*yynode)->conversion_operator_declaration = __node_83;
          }
        else if ((yytoken == Token_ADD
                  || yytoken == Token_ALIAS
                  || yytoken == Token_GET
                  || yytoken == Token_GLOBAL
                  || yytoken == Token_PARTIAL
                  || yytoken == Token_REMOVE
                  || yytoken == Token_SET
                  || yytoken == Token_VALUE
                  || yytoken == Token_WHERE
                  || yytoken == Token_YIELD
                  || yytoken == Token_ASSEMBLY
                  || yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_LPAREN ))
          {
            constructor_declaration_ast *__node_84 = 0;
            if (!parse_constructor_declaration(&__node_84, attribute_sequence, modifiers ))
              {
                return yy_expected_symbol(ast_node::Kind_constructor_declaration, "constructor_declaration");
              }
            if (__node_84->start_token < (*yynode)->start_token)
              (*yynode)->start_token = __node_84->start_token;
            (*yynode)->constructor_declaration = __node_84;
          }
        else if ((yytoken == Token_CLASS
                  || yytoken == Token_DELEGATE
                  || yytoken == Token_ENUM
                  || yytoken == Token_INTERFACE
                  || yytoken == Token_STRUCT
                  || yytoken == Token_PARTIAL) && ( (yytoken != Token_PARTIAL) || (LA(2).kind == Token_CLASS
                                                    || LA(2).kind == Token_INTERFACE || LA(2).kind == Token_ENUM
                                                    || LA(2).kind == Token_STRUCT || LA(2).kind == Token_DELEGATE) ))
          {
            type_declaration_rest_ast *__node_85 = 0;
            if (!parse_type_declaration_rest(&__node_85, attribute_sequence, modifiers ))
              {
                return yy_expected_symbol(ast_node::Kind_type_declaration_rest, "type_declaration_rest");
              }
            if (__node_85->start_token < (*yynode)->start_token)
              (*yynode)->start_token = __node_85->start_token;
            (*yynode)->type_declaration_rest = __node_85;
          }
        else if (yytoken == Token_BOOL
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR
                 || yytoken == Token_DECIMAL
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_LONG
                 || yytoken == Token_OBJECT
                 || yytoken == Token_SBYTE
                 || yytoken == Token_SHORT
                 || yytoken == Token_STRING
                 || yytoken == Token_UINT
                 || yytoken == Token_ULONG
                 || yytoken == Token_USHORT
                 || yytoken == Token_VOID
                 || yytoken == Token_ADD
                 || yytoken == Token_ALIAS
                 || yytoken == Token_GET
                 || yytoken == Token_GLOBAL
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_REMOVE
                 || yytoken == Token_SET
                 || yytoken == Token_VALUE
                 || yytoken == Token_WHERE
                 || yytoken == Token_YIELD
                 || yytoken == Token_ASSEMBLY
                 || yytoken == Token_IDENTIFIER)
          {
            return_type_ast *__node_86 = 0;
            if (!parse_return_type(&__node_86))
              {
                return yy_expected_symbol(ast_node::Kind_return_type, "return_type");
              }
            member_type = __node_86;
            if ((yytoken == Token_OPERATOR) && ( member_type->type == return_type::type_regular ))
              {
                unary_or_binary_operator_declaration_ast *__node_87 = 0;
                if (!parse_unary_or_binary_operator_declaration(&__node_87,
                    attribute_sequence, modifiers, member_type->regular_type
                                                               ))
                  {
                    return yy_expected_symbol(ast_node::Kind_unary_or_binary_operator_declaration, "unary_or_binary_operator_declaration");
                  }
                if (__node_87->start_token < (*yynode)->start_token)
                  (*yynode)->start_token = __node_87->start_token;
                (*yynode)->unary_or_binary_operator_declaration = __node_87;
              }
            else if ((yytoken == Token_THIS) && ( member_type->type == return_type::type_regular ))
              {
                indexer_declaration_ast *__node_88 = 0;
                if (!parse_indexer_declaration(&__node_88,
                                               attribute_sequence, modifiers, member_type->regular_type, 0 /* no interface type */
                                              ))
                  {
                    return yy_expected_symbol(ast_node::Kind_indexer_declaration, "indexer_declaration");
                  }
                if (__node_88->start_token < (*yynode)->start_token)
                  (*yynode)->start_token = __node_88->start_token;
                (*yynode)->indexer_declaration = __node_88;
              }
            else if ((yytoken == Token_ADD
                      || yytoken == Token_ALIAS
                      || yytoken == Token_GET
                      || yytoken == Token_GLOBAL
                      || yytoken == Token_PARTIAL
                      || yytoken == Token_REMOVE
                      || yytoken == Token_SET
                      || yytoken == Token_VALUE
                      || yytoken == Token_WHERE
                      || yytoken == Token_YIELD
                      || yytoken == Token_ASSEMBLY
                      || yytoken == Token_IDENTIFIER) && ( ( LA(2).kind == Token_SEMICOLON || LA(2).kind == Token_ASSIGN
                                                             || LA(2).kind == Token_COMMA
                                                           ) && (member_type->type == return_type::type_regular) ))
              {
                variable_declarator_ast *__node_89 = 0;
                if (!parse_variable_declarator(&__node_89))
                  {
                    return yy_expected_symbol(ast_node::Kind_variable_declarator, "variable_declarator");
                  }
                variable_declarator_sequence = snoc(variable_declarator_sequence, __node_89, memory_pool);
                while (yytoken == Token_COMMA)
                  {
                    if (yytoken != Token_COMMA)
                      return yy_expected_token(yytoken, Token_COMMA, ",");
                    yylex();
                    variable_declarator_ast *__node_90 = 0;
                    if (!parse_variable_declarator(&__node_90))
                      {
                        return yy_expected_symbol(ast_node::Kind_variable_declarator, "variable_declarator");
                      }
                    variable_declarator_sequence = snoc(variable_declarator_sequence, __node_90, memory_pool);
                  }
                if (yytoken != Token_SEMICOLON)
                  return yy_expected_token(yytoken, Token_SEMICOLON, ";");
                yylex();
                variable_declaration_data_ast *__node_91 = 0;
                if (!parse_variable_declaration_data(&__node_91,
                                                     attribute_sequence, modifiers,
                                                     member_type->regular_type, variable_declarator_sequence
                                                    ))
                  {
                    return yy_expected_symbol(ast_node::Kind_variable_declaration_data, "variable_declaration_data");
                  }
                if (__node_91->start_token < (*yynode)->start_token)
                  (*yynode)->start_token = __node_91->start_token;
                (*yynode)->field_declaration = __node_91;
              }
            else if (yytoken == Token_ADD
                     || yytoken == Token_ALIAS
                     || yytoken == Token_GET
                     || yytoken == Token_GLOBAL
                     || yytoken == Token_PARTIAL
                     || yytoken == Token_REMOVE
                     || yytoken == Token_SET
                     || yytoken == Token_VALUE
                     || yytoken == Token_WHERE
                     || yytoken == Token_YIELD
                     || yytoken == Token_ASSEMBLY
                     || yytoken == Token_IDENTIFIER)
              {
                type_name_safe_ast *__node_92 = 0;
                if (!parse_type_name_safe(&__node_92))
                  {
                    return yy_expected_symbol(ast_node::Kind_type_name_safe, "type_name_safe");
                  }
                member_name_or_interface_type = __node_92;
                if ((yytoken == Token_DOT) && ( member_type->type == return_type::type_regular ))
                  {
                    if (yytoken != Token_DOT)
                      return yy_expected_token(yytoken, Token_DOT, ".");
                    yylex();
                    indexer_declaration_ast *__node_93 = 0;
                    if (!parse_indexer_declaration(&__node_93,
                                                   attribute_sequence, modifiers,
                                                   member_type->regular_type, member_name_or_interface_type
                                                  ))
                      {
                        return yy_expected_symbol(ast_node::Kind_indexer_declaration, "indexer_declaration");
                      }
                    if (__node_93->start_token < (*yynode)->start_token)
                      (*yynode)->start_token = __node_93->start_token;
                    (*yynode)->indexer_declaration = __node_93;
                  }
                else if ((yytoken == Token_LBRACE) && ( member_type->type == return_type::type_regular ))
                  {
                    property_declaration_ast *__node_94 = 0;
                    if (!parse_property_declaration(&__node_94,
                                                    attribute_sequence, modifiers, member_type->regular_type, member_name_or_interface_type
                                                   ))
                      {
                        return yy_expected_symbol(ast_node::Kind_property_declaration, "property_declaration");
                      }
                    if (__node_94->start_token < (*yynode)->start_token)
                      (*yynode)->start_token = __node_94->start_token;
                    (*yynode)->property_declaration = __node_94;
                  }
                else if (yytoken == Token_LPAREN
                         || yytoken == Token_LESS_THAN)
                  {
                    method_declaration_ast *__node_95 = 0;
                    if (!parse_method_declaration(&__node_95,
                                                  attribute_sequence, modifiers, member_type, member_name_or_interface_type
                                                 ))
                      {
                        return yy_expected_symbol(ast_node::Kind_method_declaration, "method_declaration");
                      }
                    if (__node_95->start_token < (*yynode)->start_token)
                      (*yynode)->start_token = __node_95->start_token;
                    (*yynode)->method_declaration = __node_95;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_class_type(class_type_ast **yynode)
  {
    *yynode = create<class_type_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_OBJECT
        || yytoken == Token_STRING
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        if (yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_IDENTIFIER)
          {
            type_name_ast *__node_96 = 0;
            if (!parse_type_name(&__node_96))
              {
                return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
              }
            (*yynode)->type_name = __node_96;
          }
        else if (yytoken == Token_OBJECT
                 || yytoken == Token_STRING)
          {
            builtin_class_type_ast *__node_97 = 0;
            if (!parse_builtin_class_type(&__node_97))
              {
                return yy_expected_symbol(ast_node::Kind_builtin_class_type, "builtin_class_type");
              }
            (*yynode)->builtin_class_type = __node_97;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_compilation_unit(compilation_unit_ast **yynode)
  {
    *yynode = create<compilation_unit_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ABSTRACT
        || yytoken == Token_CLASS
        || yytoken == Token_DELEGATE
        || yytoken == Token_ENUM
        || yytoken == Token_EXTERN
        || yytoken == Token_INTERFACE
        || yytoken == Token_INTERNAL
        || yytoken == Token_NAMESPACE
        || yytoken == Token_NEW
        || yytoken == Token_OVERRIDE
        || yytoken == Token_PRIVATE
        || yytoken == Token_PROTECTED
        || yytoken == Token_PUBLIC
        || yytoken == Token_READONLY
        || yytoken == Token_SEALED
        || yytoken == Token_STATIC
        || yytoken == Token_STRUCT
        || yytoken == Token_UNSAFE
        || yytoken == Token_USING
        || yytoken == Token_VIRTUAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_PARTIAL
        || yytoken == Token_LBRACKET || yytoken == Token_EOF)
      {
        while (yytoken == Token_EXTERN)
          {
            extern_alias_directive_ast *__node_98 = 0;
            if (!parse_extern_alias_directive(&__node_98))
              {
                return yy_expected_symbol(ast_node::Kind_extern_alias_directive, "extern_alias_directive");
              }
            (*yynode)->extern_alias_sequence = snoc((*yynode)->extern_alias_sequence, __node_98, memory_pool);
          }
        while (yytoken == Token_USING)
          {
            using_directive_ast *__node_99 = 0;
            if (!parse_using_directive(&__node_99))
              {
                return yy_expected_symbol(ast_node::Kind_using_directive, "using_directive");
              }
            (*yynode)->using_sequence = snoc((*yynode)->using_sequence, __node_99, memory_pool);
          }
        while (yytoken == Token_LBRACKET)
          {
            if (LA(2).kind != Token_ASSEMBLY)
              break;
            global_attribute_section_ast *__node_100 = 0;
            if (!parse_global_attribute_section(&__node_100))
              {
                return yy_expected_symbol(ast_node::Kind_global_attribute_section, "global_attribute_section");
              }
            (*yynode)->global_attribute_sequence = snoc((*yynode)->global_attribute_sequence, __node_100, memory_pool);
          }
        while (yytoken == Token_ABSTRACT
               || yytoken == Token_CLASS
               || yytoken == Token_DELEGATE
               || yytoken == Token_ENUM
               || yytoken == Token_EXTERN
               || yytoken == Token_INTERFACE
               || yytoken == Token_INTERNAL
               || yytoken == Token_NAMESPACE
               || yytoken == Token_NEW
               || yytoken == Token_OVERRIDE
               || yytoken == Token_PRIVATE
               || yytoken == Token_PROTECTED
               || yytoken == Token_PUBLIC
               || yytoken == Token_READONLY
               || yytoken == Token_SEALED
               || yytoken == Token_STATIC
               || yytoken == Token_STRUCT
               || yytoken == Token_UNSAFE
               || yytoken == Token_VIRTUAL
               || yytoken == Token_VOLATILE
               || yytoken == Token_PARTIAL
               || yytoken == Token_LBRACKET)
          {
            namespace_member_declaration_ast *__node_101 = 0;
            if (!parse_namespace_member_declaration(&__node_101))
              {
                return yy_expected_symbol(ast_node::Kind_namespace_member_declaration, "namespace_member_declaration");
              }
            (*yynode)->namespace_sequence = snoc((*yynode)->namespace_sequence, __node_101, memory_pool);
          }
        if (Token_EOF != yytoken)
          {
            return false;
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_conditional_expression(conditional_expression_ast **yynode)
  {
    *yynode = create<conditional_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        null_coalescing_expression_ast *__node_102 = 0;
        if (!parse_null_coalescing_expression(&__node_102))
          {
            return yy_expected_symbol(ast_node::Kind_null_coalescing_expression, "null_coalescing_expression");
          }
        (*yynode)->null_coalescing_expression = __node_102;
        if (yytoken == Token_QUESTION)
          {
            if (yytoken != Token_QUESTION)
              return yy_expected_token(yytoken, Token_QUESTION, "?");
            yylex();
            expression_ast *__node_103 = 0;
            if (!parse_expression(&__node_103))
              {
                return yy_expected_symbol(ast_node::Kind_expression, "expression");
              }
            (*yynode)->if_expression = __node_103;
            if (yytoken != Token_COLON)
              return yy_expected_token(yytoken, Token_COLON, ":");
            yylex();
            expression_ast *__node_104 = 0;
            if (!parse_expression(&__node_104))
              {
                return yy_expected_symbol(ast_node::Kind_expression, "expression");
              }
            (*yynode)->else_expression = __node_104;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_constant_declaration(constant_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers)
  {
    *yynode = create<constant_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_CONST)
      {
        type_ast *type = 0;

        const list_node<constant_declarator_ast *> *declarator_sequence = 0;

        if (yytoken != Token_CONST)
          return yy_expected_token(yytoken, Token_CONST, "const");
        yylex();
        type_ast *__node_105 = 0;
        if (!parse_type(&__node_105))
          {
            return yy_expected_symbol(ast_node::Kind_type, "type");
          }
        type = __node_105;
        constant_declarator_ast *__node_106 = 0;
        if (!parse_constant_declarator(&__node_106))
          {
            return yy_expected_symbol(ast_node::Kind_constant_declarator, "constant_declarator");
          }
        declarator_sequence = snoc(declarator_sequence, __node_106, memory_pool);
        while (yytoken == Token_COMMA)
          {
            if (yytoken != Token_COMMA)
              return yy_expected_token(yytoken, Token_COMMA, ",");
            yylex();
            constant_declarator_ast *__node_107 = 0;
            if (!parse_constant_declarator(&__node_107))
              {
                return yy_expected_symbol(ast_node::Kind_constant_declarator, "constant_declarator");
              }
            declarator_sequence = snoc(declarator_sequence, __node_107, memory_pool);
          }
        if (yytoken != Token_SEMICOLON)
          return yy_expected_token(yytoken, Token_SEMICOLON, ";");
        yylex();
        constant_declaration_data_ast *__node_108 = 0;
        if (!parse_constant_declaration_data(&__node_108,
                                             attribute_sequence, modifiers, type, declarator_sequence
                                            ))
          {
            return yy_expected_symbol(ast_node::Kind_constant_declaration_data, "constant_declaration_data");
          }
        if (__node_108->start_token < (*yynode)->start_token)
          (*yynode)->start_token = __node_108->start_token;
        (*yynode)->data = __node_108;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_constant_declaration_data(constant_declaration_data_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers, type_ast *type, const list_node<constant_declarator_ast *> *constant_declarator_sequence)
  {
    *yynode = create<constant_declaration_data_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->start_token < (*yynode)->start_token)
      (*yynode)->start_token = modifiers->start_token;

    (*yynode)->type = type;
    if (type && type->start_token < (*yynode)->start_token)
      (*yynode)->start_token = type->start_token;

    (*yynode)->constant_declarator_sequence = constant_declarator_sequence;
    if (constant_declarator_sequence && constant_declarator_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = constant_declarator_sequence->to_front()->element->start_token;

    if (true /*epsilon*/ || yytoken == Token_RBRACE
        || yytoken == Token_SEMICOLON)
    {}
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_constant_declarator(constant_declarator_ast **yynode)
  {
    *yynode = create<constant_declarator_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        identifier_ast *__node_109 = 0;
        if (!parse_identifier(&__node_109))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->constant_name = __node_109;
        if (yytoken != Token_ASSIGN)
          return yy_expected_token(yytoken, Token_ASSIGN, "=");
        yylex();
        constant_expression_ast *__node_110 = 0;
        if (!parse_constant_expression(&__node_110))
          {
            return yy_expected_symbol(ast_node::Kind_constant_expression, "constant_expression");
          }
        (*yynode)->expression = __node_110;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_constant_expression(constant_expression_ast **yynode)
  {
    *yynode = create<constant_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        expression_ast *__node_111 = 0;
        if (!parse_expression(&__node_111))
          {
            return yy_expected_symbol(ast_node::Kind_expression, "expression");
          }
        (*yynode)->expression = __node_111;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_constructor_constraint(constructor_constraint_ast **yynode)
  {
    *yynode = create<constructor_constraint_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_NEW)
      {
        if (yytoken != Token_NEW)
          return yy_expected_token(yytoken, Token_NEW, "new");
        yylex();
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_constructor_declaration(constructor_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers)
  {
    *yynode = create<constructor_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->start_token < (*yynode)->start_token)
      (*yynode)->start_token = modifiers->start_token;

    if (yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        identifier_ast *__node_112 = 0;
        if (!parse_identifier(&__node_112))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->class_name = __node_112;
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        if (yytoken == Token_BOOL
            || yytoken == Token_BYTE
            || yytoken == Token_CHAR
            || yytoken == Token_DECIMAL
            || yytoken == Token_DOUBLE
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_OBJECT
            || yytoken == Token_OUT
            || yytoken == Token_PARAMS
            || yytoken == Token_REF
            || yytoken == Token_SBYTE
            || yytoken == Token_SHORT
            || yytoken == Token_STRING
            || yytoken == Token_UINT
            || yytoken == Token_ULONG
            || yytoken == Token_USHORT
            || yytoken == Token_VOID
            || yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_LBRACKET
            || yytoken == Token_IDENTIFIER)
          {
            formal_parameter_list_ast *__node_113 = 0;
            if (!parse_formal_parameter_list(&__node_113))
              {
                return yy_expected_symbol(ast_node::Kind_formal_parameter_list, "formal_parameter_list");
              }
            (*yynode)->formal_parameters = __node_113;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        if (yytoken == Token_COLON)
          {
            constructor_initializer_ast *__node_114 = 0;
            if (!parse_constructor_initializer(&__node_114))
              {
                return yy_expected_symbol(ast_node::Kind_constructor_initializer, "constructor_initializer");
              }
            (*yynode)->constructor_initializer = __node_114;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken == Token_LBRACE)
          {
            block_ast *__node_115 = 0;
            if (!parse_block(&__node_115))
              {
                return yy_expected_symbol(ast_node::Kind_block, "block");
              }
            (*yynode)->body = __node_115;
          }
        else if (yytoken == Token_SEMICOLON)
          {
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_constructor_initializer(constructor_initializer_ast **yynode)
  {
    *yynode = create<constructor_initializer_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_COLON)
      {
        if (yytoken != Token_COLON)
          return yy_expected_token(yytoken, Token_COLON, ":");
        yylex();
        if (yytoken == Token_BASE)
          {
            if (yytoken != Token_BASE)
              return yy_expected_token(yytoken, Token_BASE, "base");
            yylex();
            (*yynode)->initializer_type = constructor_initializer::type_base;
          }
        else if (yytoken == Token_THIS)
          {
            if (yytoken != Token_THIS)
              return yy_expected_token(yytoken, Token_THIS, "this");
            yylex();
            (*yynode)->initializer_type = constructor_initializer::type_this;
          }
        else
          {
            return false;
          }
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        optional_argument_list_ast *__node_116 = 0;
        if (!parse_optional_argument_list(&__node_116))
          {
            return yy_expected_symbol(ast_node::Kind_optional_argument_list, "optional_argument_list");
          }
        (*yynode)->arguments = __node_116;
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_continue_statement(continue_statement_ast **yynode)
  {
    *yynode = create<continue_statement_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_CONTINUE)
      {
        if (yytoken != Token_CONTINUE)
          return yy_expected_token(yytoken, Token_CONTINUE, "continue");
        yylex();
        if (yytoken != Token_SEMICOLON)
          return yy_expected_token(yytoken, Token_SEMICOLON, ";");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_conversion_operator_declaration(conversion_operator_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers)
  {
    *yynode = create<conversion_operator_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->start_token < (*yynode)->start_token)
      (*yynode)->start_token = modifiers->start_token;

    if (yytoken == Token_EXPLICIT
        || yytoken == Token_IMPLICIT)
      {
        if (yytoken == Token_IMPLICIT)
          {
            if (yytoken != Token_IMPLICIT)
              return yy_expected_token(yytoken, Token_IMPLICIT, "implicit");
            yylex();
            (*yynode)->conversion_type = conversion_operator_declaration::conversion_implicit;
          }
        else if (yytoken == Token_EXPLICIT)
          {
            if (yytoken != Token_EXPLICIT)
              return yy_expected_token(yytoken, Token_EXPLICIT, "explicit");
            yylex();
            (*yynode)->conversion_type = conversion_operator_declaration::conversion_explicit;
          }
        else
          {
            return false;
          }
        if (yytoken != Token_OPERATOR)
          return yy_expected_token(yytoken, Token_OPERATOR, "operator");
        yylex();
        type_ast *__node_117 = 0;
        if (!parse_type(&__node_117))
          {
            return yy_expected_symbol(ast_node::Kind_type, "type");
          }
        (*yynode)->target_type = __node_117;
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        type_ast *__node_118 = 0;
        if (!parse_type(&__node_118))
          {
            return yy_expected_symbol(ast_node::Kind_type, "type");
          }
        (*yynode)->source_type = __node_118;
        identifier_ast *__node_119 = 0;
        if (!parse_identifier(&__node_119))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->source_name = __node_119;
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        if (yytoken == Token_LBRACE)
          {
            block_ast *__node_120 = 0;
            if (!parse_block(&__node_120))
              {
                return yy_expected_symbol(ast_node::Kind_block, "block");
              }
            (*yynode)->body = __node_120;
          }
        else if (yytoken == Token_SEMICOLON)
          {
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_delegate_declaration(delegate_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers)
  {
    *yynode = create<delegate_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->start_token < (*yynode)->start_token)
      (*yynode)->start_token = modifiers->start_token;

    if (yytoken == Token_DELEGATE)
      {
        if (yytoken != Token_DELEGATE)
          return yy_expected_token(yytoken, Token_DELEGATE, "delegate");
        yylex();
        return_type_ast *__node_121 = 0;
        if (!parse_return_type(&__node_121))
          {
            return yy_expected_symbol(ast_node::Kind_return_type, "return_type");
          }
        (*yynode)->return_type = __node_121;
        identifier_ast *__node_122 = 0;
        if (!parse_identifier(&__node_122))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->delegate_name = __node_122;
        if ((yytoken == Token_LESS_THAN) && ( compatibility_mode() >= csharp20_compatibility ))
          {
            type_parameters_ast *__node_123 = 0;
            if (!parse_type_parameters(&__node_123))
              {
                return yy_expected_symbol(ast_node::Kind_type_parameters, "type_parameters");
              }
            (*yynode)->type_parameters = __node_123;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        if (yytoken == Token_BOOL
            || yytoken == Token_BYTE
            || yytoken == Token_CHAR
            || yytoken == Token_DECIMAL
            || yytoken == Token_DOUBLE
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_OBJECT
            || yytoken == Token_OUT
            || yytoken == Token_PARAMS
            || yytoken == Token_REF
            || yytoken == Token_SBYTE
            || yytoken == Token_SHORT
            || yytoken == Token_STRING
            || yytoken == Token_UINT
            || yytoken == Token_ULONG
            || yytoken == Token_USHORT
            || yytoken == Token_VOID
            || yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_LBRACKET
            || yytoken == Token_IDENTIFIER)
          {
            formal_parameter_list_ast *__node_124 = 0;
            if (!parse_formal_parameter_list(&__node_124))
              {
                return yy_expected_symbol(ast_node::Kind_formal_parameter_list, "formal_parameter_list");
              }
            (*yynode)->formal_parameters = __node_124;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        if ((yytoken == Token_WHERE) && ( compatibility_mode() >= csharp20_compatibility ))
          {
            type_parameter_constraints_clauses_ast *__node_125 = 0;
            if (!parse_type_parameter_constraints_clauses(&__node_125))
              {
                return yy_expected_symbol(ast_node::Kind_type_parameter_constraints_clauses, "type_parameter_constraints_clauses");
              }
            (*yynode)->type_parameter_constraints_clauses = __node_125;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken != Token_SEMICOLON)
          return yy_expected_token(yytoken, Token_SEMICOLON, ";");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_do_while_statement(do_while_statement_ast **yynode)
  {
    *yynode = create<do_while_statement_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_DO)
      {
        if (yytoken != Token_DO)
          return yy_expected_token(yytoken, Token_DO, "do");
        yylex();
        embedded_statement_ast *__node_126 = 0;
        if (!parse_embedded_statement(&__node_126))
          {
            return yy_expected_symbol(ast_node::Kind_embedded_statement, "embedded_statement");
          }
        (*yynode)->body = __node_126;
        if (yytoken != Token_WHILE)
          return yy_expected_token(yytoken, Token_WHILE, "while");
        yylex();
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        boolean_expression_ast *__node_127 = 0;
        if (!parse_boolean_expression(&__node_127))
          {
            return yy_expected_symbol(ast_node::Kind_boolean_expression, "boolean_expression");
          }
        (*yynode)->condition = __node_127;
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        if (yytoken != Token_SEMICOLON)
          return yy_expected_token(yytoken, Token_SEMICOLON, ";");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_embedded_statement(embedded_statement_ast **yynode)
  {
    *yynode = create<embedded_statement_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BREAK
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_CONTINUE
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DO
        || yytoken == Token_DOUBLE
        || yytoken == Token_FIXED
        || yytoken == Token_FLOAT
        || yytoken == Token_FOREACH
        || yytoken == Token_FOR
        || yytoken == Token_GOTO
        || yytoken == Token_IF
        || yytoken == Token_INT
        || yytoken == Token_LOCK
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_RETURN
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_SWITCH
        || yytoken == Token_THIS
        || yytoken == Token_THROW
        || yytoken == Token_TRY
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_UNSAFE
        || yytoken == Token_USHORT
        || yytoken == Token_USING
        || yytoken == Token_WHILE
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_LBRACE
        || yytoken == Token_SEMICOLON
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        if (yytoken == Token_LBRACE)
          {
            block_ast *__node_128 = 0;
            if (!parse_block(&__node_128))
              {
                return yy_expected_symbol(ast_node::Kind_block, "block");
              }
            (*yynode)->block = __node_128;
          }
        else if (yytoken == Token_IF)
          {
            if_statement_ast *__node_129 = 0;
            if (!parse_if_statement(&__node_129))
              {
                return yy_expected_symbol(ast_node::Kind_if_statement, "if_statement");
              }
            (*yynode)->if_statement = __node_129;
          }
        else if (yytoken == Token_SWITCH)
          {
            switch_statement_ast *__node_130 = 0;
            if (!parse_switch_statement(&__node_130))
              {
                return yy_expected_symbol(ast_node::Kind_switch_statement, "switch_statement");
              }
            (*yynode)->switch_statement = __node_130;
          }
        else if (yytoken == Token_WHILE)
          {
            while_statement_ast *__node_131 = 0;
            if (!parse_while_statement(&__node_131))
              {
                return yy_expected_symbol(ast_node::Kind_while_statement, "while_statement");
              }
            (*yynode)->while_statement = __node_131;
          }
        else if (yytoken == Token_DO)
          {
            do_while_statement_ast *__node_132 = 0;
            if (!parse_do_while_statement(&__node_132))
              {
                return yy_expected_symbol(ast_node::Kind_do_while_statement, "do_while_statement");
              }
            (*yynode)->do_while_statement = __node_132;
          }
        else if (yytoken == Token_FOR)
          {
            for_statement_ast *__node_133 = 0;
            if (!parse_for_statement(&__node_133))
              {
                return yy_expected_symbol(ast_node::Kind_for_statement, "for_statement");
              }
            (*yynode)->for_statement = __node_133;
          }
        else if (yytoken == Token_FOREACH)
          {
            foreach_statement_ast *__node_134 = 0;
            if (!parse_foreach_statement(&__node_134))
              {
                return yy_expected_symbol(ast_node::Kind_foreach_statement, "foreach_statement");
              }
            (*yynode)->foreach_statement = __node_134;
          }
        else if (yytoken == Token_BREAK)
          {
            break_statement_ast *__node_135 = 0;
            if (!parse_break_statement(&__node_135))
              {
                return yy_expected_symbol(ast_node::Kind_break_statement, "break_statement");
              }
            (*yynode)->break_statement = __node_135;
          }
        else if (yytoken == Token_CONTINUE)
          {
            continue_statement_ast *__node_136 = 0;
            if (!parse_continue_statement(&__node_136))
              {
                return yy_expected_symbol(ast_node::Kind_continue_statement, "continue_statement");
              }
            (*yynode)->continue_statement = __node_136;
          }
        else if (yytoken == Token_GOTO)
          {
            goto_statement_ast *__node_137 = 0;
            if (!parse_goto_statement(&__node_137))
              {
                return yy_expected_symbol(ast_node::Kind_goto_statement, "goto_statement");
              }
            (*yynode)->goto_statement = __node_137;
          }
        else if (yytoken == Token_RETURN)
          {
            return_statement_ast *__node_138 = 0;
            if (!parse_return_statement(&__node_138))
              {
                return yy_expected_symbol(ast_node::Kind_return_statement, "return_statement");
              }
            (*yynode)->return_statement = __node_138;
          }
        else if (yytoken == Token_THROW)
          {
            throw_statement_ast *__node_139 = 0;
            if (!parse_throw_statement(&__node_139))
              {
                return yy_expected_symbol(ast_node::Kind_throw_statement, "throw_statement");
              }
            (*yynode)->throw_statement = __node_139;
          }
        else if (yytoken == Token_TRY)
          {
            try_statement_ast *__node_140 = 0;
            if (!parse_try_statement(&__node_140))
              {
                return yy_expected_symbol(ast_node::Kind_try_statement, "try_statement");
              }
            (*yynode)->try_statement = __node_140;
          }
        else if (yytoken == Token_LOCK)
          {
            lock_statement_ast *__node_141 = 0;
            if (!parse_lock_statement(&__node_141))
              {
                return yy_expected_symbol(ast_node::Kind_lock_statement, "lock_statement");
              }
            (*yynode)->lock_statement = __node_141;
          }
        else if (yytoken == Token_USING)
          {
            using_statement_ast *__node_142 = 0;
            if (!parse_using_statement(&__node_142))
              {
                return yy_expected_symbol(ast_node::Kind_using_statement, "using_statement");
              }
            (*yynode)->using_statement = __node_142;
          }
        else if (yytoken == Token_SEMICOLON)
          {
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
          }
        else if ((yytoken == Token_CHECKED) && ( LA(2).kind == Token_LBRACE ))
          {
            checked_statement_ast *__node_143 = 0;
            if (!parse_checked_statement(&__node_143))
              {
                return yy_expected_symbol(ast_node::Kind_checked_statement, "checked_statement");
              }
            (*yynode)->checked_statement = __node_143;
          }
        else if ((yytoken == Token_UNCHECKED) && ( LA(2).kind == Token_LBRACE ))
          {
            unchecked_statement_ast *__node_144 = 0;
            if (!parse_unchecked_statement(&__node_144))
              {
                return yy_expected_symbol(ast_node::Kind_unchecked_statement, "unchecked_statement");
              }
            (*yynode)->unchecked_statement = __node_144;
          }
        else if ((yytoken == Token_YIELD) && ( LA(2).kind == Token_RETURN || LA(2).kind == Token_BREAK ))
          {
            yield_statement_ast *__node_145 = 0;
            if (!parse_yield_statement(&__node_145))
              {
                return yy_expected_symbol(ast_node::Kind_yield_statement, "yield_statement");
              }
            (*yynode)->yield_statement = __node_145;
          }
        else if (yytoken == Token_BASE
                 || yytoken == Token_BOOL
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR
                 || yytoken == Token_CHECKED
                 || yytoken == Token_DECIMAL
                 || yytoken == Token_DEFAULT
                 || yytoken == Token_DELEGATE
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_LONG
                 || yytoken == Token_NEW
                 || yytoken == Token_OBJECT
                 || yytoken == Token_SBYTE
                 || yytoken == Token_SHORT
                 || yytoken == Token_SIZEOF
                 || yytoken == Token_STRING
                 || yytoken == Token_THIS
                 || yytoken == Token_TYPEOF
                 || yytoken == Token_UINT
                 || yytoken == Token_ULONG
                 || yytoken == Token_UNCHECKED
                 || yytoken == Token_USHORT
                 || yytoken == Token_ADD
                 || yytoken == Token_ALIAS
                 || yytoken == Token_GET
                 || yytoken == Token_GLOBAL
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_REMOVE
                 || yytoken == Token_SET
                 || yytoken == Token_VALUE
                 || yytoken == Token_WHERE
                 || yytoken == Token_YIELD
                 || yytoken == Token_ASSEMBLY
                 || yytoken == Token_LPAREN
                 || yytoken == Token_BANG
                 || yytoken == Token_TILDE
                 || yytoken == Token_INCREMENT
                 || yytoken == Token_DECREMENT
                 || yytoken == Token_PLUS
                 || yytoken == Token_MINUS
                 || yytoken == Token_STAR
                 || yytoken == Token_BIT_AND
                 || yytoken == Token_TRUE
                 || yytoken == Token_FALSE
                 || yytoken == Token_NULL
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_REAL_LITERAL
                 || yytoken == Token_CHARACTER_LITERAL
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_IDENTIFIER)
          {
            statement_expression_ast *__node_146 = 0;
            if (!parse_statement_expression(&__node_146))
              {
                return yy_expected_symbol(ast_node::Kind_statement_expression, "statement_expression");
              }
            (*yynode)->expression_statement = __node_146;
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
          }
        else if (yytoken == Token_UNSAFE)
          {
            unsafe_statement_ast *__node_147 = 0;
            if (!parse_unsafe_statement(&__node_147))
              {
                return yy_expected_symbol(ast_node::Kind_unsafe_statement, "unsafe_statement");
              }
            (*yynode)->unsafe_statement = __node_147;
          }
        else if (yytoken == Token_FIXED)
          {
            fixed_statement_ast *__node_148 = 0;
            if (!parse_fixed_statement(&__node_148))
              {
                return yy_expected_symbol(ast_node::Kind_fixed_statement, "fixed_statement");
              }
            (*yynode)->fixed_statement = __node_148;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_enum_base(enum_base_ast **yynode)
  {
    *yynode = create<enum_base_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_COLON)
      {
        if (yytoken != Token_COLON)
          return yy_expected_token(yytoken, Token_COLON, ":");
        yylex();
        integral_type_ast *__node_149 = 0;
        if (!parse_integral_type(&__node_149))
          {
            return yy_expected_symbol(ast_node::Kind_integral_type, "integral_type");
          }
        (*yynode)->integral_type = __node_149;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_enum_body(enum_body_ast **yynode)
  {
    *yynode = create<enum_body_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LBRACE)
      {
        if (yytoken != Token_LBRACE)
          return yy_expected_token(yytoken, Token_LBRACE, "{");
        yylex();
        if (yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_LBRACKET
            || yytoken == Token_IDENTIFIER)
          {
            enum_member_declaration_ast *__node_150 = 0;
            if (!parse_enum_member_declaration(&__node_150))
              {
                return yy_expected_symbol(ast_node::Kind_enum_member_declaration, "enum_member_declaration");
              }
            (*yynode)->member_declaration_sequence = snoc((*yynode)->member_declaration_sequence, __node_150, memory_pool);
            while (yytoken == Token_COMMA)
              {
                if (LA(2).kind == Token_RBRACE)
                  break;
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
                enum_member_declaration_ast *__node_151 = 0;
                if (!parse_enum_member_declaration(&__node_151))
                  {
                    return yy_expected_symbol(ast_node::Kind_enum_member_declaration, "enum_member_declaration");
                  }
                (*yynode)->member_declaration_sequence = snoc((*yynode)->member_declaration_sequence, __node_151, memory_pool);
              }
            if (yytoken == Token_COMMA)
              {
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
              }
            else if (true /*epsilon*/)
            {}
            else
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
        if (yytoken != Token_RBRACE)
          return yy_expected_token(yytoken, Token_RBRACE, "}");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_enum_declaration(enum_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers)
  {
    *yynode = create<enum_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->start_token < (*yynode)->start_token)
      (*yynode)->start_token = modifiers->start_token;

    if (yytoken == Token_ENUM)
      {
        if (yytoken != Token_ENUM)
          return yy_expected_token(yytoken, Token_ENUM, "enum");
        yylex();
        identifier_ast *__node_152 = 0;
        if (!parse_identifier(&__node_152))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->enum_name = __node_152;
        if (yytoken == Token_COLON)
          {
            enum_base_ast *__node_153 = 0;
            if (!parse_enum_base(&__node_153))
              {
                return yy_expected_symbol(ast_node::Kind_enum_base, "enum_base");
              }
            (*yynode)->enum_base = __node_153;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        enum_body_ast *__node_154 = 0;
        if (!parse_enum_body(&__node_154))
          {
            return yy_expected_symbol(ast_node::Kind_enum_body, "enum_body");
          }
        (*yynode)->body = __node_154;
        if (yytoken == Token_SEMICOLON)
          {
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_enum_member_declaration(enum_member_declaration_ast **yynode)
  {
    *yynode = create<enum_member_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LBRACKET
        || yytoken == Token_IDENTIFIER)
      {
        while (yytoken == Token_LBRACKET)
          {
            attribute_section_ast *__node_155 = 0;
            if (!parse_attribute_section(&__node_155))
              {
                return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
              }
            (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_155, memory_pool);
          }
        identifier_ast *__node_156 = 0;
        if (!parse_identifier(&__node_156))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->member_name = __node_156;
        if (yytoken == Token_ASSIGN)
          {
            if (yytoken != Token_ASSIGN)
              return yy_expected_token(yytoken, Token_ASSIGN, "=");
            yylex();
            constant_expression_ast *__node_157 = 0;
            if (!parse_constant_expression(&__node_157))
              {
                return yy_expected_symbol(ast_node::Kind_constant_expression, "constant_expression");
              }
            (*yynode)->constant_expression = __node_157;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_equality_expression(equality_expression_ast **yynode)
  {
    *yynode = create<equality_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        relational_expression_ast *__node_158 = 0;
        if (!parse_relational_expression(&__node_158))
          {
            return yy_expected_symbol(ast_node::Kind_relational_expression, "relational_expression");
          }
        (*yynode)->expression = __node_158;
        while (yytoken == Token_EQUAL
               || yytoken == Token_NOT_EQUAL)
          {
            equality_expression_rest_ast *__node_159 = 0;
            if (!parse_equality_expression_rest(&__node_159))
              {
                return yy_expected_symbol(ast_node::Kind_equality_expression_rest, "equality_expression_rest");
              }
            (*yynode)->additional_expression_sequence = snoc((*yynode)->additional_expression_sequence, __node_159, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_equality_expression_rest(equality_expression_rest_ast **yynode)
  {
    *yynode = create<equality_expression_rest_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_EQUAL
        || yytoken == Token_NOT_EQUAL)
      {
        if (yytoken == Token_EQUAL)
          {
            if (yytoken != Token_EQUAL)
              return yy_expected_token(yytoken, Token_EQUAL, "==");
            yylex();
            (*yynode)->equality_operator = equality_expression_rest::op_equal;
          }
        else if (yytoken == Token_NOT_EQUAL)
          {
            if (yytoken != Token_NOT_EQUAL)
              return yy_expected_token(yytoken, Token_NOT_EQUAL, "!=");
            yylex();
            (*yynode)->equality_operator = equality_expression_rest::op_not_equal;
          }
        else
          {
            return false;
          }
        relational_expression_ast *__node_160 = 0;
        if (!parse_relational_expression(&__node_160))
          {
            return yy_expected_symbol(ast_node::Kind_relational_expression, "relational_expression");
          }
        (*yynode)->expression = __node_160;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_event_accessor_declarations(event_accessor_declarations_ast **yynode)
  {
    *yynode = create<event_accessor_declarations_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ADD
        || yytoken == Token_REMOVE
        || yytoken == Token_LBRACKET)
      {
        while (yytoken == Token_LBRACKET)
          {
            attribute_section_ast *__node_161 = 0;
            if (!parse_attribute_section(&__node_161))
              {
                return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
              }
            (*yynode)->attributes_accessor1_sequence = snoc((*yynode)->attributes_accessor1_sequence, __node_161, memory_pool);
          }
        if (yytoken == Token_ADD)
          {
            if (yytoken != Token_ADD)
              return yy_expected_token(yytoken, Token_ADD, "add");
            yylex();
            block_ast *__node_162 = 0;
            if (!parse_block(&__node_162))
              {
                return yy_expected_symbol(ast_node::Kind_block, "block");
              }
            (*yynode)->accessor1_body = __node_162;
            while (yytoken == Token_LBRACKET)
              {
                attribute_section_ast *__node_163 = 0;
                if (!parse_attribute_section(&__node_163))
                  {
                    return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
                  }
                (*yynode)->attributes_accessor2_sequence = snoc((*yynode)->attributes_accessor2_sequence, __node_163, memory_pool);
              }
            if (yytoken != Token_REMOVE)
              return yy_expected_token(yytoken, Token_REMOVE, "remove");
            yylex();
            block_ast *__node_164 = 0;
            if (!parse_block(&__node_164))
              {
                return yy_expected_symbol(ast_node::Kind_block, "block");
              }
            (*yynode)->accessor2_body = __node_164;
            (*yynode)->order = event_accessor_declarations::order_add_remove;
          }
        else if (yytoken == Token_REMOVE)
          {
            if (yytoken != Token_REMOVE)
              return yy_expected_token(yytoken, Token_REMOVE, "remove");
            yylex();
            block_ast *__node_165 = 0;
            if (!parse_block(&__node_165))
              {
                return yy_expected_symbol(ast_node::Kind_block, "block");
              }
            (*yynode)->accessor1_body = __node_165;
            while (yytoken == Token_LBRACKET)
              {
                attribute_section_ast *__node_166 = 0;
                if (!parse_attribute_section(&__node_166))
                  {
                    return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
                  }
                (*yynode)->attributes_accessor2_sequence = snoc((*yynode)->attributes_accessor2_sequence, __node_166, memory_pool);
              }
            if (yytoken != Token_ADD)
              return yy_expected_token(yytoken, Token_ADD, "add");
            yylex();
            block_ast *__node_167 = 0;
            if (!parse_block(&__node_167))
              {
                return yy_expected_symbol(ast_node::Kind_block, "block");
              }
            (*yynode)->accessor2_body = __node_167;
            (*yynode)->order = event_accessor_declarations::order_remove_add;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_event_declaration(event_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers)
  {
    *yynode = create<event_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->start_token < (*yynode)->start_token)
      (*yynode)->start_token = modifiers->start_token;

    if (yytoken == Token_EVENT)
      {
        if (yytoken != Token_EVENT)
          return yy_expected_token(yytoken, Token_EVENT, "event");
        yylex();
        type_ast *__node_168 = 0;
        if (!parse_type(&__node_168))
          {
            return yy_expected_symbol(ast_node::Kind_type, "type");
          }
        (*yynode)->type = __node_168;
        if ((yytoken == Token_ADD
             || yytoken == Token_ALIAS
             || yytoken == Token_GET
             || yytoken == Token_GLOBAL
             || yytoken == Token_PARTIAL
             || yytoken == Token_REMOVE
             || yytoken == Token_SET
             || yytoken == Token_VALUE
             || yytoken == Token_WHERE
             || yytoken == Token_YIELD
             || yytoken == Token_ASSEMBLY
             || yytoken == Token_IDENTIFIER) && ( (LA(2).kind == Token_COMMA) || (LA(2).kind == Token_ASSIGN)
                                                  || (LA(2).kind == Token_SEMICOLON)
                                                ))
          {
            variable_declarator_ast *__node_169 = 0;
            if (!parse_variable_declarator(&__node_169))
              {
                return yy_expected_symbol(ast_node::Kind_variable_declarator, "variable_declarator");
              }
            (*yynode)->variable_declarator_sequence = snoc((*yynode)->variable_declarator_sequence, __node_169, memory_pool);
            while (yytoken == Token_COMMA)
              {
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
                variable_declarator_ast *__node_170 = 0;
                if (!parse_variable_declarator(&__node_170))
                  {
                    return yy_expected_symbol(ast_node::Kind_variable_declarator, "variable_declarator");
                  }
                (*yynode)->variable_declarator_sequence = snoc((*yynode)->variable_declarator_sequence, __node_170, memory_pool);
              }
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
          }
        else if (yytoken == Token_ADD
                 || yytoken == Token_ALIAS
                 || yytoken == Token_GET
                 || yytoken == Token_GLOBAL
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_REMOVE
                 || yytoken == Token_SET
                 || yytoken == Token_VALUE
                 || yytoken == Token_WHERE
                 || yytoken == Token_YIELD
                 || yytoken == Token_ASSEMBLY
                 || yytoken == Token_IDENTIFIER)
          {
            type_name_ast *__node_171 = 0;
            if (!parse_type_name(&__node_171))
              {
                return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
              }
            (*yynode)->event_name = __node_171;
            if (yytoken != Token_LPAREN)
              return yy_expected_token(yytoken, Token_LPAREN, "(");
            yylex();
            event_accessor_declarations_ast *__node_172 = 0;
            if (!parse_event_accessor_declarations(&__node_172))
              {
                return yy_expected_symbol(ast_node::Kind_event_accessor_declarations, "event_accessor_declarations");
              }
            (*yynode)->event_accessor_declarations = __node_172;
            if (yytoken != Token_RPAREN)
              return yy_expected_token(yytoken, Token_RPAREN, ")");
            yylex();
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_expression(expression_ast **yynode)
  {
    *yynode = create<expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        conditional_expression_ast *__node_173 = 0;
        if (!parse_conditional_expression(&__node_173))
          {
            return yy_expected_symbol(ast_node::Kind_conditional_expression, "conditional_expression");
          }
        (*yynode)->conditional_expression = __node_173;
        if (yytoken == Token_ASSIGN
            || yytoken == Token_PLUS_ASSIGN
            || yytoken == Token_MINUS_ASSIGN
            || yytoken == Token_STAR_ASSIGN
            || yytoken == Token_SLASH_ASSIGN
            || yytoken == Token_BIT_AND_ASSIGN
            || yytoken == Token_BIT_OR_ASSIGN
            || yytoken == Token_BIT_XOR_ASSIGN
            || yytoken == Token_REMAINDER_ASSIGN
            || yytoken == Token_LSHIFT_ASSIGN
            || yytoken == Token_RSHIFT_ASSIGN)
          {
            if (yytoken == Token_ASSIGN)
              {
                if (yytoken != Token_ASSIGN)
                  return yy_expected_token(yytoken, Token_ASSIGN, "=");
                yylex();
                (*yynode)->assignment_operator = expression::op_assign;
              }
            else if (yytoken == Token_PLUS_ASSIGN)
              {
                if (yytoken != Token_PLUS_ASSIGN)
                  return yy_expected_token(yytoken, Token_PLUS_ASSIGN, "+=");
                yylex();
                (*yynode)->assignment_operator = expression::op_plus_assign;
              }
            else if (yytoken == Token_MINUS_ASSIGN)
              {
                if (yytoken != Token_MINUS_ASSIGN)
                  return yy_expected_token(yytoken, Token_MINUS_ASSIGN, "-=");
                yylex();
                (*yynode)->assignment_operator = expression::op_minus_assign;
              }
            else if (yytoken == Token_STAR_ASSIGN)
              {
                if (yytoken != Token_STAR_ASSIGN)
                  return yy_expected_token(yytoken, Token_STAR_ASSIGN, "*=");
                yylex();
                (*yynode)->assignment_operator = expression::op_star_assign;
              }
            else if (yytoken == Token_SLASH_ASSIGN)
              {
                if (yytoken != Token_SLASH_ASSIGN)
                  return yy_expected_token(yytoken, Token_SLASH_ASSIGN, "/=");
                yylex();
                (*yynode)->assignment_operator = expression::op_slash_assign;
              }
            else if (yytoken == Token_REMAINDER_ASSIGN)
              {
                if (yytoken != Token_REMAINDER_ASSIGN)
                  return yy_expected_token(yytoken, Token_REMAINDER_ASSIGN, "%=");
                yylex();
                (*yynode)->assignment_operator = expression::op_remainder_assign;
              }
            else if (yytoken == Token_BIT_AND_ASSIGN)
              {
                if (yytoken != Token_BIT_AND_ASSIGN)
                  return yy_expected_token(yytoken, Token_BIT_AND_ASSIGN, "&=");
                yylex();
                (*yynode)->assignment_operator = expression::op_bit_and_assign;
              }
            else if (yytoken == Token_BIT_OR_ASSIGN)
              {
                if (yytoken != Token_BIT_OR_ASSIGN)
                  return yy_expected_token(yytoken, Token_BIT_OR_ASSIGN, "|=");
                yylex();
                (*yynode)->assignment_operator = expression::op_bit_or_assign;
              }
            else if (yytoken == Token_BIT_XOR_ASSIGN)
              {
                if (yytoken != Token_BIT_XOR_ASSIGN)
                  return yy_expected_token(yytoken, Token_BIT_XOR_ASSIGN, "^=");
                yylex();
                (*yynode)->assignment_operator = expression::op_bit_xor_assign;
              }
            else if (yytoken == Token_LSHIFT_ASSIGN)
              {
                if (yytoken != Token_LSHIFT_ASSIGN)
                  return yy_expected_token(yytoken, Token_LSHIFT_ASSIGN, "<<=");
                yylex();
                (*yynode)->assignment_operator = expression::op_lshift_assign;
              }
            else if (yytoken == Token_RSHIFT_ASSIGN)
              {
                if (yytoken != Token_RSHIFT_ASSIGN)
                  return yy_expected_token(yytoken, Token_RSHIFT_ASSIGN, ">>=");
                yylex();
                (*yynode)->assignment_operator = expression::op_rshift_assign;
              }
            else
              {
                return false;
              }
            expression_ast *__node_174 = 0;
            if (!parse_expression(&__node_174))
              {
                return yy_expected_symbol(ast_node::Kind_expression, "expression");
              }
            (*yynode)->assignment_expression = __node_174;
          }
        else if (true /*epsilon*/)
          {
            (*yynode)->assignment_operator = expression::no_assignment;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_extern_alias_directive(extern_alias_directive_ast **yynode)
  {
    *yynode = create<extern_alias_directive_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_EXTERN)
      {
        if (yytoken != Token_EXTERN)
          return yy_expected_token(yytoken, Token_EXTERN, "extern");
        yylex();
        if (yytoken != Token_ALIAS)
          return yy_expected_token(yytoken, Token_ALIAS, "alias");
        yylex();
        identifier_ast *__node_175 = 0;
        if (!parse_identifier(&__node_175))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->identifier = __node_175;
        if (yytoken != Token_SEMICOLON)
          return yy_expected_token(yytoken, Token_SEMICOLON, ";");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_finalizer_declaration(finalizer_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers)
  {
    *yynode = create<finalizer_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->start_token < (*yynode)->start_token)
      (*yynode)->start_token = modifiers->start_token;

    if (yytoken == Token_TILDE)
      {
        if (yytoken != Token_TILDE)
          return yy_expected_token(yytoken, Token_TILDE, "~");
        yylex();
        identifier_ast *__node_176 = 0;
        if (!parse_identifier(&__node_176))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->class_name = __node_176;
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        if (yytoken == Token_LBRACE)
          {
            block_ast *__node_177 = 0;
            if (!parse_block(&__node_177))
              {
                return yy_expected_symbol(ast_node::Kind_block, "block");
              }
            (*yynode)->finalizer_body = __node_177;
          }
        else if (yytoken == Token_SEMICOLON)
          {
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_fixed_pointer_declarator(fixed_pointer_declarator_ast **yynode)
  {
    *yynode = create<fixed_pointer_declarator_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        identifier_ast *__node_178 = 0;
        if (!parse_identifier(&__node_178))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->pointer_name = __node_178;
        if (yytoken != Token_ASSIGN)
          return yy_expected_token(yytoken, Token_ASSIGN, "=");
        yylex();
        expression_ast *__node_179 = 0;
        if (!parse_expression(&__node_179))
          {
            return yy_expected_symbol(ast_node::Kind_expression, "expression");
          }
        (*yynode)->initializer = __node_179;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_fixed_statement(fixed_statement_ast **yynode)
  {
    *yynode = create<fixed_statement_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_FIXED)
      {
        if (yytoken != Token_FIXED)
          return yy_expected_token(yytoken, Token_FIXED, "fixed");
        yylex();
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        pointer_type_ast *__node_180 = 0;
        if (!parse_pointer_type(&__node_180))
          {
            return yy_expected_symbol(ast_node::Kind_pointer_type, "pointer_type");
          }
        (*yynode)->pointer_type = __node_180;
        fixed_pointer_declarator_ast *__node_181 = 0;
        if (!parse_fixed_pointer_declarator(&__node_181))
          {
            return yy_expected_symbol(ast_node::Kind_fixed_pointer_declarator, "fixed_pointer_declarator");
          }
        (*yynode)->fixed_pointer_declarator = __node_181;
        while (yytoken == Token_COMMA)
          {
            if (yytoken != Token_COMMA)
              return yy_expected_token(yytoken, Token_COMMA, ",");
            yylex();
            fixed_pointer_declarator_ast *__node_182 = 0;
            if (!parse_fixed_pointer_declarator(&__node_182))
              {
                return yy_expected_symbol(ast_node::Kind_fixed_pointer_declarator, "fixed_pointer_declarator");
              }
            (*yynode)->fixed_pointer_declarator = __node_182;
          }
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        embedded_statement_ast *__node_183 = 0;
        if (!parse_embedded_statement(&__node_183))
          {
            return yy_expected_symbol(ast_node::Kind_embedded_statement, "embedded_statement");
          }
        (*yynode)->body = __node_183;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_floating_point_type(floating_point_type_ast **yynode)
  {
    *yynode = create<floating_point_type_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT)
      {
        if (yytoken == Token_FLOAT)
          {
            if (yytoken != Token_FLOAT)
              return yy_expected_token(yytoken, Token_FLOAT, "float");
            yylex();
            (*yynode)->type = floating_point_type::type_float;
          }
        else if (yytoken == Token_DOUBLE)
          {
            if (yytoken != Token_DOUBLE)
              return yy_expected_token(yytoken, Token_DOUBLE, "double");
            yylex();
            (*yynode)->type = floating_point_type::type_double;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_for_control(for_control_ast **yynode)
  {
    *yynode = create<for_control_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_VOID
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_SEMICOLON
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        if ((yytoken == Token_BOOL
             || yytoken == Token_BYTE
             || yytoken == Token_CHAR
             || yytoken == Token_DECIMAL
             || yytoken == Token_DOUBLE
             || yytoken == Token_FLOAT
             || yytoken == Token_INT
             || yytoken == Token_LONG
             || yytoken == Token_OBJECT
             || yytoken == Token_SBYTE
             || yytoken == Token_SHORT
             || yytoken == Token_STRING
             || yytoken == Token_UINT
             || yytoken == Token_ULONG
             || yytoken == Token_USHORT
             || yytoken == Token_VOID
             || yytoken == Token_ADD
             || yytoken == Token_ALIAS
             || yytoken == Token_GET
             || yytoken == Token_GLOBAL
             || yytoken == Token_PARTIAL
             || yytoken == Token_REMOVE
             || yytoken == Token_SET
             || yytoken == Token_VALUE
             || yytoken == Token_WHERE
             || yytoken == Token_YIELD
             || yytoken == Token_ASSEMBLY
             || yytoken == Token_IDENTIFIER) && ( lookahead_is_local_variable_declaration() == true ))
          {
            local_variable_declaration_ast *__node_184 = 0;
            if (!parse_local_variable_declaration(&__node_184))
              {
                return yy_expected_symbol(ast_node::Kind_local_variable_declaration, "local_variable_declaration");
              }
            (*yynode)->local_variable_declaration = __node_184;
          }
        else if (yytoken == Token_BASE
                 || yytoken == Token_BOOL
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR
                 || yytoken == Token_CHECKED
                 || yytoken == Token_DECIMAL
                 || yytoken == Token_DEFAULT
                 || yytoken == Token_DELEGATE
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_LONG
                 || yytoken == Token_NEW
                 || yytoken == Token_OBJECT
                 || yytoken == Token_SBYTE
                 || yytoken == Token_SHORT
                 || yytoken == Token_SIZEOF
                 || yytoken == Token_STRING
                 || yytoken == Token_THIS
                 || yytoken == Token_TYPEOF
                 || yytoken == Token_UINT
                 || yytoken == Token_ULONG
                 || yytoken == Token_UNCHECKED
                 || yytoken == Token_USHORT
                 || yytoken == Token_ADD
                 || yytoken == Token_ALIAS
                 || yytoken == Token_GET
                 || yytoken == Token_GLOBAL
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_REMOVE
                 || yytoken == Token_SET
                 || yytoken == Token_VALUE
                 || yytoken == Token_WHERE
                 || yytoken == Token_YIELD
                 || yytoken == Token_ASSEMBLY
                 || yytoken == Token_LPAREN
                 || yytoken == Token_BANG
                 || yytoken == Token_TILDE
                 || yytoken == Token_INCREMENT
                 || yytoken == Token_DECREMENT
                 || yytoken == Token_PLUS
                 || yytoken == Token_MINUS
                 || yytoken == Token_STAR
                 || yytoken == Token_BIT_AND
                 || yytoken == Token_TRUE
                 || yytoken == Token_FALSE
                 || yytoken == Token_NULL
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_REAL_LITERAL
                 || yytoken == Token_CHARACTER_LITERAL
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_IDENTIFIER)
          {
            statement_expression_ast *__node_185 = 0;
            if (!parse_statement_expression(&__node_185))
              {
                return yy_expected_symbol(ast_node::Kind_statement_expression, "statement_expression");
              }
            (*yynode)->statement_expression_sequence = snoc((*yynode)->statement_expression_sequence, __node_185, memory_pool);
            while (yytoken == Token_COMMA)
              {
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
                statement_expression_ast *__node_186 = 0;
                if (!parse_statement_expression(&__node_186))
                  {
                    return yy_expected_symbol(ast_node::Kind_statement_expression, "statement_expression");
                  }
                (*yynode)->statement_expression_sequence = snoc((*yynode)->statement_expression_sequence, __node_186, memory_pool);
              }
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken != Token_SEMICOLON)
          return yy_expected_token(yytoken, Token_SEMICOLON, ";");
        yylex();
        if (yytoken == Token_BASE
            || yytoken == Token_BOOL
            || yytoken == Token_BYTE
            || yytoken == Token_CHAR
            || yytoken == Token_CHECKED
            || yytoken == Token_DECIMAL
            || yytoken == Token_DEFAULT
            || yytoken == Token_DELEGATE
            || yytoken == Token_DOUBLE
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_NEW
            || yytoken == Token_OBJECT
            || yytoken == Token_SBYTE
            || yytoken == Token_SHORT
            || yytoken == Token_SIZEOF
            || yytoken == Token_STRING
            || yytoken == Token_THIS
            || yytoken == Token_TYPEOF
            || yytoken == Token_UINT
            || yytoken == Token_ULONG
            || yytoken == Token_UNCHECKED
            || yytoken == Token_USHORT
            || yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_LPAREN
            || yytoken == Token_BANG
            || yytoken == Token_TILDE
            || yytoken == Token_INCREMENT
            || yytoken == Token_DECREMENT
            || yytoken == Token_PLUS
            || yytoken == Token_MINUS
            || yytoken == Token_STAR
            || yytoken == Token_BIT_AND
            || yytoken == Token_TRUE
            || yytoken == Token_FALSE
            || yytoken == Token_NULL
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_REAL_LITERAL
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_IDENTIFIER)
          {
            boolean_expression_ast *__node_187 = 0;
            if (!parse_boolean_expression(&__node_187))
              {
                return yy_expected_symbol(ast_node::Kind_boolean_expression, "boolean_expression");
              }
            (*yynode)->for_condition = __node_187;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken != Token_SEMICOLON)
          return yy_expected_token(yytoken, Token_SEMICOLON, ";");
        yylex();
        if (yytoken == Token_BASE
            || yytoken == Token_BOOL
            || yytoken == Token_BYTE
            || yytoken == Token_CHAR
            || yytoken == Token_CHECKED
            || yytoken == Token_DECIMAL
            || yytoken == Token_DEFAULT
            || yytoken == Token_DELEGATE
            || yytoken == Token_DOUBLE
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_NEW
            || yytoken == Token_OBJECT
            || yytoken == Token_SBYTE
            || yytoken == Token_SHORT
            || yytoken == Token_SIZEOF
            || yytoken == Token_STRING
            || yytoken == Token_THIS
            || yytoken == Token_TYPEOF
            || yytoken == Token_UINT
            || yytoken == Token_ULONG
            || yytoken == Token_UNCHECKED
            || yytoken == Token_USHORT
            || yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_LPAREN
            || yytoken == Token_BANG
            || yytoken == Token_TILDE
            || yytoken == Token_INCREMENT
            || yytoken == Token_DECREMENT
            || yytoken == Token_PLUS
            || yytoken == Token_MINUS
            || yytoken == Token_STAR
            || yytoken == Token_BIT_AND
            || yytoken == Token_TRUE
            || yytoken == Token_FALSE
            || yytoken == Token_NULL
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_REAL_LITERAL
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_IDENTIFIER)
          {
            statement_expression_ast *__node_188 = 0;
            if (!parse_statement_expression(&__node_188))
              {
                return yy_expected_symbol(ast_node::Kind_statement_expression, "statement_expression");
              }
            (*yynode)->for_iterator_sequence = snoc((*yynode)->for_iterator_sequence, __node_188, memory_pool);
            while (yytoken == Token_COMMA)
              {
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
                statement_expression_ast *__node_189 = 0;
                if (!parse_statement_expression(&__node_189))
                  {
                    return yy_expected_symbol(ast_node::Kind_statement_expression, "statement_expression");
                  }
                (*yynode)->for_iterator_sequence = snoc((*yynode)->for_iterator_sequence, __node_189, memory_pool);
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_for_statement(for_statement_ast **yynode)
  {
    *yynode = create<for_statement_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_FOR)
      {
        if (yytoken != Token_FOR)
          return yy_expected_token(yytoken, Token_FOR, "for");
        yylex();
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        for_control_ast *__node_190 = 0;
        if (!parse_for_control(&__node_190))
          {
            return yy_expected_symbol(ast_node::Kind_for_control, "for_control");
          }
        (*yynode)->for_control = __node_190;
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        embedded_statement_ast *__node_191 = 0;
        if (!parse_embedded_statement(&__node_191))
          {
            return yy_expected_symbol(ast_node::Kind_embedded_statement, "embedded_statement");
          }
        (*yynode)->for_body = __node_191;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_foreach_statement(foreach_statement_ast **yynode)
  {
    *yynode = create<foreach_statement_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_FOREACH)
      {
        if (yytoken != Token_FOREACH)
          return yy_expected_token(yytoken, Token_FOREACH, "foreach");
        yylex();
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        type_ast *__node_192 = 0;
        if (!parse_type(&__node_192))
          {
            return yy_expected_symbol(ast_node::Kind_type, "type");
          }
        (*yynode)->variable_type = __node_192;
        identifier_ast *__node_193 = 0;
        if (!parse_identifier(&__node_193))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->variable_name = __node_193;
        if (yytoken != Token_IN)
          return yy_expected_token(yytoken, Token_IN, "in");
        yylex();
        expression_ast *__node_194 = 0;
        if (!parse_expression(&__node_194))
          {
            return yy_expected_symbol(ast_node::Kind_expression, "expression");
          }
        (*yynode)->collection = __node_194;
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        embedded_statement_ast *__node_195 = 0;
        if (!parse_embedded_statement(&__node_195))
          {
            return yy_expected_symbol(ast_node::Kind_embedded_statement, "embedded_statement");
          }
        (*yynode)->body = __node_195;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_formal_parameter(formal_parameter_ast **yynode, bool* parameter_array_occurred)
  {
    *yynode = create<formal_parameter_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_DECIMAL
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_OBJECT
        || yytoken == Token_OUT
        || yytoken == Token_PARAMS
        || yytoken == Token_REF
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_STRING
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT
        || yytoken == Token_VOID
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LBRACKET
        || yytoken == Token_IDENTIFIER)
      {
        while (yytoken == Token_LBRACKET)
          {
            attribute_section_ast *__node_196 = 0;
            if (!parse_attribute_section(&__node_196))
              {
                return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
              }
            (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_196, memory_pool);
          }
        if (yytoken == Token_PARAMS)
          {
            parameter_array_ast *__node_197 = 0;
            if (!parse_parameter_array(&__node_197))
              {
                return yy_expected_symbol(ast_node::Kind_parameter_array, "parameter_array");
              }
            (*yynode)->parameter_array = __node_197;
            *parameter_array_occurred = true;
          }
        else if (yytoken == Token_BOOL
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR
                 || yytoken == Token_DECIMAL
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_LONG
                 || yytoken == Token_OBJECT
                 || yytoken == Token_OUT
                 || yytoken == Token_REF
                 || yytoken == Token_SBYTE
                 || yytoken == Token_SHORT
                 || yytoken == Token_STRING
                 || yytoken == Token_UINT
                 || yytoken == Token_ULONG
                 || yytoken == Token_USHORT
                 || yytoken == Token_VOID
                 || yytoken == Token_ADD
                 || yytoken == Token_ALIAS
                 || yytoken == Token_GET
                 || yytoken == Token_GLOBAL
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_REMOVE
                 || yytoken == Token_SET
                 || yytoken == Token_VALUE
                 || yytoken == Token_WHERE
                 || yytoken == Token_YIELD
                 || yytoken == Token_ASSEMBLY
                 || yytoken == Token_IDENTIFIER)
          {
            if (yytoken == Token_OUT
                || yytoken == Token_REF)
              {
                parameter_modifier_ast *__node_198 = 0;
                if (!parse_parameter_modifier(&__node_198))
                  {
                    return yy_expected_symbol(ast_node::Kind_parameter_modifier, "parameter_modifier");
                  }
                (*yynode)->modifier = __node_198;
              }
            else if (true /*epsilon*/)
            {}
            else
              {
                return false;
              }
            type_ast *__node_199 = 0;
            if (!parse_type(&__node_199))
              {
                return yy_expected_symbol(ast_node::Kind_type, "type");
              }
            (*yynode)->type = __node_199;
            identifier_ast *__node_200 = 0;
            if (!parse_identifier(&__node_200))
              {
                return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
              }
            (*yynode)->variable_name = __node_200;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_formal_parameter_list(formal_parameter_list_ast **yynode)
  {
    *yynode = create<formal_parameter_list_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_DECIMAL
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_OBJECT
        || yytoken == Token_OUT
        || yytoken == Token_PARAMS
        || yytoken == Token_REF
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_STRING
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT
        || yytoken == Token_VOID
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LBRACKET
        || yytoken == Token_IDENTIFIER)
      {
        bool parameter_array_occurred = false;
        formal_parameter_ast *__node_201 = 0;
        if (!parse_formal_parameter(&__node_201, &parameter_array_occurred))
          {
            return yy_expected_symbol(ast_node::Kind_formal_parameter, "formal_parameter");
          }
        (*yynode)->formal_parameter_sequence = snoc((*yynode)->formal_parameter_sequence, __node_201, memory_pool);
        while (yytoken == Token_COMMA)
          {
            if ( parameter_array_occurred == true )
              {
                break;
              }
            if (yytoken != Token_COMMA)
              return yy_expected_token(yytoken, Token_COMMA, ",");
            yylex();
            formal_parameter_ast *__node_202 = 0;
            if (!parse_formal_parameter(&__node_202, &parameter_array_occurred))
              {
                return yy_expected_symbol(ast_node::Kind_formal_parameter, "formal_parameter");
              }
            (*yynode)->formal_parameter_sequence = snoc((*yynode)->formal_parameter_sequence, __node_202, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_general_catch_clause(general_catch_clause_ast **yynode)
  {
    *yynode = create<general_catch_clause_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_CATCH)
      {
        if (yytoken != Token_CATCH)
          return yy_expected_token(yytoken, Token_CATCH, "catch");
        yylex();
        block_ast *__node_203 = 0;
        if (!parse_block(&__node_203))
          {
            return yy_expected_symbol(ast_node::Kind_block, "block");
          }
        (*yynode)->body = __node_203;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_generic_dimension_specifier(generic_dimension_specifier_ast **yynode)
  {
    *yynode = create<generic_dimension_specifier_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LESS_THAN)
      {
        if (yytoken != Token_LESS_THAN)
          return yy_expected_token(yytoken, Token_LESS_THAN, "<");
        yylex();
        (*yynode)->comma_count = 0;
        while (yytoken == Token_COMMA)
          {
            if (yytoken != Token_COMMA)
              return yy_expected_token(yytoken, Token_COMMA, ",");
            yylex();
            (*yynode)->comma_count++;
          }
        if (yytoken != Token_GREATER_THAN)
          return yy_expected_token(yytoken, Token_GREATER_THAN, ">");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_global_attribute_section(global_attribute_section_ast **yynode)
  {
    *yynode = create<global_attribute_section_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LBRACKET)
      {
        if (yytoken != Token_LBRACKET)
          return yy_expected_token(yytoken, Token_LBRACKET, "[");
        yylex();
        if (yytoken != Token_ASSEMBLY)
          return yy_expected_token(yytoken, Token_ASSEMBLY, "assembly");
        yylex();
        if (yytoken != Token_COLON)
          return yy_expected_token(yytoken, Token_COLON, ":");
        yylex();
        attribute_ast *__node_204 = 0;
        if (!parse_attribute(&__node_204))
          {
            return yy_expected_symbol(ast_node::Kind_attribute, "attribute");
          }
        (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_204, memory_pool);
        while (yytoken == Token_COMMA)
          {
            if (LA(2).kind == Token_RBRACKET)
              {
                break;
              }
            if (yytoken != Token_COMMA)
              return yy_expected_token(yytoken, Token_COMMA, ",");
            yylex();
            attribute_ast *__node_205 = 0;
            if (!parse_attribute(&__node_205))
              {
                return yy_expected_symbol(ast_node::Kind_attribute, "attribute");
              }
            (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_205, memory_pool);
          }
        if (yytoken == Token_COMMA)
          {
            if (yytoken != Token_COMMA)
              return yy_expected_token(yytoken, Token_COMMA, ",");
            yylex();
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken != Token_RBRACKET)
          return yy_expected_token(yytoken, Token_RBRACKET, "]");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_goto_statement(goto_statement_ast **yynode)
  {
    *yynode = create<goto_statement_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_GOTO)
      {
        if (yytoken != Token_GOTO)
          return yy_expected_token(yytoken, Token_GOTO, "goto");
        yylex();
        if (yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_IDENTIFIER)
          {
            identifier_ast *__node_206 = 0;
            if (!parse_identifier(&__node_206))
              {
                return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
              }
            (*yynode)->label = __node_206;
            (*yynode)->goto_type = goto_statement::type_labeled_statement;
          }
        else if (yytoken == Token_CASE)
          {
            if (yytoken != Token_CASE)
              return yy_expected_token(yytoken, Token_CASE, "case");
            yylex();
            constant_expression_ast *__node_207 = 0;
            if (!parse_constant_expression(&__node_207))
              {
                return yy_expected_symbol(ast_node::Kind_constant_expression, "constant_expression");
              }
            (*yynode)->constant_expression = __node_207;
            (*yynode)->goto_type = goto_statement::type_switch_case;
          }
        else if (yytoken == Token_DEFAULT)
          {
            if (yytoken != Token_DEFAULT)
              return yy_expected_token(yytoken, Token_DEFAULT, "default");
            yylex();
            (*yynode)->goto_type = goto_statement::type_switch_default;
          }
        else
          {
            return false;
          }
        if (yytoken != Token_SEMICOLON)
          return yy_expected_token(yytoken, Token_SEMICOLON, ";");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_identifier(identifier_ast **yynode)
  {
    *yynode = create<identifier_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        if (yytoken == Token_IDENTIFIER)
          {
            if (yytoken != Token_IDENTIFIER)
              return yy_expected_token(yytoken, Token_IDENTIFIER, "identifier");
            (*yynode)->ident = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_ADD)
          {
            if (yytoken != Token_ADD)
              return yy_expected_token(yytoken, Token_ADD, "add");
            (*yynode)->ident = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_ALIAS)
          {
            if (yytoken != Token_ALIAS)
              return yy_expected_token(yytoken, Token_ALIAS, "alias");
            (*yynode)->ident = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_GET)
          {
            if (yytoken != Token_GET)
              return yy_expected_token(yytoken, Token_GET, "get");
            (*yynode)->ident = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_GLOBAL)
          {
            if (yytoken != Token_GLOBAL)
              return yy_expected_token(yytoken, Token_GLOBAL, "global");
            (*yynode)->ident = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_PARTIAL)
          {
            if (yytoken != Token_PARTIAL)
              return yy_expected_token(yytoken, Token_PARTIAL, "partial");
            (*yynode)->ident = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_REMOVE)
          {
            if (yytoken != Token_REMOVE)
              return yy_expected_token(yytoken, Token_REMOVE, "remove");
            (*yynode)->ident = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_SET)
          {
            if (yytoken != Token_SET)
              return yy_expected_token(yytoken, Token_SET, "set");
            (*yynode)->ident = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_VALUE)
          {
            if (yytoken != Token_VALUE)
              return yy_expected_token(yytoken, Token_VALUE, "value");
            (*yynode)->ident = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_WHERE)
          {
            if (yytoken != Token_WHERE)
              return yy_expected_token(yytoken, Token_WHERE, "where");
            (*yynode)->ident = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_YIELD)
          {
            if (yytoken != Token_YIELD)
              return yy_expected_token(yytoken, Token_YIELD, "yield");
            (*yynode)->ident = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_ASSEMBLY)
          {
            if (yytoken != Token_ASSEMBLY)
              return yy_expected_token(yytoken, Token_ASSEMBLY, "assembly");
            (*yynode)->ident = token_stream->index() - 1;
            yylex();
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_if_statement(if_statement_ast **yynode)
  {
    *yynode = create<if_statement_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_IF)
      {
        if (yytoken != Token_IF)
          return yy_expected_token(yytoken, Token_IF, "if");
        yylex();
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        boolean_expression_ast *__node_208 = 0;
        if (!parse_boolean_expression(&__node_208))
          {
            return yy_expected_symbol(ast_node::Kind_boolean_expression, "boolean_expression");
          }
        (*yynode)->condition = __node_208;
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        embedded_statement_ast *__node_209 = 0;
        if (!parse_embedded_statement(&__node_209))
          {
            return yy_expected_symbol(ast_node::Kind_embedded_statement, "embedded_statement");
          }
        (*yynode)->if_body = __node_209;
        if (yytoken == Token_ELSE)
          {
            if (yytoken != Token_ELSE)
              return yy_expected_token(yytoken, Token_ELSE, "else");
            yylex();
            embedded_statement_ast *__node_210 = 0;
            if (!parse_embedded_statement(&__node_210))
              {
                return yy_expected_symbol(ast_node::Kind_embedded_statement, "embedded_statement");
              }
            (*yynode)->else_body = __node_210;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_indexer_declaration(indexer_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers, type_ast *type, type_name_safe_ast *interface_type)
  {
    *yynode = create<indexer_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->start_token < (*yynode)->start_token)
      (*yynode)->start_token = modifiers->start_token;

    (*yynode)->type = type;
    if (type && type->start_token < (*yynode)->start_token)
      (*yynode)->start_token = type->start_token;

    (*yynode)->interface_type = interface_type;
    if (interface_type && interface_type->start_token < (*yynode)->start_token)
      (*yynode)->start_token = interface_type->start_token;

    if (yytoken == Token_THIS)
      {
        if (yytoken != Token_THIS)
          return yy_expected_token(yytoken, Token_THIS, "this");
        yylex();
        if (yytoken != Token_LBRACKET)
          return yy_expected_token(yytoken, Token_LBRACKET, "[");
        yylex();
        formal_parameter_list_ast *__node_211 = 0;
        if (!parse_formal_parameter_list(&__node_211))
          {
            return yy_expected_symbol(ast_node::Kind_formal_parameter_list, "formal_parameter_list");
          }
        (*yynode)->formal_parameters = __node_211;
        if (yytoken != Token_RBRACKET)
          return yy_expected_token(yytoken, Token_RBRACKET, "]");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_integral_type(integral_type_ast **yynode)
  {
    *yynode = create<integral_type_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT)
      {
        if (yytoken == Token_SBYTE)
          {
            if (yytoken != Token_SBYTE)
              return yy_expected_token(yytoken, Token_SBYTE, "sbyte");
            yylex();
            (*yynode)->type = integral_type::type_sbyte;
          }
        else if (yytoken == Token_BYTE)
          {
            if (yytoken != Token_BYTE)
              return yy_expected_token(yytoken, Token_BYTE, "byte");
            yylex();
            (*yynode)->type = integral_type::type_byte;
          }
        else if (yytoken == Token_SHORT)
          {
            if (yytoken != Token_SHORT)
              return yy_expected_token(yytoken, Token_SHORT, "short");
            yylex();
            (*yynode)->type = integral_type::type_short;
          }
        else if (yytoken == Token_USHORT)
          {
            if (yytoken != Token_USHORT)
              return yy_expected_token(yytoken, Token_USHORT, "ushort");
            yylex();
            (*yynode)->type = integral_type::type_ushort;
          }
        else if (yytoken == Token_INT)
          {
            if (yytoken != Token_INT)
              return yy_expected_token(yytoken, Token_INT, "int");
            yylex();
            (*yynode)->type = integral_type::type_int;
          }
        else if (yytoken == Token_UINT)
          {
            if (yytoken != Token_UINT)
              return yy_expected_token(yytoken, Token_UINT, "uint");
            yylex();
            (*yynode)->type = integral_type::type_uint;
          }
        else if (yytoken == Token_LONG)
          {
            if (yytoken != Token_LONG)
              return yy_expected_token(yytoken, Token_LONG, "long");
            yylex();
            (*yynode)->type = integral_type::type_long;
          }
        else if (yytoken == Token_ULONG)
          {
            if (yytoken != Token_ULONG)
              return yy_expected_token(yytoken, Token_ULONG, "ulong");
            yylex();
            (*yynode)->type = integral_type::type_ulong;
          }
        else if (yytoken == Token_CHAR)
          {
            if (yytoken != Token_CHAR)
              return yy_expected_token(yytoken, Token_CHAR, "char");
            yylex();
            (*yynode)->type = integral_type::type_char;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_interface_accessors(interface_accessors_ast **yynode)
  {
    *yynode = create<interface_accessors_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_GET
        || yytoken == Token_SET
        || yytoken == Token_LBRACKET)
      {
        while (yytoken == Token_LBRACKET)
          {
            attribute_section_ast *__node_212 = 0;
            if (!parse_attribute_section(&__node_212))
              {
                return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
              }
            (*yynode)->accessor1_attribute_sequence = snoc((*yynode)->accessor1_attribute_sequence, __node_212, memory_pool);
          }
        if (yytoken == Token_GET)
          {
            if (yytoken != Token_GET)
              return yy_expected_token(yytoken, Token_GET, "get");
            yylex();
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
            (*yynode)->accessor1_type = accessor_declarations::type_get;
            if (yytoken == Token_SET
                || yytoken == Token_LBRACKET)
              {
                while (yytoken == Token_LBRACKET)
                  {
                    attribute_section_ast *__node_213 = 0;
                    if (!parse_attribute_section(&__node_213))
                      {
                        return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
                      }
                    (*yynode)->accessor2_attribute_sequence = snoc((*yynode)->accessor2_attribute_sequence, __node_213, memory_pool);
                  }
                if (yytoken != Token_SET)
                  return yy_expected_token(yytoken, Token_SET, "set");
                yylex();
                if (yytoken != Token_SEMICOLON)
                  return yy_expected_token(yytoken, Token_SEMICOLON, ";");
                yylex();
                (*yynode)->accessor2_type = accessor_declarations::type_set;
              }
            else if (true /*epsilon*/)
              {
                (*yynode)->accessor2_type = accessor_declarations::type_none;
              }
            else
              {
                return false;
              }
          }
        else if (yytoken == Token_SET)
          {
            if (yytoken != Token_SET)
              return yy_expected_token(yytoken, Token_SET, "set");
            yylex();
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
            (*yynode)->accessor1_type = accessor_declarations::type_set;
            if (yytoken == Token_GET
                || yytoken == Token_LBRACKET)
              {
                while (yytoken == Token_LBRACKET)
                  {
                    attribute_section_ast *__node_214 = 0;
                    if (!parse_attribute_section(&__node_214))
                      {
                        return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
                      }
                    (*yynode)->accessor2_attribute_sequence = snoc((*yynode)->accessor2_attribute_sequence, __node_214, memory_pool);
                  }
                if (yytoken != Token_GET)
                  return yy_expected_token(yytoken, Token_GET, "get");
                yylex();
                if (yytoken != Token_SEMICOLON)
                  return yy_expected_token(yytoken, Token_SEMICOLON, ";");
                yylex();
                (*yynode)->accessor2_type = accessor_declarations::type_get;
              }
            else if (true /*epsilon*/)
              {
                (*yynode)->accessor2_type = accessor_declarations::type_none;
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
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_interface_base(interface_base_ast **yynode)
  {
    *yynode = create<interface_base_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_COLON)
      {
        if (yytoken != Token_COLON)
          return yy_expected_token(yytoken, Token_COLON, ":");
        yylex();
        type_name_ast *__node_215 = 0;
        if (!parse_type_name(&__node_215))
          {
            return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
          }
        (*yynode)->interface_type_sequence = snoc((*yynode)->interface_type_sequence, __node_215, memory_pool);
        while (yytoken == Token_COMMA)
          {
            if (yytoken != Token_COMMA)
              return yy_expected_token(yytoken, Token_COMMA, ",");
            yylex();
            type_name_ast *__node_216 = 0;
            if (!parse_type_name(&__node_216))
              {
                return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
              }
            (*yynode)->interface_type_sequence = snoc((*yynode)->interface_type_sequence, __node_216, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_interface_body(interface_body_ast **yynode)
  {
    *yynode = create<interface_body_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LBRACE)
      {
        if (yytoken != Token_LBRACE)
          return yy_expected_token(yytoken, Token_LBRACE, "{");
        yylex();
        while (yytoken == Token_BOOL
               || yytoken == Token_BYTE
               || yytoken == Token_CHAR
               || yytoken == Token_DECIMAL
               || yytoken == Token_DOUBLE
               || yytoken == Token_EVENT
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_NEW
               || yytoken == Token_OBJECT
               || yytoken == Token_SBYTE
               || yytoken == Token_SHORT
               || yytoken == Token_STRING
               || yytoken == Token_UINT
               || yytoken == Token_ULONG
               || yytoken == Token_USHORT
               || yytoken == Token_VOID
               || yytoken == Token_ADD
               || yytoken == Token_ALIAS
               || yytoken == Token_GET
               || yytoken == Token_GLOBAL
               || yytoken == Token_PARTIAL
               || yytoken == Token_REMOVE
               || yytoken == Token_SET
               || yytoken == Token_VALUE
               || yytoken == Token_WHERE
               || yytoken == Token_YIELD
               || yytoken == Token_ASSEMBLY
               || yytoken == Token_LBRACKET
               || yytoken == Token_IDENTIFIER)
          {
            interface_member_declaration_ast *__node_217 = 0;
            if (!parse_interface_member_declaration(&__node_217))
              {
                return yy_expected_symbol(ast_node::Kind_interface_member_declaration, "interface_member_declaration");
              }
            (*yynode)->member_declaration_sequence = snoc((*yynode)->member_declaration_sequence, __node_217, memory_pool);
          }
        if (yytoken != Token_RBRACE)
          return yy_expected_token(yytoken, Token_RBRACE, "}");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_interface_declaration(interface_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers, bool partial)
  {
    *yynode = create<interface_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->start_token < (*yynode)->start_token)
      (*yynode)->start_token = modifiers->start_token;

    (*yynode)->partial = partial;
    if (yytoken == Token_INTERFACE)
      {
        if (yytoken != Token_INTERFACE)
          return yy_expected_token(yytoken, Token_INTERFACE, "interface");
        yylex();
        identifier_ast *__node_218 = 0;
        if (!parse_identifier(&__node_218))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->interface_name = __node_218;
        if ((yytoken == Token_LESS_THAN) && ( compatibility_mode() >= csharp20_compatibility ))
          {
            type_parameters_ast *__node_219 = 0;
            if (!parse_type_parameters(&__node_219))
              {
                return yy_expected_symbol(ast_node::Kind_type_parameters, "type_parameters");
              }
            (*yynode)->type_parameters = __node_219;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken == Token_COLON)
          {
            interface_base_ast *__node_220 = 0;
            if (!parse_interface_base(&__node_220))
              {
                return yy_expected_symbol(ast_node::Kind_interface_base, "interface_base");
              }
            (*yynode)->interface_base = __node_220;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if ((yytoken == Token_WHERE) && ( compatibility_mode() >= csharp20_compatibility ))
          {
            type_parameter_constraints_clauses_ast *__node_221 = 0;
            if (!parse_type_parameter_constraints_clauses(&__node_221))
              {
                return yy_expected_symbol(ast_node::Kind_type_parameter_constraints_clauses, "type_parameter_constraints_clauses");
              }
            (*yynode)->type_parameter_constraints_clauses = __node_221;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        interface_body_ast *__node_222 = 0;
        if (!parse_interface_body(&__node_222))
          {
            return yy_expected_symbol(ast_node::Kind_interface_body, "interface_body");
          }
        (*yynode)->body = __node_222;
        if (yytoken == Token_SEMICOLON)
          {
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_interface_event_declaration(interface_event_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, bool decl_new)
  {
    *yynode = create<interface_event_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->decl_new = decl_new;
    if (yytoken == Token_EVENT)
      {
        if (yytoken != Token_EVENT)
          return yy_expected_token(yytoken, Token_EVENT, "event");
        yylex();
        type_ast *__node_223 = 0;
        if (!parse_type(&__node_223))
          {
            return yy_expected_symbol(ast_node::Kind_type, "type");
          }
        (*yynode)->event_type = __node_223;
        identifier_ast *__node_224 = 0;
        if (!parse_identifier(&__node_224))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->event_name = __node_224;
        if (yytoken != Token_SEMICOLON)
          return yy_expected_token(yytoken, Token_SEMICOLON, ";");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_interface_indexer_declaration(interface_indexer_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, bool decl_new, type_ast *type)
  {
    *yynode = create<interface_indexer_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->decl_new = decl_new;
    (*yynode)->type = type;
    if (type && type->start_token < (*yynode)->start_token)
      (*yynode)->start_token = type->start_token;

    if (yytoken == Token_THIS)
      {
        if (yytoken != Token_THIS)
          return yy_expected_token(yytoken, Token_THIS, "this");
        yylex();
        if (yytoken != Token_LBRACKET)
          return yy_expected_token(yytoken, Token_LBRACKET, "[");
        yylex();
        formal_parameter_list_ast *__node_225 = 0;
        if (!parse_formal_parameter_list(&__node_225))
          {
            return yy_expected_symbol(ast_node::Kind_formal_parameter_list, "formal_parameter_list");
          }
        (*yynode)->formal_parameters = __node_225;
        if (yytoken != Token_RBRACKET)
          return yy_expected_token(yytoken, Token_RBRACKET, "]");
        yylex();
        if (yytoken != Token_LBRACE)
          return yy_expected_token(yytoken, Token_LBRACE, "{");
        yylex();
        interface_accessors_ast *__node_226 = 0;
        if (!parse_interface_accessors(&__node_226))
          {
            return yy_expected_symbol(ast_node::Kind_interface_accessors, "interface_accessors");
          }
        (*yynode)->interface_accessors = __node_226;
        if (yytoken != Token_RBRACE)
          return yy_expected_token(yytoken, Token_RBRACE, "}");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_interface_member_declaration(interface_member_declaration_ast **yynode)
  {
    *yynode = create<interface_member_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    bool decl_new;

    if (yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_DECIMAL
        || yytoken == Token_DOUBLE
        || yytoken == Token_EVENT
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_STRING
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT
        || yytoken == Token_VOID
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LBRACKET
        || yytoken == Token_IDENTIFIER)
      {
        const list_node<attribute_section_ast *> *attribute_sequence = 0;

        return_type_ast *member_type = 0;

        identifier_ast *member_name = 0;

        while (yytoken == Token_LBRACKET)
          {
            attribute_section_ast *__node_227 = 0;
            if (!parse_attribute_section(&__node_227))
              {
                return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
              }
            attribute_sequence = snoc(attribute_sequence, __node_227, memory_pool);
          }
        if (yytoken == Token_NEW)
          {
            if (yytoken != Token_NEW)
              return yy_expected_token(yytoken, Token_NEW, "new");
            yylex();
            decl_new = true;
          }
        else if (true /*epsilon*/)
          {
            decl_new = false;
          }
        else
          {
            return false;
          }
        if (yytoken == Token_EVENT)
          {
            interface_event_declaration_ast *__node_228 = 0;
            if (!parse_interface_event_declaration(&__node_228,
                                                   attribute_sequence, decl_new
                                                  ))
              {
                return yy_expected_symbol(ast_node::Kind_interface_event_declaration, "interface_event_declaration");
              }
            (*yynode)->event_declaration = __node_228;
          }
        else if (yytoken == Token_BOOL
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR
                 || yytoken == Token_DECIMAL
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_LONG
                 || yytoken == Token_OBJECT
                 || yytoken == Token_SBYTE
                 || yytoken == Token_SHORT
                 || yytoken == Token_STRING
                 || yytoken == Token_UINT
                 || yytoken == Token_ULONG
                 || yytoken == Token_USHORT
                 || yytoken == Token_VOID
                 || yytoken == Token_ADD
                 || yytoken == Token_ALIAS
                 || yytoken == Token_GET
                 || yytoken == Token_GLOBAL
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_REMOVE
                 || yytoken == Token_SET
                 || yytoken == Token_VALUE
                 || yytoken == Token_WHERE
                 || yytoken == Token_YIELD
                 || yytoken == Token_ASSEMBLY
                 || yytoken == Token_IDENTIFIER)
          {
            return_type_ast *__node_229 = 0;
            if (!parse_return_type(&__node_229))
              {
                return yy_expected_symbol(ast_node::Kind_return_type, "return_type");
              }
            member_type = __node_229;
            if ((yytoken == Token_THIS) && ( member_type->type == return_type::type_regular ))
              {
                interface_indexer_declaration_ast *__node_230 = 0;
                if (!parse_interface_indexer_declaration(&__node_230,
                    attribute_sequence, decl_new, member_type->regular_type
                                                        ))
                  {
                    return yy_expected_symbol(ast_node::Kind_interface_indexer_declaration, "interface_indexer_declaration");
                  }
                (*yynode)->indexer_declaration = __node_230;
              }
            else if (yytoken == Token_ADD
                     || yytoken == Token_ALIAS
                     || yytoken == Token_GET
                     || yytoken == Token_GLOBAL
                     || yytoken == Token_PARTIAL
                     || yytoken == Token_REMOVE
                     || yytoken == Token_SET
                     || yytoken == Token_VALUE
                     || yytoken == Token_WHERE
                     || yytoken == Token_YIELD
                     || yytoken == Token_ASSEMBLY
                     || yytoken == Token_IDENTIFIER)
              {
                identifier_ast *__node_231 = 0;
                if (!parse_identifier(&__node_231))
                  {
                    return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                  }
                member_name = __node_231;
                if ((yytoken == Token_RBRACE) && ( member_type->type == return_type::type_regular ))
                  {
                    interface_property_declaration_ast *__node_232 = 0;
                    if (!parse_interface_property_declaration(&__node_232,
                        attribute_sequence, decl_new,
                        member_type->regular_type, member_name
                                                             ))
                      {
                        return yy_expected_symbol(ast_node::Kind_interface_property_declaration, "interface_property_declaration");
                      }
                    (*yynode)->interface_property_declaration = __node_232;
                  }
                else if (yytoken == Token_LPAREN
                         || yytoken == Token_LESS_THAN)
                  {
                    interface_method_declaration_ast *__node_233 = 0;
                    if (!parse_interface_method_declaration(&__node_233,
                                                            attribute_sequence, decl_new, member_type, member_name
                                                           ))
                      {
                        return yy_expected_symbol(ast_node::Kind_interface_method_declaration, "interface_method_declaration");
                      }
                    (*yynode)->interface_method_declaration = __node_233;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_interface_method_declaration(interface_method_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, bool decl_new, return_type_ast *return_type, identifier_ast *method_name)
  {
    *yynode = create<interface_method_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->decl_new = decl_new;
    (*yynode)->return_type = return_type;
    if (return_type && return_type->start_token < (*yynode)->start_token)
      (*yynode)->start_token = return_type->start_token;

    (*yynode)->method_name = method_name;
    if (method_name && method_name->start_token < (*yynode)->start_token)
      (*yynode)->start_token = method_name->start_token;

    if (yytoken == Token_LPAREN
        || yytoken == Token_LESS_THAN)
      {
        if ((yytoken == Token_LESS_THAN) && ( compatibility_mode() >= csharp20_compatibility ))
          {
            type_parameters_ast *__node_234 = 0;
            if (!parse_type_parameters(&__node_234))
              {
                return yy_expected_symbol(ast_node::Kind_type_parameters, "type_parameters");
              }
            (*yynode)->type_parameters = __node_234;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        if (yytoken == Token_BOOL
            || yytoken == Token_BYTE
            || yytoken == Token_CHAR
            || yytoken == Token_DECIMAL
            || yytoken == Token_DOUBLE
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_OBJECT
            || yytoken == Token_OUT
            || yytoken == Token_PARAMS
            || yytoken == Token_REF
            || yytoken == Token_SBYTE
            || yytoken == Token_SHORT
            || yytoken == Token_STRING
            || yytoken == Token_UINT
            || yytoken == Token_ULONG
            || yytoken == Token_USHORT
            || yytoken == Token_VOID
            || yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_LBRACKET
            || yytoken == Token_IDENTIFIER)
          {
            formal_parameter_list_ast *__node_235 = 0;
            if (!parse_formal_parameter_list(&__node_235))
              {
                return yy_expected_symbol(ast_node::Kind_formal_parameter_list, "formal_parameter_list");
              }
            (*yynode)->formal_parameters = __node_235;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        if ((yytoken == Token_WHERE) && ( compatibility_mode() >= csharp20_compatibility ))
          {
            type_parameter_constraints_clauses_ast *__node_236 = 0;
            if (!parse_type_parameter_constraints_clauses(&__node_236))
              {
                return yy_expected_symbol(ast_node::Kind_type_parameter_constraints_clauses, "type_parameter_constraints_clauses");
              }
            (*yynode)->type_parameter_constraints_clauses = __node_236;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken != Token_SEMICOLON)
          return yy_expected_token(yytoken, Token_SEMICOLON, ";");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_interface_property_declaration(interface_property_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, bool decl_new, type_ast *type, identifier_ast *property_name)
  {
    *yynode = create<interface_property_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->decl_new = decl_new;
    (*yynode)->type = type;
    if (type && type->start_token < (*yynode)->start_token)
      (*yynode)->start_token = type->start_token;

    (*yynode)->property_name = property_name;
    if (property_name && property_name->start_token < (*yynode)->start_token)
      (*yynode)->start_token = property_name->start_token;

    if (yytoken == Token_RBRACE)
      {
        if (yytoken != Token_RBRACE)
          return yy_expected_token(yytoken, Token_RBRACE, "}");
        yylex();
        interface_accessors_ast *__node_237 = 0;
        if (!parse_interface_accessors(&__node_237))
          {
            return yy_expected_symbol(ast_node::Kind_interface_accessors, "interface_accessors");
          }
        (*yynode)->interface_accessors = __node_237;
        if (yytoken != Token_RBRACE)
          return yy_expected_token(yytoken, Token_RBRACE, "}");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_keyword(keyword_ast **yynode)
  {
    *yynode = create<keyword_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ABSTRACT
        || yytoken == Token_AS
        || yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BREAK
        || yytoken == Token_BYTE
        || yytoken == Token_CASE
        || yytoken == Token_CATCH
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_CLASS
        || yytoken == Token_CONST
        || yytoken == Token_CONTINUE
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DO
        || yytoken == Token_DOUBLE
        || yytoken == Token_ELSE
        || yytoken == Token_ENUM
        || yytoken == Token_EVENT
        || yytoken == Token_EXPLICIT
        || yytoken == Token_EXTERN
        || yytoken == Token_FINALLY
        || yytoken == Token_FIXED
        || yytoken == Token_FLOAT
        || yytoken == Token_FOREACH
        || yytoken == Token_FOR
        || yytoken == Token_GOTO
        || yytoken == Token_IF
        || yytoken == Token_IMPLICIT
        || yytoken == Token_IN
        || yytoken == Token_INT
        || yytoken == Token_INTERFACE
        || yytoken == Token_INTERNAL
        || yytoken == Token_IS
        || yytoken == Token_LOCK
        || yytoken == Token_LONG
        || yytoken == Token_NAMESPACE
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_OPERATOR
        || yytoken == Token_OUT
        || yytoken == Token_OVERRIDE
        || yytoken == Token_PARAMS
        || yytoken == Token_PRIVATE
        || yytoken == Token_PROTECTED
        || yytoken == Token_PUBLIC
        || yytoken == Token_READONLY
        || yytoken == Token_REF
        || yytoken == Token_RETURN
        || yytoken == Token_SBYTE
        || yytoken == Token_SEALED
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STACKALLOC
        || yytoken == Token_STATIC
        || yytoken == Token_STRING
        || yytoken == Token_STRUCT
        || yytoken == Token_SWITCH
        || yytoken == Token_THIS
        || yytoken == Token_THROW
        || yytoken == Token_TRY
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_UNSAFE
        || yytoken == Token_USHORT
        || yytoken == Token_USING
        || yytoken == Token_VIRTUAL
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE
        || yytoken == Token_WHILE)
      {
        if (yytoken == Token_ABSTRACT)
          {
            if (yytoken != Token_ABSTRACT)
              return yy_expected_token(yytoken, Token_ABSTRACT, "abstract");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_AS)
          {
            if (yytoken != Token_AS)
              return yy_expected_token(yytoken, Token_AS, "as");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_BASE)
          {
            if (yytoken != Token_BASE)
              return yy_expected_token(yytoken, Token_BASE, "base");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_BOOL)
          {
            if (yytoken != Token_BOOL)
              return yy_expected_token(yytoken, Token_BOOL, "bool");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_BREAK)
          {
            if (yytoken != Token_BREAK)
              return yy_expected_token(yytoken, Token_BREAK, "break");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_BYTE)
          {
            if (yytoken != Token_BYTE)
              return yy_expected_token(yytoken, Token_BYTE, "byte");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_CASE)
          {
            if (yytoken != Token_CASE)
              return yy_expected_token(yytoken, Token_CASE, "case");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_CATCH)
          {
            if (yytoken != Token_CATCH)
              return yy_expected_token(yytoken, Token_CATCH, "catch");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_CHAR)
          {
            if (yytoken != Token_CHAR)
              return yy_expected_token(yytoken, Token_CHAR, "char");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_CHECKED)
          {
            if (yytoken != Token_CHECKED)
              return yy_expected_token(yytoken, Token_CHECKED, "checked");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_CLASS)
          {
            if (yytoken != Token_CLASS)
              return yy_expected_token(yytoken, Token_CLASS, "class");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_CONST)
          {
            if (yytoken != Token_CONST)
              return yy_expected_token(yytoken, Token_CONST, "const");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_CONTINUE)
          {
            if (yytoken != Token_CONTINUE)
              return yy_expected_token(yytoken, Token_CONTINUE, "continue");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_DECIMAL)
          {
            if (yytoken != Token_DECIMAL)
              return yy_expected_token(yytoken, Token_DECIMAL, "decimal");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_DEFAULT)
          {
            if (yytoken != Token_DEFAULT)
              return yy_expected_token(yytoken, Token_DEFAULT, "default");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_DELEGATE)
          {
            if (yytoken != Token_DELEGATE)
              return yy_expected_token(yytoken, Token_DELEGATE, "delegate");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_DO)
          {
            if (yytoken != Token_DO)
              return yy_expected_token(yytoken, Token_DO, "do");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_DOUBLE)
          {
            if (yytoken != Token_DOUBLE)
              return yy_expected_token(yytoken, Token_DOUBLE, "double");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_ELSE)
          {
            if (yytoken != Token_ELSE)
              return yy_expected_token(yytoken, Token_ELSE, "else");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_ENUM)
          {
            if (yytoken != Token_ENUM)
              return yy_expected_token(yytoken, Token_ENUM, "enum");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_EVENT)
          {
            if (yytoken != Token_EVENT)
              return yy_expected_token(yytoken, Token_EVENT, "event");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_EXPLICIT)
          {
            if (yytoken != Token_EXPLICIT)
              return yy_expected_token(yytoken, Token_EXPLICIT, "explicit");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_EXTERN)
          {
            if (yytoken != Token_EXTERN)
              return yy_expected_token(yytoken, Token_EXTERN, "extern");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_FINALLY)
          {
            if (yytoken != Token_FINALLY)
              return yy_expected_token(yytoken, Token_FINALLY, "finally");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_FIXED)
          {
            if (yytoken != Token_FIXED)
              return yy_expected_token(yytoken, Token_FIXED, "fixed");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_FLOAT)
          {
            if (yytoken != Token_FLOAT)
              return yy_expected_token(yytoken, Token_FLOAT, "float");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_FOREACH)
          {
            if (yytoken != Token_FOREACH)
              return yy_expected_token(yytoken, Token_FOREACH, "foreach");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_FOR)
          {
            if (yytoken != Token_FOR)
              return yy_expected_token(yytoken, Token_FOR, "for");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_GOTO)
          {
            if (yytoken != Token_GOTO)
              return yy_expected_token(yytoken, Token_GOTO, "goto");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_IF)
          {
            if (yytoken != Token_IF)
              return yy_expected_token(yytoken, Token_IF, "if");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_IMPLICIT)
          {
            if (yytoken != Token_IMPLICIT)
              return yy_expected_token(yytoken, Token_IMPLICIT, "implicit");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_IN)
          {
            if (yytoken != Token_IN)
              return yy_expected_token(yytoken, Token_IN, "in");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_INT)
          {
            if (yytoken != Token_INT)
              return yy_expected_token(yytoken, Token_INT, "int");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_INTERFACE)
          {
            if (yytoken != Token_INTERFACE)
              return yy_expected_token(yytoken, Token_INTERFACE, "interface");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_INTERNAL)
          {
            if (yytoken != Token_INTERNAL)
              return yy_expected_token(yytoken, Token_INTERNAL, "internal");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_IS)
          {
            if (yytoken != Token_IS)
              return yy_expected_token(yytoken, Token_IS, "is");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_LOCK)
          {
            if (yytoken != Token_LOCK)
              return yy_expected_token(yytoken, Token_LOCK, "lock");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_LONG)
          {
            if (yytoken != Token_LONG)
              return yy_expected_token(yytoken, Token_LONG, "long");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_NAMESPACE)
          {
            if (yytoken != Token_NAMESPACE)
              return yy_expected_token(yytoken, Token_NAMESPACE, "namespace");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_NEW)
          {
            if (yytoken != Token_NEW)
              return yy_expected_token(yytoken, Token_NEW, "new");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_OBJECT)
          {
            if (yytoken != Token_OBJECT)
              return yy_expected_token(yytoken, Token_OBJECT, "object");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_OPERATOR)
          {
            if (yytoken != Token_OPERATOR)
              return yy_expected_token(yytoken, Token_OPERATOR, "operator");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_OUT)
          {
            if (yytoken != Token_OUT)
              return yy_expected_token(yytoken, Token_OUT, "out");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_OVERRIDE)
          {
            if (yytoken != Token_OVERRIDE)
              return yy_expected_token(yytoken, Token_OVERRIDE, "override");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_PARAMS)
          {
            if (yytoken != Token_PARAMS)
              return yy_expected_token(yytoken, Token_PARAMS, "params");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_PRIVATE)
          {
            if (yytoken != Token_PRIVATE)
              return yy_expected_token(yytoken, Token_PRIVATE, "private");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_PROTECTED)
          {
            if (yytoken != Token_PROTECTED)
              return yy_expected_token(yytoken, Token_PROTECTED, "protected");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_PUBLIC)
          {
            if (yytoken != Token_PUBLIC)
              return yy_expected_token(yytoken, Token_PUBLIC, "public");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_READONLY)
          {
            if (yytoken != Token_READONLY)
              return yy_expected_token(yytoken, Token_READONLY, "readonly");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_REF)
          {
            if (yytoken != Token_REF)
              return yy_expected_token(yytoken, Token_REF, "ref");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_RETURN)
          {
            if (yytoken != Token_RETURN)
              return yy_expected_token(yytoken, Token_RETURN, "return");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_SBYTE)
          {
            if (yytoken != Token_SBYTE)
              return yy_expected_token(yytoken, Token_SBYTE, "sbyte");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_SEALED)
          {
            if (yytoken != Token_SEALED)
              return yy_expected_token(yytoken, Token_SEALED, "sealed");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_SHORT)
          {
            if (yytoken != Token_SHORT)
              return yy_expected_token(yytoken, Token_SHORT, "short");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_SIZEOF)
          {
            if (yytoken != Token_SIZEOF)
              return yy_expected_token(yytoken, Token_SIZEOF, "sizeof");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_STACKALLOC)
          {
            if (yytoken != Token_STACKALLOC)
              return yy_expected_token(yytoken, Token_STACKALLOC, "stackalloc");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_STATIC)
          {
            if (yytoken != Token_STATIC)
              return yy_expected_token(yytoken, Token_STATIC, "static");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_STRING)
          {
            if (yytoken != Token_STRING)
              return yy_expected_token(yytoken, Token_STRING, "string");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_STRUCT)
          {
            if (yytoken != Token_STRUCT)
              return yy_expected_token(yytoken, Token_STRUCT, "struct");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_SWITCH)
          {
            if (yytoken != Token_SWITCH)
              return yy_expected_token(yytoken, Token_SWITCH, "switch");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_THIS)
          {
            if (yytoken != Token_THIS)
              return yy_expected_token(yytoken, Token_THIS, "this");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_THROW)
          {
            if (yytoken != Token_THROW)
              return yy_expected_token(yytoken, Token_THROW, "throw");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_TRY)
          {
            if (yytoken != Token_TRY)
              return yy_expected_token(yytoken, Token_TRY, "try");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_TYPEOF)
          {
            if (yytoken != Token_TYPEOF)
              return yy_expected_token(yytoken, Token_TYPEOF, "typeof");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_UINT)
          {
            if (yytoken != Token_UINT)
              return yy_expected_token(yytoken, Token_UINT, "uint");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_ULONG)
          {
            if (yytoken != Token_ULONG)
              return yy_expected_token(yytoken, Token_ULONG, "ulong");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_UNCHECKED)
          {
            if (yytoken != Token_UNCHECKED)
              return yy_expected_token(yytoken, Token_UNCHECKED, "unchecked");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_UNSAFE)
          {
            if (yytoken != Token_UNSAFE)
              return yy_expected_token(yytoken, Token_UNSAFE, "unsafe");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_USHORT)
          {
            if (yytoken != Token_USHORT)
              return yy_expected_token(yytoken, Token_USHORT, "ushort");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_USING)
          {
            if (yytoken != Token_USING)
              return yy_expected_token(yytoken, Token_USING, "using");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_VIRTUAL)
          {
            if (yytoken != Token_VIRTUAL)
              return yy_expected_token(yytoken, Token_VIRTUAL, "virtual");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_VOID)
          {
            if (yytoken != Token_VOID)
              return yy_expected_token(yytoken, Token_VOID, "void");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_VOLATILE)
          {
            if (yytoken != Token_VOLATILE)
              return yy_expected_token(yytoken, Token_VOLATILE, "volatile");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
          }
        else if (yytoken == Token_WHILE)
          {
            if (yytoken != Token_WHILE)
              return yy_expected_token(yytoken, Token_WHILE, "while");
            (*yynode)->keyword = token_stream->index() - 1;
            yylex();
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_labeled_statement(labeled_statement_ast **yynode)
  {
    *yynode = create<labeled_statement_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        identifier_ast *__node_238 = 0;
        if (!parse_identifier(&__node_238))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->label = __node_238;
        if (yytoken != Token_COLON)
          return yy_expected_token(yytoken, Token_COLON, ":");
        yylex();
        block_statement_ast *__node_239 = 0;
        if (!parse_block_statement(&__node_239))
          {
            return yy_expected_symbol(ast_node::Kind_block_statement, "block_statement");
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_literal(literal_ast **yynode)
  {
    *yynode = create<literal_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL)
      {
        if (yytoken == Token_TRUE)
          {
            if (yytoken != Token_TRUE)
              return yy_expected_token(yytoken, Token_TRUE, "true");
            yylex();
            (*yynode)->literal_type = literal::type_true;
          }
        else if (yytoken == Token_FALSE)
          {
            if (yytoken != Token_FALSE)
              return yy_expected_token(yytoken, Token_FALSE, "false");
            yylex();
            (*yynode)->literal_type = literal::type_false;
          }
        else if (yytoken == Token_NULL)
          {
            if (yytoken != Token_NULL)
              return yy_expected_token(yytoken, Token_NULL, "null");
            yylex();
            (*yynode)->literal_type = literal::type_null;
          }
        else if (yytoken == Token_INTEGER_LITERAL)
          {
            if (yytoken != Token_INTEGER_LITERAL)
              return yy_expected_token(yytoken, Token_INTEGER_LITERAL, "integer literal");
            (*yynode)->integer_literal = token_stream->index() - 1;
            yylex();
            (*yynode)->literal_type = literal::type_integer;
          }
        else if (yytoken == Token_REAL_LITERAL)
          {
            if (yytoken != Token_REAL_LITERAL)
              return yy_expected_token(yytoken, Token_REAL_LITERAL, "real literal");
            (*yynode)->floating_point_literal = token_stream->index() - 1;
            yylex();
            (*yynode)->literal_type = literal::type_real;
          }
        else if (yytoken == Token_CHARACTER_LITERAL)
          {
            if (yytoken != Token_CHARACTER_LITERAL)
              return yy_expected_token(yytoken, Token_CHARACTER_LITERAL, "character literal");
            (*yynode)->character_literal = token_stream->index() - 1;
            yylex();
            (*yynode)->literal_type = literal::type_character;
          }
        else if (yytoken == Token_STRING_LITERAL)
          {
            if (yytoken != Token_STRING_LITERAL)
              return yy_expected_token(yytoken, Token_STRING_LITERAL, "string literal");
            (*yynode)->string_literal = token_stream->index() - 1;
            yylex();
            (*yynode)->literal_type = literal::type_string;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_local_constant_declaration(local_constant_declaration_ast **yynode)
  {
    *yynode = create<local_constant_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_CONST)
      {
        type_ast *type = 0;

        const list_node<constant_declarator_ast *> *declarator_sequence = 0;

        if (yytoken != Token_CONST)
          return yy_expected_token(yytoken, Token_CONST, "const");
        yylex();
        type_ast *__node_240 = 0;
        if (!parse_type(&__node_240))
          {
            return yy_expected_symbol(ast_node::Kind_type, "type");
          }
        type = __node_240;
        constant_declarator_ast *__node_241 = 0;
        if (!parse_constant_declarator(&__node_241))
          {
            return yy_expected_symbol(ast_node::Kind_constant_declarator, "constant_declarator");
          }
        declarator_sequence = snoc(declarator_sequence, __node_241, memory_pool);
        while (yytoken == Token_COMMA)
          {
            if (yytoken != Token_COMMA)
              return yy_expected_token(yytoken, Token_COMMA, ",");
            yylex();
            constant_declarator_ast *__node_242 = 0;
            if (!parse_constant_declarator(&__node_242))
              {
                return yy_expected_symbol(ast_node::Kind_constant_declarator, "constant_declarator");
              }
            declarator_sequence = snoc(declarator_sequence, __node_242, memory_pool);
          }
        constant_declaration_data_ast *__node_243 = 0;
        if (!parse_constant_declaration_data(&__node_243,
                                             0 /* no attributes */, 0 /* no modifiers */, type, declarator_sequence
                                            ))
          {
            return yy_expected_symbol(ast_node::Kind_constant_declaration_data, "constant_declaration_data");
          }
        (*yynode)->data = __node_243;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_local_variable_declaration(local_variable_declaration_ast **yynode)
  {
    *yynode = create<local_variable_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_DECIMAL
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_STRING
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT
        || yytoken == Token_VOID
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        type_ast *type = 0;

        const list_node<variable_declarator_ast *> *declarator_sequence = 0;

        type_ast *__node_244 = 0;
        if (!parse_type(&__node_244))
          {
            return yy_expected_symbol(ast_node::Kind_type, "type");
          }
        type = __node_244;
        variable_declarator_ast *__node_245 = 0;
        if (!parse_variable_declarator(&__node_245))
          {
            return yy_expected_symbol(ast_node::Kind_variable_declarator, "variable_declarator");
          }
        declarator_sequence = snoc(declarator_sequence, __node_245, memory_pool);
        while (yytoken == Token_COMMA)
          {
            if (yytoken != Token_COMMA)
              return yy_expected_token(yytoken, Token_COMMA, ",");
            yylex();
            variable_declarator_ast *__node_246 = 0;
            if (!parse_variable_declarator(&__node_246))
              {
                return yy_expected_symbol(ast_node::Kind_variable_declarator, "variable_declarator");
              }
            declarator_sequence = snoc(declarator_sequence, __node_246, memory_pool);
          }
        variable_declaration_data_ast *__node_247 = 0;
        if (!parse_variable_declaration_data(&__node_247,
                                             0 /* no attributes */, 0 /* no modifiers */, type, declarator_sequence
                                            ))
          {
            return yy_expected_symbol(ast_node::Kind_variable_declaration_data, "variable_declaration_data");
          }
        (*yynode)->data = __node_247;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_lock_statement(lock_statement_ast **yynode)
  {
    *yynode = create<lock_statement_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LOCK)
      {
        if (yytoken != Token_LOCK)
          return yy_expected_token(yytoken, Token_LOCK, "lock");
        yylex();
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        expression_ast *__node_248 = 0;
        if (!parse_expression(&__node_248))
          {
            return yy_expected_symbol(ast_node::Kind_expression, "expression");
          }
        (*yynode)->lock_expression = __node_248;
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        embedded_statement_ast *__node_249 = 0;
        if (!parse_embedded_statement(&__node_249))
          {
            return yy_expected_symbol(ast_node::Kind_embedded_statement, "embedded_statement");
          }
        (*yynode)->body = __node_249;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_logical_and_expression(logical_and_expression_ast **yynode)
  {
    *yynode = create<logical_and_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        bit_or_expression_ast *__node_250 = 0;
        if (!parse_bit_or_expression(&__node_250))
          {
            return yy_expected_symbol(ast_node::Kind_bit_or_expression, "bit_or_expression");
          }
        (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_250, memory_pool);
        while (yytoken == Token_LOG_AND)
          {
            if (yytoken != Token_LOG_AND)
              return yy_expected_token(yytoken, Token_LOG_AND, "&&");
            yylex();
            bit_or_expression_ast *__node_251 = 0;
            if (!parse_bit_or_expression(&__node_251))
              {
                return yy_expected_symbol(ast_node::Kind_bit_or_expression, "bit_or_expression");
              }
            (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_251, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_logical_or_expression(logical_or_expression_ast **yynode)
  {
    *yynode = create<logical_or_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        logical_and_expression_ast *__node_252 = 0;
        if (!parse_logical_and_expression(&__node_252))
          {
            return yy_expected_symbol(ast_node::Kind_logical_and_expression, "logical_and_expression");
          }
        (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_252, memory_pool);
        while (yytoken == Token_LOG_OR)
          {
            if (yytoken != Token_LOG_OR)
              return yy_expected_token(yytoken, Token_LOG_OR, "||");
            yylex();
            logical_and_expression_ast *__node_253 = 0;
            if (!parse_logical_and_expression(&__node_253))
              {
                return yy_expected_symbol(ast_node::Kind_logical_and_expression, "logical_and_expression");
              }
            (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_253, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_managed_type(managed_type_ast **yynode)
  {
    *yynode = create<managed_type_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_DECIMAL
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_STRING
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        non_array_type_ast *__node_254 = 0;
        if (!parse_non_array_type(&__node_254))
          {
            return yy_expected_symbol(ast_node::Kind_non_array_type, "non_array_type");
          }
        (*yynode)->non_array_type = __node_254;
        while (yytoken == Token_LBRACKET)
          {
            if (LA(2).kind != Token_COMMA && LA(2).kind != Token_RBRACKET)
              {
                break;
              }
            rank_specifier_ast *__node_255 = 0;
            if (!parse_rank_specifier(&__node_255))
              {
                return yy_expected_symbol(ast_node::Kind_rank_specifier, "rank_specifier");
              }
            (*yynode)->rank_specifier_sequence = snoc((*yynode)->rank_specifier_sequence, __node_255, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_method_declaration(method_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers, return_type_ast *return_type, type_name_safe_ast *method_name)
  {
    *yynode = create<method_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->start_token < (*yynode)->start_token)
      (*yynode)->start_token = modifiers->start_token;

    (*yynode)->return_type = return_type;
    if (return_type && return_type->start_token < (*yynode)->start_token)
      (*yynode)->start_token = return_type->start_token;

    (*yynode)->method_name = method_name;
    if (method_name && method_name->start_token < (*yynode)->start_token)
      (*yynode)->start_token = method_name->start_token;

    if (yytoken == Token_LPAREN
        || yytoken == Token_LESS_THAN)
      {
        if ((yytoken == Token_LESS_THAN) && ( compatibility_mode() >= csharp20_compatibility ))
          {
            type_parameters_ast *__node_256 = 0;
            if (!parse_type_parameters(&__node_256))
              {
                return yy_expected_symbol(ast_node::Kind_type_parameters, "type_parameters");
              }
            (*yynode)->type_parameters = __node_256;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken != Token_LPAREN)
          return yy_expected_token(yytoken, Token_LPAREN, "(");
        yylex();
        if (yytoken == Token_BOOL
            || yytoken == Token_BYTE
            || yytoken == Token_CHAR
            || yytoken == Token_DECIMAL
            || yytoken == Token_DOUBLE
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_OBJECT
            || yytoken == Token_OUT
            || yytoken == Token_PARAMS
            || yytoken == Token_REF
            || yytoken == Token_SBYTE
            || yytoken == Token_SHORT
            || yytoken == Token_STRING
            || yytoken == Token_UINT
            || yytoken == Token_ULONG
            || yytoken == Token_USHORT
            || yytoken == Token_VOID
            || yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_LBRACKET
            || yytoken == Token_IDENTIFIER)
          {
            formal_parameter_list_ast *__node_257 = 0;
            if (!parse_formal_parameter_list(&__node_257))
              {
                return yy_expected_symbol(ast_node::Kind_formal_parameter_list, "formal_parameter_list");
              }
            (*yynode)->formal_parameters = __node_257;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken != Token_RPAREN)
          return yy_expected_token(yytoken, Token_RPAREN, ")");
        yylex();
        if ((yytoken == Token_WHERE) && ( compatibility_mode() >= csharp20_compatibility ))
          {
            type_parameter_constraints_clauses_ast *__node_258 = 0;
            if (!parse_type_parameter_constraints_clauses(&__node_258))
              {
                return yy_expected_symbol(ast_node::Kind_type_parameter_constraints_clauses, "type_parameter_constraints_clauses");
              }
            (*yynode)->type_parameter_constraints_clauses = __node_258;
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        if (yytoken == Token_LBRACE)
          {
            block_ast *__node_259 = 0;
            if (!parse_block(&__node_259))
              {
                return yy_expected_symbol(ast_node::Kind_block, "block");
              }
            (*yynode)->method_body = __node_259;
          }
        else if (yytoken == Token_SEMICOLON)
          {
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_multiplicative_expression(multiplicative_expression_ast **yynode)
  {
    *yynode = create<multiplicative_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        unary_expression_ast *__node_260 = 0;
        if (!parse_unary_expression(&__node_260))
          {
            return yy_expected_symbol(ast_node::Kind_unary_expression, "unary_expression");
          }
        (*yynode)->expression = __node_260;
        while (yytoken == Token_STAR
               || yytoken == Token_SLASH
               || yytoken == Token_REMAINDER)
          {
            multiplicative_expression_rest_ast *__node_261 = 0;
            if (!parse_multiplicative_expression_rest(&__node_261))
              {
                return yy_expected_symbol(ast_node::Kind_multiplicative_expression_rest, "multiplicative_expression_rest");
              }
            (*yynode)->additional_expression_sequence = snoc((*yynode)->additional_expression_sequence, __node_261, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_multiplicative_expression_rest(multiplicative_expression_rest_ast **yynode)
  {
    *yynode = create<multiplicative_expression_rest_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_STAR
        || yytoken == Token_SLASH
        || yytoken == Token_REMAINDER)
      {
        if (yytoken == Token_STAR)
          {
            if (yytoken != Token_STAR)
              return yy_expected_token(yytoken, Token_STAR, "*");
            yylex();
            (*yynode)->multiplicative_operator = multiplicative_expression_rest::op_star;
          }
        else if (yytoken == Token_SLASH)
          {
            if (yytoken != Token_SLASH)
              return yy_expected_token(yytoken, Token_SLASH, "/");
            yylex();
            (*yynode)->multiplicative_operator = multiplicative_expression_rest::op_slash;
          }
        else if (yytoken == Token_REMAINDER)
          {
            if (yytoken != Token_REMAINDER)
              return yy_expected_token(yytoken, Token_REMAINDER, "%");
            yylex();
            (*yynode)->multiplicative_operator = multiplicative_expression_rest::op_remainder;
          }
        else
          {
            return false;
          }
        unary_expression_ast *__node_262 = 0;
        if (!parse_unary_expression(&__node_262))
          {
            return yy_expected_symbol(ast_node::Kind_unary_expression, "unary_expression");
          }
        (*yynode)->expression = __node_262;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_named_argument(named_argument_ast **yynode)
  {
    *yynode = create<named_argument_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        identifier_ast *__node_263 = 0;
        if (!parse_identifier(&__node_263))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->argument_name = __node_263;
        if (yytoken != Token_ASSIGN)
          return yy_expected_token(yytoken, Token_ASSIGN, "=");
        yylex();
        expression_ast *__node_264 = 0;
        if (!parse_expression(&__node_264))
          {
            return yy_expected_symbol(ast_node::Kind_expression, "expression");
          }
        (*yynode)->attribute_argument_expression = __node_264;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_namespace_body(namespace_body_ast **yynode)
  {
    *yynode = create<namespace_body_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LBRACE)
      {
        if (yytoken != Token_LBRACE)
          return yy_expected_token(yytoken, Token_LBRACE, "{");
        yylex();
        while (yytoken == Token_EXTERN)
          {
            extern_alias_directive_ast *__node_265 = 0;
            if (!parse_extern_alias_directive(&__node_265))
              {
                return yy_expected_symbol(ast_node::Kind_extern_alias_directive, "extern_alias_directive");
              }
            (*yynode)->extern_alias_sequence = snoc((*yynode)->extern_alias_sequence, __node_265, memory_pool);
          }
        while (yytoken == Token_USING)
          {
            using_directive_ast *__node_266 = 0;
            if (!parse_using_directive(&__node_266))
              {
                return yy_expected_symbol(ast_node::Kind_using_directive, "using_directive");
              }
            (*yynode)->using_sequence = snoc((*yynode)->using_sequence, __node_266, memory_pool);
          }
        while (yytoken == Token_ABSTRACT
               || yytoken == Token_CLASS
               || yytoken == Token_DELEGATE
               || yytoken == Token_ENUM
               || yytoken == Token_EXTERN
               || yytoken == Token_INTERFACE
               || yytoken == Token_INTERNAL
               || yytoken == Token_NAMESPACE
               || yytoken == Token_NEW
               || yytoken == Token_OVERRIDE
               || yytoken == Token_PRIVATE
               || yytoken == Token_PROTECTED
               || yytoken == Token_PUBLIC
               || yytoken == Token_READONLY
               || yytoken == Token_SEALED
               || yytoken == Token_STATIC
               || yytoken == Token_STRUCT
               || yytoken == Token_UNSAFE
               || yytoken == Token_VIRTUAL
               || yytoken == Token_VOLATILE
               || yytoken == Token_PARTIAL
               || yytoken == Token_LBRACKET)
          {
            namespace_member_declaration_ast *__node_267 = 0;
            if (!parse_namespace_member_declaration(&__node_267))
              {
                return yy_expected_symbol(ast_node::Kind_namespace_member_declaration, "namespace_member_declaration");
              }
            (*yynode)->namespace_sequence = snoc((*yynode)->namespace_sequence, __node_267, memory_pool);
          }
        if (yytoken != Token_RBRACE)
          return yy_expected_token(yytoken, Token_RBRACE, "}");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_namespace_declaration(namespace_declaration_ast **yynode)
  {
    *yynode = create<namespace_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_NAMESPACE)
      {
        if (yytoken != Token_NAMESPACE)
          return yy_expected_token(yytoken, Token_NAMESPACE, "namespace");
        yylex();
        qualified_identifier_ast *__node_268 = 0;
        if (!parse_qualified_identifier(&__node_268))
          {
            return yy_expected_symbol(ast_node::Kind_qualified_identifier, "qualified_identifier");
          }
        (*yynode)->name = __node_268;
        namespace_body_ast *__node_269 = 0;
        if (!parse_namespace_body(&__node_269))
          {
            return yy_expected_symbol(ast_node::Kind_namespace_body, "namespace_body");
          }
        (*yynode)->body = __node_269;
        if (yytoken == Token_SEMICOLON)
          {
            if (yytoken != Token_SEMICOLON)
              return yy_expected_token(yytoken, Token_SEMICOLON, ";");
            yylex();
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_namespace_member_declaration(namespace_member_declaration_ast **yynode)
  {
    *yynode = create<namespace_member_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ABSTRACT
        || yytoken == Token_CLASS
        || yytoken == Token_DELEGATE
        || yytoken == Token_ENUM
        || yytoken == Token_EXTERN
        || yytoken == Token_INTERFACE
        || yytoken == Token_INTERNAL
        || yytoken == Token_NAMESPACE
        || yytoken == Token_NEW
        || yytoken == Token_OVERRIDE
        || yytoken == Token_PRIVATE
        || yytoken == Token_PROTECTED
        || yytoken == Token_PUBLIC
        || yytoken == Token_READONLY
        || yytoken == Token_SEALED
        || yytoken == Token_STATIC
        || yytoken == Token_STRUCT
        || yytoken == Token_UNSAFE
        || yytoken == Token_VIRTUAL
        || yytoken == Token_VOLATILE
        || yytoken == Token_PARTIAL
        || yytoken == Token_LBRACKET)
      {
        if (yytoken == Token_NAMESPACE)
          {
            namespace_declaration_ast *__node_270 = 0;
            if (!parse_namespace_declaration(&__node_270))
              {
                return yy_expected_symbol(ast_node::Kind_namespace_declaration, "namespace_declaration");
              }
            (*yynode)->namespace_declaration = __node_270;
          }
        else if (yytoken == Token_ABSTRACT
                 || yytoken == Token_CLASS
                 || yytoken == Token_DELEGATE
                 || yytoken == Token_ENUM
                 || yytoken == Token_EXTERN
                 || yytoken == Token_INTERFACE
                 || yytoken == Token_INTERNAL
                 || yytoken == Token_NEW
                 || yytoken == Token_OVERRIDE
                 || yytoken == Token_PRIVATE
                 || yytoken == Token_PROTECTED
                 || yytoken == Token_PUBLIC
                 || yytoken == Token_READONLY
                 || yytoken == Token_SEALED
                 || yytoken == Token_STATIC
                 || yytoken == Token_STRUCT
                 || yytoken == Token_UNSAFE
                 || yytoken == Token_VIRTUAL
                 || yytoken == Token_VOLATILE
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_LBRACKET)
          {
            type_declaration_ast *__node_271 = 0;
            if (!parse_type_declaration(&__node_271))
              {
                return yy_expected_symbol(ast_node::Kind_type_declaration, "type_declaration");
              }
            (*yynode)->type_declaration = __node_271;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_namespace_name(namespace_name_ast **yynode)
  {
    *yynode = create<namespace_name_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        namespace_or_type_name_ast *__node_272 = 0;
        if (!parse_namespace_or_type_name(&__node_272))
          {
            return yy_expected_symbol(ast_node::Kind_namespace_or_type_name, "namespace_or_type_name");
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_namespace_or_type_name(namespace_or_type_name_ast **yynode)
  {
    *yynode = create<namespace_or_type_name_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        if ((yytoken == Token_ADD
             || yytoken == Token_ALIAS
             || yytoken == Token_GET
             || yytoken == Token_GLOBAL
             || yytoken == Token_PARTIAL
             || yytoken == Token_REMOVE
             || yytoken == Token_SET
             || yytoken == Token_VALUE
             || yytoken == Token_WHERE
             || yytoken == Token_YIELD
             || yytoken == Token_ASSEMBLY
             || yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_SCOPE ))
          {
            identifier_ast *__node_273 = 0;
            if (!parse_identifier(&__node_273))
              {
                return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
              }
            (*yynode)->qualified_alias_label = __node_273;
            if (yytoken != Token_SCOPE)
              return yy_expected_token(yytoken, Token_SCOPE, "::");
            yylex();
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        namespace_or_type_name_part_ast *__node_274 = 0;
        if (!parse_namespace_or_type_name_part(&__node_274))
          {
            return yy_expected_symbol(ast_node::Kind_namespace_or_type_name_part, "namespace_or_type_name_part");
          }
        (*yynode)->name_part_sequence = snoc((*yynode)->name_part_sequence, __node_274, memory_pool);
        while (yytoken == Token_DOT)
          {
            if (yytoken != Token_DOT)
              return yy_expected_token(yytoken, Token_DOT, ".");
            yylex();
            namespace_or_type_name_part_ast *__node_275 = 0;
            if (!parse_namespace_or_type_name_part(&__node_275))
              {
                return yy_expected_symbol(ast_node::Kind_namespace_or_type_name_part, "namespace_or_type_name_part");
              }
            (*yynode)->name_part_sequence = snoc((*yynode)->name_part_sequence, __node_275, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_namespace_or_type_name_part(namespace_or_type_name_part_ast **yynode)
  {
    *yynode = create<namespace_or_type_name_part_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        identifier_ast *__node_276 = 0;
        if (!parse_identifier(&__node_276))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->identifier = __node_276;
        if ((yytoken == Token_LESS_THAN) && ( lookahead_is_type_arguments() == true ))
          {
            type_arguments_ast *__node_277 = 0;
            if (!parse_type_arguments(&__node_277))
              {
                return yy_expected_symbol(ast_node::Kind_type_arguments, "type_arguments");
              }
            (*yynode)->type_arguments = __node_277;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_namespace_or_type_name_safe(namespace_or_type_name_safe_ast **yynode)
  {
    *yynode = create<namespace_or_type_name_safe_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        if ((yytoken == Token_ADD
             || yytoken == Token_ALIAS
             || yytoken == Token_GET
             || yytoken == Token_GLOBAL
             || yytoken == Token_PARTIAL
             || yytoken == Token_REMOVE
             || yytoken == Token_SET
             || yytoken == Token_VALUE
             || yytoken == Token_WHERE
             || yytoken == Token_YIELD
             || yytoken == Token_ASSEMBLY
             || yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_SCOPE ))
          {
            identifier_ast *__node_278 = 0;
            if (!parse_identifier(&__node_278))
              {
                return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
              }
            (*yynode)->qualified_alias_label = __node_278;
            if (yytoken != Token_SCOPE)
              return yy_expected_token(yytoken, Token_SCOPE, "::");
            yylex();
          }
        else if (true /*epsilon*/)
        {}
        else
          {
            return false;
          }
        namespace_or_type_name_part_ast *__node_279 = 0;
        if (!parse_namespace_or_type_name_part(&__node_279))
          {
            return yy_expected_symbol(ast_node::Kind_namespace_or_type_name_part, "namespace_or_type_name_part");
          }
        (*yynode)->name_part_sequence = snoc((*yynode)->name_part_sequence, __node_279, memory_pool);
        while (yytoken == Token_DOT)
          {
            if (LA(2).kind != Token_IDENTIFIER)
              break;
            if (yytoken != Token_DOT)
              return yy_expected_token(yytoken, Token_DOT, ".");
            yylex();
            namespace_or_type_name_part_ast *__node_280 = 0;
            if (!parse_namespace_or_type_name_part(&__node_280))
              {
                return yy_expected_symbol(ast_node::Kind_namespace_or_type_name_part, "namespace_or_type_name_part");
              }
            (*yynode)->name_part_sequence = snoc((*yynode)->name_part_sequence, __node_280, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_new_expression(new_expression_ast **yynode)
  {
    *yynode = create<new_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_NEW)
      {
        if (yytoken != Token_NEW)
          return yy_expected_token(yytoken, Token_NEW, "new");
        yylex();
        type_ast *__node_281 = 0;
        if (!parse_type(&__node_281))
          {
            return yy_expected_symbol(ast_node::Kind_type, "type");
          }
        (*yynode)->type = __node_281;
        if (yytoken == Token_LBRACE
            || yytoken == Token_LBRACKET)
          {
            array_creation_expression_rest_ast *__node_282 = 0;
            if (!parse_array_creation_expression_rest(&__node_282))
              {
                return yy_expected_symbol(ast_node::Kind_array_creation_expression_rest, "array_creation_expression_rest");
              }
            (*yynode)->array_creation_expression_rest = __node_282;
          }
        else if (yytoken == Token_LPAREN)
          {
            if (yytoken != Token_LPAREN)
              return yy_expected_token(yytoken, Token_LPAREN, "(");
            yylex();
            optional_argument_list_ast *__node_283 = 0;
            if (!parse_optional_argument_list(&__node_283))
              {
                return yy_expected_symbol(ast_node::Kind_optional_argument_list, "optional_argument_list");
              }
            (*yynode)->expression_or_argument_list = __node_283;
            if (yytoken != Token_RPAREN)
              return yy_expected_token(yytoken, Token_RPAREN, ")");
            yylex();
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_non_array_type(non_array_type_ast **yynode)
  {
    *yynode = create<non_array_type_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_DECIMAL
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_STRING
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        if (yytoken == Token_OBJECT
            || yytoken == Token_STRING)
          {
            builtin_class_type_ast *__node_284 = 0;
            if (!parse_builtin_class_type(&__node_284))
              {
                return yy_expected_symbol(ast_node::Kind_builtin_class_type, "builtin_class_type");
              }
            (*yynode)->builtin_class_type = __node_284;
          }
        else if (yytoken == Token_BOOL
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR
                 || yytoken == Token_DECIMAL
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_LONG
                 || yytoken == Token_SBYTE
                 || yytoken == Token_SHORT
                 || yytoken == Token_UINT
                 || yytoken == Token_ULONG
                 || yytoken == Token_USHORT
                 || yytoken == Token_ADD
                 || yytoken == Token_ALIAS
                 || yytoken == Token_GET
                 || yytoken == Token_GLOBAL
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_REMOVE
                 || yytoken == Token_SET
                 || yytoken == Token_VALUE
                 || yytoken == Token_WHERE
                 || yytoken == Token_YIELD
                 || yytoken == Token_ASSEMBLY
                 || yytoken == Token_IDENTIFIER)
          {
            optionally_nullable_type_ast *__node_285 = 0;
            if (!parse_optionally_nullable_type(&__node_285))
              {
                return yy_expected_symbol(ast_node::Kind_optionally_nullable_type, "optionally_nullable_type");
              }
            (*yynode)->optionally_nullable_type = __node_285;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_non_nullable_type(non_nullable_type_ast **yynode)
  {
    *yynode = create<non_nullable_type_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_DECIMAL
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        if (yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_IDENTIFIER)
          {
            type_name_ast *__node_286 = 0;
            if (!parse_type_name(&__node_286))
              {
                return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
              }
            (*yynode)->type_name = __node_286;
          }
        else if (yytoken == Token_BOOL
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR
                 || yytoken == Token_DECIMAL
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_LONG
                 || yytoken == Token_SBYTE
                 || yytoken == Token_SHORT
                 || yytoken == Token_UINT
                 || yytoken == Token_ULONG
                 || yytoken == Token_USHORT)
          {
            simple_type_ast *__node_287 = 0;
            if (!parse_simple_type(&__node_287))
              {
                return yy_expected_symbol(ast_node::Kind_simple_type, "simple_type");
              }
            (*yynode)->simple_type = __node_287;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_null_coalescing_expression(null_coalescing_expression_ast **yynode)
  {
    *yynode = create<null_coalescing_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        logical_or_expression_ast *__node_288 = 0;
        if (!parse_logical_or_expression(&__node_288))
          {
            return yy_expected_symbol(ast_node::Kind_logical_or_expression, "logical_or_expression");
          }
        (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_288, memory_pool);
        while (yytoken == Token_QUESTIONQUESTION)
          {
            if (yytoken != Token_QUESTIONQUESTION)
              return yy_expected_token(yytoken, Token_QUESTIONQUESTION, "??");
            yylex();
            logical_or_expression_ast *__node_289 = 0;
            if (!parse_logical_or_expression(&__node_289))
              {
                return yy_expected_symbol(ast_node::Kind_logical_or_expression, "logical_or_expression");
              }
            (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_289, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_numeric_type(numeric_type_ast **yynode)
  {
    *yynode = create<numeric_type_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_DECIMAL
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT)
      {
        if (yytoken == Token_BYTE
            || yytoken == Token_CHAR
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_SBYTE
            || yytoken == Token_SHORT
            || yytoken == Token_UINT
            || yytoken == Token_ULONG
            || yytoken == Token_USHORT)
          {
            integral_type_ast *__node_290 = 0;
            if (!parse_integral_type(&__node_290))
              {
                return yy_expected_symbol(ast_node::Kind_integral_type, "integral_type");
              }
            (*yynode)->int_type = __node_290;
            (*yynode)->type = numeric_type::type_integral;
          }
        else if (yytoken == Token_DOUBLE
                 || yytoken == Token_FLOAT)
          {
            floating_point_type_ast *__node_291 = 0;
            if (!parse_floating_point_type(&__node_291))
              {
                return yy_expected_symbol(ast_node::Kind_floating_point_type, "floating_point_type");
              }
            (*yynode)->float_type = __node_291;
            (*yynode)->type = numeric_type::type_floating_point;
          }
        else if (yytoken == Token_DECIMAL)
          {
            if (yytoken != Token_DECIMAL)
              return yy_expected_token(yytoken, Token_DECIMAL, "decimal");
            yylex();
            (*yynode)->type = numeric_type::type_decimal;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_optional_argument_list(optional_argument_list_ast **yynode)
  {
    *yynode = create<optional_argument_list_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_OUT
        || yytoken == Token_REF
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER || yytoken == Token_RPAREN)
      {
        if (yytoken == Token_BASE
            || yytoken == Token_BOOL
            || yytoken == Token_BYTE
            || yytoken == Token_CHAR
            || yytoken == Token_CHECKED
            || yytoken == Token_DECIMAL
            || yytoken == Token_DEFAULT
            || yytoken == Token_DELEGATE
            || yytoken == Token_DOUBLE
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_NEW
            || yytoken == Token_OBJECT
            || yytoken == Token_OUT
            || yytoken == Token_REF
            || yytoken == Token_SBYTE
            || yytoken == Token_SHORT
            || yytoken == Token_SIZEOF
            || yytoken == Token_STRING
            || yytoken == Token_THIS
            || yytoken == Token_TYPEOF
            || yytoken == Token_UINT
            || yytoken == Token_ULONG
            || yytoken == Token_UNCHECKED
            || yytoken == Token_USHORT
            || yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_LPAREN
            || yytoken == Token_BANG
            || yytoken == Token_TILDE
            || yytoken == Token_INCREMENT
            || yytoken == Token_DECREMENT
            || yytoken == Token_PLUS
            || yytoken == Token_MINUS
            || yytoken == Token_STAR
            || yytoken == Token_BIT_AND
            || yytoken == Token_TRUE
            || yytoken == Token_FALSE
            || yytoken == Token_NULL
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_REAL_LITERAL
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_IDENTIFIER)
          {
            argument_ast *__node_292 = 0;
            if (!parse_argument(&__node_292))
              {
                return yy_expected_symbol(ast_node::Kind_argument, "argument");
              }
            (*yynode)->argument_sequence = snoc((*yynode)->argument_sequence, __node_292, memory_pool);
            while (yytoken == Token_COMMA)
              {
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
                argument_ast *__node_293 = 0;
                if (!parse_argument(&__node_293))
                  {
                    return yy_expected_symbol(ast_node::Kind_argument, "argument");
                  }
                (*yynode)->argument_sequence = snoc((*yynode)->argument_sequence, __node_293, memory_pool);
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_optional_modifiers(optional_modifiers_ast **yynode)
  {
    *yynode = create<optional_modifiers_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ABSTRACT
        || yytoken == Token_EXTERN
        || yytoken == Token_INTERNAL
        || yytoken == Token_NEW
        || yytoken == Token_OVERRIDE
        || yytoken == Token_PRIVATE
        || yytoken == Token_PROTECTED
        || yytoken == Token_PUBLIC
        || yytoken == Token_READONLY
        || yytoken == Token_SEALED
        || yytoken == Token_STATIC
        || yytoken == Token_UNSAFE
        || yytoken == Token_VIRTUAL
        || yytoken == Token_VOLATILE || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CLASS
        || yytoken == Token_CONST
        || yytoken == Token_DECIMAL
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_EVENT
        || yytoken == Token_EXPLICIT
        || yytoken == Token_FLOAT
        || yytoken == Token_IMPLICIT
        || yytoken == Token_INT
        || yytoken == Token_INTERFACE
        || yytoken == Token_LONG
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_STRING
        || yytoken == Token_STRUCT
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT
        || yytoken == Token_VOID
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_TILDE
        || yytoken == Token_IDENTIFIER)
      {
        while (yytoken == Token_ABSTRACT
               || yytoken == Token_EXTERN
               || yytoken == Token_INTERNAL
               || yytoken == Token_NEW
               || yytoken == Token_OVERRIDE
               || yytoken == Token_PRIVATE
               || yytoken == Token_PROTECTED
               || yytoken == Token_PUBLIC
               || yytoken == Token_READONLY
               || yytoken == Token_SEALED
               || yytoken == Token_STATIC
               || yytoken == Token_UNSAFE
               || yytoken == Token_VIRTUAL
               || yytoken == Token_VOLATILE)
          {
            if (yytoken == Token_NEW)
              {
                if (yytoken != Token_NEW)
                  return yy_expected_token(yytoken, Token_NEW, "new");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_new;
              }
            else if (yytoken == Token_PUBLIC)
              {
                if (yytoken != Token_PUBLIC)
                  return yy_expected_token(yytoken, Token_PUBLIC, "public");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_public;
              }
            else if (yytoken == Token_PROTECTED)
              {
                if (yytoken != Token_PROTECTED)
                  return yy_expected_token(yytoken, Token_PROTECTED, "protected");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_protected;
              }
            else if (yytoken == Token_INTERNAL)
              {
                if (yytoken != Token_INTERNAL)
                  return yy_expected_token(yytoken, Token_INTERNAL, "internal");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_internal;
              }
            else if (yytoken == Token_PRIVATE)
              {
                if (yytoken != Token_PRIVATE)
                  return yy_expected_token(yytoken, Token_PRIVATE, "private");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_private;
              }
            else if (yytoken == Token_ABSTRACT)
              {
                if (yytoken != Token_ABSTRACT)
                  return yy_expected_token(yytoken, Token_ABSTRACT, "abstract");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_abstract;
              }
            else if (yytoken == Token_SEALED)
              {
                if (yytoken != Token_SEALED)
                  return yy_expected_token(yytoken, Token_SEALED, "sealed");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_sealed;
              }
            else if (yytoken == Token_STATIC)
              {
                if (yytoken != Token_STATIC)
                  return yy_expected_token(yytoken, Token_STATIC, "static");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_static;
              }
            else if (yytoken == Token_READONLY)
              {
                if (yytoken != Token_READONLY)
                  return yy_expected_token(yytoken, Token_READONLY, "readonly");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_readonly;
              }
            else if (yytoken == Token_VOLATILE)
              {
                if (yytoken != Token_VOLATILE)
                  return yy_expected_token(yytoken, Token_VOLATILE, "volatile");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_volatile;
              }
            else if (yytoken == Token_VIRTUAL)
              {
                if (yytoken != Token_VIRTUAL)
                  return yy_expected_token(yytoken, Token_VIRTUAL, "virtual");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_virtual;
              }
            else if (yytoken == Token_OVERRIDE)
              {
                if (yytoken != Token_OVERRIDE)
                  return yy_expected_token(yytoken, Token_OVERRIDE, "override");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_override;
              }
            else if (yytoken == Token_EXTERN)
              {
                if (yytoken != Token_EXTERN)
                  return yy_expected_token(yytoken, Token_EXTERN, "extern");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_extern;
              }
            else if (yytoken == Token_UNSAFE)
              {
                if (yytoken != Token_UNSAFE)
                  return yy_expected_token(yytoken, Token_UNSAFE, "unsafe");
                yylex();
                (*yynode)->modifiers |= modifiers::mod_unsafe;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_optionally_nullable_type(optionally_nullable_type_ast **yynode)
  {
    *yynode = create<optionally_nullable_type_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_DECIMAL
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        non_nullable_type_ast *__node_294 = 0;
        if (!parse_non_nullable_type(&__node_294))
          {
            return yy_expected_symbol(ast_node::Kind_non_nullable_type, "non_nullable_type");
          }
        (*yynode)->non_nullable_type = __node_294;
        if ((yytoken == Token_QUESTION) && ( compatibility_mode() >= csharp20_compatibility ))
          {
            if (yytoken != Token_QUESTION)
              return yy_expected_token(yytoken, Token_QUESTION, "?");
            yylex();
            (*yynode)->nullable = true;
          }
        else if (true /*epsilon*/)
          {
            (*yynode)->nullable = false;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_overloadable_binary_only_operator(overloadable_binary_only_operator_ast **yynode, overloadable_operator::overloadable_operator_enum* op)
  {
    *yynode = create<overloadable_binary_only_operator_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_EQUAL
        || yytoken == Token_LESS_THAN
        || yytoken == Token_LESS_EQUAL
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_GREATER_EQUAL
        || yytoken == Token_NOT_EQUAL
        || yytoken == Token_STAR
        || yytoken == Token_SLASH
        || yytoken == Token_BIT_AND
        || yytoken == Token_BIT_OR
        || yytoken == Token_BIT_XOR
        || yytoken == Token_REMAINDER
        || yytoken == Token_LSHIFT
        || yytoken == Token_RSHIFT)
      {
        if (yytoken == Token_STAR)
          {
            if (yytoken != Token_STAR)
              return yy_expected_token(yytoken, Token_STAR, "*");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_star;
          }
        else if (yytoken == Token_SLASH)
          {
            if (yytoken != Token_SLASH)
              return yy_expected_token(yytoken, Token_SLASH, "/");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_slash;
          }
        else if (yytoken == Token_REMAINDER)
          {
            if (yytoken != Token_REMAINDER)
              return yy_expected_token(yytoken, Token_REMAINDER, "%");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_remainder;
          }
        else if (yytoken == Token_BIT_AND)
          {
            if (yytoken != Token_BIT_AND)
              return yy_expected_token(yytoken, Token_BIT_AND, "&");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_bit_and;
          }
        else if (yytoken == Token_BIT_OR)
          {
            if (yytoken != Token_BIT_OR)
              return yy_expected_token(yytoken, Token_BIT_OR, "|");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_bit_or;
          }
        else if (yytoken == Token_BIT_XOR)
          {
            if (yytoken != Token_BIT_XOR)
              return yy_expected_token(yytoken, Token_BIT_XOR, "^");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_bit_xor;
          }
        else if (yytoken == Token_LSHIFT)
          {
            if (yytoken != Token_LSHIFT)
              return yy_expected_token(yytoken, Token_LSHIFT, "<<");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_lshift;
          }
        else if (yytoken == Token_RSHIFT)
          {
            if (yytoken != Token_RSHIFT)
              return yy_expected_token(yytoken, Token_RSHIFT, ">>");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_rshift;
          }
        else if (yytoken == Token_EQUAL)
          {
            if (yytoken != Token_EQUAL)
              return yy_expected_token(yytoken, Token_EQUAL, "==");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_equal;
          }
        else if (yytoken == Token_NOT_EQUAL)
          {
            if (yytoken != Token_NOT_EQUAL)
              return yy_expected_token(yytoken, Token_NOT_EQUAL, "!=");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_not_equal;
          }
        else if (yytoken == Token_GREATER_THAN)
          {
            if (yytoken != Token_GREATER_THAN)
              return yy_expected_token(yytoken, Token_GREATER_THAN, ">");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_greater_than;
          }
        else if (yytoken == Token_LESS_THAN)
          {
            if (yytoken != Token_LESS_THAN)
              return yy_expected_token(yytoken, Token_LESS_THAN, "<");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_less_than;
          }
        else if (yytoken == Token_GREATER_EQUAL)
          {
            if (yytoken != Token_GREATER_EQUAL)
              return yy_expected_token(yytoken, Token_GREATER_EQUAL, ">=");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_greater_equal;
          }
        else if (yytoken == Token_LESS_EQUAL)
          {
            if (yytoken != Token_LESS_EQUAL)
              return yy_expected_token(yytoken, Token_LESS_EQUAL, "<=");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_less_equal;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_overloadable_unary_only_operator(overloadable_unary_only_operator_ast **yynode, overloadable_operator::overloadable_operator_enum* op)
  {
    *yynode = create<overloadable_unary_only_operator_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE)
      {
        if (yytoken == Token_BANG)
          {
            if (yytoken != Token_BANG)
              return yy_expected_token(yytoken, Token_BANG, "!");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_bang;
          }
        else if (yytoken == Token_TILDE)
          {
            if (yytoken != Token_TILDE)
              return yy_expected_token(yytoken, Token_TILDE, "~");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_tilde;
          }
        else if (yytoken == Token_INCREMENT)
          {
            if (yytoken != Token_INCREMENT)
              return yy_expected_token(yytoken, Token_INCREMENT, "++");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_increment;
          }
        else if (yytoken == Token_DECREMENT)
          {
            if (yytoken != Token_DECREMENT)
              return yy_expected_token(yytoken, Token_DECREMENT, "--");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_decrement;
          }
        else if (yytoken == Token_TRUE)
          {
            if (yytoken != Token_TRUE)
              return yy_expected_token(yytoken, Token_TRUE, "true");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_true;
          }
        else if (yytoken == Token_FALSE)
          {
            if (yytoken != Token_FALSE)
              return yy_expected_token(yytoken, Token_FALSE, "false");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_false;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_overloadable_unary_or_binary_operator(overloadable_unary_or_binary_operator_ast **yynode, overloadable_operator::overloadable_operator_enum* op)
  {
    *yynode = create<overloadable_unary_or_binary_operator_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_PLUS
        || yytoken == Token_MINUS)
      {
        if (yytoken == Token_PLUS)
          {
            if (yytoken != Token_PLUS)
              return yy_expected_token(yytoken, Token_PLUS, "+");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_plus;
          }
        else if (yytoken == Token_MINUS)
          {
            if (yytoken != Token_MINUS)
              return yy_expected_token(yytoken, Token_MINUS, "-");
            (*yynode)->op = token_stream->index() - 1;
            yylex();
            *op = overloadable_operator::op_minus;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_parameter_array(parameter_array_ast **yynode)
  {
    *yynode = create<parameter_array_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_PARAMS)
      {
        if (yytoken != Token_PARAMS)
          return yy_expected_token(yytoken, Token_PARAMS, "params");
        yylex();
        array_type_ast *__node_295 = 0;
        if (!parse_array_type(&__node_295))
          {
            return yy_expected_symbol(ast_node::Kind_array_type, "array_type");
          }
        (*yynode)->type = __node_295;
        identifier_ast *__node_296 = 0;
        if (!parse_identifier(&__node_296))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->variable_name = __node_296;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_parameter_modifier(parameter_modifier_ast **yynode)
  {
    *yynode = create<parameter_modifier_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_OUT
        || yytoken == Token_REF)
      {
        if (yytoken == Token_REF)
          {
            if (yytoken != Token_REF)
              return yy_expected_token(yytoken, Token_REF, "ref");
            yylex();
            (*yynode)->modifier = parameter_modifier::mod_ref;
          }
        else if (yytoken == Token_OUT)
          {
            if (yytoken != Token_OUT)
              return yy_expected_token(yytoken, Token_OUT, "out");
            yylex();
            (*yynode)->modifier = parameter_modifier::mod_out;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_pointer_type(pointer_type_ast **yynode)
  {
    *yynode = create<pointer_type_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_DECIMAL
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_STRING
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT
        || yytoken == Token_VOID
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        (*yynode)->star_count = 0;
        if (yytoken == Token_BOOL
            || yytoken == Token_BYTE
            || yytoken == Token_CHAR
            || yytoken == Token_DECIMAL
            || yytoken == Token_DOUBLE
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_OBJECT
            || yytoken == Token_SBYTE
            || yytoken == Token_SHORT
            || yytoken == Token_STRING
            || yytoken == Token_UINT
            || yytoken == Token_ULONG
            || yytoken == Token_USHORT
            || yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_IDENTIFIER)
          {
            managed_type_ast *__node_297 = 0;
            if (!parse_managed_type(&__node_297))
              {
                return yy_expected_symbol(ast_node::Kind_managed_type, "managed_type");
              }
            (*yynode)->regular_type = __node_297;
            (*yynode)->type = pointer_type::type_regular;
          }
        else if (yytoken == Token_VOID)
          {
            if (yytoken != Token_VOID)
              return yy_expected_token(yytoken, Token_VOID, "void");
            yylex();
            if (yytoken != Token_STAR)
              return yy_expected_token(yytoken, Token_STAR, "*");
            yylex();
            (*yynode)->star_count++;
            (*yynode)->type = pointer_type::type_void;
          }
        else
          {
            return false;
          }
        do
          {
            if (yytoken != Token_STAR)
              return yy_expected_token(yytoken, Token_STAR, "*");
            yylex();
            (*yynode)->star_count++;
          }
        while (yytoken == Token_STAR);
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_positional_argument(positional_argument_ast **yynode)
  {
    *yynode = create<positional_argument_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        expression_ast *__node_298 = 0;
        if (!parse_expression(&__node_298))
          {
            return yy_expected_symbol(ast_node::Kind_expression, "expression");
          }
        (*yynode)->attribute_argument_expression = __node_298;
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_predefined_type(predefined_type_ast **yynode)
  {
    *yynode = create<predefined_type_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_DECIMAL
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_STRING
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_USHORT)
      {
        if (yytoken == Token_BOOL)
          {
            if (yytoken != Token_BOOL)
              return yy_expected_token(yytoken, Token_BOOL, "bool");
            yylex();
            (*yynode)->type = predefined_type::type_bool;
          }
        else if (yytoken == Token_BYTE)
          {
            if (yytoken != Token_BYTE)
              return yy_expected_token(yytoken, Token_BYTE, "byte");
            yylex();
            (*yynode)->type = predefined_type::type_byte;
          }
        else if (yytoken == Token_CHAR)
          {
            if (yytoken != Token_CHAR)
              return yy_expected_token(yytoken, Token_CHAR, "char");
            yylex();
            (*yynode)->type = predefined_type::type_char;
          }
        else if (yytoken == Token_DECIMAL)
          {
            if (yytoken != Token_DECIMAL)
              return yy_expected_token(yytoken, Token_DECIMAL, "decimal");
            yylex();
            (*yynode)->type = predefined_type::type_decimal;
          }
        else if (yytoken == Token_DOUBLE)
          {
            if (yytoken != Token_DOUBLE)
              return yy_expected_token(yytoken, Token_DOUBLE, "double");
            yylex();
            (*yynode)->type = predefined_type::type_double;
          }
        else if (yytoken == Token_FLOAT)
          {
            if (yytoken != Token_FLOAT)
              return yy_expected_token(yytoken, Token_FLOAT, "float");
            yylex();
            (*yynode)->type = predefined_type::type_float;
          }
        else if (yytoken == Token_INT)
          {
            if (yytoken != Token_INT)
              return yy_expected_token(yytoken, Token_INT, "int");
            yylex();
            (*yynode)->type = predefined_type::type_int;
          }
        else if (yytoken == Token_LONG)
          {
            if (yytoken != Token_LONG)
              return yy_expected_token(yytoken, Token_LONG, "long");
            yylex();
            (*yynode)->type = predefined_type::type_long;
          }
        else if (yytoken == Token_OBJECT)
          {
            if (yytoken != Token_OBJECT)
              return yy_expected_token(yytoken, Token_OBJECT, "object");
            yylex();
            (*yynode)->type = predefined_type::type_object;
          }
        else if (yytoken == Token_SBYTE)
          {
            if (yytoken != Token_SBYTE)
              return yy_expected_token(yytoken, Token_SBYTE, "sbyte");
            yylex();
            (*yynode)->type = predefined_type::type_sbyte;
          }
        else if (yytoken == Token_SHORT)
          {
            if (yytoken != Token_SHORT)
              return yy_expected_token(yytoken, Token_SHORT, "short");
            yylex();
            (*yynode)->type = predefined_type::type_short;
          }
        else if (yytoken == Token_STRING)
          {
            if (yytoken != Token_STRING)
              return yy_expected_token(yytoken, Token_STRING, "string");
            yylex();
            (*yynode)->type = predefined_type::type_string;
          }
        else if (yytoken == Token_UINT)
          {
            if (yytoken != Token_UINT)
              return yy_expected_token(yytoken, Token_UINT, "uint");
            yylex();
            (*yynode)->type = predefined_type::type_uint;
          }
        else if (yytoken == Token_ULONG)
          {
            if (yytoken != Token_ULONG)
              return yy_expected_token(yytoken, Token_ULONG, "ulong");
            yylex();
            (*yynode)->type = predefined_type::type_ulong;
          }
        else if (yytoken == Token_USHORT)
          {
            if (yytoken != Token_USHORT)
              return yy_expected_token(yytoken, Token_USHORT, "ushort");
            yylex();
            (*yynode)->type = predefined_type::type_ushort;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_primary_atom(primary_atom_ast **yynode)
  {
    *yynode = create<primary_atom_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        if (yytoken == Token_TRUE
            || yytoken == Token_FALSE
            || yytoken == Token_NULL
            || yytoken == Token_INTEGER_LITERAL
            || yytoken == Token_REAL_LITERAL
            || yytoken == Token_CHARACTER_LITERAL
            || yytoken == Token_STRING_LITERAL)
          {
            literal_ast *__node_299 = 0;
            if (!parse_literal(&__node_299))
              {
                return yy_expected_symbol(ast_node::Kind_literal, "literal");
              }
            (*yynode)->literal = __node_299;
            (*yynode)->rule_type = primary_atom::type_literal;
          }
        else if (yytoken == Token_LPAREN)
          {
            if (yytoken != Token_LPAREN)
              return yy_expected_token(yytoken, Token_LPAREN, "(");
            yylex();
            expression_ast *__node_300 = 0;
            if (!parse_expression(&__node_300))
              {
                return yy_expected_symbol(ast_node::Kind_expression, "expression");
              }
            (*yynode)->expression = __node_300;
            if (yytoken != Token_RPAREN)
              return yy_expected_token(yytoken, Token_RPAREN, ")");
            yylex();
            (*yynode)->rule_type = primary_atom::type_parenthesized_expression;
          }
        else if (yytoken == Token_BOOL
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR
                 || yytoken == Token_DECIMAL
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_LONG
                 || yytoken == Token_OBJECT
                 || yytoken == Token_SBYTE
                 || yytoken == Token_SHORT
                 || yytoken == Token_STRING
                 || yytoken == Token_UINT
                 || yytoken == Token_ULONG
                 || yytoken == Token_USHORT
                 || yytoken == Token_ADD
                 || yytoken == Token_ALIAS
                 || yytoken == Token_GET
                 || yytoken == Token_GLOBAL
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_REMOVE
                 || yytoken == Token_SET
                 || yytoken == Token_VALUE
                 || yytoken == Token_WHERE
                 || yytoken == Token_YIELD
                 || yytoken == Token_ASSEMBLY
                 || yytoken == Token_IDENTIFIER)
          {
            simple_name_or_member_access_ast *__node_301 = 0;
            if (!parse_simple_name_or_member_access(&__node_301))
              {
                return yy_expected_symbol(ast_node::Kind_simple_name_or_member_access, "simple_name_or_member_access");
              }
            (*yynode)->simple_name_or_member_access = __node_301;
            (*yynode)->rule_type = primary_atom::type_member_access;
          }
        else if (yytoken == Token_THIS)
          {
            if (yytoken != Token_THIS)
              return yy_expected_token(yytoken, Token_THIS, "this");
            yylex();
            (*yynode)->rule_type = primary_atom::type_this_access;
          }
        else if (yytoken == Token_BASE)
          {
            base_access_ast *__node_302 = 0;
            if (!parse_base_access(&__node_302))
              {
                return yy_expected_symbol(ast_node::Kind_base_access, "base_access");
              }
            (*yynode)->base_access = __node_302;
            (*yynode)->rule_type = primary_atom::type_base_access;
          }
        else if (yytoken == Token_NEW)
          {
            new_expression_ast *__node_303 = 0;
            if (!parse_new_expression(&__node_303))
              {
                return yy_expected_symbol(ast_node::Kind_new_expression, "new_expression");
              }
            (*yynode)->new_expression = __node_303;
            (*yynode)->rule_type = primary_atom::type_new_expression;
          }
        else if (yytoken == Token_TYPEOF)
          {
            typeof_expression_ast *__node_304 = 0;
            if (!parse_typeof_expression(&__node_304))
              {
                return yy_expected_symbol(ast_node::Kind_typeof_expression, "typeof_expression");
              }
            (*yynode)->typeof_expression = __node_304;
            (*yynode)->rule_type = primary_atom::type_typeof_expression;
          }
        else if (yytoken == Token_CHECKED)
          {
            if (yytoken != Token_CHECKED)
              return yy_expected_token(yytoken, Token_CHECKED, "checked");
            yylex();
            if (yytoken != Token_LPAREN)
              return yy_expected_token(yytoken, Token_LPAREN, "(");
            yylex();
            expression_ast *__node_305 = 0;
            if (!parse_expression(&__node_305))
              {
                return yy_expected_symbol(ast_node::Kind_expression, "expression");
              }
            (*yynode)->expression = __node_305;
            if (yytoken != Token_RPAREN)
              return yy_expected_token(yytoken, Token_RPAREN, ")");
            yylex();
            (*yynode)->rule_type = primary_atom::type_checked_expression;
          }
        else if (yytoken == Token_UNCHECKED)
          {
            if (yytoken != Token_UNCHECKED)
              return yy_expected_token(yytoken, Token_UNCHECKED, "unchecked");
            yylex();
            if (yytoken != Token_LPAREN)
              return yy_expected_token(yytoken, Token_LPAREN, "(");
            yylex();
            expression_ast *__node_306 = 0;
            if (!parse_expression(&__node_306))
              {
                return yy_expected_symbol(ast_node::Kind_expression, "expression");
              }
            (*yynode)->expression = __node_306;
            if (yytoken != Token_RPAREN)
              return yy_expected_token(yytoken, Token_RPAREN, ")");
            yylex();
            (*yynode)->rule_type = primary_atom::type_unchecked_expression;
          }
        else if (yytoken == Token_DEFAULT)
          {
            if (yytoken != Token_DEFAULT)
              return yy_expected_token(yytoken, Token_DEFAULT, "default");
            yylex();
            if (yytoken != Token_LPAREN)
              return yy_expected_token(yytoken, Token_LPAREN, "(");
            yylex();
            type_ast *__node_307 = 0;
            if (!parse_type(&__node_307))
              {
                return yy_expected_symbol(ast_node::Kind_type, "type");
              }
            (*yynode)->type = __node_307;
            if (yytoken != Token_RPAREN)
              return yy_expected_token(yytoken, Token_RPAREN, ")");
            yylex();
            (*yynode)->rule_type = primary_atom::type_default_value_expression;
          }
        else if (yytoken == Token_DELEGATE)
          {
            anonymous_method_expression_ast *__node_308 = 0;
            if (!parse_anonymous_method_expression(&__node_308))
              {
                return yy_expected_symbol(ast_node::Kind_anonymous_method_expression, "anonymous_method_expression");
              }
            (*yynode)->anonymous_method_expression = __node_308;
            (*yynode)->rule_type = primary_atom::type_anonymous_method_expression;
          }
        else if (yytoken == Token_SIZEOF)
          {
            if (yytoken != Token_SIZEOF)
              return yy_expected_token(yytoken, Token_SIZEOF, "sizeof");
            yylex();
            if (yytoken != Token_LPAREN)
              return yy_expected_token(yytoken, Token_LPAREN, "(");
            yylex();
            unmanaged_type_ast *__node_309 = 0;
            if (!parse_unmanaged_type(&__node_309))
              {
                return yy_expected_symbol(ast_node::Kind_unmanaged_type, "unmanaged_type");
              }
            (*yynode)->unmanaged_type = __node_309;
            if (yytoken != Token_RPAREN)
              return yy_expected_token(yytoken, Token_RPAREN, ")");
            yylex();
            (*yynode)->rule_type = primary_atom::type_sizeof_expression;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_primary_expression(primary_expression_ast **yynode)
  {
    *yynode = create<primary_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        primary_atom_ast *__node_310 = 0;
        if (!parse_primary_atom(&__node_310))
          {
            return yy_expected_symbol(ast_node::Kind_primary_atom, "primary_atom");
          }
        (*yynode)->primary_atom = __node_310;
        while (yytoken == Token_LPAREN
               || yytoken == Token_LBRACKET
               || yytoken == Token_DOT
               || yytoken == Token_ARROW_RIGHT
               || yytoken == Token_INCREMENT
               || yytoken == Token_DECREMENT)
          {
            primary_suffix_ast *__node_311 = 0;
            if (!parse_primary_suffix(&__node_311))
              {
                return yy_expected_symbol(ast_node::Kind_primary_suffix, "primary_suffix");
              }
            (*yynode)->primary_suffix_sequence = snoc((*yynode)->primary_suffix_sequence, __node_311, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_primary_or_secondary_constraint(primary_or_secondary_constraint_ast **yynode)
  {
    *yynode = create<primary_or_secondary_constraint_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_CLASS
        || yytoken == Token_OBJECT
        || yytoken == Token_STRING
        || yytoken == Token_STRUCT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        if (yytoken == Token_OBJECT
            || yytoken == Token_STRING
            || yytoken == Token_ADD
            || yytoken == Token_ALIAS
            || yytoken == Token_GET
            || yytoken == Token_GLOBAL
            || yytoken == Token_PARTIAL
            || yytoken == Token_REMOVE
            || yytoken == Token_SET
            || yytoken == Token_VALUE
            || yytoken == Token_WHERE
            || yytoken == Token_YIELD
            || yytoken == Token_ASSEMBLY
            || yytoken == Token_IDENTIFIER)
          {
            class_type_ast *__node_312 = 0;
            if (!parse_class_type(&__node_312))
              {
                return yy_expected_symbol(ast_node::Kind_class_type, "class_type");
              }
            (*yynode)->class_type_or_secondary_constraint = __node_312;
            (*yynode)->constraint_type = primary_or_secondary_constraint::type_type;
          }
        else if (yytoken == Token_CLASS)
          {
            if (yytoken != Token_CLASS)
              return yy_expected_token(yytoken, Token_CLASS, "class");
            yylex();
            (*yynode)->constraint_type = primary_or_secondary_constraint::type_class;
          }
        else if (yytoken == Token_STRUCT)
          {
            if (yytoken != Token_STRUCT)
              return yy_expected_token(yytoken, Token_STRUCT, "struct");
            yylex();
            (*yynode)->constraint_type = primary_or_secondary_constraint::type_struct;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_primary_suffix(primary_suffix_ast **yynode)
  {
    *yynode = create<primary_suffix_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LPAREN
        || yytoken == Token_LBRACKET
        || yytoken == Token_DOT
        || yytoken == Token_ARROW_RIGHT
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT)
      {
        if (yytoken == Token_DOT)
          {
            if (yytoken != Token_DOT)
              return yy_expected_token(yytoken, Token_DOT, ".");
            yylex();
            identifier_ast *__node_313 = 0;
            if (!parse_identifier(&__node_313))
              {
                return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
              }
            (*yynode)->member_name = __node_313;
            if ((yytoken == Token_LESS_THAN) && ( lookahead_is_type_arguments() == true ))
              {
                type_arguments_ast *__node_314 = 0;
                if (!parse_type_arguments(&__node_314))
                  {
                    return yy_expected_symbol(ast_node::Kind_type_arguments, "type_arguments");
                  }
                (*yynode)->type_arguments = __node_314;
              }
            else if (true /*epsilon*/)
            {}
            else
              {
                return false;
              }
            (*yynode)->suffix_type = primary_suffix::type_member_access;
          }
        else if (yytoken == Token_LPAREN)
          {
            if (yytoken != Token_LPAREN)
              return yy_expected_token(yytoken, Token_LPAREN, "(");
            yylex();
            optional_argument_list_ast *__node_315 = 0;
            if (!parse_optional_argument_list(&__node_315))
              {
                return yy_expected_symbol(ast_node::Kind_optional_argument_list, "optional_argument_list");
              }
            (*yynode)->arguments = __node_315;
            if (yytoken != Token_RPAREN)
              return yy_expected_token(yytoken, Token_RPAREN, ")");
            yylex();
            (*yynode)->suffix_type = primary_suffix::type_invocation;
          }
        else if (yytoken == Token_LBRACKET)
          {
            if (yytoken != Token_LBRACKET)
              return yy_expected_token(yytoken, Token_LBRACKET, "[");
            yylex();
            expression_ast *__node_316 = 0;
            if (!parse_expression(&__node_316))
              {
                return yy_expected_symbol(ast_node::Kind_expression, "expression");
              }
            (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_316, memory_pool);
            while (yytoken == Token_COMMA)
              {
                if (yytoken != Token_COMMA)
                  return yy_expected_token(yytoken, Token_COMMA, ",");
                yylex();
                expression_ast *__node_317 = 0;
                if (!parse_expression(&__node_317))
                  {
                    return yy_expected_symbol(ast_node::Kind_expression, "expression");
                  }
                (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_317, memory_pool);
              }
            if (yytoken != Token_RBRACKET)
              return yy_expected_token(yytoken, Token_RBRACKET, "]");
            yylex();
            (*yynode)->suffix_type = primary_suffix::type_element_access;
          }
        else if (yytoken == Token_INCREMENT)
          {
            if (yytoken != Token_INCREMENT)
              return yy_expected_token(yytoken, Token_INCREMENT, "++");
            yylex();
            (*yynode)->suffix_type = primary_suffix::type_increment;
          }
        else if (yytoken == Token_DECREMENT)
          {
            if (yytoken != Token_DECREMENT)
              return yy_expected_token(yytoken, Token_DECREMENT, "--");
            yylex();
            (*yynode)->suffix_type = primary_suffix::type_decrement;
          }
        else if (yytoken == Token_ARROW_RIGHT)
          {
            if (yytoken != Token_ARROW_RIGHT)
              return yy_expected_token(yytoken, Token_ARROW_RIGHT, "->");
            yylex();
            identifier_ast *__node_318 = 0;
            if (!parse_identifier(&__node_318))
              {
                return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
              }
            (*yynode)->member_name = __node_318;
            if ((yytoken == Token_LESS_THAN) && ( lookahead_is_type_arguments() == true ))
              {
                type_arguments_ast *__node_319 = 0;
                if (!parse_type_arguments(&__node_319))
                  {
                    return yy_expected_symbol(ast_node::Kind_type_arguments, "type_arguments");
                  }
                (*yynode)->type_arguments = __node_319;
              }
            else if (true /*epsilon*/)
            {}
            else
              {
                return false;
              }
            (*yynode)->suffix_type = primary_suffix::type_pointer_member_access;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_property_declaration(property_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers, type_ast *type, type_name_safe_ast *property_name)
  {
    *yynode = create<property_declaration_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    (*yynode)->attribute_sequence = attribute_sequence;
    if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
      (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

    (*yynode)->modifiers = modifiers;
    if (modifiers && modifiers->start_token < (*yynode)->start_token)
      (*yynode)->start_token = modifiers->start_token;

    (*yynode)->type = type;
    if (type && type->start_token < (*yynode)->start_token)
      (*yynode)->start_token = type->start_token;

    (*yynode)->property_name = property_name;
    if (property_name && property_name->start_token < (*yynode)->start_token)
      (*yynode)->start_token = property_name->start_token;

    if (yytoken == Token_LBRACE)
      {
        if (yytoken != Token_LBRACE)
          return yy_expected_token(yytoken, Token_LBRACE, "{");
        yylex();
        accessor_declarations_ast *__node_320 = 0;
        if (!parse_accessor_declarations(&__node_320))
          {
            return yy_expected_symbol(ast_node::Kind_accessor_declarations, "accessor_declarations");
          }
        (*yynode)->accessor_declarations = __node_320;
        if (yytoken != Token_RBRACE)
          return yy_expected_token(yytoken, Token_RBRACE, "}");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_qualified_identifier(qualified_identifier_ast **yynode)
  {
    *yynode = create<qualified_identifier_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_IDENTIFIER)
      {
        identifier_ast *__node_321 = 0;
        if (!parse_identifier(&__node_321))
          {
            return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
          }
        (*yynode)->name_sequence = snoc((*yynode)->name_sequence, __node_321, memory_pool);
        while (yytoken == Token_DOT)
          {
            if (yytoken != Token_DOT)
              return yy_expected_token(yytoken, Token_DOT, ".");
            yylex();
            identifier_ast *__node_322 = 0;
            if (!parse_identifier(&__node_322))
              {
                return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
              }
            (*yynode)->name_sequence = snoc((*yynode)->name_sequence, __node_322, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_rank_specifier(rank_specifier_ast **yynode)
  {
    *yynode = create<rank_specifier_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_LBRACKET)
      {
        if (yytoken != Token_LBRACKET)
          return yy_expected_token(yytoken, Token_LBRACKET, "[");
        yylex();
        (*yynode)->dimension_seperator_count = 0;
        while (yytoken == Token_COMMA)
          {
            if (yytoken != Token_COMMA)
              return yy_expected_token(yytoken, Token_COMMA, ",");
            yylex();
            (*yynode)->dimension_seperator_count++;
          }
        if (yytoken != Token_RBRACKET)
          return yy_expected_token(yytoken, Token_RBRACKET, "]");
        yylex();
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_relational_expression(relational_expression_ast **yynode)
  {
    *yynode = create<relational_expression_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        shift_expression_ast *__node_323 = 0;
        if (!parse_shift_expression(&__node_323))
          {
            return yy_expected_symbol(ast_node::Kind_shift_expression, "shift_expression");
          }
        (*yynode)->expression = __node_323;
        while (yytoken == Token_AS
               || yytoken == Token_IS
               || yytoken == Token_LESS_THAN
               || yytoken == Token_LESS_EQUAL
               || yytoken == Token_GREATER_THAN
               || yytoken == Token_GREATER_EQUAL)
          {
            relational_expression_rest_ast *__node_324 = 0;
            if (!parse_relational_expression_rest(&__node_324))
              {
                return yy_expected_symbol(ast_node::Kind_relational_expression_rest, "relational_expression_rest");
              }
            (*yynode)->additional_expression_sequence = snoc((*yynode)->additional_expression_sequence, __node_324, memory_pool);
          }
      }
    else
      {
        return false;
      }

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_relational_expression_rest(relational_expression_rest_ast **yynode)
  {
    *yynode = create<relational_expression_rest_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_AS
        || yytoken == Token_IS
        || yytoken == Token_LESS_THAN
        || yytoken == Token_LESS_EQUAL
        || yytoken == Token_GREATER_THAN
        || yytoken == Token_GREATER_EQUAL)
      {
        if (yytoken == Token_LESS_THAN
            || yytoken == Token_LESS_EQUAL
            || yytoken == Token_GREATER_THAN
            || yytoken == Token_GREATER_EQUAL)
          {
            if (yytoken == Token_LESS_THAN)
              {
                if (yytoken != Token_LESS_THAN)
                  return yy_expected_token(yytoken, Token_LESS_THAN, "<");
                yylex();
                (*yynode)->relational_operator = relational_expression_rest::op_less_than;
              }
            else if (yytoken == Token_GREATER_THAN)
              {
                if (yytoken != Token_GREATER_THAN)
                  return yy_expected_token(yytoken, Token_GREATER_THAN, ">");
                yylex();
                (*yynode)->relational_operator = relational_expression_rest::op_greater_than;
              }
            else if (yytoken == Token_LESS_EQUAL)
              {
                if (yytoken != Token_LESS_EQUAL)
                  return yy_expected_token(yytoken, Token_LESS_EQUAL, "<=");
                yylex();
                (*yynode)->relational_operator = relational_expression_rest::op_less_equal;
              }
            else if (yytoken == Token_GREATER_EQUAL)
              {
                if (yytoken != Token_GREATER_EQUAL)
                  return yy_expected_token(yytoken, Token_GREATER_EQUAL, ">=");
                yylex();
                (*yynode)->relational_operator = relational_expression_rest::op_greater_equal;
              }
            else
              {
                return false;
              }
            shift_expression_ast *__node_325 = 0;
            if (!parse_shift_expression(&__node_325))
              {
                return yy_expected_symbol(ast_node::Kind_shift_expression, "shift_expression");
              }
            (*yynode)->expression = __node_325;
          }
        else if (yytoken == Token_AS
                 || yytoken == Token_IS)
          {
            if (yytoken == Token_IS)
              {
                if (yytoken != Token_IS)
                  return yy_expected_token(yytoken, Token_IS, "is");
                yylex();
                (*yynode)->relational_operator = relational_expression_rest::op_is;
              }
            else if (yytoken == Token_AS)
              {
                if (yytoken != Token_AS)
                  return yy_expected_token(yytoken, Token_AS, "as");
                yylex();
                (*yynode)->relational_operator = relational_expression_rest::op_as;
              }
            else
              {
                return false;
              }
            type_ast *__node_326 = 0;
            if (!parse_type(&__node_326))
              {
                return yy_expected_symbol(ast_node::Kind_type, "type");
              }
            (*yynode)->type = __node_326;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_resource_acquisition(resource_acquisition_ast **yynode)
  {
    *yynode = create<resource_acquisition_ast>();

    (*yynode)->start_token = token_stream->index() - 1;

    if (yytoken == Token_BASE
        || yytoken == Token_BOOL
        || yytoken == Token_BYTE
        || yytoken == Token_CHAR
        || yytoken == Token_CHECKED
        || yytoken == Token_DECIMAL
        || yytoken == Token_DEFAULT
        || yytoken == Token_DELEGATE
        || yytoken == Token_DOUBLE
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_NEW
        || yytoken == Token_OBJECT
        || yytoken == Token_SBYTE
        || yytoken == Token_SHORT
        || yytoken == Token_SIZEOF
        || yytoken == Token_STRING
        || yytoken == Token_THIS
        || yytoken == Token_TYPEOF
        || yytoken == Token_UINT
        || yytoken == Token_ULONG
        || yytoken == Token_UNCHECKED
        || yytoken == Token_USHORT
        || yytoken == Token_VOID
        || yytoken == Token_ADD
        || yytoken == Token_ALIAS
        || yytoken == Token_GET
        || yytoken == Token_GLOBAL
        || yytoken == Token_PARTIAL
        || yytoken == Token_REMOVE
        || yytoken == Token_SET
        || yytoken == Token_VALUE
        || yytoken == Token_WHERE
        || yytoken == Token_YIELD
        || yytoken == Token_ASSEMBLY
        || yytoken == Token_LPAREN
        || yytoken == Token_BANG
        || yytoken == Token_TILDE
        || yytoken == Token_INCREMENT
        || yytoken == Token_DECREMENT
        || yytoken == Token_PLUS
        || yytoken == Token_MINUS
        || yytoken == Token_STAR
        || yytoken == Token_BIT_AND
        || yytoken == Token_TRUE
        || yytoken == Token_FALSE
        || yytoken == Token_NULL
        || yytoken == Token_INTEGER_LITERAL
        || yytoken == Token_REAL_LITERAL
        || yytoken == Token_CHARACTER_LITERAL
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_IDENTIFIER)
      {
        if ((yytoken == Token_BOOL
             || yytoken == Token_BYTE
             || yytoken == Token_CHAR
             || yytoken == Token_DECIMAL
             || yytoken == Token_DOUBLE
             || yytoken == Token_FLOAT
             || yytoken == Token_INT
             || yytoken == Token_LONG
             || yytoken == Token_OBJECT
             || yytoken == Token_SBYTE
             || yytoken == Token_SHORT
             || yytoken == Token_STRING
             || yytoken == Token_UINT
             || yytoken == Token_ULONG
             || yytoken == Token_USHORT
             || yytoken == Token_VOID
             || yytoken == Token_ADD
             || yytoken == Token_ALIAS
             || yytoken == Token_GET
             || yytoken == Token_GLOBAL
             || yytoken == Token_PARTIAL
             || yytoken == Token_REMOVE
             || yytoken == Token_SET
             || yytoken == Token_VALUE
             || yytoken == Token_WHERE
             || yytoken == Token_YIELD
             || yytoken == Token_ASSEMBLY
             || yytoken == Token_IDENTIFIER) && ( lookahead_is_local_variable_declaration() == true ))
          {
            local_variable_declaration_ast *__node_327 = 0;
            if (!parse_local_variable_declaration(&__node_327))
              {
                return yy_expected_symbol(ast_node::Kind_local_variable_declaration, "local_variable_declaration");
              }
            (*yynode)->local_variable_declaration = __node_327;
          }
        else if (yytoken == Token_BASE
                 || yytoken == Token_BOOL
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR
                 || yytoken == Token_CHECKED
                 || yytoken == Token_DECIMAL
                 || yytoken == Token_DEFAULT
                 || yytoken == Token_DELEGATE
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_LONG
                 || yytoken == Token_NEW
                 || yytoken == Token_OBJECT
                 || yytoken == Token_SBYTE
                 || yytoken == Token_SHORT
                 || yytoken == Token_SIZEOF
                 || yytoken == Token_STRING
                 || yytoken == Token_THIS
                 || yytoken == Token_TYPEOF
                 || yytoken == Token_UINT
                 || yytoken == Token_ULONG
                 || yytoken == Token_UNCHECKED
                 || yytoken == Token_USHORT
                 || yytoken == Token_ADD
                 || yytoken == Token_ALIAS
                 || yytoken == Token_GET
                 || yytoken == Token_GLOBAL
                 || yytoken == Token_PARTIAL
                 || yytoken == Token_REMOVE
                 || yytoken == Token_SET
                 || yytoken == Token_VALUE
                 || yytoken == Token_WHERE
                 || yytoken == Token_YIELD
                 || yytoken == Token_ASSEMBLY
                 || yytoken == Token_LPAREN
                 || yytoken == Token_BANG
                 || yytoken == Token_TILDE
                 || yytoken == Token_INCREMENT
                 || yytoken == Token_DECREMENT
                 || yytoken == Token_PLUS
                 || yytoken == Token_MINUS
                 || yytoken == Token_STAR
                 || yytoken == Token_BIT_AND
                 || yytoken == Token_TRUE
                 || yytoken == Token_FALSE
                 || yytoken == Token_NULL
                 || yytoken == Token_INTEGER_LITERAL
                 || yytoken == Token_REAL_LITERAL
                 || yytoken == Token_CHARACTER_LITERAL
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_IDENTIFIER)
          {
            expression_ast *__node_328 = 0;
            if (!parse_expression(&__node_328))
              {
                return yy_expected_symbol(ast_node::Kind_expression, "expression");
              }
            (*yynode)->expression = __node_328;
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

    (*yynode)->end_token = token_stream->index() - 1;

    return true;
  }

  bool parser::parse_return_statement(return_statement_ast **yynode)
                           {
                             *yynode = create<return_statement_ast>();

                             (*yynode)->start_token = token_stream->index() - 1;

                             if (yytoken == Token_RETURN)
                               {
                                 if (yytoken != Token_RETURN)
                                   return yy_expected_token(yytoken, Token_RETURN, "return");
                                 yylex();
                                 if (yytoken == Token_BASE
                                     || yytoken == Token_BOOL
                                     || yytoken == Token_BYTE
                                     || yytoken == Token_CHAR
                                     || yytoken == Token_CHECKED
                                     || yytoken == Token_DECIMAL
                                     || yytoken == Token_DEFAULT
                                     || yytoken == Token_DELEGATE
                                     || yytoken == Token_DOUBLE
                                     || yytoken == Token_FLOAT
                                     || yytoken == Token_INT
                                     || yytoken == Token_LONG
                                     || yytoken == Token_NEW
                                     || yytoken == Token_OBJECT
                                     || yytoken == Token_SBYTE
                                     || yytoken == Token_SHORT
                                     || yytoken == Token_SIZEOF
                                     || yytoken == Token_STRING
                                     || yytoken == Token_THIS
                                     || yytoken == Token_TYPEOF
                                     || yytoken == Token_UINT
                                     || yytoken == Token_ULONG
                                     || yytoken == Token_UNCHECKED
                                     || yytoken == Token_USHORT
                                     || yytoken == Token_ADD
                                     || yytoken == Token_ALIAS
                                     || yytoken == Token_GET
                                     || yytoken == Token_GLOBAL
                                     || yytoken == Token_PARTIAL
                                     || yytoken == Token_REMOVE
                                     || yytoken == Token_SET
                                     || yytoken == Token_VALUE
                                     || yytoken == Token_WHERE
                                     || yytoken == Token_YIELD
                                     || yytoken == Token_ASSEMBLY
                                     || yytoken == Token_LPAREN
                                     || yytoken == Token_BANG
                                     || yytoken == Token_TILDE
                                     || yytoken == Token_INCREMENT
                                     || yytoken == Token_DECREMENT
                                     || yytoken == Token_PLUS
                                     || yytoken == Token_MINUS
                                     || yytoken == Token_STAR
                                     || yytoken == Token_BIT_AND
                                     || yytoken == Token_TRUE
                                     || yytoken == Token_FALSE
                                     || yytoken == Token_NULL
                                     || yytoken == Token_INTEGER_LITERAL
                                     || yytoken == Token_REAL_LITERAL
                                     || yytoken == Token_CHARACTER_LITERAL
                                     || yytoken == Token_STRING_LITERAL
                                     || yytoken == Token_IDENTIFIER)
                                   {
                                     expression_ast *__node_329 = 0;
                                     if (!parse_expression(&__node_329))
                                       {
                                         return yy_expected_symbol(ast_node::Kind_expression, "expression");
                                       }
                                     (*yynode)->return_expression = __node_329;
                                   }
                                 else if (true /*epsilon*/)
                                 {}
                                 else
                                   {
                                     return false;
                                   }
                                 if (yytoken != Token_SEMICOLON)
                                   return yy_expected_token(yytoken, Token_SEMICOLON, ";");
                                 yylex();
                               }
                             else
                               {
                                 return false;
                               }

                             (*yynode)->end_token = token_stream->index() - 1;

                             return true;
                           }

                           bool parser::parse_return_type(return_type_ast **yynode)
                                                    {
                                                      *yynode = create<return_type_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_BOOL
                                                          || yytoken == Token_BYTE
                                                          || yytoken == Token_CHAR
                                                          || yytoken == Token_DECIMAL
                                                          || yytoken == Token_DOUBLE
                                                          || yytoken == Token_FLOAT
                                                          || yytoken == Token_INT
                                                          || yytoken == Token_LONG
                                                          || yytoken == Token_OBJECT
                                                          || yytoken == Token_SBYTE
                                                          || yytoken == Token_SHORT
                                                          || yytoken == Token_STRING
                                                          || yytoken == Token_UINT
                                                          || yytoken == Token_ULONG
                                                          || yytoken == Token_USHORT
                                                          || yytoken == Token_VOID
                                                          || yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          if ((yytoken == Token_VOID) && ( LA(2).kind != Token_STAR ))
                                                            {
                                                              if (yytoken != Token_VOID)
                                                                return yy_expected_token(yytoken, Token_VOID, "void");
                                                              yylex();
                                                              (*yynode)->type = return_type::type_void;
                                                            }
                                                          else if (yytoken == Token_BOOL
                                                                   || yytoken == Token_BYTE
                                                                   || yytoken == Token_CHAR
                                                                   || yytoken == Token_DECIMAL
                                                                   || yytoken == Token_DOUBLE
                                                                   || yytoken == Token_FLOAT
                                                                   || yytoken == Token_INT
                                                                   || yytoken == Token_LONG
                                                                   || yytoken == Token_OBJECT
                                                                   || yytoken == Token_SBYTE
                                                                   || yytoken == Token_SHORT
                                                                   || yytoken == Token_STRING
                                                                   || yytoken == Token_UINT
                                                                   || yytoken == Token_ULONG
                                                                   || yytoken == Token_USHORT
                                                                   || yytoken == Token_VOID
                                                                   || yytoken == Token_ADD
                                                                   || yytoken == Token_ALIAS
                                                                   || yytoken == Token_GET
                                                                   || yytoken == Token_GLOBAL
                                                                   || yytoken == Token_PARTIAL
                                                                   || yytoken == Token_REMOVE
                                                                   || yytoken == Token_SET
                                                                   || yytoken == Token_VALUE
                                                                   || yytoken == Token_WHERE
                                                                   || yytoken == Token_YIELD
                                                                   || yytoken == Token_ASSEMBLY
                                                                   || yytoken == Token_IDENTIFIER)
                                                            {
                                                              type_ast *__node_330 = 0;
                                                              if (!parse_type(&__node_330))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type, "type");
                                                                }
                                                              (*yynode)->regular_type = __node_330;
                                                              (*yynode)->type = return_type::type_regular;
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

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_secondary_constraints(secondary_constraints_ast **yynode)
                                                    {
                                                      *yynode = create<secondary_constraints_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          type_name_ast *__node_331 = 0;
                                                          if (!parse_type_name(&__node_331))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
                                                            }
                                                          (*yynode)->interface_type_or_type_parameter_sequence = snoc((*yynode)->interface_type_or_type_parameter_sequence, __node_331, memory_pool);
                                                          while (yytoken == Token_COMMA)
                                                            {
                                                              if (LA(2).kind == Token_NEW)
                                                                {
                                                                  break;
                                                                }
                                                              if (yytoken != Token_COMMA)
                                                                return yy_expected_token(yytoken, Token_COMMA, ",");
                                                              yylex();
                                                              type_name_ast *__node_332 = 0;
                                                              if (!parse_type_name(&__node_332))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
                                                                }
                                                              (*yynode)->interface_type_or_type_parameter_sequence = snoc((*yynode)->interface_type_or_type_parameter_sequence, __node_332, memory_pool);
                                                            }
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_shift_expression(shift_expression_ast **yynode)
                                                    {
                                                      *yynode = create<shift_expression_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_BASE
                                                          || yytoken == Token_BOOL
                                                          || yytoken == Token_BYTE
                                                          || yytoken == Token_CHAR
                                                          || yytoken == Token_CHECKED
                                                          || yytoken == Token_DECIMAL
                                                          || yytoken == Token_DEFAULT
                                                          || yytoken == Token_DELEGATE
                                                          || yytoken == Token_DOUBLE
                                                          || yytoken == Token_FLOAT
                                                          || yytoken == Token_INT
                                                          || yytoken == Token_LONG
                                                          || yytoken == Token_NEW
                                                          || yytoken == Token_OBJECT
                                                          || yytoken == Token_SBYTE
                                                          || yytoken == Token_SHORT
                                                          || yytoken == Token_SIZEOF
                                                          || yytoken == Token_STRING
                                                          || yytoken == Token_THIS
                                                          || yytoken == Token_TYPEOF
                                                          || yytoken == Token_UINT
                                                          || yytoken == Token_ULONG
                                                          || yytoken == Token_UNCHECKED
                                                          || yytoken == Token_USHORT
                                                          || yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_LPAREN
                                                          || yytoken == Token_BANG
                                                          || yytoken == Token_TILDE
                                                          || yytoken == Token_INCREMENT
                                                          || yytoken == Token_DECREMENT
                                                          || yytoken == Token_PLUS
                                                          || yytoken == Token_MINUS
                                                          || yytoken == Token_STAR
                                                          || yytoken == Token_BIT_AND
                                                          || yytoken == Token_TRUE
                                                          || yytoken == Token_FALSE
                                                          || yytoken == Token_NULL
                                                          || yytoken == Token_INTEGER_LITERAL
                                                          || yytoken == Token_REAL_LITERAL
                                                          || yytoken == Token_CHARACTER_LITERAL
                                                          || yytoken == Token_STRING_LITERAL
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          additive_expression_ast *__node_333 = 0;
                                                          if (!parse_additive_expression(&__node_333))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_additive_expression, "additive_expression");
                                                            }
                                                          (*yynode)->expression = __node_333;
                                                          while (yytoken == Token_LSHIFT
                                                                 || yytoken == Token_RSHIFT)
                                                            {
                                                              shift_expression_rest_ast *__node_334 = 0;
                                                              if (!parse_shift_expression_rest(&__node_334))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_shift_expression_rest, "shift_expression_rest");
                                                                }
                                                              (*yynode)->additional_expression_sequence = snoc((*yynode)->additional_expression_sequence, __node_334, memory_pool);
                                                            }
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_shift_expression_rest(shift_expression_rest_ast **yynode)
                                                    {
                                                      *yynode = create<shift_expression_rest_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_LSHIFT
                                                          || yytoken == Token_RSHIFT)
                                                        {
                                                          if (yytoken == Token_LSHIFT)
                                                            {
                                                              if (yytoken != Token_LSHIFT)
                                                                return yy_expected_token(yytoken, Token_LSHIFT, "<<");
                                                              yylex();
                                                              (*yynode)->shift_operator = shift_expression_rest::op_lshift;
                                                            }
                                                          else if (yytoken == Token_RSHIFT)
                                                            {
                                                              if (yytoken != Token_RSHIFT)
                                                                return yy_expected_token(yytoken, Token_RSHIFT, ">>");
                                                              yylex();
                                                              (*yynode)->shift_operator = shift_expression_rest::op_rshift;
                                                            }
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          additive_expression_ast *__node_335 = 0;
                                                          if (!parse_additive_expression(&__node_335))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_additive_expression, "additive_expression");
                                                            }
                                                          (*yynode)->expression = __node_335;
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_simple_name_or_member_access(simple_name_or_member_access_ast **yynode)
                                                    {
                                                      *yynode = create<simple_name_or_member_access_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_BOOL
                                                          || yytoken == Token_BYTE
                                                          || yytoken == Token_CHAR
                                                          || yytoken == Token_DECIMAL
                                                          || yytoken == Token_DOUBLE
                                                          || yytoken == Token_FLOAT
                                                          || yytoken == Token_INT
                                                          || yytoken == Token_LONG
                                                          || yytoken == Token_OBJECT
                                                          || yytoken == Token_SBYTE
                                                          || yytoken == Token_SHORT
                                                          || yytoken == Token_STRING
                                                          || yytoken == Token_UINT
                                                          || yytoken == Token_ULONG
                                                          || yytoken == Token_USHORT
                                                          || yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          if (yytoken == Token_ADD
                                                              || yytoken == Token_ALIAS
                                                              || yytoken == Token_GET
                                                              || yytoken == Token_GLOBAL
                                                              || yytoken == Token_PARTIAL
                                                              || yytoken == Token_REMOVE
                                                              || yytoken == Token_SET
                                                              || yytoken == Token_VALUE
                                                              || yytoken == Token_WHERE
                                                              || yytoken == Token_YIELD
                                                              || yytoken == Token_ASSEMBLY
                                                              || yytoken == Token_IDENTIFIER)
                                                            {
                                                              if ((yytoken == Token_ADD
                                                                   || yytoken == Token_ALIAS
                                                                   || yytoken == Token_GET
                                                                   || yytoken == Token_GLOBAL
                                                                   || yytoken == Token_PARTIAL
                                                                   || yytoken == Token_REMOVE
                                                                   || yytoken == Token_SET
                                                                   || yytoken == Token_VALUE
                                                                   || yytoken == Token_WHERE
                                                                   || yytoken == Token_YIELD
                                                                   || yytoken == Token_ASSEMBLY
                                                                   || yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_SCOPE ))
                                                                {
                                                                  identifier_ast *__node_336 = 0;
                                                                  if (!parse_identifier(&__node_336))
                                                                    {
                                                                      return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                                    }
                                                                  (*yynode)->qualified_alias_label = __node_336;
                                                                  if (yytoken != Token_SCOPE)
                                                                    return yy_expected_token(yytoken, Token_SCOPE, "::");
                                                                  yylex();
                                                                }
                                                              else if (true /*epsilon*/)
                                                              {}
                                                              else
                                                                {
                                                                  return false;
                                                                }
                                                              identifier_ast *__node_337 = 0;
                                                              if (!parse_identifier(&__node_337))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                                }
                                                              (*yynode)->member_name = __node_337;
                                                              if ((yytoken == Token_LESS_THAN) && ( lookahead_is_type_arguments() == true ))
                                                                {
                                                                  type_arguments_ast *__node_338 = 0;
                                                                  if (!parse_type_arguments(&__node_338))
                                                                    {
                                                                      return yy_expected_symbol(ast_node::Kind_type_arguments, "type_arguments");
                                                                    }
                                                                  (*yynode)->type_arguments = __node_338;
                                                                }
                                                              else if (true /*epsilon*/)
                                                              {}
                                                              else
                                                                {
                                                                  return false;
                                                                }
                                                            }
                                                          else if (yytoken == Token_BOOL
                                                                   || yytoken == Token_BYTE
                                                                   || yytoken == Token_CHAR
                                                                   || yytoken == Token_DECIMAL
                                                                   || yytoken == Token_DOUBLE
                                                                   || yytoken == Token_FLOAT
                                                                   || yytoken == Token_INT
                                                                   || yytoken == Token_LONG
                                                                   || yytoken == Token_OBJECT
                                                                   || yytoken == Token_SBYTE
                                                                   || yytoken == Token_SHORT
                                                                   || yytoken == Token_STRING
                                                                   || yytoken == Token_UINT
                                                                   || yytoken == Token_ULONG
                                                                   || yytoken == Token_USHORT)
                                                            {
                                                              predefined_type_ast *__node_339 = 0;
                                                              if (!parse_predefined_type(&__node_339))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_predefined_type, "predefined_type");
                                                                }
                                                              (*yynode)->predefined_type = __node_339;
                                                              if (yytoken != Token_DOT)
                                                                return yy_expected_token(yytoken, Token_DOT, ".");
                                                              yylex();
                                                              identifier_ast *__node_340 = 0;
                                                              if (!parse_identifier(&__node_340))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                                }
                                                              (*yynode)->member_name = __node_340;
                                                              if ((yytoken == Token_LESS_THAN) && ( lookahead_is_type_arguments() == true ))
                                                                {
                                                                  type_arguments_ast *__node_341 = 0;
                                                                  if (!parse_type_arguments(&__node_341))
                                                                    {
                                                                      return yy_expected_symbol(ast_node::Kind_type_arguments, "type_arguments");
                                                                    }
                                                                  (*yynode)->type_arguments = __node_341;
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
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_simple_type(simple_type_ast **yynode)
                                                    {
                                                      *yynode = create<simple_type_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_BOOL
                                                          || yytoken == Token_BYTE
                                                          || yytoken == Token_CHAR
                                                          || yytoken == Token_DECIMAL
                                                          || yytoken == Token_DOUBLE
                                                          || yytoken == Token_FLOAT
                                                          || yytoken == Token_INT
                                                          || yytoken == Token_LONG
                                                          || yytoken == Token_SBYTE
                                                          || yytoken == Token_SHORT
                                                          || yytoken == Token_UINT
                                                          || yytoken == Token_ULONG
                                                          || yytoken == Token_USHORT)
                                                        {
                                                          if (yytoken == Token_BYTE
                                                              || yytoken == Token_CHAR
                                                              || yytoken == Token_DECIMAL
                                                              || yytoken == Token_DOUBLE
                                                              || yytoken == Token_FLOAT
                                                              || yytoken == Token_INT
                                                              || yytoken == Token_LONG
                                                              || yytoken == Token_SBYTE
                                                              || yytoken == Token_SHORT
                                                              || yytoken == Token_UINT
                                                              || yytoken == Token_ULONG
                                                              || yytoken == Token_USHORT)
                                                            {
                                                              numeric_type_ast *__node_342 = 0;
                                                              if (!parse_numeric_type(&__node_342))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_numeric_type, "numeric_type");
                                                                }
                                                              (*yynode)->numeric_type = __node_342;
                                                              (*yynode)->type = simple_type::type_numeric;
                                                            }
                                                          else if (yytoken == Token_BOOL)
                                                            {
                                                              if (yytoken != Token_BOOL)
                                                                return yy_expected_token(yytoken, Token_BOOL, "bool");
                                                              yylex();
                                                              (*yynode)->type = simple_type::type_bool;
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

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_specific_catch_clause(specific_catch_clause_ast **yynode)
                                                    {
                                                      *yynode = create<specific_catch_clause_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_CATCH)
                                                        {
                                                          if (yytoken != Token_CATCH)
                                                            return yy_expected_token(yytoken, Token_CATCH, "catch");
                                                          yylex();
                                                          if (yytoken != Token_LPAREN)
                                                            return yy_expected_token(yytoken, Token_LPAREN, "(");
                                                          yylex();
                                                          class_type_ast *__node_343 = 0;
                                                          if (!parse_class_type(&__node_343))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_class_type, "class_type");
                                                            }
                                                          (*yynode)->exception_type = __node_343;
                                                          if (yytoken == Token_ADD
                                                              || yytoken == Token_ALIAS
                                                              || yytoken == Token_GET
                                                              || yytoken == Token_GLOBAL
                                                              || yytoken == Token_PARTIAL
                                                              || yytoken == Token_REMOVE
                                                              || yytoken == Token_SET
                                                              || yytoken == Token_VALUE
                                                              || yytoken == Token_WHERE
                                                              || yytoken == Token_YIELD
                                                              || yytoken == Token_ASSEMBLY
                                                              || yytoken == Token_IDENTIFIER)
                                                            {
                                                              identifier_ast *__node_344 = 0;
                                                              if (!parse_identifier(&__node_344))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                                }
                                                              (*yynode)->exception_name = __node_344;
                                                            }
                                                          else if (true /*epsilon*/)
                                                          {}
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          if (yytoken != Token_RPAREN)
                                                            return yy_expected_token(yytoken, Token_RPAREN, ")");
                                                          yylex();
                                                          block_ast *__node_345 = 0;
                                                          if (!parse_block(&__node_345))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_block, "block");
                                                            }
                                                          (*yynode)->body = __node_345;
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_stackalloc_initializer(stackalloc_initializer_ast **yynode)
                                                    {
                                                      *yynode = create<stackalloc_initializer_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_STACKALLOC)
                                                        {
                                                          if (yytoken != Token_STACKALLOC)
                                                            return yy_expected_token(yytoken, Token_STACKALLOC, "stackalloc");
                                                          yylex();
                                                          unmanaged_type_ast *__node_346 = 0;
                                                          if (!parse_unmanaged_type(&__node_346))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_unmanaged_type, "unmanaged_type");
                                                            }
                                                          if (yytoken != Token_LBRACKET)
                                                            return yy_expected_token(yytoken, Token_LBRACKET, "[");
                                                          yylex();
                                                          expression_ast *__node_347 = 0;
                                                          if (!parse_expression(&__node_347))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_expression, "expression");
                                                            }
                                                          (*yynode)->expression = __node_347;
                                                          if (yytoken != Token_RBRACKET)
                                                            return yy_expected_token(yytoken, Token_RBRACKET, "]");
                                                          yylex();
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_statement_expression(statement_expression_ast **yynode)
                                                    {
                                                      *yynode = create<statement_expression_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_BASE
                                                          || yytoken == Token_BOOL
                                                          || yytoken == Token_BYTE
                                                          || yytoken == Token_CHAR
                                                          || yytoken == Token_CHECKED
                                                          || yytoken == Token_DECIMAL
                                                          || yytoken == Token_DEFAULT
                                                          || yytoken == Token_DELEGATE
                                                          || yytoken == Token_DOUBLE
                                                          || yytoken == Token_FLOAT
                                                          || yytoken == Token_INT
                                                          || yytoken == Token_LONG
                                                          || yytoken == Token_NEW
                                                          || yytoken == Token_OBJECT
                                                          || yytoken == Token_SBYTE
                                                          || yytoken == Token_SHORT
                                                          || yytoken == Token_SIZEOF
                                                          || yytoken == Token_STRING
                                                          || yytoken == Token_THIS
                                                          || yytoken == Token_TYPEOF
                                                          || yytoken == Token_UINT
                                                          || yytoken == Token_ULONG
                                                          || yytoken == Token_UNCHECKED
                                                          || yytoken == Token_USHORT
                                                          || yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_LPAREN
                                                          || yytoken == Token_BANG
                                                          || yytoken == Token_TILDE
                                                          || yytoken == Token_INCREMENT
                                                          || yytoken == Token_DECREMENT
                                                          || yytoken == Token_PLUS
                                                          || yytoken == Token_MINUS
                                                          || yytoken == Token_STAR
                                                          || yytoken == Token_BIT_AND
                                                          || yytoken == Token_TRUE
                                                          || yytoken == Token_FALSE
                                                          || yytoken == Token_NULL
                                                          || yytoken == Token_INTEGER_LITERAL
                                                          || yytoken == Token_REAL_LITERAL
                                                          || yytoken == Token_CHARACTER_LITERAL
                                                          || yytoken == Token_STRING_LITERAL
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          expression_ast *__node_348 = 0;
                                                          if (!parse_expression(&__node_348))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_expression, "expression");
                                                            }
                                                          (*yynode)->expression = __node_348;
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_struct_body(struct_body_ast **yynode)
                                                    {
                                                      *yynode = create<struct_body_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_LBRACE)
                                                        {
                                                          if (yytoken != Token_LBRACE)
                                                            return yy_expected_token(yytoken, Token_LBRACE, "{");
                                                          yylex();
                                                          while (yytoken == Token_ABSTRACT
                                                                 || yytoken == Token_BOOL
                                                                 || yytoken == Token_BYTE
                                                                 || yytoken == Token_CHAR
                                                                 || yytoken == Token_CLASS
                                                                 || yytoken == Token_CONST
                                                                 || yytoken == Token_DECIMAL
                                                                 || yytoken == Token_DELEGATE
                                                                 || yytoken == Token_DOUBLE
                                                                 || yytoken == Token_ENUM
                                                                 || yytoken == Token_EVENT
                                                                 || yytoken == Token_EXPLICIT
                                                                 || yytoken == Token_EXTERN
                                                                 || yytoken == Token_FLOAT
                                                                 || yytoken == Token_IMPLICIT
                                                                 || yytoken == Token_INT
                                                                 || yytoken == Token_INTERFACE
                                                                 || yytoken == Token_INTERNAL
                                                                 || yytoken == Token_LONG
                                                                 || yytoken == Token_NEW
                                                                 || yytoken == Token_OBJECT
                                                                 || yytoken == Token_OVERRIDE
                                                                 || yytoken == Token_PRIVATE
                                                                 || yytoken == Token_PROTECTED
                                                                 || yytoken == Token_PUBLIC
                                                                 || yytoken == Token_READONLY
                                                                 || yytoken == Token_SBYTE
                                                                 || yytoken == Token_SEALED
                                                                 || yytoken == Token_SHORT
                                                                 || yytoken == Token_STATIC
                                                                 || yytoken == Token_STRING
                                                                 || yytoken == Token_STRUCT
                                                                 || yytoken == Token_UINT
                                                                 || yytoken == Token_ULONG
                                                                 || yytoken == Token_UNSAFE
                                                                 || yytoken == Token_USHORT
                                                                 || yytoken == Token_VIRTUAL
                                                                 || yytoken == Token_VOID
                                                                 || yytoken == Token_VOLATILE
                                                                 || yytoken == Token_ADD
                                                                 || yytoken == Token_ALIAS
                                                                 || yytoken == Token_GET
                                                                 || yytoken == Token_GLOBAL
                                                                 || yytoken == Token_PARTIAL
                                                                 || yytoken == Token_REMOVE
                                                                 || yytoken == Token_SET
                                                                 || yytoken == Token_VALUE
                                                                 || yytoken == Token_WHERE
                                                                 || yytoken == Token_YIELD
                                                                 || yytoken == Token_ASSEMBLY
                                                                 || yytoken == Token_LBRACKET
                                                                 || yytoken == Token_IDENTIFIER)
                                                            {
                                                              struct_member_declaration_ast *__node_349 = 0;
                                                              if (!parse_struct_member_declaration(&__node_349))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_struct_member_declaration, "struct_member_declaration");
                                                                }
                                                              (*yynode)->member_declaration_sequence = snoc((*yynode)->member_declaration_sequence, __node_349, memory_pool);
                                                            }
                                                          if (yytoken != Token_RBRACE)
                                                            return yy_expected_token(yytoken, Token_RBRACE, "}");
                                                          yylex();
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_struct_declaration(struct_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers, bool partial)
                                                    {
                                                      *yynode = create<struct_declaration_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      (*yynode)->attribute_sequence = attribute_sequence;
                                                      if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
                                                        (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

                                                      (*yynode)->modifiers = modifiers;
                                                      if (modifiers && modifiers->start_token < (*yynode)->start_token)
                                                        (*yynode)->start_token = modifiers->start_token;

                                                      (*yynode)->partial = partial;
                                                      if (yytoken == Token_STRUCT)
                                                        {
                                                          if (yytoken != Token_STRUCT)
                                                            return yy_expected_token(yytoken, Token_STRUCT, "struct");
                                                          yylex();
                                                          identifier_ast *__node_350 = 0;
                                                          if (!parse_identifier(&__node_350))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                            }
                                                          (*yynode)->struct_name = __node_350;
                                                          if ((yytoken == Token_LESS_THAN) && ( compatibility_mode() >= csharp20_compatibility ))
                                                            {
                                                              type_parameters_ast *__node_351 = 0;
                                                              if (!parse_type_parameters(&__node_351))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type_parameters, "type_parameters");
                                                                }
                                                              (*yynode)->type_parameters = __node_351;
                                                            }
                                                          else if (true /*epsilon*/)
                                                          {}
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          if (yytoken == Token_COLON)
                                                            {
                                                              struct_interfaces_ast *__node_352 = 0;
                                                              if (!parse_struct_interfaces(&__node_352))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_struct_interfaces, "struct_interfaces");
                                                                }
                                                              (*yynode)->struct_interfaces = __node_352;
                                                            }
                                                          else if (true /*epsilon*/)
                                                          {}
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          if ((yytoken == Token_WHERE) && ( compatibility_mode() >= csharp20_compatibility ))
                                                            {
                                                              type_parameter_constraints_clauses_ast *__node_353 = 0;
                                                              if (!parse_type_parameter_constraints_clauses(&__node_353))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type_parameter_constraints_clauses, "type_parameter_constraints_clauses");
                                                                }
                                                              (*yynode)->type_parameter_constraints_clauses = __node_353;
                                                            }
                                                          else if (true /*epsilon*/)
                                                          {}
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          struct_body_ast *__node_354 = 0;
                                                          if (!parse_struct_body(&__node_354))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_struct_body, "struct_body");
                                                            }
                                                          (*yynode)->body = __node_354;
                                                          if (yytoken == Token_SEMICOLON)
                                                            {
                                                              if (yytoken != Token_SEMICOLON)
                                                                return yy_expected_token(yytoken, Token_SEMICOLON, ";");
                                                              yylex();
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

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_struct_interfaces(struct_interfaces_ast **yynode)
                                                    {
                                                      *yynode = create<struct_interfaces_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_COLON)
                                                        {
                                                          if (yytoken != Token_COLON)
                                                            return yy_expected_token(yytoken, Token_COLON, ":");
                                                          yylex();
                                                          type_name_ast *__node_355 = 0;
                                                          if (!parse_type_name(&__node_355))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
                                                            }
                                                          (*yynode)->interface_type_sequence = snoc((*yynode)->interface_type_sequence, __node_355, memory_pool);
                                                          while (yytoken == Token_COMMA)
                                                            {
                                                              if (yytoken != Token_COMMA)
                                                                return yy_expected_token(yytoken, Token_COMMA, ",");
                                                              yylex();
                                                              type_name_ast *__node_356 = 0;
                                                              if (!parse_type_name(&__node_356))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type_name, "type_name");
                                                                }
                                                              (*yynode)->interface_type_sequence = snoc((*yynode)->interface_type_sequence, __node_356, memory_pool);
                                                            }
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_struct_member_declaration(struct_member_declaration_ast **yynode)
                                                    {
                                                      *yynode = create<struct_member_declaration_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_ABSTRACT
                                                          || yytoken == Token_BOOL
                                                          || yytoken == Token_BYTE
                                                          || yytoken == Token_CHAR
                                                          || yytoken == Token_CLASS
                                                          || yytoken == Token_CONST
                                                          || yytoken == Token_DECIMAL
                                                          || yytoken == Token_DELEGATE
                                                          || yytoken == Token_DOUBLE
                                                          || yytoken == Token_ENUM
                                                          || yytoken == Token_EVENT
                                                          || yytoken == Token_EXPLICIT
                                                          || yytoken == Token_EXTERN
                                                          || yytoken == Token_FLOAT
                                                          || yytoken == Token_IMPLICIT
                                                          || yytoken == Token_INT
                                                          || yytoken == Token_INTERFACE
                                                          || yytoken == Token_INTERNAL
                                                          || yytoken == Token_LONG
                                                          || yytoken == Token_NEW
                                                          || yytoken == Token_OBJECT
                                                          || yytoken == Token_OVERRIDE
                                                          || yytoken == Token_PRIVATE
                                                          || yytoken == Token_PROTECTED
                                                          || yytoken == Token_PUBLIC
                                                          || yytoken == Token_READONLY
                                                          || yytoken == Token_SBYTE
                                                          || yytoken == Token_SEALED
                                                          || yytoken == Token_SHORT
                                                          || yytoken == Token_STATIC
                                                          || yytoken == Token_STRING
                                                          || yytoken == Token_STRUCT
                                                          || yytoken == Token_UINT
                                                          || yytoken == Token_ULONG
                                                          || yytoken == Token_UNSAFE
                                                          || yytoken == Token_USHORT
                                                          || yytoken == Token_VIRTUAL
                                                          || yytoken == Token_VOID
                                                          || yytoken == Token_VOLATILE
                                                          || yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_LBRACKET
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          const list_node<attribute_section_ast *> *attribute_sequence = 0;

                                                          optional_modifiers_ast *modifiers = 0;

                                                          while (yytoken == Token_LBRACKET)
                                                            {
                                                              attribute_section_ast *__node_357 = 0;
                                                              if (!parse_attribute_section(&__node_357))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
                                                                }
                                                              attribute_sequence = snoc(attribute_sequence, __node_357, memory_pool);
                                                            }
                                                          optional_modifiers_ast *__node_358 = 0;
                                                          if (!parse_optional_modifiers(&__node_358))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_optional_modifiers, "optional_modifiers");
                                                            }
                                                          modifiers = __node_358;
                                                          class_or_struct_member_declaration_ast *__node_359 = 0;
                                                          if (!parse_class_or_struct_member_declaration(&__node_359, attribute_sequence, modifiers ))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_class_or_struct_member_declaration, "class_or_struct_member_declaration");
                                                            }
                                                          (*yynode)->declaration = __node_359;
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_switch_label(switch_label_ast **yynode)
                                                    {
                                                      *yynode = create<switch_label_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_CASE
                                                          || yytoken == Token_DEFAULT)
                                                        {
                                                          if (yytoken == Token_CASE)
                                                            {
                                                              if (yytoken != Token_CASE)
                                                                return yy_expected_token(yytoken, Token_CASE, "case");
                                                              yylex();
                                                              constant_expression_ast *__node_360 = 0;
                                                              if (!parse_constant_expression(&__node_360))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_constant_expression, "constant_expression");
                                                                }
                                                              (*yynode)->case_expression = __node_360;
                                                              (*yynode)->branch_type = switch_label::case_branch;
                                                            }
                                                          else if (yytoken == Token_DEFAULT)
                                                            {
                                                              if (yytoken != Token_DEFAULT)
                                                                return yy_expected_token(yytoken, Token_DEFAULT, "default");
                                                              yylex();
                                                              (*yynode)->branch_type = switch_label::default_branch;
                                                            }
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          if (yytoken != Token_COLON)
                                                            return yy_expected_token(yytoken, Token_COLON, ":");
                                                          yylex();
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_switch_section(switch_section_ast **yynode)
                                                    {
                                                      *yynode = create<switch_section_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_CASE
                                                          || yytoken == Token_DEFAULT)
                                                        {
                                                          do
                                                            {
                                                              switch_label_ast *__node_361 = 0;
                                                              if (!parse_switch_label(&__node_361))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_switch_label, "switch_label");
                                                                }
                                                              (*yynode)->label_sequence = snoc((*yynode)->label_sequence, __node_361, memory_pool);
                                                            }
                                                          while (yytoken == Token_CASE
                                                                 || yytoken == Token_DEFAULT);
                                                          do
                                                            {
                                                              if (yytoken == Token_DEFAULT && LA(2).kind != Token_LPAREN)
                                                                {
                                                                  break;
                                                                }  // don't give in to default_value_expression
                                                              block_statement_ast *__node_362 = 0;
                                                              if (!parse_block_statement(&__node_362))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_block_statement, "block_statement");
                                                                }
                                                              (*yynode)->statement_sequence = snoc((*yynode)->statement_sequence, __node_362, memory_pool);
                                                            }
                                                          while (yytoken == Token_BASE
                                                                 || yytoken == Token_BOOL
                                                                 || yytoken == Token_BREAK
                                                                 || yytoken == Token_BYTE
                                                                 || yytoken == Token_CHAR
                                                                 || yytoken == Token_CHECKED
                                                                 || yytoken == Token_CONST
                                                                 || yytoken == Token_CONTINUE
                                                                 || yytoken == Token_DECIMAL
                                                                 || yytoken == Token_DEFAULT
                                                                 || yytoken == Token_DELEGATE
                                                                 || yytoken == Token_DO
                                                                 || yytoken == Token_DOUBLE
                                                                 || yytoken == Token_FIXED
                                                                 || yytoken == Token_FLOAT
                                                                 || yytoken == Token_FOREACH
                                                                 || yytoken == Token_FOR
                                                                 || yytoken == Token_GOTO
                                                                 || yytoken == Token_IF
                                                                 || yytoken == Token_INT
                                                                 || yytoken == Token_LOCK
                                                                 || yytoken == Token_LONG
                                                                 || yytoken == Token_NEW
                                                                 || yytoken == Token_OBJECT
                                                                 || yytoken == Token_RETURN
                                                                 || yytoken == Token_SBYTE
                                                                 || yytoken == Token_SHORT
                                                                 || yytoken == Token_SIZEOF
                                                                 || yytoken == Token_STRING
                                                                 || yytoken == Token_SWITCH
                                                                 || yytoken == Token_THIS
                                                                 || yytoken == Token_THROW
                                                                 || yytoken == Token_TRY
                                                                 || yytoken == Token_TYPEOF
                                                                 || yytoken == Token_UINT
                                                                 || yytoken == Token_ULONG
                                                                 || yytoken == Token_UNCHECKED
                                                                 || yytoken == Token_UNSAFE
                                                                 || yytoken == Token_USHORT
                                                                 || yytoken == Token_USING
                                                                 || yytoken == Token_VOID
                                                                 || yytoken == Token_WHILE
                                                                 || yytoken == Token_ADD
                                                                 || yytoken == Token_ALIAS
                                                                 || yytoken == Token_GET
                                                                 || yytoken == Token_GLOBAL
                                                                 || yytoken == Token_PARTIAL
                                                                 || yytoken == Token_REMOVE
                                                                 || yytoken == Token_SET
                                                                 || yytoken == Token_VALUE
                                                                 || yytoken == Token_WHERE
                                                                 || yytoken == Token_YIELD
                                                                 || yytoken == Token_ASSEMBLY
                                                                 || yytoken == Token_LPAREN
                                                                 || yytoken == Token_LBRACE
                                                                 || yytoken == Token_SEMICOLON
                                                                 || yytoken == Token_BANG
                                                                 || yytoken == Token_TILDE
                                                                 || yytoken == Token_INCREMENT
                                                                 || yytoken == Token_DECREMENT
                                                                 || yytoken == Token_PLUS
                                                                 || yytoken == Token_MINUS
                                                                 || yytoken == Token_STAR
                                                                 || yytoken == Token_BIT_AND
                                                                 || yytoken == Token_TRUE
                                                                 || yytoken == Token_FALSE
                                                                 || yytoken == Token_NULL
                                                                 || yytoken == Token_INTEGER_LITERAL
                                                                 || yytoken == Token_REAL_LITERAL
                                                                 || yytoken == Token_CHARACTER_LITERAL
                                                                 || yytoken == Token_STRING_LITERAL
                                                                 || yytoken == Token_IDENTIFIER);
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_switch_statement(switch_statement_ast **yynode)
                                                    {
                                                      *yynode = create<switch_statement_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_SWITCH)
                                                        {
                                                          if (yytoken != Token_SWITCH)
                                                            return yy_expected_token(yytoken, Token_SWITCH, "switch");
                                                          yylex();
                                                          if (yytoken != Token_LPAREN)
                                                            return yy_expected_token(yytoken, Token_LPAREN, "(");
                                                          yylex();
                                                          expression_ast *__node_363 = 0;
                                                          if (!parse_expression(&__node_363))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_expression, "expression");
                                                            }
                                                          (*yynode)->switch_expression = __node_363;
                                                          if (yytoken != Token_RPAREN)
                                                            return yy_expected_token(yytoken, Token_RPAREN, ")");
                                                          yylex();
                                                          if (yytoken != Token_LBRACE)
                                                            return yy_expected_token(yytoken, Token_LBRACE, "{");
                                                          yylex();
                                                          while (yytoken == Token_CASE
                                                                 || yytoken == Token_DEFAULT)
                                                            {
                                                              switch_section_ast *__node_364 = 0;
                                                              if (!parse_switch_section(&__node_364))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_switch_section, "switch_section");
                                                                }
                                                              (*yynode)->switch_section_sequence = snoc((*yynode)->switch_section_sequence, __node_364, memory_pool);
                                                            }
                                                          if (yytoken != Token_RBRACE)
                                                            return yy_expected_token(yytoken, Token_RBRACE, "}");
                                                          yylex();
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_throw_statement(throw_statement_ast **yynode)
                                                    {
                                                      *yynode = create<throw_statement_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_THROW)
                                                        {
                                                          if (yytoken != Token_THROW)
                                                            return yy_expected_token(yytoken, Token_THROW, "throw");
                                                          yylex();
                                                          if (yytoken == Token_BASE
                                                              || yytoken == Token_BOOL
                                                              || yytoken == Token_BYTE
                                                              || yytoken == Token_CHAR
                                                              || yytoken == Token_CHECKED
                                                              || yytoken == Token_DECIMAL
                                                              || yytoken == Token_DEFAULT
                                                              || yytoken == Token_DELEGATE
                                                              || yytoken == Token_DOUBLE
                                                              || yytoken == Token_FLOAT
                                                              || yytoken == Token_INT
                                                              || yytoken == Token_LONG
                                                              || yytoken == Token_NEW
                                                              || yytoken == Token_OBJECT
                                                              || yytoken == Token_SBYTE
                                                              || yytoken == Token_SHORT
                                                              || yytoken == Token_SIZEOF
                                                              || yytoken == Token_STRING
                                                              || yytoken == Token_THIS
                                                              || yytoken == Token_TYPEOF
                                                              || yytoken == Token_UINT
                                                              || yytoken == Token_ULONG
                                                              || yytoken == Token_UNCHECKED
                                                              || yytoken == Token_USHORT
                                                              || yytoken == Token_ADD
                                                              || yytoken == Token_ALIAS
                                                              || yytoken == Token_GET
                                                              || yytoken == Token_GLOBAL
                                                              || yytoken == Token_PARTIAL
                                                              || yytoken == Token_REMOVE
                                                              || yytoken == Token_SET
                                                              || yytoken == Token_VALUE
                                                              || yytoken == Token_WHERE
                                                              || yytoken == Token_YIELD
                                                              || yytoken == Token_ASSEMBLY
                                                              || yytoken == Token_LPAREN
                                                              || yytoken == Token_BANG
                                                              || yytoken == Token_TILDE
                                                              || yytoken == Token_INCREMENT
                                                              || yytoken == Token_DECREMENT
                                                              || yytoken == Token_PLUS
                                                              || yytoken == Token_MINUS
                                                              || yytoken == Token_STAR
                                                              || yytoken == Token_BIT_AND
                                                              || yytoken == Token_TRUE
                                                              || yytoken == Token_FALSE
                                                              || yytoken == Token_NULL
                                                              || yytoken == Token_INTEGER_LITERAL
                                                              || yytoken == Token_REAL_LITERAL
                                                              || yytoken == Token_CHARACTER_LITERAL
                                                              || yytoken == Token_STRING_LITERAL
                                                              || yytoken == Token_IDENTIFIER)
                                                            {
                                                              expression_ast *__node_365 = 0;
                                                              if (!parse_expression(&__node_365))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_expression, "expression");
                                                                }
                                                              (*yynode)->exception = __node_365;
                                                            }
                                                          else if (true /*epsilon*/)
                                                          {}
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          if (yytoken != Token_SEMICOLON)
                                                            return yy_expected_token(yytoken, Token_SEMICOLON, ";");
                                                          yylex();
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_try_statement(try_statement_ast **yynode)
                                                    {
                                                      *yynode = create<try_statement_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_TRY)
                                                        {
                                                          if (yytoken != Token_TRY)
                                                            return yy_expected_token(yytoken, Token_TRY, "try");
                                                          yylex();
                                                          block_ast *__node_366 = 0;
                                                          if (!parse_block(&__node_366))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_block, "block");
                                                            }
                                                          (*yynode)->try_body = __node_366;
                                                          if (yytoken == Token_CATCH)
                                                            {
                                                              catch_clauses_ast *__node_367 = 0;
                                                              if (!parse_catch_clauses(&__node_367))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_catch_clauses, "catch_clauses");
                                                                }
                                                              (*yynode)->catch_clauses = __node_367;
                                                              if (yytoken == Token_FINALLY)
                                                                {
                                                                  if (yytoken != Token_FINALLY)
                                                                    return yy_expected_token(yytoken, Token_FINALLY, "finally");
                                                                  yylex();
                                                                  block_ast *__node_368 = 0;
                                                                  if (!parse_block(&__node_368))
                                                                    {
                                                                      return yy_expected_symbol(ast_node::Kind_block, "block");
                                                                    }
                                                                  (*yynode)->finally_body = __node_368;
                                                                }
                                                              else if (true /*epsilon*/)
                                                              {}
                                                              else
                                                                {
                                                                  return false;
                                                                }
                                                            }
                                                          else if (yytoken == Token_FINALLY)
                                                            {
                                                              if (yytoken != Token_FINALLY)
                                                                return yy_expected_token(yytoken, Token_FINALLY, "finally");
                                                              yylex();
                                                              block_ast *__node_369 = 0;
                                                              if (!parse_block(&__node_369))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_block, "block");
                                                                }
                                                              (*yynode)->finally_body = __node_369;
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

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_type(type_ast **yynode)
                                                    {
                                                      *yynode = create<type_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_BOOL
                                                          || yytoken == Token_BYTE
                                                          || yytoken == Token_CHAR
                                                          || yytoken == Token_DECIMAL
                                                          || yytoken == Token_DOUBLE
                                                          || yytoken == Token_FLOAT
                                                          || yytoken == Token_INT
                                                          || yytoken == Token_LONG
                                                          || yytoken == Token_OBJECT
                                                          || yytoken == Token_SBYTE
                                                          || yytoken == Token_SHORT
                                                          || yytoken == Token_STRING
                                                          || yytoken == Token_UINT
                                                          || yytoken == Token_ULONG
                                                          || yytoken == Token_USHORT
                                                          || yytoken == Token_VOID
                                                          || yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          unmanaged_type_ast *__node_370 = 0;
                                                          if (!parse_unmanaged_type(&__node_370))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_unmanaged_type, "unmanaged_type");
                                                            }
                                                          (*yynode)->unmanaged_type = __node_370;
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_type_arguments(type_arguments_ast **yynode)
                                                    {
                                                      *yynode = create<type_arguments_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_LESS_THAN)
                                                        {
                                                          if (yytoken != Token_LESS_THAN)
                                                            return yy_expected_token(yytoken, Token_LESS_THAN, "<");
                                                          yylex();
                                                          int currentLtLevel = _M_ltCounter;
                                                          _M_ltCounter++;
                                                          type_ast *__node_371 = 0;
                                                          if (!parse_type(&__node_371))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_type, "type");
                                                            }
                                                          (*yynode)->type_argument_sequence = snoc((*yynode)->type_argument_sequence, __node_371, memory_pool);
                                                          while (yytoken == Token_COMMA)
                                                            {
                                                              if (yytoken != Token_COMMA)
                                                                return yy_expected_token(yytoken, Token_COMMA, ",");
                                                              yylex();
                                                              type_ast *__node_372 = 0;
                                                              if (!parse_type(&__node_372))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type, "type");
                                                                }
                                                              (*yynode)->type_argument_sequence = snoc((*yynode)->type_argument_sequence, __node_372, memory_pool);
                                                            }
                                                          if (yytoken == Token_GREATER_THAN
                                                              || yytoken == Token_RSHIFT)
                                                            {
                                                              type_arguments_or_parameters_end_ast *__node_373 = 0;
                                                              if (!parse_type_arguments_or_parameters_end(&__node_373))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type_arguments_or_parameters_end, "type_arguments_or_parameters_end");
                                                                }
                                                            }
                                                          else if (true /*epsilon*/)
                                                          {}
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          if ( currentLtLevel == 0 && _M_ltCounter != currentLtLevel )
                                                            {
                                                              report_problem(error, "The amount of closing ``>'' characters is incorrect");
                                                              return false;
                                                            }
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_type_arguments_or_parameters_end(type_arguments_or_parameters_end_ast **yynode)
                                                    {
                                                      *yynode = create<type_arguments_or_parameters_end_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_GREATER_THAN
                                                          || yytoken == Token_RSHIFT)
                                                        {
                                                          if (yytoken == Token_GREATER_THAN)
                                                            {
                                                              if (yytoken != Token_GREATER_THAN)
                                                                return yy_expected_token(yytoken, Token_GREATER_THAN, ">");
                                                              yylex();
                                                              _M_ltCounter -= 1;
                                                            }
                                                          else if (yytoken == Token_RSHIFT)
                                                            {
                                                              if (yytoken != Token_RSHIFT)
                                                                return yy_expected_token(yytoken, Token_RSHIFT, ">>");
                                                              yylex();
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

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_type_declaration(type_declaration_ast **yynode)
                                                    {
                                                      *yynode = create<type_declaration_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_ABSTRACT
                                                          || yytoken == Token_CLASS
                                                          || yytoken == Token_DELEGATE
                                                          || yytoken == Token_ENUM
                                                          || yytoken == Token_EXTERN
                                                          || yytoken == Token_INTERFACE
                                                          || yytoken == Token_INTERNAL
                                                          || yytoken == Token_NEW
                                                          || yytoken == Token_OVERRIDE
                                                          || yytoken == Token_PRIVATE
                                                          || yytoken == Token_PROTECTED
                                                          || yytoken == Token_PUBLIC
                                                          || yytoken == Token_READONLY
                                                          || yytoken == Token_SEALED
                                                          || yytoken == Token_STATIC
                                                          || yytoken == Token_STRUCT
                                                          || yytoken == Token_UNSAFE
                                                          || yytoken == Token_VIRTUAL
                                                          || yytoken == Token_VOLATILE
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_LBRACKET)
                                                        {
                                                          const list_node<attribute_section_ast *> *attribute_sequence = 0;

                                                          optional_modifiers_ast *modifiers = 0;

                                                          while (yytoken == Token_LBRACKET)
                                                            {
                                                              attribute_section_ast *__node_374 = 0;
                                                              if (!parse_attribute_section(&__node_374))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
                                                                }
                                                              attribute_sequence = snoc(attribute_sequence, __node_374, memory_pool);
                                                            }
                                                          optional_modifiers_ast *__node_375 = 0;
                                                          if (!parse_optional_modifiers(&__node_375))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_optional_modifiers, "optional_modifiers");
                                                            }
                                                          modifiers = __node_375;
                                                          type_declaration_rest_ast *__node_376 = 0;
                                                          if (!parse_type_declaration_rest(&__node_376, attribute_sequence, modifiers ))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_type_declaration_rest, "type_declaration_rest");
                                                            }
                                                          (*yynode)->rest = __node_376;
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_type_declaration_rest(type_declaration_rest_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers)
                                                    {
                                                      *yynode = create<type_declaration_rest_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_CLASS
                                                          || yytoken == Token_DELEGATE
                                                          || yytoken == Token_ENUM
                                                          || yytoken == Token_INTERFACE
                                                          || yytoken == Token_STRUCT
                                                          || yytoken == Token_PARTIAL)
                                                        {
                                                          if (yytoken == Token_PARTIAL)
                                                            {
                                                              if (yytoken != Token_PARTIAL)
                                                                return yy_expected_token(yytoken, Token_PARTIAL, "partial");
                                                              yylex();
                                                              if (yytoken == Token_CLASS)
                                                                {
                                                                  class_declaration_ast *__node_377 = 0;
                                                                  if (!parse_class_declaration(&__node_377, attribute_sequence, modifiers, true ))
                                                                    {
                                                                      return yy_expected_symbol(ast_node::Kind_class_declaration, "class_declaration");
                                                                    }
                                                                  if (__node_377->start_token < (*yynode)->start_token)
                                                                    (*yynode)->start_token = __node_377->start_token;
                                                                  (*yynode)->class_declaration = __node_377;
                                                                }
                                                              else if (yytoken == Token_STRUCT)
                                                                {
                                                                  struct_declaration_ast *__node_378 = 0;
                                                                  if (!parse_struct_declaration(&__node_378, attribute_sequence, modifiers, true ))
                                                                    {
                                                                      return yy_expected_symbol(ast_node::Kind_struct_declaration, "struct_declaration");
                                                                    }
                                                                  if (__node_378->start_token < (*yynode)->start_token)
                                                                    (*yynode)->start_token = __node_378->start_token;
                                                                  (*yynode)->struct_declaration = __node_378;
                                                                }
                                                              else if (yytoken == Token_INTERFACE)
                                                                {
                                                                  interface_declaration_ast *__node_379 = 0;
                                                                  if (!parse_interface_declaration(&__node_379, attribute_sequence, modifiers, true ))
                                                                    {
                                                                      return yy_expected_symbol(ast_node::Kind_interface_declaration, "interface_declaration");
                                                                    }
                                                                  if (__node_379->start_token < (*yynode)->start_token)
                                                                    (*yynode)->start_token = __node_379->start_token;
                                                                  (*yynode)->interface_declaration = __node_379;
                                                                }
                                                              else
                                                                {
                                                                  return false;
                                                                }
                                                            }
                                                          else if (yytoken == Token_CLASS)
                                                            {
                                                              class_declaration_ast *__node_380 = 0;
                                                              if (!parse_class_declaration(&__node_380, attribute_sequence, modifiers, false ))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_class_declaration, "class_declaration");
                                                                }
                                                              if (__node_380->start_token < (*yynode)->start_token)
                                                                (*yynode)->start_token = __node_380->start_token;
                                                              (*yynode)->class_declaration = __node_380;
                                                            }
                                                          else if (yytoken == Token_STRUCT)
                                                            {
                                                              struct_declaration_ast *__node_381 = 0;
                                                              if (!parse_struct_declaration(&__node_381, attribute_sequence, modifiers, false ))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_struct_declaration, "struct_declaration");
                                                                }
                                                              if (__node_381->start_token < (*yynode)->start_token)
                                                                (*yynode)->start_token = __node_381->start_token;
                                                              (*yynode)->struct_declaration = __node_381;
                                                            }
                                                          else if (yytoken == Token_INTERFACE)
                                                            {
                                                              interface_declaration_ast *__node_382 = 0;
                                                              if (!parse_interface_declaration(&__node_382, attribute_sequence, modifiers, false ))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_interface_declaration, "interface_declaration");
                                                                }
                                                              if (__node_382->start_token < (*yynode)->start_token)
                                                                (*yynode)->start_token = __node_382->start_token;
                                                              (*yynode)->interface_declaration = __node_382;
                                                            }
                                                          else if (yytoken == Token_ENUM)
                                                            {
                                                              enum_declaration_ast *__node_383 = 0;
                                                              if (!parse_enum_declaration(&__node_383, attribute_sequence, modifiers ))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_enum_declaration, "enum_declaration");
                                                                }
                                                              if (__node_383->start_token < (*yynode)->start_token)
                                                                (*yynode)->start_token = __node_383->start_token;
                                                              (*yynode)->enum_declaration = __node_383;
                                                            }
                                                          else if (yytoken == Token_DELEGATE)
                                                            {
                                                              delegate_declaration_ast *__node_384 = 0;
                                                              if (!parse_delegate_declaration(&__node_384, attribute_sequence, modifiers ))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_delegate_declaration, "delegate_declaration");
                                                                }
                                                              if (__node_384->start_token < (*yynode)->start_token)
                                                                (*yynode)->start_token = __node_384->start_token;
                                                              (*yynode)->delegate_declaration = __node_384;
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

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_type_name(type_name_ast **yynode)
                                                    {
                                                      *yynode = create<type_name_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          namespace_or_type_name_ast *__node_385 = 0;
                                                          if (!parse_namespace_or_type_name(&__node_385))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_namespace_or_type_name, "namespace_or_type_name");
                                                            }
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_type_name_safe(type_name_safe_ast **yynode)
                                                    {
                                                      *yynode = create<type_name_safe_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          namespace_or_type_name_safe_ast *__node_386 = 0;
                                                          if (!parse_namespace_or_type_name_safe(&__node_386))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_namespace_or_type_name_safe, "namespace_or_type_name_safe");
                                                            }
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_type_parameter(type_parameter_ast **yynode)
                                                    {
                                                      *yynode = create<type_parameter_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_LBRACKET
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          while (yytoken == Token_LBRACKET)
                                                            {
                                                              attribute_section_ast *__node_387 = 0;
                                                              if (!parse_attribute_section(&__node_387))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_attribute_section, "attribute_section");
                                                                }
                                                              (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_387, memory_pool);
                                                            }
                                                          identifier_ast *__node_388 = 0;
                                                          if (!parse_identifier(&__node_388))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                            }
                                                          (*yynode)->parameter_name = __node_388;
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_type_parameter_constraints(type_parameter_constraints_ast **yynode)
                                                    {
                                                      *yynode = create<type_parameter_constraints_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_CLASS
                                                          || yytoken == Token_NEW
                                                          || yytoken == Token_OBJECT
                                                          || yytoken == Token_STRING
                                                          || yytoken == Token_STRUCT
                                                          || yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          if (yytoken == Token_CLASS
                                                              || yytoken == Token_OBJECT
                                                              || yytoken == Token_STRING
                                                              || yytoken == Token_STRUCT
                                                              || yytoken == Token_ADD
                                                              || yytoken == Token_ALIAS
                                                              || yytoken == Token_GET
                                                              || yytoken == Token_GLOBAL
                                                              || yytoken == Token_PARTIAL
                                                              || yytoken == Token_REMOVE
                                                              || yytoken == Token_SET
                                                              || yytoken == Token_VALUE
                                                              || yytoken == Token_WHERE
                                                              || yytoken == Token_YIELD
                                                              || yytoken == Token_ASSEMBLY
                                                              || yytoken == Token_IDENTIFIER)
                                                            {
                                                              primary_or_secondary_constraint_ast *__node_389 = 0;
                                                              if (!parse_primary_or_secondary_constraint(&__node_389))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_primary_or_secondary_constraint, "primary_or_secondary_constraint");
                                                                }
                                                              (*yynode)->primary_or_secondary_constraint = __node_389;
                                                              if (yytoken == Token_COMMA)
                                                                {
                                                                  if (yytoken != Token_COMMA)
                                                                    return yy_expected_token(yytoken, Token_COMMA, ",");
                                                                  yylex();
                                                                  if (yytoken == Token_ADD
                                                                      || yytoken == Token_ALIAS
                                                                      || yytoken == Token_GET
                                                                      || yytoken == Token_GLOBAL
                                                                      || yytoken == Token_PARTIAL
                                                                      || yytoken == Token_REMOVE
                                                                      || yytoken == Token_SET
                                                                      || yytoken == Token_VALUE
                                                                      || yytoken == Token_WHERE
                                                                      || yytoken == Token_YIELD
                                                                      || yytoken == Token_ASSEMBLY
                                                                      || yytoken == Token_IDENTIFIER)
                                                                    {
                                                                      secondary_constraints_ast *__node_390 = 0;
                                                                      if (!parse_secondary_constraints(&__node_390))
                                                                        {
                                                                          return yy_expected_symbol(ast_node::Kind_secondary_constraints, "secondary_constraints");
                                                                        }
                                                                      (*yynode)->secondary_constraints = __node_390;
                                                                      if (yytoken == Token_COMMA)
                                                                        {
                                                                          if (yytoken != Token_COMMA)
                                                                            return yy_expected_token(yytoken, Token_COMMA, ",");
                                                                          yylex();
                                                                          constructor_constraint_ast *__node_391 = 0;
                                                                          if (!parse_constructor_constraint(&__node_391))
                                                                            {
                                                                              return yy_expected_symbol(ast_node::Kind_constructor_constraint, "constructor_constraint");
                                                                            }
                                                                          (*yynode)->constructor_constraint = __node_391;
                                                                        }
                                                                      else if (true /*epsilon*/)
                                                                      {}
                                                                      else
                                                                        {
                                                                          return false;
                                                                        }
                                                                    }
                                                                  else if (yytoken == Token_NEW)
                                                                    {
                                                                      constructor_constraint_ast *__node_392 = 0;
                                                                      if (!parse_constructor_constraint(&__node_392))
                                                                        {
                                                                          return yy_expected_symbol(ast_node::Kind_constructor_constraint, "constructor_constraint");
                                                                        }
                                                                      (*yynode)->constructor_constraint = __node_392;
                                                                    }
                                                                  else
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
                                                          else if (yytoken == Token_ADD
                                                                   || yytoken == Token_ALIAS
                                                                   || yytoken == Token_GET
                                                                   || yytoken == Token_GLOBAL
                                                                   || yytoken == Token_PARTIAL
                                                                   || yytoken == Token_REMOVE
                                                                   || yytoken == Token_SET
                                                                   || yytoken == Token_VALUE
                                                                   || yytoken == Token_WHERE
                                                                   || yytoken == Token_YIELD
                                                                   || yytoken == Token_ASSEMBLY
                                                                   || yytoken == Token_IDENTIFIER)
                                                            {
                                                              secondary_constraints_ast *__node_393 = 0;
                                                              if (!parse_secondary_constraints(&__node_393))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_secondary_constraints, "secondary_constraints");
                                                                }
                                                              (*yynode)->secondary_constraints = __node_393;
                                                              if (yytoken == Token_COMMA)
                                                                {
                                                                  if (yytoken != Token_COMMA)
                                                                    return yy_expected_token(yytoken, Token_COMMA, ",");
                                                                  yylex();
                                                                  constructor_constraint_ast *__node_394 = 0;
                                                                  if (!parse_constructor_constraint(&__node_394))
                                                                    {
                                                                      return yy_expected_symbol(ast_node::Kind_constructor_constraint, "constructor_constraint");
                                                                    }
                                                                  (*yynode)->constructor_constraint = __node_394;
                                                                }
                                                              else if (true /*epsilon*/)
                                                              {}
                                                              else
                                                                {
                                                                  return false;
                                                                }
                                                            }
                                                          else if (yytoken == Token_NEW)
                                                            {
                                                              constructor_constraint_ast *__node_395 = 0;
                                                              if (!parse_constructor_constraint(&__node_395))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_constructor_constraint, "constructor_constraint");
                                                                }
                                                              (*yynode)->constructor_constraint = __node_395;
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

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_type_parameter_constraints_clauses(type_parameter_constraints_clauses_ast **yynode)
                                                    {
                                                      *yynode = create<type_parameter_constraints_clauses_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_WHERE)
                                                        {
                                                          if (yytoken != Token_WHERE)
                                                            return yy_expected_token(yytoken, Token_WHERE, "where");
                                                          yylex();
                                                          identifier_ast *__node_396 = 0;
                                                          if (!parse_identifier(&__node_396))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                            }
                                                          (*yynode)->type_parameter = __node_396;
                                                          if (yytoken != Token_COLON)
                                                            return yy_expected_token(yytoken, Token_COLON, ":");
                                                          yylex();
                                                          type_parameter_constraints_ast *__node_397 = 0;
                                                          if (!parse_type_parameter_constraints(&__node_397))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_type_parameter_constraints, "type_parameter_constraints");
                                                            }
                                                          (*yynode)->constraints = __node_397;
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_type_parameters(type_parameters_ast **yynode)
                                                    {
                                                      *yynode = create<type_parameters_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_LESS_THAN)
                                                        {
                                                          if (yytoken != Token_LESS_THAN)
                                                            return yy_expected_token(yytoken, Token_LESS_THAN, "<");
                                                          yylex();
                                                          int currentLtLevel = _M_ltCounter;
                                                          _M_ltCounter++;
                                                          type_parameter_ast *__node_398 = 0;
                                                          if (!parse_type_parameter(&__node_398))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_type_parameter, "type_parameter");
                                                            }
                                                          (*yynode)->type_parameter_sequence = snoc((*yynode)->type_parameter_sequence, __node_398, memory_pool);
                                                          while (yytoken == Token_COMMA)
                                                            {
                                                              if (yytoken != Token_COMMA)
                                                                return yy_expected_token(yytoken, Token_COMMA, ",");
                                                              yylex();
                                                              type_parameter_ast *__node_399 = 0;
                                                              if (!parse_type_parameter(&__node_399))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type_parameter, "type_parameter");
                                                                }
                                                              (*yynode)->type_parameter_sequence = snoc((*yynode)->type_parameter_sequence, __node_399, memory_pool);
                                                            }
                                                          if (yytoken == Token_GREATER_THAN
                                                              || yytoken == Token_RSHIFT)
                                                            {
                                                              type_arguments_or_parameters_end_ast *__node_400 = 0;
                                                              if (!parse_type_arguments_or_parameters_end(&__node_400))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type_arguments_or_parameters_end, "type_arguments_or_parameters_end");
                                                                }
                                                            }
                                                          else if (true /*epsilon*/)
                                                          {}
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          if ( currentLtLevel == 0 && _M_ltCounter != currentLtLevel )
                                                            {
                                                              report_problem(error, "The amount of closing ``>'' characters is incorrect");
                                                              return false;
                                                            }
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_typeof_expression(typeof_expression_ast **yynode)
                                                    {
                                                      *yynode = create<typeof_expression_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_TYPEOF)
                                                        {
                                                          if (yytoken != Token_TYPEOF)
                                                            return yy_expected_token(yytoken, Token_TYPEOF, "typeof");
                                                          yylex();
                                                          if (yytoken != Token_LPAREN)
                                                            return yy_expected_token(yytoken, Token_LPAREN, "(");
                                                          yylex();
                                                          if ((yytoken == Token_VOID) && ( LA(2).kind == Token_RPAREN ))
                                                            {
                                                              if (yytoken != Token_VOID)
                                                                return yy_expected_token(yytoken, Token_VOID, "void");
                                                              yylex();
                                                              (*yynode)->typeof_type = typeof_expression::type_void;
                                                            }
                                                          else if ((yytoken == Token_ADD
                                                                    || yytoken == Token_ALIAS
                                                                    || yytoken == Token_GET
                                                                    || yytoken == Token_GLOBAL
                                                                    || yytoken == Token_PARTIAL
                                                                    || yytoken == Token_REMOVE
                                                                    || yytoken == Token_SET
                                                                    || yytoken == Token_VALUE
                                                                    || yytoken == Token_WHERE
                                                                    || yytoken == Token_YIELD
                                                                    || yytoken == Token_ASSEMBLY
                                                                    || yytoken == Token_IDENTIFIER) && ( (compatibility_mode() >= csharp20_compatibility)
                                                                                                         && (lookahead_is_unbound_type_name() == true)
                                                                                                       ))
                                                            {
                                                              unbound_type_name_ast *__node_401 = 0;
                                                              if (!parse_unbound_type_name(&__node_401))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_unbound_type_name, "unbound_type_name");
                                                                }
                                                              (*yynode)->unbound_type_name = __node_401;
                                                              (*yynode)->typeof_type = typeof_expression::type_unbound_type_name;
                                                            }
                                                          else if (yytoken == Token_BOOL
                                                                   || yytoken == Token_BYTE
                                                                   || yytoken == Token_CHAR
                                                                   || yytoken == Token_DECIMAL
                                                                   || yytoken == Token_DOUBLE
                                                                   || yytoken == Token_FLOAT
                                                                   || yytoken == Token_INT
                                                                   || yytoken == Token_LONG
                                                                   || yytoken == Token_OBJECT
                                                                   || yytoken == Token_SBYTE
                                                                   || yytoken == Token_SHORT
                                                                   || yytoken == Token_STRING
                                                                   || yytoken == Token_UINT
                                                                   || yytoken == Token_ULONG
                                                                   || yytoken == Token_USHORT
                                                                   || yytoken == Token_VOID
                                                                   || yytoken == Token_ADD
                                                                   || yytoken == Token_ALIAS
                                                                   || yytoken == Token_GET
                                                                   || yytoken == Token_GLOBAL
                                                                   || yytoken == Token_PARTIAL
                                                                   || yytoken == Token_REMOVE
                                                                   || yytoken == Token_SET
                                                                   || yytoken == Token_VALUE
                                                                   || yytoken == Token_WHERE
                                                                   || yytoken == Token_YIELD
                                                                   || yytoken == Token_ASSEMBLY
                                                                   || yytoken == Token_IDENTIFIER)
                                                            {
                                                              type_ast *__node_402 = 0;
                                                              if (!parse_type(&__node_402))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type, "type");
                                                                }
                                                              (*yynode)->other_type = __node_402;
                                                              (*yynode)->typeof_type = typeof_expression::type_type;
                                                            }
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          if (yytoken != Token_RPAREN)
                                                            return yy_expected_token(yytoken, Token_RPAREN, ")");
                                                          yylex();
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_unary_expression(unary_expression_ast **yynode)
                                                    {
                                                      *yynode = create<unary_expression_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_BASE
                                                          || yytoken == Token_BOOL
                                                          || yytoken == Token_BYTE
                                                          || yytoken == Token_CHAR
                                                          || yytoken == Token_CHECKED
                                                          || yytoken == Token_DECIMAL
                                                          || yytoken == Token_DEFAULT
                                                          || yytoken == Token_DELEGATE
                                                          || yytoken == Token_DOUBLE
                                                          || yytoken == Token_FLOAT
                                                          || yytoken == Token_INT
                                                          || yytoken == Token_LONG
                                                          || yytoken == Token_NEW
                                                          || yytoken == Token_OBJECT
                                                          || yytoken == Token_SBYTE
                                                          || yytoken == Token_SHORT
                                                          || yytoken == Token_SIZEOF
                                                          || yytoken == Token_STRING
                                                          || yytoken == Token_THIS
                                                          || yytoken == Token_TYPEOF
                                                          || yytoken == Token_UINT
                                                          || yytoken == Token_ULONG
                                                          || yytoken == Token_UNCHECKED
                                                          || yytoken == Token_USHORT
                                                          || yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_LPAREN
                                                          || yytoken == Token_BANG
                                                          || yytoken == Token_TILDE
                                                          || yytoken == Token_INCREMENT
                                                          || yytoken == Token_DECREMENT
                                                          || yytoken == Token_PLUS
                                                          || yytoken == Token_MINUS
                                                          || yytoken == Token_STAR
                                                          || yytoken == Token_BIT_AND
                                                          || yytoken == Token_TRUE
                                                          || yytoken == Token_FALSE
                                                          || yytoken == Token_NULL
                                                          || yytoken == Token_INTEGER_LITERAL
                                                          || yytoken == Token_REAL_LITERAL
                                                          || yytoken == Token_CHARACTER_LITERAL
                                                          || yytoken == Token_STRING_LITERAL
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          if (yytoken == Token_INCREMENT)
                                                            {
                                                              if (yytoken != Token_INCREMENT)
                                                                return yy_expected_token(yytoken, Token_INCREMENT, "++");
                                                              yylex();
                                                              unary_expression_ast *__node_403 = 0;
                                                              if (!parse_unary_expression(&__node_403))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_unary_expression, "unary_expression");
                                                                }
                                                              (*yynode)->unary_expression = __node_403;
                                                              (*yynode)->rule_type = unary_expression::type_incremented_expression;
                                                            }
                                                          else if (yytoken == Token_DECREMENT)
                                                            {
                                                              if (yytoken != Token_DECREMENT)
                                                                return yy_expected_token(yytoken, Token_DECREMENT, "--");
                                                              yylex();
                                                              unary_expression_ast *__node_404 = 0;
                                                              if (!parse_unary_expression(&__node_404))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_unary_expression, "unary_expression");
                                                                }
                                                              (*yynode)->unary_expression = __node_404;
                                                              (*yynode)->rule_type = unary_expression::type_decremented_expression;
                                                            }
                                                          else if (yytoken == Token_MINUS)
                                                            {
                                                              if (yytoken != Token_MINUS)
                                                                return yy_expected_token(yytoken, Token_MINUS, "-");
                                                              yylex();
                                                              unary_expression_ast *__node_405 = 0;
                                                              if (!parse_unary_expression(&__node_405))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_unary_expression, "unary_expression");
                                                                }
                                                              (*yynode)->unary_expression = __node_405;
                                                              (*yynode)->rule_type = unary_expression::type_unary_minus_expression;
                                                            }
                                                          else if (yytoken == Token_PLUS)
                                                            {
                                                              if (yytoken != Token_PLUS)
                                                                return yy_expected_token(yytoken, Token_PLUS, "+");
                                                              yylex();
                                                              unary_expression_ast *__node_406 = 0;
                                                              if (!parse_unary_expression(&__node_406))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_unary_expression, "unary_expression");
                                                                }
                                                              (*yynode)->unary_expression = __node_406;
                                                              (*yynode)->rule_type = unary_expression::type_unary_plus_expression;
                                                            }
                                                          else if (yytoken == Token_TILDE)
                                                            {
                                                              if (yytoken != Token_TILDE)
                                                                return yy_expected_token(yytoken, Token_TILDE, "~");
                                                              yylex();
                                                              unary_expression_ast *__node_407 = 0;
                                                              if (!parse_unary_expression(&__node_407))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_unary_expression, "unary_expression");
                                                                }
                                                              (*yynode)->bitwise_not_expression = __node_407;
                                                              (*yynode)->rule_type = unary_expression::type_bitwise_not_expression;
                                                            }
                                                          else if (yytoken == Token_BANG)
                                                            {
                                                              if (yytoken != Token_BANG)
                                                                return yy_expected_token(yytoken, Token_BANG, "!");
                                                              yylex();
                                                              unary_expression_ast *__node_408 = 0;
                                                              if (!parse_unary_expression(&__node_408))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_unary_expression, "unary_expression");
                                                                }
                                                              (*yynode)->logical_not_expression = __node_408;
                                                              (*yynode)->rule_type = unary_expression::type_logical_not_expression;
                                                            }
                                                          else if ((yytoken == Token_LPAREN) && ( lookahead_is_cast_expression() == true ))
                                                            {
                                                              cast_expression_ast *__node_409 = 0;
                                                              if (!parse_cast_expression(&__node_409))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_cast_expression, "cast_expression");
                                                                }
                                                              (*yynode)->cast_expression = __node_409;
                                                              (*yynode)->rule_type = unary_expression::type_cast_expression;
                                                            }
                                                          else if (yytoken == Token_BASE
                                                                   || yytoken == Token_BOOL
                                                                   || yytoken == Token_BYTE
                                                                   || yytoken == Token_CHAR
                                                                   || yytoken == Token_CHECKED
                                                                   || yytoken == Token_DECIMAL
                                                                   || yytoken == Token_DEFAULT
                                                                   || yytoken == Token_DELEGATE
                                                                   || yytoken == Token_DOUBLE
                                                                   || yytoken == Token_FLOAT
                                                                   || yytoken == Token_INT
                                                                   || yytoken == Token_LONG
                                                                   || yytoken == Token_NEW
                                                                   || yytoken == Token_OBJECT
                                                                   || yytoken == Token_SBYTE
                                                                   || yytoken == Token_SHORT
                                                                   || yytoken == Token_SIZEOF
                                                                   || yytoken == Token_STRING
                                                                   || yytoken == Token_THIS
                                                                   || yytoken == Token_TYPEOF
                                                                   || yytoken == Token_UINT
                                                                   || yytoken == Token_ULONG
                                                                   || yytoken == Token_UNCHECKED
                                                                   || yytoken == Token_USHORT
                                                                   || yytoken == Token_ADD
                                                                   || yytoken == Token_ALIAS
                                                                   || yytoken == Token_GET
                                                                   || yytoken == Token_GLOBAL
                                                                   || yytoken == Token_PARTIAL
                                                                   || yytoken == Token_REMOVE
                                                                   || yytoken == Token_SET
                                                                   || yytoken == Token_VALUE
                                                                   || yytoken == Token_WHERE
                                                                   || yytoken == Token_YIELD
                                                                   || yytoken == Token_ASSEMBLY
                                                                   || yytoken == Token_LPAREN
                                                                   || yytoken == Token_TRUE
                                                                   || yytoken == Token_FALSE
                                                                   || yytoken == Token_NULL
                                                                   || yytoken == Token_INTEGER_LITERAL
                                                                   || yytoken == Token_REAL_LITERAL
                                                                   || yytoken == Token_CHARACTER_LITERAL
                                                                   || yytoken == Token_STRING_LITERAL
                                                                   || yytoken == Token_IDENTIFIER)
                                                            {
                                                              primary_expression_ast *__node_410 = 0;
                                                              if (!parse_primary_expression(&__node_410))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_primary_expression, "primary_expression");
                                                                }
                                                              (*yynode)->primary_expression = __node_410;
                                                              (*yynode)->rule_type = unary_expression::type_primary_expression;
                                                            }
                                                          else if (yytoken == Token_STAR)
                                                            {
                                                              if (yytoken != Token_STAR)
                                                                return yy_expected_token(yytoken, Token_STAR, "*");
                                                              yylex();
                                                              unary_expression_ast *__node_411 = 0;
                                                              if (!parse_unary_expression(&__node_411))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_unary_expression, "unary_expression");
                                                                }
                                                              (*yynode)->pointer_indirection_expression = __node_411;
                                                              (*yynode)->rule_type = unary_expression::type_pointer_indirection_expression;
                                                            }
                                                          else if (yytoken == Token_BIT_AND)
                                                            {
                                                              if (yytoken != Token_BIT_AND)
                                                                return yy_expected_token(yytoken, Token_BIT_AND, "&");
                                                              yylex();
                                                              unary_expression_ast *__node_412 = 0;
                                                              if (!parse_unary_expression(&__node_412))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_unary_expression, "unary_expression");
                                                                }
                                                              (*yynode)->addressof_expression = __node_412;
                                                              (*yynode)->rule_type = unary_expression::type_addressof_expression;
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

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_unary_or_binary_operator_declaration(unary_or_binary_operator_declaration_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers, type_ast *return_type)
                                                    {
                                                      *yynode = create<unary_or_binary_operator_declaration_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      (*yynode)->attribute_sequence = attribute_sequence;
                                                      if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
                                                        (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

                                                      (*yynode)->modifiers = modifiers;
                                                      if (modifiers && modifiers->start_token < (*yynode)->start_token)
                                                        (*yynode)->start_token = modifiers->start_token;

                                                      (*yynode)->return_type = return_type;
                                                      if (return_type && return_type->start_token < (*yynode)->start_token)
                                                        (*yynode)->start_token = return_type->start_token;

                                                      if (yytoken == Token_OPERATOR)
                                                        {
                                                          overloadable_unary_only_operator_ast *unary_op = 0;

                                                          overloadable_binary_only_operator_ast *binary_op = 0;

                                                          overloadable_unary_or_binary_operator_ast *unary_or_binary_op = 0;

                                                          if (yytoken != Token_OPERATOR)
                                                            return yy_expected_token(yytoken, Token_OPERATOR, "operator");
                                                          yylex();
                                                          if (yytoken == Token_BANG
                                                              || yytoken == Token_TILDE
                                                              || yytoken == Token_INCREMENT
                                                              || yytoken == Token_DECREMENT
                                                              || yytoken == Token_TRUE
                                                              || yytoken == Token_FALSE)
                                                            {
                                                              overloadable_unary_only_operator_ast *__node_413 = 0;
                                                              if (!parse_overloadable_unary_only_operator(&__node_413, &(*yynode)->overloadable_operator_type))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_overloadable_unary_only_operator, "overloadable_unary_only_operator");
                                                                }
                                                              unary_op = __node_413;
                                                              if (yytoken != Token_LPAREN)
                                                                return yy_expected_token(yytoken, Token_LPAREN, "(");
                                                              yylex();
                                                              type_ast *__node_414 = 0;
                                                              if (!parse_type(&__node_414))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type, "type");
                                                                }
                                                              (*yynode)->source1_type = __node_414;
                                                              identifier_ast *__node_415 = 0;
                                                              if (!parse_identifier(&__node_415))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                                }
                                                              (*yynode)->source1_name = __node_415;
                                                              if (yytoken != Token_RPAREN)
                                                                return yy_expected_token(yytoken, Token_RPAREN, ")");
                                                              yylex();
                                                              (*yynode)->overloadable_operator_token = unary_op->op;
                                                              (*yynode)->unary_or_binary = overloadable_operator::type_unary;
                                                            }
                                                          else if (yytoken == Token_EQUAL
                                                                   || yytoken == Token_LESS_THAN
                                                                   || yytoken == Token_LESS_EQUAL
                                                                   || yytoken == Token_GREATER_THAN
                                                                   || yytoken == Token_GREATER_EQUAL
                                                                   || yytoken == Token_NOT_EQUAL
                                                                   || yytoken == Token_STAR
                                                                   || yytoken == Token_SLASH
                                                                   || yytoken == Token_BIT_AND
                                                                   || yytoken == Token_BIT_OR
                                                                   || yytoken == Token_BIT_XOR
                                                                   || yytoken == Token_REMAINDER
                                                                   || yytoken == Token_LSHIFT
                                                                   || yytoken == Token_RSHIFT)
                                                            {
                                                              overloadable_binary_only_operator_ast *__node_416 = 0;
                                                              if (!parse_overloadable_binary_only_operator(&__node_416, &(*yynode)->overloadable_operator_type))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_overloadable_binary_only_operator, "overloadable_binary_only_operator");
                                                                }
                                                              binary_op = __node_416;
                                                              if (yytoken != Token_LPAREN)
                                                                return yy_expected_token(yytoken, Token_LPAREN, "(");
                                                              yylex();
                                                              type_ast *__node_417 = 0;
                                                              if (!parse_type(&__node_417))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type, "type");
                                                                }
                                                              (*yynode)->source1_type = __node_417;
                                                              identifier_ast *__node_418 = 0;
                                                              if (!parse_identifier(&__node_418))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                                }
                                                              (*yynode)->source1_name = __node_418;
                                                              if (yytoken != Token_COMMA)
                                                                return yy_expected_token(yytoken, Token_COMMA, ",");
                                                              yylex();
                                                              type_ast *__node_419 = 0;
                                                              if (!parse_type(&__node_419))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type, "type");
                                                                }
                                                              (*yynode)->source2_type = __node_419;
                                                              identifier_ast *__node_420 = 0;
                                                              if (!parse_identifier(&__node_420))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                                }
                                                              (*yynode)->source2_name = __node_420;
                                                              if (yytoken != Token_RPAREN)
                                                                return yy_expected_token(yytoken, Token_RPAREN, ")");
                                                              yylex();
                                                              (*yynode)->overloadable_operator_token = binary_op->op;
                                                              (*yynode)->unary_or_binary = overloadable_operator::type_binary;
                                                            }
                                                          else if (yytoken == Token_PLUS
                                                                   || yytoken == Token_MINUS)
                                                            {
                                                              overloadable_unary_or_binary_operator_ast *__node_421 = 0;
                                                              if (!parse_overloadable_unary_or_binary_operator(&__node_421, &(*yynode)->overloadable_operator_type))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_overloadable_unary_or_binary_operator, "overloadable_unary_or_binary_operator");
                                                                }
                                                              unary_or_binary_op = __node_421;
                                                              (*yynode)->overloadable_operator_token = unary_or_binary_op->op;
                                                              if (yytoken != Token_LPAREN)
                                                                return yy_expected_token(yytoken, Token_LPAREN, "(");
                                                              yylex();
                                                              type_ast *__node_422 = 0;
                                                              if (!parse_type(&__node_422))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_type, "type");
                                                                }
                                                              (*yynode)->source1_type = __node_422;
                                                              identifier_ast *__node_423 = 0;
                                                              if (!parse_identifier(&__node_423))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                                }
                                                              (*yynode)->source1_name = __node_423;
                                                              if (yytoken == Token_COMMA)
                                                                {
                                                                  if (yytoken != Token_COMMA)
                                                                    return yy_expected_token(yytoken, Token_COMMA, ",");
                                                                  yylex();
                                                                  type_ast *__node_424 = 0;
                                                                  if (!parse_type(&__node_424))
                                                                    {
                                                                      return yy_expected_symbol(ast_node::Kind_type, "type");
                                                                    }
                                                                  (*yynode)->source2_type = __node_424;
                                                                  identifier_ast *__node_425 = 0;
                                                                  if (!parse_identifier(&__node_425))
                                                                    {
                                                                      return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                                    }
                                                                  (*yynode)->source2_name = __node_425;
                                                                  (*yynode)->unary_or_binary = overloadable_operator::type_binary;
                                                                }
                                                              else if (true /*epsilon*/)
                                                                {
                                                                  (*yynode)->unary_or_binary = overloadable_operator::type_unary;
                                                                }
                                                              else
                                                                {
                                                                  return false;
                                                                }
                                                              if (yytoken != Token_RPAREN)
                                                                return yy_expected_token(yytoken, Token_RPAREN, ")");
                                                              yylex();
                                                            }
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          if (yytoken == Token_LBRACE)
                                                            {
                                                              block_ast *__node_426 = 0;
                                                              if (!parse_block(&__node_426))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_block, "block");
                                                                }
                                                              (*yynode)->body = __node_426;
                                                            }
                                                          else if (yytoken == Token_SEMICOLON)
                                                            {
                                                              if (yytoken != Token_SEMICOLON)
                                                                return yy_expected_token(yytoken, Token_SEMICOLON, ";");
                                                              yylex();
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

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_unbound_type_name(unbound_type_name_ast **yynode)
                                                    {
                                                      *yynode = create<unbound_type_name_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          if ((yytoken == Token_ADD
                                                               || yytoken == Token_ALIAS
                                                               || yytoken == Token_GET
                                                               || yytoken == Token_GLOBAL
                                                               || yytoken == Token_PARTIAL
                                                               || yytoken == Token_REMOVE
                                                               || yytoken == Token_SET
                                                               || yytoken == Token_VALUE
                                                               || yytoken == Token_WHERE
                                                               || yytoken == Token_YIELD
                                                               || yytoken == Token_ASSEMBLY
                                                               || yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_SCOPE ))
                                                            {
                                                              identifier_ast *__node_427 = 0;
                                                              if (!parse_identifier(&__node_427))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                                }
                                                              (*yynode)->qualified_alias_label = __node_427;
                                                              if (yytoken != Token_SCOPE)
                                                                return yy_expected_token(yytoken, Token_SCOPE, "::");
                                                              yylex();
                                                            }
                                                          else if (true /*epsilon*/)
                                                          {}
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          unbound_type_name_part_ast *__node_428 = 0;
                                                          if (!parse_unbound_type_name_part(&__node_428))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_unbound_type_name_part, "unbound_type_name_part");
                                                            }
                                                          (*yynode)->name_part_sequence = snoc((*yynode)->name_part_sequence, __node_428, memory_pool);
                                                          while (yytoken == Token_DOT)
                                                            {
                                                              if (yytoken != Token_DOT)
                                                                return yy_expected_token(yytoken, Token_DOT, ".");
                                                              yylex();
                                                              unbound_type_name_part_ast *__node_429 = 0;
                                                              if (!parse_unbound_type_name_part(&__node_429))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_unbound_type_name_part, "unbound_type_name_part");
                                                                }
                                                              (*yynode)->name_part_sequence = snoc((*yynode)->name_part_sequence, __node_429, memory_pool);
                                                            }
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_unbound_type_name_part(unbound_type_name_part_ast **yynode)
                                                    {
                                                      *yynode = create<unbound_type_name_part_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          identifier_ast *__node_430 = 0;
                                                          if (!parse_identifier(&__node_430))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                            }
                                                          (*yynode)->identifier = __node_430;
                                                          if (yytoken == Token_LESS_THAN)
                                                            {
                                                              generic_dimension_specifier_ast *__node_431 = 0;
                                                              if (!parse_generic_dimension_specifier(&__node_431))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_generic_dimension_specifier, "generic_dimension_specifier");
                                                                }
                                                              (*yynode)->generic_dimension_specifier = __node_431;
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

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_unchecked_statement(unchecked_statement_ast **yynode)
                                                    {
                                                      *yynode = create<unchecked_statement_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_UNCHECKED)
                                                        {
                                                          if (yytoken != Token_UNCHECKED)
                                                            return yy_expected_token(yytoken, Token_UNCHECKED, "unchecked");
                                                          yylex();
                                                          block_ast *__node_432 = 0;
                                                          if (!parse_block(&__node_432))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_block, "block");
                                                            }
                                                          (*yynode)->body = __node_432;
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_unmanaged_type(unmanaged_type_ast **yynode)
                                                    {
                                                      *yynode = create<unmanaged_type_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_BOOL
                                                          || yytoken == Token_BYTE
                                                          || yytoken == Token_CHAR
                                                          || yytoken == Token_DECIMAL
                                                          || yytoken == Token_DOUBLE
                                                          || yytoken == Token_FLOAT
                                                          || yytoken == Token_INT
                                                          || yytoken == Token_LONG
                                                          || yytoken == Token_OBJECT
                                                          || yytoken == Token_SBYTE
                                                          || yytoken == Token_SHORT
                                                          || yytoken == Token_STRING
                                                          || yytoken == Token_UINT
                                                          || yytoken == Token_ULONG
                                                          || yytoken == Token_USHORT
                                                          || yytoken == Token_VOID
                                                          || yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          (*yynode)->star_count = 0;
                                                          if (yytoken == Token_BOOL
                                                              || yytoken == Token_BYTE
                                                              || yytoken == Token_CHAR
                                                              || yytoken == Token_DECIMAL
                                                              || yytoken == Token_DOUBLE
                                                              || yytoken == Token_FLOAT
                                                              || yytoken == Token_INT
                                                              || yytoken == Token_LONG
                                                              || yytoken == Token_OBJECT
                                                              || yytoken == Token_SBYTE
                                                              || yytoken == Token_SHORT
                                                              || yytoken == Token_STRING
                                                              || yytoken == Token_UINT
                                                              || yytoken == Token_ULONG
                                                              || yytoken == Token_USHORT
                                                              || yytoken == Token_ADD
                                                              || yytoken == Token_ALIAS
                                                              || yytoken == Token_GET
                                                              || yytoken == Token_GLOBAL
                                                              || yytoken == Token_PARTIAL
                                                              || yytoken == Token_REMOVE
                                                              || yytoken == Token_SET
                                                              || yytoken == Token_VALUE
                                                              || yytoken == Token_WHERE
                                                              || yytoken == Token_YIELD
                                                              || yytoken == Token_ASSEMBLY
                                                              || yytoken == Token_IDENTIFIER)
                                                            {
                                                              managed_type_ast *__node_433 = 0;
                                                              if (!parse_managed_type(&__node_433))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_managed_type, "managed_type");
                                                                }
                                                              (*yynode)->regular_type = __node_433;
                                                              (*yynode)->type = pointer_type::type_regular;
                                                            }
                                                          else if (yytoken == Token_VOID)
                                                            {
                                                              if (yytoken != Token_VOID)
                                                                return yy_expected_token(yytoken, Token_VOID, "void");
                                                              yylex();
                                                              if (yytoken != Token_STAR)
                                                                return yy_expected_token(yytoken, Token_STAR, "*");
                                                              yylex();
                                                              (*yynode)->star_count++;
                                                              (*yynode)->type = pointer_type::type_void;
                                                            }
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          while (yytoken == Token_STAR)
                                                            {
                                                              if (yytoken != Token_STAR)
                                                                return yy_expected_token(yytoken, Token_STAR, "*");
                                                              yylex();
                                                              (*yynode)->star_count++;
                                                            }
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_unsafe_statement(unsafe_statement_ast **yynode)
                                                    {
                                                      *yynode = create<unsafe_statement_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_UNSAFE)
                                                        {
                                                          if (yytoken != Token_UNSAFE)
                                                            return yy_expected_token(yytoken, Token_UNSAFE, "unsafe");
                                                          yylex();
                                                          block_ast *__node_434 = 0;
                                                          if (!parse_block(&__node_434))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_block, "block");
                                                            }
                                                          (*yynode)->body = __node_434;
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_using_directive(using_directive_ast **yynode)
                                                    {
                                                      *yynode = create<using_directive_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_USING)
                                                        {
                                                          if (yytoken != Token_USING)
                                                            return yy_expected_token(yytoken, Token_USING, "using");
                                                          yylex();
                                                          if ((yytoken == Token_ADD
                                                               || yytoken == Token_ALIAS
                                                               || yytoken == Token_GET
                                                               || yytoken == Token_GLOBAL
                                                               || yytoken == Token_PARTIAL
                                                               || yytoken == Token_REMOVE
                                                               || yytoken == Token_SET
                                                               || yytoken == Token_VALUE
                                                               || yytoken == Token_WHERE
                                                               || yytoken == Token_YIELD
                                                               || yytoken == Token_ASSEMBLY
                                                               || yytoken == Token_IDENTIFIER) && ( LA(2).kind == Token_ASSIGN ))
                                                            {
                                                              identifier_ast *__node_435 = 0;
                                                              if (!parse_identifier(&__node_435))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                                }
                                                              (*yynode)->alias = __node_435;
                                                              if (yytoken != Token_ASSIGN)
                                                                return yy_expected_token(yytoken, Token_ASSIGN, "=");
                                                              yylex();
                                                              namespace_or_type_name_ast *__node_436 = 0;
                                                              if (!parse_namespace_or_type_name(&__node_436))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_namespace_or_type_name, "namespace_or_type_name");
                                                                }
                                                              (*yynode)->namespace_or_type_name = __node_436;
                                                            }
                                                          else if (yytoken == Token_ADD
                                                                   || yytoken == Token_ALIAS
                                                                   || yytoken == Token_GET
                                                                   || yytoken == Token_GLOBAL
                                                                   || yytoken == Token_PARTIAL
                                                                   || yytoken == Token_REMOVE
                                                                   || yytoken == Token_SET
                                                                   || yytoken == Token_VALUE
                                                                   || yytoken == Token_WHERE
                                                                   || yytoken == Token_YIELD
                                                                   || yytoken == Token_ASSEMBLY
                                                                   || yytoken == Token_IDENTIFIER)
                                                            {
                                                              namespace_or_type_name_ast *__node_437 = 0;
                                                              if (!parse_namespace_or_type_name(&__node_437))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_namespace_or_type_name, "namespace_or_type_name");
                                                                }
                                                              (*yynode)->namespace_name = __node_437;
                                                            }
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          if (yytoken != Token_SEMICOLON)
                                                            return yy_expected_token(yytoken, Token_SEMICOLON, ";");
                                                          yylex();
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_using_statement(using_statement_ast **yynode)
                                                    {
                                                      *yynode = create<using_statement_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_USING)
                                                        {
                                                          if (yytoken != Token_USING)
                                                            return yy_expected_token(yytoken, Token_USING, "using");
                                                          yylex();
                                                          if (yytoken != Token_LPAREN)
                                                            return yy_expected_token(yytoken, Token_LPAREN, "(");
                                                          yylex();
                                                          resource_acquisition_ast *__node_438 = 0;
                                                          if (!parse_resource_acquisition(&__node_438))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_resource_acquisition, "resource_acquisition");
                                                            }
                                                          (*yynode)->resource_acquisition = __node_438;
                                                          if (yytoken != Token_RPAREN)
                                                            return yy_expected_token(yytoken, Token_RPAREN, ")");
                                                          yylex();
                                                          embedded_statement_ast *__node_439 = 0;
                                                          if (!parse_embedded_statement(&__node_439))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_embedded_statement, "embedded_statement");
                                                            }
                                                          (*yynode)->body = __node_439;
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_variable_declaration_data(variable_declaration_data_ast **yynode, const list_node<attribute_section_ast *> *attribute_sequence, optional_modifiers_ast *modifiers, type_ast *type, const list_node<variable_declarator_ast *> *variable_declarator_sequence)
                                                    {
                                                      *yynode = create<variable_declaration_data_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      (*yynode)->attribute_sequence = attribute_sequence;
                                                      if (attribute_sequence && attribute_sequence->to_front()->element->start_token < (*yynode)->start_token)
                                                        (*yynode)->start_token = attribute_sequence->to_front()->element->start_token;

                                                      (*yynode)->modifiers = modifiers;
                                                      if (modifiers && modifiers->start_token < (*yynode)->start_token)
                                                        (*yynode)->start_token = modifiers->start_token;

                                                      (*yynode)->type = type;
                                                      if (type && type->start_token < (*yynode)->start_token)
                                                        (*yynode)->start_token = type->start_token;

                                                      (*yynode)->variable_declarator_sequence = variable_declarator_sequence;
                                                      if (variable_declarator_sequence && variable_declarator_sequence->to_front()->element->start_token < (*yynode)->start_token)
                                                        (*yynode)->start_token = variable_declarator_sequence->to_front()->element->start_token;

                                                      if (true /*epsilon*/ || yytoken == Token_RPAREN
                                                          || yytoken == Token_RBRACE
                                                          || yytoken == Token_SEMICOLON)
                                                      {}
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_variable_declarator(variable_declarator_ast **yynode)
                                                    {
                                                      *yynode = create<variable_declarator_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          identifier_ast *__node_440 = 0;
                                                          if (!parse_identifier(&__node_440))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_identifier, "identifier");
                                                            }
                                                          (*yynode)->variable_name = __node_440;
                                                          if (yytoken == Token_ASSIGN)
                                                            {
                                                              if (yytoken != Token_ASSIGN)
                                                                return yy_expected_token(yytoken, Token_ASSIGN, "=");
                                                              yylex();
                                                              variable_initializer_ast *__node_441 = 0;
                                                              if (!parse_variable_initializer(&__node_441))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_variable_initializer, "variable_initializer");
                                                                }
                                                              (*yynode)->variable_initializer = __node_441;
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

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_variable_initializer(variable_initializer_ast **yynode)
                                                    {
                                                      *yynode = create<variable_initializer_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_BASE
                                                          || yytoken == Token_BOOL
                                                          || yytoken == Token_BYTE
                                                          || yytoken == Token_CHAR
                                                          || yytoken == Token_CHECKED
                                                          || yytoken == Token_DECIMAL
                                                          || yytoken == Token_DEFAULT
                                                          || yytoken == Token_DELEGATE
                                                          || yytoken == Token_DOUBLE
                                                          || yytoken == Token_FLOAT
                                                          || yytoken == Token_INT
                                                          || yytoken == Token_LONG
                                                          || yytoken == Token_NEW
                                                          || yytoken == Token_OBJECT
                                                          || yytoken == Token_SBYTE
                                                          || yytoken == Token_SHORT
                                                          || yytoken == Token_SIZEOF
                                                          || yytoken == Token_STACKALLOC
                                                          || yytoken == Token_STRING
                                                          || yytoken == Token_THIS
                                                          || yytoken == Token_TYPEOF
                                                          || yytoken == Token_UINT
                                                          || yytoken == Token_ULONG
                                                          || yytoken == Token_UNCHECKED
                                                          || yytoken == Token_USHORT
                                                          || yytoken == Token_ADD
                                                          || yytoken == Token_ALIAS
                                                          || yytoken == Token_GET
                                                          || yytoken == Token_GLOBAL
                                                          || yytoken == Token_PARTIAL
                                                          || yytoken == Token_REMOVE
                                                          || yytoken == Token_SET
                                                          || yytoken == Token_VALUE
                                                          || yytoken == Token_WHERE
                                                          || yytoken == Token_YIELD
                                                          || yytoken == Token_ASSEMBLY
                                                          || yytoken == Token_LPAREN
                                                          || yytoken == Token_LBRACE
                                                          || yytoken == Token_BANG
                                                          || yytoken == Token_TILDE
                                                          || yytoken == Token_INCREMENT
                                                          || yytoken == Token_DECREMENT
                                                          || yytoken == Token_PLUS
                                                          || yytoken == Token_MINUS
                                                          || yytoken == Token_STAR
                                                          || yytoken == Token_BIT_AND
                                                          || yytoken == Token_TRUE
                                                          || yytoken == Token_FALSE
                                                          || yytoken == Token_NULL
                                                          || yytoken == Token_INTEGER_LITERAL
                                                          || yytoken == Token_REAL_LITERAL
                                                          || yytoken == Token_CHARACTER_LITERAL
                                                          || yytoken == Token_STRING_LITERAL
                                                          || yytoken == Token_IDENTIFIER)
                                                        {
                                                          if (yytoken == Token_BASE
                                                              || yytoken == Token_BOOL
                                                              || yytoken == Token_BYTE
                                                              || yytoken == Token_CHAR
                                                              || yytoken == Token_CHECKED
                                                              || yytoken == Token_DECIMAL
                                                              || yytoken == Token_DEFAULT
                                                              || yytoken == Token_DELEGATE
                                                              || yytoken == Token_DOUBLE
                                                              || yytoken == Token_FLOAT
                                                              || yytoken == Token_INT
                                                              || yytoken == Token_LONG
                                                              || yytoken == Token_NEW
                                                              || yytoken == Token_OBJECT
                                                              || yytoken == Token_SBYTE
                                                              || yytoken == Token_SHORT
                                                              || yytoken == Token_SIZEOF
                                                              || yytoken == Token_STRING
                                                              || yytoken == Token_THIS
                                                              || yytoken == Token_TYPEOF
                                                              || yytoken == Token_UINT
                                                              || yytoken == Token_ULONG
                                                              || yytoken == Token_UNCHECKED
                                                              || yytoken == Token_USHORT
                                                              || yytoken == Token_ADD
                                                              || yytoken == Token_ALIAS
                                                              || yytoken == Token_GET
                                                              || yytoken == Token_GLOBAL
                                                              || yytoken == Token_PARTIAL
                                                              || yytoken == Token_REMOVE
                                                              || yytoken == Token_SET
                                                              || yytoken == Token_VALUE
                                                              || yytoken == Token_WHERE
                                                              || yytoken == Token_YIELD
                                                              || yytoken == Token_ASSEMBLY
                                                              || yytoken == Token_LPAREN
                                                              || yytoken == Token_BANG
                                                              || yytoken == Token_TILDE
                                                              || yytoken == Token_INCREMENT
                                                              || yytoken == Token_DECREMENT
                                                              || yytoken == Token_PLUS
                                                              || yytoken == Token_MINUS
                                                              || yytoken == Token_STAR
                                                              || yytoken == Token_BIT_AND
                                                              || yytoken == Token_TRUE
                                                              || yytoken == Token_FALSE
                                                              || yytoken == Token_NULL
                                                              || yytoken == Token_INTEGER_LITERAL
                                                              || yytoken == Token_REAL_LITERAL
                                                              || yytoken == Token_CHARACTER_LITERAL
                                                              || yytoken == Token_STRING_LITERAL
                                                              || yytoken == Token_IDENTIFIER)
                                                            {
                                                              expression_ast *__node_442 = 0;
                                                              if (!parse_expression(&__node_442))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_expression, "expression");
                                                                }
                                                              (*yynode)->expression = __node_442;
                                                            }
                                                          else if (yytoken == Token_LBRACE)
                                                            {
                                                              array_initializer_ast *__node_443 = 0;
                                                              if (!parse_array_initializer(&__node_443))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_array_initializer, "array_initializer");
                                                                }
                                                              (*yynode)->array_initializer = __node_443;
                                                            }
                                                          else if (yytoken == Token_STACKALLOC)
                                                            {
                                                              stackalloc_initializer_ast *__node_444 = 0;
                                                              if (!parse_stackalloc_initializer(&__node_444))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_stackalloc_initializer, "stackalloc_initializer");
                                                                }
                                                              (*yynode)->stackalloc_initializer = __node_444;
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

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_while_statement(while_statement_ast **yynode)
                                                    {
                                                      *yynode = create<while_statement_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_WHILE)
                                                        {
                                                          if (yytoken != Token_WHILE)
                                                            return yy_expected_token(yytoken, Token_WHILE, "while");
                                                          yylex();
                                                          if (yytoken != Token_LPAREN)
                                                            return yy_expected_token(yytoken, Token_LPAREN, "(");
                                                          yylex();
                                                          boolean_expression_ast *__node_445 = 0;
                                                          if (!parse_boolean_expression(&__node_445))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_boolean_expression, "boolean_expression");
                                                            }
                                                          (*yynode)->condition = __node_445;
                                                          if (yytoken != Token_RPAREN)
                                                            return yy_expected_token(yytoken, Token_RPAREN, ")");
                                                          yylex();
                                                          embedded_statement_ast *__node_446 = 0;
                                                          if (!parse_embedded_statement(&__node_446))
                                                            {
                                                              return yy_expected_symbol(ast_node::Kind_embedded_statement, "embedded_statement");
                                                            }
                                                          (*yynode)->body = __node_446;
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    bool parser::parse_yield_statement(yield_statement_ast **yynode)
                                                    {
                                                      *yynode = create<yield_statement_ast>();

                                                      (*yynode)->start_token = token_stream->index() - 1;

                                                      if (yytoken == Token_YIELD)
                                                        {
                                                          if (yytoken != Token_YIELD)
                                                            return yy_expected_token(yytoken, Token_YIELD, "yield");
                                                          yylex();
                                                          if (yytoken == Token_RETURN)
                                                            {
                                                              if (yytoken != Token_RETURN)
                                                                return yy_expected_token(yytoken, Token_RETURN, "return");
                                                              yylex();
                                                              expression_ast *__node_447 = 0;
                                                              if (!parse_expression(&__node_447))
                                                                {
                                                                  return yy_expected_symbol(ast_node::Kind_expression, "expression");
                                                                }
                                                              (*yynode)->return_expression = __node_447;
                                                              (*yynode)->yield_type = yield_statement::type_yield_return;
                                                            }
                                                          else if (yytoken == Token_BREAK)
                                                            {
                                                              if (yytoken != Token_BREAK)
                                                                return yy_expected_token(yytoken, Token_BREAK, "break");
                                                              yylex();
                                                              (*yynode)->yield_type = yield_statement::type_yield_break;
                                                            }
                                                          else
                                                            {
                                                              return false;
                                                            }
                                                          if (yytoken != Token_SEMICOLON)
                                                            return yy_expected_token(yytoken, Token_SEMICOLON, ";");
                                                          yylex();
                                                        }
                                                      else
                                                        {
                                                          return false;
                                                        }

                                                      (*yynode)->end_token = token_stream->index() - 1;

                                                      return true;
                                                    }

                                                    visitor::parser_fun_t visitor::_S_parser_table[] = {
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_accessor_declarations),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_accessor_modifier),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_additive_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_additive_expression_rest),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_anonymous_method_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_anonymous_method_parameter),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_argument),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_array_creation_expression_rest),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_array_initializer),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_array_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_attribute),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_attribute_arguments),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_attribute_section),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_attribute_target),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_base_access),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_bit_and_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_bit_or_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_bit_xor_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_block),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_block_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_boolean_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_break_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_builtin_class_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_cast_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_catch_clauses),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_checked_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_class_base),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_class_body),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_class_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_class_member_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_class_or_struct_member_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_class_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_compilation_unit),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_conditional_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_constant_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_constant_declaration_data),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_constant_declarator),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_constant_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_constructor_constraint),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_constructor_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_constructor_initializer),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_continue_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_conversion_operator_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_delegate_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_do_while_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_embedded_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_enum_base),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_enum_body),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_enum_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_enum_member_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_equality_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_equality_expression_rest),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_event_accessor_declarations),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_event_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_extern_alias_directive),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_finalizer_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_fixed_pointer_declarator),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_fixed_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_floating_point_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_for_control),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_for_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_foreach_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_formal_parameter),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_formal_parameter_list),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_general_catch_clause),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_generic_dimension_specifier),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_global_attribute_section),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_goto_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_identifier),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_if_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_indexer_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_integral_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_interface_accessors),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_interface_base),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_interface_body),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_interface_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_interface_event_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_interface_indexer_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_interface_member_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_interface_method_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_interface_property_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_keyword),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_labeled_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_literal),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_local_constant_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_local_variable_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_lock_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_logical_and_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_logical_or_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_managed_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_method_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_multiplicative_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_multiplicative_expression_rest),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_named_argument),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_namespace_body),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_namespace_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_namespace_member_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_namespace_name),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_namespace_or_type_name),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_namespace_or_type_name_part),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_namespace_or_type_name_safe),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_new_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_non_array_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_non_nullable_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_null_coalescing_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_numeric_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_optional_argument_list),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_optional_modifiers),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_optionally_nullable_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_overloadable_binary_only_operator),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_overloadable_unary_only_operator),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_overloadable_unary_or_binary_operator),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_parameter_array),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_parameter_modifier),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_pointer_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_positional_argument),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_predefined_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_primary_atom),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_primary_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_primary_or_secondary_constraint),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_primary_suffix),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_property_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_qualified_identifier),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_rank_specifier),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_relational_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_relational_expression_rest),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_resource_acquisition),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_return_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_return_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_secondary_constraints),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_shift_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_shift_expression_rest),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_simple_name_or_member_access),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_simple_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_specific_catch_clause),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_stackalloc_initializer),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_statement_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_struct_body),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_struct_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_struct_interfaces),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_struct_member_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_switch_label),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_switch_section),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_switch_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_throw_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_try_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_type_arguments),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_type_arguments_or_parameters_end),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_type_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_type_declaration_rest),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_type_name),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_type_name_safe),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_type_parameter),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_type_parameter_constraints),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_type_parameter_constraints_clauses),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_type_parameters),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_typeof_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_unary_expression),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_unary_or_binary_operator_declaration),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_unbound_type_name),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_unbound_type_name_part),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_unchecked_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_unmanaged_type),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_unsafe_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_using_directive),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_using_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_variable_declaration_data),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_variable_declarator),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_variable_initializer),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_while_statement),
                                                          reinterpret_cast<parser_fun_t>(&visitor::visit_yield_statement)
                                                        }; // _S_parser_table[]

} // end of namespace csharp


