// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "cool.h"


bool cool::parse_additive_expression(additive_expression_ast **yynode)
{
  *yynode = create<additive_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE
      || yytoken == Token_ID
      || yytoken == Token_LPAREN
      || yytoken == Token_INTEGER
      || yytoken == Token_STRING
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NEW
      || yytoken == Token_TILDE
      || yytoken == Token_NOT
      || yytoken == Token_ISVOID
      || yytoken == Token_IF
      || yytoken == Token_WHILE
      || yytoken == Token_LET
      || yytoken == Token_CASE)
    {
      multiplicative_expression_ast *__node_0 = 0;

      if (!parse_multiplicative_expression(&__node_0))
        {
          return yy_expected_symbol(cool_ast_node::Kind_multiplicative_expression, "multiplicative_expression");
        }

      (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_0, memory_pool);

      if (yytoken == Token_PLUS
          || yytoken == Token_MINUS)
        {
          while (yytoken == Token_PLUS
                 || yytoken == Token_MINUS)
            {
              if (yytoken == Token_PLUS)
                {
                  if (yytoken != Token_PLUS)
                    return yy_expected_token(yytoken, Token_PLUS, "PLUS");

                  (*yynode)->op = token_stream->index() - 1;

                  yylex();
                }

              else if (yytoken == Token_MINUS)
                {
                  if (yytoken != Token_MINUS)
                    return yy_expected_token(yytoken, Token_MINUS, "MINUS");

                  (*yynode)->op = token_stream->index() - 1;

                  yylex();
                }

              else
                {
                  return false;
                }

              multiplicative_expression_ast *__node_1 = 0;

              if (!parse_multiplicative_expression(&__node_1))
                {
                  return yy_expected_symbol(cool_ast_node::Kind_multiplicative_expression, "multiplicative_expression");
                }

              (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_1, memory_pool);
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

bool cool::parse_block_expression(block_expression_ast **yynode)
{
  *yynode = create<block_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE)
    {
      if (yytoken != Token_LBRACE)
        return yy_expected_token(yytoken, Token_LBRACE, "LBRACE");

      yylex();

      while (yytoken == Token_LBRACE
             || yytoken == Token_ID
             || yytoken == Token_LPAREN
             || yytoken == Token_INTEGER
             || yytoken == Token_STRING
             || yytoken == Token_TRUE
             || yytoken == Token_FALSE
             || yytoken == Token_NEW
             || yytoken == Token_TILDE
             || yytoken == Token_NOT
             || yytoken == Token_ISVOID
             || yytoken == Token_IF
             || yytoken == Token_WHILE
             || yytoken == Token_LET
             || yytoken == Token_CASE)
        {
          expression_ast *__node_2 = 0;

          if (!parse_expression(&__node_2))
            {
              return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
            }

          (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_2, memory_pool);

          if (yytoken != Token_SEMICOLON)
            return yy_expected_token(yytoken, Token_SEMICOLON, "SEMICOLON");

          yylex();
        }

      if (yytoken != Token_RBRACE)
        return yy_expected_token(yytoken, Token_RBRACE, "RBRACE");

      yylex();
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool cool::parse_case_condition(case_condition_ast **yynode)
{
  *yynode = create<case_condition_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID)
    {
      if (yytoken != Token_ID)
        return yy_expected_token(yytoken, Token_ID, "ID");

      (*yynode)->name = token_stream->index() - 1;

      yylex();

      if (yytoken != Token_COLON)
        return yy_expected_token(yytoken, Token_COLON, "COLON");

      yylex();

      if (yytoken != Token_TYPE)
        return yy_expected_token(yytoken, Token_TYPE, "TYPE");

      (*yynode)->type = token_stream->index() - 1;

      yylex();

      if (yytoken != Token_RIGHT_ARROW)
        return yy_expected_token(yytoken, Token_RIGHT_ARROW, "RIGHT_ARROW");

      yylex();

      expression_ast *__node_3 = 0;

      if (!parse_expression(&__node_3))
        {
          return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
        }

      (*yynode)->expression = __node_3;
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool cool::parse_case_expression(case_expression_ast **yynode)
{
  *yynode = create<case_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_CASE)
    {
      if (yytoken != Token_CASE)
        return yy_expected_token(yytoken, Token_CASE, "CASE");

      yylex();

      expression_ast *__node_4 = 0;

      if (!parse_expression(&__node_4))
        {
          return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
        }

      (*yynode)->expression = __node_4;

      if (yytoken != Token_OF)
        return yy_expected_token(yytoken, Token_OF, "OF");

      yylex();

      while (yytoken == Token_ID)
        {
          case_condition_ast *__node_5 = 0;

          if (!parse_case_condition(&__node_5))
            {
              return yy_expected_symbol(cool_ast_node::Kind_case_condition, "case_condition");
            }

          (*yynode)->condition_sequence = snoc((*yynode)->condition_sequence, __node_5, memory_pool);

          if (yytoken != Token_SEMICOLON)
            return yy_expected_token(yytoken, Token_SEMICOLON, "SEMICOLON");

          yylex();
        }

      if (yytoken != Token_ESAC)
        return yy_expected_token(yytoken, Token_ESAC, "ESAC");

      yylex();
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool cool::parse_class(class_ast **yynode)
{
  *yynode = create<class_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_CLASS)
    {
      if (yytoken != Token_CLASS)
        return yy_expected_token(yytoken, Token_CLASS, "CLASS");

      yylex();

      if (yytoken != Token_TYPE)
        return yy_expected_token(yytoken, Token_TYPE, "TYPE");

      (*yynode)->type = token_stream->index() - 1;

      yylex();

      if (yytoken == Token_INHERITS)
        {
          if (yytoken != Token_INHERITS)
            return yy_expected_token(yytoken, Token_INHERITS, "INHERITS");

          yylex();

          if (yytoken != Token_TYPE)
            return yy_expected_token(yytoken, Token_TYPE, "TYPE");

          (*yynode)->base_type = token_stream->index() - 1;

          yylex();
        }

      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }

      if (yytoken != Token_LBRACE)
        return yy_expected_token(yytoken, Token_LBRACE, "LBRACE");

      yylex();

      while (yytoken == Token_ID)
        {
          feature_ast *__node_6 = 0;

          if (!parse_feature(&__node_6))
            {
              return yy_expected_symbol(cool_ast_node::Kind_feature, "feature");
            }

          (*yynode)->feature_sequence = snoc((*yynode)->feature_sequence, __node_6, memory_pool);

          if (yytoken != Token_SEMICOLON)
            return yy_expected_token(yytoken, Token_SEMICOLON, "SEMICOLON");

          yylex();
        }

      if (yytoken != Token_RBRACE)
        return yy_expected_token(yytoken, Token_RBRACE, "RBRACE");

      yylex();
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool cool::parse_expression(expression_ast **yynode)
{
  *yynode = create<expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE
      || yytoken == Token_ID
      || yytoken == Token_LPAREN
      || yytoken == Token_INTEGER
      || yytoken == Token_STRING
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NEW
      || yytoken == Token_TILDE
      || yytoken == Token_NOT
      || yytoken == Token_ISVOID
      || yytoken == Token_IF
      || yytoken == Token_WHILE
      || yytoken == Token_LET
      || yytoken == Token_CASE)
    {
      relational_expression_ast *__node_7 = 0;

      if (!parse_relational_expression(&__node_7))
        {
          return yy_expected_symbol(cool_ast_node::Kind_relational_expression, "relational_expression");
        }

      (*yynode)->expression = __node_7;
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool cool::parse_feature(feature_ast **yynode)
{
  *yynode = create<feature_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID)
    {
      if (( LA(2).kind == Token_LPAREN ) && (yytoken == Token_ID))
        {
          if (yytoken != Token_ID)
            return yy_expected_token(yytoken, Token_ID, "ID");

          (*yynode)->name = token_stream->index() - 1;

          yylex();

          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "LPAREN");

          yylex();

          if (yytoken == Token_ID)
            {
              formal_ast *__node_8 = 0;

              if (!parse_formal(&__node_8))
                {
                  return yy_expected_symbol(cool_ast_node::Kind_formal, "formal");
                }

              (*yynode)->formal_sequence = snoc((*yynode)->formal_sequence, __node_8, memory_pool);

              if (yytoken == Token_COMMA)
                {
                  while (yytoken == Token_COMMA)
                    {
                      if (yytoken != Token_COMMA)
                        return yy_expected_token(yytoken, Token_COMMA, "COMMA");

                      yylex();

                      formal_ast *__node_9 = 0;

                      if (!parse_formal(&__node_9))
                        {
                          return yy_expected_symbol(cool_ast_node::Kind_formal, "formal");
                        }

                      (*yynode)->formal_sequence = snoc((*yynode)->formal_sequence, __node_9, memory_pool);
                    }
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

          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, "RPAREN");

          yylex();

          if (yytoken != Token_COLON)
            return yy_expected_token(yytoken, Token_COLON, "COLON");

          yylex();

          if (yytoken != Token_TYPE)
            return yy_expected_token(yytoken, Token_TYPE, "TYPE");

          (*yynode)->type = token_stream->index() - 1;

          yylex();

          if (yytoken != Token_LBRACE)
            return yy_expected_token(yytoken, Token_LBRACE, "LBRACE");

          yylex();

          expression_ast *__node_10 = 0;

          if (!parse_expression(&__node_10))
            {
              return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
            }

          (*yynode)->expression = __node_10;

          if (yytoken != Token_RBRACE)
            return yy_expected_token(yytoken, Token_RBRACE, "RBRACE");

          yylex();
        }

      else if (( LA(2).kind == Token_COLON ) && (yytoken == Token_ID))
        {
          if (yytoken != Token_ID)
            return yy_expected_token(yytoken, Token_ID, "ID");

          (*yynode)->name = token_stream->index() - 1;

          yylex();

          if (yytoken != Token_COLON)
            return yy_expected_token(yytoken, Token_COLON, "COLON");

          yylex();

          if (yytoken != Token_TYPE)
            return yy_expected_token(yytoken, Token_TYPE, "TYPE");

          (*yynode)->type = token_stream->index() - 1;

          yylex();

          if (yytoken == Token_LEFT_ARROW)
            {
              if (yytoken != Token_LEFT_ARROW)
                return yy_expected_token(yytoken, Token_LEFT_ARROW, "LEFT_ARROW");

              yylex();

              expression_ast *__node_11 = 0;

              if (!parse_expression(&__node_11))
                {
                  return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
                }

              (*yynode)->expression = __node_11;
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

bool cool::parse_formal(formal_ast **yynode)
{
  *yynode = create<formal_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID)
    {
      if (yytoken != Token_ID)
        return yy_expected_token(yytoken, Token_ID, "ID");

      (*yynode)->name = token_stream->index() - 1;

      yylex();

      if (yytoken != Token_COLON)
        return yy_expected_token(yytoken, Token_COLON, "COLON");

      yylex();

      if (yytoken != Token_TYPE)
        return yy_expected_token(yytoken, Token_TYPE, "TYPE");

      (*yynode)->type = token_stream->index() - 1;

      yylex();
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool cool::parse_if_expression(if_expression_ast **yynode)
{
  *yynode = create<if_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IF)
    {
      if (yytoken != Token_IF)
        return yy_expected_token(yytoken, Token_IF, "IF");

      yylex();

      expression_ast *__node_12 = 0;

      if (!parse_expression(&__node_12))
        {
          return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
        }

      (*yynode)->condition = __node_12;

      if (yytoken != Token_THEN)
        return yy_expected_token(yytoken, Token_THEN, "THEN");

      yylex();

      expression_ast *__node_13 = 0;

      if (!parse_expression(&__node_13))
        {
          return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
        }

      (*yynode)->true_expression = __node_13;

      if (yytoken != Token_ELSE)
        return yy_expected_token(yytoken, Token_ELSE, "ELSE");

      yylex();

      expression_ast *__node_14 = 0;

      if (!parse_expression(&__node_14))
        {
          return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
        }

      (*yynode)->false_expression = __node_14;

      if (yytoken != Token_FI)
        return yy_expected_token(yytoken, Token_FI, "FI");

      yylex();
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool cool::parse_let_declaration(let_declaration_ast **yynode)
{
  *yynode = create<let_declaration_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID)
    {
      if (yytoken != Token_ID)
        return yy_expected_token(yytoken, Token_ID, "ID");

      (*yynode)->name = token_stream->index() - 1;

      yylex();

      if (yytoken != Token_COLON)
        return yy_expected_token(yytoken, Token_COLON, "COLON");

      yylex();

      if (yytoken != Token_TYPE)
        return yy_expected_token(yytoken, Token_TYPE, "TYPE");

      (*yynode)->type = token_stream->index() - 1;

      yylex();

      if (yytoken == Token_LEFT_ARROW)
        {
          if (yytoken != Token_LEFT_ARROW)
            return yy_expected_token(yytoken, Token_LEFT_ARROW, "LEFT_ARROW");

          yylex();

          expression_ast *__node_15 = 0;

          if (!parse_expression(&__node_15))
            {
              return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
            }

          (*yynode)->expression = __node_15;
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

bool cool::parse_let_expression(let_expression_ast **yynode)
{
  *yynode = create<let_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LET)
    {
      if (yytoken != Token_LET)
        return yy_expected_token(yytoken, Token_LET, "LET");

      yylex();

      let_declaration_ast *__node_16 = 0;

      if (!parse_let_declaration(&__node_16))
        {
          return yy_expected_symbol(cool_ast_node::Kind_let_declaration, "let_declaration");
        }

      (*yynode)->declaration_sequence = snoc((*yynode)->declaration_sequence, __node_16, memory_pool);

      if (yytoken == Token_COMMA)
        {
          while (yytoken == Token_COMMA)
            {
              if (yytoken != Token_COMMA)
                return yy_expected_token(yytoken, Token_COMMA, "COMMA");

              yylex();

              let_declaration_ast *__node_17 = 0;

              if (!parse_let_declaration(&__node_17))
                {
                  return yy_expected_symbol(cool_ast_node::Kind_let_declaration, "let_declaration");
                }

              (*yynode)->declaration_sequence = snoc((*yynode)->declaration_sequence, __node_17, memory_pool);
            }
        }

      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }

      if (yytoken != Token_IN)
        return yy_expected_token(yytoken, Token_IN, "IN");

      yylex();

      expression_ast *__node_18 = 0;

      if (!parse_expression(&__node_18))
        {
          return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
        }

      (*yynode)->body_expression = __node_18;
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool cool::parse_multiplicative_expression(multiplicative_expression_ast **yynode)
{
  *yynode = create<multiplicative_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE
      || yytoken == Token_ID
      || yytoken == Token_LPAREN
      || yytoken == Token_INTEGER
      || yytoken == Token_STRING
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NEW
      || yytoken == Token_TILDE
      || yytoken == Token_NOT
      || yytoken == Token_ISVOID
      || yytoken == Token_IF
      || yytoken == Token_WHILE
      || yytoken == Token_LET
      || yytoken == Token_CASE)
    {
      postfix_expression_ast *__node_19 = 0;

      if (!parse_postfix_expression(&__node_19))
        {
          return yy_expected_symbol(cool_ast_node::Kind_postfix_expression, "postfix_expression");
        }

      (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_19, memory_pool);

      if (yytoken == Token_STAR
          || yytoken == Token_DIVIDE)
        {
          while (yytoken == Token_STAR
                 || yytoken == Token_DIVIDE)
            {
              if (yytoken == Token_STAR)
                {
                  if (yytoken != Token_STAR)
                    return yy_expected_token(yytoken, Token_STAR, "STAR");

                  (*yynode)->op = token_stream->index() - 1;

                  yylex();
                }

              else if (yytoken == Token_DIVIDE)
                {
                  if (yytoken != Token_DIVIDE)
                    return yy_expected_token(yytoken, Token_DIVIDE, "DIVIDE");

                  (*yynode)->op = token_stream->index() - 1;

                  yylex();
                }

              else
                {
                  return false;
                }

              postfix_expression_ast *__node_20 = 0;

              if (!parse_postfix_expression(&__node_20))
                {
                  return yy_expected_symbol(cool_ast_node::Kind_postfix_expression, "postfix_expression");
                }

              (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_20, memory_pool);
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

bool cool::parse_postfix_expression(postfix_expression_ast **yynode)
{
  *yynode = create<postfix_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE
      || yytoken == Token_ID
      || yytoken == Token_LPAREN
      || yytoken == Token_INTEGER
      || yytoken == Token_STRING
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NEW
      || yytoken == Token_TILDE
      || yytoken == Token_NOT
      || yytoken == Token_ISVOID
      || yytoken == Token_IF
      || yytoken == Token_WHILE
      || yytoken == Token_LET
      || yytoken == Token_CASE)
    {
      unary_expression_ast *__node_21 = 0;

      if (!parse_unary_expression(&__node_21))
        {
          return yy_expected_symbol(cool_ast_node::Kind_unary_expression, "unary_expression");
        }

      (*yynode)->base_expression = __node_21;

      while (yytoken == Token_AT
             || yytoken == Token_DOT)
        {
          if (yytoken == Token_AT)
            {
              if (yytoken != Token_AT)
                return yy_expected_token(yytoken, Token_AT, "AT");

              yylex();

              if (yytoken != Token_TYPE)
                return yy_expected_token(yytoken, Token_TYPE, "TYPE");

              (*yynode)->at_type = token_stream->index() - 1;

              yylex();

              if (yytoken != Token_DOT)
                return yy_expected_token(yytoken, Token_DOT, "DOT");

              yylex();

              if (yytoken != Token_ID)
                return yy_expected_token(yytoken, Token_ID, "ID");

              (*yynode)->name = token_stream->index() - 1;

              yylex();

              if (yytoken != Token_LPAREN)
                return yy_expected_token(yytoken, Token_LPAREN, "LPAREN");

              yylex();

              if (yytoken == Token_LBRACE
                  || yytoken == Token_ID
                  || yytoken == Token_LPAREN
                  || yytoken == Token_INTEGER
                  || yytoken == Token_STRING
                  || yytoken == Token_TRUE
                  || yytoken == Token_FALSE
                  || yytoken == Token_NEW
                  || yytoken == Token_TILDE
                  || yytoken == Token_NOT
                  || yytoken == Token_ISVOID
                  || yytoken == Token_IF
                  || yytoken == Token_WHILE
                  || yytoken == Token_LET
                  || yytoken == Token_CASE)
                {
                  expression_ast *__node_22 = 0;

                  if (!parse_expression(&__node_22))
                    {
                      return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
                    }

                  (*yynode)->arguments_sequence = snoc((*yynode)->arguments_sequence, __node_22, memory_pool);

                  if (yytoken == Token_COMMA)
                    {
                      while (yytoken == Token_COMMA)
                        {
                          if (yytoken != Token_COMMA)
                            return yy_expected_token(yytoken, Token_COMMA, "COMMA");

                          yylex();

                          expression_ast *__node_23 = 0;

                          if (!parse_expression(&__node_23))
                            {
                              return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
                            }

                          (*yynode)->arguments_sequence = snoc((*yynode)->arguments_sequence, __node_23, memory_pool);
                        }
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

              if (yytoken != Token_RPAREN)
                return yy_expected_token(yytoken, Token_RPAREN, "RPAREN");

              yylex();
            }

          else if (yytoken == Token_DOT)
            {
              if (yytoken != Token_DOT)
                return yy_expected_token(yytoken, Token_DOT, "DOT");

              yylex();

              if (yytoken != Token_ID)
                return yy_expected_token(yytoken, Token_ID, "ID");

              (*yynode)->name = token_stream->index() - 1;

              yylex();

              if (yytoken != Token_LPAREN)
                return yy_expected_token(yytoken, Token_LPAREN, "LPAREN");

              yylex();

              if (yytoken == Token_LBRACE
                  || yytoken == Token_ID
                  || yytoken == Token_LPAREN
                  || yytoken == Token_INTEGER
                  || yytoken == Token_STRING
                  || yytoken == Token_TRUE
                  || yytoken == Token_FALSE
                  || yytoken == Token_NEW
                  || yytoken == Token_TILDE
                  || yytoken == Token_NOT
                  || yytoken == Token_ISVOID
                  || yytoken == Token_IF
                  || yytoken == Token_WHILE
                  || yytoken == Token_LET
                  || yytoken == Token_CASE)
                {
                  expression_ast *__node_24 = 0;

                  if (!parse_expression(&__node_24))
                    {
                      return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
                    }

                  (*yynode)->arguments_sequence = snoc((*yynode)->arguments_sequence, __node_24, memory_pool);

                  if (yytoken == Token_COMMA)
                    {
                      while (yytoken == Token_COMMA)
                        {
                          if (yytoken != Token_COMMA)
                            return yy_expected_token(yytoken, Token_COMMA, "COMMA");

                          yylex();

                          expression_ast *__node_25 = 0;

                          if (!parse_expression(&__node_25))
                            {
                              return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
                            }

                          (*yynode)->arguments_sequence = snoc((*yynode)->arguments_sequence, __node_25, memory_pool);
                        }
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

              if (yytoken != Token_RPAREN)
                return yy_expected_token(yytoken, Token_RPAREN, "RPAREN");

              yylex();
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

bool cool::parse_primary_expression(primary_expression_ast **yynode)
{
  *yynode = create<primary_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE
      || yytoken == Token_ID
      || yytoken == Token_LPAREN
      || yytoken == Token_INTEGER
      || yytoken == Token_STRING
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NEW
      || yytoken == Token_IF
      || yytoken == Token_WHILE
      || yytoken == Token_LET
      || yytoken == Token_CASE)
    {
      if (( LA(2).kind == Token_LEFT_ARROW ) && (yytoken == Token_ID))
        {
          if (yytoken != Token_ID)
            return yy_expected_token(yytoken, Token_ID, "ID");

          (*yynode)->name = token_stream->index() - 1;

          yylex();

          if (yytoken != Token_LEFT_ARROW)
            return yy_expected_token(yytoken, Token_LEFT_ARROW, "LEFT_ARROW");

          yylex();

          expression_ast *__node_26 = 0;

          if (!parse_expression(&__node_26))
            {
              return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
            }

          (*yynode)->expression = __node_26;
        }

      else if (( LA(2).kind == Token_LPAREN ) && (yytoken == Token_ID))
        {
          if (yytoken != Token_ID)
            return yy_expected_token(yytoken, Token_ID, "ID");

          (*yynode)->name = token_stream->index() - 1;

          yylex();

          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "LPAREN");

          yylex();

          if (yytoken == Token_LBRACE
              || yytoken == Token_ID
              || yytoken == Token_LPAREN
              || yytoken == Token_INTEGER
              || yytoken == Token_STRING
              || yytoken == Token_TRUE
              || yytoken == Token_FALSE
              || yytoken == Token_NEW
              || yytoken == Token_TILDE
              || yytoken == Token_NOT
              || yytoken == Token_ISVOID
              || yytoken == Token_IF
              || yytoken == Token_WHILE
              || yytoken == Token_LET
              || yytoken == Token_CASE)
            {
              expression_ast *__node_27 = 0;

              if (!parse_expression(&__node_27))
                {
                  return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
                }

              (*yynode)->argument_sequence = snoc((*yynode)->argument_sequence, __node_27, memory_pool);

              if (yytoken == Token_COMMA)
                {
                  while (yytoken == Token_COMMA)
                    {
                      if (yytoken != Token_COMMA)
                        return yy_expected_token(yytoken, Token_COMMA, "COMMA");

                      yylex();

                      expression_ast *__node_28 = 0;

                      if (!parse_expression(&__node_28))
                        {
                          return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
                        }

                      (*yynode)->argument_sequence = snoc((*yynode)->argument_sequence, __node_28, memory_pool);
                    }
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

          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, "RPAREN");

          yylex();
        }

      else if (yytoken == Token_ID)
        {
          if (yytoken != Token_ID)
            return yy_expected_token(yytoken, Token_ID, "ID");

          (*yynode)->variable = token_stream->index() - 1;

          yylex();
        }

      else if (yytoken == Token_INTEGER)
        {
          if (yytoken != Token_INTEGER)
            return yy_expected_token(yytoken, Token_INTEGER, "INTEGER");

          (*yynode)->integer_literal = token_stream->index() - 1;

          yylex();
        }

      else if (yytoken == Token_STRING)
        {
          if (yytoken != Token_STRING)
            return yy_expected_token(yytoken, Token_STRING, "STRING");

          (*yynode)->string_literal = token_stream->index() - 1;

          yylex();
        }

      else if (yytoken == Token_TRUE)
        {
          if (yytoken != Token_TRUE)
            return yy_expected_token(yytoken, Token_TRUE, "TRUE");

          (*yynode)->true_literal = token_stream->index() - 1;

          yylex();
        }

      else if (yytoken == Token_FALSE)
        {
          if (yytoken != Token_FALSE)
            return yy_expected_token(yytoken, Token_FALSE, "FALSE");

          (*yynode)->false_literal = token_stream->index() - 1;

          yylex();
        }

      else if (yytoken == Token_NEW)
        {
          if (yytoken != Token_NEW)
            return yy_expected_token(yytoken, Token_NEW, "NEW");

          yylex();

          if (yytoken != Token_TYPE)
            return yy_expected_token(yytoken, Token_TYPE, "TYPE");

          (*yynode)->new_type = token_stream->index() - 1;

          yylex();
        }

      else if (yytoken == Token_LPAREN)
        {
          if (yytoken != Token_LPAREN)
            return yy_expected_token(yytoken, Token_LPAREN, "LPAREN");

          yylex();

          expression_ast *__node_29 = 0;

          if (!parse_expression(&__node_29))
            {
              return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
            }

          (*yynode)->expression = __node_29;

          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, "RPAREN");

          yylex();
        }

      else if (yytoken == Token_IF)
        {
          if_expression_ast *__node_30 = 0;

          if (!parse_if_expression(&__node_30))
            {
              return yy_expected_symbol(cool_ast_node::Kind_if_expression, "if_expression");
            }

          (*yynode)->if_expression = __node_30;
        }

      else if (yytoken == Token_WHILE)
        {
          while_expression_ast *__node_31 = 0;

          if (!parse_while_expression(&__node_31))
            {
              return yy_expected_symbol(cool_ast_node::Kind_while_expression, "while_expression");
            }

          (*yynode)->while_expression = __node_31;
        }

      else if (yytoken == Token_LBRACE)
        {
          block_expression_ast *__node_32 = 0;

          if (!parse_block_expression(&__node_32))
            {
              return yy_expected_symbol(cool_ast_node::Kind_block_expression, "block_expression");
            }

          (*yynode)->block_expression = __node_32;
        }

      else if (yytoken == Token_LET)
        {
          let_expression_ast *__node_33 = 0;

          if (!parse_let_expression(&__node_33))
            {
              return yy_expected_symbol(cool_ast_node::Kind_let_expression, "let_expression");
            }

          (*yynode)->let_expression = __node_33;
        }

      else if (yytoken == Token_CASE)
        {
          case_expression_ast *__node_34 = 0;

          if (!parse_case_expression(&__node_34))
            {
              return yy_expected_symbol(cool_ast_node::Kind_case_expression, "case_expression");
            }

          (*yynode)->case_expression = __node_34;
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

bool cool::parse_program(program_ast **yynode)
{
  *yynode = create<program_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_CLASS)
    {
      while (yytoken == Token_CLASS)
        {
          class_ast *__node_35 = 0;

          if (!parse_class(&__node_35))
            {
              return yy_expected_symbol(cool_ast_node::Kind_class, "class");
            }

          (*yynode)->klass_sequence = snoc((*yynode)->klass_sequence, __node_35, memory_pool);

          if (yytoken != Token_SEMICOLON)
            return yy_expected_token(yytoken, Token_SEMICOLON, "SEMICOLON");

          yylex();
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

bool cool::parse_relational_expression(relational_expression_ast **yynode)
{
  *yynode = create<relational_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE
      || yytoken == Token_ID
      || yytoken == Token_LPAREN
      || yytoken == Token_INTEGER
      || yytoken == Token_STRING
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NEW
      || yytoken == Token_TILDE
      || yytoken == Token_NOT
      || yytoken == Token_ISVOID
      || yytoken == Token_IF
      || yytoken == Token_WHILE
      || yytoken == Token_LET
      || yytoken == Token_CASE)
    {
      additive_expression_ast *__node_36 = 0;

      if (!parse_additive_expression(&__node_36))
        {
          return yy_expected_symbol(cool_ast_node::Kind_additive_expression, "additive_expression");
        }

      (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_36, memory_pool);

      if (yytoken == Token_EQUAL
          || yytoken == Token_LESS_EQUAL
          || yytoken == Token_LESS)
        {
          while (yytoken == Token_EQUAL
                 || yytoken == Token_LESS_EQUAL
                 || yytoken == Token_LESS)
            {
              if (yytoken == Token_EQUAL)
                {
                  if (yytoken != Token_EQUAL)
                    return yy_expected_token(yytoken, Token_EQUAL, "EQUAL");

                  (*yynode)->op = token_stream->index() - 1;

                  yylex();
                }

              else if (yytoken == Token_LESS_EQUAL)
                {
                  if (yytoken != Token_LESS_EQUAL)
                    return yy_expected_token(yytoken, Token_LESS_EQUAL, "LESS_EQUAL");

                  (*yynode)->op = token_stream->index() - 1;

                  yylex();
                }

              else if (yytoken == Token_LESS)
                {
                  if (yytoken != Token_LESS)
                    return yy_expected_token(yytoken, Token_LESS, "LESS");

                  (*yynode)->op = token_stream->index() - 1;

                  yylex();
                }

              else
                {
                  return false;
                }

              additive_expression_ast *__node_37 = 0;

              if (!parse_additive_expression(&__node_37))
                {
                  return yy_expected_symbol(cool_ast_node::Kind_additive_expression, "additive_expression");
                }

              (*yynode)->expression_sequence = snoc((*yynode)->expression_sequence, __node_37, memory_pool);
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

bool cool::parse_unary_expression(unary_expression_ast **yynode)
{
  *yynode = create<unary_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE
      || yytoken == Token_ID
      || yytoken == Token_LPAREN
      || yytoken == Token_INTEGER
      || yytoken == Token_STRING
      || yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NEW
      || yytoken == Token_TILDE
      || yytoken == Token_NOT
      || yytoken == Token_ISVOID
      || yytoken == Token_IF
      || yytoken == Token_WHILE
      || yytoken == Token_LET
      || yytoken == Token_CASE)
    {
      if (yytoken == Token_TILDE)
        {
          if (yytoken != Token_TILDE)
            return yy_expected_token(yytoken, Token_TILDE, "TILDE");

          (*yynode)->op = token_stream->index() - 1;

          yylex();

          primary_expression_ast *__node_38 = 0;

          if (!parse_primary_expression(&__node_38))
            {
              return yy_expected_symbol(cool_ast_node::Kind_primary_expression, "primary_expression");
            }

          (*yynode)->expression = __node_38;
        }

      else if (yytoken == Token_NOT)
        {
          if (yytoken != Token_NOT)
            return yy_expected_token(yytoken, Token_NOT, "NOT");

          (*yynode)->op = token_stream->index() - 1;

          yylex();

          primary_expression_ast *__node_39 = 0;

          if (!parse_primary_expression(&__node_39))
            {
              return yy_expected_symbol(cool_ast_node::Kind_primary_expression, "primary_expression");
            }

          (*yynode)->expression = __node_39;
        }

      else if (yytoken == Token_ISVOID)
        {
          if (yytoken != Token_ISVOID)
            return yy_expected_token(yytoken, Token_ISVOID, "ISVOID");

          (*yynode)->op = token_stream->index() - 1;

          yylex();

          primary_expression_ast *__node_40 = 0;

          if (!parse_primary_expression(&__node_40))
            {
              return yy_expected_symbol(cool_ast_node::Kind_primary_expression, "primary_expression");
            }

          (*yynode)->expression = __node_40;
        }

      else if (yytoken == Token_LBRACE
               || yytoken == Token_ID
               || yytoken == Token_LPAREN
               || yytoken == Token_INTEGER
               || yytoken == Token_STRING
               || yytoken == Token_TRUE
               || yytoken == Token_FALSE
               || yytoken == Token_NEW
               || yytoken == Token_IF
               || yytoken == Token_WHILE
               || yytoken == Token_LET
               || yytoken == Token_CASE)
        {
          primary_expression_ast *__node_41 = 0;

          if (!parse_primary_expression(&__node_41))
            {
              return yy_expected_symbol(cool_ast_node::Kind_primary_expression, "primary_expression");
            }

          (*yynode)->expression = __node_41;
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

bool cool::parse_while_expression(while_expression_ast **yynode)
{
  *yynode = create<while_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_WHILE)
    {
      if (yytoken != Token_WHILE)
        return yy_expected_token(yytoken, Token_WHILE, "WHILE");

      yylex();

      expression_ast *__node_42 = 0;

      if (!parse_expression(&__node_42))
        {
          return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
        }

      (*yynode)->condition = __node_42;

      if (yytoken != Token_LOOP)
        return yy_expected_token(yytoken, Token_LOOP, "LOOP");

      yylex();

      expression_ast *__node_43 = 0;

      if (!parse_expression(&__node_43))
        {
          return yy_expected_symbol(cool_ast_node::Kind_expression, "expression");
        }

      (*yynode)->loop_expression = __node_43;

      if (yytoken != Token_POOL)
        return yy_expected_token(yytoken, Token_POOL, "POOL");

      yylex();
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

cool_visitor::parser_fun_t cool_visitor::_S_parser_table[] = {
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_additive_expression),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_block_expression),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_case_condition),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_case_expression),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_class),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_expression),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_feature),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_formal),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_if_expression),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_let_declaration),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_let_expression),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_multiplicative_expression),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_postfix_expression),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_primary_expression),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_program),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_relational_expression),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_unary_expression),
      reinterpret_cast<parser_fun_t>(&cool_visitor::visit_while_expression)
    }; // _S_parser_table[]

