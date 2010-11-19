
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


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
     T_NUMBER = 263,
     T_TOKEN_DECLARATION = 264,
     T_TOKEN_STREAM_DECLARATION = 265,
     T_NAMESPACE_DECLARATION = 266,
     T_PARSERCLASS_DECLARATION = 267,
     T_LEXERCLASS_DECLARATION = 268,
     T_PUBLIC = 269,
     T_PRIVATE = 270,
     T_PROTECTED = 271,
     T_DECLARATION = 272,
     T_BITS = 273,
     T_CONSTRUCTOR = 274,
     T_DESTRUCTOR = 275,
     T_TRY_RECOVER = 276,
     T_TRY_ROLLBACK = 277,
     T_CATCH = 278,
     T_RULE_ARGUMENTS = 279,
     T_MEMBER = 280,
     T_TEMPORARY = 281,
     T_ARGUMENT = 282,
     T_EXPORT_MACRO = 283,
     T_NODE = 284,
     T_NODE_SEQUENCE = 285,
     T_TOKEN = 286,
     T_VARIABLE = 287,
     T_EXPORT_MACRO_HEADER = 288,
     T_AST_DECLARATION = 289,
     T_PARSER_DECLARATION_HEADER = 290,
     T_PARSER_BITS_HEADER = 291,
     T_AST_HEADER = 292,
     T_TOKEN_STREAM_DECLARATION_HEADER = 293,
     T_TOKEN_STREAM_BITS_HEADER = 294,
     T_PARSER_BASE = 295,
     T_AST_BASE = 296,
     T_TOKEN_STREAM_BASE = 297,
     T_BIN = 298,
     T_PRE = 299,
     T_POST = 300,
     T_TERN = 301,
     T_LOPR = 302,
     T_ROPR = 303,
     T_LEFT_ASSOC = 304,
     T_RIGHT_ASSOC = 305,
     T_IS_LEFT_ASSOC = 306,
     T_IS_RIGHT_ASSOC = 307,
     T_PRIORITY = 308,
     T_PAREN = 309,
     T_INLINE = 310,
     T_LEXER = 311,
     T_INPUT_STREAM = 312,
     T_INPUT_ENCODING = 313,
     T_TABLE_LEXER = 314,
     T_SEQUENCE_LEXER = 315
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 46 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"

    KDevPG::Model::Node *item;
    char* str;
    KDevPG::Model::VariableDeclarationItem::DeclarationType declarationType;
    KDevPG::Model::VariableDeclarationItem::StorageType     storageType;
    KDevPG::Model::VariableDeclarationItem::VariableType    variableType;
    KDevPG::Model::Operator                                *operatorInformation;
    KDevPG::GNFA                                           *nfa;



/* Line 1676 of yacc.c  */
#line 124 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.hh"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


