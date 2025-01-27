--   SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
--   SPDX-FileCopyrightText: 2009 Jonathan Schmidt-Dominé <devel@the-user.org>
--
--   SPDX-License-Identifier: LGPL-2.0-or-later

[:
#include <QString>
#include <QDebug>
:]

%parserclass (protected declaration)
[:
void expectedSymbol(cc::AstNode::AstNodeKind kind, const QString& name) { qWarning() << "In AstNode " << kind << ": Expected symbol " << name; }
void expectedToken(int kind, enum TokenType token, const QString& name) { qWarning() << "In AstNode " << kind << ": Expected token " << name << " (" << token << ")";}
struct ParserState {
  int ltCounter;
};
ParserState m_state;
:]

%parser_declaration_header "ccast.h"

------------------------------------------------------------
-- T O K E N   L I S T
------------------------------------------------------------

-- keywords:
%token CASE ("case"), DEFAULT ("default"), IF ("if"), ELSE ("else"),
       SWITCH ("switch"), WHILE ("while"), DO ("do"), FOR ("for"),
       BREAK ("break"), CONTINUE ("continue"), GOTO ("goto"),
       RETURN ("return"), TYPEDEF ("typedef"), EXTERN ("extern"),
       STATIC ("static"), AUTO ("auto"), REGISTER ("register"), VOID ("void"),
       CHAR ("char"), SHORT ("short"), INT ("int"), LONG ("long"),
       FLOAT ("float"), DOUBLE ("double"), SIGNED ("signed"),
       UNSIGNED ("unsigned"), TYPEDEF_NAME ("pre-defined type specification"),
       STRUCT ("struct"), UNION ("union"), ENUM ("enum"), CONST ("const"),
       VOLATILE ("volatile") ;;

-- seperators:
%token LPAREN ("("), RPAREN (")"), LBRACE ("{"), RBRACE ("}"), LBRACKET ("["),
       RBRACKET ("]"), DOT ("."), ARROW ("->"), COLON (":"), COMMA (","),
       SEMICOLON (";") ;;

-- operators:
%token PLUS ("+"), MINUS ("-"), STAR ("*"), DIVIDE ("/"), REMAINDER ("%"),
       TILDE ("~"), AND ("&"), OR ("|"), XOR ("^"), NOT ("!"),
       SIZEOF ("sizeof"), PLUS_PLUS ("++"), MINUS_MINUS ("--"), LSHIFT ("<<"),
       RSHIFT (">>"), AND_AND ("&&"), OR_OR ("||"), QUESTION ("?"),
       EQUAL ("="), PLUS_EQUAL ("+="), MINUS_EQUAL ("-="), STAR_EQUAL ("*="),
       DIVIDE_EQUAL ("/="), REMAINDER_EQUAL ("%="), AND_EQUAL ("&="),
       OR_EQUAL ("|="), XOR_EQUAL ("^="), LSHIFT_EQUAL ("<<="),
       RSHIFT_EQUAL (">>="), EQUAL_EQUAL ("=="), NOT_EQUAL ("!="),
       LESS ("<"), GREATER (">"), LESS_EQUAL ("<="), GREATER_EQUAL (">="),
       ELLIPSIS ("...") ;;

-- identifiers and literals:
%token IDENTIFIER ("identifier"), STRING_LITERAL ("string literal"),
       X_CONSTANT ;;
       
-- GCC extensions
%token INLINE ("inline"), EXTENSION ("__extension__"), ASM ("asm") ;;




