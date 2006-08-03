// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef fact_h_INCLUDED
#define fact_h_INCLUDED

#include "kdev-pg-memory-pool.h"
#include "kdev-pg-allocator.h"
#include "kdev-pg-list.h"
#include "kdev-pg-token-stream.h"
#include <cassert>

namespace fact
  {

  struct assignment_statement_ast;
  struct block_statement_ast;
  struct body_ast;
  struct condition_ast;
  struct declaration_ast;
  struct expression_ast;
  struct function_definition_ast;
  struct if_statement_ast;
  struct mult_expression_ast;
  struct primary_ast;
  struct program_ast;
  struct return_statement_ast;
  struct statement_ast;
  struct variable_ast;


  struct ast_node
    {
      enum ast_node_kind_enum {
        Kind_assignment_statement = 1000,
        Kind_block_statement = 1001,
        Kind_body = 1002,
        Kind_condition = 1003,
        Kind_declaration = 1004,
        Kind_expression = 1005,
        Kind_function_definition = 1006,
        Kind_if_statement = 1007,
        Kind_mult_expression = 1008,
        Kind_primary = 1009,
        Kind_program = 1010,
        Kind_return_statement = 1011,
        Kind_statement = 1012,
        Kind_variable = 1013,
        AST_NODE_KIND_COUNT
      };

      int kind;
      std::size_t start_token;
      std::size_t end_token;
    };

  struct assignment_statement_ast: public ast_node
    {
      enum
      {
        KIND = Kind_assignment_statement
      };

      std::size_t id;
      expression_ast *expr;
    };

  struct block_statement_ast: public ast_node
    {
      enum
      {
        KIND = Kind_block_statement
      };

      const list_node<statement_ast *> *stmt_sequence;
    };

  struct body_ast: public ast_node
    {
      enum
      {
        KIND = Kind_body
      };

      const list_node<declaration_ast *> *decl_sequence;
      const list_node<statement_ast *> *stmt_sequence;
    };

  struct condition_ast: public ast_node
    {
      enum
      {
        KIND = Kind_condition
      };

      expression_ast *left_expr;
      expression_ast *right_expr;
    };

  struct declaration_ast: public ast_node
    {
      enum
      {
        KIND = Kind_declaration
      };

      variable_ast *var;
    };

  struct expression_ast: public ast_node
    {
      enum
      {
        KIND = Kind_expression
      };

      mult_expression_ast *left_expr;
      mult_expression_ast *right_expr;
    };

  struct function_definition_ast: public ast_node
    {
      enum
      {
        KIND = Kind_function_definition
      };

      std::size_t id;
      const list_node<std::size_t > *param_sequence;
      body_ast *body;
    };

  struct if_statement_ast: public ast_node
    {
      enum
      {
        KIND = Kind_if_statement
      };

      condition_ast *cond;
      statement_ast *if_stmt;
      statement_ast *else_stmt;
    };

  struct mult_expression_ast: public ast_node
    {
      enum
      {
        KIND = Kind_mult_expression
      };

      primary_ast *left_expr;
      primary_ast *right_expr;
    };

  struct primary_ast: public ast_node
    {
      enum
      {
        KIND = Kind_primary
      };

      std::size_t num;
      std::size_t id;
      const list_node<expression_ast *> *argument_sequence;
    };

  struct program_ast: public ast_node
    {
      enum
      {
        KIND = Kind_program
      };

      const list_node<function_definition_ast *> *fun_sequence;
    };

  struct return_statement_ast: public ast_node
                 {
                   enum
                   {
                     KIND = Kind_return_statement
                   };

                   expression_ast *expr;
                 };

  struct statement_ast: public ast_node
    {
      enum
      {
        KIND = Kind_statement
      };

      assignment_statement_ast *assign_stmt;
      if_statement_ast *if_stmt;
      block_statement_ast *block_stmt;
      return_statement_ast *return_stmt;
    };

  struct variable_ast: public ast_node
    {
      enum
      {
        KIND = Kind_variable
      };

      std::size_t id;
    };



} // end of namespace fact


