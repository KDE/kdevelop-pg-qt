// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "fact.h"
#include <cassert>


assignment_statement_ast *fact::parse_assignment_statement()
{
  assignment_statement_ast *yynode = create<assignment_statement_ast>();

  yynode->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID)
    {
      require_token(yytoken, Token_ID);
      yynode->id = token_stream->index() - 1;
      yylex();
      require_token(yytoken, Token_EQUAL);
      yylex();
      require(yynode->expr = parse_expression(), fact_ast_node::Kind_expression);
      require_token(yytoken, Token_SEMICOLON);
      yylex();
    }

  else
    return 0;

  yynode->end_token = token_stream->index() - 1;

  return yynode;
}

block_statement_ast *fact::parse_block_statement()
{
  block_statement_ast *yynode = create<block_statement_ast>();

  yynode->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE)
    {
      require_token(yytoken, Token_LBRACE);
      yylex();

      while (yytoken == Token_ID
             || yytoken == Token_LBRACE
             || yytoken == Token_IF
             || yytoken == Token_RETURN)
        {
          {
            statement_ast *stmt;
            require(stmt = parse_statement(), fact_ast_node::Kind_statement);
            yynode->stmt_sequence = snoc(yynode->stmt_sequence, stmt, memory_pool);
          }

        }

      require_token(yytoken, Token_RBRACE);
      yylex();
    }

  else
    return 0;

  yynode->end_token = token_stream->index() - 1;

  return yynode;
}

body_ast *fact::parse_body()
{
  body_ast *yynode = create<body_ast>();

  yynode->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACE)
    {
      require_token(yytoken, Token_LBRACE);
      yylex();

      while (yytoken == Token_VAR)
        {
          {
            declaration_ast *decl;
            require(decl = parse_declaration(), fact_ast_node::Kind_declaration);
            yynode->decl_sequence = snoc(yynode->decl_sequence, decl, memory_pool);
          }

        }

      while (yytoken == Token_ID
             || yytoken == Token_LBRACE
             || yytoken == Token_IF
             || yytoken == Token_RETURN)
        {
          {
            statement_ast *stmt;
            require(stmt = parse_statement(), fact_ast_node::Kind_statement);
            yynode->stmt_sequence = snoc(yynode->stmt_sequence, stmt, memory_pool);
          }

        }

      require_token(yytoken, Token_RBRACE);
      yylex();
    }

  else
    return 0;

  yynode->end_token = token_stream->index() - 1;

  return yynode;
}

condition_ast *fact::parse_condition()
{
  condition_ast *yynode = create<condition_ast>();

  yynode->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID
      || yytoken == Token_NUMBER)
    {
      require(yynode->left_expr = parse_expression(), fact_ast_node::Kind_expression);
      require_token(yytoken, Token_EQUAL_EQUAL);
      yynode->op = token_stream->index() - 1;
      yylex();
      require(yynode->right_expr = parse_expression(), fact_ast_node::Kind_expression);
    }

  else
    return 0;

  yynode->end_token = token_stream->index() - 1;

  return yynode;
}

declaration_ast *fact::parse_declaration()
{
  declaration_ast *yynode = create<declaration_ast>();

  yynode->start_token = token_stream->index() - 1;

  if (yytoken == Token_VAR)
    {
      require_token(yytoken, Token_VAR);
      yylex();
      require(yynode->var = parse_variable(), fact_ast_node::Kind_variable);

      while (yytoken == Token_COMMA)
        {
          require_token(yytoken, Token_COMMA);
          yylex();
          require(yynode->var = parse_variable(), fact_ast_node::Kind_variable);
        }

      require_token(yytoken, Token_SEMICOLON);
      yylex();
    }

  else
    return 0;

  yynode->end_token = token_stream->index() - 1;

  return yynode;
}

