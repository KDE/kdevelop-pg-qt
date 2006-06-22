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

  if (yytoken == Token_IDENTIFIER)
    {
      type_name_ast *__node_0 = 0;
      if (!parse_type_name(&__node_0))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_type_name, "type_name");
        }
      (*yynode)->name = __node_0;
      if (yytoken == Token_LPAREN)
        {
          attribute_arguments_ast *__node_1 = 0;
          if (!parse_attribute_arguments(&__node_1))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_attribute_arguments, "attribute_arguments");
            }
          (*yynode)->arguments = __node_1;
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

bool csharp::parse_attribute_arguments(attribute_arguments_ast **yynode)
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
      else if (( LA(2).kind == Token_ASSIGN ) && (yytoken == Token_IDENTIFIER))
        {
          named_argument_ast *__node_2 = 0;
          if (!parse_named_argument(&__node_2))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_named_argument, "named_argument");
            }
          (*yynode)->named_argument_sequence = snoc((*yynode)->named_argument_sequence, __node_2, memory_pool);
          while (yytoken == Token_COMMA)
            {
              if (yytoken != Token_COMMA)
                return yy_expected_token(yytoken, Token_COMMA, ",");
              yylex();
              named_argument_ast *__node_3 = 0;
              if (!parse_named_argument(&__node_3))
                {
                  return yy_expected_symbol(csharp_ast_node::Kind_named_argument, "named_argument");
                }
              (*yynode)->named_argument_sequence = snoc((*yynode)->named_argument_sequence, __node_3, memory_pool);
            }
          if (yytoken != Token_RPAREN)
            return yy_expected_token(yytoken, Token_RPAREN, ")");
          yylex();
        }
      else if (yytoken == Token_IDENTIFIER)
        {
          positional_argument_ast *__node_4 = 0;
          if (!parse_positional_argument(&__node_4))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_positional_argument, "positional_argument");
            }
          (*yynode)->positional_argument_sequence = snoc((*yynode)->positional_argument_sequence, __node_4, memory_pool);
          while (yytoken == Token_COMMA)
            {
              if (yytoken != Token_COMMA)
                return yy_expected_token(yytoken, Token_COMMA, ",");
              yylex();
              if (( (yytoken == Token_IDENTIFIER) && (LA(2).kind == Token_ASSIGN) ) && (yytoken == Token_IDENTIFIER))
                {
                  named_argument_ast *__node_5 = 0;
                  if (!parse_named_argument(&__node_5))
                    {
                      return yy_expected_symbol(csharp_ast_node::Kind_named_argument, "named_argument");
                    }
                  (*yynode)->named_argument_sequence = snoc((*yynode)->named_argument_sequence, __node_5, memory_pool);
                  while (yytoken == Token_COMMA)
                    {
                      if (yytoken != Token_COMMA)
                        return yy_expected_token(yytoken, Token_COMMA, ",");
                      yylex();
                      named_argument_ast *__node_6 = 0;
                      if (!parse_named_argument(&__node_6))
                        {
                          return yy_expected_symbol(csharp_ast_node::Kind_named_argument, "named_argument");
                        }
                      (*yynode)->named_argument_sequence = snoc((*yynode)->named_argument_sequence, __node_6, memory_pool);
                    }
                  break;
                }
              else if (yytoken == Token_IDENTIFIER)
                {
                  positional_argument_ast *__node_7 = 0;
                  if (!parse_positional_argument(&__node_7))
                    {
                      return yy_expected_symbol(csharp_ast_node::Kind_positional_argument, "positional_argument");
                    }
                  (*yynode)->positional_argument_sequence = snoc((*yynode)->positional_argument_sequence, __node_7, memory_pool);
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

bool csharp::parse_attribute_section(attribute_section_ast **yynode)
{
  *yynode = create<attribute_section_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_LBRACKET)
    {
      if (yytoken != Token_LBRACKET)
        return yy_expected_token(yytoken, Token_LBRACKET, "[");
      yylex();
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
          || yytoken == Token_IDENTIFIER)
        {
          attribute_target_ast *__node_8 = 0;
          if (!parse_attribute_target(&__node_8))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_attribute_target, "attribute_target");
            }
          (*yynode)->target = __node_8;
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
      attribute_ast *__node_9 = 0;
      if (!parse_attribute(&__node_9))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_attribute, "attribute");
        }
      (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_9, memory_pool);
      while (yytoken == Token_COMMA)
        {
          if (LA(2).kind == Token_RBRACKET)
            {
              break;
            }
          if (yytoken != Token_COMMA)
            return yy_expected_token(yytoken, Token_COMMA, ",");
          yylex();
          attribute_ast *__node_10 = 0;
          if (!parse_attribute(&__node_10))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_attribute, "attribute");
            }
          (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_10, memory_pool);
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
      || yytoken == Token_IDENTIFIER)
    {
      if (yytoken == Token_IDENTIFIER)
        {
          identifier_ast *__node_11 = 0;
          if (!parse_identifier(&__node_11))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_identifier, "identifier");
            }
          (*yynode)->identifier = __node_11;
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
          keyword_ast *__node_12 = 0;
          if (!parse_keyword(&__node_12))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_keyword, "keyword");
            }
          (*yynode)->keyword = __node_12;
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
      || yytoken == Token_STUB_B || yytoken == Token_EOF)
    {
      while (yytoken == Token_EXTERN)
        {
          extern_alias_directive_ast *__node_13 = 0;
          if (!parse_extern_alias_directive(&__node_13))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_extern_alias_directive, "extern_alias_directive");
            }
          (*yynode)->extern_alias_sequence = snoc((*yynode)->extern_alias_sequence, __node_13, memory_pool);
        }
      while (yytoken == Token_USING)
        {
          using_directive_ast *__node_14 = 0;
          if (!parse_using_directive(&__node_14))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_using_directive, "using_directive");
            }
          (*yynode)->using_sequence = snoc((*yynode)->using_sequence, __node_14, memory_pool);
        }
      while (yytoken == Token_LBRACKET)
        {
          global_attribute_section_ast *__node_15 = 0;
          if (!parse_global_attribute_section(&__node_15))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_global_attribute_section, "global_attribute_section");
            }
          (*yynode)->global_attribute_sequence = snoc((*yynode)->global_attribute_sequence, __node_15, memory_pool);
        }
      while (yytoken == Token_STUB_B)
        {
          namespace_member_declaration_ast *__node_16 = 0;
          if (!parse_namespace_member_declaration(&__node_16))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_namespace_member_declaration, "namespace_member_declaration");
            }
          (*yynode)->namespace_sequence = snoc((*yynode)->namespace_sequence, __node_16, memory_pool);
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

