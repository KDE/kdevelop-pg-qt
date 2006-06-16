-- This file is part of KDevelop.
-- Copyright (c) 2005 Jakob Petsovits <jpetso@gmx.at>
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


-- Grammar for Java 1.3, 1.4 or 1.5
-- Modelled after the public domain ANTLR Java 1.5 grammar at
-- http://www.antlr.org/grammar/1090713067533/index.html
-- (Version 1.22.5 from January 03, 2005)
-- and the reference grammar of the Java language specification,
-- Third Edition, at http://java.sun.com/docs/books/jls/.



-- Known problematic conflicts (4 conflicts), requiring automatic LL(k):
--  - Part of the first/follow ABSTRACT, CLASS, ENUM, FINAL etc. conflict
--    in compilation_unit (namely: package_declaration vs. type_declaration).
--    Solved by lookahead_is_package_declaration().
--    (1 conflict)
--  - The first/first BOOLEAN, BYTE, CHAR, DOUBLE, etc. conflict in
--    block_statement which is essentially an expression statements vs.
--    variable declarations conflict (ignore the modifier conflicts,
--    they are there by design and are completely harmless).
--    The real conflict is just the IDENTIFIER one.
--    Solved by lookahead_is_parameter_declaration().
--    The SYNCHRONIZED conflict in this error message is also
--    independent and has been resolved too.
--    (1 conflict)
--  - The first/first BOOLEAN, BYTE, CHAR, DOUBLE etc. conflict in for_control.
--    This is the same variable/parameter declaration vs. expression issue
--    that block_statement also suffers from.
--    Also solved by lookahead_is_parameter_declaration().
--    (1 conflict)
--  - The first/first LPAREN conflict in unary_expression_not_plusminus
--    which is cast_expression vs. primary_expression.
--    Solved by lookahead_is_cast_expression().
--    (1 conflict)

-- Known harmless or resolved conflicts (17 conflicts):
--  - The first/follow IMPORT, AT conflict in compilation_unit
--    (done right by default, 1 conflict)
--  - Part of the first/follow ABSTRACT, CLASS, ENUM, FINAL etc. conflict
--    in compilation_unit. Everything except AT is harmless and done right
--    by default. (already counted in the problematic conflicts section)
--  - The first/follow LBRACKET conflict in optional_declarator_brackets
--    (done right by default, 1 conflict)
--  - The first/follow COMMA conflict in variable_declaration_rest: greedy is ok
--    (done right by default, 1 conflict)
--  - The first/follow LBRACKET conflict in primary_atom
--    (manually resolved, 1 conflict)
--  - The first/follow AT conflict in optional_modifiers: greedy is ok
--    (done right by default, 1 conflict)
--  - The first/first IDENTIFIER conflicts in *_field,
--    between method_name and variable_name
--    (manually resolved, 4 conflicts)
--  - The first/first IDENTIFIER conflict in class_field
--    (manually resolved, 1 conflict)
--  - The first/first STATIC conflict in class_field
--    (manually resolved, 1 conflict)
--  - The first/first IDENTIFIER conflict in annotation_arguments
--    (manually resolved, 1 conflict)
--  - The first/first FINAL, SYNCHRONIZED, AT conflict in block_statement,
--    which is a side product of the lookahead solution and solved by it
--    as well. Harmless because lookahead chooses the right one.
--    (manually resolved, 1 conflict)
--  - The first/first IDENTIFIER conflict (labels) in statement
--    (manually resolved, 1 conflict)
--  - The first/first IDENTIFIER conflicts in primary_selector and
--    super_suffix. Could be written without conflict, but done on purpose
--    to tell methods (with possible type arguments) and variables
--    (without these) apart. (2 identical conflicts)
--  - The first/follow LBRACKET conflict in array_creator_rest.
--    This is by design and works as expected.
--    (manually resolved, 1 conflict)

-- Total amount of conflicts: 21


--
-- Global declarations
--

[:
#include <string>
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
   * The compatibility_mode status variable tells which version of Java
   * should be checked against.
   */
  enum java_compatibility_mode {
    java13_compatibility = 130,
    java14_compatibility = 140,
    java15_compatibility = 150,
  };

  java::java_compatibility_mode compatibility_mode();
  void set_compatibility_mode( java::java_compatibility_mode mode );

  enum problem_type {
    error,
    warning,
    info
  };
  void report_problem( java::problem_type type, const char* message );
  void report_problem( java::problem_type type, std::string message );
:]

%member (parserclass: private declaration)
[:
  java::java_compatibility_mode _M_compatibility_mode;

  // ltCounter stores the amount of currently open type arguments rules,
  // all of which are beginning with a less than ("<") character.
  // This way, also SIGNED_RSHIFT (">>") and UNSIGNED_RSHIFT (">>>") can be used
  // to close type arguments rules, in addition to GREATER_THAN (">").
  int ltCounter;

  // ellipsisOccurred is used as a means of communication between
  // parameter_declaration_list and parameter_declaration_ellipsis to determine
  // if an ellipsis was already in the list (then no more declarations
  // may follow).
  bool ellipsisOccurred;

  // Lookahead hacks
  bool lookahead_is_package_declaration();
  bool lookahead_is_parameter_declaration();
  bool lookahead_is_cast_expression();
:]

%member (parserclass: constructor)
  [: _M_compatibility_mode = java15_compatibility; :]


--
-- Additional AST members
--

%member (import_declaration: public declaration)
  [: bool static_import; :]

%member (parameter_declaration_ellipsis: public declaration)
  [: bool has_ellipsis; :]

%member (optional_parameter_modifiers: public declaration)
  [: bool mod_final; :]

%member (wildcard_type_bounds: public declaration)
[:
  enum extends_or_super_enum {
    extends,
    super
  };
  extends_or_super_enum extends_or_super;
:]

%member (builtin_type: public declaration)
[:
  enum builtin_type_enum {
    type_void,
    type_boolean,
    type_byte,
    type_char,
    type_short,
    type_int,
    type_float,
    type_long,
    type_double
  };
  builtin_type_enum type;
:]

%member (qualified_identifier_with_optional_star: public declaration)
  [: bool has_star; :]

%member (optional_declarator_brackets: public declaration)
  [: int bracket_count; :]
%member (mandatory_declarator_brackets: public declaration)
  [: int bracket_count; :]

%member (annotation: public declaration)
  [: bool has_parentheses; :]

%member (statement: public declaration)
[:
  enum statement_kind_enum {
    kind_empty_statement,
    kind_block_statement,
    kind_assert_statement,
    kind_if_statement,
    kind_for_statement,
    kind_while_statement,
    kind_do_while_statement,
    kind_try_statement,
    kind_switch_statement,
    kind_synchronized_statement,
    kind_return_statement,
    kind_throw_statement,
    kind_break_statement,
    kind_continue_statement,
    kind_labeled_statement,
    kind_expression_statement
  };
  statement_kind_enum statement_kind;
:]

%member (switch_case: public declaration)
[:
  enum branch_type_enum {
    case_branch,
    default_branch
  };
  branch_type_enum branch_type;
:]

%member (expression: public declaration)
[:
  enum assignment_operator_enum {
    no_assignment,
    op_assign,
    op_plus_assign,
    op_minus_assign,
    op_star_assign,
    op_slash_assign,
    op_bit_and_assign,
    op_bit_or_assign,
    op_bit_xor_assign,
    op_remainder_assign,
    op_lshift_assign,
    op_signed_rshift_assign,
    op_unsigned_rshift_assign
  };
  assignment_operator_enum assignment_operator;
:]

%member (equality_expression_rest: public declaration)
[:
  enum equality_operator_enum {
    op_equal,
    op_not_equal
  };
  equality_operator_enum equality_operator;
:]