expression_ast *fact::parse_expression()
{
  expression_ast *yynode = create<expression_ast>();

  yynode->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID
      || yytoken == Token_NUMBER)
    {
      require(yynode->left_expr = parse_mult_expression(), fact_ast_node::Kind_mult_expression);

      while (yytoken == Token_MINUS)
        {
          require_token(yytoken, Token_MINUS);
          yynode->op = token_stream->index() - 1;
          yylex();
          require(yynode->right_expr = parse_mult_expression(), fact_ast_node::Kind_mult_expression);
        }
    }

  else
    return 0;

  yynode->end_token = token_stream->index() - 1;

  return yynode;
}

function_definition_ast *fact::parse_function_definition()
{
  function_definition_ast *yynode = create<function_definition_ast>();

  yynode->start_token = token_stream->index() - 1;

  if (yytoken == Token_FUNCTION)
    {
      require_token(yytoken, Token_FUNCTION);
      yylex();
      require_token(yytoken, Token_ID);
      yynode->id = token_stream->index() - 1;
      yylex();
      require_token(yytoken, Token_LPAREN);
      yylex();

      if (yytoken == Token_ID)
        {
          {
            require_token(yytoken, Token_ID);
            yynode->param_sequence = snoc(yynode->param_sequence, token_stream->index() - 1, memory_pool);
            yylex();
          }

          while (yytoken == Token_COMMA)
            {
              require_token(yytoken, Token_COMMA);
              yylex();
              {
                require_token(yytoken, Token_ID);
                yynode->param_sequence = snoc(yynode->param_sequence, token_stream->index() - 1, memory_pool);
                yylex();
              }

            }
        }

      else if (true /*epsilon*/)
      {}

      require_token(yytoken, Token_RPAREN);

      yylex();
      require(yynode->body = parse_body(), fact_ast_node::Kind_body);
    }

  else
    return 0;

  yynode->end_token = token_stream->index() - 1;

  return yynode;
}

if_statement_ast *fact::parse_if_statement()
{
  if_statement_ast *yynode = create<if_statement_ast>();

  yynode->start_token = token_stream->index() - 1;

  if (yytoken == Token_IF)
    {
      require_token(yytoken, Token_IF);
      yylex();
      require_token(yytoken, Token_LPAREN);
      yylex();
      require(yynode->cond = parse_condition(), fact_ast_node::Kind_condition);
      require_token(yytoken, Token_RPAREN);
      yylex();
      require(yynode->stmt = parse_statement(), fact_ast_node::Kind_statement);

      if (yytoken == Token_ELSE)
        {
          require_token(yytoken, Token_ELSE);
          yylex();
          require(yynode->else_stmt = parse_statement(), fact_ast_node::Kind_statement);
        }

      else if (true /*epsilon*/)
      {}

    }
  else
    return 0;

  yynode->end_token = token_stream->index() - 1;

  return yynode;
}

mult_expression_ast *fact::parse_mult_expression()
{
  mult_expression_ast *yynode = create<mult_expression_ast>();

  yynode->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID
      || yytoken == Token_NUMBER)
    {
      require(yynode->left_expr = parse_primary(), fact_ast_node::Kind_primary);

      while (yytoken == Token_STAR)
        {
          require_token(yytoken, Token_STAR);
          yynode->op = token_stream->index() - 1;
          yylex();
          require(yynode->right_expr = parse_primary(), fact_ast_node::Kind_primary);
        }
    }

  else
    return 0;

  yynode->end_token = token_stream->index() - 1;

  return yynode;
}

