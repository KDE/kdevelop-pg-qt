/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
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
     T_PUBLIC = 268,
     T_PRIVATE = 269,
     T_PROTECTED = 270,
     T_DECLARATION = 271,
     T_CONSTRUCTOR = 272,
     T_DESTRUCTOR = 273,
     T_TRY_RECOVER = 274,
     T_TRY_ROLLBACK = 275,
     T_CATCH = 276,
     T_RULE_ARGUMENTS = 277,
     T_MEMBER = 278,
     T_TEMPORARY = 279,
     T_ARGUMENT = 280,
     T_EXPORT_MACRO = 281,
     T_NODE = 282,
     T_NODE_SEQUENCE = 283,
     T_TOKEN = 284,
     T_VARIABLE = 285,
     T_EXPORT_MACRO_HEADER = 286,
     T_AST_DECLARATION = 287,
     T_PARSER_DECLARATION_HEADER = 288,
     T_PARSER_BITS_HEADER = 289,
     T_AST_HEADER = 290,
     T_PARSER_BASE = 291,
     T_AST_BASE = 292,
     T_BIN = 293,
     T_PRE = 294,
     T_POST = 295,
     T_TERN = 296,
     T_LOPR = 297,
     T_ROPR = 298,
     T_LEFT_ASSOC = 299,
     T_RIGHT_ASSOC = 300,
     T_IS_LEFT_ASSOC = 301,
     T_IS_RIGHT_ASSOC = 302,
     T_PRIORITY = 303,
     T_PAREN = 304
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 42 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"

    KDevPG::Model::Node *item;
    char* str;
    KDevPG::Model::VariableDeclarationItem::DeclarationType declarationType;
    KDevPG::Model::VariableDeclarationItem::StorageType     storageType;
    KDevPG::Model::VariableDeclarationItem::VariableType    variableType;
    KDevPG::Model::Operator                                *operatorInformation;



/* Line 1685 of yacc.c  */
#line 111 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.hh"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