namespace fact
  {

  class parser
    {
    public:
      typedef kdev_pg_token_stream token_stream_type;
      typedef kdev_pg_token_stream::token_type token_type;
      kdev_pg_token_stream *token_stream;
      int yytoken;

      inline token_type LA(std::size_t k = 1) const
        {
          return token_stream->token(token_stream->index() - 1 + k - 1);
        }
      inline int yylex()
      {
        return (yytoken = token_stream->next_token());
      }
      inline void rewind(std::size_t index)
      {
        token_stream->rewind(index);
        yylex();
      }

      // token stream
      void set_token_stream(kdev_pg_token_stream *s)
      {
        token_stream = s;
      }

      // error handling
      void yy_expected_symbol(int kind, char const *name);
      void yy_expected_token(int kind, std::size_t token, char const *name);

      bool yy_block_errors;
      inline bool block_errors(bool block)
      {
        bool previous = yy_block_errors;
        yy_block_errors = block;
        return previous;
      }

      // memory pool
      typedef kdev_pg_memory_pool memory_pool_type;

      kdev_pg_memory_pool *memory_pool;
      void set_memory_pool(kdev_pg_memory_pool *p)
      {
        memory_pool = p;
      }
      template <class T>
      inline T *create()
      {
        T *node = new (memory_pool->allocate(sizeof(T))) T();
        node->kind = T::KIND;
        return node;
      }

      enum token_type_enum
      {
        Token_ASSIGN = 1000,
        Token_COMMA = 1001,
        Token_ELSE = 1002,
        Token_EOF = 1003,
        Token_EQUAL = 1004,
        Token_FUNCTION = 1005,
        Token_IDENTIFIER = 1006,
        Token_IF = 1007,
        Token_INVALID = 1008,
        Token_LBRACE = 1009,
        Token_LPAREN = 1010,
        Token_MINUS = 1011,
        Token_NUMBER = 1012,
        Token_RBRACE = 1013,
        Token_RETURN = 1014,
        Token_RPAREN = 1015,
        Token_SEMICOLON = 1016,
        Token_STAR = 1017,
        Token_VAR = 1018,
        token_type_size
      }; // token_type_enum

      // user defined declarations:
    public:

      /**
       * Transform the raw input into tokens.
       * When this method returns, the parser's token stream has been filled
       * and any parse_*() method can be called.
       */
      void tokenize();

      enum problem_type {
        error,
        warning,
        info,
      };
      void report_problem( parser::problem_type type, const char* message );
      void report_problem( parser::problem_type type, std::string message );


    public:
      parser()
      {
        memory_pool = 0;
        token_stream = 0;
        yytoken = Token_EOF;
        yy_block_errors = false;
      }

      virtual ~parser()
      {}

      bool parse_assignment_statement(assignment_statement_ast **yynode);
      bool parse_block_statement(block_statement_ast **yynode);
      bool parse_body(body_ast **yynode);
      bool parse_condition(condition_ast **yynode);
      bool parse_declaration(declaration_ast **yynode);
      bool parse_expression(expression_ast **yynode);
      bool parse_function_definition(function_definition_ast **yynode);
      bool parse_if_statement(if_statement_ast **yynode);
      bool parse_mult_expression(mult_expression_ast **yynode);
      bool parse_primary(primary_ast **yynode);
      bool parse_program(program_ast **yynode);
      bool parse_return_statement(return_statement_ast **yynode);
      bool parse_statement(statement_ast **yynode);
      bool parse_variable(variable_ast **yynode);
    };
  class visitor
    {
      typedef void (visitor::*parser_fun_t)(ast_node *);
      static parser_fun_t _S_parser_table[];

    public:
      virtual ~visitor()
      {}
      virtual void visit_node(ast_node *node)
      {
        if (node)
          (this->*_S_parser_table[node->kind - 1000])(node);
      }
      virtual void visit_assignment_statement(assignment_statement_ast *)
    {}
      virtual void visit_block_statement(block_statement_ast *)
      {}
      virtual void visit_body(body_ast *)
      {}
      virtual void visit_condition(condition_ast *)
      {}
      virtual void visit_declaration(declaration_ast *)
      {}
      virtual void visit_expression(expression_ast *)
      {}
      virtual void visit_function_definition(function_definition_ast *)
      {}
      virtual void visit_if_statement(if_statement_ast *)
      {}
      virtual void visit_mult_expression(mult_expression_ast *)
      {}
      virtual void visit_primary(primary_ast *)
      {}
      virtual void visit_program(program_ast *)
      {}
      virtual void visit_return_statement(return_statement_ast *)
                               {}
                               virtual void visit_statement(statement_ast *)
                               {}
                               virtual void visit_variable(variable_ast *)
                               {}
                             }
                           ;
  class default_visitor: public visitor
    {
    public:
      virtual void visit_assignment_statement(assignment_statement_ast *node)
      {
        visit_node(node->expr);
      }

      virtual void visit_block_statement(block_statement_ast *node)
      {
        if (node->stmt_sequence)
          {
            const list_node<statement_ast*> *__it = node->stmt_sequence->to_front(), *__end = __it;
            do
              {
                visit_node(__it->element);
                __it = __it->next;
              }
            while (__it != __end);
          }
      }

      virtual void visit_body(body_ast *node)
      {
        if (node->decl_sequence)
          {
            const list_node<declaration_ast*> *__it = node->decl_sequence->to_front(), *__end = __it;
            do
              {
                visit_node(__it->element);
                __it = __it->next;
              }
            while (__it != __end);
          }
        if (node->stmt_sequence)
          {
            const list_node<statement_ast*> *__it = node->stmt_sequence->to_front(), *__end = __it;
            do
              {
                visit_node(__it->element);
                __it = __it->next;
              }
            while (__it != __end);
          }
      }

      virtual void visit_condition(condition_ast *node)
      {
        visit_node(node->left_expr);
        visit_node(node->right_expr);
      }

      virtual void visit_declaration(declaration_ast *node)
      {
        visit_node(node->var);
      }

      virtual void visit_expression(expression_ast *node)
      {
        visit_node(node->left_expr);
        visit_node(node->right_expr);
      }

      virtual void visit_function_definition(function_definition_ast *node)
      {
        visit_node(node->body);
      }

      virtual void visit_if_statement(if_statement_ast *node)
      {
        visit_node(node->cond);
        visit_node(node->if_stmt);
        visit_node(node->else_stmt);
      }

      virtual void visit_mult_expression(mult_expression_ast *node)
      {
        visit_node(node->left_expr);
        visit_node(node->right_expr);
      }

      virtual void visit_primary(primary_ast *node)
      {
        if (node->argument_sequence)
          {
            const list_node<expression_ast*> *__it = node->argument_sequence->to_front(), *__end = __it;
            do
              {
                visit_node(__it->element);
                __it = __it->next;
              }
            while (__it != __end);
          }
      }

      virtual void visit_program(program_ast *node)
      {
        if (node->fun_sequence)
          {
            const list_node<function_definition_ast*> *__it = node->fun_sequence->to_front(), *__end = __it;
            do
              {
                visit_node(__it->element);
                __it = __it->next;
              }
            while (__it != __end);
          }
      }

      virtual void visit_return_statement(return_statement_ast *node)
                               {
                                 visit_node(node->expr);
                               }

                               virtual void visit_statement(statement_ast *node)
                               {
                                 visit_node(node->assign_stmt);
                                 visit_node(node->if_stmt);
                                 visit_node(node->block_stmt);
                                 visit_node(node->return_stmt);
                               }

                               virtual void visit_variable(variable_ast *)
                               {}

                             }
                           ;

} // end of namespace fact

#endif