%member (relational_expression_rest: public declaration)
[:
  enum relational_operator_enum {
    op_less_than,
    op_greater_than,
    op_less_equal,
    op_greater_equal
  };
  relational_operator_enum relational_operator;
:]

%member (shift_expression_rest: public declaration)
[:
  enum shift_operator_enum {
    op_lshift,
    op_signed_rshift,
    op_unsigned_rshift
  };
  shift_operator_enum shift_operator;
:]

%member (additive_expression_rest: public declaration)
[:
  enum additive_operator_enum {
    op_plus,
    op_minus
  };
  additive_operator_enum additive_operator;
:]

%member (multiplicative_expression_rest: public declaration)
[:
  enum multiplicative_operator_enum {
    op_star,
    op_slash,
    op_remainder
  };
  multiplicative_operator_enum multiplicative_operator;
:]

%member (unary_expression: public declaration)
[:
  enum unary_expression_type_enum {
    type_incremented_expression,
    type_decremented_expression,
    type_unary_minus_expression,
    type_unary_plus_expression,
    type_unary_expression_not_plusminus
  };
  unary_expression_type_enum type;
:]

%member (postfix_operator: public declaration)
[:
  enum postfix_operator_enum {
    op_increment,
    op_decrement
  };
  postfix_operator_enum postfix_operator;
:]

%member (primary_atom: public declaration)
[:
  enum primary_atom_kind_enum {
    kind_literal,
    kind_new_expression,
    kind_parenthesis_expression,
    kind_builtin_type_dot_class,
    kind_array_type_dot_class,
    kind_type_name,
    kind_this_call_no_type_arguments,
    kind_this_call_with_type_arguments,
    kind_super_call_no_type_arguments,
    kind_super_call_with_type_arguments,
    kind_method_call_no_type_arguments,
    kind_method_call_with_type_arguments,
  };
  primary_atom_kind_enum primary_atom_kind;
:]

%member (optional_modifiers: public declaration)
[:
  enum modifier_enum {
    mod_private      = 1,
    mod_public       = 2,
    mod_protected    = 4,
    mod_static       = 8,
    mod_transient    = 16,
    mod_final        = 32,
    mod_abstract     = 64,
    mod_native       = 128,
    mod_synchronized = 256,
    mod_volatile     = 512,
    mod_strictfp     = 1024
  };
  int modifiers;
:]

%member (literal: public declaration)
[:
  enum literal_type_enum {
    type_true,
    type_false,
    type_null,
    type_integer,
    type_floating_point,
    type_character,
    type_string
  };
  literal_type_enum literal_type;
:]



--
-- List of defined tokens
--

-- keywords:
%token ABSTRACT ("abstract"), ASSERT ("assert"), BOOLEAN ("boolean"),
       BREAK ("break"), BYTE ("byte"), CASE ("case"), CATCH ("catch"),
       CHAR ("char"), CLASS ("class"), CONST ("const"), CONTINUE ("continue"),
       DEFAULT ("default"), DO ("do"), DOUBLE ("double"), ELSE ("else"),
       ENUM ("enum"), EXTENDS ("extends"), FINAL ("final"),
       FINALLY ("finally"), FLOAT ("float"), FOR ("for"), GOTO ("goto"),
       IF ("if"), IMPLEMENTS ("implements"), IMPORT ("import"),
       INSTANCEOF ("instanceof"), INT ("int"), INTERFACE ("interface"),
       LONG ("long"), NATIVE ("native"), NEW ("new"), PACKAGE ("package"),
       PRIVATE ("private"), PROTECTED ("protected"), PUBLIC ("public"),
       RETURN ("return"), SHORT ("short"), STATIC ("static"),
       STRICTFP ("strictfp"), SUPER ("super"), SWITCH ("switch"),
       SYNCHRONIZED ("synchronized"), THIS ("this"), THROW ("throw"),
       THROWS ("throws"), TRANSIENT ("transient"), TRY ("try"), VOID ("void"),
       VOLATILE ("volatile"), WHILE ("while") ;;

-- seperators:
%token LPAREN ("("), RPAREN (")"), LBRACE ("{"), RBRACE ("}"), LBRACKET ("["),
       RBRACKET ("]"), SEMICOLON (";"), COMMA (","), DOT ("."), AT ("@") ;;

-- operators:
%token ASSIGN ("="), LESS_THAN ("<"), GREATER_THAN (">"), BANG ("!"),
       TILDE ("~"), QUESTION ("?"), COLON (":"), EQUAL ("=="),
       LESS_EQUAL ("<="), GREATER_EQUAL (">="), NOT_EQUAL ("!="),
       LOG_AND ("&&"), LOG_OR ("||"), INCREMENT ("++"), DECREMENT ("--"),
       PLUS ("+"), MINUS ("-"), STAR ("*"), SLASH ("/"), BIT_AND ("&"),
       BIT_OR ("|"), BIT_XOR ("^"), REMAINDER ("%"), LSHIFT ("<<"),
       SIGNED_RSHIFT (">>"), UNSIGNED_RSHIFT (">>>"), PLUS_ASSIGN ("+="),
       MINUS_ASSIGN ("-="), STAR_ASSIGN ("*="), SLASH_ASSIGN ("/="),
       BIT_AND_ASSIGN ("&="), BIT_OR_ASSIGN ("|="), BIT_XOR_ASSIGN ("^="),
       REMAINDER_ASSIGN ("%="), LSHIFT_ASSIGN ("<<="),
       SIGNED_RSHIFT_ASSIGN (">>="), UNSIGNED_RSHIFT_ASSIGN (">>>="),
       ELLIPSIS ("...") ;;

-- literals and identifiers:
%token TRUE ("true"), FALSE ("false"), NULL ("null"),
       INTEGER_LITERAL ("integer literal"),
       FLOATING_POINT_LITERAL ("floating point literal"),
       CHARACTER_LITERAL ("character literal"),
       STRING_LITERAL ("string literal"), IDENTIFIER ("identifier") ;;

-- token that makes the parser fail in any case:
%token INVALID ("invalid token") ;;




