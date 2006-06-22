// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "java.h"


#include "java_lookahead.h"


java::java_compatibility_mode java::compatibility_mode()
{
  return _M_compatibility_mode;
}
void java::set_compatibility_mode( java::java_compatibility_mode mode )
{
  _M_compatibility_mode = mode;
}


// custom error recovery
bool java::yy_expected_token(int /*expected*/, std::size_t where, char const *name)
{
  //print_token_environment(this);
  report_problem(
    java::error,
    std::string("Expected token ``") + name
    //+ "'' instead of ``" + current_token_text
    + "''"
  );
  return false;
}

bool java::yy_expected_symbol(int /*expected_symbol*/, char const *name)
{
  //print_token_environment(this);
  report_problem(
    java::error,
    std::string("Expected symbol ``") + name
    //+ "'' instead of ``" + current_token_text
    + "''"
  );
  return false;
}


// lookahead hacks to make up for backtracking or LL(k)
// which are not yet implemented

/**
* This function checks if the next following tokens of the parser class
* match the beginning of a package declaration. If true is returned then it
* looks like a package declaration is coming up. It doesn't have to match the
* full package_declaration rule (because annotation contents are only checked
* rudimentarily), but it is guaranteed that the upcoming tokens are
* not a type specification.
* The function returns false if the upcoming tokens are (for sure) not
* the beginning of a package declaration.
*/
bool java::lookahead_is_package_declaration()
{
  java_lookahead* la = new java_lookahead(this);
  bool result = la->is_package_declaration_start();
  delete la;
  return result;
}

/**
* This function checks if the next following tokens of the parser class
* match the beginning of a variable declaration. If true is returned then it
* looks like a variable declaration is coming up. It doesn't have to match the
* full variable_declaration rule (as only the first few tokens are checked),
* but it is guaranteed that the upcoming tokens are not an expression.
* The function returns false if the upcoming tokens are (for sure) not
* the beginning of a variable declaration.
*/
bool java::lookahead_is_parameter_declaration()
{
  java_lookahead* la = new java_lookahead(this);
  bool result = la->is_parameter_declaration_start();
  delete la;
  return result;
}

/**
* This function checks if the next following tokens of the parser class
* match the beginning of a cast expression. If true is returned then it
* looks like a cast expression is coming up. It doesn't have to match the
* full cast_expression rule (because type arguments are only checked
* rudimentarily), but it is guaranteed that the upcoming tokens are
* not a primary expression.
* The function returns false if the upcoming tokens are (for sure) not
* the beginning of a cast expression.
*/
bool java::lookahead_is_cast_expression()
{
  java_lookahead* la = new java_lookahead(this);
  bool result = la->is_cast_expression_start();
  delete la;
  return result;
}