primary_ast *fact::parse_primary()
{
  primary_ast *yynode = create<primary_ast>();

  yynode->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID
      || yytoken == Token_NUMBER)
    {
      if (yytoken == Token_NUMBER)
        {
          require_token(yytoken, Token_NUMBER);
          yynode->num = token_stream->index() - 1;
          yylex();
        }

      else if (yytoken == Token_ID)
        {
          require_token(yytoken, Token_ID);
          yynode->id = token_stream->index() - 1;
          yylex();

          if (yytoken == Token_LPAREN)
            {
              require_token(yytoken, Token_LPAREN);
              yylex();
              {
                expression_ast *arg;
                require(arg = parse_expression(), fact_ast_node::Kind_expression);
                yynode->arg_sequence = snoc(yynode->arg_sequence, arg, memory_pool);
              }

              while (yytoken == Token_COMMA)
                {
                  require_token(yytoken, Token_COMMA);
                  yylex();
                  {
                    expression_ast *arg;
                    require(arg = parse_expression(), fact_ast_node::Kind_expression);
                    yynode->arg_sequence = snoc(yynode->arg_sequence, arg, memory_pool);
                  }

                }

              require_token(yytoken, Token_RPAREN);
              yylex();
            }

          else if (true /*epsilon*/)
          {}

        }

    }
  else
    return 0;

  yynode->end_token = token_stream->index() - 1;

  return yynode;
}

program_ast *fact::parse_program()
{
  program_ast *yynode = create<program_ast>();

  yynode->start_token = token_stream->index() - 1;

  if (yytoken == Token_FUNCTION
      || yytoken == Token_EOF)
    {
      while (yytoken == Token_FUNCTION)
        {
          {
            function_definition_ast *fun;
            require(fun = parse_function_definition(), fact_ast_node::Kind_function_definition);
            yynode->fun_sequence = snoc(yynode->fun_sequence, fun, memory_pool);
          }

        }

      require_token(Token_EOF, yytoken);
    }

  else
    return 0;

  yynode->end_token = token_stream->index() - 1;

  return yynode;
}

return_statement_ast *fact::parse_return_statement()
                                        {
                                          return_statement_ast *yynode = create<return_statement_ast>();

                                          yynode->start_token = token_stream->index() - 1;

                                          if (yytoken == Token_RETURN)
                                            {
                                              require_token(yytoken, Token_RETURN);
                                              yylex();
                                              require(yynode->expr = parse_expression(), fact_ast_node::Kind_expression);
                                              require_token(yytoken, Token_SEMICOLON);
                                              yylex();
                                            }

                                          else
                                            return 0;

                                          yynode->end_token = token_stream->index() - 1;

                                          return yynode;
                                        }

                                        statement_ast *fact::parse_statement()
                                        {
                                          statement_ast *yynode = create<statement_ast>();

                                          yynode->start_token = token_stream->index() - 1;

                                          if (yytoken == Token_ID
                                              || yytoken == Token_LBRACE
                                              || yytoken == Token_IF
                                              || yytoken == Token_RETURN)
                                            {
                                              if (yytoken == Token_ID)
                                                {
                                                  require(yynode->assgn_stmt = parse_assignment_statement(), fact_ast_node::Kind_assignment_statement);
                                                }

                                              else if (yytoken == Token_IF)
                                                {
                                                  require(yynode->if_stmt = parse_if_statement(), fact_ast_node::Kind_if_statement);
                                                }

                                              else if (yytoken == Token_LBRACE)
                                                {
                                                  require(yynode->block_stmt = parse_block_statement(), fact_ast_node::Kind_block_statement);
                                                }

                                              else if (yytoken == Token_RETURN)
                                                {
                                                  require(yynode->ret_stmt = parse_return_statement(), fact_ast_node::Kind_return_statement);
                                                }
                                            }

                                          else
                                            return 0;

                                          yynode->end_token = token_stream->index() - 1;

                                          return yynode;
                                        }

                                        variable_ast *fact::parse_variable()
                                        {
                                          variable_ast *yynode = create<variable_ast>();

                                          yynode->start_token = token_stream->index() - 1;

                                          if (yytoken == Token_ID)
                                            {
                                              require_token(yytoken, Token_ID);
                                              yynode->id = token_stream->index() - 1;
                                              yylex();
                                            }

                                          else
                                            return 0;

                                          yynode->end_token = token_stream->index() - 1;

                                          return yynode;
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