bool csharp::parse_expression(expression_ast **yynode)
{
  *yynode = create<expression_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      identifier_ast *__node_17 = 0;
      if (!parse_identifier(&__node_17))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_identifier, "identifier");
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
      identifier_ast *__node_18 = 0;
      if (!parse_identifier(&__node_18))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->identifier = __node_18;
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
      attribute_target_ast *__node_19 = 0;
      if (!parse_attribute_target(&__node_19))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_attribute_target, "attribute_target");
        }
      (*yynode)->target = __node_19;
      if (yytoken != Token_COLON)
        return yy_expected_token(yytoken, Token_COLON, ":");
      yylex();
      attribute_ast *__node_20 = 0;
      if (!parse_attribute(&__node_20))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_attribute, "attribute");
        }
      (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_20, memory_pool);
      while (yytoken == Token_COMMA)
        {
          if (LA(2).kind == Token_RBRACKET)
            {
              break;
            }
          if (yytoken != Token_COMMA)
            return yy_expected_token(yytoken, Token_COMMA, ",");
          yylex();
          attribute_ast *__node_21 = 0;
          if (!parse_attribute(&__node_21))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_attribute, "attribute");
            }
          (*yynode)->attribute_sequence = snoc((*yynode)->attribute_sequence, __node_21, memory_pool);
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
            return yy_expected_token(yytoken, Token_UNCHECKED, "unsafe");
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

bool csharp::parse_named_argument(named_argument_ast **yynode)
{
  *yynode = create<named_argument_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      identifier_ast *__node_22 = 0;
      if (!parse_identifier(&__node_22))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->argument_name = __node_22;
      if (yytoken != Token_ASSIGN)
        return yy_expected_token(yytoken, Token_ASSIGN, "=");
      yylex();
      expression_ast *__node_23 = 0;
      if (!parse_expression(&__node_23))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_expression, "expression");
        }
      (*yynode)->attribute_argument_expression = __node_23;
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

