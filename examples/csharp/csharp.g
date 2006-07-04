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
--  - Nothing until now. But I'm sure I'll find some.
--    (0 conflicts)

-- Known harmless or resolved conflicts (9 conflicts):
--  - The first/follow LBRACKET conflict in compilation_unit
--    (manually resolved, 2 conflicts)
--  - The first/follow COMMA conflict in global_attribute_section,
--    and the same one in attribute_section
--    (manually resolved, 2 conflicts)
--  - The first/follow COMMA conflict in enum_body, similar to the above
--    (manually resolved, 1 conflict)
--  - The first/follow DOT conflict in namespace_or_type_name_safe,
--    which actually stems from indexer_declaration
--    (manually resolved, 1 conflict
--  - The first/first ADD, ALIAS, etc. (identifier) conflict in using_directive
--    (manually resolved, 1 conflict)
--  - The first/first ADD, ALIAS, etc. (identifier) conflicts
--    in attribute_arguments, two of them
--    (manually resolved, 2 conflicts)

-- Total amount of conflicts: 9


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

  /**
   * The compatibility_mode status variable tells which version of C#
   * should be checked against.
   */
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

%member (type_declaration_rest: public declaration)
[:
  bool partial;
:]

%member (constructor_initializer: public declaration)
[:
  enum constructor_initializer_type_enum {
    type_base,
    type_this,
  };
  constructor_initializer_type_enum type;
:]

%member (overloadable_unary_only_operator: public declaration)
[:
  enum overloadable_unary_only_operator_enum {
    op_bang,
    op_tilde,
    op_increment,
    op_decrement,
    op_true,
    op_false,
  };
  overloadable_unary_only_operator_enum op;
:]

%member (overloadable_binary_only_operator: public declaration)
[:
  enum overloadable_binary_only_operator_enum {
    op_star,
    op_slash,
    op_remainder,
    op_bit_and,
    op_bit_or,
    op_bit_xor,
    op_lshift,
    op_rshift,
    op_equal,
    op_not_equal,
    op_greater_than,
    op_less_than,
    op_greater_equal,
    op_less_equal,
  };
  overloadable_binary_only_operator_enum op;
:]

%member (overloadable_unary_or_binary_operator: public declaration)
[:
  enum overloadable_unary_or_binary_operator_enum {
    op_plus,
    op_minus,
  };
  overloadable_unary_or_binary_operator_enum op;
:]

%member (argument: public declaration)
[:
  enum argument_type_enum {
    type_value_parameter,
    type_reference_parameter,
    type_output_parameter,
  };
  argument_type_enum type;
:]

%member (return_type: public declaration)
[:
  enum return_type_enum {
    type_regular,
    type_void,
  };
  return_type_enum type;
:]

%member (builtin_class_type: public declaration)
[:
  enum builtin_class_type_enum {
    type_object,
    type_string,
  };
  builtin_class_type_enum type;
:]

%member (rank_specifier: public declaration)
[:
  int dimension_seperator_count;
:]

%member (optionally_nullable_type: public declaration)
[:
  bool nullable;
:]

%member (simple_type: public declaration)
[:
  enum simple_type_enum {
    type_numeric,
    type_bool,
  };
  simple_type_enum type;
:]

%member (numeric_type: public declaration)
[:
  enum numeric_type_enum {
    type_integral,
    type_floating_point,
    type_decimal,
  };
  numeric_type_enum type;
:]

%member (integral_type: public declaration)
[:
  enum integral_type_enum {
    type_sbyte,
    type_byte,
    type_short,
    type_ushort,
    type_int,
    type_uint,
    type_long,
    type_ulong,
    type_char,
  };
  integral_type_enum type;
:]

%member (floating_point_type: public declaration)
[:
  enum floating_point_type_enum {
    type_float,
    type_double,
  };
  floating_point_type_enum type;
:]

%member (parameter_modifier: public declaration)
[:
  enum parameter_modifier_enum {
    mod_ref,
    mod_out,
  };
  parameter_modifier_enum modifier;
:]

%member (optional_modifiers: public declaration)
[:
  enum modifier_enum {
    mod_new          = 1,
    mod_public       = 2,
    mod_protected    = 4,
    mod_internal     = 8,
    mod_private      = 16,
    mod_abstract     = 32,
    mod_sealed       = 64,
    mod_static       = 128,
    mod_readonly     = 256,
    mod_volatile     = 512,
    mod_virtual      = 1024,
    mod_override     = 2048,
    mod_extern       = 4096,
  };
  int modifiers;
:]

%member (optional_type_modifiers: public declaration)
[:
  int modifiers; // using the optional_modifier_enum values
:]

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
       EXTERN ("extern"), FINALLY ("finally"), FIXED ("fixed"),
       FLOAT ("float"), FOREACH ("foreach"), FOR ("for"), GOTO ("goto"),
       IF ("if"), IMPLICIT ("implicit"), IN ("in"), INT ("int"),
       INTERFACE ("interface"), INTERNAL ("internal"), IS ("is"),
       LOCK ("lock"), LONG ("long"), NAMESPACE ("namespace"), NEW ("new"),
       OBJECT ("object"), OPERATOR ("operator"), OUT ("out"),
       OVERRIDE ("override"), PARAMS ("params"), PRIVATE ("private"),
       PROTECTED ("protected"), PUBLIC ("public"), READONLY ("readonly"),
       REF ("ref"), RETURN ("return"), SBYTE ("sbyte"), SEALED ("sealed"),
       SHORT ("short"), SIZEOF ("sizeof"), STACKALLOC ("stackalloc"),
       STATIC ("static"), STRING ("string"), STRUCT ("struct"),
       SWITCH ("switch"), THIS ("this"), THROW ("throw"), TRY ("try"),
       TYPEOF ("typeof"), UINT ("uint"), ULONG ("ulong"), UNCHECKED ("unsafe"),
       UNSAFE ("unsafe"), USHORT ("ushort"), USING ("using"),
       VIRTUAL ("virtual"), VOID ("void"), VOLATILE ("volatile"),
       WHILE ("while") ;;

-- non-keyword identifiers with special meaning in the grammar:
%token ADD ("add"), ALIAS("alias"), GET ("get"), GLOBAL ("global"),
       PARTIAL ("partial"), REMOVE ("remove"), SET ("set"), VALUE ("value"),
       WHERE ("where"), YIELD ("yield"), ASSEMBLY ("assembly") ;;

-- seperators:
%token LPAREN ("("), RPAREN (")"), LBRACE ("{"), RBRACE ("}"), LBRACKET ("["),
       RBRACKET ("]"), COMMA (","), SEMICOLON (";"), DOT (".") ;;

-- operators:
%token COLON (":"), SCOPE ("::"), QUESTION ("?"), QUESTIONQUESTION ("??"),
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

%token STUB_A, STUB_B, STUB_C, STUB_D, STUB_E, STUB_F, STUB_G, STUB_H,
       STUB_I, STUB_J, STUB_K, STUB_L, STUB_M, STUB_N, STUB_O, STUB_P,
       STUB_Q, STUB_R, STUB_S, STUB_T, STUB_U, STUB_V, STUB_W, STUB_X ;;




--
-- Start of the actual grammar
--

   (#extern_alias=extern_alias_directive)*  -- TODO: probably not in C# 1.0
   (#using=using_directive)*
   (  0 [: if (LA(2).kind != Token_ASSEMBLY) break; :] -- exit the "star loop"
      #global_attribute=global_attribute_section
   )*
   (#namespace=namespace_member_declaration)*
-> compilation_unit ;;


   EXTERN ALIAS identifier=identifier SEMICOLON
-> extern_alias_directive ;;

   USING
   (  ?[: LA(2).kind == Token_ASSIGN :]      -- "using alias" directive
      alias=identifier ASSIGN namespace_or_type_name=namespace_or_type_name
    |
      namespace_name=namespace_or_type_name  -- "using namespace" directive
   )
   SEMICOLON
-> using_directive ;;




-- ATTRIBUTE sections, global and standard ones. They have a slight similarity
-- with Java's annotations in that they are used as advanced type modifiers.

-- Strictly seen, the ASSEMBLY here should just be attribute_target.
-- But for the sake of avoiding an LL(k)-ambiguous conflict
-- (in compilation_unit), we just allow "assembly".

   LBRACKET ASSEMBLY COLON
   #attribute=attribute
   ( 0 [: if (LA(2).kind == Token_RBRACKET) { break; } :]
     COMMA #attribute=attribute
   )*
   ( COMMA | 0 )
   RBRACKET
-> global_attribute_section ;;

   LBRACKET
   (target=attribute_target COLON | 0)
   #attribute=attribute
   ( 0 [: if (LA(2).kind == Token_RBRACKET) { break; } :]
     COMMA #attribute=attribute
   )*
   ( COMMA | 0 )
   RBRACKET
-> attribute_section ;;

   identifier=identifier | keyword=keyword
-> attribute_target ;;

   name=type_name (arguments=attribute_arguments | 0)
-> attribute ;;

   LPAREN
   (
      -- empty argument list:
      RPAREN
    |
      -- argument list only containing named arguments:
      ?[: LA(2).kind == Token_ASSIGN :]
      #named_argument=named_argument @ COMMA
      RPAREN
    |
      -- argument list with positional arguments and
      -- optionally appended named arguments:
      #positional_argument=positional_argument
      ( COMMA
        (  ?[: (yytoken == Token_IDENTIFIER) && (LA(2).kind == Token_ASSIGN) :]
           (#named_argument=named_argument @ COMMA)
           [: break; :] -- go directly to the closing parenthesis
         |
           #positional_argument=positional_argument
        )
      )*
      RPAREN
   )
-> attribute_arguments ;;

   attribute_argument_expression=expression
-> positional_argument ;;

   argument_name=identifier ASSIGN attribute_argument_expression=expression
-> named_argument ;;




-- NAMESPACES can be nested arbitrarily and contain stuff
-- like classes, interfaces, or other declarations.

   namespace_declaration=namespace_declaration
 | type_declaration=type_declaration
-> namespace_member_declaration ;;

   NAMESPACE name=qualified_identifier body=namespace_body (SEMICOLON | 0)
-> namespace_declaration ;;

   LBRACE
   (#extern_alias=extern_alias_directive)*  -- TODO: probably not in C# 1.0
   (#using=using_directive)*
   (#namespace=namespace_member_declaration)*
   RBRACE
-> namespace_body ;;

   (#attribute=attribute_section)*
   modifiers=optional_type_modifiers
   rest=type_declaration_rest
-> type_declaration ;;

 (
   PARTIAL  [: (*yynode)->partial = true;  :]
   (  class_declaration=class_declaration
     | struct_declaration=struct_declaration
     | interface_declaration=interface_declaration
   )
 |
   0        [: (*yynode)->partial = false; :]
   (  class_declaration=class_declaration
     | struct_declaration=struct_declaration
     | interface_declaration=interface_declaration
     | enum_declaration=enum_declaration
     | delegate_declaration=delegate_declaration
   )
 )
-> type_declaration_rest ;;

 (
   NEW        [: (*yynode)->modifiers |= optional_modifiers_ast::mod_new;       :]
 | PUBLIC     [: (*yynode)->modifiers |= optional_modifiers_ast::mod_public;    :]
 | PROTECTED  [: (*yynode)->modifiers |= optional_modifiers_ast::mod_protected; :]
 | INTERNAL   [: (*yynode)->modifiers |= optional_modifiers_ast::mod_internal;  :]
 | PRIVATE    [: (*yynode)->modifiers |= optional_modifiers_ast::mod_private;   :]
 -- the following three ones only occur in class declarations:
 | ABSTRACT   [: (*yynode)->modifiers |= optional_modifiers_ast::mod_abstract;  :]
 | SEALED     [: (*yynode)->modifiers |= optional_modifiers_ast::mod_sealed;    :]
 | STATIC     [: (*yynode)->modifiers |= optional_modifiers_ast::mod_static;    :]
 )*
-> optional_type_modifiers ;;



-- Definition of a C# CLASS

   CLASS class_name=identifier
   (
      ?[: compatibility_mode() >= csharp20_compatibility :]
      type_parameters=type_parameters
    | 0
   )
   (class_base=class_base | 0)
   (
      ?[: compatibility_mode() >= csharp20_compatibility :]
      type_parameter_constraints_clauses=type_parameter_constraints_clauses
    | 0
   )
   body=class_body
   (SEMICOLON | 0)
-> class_declaration ;;


-- Definition of a C# STRUCT

   STRUCT struct_name=identifier
   (
      ?[: compatibility_mode() >= csharp20_compatibility :]
      type_parameters=type_parameters
    | 0
   )
   (struct_interfaces=struct_interfaces | 0)
   (
      ?[: compatibility_mode() >= csharp20_compatibility :]
      type_parameter_constraints_clauses=type_parameter_constraints_clauses
    | 0
   )
   body=struct_body
   (SEMICOLON | 0)
-> struct_declaration ;;


-- Definition of a C# INTERFACE

   INTERFACE interface_name=identifier
   (
      ?[: compatibility_mode() >= csharp20_compatibility :]
      type_parameters=type_parameters
    | 0
   )
   (interface_base=interface_base | 0)
   (
      ?[: compatibility_mode() >= csharp20_compatibility :]
      type_parameter_constraints_clauses=type_parameter_constraints_clauses
    | 0
   )
   body=interface_body
   (SEMICOLON | 0)
-> interface_declaration ;;


-- Definition of a C# ENUM

   ENUM enum_name=identifier
   (enum_base=enum_base | 0)
   body=enum_body
   (SEMICOLON | 0)
-> enum_declaration ;;


-- Definition of a C# DELEGATE

   DELEGATE return_type=return_type delegate_name=identifier
   (
      ?[: compatibility_mode() >= csharp20_compatibility :]
      type_parameters=type_parameters
    | 0
   )
   LPAREN (formal_parameters=formal_parameters | 0) RPAREN
   (
      ?[: compatibility_mode() >= csharp20_compatibility :]
      type_parameter_constraints_clauses=type_parameter_constraints_clauses
    | 0
   )
   SEMICOLON
-> delegate_declaration ;;


-- BASE CLASSES and INTERFACES
-- which can be implemented by the types above

-- For class_base, the first type in the list of base types _may_ be a class.
-- (But it can also be an interface.) In order to avoid ambiguities, only the
-- first part of the rule has the exact seperation. If the second part of the
-- rule is chosen, then the first element of base_type_sequence can be
-- the base class.

   COLON
   (  builtin_class_type=builtin_class_type
      (COMMA (#interface_type=type_name @ COMMA) | 0)
    |
      #base_type=type_name @ COMMA
   )
-> class_base ;;

   COLON #interface_type=type_name @ COMMA
-> struct_interfaces ;;

   COLON #interface_type=type_name @ COMMA
-> interface_base ;;

   COLON integral_type=integral_type
-> enum_base ;;



-- BODIES of classes, interfaces, and the likes.

   LBRACE (#member_declaration=class_member_declaration)* RBRACE
-> class_body ;;

   LBRACE (#member_declaration=struct_member_declaration)* RBRACE
-> struct_body ;;

   LBRACE (#member_declaration=interface_member_declaration)* RBRACE
-> interface_body ;;

   LBRACE
   (
      #member_declaration=enum_member_declaration
      ( 0 [: if (LA(2).kind == Token_RBRACE) break; :] -- exit the "star loop"
        COMMA #member_declaration=enum_member_declaration
      )*
      (COMMA | 0)
    |
      0
   )
   RBRACE
-> enum_body ;;

   (#attribute=attribute_section)*
   member_name=identifier
   (ASSIGN constant_expression=constant_expression | 0)
-> enum_member_declaration ;;




-- Now on to what happens inside the class, interface, etc. bodies:


-- The CLASS MEMBER DECLARATION is one of the most complex rules in here,
-- and covers everything that can occur inside a class body.

--   #(attribute=attribute_section)*
--   modifiers=optional_modifiers
--   (
--      finalizer_declaration=finalizer_declaration
--    |
--      other member declarations
--   )
---> class_member_declaration ;;


-- The CONSTANT DECLARATION. Declares "const" values.

   CONST type=type (#constant_declarator=constant_declarator @ COMMA) SEMICOLON
-> constant_declaration ;;

   constant_name=identifier ASSIGN expression=constant_expression
-> constant_declarator ;;


-- The FIELD DECLARATION. Begins with type: will be folded into member_decl.

   type=type (#variable_declarator=variable_declarator @ COMMA) SEMICOLON
-> field_declaration ;;

   variable_name=identifier
   (ASSIGN variable_initializer=variable_initializer | 0)
-> variable_declarator ;;

   expression=expression
 | array_initializer=array_initializer
-> variable_initializer ;;


-- The METHOD DECLARATION. Begins with type: will be folded into member_decl.
-- New in C# 2.0: generic methods.

   return_type=return_type method_name=member_name
   (
      ?[: compatibility_mode() >= csharp20_compatibility :]
      type_parameters=type_parameters
    | 0
   )
   LPAREN (formal_parameters=formal_parameters | 0) RPAREN
   (
      ?[: compatibility_mode() >= csharp20_compatibility :]
      type_parameter_constraints_clauses=type_parameter_constraints_clauses
    | 0
   )
   (method_body=block | SEMICOLON)
-> method_declaration ;;


-- The CONSTRUCTOR DECLARATION. Naturally quite similar to the method one.
-- Will also be folded into the member_declaration.

   class_name=identifier
   LPAREN (formal_parameters=formal_parameters | 0) RPAREN
   (constructor_initializer=constructor_initializer | 0)
   (constructor_body=block | SEMICOLON)
-> constructor_declaration ;;

   COLON
   (  BASE [: (*yynode)->type = constructor_initializer_ast::type_base; :]
    | THIS [: (*yynode)->type = constructor_initializer_ast::type_this; :]
   )
   LPAREN (arguments=arguments | 0) RPAREN
-> constructor_initializer ;;

-- The STATIC CONSTRUCTOR DECLARATION is only used if the modifiers
-- contain "static" (and optionally "extern", and nothing else).

   class_name=identifier LPAREN RPAREN
   (static_constructor_body=block | SEMICOLON)
-> static_constructor_declaration ;;


-- The FINALIZER is what other languages know as deconstructor.
-- Only allowed inside classes.

   TILDE class_name=identifier LPAREN RPAREN
   (finalizer_body=block | SEMICOLON)
-> finalizer_declaration ;;


-- The PROPERTY DECLARATION. Begins with type: will be folded into member_decl.

   type=type property_name=member_name
   LBRACE accessor_declarations=accessor_declarations RBRACE
-> property_declaration ;;


-- The EVENT DECLARATION.

   EVENT type=type
   (
      -- this condition avoids the LL(k) conflict here:
      ?[: (LA(2).kind == Token_COMMA) || (LA(2).kind == Token_ASSIGN)
          || (LA(2).kind == Token_SEMICOLON)
       :]
      (#variable_declarator=variable_declarator @ COMMA) SEMICOLON
    |
      event_name=member_name
      LPAREN event_accessor_declarations RPAREN
   )
-> event_declaration ;;

-- The INDEXER DECLARATION. Begins with type: will be folded into member_decl.

   type=type (interface_type=type_name_safe DOT | 0) THIS
   LBRACKET formal_parameters=formal_parameters RBRACKET
-> indexer_declaration ;;


-- The OPERATOR DECLARATION. Two of the three derivations begin with type,
-- so this will be folded into member_decl. and need a bit of work.

   (
      type=type OPERATOR
      (
         unary_only_operator=overloadable_unary_only_operator
         LPAREN arg1_type=type arg1_name=identifier RPAREN
       |
         binary_only_operator=overloadable_binary_only_operator
         LPAREN arg1_type=type arg1_name=identifier
         COMMA  arg2_type=type arg2_name=identifier RPAREN
       |
         unary_or_binary_operator=overloadable_unary_or_binary_operator
         LPAREN arg1_type=type arg1_name=identifier
         (COMMA arg2_type=type arg2_name=identifier | 0) RPAREN
      )
    |
      (IMPLICIT | EXPLICIT) OPERATOR type=type
      LPAREN arg1_type=type arg1_name=identifier RPAREN
   )
   (operator_body=block | SEMICOLON)
-> operator_declaration ;;

 (
   BANG       [: (*yynode)->op = overloadable_unary_only_operator_ast::op_bang;      :]
 | TILDE      [: (*yynode)->op = overloadable_unary_only_operator_ast::op_tilde;     :]
 | INCREMENT  [: (*yynode)->op = overloadable_unary_only_operator_ast::op_increment; :]
 | DECREMENT  [: (*yynode)->op = overloadable_unary_only_operator_ast::op_decrement; :]
 | TRUE       [: (*yynode)->op = overloadable_unary_only_operator_ast::op_true;      :]
 | FALSE      [: (*yynode)->op = overloadable_unary_only_operator_ast::op_false;     :]
 )
-> overloadable_unary_only_operator ;;

 (
   STAR          [: (*yynode)->op = overloadable_binary_only_operator_ast::op_star;          :]
 | SLASH         [: (*yynode)->op = overloadable_binary_only_operator_ast::op_slash;         :]
 | REMAINDER     [: (*yynode)->op = overloadable_binary_only_operator_ast::op_remainder;     :]
 | BIT_AND       [: (*yynode)->op = overloadable_binary_only_operator_ast::op_bit_and;       :]
 | BIT_OR        [: (*yynode)->op = overloadable_binary_only_operator_ast::op_bit_or;        :]
 | BIT_XOR       [: (*yynode)->op = overloadable_binary_only_operator_ast::op_bit_xor;       :]
 | LSHIFT        [: (*yynode)->op = overloadable_binary_only_operator_ast::op_lshift;        :]
 | RSHIFT        [: (*yynode)->op = overloadable_binary_only_operator_ast::op_rshift;        :]
 | EQUAL         [: (*yynode)->op = overloadable_binary_only_operator_ast::op_equal;         :]
 | NOT_EQUAL     [: (*yynode)->op = overloadable_binary_only_operator_ast::op_not_equal;     :]
 | GREATER_THAN  [: (*yynode)->op = overloadable_binary_only_operator_ast::op_greater_than;  :]
 | LESS_THAN     [: (*yynode)->op = overloadable_binary_only_operator_ast::op_less_than;     :]
 | GREATER_EQUAL [: (*yynode)->op = overloadable_binary_only_operator_ast::op_greater_equal; :]
 | LESS_EQUAL    [: (*yynode)->op = overloadable_binary_only_operator_ast::op_less_equal;    :]
 )
-> overloadable_binary_only_operator ;;

   PLUS   [: (*yynode)->op = overloadable_unary_or_binary_operator_ast::op_plus;   :]
 | MINUS  [: (*yynode)->op = overloadable_unary_or_binary_operator_ast::op_minus;  :]
-> overloadable_unary_or_binary_operator ;;




-- An ARGUMENT LIST is used when calling methods
-- (not for declaring them, that's what parameter lists are for).

   #argument=argument @ COMMA
-> arguments ;;

 (
   expression=expression
     [: (*yynode)->type = argument_ast::type_value_parameter;     :]
 | REF expression=expression
     [: (*yynode)->type = argument_ast::type_reference_parameter; :]
 | OUT expression=expression
     [: (*yynode)->type = argument_ast::type_output_parameter;    :]
 )
-> argument ;;



-- All kinds of rules for types here.

-- The RETURN TYPE can only be used as return value, not in a declaration.

   regular_type=type [: (*yynode)->type = return_type_ast::type_regular; :]
   VOID              [: (*yynode)->type = return_type_ast::type_void;    :]
-> return_type ;;

-- The regular TYPE recognizes the same set of tokens as the one in the C#
-- specification, but had to be refactored quite a bit. Looks different here.

   non_array_type=non_array_type (#rank_specifier=rank_specifier)*
-> type ;;

   LBRACKET [: (*yynode)->dimension_seperator_count = 0; :]
   ( COMMA  [: (*yynode)->dimension_seperator_count++;   :] )*
   RBRACKET
-> rank_specifier ;;

   builtin_class_type=builtin_class_type
 | optionally_nullable_type=optionally_nullable_type
-> non_array_type ;;

   type_name=type_name
 | builtin_class_type=builtin_class_type
-> class_type ;;

   OBJECT [: (*yynode)->type = builtin_class_type_ast::type_object; :]
 | STRING [: (*yynode)->type = builtin_class_type_ast::type_string; :]
-> builtin_class_type ;;

-- NULLABLE TYPES are new in C# 2.0 and need to be expressed a little bit
-- differently than in LALR grammars like in the C# specification.

   non_nullable_type
   (  ?[: compatibility_mode() >= csharp20_compatibility :]
      QUESTION [: (*yynode)->nullable = true;  :]
    |
      0        [: (*yynode)->nullable = false; :]
   )
-> optionally_nullable_type ;;

   type_name=type_name
 | simple_type=simple_type
-> non_nullable_type ;;


-- Now for SIMPLE TYPES, this is easier ;)

 (
   numeric_type=numeric_type
     [: (*yynode)->type = simple_type_ast::type_numeric; :]
 | BOOL
     [: (*yynode)->type = simple_type_ast::type_bool; :]
 )
-> simple_type ;;


-- NUMERIC TYPES include INTEGRAL TYPES, FLOATING POINT TYPES, and DECIMAL.

 (
   int_type=integral_type
     [: (*yynode)->type = numeric_type_ast::type_integral; :]
 | float_type=floating_point_type
     [: (*yynode)->type = numeric_type_ast::type_floating_point; :]
 | DECIMAL
     [: (*yynode)->type = numeric_type_ast::type_decimal; :]
 )
-> numeric_type ;;

 (
   SBYTE   [: (*yynode)->type = integral_type_ast::type_sbyte;  :]
 | BYTE    [: (*yynode)->type = integral_type_ast::type_byte;   :]
 | SHORT   [: (*yynode)->type = integral_type_ast::type_short;  :]
 | USHORT  [: (*yynode)->type = integral_type_ast::type_ushort; :]
 | INT     [: (*yynode)->type = integral_type_ast::type_int;    :]
 | UINT    [: (*yynode)->type = integral_type_ast::type_uint;   :]
 | LONG    [: (*yynode)->type = integral_type_ast::type_long;   :]
 | ULONG   [: (*yynode)->type = integral_type_ast::type_ulong;  :]
 | CHAR    [: (*yynode)->type = integral_type_ast::type_char;   :]
 )
-> integral_type ;;

 (
   FLOAT   [: (*yynode)->type = floating_point_type_ast::type_float;  :]
 | DOUBLE  [: (*yynode)->type = floating_point_type_ast::type_double; :]
 )
-> floating_point_type ;;


-- TYPE NAMES and NAMESPACE NAMES are the same thing,
-- essentially qualified identifiers with optional type arguments.

   namespace_or_type_name
-> namespace_name ;;

   namespace_or_type_name
-> type_name ;;

   (  ?[: LA(2).kind == Token_SCOPE :] qualified_alias_label=identifier SCOPE
    | 0
   )
   #name_part=namespace_or_type_name_part @ DOT
-> namespace_or_type_name ;;

   identifier=identifier
   (  ?[: compatibility_mode() >= csharp20_compatibility :]
      type_arguments=type_arguments
    | 0
   )
-> namespace_or_type_name_part ;;

   namespace_or_type_name_safe
-> type_name_safe ;;

   (  ?[: LA(2).kind == Token_SCOPE :] qualified_alias_label=identifier SCOPE
    | 0
   )
   #name_part=namespace_or_type_name_part
   ( 0 [: if (LA(2).kind != Token_IDENTIFIER) break; :] -- exit the "star loop"
     DOT #name_part=namespace_or_type_name_part
   )*
-> namespace_or_type_name_safe ;;


-- QUALIFIED identifiers are either qualified ones or raw identifiers.

   #name=identifier @ DOT
-> qualified_identifier ;;




--
-- MODIFIERS, KEYWORDS, LITERALS, and the IDENTIFIER wrapper
--

   REF       [: (*yynode)->modifier = parameter_modifier_ast::mod_ref; :]
 | OUT       [: (*yynode)->modifier = parameter_modifier_ast::mod_out; :]
-> parameter_modifier ;;

-- These are all the modifiers that can occur in front of type and type member
-- declarations. They are not valid in every combination, this has to be
-- checked seperately after parsing this rule.

 (
   NEW        [: (*yynode)->modifiers |= optional_modifiers_ast::mod_new;       :]
 | PUBLIC     [: (*yynode)->modifiers |= optional_modifiers_ast::mod_public;    :]
 | PROTECTED  [: (*yynode)->modifiers |= optional_modifiers_ast::mod_protected; :]
 | INTERNAL   [: (*yynode)->modifiers |= optional_modifiers_ast::mod_internal;  :]
 | PRIVATE    [: (*yynode)->modifiers |= optional_modifiers_ast::mod_private;   :]
 | ABSTRACT   [: (*yynode)->modifiers |= optional_modifiers_ast::mod_abstract;  :]
 | SEALED     [: (*yynode)->modifiers |= optional_modifiers_ast::mod_sealed;    :]
 | STATIC     [: (*yynode)->modifiers |= optional_modifiers_ast::mod_static;    :]
 | READONLY   [: (*yynode)->modifiers |= optional_modifiers_ast::mod_readonly;  :]
 | VOLATILE   [: (*yynode)->modifiers |= optional_modifiers_ast::mod_volatile;  :]
 | VIRTUAL    [: (*yynode)->modifiers |= optional_modifiers_ast::mod_virtual;   :]
 | OVERRIDE   [: (*yynode)->modifiers |= optional_modifiers_ast::mod_override;  :]
 | EXTERN     [: (*yynode)->modifiers |= optional_modifiers_ast::mod_extern;    :]
 )*
-> optional_modifiers ;;

 (
   keyword=ABSTRACT | keyword=AS | keyword=BASE | keyword=BOOL
 | keyword=BREAK | keyword=BYTE | keyword=CASE | keyword=CATCH | keyword=CHAR
 | keyword=CHECKED | keyword=CLASS | keyword=CONST | keyword=CONTINUE
 | keyword=DECIMAL | keyword=DEFAULT | keyword=DELEGATE | keyword=DO
 | keyword=DOUBLE | keyword=ELSE | keyword=ENUM | keyword=EVENT
 | keyword=EXPLICIT | keyword=EXTERN | keyword=FINALLY | keyword=FIXED
 | keyword=FLOAT | keyword=FOREACH | keyword=FOR | keyword=GOTO | keyword=IF
 | keyword=IMPLICIT | keyword=IN | keyword=INT | keyword=INTERFACE
 | keyword=INTERNAL | keyword=IS | keyword=LOCK | keyword=LONG
 | keyword=NAMESPACE | keyword=NEW | keyword=OBJECT | keyword=OPERATOR
 | keyword=OUT | keyword=OVERRIDE | keyword=PARAMS | keyword=PRIVATE
 | keyword=PROTECTED | keyword=PUBLIC | keyword=READONLY | keyword=REF
 | keyword=RETURN | keyword=SBYTE | keyword=SEALED | keyword=SHORT
 | keyword=SIZEOF | keyword=STACKALLOC | keyword=STATIC | keyword=STRING
 | keyword=STRUCT | keyword=SWITCH | keyword=THIS | keyword=THROW | keyword=TRY
 | keyword=TYPEOF | keyword=UINT | keyword=ULONG | keyword=UNCHECKED
 | keyword=UNSAFE | keyword=USHORT | keyword=USING | keyword=VIRTUAL
 | keyword=VOID | keyword=VOLATILE | keyword=WHILE
 )
-> keyword ;;

 (
   ident=IDENTIFIER
 | ident=ADD
 | ident=ALIAS
 | ident=GET
 | ident=GLOBAL
 | ident=PARTIAL
 | ident=REMOVE
 | ident=SET
 | ident=VALUE
 | ident=WHERE
 | ident=YIELD
 | ident=ASSEMBLY
 )
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
-- Appendix: Rule stubs
--

STUB_A -> type_arguments ;;
STUB_B -> type_parameters ;;
STUB_C -> type_parameter_constraints_clauses ;;
STUB_D -> class_member_declaration ;;
STUB_E -> struct_member_declaration ;;
STUB_F -> interface_member_declaration ;;
STUB_G -> constant_expression ;;
STUB_I -> formal_parameters ;;
STUB_J -> member_name ;;
STUB_K -> array_initializer ;;
LBRACE STUB_L RBRACE -> block ;;
identifier -> expression ;;
STUB_M -> accessor_declarations ;;
STUB_N -> event_accessor_declarations ;;







--
-- Code segments copied to the implementation (.cpp) file.
-- If existent, kdevelop-pg's current syntax requires this block to occur
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