bool java::parse_additive_expression(additive_expression_ast **yynode)
{
  *yynode = create<additive_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      multiplicative_expression_ast *__node_0 = 0;
      if (!parse_multiplicative_expression(&__node_0))
        {
          return yy_expected_symbol(java_ast_node::Kind_multiplicative_expression, "multiplicative_expression");
        }
      (*yynode)->expression = __node_0;
      while (yytoken == Token_PLUS
             || yytoken == Token_MINUS)
        {
          additive_expression_rest_ast *__node_1 = 0;
          if (!parse_additive_expression_rest(&__node_1))
            {
              return yy_expected_symbol(java_ast_node::Kind_additive_expression_rest, "additive_expression_rest");
            }
          (*yynode)->additional_expression_sequence = snoc((*yynode)->additional_expression_sequence, __node_1, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_additive_expression_rest(additive_expression_rest_ast **yynode)
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
          (*yynode)->additive_operator = additive_expression_rest_ast::op_plus;
        }
      else if (yytoken == Token_MINUS)
        {
          if (yytoken != Token_MINUS)
            return yy_expected_token(yytoken, Token_MINUS, "-");
          yylex();
          (*yynode)->additive_operator = additive_expression_rest_ast::op_minus;
        }
      else
        {
          return false;
        }
      multiplicative_expression_ast *__node_2 = 0;
      if (!parse_multiplicative_expression(&__node_2))
        {
          return yy_expected_symbol(java_ast_node::Kind_multiplicative_expression, "multiplicative_expression");
        }
      (*yynode)->expression = __node_2;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_annotation(annotation_ast **yynode)
{
  *yynode = create<annotation_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_AT)
    {
      if (yytoken != Token_AT)
        return yy_expected_token(yytoken, Token_AT, "@");
      yylex();
      qualified_identifier_ast *__node_3 = 0;
      if (!parse_qualified_identifier(&__node_3))
        {
          return yy_expected_symbol(java_ast_node::Kind_qualified_identifier, "qualified_identifier");
        }
      (*yynode)->type_name = __node_3;
      if (yytoken == Token_LPAREN)
        {
          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "(");
          yylex();
          if (yytoken == Token_BOOLEAN
              || yytoken == Token_BYTE
              || yytoken == Token_CHAR
              || yytoken == Token_DOUBLE
              || yytoken == Token_FLOAT
              || yytoken == Token_INT
              || yytoken == Token_LONG
              || yytoken == Token_NEW
              || yytoken == Token_SHORT
              || yytoken == Token_SUPER
              || yytoken == Token_THIS
              || yytoken == Token_VOID
              || yytoken == Token_LPAREN
              || yytoken == Token_LBRACE
              || yytoken == Token_AT
              || yytoken == Token_LESS_THAN
              || yytoken == Token_BANG
              || yytoken == Token_TILDE
              || yytoken == Token_INCREMENT
              || yytoken == Token_DECREMENT
              || yytoken == Token_PLUS
              || yytoken == Token_MINUS
              || yytoken == Token_TRUE
              || yytoken == Token_FALSE
              || yytoken == Token_NULL
              || yytoken == Token_INTEGER_LITERAL
              || yytoken == Token_FLOATING_POINT_LITERAL
              || yytoken == Token_CHARACTER_LITERAL
              || yytoken == Token_STRING_LITERAL
              || yytoken == Token_IDENTIFIER)
            {
              annotation_arguments_ast *__node_4 = 0;
              if (!parse_annotation_arguments(&__node_4))
                {
                  return yy_expected_symbol(java_ast_node::Kind_annotation_arguments, "annotation_arguments");
                }
              (*yynode)->args = __node_4;
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
          (*yynode)->has_parentheses = true;
        }
      else if (true /*epsilon*/)
        {
          (*yynode)->has_parentheses = false;
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

bool java::parse_annotation_arguments(annotation_arguments_ast **yynode)
{
  *yynode = create<annotation_arguments_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LBRACE
      || yytoken == Token_AT
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      if (( LA(2).kind == Token_ASSIGN ) && (yytoken == Token_IDENTIFIER))
        {
          annotation_element_value_pair_ast *__node_5 = 0;
          if (!parse_annotation_element_value_pair(&__node_5))
            {
              return yy_expected_symbol(java_ast_node::Kind_annotation_element_value_pair, "annotation_element_value_pair");
            }
          (*yynode)->value_pair_sequence = snoc((*yynode)->value_pair_sequence, __node_5, memory_pool);
          while (yytoken == Token_COMMA)
            {
              if (yytoken != Token_COMMA)
                return yy_expected_token(yytoken, Token_COMMA, ",");
              yylex();
              annotation_element_value_pair_ast *__node_6 = 0;
              if (!parse_annotation_element_value_pair(&__node_6))
                {
                  return yy_expected_symbol(java_ast_node::Kind_annotation_element_value_pair, "annotation_element_value_pair");
                }
              (*yynode)->value_pair_sequence = snoc((*yynode)->value_pair_sequence, __node_6, memory_pool);
            }
        }
      else if (yytoken == Token_BOOLEAN
               || yytoken == Token_BYTE
               || yytoken == Token_CHAR
               || yytoken == Token_DOUBLE
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_NEW
               || yytoken == Token_SHORT
               || yytoken == Token_SUPER
               || yytoken == Token_THIS
               || yytoken == Token_VOID
               || yytoken == Token_LPAREN
               || yytoken == Token_LBRACE
               || yytoken == Token_AT
               || yytoken == Token_LESS_THAN
               || yytoken == Token_BANG
               || yytoken == Token_TILDE
               || yytoken == Token_INCREMENT
               || yytoken == Token_DECREMENT
               || yytoken == Token_PLUS
               || yytoken == Token_MINUS
               || yytoken == Token_TRUE
               || yytoken == Token_FALSE
               || yytoken == Token_NULL
               || yytoken == Token_INTEGER_LITERAL
               || yytoken == Token_FLOATING_POINT_LITERAL
               || yytoken == Token_CHARACTER_LITERAL
               || yytoken == Token_STRING_LITERAL
               || yytoken == Token_IDENTIFIER)
        {
          annotation_element_value_ast *__node_7 = 0;
          if (!parse_annotation_element_value(&__node_7))
            {
              return yy_expected_symbol(java_ast_node::Kind_annotation_element_value, "annotation_element_value");
            }
          (*yynode)->element_value = __node_7;
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

bool java::parse_annotation_element_array_initializer(annotation_element_array_initializer_ast **yynode)
{
  *yynode = create<annotation_element_array_initializer_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE)
    {
      if (yytoken != Token_LBRACE)
        return yy_expected_token(yytoken, Token_LBRACE, "{");
      yylex();
      if (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_NEW
          || yytoken == Token_SHORT
          || yytoken == Token_SUPER
          || yytoken == Token_THIS
          || yytoken == Token_VOID
          || yytoken == Token_LPAREN
          || yytoken == Token_AT
          || yytoken == Token_LESS_THAN
          || yytoken == Token_BANG
          || yytoken == Token_TILDE
          || yytoken == Token_INCREMENT
          || yytoken == Token_DECREMENT
          || yytoken == Token_PLUS
          || yytoken == Token_MINUS
          || yytoken == Token_TRUE
          || yytoken == Token_FALSE
          || yytoken == Token_NULL
          || yytoken == Token_INTEGER_LITERAL
          || yytoken == Token_FLOATING_POINT_LITERAL
          || yytoken == Token_CHARACTER_LITERAL
          || yytoken == Token_STRING_LITERAL
          || yytoken == Token_IDENTIFIER)
        {
          annotation_element_array_value_ast *__node_8 = 0;
          if (!parse_annotation_element_array_value(&__node_8))
            {
              return yy_expected_symbol(java_ast_node::Kind_annotation_element_array_value, "annotation_element_array_value");
            }
          (*yynode)->element_value_sequence = snoc((*yynode)->element_value_sequence, __node_8, memory_pool);
          while (yytoken == Token_COMMA)
            {
              if (LA(2).kind == Token_RBRACE)
                {
                  break;
                }
              if (yytoken != Token_COMMA)
                return yy_expected_token(yytoken, Token_COMMA, ",");
              yylex();
              annotation_element_array_value_ast *__node_9 = 0;
              if (!parse_annotation_element_array_value(&__node_9))
                {
                  return yy_expected_symbol(java_ast_node::Kind_annotation_element_array_value, "annotation_element_array_value");
                }
              (*yynode)->element_value_sequence = snoc((*yynode)->element_value_sequence, __node_9, memory_pool);
            }
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
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

bool java::parse_annotation_element_array_value(annotation_element_array_value_ast **yynode)
{
  *yynode = create<annotation_element_array_value_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_AT
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_NEW
          || yytoken == Token_SHORT
          || yytoken == Token_SUPER
          || yytoken == Token_THIS
          || yytoken == Token_VOID
          || yytoken == Token_LPAREN
          || yytoken == Token_LESS_THAN
          || yytoken == Token_BANG
          || yytoken == Token_TILDE
          || yytoken == Token_INCREMENT
          || yytoken == Token_DECREMENT
          || yytoken == Token_PLUS
          || yytoken == Token_MINUS
          || yytoken == Token_TRUE
          || yytoken == Token_FALSE
          || yytoken == Token_NULL
          || yytoken == Token_INTEGER_LITERAL
          || yytoken == Token_FLOATING_POINT_LITERAL
          || yytoken == Token_CHARACTER_LITERAL
          || yytoken == Token_STRING_LITERAL
          || yytoken == Token_IDENTIFIER)
        {
          conditional_expression_ast *__node_10 = 0;
          if (!parse_conditional_expression(&__node_10))
            {
              return yy_expected_symbol(java_ast_node::Kind_conditional_expression, "conditional_expression");
            }
          (*yynode)->cond_expression = __node_10;
        }
      else if (yytoken == Token_AT)
        {
          annotation_ast *__node_11 = 0;
          if (!parse_annotation(&__node_11))
            {
              return yy_expected_symbol(java_ast_node::Kind_annotation, "annotation");
            }
          (*yynode)->annotation = __node_11;
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

bool java::parse_annotation_element_value(annotation_element_value_ast **yynode)
{
  *yynode = create<annotation_element_value_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LBRACE
      || yytoken == Token_AT
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_NEW
          || yytoken == Token_SHORT
          || yytoken == Token_SUPER
          || yytoken == Token_THIS
          || yytoken == Token_VOID
          || yytoken == Token_LPAREN
          || yytoken == Token_LESS_THAN
          || yytoken == Token_BANG
          || yytoken == Token_TILDE
          || yytoken == Token_INCREMENT
          || yytoken == Token_DECREMENT
          || yytoken == Token_PLUS
          || yytoken == Token_MINUS
          || yytoken == Token_TRUE
          || yytoken == Token_FALSE
          || yytoken == Token_NULL
          || yytoken == Token_INTEGER_LITERAL
          || yytoken == Token_FLOATING_POINT_LITERAL
          || yytoken == Token_CHARACTER_LITERAL
          || yytoken == Token_STRING_LITERAL
          || yytoken == Token_IDENTIFIER)
        {
          conditional_expression_ast *__node_12 = 0;
          if (!parse_conditional_expression(&__node_12))
            {
              return yy_expected_symbol(java_ast_node::Kind_conditional_expression, "conditional_expression");
            }
          (*yynode)->cond_expression = __node_12;
        }
      else if (yytoken == Token_AT)
        {
          annotation_ast *__node_13 = 0;
          if (!parse_annotation(&__node_13))
            {
              return yy_expected_symbol(java_ast_node::Kind_annotation, "annotation");
            }
          (*yynode)->annotation = __node_13;
        }
      else if (yytoken == Token_LBRACE)
        {
          annotation_element_array_initializer_ast *__node_14 = 0;
          if (!parse_annotation_element_array_initializer(&__node_14))
            {
              return yy_expected_symbol(java_ast_node::Kind_annotation_element_array_initializer, "annotation_element_array_initializer");
            }
          (*yynode)->element_array_initializer = __node_14;
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

bool java::parse_annotation_element_value_pair(annotation_element_value_pair_ast **yynode)
{
  *yynode = create<annotation_element_value_pair_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      identifier_ast *__node_15 = 0;
      if (!parse_identifier(&__node_15))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->element_name = __node_15;
      if (yytoken != Token_ASSIGN)
        return yy_expected_token(yytoken, Token_ASSIGN, "=");
      yylex();
      annotation_element_value_ast *__node_16 = 0;
      if (!parse_annotation_element_value(&__node_16))
        {
          return yy_expected_symbol(java_ast_node::Kind_annotation_element_value, "annotation_element_value");
        }
      (*yynode)->element_value = __node_16;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_annotation_type_body(annotation_type_body_ast **yynode)
{
  *yynode = create<annotation_type_body_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE)
    {
      if (yytoken != Token_LBRACE)
        return yy_expected_token(yytoken, Token_LBRACE, "{");
      yylex();
      while (yytoken == Token_ABSTRACT
             || yytoken == Token_BOOLEAN
             || yytoken == Token_BYTE
             || yytoken == Token_CHAR
             || yytoken == Token_CLASS
             || yytoken == Token_DOUBLE
             || yytoken == Token_ENUM
             || yytoken == Token_FINAL
             || yytoken == Token_FLOAT
             || yytoken == Token_INT
             || yytoken == Token_INTERFACE
             || yytoken == Token_LONG
             || yytoken == Token_NATIVE
             || yytoken == Token_PRIVATE
             || yytoken == Token_PROTECTED
             || yytoken == Token_PUBLIC
             || yytoken == Token_SHORT
             || yytoken == Token_STATIC
             || yytoken == Token_STRICTFP
             || yytoken == Token_SYNCHRONIZED
             || yytoken == Token_TRANSIENT
             || yytoken == Token_VOID
             || yytoken == Token_VOLATILE
             || yytoken == Token_SEMICOLON
             || yytoken == Token_AT
             || yytoken == Token_IDENTIFIER)
        {
          annotation_type_field_ast *__node_17 = 0;
          if (!parse_annotation_type_field(&__node_17))
            {
              return yy_expected_symbol(java_ast_node::Kind_annotation_type_field, "annotation_type_field");
            }
          (*yynode)->annotation_type_field_sequence = snoc((*yynode)->annotation_type_field_sequence, __node_17, memory_pool);
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

bool java::parse_annotation_type_declaration(annotation_type_declaration_ast **yynode)
{
  *yynode = create<annotation_type_declaration_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_AT)
    {
      if (yytoken != Token_AT)
        return yy_expected_token(yytoken, Token_AT, "@");
      yylex();
      if (yytoken != Token_INTERFACE)
        return yy_expected_token(yytoken, Token_INTERFACE, "interface");
      yylex();
      identifier_ast *__node_18 = 0;
      if (!parse_identifier(&__node_18))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->annotation_type_name = __node_18;
      annotation_type_body_ast *__node_19 = 0;
      if (!parse_annotation_type_body(&__node_19))
        {
          return yy_expected_symbol(java_ast_node::Kind_annotation_type_body, "annotation_type_body");
        }
      (*yynode)->body = __node_19;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_annotation_type_field(annotation_type_field_ast **yynode)
{
  *yynode = create<annotation_type_field_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ABSTRACT
      || yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_CLASS
      || yytoken == Token_DOUBLE
      || yytoken == Token_ENUM
      || yytoken == Token_FINAL
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_INTERFACE
      || yytoken == Token_LONG
      || yytoken == Token_NATIVE
      || yytoken == Token_PRIVATE
      || yytoken == Token_PROTECTED
      || yytoken == Token_PUBLIC
      || yytoken == Token_SHORT
      || yytoken == Token_STATIC
      || yytoken == Token_STRICTFP
      || yytoken == Token_SYNCHRONIZED
      || yytoken == Token_TRANSIENT
      || yytoken == Token_VOID
      || yytoken == Token_VOLATILE
      || yytoken == Token_SEMICOLON
      || yytoken == Token_AT
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_ABSTRACT
          || yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_CLASS
          || yytoken == Token_DOUBLE
          || yytoken == Token_ENUM
          || yytoken == Token_FINAL
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_INTERFACE
          || yytoken == Token_LONG
          || yytoken == Token_NATIVE
          || yytoken == Token_PRIVATE
          || yytoken == Token_PROTECTED
          || yytoken == Token_PUBLIC
          || yytoken == Token_SHORT
          || yytoken == Token_STATIC
          || yytoken == Token_STRICTFP
          || yytoken == Token_SYNCHRONIZED
          || yytoken == Token_TRANSIENT
          || yytoken == Token_VOID
          || yytoken == Token_VOLATILE
          || yytoken == Token_AT
          || yytoken == Token_IDENTIFIER)
        {
          optional_modifiers_ast *__node_20 = 0;
          if (!parse_optional_modifiers(&__node_20))
            {
              return yy_expected_symbol(java_ast_node::Kind_optional_modifiers, "optional_modifiers");
            }
          (*yynode)->modifiers = __node_20;
          if (yytoken == Token_CLASS)
            {
              class_declaration_ast *__node_21 = 0;
              if (!parse_class_declaration(&__node_21))
                {
                  return yy_expected_symbol(java_ast_node::Kind_class_declaration, "class_declaration");
                }
              (*yynode)->class_declaration = __node_21;
            }
          else if (yytoken == Token_ENUM)
            {
              enum_declaration_ast *__node_22 = 0;
              if (!parse_enum_declaration(&__node_22))
                {
                  return yy_expected_symbol(java_ast_node::Kind_enum_declaration, "enum_declaration");
                }
              (*yynode)->enum_declaration = __node_22;
            }
          else if (yytoken == Token_INTERFACE)
            {
              interface_declaration_ast *__node_23 = 0;
              if (!parse_interface_declaration(&__node_23))
                {
                  return yy_expected_symbol(java_ast_node::Kind_interface_declaration, "interface_declaration");
                }
              (*yynode)->interface_declaration = __node_23;
            }
          else if (yytoken == Token_AT)
            {
              annotation_type_declaration_ast *__node_24 = 0;
              if (!parse_annotation_type_declaration(&__node_24))
                {
                  return yy_expected_symbol(java_ast_node::Kind_annotation_type_declaration, "annotation_type_declaration");
                }
              (*yynode)->annotation_type_declaration = __node_24;
            }
          else if (yytoken == Token_BOOLEAN
                   || yytoken == Token_BYTE
                   || yytoken == Token_CHAR
                   || yytoken == Token_DOUBLE
                   || yytoken == Token_FLOAT
                   || yytoken == Token_INT
                   || yytoken == Token_LONG
                   || yytoken == Token_SHORT
                   || yytoken == Token_VOID
                   || yytoken == Token_IDENTIFIER)
            {
              type_specification_ast *__node_25 = 0;
              if (!parse_type_specification(&__node_25))
                {
                  return yy_expected_symbol(java_ast_node::Kind_type_specification, "type_specification");
                }
              (*yynode)->type = __node_25;
              if (( LA(2).kind == Token_LPAREN ) && (yytoken == Token_IDENTIFIER))
                {
                  identifier_ast *__node_26 = 0;
                  if (!parse_identifier(&__node_26))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
                    }
                  (*yynode)->identifier = __node_26;
                  if (yytoken != Token_LPAREN)
                    return yy_expected_token(yytoken, Token_LPAREN, "(");
                  yylex();
                  if (yytoken != Token_RPAREN)
                    return yy_expected_token(yytoken, Token_RPAREN, ")");
                  yylex();
                  if (yytoken == Token_DEFAULT)
                    {
                      if (yytoken != Token_DEFAULT)
                        return yy_expected_token(yytoken, Token_DEFAULT, "default");
                      yylex();
                      annotation_element_value_ast *__node_27 = 0;
                      if (!parse_annotation_element_value(&__node_27))
                        {
                          return yy_expected_symbol(java_ast_node::Kind_annotation_element_value, "annotation_element_value");
                        }
                      (*yynode)->annotation_element_value = __node_27;
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
              else if (yytoken == Token_IDENTIFIER)
                {
                  variable_declarator_ast *__node_28 = 0;
                  if (!parse_variable_declarator(&__node_28))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_variable_declarator, "variable_declarator");
                    }
                  (*yynode)->variable_declarator_sequence = snoc((*yynode)->variable_declarator_sequence, __node_28, memory_pool);
                  while (yytoken == Token_COMMA)
                    {
                      if (yytoken != Token_COMMA)
                        return yy_expected_token(yytoken, Token_COMMA, ",");
                      yylex();
                      variable_declarator_ast *__node_29 = 0;
                      if (!parse_variable_declarator(&__node_29))
                        {
                          return yy_expected_symbol(java_ast_node::Kind_variable_declarator, "variable_declarator");
                        }
                      (*yynode)->variable_declarator_sequence = snoc((*yynode)->variable_declarator_sequence, __node_29, memory_pool);
                    }
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

bool java::parse_argument_list(argument_list_ast **yynode)
{
  *yynode = create<argument_list_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER || yytoken == Token_RPAREN)
    {
      if (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_NEW
          || yytoken == Token_SHORT
          || yytoken == Token_SUPER
          || yytoken == Token_THIS
          || yytoken == Token_VOID
          || yytoken == Token_LPAREN
          || yytoken == Token_LESS_THAN
          || yytoken == Token_BANG
          || yytoken == Token_TILDE
          || yytoken == Token_INCREMENT
          || yytoken == Token_DECREMENT
          || yytoken == Token_PLUS
          || yytoken == Token_MINUS
          || yytoken == Token_TRUE
          || yytoken == Token_FALSE
          || yytoken == Token_NULL
          || yytoken == Token_INTEGER_LITERAL
          || yytoken == Token_FLOATING_POINT_LITERAL
          || yytoken == Token_CHARACTER_LITERAL
          || yytoken == Token_STRING_LITERAL
          || yytoken == Token_IDENTIFIER)
        {
          expression_ast *__node_30 = 0;
          if (!parse_expression(&__node_30))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_30, memory_pool);
          while (yytoken == Token_COMMA)
            {
              if (yytoken != Token_COMMA)
                return yy_expected_token(yytoken, Token_COMMA, ",");
              yylex();
              expression_ast *__node_31 = 0;
              if (!parse_expression(&__node_31))
                {
                  return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
                }
              (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_31, memory_pool);
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

bool java::parse_array_creator_rest(array_creator_rest_ast **yynode)
{
  *yynode = create<array_creator_rest_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACKET)
    {
      if (( LA(2).kind == Token_RBRACKET ) && (yytoken == Token_LBRACKET))
        {
          mandatory_declarator_brackets_ast *__node_32 = 0;
          if (!parse_mandatory_declarator_brackets(&__node_32))
            {
              return yy_expected_symbol(java_ast_node::Kind_mandatory_declarator_brackets, "mandatory_declarator_brackets");
            }
          (*yynode)->mandatory_declarator_brackets = __node_32;
          variable_array_initializer_ast *__node_33 = 0;
          if (!parse_variable_array_initializer(&__node_33))
            {
              return yy_expected_symbol(java_ast_node::Kind_variable_array_initializer, "variable_array_initializer");
            }
          (*yynode)->array_initializer = __node_33;
        }
      else if (yytoken == Token_LBRACKET)
        {
          if (yytoken != Token_LBRACKET)
            return yy_expected_token(yytoken, Token_LBRACKET, "[");
          yylex();
          expression_ast *__node_34 = 0;
          if (!parse_expression(&__node_34))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->index_expression_sequence = snoc((*yynode)->index_expression_sequence, __node_34, memory_pool);
          if (yytoken != Token_RBRACKET)
            return yy_expected_token(yytoken, Token_RBRACKET, "]");
          yylex();
          while (yytoken == Token_LBRACKET)
            {
              if (LA(2).kind == Token_RBRACKET)
                {
                  break;
                }
              if (yytoken != Token_LBRACKET)
                return yy_expected_token(yytoken, Token_LBRACKET, "[");
              yylex();
              expression_ast *__node_35 = 0;
              if (!parse_expression(&__node_35))
                {
                  return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
                }
              (*yynode)->index_expression_sequence = snoc((*yynode)->index_expression_sequence, __node_35, memory_pool);
              if (yytoken != Token_RBRACKET)
                return yy_expected_token(yytoken, Token_RBRACKET, "]");
              yylex();
            }
          optional_declarator_brackets_ast *__node_36 = 0;
          if (!parse_optional_declarator_brackets(&__node_36))
            {
              return yy_expected_symbol(java_ast_node::Kind_optional_declarator_brackets, "optional_declarator_brackets");
            }
          (*yynode)->optional_declarator_brackets = __node_36;
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

bool java::parse_bit_and_expression(bit_and_expression_ast **yynode)
{
  *yynode = create<bit_and_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      equality_expression_ast *__node_37 = 0;
      if (!parse_equality_expression(&__node_37))
        {
          return yy_expected_symbol(java_ast_node::Kind_equality_expression, "equality_expression");
        }
      (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_37, memory_pool);
      while (yytoken == Token_BIT_AND)
        {
          if (yytoken != Token_BIT_AND)
            return yy_expected_token(yytoken, Token_BIT_AND, "&");
          yylex();
          equality_expression_ast *__node_38 = 0;
          if (!parse_equality_expression(&__node_38))
            {
              return yy_expected_symbol(java_ast_node::Kind_equality_expression, "equality_expression");
            }
          (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_38, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_bit_or_expression(bit_or_expression_ast **yynode)
{
  *yynode = create<bit_or_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      bit_xor_expression_ast *__node_39 = 0;
      if (!parse_bit_xor_expression(&__node_39))
        {
          return yy_expected_symbol(java_ast_node::Kind_bit_xor_expression, "bit_xor_expression");
        }
      (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_39, memory_pool);
      while (yytoken == Token_BIT_OR)
        {
          if (yytoken != Token_BIT_OR)
            return yy_expected_token(yytoken, Token_BIT_OR, "|");
          yylex();
          bit_xor_expression_ast *__node_40 = 0;
          if (!parse_bit_xor_expression(&__node_40))
            {
              return yy_expected_symbol(java_ast_node::Kind_bit_xor_expression, "bit_xor_expression");
            }
          (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_40, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_bit_xor_expression(bit_xor_expression_ast **yynode)
{
  *yynode = create<bit_xor_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      bit_and_expression_ast *__node_41 = 0;
      if (!parse_bit_and_expression(&__node_41))
        {
          return yy_expected_symbol(java_ast_node::Kind_bit_and_expression, "bit_and_expression");
        }
      (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_41, memory_pool);
      while (yytoken == Token_BIT_XOR)
        {
          if (yytoken != Token_BIT_XOR)
            return yy_expected_token(yytoken, Token_BIT_XOR, "^");
          yylex();
          bit_and_expression_ast *__node_42 = 0;
          if (!parse_bit_and_expression(&__node_42))
            {
              return yy_expected_symbol(java_ast_node::Kind_bit_and_expression, "bit_and_expression");
            }
          (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_42, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_block(block_ast **yynode)
{
  *yynode = create<block_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE)
    {
      if (yytoken != Token_LBRACE)
        return yy_expected_token(yytoken, Token_LBRACE, "{");
      yylex();
      while (yytoken == Token_ABSTRACT
             || yytoken == Token_ASSERT
             || yytoken == Token_BOOLEAN
             || yytoken == Token_BREAK
             || yytoken == Token_BYTE
             || yytoken == Token_CHAR
             || yytoken == Token_CLASS
             || yytoken == Token_CONTINUE
             || yytoken == Token_DO
             || yytoken == Token_DOUBLE
             || yytoken == Token_ENUM
             || yytoken == Token_FINAL
             || yytoken == Token_FLOAT
             || yytoken == Token_FOR
             || yytoken == Token_IF
             || yytoken == Token_INT
             || yytoken == Token_INTERFACE
             || yytoken == Token_LONG
             || yytoken == Token_NATIVE
             || yytoken == Token_NEW
             || yytoken == Token_PRIVATE
             || yytoken == Token_PROTECTED
             || yytoken == Token_PUBLIC
             || yytoken == Token_RETURN
             || yytoken == Token_SHORT
             || yytoken == Token_STATIC
             || yytoken == Token_STRICTFP
             || yytoken == Token_SUPER
             || yytoken == Token_SWITCH
             || yytoken == Token_SYNCHRONIZED
             || yytoken == Token_THIS
             || yytoken == Token_THROW
             || yytoken == Token_TRANSIENT
             || yytoken == Token_TRY
             || yytoken == Token_VOID
             || yytoken == Token_VOLATILE
             || yytoken == Token_WHILE
             || yytoken == Token_LPAREN
             || yytoken == Token_LBRACE
             || yytoken == Token_SEMICOLON
             || yytoken == Token_AT
             || yytoken == Token_LESS_THAN
             || yytoken == Token_BANG
             || yytoken == Token_TILDE
             || yytoken == Token_INCREMENT
             || yytoken == Token_DECREMENT
             || yytoken == Token_PLUS
             || yytoken == Token_MINUS
             || yytoken == Token_TRUE
             || yytoken == Token_FALSE
             || yytoken == Token_NULL
             || yytoken == Token_INTEGER_LITERAL
             || yytoken == Token_FLOATING_POINT_LITERAL
             || yytoken == Token_CHARACTER_LITERAL
             || yytoken == Token_STRING_LITERAL
             || yytoken == Token_IDENTIFIER)
        {
          block_statement_ast *__node_43 = 0;
          if (!parse_block_statement(&__node_43))
            {
              return yy_expected_symbol(java_ast_node::Kind_block_statement, "block_statement");
            }
          (*yynode)->statement_sequence = snoc((*yynode)->statement_sequence, __node_43, memory_pool);
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

bool java::parse_block_statement(block_statement_ast **yynode)
{
  *yynode = create<block_statement_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ABSTRACT
      || yytoken == Token_ASSERT
      || yytoken == Token_BOOLEAN
      || yytoken == Token_BREAK
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_CLASS
      || yytoken == Token_CONTINUE
      || yytoken == Token_DO
      || yytoken == Token_DOUBLE
      || yytoken == Token_ENUM
      || yytoken == Token_FINAL
      || yytoken == Token_FLOAT
      || yytoken == Token_FOR
      || yytoken == Token_IF
      || yytoken == Token_INT
      || yytoken == Token_INTERFACE
      || yytoken == Token_LONG
      || yytoken == Token_NATIVE
      || yytoken == Token_NEW
      || yytoken == Token_PRIVATE
      || yytoken == Token_PROTECTED
      || yytoken == Token_PUBLIC
      || yytoken == Token_RETURN
      || yytoken == Token_SHORT
      || yytoken == Token_STATIC
      || yytoken == Token_STRICTFP
      || yytoken == Token_SUPER
      || yytoken == Token_SWITCH
      || yytoken == Token_SYNCHRONIZED
      || yytoken == Token_THIS
      || yytoken == Token_THROW
      || yytoken == Token_TRANSIENT
      || yytoken == Token_TRY
      || yytoken == Token_VOID
      || yytoken == Token_VOLATILE
      || yytoken == Token_WHILE
      || yytoken == Token_LPAREN
      || yytoken == Token_LBRACE
      || yytoken == Token_SEMICOLON
      || yytoken == Token_AT
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      if (( lookahead_is_parameter_declaration() == true ) && (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FINAL
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_SHORT
          || yytoken == Token_VOID
          || yytoken == Token_AT
          || yytoken == Token_IDENTIFIER))
        {
          variable_declaration_ast *__node_44 = 0;
          if (!parse_variable_declaration(&__node_44))
            {
              return yy_expected_symbol(java_ast_node::Kind_variable_declaration, "variable_declaration");
            }
          (*yynode)->variable_declaration = __node_44;
          if (yytoken != Token_SEMICOLON)
            return yy_expected_token(yytoken, Token_SEMICOLON, ";");
          yylex();
        }
      else if (( (yytoken != Token_SYNCHRONIZED) ||
                 (yytoken == Token_SYNCHRONIZED && LA(2).kind == Token_LPAREN)
               ) && (yytoken == Token_ASSERT
                     || yytoken == Token_BOOLEAN
                     || yytoken == Token_BREAK
                     || yytoken == Token_BYTE
                     || yytoken == Token_CHAR
                     || yytoken == Token_CONTINUE
                     || yytoken == Token_DO
                     || yytoken == Token_DOUBLE
                     || yytoken == Token_FLOAT
                     || yytoken == Token_FOR
                     || yytoken == Token_IF
                     || yytoken == Token_INT
                     || yytoken == Token_LONG
                     || yytoken == Token_NEW
                     || yytoken == Token_RETURN
                     || yytoken == Token_SHORT
                     || yytoken == Token_SUPER
                     || yytoken == Token_SWITCH
                     || yytoken == Token_SYNCHRONIZED
                     || yytoken == Token_THIS
                     || yytoken == Token_THROW
                     || yytoken == Token_TRY
                     || yytoken == Token_VOID
                     || yytoken == Token_WHILE
                     || yytoken == Token_LPAREN
                     || yytoken == Token_LBRACE
                     || yytoken == Token_SEMICOLON
                     || yytoken == Token_LESS_THAN
                     || yytoken == Token_BANG
                     || yytoken == Token_TILDE
                     || yytoken == Token_INCREMENT
                     || yytoken == Token_DECREMENT
                     || yytoken == Token_PLUS
                     || yytoken == Token_MINUS
                     || yytoken == Token_TRUE
                     || yytoken == Token_FALSE
                     || yytoken == Token_NULL
                     || yytoken == Token_INTEGER_LITERAL
                     || yytoken == Token_FLOATING_POINT_LITERAL
                     || yytoken == Token_CHARACTER_LITERAL
                     || yytoken == Token_STRING_LITERAL
                     || yytoken == Token_IDENTIFIER))
        {
          statement_ast *__node_45 = 0;
          if (!parse_statement(&__node_45))
            {
              return yy_expected_symbol(java_ast_node::Kind_statement, "statement");
            }
          (*yynode)->statement = __node_45;
        }
      else if (yytoken == Token_ABSTRACT
               || yytoken == Token_CLASS
               || yytoken == Token_ENUM
               || yytoken == Token_FINAL
               || yytoken == Token_INTERFACE
               || yytoken == Token_NATIVE
               || yytoken == Token_PRIVATE
               || yytoken == Token_PROTECTED
               || yytoken == Token_PUBLIC
               || yytoken == Token_STATIC
               || yytoken == Token_STRICTFP
               || yytoken == Token_SYNCHRONIZED
               || yytoken == Token_TRANSIENT
               || yytoken == Token_VOLATILE
               || yytoken == Token_AT)
        {
          optional_modifiers_ast *__node_46 = 0;
          if (!parse_optional_modifiers(&__node_46))
            {
              return yy_expected_symbol(java_ast_node::Kind_optional_modifiers, "optional_modifiers");
            }
          (*yynode)->modifiers = __node_46;
          if (yytoken == Token_CLASS)
            {
              class_declaration_ast *__node_47 = 0;
              if (!parse_class_declaration(&__node_47))
                {
                  return yy_expected_symbol(java_ast_node::Kind_class_declaration, "class_declaration");
                }
              (*yynode)->class_declaration = __node_47;
            }
          else if (yytoken == Token_ENUM)
            {
              enum_declaration_ast *__node_48 = 0;
              if (!parse_enum_declaration(&__node_48))
                {
                  return yy_expected_symbol(java_ast_node::Kind_enum_declaration, "enum_declaration");
                }
              (*yynode)->enum_declaration = __node_48;
            }
          else if (yytoken == Token_INTERFACE)
            {
              interface_declaration_ast *__node_49 = 0;
              if (!parse_interface_declaration(&__node_49))
                {
                  return yy_expected_symbol(java_ast_node::Kind_interface_declaration, "interface_declaration");
                }
              (*yynode)->interface_declaration = __node_49;
            }
          else if (yytoken == Token_AT)
            {
              annotation_type_declaration_ast *__node_50 = 0;
              if (!parse_annotation_type_declaration(&__node_50))
                {
                  return yy_expected_symbol(java_ast_node::Kind_annotation_type_declaration, "annotation_type_declaration");
                }
              (*yynode)->annotation_type_declaration = __node_50;
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

bool java::parse_builtin_type(builtin_type_ast **yynode)
{
  *yynode = create<builtin_type_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_SHORT
      || yytoken == Token_VOID)
    {
      if (yytoken == Token_VOID)
        {
          if (yytoken != Token_VOID)
            return yy_expected_token(yytoken, Token_VOID, "void");
          yylex();
          (*yynode)->type = builtin_type_ast::type_void;
        }
      else if (yytoken == Token_BOOLEAN)
        {
          if (yytoken != Token_BOOLEAN)
            return yy_expected_token(yytoken, Token_BOOLEAN, "boolean");
          yylex();
          (*yynode)->type = builtin_type_ast::type_boolean;
        }
      else if (yytoken == Token_BYTE)
        {
          if (yytoken != Token_BYTE)
            return yy_expected_token(yytoken, Token_BYTE, "byte");
          yylex();
          (*yynode)->type = builtin_type_ast::type_byte;
        }
      else if (yytoken == Token_CHAR)
        {
          if (yytoken != Token_CHAR)
            return yy_expected_token(yytoken, Token_CHAR, "char");
          yylex();
          (*yynode)->type = builtin_type_ast::type_char;
        }
      else if (yytoken == Token_SHORT)
        {
          if (yytoken != Token_SHORT)
            return yy_expected_token(yytoken, Token_SHORT, "short");
          yylex();
          (*yynode)->type = builtin_type_ast::type_short;
        }
      else if (yytoken == Token_INT)
        {
          if (yytoken != Token_INT)
            return yy_expected_token(yytoken, Token_INT, "int");
          yylex();
          (*yynode)->type = builtin_type_ast::type_int;
        }
      else if (yytoken == Token_FLOAT)
        {
          if (yytoken != Token_FLOAT)
            return yy_expected_token(yytoken, Token_FLOAT, "float");
          yylex();
          (*yynode)->type = builtin_type_ast::type_float;
        }
      else if (yytoken == Token_LONG)
        {
          if (yytoken != Token_LONG)
            return yy_expected_token(yytoken, Token_LONG, "long");
          yylex();
          (*yynode)->type = builtin_type_ast::type_long;
        }
      else if (yytoken == Token_DOUBLE)
        {
          if (yytoken != Token_DOUBLE)
            return yy_expected_token(yytoken, Token_DOUBLE, "double");
          yylex();
          (*yynode)->type = builtin_type_ast::type_double;
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

bool java::parse_builtin_type_array_specification(builtin_type_array_specification_ast **yynode)
{
  *yynode = create<builtin_type_array_specification_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_SHORT
      || yytoken == Token_VOID)
    {
      builtin_type_ast *__node_51 = 0;
      if (!parse_builtin_type(&__node_51))
        {
          return yy_expected_symbol(java_ast_node::Kind_builtin_type, "builtin_type");
        }
      (*yynode)->type = __node_51;
      mandatory_declarator_brackets_ast *__node_52 = 0;
      if (!parse_mandatory_declarator_brackets(&__node_52))
        {
          return yy_expected_symbol(java_ast_node::Kind_mandatory_declarator_brackets, "mandatory_declarator_brackets");
        }
      (*yynode)->declarator_brackets = __node_52;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_builtin_type_specification(builtin_type_specification_ast **yynode)
{
  *yynode = create<builtin_type_specification_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_SHORT
      || yytoken == Token_VOID)
    {
      builtin_type_ast *__node_53 = 0;
      if (!parse_builtin_type(&__node_53))
        {
          return yy_expected_symbol(java_ast_node::Kind_builtin_type, "builtin_type");
        }
      (*yynode)->type = __node_53;
      optional_declarator_brackets_ast *__node_54 = 0;
      if (!parse_optional_declarator_brackets(&__node_54))
        {
          return yy_expected_symbol(java_ast_node::Kind_optional_declarator_brackets, "optional_declarator_brackets");
        }
      (*yynode)->declarator_brackets = __node_54;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_cast_expression(cast_expression_ast **yynode)
{
  *yynode = create<cast_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LPAREN)
    {
      if (yytoken != Token_LPAREN)
        return yy_expected_token(yytoken, Token_LPAREN, "(");
      yylex();
      if (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_SHORT
          || yytoken == Token_VOID)
        {
          builtin_type_specification_ast *__node_55 = 0;
          if (!parse_builtin_type_specification(&__node_55))
            {
              return yy_expected_symbol(java_ast_node::Kind_builtin_type_specification, "builtin_type_specification");
            }
          (*yynode)->builtin_type_specification = __node_55;
          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, ")");
          yylex();
          unary_expression_ast *__node_56 = 0;
          if (!parse_unary_expression(&__node_56))
            {
              return yy_expected_symbol(java_ast_node::Kind_unary_expression, "unary_expression");
            }
          (*yynode)->builtin_casted_expression = __node_56;
        }
      else if (yytoken == Token_IDENTIFIER)
        {
          class_type_specification_ast *__node_57 = 0;
          if (!parse_class_type_specification(&__node_57))
            {
              return yy_expected_symbol(java_ast_node::Kind_class_type_specification, "class_type_specification");
            }
          (*yynode)->class_type_specification = __node_57;
          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, ")");
          yylex();
          unary_expression_not_plusminus_ast *__node_58 = 0;
          if (!parse_unary_expression_not_plusminus(&__node_58))
            {
              return yy_expected_symbol(java_ast_node::Kind_unary_expression_not_plusminus, "unary_expression_not_plusminus");
            }
          (*yynode)->class_casted_expression = __node_58;
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

bool java::parse_class_body(class_body_ast **yynode)
{
  *yynode = create<class_body_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE)
    {
      if (yytoken != Token_LBRACE)
        return yy_expected_token(yytoken, Token_LBRACE, "{");
      yylex();
      while (yytoken == Token_ABSTRACT
             || yytoken == Token_BOOLEAN
             || yytoken == Token_BYTE
             || yytoken == Token_CHAR
             || yytoken == Token_CLASS
             || yytoken == Token_DOUBLE
             || yytoken == Token_ENUM
             || yytoken == Token_FINAL
             || yytoken == Token_FLOAT
             || yytoken == Token_INT
             || yytoken == Token_INTERFACE
             || yytoken == Token_LONG
             || yytoken == Token_NATIVE
             || yytoken == Token_PRIVATE
             || yytoken == Token_PROTECTED
             || yytoken == Token_PUBLIC
             || yytoken == Token_SHORT
             || yytoken == Token_STATIC
             || yytoken == Token_STRICTFP
             || yytoken == Token_SYNCHRONIZED
             || yytoken == Token_TRANSIENT
             || yytoken == Token_VOID
             || yytoken == Token_VOLATILE
             || yytoken == Token_LBRACE
             || yytoken == Token_SEMICOLON
             || yytoken == Token_AT
             || yytoken == Token_LESS_THAN
             || yytoken == Token_IDENTIFIER)
        {
          class_field_ast *__node_59 = 0;
          if (!parse_class_field(&__node_59))
            {
              return yy_expected_symbol(java_ast_node::Kind_class_field, "class_field");
            }
          (*yynode)->declaration_sequence = snoc((*yynode)->declaration_sequence, __node_59, memory_pool);
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

bool java::parse_class_declaration(class_declaration_ast **yynode)
{
  *yynode = create<class_declaration_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_CLASS)
    {
      if (yytoken != Token_CLASS)
        return yy_expected_token(yytoken, Token_CLASS, "class");
      yylex();
      identifier_ast *__node_60 = 0;
      if (!parse_identifier(&__node_60))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->class_name = __node_60;
      if (yytoken == Token_LESS_THAN)
        {
          type_parameters_ast *__node_61 = 0;
          if (!parse_type_parameters(&__node_61))
            {
              return yy_expected_symbol(java_ast_node::Kind_type_parameters, "type_parameters");
            }
          (*yynode)->type_parameters = __node_61;
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      if (yytoken == Token_EXTENDS)
        {
          class_extends_clause_ast *__node_62 = 0;
          if (!parse_class_extends_clause(&__node_62))
            {
              return yy_expected_symbol(java_ast_node::Kind_class_extends_clause, "class_extends_clause");
            }
          (*yynode)->extends = __node_62;
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      if (yytoken == Token_IMPLEMENTS)
        {
          implements_clause_ast *__node_63 = 0;
          if (!parse_implements_clause(&__node_63))
            {
              return yy_expected_symbol(java_ast_node::Kind_implements_clause, "implements_clause");
            }
          (*yynode)->implements = __node_63;
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      class_body_ast *__node_64 = 0;
      if (!parse_class_body(&__node_64))
        {
          return yy_expected_symbol(java_ast_node::Kind_class_body, "class_body");
        }
      (*yynode)->body = __node_64;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_class_extends_clause(class_extends_clause_ast **yynode)
{
  *yynode = create<class_extends_clause_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_EXTENDS)
    {
      if (yytoken != Token_EXTENDS)
        return yy_expected_token(yytoken, Token_EXTENDS, "extends");
      yylex();
      class_or_interface_type_ast *__node_65 = 0;
      if (!parse_class_or_interface_type(&__node_65))
        {
          return yy_expected_symbol(java_ast_node::Kind_class_or_interface_type, "class_or_interface_type");
        }
      (*yynode)->type = __node_65;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_class_field(class_field_ast **yynode)
{
  *yynode = create<class_field_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ABSTRACT
      || yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_CLASS
      || yytoken == Token_DOUBLE
      || yytoken == Token_ENUM
      || yytoken == Token_FINAL
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_INTERFACE
      || yytoken == Token_LONG
      || yytoken == Token_NATIVE
      || yytoken == Token_PRIVATE
      || yytoken == Token_PROTECTED
      || yytoken == Token_PUBLIC
      || yytoken == Token_SHORT
      || yytoken == Token_STATIC
      || yytoken == Token_STRICTFP
      || yytoken == Token_SYNCHRONIZED
      || yytoken == Token_TRANSIENT
      || yytoken == Token_VOID
      || yytoken == Token_VOLATILE
      || yytoken == Token_LBRACE
      || yytoken == Token_SEMICOLON
      || yytoken == Token_AT
      || yytoken == Token_LESS_THAN
      || yytoken == Token_IDENTIFIER)
    {
      if (( !(yytoken == Token_STATIC && LA(2).kind == Token_LBRACE) ) && (yytoken == Token_ABSTRACT
          || yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_CLASS
          || yytoken == Token_DOUBLE
          || yytoken == Token_ENUM
          || yytoken == Token_FINAL
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_INTERFACE
          || yytoken == Token_LONG
          || yytoken == Token_NATIVE
          || yytoken == Token_PRIVATE
          || yytoken == Token_PROTECTED
          || yytoken == Token_PUBLIC
          || yytoken == Token_SHORT
          || yytoken == Token_STATIC
          || yytoken == Token_STRICTFP
          || yytoken == Token_SYNCHRONIZED
          || yytoken == Token_TRANSIENT
          || yytoken == Token_VOID
          || yytoken == Token_VOLATILE
          || yytoken == Token_AT
          || yytoken == Token_LESS_THAN
          || yytoken == Token_IDENTIFIER))
        {
          optional_modifiers_ast *__node_66 = 0;
          if (!parse_optional_modifiers(&__node_66))
            {
              return yy_expected_symbol(java_ast_node::Kind_optional_modifiers, "optional_modifiers");
            }
          (*yynode)->modifiers = __node_66;
          if (yytoken == Token_CLASS)
            {
              class_declaration_ast *__node_67 = 0;
              if (!parse_class_declaration(&__node_67))
                {
                  return yy_expected_symbol(java_ast_node::Kind_class_declaration, "class_declaration");
                }
              (*yynode)->class_declaration = __node_67;
            }
          else if (yytoken == Token_ENUM)
            {
              enum_declaration_ast *__node_68 = 0;
              if (!parse_enum_declaration(&__node_68))
                {
                  return yy_expected_symbol(java_ast_node::Kind_enum_declaration, "enum_declaration");
                }
              (*yynode)->enum_declaration = __node_68;
            }
          else if (yytoken == Token_INTERFACE)
            {
              interface_declaration_ast *__node_69 = 0;
              if (!parse_interface_declaration(&__node_69))
                {
                  return yy_expected_symbol(java_ast_node::Kind_interface_declaration, "interface_declaration");
                }
              (*yynode)->interface_declaration = __node_69;
            }
          else if (yytoken == Token_AT)
            {
              annotation_type_declaration_ast *__node_70 = 0;
              if (!parse_annotation_type_declaration(&__node_70))
                {
                  return yy_expected_symbol(java_ast_node::Kind_annotation_type_declaration, "annotation_type_declaration");
                }
              (*yynode)->annotation_type_declaration = __node_70;
            }
          else if (yytoken == Token_BOOLEAN
                   || yytoken == Token_BYTE
                   || yytoken == Token_CHAR
                   || yytoken == Token_DOUBLE
                   || yytoken == Token_FLOAT
                   || yytoken == Token_INT
                   || yytoken == Token_LONG
                   || yytoken == Token_SHORT
                   || yytoken == Token_VOID
                   || yytoken == Token_LESS_THAN
                   || yytoken == Token_IDENTIFIER)
            {
              if (yytoken == Token_LESS_THAN)
                {
                  type_parameters_ast *__node_71 = 0;
                  if (!parse_type_parameters(&__node_71))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_type_parameters, "type_parameters");
                    }
                  (*yynode)->type_params = __node_71;
                }
              else if (true /*epsilon*/)
              {}
              else
                {
                  return false;
                }
              if (( LA(2).kind == Token_LPAREN ) && (yytoken == Token_IDENTIFIER))
                {
                  identifier_ast *__node_72 = 0;
                  if (!parse_identifier(&__node_72))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
                    }
                  (*yynode)->constructor_name = __node_72;
                  parameter_declaration_list_ast *__node_73 = 0;
                  if (!parse_parameter_declaration_list(&__node_73))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_parameter_declaration_list, "parameter_declaration_list");
                    }
                  (*yynode)->constructor_parameters = __node_73;
                  if (yytoken == Token_THROWS)
                    {
                      throws_clause_ast *__node_74 = 0;
                      if (!parse_throws_clause(&__node_74))
                        {
                          return yy_expected_symbol(java_ast_node::Kind_throws_clause, "throws_clause");
                        }
                      (*yynode)->constructor_throws_clause = __node_74;
                    }
                  else if (true /*epsilon*/)
                  {}
                  else
                    {
                      return false;
                    }
                  block_ast *__node_75 = 0;
                  if (!parse_block(&__node_75))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_block, "block");
                    }
                  (*yynode)->constructor_body = __node_75;
                }
              else if (yytoken == Token_BOOLEAN
                       || yytoken == Token_BYTE
                       || yytoken == Token_CHAR
                       || yytoken == Token_DOUBLE
                       || yytoken == Token_FLOAT
                       || yytoken == Token_INT
                       || yytoken == Token_LONG
                       || yytoken == Token_SHORT
                       || yytoken == Token_VOID
                       || yytoken == Token_IDENTIFIER)
                {
                  type_specification_ast *__node_76 = 0;
                  if (!parse_type_specification(&__node_76))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_type_specification, "type_specification");
                    }
                  (*yynode)->type = __node_76;
                  if (( LA(2).kind == Token_LPAREN ) && (yytoken == Token_IDENTIFIER))
                    {
                      identifier_ast *__node_77 = 0;
                      if (!parse_identifier(&__node_77))
                        {
                          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
                        }
                      (*yynode)->method_name = __node_77;
                      parameter_declaration_list_ast *__node_78 = 0;
                      if (!parse_parameter_declaration_list(&__node_78))
                        {
                          return yy_expected_symbol(java_ast_node::Kind_parameter_declaration_list, "parameter_declaration_list");
                        }
                      (*yynode)->method_parameters = __node_78;
                      optional_declarator_brackets_ast *__node_79 = 0;
                      if (!parse_optional_declarator_brackets(&__node_79))
                        {
                          return yy_expected_symbol(java_ast_node::Kind_optional_declarator_brackets, "optional_declarator_brackets");
                        }
                      (*yynode)->method_declarator_brackets = __node_79;
                      if (yytoken == Token_THROWS)
                        {
                          throws_clause_ast *__node_80 = 0;
                          if (!parse_throws_clause(&__node_80))
                            {
                              return yy_expected_symbol(java_ast_node::Kind_throws_clause, "throws_clause");
                            }
                          (*yynode)->method_throws_clause = __node_80;
                        }
                      else if (true /*epsilon*/)
                      {}
                      else
                        {
                          return false;
                        }
                      if (yytoken == Token_LBRACE)
                        {
                          block_ast *__node_81 = 0;
                          if (!parse_block(&__node_81))
                            {
                              return yy_expected_symbol(java_ast_node::Kind_block, "block");
                            }
                          (*yynode)->method_body = __node_81;
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
                  else if (yytoken == Token_IDENTIFIER)
                    {
                      variable_declarator_ast *__node_82 = 0;
                      if (!parse_variable_declarator(&__node_82))
                        {
                          return yy_expected_symbol(java_ast_node::Kind_variable_declarator, "variable_declarator");
                        }
                      (*yynode)->variable_declarator_sequence = snoc((*yynode)->variable_declarator_sequence, __node_82, memory_pool);
                      while (yytoken == Token_COMMA)
                        {
                          if (yytoken != Token_COMMA)
                            return yy_expected_token(yytoken, Token_COMMA, ",");
                          yylex();
                          variable_declarator_ast *__node_83 = 0;
                          if (!parse_variable_declarator(&__node_83))
                            {
                              return yy_expected_symbol(java_ast_node::Kind_variable_declarator, "variable_declarator");
                            }
                          (*yynode)->variable_declarator_sequence = snoc((*yynode)->variable_declarator_sequence, __node_83, memory_pool);
                        }
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
            }
          else
            {
              return false;
            }
        }
      else if (yytoken == Token_LBRACE)
        {
          block_ast *__node_84 = 0;
          if (!parse_block(&__node_84))
            {
              return yy_expected_symbol(java_ast_node::Kind_block, "block");
            }
          (*yynode)->instance_initializer_block = __node_84;
        }
      else if (( LA(2).kind == Token_LBRACE ) && (yytoken == Token_STATIC))
        {
          if (yytoken != Token_STATIC)
            return yy_expected_token(yytoken, Token_STATIC, "static");
          yylex();
          block_ast *__node_85 = 0;
          if (!parse_block(&__node_85))
            {
              return yy_expected_symbol(java_ast_node::Kind_block, "block");
            }
          (*yynode)->static_initializer_block = __node_85;
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

bool java::parse_class_or_interface_type(class_or_interface_type_ast **yynode)
{
  *yynode = create<class_or_interface_type_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      class_or_interface_type_part_ast *__node_86 = 0;
      if (!parse_class_or_interface_type_part(&__node_86))
        {
          return yy_expected_symbol(java_ast_node::Kind_class_or_interface_type_part, "class_or_interface_type_part");
        }
      (*yynode)->part_sequence = snoc((*yynode)->part_sequence, __node_86, memory_pool);
      while (yytoken == Token_DOT)
        {
          if (yytoken != Token_DOT)
            return yy_expected_token(yytoken, Token_DOT, ".");
          yylex();
          class_or_interface_type_part_ast *__node_87 = 0;
          if (!parse_class_or_interface_type_part(&__node_87))
            {
              return yy_expected_symbol(java_ast_node::Kind_class_or_interface_type_part, "class_or_interface_type_part");
            }
          (*yynode)->part_sequence = snoc((*yynode)->part_sequence, __node_87, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_class_or_interface_type_part(class_or_interface_type_part_ast **yynode)
{
  *yynode = create<class_or_interface_type_part_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      identifier_ast *__node_88 = 0;
      if (!parse_identifier(&__node_88))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->identifier = __node_88;
      if (( compatibility_mode() >= java15_compatibility ) && (yytoken == Token_LESS_THAN))
        {
          type_arguments_ast *__node_89 = 0;
          if (!parse_type_arguments(&__node_89))
            {
              return yy_expected_symbol(java_ast_node::Kind_type_arguments, "type_arguments");
            }
          (*yynode)->type_arguments = __node_89;
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

bool java::parse_class_type_specification(class_type_specification_ast **yynode)
{
  *yynode = create<class_type_specification_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      class_or_interface_type_ast *__node_90 = 0;
      if (!parse_class_or_interface_type(&__node_90))
        {
          return yy_expected_symbol(java_ast_node::Kind_class_or_interface_type, "class_or_interface_type");
        }
      (*yynode)->type = __node_90;
      optional_declarator_brackets_ast *__node_91 = 0;
      if (!parse_optional_declarator_brackets(&__node_91))
        {
          return yy_expected_symbol(java_ast_node::Kind_optional_declarator_brackets, "optional_declarator_brackets");
        }
      (*yynode)->declarator_brackets = __node_91;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_compilation_unit(compilation_unit_ast **yynode)
{
  *yynode = create<compilation_unit_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ABSTRACT
      || yytoken == Token_CLASS
      || yytoken == Token_ENUM
      || yytoken == Token_FINAL
      || yytoken == Token_IMPORT
      || yytoken == Token_INTERFACE
      || yytoken == Token_NATIVE
      || yytoken == Token_PACKAGE
      || yytoken == Token_PRIVATE
      || yytoken == Token_PROTECTED
      || yytoken == Token_PUBLIC
      || yytoken == Token_STATIC
      || yytoken == Token_STRICTFP
      || yytoken == Token_SYNCHRONIZED
      || yytoken == Token_TRANSIENT
      || yytoken == Token_VOLATILE
      || yytoken == Token_SEMICOLON
      || yytoken == Token_AT || yytoken == Token_EOF)
    {
      ltCounter = 0;
      if (( lookahead_is_package_declaration() == true ) && (yytoken == Token_PACKAGE
          || yytoken == Token_AT))
        {
          package_declaration_ast *__node_92 = 0;
          if (!parse_package_declaration(&__node_92))
            {
              return yy_expected_symbol(java_ast_node::Kind_package_declaration, "package_declaration");
            }
          (*yynode)->package_declaration = __node_92;
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      while (yytoken == Token_IMPORT)
        {
          import_declaration_ast *__node_93 = 0;
          if (!parse_import_declaration(&__node_93))
            {
              return yy_expected_symbol(java_ast_node::Kind_import_declaration, "import_declaration");
            }
          (*yynode)->import_declaration_sequence = snoc((*yynode)->import_declaration_sequence, __node_93, memory_pool);
        }
      while (yytoken == Token_ABSTRACT
             || yytoken == Token_CLASS
             || yytoken == Token_ENUM
             || yytoken == Token_FINAL
             || yytoken == Token_INTERFACE
             || yytoken == Token_NATIVE
             || yytoken == Token_PRIVATE
             || yytoken == Token_PROTECTED
             || yytoken == Token_PUBLIC
             || yytoken == Token_STATIC
             || yytoken == Token_STRICTFP
             || yytoken == Token_SYNCHRONIZED
             || yytoken == Token_TRANSIENT
             || yytoken == Token_VOLATILE
             || yytoken == Token_SEMICOLON
             || yytoken == Token_AT)
        {
          type_declaration_ast *__node_94 = 0;
          if (!parse_type_declaration(&__node_94))
            {
              return yy_expected_symbol(java_ast_node::Kind_type_declaration, "type_declaration");
            }
          (*yynode)->type_declaration_sequence = snoc((*yynode)->type_declaration_sequence, __node_94, memory_pool);
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

bool java::parse_conditional_expression(conditional_expression_ast **yynode)
{
  *yynode = create<conditional_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      logical_or_expression_ast *__node_95 = 0;
      if (!parse_logical_or_expression(&__node_95))
        {
          return yy_expected_symbol(java_ast_node::Kind_logical_or_expression, "logical_or_expression");
        }
      (*yynode)->logical_or_expression = __node_95;
      if (yytoken == Token_QUESTION)
        {
          if (yytoken != Token_QUESTION)
            return yy_expected_token(yytoken, Token_QUESTION, "?");
          yylex();
          expression_ast *__node_96 = 0;
          if (!parse_expression(&__node_96))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->if_expression = __node_96;
          if (yytoken != Token_COLON)
            return yy_expected_token(yytoken, Token_COLON, ":");
          yylex();
          conditional_expression_ast *__node_97 = 0;
          if (!parse_conditional_expression(&__node_97))
            {
              return yy_expected_symbol(java_ast_node::Kind_conditional_expression, "conditional_expression");
            }
          (*yynode)->else_expression = __node_97;
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

bool java::parse_enum_body(enum_body_ast **yynode)
{
  *yynode = create<enum_body_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE)
    {
      if (yytoken != Token_LBRACE)
        return yy_expected_token(yytoken, Token_LBRACE, "{");
      yylex();
      if (yytoken == Token_AT
          || yytoken == Token_IDENTIFIER)
        {
          enum_constant_ast *__node_98 = 0;
          if (!parse_enum_constant(&__node_98))
            {
              return yy_expected_symbol(java_ast_node::Kind_enum_constant, "enum_constant");
            }
          (*yynode)->enum_constant_sequence = snoc((*yynode)->enum_constant_sequence, __node_98, memory_pool);
          while (yytoken == Token_COMMA)
            {
              if ( LA(2).kind == Token_SEMICOLON
                   || LA(2).kind == Token_RBRACE )
                {
                  break;
                }
              if (yytoken != Token_COMMA)
                return yy_expected_token(yytoken, Token_COMMA, ",");
              yylex();
              enum_constant_ast *__node_99 = 0;
              if (!parse_enum_constant(&__node_99))
                {
                  return yy_expected_symbol(java_ast_node::Kind_enum_constant, "enum_constant");
                }
              (*yynode)->enum_constant_sequence = snoc((*yynode)->enum_constant_sequence, __node_99, memory_pool);
            }
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
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
      if (yytoken == Token_SEMICOLON)
        {
          if (yytoken != Token_SEMICOLON)
            return yy_expected_token(yytoken, Token_SEMICOLON, ";");
          yylex();
          while (yytoken == Token_ABSTRACT
                 || yytoken == Token_BOOLEAN
                 || yytoken == Token_BYTE
                 || yytoken == Token_CHAR
                 || yytoken == Token_CLASS
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_ENUM
                 || yytoken == Token_FINAL
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_INTERFACE
                 || yytoken == Token_LONG
                 || yytoken == Token_NATIVE
                 || yytoken == Token_PRIVATE
                 || yytoken == Token_PROTECTED
                 || yytoken == Token_PUBLIC
                 || yytoken == Token_SHORT
                 || yytoken == Token_STATIC
                 || yytoken == Token_STRICTFP
                 || yytoken == Token_SYNCHRONIZED
                 || yytoken == Token_TRANSIENT
                 || yytoken == Token_VOID
                 || yytoken == Token_VOLATILE
                 || yytoken == Token_LBRACE
                 || yytoken == Token_SEMICOLON
                 || yytoken == Token_AT
                 || yytoken == Token_LESS_THAN
                 || yytoken == Token_IDENTIFIER)
            {
              class_field_ast *__node_100 = 0;
              if (!parse_class_field(&__node_100))
                {
                  return yy_expected_symbol(java_ast_node::Kind_class_field, "class_field");
                }
              (*yynode)->class_field_sequence = snoc((*yynode)->class_field_sequence, __node_100, memory_pool);
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

bool java::parse_enum_constant(enum_constant_ast **yynode)
{
  *yynode = create<enum_constant_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_AT
      || yytoken == Token_IDENTIFIER)
    {
      while (yytoken == Token_AT)
        {
          annotation_ast *__node_101 = 0;
          if (!parse_annotation(&__node_101))
            {
              return yy_expected_symbol(java_ast_node::Kind_annotation, "annotation");
            }
          (*yynode)->annotation_sequence = snoc((*yynode)->annotation_sequence, __node_101, memory_pool);
        }
      identifier_ast *__node_102 = 0;
      if (!parse_identifier(&__node_102))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->identifier = __node_102;
      if (yytoken == Token_LPAREN)
        {
          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "(");
          yylex();
          argument_list_ast *__node_103 = 0;
          if (!parse_argument_list(&__node_103))
            {
              return yy_expected_symbol(java_ast_node::Kind_argument_list, "argument_list");
            }
          (*yynode)->arguments = __node_103;
          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, ")");
          yylex();
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      if (yytoken == Token_LBRACE)
        {
          enum_constant_body_ast *__node_104 = 0;
          if (!parse_enum_constant_body(&__node_104))
            {
              return yy_expected_symbol(java_ast_node::Kind_enum_constant_body, "enum_constant_body");
            }
          (*yynode)->body = __node_104;
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

bool java::parse_enum_constant_body(enum_constant_body_ast **yynode)
{
  *yynode = create<enum_constant_body_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE)
    {
      if (yytoken != Token_LBRACE)
        return yy_expected_token(yytoken, Token_LBRACE, "{");
      yylex();
      while (yytoken == Token_ABSTRACT
             || yytoken == Token_BOOLEAN
             || yytoken == Token_BYTE
             || yytoken == Token_CHAR
             || yytoken == Token_CLASS
             || yytoken == Token_DOUBLE
             || yytoken == Token_ENUM
             || yytoken == Token_FINAL
             || yytoken == Token_FLOAT
             || yytoken == Token_INT
             || yytoken == Token_INTERFACE
             || yytoken == Token_LONG
             || yytoken == Token_NATIVE
             || yytoken == Token_PRIVATE
             || yytoken == Token_PROTECTED
             || yytoken == Token_PUBLIC
             || yytoken == Token_SHORT
             || yytoken == Token_STATIC
             || yytoken == Token_STRICTFP
             || yytoken == Token_SYNCHRONIZED
             || yytoken == Token_TRANSIENT
             || yytoken == Token_VOID
             || yytoken == Token_VOLATILE
             || yytoken == Token_LBRACE
             || yytoken == Token_SEMICOLON
             || yytoken == Token_AT
             || yytoken == Token_LESS_THAN
             || yytoken == Token_IDENTIFIER)
        {
          enum_constant_field_ast *__node_105 = 0;
          if (!parse_enum_constant_field(&__node_105))
            {
              return yy_expected_symbol(java_ast_node::Kind_enum_constant_field, "enum_constant_field");
            }
          (*yynode)->declaration_sequence = snoc((*yynode)->declaration_sequence, __node_105, memory_pool);
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

bool java::parse_enum_constant_field(enum_constant_field_ast **yynode)
{
  *yynode = create<enum_constant_field_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ABSTRACT
      || yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_CLASS
      || yytoken == Token_DOUBLE
      || yytoken == Token_ENUM
      || yytoken == Token_FINAL
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_INTERFACE
      || yytoken == Token_LONG
      || yytoken == Token_NATIVE
      || yytoken == Token_PRIVATE
      || yytoken == Token_PROTECTED
      || yytoken == Token_PUBLIC
      || yytoken == Token_SHORT
      || yytoken == Token_STATIC
      || yytoken == Token_STRICTFP
      || yytoken == Token_SYNCHRONIZED
      || yytoken == Token_TRANSIENT
      || yytoken == Token_VOID
      || yytoken == Token_VOLATILE
      || yytoken == Token_LBRACE
      || yytoken == Token_SEMICOLON
      || yytoken == Token_AT
      || yytoken == Token_LESS_THAN
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_ABSTRACT
          || yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_CLASS
          || yytoken == Token_DOUBLE
          || yytoken == Token_ENUM
          || yytoken == Token_FINAL
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_INTERFACE
          || yytoken == Token_LONG
          || yytoken == Token_NATIVE
          || yytoken == Token_PRIVATE
          || yytoken == Token_PROTECTED
          || yytoken == Token_PUBLIC
          || yytoken == Token_SHORT
          || yytoken == Token_STATIC
          || yytoken == Token_STRICTFP
          || yytoken == Token_SYNCHRONIZED
          || yytoken == Token_TRANSIENT
          || yytoken == Token_VOID
          || yytoken == Token_VOLATILE
          || yytoken == Token_AT
          || yytoken == Token_LESS_THAN
          || yytoken == Token_IDENTIFIER)
        {
          optional_modifiers_ast *__node_106 = 0;
          if (!parse_optional_modifiers(&__node_106))
            {
              return yy_expected_symbol(java_ast_node::Kind_optional_modifiers, "optional_modifiers");
            }
          (*yynode)->modifiers = __node_106;
          if (yytoken == Token_CLASS)
            {
              class_declaration_ast *__node_107 = 0;
              if (!parse_class_declaration(&__node_107))
                {
                  return yy_expected_symbol(java_ast_node::Kind_class_declaration, "class_declaration");
                }
              (*yynode)->class_declaration = __node_107;
            }
          else if (yytoken == Token_ENUM)
            {
              enum_declaration_ast *__node_108 = 0;
              if (!parse_enum_declaration(&__node_108))
                {
                  return yy_expected_symbol(java_ast_node::Kind_enum_declaration, "enum_declaration");
                }
              (*yynode)->enum_declaration = __node_108;
            }
          else if (yytoken == Token_INTERFACE)
            {
              interface_declaration_ast *__node_109 = 0;
              if (!parse_interface_declaration(&__node_109))
                {
                  return yy_expected_symbol(java_ast_node::Kind_interface_declaration, "interface_declaration");
                }
              (*yynode)->interface_declaration = __node_109;
            }
          else if (yytoken == Token_AT)
            {
              annotation_type_declaration_ast *__node_110 = 0;
              if (!parse_annotation_type_declaration(&__node_110))
                {
                  return yy_expected_symbol(java_ast_node::Kind_annotation_type_declaration, "annotation_type_declaration");
                }
              (*yynode)->annotation_type_declaration = __node_110;
            }
          else if (yytoken == Token_BOOLEAN
                   || yytoken == Token_BYTE
                   || yytoken == Token_CHAR
                   || yytoken == Token_DOUBLE
                   || yytoken == Token_FLOAT
                   || yytoken == Token_INT
                   || yytoken == Token_LONG
                   || yytoken == Token_SHORT
                   || yytoken == Token_VOID
                   || yytoken == Token_LESS_THAN
                   || yytoken == Token_IDENTIFIER)
            {
              if (yytoken == Token_LESS_THAN)
                {
                  type_parameters_ast *__node_111 = 0;
                  if (!parse_type_parameters(&__node_111))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_type_parameters, "type_parameters");
                    }
                  (*yynode)->type_params = __node_111;
                }
              else if (true /*epsilon*/)
              {}
              else
                {
                  return false;
                }
              type_specification_ast *__node_112 = 0;
              if (!parse_type_specification(&__node_112))
                {
                  return yy_expected_symbol(java_ast_node::Kind_type_specification, "type_specification");
                }
              (*yynode)->type = __node_112;
              if (( LA(2).kind == Token_LPAREN ) && (yytoken == Token_IDENTIFIER))
                {
                  identifier_ast *__node_113 = 0;
                  if (!parse_identifier(&__node_113))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
                    }
                  (*yynode)->method_name = __node_113;
                  parameter_declaration_list_ast *__node_114 = 0;
                  if (!parse_parameter_declaration_list(&__node_114))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_parameter_declaration_list, "parameter_declaration_list");
                    }
                  (*yynode)->method_parameters = __node_114;
                  optional_declarator_brackets_ast *__node_115 = 0;
                  if (!parse_optional_declarator_brackets(&__node_115))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_optional_declarator_brackets, "optional_declarator_brackets");
                    }
                  (*yynode)->method_declarator_brackets = __node_115;
                  if (yytoken == Token_THROWS)
                    {
                      throws_clause_ast *__node_116 = 0;
                      if (!parse_throws_clause(&__node_116))
                        {
                          return yy_expected_symbol(java_ast_node::Kind_throws_clause, "throws_clause");
                        }
                      (*yynode)->method_throws_clause = __node_116;
                    }
                  else if (true /*epsilon*/)
                  {}
                  else
                    {
                      return false;
                    }
                  if (yytoken == Token_LBRACE)
                    {
                      block_ast *__node_117 = 0;
                      if (!parse_block(&__node_117))
                        {
                          return yy_expected_symbol(java_ast_node::Kind_block, "block");
                        }
                      (*yynode)->method_body = __node_117;
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
              else if (yytoken == Token_IDENTIFIER)
                {
                  variable_declarator_ast *__node_118 = 0;
                  if (!parse_variable_declarator(&__node_118))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_variable_declarator, "variable_declarator");
                    }
                  (*yynode)->variable_declarator_sequence = snoc((*yynode)->variable_declarator_sequence, __node_118, memory_pool);
                  while (yytoken == Token_COMMA)
                    {
                      if (yytoken != Token_COMMA)
                        return yy_expected_token(yytoken, Token_COMMA, ",");
                      yylex();
                      variable_declarator_ast *__node_119 = 0;
                      if (!parse_variable_declarator(&__node_119))
                        {
                          return yy_expected_symbol(java_ast_node::Kind_variable_declarator, "variable_declarator");
                        }
                      (*yynode)->variable_declarator_sequence = snoc((*yynode)->variable_declarator_sequence, __node_119, memory_pool);
                    }
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
        }
      else if (yytoken == Token_LBRACE)
        {
          block_ast *__node_120 = 0;
          if (!parse_block(&__node_120))
            {
              return yy_expected_symbol(java_ast_node::Kind_block, "block");
            }
          (*yynode)->instance_initializer_block = __node_120;
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

bool java::parse_enum_declaration(enum_declaration_ast **yynode)
{
  *yynode = create<enum_declaration_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ENUM)
    {
      if (yytoken != Token_ENUM)
        return yy_expected_token(yytoken, Token_ENUM, "enum");
      yylex();
      identifier_ast *__node_121 = 0;
      if (!parse_identifier(&__node_121))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->enum_name = __node_121;
      if (yytoken == Token_IMPLEMENTS)
        {
          implements_clause_ast *__node_122 = 0;
          if (!parse_implements_clause(&__node_122))
            {
              return yy_expected_symbol(java_ast_node::Kind_implements_clause, "implements_clause");
            }
          (*yynode)->implements = __node_122;
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      enum_body_ast *__node_123 = 0;
      if (!parse_enum_body(&__node_123))
        {
          return yy_expected_symbol(java_ast_node::Kind_enum_body, "enum_body");
        }
      (*yynode)->body = __node_123;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_equality_expression(equality_expression_ast **yynode)
{
  *yynode = create<equality_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      relational_expression_ast *__node_124 = 0;
      if (!parse_relational_expression(&__node_124))
        {
          return yy_expected_symbol(java_ast_node::Kind_relational_expression, "relational_expression");
        }
      (*yynode)->expression = __node_124;
      while (yytoken == Token_EQUAL
             || yytoken == Token_NOT_EQUAL)
        {
          equality_expression_rest_ast *__node_125 = 0;
          if (!parse_equality_expression_rest(&__node_125))
            {
              return yy_expected_symbol(java_ast_node::Kind_equality_expression_rest, "equality_expression_rest");
            }
          (*yynode)->additional_expression_sequence = snoc((*yynode)->additional_expression_sequence, __node_125, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_equality_expression_rest(equality_expression_rest_ast **yynode)
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
          (*yynode)->equality_operator = equality_expression_rest_ast::op_equal;
        }
      else if (yytoken == Token_NOT_EQUAL)
        {
          if (yytoken != Token_NOT_EQUAL)
            return yy_expected_token(yytoken, Token_NOT_EQUAL, "!=");
          yylex();
          (*yynode)->equality_operator = equality_expression_rest_ast::op_not_equal;
        }
      else
        {
          return false;
        }
      relational_expression_ast *__node_126 = 0;
      if (!parse_relational_expression(&__node_126))
        {
          return yy_expected_symbol(java_ast_node::Kind_relational_expression, "relational_expression");
        }
      (*yynode)->expression = __node_126;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_expression(expression_ast **yynode)
{
  *yynode = create<expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      conditional_expression_ast *__node_127 = 0;
      if (!parse_conditional_expression(&__node_127))
        {
          return yy_expected_symbol(java_ast_node::Kind_conditional_expression, "conditional_expression");
        }
      (*yynode)->conditional_expression = __node_127;
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
          || yytoken == Token_SIGNED_RSHIFT_ASSIGN
          || yytoken == Token_UNSIGNED_RSHIFT_ASSIGN)
        {
          if (yytoken == Token_ASSIGN)
            {
              if (yytoken != Token_ASSIGN)
                return yy_expected_token(yytoken, Token_ASSIGN, "=");
              yylex();
              (*yynode)->assignment_operator = expression_ast::op_assign;
            }
          else if (yytoken == Token_PLUS_ASSIGN)
            {
              if (yytoken != Token_PLUS_ASSIGN)
                return yy_expected_token(yytoken, Token_PLUS_ASSIGN, "+=");
              yylex();
              (*yynode)->assignment_operator = expression_ast::op_plus_assign;
            }
          else if (yytoken == Token_MINUS_ASSIGN)
            {
              if (yytoken != Token_MINUS_ASSIGN)
                return yy_expected_token(yytoken, Token_MINUS_ASSIGN, "-=");
              yylex();
              (*yynode)->assignment_operator = expression_ast::op_minus_assign;
            }
          else if (yytoken == Token_STAR_ASSIGN)
            {
              if (yytoken != Token_STAR_ASSIGN)
                return yy_expected_token(yytoken, Token_STAR_ASSIGN, "*=");
              yylex();
              (*yynode)->assignment_operator = expression_ast::op_star_assign;
            }
          else if (yytoken == Token_SLASH_ASSIGN)
            {
              if (yytoken != Token_SLASH_ASSIGN)
                return yy_expected_token(yytoken, Token_SLASH_ASSIGN, "/=");
              yylex();
              (*yynode)->assignment_operator = expression_ast::op_slash_assign;
            }
          else if (yytoken == Token_BIT_AND_ASSIGN)
            {
              if (yytoken != Token_BIT_AND_ASSIGN)
                return yy_expected_token(yytoken, Token_BIT_AND_ASSIGN, "&=");
              yylex();
              (*yynode)->assignment_operator = expression_ast::op_bit_and_assign;
            }
          else if (yytoken == Token_BIT_OR_ASSIGN)
            {
              if (yytoken != Token_BIT_OR_ASSIGN)
                return yy_expected_token(yytoken, Token_BIT_OR_ASSIGN, "|=");
              yylex();
              (*yynode)->assignment_operator = expression_ast::op_bit_or_assign;
            }
          else if (yytoken == Token_BIT_XOR_ASSIGN)
            {
              if (yytoken != Token_BIT_XOR_ASSIGN)
                return yy_expected_token(yytoken, Token_BIT_XOR_ASSIGN, "^=");
              yylex();
              (*yynode)->assignment_operator = expression_ast::op_bit_xor_assign;
            }
          else if (yytoken == Token_REMAINDER_ASSIGN)
            {
              if (yytoken != Token_REMAINDER_ASSIGN)
                return yy_expected_token(yytoken, Token_REMAINDER_ASSIGN, "%=");
              yylex();
              (*yynode)->assignment_operator = expression_ast::op_remainder_assign;
            }
          else if (yytoken == Token_LSHIFT_ASSIGN)
            {
              if (yytoken != Token_LSHIFT_ASSIGN)
                return yy_expected_token(yytoken, Token_LSHIFT_ASSIGN, "<<=");
              yylex();
              (*yynode)->assignment_operator = expression_ast::op_lshift_assign;
            }
          else if (yytoken == Token_SIGNED_RSHIFT_ASSIGN)
            {
              if (yytoken != Token_SIGNED_RSHIFT_ASSIGN)
                return yy_expected_token(yytoken, Token_SIGNED_RSHIFT_ASSIGN, ">>=");
              yylex();
              (*yynode)->assignment_operator = expression_ast::op_signed_rshift_assign;
            }
          else if (yytoken == Token_UNSIGNED_RSHIFT_ASSIGN)
            {
              if (yytoken != Token_UNSIGNED_RSHIFT_ASSIGN)
                return yy_expected_token(yytoken, Token_UNSIGNED_RSHIFT_ASSIGN, ">>>=");
              yylex();
              (*yynode)->assignment_operator = expression_ast::op_unsigned_rshift_assign;
            }
          else
            {
              return false;
            }
          expression_ast *__node_128 = 0;
          if (!parse_expression(&__node_128))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->assignment_expression = __node_128;
        }
      else if (true /*epsilon*/)
        {
          (*yynode)->assignment_operator = expression_ast::no_assignment;
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

bool java::parse_for_clause_traditional_rest(for_clause_traditional_rest_ast **yynode)
{
  *yynode = create<for_clause_traditional_rest_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_SEMICOLON)
    {
      if (yytoken != Token_SEMICOLON)
        return yy_expected_token(yytoken, Token_SEMICOLON, ";");
      yylex();
      if (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_NEW
          || yytoken == Token_SHORT
          || yytoken == Token_SUPER
          || yytoken == Token_THIS
          || yytoken == Token_VOID
          || yytoken == Token_LPAREN
          || yytoken == Token_LESS_THAN
          || yytoken == Token_BANG
          || yytoken == Token_TILDE
          || yytoken == Token_INCREMENT
          || yytoken == Token_DECREMENT
          || yytoken == Token_PLUS
          || yytoken == Token_MINUS
          || yytoken == Token_TRUE
          || yytoken == Token_FALSE
          || yytoken == Token_NULL
          || yytoken == Token_INTEGER_LITERAL
          || yytoken == Token_FLOATING_POINT_LITERAL
          || yytoken == Token_CHARACTER_LITERAL
          || yytoken == Token_STRING_LITERAL
          || yytoken == Token_IDENTIFIER)
        {
          expression_ast *__node_129 = 0;
          if (!parse_expression(&__node_129))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->for_condition = __node_129;
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
      if (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_NEW
          || yytoken == Token_SHORT
          || yytoken == Token_SUPER
          || yytoken == Token_THIS
          || yytoken == Token_VOID
          || yytoken == Token_LPAREN
          || yytoken == Token_LESS_THAN
          || yytoken == Token_BANG
          || yytoken == Token_TILDE
          || yytoken == Token_INCREMENT
          || yytoken == Token_DECREMENT
          || yytoken == Token_PLUS
          || yytoken == Token_MINUS
          || yytoken == Token_TRUE
          || yytoken == Token_FALSE
          || yytoken == Token_NULL
          || yytoken == Token_INTEGER_LITERAL
          || yytoken == Token_FLOATING_POINT_LITERAL
          || yytoken == Token_CHARACTER_LITERAL
          || yytoken == Token_STRING_LITERAL
          || yytoken == Token_IDENTIFIER)
        {
          expression_ast *__node_130 = 0;
          if (!parse_expression(&__node_130))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->for_update_expression_sequence = snoc((*yynode)->for_update_expression_sequence, __node_130, memory_pool);
          while (yytoken == Token_COMMA)
            {
              if (yytoken != Token_COMMA)
                return yy_expected_token(yytoken, Token_COMMA, ",");
              yylex();
              expression_ast *__node_131 = 0;
              if (!parse_expression(&__node_131))
                {
                  return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
                }
              (*yynode)->for_update_expression_sequence = snoc((*yynode)->for_update_expression_sequence, __node_131, memory_pool);
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

bool java::parse_for_control(for_control_ast **yynode)
{
  *yynode = create<for_control_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FINAL
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_SEMICOLON
      || yytoken == Token_AT
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      if (( lookahead_is_parameter_declaration() == true ) && (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FINAL
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_SHORT
          || yytoken == Token_VOID
          || yytoken == Token_AT
          || yytoken == Token_IDENTIFIER))
        {
          parameter_declaration_ast *__node_132 = 0;
          if (!parse_parameter_declaration(&__node_132))
            {
              return yy_expected_symbol(java_ast_node::Kind_parameter_declaration, "parameter_declaration");
            }
          (*yynode)->vardecl_start_or_foreach_parameter = __node_132;
          if (( compatibility_mode() >= java15_compatibility ) && (yytoken == Token_COLON))
            {
              if (yytoken != Token_COLON)
                return yy_expected_token(yytoken, Token_COLON, ":");
              yylex();
              expression_ast *__node_133 = 0;
              if (!parse_expression(&__node_133))
                {
                  return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
                }
              (*yynode)->iterable_expression = __node_133;
            }
          else if (yytoken == Token_SEMICOLON
                   || yytoken == Token_COMMA
                   || yytoken == Token_ASSIGN)
            {
              variable_declaration_rest_ast *__node_134 = 0;
              if (!parse_variable_declaration_rest(&__node_134))
                {
                  return yy_expected_symbol(java_ast_node::Kind_variable_declaration_rest, "variable_declaration_rest");
                }
              (*yynode)->variable_declaration_rest = __node_134;
              for_clause_traditional_rest_ast *__node_135 = 0;
              if (!parse_for_clause_traditional_rest(&__node_135))
                {
                  return yy_expected_symbol(java_ast_node::Kind_for_clause_traditional_rest, "for_clause_traditional_rest");
                }
              (*yynode)->traditional_for_rest = __node_135;
            }
          else
            {
              return false;
            }
        }
      else if (yytoken == Token_SEMICOLON)
        {
          for_clause_traditional_rest_ast *__node_136 = 0;
          if (!parse_for_clause_traditional_rest(&__node_136))
            {
              return yy_expected_symbol(java_ast_node::Kind_for_clause_traditional_rest, "for_clause_traditional_rest");
            }
          (*yynode)->traditional_for_rest = __node_136;
        }
      else if (yytoken == Token_BOOLEAN
               || yytoken == Token_BYTE
               || yytoken == Token_CHAR
               || yytoken == Token_DOUBLE
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_NEW
               || yytoken == Token_SHORT
               || yytoken == Token_SUPER
               || yytoken == Token_THIS
               || yytoken == Token_VOID
               || yytoken == Token_LPAREN
               || yytoken == Token_LESS_THAN
               || yytoken == Token_BANG
               || yytoken == Token_TILDE
               || yytoken == Token_INCREMENT
               || yytoken == Token_DECREMENT
               || yytoken == Token_PLUS
               || yytoken == Token_MINUS
               || yytoken == Token_TRUE
               || yytoken == Token_FALSE
               || yytoken == Token_NULL
               || yytoken == Token_INTEGER_LITERAL
               || yytoken == Token_FLOATING_POINT_LITERAL
               || yytoken == Token_CHARACTER_LITERAL
               || yytoken == Token_STRING_LITERAL
               || yytoken == Token_IDENTIFIER)
        {
          expression_ast *__node_137 = 0;
          if (!parse_expression(&__node_137))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_137, memory_pool);
          while (yytoken == Token_COMMA)
            {
              if (yytoken != Token_COMMA)
                return yy_expected_token(yytoken, Token_COMMA, ",");
              yylex();
              expression_ast *__node_138 = 0;
              if (!parse_expression(&__node_138))
                {
                  return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
                }
              (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_138, memory_pool);
            }
          for_clause_traditional_rest_ast *__node_139 = 0;
          if (!parse_for_clause_traditional_rest(&__node_139))
            {
              return yy_expected_symbol(java_ast_node::Kind_for_clause_traditional_rest, "for_clause_traditional_rest");
            }
          (*yynode)->traditional_for_rest = __node_139;
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

bool java::parse_identifier(identifier_ast **yynode)
{
  *yynode = create<identifier_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      if (yytoken != Token_IDENTIFIER)
        return yy_expected_token(yytoken, Token_IDENTIFIER, "identifier");
      (*yynode)->ident = token_stream->index() - 1;
      yylex();
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_implements_clause(implements_clause_ast **yynode)
{
  *yynode = create<implements_clause_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IMPLEMENTS)
    {
      if (yytoken != Token_IMPLEMENTS)
        return yy_expected_token(yytoken, Token_IMPLEMENTS, "implements");
      yylex();
      class_or_interface_type_ast *__node_140 = 0;
      if (!parse_class_or_interface_type(&__node_140))
        {
          return yy_expected_symbol(java_ast_node::Kind_class_or_interface_type, "class_or_interface_type");
        }
      (*yynode)->type_sequence = snoc((*yynode)->type_sequence, __node_140, memory_pool);
      while (yytoken == Token_COMMA)
        {
          if (yytoken != Token_COMMA)
            return yy_expected_token(yytoken, Token_COMMA, ",");
          yylex();
          class_or_interface_type_ast *__node_141 = 0;
          if (!parse_class_or_interface_type(&__node_141))
            {
              return yy_expected_symbol(java_ast_node::Kind_class_or_interface_type, "class_or_interface_type");
            }
          (*yynode)->type_sequence = snoc((*yynode)->type_sequence, __node_141, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_import_declaration(import_declaration_ast **yynode)
{
  *yynode = create<import_declaration_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IMPORT)
    {
      if (yytoken != Token_IMPORT)
        return yy_expected_token(yytoken, Token_IMPORT, "import");
      yylex();
      if (yytoken == Token_STATIC)
        {
          if (yytoken != Token_STATIC)
            return yy_expected_token(yytoken, Token_STATIC, "static");
          yylex();
          (*yynode)->static_import = true;
        }
      else if (true /*epsilon*/)
        {
          (*yynode)->static_import = false;
        }
      else
        {
          return false;
        }
      qualified_identifier_with_optional_star_ast *__node_142 = 0;
      if (!parse_qualified_identifier_with_optional_star(&__node_142))
        {
          return yy_expected_symbol(java_ast_node::Kind_qualified_identifier_with_optional_star, "qualified_identifier_with_optional_star");
        }
      (*yynode)->identifier_name = __node_142;
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

bool java::parse_interface_body(interface_body_ast **yynode)
{
  *yynode = create<interface_body_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE)
    {
      if (yytoken != Token_LBRACE)
        return yy_expected_token(yytoken, Token_LBRACE, "{");
      yylex();
      while (yytoken == Token_ABSTRACT
             || yytoken == Token_BOOLEAN
             || yytoken == Token_BYTE
             || yytoken == Token_CHAR
             || yytoken == Token_CLASS
             || yytoken == Token_DOUBLE
             || yytoken == Token_ENUM
             || yytoken == Token_FINAL
             || yytoken == Token_FLOAT
             || yytoken == Token_INT
             || yytoken == Token_INTERFACE
             || yytoken == Token_LONG
             || yytoken == Token_NATIVE
             || yytoken == Token_PRIVATE
             || yytoken == Token_PROTECTED
             || yytoken == Token_PUBLIC
             || yytoken == Token_SHORT
             || yytoken == Token_STATIC
             || yytoken == Token_STRICTFP
             || yytoken == Token_SYNCHRONIZED
             || yytoken == Token_TRANSIENT
             || yytoken == Token_VOID
             || yytoken == Token_VOLATILE
             || yytoken == Token_SEMICOLON
             || yytoken == Token_AT
             || yytoken == Token_LESS_THAN
             || yytoken == Token_IDENTIFIER)
        {
          interface_field_ast *__node_143 = 0;
          if (!parse_interface_field(&__node_143))
            {
              return yy_expected_symbol(java_ast_node::Kind_interface_field, "interface_field");
            }
          (*yynode)->declaration_sequence = snoc((*yynode)->declaration_sequence, __node_143, memory_pool);
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

bool java::parse_interface_declaration(interface_declaration_ast **yynode)
{
  *yynode = create<interface_declaration_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_INTERFACE)
    {
      if (yytoken != Token_INTERFACE)
        return yy_expected_token(yytoken, Token_INTERFACE, "interface");
      yylex();
      identifier_ast *__node_144 = 0;
      if (!parse_identifier(&__node_144))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->interface_name = __node_144;
      if (yytoken == Token_LESS_THAN)
        {
          type_parameters_ast *__node_145 = 0;
          if (!parse_type_parameters(&__node_145))
            {
              return yy_expected_symbol(java_ast_node::Kind_type_parameters, "type_parameters");
            }
          (*yynode)->type_parameters = __node_145;
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      if (yytoken == Token_EXTENDS)
        {
          interface_extends_clause_ast *__node_146 = 0;
          if (!parse_interface_extends_clause(&__node_146))
            {
              return yy_expected_symbol(java_ast_node::Kind_interface_extends_clause, "interface_extends_clause");
            }
          (*yynode)->extends = __node_146;
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      interface_body_ast *__node_147 = 0;
      if (!parse_interface_body(&__node_147))
        {
          return yy_expected_symbol(java_ast_node::Kind_interface_body, "interface_body");
        }
      (*yynode)->body = __node_147;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_interface_extends_clause(interface_extends_clause_ast **yynode)
{
  *yynode = create<interface_extends_clause_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_EXTENDS)
    {
      if (yytoken != Token_EXTENDS)
        return yy_expected_token(yytoken, Token_EXTENDS, "extends");
      yylex();
      class_or_interface_type_ast *__node_148 = 0;
      if (!parse_class_or_interface_type(&__node_148))
        {
          return yy_expected_symbol(java_ast_node::Kind_class_or_interface_type, "class_or_interface_type");
        }
      (*yynode)->type_sequence = snoc((*yynode)->type_sequence, __node_148, memory_pool);
      while (yytoken == Token_COMMA)
        {
          if (yytoken != Token_COMMA)
            return yy_expected_token(yytoken, Token_COMMA, ",");
          yylex();
          class_or_interface_type_ast *__node_149 = 0;
          if (!parse_class_or_interface_type(&__node_149))
            {
              return yy_expected_symbol(java_ast_node::Kind_class_or_interface_type, "class_or_interface_type");
            }
          (*yynode)->type_sequence = snoc((*yynode)->type_sequence, __node_149, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_interface_field(interface_field_ast **yynode)
{
  *yynode = create<interface_field_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ABSTRACT
      || yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_CLASS
      || yytoken == Token_DOUBLE
      || yytoken == Token_ENUM
      || yytoken == Token_FINAL
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_INTERFACE
      || yytoken == Token_LONG
      || yytoken == Token_NATIVE
      || yytoken == Token_PRIVATE
      || yytoken == Token_PROTECTED
      || yytoken == Token_PUBLIC
      || yytoken == Token_SHORT
      || yytoken == Token_STATIC
      || yytoken == Token_STRICTFP
      || yytoken == Token_SYNCHRONIZED
      || yytoken == Token_TRANSIENT
      || yytoken == Token_VOID
      || yytoken == Token_VOLATILE
      || yytoken == Token_SEMICOLON
      || yytoken == Token_AT
      || yytoken == Token_LESS_THAN
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_ABSTRACT
          || yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_CLASS
          || yytoken == Token_DOUBLE
          || yytoken == Token_ENUM
          || yytoken == Token_FINAL
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_INTERFACE
          || yytoken == Token_LONG
          || yytoken == Token_NATIVE
          || yytoken == Token_PRIVATE
          || yytoken == Token_PROTECTED
          || yytoken == Token_PUBLIC
          || yytoken == Token_SHORT
          || yytoken == Token_STATIC
          || yytoken == Token_STRICTFP
          || yytoken == Token_SYNCHRONIZED
          || yytoken == Token_TRANSIENT
          || yytoken == Token_VOID
          || yytoken == Token_VOLATILE
          || yytoken == Token_AT
          || yytoken == Token_LESS_THAN
          || yytoken == Token_IDENTIFIER)
        {
          optional_modifiers_ast *__node_150 = 0;
          if (!parse_optional_modifiers(&__node_150))
            {
              return yy_expected_symbol(java_ast_node::Kind_optional_modifiers, "optional_modifiers");
            }
          (*yynode)->modifiers = __node_150;
          if (yytoken == Token_CLASS)
            {
              class_declaration_ast *__node_151 = 0;
              if (!parse_class_declaration(&__node_151))
                {
                  return yy_expected_symbol(java_ast_node::Kind_class_declaration, "class_declaration");
                }
              (*yynode)->class_declaration = __node_151;
            }
          else if (yytoken == Token_ENUM)
            {
              enum_declaration_ast *__node_152 = 0;
              if (!parse_enum_declaration(&__node_152))
                {
                  return yy_expected_symbol(java_ast_node::Kind_enum_declaration, "enum_declaration");
                }
              (*yynode)->enum_declaration = __node_152;
            }
          else if (yytoken == Token_INTERFACE)
            {
              interface_declaration_ast *__node_153 = 0;
              if (!parse_interface_declaration(&__node_153))
                {
                  return yy_expected_symbol(java_ast_node::Kind_interface_declaration, "interface_declaration");
                }
              (*yynode)->interface_declaration = __node_153;
            }
          else if (yytoken == Token_AT)
            {
              annotation_type_declaration_ast *__node_154 = 0;
              if (!parse_annotation_type_declaration(&__node_154))
                {
                  return yy_expected_symbol(java_ast_node::Kind_annotation_type_declaration, "annotation_type_declaration");
                }
              (*yynode)->annotation_type_declaration = __node_154;
            }
          else if (yytoken == Token_BOOLEAN
                   || yytoken == Token_BYTE
                   || yytoken == Token_CHAR
                   || yytoken == Token_DOUBLE
                   || yytoken == Token_FLOAT
                   || yytoken == Token_INT
                   || yytoken == Token_LONG
                   || yytoken == Token_SHORT
                   || yytoken == Token_VOID
                   || yytoken == Token_LESS_THAN
                   || yytoken == Token_IDENTIFIER)
            {
              if (yytoken == Token_LESS_THAN)
                {
                  type_parameters_ast *__node_155 = 0;
                  if (!parse_type_parameters(&__node_155))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_type_parameters, "type_parameters");
                    }
                  (*yynode)->type_params = __node_155;
                }
              else if (true /*epsilon*/)
              {}
              else
                {
                  return false;
                }
              type_specification_ast *__node_156 = 0;
              if (!parse_type_specification(&__node_156))
                {
                  return yy_expected_symbol(java_ast_node::Kind_type_specification, "type_specification");
                }
              (*yynode)->type = __node_156;
              if (( LA(2).kind == Token_LPAREN ) && (yytoken == Token_IDENTIFIER))
                {
                  identifier_ast *__node_157 = 0;
                  if (!parse_identifier(&__node_157))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
                    }
                  (*yynode)->method_name = __node_157;
                  parameter_declaration_list_ast *__node_158 = 0;
                  if (!parse_parameter_declaration_list(&__node_158))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_parameter_declaration_list, "parameter_declaration_list");
                    }
                  (*yynode)->method_parameters = __node_158;
                  optional_declarator_brackets_ast *__node_159 = 0;
                  if (!parse_optional_declarator_brackets(&__node_159))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_optional_declarator_brackets, "optional_declarator_brackets");
                    }
                  (*yynode)->method_declarator_brackets = __node_159;
                  if (yytoken == Token_THROWS)
                    {
                      throws_clause_ast *__node_160 = 0;
                      if (!parse_throws_clause(&__node_160))
                        {
                          return yy_expected_symbol(java_ast_node::Kind_throws_clause, "throws_clause");
                        }
                      (*yynode)->method_throws_clause = __node_160;
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
              else if (yytoken == Token_IDENTIFIER)
                {
                  variable_declarator_ast *__node_161 = 0;
                  if (!parse_variable_declarator(&__node_161))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_variable_declarator, "variable_declarator");
                    }
                  (*yynode)->variable_declarator_sequence = snoc((*yynode)->variable_declarator_sequence, __node_161, memory_pool);
                  while (yytoken == Token_COMMA)
                    {
                      if (yytoken != Token_COMMA)
                        return yy_expected_token(yytoken, Token_COMMA, ",");
                      yylex();
                      variable_declarator_ast *__node_162 = 0;
                      if (!parse_variable_declarator(&__node_162))
                        {
                          return yy_expected_symbol(java_ast_node::Kind_variable_declarator, "variable_declarator");
                        }
                      (*yynode)->variable_declarator_sequence = snoc((*yynode)->variable_declarator_sequence, __node_162, memory_pool);
                    }
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

bool java::parse_literal(literal_ast **yynode)
{
  *yynode = create<literal_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL)
    {
      if (yytoken == Token_TRUE)
        {
          if (yytoken != Token_TRUE)
            return yy_expected_token(yytoken, Token_TRUE, "true");
          yylex();
          (*yynode)->literal_type = literal_ast::type_true;
        }
      else if (yytoken == Token_FALSE)
        {
          if (yytoken != Token_FALSE)
            return yy_expected_token(yytoken, Token_FALSE, "false");
          yylex();
          (*yynode)->literal_type = literal_ast::type_false;
        }
      else if (yytoken == Token_NULL)
        {
          if (yytoken != Token_NULL)
            return yy_expected_token(yytoken, Token_NULL, "null");
          yylex();
          (*yynode)->literal_type = literal_ast::type_null;
        }
      else if (yytoken == Token_INTEGER_LITERAL)
        {
          if (yytoken != Token_INTEGER_LITERAL)
            return yy_expected_token(yytoken, Token_INTEGER_LITERAL, "integer literal");
          (*yynode)->integer_literal = token_stream->index() - 1;
          yylex();
          (*yynode)->literal_type = literal_ast::type_integer;
        }
      else if (yytoken == Token_FLOATING_POINT_LITERAL)
        {
          if (yytoken != Token_FLOATING_POINT_LITERAL)
            return yy_expected_token(yytoken, Token_FLOATING_POINT_LITERAL, "floating point literal");
          (*yynode)->floating_point_literal = token_stream->index() - 1;
          yylex();
          (*yynode)->literal_type = literal_ast::type_floating_point;
        }
      else if (yytoken == Token_CHARACTER_LITERAL)
        {
          if (yytoken != Token_CHARACTER_LITERAL)
            return yy_expected_token(yytoken, Token_CHARACTER_LITERAL, "character literal");
          (*yynode)->character_literal = token_stream->index() - 1;
          yylex();
          (*yynode)->literal_type = literal_ast::type_character;
        }
      else if (yytoken == Token_STRING_LITERAL)
        {
          if (yytoken != Token_STRING_LITERAL)
            return yy_expected_token(yytoken, Token_STRING_LITERAL, "string literal");
          (*yynode)->string_literal = token_stream->index() - 1;
          yylex();
          (*yynode)->literal_type = literal_ast::type_string;
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

bool java::parse_logical_and_expression(logical_and_expression_ast **yynode)
{
  *yynode = create<logical_and_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      bit_or_expression_ast *__node_163 = 0;
      if (!parse_bit_or_expression(&__node_163))
        {
          return yy_expected_symbol(java_ast_node::Kind_bit_or_expression, "bit_or_expression");
        }
      (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_163, memory_pool);
      while (yytoken == Token_LOG_AND)
        {
          if (yytoken != Token_LOG_AND)
            return yy_expected_token(yytoken, Token_LOG_AND, "&&");
          yylex();
          bit_or_expression_ast *__node_164 = 0;
          if (!parse_bit_or_expression(&__node_164))
            {
              return yy_expected_symbol(java_ast_node::Kind_bit_or_expression, "bit_or_expression");
            }
          (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_164, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_logical_or_expression(logical_or_expression_ast **yynode)
{
  *yynode = create<logical_or_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      logical_and_expression_ast *__node_165 = 0;
      if (!parse_logical_and_expression(&__node_165))
        {
          return yy_expected_symbol(java_ast_node::Kind_logical_and_expression, "logical_and_expression");
        }
      (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_165, memory_pool);
      while (yytoken == Token_LOG_OR)
        {
          if (yytoken != Token_LOG_OR)
            return yy_expected_token(yytoken, Token_LOG_OR, "||");
          yylex();
          logical_and_expression_ast *__node_166 = 0;
          if (!parse_logical_and_expression(&__node_166))
            {
              return yy_expected_symbol(java_ast_node::Kind_logical_and_expression, "logical_and_expression");
            }
          (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_166, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_mandatory_declarator_brackets(mandatory_declarator_brackets_ast **yynode)
{
  *yynode = create<mandatory_declarator_brackets_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACKET)
    {
      do
        {
          if (yytoken != Token_LBRACKET)
            return yy_expected_token(yytoken, Token_LBRACKET, "[");
          yylex();
          if (yytoken != Token_RBRACKET)
            return yy_expected_token(yytoken, Token_RBRACKET, "]");
          yylex();
          (*yynode)->bracket_count++;
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

bool java::parse_multiplicative_expression(multiplicative_expression_ast **yynode)
{
  *yynode = create<multiplicative_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      unary_expression_ast *__node_167 = 0;
      if (!parse_unary_expression(&__node_167))
        {
          return yy_expected_symbol(java_ast_node::Kind_unary_expression, "unary_expression");
        }
      (*yynode)->expression = __node_167;
      while (yytoken == Token_STAR
             || yytoken == Token_SLASH
             || yytoken == Token_REMAINDER)
        {
          multiplicative_expression_rest_ast *__node_168 = 0;
          if (!parse_multiplicative_expression_rest(&__node_168))
            {
              return yy_expected_symbol(java_ast_node::Kind_multiplicative_expression_rest, "multiplicative_expression_rest");
            }
          (*yynode)->additional_expression_sequence = snoc((*yynode)->additional_expression_sequence, __node_168, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_multiplicative_expression_rest(multiplicative_expression_rest_ast **yynode)
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
          (*yynode)->multiplicative_operator = multiplicative_expression_rest_ast::op_star;
        }
      else if (yytoken == Token_SLASH)
        {
          if (yytoken != Token_SLASH)
            return yy_expected_token(yytoken, Token_SLASH, "/");
          yylex();
          (*yynode)->multiplicative_operator = multiplicative_expression_rest_ast::op_slash;
        }
      else if (yytoken == Token_REMAINDER)
        {
          if (yytoken != Token_REMAINDER)
            return yy_expected_token(yytoken, Token_REMAINDER, "%");
          yylex();
          (*yynode)->multiplicative_operator = multiplicative_expression_rest_ast::op_remainder;
        }
      else
        {
          return false;
        }
      unary_expression_ast *__node_169 = 0;
      if (!parse_unary_expression(&__node_169))
        {
          return yy_expected_symbol(java_ast_node::Kind_unary_expression, "unary_expression");
        }
      (*yynode)->expression = __node_169;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_new_expression(new_expression_ast **yynode)
{
  *yynode = create<new_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_NEW)
    {
      if (yytoken != Token_NEW)
        return yy_expected_token(yytoken, Token_NEW, "new");
      yylex();
      if (( compatibility_mode() >= java15_compatibility ) && (yytoken == Token_LESS_THAN))
        {
          non_wildcard_type_arguments_ast *__node_170 = 0;
          if (!parse_non_wildcard_type_arguments(&__node_170))
            {
              return yy_expected_symbol(java_ast_node::Kind_non_wildcard_type_arguments, "non_wildcard_type_arguments");
            }
          (*yynode)->type_arguments = __node_170;
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      type_specification_noarray_ast *__node_171 = 0;
      if (!parse_type_specification_noarray(&__node_171))
        {
          return yy_expected_symbol(java_ast_node::Kind_type_specification_noarray, "type_specification_noarray");
        }
      (*yynode)->type = __node_171;
      if (yytoken == Token_LPAREN)
        {
          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "(");
          yylex();
          argument_list_ast *__node_172 = 0;
          if (!parse_argument_list(&__node_172))
            {
              return yy_expected_symbol(java_ast_node::Kind_argument_list, "argument_list");
            }
          (*yynode)->class_constructor_arguments = __node_172;
          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, ")");
          yylex();
          if (yytoken == Token_LBRACE)
            {
              class_body_ast *__node_173 = 0;
              if (!parse_class_body(&__node_173))
                {
                  return yy_expected_symbol(java_ast_node::Kind_class_body, "class_body");
                }
              (*yynode)->class_body = __node_173;
            }
          else if (true /*epsilon*/)
          {}
          else
            {
              return false;
            }
        }
      else if (yytoken == Token_LBRACKET)
        {
          array_creator_rest_ast *__node_174 = 0;
          if (!parse_array_creator_rest(&__node_174))
            {
              return yy_expected_symbol(java_ast_node::Kind_array_creator_rest, "array_creator_rest");
            }
          (*yynode)->array_creator_rest = __node_174;
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

bool java::parse_non_wildcard_type_arguments(non_wildcard_type_arguments_ast **yynode)
{
  *yynode = create<non_wildcard_type_arguments_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LESS_THAN)
    {
      if (yytoken != Token_LESS_THAN)
        return yy_expected_token(yytoken, Token_LESS_THAN, "<");
      yylex();
      int currentLtLevel = ltCounter;
      ltCounter++;
      type_argument_specification_ast *__node_175 = 0;
      if (!parse_type_argument_specification(&__node_175))
        {
          return yy_expected_symbol(java_ast_node::Kind_type_argument_specification, "type_argument_specification");
        }
      (*yynode)->type_argument_specification_sequence = snoc((*yynode)->type_argument_specification_sequence, __node_175, memory_pool);
      while (yytoken == Token_COMMA)
        {
          if ( ltCounter != currentLtLevel + 1 )
            {
              break;
            }
          if (yytoken != Token_COMMA)
            return yy_expected_token(yytoken, Token_COMMA, ",");
          yylex();
          type_argument_specification_ast *__node_176 = 0;
          if (!parse_type_argument_specification(&__node_176))
            {
              return yy_expected_symbol(java_ast_node::Kind_type_argument_specification, "type_argument_specification");
            }
          (*yynode)->type_argument_specification_sequence = snoc((*yynode)->type_argument_specification_sequence, __node_176, memory_pool);
        }
      if (yytoken == Token_GREATER_THAN
          || yytoken == Token_SIGNED_RSHIFT
          || yytoken == Token_UNSIGNED_RSHIFT)
        {
          type_arguments_or_parameters_end_ast *__node_177 = 0;
          if (!parse_type_arguments_or_parameters_end(&__node_177))
            {
              return yy_expected_symbol(java_ast_node::Kind_type_arguments_or_parameters_end, "type_arguments_or_parameters_end");
            }
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      if ( currentLtLevel == 0 && ltCounter != currentLtLevel )
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

bool java::parse_optional_declarator_brackets(optional_declarator_brackets_ast **yynode)
{
  *yynode = create<optional_declarator_brackets_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACKET || yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_EXTENDS
      || yytoken == Token_FLOAT
      || yytoken == Token_IMPLEMENTS
      || yytoken == Token_INSTANCEOF
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_THROWS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_RPAREN
      || yytoken == Token_LBRACE
      || yytoken == Token_RBRACE
      || yytoken == Token_LBRACKET
      || yytoken == Token_RBRACKET
      || yytoken == Token_SEMICOLON
      || yytoken == Token_COMMA
      || yytoken == Token_DOT
      || yytoken == Token_ASSIGN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_GREATER_THAN
      || yytoken == Token_QUESTION
      || yytoken == Token_COLON
      || yytoken == Token_EQUAL
      || yytoken == Token_LESS_EQUAL
      || yytoken == Token_GREATER_EQUAL
      || yytoken == Token_NOT_EQUAL
      || yytoken == Token_LOG_AND
      || yytoken == Token_LOG_OR
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_STAR
      || yytoken == Token_SLASH
      || yytoken == Token_BIT_AND
      || yytoken == Token_BIT_OR
      || yytoken == Token_BIT_XOR
      || yytoken == Token_REMAINDER
      || yytoken == Token_LSHIFT
      || yytoken == Token_SIGNED_RSHIFT
      || yytoken == Token_UNSIGNED_RSHIFT
      || yytoken == Token_PLUS_ASSIGN
      || yytoken == Token_MINUS_ASSIGN
      || yytoken == Token_STAR_ASSIGN
      || yytoken == Token_SLASH_ASSIGN
      || yytoken == Token_BIT_AND_ASSIGN
      || yytoken == Token_BIT_OR_ASSIGN
      || yytoken == Token_BIT_XOR_ASSIGN
      || yytoken == Token_REMAINDER_ASSIGN
      || yytoken == Token_LSHIFT_ASSIGN
      || yytoken == Token_SIGNED_RSHIFT_ASSIGN
      || yytoken == Token_UNSIGNED_RSHIFT_ASSIGN
      || yytoken == Token_ELLIPSIS
      || yytoken == Token_IDENTIFIER)
    {
      while (yytoken == Token_LBRACKET)
        {
          if (yytoken != Token_LBRACKET)
            return yy_expected_token(yytoken, Token_LBRACKET, "[");
          yylex();
          if (yytoken != Token_RBRACKET)
            return yy_expected_token(yytoken, Token_RBRACKET, "]");
          yylex();
          (*yynode)->bracket_count++;
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_optional_modifiers(optional_modifiers_ast **yynode)
{
  *yynode = create<optional_modifiers_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ABSTRACT
      || yytoken == Token_FINAL
      || yytoken == Token_NATIVE
      || yytoken == Token_PRIVATE
      || yytoken == Token_PROTECTED
      || yytoken == Token_PUBLIC
      || yytoken == Token_STATIC
      || yytoken == Token_STRICTFP
      || yytoken == Token_SYNCHRONIZED
      || yytoken == Token_TRANSIENT
      || yytoken == Token_VOLATILE
      || yytoken == Token_AT || yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_CLASS
      || yytoken == Token_DOUBLE
      || yytoken == Token_ENUM
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_INTERFACE
      || yytoken == Token_LONG
      || yytoken == Token_SHORT
      || yytoken == Token_VOID
      || yytoken == Token_AT
      || yytoken == Token_LESS_THAN
      || yytoken == Token_IDENTIFIER)
    {
      while (yytoken == Token_ABSTRACT
             || yytoken == Token_FINAL
             || yytoken == Token_NATIVE
             || yytoken == Token_PRIVATE
             || yytoken == Token_PROTECTED
             || yytoken == Token_PUBLIC
             || yytoken == Token_STATIC
             || yytoken == Token_STRICTFP
             || yytoken == Token_SYNCHRONIZED
             || yytoken == Token_TRANSIENT
             || yytoken == Token_VOLATILE
             || yytoken == Token_AT)
        {
          if (yytoken == Token_PRIVATE)
            {
              if (yytoken != Token_PRIVATE)
                return yy_expected_token(yytoken, Token_PRIVATE, "private");
              yylex();
              (*yynode)->modifiers |= optional_modifiers_ast::mod_private;
            }
          else if (yytoken == Token_PUBLIC)
            {
              if (yytoken != Token_PUBLIC)
                return yy_expected_token(yytoken, Token_PUBLIC, "public");
              yylex();
              (*yynode)->modifiers |= optional_modifiers_ast::mod_public;
            }
          else if (yytoken == Token_PROTECTED)
            {
              if (yytoken != Token_PROTECTED)
                return yy_expected_token(yytoken, Token_PROTECTED, "protected");
              yylex();
              (*yynode)->modifiers |= optional_modifiers_ast::mod_protected;
            }
          else if (yytoken == Token_STATIC)
            {
              if (yytoken != Token_STATIC)
                return yy_expected_token(yytoken, Token_STATIC, "static");
              yylex();
              (*yynode)->modifiers |= optional_modifiers_ast::mod_static;
            }
          else if (yytoken == Token_TRANSIENT)
            {
              if (yytoken != Token_TRANSIENT)
                return yy_expected_token(yytoken, Token_TRANSIENT, "transient");
              yylex();
              (*yynode)->modifiers |= optional_modifiers_ast::mod_transient;
            }
          else if (yytoken == Token_FINAL)
            {
              if (yytoken != Token_FINAL)
                return yy_expected_token(yytoken, Token_FINAL, "final");
              yylex();
              (*yynode)->modifiers |= optional_modifiers_ast::mod_final;
            }
          else if (yytoken == Token_ABSTRACT)
            {
              if (yytoken != Token_ABSTRACT)
                return yy_expected_token(yytoken, Token_ABSTRACT, "abstract");
              yylex();
              (*yynode)->modifiers |= optional_modifiers_ast::mod_abstract;
            }
          else if (yytoken == Token_NATIVE)
            {
              if (yytoken != Token_NATIVE)
                return yy_expected_token(yytoken, Token_NATIVE, "native");
              yylex();
              (*yynode)->modifiers |= optional_modifiers_ast::mod_native;
            }
          else if (yytoken == Token_SYNCHRONIZED)
            {
              if (yytoken != Token_SYNCHRONIZED)
                return yy_expected_token(yytoken, Token_SYNCHRONIZED, "synchronized");
              yylex();
              (*yynode)->modifiers |= optional_modifiers_ast::mod_synchronized;
            }
          else if (yytoken == Token_VOLATILE)
            {
              if (yytoken != Token_VOLATILE)
                return yy_expected_token(yytoken, Token_VOLATILE, "volatile");
              yylex();
              (*yynode)->modifiers |= optional_modifiers_ast::mod_volatile;
            }
          else if (yytoken == Token_STRICTFP)
            {
              if (yytoken != Token_STRICTFP)
                return yy_expected_token(yytoken, Token_STRICTFP, "strictfp");
              yylex();
              (*yynode)->modifiers |= optional_modifiers_ast::mod_strictfp;
            }
          else if (yytoken == Token_AT)
            {
              if (yytoken == Token_AT && LA(2).kind == Token_INTERFACE)
                {
                  break;
                }
              annotation_ast *__node_178 = 0;
              if (!parse_annotation(&__node_178))
                {
                  return yy_expected_symbol(java_ast_node::Kind_annotation, "annotation");
                }
              (*yynode)->mod_annotation_sequence = snoc((*yynode)->mod_annotation_sequence, __node_178, memory_pool);
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

bool java::parse_optional_parameter_modifiers(optional_parameter_modifiers_ast **yynode)
{
  *yynode = create<optional_parameter_modifiers_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_FINAL
      || yytoken == Token_AT || yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_SHORT
      || yytoken == Token_VOID
      || yytoken == Token_IDENTIFIER)
    {
      (*yynode)->mod_final = false;
      while (yytoken == Token_FINAL
             || yytoken == Token_AT)
        {
          if (yytoken == Token_FINAL)
            {
              if (yytoken != Token_FINAL)
                return yy_expected_token(yytoken, Token_FINAL, "final");
              yylex();
              (*yynode)->mod_final = true;
            }
          else if (yytoken == Token_AT)
            {
              annotation_ast *__node_179 = 0;
              if (!parse_annotation(&__node_179))
                {
                  return yy_expected_symbol(java_ast_node::Kind_annotation, "annotation");
                }
              (*yynode)->mod_annotation_sequence = snoc((*yynode)->mod_annotation_sequence, __node_179, memory_pool);
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

bool java::parse_package_declaration(package_declaration_ast **yynode)
{
  *yynode = create<package_declaration_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_PACKAGE
      || yytoken == Token_AT)
    {
      while (yytoken == Token_AT)
        {
          annotation_ast *__node_180 = 0;
          if (!parse_annotation(&__node_180))
            {
              return yy_expected_symbol(java_ast_node::Kind_annotation, "annotation");
            }
          (*yynode)->annotation_sequence = snoc((*yynode)->annotation_sequence, __node_180, memory_pool);
        }
      if (yytoken != Token_PACKAGE)
        return yy_expected_token(yytoken, Token_PACKAGE, "package");
      yylex();
      qualified_identifier_ast *__node_181 = 0;
      if (!parse_qualified_identifier(&__node_181))
        {
          return yy_expected_symbol(java_ast_node::Kind_qualified_identifier, "qualified_identifier");
        }
      (*yynode)->package_name = __node_181;
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

bool java::parse_parameter_declaration(parameter_declaration_ast **yynode)
{
  *yynode = create<parameter_declaration_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FINAL
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_SHORT
      || yytoken == Token_VOID
      || yytoken == Token_AT
      || yytoken == Token_IDENTIFIER)
    {
      optional_parameter_modifiers_ast *__node_182 = 0;
      if (!parse_optional_parameter_modifiers(&__node_182))
        {
          return yy_expected_symbol(java_ast_node::Kind_optional_parameter_modifiers, "optional_parameter_modifiers");
        }
      (*yynode)->parameter_modifiers = __node_182;
      type_specification_ast *__node_183 = 0;
      if (!parse_type_specification(&__node_183))
        {
          return yy_expected_symbol(java_ast_node::Kind_type_specification, "type_specification");
        }
      (*yynode)->type_specification = __node_183;
      identifier_ast *__node_184 = 0;
      if (!parse_identifier(&__node_184))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->variable_identifier = __node_184;
      optional_declarator_brackets_ast *__node_185 = 0;
      if (!parse_optional_declarator_brackets(&__node_185))
        {
          return yy_expected_symbol(java_ast_node::Kind_optional_declarator_brackets, "optional_declarator_brackets");
        }
      (*yynode)->declarator_brackets = __node_185;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_parameter_declaration_ellipsis(parameter_declaration_ellipsis_ast **yynode)
{
  *yynode = create<parameter_declaration_ellipsis_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FINAL
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_SHORT
      || yytoken == Token_VOID
      || yytoken == Token_AT
      || yytoken == Token_IDENTIFIER)
    {
      optional_parameter_modifiers_ast *__node_186 = 0;
      if (!parse_optional_parameter_modifiers(&__node_186))
        {
          return yy_expected_symbol(java_ast_node::Kind_optional_parameter_modifiers, "optional_parameter_modifiers");
        }
      (*yynode)->parameter_modifiers = __node_186;
      type_specification_ast *__node_187 = 0;
      if (!parse_type_specification(&__node_187))
        {
          return yy_expected_symbol(java_ast_node::Kind_type_specification, "type_specification");
        }
      (*yynode)->type_specification = __node_187;
      if (yytoken == Token_ELLIPSIS)
        {
          if (yytoken != Token_ELLIPSIS)
            return yy_expected_token(yytoken, Token_ELLIPSIS, "...");
          yylex();
          (*yynode)->has_ellipsis = true;
          ellipsisOccurred = true;
        }
      else if (true /*epsilon*/)
        {
          (*yynode)->has_ellipsis = false;
        }
      else
        {
          return false;
        }
      identifier_ast *__node_188 = 0;
      if (!parse_identifier(&__node_188))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->variable_identifier = __node_188;
      optional_declarator_brackets_ast *__node_189 = 0;
      if (!parse_optional_declarator_brackets(&__node_189))
        {
          return yy_expected_symbol(java_ast_node::Kind_optional_declarator_brackets, "optional_declarator_brackets");
        }
      (*yynode)->declarator_brackets = __node_189;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_parameter_declaration_list(parameter_declaration_list_ast **yynode)
{
  *yynode = create<parameter_declaration_list_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LPAREN)
    {
      if (yytoken != Token_LPAREN)
        return yy_expected_token(yytoken, Token_LPAREN, "(");
      yylex();
      ellipsisOccurred = false;
      if (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FINAL
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_SHORT
          || yytoken == Token_VOID
          || yytoken == Token_AT
          || yytoken == Token_IDENTIFIER)
        {
          parameter_declaration_ellipsis_ast *__node_190 = 0;
          if (!parse_parameter_declaration_ellipsis(&__node_190))
            {
              return yy_expected_symbol(java_ast_node::Kind_parameter_declaration_ellipsis, "parameter_declaration_ellipsis");
            }
          (*yynode)->parameter_declaration_sequence = snoc((*yynode)->parameter_declaration_sequence, __node_190, memory_pool);
          while (yytoken == Token_COMMA)
            {
              if ( ellipsisOccurred == true )
                {
                  break;
                }
              if (yytoken != Token_COMMA)
                return yy_expected_token(yytoken, Token_COMMA, ",");
              yylex();
              parameter_declaration_ellipsis_ast *__node_191 = 0;
              if (!parse_parameter_declaration_ellipsis(&__node_191))
                {
                  return yy_expected_symbol(java_ast_node::Kind_parameter_declaration_ellipsis, "parameter_declaration_ellipsis");
                }
              (*yynode)->parameter_declaration_sequence = snoc((*yynode)->parameter_declaration_sequence, __node_191, memory_pool);
            }
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
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_postfix_operator(postfix_operator_ast **yynode)
{
  *yynode = create<postfix_operator_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT)
    {
      if (yytoken == Token_INCREMENT)
        {
          if (yytoken != Token_INCREMENT)
            return yy_expected_token(yytoken, Token_INCREMENT, "++");
          yylex();
          (*yynode)->postfix_operator = postfix_operator_ast::op_increment;
        }
      else if (yytoken == Token_DECREMENT)
        {
          if (yytoken != Token_DECREMENT)
            return yy_expected_token(yytoken, Token_DECREMENT, "--");
          yylex();
          (*yynode)->postfix_operator = postfix_operator_ast::op_decrement;
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

bool java::parse_primary_atom(primary_atom_ast **yynode)
{
  *yynode = create<primary_atom_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_SHORT
          || yytoken == Token_VOID)
        {
          builtin_type_specification_ast *__node_192 = 0;
          if (!parse_builtin_type_specification(&__node_192))
            {
              return yy_expected_symbol(java_ast_node::Kind_builtin_type_specification, "builtin_type_specification");
            }
          (*yynode)->builtin_type = __node_192;
          if (yytoken != Token_DOT)
            return yy_expected_token(yytoken, Token_DOT, ".");
          yylex();
          if (yytoken != Token_CLASS)
            return yy_expected_token(yytoken, Token_CLASS, "class");
          yylex();
          (*yynode)->primary_atom_kind = primary_atom_ast::kind_builtin_type_dot_class;
        }
      else if (yytoken == Token_TRUE
               || yytoken == Token_FALSE
               || yytoken == Token_NULL
               || yytoken == Token_INTEGER_LITERAL
               || yytoken == Token_FLOATING_POINT_LITERAL
               || yytoken == Token_CHARACTER_LITERAL
               || yytoken == Token_STRING_LITERAL)
        {
          literal_ast *__node_193 = 0;
          if (!parse_literal(&__node_193))
            {
              return yy_expected_symbol(java_ast_node::Kind_literal, "literal");
            }
          (*yynode)->literal = __node_193;
          (*yynode)->primary_atom_kind = primary_atom_ast::kind_literal;
        }
      else if (yytoken == Token_NEW)
        {
          new_expression_ast *__node_194 = 0;
          if (!parse_new_expression(&__node_194))
            {
              return yy_expected_symbol(java_ast_node::Kind_new_expression, "new_expression");
            }
          (*yynode)->new_expression = __node_194;
          (*yynode)->primary_atom_kind = primary_atom_ast::kind_new_expression;
        }
      else if (yytoken == Token_LPAREN)
        {
          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "(");
          yylex();
          expression_ast *__node_195 = 0;
          if (!parse_expression(&__node_195))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->parenthesis_expression = __node_195;
          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, ")");
          yylex();
          (*yynode)->primary_atom_kind = primary_atom_ast::kind_parenthesis_expression;
        }
      else if (yytoken == Token_THIS)
        {
          if (yytoken != Token_THIS)
            return yy_expected_token(yytoken, Token_THIS, "this");
          yylex();
          if (yytoken == Token_LPAREN)
            {
              if (yytoken != Token_LPAREN)
                return yy_expected_token(yytoken, Token_LPAREN, "(");
              yylex();
              argument_list_ast *__node_196 = 0;
              if (!parse_argument_list(&__node_196))
                {
                  return yy_expected_symbol(java_ast_node::Kind_argument_list, "argument_list");
                }
              (*yynode)->this_constructor_arguments = __node_196;
              if (yytoken != Token_RPAREN)
                return yy_expected_token(yytoken, Token_RPAREN, ")");
              yylex();
            }
          else if (true /*epsilon*/)
          {}
          else
            {
              return false;
            }
          (*yynode)->primary_atom_kind = primary_atom_ast::kind_this_call_no_type_arguments;
        }
      else if (yytoken == Token_SUPER)
        {
          if (yytoken != Token_SUPER)
            return yy_expected_token(yytoken, Token_SUPER, "super");
          yylex();
          super_suffix_ast *__node_197 = 0;
          if (!parse_super_suffix(&__node_197))
            {
              return yy_expected_symbol(java_ast_node::Kind_super_suffix, "super_suffix");
            }
          (*yynode)->super_suffix = __node_197;
          (*yynode)->primary_atom_kind = primary_atom_ast::kind_super_call_no_type_arguments;
        }
      else if (( compatibility_mode() >= java15_compatibility ) && (yytoken == Token_LESS_THAN))
        {
          non_wildcard_type_arguments_ast *__node_198 = 0;
          if (!parse_non_wildcard_type_arguments(&__node_198))
            {
              return yy_expected_symbol(java_ast_node::Kind_non_wildcard_type_arguments, "non_wildcard_type_arguments");
            }
          (*yynode)->type_arguments = __node_198;
          if (yytoken == Token_SUPER)
            {
              if (yytoken != Token_SUPER)
                return yy_expected_token(yytoken, Token_SUPER, "super");
              yylex();
              super_suffix_ast *__node_199 = 0;
              if (!parse_super_suffix(&__node_199))
                {
                  return yy_expected_symbol(java_ast_node::Kind_super_suffix, "super_suffix");
                }
              (*yynode)->super_suffix = __node_199;
              (*yynode)->primary_atom_kind = primary_atom_ast::kind_super_call_with_type_arguments;
            }
          else if (yytoken == Token_THIS)
            {
              if (yytoken != Token_THIS)
                return yy_expected_token(yytoken, Token_THIS, "this");
              yylex();
              if (yytoken != Token_LPAREN)
                return yy_expected_token(yytoken, Token_LPAREN, "(");
              yylex();
              argument_list_ast *__node_200 = 0;
              if (!parse_argument_list(&__node_200))
                {
                  return yy_expected_symbol(java_ast_node::Kind_argument_list, "argument_list");
                }
              (*yynode)->this_constructor_arguments = __node_200;
              if (yytoken != Token_RPAREN)
                return yy_expected_token(yytoken, Token_RPAREN, ")");
              yylex();
              (*yynode)->primary_atom_kind = primary_atom_ast::kind_this_call_with_type_arguments;
            }
          else if (yytoken == Token_IDENTIFIER)
            {
              identifier_ast *__node_201 = 0;
              if (!parse_identifier(&__node_201))
                {
                  return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
                }
              (*yynode)->method_name_typed = __node_201;
              if (yytoken != Token_LPAREN)
                return yy_expected_token(yytoken, Token_LPAREN, "(");
              yylex();
              argument_list_ast *__node_202 = 0;
              if (!parse_argument_list(&__node_202))
                {
                  return yy_expected_symbol(java_ast_node::Kind_argument_list, "argument_list");
                }
              (*yynode)->method_arguments = __node_202;
              if (yytoken != Token_RPAREN)
                return yy_expected_token(yytoken, Token_RPAREN, ")");
              yylex();
              (*yynode)->primary_atom_kind = primary_atom_ast::kind_method_call_with_type_arguments;
            }
          else
            {
              return false;
            }
        }
      else if (yytoken == Token_IDENTIFIER)
        {
          qualified_identifier_safe_ast *__node_203 = 0;
          if (!parse_qualified_identifier_safe(&__node_203))
            {
              return yy_expected_symbol(java_ast_node::Kind_qualified_identifier_safe, "qualified_identifier_safe");
            }
          (*yynode)->identifier = __node_203;
          if (yytoken == Token_LPAREN)
            {
              if (yytoken != Token_LPAREN)
                return yy_expected_token(yytoken, Token_LPAREN, "(");
              yylex();
              argument_list_ast *__node_204 = 0;
              if (!parse_argument_list(&__node_204))
                {
                  return yy_expected_symbol(java_ast_node::Kind_argument_list, "argument_list");
                }
              (*yynode)->method_arguments = __node_204;
              if (yytoken != Token_RPAREN)
                return yy_expected_token(yytoken, Token_RPAREN, ")");
              yylex();
              (*yynode)->primary_atom_kind = primary_atom_ast::kind_method_call_no_type_arguments;
            }
          else if (( LA(2).kind == Token_RBRACKET ) && (yytoken == Token_LBRACKET))
            {
              mandatory_declarator_brackets_ast *__node_205 = 0;
              if (!parse_mandatory_declarator_brackets(&__node_205))
                {
                  return yy_expected_symbol(java_ast_node::Kind_mandatory_declarator_brackets, "mandatory_declarator_brackets");
                }
              (*yynode)->declarator_brackets = __node_205;
              if (yytoken != Token_DOT)
                return yy_expected_token(yytoken, Token_DOT, ".");
              yylex();
              if (yytoken != Token_CLASS)
                return yy_expected_token(yytoken, Token_CLASS, "class");
              (*yynode)->array_dotclass = token_stream->index() - 1;
              yylex();
              (*yynode)->primary_atom_kind = primary_atom_ast::kind_array_type_dot_class;
            }
          else if (true /*epsilon*/)
            {
              (*yynode)->primary_atom_kind = primary_atom_ast::kind_type_name;
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

bool java::parse_primary_expression(primary_expression_ast **yynode)
{
  *yynode = create<primary_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      primary_atom_ast *__node_206 = 0;
      if (!parse_primary_atom(&__node_206))
        {
          return yy_expected_symbol(java_ast_node::Kind_primary_atom, "primary_atom");
        }
      (*yynode)->primary_atom = __node_206;
      while (yytoken == Token_LBRACKET
             || yytoken == Token_DOT)
        {
          primary_selector_ast *__node_207 = 0;
          if (!parse_primary_selector(&__node_207))
            {
              return yy_expected_symbol(java_ast_node::Kind_primary_selector, "primary_selector");
            }
          (*yynode)->selector_sequence = snoc((*yynode)->selector_sequence, __node_207, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_primary_selector(primary_selector_ast **yynode)
{
  *yynode = create<primary_selector_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACKET
      || yytoken == Token_DOT)
    {
      if (yytoken == Token_DOT)
        {
          if (yytoken != Token_DOT)
            return yy_expected_token(yytoken, Token_DOT, ".");
          yylex();
          if (yytoken == Token_CLASS)
            {
              if (yytoken != Token_CLASS)
                return yy_expected_token(yytoken, Token_CLASS, "class");
              (*yynode)->dotclass = token_stream->index() - 1;
              yylex();
            }
          else if (yytoken == Token_THIS)
            {
              if (yytoken != Token_THIS)
                return yy_expected_token(yytoken, Token_THIS, "this");
              (*yynode)->dotthis = token_stream->index() - 1;
              yylex();
            }
          else if (yytoken == Token_NEW)
            {
              new_expression_ast *__node_208 = 0;
              if (!parse_new_expression(&__node_208))
                {
                  return yy_expected_symbol(java_ast_node::Kind_new_expression, "new_expression");
                }
              (*yynode)->new_expression = __node_208;
            }
          else if (( LA(2).kind != Token_LPAREN ) && (yytoken == Token_IDENTIFIER))
            {
              identifier_ast *__node_209 = 0;
              if (!parse_identifier(&__node_209))
                {
                  return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
                }
              (*yynode)->variable_name = __node_209;
            }
          else if (yytoken == Token_SUPER
                   || yytoken == Token_LESS_THAN
                   || yytoken == Token_IDENTIFIER)
            {
              if (( compatibility_mode() >= java15_compatibility ) && (yytoken == Token_LESS_THAN))
                {
                  non_wildcard_type_arguments_ast *__node_210 = 0;
                  if (!parse_non_wildcard_type_arguments(&__node_210))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_non_wildcard_type_arguments, "non_wildcard_type_arguments");
                    }
                  (*yynode)->type_arguments = __node_210;
                }
              else if (true /*epsilon*/)
              {}
              else
                {
                  return false;
                }
              if (yytoken == Token_SUPER)
                {
                  if (yytoken != Token_SUPER)
                    return yy_expected_token(yytoken, Token_SUPER, "super");
                  yylex();
                  super_suffix_ast *__node_211 = 0;
                  if (!parse_super_suffix(&__node_211))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_super_suffix, "super_suffix");
                    }
                  (*yynode)->super_suffix = __node_211;
                }
              else if (yytoken == Token_IDENTIFIER)
                {
                  identifier_ast *__node_212 = 0;
                  if (!parse_identifier(&__node_212))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
                    }
                  (*yynode)->method_name = __node_212;
                  if (yytoken != Token_LPAREN)
                    return yy_expected_token(yytoken, Token_LPAREN, "(");
                  yylex();
                  argument_list_ast *__node_213 = 0;
                  if (!parse_argument_list(&__node_213))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_argument_list, "argument_list");
                    }
                  (*yynode)->method_arguments = __node_213;
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
        }
      else if (yytoken == Token_LBRACKET)
        {
          if (yytoken != Token_LBRACKET)
            return yy_expected_token(yytoken, Token_LBRACKET, "[");
          yylex();
          expression_ast *__node_214 = 0;
          if (!parse_expression(&__node_214))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->array_index_expression = __node_214;
          if (yytoken != Token_RBRACKET)
            return yy_expected_token(yytoken, Token_RBRACKET, "]");
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

bool java::parse_qualified_identifier(qualified_identifier_ast **yynode)
{
  *yynode = create<qualified_identifier_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      identifier_ast *__node_215 = 0;
      if (!parse_identifier(&__node_215))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->name_sequence = snoc((*yynode)->name_sequence, __node_215, memory_pool);
      while (yytoken == Token_DOT)
        {
          if (yytoken != Token_DOT)
            return yy_expected_token(yytoken, Token_DOT, ".");
          yylex();
          identifier_ast *__node_216 = 0;
          if (!parse_identifier(&__node_216))
            {
              return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
            }
          (*yynode)->name_sequence = snoc((*yynode)->name_sequence, __node_216, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_qualified_identifier_safe(qualified_identifier_safe_ast **yynode)
{
  *yynode = create<qualified_identifier_safe_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      identifier_ast *__node_217 = 0;
      if (!parse_identifier(&__node_217))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->name_sequence = snoc((*yynode)->name_sequence, __node_217, memory_pool);
      while (yytoken == Token_DOT)
        {
          if (LA(2).kind != Token_IDENTIFIER)
            {
              break;
            }
          if (yytoken != Token_DOT)
            return yy_expected_token(yytoken, Token_DOT, ".");
          yylex();
          identifier_ast *__node_218 = 0;
          if (!parse_identifier(&__node_218))
            {
              return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
            }
          (*yynode)->name_sequence = snoc((*yynode)->name_sequence, __node_218, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_qualified_identifier_with_optional_star(qualified_identifier_with_optional_star_ast **yynode)
{
  *yynode = create<qualified_identifier_with_optional_star_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      identifier_ast *__node_219 = 0;
      if (!parse_identifier(&__node_219))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->name_sequence = snoc((*yynode)->name_sequence, __node_219, memory_pool);
      (*yynode)->has_star = false;
      while (yytoken == Token_DOT)
        {
          if (yytoken != Token_DOT)
            return yy_expected_token(yytoken, Token_DOT, ".");
          yylex();
          if (yytoken == Token_IDENTIFIER)
            {
              identifier_ast *__node_220 = 0;
              if (!parse_identifier(&__node_220))
                {
                  return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
                }
              (*yynode)->name_sequence = snoc((*yynode)->name_sequence, __node_220, memory_pool);
            }
          else if (yytoken == Token_STAR)
            {
              if (yytoken != Token_STAR)
                return yy_expected_token(yytoken, Token_STAR, "*");
              yylex();
              (*yynode)->has_star = true;
              break;
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

bool java::parse_relational_expression(relational_expression_ast **yynode)
{
  *yynode = create<relational_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      shift_expression_ast *__node_221 = 0;
      if (!parse_shift_expression(&__node_221))
        {
          return yy_expected_symbol(java_ast_node::Kind_shift_expression, "shift_expression");
        }
      (*yynode)->expression = __node_221;
      if (yytoken == Token_LESS_THAN
          || yytoken == Token_GREATER_THAN
          || yytoken == Token_LESS_EQUAL
          || yytoken == Token_GREATER_EQUAL)
        {
          do
            {
              relational_expression_rest_ast *__node_222 = 0;
              if (!parse_relational_expression_rest(&__node_222))
                {
                  return yy_expected_symbol(java_ast_node::Kind_relational_expression_rest, "relational_expression_rest");
                }
              (*yynode)->additional_expression_sequence = snoc((*yynode)->additional_expression_sequence, __node_222, memory_pool);
            }
          while (yytoken == Token_LESS_THAN
                 || yytoken == Token_GREATER_THAN
                 || yytoken == Token_LESS_EQUAL
                 || yytoken == Token_GREATER_EQUAL);
        }
      else if (yytoken == Token_INSTANCEOF)
        {
          if (yytoken != Token_INSTANCEOF)
            return yy_expected_token(yytoken, Token_INSTANCEOF, "instanceof");
          yylex();
          type_specification_ast *__node_223 = 0;
          if (!parse_type_specification(&__node_223))
            {
              return yy_expected_symbol(java_ast_node::Kind_type_specification, "type_specification");
            }
          (*yynode)->instanceof_type = __node_223;
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

bool java::parse_relational_expression_rest(relational_expression_rest_ast **yynode)
{
  *yynode = create<relational_expression_rest_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LESS_THAN
      || yytoken == Token_GREATER_THAN
      || yytoken == Token_LESS_EQUAL
      || yytoken == Token_GREATER_EQUAL)
    {
      if (yytoken == Token_LESS_THAN)
        {
          if (yytoken != Token_LESS_THAN)
            return yy_expected_token(yytoken, Token_LESS_THAN, "<");
          yylex();
          (*yynode)->relational_operator = relational_expression_rest_ast::op_less_than;
        }
      else if (yytoken == Token_GREATER_THAN)
        {
          if (yytoken != Token_GREATER_THAN)
            return yy_expected_token(yytoken, Token_GREATER_THAN, ">");
          yylex();
          (*yynode)->relational_operator = relational_expression_rest_ast::op_greater_than;
        }
      else if (yytoken == Token_LESS_EQUAL)
        {
          if (yytoken != Token_LESS_EQUAL)
            return yy_expected_token(yytoken, Token_LESS_EQUAL, "<=");
          yylex();
          (*yynode)->relational_operator = relational_expression_rest_ast::op_less_equal;
        }
      else if (yytoken == Token_GREATER_EQUAL)
        {
          if (yytoken != Token_GREATER_EQUAL)
            return yy_expected_token(yytoken, Token_GREATER_EQUAL, ">=");
          yylex();
          (*yynode)->relational_operator = relational_expression_rest_ast::op_greater_equal;
        }
      else
        {
          return false;
        }
      shift_expression_ast *__node_224 = 0;
      if (!parse_shift_expression(&__node_224))
        {
          return yy_expected_symbol(java_ast_node::Kind_shift_expression, "shift_expression");
        }
      (*yynode)->expression = __node_224;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_shift_expression(shift_expression_ast **yynode)
{
  *yynode = create<shift_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      additive_expression_ast *__node_225 = 0;
      if (!parse_additive_expression(&__node_225))
        {
          return yy_expected_symbol(java_ast_node::Kind_additive_expression, "additive_expression");
        }
      (*yynode)->expression = __node_225;
      while (yytoken == Token_LSHIFT
             || yytoken == Token_SIGNED_RSHIFT
             || yytoken == Token_UNSIGNED_RSHIFT)
        {
          shift_expression_rest_ast *__node_226 = 0;
          if (!parse_shift_expression_rest(&__node_226))
            {
              return yy_expected_symbol(java_ast_node::Kind_shift_expression_rest, "shift_expression_rest");
            }
          (*yynode)->additional_expression_sequence = snoc((*yynode)->additional_expression_sequence, __node_226, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_shift_expression_rest(shift_expression_rest_ast **yynode)
{
  *yynode = create<shift_expression_rest_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LSHIFT
      || yytoken == Token_SIGNED_RSHIFT
      || yytoken == Token_UNSIGNED_RSHIFT)
    {
      if (yytoken == Token_LSHIFT)
        {
          if (yytoken != Token_LSHIFT)
            return yy_expected_token(yytoken, Token_LSHIFT, "<<");
          yylex();
          (*yynode)->shift_operator = shift_expression_rest_ast::op_lshift;
        }
      else if (yytoken == Token_SIGNED_RSHIFT)
        {
          if (yytoken != Token_SIGNED_RSHIFT)
            return yy_expected_token(yytoken, Token_SIGNED_RSHIFT, ">>");
          yylex();
          (*yynode)->shift_operator = shift_expression_rest_ast::op_signed_rshift;
        }
      else if (yytoken == Token_UNSIGNED_RSHIFT)
        {
          if (yytoken != Token_UNSIGNED_RSHIFT)
            return yy_expected_token(yytoken, Token_UNSIGNED_RSHIFT, ">>>");
          yylex();
          (*yynode)->shift_operator = shift_expression_rest_ast::op_unsigned_rshift;
        }
      else
        {
          return false;
        }
      additive_expression_ast *__node_227 = 0;
      if (!parse_additive_expression(&__node_227))
        {
          return yy_expected_symbol(java_ast_node::Kind_additive_expression, "additive_expression");
        }
      (*yynode)->expression = __node_227;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_statement(statement_ast **yynode)
{
  *yynode = create<statement_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ASSERT
      || yytoken == Token_BOOLEAN
      || yytoken == Token_BREAK
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_CONTINUE
      || yytoken == Token_DO
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_FOR
      || yytoken == Token_IF
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_RETURN
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_SWITCH
      || yytoken == Token_SYNCHRONIZED
      || yytoken == Token_THIS
      || yytoken == Token_THROW
      || yytoken == Token_TRY
      || yytoken == Token_VOID
      || yytoken == Token_WHILE
      || yytoken == Token_LPAREN
      || yytoken == Token_LBRACE
      || yytoken == Token_SEMICOLON
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_LBRACE)
        {
          block_ast *__node_228 = 0;
          if (!parse_block(&__node_228))
            {
              return yy_expected_symbol(java_ast_node::Kind_block, "block");
            }
          (*yynode)->block = __node_228;
          (*yynode)->statement_kind = statement_ast::kind_block_statement;
        }
      else if (yytoken == Token_ASSERT)
        {
          if (yytoken != Token_ASSERT)
            return yy_expected_token(yytoken, Token_ASSERT, "assert");
          yylex();
          expression_ast *__node_229 = 0;
          if (!parse_expression(&__node_229))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->assert_condition = __node_229;
          if (yytoken == Token_COLON)
            {
              if (yytoken != Token_COLON)
                return yy_expected_token(yytoken, Token_COLON, ":");
              yylex();
              expression_ast *__node_230 = 0;
              if (!parse_expression(&__node_230))
                {
                  return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
                }
              (*yynode)->assert_message = __node_230;
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
          (*yynode)->statement_kind = statement_ast::kind_assert_statement;
        }
      else if (yytoken == Token_IF)
        {
          if (yytoken != Token_IF)
            return yy_expected_token(yytoken, Token_IF, "if");
          yylex();
          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "(");
          yylex();
          expression_ast *__node_231 = 0;
          if (!parse_expression(&__node_231))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->if_condition = __node_231;
          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, ")");
          yylex();
          statement_ast *__node_232 = 0;
          if (!parse_statement(&__node_232))
            {
              return yy_expected_symbol(java_ast_node::Kind_statement, "statement");
            }
          (*yynode)->if_statement = __node_232;
          if (yytoken == Token_ELSE)
            {
              if (yytoken != Token_ELSE)
                return yy_expected_token(yytoken, Token_ELSE, "else");
              yylex();
              statement_ast *__node_233 = 0;
              if (!parse_statement(&__node_233))
                {
                  return yy_expected_symbol(java_ast_node::Kind_statement, "statement");
                }
              (*yynode)->else_statement = __node_233;
            }
          else if (true /*epsilon*/)
          {}
          else
            {
              return false;
            }
          (*yynode)->statement_kind = statement_ast::kind_if_statement;
        }
      else if (yytoken == Token_FOR)
        {
          if (yytoken != Token_FOR)
            return yy_expected_token(yytoken, Token_FOR, "for");
          yylex();
          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "(");
          yylex();
          for_control_ast *__node_234 = 0;
          if (!parse_for_control(&__node_234))
            {
              return yy_expected_symbol(java_ast_node::Kind_for_control, "for_control");
            }
          (*yynode)->for_control = __node_234;
          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, ")");
          yylex();
          statement_ast *__node_235 = 0;
          if (!parse_statement(&__node_235))
            {
              return yy_expected_symbol(java_ast_node::Kind_statement, "statement");
            }
          (*yynode)->for_statement = __node_235;
          (*yynode)->statement_kind = statement_ast::kind_for_statement;
        }
      else if (yytoken == Token_WHILE)
        {
          if (yytoken != Token_WHILE)
            return yy_expected_token(yytoken, Token_WHILE, "while");
          yylex();
          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "(");
          yylex();
          expression_ast *__node_236 = 0;
          if (!parse_expression(&__node_236))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->while_condition = __node_236;
          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, ")");
          yylex();
          statement_ast *__node_237 = 0;
          if (!parse_statement(&__node_237))
            {
              return yy_expected_symbol(java_ast_node::Kind_statement, "statement");
            }
          (*yynode)->while_statement = __node_237;
          (*yynode)->statement_kind = statement_ast::kind_while_statement;
        }
      else if (yytoken == Token_DO)
        {
          if (yytoken != Token_DO)
            return yy_expected_token(yytoken, Token_DO, "do");
          yylex();
          statement_ast *__node_238 = 0;
          if (!parse_statement(&__node_238))
            {
              return yy_expected_symbol(java_ast_node::Kind_statement, "statement");
            }
          (*yynode)->do_while_statement = __node_238;
          if (yytoken != Token_WHILE)
            return yy_expected_token(yytoken, Token_WHILE, "while");
          yylex();
          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "(");
          yylex();
          expression_ast *__node_239 = 0;
          if (!parse_expression(&__node_239))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->do_while_condition = __node_239;
          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, ")");
          yylex();
          if (yytoken != Token_SEMICOLON)
            return yy_expected_token(yytoken, Token_SEMICOLON, ";");
          yylex();
          (*yynode)->statement_kind = statement_ast::kind_do_while_statement;
        }
      else if (yytoken == Token_TRY)
        {
          if (yytoken != Token_TRY)
            return yy_expected_token(yytoken, Token_TRY, "try");
          yylex();
          block_ast *__node_240 = 0;
          if (!parse_block(&__node_240))
            {
              return yy_expected_symbol(java_ast_node::Kind_block, "block");
            }
          (*yynode)->try_block = __node_240;
          while (yytoken == Token_CATCH)
            {
              try_handler_ast *__node_241 = 0;
              if (!parse_try_handler(&__node_241))
                {
                  return yy_expected_symbol(java_ast_node::Kind_try_handler, "try_handler");
                }
              (*yynode)->handler_sequence = snoc((*yynode)->handler_sequence, __node_241, memory_pool);
            }
          if (yytoken == Token_FINALLY)
            {
              if (yytoken != Token_FINALLY)
                return yy_expected_token(yytoken, Token_FINALLY, "finally");
              yylex();
              block_ast *__node_242 = 0;
              if (!parse_block(&__node_242))
                {
                  return yy_expected_symbol(java_ast_node::Kind_block, "block");
                }
              (*yynode)->finally_block = __node_242;
            }
          else if (true /*epsilon*/)
          {}
          else
            {
              return false;
            }
          (*yynode)->statement_kind = statement_ast::kind_try_statement;
        }
      else if (yytoken == Token_SWITCH)
        {
          if (yytoken != Token_SWITCH)
            return yy_expected_token(yytoken, Token_SWITCH, "switch");
          yylex();
          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "(");
          yylex();
          expression_ast *__node_243 = 0;
          if (!parse_expression(&__node_243))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->switch_expression = __node_243;
          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, ")");
          yylex();
          if (yytoken != Token_LBRACE)
            return yy_expected_token(yytoken, Token_LBRACE, "{");
          yylex();
          while (yytoken == Token_CASE
                 || yytoken == Token_DEFAULT)
            {
              switch_statements_group_ast *__node_244 = 0;
              if (!parse_switch_statements_group(&__node_244))
                {
                  return yy_expected_symbol(java_ast_node::Kind_switch_statements_group, "switch_statements_group");
                }
              (*yynode)->switch_cases_sequence = snoc((*yynode)->switch_cases_sequence, __node_244, memory_pool);
            }
          if (yytoken != Token_RBRACE)
            return yy_expected_token(yytoken, Token_RBRACE, "}");
          yylex();
          (*yynode)->statement_kind = statement_ast::kind_switch_statement;
        }
      else if (yytoken == Token_SYNCHRONIZED)
        {
          if (yytoken != Token_SYNCHRONIZED)
            return yy_expected_token(yytoken, Token_SYNCHRONIZED, "synchronized");
          yylex();
          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "(");
          yylex();
          expression_ast *__node_245 = 0;
          if (!parse_expression(&__node_245))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->synchronized_locked_type = __node_245;
          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, ")");
          yylex();
          block_ast *__node_246 = 0;
          if (!parse_block(&__node_246))
            {
              return yy_expected_symbol(java_ast_node::Kind_block, "block");
            }
          (*yynode)->synchronized_block = __node_246;
          (*yynode)->statement_kind = statement_ast::kind_synchronized_statement;
        }
      else if (yytoken == Token_RETURN)
        {
          if (yytoken != Token_RETURN)
            return yy_expected_token(yytoken, Token_RETURN, "return");
          yylex();
          if (yytoken == Token_BOOLEAN
              || yytoken == Token_BYTE
              || yytoken == Token_CHAR
              || yytoken == Token_DOUBLE
              || yytoken == Token_FLOAT
              || yytoken == Token_INT
              || yytoken == Token_LONG
              || yytoken == Token_NEW
              || yytoken == Token_SHORT
              || yytoken == Token_SUPER
              || yytoken == Token_THIS
              || yytoken == Token_VOID
              || yytoken == Token_LPAREN
              || yytoken == Token_LESS_THAN
              || yytoken == Token_BANG
              || yytoken == Token_TILDE
              || yytoken == Token_INCREMENT
              || yytoken == Token_DECREMENT
              || yytoken == Token_PLUS
              || yytoken == Token_MINUS
              || yytoken == Token_TRUE
              || yytoken == Token_FALSE
              || yytoken == Token_NULL
              || yytoken == Token_INTEGER_LITERAL
              || yytoken == Token_FLOATING_POINT_LITERAL
              || yytoken == Token_CHARACTER_LITERAL
              || yytoken == Token_STRING_LITERAL
              || yytoken == Token_IDENTIFIER)
            {
              expression_ast *__node_247 = 0;
              if (!parse_expression(&__node_247))
                {
                  return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
                }
              (*yynode)->return_expression = __node_247;
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
          (*yynode)->statement_kind = statement_ast::kind_return_statement;
        }
      else if (yytoken == Token_THROW)
        {
          if (yytoken != Token_THROW)
            return yy_expected_token(yytoken, Token_THROW, "throw");
          yylex();
          expression_ast *__node_248 = 0;
          if (!parse_expression(&__node_248))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->throw_exception = __node_248;
          if (yytoken != Token_SEMICOLON)
            return yy_expected_token(yytoken, Token_SEMICOLON, ";");
          yylex();
          (*yynode)->statement_kind = statement_ast::kind_throw_statement;
        }
      else if (yytoken == Token_BREAK)
        {
          if (yytoken != Token_BREAK)
            return yy_expected_token(yytoken, Token_BREAK, "break");
          yylex();
          if (yytoken == Token_IDENTIFIER)
            {
              identifier_ast *__node_249 = 0;
              if (!parse_identifier(&__node_249))
                {
                  return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
                }
              (*yynode)->break_label = __node_249;
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
          (*yynode)->statement_kind = statement_ast::kind_break_statement;
        }
      else if (yytoken == Token_CONTINUE)
        {
          if (yytoken != Token_CONTINUE)
            return yy_expected_token(yytoken, Token_CONTINUE, "continue");
          yylex();
          if (yytoken == Token_IDENTIFIER)
            {
              identifier_ast *__node_250 = 0;
              if (!parse_identifier(&__node_250))
                {
                  return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
                }
              (*yynode)->continue_label = __node_250;
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
          (*yynode)->statement_kind = statement_ast::kind_continue_statement;
        }
      else if (yytoken == Token_SEMICOLON)
        {
          if (yytoken != Token_SEMICOLON)
            return yy_expected_token(yytoken, Token_SEMICOLON, ";");
          yylex();
          (*yynode)->statement_kind = statement_ast::kind_empty_statement;
        }
      else if (( LA(2).kind == Token_COLON ) && (yytoken == Token_IDENTIFIER))
        {
          identifier_ast *__node_251 = 0;
          if (!parse_identifier(&__node_251))
            {
              return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
            }
          (*yynode)->labeled_statement_identifier = __node_251;
          if (yytoken != Token_COLON)
            return yy_expected_token(yytoken, Token_COLON, ":");
          yylex();
          statement_ast *__node_252 = 0;
          if (!parse_statement(&__node_252))
            {
              return yy_expected_symbol(java_ast_node::Kind_statement, "statement");
            }
          (*yynode)->labeled_statement = __node_252;
          (*yynode)->statement_kind = statement_ast::kind_labeled_statement;
        }
      else if (yytoken == Token_BOOLEAN
               || yytoken == Token_BYTE
               || yytoken == Token_CHAR
               || yytoken == Token_DOUBLE
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_NEW
               || yytoken == Token_SHORT
               || yytoken == Token_SUPER
               || yytoken == Token_THIS
               || yytoken == Token_VOID
               || yytoken == Token_LPAREN
               || yytoken == Token_LESS_THAN
               || yytoken == Token_BANG
               || yytoken == Token_TILDE
               || yytoken == Token_INCREMENT
               || yytoken == Token_DECREMENT
               || yytoken == Token_PLUS
               || yytoken == Token_MINUS
               || yytoken == Token_TRUE
               || yytoken == Token_FALSE
               || yytoken == Token_NULL
               || yytoken == Token_INTEGER_LITERAL
               || yytoken == Token_FLOATING_POINT_LITERAL
               || yytoken == Token_CHARACTER_LITERAL
               || yytoken == Token_STRING_LITERAL
               || yytoken == Token_IDENTIFIER)
        {
          expression_ast *__node_253 = 0;
          if (!parse_expression(&__node_253))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->expression_statement = __node_253;
          if (yytoken != Token_SEMICOLON)
            return yy_expected_token(yytoken, Token_SEMICOLON, ";");
          yylex();
          (*yynode)->statement_kind = statement_ast::kind_expression_statement;
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

bool java::parse_super_suffix(super_suffix_ast **yynode)
{
  *yynode = create<super_suffix_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LPAREN
      || yytoken == Token_DOT)
    {
      if (yytoken == Token_LPAREN)
        {
          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "(");
          yylex();
          argument_list_ast *__node_254 = 0;
          if (!parse_argument_list(&__node_254))
            {
              return yy_expected_symbol(java_ast_node::Kind_argument_list, "argument_list");
            }
          (*yynode)->constructor_arguments = __node_254;
          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, ")");
          yylex();
        }
      else if (yytoken == Token_DOT)
        {
          if (yytoken != Token_DOT)
            return yy_expected_token(yytoken, Token_DOT, ".");
          yylex();
          if (( LA(2).kind != Token_LPAREN ) && (yytoken == Token_IDENTIFIER))
            {
              identifier_ast *__node_255 = 0;
              if (!parse_identifier(&__node_255))
                {
                  return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
                }
              (*yynode)->variable_name = __node_255;
            }
          else if (yytoken == Token_LESS_THAN
                   || yytoken == Token_IDENTIFIER)
            {
              if (( compatibility_mode() >= java15_compatibility ) && (yytoken == Token_LESS_THAN))
                {
                  non_wildcard_type_arguments_ast *__node_256 = 0;
                  if (!parse_non_wildcard_type_arguments(&__node_256))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_non_wildcard_type_arguments, "non_wildcard_type_arguments");
                    }
                  (*yynode)->type_arguments = __node_256;
                }
              else if (true /*epsilon*/)
              {}
              else
                {
                  return false;
                }
              identifier_ast *__node_257 = 0;
              if (!parse_identifier(&__node_257))
                {
                  return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
                }
              (*yynode)->method_name = __node_257;
              if (yytoken == Token_LPAREN)
                {
                  if (yytoken != Token_LPAREN)
                    return yy_expected_token(yytoken, Token_LPAREN, "(");
                  yylex();
                  argument_list_ast *__node_258 = 0;
                  if (!parse_argument_list(&__node_258))
                    {
                      return yy_expected_symbol(java_ast_node::Kind_argument_list, "argument_list");
                    }
                  (*yynode)->method_arguments = __node_258;
                  if (yytoken != Token_RPAREN)
                    return yy_expected_token(yytoken, Token_RPAREN, ")");
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

bool java::parse_switch_case(switch_case_ast **yynode)
{
  *yynode = create<switch_case_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_CASE
      || yytoken == Token_DEFAULT)
    {
      if (yytoken == Token_CASE)
        {
          if (yytoken != Token_CASE)
            return yy_expected_token(yytoken, Token_CASE, "case");
          yylex();
          expression_ast *__node_259 = 0;
          if (!parse_expression(&__node_259))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->expression = __node_259;
          (*yynode)->branch_type = switch_case_ast::case_branch;
        }
      else if (yytoken == Token_DEFAULT)
        {
          if (yytoken != Token_DEFAULT)
            return yy_expected_token(yytoken, Token_DEFAULT, "default");
          yylex();
          (*yynode)->branch_type = switch_case_ast::default_branch;
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

bool java::parse_switch_statements_group(switch_statements_group_ast **yynode)
{
  *yynode = create<switch_statements_group_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_CASE
      || yytoken == Token_DEFAULT)
    {
      do
        {
          switch_case_ast *__node_260 = 0;
          if (!parse_switch_case(&__node_260))
            {
              return yy_expected_symbol(java_ast_node::Kind_switch_case, "switch_case");
            }
          (*yynode)->case_sequence = snoc((*yynode)->case_sequence, __node_260, memory_pool);
        }
      while (yytoken == Token_CASE
             || yytoken == Token_DEFAULT);
      while (yytoken == Token_ABSTRACT
             || yytoken == Token_ASSERT
             || yytoken == Token_BOOLEAN
             || yytoken == Token_BREAK
             || yytoken == Token_BYTE
             || yytoken == Token_CHAR
             || yytoken == Token_CLASS
             || yytoken == Token_CONTINUE
             || yytoken == Token_DO
             || yytoken == Token_DOUBLE
             || yytoken == Token_ENUM
             || yytoken == Token_FINAL
             || yytoken == Token_FLOAT
             || yytoken == Token_FOR
             || yytoken == Token_IF
             || yytoken == Token_INT
             || yytoken == Token_INTERFACE
             || yytoken == Token_LONG
             || yytoken == Token_NATIVE
             || yytoken == Token_NEW
             || yytoken == Token_PRIVATE
             || yytoken == Token_PROTECTED
             || yytoken == Token_PUBLIC
             || yytoken == Token_RETURN
             || yytoken == Token_SHORT
             || yytoken == Token_STATIC
             || yytoken == Token_STRICTFP
             || yytoken == Token_SUPER
             || yytoken == Token_SWITCH
             || yytoken == Token_SYNCHRONIZED
             || yytoken == Token_THIS
             || yytoken == Token_THROW
             || yytoken == Token_TRANSIENT
             || yytoken == Token_TRY
             || yytoken == Token_VOID
             || yytoken == Token_VOLATILE
             || yytoken == Token_WHILE
             || yytoken == Token_LPAREN
             || yytoken == Token_LBRACE
             || yytoken == Token_SEMICOLON
             || yytoken == Token_AT
             || yytoken == Token_LESS_THAN
             || yytoken == Token_BANG
             || yytoken == Token_TILDE
             || yytoken == Token_INCREMENT
             || yytoken == Token_DECREMENT
             || yytoken == Token_PLUS
             || yytoken == Token_MINUS
             || yytoken == Token_TRUE
             || yytoken == Token_FALSE
             || yytoken == Token_NULL
             || yytoken == Token_INTEGER_LITERAL
             || yytoken == Token_FLOATING_POINT_LITERAL
             || yytoken == Token_CHARACTER_LITERAL
             || yytoken == Token_STRING_LITERAL
             || yytoken == Token_IDENTIFIER)
        {
          block_statement_ast *__node_261 = 0;
          if (!parse_block_statement(&__node_261))
            {
              return yy_expected_symbol(java_ast_node::Kind_block_statement, "block_statement");
            }
          (*yynode)->statement_sequence = snoc((*yynode)->statement_sequence, __node_261, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_throws_clause(throws_clause_ast **yynode)
{
  *yynode = create<throws_clause_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_THROWS)
    {
      if (yytoken != Token_THROWS)
        return yy_expected_token(yytoken, Token_THROWS, "throws");
      yylex();
      qualified_identifier_ast *__node_262 = 0;
      if (!parse_qualified_identifier(&__node_262))
        {
          return yy_expected_symbol(java_ast_node::Kind_qualified_identifier, "qualified_identifier");
        }
      (*yynode)->identifier_sequence = snoc((*yynode)->identifier_sequence, __node_262, memory_pool);
      while (yytoken == Token_COMMA)
        {
          if (yytoken != Token_COMMA)
            return yy_expected_token(yytoken, Token_COMMA, ",");
          yylex();
          qualified_identifier_ast *__node_263 = 0;
          if (!parse_qualified_identifier(&__node_263))
            {
              return yy_expected_symbol(java_ast_node::Kind_qualified_identifier, "qualified_identifier");
            }
          (*yynode)->identifier_sequence = snoc((*yynode)->identifier_sequence, __node_263, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_try_handler(try_handler_ast **yynode)
{
  *yynode = create<try_handler_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_CATCH)
    {
      if (yytoken != Token_CATCH)
        return yy_expected_token(yytoken, Token_CATCH, "catch");
      yylex();
      if (yytoken != Token_LPAREN)
        return yy_expected_token(yytoken, Token_LPAREN, "(");
      yylex();
      parameter_declaration_ast *__node_264 = 0;
      if (!parse_parameter_declaration(&__node_264))
        {
          return yy_expected_symbol(java_ast_node::Kind_parameter_declaration, "parameter_declaration");
        }
      (*yynode)->exception_parameter = __node_264;
      if (yytoken != Token_RPAREN)
        return yy_expected_token(yytoken, Token_RPAREN, ")");
      yylex();
      block_ast *__node_265 = 0;
      if (!parse_block(&__node_265))
        {
          return yy_expected_symbol(java_ast_node::Kind_block, "block");
        }
      (*yynode)->catch_block = __node_265;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_type_argument(type_argument_ast **yynode)
{
  *yynode = create<type_argument_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_SHORT
      || yytoken == Token_VOID
      || yytoken == Token_QUESTION
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_SHORT
          || yytoken == Token_VOID
          || yytoken == Token_IDENTIFIER)
        {
          type_argument_specification_ast *__node_266 = 0;
          if (!parse_type_argument_specification(&__node_266))
            {
              return yy_expected_symbol(java_ast_node::Kind_type_argument_specification, "type_argument_specification");
            }
          (*yynode)->type_argument_specification = __node_266;
        }
      else if (yytoken == Token_QUESTION)
        {
          wildcard_type_ast *__node_267 = 0;
          if (!parse_wildcard_type(&__node_267))
            {
              return yy_expected_symbol(java_ast_node::Kind_wildcard_type, "wildcard_type");
            }
          (*yynode)->wildcard_type = __node_267;
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

bool java::parse_type_argument_specification(type_argument_specification_ast **yynode)
{
  *yynode = create<type_argument_specification_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_SHORT
      || yytoken == Token_VOID
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_IDENTIFIER)
        {
          class_type_specification_ast *__node_268 = 0;
          if (!parse_class_type_specification(&__node_268))
            {
              return yy_expected_symbol(java_ast_node::Kind_class_type_specification, "class_type_specification");
            }
          (*yynode)->class_type = __node_268;
        }
      else if (yytoken == Token_BOOLEAN
               || yytoken == Token_BYTE
               || yytoken == Token_CHAR
               || yytoken == Token_DOUBLE
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_SHORT
               || yytoken == Token_VOID)
        {
          builtin_type_array_specification_ast *__node_269 = 0;
          if (!parse_builtin_type_array_specification(&__node_269))
            {
              return yy_expected_symbol(java_ast_node::Kind_builtin_type_array_specification, "builtin_type_array_specification");
            }
          (*yynode)->builtin_type_array = __node_269;
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

bool java::parse_type_arguments(type_arguments_ast **yynode)
{
  *yynode = create<type_arguments_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LESS_THAN)
    {
      if (yytoken != Token_LESS_THAN)
        return yy_expected_token(yytoken, Token_LESS_THAN, "<");
      yylex();
      int currentLtLevel = ltCounter;
      ltCounter++;
      type_argument_ast *__node_270 = 0;
      if (!parse_type_argument(&__node_270))
        {
          return yy_expected_symbol(java_ast_node::Kind_type_argument, "type_argument");
        }
      (*yynode)->type_argument_sequence = snoc((*yynode)->type_argument_sequence, __node_270, memory_pool);
      while (yytoken == Token_COMMA)
        {
          if ( ltCounter != currentLtLevel + 1 )
            {
              break;
            }
          if (yytoken != Token_COMMA)
            return yy_expected_token(yytoken, Token_COMMA, ",");
          yylex();
          type_argument_ast *__node_271 = 0;
          if (!parse_type_argument(&__node_271))
            {
              return yy_expected_symbol(java_ast_node::Kind_type_argument, "type_argument");
            }
          (*yynode)->type_argument_sequence = snoc((*yynode)->type_argument_sequence, __node_271, memory_pool);
        }
      if (yytoken == Token_GREATER_THAN
          || yytoken == Token_SIGNED_RSHIFT
          || yytoken == Token_UNSIGNED_RSHIFT)
        {
          type_arguments_or_parameters_end_ast *__node_272 = 0;
          if (!parse_type_arguments_or_parameters_end(&__node_272))
            {
              return yy_expected_symbol(java_ast_node::Kind_type_arguments_or_parameters_end, "type_arguments_or_parameters_end");
            }
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      if ( currentLtLevel == 0 && ltCounter != currentLtLevel )
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

bool java::parse_type_arguments_or_parameters_end(type_arguments_or_parameters_end_ast **yynode)
{
  *yynode = create<type_arguments_or_parameters_end_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_GREATER_THAN
      || yytoken == Token_SIGNED_RSHIFT
      || yytoken == Token_UNSIGNED_RSHIFT)
    {
      if (yytoken == Token_GREATER_THAN)
        {
          if (yytoken != Token_GREATER_THAN)
            return yy_expected_token(yytoken, Token_GREATER_THAN, ">");
          yylex();
          ltCounter -= 1;
        }
      else if (yytoken == Token_SIGNED_RSHIFT)
        {
          if (yytoken != Token_SIGNED_RSHIFT)
            return yy_expected_token(yytoken, Token_SIGNED_RSHIFT, ">>");
          yylex();
          ltCounter -= 2;
        }
      else if (yytoken == Token_UNSIGNED_RSHIFT)
        {
          if (yytoken != Token_UNSIGNED_RSHIFT)
            return yy_expected_token(yytoken, Token_UNSIGNED_RSHIFT, ">>>");
          yylex();
          ltCounter -= 3;
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

bool java::parse_type_declaration(type_declaration_ast **yynode)
{
  *yynode = create<type_declaration_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ABSTRACT
      || yytoken == Token_CLASS
      || yytoken == Token_ENUM
      || yytoken == Token_FINAL
      || yytoken == Token_INTERFACE
      || yytoken == Token_NATIVE
      || yytoken == Token_PRIVATE
      || yytoken == Token_PROTECTED
      || yytoken == Token_PUBLIC
      || yytoken == Token_STATIC
      || yytoken == Token_STRICTFP
      || yytoken == Token_SYNCHRONIZED
      || yytoken == Token_TRANSIENT
      || yytoken == Token_VOLATILE
      || yytoken == Token_SEMICOLON
      || yytoken == Token_AT)
    {
      if (yytoken == Token_ABSTRACT
          || yytoken == Token_CLASS
          || yytoken == Token_ENUM
          || yytoken == Token_FINAL
          || yytoken == Token_INTERFACE
          || yytoken == Token_NATIVE
          || yytoken == Token_PRIVATE
          || yytoken == Token_PROTECTED
          || yytoken == Token_PUBLIC
          || yytoken == Token_STATIC
          || yytoken == Token_STRICTFP
          || yytoken == Token_SYNCHRONIZED
          || yytoken == Token_TRANSIENT
          || yytoken == Token_VOLATILE
          || yytoken == Token_AT)
        {
          optional_modifiers_ast *__node_273 = 0;
          if (!parse_optional_modifiers(&__node_273))
            {
              return yy_expected_symbol(java_ast_node::Kind_optional_modifiers, "optional_modifiers");
            }
          (*yynode)->modifiers = __node_273;
          if (yytoken == Token_CLASS)
            {
              class_declaration_ast *__node_274 = 0;
              if (!parse_class_declaration(&__node_274))
                {
                  return yy_expected_symbol(java_ast_node::Kind_class_declaration, "class_declaration");
                }
              (*yynode)->class_declaration = __node_274;
            }
          else if (yytoken == Token_ENUM)
            {
              enum_declaration_ast *__node_275 = 0;
              if (!parse_enum_declaration(&__node_275))
                {
                  return yy_expected_symbol(java_ast_node::Kind_enum_declaration, "enum_declaration");
                }
              (*yynode)->enum_declaration = __node_275;
            }
          else if (yytoken == Token_INTERFACE)
            {
              interface_declaration_ast *__node_276 = 0;
              if (!parse_interface_declaration(&__node_276))
                {
                  return yy_expected_symbol(java_ast_node::Kind_interface_declaration, "interface_declaration");
                }
              (*yynode)->interface_declaration = __node_276;
            }
          else if (yytoken == Token_AT)
            {
              annotation_type_declaration_ast *__node_277 = 0;
              if (!parse_annotation_type_declaration(&__node_277))
                {
                  return yy_expected_symbol(java_ast_node::Kind_annotation_type_declaration, "annotation_type_declaration");
                }
              (*yynode)->annotation_type_declaration = __node_277;
            }
          else
            {
              return false;
            }
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

bool java::parse_type_parameter(type_parameter_ast **yynode)
{
  *yynode = create<type_parameter_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      identifier_ast *__node_278 = 0;
      if (!parse_identifier(&__node_278))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->identifier = __node_278;
      if (yytoken == Token_EXTENDS)
        {
          if (yytoken != Token_EXTENDS)
            return yy_expected_token(yytoken, Token_EXTENDS, "extends");
          yylex();
          class_or_interface_type_ast *__node_279 = 0;
          if (!parse_class_or_interface_type(&__node_279))
            {
              return yy_expected_symbol(java_ast_node::Kind_class_or_interface_type, "class_or_interface_type");
            }
          (*yynode)->extends_type_sequence = snoc((*yynode)->extends_type_sequence, __node_279, memory_pool);
          while (yytoken == Token_BIT_AND)
            {
              if (yytoken != Token_BIT_AND)
                return yy_expected_token(yytoken, Token_BIT_AND, "&");
              yylex();
              class_or_interface_type_ast *__node_280 = 0;
              if (!parse_class_or_interface_type(&__node_280))
                {
                  return yy_expected_symbol(java_ast_node::Kind_class_or_interface_type, "class_or_interface_type");
                }
              (*yynode)->extends_type_sequence = snoc((*yynode)->extends_type_sequence, __node_280, memory_pool);
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

bool java::parse_type_parameters(type_parameters_ast **yynode)
{
  *yynode = create<type_parameters_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LESS_THAN)
    {
      if (yytoken != Token_LESS_THAN)
        return yy_expected_token(yytoken, Token_LESS_THAN, "<");
      yylex();
      int currentLtLevel = ltCounter;
      ltCounter++;
      type_parameter_ast *__node_281 = 0;
      if (!parse_type_parameter(&__node_281))
        {
          return yy_expected_symbol(java_ast_node::Kind_type_parameter, "type_parameter");
        }
      (*yynode)->type_parameter_sequence = snoc((*yynode)->type_parameter_sequence, __node_281, memory_pool);
      while (yytoken == Token_COMMA)
        {
          if (yytoken != Token_COMMA)
            return yy_expected_token(yytoken, Token_COMMA, ",");
          yylex();
          type_parameter_ast *__node_282 = 0;
          if (!parse_type_parameter(&__node_282))
            {
              return yy_expected_symbol(java_ast_node::Kind_type_parameter, "type_parameter");
            }
          (*yynode)->type_parameter_sequence = snoc((*yynode)->type_parameter_sequence, __node_282, memory_pool);
        }
      if (yytoken == Token_GREATER_THAN
          || yytoken == Token_SIGNED_RSHIFT
          || yytoken == Token_UNSIGNED_RSHIFT)
        {
          type_arguments_or_parameters_end_ast *__node_283 = 0;
          if (!parse_type_arguments_or_parameters_end(&__node_283))
            {
              return yy_expected_symbol(java_ast_node::Kind_type_arguments_or_parameters_end, "type_arguments_or_parameters_end");
            }
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      if ( currentLtLevel == 0 && ltCounter != currentLtLevel )
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

bool java::parse_type_specification(type_specification_ast **yynode)
{
  *yynode = create<type_specification_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_SHORT
      || yytoken == Token_VOID
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_IDENTIFIER)
        {
          class_type_specification_ast *__node_284 = 0;
          if (!parse_class_type_specification(&__node_284))
            {
              return yy_expected_symbol(java_ast_node::Kind_class_type_specification, "class_type_specification");
            }
          (*yynode)->class_type_spec = __node_284;
        }
      else if (yytoken == Token_BOOLEAN
               || yytoken == Token_BYTE
               || yytoken == Token_CHAR
               || yytoken == Token_DOUBLE
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_SHORT
               || yytoken == Token_VOID)
        {
          builtin_type_specification_ast *__node_285 = 0;
          if (!parse_builtin_type_specification(&__node_285))
            {
              return yy_expected_symbol(java_ast_node::Kind_builtin_type_specification, "builtin_type_specification");
            }
          (*yynode)->builtin_type_spec = __node_285;
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

bool java::parse_type_specification_noarray(type_specification_noarray_ast **yynode)
{
  *yynode = create<type_specification_noarray_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_SHORT
      || yytoken == Token_VOID
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_IDENTIFIER)
        {
          class_or_interface_type_ast *__node_286 = 0;
          if (!parse_class_or_interface_type(&__node_286))
            {
              return yy_expected_symbol(java_ast_node::Kind_class_or_interface_type, "class_or_interface_type");
            }
          (*yynode)->class_or_interface_type = __node_286;
        }
      else if (yytoken == Token_BOOLEAN
               || yytoken == Token_BYTE
               || yytoken == Token_CHAR
               || yytoken == Token_DOUBLE
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_SHORT
               || yytoken == Token_VOID)
        {
          builtin_type_ast *__node_287 = 0;
          if (!parse_builtin_type(&__node_287))
            {
              return yy_expected_symbol(java_ast_node::Kind_builtin_type, "builtin_type");
            }
          (*yynode)->builtin_type = __node_287;
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

bool java::parse_unary_expression(unary_expression_ast **yynode)
{
  *yynode = create<unary_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_INCREMENT)
        {
          if (yytoken != Token_INCREMENT)
            return yy_expected_token(yytoken, Token_INCREMENT, "++");
          yylex();
          unary_expression_ast *__node_288 = 0;
          if (!parse_unary_expression(&__node_288))
            {
              return yy_expected_symbol(java_ast_node::Kind_unary_expression, "unary_expression");
            }
          (*yynode)->unary_expression = __node_288;
          (*yynode)->type = unary_expression_ast::type_incremented_expression;
        }
      else if (yytoken == Token_DECREMENT)
        {
          if (yytoken != Token_DECREMENT)
            return yy_expected_token(yytoken, Token_DECREMENT, "--");
          yylex();
          unary_expression_ast *__node_289 = 0;
          if (!parse_unary_expression(&__node_289))
            {
              return yy_expected_symbol(java_ast_node::Kind_unary_expression, "unary_expression");
            }
          (*yynode)->unary_expression = __node_289;
          (*yynode)->type = unary_expression_ast::type_decremented_expression;
        }
      else if (yytoken == Token_MINUS)
        {
          if (yytoken != Token_MINUS)
            return yy_expected_token(yytoken, Token_MINUS, "-");
          yylex();
          unary_expression_ast *__node_290 = 0;
          if (!parse_unary_expression(&__node_290))
            {
              return yy_expected_symbol(java_ast_node::Kind_unary_expression, "unary_expression");
            }
          (*yynode)->unary_expression = __node_290;
          (*yynode)->type = unary_expression_ast::type_unary_minus_expression;
        }
      else if (yytoken == Token_PLUS)
        {
          if (yytoken != Token_PLUS)
            return yy_expected_token(yytoken, Token_PLUS, "+");
          yylex();
          unary_expression_ast *__node_291 = 0;
          if (!parse_unary_expression(&__node_291))
            {
              return yy_expected_symbol(java_ast_node::Kind_unary_expression, "unary_expression");
            }
          (*yynode)->unary_expression = __node_291;
          (*yynode)->type = unary_expression_ast::type_unary_plus_expression;
        }
      else if (yytoken == Token_BOOLEAN
               || yytoken == Token_BYTE
               || yytoken == Token_CHAR
               || yytoken == Token_DOUBLE
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_NEW
               || yytoken == Token_SHORT
               || yytoken == Token_SUPER
               || yytoken == Token_THIS
               || yytoken == Token_VOID
               || yytoken == Token_LPAREN
               || yytoken == Token_LESS_THAN
               || yytoken == Token_BANG
               || yytoken == Token_TILDE
               || yytoken == Token_TRUE
               || yytoken == Token_FALSE
               || yytoken == Token_NULL
               || yytoken == Token_INTEGER_LITERAL
               || yytoken == Token_FLOATING_POINT_LITERAL
               || yytoken == Token_CHARACTER_LITERAL
               || yytoken == Token_STRING_LITERAL
               || yytoken == Token_IDENTIFIER)
        {
          unary_expression_not_plusminus_ast *__node_292 = 0;
          if (!parse_unary_expression_not_plusminus(&__node_292))
            {
              return yy_expected_symbol(java_ast_node::Kind_unary_expression_not_plusminus, "unary_expression_not_plusminus");
            }
          (*yynode)->unary_expression_not_plusminus = __node_292;
          (*yynode)->type = unary_expression_ast::type_unary_expression_not_plusminus;
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

bool java::parse_unary_expression_not_plusminus(unary_expression_not_plusminus_ast **yynode)
{
  *yynode = create<unary_expression_not_plusminus_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_TILDE)
        {
          if (yytoken != Token_TILDE)
            return yy_expected_token(yytoken, Token_TILDE, "~");
          yylex();
          unary_expression_ast *__node_293 = 0;
          if (!parse_unary_expression(&__node_293))
            {
              return yy_expected_symbol(java_ast_node::Kind_unary_expression, "unary_expression");
            }
          (*yynode)->bitwise_not_expression = __node_293;
        }
      else if (yytoken == Token_BANG)
        {
          if (yytoken != Token_BANG)
            return yy_expected_token(yytoken, Token_BANG, "!");
          yylex();
          unary_expression_ast *__node_294 = 0;
          if (!parse_unary_expression(&__node_294))
            {
              return yy_expected_symbol(java_ast_node::Kind_unary_expression, "unary_expression");
            }
          (*yynode)->logical_not_expression = __node_294;
        }
      else if (( lookahead_is_cast_expression() == true ) && (yytoken == Token_LPAREN))
        {
          cast_expression_ast *__node_295 = 0;
          if (!parse_cast_expression(&__node_295))
            {
              return yy_expected_symbol(java_ast_node::Kind_cast_expression, "cast_expression");
            }
          (*yynode)->cast_expression = __node_295;
        }
      else if (yytoken == Token_BOOLEAN
               || yytoken == Token_BYTE
               || yytoken == Token_CHAR
               || yytoken == Token_DOUBLE
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_NEW
               || yytoken == Token_SHORT
               || yytoken == Token_SUPER
               || yytoken == Token_THIS
               || yytoken == Token_VOID
               || yytoken == Token_LPAREN
               || yytoken == Token_LESS_THAN
               || yytoken == Token_TRUE
               || yytoken == Token_FALSE
               || yytoken == Token_NULL
               || yytoken == Token_INTEGER_LITERAL
               || yytoken == Token_FLOATING_POINT_LITERAL
               || yytoken == Token_CHARACTER_LITERAL
               || yytoken == Token_STRING_LITERAL
               || yytoken == Token_IDENTIFIER)
        {
          primary_expression_ast *__node_296 = 0;
          if (!parse_primary_expression(&__node_296))
            {
              return yy_expected_symbol(java_ast_node::Kind_primary_expression, "primary_expression");
            }
          (*yynode)->primary_expression = __node_296;
          while (yytoken == Token_INCREMENT
                 || yytoken == Token_DECREMENT)
            {
              postfix_operator_ast *__node_297 = 0;
              if (!parse_postfix_operator(&__node_297))
                {
                  return yy_expected_symbol(java_ast_node::Kind_postfix_operator, "postfix_operator");
                }
              (*yynode)->postfix_operator_sequence = snoc((*yynode)->postfix_operator_sequence, __node_297, memory_pool);
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

bool java::parse_variable_array_initializer(variable_array_initializer_ast **yynode)
{
  *yynode = create<variable_array_initializer_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE)
    {
      if (yytoken != Token_LBRACE)
        return yy_expected_token(yytoken, Token_LBRACE, "{");
      yylex();
      if (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_NEW
          || yytoken == Token_SHORT
          || yytoken == Token_SUPER
          || yytoken == Token_THIS
          || yytoken == Token_VOID
          || yytoken == Token_LPAREN
          || yytoken == Token_LBRACE
          || yytoken == Token_LESS_THAN
          || yytoken == Token_BANG
          || yytoken == Token_TILDE
          || yytoken == Token_INCREMENT
          || yytoken == Token_DECREMENT
          || yytoken == Token_PLUS
          || yytoken == Token_MINUS
          || yytoken == Token_TRUE
          || yytoken == Token_FALSE
          || yytoken == Token_NULL
          || yytoken == Token_INTEGER_LITERAL
          || yytoken == Token_FLOATING_POINT_LITERAL
          || yytoken == Token_CHARACTER_LITERAL
          || yytoken == Token_STRING_LITERAL
          || yytoken == Token_IDENTIFIER)
        {
          variable_initializer_ast *__node_298 = 0;
          if (!parse_variable_initializer(&__node_298))
            {
              return yy_expected_symbol(java_ast_node::Kind_variable_initializer, "variable_initializer");
            }
          (*yynode)->variable_initializer_sequence = snoc((*yynode)->variable_initializer_sequence, __node_298, memory_pool);
          while (yytoken == Token_COMMA)
            {
              if (LA(2).kind == Token_RBRACE)
                {
                  break;
                }
              if (yytoken != Token_COMMA)
                return yy_expected_token(yytoken, Token_COMMA, ",");
              yylex();
              variable_initializer_ast *__node_299 = 0;
              if (!parse_variable_initializer(&__node_299))
                {
                  return yy_expected_symbol(java_ast_node::Kind_variable_initializer, "variable_initializer");
                }
              (*yynode)->variable_initializer_sequence = snoc((*yynode)->variable_initializer_sequence, __node_299, memory_pool);
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

bool java::parse_variable_declaration(variable_declaration_ast **yynode)
{
  *yynode = create<variable_declaration_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FINAL
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_SHORT
      || yytoken == Token_VOID
      || yytoken == Token_AT
      || yytoken == Token_IDENTIFIER)
    {
      parameter_declaration_ast *__node_300 = 0;
      if (!parse_parameter_declaration(&__node_300))
        {
          return yy_expected_symbol(java_ast_node::Kind_parameter_declaration, "parameter_declaration");
        }
      (*yynode)->initial_declaration = __node_300;
      variable_declaration_rest_ast *__node_301 = 0;
      if (!parse_variable_declaration_rest(&__node_301))
        {
          return yy_expected_symbol(java_ast_node::Kind_variable_declaration_rest, "variable_declaration_rest");
        }
      (*yynode)->rest = __node_301;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_variable_declaration_rest(variable_declaration_rest_ast **yynode)
{
  *yynode = create<variable_declaration_rest_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_COMMA
      || yytoken == Token_ASSIGN || yytoken == Token_SEMICOLON)
    {
      if (yytoken == Token_ASSIGN)
        {
          if (yytoken != Token_ASSIGN)
            return yy_expected_token(yytoken, Token_ASSIGN, "=");
          yylex();
          variable_initializer_ast *__node_302 = 0;
          if (!parse_variable_initializer(&__node_302))
            {
              return yy_expected_symbol(java_ast_node::Kind_variable_initializer, "variable_initializer");
            }
          (*yynode)->first_initializer = __node_302;
        }
      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }
      while (yytoken == Token_COMMA)
        {
          if (yytoken != Token_COMMA)
            return yy_expected_token(yytoken, Token_COMMA, ",");
          yylex();
          variable_declarator_ast *__node_303 = 0;
          if (!parse_variable_declarator(&__node_303))
            {
              return yy_expected_symbol(java_ast_node::Kind_variable_declarator, "variable_declarator");
            }
          (*yynode)->variable_declarator_sequence = snoc((*yynode)->variable_declarator_sequence, __node_303, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool java::parse_variable_declarator(variable_declarator_ast **yynode)
{
  *yynode = create<variable_declarator_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      identifier_ast *__node_304 = 0;
      if (!parse_identifier(&__node_304))
        {
          return yy_expected_symbol(java_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->variable_name = __node_304;
      optional_declarator_brackets_ast *__node_305 = 0;
      if (!parse_optional_declarator_brackets(&__node_305))
        {
          return yy_expected_symbol(java_ast_node::Kind_optional_declarator_brackets, "optional_declarator_brackets");
        }
      (*yynode)->declarator_brackets = __node_305;
      if (yytoken == Token_ASSIGN)
        {
          if (yytoken != Token_ASSIGN)
            return yy_expected_token(yytoken, Token_ASSIGN, "=");
          yylex();
          variable_initializer_ast *__node_306 = 0;
          if (!parse_variable_initializer(&__node_306))
            {
              return yy_expected_symbol(java_ast_node::Kind_variable_initializer, "variable_initializer");
            }
          (*yynode)->initializer = __node_306;
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

bool java::parse_variable_initializer(variable_initializer_ast **yynode)
{
  *yynode = create<variable_initializer_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_BOOLEAN
      || yytoken == Token_BYTE
      || yytoken == Token_CHAR
      || yytoken == Token_DOUBLE
      || yytoken == Token_FLOAT
      || yytoken == Token_INT
      || yytoken == Token_LONG
      || yytoken == Token_NEW
      || yytoken == Token_SHORT
      || yytoken == Token_SUPER
      || yytoken == Token_THIS
      || yytoken == Token_VOID
      || yytoken == Token_LPAREN
      || yytoken == Token_LBRACE
      || yytoken == Token_LESS_THAN
      || yytoken == Token_BANG
      || yytoken == Token_TILDE
      || yytoken == Token_INCREMENT
      || yytoken == Token_DECREMENT
      || yytoken == Token_PLUS
      || yytoken == Token_MINUS
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_FLOATING_POINT_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_BOOLEAN
          || yytoken == Token_BYTE
          || yytoken == Token_CHAR
          || yytoken == Token_DOUBLE
          || yytoken == Token_FLOAT
          || yytoken == Token_INT
          || yytoken == Token_LONG
          || yytoken == Token_NEW
          || yytoken == Token_SHORT
          || yytoken == Token_SUPER
          || yytoken == Token_THIS
          || yytoken == Token_VOID
          || yytoken == Token_LPAREN
          || yytoken == Token_LESS_THAN
          || yytoken == Token_BANG
          || yytoken == Token_TILDE
          || yytoken == Token_INCREMENT
          || yytoken == Token_DECREMENT
          || yytoken == Token_PLUS
          || yytoken == Token_MINUS
          || yytoken == Token_TRUE
          || yytoken == Token_FALSE
          || yytoken == Token_NULL
          || yytoken == Token_INTEGER_LITERAL
          || yytoken == Token_FLOATING_POINT_LITERAL
          || yytoken == Token_CHARACTER_LITERAL
          || yytoken == Token_STRING_LITERAL
          || yytoken == Token_IDENTIFIER)
        {
          expression_ast *__node_307 = 0;
          if (!parse_expression(&__node_307))
            {
              return yy_expected_symbol(java_ast_node::Kind_expression, "expression");
            }
          (*yynode)->expression = __node_307;
        }
      else if (yytoken == Token_LBRACE)
        {
          variable_array_initializer_ast *__node_308 = 0;
          if (!parse_variable_array_initializer(&__node_308))
            {
              return yy_expected_symbol(java_ast_node::Kind_variable_array_initializer, "variable_array_initializer");
            }
          (*yynode)->array_initializer = __node_308;
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

bool java::parse_wildcard_type(wildcard_type_ast **yynode)
{
  *yynode = create<wildcard_type_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_QUESTION)
    {
      if (yytoken != Token_QUESTION)
        return yy_expected_token(yytoken, Token_QUESTION, "?");
      yylex();
      if (yytoken == Token_EXTENDS
          || yytoken == Token_SUPER)
        {
          wildcard_type_bounds_ast *__node_309 = 0;
          if (!parse_wildcard_type_bounds(&__node_309))
            {
              return yy_expected_symbol(java_ast_node::Kind_wildcard_type_bounds, "wildcard_type_bounds");
            }
          (*yynode)->bounds = __node_309;
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

bool java::parse_wildcard_type_bounds(wildcard_type_bounds_ast **yynode)
{
  *yynode = create<wildcard_type_bounds_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_EXTENDS
      || yytoken == Token_SUPER)
    {
      if (yytoken == Token_EXTENDS)
        {
          if (yytoken != Token_EXTENDS)
            return yy_expected_token(yytoken, Token_EXTENDS, "extends");
          yylex();
          (*yynode)->extends_or_super = wildcard_type_bounds_ast::extends;
        }
      else if (yytoken == Token_SUPER)
        {
          if (yytoken != Token_SUPER)
            return yy_expected_token(yytoken, Token_SUPER, "super");
          yylex();
          (*yynode)->extends_or_super = wildcard_type_bounds_ast::super;
        }
      else
        {
          return false;
        }
      class_type_specification_ast *__node_310 = 0;
      if (!parse_class_type_specification(&__node_310))
        {
          return yy_expected_symbol(java_ast_node::Kind_class_type_specification, "class_type_specification");
        }
      (*yynode)->type = __node_310;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

java_visitor::parser_fun_t java_visitor::_S_parser_table[] = {
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_additive_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_additive_expression_rest),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_annotation),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_annotation_arguments),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_annotation_element_array_initializer),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_annotation_element_array_value),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_annotation_element_value),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_annotation_element_value_pair),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_annotation_type_body),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_annotation_type_declaration),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_annotation_type_field),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_argument_list),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_array_creator_rest),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_bit_and_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_bit_or_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_bit_xor_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_block),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_block_statement),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_builtin_type),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_builtin_type_array_specification),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_builtin_type_specification),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_cast_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_class_body),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_class_declaration),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_class_extends_clause),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_class_field),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_class_or_interface_type),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_class_or_interface_type_part),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_class_type_specification),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_compilation_unit),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_conditional_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_enum_body),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_enum_constant),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_enum_constant_body),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_enum_constant_field),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_enum_declaration),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_equality_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_equality_expression_rest),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_for_clause_traditional_rest),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_for_control),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_identifier),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_implements_clause),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_import_declaration),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_interface_body),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_interface_declaration),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_interface_extends_clause),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_interface_field),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_literal),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_logical_and_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_logical_or_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_mandatory_declarator_brackets),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_multiplicative_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_multiplicative_expression_rest),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_new_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_non_wildcard_type_arguments),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_optional_declarator_brackets),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_optional_modifiers),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_optional_parameter_modifiers),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_package_declaration),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_parameter_declaration),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_parameter_declaration_ellipsis),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_parameter_declaration_list),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_postfix_operator),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_primary_atom),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_primary_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_primary_selector),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_qualified_identifier),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_qualified_identifier_safe),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_qualified_identifier_with_optional_star),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_relational_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_relational_expression_rest),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_shift_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_shift_expression_rest),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_statement),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_super_suffix),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_switch_case),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_switch_statements_group),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_throws_clause),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_try_handler),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_type_argument),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_type_argument_specification),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_type_arguments),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_type_arguments_or_parameters_end),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_type_declaration),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_type_parameter),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_type_parameters),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_type_specification),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_type_specification_noarray),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_unary_expression),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_unary_expression_not_plusminus),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_variable_array_initializer),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_variable_declaration),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_variable_declaration_rest),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_variable_declarator),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_variable_initializer),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_wildcard_type),
      reinterpret_cast<parser_fun_t>(&java_visitor::visit_wildcard_type_bounds)
    }; // _S_parser_table[]