bool csharp::parse_namespace_name(namespace_name_ast **yynode)
{
  *yynode = create<namespace_name_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      namespace_or_type_name_ast *__node_24 = 0;
      if (!parse_namespace_or_type_name(&__node_24))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_namespace_or_type_name, "namespace_or_type_name");
        }
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

  if (yytoken == Token_IDENTIFIER)
    {
      if (( LA(2).kind == Token_SCOPE ) && (yytoken == Token_IDENTIFIER))
        {
          identifier_ast *__node_25 = 0;
          if (!parse_identifier(&__node_25))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_identifier, "identifier");
            }
          (*yynode)->qualified_alias_label = __node_25;
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
      namespace_or_type_name_part_ast *__node_26 = 0;
      if (!parse_namespace_or_type_name_part(&__node_26))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_namespace_or_type_name_part, "namespace_or_type_name_part");
        }
      (*yynode)->name_part_sequence = snoc((*yynode)->name_part_sequence, __node_26, memory_pool);
      while (yytoken == Token_DOT)
        {
          if (yytoken != Token_DOT)
            return yy_expected_token(yytoken, Token_DOT, ".");
          yylex();
          namespace_or_type_name_part_ast *__node_27 = 0;
          if (!parse_namespace_or_type_name_part(&__node_27))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_namespace_or_type_name_part, "namespace_or_type_name_part");
            }
          (*yynode)->name_part_sequence = snoc((*yynode)->name_part_sequence, __node_27, memory_pool);
        }
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool csharp::parse_namespace_or_type_name_part(namespace_or_type_name_part_ast **yynode)
{
  *yynode = create<namespace_or_type_name_part_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      identifier_ast *__node_28 = 0;
      if (!parse_identifier(&__node_28))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_identifier, "identifier");
        }
      (*yynode)->identifier = __node_28;
      if (( compatibility_mode() >= csharp20_compatibility ) && (yytoken == Token_STUB_A))
        {
          type_arguments_ast *__node_29 = 0;
          if (!parse_type_arguments(&__node_29))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_type_arguments, "type_arguments");
            }
          (*yynode)->type_arguments = __node_29;
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

bool csharp::parse_positional_argument(positional_argument_ast **yynode)
{
  *yynode = create<positional_argument_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      expression_ast *__node_30 = 0;
      if (!parse_expression(&__node_30))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_expression, "expression");
        }
      (*yynode)->attribute_argument_expression = __node_30;
    }
  else
    {
      return false;
    }

  (*yynode)->end_token = token_stream->index() - 1;

  return true;
}

bool csharp::parse_type_arguments(type_arguments_ast **yynode)
{
  *yynode = create<type_arguments_ast>();

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

bool csharp::parse_type_name(type_name_ast **yynode)
{
  *yynode = create<type_name_ast>();

  (*yynode)->start_token = token_stream->index() - 1;

  if (yytoken == Token_IDENTIFIER)
    {
      namespace_or_type_name_ast *__node_31 = 0;
      if (!parse_namespace_or_type_name(&__node_31))
        {
          return yy_expected_symbol(csharp_ast_node::Kind_namespace_or_type_name, "namespace_or_type_name");
        }
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
          identifier_ast *__node_32 = 0;
          if (!parse_identifier(&__node_32))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_identifier, "identifier");
            }
          (*yynode)->alias = __node_32;
          if (yytoken != Token_ASSIGN)
            return yy_expected_token(yytoken, Token_ASSIGN, "=");
          yylex();
          namespace_or_type_name_ast *__node_33 = 0;
          if (!parse_namespace_or_type_name(&__node_33))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_namespace_or_type_name, "namespace_or_type_name");
            }
          (*yynode)->namespace_or_type_name = __node_33;
        }
      else if (yytoken == Token_IDENTIFIER)
        {
          namespace_or_type_name_ast *__node_34 = 0;
          if (!parse_namespace_or_type_name(&__node_34))
            {
              return yy_expected_symbol(csharp_ast_node::Kind_namespace_or_type_name, "namespace_or_type_name");
            }
          (*yynode)->namespace_name = __node_34;
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
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_attribute_arguments),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_attribute_section),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_attribute_target),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_compilation_unit),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_expression),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_extern_alias_directive),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_global_attribute_section),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_identifier),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_keyword),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_literal),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_named_argument),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_namespace_member_declaration),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_namespace_name),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_namespace_or_type_name),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_namespace_or_type_name_part),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_positional_argument),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_type_arguments),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_type_name),
      reinterpret_cast<parser_fun_t>(&csharp_visitor::visit_using_directive)
    }; // _S_parser_table[]