-- The grammar starts with compilation_unit,
-- which is equivalent to a single source file.

   0 [: ltCounter = 0; :]
   ( -- The first thing there is (haha) is a serious conflict between
     -- package_declaration and type_declaration, both of which can start
     -- with annotations. As this is only solvable with LL(k), it's
     -- implemented with a workaround hack until backtracking or real
     -- LL(k) is available. When this is available, you can also say:
     -- ?( package_declararation_lookahead ) instead of the current one:
     ?[: lookahead_is_package_declaration() == true :]
      package_declaration=package_declaration
    | 0
   )
   (#import_declaration=import_declaration)*
   (#type_declaration=type_declaration)*
-> compilation_unit ;;

--    (#annotation=annotation)* PACKAGE
-- -> package_declaration_lookahead ;;  -- only use for lookaheads!



-- A PACKAGE DECLARATION: optional annotations followed by "package",
--                        then the package identifier.
-- 1 first/first conflict, because annotation as well as "| 0"
-- inside of compilation_unit may both be 0. The ANTLR grammar
-- checks on ?[:annotations "package":] to do a package_declaration.

   (#annotation=annotation)*
   PACKAGE package_name=qualified_identifier SEMICOLON
-> package_declaration ;;


-- An IMPORT DECLARATION is "import" followed by a package or type (=class) name.

   IMPORT [: (*yynode)->static_import = false; :]
   (  STATIC [: (*yynode)->static_import = true;  :]
    | 0      -- [: (*yynode)->static_import = false; :]
             -- doesn't compile, probably a kdev-pg bug. TODO: fix
   )
   identifier_name=qualified_identifier_with_optional_star SEMICOLON
-> import_declaration ;;


-- A TYPE DECLARATION is either a class, interface, enum or annotation.

   (  modifiers=optional_modifiers
      (  class_declaration=class_declaration
       | enum_declaration=enum_declaration
       | interface_declaration=interface_declaration
       | annotation_type_declaration=annotation_type_declaration
      )
    | SEMICOLON
   )
-> type_declaration ;;



-- Definition of a Java CLASS

   CLASS class_name=identifier
   (type_parameters=type_parameters  | 0)  -- it might have type parameters
   (extends=class_extends_clause     | 0)  -- it might have a super class
   (implements=implements_clause     | 0)  -- it might implement some interfaces
   body=class_body
-> class_declaration ;;


-- Definition of a Java INTERFACE

   INTERFACE interface_name=identifier
   (type_parameters=type_parameters  | 0)  -- it might have type parameters
   (extends=interface_extends_clause | 0)  -- it might extend other interfaces
   body=interface_body
-> interface_declaration ;;


-- Definition of ENUMERATIONs and ANNOTATION TYPEs

   ENUM enum_name=identifier
   (implements=implements_clause     | 0)  -- it might implement some interfaces
   body=enum_body
-> enum_declaration ;;

   AT INTERFACE annotation_type_name=identifier
   body=annotation_type_body
-> annotation_type_declaration ;;



-- BODIES of classes, interfaces, annotation types and enums.

   LBRACE (#declaration=class_field)* RBRACE
-> class_body ;;

   LBRACE (#declaration=interface_field)* RBRACE
-> interface_body ;;

   LBRACE (#annotation_type_field=annotation_type_field)* RBRACE
-> annotation_type_body ;;

-- In an enum body, you can have zero or more enum constants
-- followed by any number of fields like a regular class.

   LBRACE
   ( #enum_constant=enum_constant
     @ ( 0 [: if ( LA(2).kind == Token_SEMICOLON
                || LA(2).kind == Token_RBRACE )
              { break; } :] -- if the list is over, then exit the loop
         COMMA
       )
   | 0
   )
   ( COMMA | 0 )
   ( SEMICOLON (#class_field=class_field)* | 0 )
   RBRACE
-> enum_body ;;

-- An enum constant may have optional parameters and may have a class body

   ( #annotation=annotation )* identifier=identifier
   ( LPAREN arguments=argument_list RPAREN | 0 )
   ( body=enum_constant_body | 0 )
-> enum_constant ;;

   LBRACE (#declaration=enum_constant_field)* RBRACE
-> enum_constant_body ;;



-- Short CLAUSES used in various declarations

   EXTENDS type=class_or_interface_type
-> class_extends_clause ;;

   EXTENDS #type=class_or_interface_type @ COMMA
-> interface_extends_clause ;;

   IMPLEMENTS #type=class_or_interface_type @ COMMA
-> implements_clause ;;

   THROWS #identifier=qualified_identifier @ COMMA
-> throws_clause ;;




-- Now on to what happens inside the class, interface, etc. bodies:


-- An ANNOTATION TYPE FIELD. The Java specification has a bug here,
-- two different AnnotationTypeElementDeclarations in the book's body
-- and the grammar appendix. I chose the one from the body,
-- which is the same that the ANTLR grammar also uses.

 ( modifiers=optional_modifiers
   (  class_declaration=class_declaration
    | enum_declaration=enum_declaration
    | interface_declaration=interface_declaration
    | annotation_type_declaration=annotation_type_declaration
    |
      type=type_specification
      (                      -- annotation method without arguments:
         ?[: LA(2).kind == Token_LPAREN :] -- resolves the identifier conflict
                                      -- between method_name and variable_name
         identifier=identifier
         LPAREN RPAREN
         -- declarator_brackets=optional_declarator_brackets -- ANTLR grammar's bug:
         -- It's not in the Java Spec, and obviously has been copied
         -- from classField even if it doesn't belong here.
         (DEFAULT annotation_element_value=annotation_element_value | 0)
         SEMICOLON
       |                     -- or a ConstantDeclaration:
         #variable_declarator=variable_declarator @ COMMA
         SEMICOLON
      )
   )
 | SEMICOLON
 )
-> annotation_type_field ;;


-- A CLASS FIELD, representing the various things
-- that can be defined inside a class.

 ( ?[: !(yytoken == Token_STATIC && LA(2).kind == Token_LBRACE) :]
    -- resolves the 'static' conflict, see further down
   modifiers=optional_modifiers
   (  class_declaration=class_declaration
    | enum_declaration=enum_declaration
    | interface_declaration=interface_declaration
    | annotation_type_declaration=annotation_type_declaration
    |
      -- A generic method/ctor has the type_parameters before the return type.
      -- This is not allowed for variable definitions, but this production
      -- allows it, a semantic check could be used if you wanted.
      -- (Note: kdev-pg does not yet support semantic checks.)
      (type_params=type_parameters | 0)
      (
         -- constructor declaration (without prepended type_specification)
         ?[: LA(2).kind == Token_LPAREN :]
         -- resolves the identifier conflict with type_specification
         constructor_name=identifier
         constructor_parameters=parameter_declaration_list
         (constructor_throws_clause=throws_clause | 0)
         constructor_body=block
         -- leaving out explicit this(...) and super(...) invocations,
         -- these are just normal statements for the grammar
       |
         -- method or variable declaration
         type=type_specification
         (
            ?[: LA(2).kind == Token_LPAREN :] -- resolves the identifier
                          -- conflict between method_name and variable_name
            method_name=identifier
            method_parameters=parameter_declaration_list
            method_declarator_brackets=optional_declarator_brackets
            (method_throws_clause=throws_clause | 0)
            (method_body=block | SEMICOLON)
          |
            #variable_declarator=variable_declarator @ COMMA
            SEMICOLON
         )
      )
   )
 |
   instance_initializer_block=block  -- "{...}" instance initializer
 |
   -- The static class initializer block ("static {...}") has a conflict with
   -- the modifiers from above, which can also be static. A block must always
   -- start with "{", so when encountering static, this can be used to resolve
   -- this conflict.
   ?[: LA(2).kind == Token_LBRACE :] STATIC static_initializer_block=block
 |
   SEMICOLON
 )
-> class_field ;;


-- An ENUM CONSTANT FIELD is just like a class field but without
-- the possibility of a constructor definition or a static initializer.

 ( modifiers=optional_modifiers
   (  class_declaration=class_declaration
    | enum_declaration=enum_declaration
    | interface_declaration=interface_declaration
    | annotation_type_declaration=annotation_type_declaration
    |
      -- A generic method/ctor has the type_parameters before the return type.
      -- This is not allowed for variable definitions, but this production
      -- allows it, a semantic check could be used if you wanted.
      -- (Note: kdev-pg does not yet support semantic checks.)
      (type_params=type_parameters | 0) type=type_specification
      (
         ?[: LA(2).kind == Token_LPAREN :] -- resolves the identifier conflict
                                      -- between method_name and variable_name
         method_name=identifier
         method_parameters=parameter_declaration_list
         method_declarator_brackets=optional_declarator_brackets
         (method_throws_clause=throws_clause | 0)
         (method_body=block | SEMICOLON)
       |
         #variable_declarator=variable_declarator @ COMMA
         SEMICOLON
      )
   )
 | instance_initializer_block=block  -- "{...}" instance initializer
 | SEMICOLON
 )
-> enum_constant_field ;;


-- An INTERFACE FIELD is the same as an enum constant field but without
-- the possibility of any initializers or method blocks.

 ( modifiers=optional_modifiers
   (  class_declaration=class_declaration
    | enum_declaration=enum_declaration
    | interface_declaration=interface_declaration
    | annotation_type_declaration=annotation_type_declaration
    |
      -- A generic method/ctor has the type_parameters before the return type.
      -- This is not allowed for variable definitions, but this production
      -- allows it, a semantic check could be used if you wanted.
      -- (Note: kdev-pg does not yet support semantic checks.)
      (type_params=type_parameters | 0) type=type_specification
      (
         ?[: LA(2).kind == Token_LPAREN :] -- resolves the identifier conflict
                                      -- between method_name and variable_name
         method_name=identifier
         method_parameters=parameter_declaration_list
         method_declarator_brackets=optional_declarator_brackets
         (method_throws_clause=throws_clause | 0)
         SEMICOLON
       |
         #variable_declarator=variable_declarator @ COMMA
         SEMICOLON
      )
   )
 | SEMICOLON
 )
-> interface_field ;;




-- So much for the rough structure, now we get into the details


-- A PARAMETER DECLARATION LIST is part of a method header and can contain
-- zero or more parameters, optionally ending with a variable-length parameter.
-- It's not as hackish as it used to be, nevertheless it could still be nicer.
-- TODO: Maybe some fine day rule parameters will be implemented.
--       In that case, please make ellipsisOccurred totally local here.

   LPAREN [: ellipsisOccurred = false; :]
   (
      #parameter_declaration=parameter_declaration_ellipsis
      @ ( 0 [: if( ellipsisOccurred == true ) { break; } :]
            -- Don't proceed after the ellipsis. If there's a cleaner way
            -- to exit the loop when ellipsisOccurred == true,
            -- please use that instead of this construct (see below).
          COMMA
        )
    |
      0
   )
   RPAREN
-> parameter_declaration_list ;;

-- How it _should_ look:
--
--    LPAREN [: ellipsisOccurred = false; :]
--    (
--       #parameter_declaration=parameter_declaration_ellipsis
--       @ ( ?[: ellipsisOccurred == false :] COMMA )
--           -- kdev-pg dismisses this condition!
--     |
--       0
--    )
--    RPAREN
-- -> parameter_declaration_list ;;

   parameter_modifiers=optional_parameter_modifiers
   type_specification=type_specification [: (*yynode)->has_ellipsis = false; :]
   (  ELLIPSIS [: (*yynode)->has_ellipsis = true; ellipsisOccurred = true; :]
    | 0        -- [: (*yynode)->has_ellipsis = false; :]
               -- doesn't compile, probably a kdev-pg bug. TODO: fix
   )
   variable_identifier=identifier
   declarator_brackets=optional_declarator_brackets
-> parameter_declaration_ellipsis ;;

-- This PARAMETER DECLARATION rule is not used in parameter_declaration_list,
-- and lacks the ellipsis possibility & handling. It's used in try_handler
-- and in for_control.

   parameter_modifiers=optional_parameter_modifiers
   type_specification=type_specification
   variable_identifier=identifier
   declarator_brackets=optional_declarator_brackets
-> parameter_declaration ;;

   0 [: (*yynode)->mod_final = false; :]
   (  FINAL [: (*yynode)->mod_final = true; :]
    | #mod_annotation=annotation
   )*
-> optional_parameter_modifiers ;;



-- The body of a CONSTRUCTOR METHOD is the same as a normal block, except that
-- it's possible to have a constructor call like this(...) or super(...)
-- at the beginning of the block. This causes a conflict which is difficult
-- to resolve, so class_field uses block instead of constructor_body.
--
--    LBRACE
--    (explicit_constructor_invocation=explicit_constructor_invocation | 0)
--    (#statement=statement)*
--    RBRACE
-- -> constructor_body ;;
--
-- -- Catches obvious constructor calls, but not the expr.super(...) calls:
--
--    (  ?[: compatibility_mode() >= java15_compatibility :]
--       type_arguments=type_arguments
--     | 0
--    )
--    (invocated_constructor=THIS | invocated_constructor=SUPER)
--    LPAREN arguments=argument_list RPAREN SEMICOLON
-- -> explicit_constructor_invocation ;;






-- Type parameters and type arguments, the two rules responsible for the
-- greater-than special casing. (This is the generic aspect in Java >= 1.5.)

-- TYPE PARAMETERS are used in class, interface etc. declarations to
-- determine the generic types allowed as type argument.

   LESS_THAN [: int currentLtLevel = ltCounter; ltCounter++; :]
   #type_parameter=type_parameter @ COMMA
   (
      type_arguments_or_parameters_end
      -- make sure we have gobbled up enough '>' characters
      -- if we are at the "top level" of nested type_parameters productions
      [: if( currentLtLevel == 0 && ltCounter != currentLtLevel )
          { return false; }
       :]
      -- TODO: error message, saying that the amount of ">" chars is incorrect
    |
      0  -- they can also be changed by type_parameter or type_argument
   )
-> type_parameters ;;

   identifier=identifier
   (EXTENDS (#extends_type=class_or_interface_type @ BIT_AND) | 0)
-> type_parameter ;;


-- TYPE ARGUMENTS are used in initializers, invocations, etc. to
-- specify the exact types for this generic class/method instance.

   LESS_THAN [: int currentLtLevel = ltCounter; ltCounter++; :]
   #type_argument=type_argument
   @ ( 0 [: if( ltCounter != currentLtLevel + 1 ) { break; } :]
       COMMA
     ) -- only proceed when we are at the right nesting level
   (
      type_arguments_or_parameters_end
      -- make sure we have gobbled up enough '>' characters
      -- if we are at the "top level" of nested type_argument productions
      [: if( currentLtLevel == 0 && ltCounter != currentLtLevel )
          { return false; }
       :]
      -- TODO: error message, saying that the amount of ">" chars is incorrect
    |
      0  -- they can also be changed by type_parameter or type_argument
   )
-> type_arguments ;;

   LESS_THAN [: int currentLtLevel = ltCounter; ltCounter++; :]
   #type_argument_specification=type_argument_specification
   @ ( 0 [: if( ltCounter != currentLtLevel + 1 ) { break; } :]
       COMMA
     ) -- only proceed when we are at the right nesting level
   (
      type_arguments_or_parameters_end
      -- make sure we have gobbled up enough '>' characters
      -- if we are at the "top level" of nested type_argument productions
      [: if( currentLtLevel == 0 && ltCounter != currentLtLevel )
          { return false; }
       :]
      -- TODO: error message, saying that the amount of ">" chars is incorrect
    |
      0  -- they can also be changed by type_parameter or type_argument
   )
-> non_wildcard_type_arguments ;;

   type_argument_specification=type_argument_specification
 | wildcard_type=wildcard_type
-> type_argument ;;

-- Any type specification except primitive types is allowed as type argument.
-- Arrays of primitive types are allowed nonetheless.

   class_type=class_type_specification
 | builtin_type_array=builtin_type_array_specification
-> type_argument_specification ;;

   QUESTION (bounds=wildcard_type_bounds | 0)
-> wildcard_type ;;

   (  EXTENDS [: (*yynode)->extends_or_super = wildcard_type_bounds_ast::extends; :]
    | SUPER   [: (*yynode)->extends_or_super = wildcard_type_bounds_ast::super; :]
   )
   type=class_type_specification
-> wildcard_type_bounds ;;


   GREATER_THAN    [: ltCounter -= 1; :]  -- ">"
 | SIGNED_RSHIFT   [: ltCounter -= 2; :]  -- ">>"
 | UNSIGNED_RSHIFT [: ltCounter -= 3; :]  -- ">>>"
-> type_arguments_or_parameters_end ;;




-- All kinds of rules for types here.

-- A TYPE SPECIFICATION is a type name with possible brackets afterwards
-- (which would make it an array type). Called "Type" in the Java spec.

   class_type_spec=class_type_specification
 | builtin_type_spec=builtin_type_specification
-> type_specification ;;

   type=class_or_interface_type
   declarator_brackets=optional_declarator_brackets
-> class_type_specification ;;

   type=builtin_type declarator_brackets=optional_declarator_brackets
-> builtin_type_specification ;;

   type=builtin_type declarator_brackets=mandatory_declarator_brackets
-> builtin_type_array_specification ;;


-- A SIMPLE TYPE SPECIFICATION is just a type name,
-- with no possibility of brackets afterwards.

   class_or_interface_type=class_or_interface_type
 | builtin_type=builtin_type
-> type_specification_noarray ;;

-- The primitive types. The Java specification doesn't include void here,
-- but the ANTLR grammar works that way, and so does this one.

   VOID    [: (*yynode)->type = builtin_type_ast::type_void;    :]
 | BOOLEAN [: (*yynode)->type = builtin_type_ast::type_boolean; :]
 | BYTE    [: (*yynode)->type = builtin_type_ast::type_byte;    :]
 | CHAR    [: (*yynode)->type = builtin_type_ast::type_char;    :]
 | SHORT   [: (*yynode)->type = builtin_type_ast::type_short;   :]
 | INT     [: (*yynode)->type = builtin_type_ast::type_int;     :]
 | FLOAT   [: (*yynode)->type = builtin_type_ast::type_float;   :]
 | LONG    [: (*yynode)->type = builtin_type_ast::type_long;    :]
 | DOUBLE  [: (*yynode)->type = builtin_type_ast::type_double;  :]
-> builtin_type ;;

   #part=class_or_interface_type_part @ DOT
-> class_or_interface_type ;;

   identifier=identifier
   (  ?[: compatibility_mode() >= java15_compatibility :]
      type_arguments=type_arguments
    | 0
   )
-> class_or_interface_type_part ;;



-- QUALIFIED identifiers are either qualified ones or raw identifiers.

   #name=identifier @ DOT
-> qualified_identifier ;;

   #name=identifier
   ( 0 [: if (LA(2).kind != Token_IDENTIFIER) { break; } :]
     DOT #name=identifier
   )*
-> qualified_identifier_safe ;; -- lookahead version of the above

   #name=identifier [: (*yynode)->has_star = false; :]
   ( DOT (  #name=identifier
          | STAR    [: (*yynode)->has_star = true; break; :]
                       -- break -> no more identifiers after the star
         )
   )*
-> qualified_identifier_with_optional_star ;;

-- Declarator brackets are part of a type specification, like String[][]
-- They are always empty, only have to be counted.

   ( LBRACKET RBRACKET [: (*yynode)->bracket_count++; :] )*
-> optional_declarator_brackets ;;

   ( LBRACKET RBRACKET [: (*yynode)->bracket_count++; :] )+
-> mandatory_declarator_brackets ;;




-- ANNOTATIONS look for example like @Info( name="Jakob", born=1983 ),
-- or @Info("Jakob"), or just @Info, and are attached to a method, class or package.
-- @Info is equivalent to @Info().

   AT type_name=qualified_identifier
   (  LPAREN (args=annotation_arguments | 0) RPAREN
        [: (*yynode)->has_parentheses = true; :]
    | 0 [: (*yynode)->has_parentheses = false; :]
   )
-> annotation ;;

 ( ( ?[: LA(2).kind == Token_ASSIGN :]
     #value_pair=annotation_element_value_pair @ COMMA
   )
 | element_value=annotation_element_value  -- element_name is "value" here
 )
-> annotation_arguments ;;

   element_name=identifier ASSIGN element_value=annotation_element_value
-> annotation_element_value_pair ;;

   cond_expression=conditional_expression
 | annotation=annotation
 | element_array_initializer=annotation_element_array_initializer
-> annotation_element_value ;;

-- Same as annotation_element_value, but array_initializer is excluded.
-- That's because nested annotation array initialisers are not valid.
-- (The Java specification hides that in a short "discussion" area.)
   cond_expression=conditional_expression
 | annotation=annotation
-> annotation_element_array_value ;;

   LBRACE
   ( #element_value=annotation_element_array_value @ COMMA | 0 )
   ( COMMA | 0 )
   RBRACE
-> annotation_element_array_initializer ;;




-- And now for the good stuff: statements, expressions and the likes. Yay!

-- This is a BLOCK, a list of statements. It is used in many contexts:
-- Inside a class definition prefixed with "static" as class initializer
-- Inside a class definition without "static" as instance initializer
-- As the body of a method
-- As a completely independent braced block of code inside a method,
--  starting a new scope for variable definitions

   LBRACE (#statement=block_statement)* RBRACE
-> block ;;

-- A BLOCK STATEMENT is either a normal statement, a variable declaration
-- or a type declaration (you know, nested classes and the likes...).
-- To avoid ambiguities, the variable declarations and type declarations
-- are handled together. But that doesn't resolve the other conflict.

 (
   -- Variable declarations, as well as expression statements, can start with
   -- class1<xxx>.bla or similar. This is only soĺvable with LL(k), so what's
   -- needed here is the following hack lookahead function, until backtracking
   -- or real LL(k) is implemented. Note that a variable declaration starts
   -- just like a mere parameter declaration.
   ?[: lookahead_is_parameter_declaration() == true :]
   variable_declaration=variable_declaration SEMICOLON
 |
   ?[: (yytoken != Token_SYNCHRONIZED) ||
       (yytoken == Token_SYNCHRONIZED && LA(2).kind == Token_LPAREN)
     :]  -- resolves the SYNCHRONIZED conflict between statement and modifier.
   statement=statement
 |
   -- Inside a block, our four "complex types" can be declared
   -- (enums, nested classes and the likes...):
   modifiers=optional_modifiers
   (  class_declaration=class_declaration
    | enum_declaration=enum_declaration
    | interface_declaration=interface_declaration
    | annotation_type_declaration=annotation_type_declaration
   )
 )
-> block_statement ;;


-- VARIABLE DECLARATIONS, initializers, etc.

   initial_declaration=parameter_declaration
   rest=variable_declaration_rest
-> variable_declaration ;;

   ( ASSIGN first_initializer=variable_initializer | 0 )
   ( COMMA #variable_declarator=variable_declarator )*
-> variable_declaration_rest ;;

-- A VARIABLE DECLARATOR, as used in a variable_declaration or *_field

   variable_name=identifier
   declarator_brackets=optional_declarator_brackets
   ( ASSIGN initializer=variable_initializer | 0 )
-> variable_declarator ;;

   ( expression=expression | array_initializer=variable_array_initializer )
-> variable_initializer ;;

   LBRACE
   (  ( #variable_initializer=variable_initializer
        ( 0 [: if (LA(2).kind == Token_RBRACE) { break; } :]
          COMMA #variable_initializer=variable_initializer
        )*
        ( COMMA | 0 )
      )
    | 0
   )
   RBRACE
-> variable_array_initializer ;;




-- The STATEMENT is a central point of the grammar.

 (
   block=block  -- more statements within {} braces
   [: (*yynode)->statement_kind = statement_ast::kind_block_statement; :]
 |
   ASSERT assert_condition=expression
   (COLON assert_message=expression | 0) SEMICOLON
   [: (*yynode)->statement_kind = statement_ast::kind_assert_statement; :]
 |
   IF LPAREN if_condition=expression RPAREN if_statement=statement
   (ELSE else_statement=statement | 0)
   -- conflict: the old "dangling-else" problem...
   -- kdevelop-pg generates proper code, matching as soon as possible.
   [: (*yynode)->statement_kind = statement_ast::kind_if_statement; :]
 |
   FOR LPAREN for_control=for_control RPAREN for_statement=statement
   [: (*yynode)->statement_kind = statement_ast::kind_for_statement; :]
 |
   WHILE LPAREN while_condition=expression RPAREN while_statement=statement
   [: (*yynode)->statement_kind = statement_ast::kind_while_statement; :]
 |
   DO do_while_statement=statement
   WHILE LPAREN do_while_condition=expression RPAREN SEMICOLON
   [: (*yynode)->statement_kind = statement_ast::kind_do_while_statement; :]
 |
   TRY try_block=block (#handler=try_handler)*
   (FINALLY finally_block=block | 0)
   [: (*yynode)->statement_kind = statement_ast::kind_try_statement; :]
 |
   SWITCH LPAREN switch_expression=expression RPAREN
   LBRACE (#switch_cases=switch_statements_group)* RBRACE
   [: (*yynode)->statement_kind = statement_ast::kind_switch_statement; :]
 |
   SYNCHRONIZED LPAREN synchronized_locked_type=expression RPAREN
   synchronized_block=block
   [: (*yynode)->statement_kind = statement_ast::kind_synchronized_statement; :]
 |
   RETURN (return_expression=expression | 0) SEMICOLON
   [: (*yynode)->statement_kind = statement_ast::kind_return_statement; :]
 |
   THROW throw_exception=expression SEMICOLON
   [: (*yynode)->statement_kind = statement_ast::kind_throw_statement; :]
 |
   BREAK (break_label=identifier | 0) SEMICOLON
   [: (*yynode)->statement_kind = statement_ast::kind_break_statement; :]
 |
   CONTINUE (continue_label=identifier | 0) SEMICOLON
   [: (*yynode)->statement_kind = statement_ast::kind_continue_statement; :]
 |
   SEMICOLON
   [: (*yynode)->statement_kind = statement_ast::kind_empty_statement; :]
 |
   ?[: LA(2).kind == Token_COLON :]
   labeled_statement_identifier=identifier COLON labeled_statement=statement
   [: (*yynode)->statement_kind = statement_ast::kind_labeled_statement; :]
 |
   expression_statement=expression SEMICOLON  -- method call, assignment, etc.
   [: (*yynode)->statement_kind = statement_ast::kind_expression_statement; :]
 )
-> statement ;;


-- TRY HANDLERs are the catch(...) {...} constructs in try/catch blocks.

   CATCH LPAREN exception_parameter=parameter_declaration RPAREN
   catch_block=block
-> try_handler ;;


-- A group of SWITCH STATEMENTS are any number of "case x:" or "default:"
-- labels followed by a list of statements.

   (#case=switch_case)+
   (#statement=block_statement)*
-> switch_statements_group ;;

   (  CASE expression=expression
      [: (*yynode)->branch_type = switch_case_ast::case_branch;    :]
    | DEFAULT
      [: (*yynode)->branch_type = switch_case_ast::default_branch; :]
   ) COLON
-> switch_case ;;


-- The FOR CONTROL is the three statements inside the for(...) parentheses,
-- or the alternative foreach specifier. It has the same problematic conflict
-- between parameter_declaration and expression that block_statement also has
-- and which is only solvable with LL(k). Until backtracking or real LL(k) is
-- implemented, we have to workaround with a lookahead hack function.

 ( ?[: lookahead_is_parameter_declaration() == true :]
   vardecl_start_or_foreach_parameter=parameter_declaration  -- "int i"
   (
      -- foreach: int i : intList.values()
      ?[: compatibility_mode() >= java15_compatibility :]
      COLON iterable_expression=expression
    |
      -- traditional: int i = 0; i < size; i++
      variable_declaration_rest=variable_declaration_rest -- "= 0"
      traditional_for_rest=for_clause_traditional_rest    -- "; i < size; i++"
   )
 |
   traditional_for_rest=for_clause_traditional_rest  -- only starting with ";"
 |
   #expression=expression @ COMMA
   traditional_for_rest=for_clause_traditional_rest
 )
-> for_control ;;

   SEMICOLON
   (for_condition=expression                  | 0) SEMICOLON   -- "i < size;"
   (#for_update_expression=expression @ COMMA | 0)             -- "i++"
-> for_clause_traditional_rest ;;




-- EXPRESSIONs
-- Note that most of these expressions follow the pattern
--   thisLevelExpression :
--     nextHigherPrecedenceExpression @ OPERATOR
--
-- The operators in java have the following precedences:
--  lowest  (13)  = *= /= %= += -= <<= >>= >>>= &= ^= |=
--          (12)  ?:
--          (11)  ||
--          (10)  &&
--          ( 9)  |
--          ( 8)  ^
--          ( 7)  &
--          ( 6)  == !=
--          ( 5)  < <= > >=
--          ( 4)  << >>
--          ( 3)  +(binary) -(binary)
--          ( 2)  * / %
--          ( 1)  ++ -- +(unary) -(unary)  ~  !  (type)
--                []   () (method call)  . (dot -- identifier qualification)
--                new   ()  (explicit parenthesis)
--
-- the last two are not usually on a precedence chart; they are put in
-- to point out that new has a higher precedence than '.', so you
-- can validy use
--   new Frame().show()


   conditional_expression=conditional_expression
   (
      (  ASSIGN
           [: (*yynode)->assignment_operator = expression_ast::op_assign;                :]
       | PLUS_ASSIGN
           [: (*yynode)->assignment_operator = expression_ast::op_plus_assign;           :]
       | MINUS_ASSIGN
           [: (*yynode)->assignment_operator = expression_ast::op_minus_assign;          :]
       | STAR_ASSIGN
           [: (*yynode)->assignment_operator = expression_ast::op_star_assign;           :]
       | SLASH_ASSIGN
           [: (*yynode)->assignment_operator = expression_ast::op_slash_assign;          :]
       | BIT_AND_ASSIGN
           [: (*yynode)->assignment_operator = expression_ast::op_bit_and_assign;        :]
       | BIT_OR_ASSIGN
           [: (*yynode)->assignment_operator = expression_ast::op_bit_or_assign;         :]
       | BIT_XOR_ASSIGN
           [: (*yynode)->assignment_operator = expression_ast::op_bit_xor_assign;        :]
       | REMAINDER_ASSIGN
           [: (*yynode)->assignment_operator = expression_ast::op_remainder_assign;      :]
       | LSHIFT_ASSIGN
           [: (*yynode)->assignment_operator = expression_ast::op_lshift_assign;         :]
       | SIGNED_RSHIFT_ASSIGN
           [: (*yynode)->assignment_operator = expression_ast::op_signed_rshift_assign;   :]
       | UNSIGNED_RSHIFT_ASSIGN
           [: (*yynode)->assignment_operator = expression_ast::op_unsigned_rshift_assign; :]
      )
      assignment_expression=expression
    |
      0 [: (*yynode)->assignment_operator = expression_ast::no_assignment; :]
   )
-> expression ;;


   logical_or_expression=logical_or_expression
   (  QUESTION if_expression=expression
      COLON    else_expression=conditional_expression
    | 0
   )
-> conditional_expression ;;

   #expression=logical_and_expression @ LOG_OR
-> logical_or_expression ;;

   #expression=bit_or_expression @ LOG_AND
-> logical_and_expression ;;

   #expression=bit_xor_expression @ BIT_OR
-> bit_or_expression ;;

   #expression=bit_and_expression @ BIT_XOR
-> bit_xor_expression ;;

   #expression=equality_expression @ BIT_AND
-> bit_and_expression ;;

   expression=relational_expression
   (#additional_expression=equality_expression_rest)*
-> equality_expression ;;

   (  EQUAL     [: (*yynode)->equality_operator = equality_expression_rest_ast::op_equal;     :]
    | NOT_EQUAL [: (*yynode)->equality_operator = equality_expression_rest_ast::op_not_equal; :]
   )
   expression=relational_expression
-> equality_expression_rest ;;

   expression=shift_expression
   (  (#additional_expression=relational_expression_rest)+
    | INSTANCEOF instanceof_type=type_specification
    | 0
   )
-> relational_expression ;;

   (  LESS_THAN     [: (*yynode)->relational_operator = relational_expression_rest_ast::op_less_than;     :]
    | GREATER_THAN  [: (*yynode)->relational_operator = relational_expression_rest_ast::op_greater_than;  :]
    | LESS_EQUAL    [: (*yynode)->relational_operator = relational_expression_rest_ast::op_less_equal;    :]
    | GREATER_EQUAL [: (*yynode)->relational_operator = relational_expression_rest_ast::op_greater_equal; :]
   )
   expression=shift_expression
-> relational_expression_rest ;;

   expression=additive_expression
   (#additional_expression=shift_expression_rest)*
-> shift_expression ;;

   (  LSHIFT          [: (*yynode)->shift_operator = shift_expression_rest_ast::op_lshift;          :]
    | SIGNED_RSHIFT   [: (*yynode)->shift_operator = shift_expression_rest_ast::op_signed_rshift;   :]
    | UNSIGNED_RSHIFT [: (*yynode)->shift_operator = shift_expression_rest_ast::op_unsigned_rshift; :]
   )
   expression=additive_expression
-> shift_expression_rest ;;

   expression=multiplicative_expression
   (#additional_expression=additive_expression_rest)*
-> additive_expression ;;

   (  PLUS  [: (*yynode)->additive_operator = additive_expression_rest_ast::op_plus;  :]
    | MINUS [: (*yynode)->additive_operator = additive_expression_rest_ast::op_minus; :]
   )
   expression=multiplicative_expression
-> additive_expression_rest ;;

   expression=unary_expression
   (#additional_expression=multiplicative_expression_rest)*
-> multiplicative_expression ;;

   (  STAR      [: (*yynode)->multiplicative_operator = multiplicative_expression_rest_ast::op_star;      :]
    | SLASH     [: (*yynode)->multiplicative_operator = multiplicative_expression_rest_ast::op_slash;     :]
    | REMAINDER [: (*yynode)->multiplicative_operator = multiplicative_expression_rest_ast::op_remainder; :]
   )
   expression=unary_expression
-> multiplicative_expression_rest ;;

 (
   INCREMENT unary_expression=unary_expression
     [: (*yynode)->type = unary_expression_ast::type_incremented_expression; :]
 | DECREMENT unary_expression=unary_expression
     [: (*yynode)->type = unary_expression_ast::type_decremented_expression; :]
 | MINUS unary_expression=unary_expression
     [: (*yynode)->type = unary_expression_ast::type_unary_minus_expression; :]
 | PLUS  unary_expression=unary_expression
     [: (*yynode)->type = unary_expression_ast::type_unary_plus_expression; :]
 | unary_expression_not_plusminus=unary_expression_not_plusminus
     [: (*yynode)->type = unary_expression_ast::type_unary_expression_not_plusminus; :]
 )
-> unary_expression ;;


-- So, up till now this was the easy stuff. Here comes another sincere
-- conflict in the grammar that can only be solved with LL(k).
-- The conflict in this rule is the ambiguity between type casts (which
-- can be arbitrary class names within parentheses) and primary_expressions,
-- which can also look that way from an LL(1) perspective.
-- Until real LL(k) or backtracking is implemented in kdev-pg, this problem
-- is solved with another lookahead hack function.

   TILDE bitwise_not_expression=unary_expression
 | BANG  logical_not_expression=unary_expression
 | ?[: lookahead_is_cast_expression() == true :]
   cast_expression=cast_expression
 | primary_expression=primary_expression (#postfix_operator=postfix_operator)*
-> unary_expression_not_plusminus ;;


--    LPAREN type_specification RPAREN
-- -> cast_expression_lookahead ;;  -- only use for lookaheads!

   LPAREN
   (  builtin_type_specification=builtin_type_specification RPAREN
      builtin_casted_expression=unary_expression
    |
      class_type_specification=class_type_specification RPAREN
      class_casted_expression=unary_expression_not_plusminus
   )
-> cast_expression ;;

   INCREMENT [: (*yynode)->postfix_operator = postfix_operator_ast::op_increment; :]
 | DECREMENT [: (*yynode)->postfix_operator = postfix_operator_ast::op_decrement; :]
-> postfix_operator ;;


-- PRIMARY EXPRESSIONs: qualified names, array expressions,
--                      method invocation, post increment/decrement

   primary_atom=primary_atom (#selector=primary_selector)*
-> primary_expression ;;

-- SELECTORs appended to a primary atom can provide access to ".this" or
-- ".super", create classes with ".new ClassName(...)", call methods with
-- ".methodName(...)", access a member variable with ".variableName",
-- the expression's class info with ".class" and access arrays with "[...]".

 (
   DOT
   (  dotclass=CLASS
    | dotthis=THIS
    | new_expression=new_expression
    | ?[: LA(2).kind != Token_LPAREN :]  -- member variable access
      variable_name=identifier           -- (no method call)
    |
      -- method calls (including the "super" ones) may have type arguments
      (  ?[: compatibility_mode() >= java15_compatibility :]
         type_arguments=non_wildcard_type_arguments
       | 0
      )
      (  SUPER super_suffix=super_suffix
       | method_name=identifier
         LPAREN method_arguments=argument_list RPAREN
      )
   )
 |
   LBRACKET array_index_expression=expression RBRACKET
 )
-> primary_selector ;;


-- SUPER SUFFIX: a call to either a constructor, a method or
--               a member variable of the super class.

 (
   LPAREN constructor_arguments=argument_list RPAREN  -- constructor call
 |
   DOT  -- member access
   (  ?[: LA(2).kind != Token_LPAREN :]  -- member variable access (no method call)
      variable_name=identifier
    |
      -- method access (looks like super.methodName(...) in the end)
      (  ?[: compatibility_mode() >= java15_compatibility :]
         type_arguments=non_wildcard_type_arguments
       | 0
      )
      method_name=identifier
      (LPAREN method_arguments=argument_list RPAREN | 0)
   )
 )
-> super_suffix ;;



-- PRIMARY ATOM: the basic element of a primary expression,
--               and expressions in general

 (
   builtin_type=builtin_type_specification
   DOT CLASS   -- things like int.class or int[].class
   [: (*yynode)->primary_atom_kind = primary_atom_ast::kind_builtin_type_dot_class;             :]
 |
   literal=literal
   [: (*yynode)->primary_atom_kind = primary_atom_ast::kind_literal;                            :]
 |
   new_expression=new_expression
   [: (*yynode)->primary_atom_kind = primary_atom_ast::kind_new_expression;                     :]
 |
   LPAREN parenthesis_expression=expression RPAREN
   [: (*yynode)->primary_atom_kind = primary_atom_ast::kind_parenthesis_expression;             :]
 |
   THIS (LPAREN this_constructor_arguments=argument_list RPAREN | 0)
   [: (*yynode)->primary_atom_kind = primary_atom_ast::kind_this_call_no_type_arguments;        :]
 |
   SUPER super_suffix=super_suffix
   [: (*yynode)->primary_atom_kind = primary_atom_ast::kind_super_call_no_type_arguments;       :]
 |
   ?[: compatibility_mode() >= java15_compatibility :]
   -- generic method invocation with type arguments:
   type_arguments=non_wildcard_type_arguments
   (  SUPER super_suffix=super_suffix
      [: (*yynode)->primary_atom_kind = primary_atom_ast::kind_super_call_with_type_arguments;  :]
    | THIS LPAREN this_constructor_arguments=argument_list RPAREN
      [: (*yynode)->primary_atom_kind = primary_atom_ast::kind_this_call_with_type_arguments;   :]
    | method_name_typed=identifier
      LPAREN method_arguments=argument_list RPAREN
      [: (*yynode)->primary_atom_kind = primary_atom_ast::kind_method_call_with_type_arguments; :]
   )
 |
   -- type names (normal) - either pure, as method or like bla[][].class
   identifier=qualified_identifier_safe  -- without type arguments
   (  LPAREN method_arguments=argument_list RPAREN
      [: (*yynode)->primary_atom_kind = primary_atom_ast::kind_method_call_no_type_arguments;   :]
    | ?[: LA(2).kind == Token_RBRACKET :]
      declarator_brackets=mandatory_declarator_brackets
      DOT array_dotclass=CLASS
      [: (*yynode)->primary_atom_kind = primary_atom_ast::kind_array_type_dot_class;            :]
    | 0
      [: (*yynode)->primary_atom_kind = primary_atom_ast::kind_type_name;                       :]
   )
 )
-> primary_atom ;;


-- NEW EXPRESSIONs are allocations of new types or arrays.

   NEW
   (  ?[: compatibility_mode() >= java15_compatibility :]
      type_arguments=non_wildcard_type_arguments
    | 0
   )
   type=type_specification_noarray
   (  LPAREN class_constructor_arguments=argument_list RPAREN
      (class_body=class_body | 0)
    |
      array_creator_rest=array_creator_rest
   )
-> new_expression ;;

-- This array creator rest can be either
-- a.) empty brackets with an optional initializer (e.g. "[][]{exp,exp}") or
-- b.) at least one filled bracket, afterwards any amount of empty ones

 (
   ?[: LA(2).kind == Token_RBRACKET :]
   mandatory_declarator_brackets=mandatory_declarator_brackets
   array_initializer=variable_array_initializer
 |
   LBRACKET #index_expression=expression RBRACKET
   ( 0 [: if (LA(2).kind == Token_RBRACKET) { break; } :]
        -- exit the loop when noticing declarator brackets
     LBRACKET #index_expression=expression RBRACKET
   )*
   optional_declarator_brackets=optional_declarator_brackets
 )
-> array_creator_rest ;;



-- An ARGUMENT LIST mostly occurs in method calls, always between an LPAREN
-- and an RPAREN, to specify the values for the called method/initializer/etc.

   #expression=expression @ COMMA
 | 0
-> argument_list ;;




-- MODIFIERs for Java classes, interfaces, class/instance vars and methods.
-- Sometimes not all of them are valid, but that has to be checked manually
-- after running the parser. The ANTLR grammar also does it this way.
-- All the occurring modifiers are stored together in the "modifiers"
-- AST node member as flags, except for the annotations who get their own list.

 (
   PRIVATE      [: (*yynode)->modifiers |= optional_modifiers_ast::mod_private;   :]
 | PUBLIC       [: (*yynode)->modifiers |= optional_modifiers_ast::mod_public;    :]
 | PROTECTED    [: (*yynode)->modifiers |= optional_modifiers_ast::mod_protected; :]
 | STATIC       [: (*yynode)->modifiers |= optional_modifiers_ast::mod_static;    :]
 | TRANSIENT    [: (*yynode)->modifiers |= optional_modifiers_ast::mod_transient; :]
 | FINAL        [: (*yynode)->modifiers |= optional_modifiers_ast::mod_final;     :]
 | ABSTRACT     [: (*yynode)->modifiers |= optional_modifiers_ast::mod_abstract;  :]
 | NATIVE       [: (*yynode)->modifiers |= optional_modifiers_ast::mod_native;    :]
 -- Neither in the Java spec nor in the JavaCC grammar, just in the ANTLR one:
 -- | mod_threadsafe=THREADSAFE
 | SYNCHRONIZED [: (*yynode)->modifiers |= optional_modifiers_ast::mod_synchronized; :]
 | VOLATILE     [: (*yynode)->modifiers |= optional_modifiers_ast::mod_volatile;  :]
 | STRICTFP     [: (*yynode)->modifiers |= optional_modifiers_ast::mod_strictfp;  :]
 |
 -- A modifier may be any annotation (e.g. @bla), but not @interface.
 -- This condition resolves the conflict between modifiers
 -- and annotation type declarations:
   0 [: if (yytoken == Token_AT && LA(2).kind == Token_INTERFACE) { break; } :]
   #mod_annotation=annotation
 )*
-> optional_modifiers ;;



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
   floating_point_literal=FLOATING_POINT_LITERAL
   [: (*yynode)->literal_type = literal_ast::type_floating_point;  :]
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
#include "java_lookahead.h"


java::java_compatibility_mode java::compatibility_mode() {
  return _M_compatibility_mode;
}
void java::set_compatibility_mode( java::java_compatibility_mode mode ) {
  _M_compatibility_mode = mode;
}


// custom error recovery
bool java::yy_expected_token(int /*expected*/, std::size_t where, char const *name)
{
  //print_token_environment(this);
  report_problem(
    java::error,
    std::string("Expected token ``") + name
      //+ "'' instead of ``" + current_token_text
      + "''"
  );
  return false;
}

bool java::yy_expected_symbol(int /*expected_symbol*/, char const *name)
{
  //print_token_environment(this);
  report_problem(
    java::error,
    std::string("Expected symbol ``") + name
      //+ "'' instead of ``" + current_token_text
      + "''"
  );
  return false;
}


// lookahead hacks to make up for backtracking or LL(k)
// which are not yet implemented

/**
* This function checks if the next following tokens of the parser class
* match the beginning of a package declaration. If true is returned then it
* looks like a package declaration is coming up. It doesn't have to match the
* full package_declaration rule (because annotation contents are only checked
* rudimentarily), but it is guaranteed that the upcoming tokens are
* not a type specification.
* The function returns false if the upcoming tokens are (for sure) not
* the beginning of a package declaration.
*/
bool java::lookahead_is_package_declaration()
{
    java_lookahead* la = new java_lookahead(this);
    bool result = la->is_package_declaration_start();
    delete la;
    return result;
}

/**
* This function checks if the next following tokens of the parser class
* match the beginning of a variable declaration. If true is returned then it
* looks like a variable declaration is coming up. It doesn't have to match the
* full variable_declaration rule (as only the first few tokens are checked),
* but it is guaranteed that the upcoming tokens are not an expression.
* The function returns false if the upcoming tokens are (for sure) not
* the beginning of a variable declaration.
*/
bool java::lookahead_is_parameter_declaration()
{
    java_lookahead* la = new java_lookahead(this);
    bool result = la->is_parameter_declaration_start();
    delete la;
    return result;
}

/**
* This function checks if the next following tokens of the parser class
* match the beginning of a cast expression. If true is returned then it
* looks like a cast expression is coming up. It doesn't have to match the
* full cast_expression rule (because type arguments are only checked
* rudimentarily), but it is guaranteed that the upcoming tokens are
* not a primary expression.
* The function returns false if the upcoming tokens are (for sure) not
* the beginning of a cast expression.
*/
bool java::lookahead_is_cast_expression()
{
    java_lookahead* la = new java_lookahead(this);
    bool result = la->is_cast_expression_start();
    delete la;
    return result;
}

:]
