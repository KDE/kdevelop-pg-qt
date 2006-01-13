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


-- Grammar for Java 1.5
-- Modelled after the public domain ANTLR Java 1.5 grammar at
-- http://www.antlr.org/grammar/1090713067533/index.html
-- (Version 1.22.5 from January 03, 2005)
-- and the reference grammar of the Java language specification,
-- Third Edition, at http://java.sun.com/docs/books/jls/.



-- Known problematic conflicts (4 conflicts), requiring automatic LL(k):
--  - Part of the first/follow SEMICOLON, IMPORT, STATIC, CLASS etc. conflict
--    in compilation_unit (namely: package_declaration vs. type_declaration).
--    Solved by lookahead_is_package_declaration().
--    (1 conflict)
--  - The first/first SEMICOLON, VOID, BOOLEAN etc. conflict in
--    block_statement which is essentially an expression statements vs.
--    variable declarations conflict (ignore the modifier conflicts,
--    they are there by design and are completely harmless).
--    The real conflict is just the IDENTIFIER one.
--    Solved by lookahead_is_parameter_declaration().
--    The SYNCHRONIZED conflict in this error message is also
--    independent and has been resolved too.
--    (1 conflict)
--  - The first/first VOID, BOOLEAN, BYTE etc. conflict in for_init.
--    This is the same variable/parameter declaration vs. expression issue
--    that block_statement also suffers from.
--    Also solved by lookahead_is_parameter_declaration().
--    (1 conflict)
--  - The first/first LPAREN conflict in unary_expression_not_plusminus
--    which is cast_expression vs. primary_expression.
--    Solved by lookahead_is_cast_expression().
--    (1 conflict)

-- Known harmless or resolved conflicts (22 conflicts):
--  - The first/follow IMPORT, AT conflict in compilation_unit
--    (done right by default, 1 conflict)
--  - Part of the first/follow SEMICOLON, IMPORT, STATIC, CLASS etc. conflict
--    in compilation_unit. Everything except AT is harmless and done right
--    by default. (already counted in the problematic conflicts section)
--  - The first/follow LBRACKET conflict in optional_declarator_brackets
--    (done right by default, 1 conflict)
--  - The first/follow COMMA, ASSIGN conflict in variable_declaration,
--    and the COMMA conflict in variable_declaration_rest: greedy is ok
--    (done right by default, 2 conflicts)
--  - The first/follow AT conflict in optional_modifiers: greedy is ok
--    (done right by default, 1 conflict)
--  - The first/first IDENTIFIER conflicts in *_field,
--    between method_name and variable_name
--    (manually resolved, 4 conflicts)
--  - The first/first IDENTIFIER conflict in class_field
--    (manually resolved, 1 conflict)
--  - The first/first STATIC conflict in class_field
--    (manually resolved, 1 conflict)
--  - The first/first "0" conflicts in parameter_declaration_list
--    (done right by default, 2 conflicts)
--  - The first/first "0" conflicts in [non_wildcard_]type_arguments, which is
--    the same kind of conflict like in parameter_declaration_list above
--    (done right by default, 2 conflicts)
--  - The first/first IDENTIFIER conflict in annotation_arguments
--    (manually resolved, 1 conflict)
--  - The first/first AT, FINAL, SYNCHRONIZED conflict in block_statement,
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
--  - The first/first "0" contlict in optional_modifiers.
--    Seems to originate in (0 annotation | 0) (which is by design),
--    so it should be harmless.
--    (done right by default, 1 conflict)

-- Conflicts of unknown consequence (13 conflicts):
--  - The first/follow COMMA conflicts in enum_body
--    (2 conflicts)
--  - The first/first "0" conflicts in compilation_unit.
--    Should be harmless, but who knows?
--    (2 conflicts)
--  - The first/first "0" conflict in class_body, interface_body,
--    annotation_type_body and enum_body (3x for the latter one),
--    seemingly similar to the compilation_unit conflict above
--    (6 conflicts)
--  - The first/first "0" conflict in enum_constant_body, also the same
--    (1 conflict)
--  - The first/first "0" conflict in block, again the same thing
--    (1 conflict)
--  - The first/first "0" conflict in primary_atom. Don't ask me what it
--    means and why it's present.
--    (1 conflict)

