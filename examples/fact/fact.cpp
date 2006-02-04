// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "fact.h"


bool fact::parse_assignment_statement(assignment_statement_ast **yynode)
{
  *yynode = create<assignment_statement_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID)
    {
      if (yytoken != Token_ID)
        return yy_expected_token(yytoken, Token_ID, "ID");

      (*yynode)->id = token_stream->index() - 1;

      yylex();

      if (yytoken != Token_EQUAL)
        return yy_expected_token(yytoken, Token_EQUAL, "EQUAL");

      yylex();

      expression_ast *__node_0 = 0;

      if (!parse_expression(&__node_0))
        {
          return yy_expected_symbol(fact_ast_node::Kind_expression, "expression");
        }

      (*yynode)->expr = __node_0;

      if (yytoken != Token_SEMICOLON)
        return yy_expected_token(yytoken, Token_SEMICOLON, "SEMICOLON");

      yylex();
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool fact::parse_block_statement(block_statement_ast **yynode)
{
  *yynode = create<block_statement_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE)
    {
      if (yytoken != Token_LBRACE)
        return yy_expected_token(yytoken, Token_LBRACE, "LBRACE");

      yylex();

      while (yytoken == Token_ID
             || yytoken == Token_LBRACE
             || yytoken == Token_IF
             || yytoken == Token_RETURN)
        {
          statement_ast *__node_1 = 0;

          if (!parse_statement(&__node_1))
            {
              return yy_expected_symbol(fact_ast_node::Kind_statement, "statement");
            }

          (*yynode)->stmt_sequence = snoc((*yynode)->stmt_sequence, __node_1, memory_pool);
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

bool fact::parse_body(body_ast **yynode)
{
  *yynode = create<body_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE)
    {
      if (yytoken != Token_LBRACE)
        return yy_expected_token(yytoken, Token_LBRACE, "LBRACE");

      yylex();

      while (yytoken == Token_VAR)
        {
          declaration_ast *__node_2 = 0;

          if (!parse_declaration(&__node_2))
            {
              return yy_expected_symbol(fact_ast_node::Kind_declaration, "declaration");
            }

          (*yynode)->decl_sequence = snoc((*yynode)->decl_sequence, __node_2, memory_pool);
        }

      while (yytoken == Token_ID
             || yytoken == Token_LBRACE
             || yytoken == Token_IF
             || yytoken == Token_RETURN)
        {
          statement_ast *__node_3 = 0;

          if (!parse_statement(&__node_3))
            {
              return yy_expected_symbol(fact_ast_node::Kind_statement, "statement");
            }

          (*yynode)->stmt_sequence = snoc((*yynode)->stmt_sequence, __node_3, memory_pool);
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

bool fact::parse_condition(condition_ast **yynode)
{
  *yynode = create<condition_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID
      || yytoken == Token_NUMBER)
    {
      expression_ast *__node_4 = 0;

      if (!parse_expression(&__node_4))
        {
          return yy_expected_symbol(fact_ast_node::Kind_expression, "expression");
        }

      (*yynode)->left_expr = __node_4;

      if (yytoken != Token_EQUAL_EQUAL)
        return yy_expected_token(yytoken, Token_EQUAL_EQUAL, "EQUAL_EQUAL");

      (*yynode)->op = token_stream->index() - 1;

      yylex();

      expression_ast *__node_5 = 0;

      if (!parse_expression(&__node_5))
        {
          return yy_expected_symbol(fact_ast_node::Kind_expression, "expression");
        }

      (*yynode)->right_expr = __node_5;
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool fact::parse_declaration(declaration_ast **yynode)
{
  *yynode = create<declaration_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_VAR)
    {
      if (yytoken != Token_VAR)
        return yy_expected_token(yytoken, Token_VAR, "VAR");

      yylex();

      variable_ast *__node_6 = 0;

      if (!parse_variable(&__node_6))
        {
          return yy_expected_symbol(fact_ast_node::Kind_variable, "variable");
        }

      (*yynode)->var = __node_6;

      if (yytoken == Token_COMMA)
        {
          while (yytoken == Token_COMMA)
            {
              if (yytoken != Token_COMMA)
                return yy_expected_token(yytoken, Token_COMMA, "COMMA");

              yylex();

              variable_ast *__node_7 = 0;

              if (!parse_variable(&__node_7))
                {
                  return yy_expected_symbol(fact_ast_node::Kind_variable, "variable");
                }

              (*yynode)->var = __node_7;
            }
        }

      else if (true /*epsilon*/)
      {}
      else
        {
          return false;
        }

      if (yytoken != Token_SEMICOLON)
        return yy_expected_token(yytoken, Token_SEMICOLON, "SEMICOLON");

      yylex();
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool fact::parse_expression(expression_ast **yynode)
{
  *yynode = create<expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID
      || yytoken == Token_NUMBER)
    {
      mult_expression_ast *__node_8 = 0;

      if (!parse_mult_expression(&__node_8))
        {
          return yy_expected_symbol(fact_ast_node::Kind_mult_expression, "mult_expression");
        }

      (*yynode)->left_expr = __node_8;

      while (yytoken == Token_MINUS)
        {
          if (yytoken != Token_MINUS)
            return yy_expected_token(yytoken, Token_MINUS, "MINUS");

          (*yynode)->op = token_stream->index() - 1;

          yylex();

          mult_expression_ast *__node_9 = 0;

          if (!parse_mult_expression(&__node_9))
            {
              return yy_expected_symbol(fact_ast_node::Kind_mult_expression, "mult_expression");
            }

          (*yynode)->right_expr = __node_9;
        }
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool fact::parse_function_definition(function_definition_ast **yynode)
{
  *yynode = create<function_definition_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_FUNCTION)
    {
      if (yytoken != Token_FUNCTION)
        return yy_expected_token(yytoken, Token_FUNCTION, "FUNCTION");

      yylex();

      if (yytoken != Token_ID)
        return yy_expected_token(yytoken, Token_ID, "ID");

      (*yynode)->id = token_stream->index() - 1;

      yylex();

      if (yytoken != Token_LPAREN)
        return yy_expected_token(yytoken, Token_LPAREN, "LPAREN");

      yylex();

      if (yytoken == Token_ID)
        {
          if (yytoken != Token_ID)
            return yy_expected_token(yytoken, Token_ID, "ID");

          (*yynode)->param_sequence = snoc((*yynode)->param_sequence, token_stream->index() - 1, memory_pool);

          yylex();

          if (yytoken == Token_COMMA)
            {
              while (yytoken == Token_COMMA)
                {
                  if (yytoken != Token_COMMA)
                    return yy_expected_token(yytoken, Token_COMMA, "COMMA");

                  yylex();

                  if (yytoken != Token_ID)
                    return yy_expected_token(yytoken, Token_ID, "ID");

                  (*yynode)->param_sequence = snoc((*yynode)->param_sequence, token_stream->index() - 1, memory_pool);

                  yylex();
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

      body_ast *__node_10 = 0;

      if (!parse_body(&__node_10))
        {
          return yy_expected_symbol(fact_ast_node::Kind_body, "body");
        }

      (*yynode)->body = __node_10;
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool fact::parse_if_statement(if_statement_ast **yynode)
{
  *yynode = create<if_statement_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IF)
    {
      if (yytoken != Token_IF)
        return yy_expected_token(yytoken, Token_IF, "IF");

      yylex();

      if (yytoken != Token_LPAREN)
        return yy_expected_token(yytoken, Token_LPAREN, "LPAREN");

      yylex();

      condition_ast *__node_11 = 0;

      if (!parse_condition(&__node_11))
        {
          return yy_expected_symbol(fact_ast_node::Kind_condition, "condition");
        }

      (*yynode)->cond = __node_11;

      if (yytoken != Token_RPAREN)
        return yy_expected_token(yytoken, Token_RPAREN, "RPAREN");

      yylex();

      statement_ast *__node_12 = 0;

      if (!parse_statement(&__node_12))
        {
          return yy_expected_symbol(fact_ast_node::Kind_statement, "statement");
        }

      (*yynode)->stmt = __node_12;

      if (yytoken == Token_ELSE)
        {
          if (yytoken != Token_ELSE)
            return yy_expected_token(yytoken, Token_ELSE, "ELSE");

          yylex();

          statement_ast *__node_13 = 0;

          if (!parse_statement(&__node_13))
            {
              return yy_expected_symbol(fact_ast_node::Kind_statement, "statement");
            }

          (*yynode)->else_stmt = __node_13;
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

bool fact::parse_mult_expression(mult_expression_ast **yynode)
{
  *yynode = create<mult_expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID
      || yytoken == Token_NUMBER)
    {
      primary_ast *__node_14 = 0;

      if (!parse_primary(&__node_14))
        {
          return yy_expected_symbol(fact_ast_node::Kind_primary, "primary");
        }

      (*yynode)->left_expr = __node_14;

      while (yytoken == Token_STAR)
        {
          if (yytoken != Token_STAR)
            return yy_expected_token(yytoken, Token_STAR, "STAR");

          (*yynode)->op = token_stream->index() - 1;

          yylex();

          primary_ast *__node_15 = 0;

          if (!parse_primary(&__node_15))
            {
              return yy_expected_symbol(fact_ast_node::Kind_primary, "primary");
            }

          (*yynode)->right_expr = __node_15;
        }
    }

  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool fact::parse_primary(primary_ast **yynode)
{
  *yynode = create<primary_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID
      || yytoken == Token_NUMBER)
    {
      if (yytoken == Token_NUMBER)
        {
          if (yytoken != Token_NUMBER)
            return yy_expected_token(yytoken, Token_NUMBER, "NUMBER");

          (*yynode)->num = token_stream->index() - 1;

          yylex();
        }

      else if (yytoken == Token_ID)
        {
          if (yytoken != Token_ID)
            return yy_expected_token(yytoken, Token_ID, "ID");

          (*yynode)->id = token_stream->index() - 1;

          yylex();

          if (yytoken == Token_LPAREN)
            {
              if (yytoken != Token_LPAREN)
                return yy_expected_token(yytoken, Token_LPAREN, "LPAREN");

              yylex();

              expression_ast *__node_16 = 0;

              if (!parse_expression(&__node_16))
                {
                  return yy_expected_symbol(fact_ast_node::Kind_expression, "expression");
                }

              (*yynode)->arg_sequence = snoc((*yynode)->arg_sequence, __node_16, memory_pool);

              if (yytoken == Token_COMMA)
                {
                  while (yytoken == Token_COMMA)
                    {
                      if (yytoken != Token_COMMA)
                        return yy_expected_token(yytoken, Token_COMMA, "COMMA");

                      yylex();

                      expression_ast *__node_17 = 0;

                      if (!parse_expression(&__node_17))
                        {
                          return yy_expected_symbol(fact_ast_node::Kind_expression, "expression");
                        }

                      (*yynode)->arg_sequence = snoc((*yynode)->arg_sequence, __node_17, memory_pool);
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

bool fact::parse_program(program_ast **yynode)
{
  *yynode = create<program_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_FUNCTION)
    {
      while (yytoken == Token_FUNCTION)
        {
          function_definition_ast *__node_18 = 0;

          if (!parse_function_definition(&__node_18))
            {
              return yy_expected_symbol(fact_ast_node::Kind_function_definition, "function_definition");
            }

          (*yynode)->fun_sequence = snoc((*yynode)->fun_sequence, __node_18, memory_pool);
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

bool fact::parse_return_statement(return_statement_ast **yynode)
                       {
                         *yynode = create<return_statement_ast>();

                         (*yynode)->start_token = token_stream->index() - 1;

                         if (yytoken == Token_RETURN)
                           {
                             if (yytoken != Token_RETURN)
                               return yy_expected_token(yytoken, Token_RETURN, "RETURN");

                             yylex();

                             expression_ast *__node_19 = 0;

                             if (!parse_expression(&__node_19))
                               {
                                 return yy_expected_symbol(fact_ast_node::Kind_expression, "expression");
                               }

                             (*yynode)->expr = __node_19;

                             if (yytoken != Token_SEMICOLON)
                               return yy_expected_token(yytoken, Token_SEMICOLON, "SEMICOLON");

                             yylex();
                           }

                         else
                           {
                             return false;
                           }

                         (*yynode)->end_token = token_stream->index() - 1;

                         return true;
                       }

                       bool fact::parse_statement(statement_ast **yynode)
                       {
                         *yynode = create<statement_ast>();

                         (*yynode)->start_token = token_stream->index() - 1;

                         if (yytoken == Token_ID
                             || yytoken == Token_LBRACE
                             || yytoken == Token_IF
                             || yytoken == Token_RETURN)
                           {
                             if (yytoken == Token_ID)
                               {
                                 assignment_statement_ast *__node_20 = 0;

                                 if (!parse_assignment_statement(&__node_20))
                                   {
                                     return yy_expected_symbol(fact_ast_node::Kind_assignment_statement, "assignment_statement");
                                   }

                                 (*yynode)->assgn_stmt = __node_20;
                               }

                             else if (yytoken == Token_IF)
                               {
                                 if_statement_ast *__node_21 = 0;

                                 if (!parse_if_statement(&__node_21))
                                   {
                                     return yy_expected_symbol(fact_ast_node::Kind_if_statement, "if_statement");
                                   }

                                 (*yynode)->if_stmt = __node_21;
                               }

                             else if (yytoken == Token_LBRACE)
                               {
                                 block_statement_ast *__node_22 = 0;

                                 if (!parse_block_statement(&__node_22))
                                   {
                                     return yy_expected_symbol(fact_ast_node::Kind_block_statement, "block_statement");
                                   }

                                 (*yynode)->block_stmt = __node_22;
                               }

                             else if (yytoken == Token_RETURN)
                               {
                                 return_statement_ast *__node_23 = 0;

                                 if (!parse_return_statement(&__node_23))
                                   {
                                     return yy_expected_symbol(fact_ast_node::Kind_return_statement, "return_statement");
                                   }

                                 (*yynode)->ret_stmt = __node_23;
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

                       bool fact::parse_variable(variable_ast **yynode)
                       {
                         *yynode = create<variable_ast>();

                         (*yynode)->start_token = token_stream->index() - 1;

                         if (yytoken == Token_ID)
                           {
                             if (yytoken != Token_ID)
                               return yy_expected_token(yytoken, Token_ID, "ID");

                             (*yynode)->id = token_stream->index() - 1;

                             yylex();
                           }

                         else
                           {
                             return false;
                           }

                         (*yynode)->end_token = token_stream->index() - 1;

                         return true;
                       }

                       fact_visitor::parser_fun_t fact_visitor::_S_parser_table[] = {
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_assignment_statement),
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_block_statement),
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_body),
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_condition),
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_declaration),
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_expression),
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_function_definition),
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_if_statement),
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_mult_expression),
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_primary),
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_program),
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_return_statement),
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_statement),
                             reinterpret_cast<parser_fun_t>(&fact_visitor::visit_variable)
                           }; // _S_parser_table[]

