// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "csharp.h"




csharp::csharp_compatibility_mode csharp::compatibility_mode()
{
  return _M_compatibility_mode;
}
void csharp::set_compatibility_mode( csharp::csharp_compatibility_mode mode )
{
  _M_compatibility_mode = mode;
}

void csharp::pp_define_symbol( std::string symbol_name )
{
  _M_pp_defined_symbols.insert(symbol_name);
}

void csharp::pp_undefine_symbol( std::string symbol_name )
{
  _M_pp_defined_symbols.erase(symbol_name);
}

bool csharp::pp_is_symbol_defined( std::string symbol_name )
{
  return (_M_pp_defined_symbols.find(symbol_name) != _M_pp_defined_symbols.end());
}


// custom error recovery
bool csharp::yy_expected_token(int /*expected*/, std::size_t where, char const *name)
{
  //print_token_environment(this);
  report_problem(
    csharp::error,
    std::string("Expected token ``") + name
    //+ "'' instead of ``" + current_token_text
    + "''"
  );
  return false;
}

bool csharp::yy_expected_symbol(int /*expected_symbol*/, char const *name)
{
  //print_token_environment(this);
  report_problem(
    csharp::error,
    std::string("Expected symbol ``") + name
    //+ "'' instead of ``" + current_token_text
    + "''"
  );
  return false;
}


bool csharp::parse_compilation_unit(compilation_unit_ast **yynode)
{
  *yynode = create<compilation_unit_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_TRUE
      || yytoken == Token_FALSE
      || yytoken == Token_NULL
      || yytoken == Token_INTEGER_LITERAL
      || yytoken == Token_REAL_LITERAL
      || yytoken == Token_CHARACTER_LITERAL
      || yytoken == Token_STRING_LITERAL
      || yytoken == Token_IDENTIFIER || yytoken == Token_EOF)
    {
      while (yytoken == Token_TRUE
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
              literal_ast *__node_0 = 0;
              if (!parse_literal(&__node_0))
                {
                  return yy_expected_symbol(csharp_ast_node::Kind_literal, "literal");
                }
            }
          else if (yytoken == Token_IDENTIFIER)
            {
              identifier_ast *__node_1 = 0;
              if (!parse_identifier(&__node_1))
                {
                  return yy_expected_symbol(csharp_ast_node::Kind_identifier, "identifier");
                }
            }
          else
            {
              return false;
            }
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

bool csharp::parse_identifier(identifier_ast **yynode)
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

bool csharp::parse_literal(literal_ast **yynode)
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
      else if (yytoken == Token_REAL_LITERAL)
        {
          if (yytoken != Token_REAL_LITERAL)
            return yy_expected_token(yytoken, Token_REAL_LITERAL, "real literal");
          (*yynode)->floating_point_literal = token_stream->index() - 1;
          yylex();
          (*yynode)->literal_type = literal_ast::type_real;
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

csharp_visitor::parser_fun_t csharp_visitor::_S_parser_table[] = {
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_compilation_unit),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_identifier),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_literal)
    }; // _S_parser_table[]

