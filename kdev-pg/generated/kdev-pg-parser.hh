/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C

    SPDX-FileCopyrightText: 1984, 1989-1990, 2000-2011 Free Software Foundation Inc.

    SPDX-License-Identifier: GPL-3.0-or-later WITH Bison-exception-2.2
*/

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_IDENTIFIER = 258,
     T_ARROW = 259,
     T_TERMINAL = 260,
     T_CODE = 261,
     T_STRING = 262,
     T_UNQUOTED_STRING = 263,
     T_NUMBER = 264,
     T_TOKEN_DECLARATION = 265,
     T_TOKEN_STREAM_DECLARATION = 266,
     T_NAMESPACE_DECLARATION = 267,
     T_PARSERCLASS_DECLARATION = 268,
     T_LEXERCLASS_DECLARATION = 269,
     T_PUBLIC = 270,
     T_PRIVATE = 271,
     T_PROTECTED = 272,
     T_DECLARATION = 273,
     T_BITS = 274,
     T_CONSTRUCTOR = 275,
     T_DESTRUCTOR = 276,
     T_TRY_RECOVER = 277,
     T_TRY_ROLLBACK = 278,
     T_CATCH = 279,
     T_RULE_ARGUMENTS = 280,
     T_MEMBER = 281,
     T_TEMPORARY = 282,
     T_ARGUMENT = 283,
     T_EXPORT_MACRO = 284,
     T_NODE = 285,
     T_NODE_SEQUENCE = 286,
     T_TOKEN = 287,
     T_VARIABLE = 288,
     T_EXPORT_MACRO_HEADER = 289,
     T_AST_DECLARATION = 290,
     T_PARSER_DECLARATION_HEADER = 291,
     T_PARSER_BITS_HEADER = 292,
     T_AST_HEADER = 293,
     T_LEXER_DECLARATION_HEADER = 294,
     T_LEXER_BITS_HEADER = 295,
     T_PARSER_BASE = 296,
     T_AST_BASE = 297,
     T_LEXER_BASE = 298,
     T_BIN = 299,
     T_PRE = 300,
     T_POST = 301,
     T_TERN = 302,
     T_LOPR = 303,
     T_ROPR = 304,
     T_LEFT_ASSOC = 305,
     T_RIGHT_ASSOC = 306,
     T_IS_LEFT_ASSOC = 307,
     T_IS_RIGHT_ASSOC = 308,
     T_PRIORITY = 309,
     T_PAREN = 310,
     T_INLINE = 311,
     T_LEXER = 312,
     T_INPUT_STREAM = 313,
     T_INPUT_ENCODING = 314,
     T_TABLE_LEXER = 315,
     T_SEQUENCE_LEXER = 316,
     T_NAMED_REGEXP = 317,
     T_CONTINUE = 318,
     T_RANGE = 319,
     T_FAIL = 320,
     T_LOOKAHEAD = 321,
     T_BARRIER = 322,
     T_ENTER_RULE_SET = 323,
     T_LEAVE_RULE_SET = 324
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 49 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"

    KDevPG::Model::Node *item;
    char* str;
    KDevPG::Model::VariableDeclarationItem::DeclarationType declarationType;
    KDevPG::Model::VariableDeclarationItem::StorageType     storageType;
    KDevPG::Model::VariableDeclarationItem::VariableType    variableType;
    KDevPG::Model::Operator                                *operatorInformation;
    KDevPG::GNFA                                           *nfa;



/* Line 2068 of yacc.c  */
#line 131 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.hh"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