------------------------------------------------------------
-- E X T E R N A L    D E C L A R A T I O N S
------------------------------------------------------------
   (#ddeclaration=ddeclaration)*
-> document ;;

   enum_specifier=enum_specifier SEMICOLON
 | struct_or_union_specifier=struct_or_union_specifier SEMICOLON
 | TYPEDEF typedef_d=typedef_d SEMICOLON
 | try/rollback(external_block=external_block) catch(
      value_declaration=value_declaration
    )
-> ddeclaration ;;

   typed_identifier ( SEMICOLON
 | try/rollback(function_definition=function_definition) catch(
      function_declaration=function_declaration
   ))
-> value_declaration ;;

   EXTERN STRING_LITERAL LBRACE (#ddeclaration=ddeclaration)* RBRACE
-> external_block ;;

--   VOID
-- | CHAR
-- | SHORT
-- | INT
-- | LONG
-- | FLOAT
-- | DOUBLE
---> type_name_d ;;

   LPAREN type_attribute_identifier=type_attribute_identifier RPAREN (LPAREN (0 | (#function_pointer_parameter=function_pointer_parameter @ COMMA)) RPAREN | 0)
 | STAR type_attribute_identifier=type_attribute_identifier
 | type_attribute_identifier=type_attribute_identifier LBRACKET (0 | X_CONSTANT) RBRACKET
 | IDENTIFIER
-> type_attribute_identifier ;;

   type_name=type_name type_attribute_identifier=type_attribute_identifier
-> typed_identifier ;;

   typed_identifier=typed_identifier SEMICOLON
-> variable_declaration ;;

   try/rollback(typed_identifier=typed_identifier) catch(
      type_name=type_name
   )
-> parameter ;;

   struct_or_union_specifier=struct_or_union_specifier
 | enum_specifier=enum_specifier
 | typed_identifier=typed_identifier
-> typedef_d ;;

   (#statement = statement)*
-> execution_block ;;

   LPAREN (0|#declaration_parameter=declaration_parameter @ COMMA) RPAREN (0|asm_against_mangling=asm_against_mangling) SEMICOLON
-> function_declaration ;;

   typed_identifier=typed_identifier (0 | EQUAL constant_expression=constant_expression)
 | ELLIPSIS
-> named_parameter ;;

   try/rollback(typed_identifier=typed_identifier (0 | EQUAL constant_expression=constant_expression)) catch(
      type_name=type_name
   )
 | ELLIPSIS
-> declaration_parameter ;;

   try/rollback(typed_identifier=typed_identifier) catch(
       type_name=type_name
   )
 | ELLIPSIS
-> function_pointer_parameter ;;

   LPAREN (#named_parameter=named_parameter @ COMMA) RPAREN LBRACE execution_block=execution_block RBRACE
-> function_definition ;;

--   (#external_declaration=external_declaration)*
---> translation_unit ;;

   #declaration_specifier=declaration_specifier (#declaration_specifier=declaration_specifier)*
-> declaration_header ;;

--   declaration_header=declaration_header variable_or_function=variable_or_function
---> external_declaration ;;

--   declarator=declarator (COMMA #init_declarator=init_declarator @ COMMA SEMICOLON
--               | SEMICOLON
--               | ?[:is_fun_definition:] declaration* compound_statement
--               | (#declaration=declaration)* compound_statement=compound_statement
--               | initializer=initializer (COMMA #init_declarator=init_declarator)* SEMICOLON)
---> variable_or_function ;;

------------------------------------------------------------
-- GCC-STUFF
------------------------------------------------------------
   STRING_LITERAL LPAREN IDENTIFIER
-> asm_specifier ;;

   ASM (0 | VOLATILE) LPAREN (STRING_LITERAL*) (0 | COLON (#output_operands=asm_specifier @ COMMA) (0 | COLON (#input_operands=asm_specifier @ COMMA) (0 | COLON (STRING_LITERAL @ COMMA))))
-> inline_asm ;;

   EXTENSION LPAREN LBRACE execution_block RBRACE RPAREN
-> ext_expression ;;

   ASM LPAREN STRING_LITERAL RPAREN
-> asm_against_mangling ;;

------------------------------------------------------------
-- E X P R E S S I O N S
------------------------------------------------------------

   identifier=IDENTIFIER
 | constant=constant
 | string_literal=STRING_LITERAL
 | LPAREN expression=expression RPAREN
-> primary_expression ;;

   primary_expression=primary_expression (#postfix_expression_rest=postfix_expression_rest)*
-> postfix_expression ;;

   (DOT | ARROW) IDENTIFIER
 | PLUS_PLUS
 | MINUS_MINUS
 | LPAREN (argument_expression_list=argument_expression_list | 0) RPAREN
 | LBRACKET expression=expression RBRACKET
-> postfix_expression_rest ;;

   #assignment_expression=assignment_expression @ COMMA
-> argument_expression_list ;;

   postfix_expression=postfix_expression
 | PLUS_PLUS unary_expression=unary_expression
 | MINUS_MINUS unary_expression=unary_expression
 | unary_operator cast_expression=cast_expression
 | SIZEOF LPAREN type_name=type_name RPAREN
-> unary_expression ;;

   AND
 | STAR
 | PLUS
 | MINUS
 | TILDE
 | NOT
-> unary_operator ;;

   LPAREN type_name=type_name RPAREN cast_expression=cast_expression
 | unary_expression=unary_expression
-> cast_expression ;;

   #cast_expression=cast_expression @ (STAR | DIVIDE | REMAINDER)
-> multiplicative_expression ;;

   #multiplicative_expression=multiplicative_expression @ (PLUS | MINUS)
-> additive_expression ;;

   #additive_expression=additive_expression @ (LSHIFT | RSHIFT)
-> shift_expression ;;

   #shift_expression=shift_expression @ (LESS | GREATER | LESS_EQUAL | GREATER_EQUAL)
-> relational_expression ;;

   #relational_expression=relational_expression @ (EQUAL_EQUAL | NOT_EQUAL)
-> equality_expression ;;

   #equality_expression=equality_expression @ AND
-> AND_expression ;;

   #AND_expression=AND_expression @ XOR
-> exclusive_OR_expression ;;

   #exclusive_OR_expression=exclusive_OR_expression @ OR
-> inclusive_OR_expression ;;

   #inclusive_OR_expression=inclusive_OR_expression @ AND_AND
-> logical_AND_expression ;;

   #logical_AND_expression=logical_AND_expression @ OR_OR
-> logical_OR_expression ;;

   logical_OR_expression=logical_OR_expression (QUESTION expression COLON conditional_expression | 0)
-> conditional_expression ;;

   #conditional_expression=conditional_expression @ assignment_operator
-> assignment_expression ;;

   EQUAL
 | STAR_EQUAL
 | DIVIDE_EQUAL
 | REMAINDER_EQUAL
 | PLUS_EQUAL
 | MINUS_EQUAL
 | LSHIFT_EQUAL
 | RSHIFT_EQUAL
 | AND_EQUAL
 | XOR_EQUAL
 | OR_EQUAL
-> assignment_operator ;;

   #assignment_expression=assignment_expression @ COMMA
-> expression ;;

   conditional_expression=conditional_expression
-> constant_expression ;;

   X_CONSTANT
-> constant ;;

------------------------------------------------------------
-- S T A T E M E N T S
------------------------------------------------------------
   IDENTIFIER COLON
 | labeled_statement=labeled_statement
 | compound_statement=compound_statement
 | expression_statement=expression_statement
 | selection_statement=selection_statement
 | iteration_statement=iteration_statement
 | jump_statement=jump_statement
 | inline_asm
 | SEMICOLON
-> statement ;;

   CASE constant_expression=constant_expression COLON statement=statement
 | DEFAULT COLON statement=statement
-> labeled_statement ;;

   LBRACE (#declaration=declaration)* (#statement=statement)* RBRACE
-> compound_statement ;;

   expression=expression SEMICOLON
-> expression_statement ;;

   IF LPAREN expression=expression RPAREN statement=statement (ELSE alternative_statement=statement | 0)
 | SWITCH LPAREN expression=expression RPAREN statement=statement
-> selection_statement ;;

   WHILE LPAREN (expression=expression | ext_expression=ext_expression) RPAREN statement=statement
 | DO statement WHILE LPAREN expression=expression RPAREN SEMICOLON
 | FOR LPAREN (for_1=expression|for1_ext=ext_expression|0) SEMICOLON (for_2=expression|for2_ext=ext_expression|0) SEMICOLON (for_3=expression|for3_ext=ext_expression|0) RPAREN statement=statement
-> iteration_statement ;;

   GOTO IDENTIFIER SEMICOLON
 | CONTINUE SEMICOLON
 | BREAK SEMICOLON
 | RETURN (expression=expression | 0) SEMICOLON
-> jump_statement ;;

------------------------------------------------------------
-- D E C L A R A T I O N S
------------------------------------------------------------

   #declaration_specifier=declaration_specifier (#declaration_specifier=declaration_specifier)* (#init_declarator=init_declarator @ COMMA | 0) SEMICOLON
-> declaration ;;

   storage_class_specifier=storage_class_specifier
 | type_specifier=type_specifier
 | type_qualifier=type_qualifier
-> declaration_specifier ;;

   declarator=declarator (EQUAL initializer=initializer | 0)
-> init_declarator ;;

   TYPEDEF
 | EXTERN
 | STATIC
 | AUTO
 | REGISTER
-> storage_class_specifier ;;

   VOID
 | CHAR
 | SHORT
 | INT
 | LONG
 | FLOAT
 | DOUBLE
 | SIGNED
 | UNSIGNED
 | struct_or_union_specifier=struct_or_union_specifier
 | enum_specifier=enum_specifier
 | TYPEDEF_NAME
-> type_specifier ;;

--   EXTERN STRING_LITERAL LBRACE (#external_declaration=external_declaration)* RBRACE
---> external_block ;;

   (STRUCT | UNION) (IDENTIFIER LBRACE (#struct_declaration=struct_declaration)* RBRACE
                     | LBRACE (#struct_declaration=struct_declaration)* RBRACE)
-> struct_or_union_specifier ;;

   #specifier_qualifier=specifier_qualifier #specifier_qualifier=specifier_qualifier (#specifier_qualifier=specifier_qualifier*) (#struct_declarator=struct_declarator)* SEMICOLON
-> struct_declaration ;;

   type_specifier=type_specifier
 | type_qualifier=type_qualifier
-> specifier_qualifier ;;

   declarator=declarator (constant_expression=constant_expression | 0)
 | COLON constant_expression=constant_expression
-> struct_declarator ;;

   ENUM (IDENTIFIER LBRACE #enumerator=enumerator @ COMMA RBRACE | LBRACE #enumerator=enumerator @ COMMA RBRACE)
-> enum_specifier ;;

   IDENTIFIER (EQUAL constant_expression=constant_expression | 0)
-> enumerator ;;

   CONST
 | VOLATILE
-> type_qualifier ;;

   (pointer=pointer direct_declarator=direct_declarator | direct_declarator=direct_declarator) (#direct_declarator_rest=direct_declarator_rest)*
 | direct_declarator=direct_declarator
-> declarator ;;

   IDENTIFIER
 | LPAREN declarator=declarator RPAREN
-> direct_declarator ;;

   LBRACKET (constant_expression | 0) RBRACKET
 | LPAREN (IDENTIFIER @ COMMA | parameter_type_list=parameter_type_list | 0) RPAREN
-> direct_declarator_rest ;;

   STAR (#type_qualifier=type_qualifier | STAR)*
-> pointer ;;

   (#parameter_declaration=parameter_declaration | ELLIPSIS) @ COMMA
 | 0
-> parameter_type_list ;;

   #declaration_specifier=declaration_specifier (#declaration_specifier=declaration_specifier)* (declarator=declarator | abstract_declarator=abstract_declarator | 0)
-> parameter_declaration ;;

   #specifier_qualifier=specifier_qualifier (#specifier_qualifier=specifier_qualifier)*
-> type_name ;;

   (pointer=pointer #direct_abstract_declarator=direct_abstract_declarator | #direct_abstract_declarator=direct_abstract_declarator) (#direct_abstract_declarator=direct_abstract_declarator)*
-> abstract_declarator ;;

   LPAREN (abstract_declarator=abstract_declarator | parameter_type_list=parameter_type_list) RPAREN
 | LBRACKET (constant_expression | 0) RBRACKET
-> direct_abstract_declarator ;;

   assignment_expression=assignment_expression
 | LBRACE #initializer=initializer (COMMA (#initializer=initializer | 0))* RBRACE
-> initializer ;;

[:
namespace cc
{
Parser::ParserState *Parser::copyCurrentState()
{
  ParserState *state = new ParserState();
  state->ltCounter = m_state.ltCounter;
  return state;
}

void Parser::restoreState( Parser::ParserState *state )
{
  m_state.ltCounter = state->ltCounter;
}
};
:]
