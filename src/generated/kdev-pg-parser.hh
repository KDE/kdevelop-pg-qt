/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

    SPDX-FileCopyrightText: 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation, Inc.

    SPDX-License-Identifier: GPL-3.0-or-later WITH Bison-exception-2.2
*/

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef KDEV_PG_PARSER_HH_INCLUDED
# define KDEV_PG_PARSER_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_IDENTIFIER = 258,            /* T_IDENTIFIER  */
    T_ARROW = 259,                 /* T_ARROW  */
    T_TERMINAL = 260,              /* T_TERMINAL  */
    T_CODE = 261,                  /* T_CODE  */
    T_STRING = 262,                /* T_STRING  */
    T_UNQUOTED_STRING = 263,       /* T_UNQUOTED_STRING  */
    T_NUMBER = 264,                /* T_NUMBER  */
    T_TOKEN_DECLARATION = 265,     /* T_TOKEN_DECLARATION  */
    T_TOKEN_STREAM_DECLARATION = 266, /* T_TOKEN_STREAM_DECLARATION  */
    T_NAMESPACE_DECLARATION = 267, /* T_NAMESPACE_DECLARATION  */
    T_PARSERCLASS_DECLARATION = 268, /* T_PARSERCLASS_DECLARATION  */
    T_LEXERCLASS_DECLARATION = 269, /* T_LEXERCLASS_DECLARATION  */
    T_PUBLIC = 270,                /* T_PUBLIC  */
    T_PRIVATE = 271,               /* T_PRIVATE  */
    T_PROTECTED = 272,             /* T_PROTECTED  */
    T_DECLARATION = 273,           /* T_DECLARATION  */
    T_BITS = 274,                  /* T_BITS  */
    T_CONSTRUCTOR = 275,           /* T_CONSTRUCTOR  */
    T_DESTRUCTOR = 276,            /* T_DESTRUCTOR  */
    T_TRY_RECOVER = 277,           /* T_TRY_RECOVER  */
    T_TRY_ROLLBACK = 278,          /* T_TRY_ROLLBACK  */
    T_CATCH = 279,                 /* T_CATCH  */
    T_RULE_ARGUMENTS = 280,        /* T_RULE_ARGUMENTS  */
    T_MEMBER = 281,                /* T_MEMBER  */
    T_TEMPORARY = 282,             /* T_TEMPORARY  */
    T_ARGUMENT = 283,              /* T_ARGUMENT  */
    T_EXPORT_MACRO = 284,          /* T_EXPORT_MACRO  */
    T_NODE = 285,                  /* T_NODE  */
    T_NODE_SEQUENCE = 286,         /* T_NODE_SEQUENCE  */
    T_TOKEN = 287,                 /* T_TOKEN  */
    T_VARIABLE = 288,              /* T_VARIABLE  */
    T_EXPORT_MACRO_HEADER = 289,   /* T_EXPORT_MACRO_HEADER  */
    T_AST_DECLARATION = 290,       /* T_AST_DECLARATION  */
    T_PARSER_DECLARATION_HEADER = 291, /* T_PARSER_DECLARATION_HEADER  */
    T_PARSER_BITS_HEADER = 292,    /* T_PARSER_BITS_HEADER  */
    T_AST_HEADER = 293,            /* T_AST_HEADER  */
    T_LEXER_DECLARATION_HEADER = 294, /* T_LEXER_DECLARATION_HEADER  */
    T_LEXER_BITS_HEADER = 295,     /* T_LEXER_BITS_HEADER  */
    T_PARSER_BASE = 296,           /* T_PARSER_BASE  */
    T_AST_BASE = 297,              /* T_AST_BASE  */
    T_LEXER_BASE = 298,            /* T_LEXER_BASE  */
    T_BIN = 299,                   /* T_BIN  */
    T_PRE = 300,                   /* T_PRE  */
    T_POST = 301,                  /* T_POST  */
    T_TERN = 302,                  /* T_TERN  */
    T_LOPR = 303,                  /* T_LOPR  */
    T_ROPR = 304,                  /* T_ROPR  */
    T_LEFT_ASSOC = 305,            /* T_LEFT_ASSOC  */
    T_RIGHT_ASSOC = 306,           /* T_RIGHT_ASSOC  */
    T_IS_LEFT_ASSOC = 307,         /* T_IS_LEFT_ASSOC  */
    T_IS_RIGHT_ASSOC = 308,        /* T_IS_RIGHT_ASSOC  */
    T_PRIORITY = 309,              /* T_PRIORITY  */
    T_PAREN = 310,                 /* T_PAREN  */
    T_INLINE = 311,                /* T_INLINE  */
    T_LEXER = 312,                 /* T_LEXER  */
    T_INPUT_STREAM = 313,          /* T_INPUT_STREAM  */
    T_INPUT_ENCODING = 314,        /* T_INPUT_ENCODING  */
    T_TABLE_LEXER = 315,           /* T_TABLE_LEXER  */
    T_SEQUENCE_LEXER = 316,        /* T_SEQUENCE_LEXER  */
    T_NAMED_REGEXP = 317,          /* T_NAMED_REGEXP  */
    T_CONTINUE = 318,              /* T_CONTINUE  */
    T_RANGE = 319,                 /* T_RANGE  */
    T_FAIL = 320,                  /* T_FAIL  */
    T_LOOKAHEAD = 321,             /* T_LOOKAHEAD  */
    T_BARRIER = 322,               /* T_BARRIER  */
    T_ENTER_RULE_SET = 323,        /* T_ENTER_RULE_SET  */
    T_LEAVE_RULE_SET = 324         /* T_LEAVE_RULE_SET  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 36 "kdev-pg-parser.yy"

    KDevPG::Model::Node *item;
    char* str;
    KDevPG::Model::VariableDeclarationItem::DeclarationType declarationType;
    KDevPG::Model::VariableDeclarationItem::StorageType     storageType;
    KDevPG::Model::VariableDeclarationItem::VariableType    variableType;
    KDevPG::Model::Operator                                *operatorInformation;
    KDevPG::GNFA                                           *nfa;

#line 143 "kdev-pg-parser.hh"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !KDEV_PG_PARSER_HH_INCLUDED  */
