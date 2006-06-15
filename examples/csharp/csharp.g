-- This file is part of KDevelop.
-- Copyright (c) 2006 Jakob Petsovits <jpetso@gmx.at>
--
-- This grammar is free software; you can redistribute it and/or
-- modify it under the terms of the GNU Library General Public
-- License as published by the Free Software Foundation; either
-- version 2 of the License, or (at your option) any later version.
--
-- This grammar is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
-- Lesser General Public License for more details.
--
-- You should have received a copy of the GNU Library General Public License
-- along with this library; see the file COPYING.LIB.  If not, write to
-- the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
-- Boston, MA 02110-1301, USA.


-- Grammar for C# 2.0
-- Modelled after the [license] [pg] C# 1.0 grammar at
-- [url]
-- (Version [version] from [January 03, 2005?])
-- and the reference grammar of the C# 2.0 language specification
-- (ECMA-334, Third Edition from June 2005, available at
-- http://www.ecma-international.org/publications/standards/Ecma-334.htm).



-- Known problematic conflicts (0 conflicts), requiring automatic LL(k):
--  - The first/follow NOTHING, FORNAUGHT conflict in compilation_unit
--    (0 conflicts)

-- Known harmless or resolved conflicts (0 conflicts):
--  - none
--    (done right by default, 0 conflicts)
--  - still none
--    (manually resolved, 0 conflicts)

-- Total amount of conflicts: 0


--
-- Global declarations
--

[:
#include <string>
#include <set>
:]



--
-- Parser class members
--

%member (parserclass: public declaration)
[:
  /**
   * Transform the raw input into tokens.
   * When this method returns, the parser's token stream has been filled
   * and any parse_*() method can be called.
   */
  void tokenize();

  // The compatibility_mode status variable tells which version of Java
  // should be checked against.
  enum csharp_compatibility_mode {
    csharp10_compatibility = 100,
    csharp20_compatibility = 200,
  };
  csharp::csharp_compatibility_mode compatibility_mode();
  void set_compatibility_mode( csharp::csharp_compatibility_mode mode );

  void pp_define_symbol( std::string symbol_name );

  enum problem_type {
    error,
    warning,
    info
  };
  void report_problem( csharp::problem_type type, const char* message );
  void report_problem( csharp::problem_type type, std::string message );
:]

%member (parserclass: protected declaration)
[:
  friend class csharp_pp_handler_visitor; // calls the pp_*() methods

  /** Called when an #error or #warning directive has been found.
   *  @param type   Either csharp::error or csharp::warning.
   *  @param label  The error/warning text.
   */
  virtual void pp_diagnostic( csharp::problem_type type, std::string message ) {}
  virtual void pp_diagnostic( csharp::problem_type type ) {}
:]

%member (parserclass: private declaration)
[:
  void pp_undefine_symbol( std::string symbol_name );
  bool pp_is_symbol_defined( std::string symbol_name );

  csharp::csharp_compatibility_mode _M_compatibility_mode;
  std::set<std::string> _M_pp_defined_symbols;
:]

%member (parserclass: constructor)
[:
  _M_compatibility_mode = csharp20_compatibility;
:]



--
-- Additional AST members
--

%member (literal: public declaration)
[:
  enum literal_type_enum {
    type_true,
    type_false,
    type_null,
    type_integer,
    type_real,
    type_character,
    type_string
  };
  literal_type_enum literal_type;
:]




--
-- List of defined tokens
--

-- keywords:
%token ABSTRACT ("abstract"), AS ("as"), BASE ("base"), BOOL ("bool"),
       BREAK ("break"), BYTE ("byte"), CASE ("case"), CATCH ("catch"),
       CHAR ("char"), CHECKED ("checked"), CLASS ("class"), CONST ("const"),
       CONTINUE ("continue"), DECIMAL ("decimal"), DEFAULT ("default"),
       DELEGATE ("delegate"), DO ("do"), DOUBLE ("double"), ELSE ("else"),
       ENUM ("enum"), EVENT ("event"), EXPLICIT ("explicit"),
       FINALLY ("finally"), FIXED ("fixed"), FLOAT ("float"),
       FOREACH ("foreach"), FOR ("for"), GOTO ("goto"), IF ("if"),
       IMPLICIT ("implicit"), IN ("in"), INT ("int"), INTERFACE ("interface"),
       INTERNAL ("internal"), IS ("is"), LOCK ("lock"), LONG ("long"),
       NAMESPACE ("namespace"), NEW ("new"), OBJECT ("object"),
       OPERATOR ("operator"), OUT ("out"), OVERRIDE ("override"),
       PARAMS ("params"), PRIVATE ("private"), PROTECTED ("protected"),
       PUBLIC ("public"), READONLY ("readonly"), REF ("ref"),
       RETURN ("return"), SBYTE ("sbyte"), SEALED ("sealed"), SHORT ("short"),
       SIZEOF ("sizeof"), STACKALLOC ("stackalloc"), STATIC ("static"),
       STRING ("string"), STRUCT ("struct"), SWITCH ("switch"),
       THIS ("this"), THROW ("throw"), TRY ("try"), TYPEOF ("typeof"),
       UINT ("uint"), ULONG ("ulong"), UNCHECKED ("unsafe"), UNSAFE ("unsafe"),
       USHORT ("ushort"), USING ("using"), VIRTUAL ("virtual"), VOID ("void"),
       VOLATILE ("volatile"), WHILE ("while") ;;

-- non-keyword identifiers with special meaning in the grammar:
%token ADD ("add"), ALIAS("alias"), GET ("get"), GLOBAL ("global"),
       PARTIAL ("partial"), REMOVE ("remove"), SET ("set"), VALUE ("value"),
       WHERE ("where"), YIELD ("yield") ;;

-- seperators:
%token LPAREN ("("), RPAREN (")"), LBRACE ("{"), RBRACE ("}"), LBRACKET ("["),
       RBRACKET ("]"), COMMA (","), SEMICOLON (";"), DOT (".") ;;

-- operators:
%token COLON (":"), COLONCOLON ("::"), QUESTION ("?"), QUESTIONQUESTION ("??"),
       BANG ("!"), TILDE ("~"), EQUAL ("=="), LESS_THAN ("<"),
       LESS_EQUAL ("<="), GREATER_THAN (">"), GREATER_EQUAL (">="),
       NOT_EQUAL ("!="), LOG_AND ("&&"), LOG_OR ("||"), ARROW_RIGHT ("->"),
       INCREMENT ("++"), DECREMENT ("--"), ASSIGN ("="), PLUS ("+"),
       PLUS_ASSIGN ("+="), MINUS ("-"), MINUS_ASSIGN ("-="), STAR ("*"),
       STAR_ASSIGN ("*="), SLASH ("/"), SLASH_ASSIGN ("/="), BIT_AND ("&"),
       BIT_AND_ASSIGN ("&="), BIT_OR ("|"), BIT_OR_ASSIGN ("|="),
       BIT_XOR ("^"), BIT_XOR_ASSIGN ("^="), REMAINDER ("%"),
       REMAINDER_ASSIGN ("%="), LSHIFT ("<<"), LSHIFT_ASSIGN ("<<="),
       RSHIFT (">>"), RSHIFT_ASSIGN (">>=") ;;

-- literals and identifiers:
%token TRUE ("true"), FALSE ("false"), NULL ("null"),
       INTEGER_LITERAL ("integer literal"), REAL_LITERAL ("real literal"),
       CHARACTER_LITERAL ("character literal"),
       STRING_LITERAL ("string literal"), IDENTIFIER ("identifier") ;;

-- token that makes the parser fail in any case:
%token INVALID ("invalid token") ;;




--
-- Start of the actual grammar
--

   ( literal | identifier )*
-> compilation_unit ;;

   ident=IDENTIFIER
-> identifier ;;

 (
   TRUE   [: (*yynode)->literal_type = literal_ast::type_true;  :]
 | FALSE  [: (*yynode)->literal_type = literal_ast::type_false; :]
 | NULL   [: (*yynode)->literal_type = literal_ast::type_null;  :]
 |
   integer_literal=INTEGER_LITERAL
   [: (*yynode)->literal_type = literal_ast::type_integer;  :]
 |
   floating_point_literal=REAL_LITERAL
   [: (*yynode)->literal_type = literal_ast::type_real;  :]
 |
   character_literal=CHARACTER_LITERAL
   [: (*yynode)->literal_type = literal_ast::type_character;  :]
 |
   string_literal=STRING_LITERAL
   [: (*yynode)->literal_type = literal_ast::type_string;  :]
 )
-> literal ;;







--
-- Code segments copied to the implementation (.cpp) file.
-- If existant, kdevelop-pg's current syntax requires this block to occur
-- at the end of the file.
--

[:


csharp::csharp_compatibility_mode csharp::compatibility_mode() {
  return _M_compatibility_mode;
}
void csharp::set_compatibility_mode( csharp::csharp_compatibility_mode mode ) {
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

:]