-- Total amount of conflicts: 39



-- Global variables and initializations

-- I'd rather have these as members of the java class,
-- but at the time of writing this doesn't seem to be possible.
[:
// The compatibility_mode status variable tells which version of Java
// should be checked against.
enum java_compatibility_mode {
  java13_compatibility = 130,
  java14_compatibility = 140,
  java15_compatibility = 150,
};

static java_compatibility_mode _M_compatibility_mode = java15_compatibility;

static java_compatibility_mode compatibility_mode() {
  return _M_compatibility_mode;
}
static void set_compatibility_mode( java_compatibility_mode mode ) {
  _M_compatibility_mode = mode;
}


// ltCounter stores the amount of currently open type arguments rules,
// all of which are beginning with a less than ("<") character.
// This way, also SIGNED_RSHIFT (">>") and UNSIGNED_RSHIFT (">>>") can be used
// to close type arguments rules, in addition to GREATER_THAN (">").
static int  ltCounter = 0;

// tripleDotOccurred is used as a means of communication between
// parameter_declaration_list and parameter_declaration_tripledot to determine
// if a triple dot was already in the list (then no more declarations
// may follow).
static bool tripleDotOccurred;


class java; // this code block is put before the class declaration

// lookahead hacks to make up for backtracking or LL(k)
// which are not yet implemented
bool lookahead_is_package_declaration(java* parser);
bool lookahead_is_parameter_declaration(java* parser);
bool lookahead_is_cast_expression(java* parser);
:]


-- TODO: when there is an "ast node member" code insertion syntax available,
-- re-simplify the operators, literals and modifiers to be just "op_token",
-- "literal_token" and "mod_token", and make an additional ast node member
-- for each, having the type of an enum that should be defined in the class,
-- which tells the type. Less memory consumption that way.




