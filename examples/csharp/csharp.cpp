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


bool csharp::parse_attribute(attribute_ast **yynode)
{
  *yynode = create<attribute_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_STUB_D)
    {
      if (yytoken != Token_STUB_D)
        return yy_expected_token(yytoken, Token_STUB_D, "STUB_D");
      yylex();
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool csharp::parse_attribute_section(attribute_section_ast **yynode)
{
  *yynode = create<attribute_section_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACKET)
    {
      if (yytoken != Token_LBRACKET)
        return yy_expected_token(yytoken, Token_LBRACKET, "[");
      yylex();
      if (yytoken == Token_IDENTIFIER
          || yytoken == Token_STUB_B)
        {
          attribute_target_ast *__node_0 = 0;
          if (!parse_attribute_target(&__node_0))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_attribute_target, "attribute_target");
            }
          (*yynode)->target = __node_0;
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
      attribute_ast *__node_1 = 0;
      if (!parse_attribute(&__node_1))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_attribute, "attribute");
        }
      (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_1, memory_pool);
      while (yytoken == Token_COMMA)
        {
          if (yytoken != Token_COMMA)
            return yy_expected_token(yytoken, Token_COMMA, ",");
          yylex();
          attribute_ast *__node_2 = 0;
          if (!parse_attribute(&__node_2))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_attribute, "attribute");
            }
          (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_2, memory_pool);
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

bool csharp::parse_attribute_target(attribute_target_ast **yynode)
{
  *yynode = create<attribute_target_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER
      || yytoken == Token_STUB_B)
    {
      if (yytoken == Token_IDENTIFIER)
        {
          identifier_ast *__node_3 = 0;
          if (!parse_identifier(&__node_3))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_identifier, "identifier");
            }
          (*yynode)->identifier = __node_3;
        }
      else if (yytoken == Token_STUB_B)
        {
          keyword_ast *__node_4 = 0;
          if (!parse_keyword(&__node_4))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_keyword, "keyword");
            }
          (*yynode)->keyword = __node_4;
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

bool csharp::parse_compilation_unit(compilation_unit_ast **yynode)
{
  *yynode = create<compilation_unit_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_EXTERN
      || yytoken == Token_USING
      || yytoken == Token_LBRACKET
      || yytoken == Token_STUB_C || yytoken == Token_EOF)
    {
      while (yytoken == Token_EXTERN)
        {
          extern_alias_directive_ast *__node_5 = 0;
          if (!parse_extern_alias_directive(&__node_5))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_extern_alias_directive, "extern_alias_directive");
            }
          (*yynode)->extern_alias_sequence = snoc((*yynode)->extern_alias_sequence, __node_5, memory_pool);
        }
      while (yytoken == Token_USING)
        {
          using_directive_ast *__node_6 = 0;
          if (!parse_using_directive(&__node_6))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_using_directive, "using_directive");
            }
          (*yynode)->using_sequence = snoc((*yynode)->using_sequence, __node_6, memory_pool);
        }
      while (yytoken == Token_LBRACKET)
        {
          global_attribute_section_ast *__node_7 = 0;
          if (!parse_global_attribute_section(&__node_7))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_global_attribute_section, "global_attribute_section");
            }
          (*yynode)->global_attribute_sequence = snoc((*yynode)->global_attribute_sequence, __node_7, memory_pool);
        }
      while (yytoken == Token_STUB_C)
        {
          namespace_member_declaration_ast *__node_8 = 0;
          if (!parse_namespace_member_declaration(&__node_8))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_namespace_member_declaration, "namespace_member_declaration");
            }
          (*yynode)->namespace_sequence = snoc((*yynode)->namespace_sequence, __node_8, memory_pool);
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

bool csharp::parse_extern_alias_directive(extern_alias_directive_ast **yynode)
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
      identifier_ast *__node_9 = 0;
      if (!parse_identifier(&__node_9))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->identifier = __node_9;
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

bool csharp::parse_global_attribute_section(global_attribute_section_ast **yynode)
{
  *yynode = create<global_attribute_section_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACKET)
    {
      if (yytoken != Token_LBRACKET)
        return yy_expected_token(yytoken, Token_LBRACKET, "[");
      yylex();
      attribute_target_ast *__node_10 = 0;
      if (!parse_attribute_target(&__node_10))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_attribute_target, "attribute_target");
        }
      (*yynode)->target = __node_10;
      if (yytoken != Token_COLON)
        return yy_expected_token(yytoken, Token_COLON, ":");
      yylex();
      attribute_ast *__node_11 = 0;
      if (!parse_attribute(&__node_11))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_attribute, "attribute");
        }
      (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_11, memory_pool);
      while (yytoken == Token_COMMA)
        {
          if (yytoken != Token_COMMA)
            return yy_expected_token(yytoken, Token_COMMA, ",");
          yylex();
          attribute_ast *__node_12 = 0;
          if (!parse_attribute(&__node_12))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_attribute, "attribute");
            }
          (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_12, memory_pool);
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

bool csharp::parse_keyword(keyword_ast **yynode)
{
  *yynode = create<keyword_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_STUB_B)
    {
      if (yytoken != Token_STUB_B)
        return yy_expected_token(yytoken, Token_STUB_B, "STUB_B");
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

bool csharp::parse_namespace_member_declaration(namespace_member_declaration_ast **yynode)
{
  *yynode = create<namespace_member_declaration_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_STUB_C)
    {
      if (yytoken != Token_STUB_C)
        return yy_expected_token(yytoken, Token_STUB_C, "STUB_C");
      yylex();
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool csharp::parse_namespace_or_type_name(namespace_or_type_name_ast **yynode)
{
  *yynode = create<namespace_or_type_name_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_STUB_A)
    {
      if (yytoken != Token_STUB_A)
        return yy_expected_token(yytoken, Token_STUB_A, "STUB_A");
      yylex();
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool csharp::parse_using_directive(using_directive_ast **yynode)
{
  *yynode = create<using_directive_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_USING)
    {
      if (yytoken != Token_USING)
        return yy_expected_token(yytoken, Token_USING, "using");
      yylex();
      if (( LA(2).kind == Token_ASSIGN ) && (yytoken == Token_IDENTIFIER))
        {
          identifier_ast *__node_13 = 0;
          if (!parse_identifier(&__node_13))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_identifier, "identifier");
            }
          (*yynode)->alias = __node_13;
          if (yytoken != Token_ASSIGN)
            return yy_expected_token(yytoken, Token_ASSIGN, "=");
          yylex();
          namespace_or_type_name_ast *__node_14 = 0;
          if (!parse_namespace_or_type_name(&__node_14))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_namespace_or_type_name, "namespace_or_type_name");
            }
          (*yynode)->namespace_or_type_name = __node_14;
        }
      else if (yytoken == Token_STUB_A)
        {
          namespace_or_type_name_ast *__node_15 = 0;
          if (!parse_namespace_or_type_name(&__node_15))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_namespace_or_type_name, "namespace_or_type_name");
            }
          (*yynode)->namespace_name = __node_15;
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

csharp_visitor::parser_fun_t csharp_visitor::_S_parser_table[] = {
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_attribute),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_attribute_section),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_attribute_target),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_compilation_unit),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_extern_alias_directive),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_global_attribute_section),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_identifier),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_keyword),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_literal),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_namespace_member_declaration),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_namespace_or_type_name),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_using_directive)
    }; // _S_parser_table[]

