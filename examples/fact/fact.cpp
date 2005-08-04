// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "fact.h"
#include <cassert>


bool fact::parse_assignment_statement(assignment_statement_ast **yynode)
{
  *yynode = create<assignment_statement_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_ID)
    {
      if (yytoken != Token_ID)
        return false;
      (*yynode)->id = token_stream->index() - 1;
      yylex();
      if (yytoken != Token_EQUAL)
        return false;
      yylex();
      expression_ast *__node_0 = 0;
      if (!parse_expression(&__node_0))
        return false;
      if (yytoken != Token_SEMICOLON)
        return false;
      yylex();
    }
  else
    return false;

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
        return false;
      yylex();
      while (yytoken == Token_ID
             || yytoken == Token_LBRACE
             || yytoken == Token_IF
             || yytoken == Token_RETURN)
        {
          {
            statement_ast *__node_1 = 0;
            if (!parse_statement(&__node_1))
              return false;
            (*yynode)->stmt_sequence = snoc((*yynode)->stmt_sequence, __node_1, memory_pool);
          }

        }
      if (yytoken != Token_RBRACE)
        return false;
      yylex();
    }
  else
    return false;

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
        return false;
      yylex();
      while (yytoken == Token_VAR)
        {
          {
            declaration_ast *__node_2 = 0;
            if (!parse_declaration(&__node_2))
              return false;
            (*yynode)->decl_sequence = snoc((*yynode)->decl_sequence, __node_2, memory_pool);
          }

        }
      while (yytoken == Token_ID
             || yytoken == Token_LBRACE
             || yytoken == Token_IF
             || yytoken == Token_RETURN)
        {
          {
            statement_ast *__node_3 = 0;
            if (!parse_statement(&__node_3))
              return false;
            (*yynode)->stmt_sequence = snoc((*yynode)->stmt_sequence, __node_3, memory_pool);
          }

        }
      if (yytoken != Token_RBRACE)
        return false;
      yylex();
    }
  else
    return false;

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
        return false;
      if (yytoken != Token_EQUAL_EQUAL)
        return false;
      (*yynode)->op = token_stream->index() - 1;
      yylex();
      expression_ast *__node_5 = 0;
      if (!parse_expression(&__node_5))
        return false;
    }
  else
    return false;

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
        return false;
      yylex();
      variable_ast *__node_6 = 0;
      if (!parse_variable(&__node_6))
        return false;
      while (yytoken == Token_COMMA)
        {
          if (yytoken != Token_COMMA)
            return false;
          yylex();
          variable_ast *__node_7 = 0;
          if (!parse_variable(&__node_7))
            return false;
        }
      if (yytoken != Token_SEMICOLON)
        return false;
      yylex();
    }
  else
    return false;

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
        return false;
      while (yytoken == Token_MINUS)
        {
          if (yytoken != Token_MINUS)
            return false;
          (*yynode)->op = token_stream->index() - 1;
          yylex();
          mult_expression_ast *__node_9 = 0;
          if (!parse_mult_expression(&__node_9))
            return false;
        }
    }
  else
    return false;

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
        return false;
      yylex();
      if (yytoken != Token_ID)
        return false;
      (*yynode)->id = token_stream->index() - 1;
      yylex();
      if (yytoken != Token_LPAREN)
        return false;
      yylex();
      if (yytoken == Token_ID)
        {
          {
            if (yytoken != Token_ID)
              return false;
            (*yynode)->param_sequence = snoc((*yynode)->param_sequence, token_stream->index() - 1, memory_pool);
            yylex();
          }

          while (yytoken == Token_COMMA)
            {
              if (yytoken != Token_COMMA)
                return false;
              yylex();
              {
                if (yytoken != Token_ID)
                  return false;
                (*yynode)->param_sequence = snoc((*yynode)->param_sequence, token_stream->index() - 1, memory_pool);
                yylex();
              }

            }
        }
      else if (true /*epsilon*/)
      {}
      if (yytoken != Token_RPAREN)
        return false;
      yylex();
      body_ast *__node_10 = 0;
      if (!parse_body(&__node_10))
        return false;
    }
  else
    return false;

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
        return false;
      yylex();
      if (yytoken != Token_LPAREN)
        return false;
      yylex();
      condition_ast *__node_11 = 0;
      if (!parse_condition(&__node_11))
        return false;
      if (yytoken != Token_RPAREN)
        return false;
      yylex();
      statement_ast *__node_12 = 0;
      if (!parse_statement(&__node_12))
        return false;
      if (yytoken == Token_ELSE)
        {
          if (yytoken != Token_ELSE)
            return false;
          yylex();
          statement_ast *__node_13 = 0;
          if (!parse_statement(&__node_13))
            return false;
        }
      else if (true /*epsilon*/)
      {}
    }
  else
    return false;

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
        return false;
      while (yytoken == Token_STAR)
        {
          if (yytoken != Token_STAR)
            return false;
          (*yynode)->op = token_stream->index() - 1;
          yylex();
          primary_ast *__node_15 = 0;
          if (!parse_primary(&__node_15))
            return false;
        }
    }
  else
    return false;

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
            return false;
          (*yynode)->num = token_stream->index() - 1;
          yylex();
        }
      else if (yytoken == Token_ID)
        {
          if (yytoken != Token_ID)
            return false;
          (*yynode)->id = token_stream->index() - 1;
          yylex();
          if (yytoken == Token_LPAREN)
            {
              if (yytoken != Token_LPAREN)
                return false;
              yylex();
              {
                expression_ast *__node_16 = 0;
                if (!parse_expression(&__node_16))
                  return false;
                (*yynode)->arg_sequence = snoc((*yynode)->arg_sequence, __node_16, memory_pool);
              }

              while (yytoken == Token_COMMA)
                {
                  if (yytoken != Token_COMMA)
                    return false;
                  yylex();
                  {
                    expression_ast *__node_17 = 0;
                    if (!parse_expression(&__node_17))
                      return false;
                    (*yynode)->arg_sequence = snoc((*yynode)->arg_sequence, __node_17, memory_pool);
                  }

                }
              if (yytoken != Token_RPAREN)
                return false;
              yylex();
            }
          else if (true /*epsilon*/)
          {}
        }
    }
  else
    return false;

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
          {
            function_definition_ast *__node_18 = 0;
            if (!parse_function_definition(&__node_18))
              return false;
            (*yynode)->fun_sequence = snoc((*yynode)->fun_sequence, __node_18, memory_pool);
          }

        }
      if (Token_EOF != yytoken)
        return false;
    }
  else
    return false;

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
                               return false;
                             yylex();
                             expression_ast *__node_19 = 0;
                             if (!parse_expression(&__node_19))
                               return false;
                             if (yytoken != Token_SEMICOLON)
                               return false;
                             yylex();
                           }
                         else
                           return false;

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
                                   return false;
                               }
                             else if (yytoken == Token_IF)
                               {
                                 if_statement_ast *__node_21 = 0;
                                 if (!parse_if_statement(&__node_21))
                                   return false;
                               }
                             else if (yytoken == Token_LBRACE)
                               {
                                 block_statement_ast *__node_22 = 0;
                                 if (!parse_block_statement(&__node_22))
                                   return false;
                               }
                             else if (yytoken == Token_RETURN)
                               {
                                 return_statement_ast *__node_23 = 0;
                                 if (!parse_return_statement(&__node_23))
                                   return false;
                               }
                           }
                         else
                           return false;

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
                               return false;
                             (*yynode)->id = token_stream->index() - 1;
                             yylex();
                           }
                         else
                           return false;

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