-- The grammar starts with compilation_unit,
-- which is equivalent to a single source file.

   ( -- The first thing there is (haha) is a serious conflict between
     -- package_declaration and type_declaration, both of which can start
     -- with annotations. As this is only solvable with LL(k), it's
     -- implemented with a workaround hack until backtracking or real
     -- LL(k) is available. When this is available, you can also say:
     -- ?( package_declararation_lookahead ) instead of the current one:
     ?[: lookahead_is_package_declaration(this) == true :]
      package_declaration=package_declaration
    | 0
   )
   ( !(#import_declaration=import_declaration) | 0 )
   ( !(#type_declaration=type_declaration) | 0 )
-> compilation_unit ;;

--    ( !(#annotation=annotation) | 0 ) PACKAGE
-- -> package_declaration_lookahead ;;  -- only use for lookaheads!



-- A PACKAGE DECLARATION: optional annotations followed by "package",
--                        then the package identifier.
-- 1 first/first conflict, because annotation as well as "| 0"
-- inside of compilation_unit may both be 0. The ANTLR grammar
-- checks on ?[:annotations "package":] to do a package_declaration.

   ( !(#annotation=annotation) | 0 )
   PACKAGE package_name=qualified_identifier SEMICOLON
-> package_declaration ;;


-- An IMPORT DECLARATION is "import" followed by a package or type (=class) name.

   IMPORT (token_static=STATIC | 0)
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

   LBRACE ( !(#declaration=class_field) | 0 ) RBRACE
-> class_body ;;

   LBRACE ( !(#declaration=interface_field) | 0 ) RBRACE
-> interface_body ;;

   LBRACE ( !(#annotation_type_field=annotation_type_field) | 0 ) RBRACE
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
   ( SEMICOLON ( !(#class_field=class_field) | 0 ) | 0 )
   RBRACE
-> enum_body ;;

-- An enum constant may have optional parameters and may have a class body

   ( !( #annotation=annotation ) | 0 ) identifier=identifier
   ( LPAREN arguments=argument_list RPAREN | 0 )
   ( body=enum_constant_body | 0 )
-> enum_constant ;;

   LBRACE ( !(#declaration=enum_constant_field) | 0 ) RBRACE
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

 ( ?[: yytoken != Token_STATIC || LA(2).kind != Token_LBRACE :]
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

   LPAREN [: tripleDotOccurred = false; :]
   (
      #parameter_declaration=parameter_declaration_tripledot
      @ ( 0 [: if( tripleDotOccurred == true ) { break; } :]
            -- Don't proceed after the triple dot. If there's a cleaner way
            -- to exit the loop when tripleDotOccurred == true,
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
--    LPAREN [: tripleDotOccurred = false; :]
--    (
--       #parameter_declaration=parameter_declaration_tripledot
--       @ ( ?[: tripleDotOccurred == false :] COMMA )
--           -- kdev-pg dismisses this condition!
--     |
--       0
--    )
--    RPAREN
-- -> parameter_declaration_list ;;

   parameter_modifiers=optional_parameter_modifiers
   type_specification=type_specification
   ( triple_dot=TRIPLE_DOT [: tripleDotOccurred = true; :] | 0 )
   variable_identifier=identifier
   declarator_brackets=optional_declarator_brackets
-> parameter_declaration_tripledot ;;

-- This PARAMETER DECLARATION rule is not used in parameter_declaration_list,
-- and lacks the tripledot possibility & handling. It's used in try_handler
-- and in for_control.

   parameter_modifiers=optional_parameter_modifiers
   type_specification=type_specification
   variable_identifier=identifier
   declarator_brackets=optional_declarator_brackets
-> parameter_declaration ;;

   ( !( mod_final=FINAL | #mod_annotation=annotation ) | 0 )
-> optional_parameter_modifiers ;;



-- The body of a CONSTRUCTOR METHOD is the same as a normal block, except that
-- it's possible to have a constructor call like this(...) or super(...)
-- at the beginning of the block. This causes a conflict which is difficult
-- to resolve, so class_field uses block instead of constructor_body.
--
--    LBRACE
--    ( explicit_constructor_invocation=explicit_constructor_invocation | 0 )
--    ( !(#statement=statement) | 0 )
--    RBRACE
-- -> constructor_body ;;
--
-- -- Catches obvious constructor calls, but not the expr.super(...) calls:
--
--    (  ?[: _M_compatibility_mode >= java15_compatibility :]
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
   (EXTENDS (#type=class_or_interface_type @ BIT_AND) | 0)
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

   (extends_or_super=EXTENDS | extends_or_super=SUPER)
   type=class_or_interface_type
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
-- but the ANTLR grammar works that way.
-- TODO: rename type to type_[specifictype]

   type=VOID
 | type=BOOLEAN
 | type=BYTE
 | type=CHAR
 | type=SHORT
 | type=INT
 | type=FLOAT
 | type=LONG
 | type=DOUBLE
-> builtin_type ;;

   #part=class_or_interface_type_part @ DOT
-> class_or_interface_type ;;

   identifier=identifier
   (  ?[: _M_compatibility_mode >= java15_compatibility :]
      type_arguments=type_arguments
    | 0
   )
-> class_or_interface_type_part ;;



-- QUALIFIED identifiers are either qualified ones or raw identifiers.

   #name=identifier @ DOT
-> qualified_identifier ;;

   #name=identifier
   ( !( 0 [: if (LA(2).kind != Token_IDENTIFIER) { break; } :]
        DOT #name=identifier )
     | 0
   )
-> qualified_identifier_safe ;; -- lookahead version of the above

   #name=identifier
   (  !( DOT (  #name=identifier
              | star=STAR [: break; :] -- no more identifiers after the star
             )
      )
    | 0
   )
-> qualified_identifier_with_optional_star ;;

-- Declarator brackets are part of a type specification, like String[][]
-- They are always empty, only have to be counted.

   ( !( #lbracket=LBRACKET RBRACKET ) | 0 )
-> optional_declarator_brackets ;;
-- TODO: make a counter instead of filling the sequence array with lbrackets

   !( #lbracket=LBRACKET RBRACKET )
-> mandatory_declarator_brackets ;;
-- TODO: make a counter instead of filling the sequence array with lbrackets




-- ANNOTATIONS look for example like @Info( name="Jakob", born=1983 ),
-- or @Info("Jakob"), or just @Info, and are attached to a method, class or package.
-- @Info is equivalent to @Info().

   AT type_name=qualified_identifier
   ( lparen=LPAREN (args=annotation_arguments | 0) RPAREN  | 0 )
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

   LBRACE ( !(#statement=block_statement) | 0 ) RBRACE
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
   ?[: lookahead_is_parameter_declaration(this) == true :]
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
   ( !( COMMA #variable_declarator=variable_declarator ) | 0 )
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
        (  !( 0 [: if (LA(2).kind == Token_RBRACE) { break; } :]
              COMMA #variable_initializer=variable_initializer
           )
         | 0
        )
        ( COMMA | 0 )
      )
    | 0
   )
   RBRACE
-> variable_array_initializer ;;




-- The STATEMENT is a central point of the grammar.

 (
   block=block  -- more statements within {} braces
 |
   ASSERT assert_condition=expression
   (COLON assert_message=expression | 0) SEMICOLON
 |
   IF LPAREN if_condition=expression RPAREN if_statement=statement
   (ELSE else_statement=statement | 0)
   -- conflict: the old "dangling-else" problem...
   -- kdevelop-pg generates proper code matching as soon as possible.
 |
   FOR LPAREN for_control=for_control RPAREN for_statement=statement
 |
   WHILE LPAREN while_condition=expression RPAREN while_statement=statement
 |
   DO do_while_statement=statement
   WHILE LPAREN do_while_condition=expression RPAREN SEMICOLON
 |
   TRY try_block=block ( !(#handler=try_handler) | 0 )
   (FINALLY finally_block=block | 0)
 |
   SWITCH LPAREN switch_expression=expression RPAREN
   LBRACE ( !(#switch_cases=switch_statements_group) | 0 ) RBRACE
 |
   SYNCHRONIZED LPAREN synchronized_locked_type=expression RPAREN
   synchronized_block=block
 |
   return_token=RETURN (return_expression=expression | 0) SEMICOLON
 |
   THROW throw_exception=expression SEMICOLON
 |
   break_token=BREAK (break_label=identifier | 0) SEMICOLON
 |
   continue_token=CONTINUE (continue_label=identifier | 0) SEMICOLON
 |
   SEMICOLON
 |
   ?[: LA(2).kind == Token_COLON :]
   labeled_statement_identifier=identifier COLON labeled_statement=statement
 |
   expression_statement=expression SEMICOLON  -- method call, assignment, etc.
 )
-> statement ;;


-- TRY HANDLERs are the catch(...) {...} constructs in try/catch blocks.

   CATCH LPAREN exception_parameter=parameter_declaration RPAREN
   catch_block=block
-> try_handler ;;


-- A group of SWITCH STATEMENTS are any number of "case x:" or "default:"
-- labels followed by a list of statements.

   #case=switch_case ( !(#case=switch_case) | 0 )
   ( !(#statement=block_statement) | 0 )
-> switch_statements_group ;;

   ( token=CASE expression=expression | token=DEFAULT ) COLON
-> switch_case ;;


-- The FOR CONTROL is the three statements inside the for(...) parentheses,
-- or the alternative foreach specifier. It has the same problematic conflict
-- between parameter_declaration and expression that block_statement also has
-- and which is only solvable with LL(k). Until backtracking or real LL(k) is
-- implemented, we have to workaround with a lookahead hack function.

 ( ?[: lookahead_is_parameter_declaration(this) == true :]
   vardecl_start_or_foreach_parameter=parameter_declaration  -- "int i"
   (
      -- foreach: int i : intList.values()
      ?[: _M_compatibility_mode >= java15_compatibility :]
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
      (  op_assign=ASSIGN
       | op_plus_assign=PLUS_ASSIGN
       | op_minus_assign=MINUS_ASSIGN
       | op_star_assign=STAR_ASSIGN
       | op_slash_assign=SLASH_ASSIGN
       | op_and_assign=BIT_AND_ASSIGN
       | op_or_assign=BIT_OR_ASSIGN
       | op_xor_assign=BIT_XOR_ASSIGN
       | op_remainder_assign=REMAINDER_ASSIGN
       | op_lshift_assign=LSHIFT_ASSIGN
       | op_rsignedshift_assign=SIGNED_RSHIFT_ASSIGN
       | op_runsignedshift_assign=UNSIGNED_RSHIFT_ASSIGN
      )
      assignment_expression=expression
    |
      0
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
   ( !(#additional_expression=equality_expression_rest) | 0 )
-> equality_expression ;;

   ( op_equal=EQUAL | op_notequal=NOT_EQUAL )
   expression=relational_expression
-> equality_expression_rest ;;

   expression=shift_expression
   (  !(#additional_expression=relational_expression_rest)
    | INSTANCEOF instanceof_type=type_specification
    | 0
   )
-> relational_expression ;;

   (  op_lessthan=LESS_THAN | op_greaterthan=GREATER_THAN
    | op_lessequal=LESS_EQUAL | op_greaterequal=GREATER_EQUAL )
   expression=shift_expression
-> relational_expression_rest ;;

   expression=additive_expression
   ( !(#additional_expression=shift_expression_rest) | 0 )
-> shift_expression ;;

   (  op_lshift=LSHIFT | op_rsignedshift=SIGNED_RSHIFT
    | op_runsignedshift=UNSIGNED_RSHIFT )
   expression=additive_expression
-> shift_expression_rest ;;

   expression=multiplicative_expression
   ( !(#additional_expression=additive_expression_rest) | 0 )
-> additive_expression ;;

   ( op_plus=PLUS | op_minus=MINUS )
   expression=multiplicative_expression
-> additive_expression_rest ;;

   expression=unary_expression
   ( !(#additional_expression=multiplicative_expression_rest) | 0 )
-> multiplicative_expression ;;

   ( op_star=STAR | op_slash=SLASH | op_remainder=REMAINDER )
   expression=unary_expression
-> multiplicative_expression_rest ;;

   INCREMENT incremented_expression=unary_expression
 | DECREMENT decremented_expression=unary_expression
 | MINUS unary_minus_expression=unary_expression
 | PLUS  unary_plus_expression=unary_expression
 | other_expression=unary_expression_not_plusminus
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
 | ?[: lookahead_is_cast_expression(this) == true :]
   cast_expression
 | primary_expression=primary_expression ( !(#postfix_operator=postfix_operator) | 0 )
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

   op_increment=INCREMENT
 | op_decrement=DECREMENT
-> postfix_operator ;;


-- PRIMARY EXPRESSIONs: qualified names, array expressions,
--                      method invocation, post increment/decrement

   primary_atom=primary_atom ( !(#selector=primary_selector) | 0 )
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
      (  ?[: _M_compatibility_mode >= java15_compatibility :]
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
      (  ?[: _M_compatibility_mode >= java15_compatibility :]
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
   DOT builtin_dotclass=CLASS   -- things like int.class or int[].class
 |
   literal=literal
 |
   new_expression=new_expression
 |
   LPAREN parenthesis_expression=expression RPAREN
 |
   this_call_untyped=THIS
   (LPAREN this_constructor_arguments=argument_list RPAREN | 0)
 |
   SUPER super_suffix_untyped=super_suffix
 |
   ?[: _M_compatibility_mode >= java15_compatibility :]
   -- generic method invocation with type arguments:
   type_arguments=non_wildcard_type_arguments
   (  SUPER super_suffix_typed=super_suffix
    | this_call_typed=THIS
      LPAREN this_constructor_arguments=argument_list RPAREN
    | method_name_typed=identifier
      LPAREN method_arguments=argument_list RPAREN
   )
 |
   -- type names (normal) - either pure, as method or like bla[][].class
   identifier_untyped=qualified_identifier_safe  -- without type arguments
   (  LPAREN method_arguments=argument_list RPAREN
    | ?[: LA(2).kind == Token_RBRACKET :]
      declarator_brackets=mandatory_declarator_brackets
      DOT array_dotclass=CLASS
    | 0
   )
 )
-> primary_atom ;;


-- NEW EXPRESSIONs are allocations of new types or arrays.

   NEW
   (  ?[: _M_compatibility_mode >= java15_compatibility :]
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
   !( 0 [: if (LA(2).kind == Token_RBRACKET) { break; } :]
         -- exit the loop when noticing declarator brackets
      LBRACKET #index_expression=expression RBRACKET
   )
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

 -- A modifier may be any annotation (e.g. @bla), but not @interface.
 -- This condition resolves the conflict between modifiers
 -- and annotation type declarations:
 ( !(
      mod_private=PRIVATE
    | mod_public=PUBLIC
    | mod_protected=PROTECTED
    | mod_static=STATIC
    | mod_transient=TRANSIENT
    | mod_final=FINAL
    | mod_abstract=ABSTRACT
    | mod_native=NATIVE
    -- Neither in the Java spec nor in the JavaCC grammar, just in the ANTLR one:
    -- | mod_threadsafe=THREADSAFE
    | mod_synchronized=SYNCHRONIZED
    | mod_volatile=VOLATILE
    | mod_strictfp=STRICTFP
    |
      0 [: if (yytoken == Token_AT && LA(2).kind == Token_INTERFACE) { break; } :]
      #mod_annotation=annotation
   )
 | 0
 )
-> optional_modifiers ;;



   ident=IDENTIFIER
-> identifier ;;

   true_literal=TRUE
 | false_literal=FALSE
 | null_literal=NULL
 | integer_literal=INTEGER_LITERAL
 | floating_point_literal=FLOATING_POINT_LITERAL
 | character_literal=CHARACTER_LITERAL
 | string_literal=STRING_LITERAL
-> literal ;;







--
-- Appendix: token list
--

   ( keyword | seperator | operator | literal | identifier | INVALID )
-> token ;;

   (  ABSTRACT | ASSERT | BOOLEAN | BREAK | BYTE | CASE | CATCH | CHAR | CLASS | CONST | CONTINUE
    | DEFAULT | DO | DOUBLE | ELSE | ENUM | EXTENDS | FINAL | FINALLY | FLOAT | FOR | GOTO
    | IF | IMPLEMENTS | IMPORT | INSTANCEOF | INT | INTERFACE | LONG | NATIVE | NEW | PACKAGE
    | PRIVATE | PROTECTED | PUBLIC | RETURN | SHORT | STATIC | STRICTFP | SUPER | SWITCH
    | SYNCHRONIZED | THIS | THROW | THROWS | TRANSIENT | TRY | VOID | VOLATILE | WHILE )
-> keyword ;;

   ( LPAREN | RPAREN | LBRACE | RBRACE | LBRACKET | RBRACKET | SEMICOLON | COMMA | DOT | AT )
-> seperator ;;

   (  ASSIGN | LESS_THAN | BANG | TILDE | QUESTION | COLON | EQUAL | LESS_EQUAL | GREATER_EQUAL
    | NOT_EQUAL | LOG_AND | LOG_OR | INCREMENT | DECREMENT | PLUS | MINUS | STAR | SLASH | BIT_AND
    | BIT_OR | BIT_XOR | REMAINDER | LSHIFT | PLUS_ASSIGN | MINUS_ASSIGN | STAR_ASSIGN | SLASH_ASSIGN
    | BIT_AND_ASSIGN | BIT_OR_ASSIGN | BIT_XOR_ASSIGN | REMAINDER_ASSIGN | LSHIFT_ASSIGN | SIGNED_RSHIFT_ASSIGN
    | UNSIGNED_RSHIFT_ASSIGN | GREATER_THAN | SIGNED_RSHIFT | UNSIGNED_RSHIFT | TRIPLE_DOT )
-> operator ;;

