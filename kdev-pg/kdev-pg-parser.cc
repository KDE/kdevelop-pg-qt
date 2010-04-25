/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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
     T_PAREN = 301
   };
#endif
/* Tokens.  */
#define T_IDENTIFIER 258
#define T_ARROW 259
#define T_TERMINAL 260
#define T_CODE 261
#define T_STRING 262
#define T_NUMBER 263
#define T_TOKEN_DECLARATION 264
#define T_TOKEN_STREAM_DECLARATION 265
#define T_NAMESPACE_DECLARATION 266
#define T_PARSERCLASS_DECLARATION 267
#define T_PUBLIC 268
#define T_PRIVATE 269
#define T_PROTECTED 270
#define T_DECLARATION 271
#define T_CONSTRUCTOR 272
#define T_DESTRUCTOR 273
#define T_TRY_RECOVER 274
#define T_TRY_ROLLBACK 275
#define T_CATCH 276
#define T_RULE_ARGUMENTS 277
#define T_MEMBER 278
#define T_TEMPORARY 279
#define T_ARGUMENT 280
#define T_EXPORT_MACRO 281
#define T_NODE 282
#define T_NODE_SEQUENCE 283
#define T_TOKEN 284
#define T_VARIABLE 285
#define T_EXPORT_MACRO_HEADER 286
#define T_AST_DECLARATION 287
#define T_PARSER_DECLARATION_HEADER 288
#define T_PARSER_BITS_HEADER 289
#define T_AST_HEADER 290
#define T_PARSER_BASE 291
#define T_AST_BASE 292
#define T_BIN 293
#define T_PRE 294
#define T_POST 295
#define T_TERN 296
#define T_LOPR 297
#define T_ROPR 298
#define T_LEFT_ASSOC 299
#define T_RIGHT_ASSOC 300
#define T_PAREN 301




/* Copy the first part of user declarations.  */
#line 2 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"

/* This file is part of kdev-pg
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>
   Copyright (C) 2006 Jakob Petsovits <jpetso@gmx.at>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "kdev-pg.h"
#include "kdev-pg-clone-tree.h"

#include <cassert>

extern int yylex();
extern void yyerror(const char* msg);

KDevPG::Model::OperatorItem *operatorNode = 0;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 36 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
{
    KDevPG::Model::Node *item;
    char* str;
    KDevPG::Model::VariableDeclarationItem::DeclarationType declarationType;
    KDevPG::Model::VariableDeclarationItem::StorateType     storageType;
    KDevPG::Model::VariableDeclarationItem::VariableType    variableType;
    KDevPG::Model::Operator                                *operatorInformation;
}
/* Line 187 of yacc.c.  */
#line 230 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 243 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   247

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNRULES -- Number of states.  */
#define YYNSTATES  205

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    52,     2,     2,     2,     2,
      48,    49,    57,    56,    50,     2,    53,     2,    51,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    55,     8,
       2,    54,     2,    58,    59,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    61,     2,    62,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    60,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    10,    12,    15,    18,    22,    26,
      29,    32,    35,    38,    41,    44,    47,    51,    54,    60,
      66,    72,    77,    82,    84,    89,    93,   100,   103,   107,
     109,   113,   115,   117,   121,   126,   129,   131,   136,   145,
     146,   148,   150,   154,   156,   158,   161,   164,   166,   169,
     171,   175,   178,   180,   182,   185,   187,   191,   193,   197,
     205,   213,   218,   219,   222,   223,   225,   228,   229,   239,
     249,   256,   261,   266,   272,   278,   282,   286,   291,   296,
     300,   303,   305,   307,   310,   317,   323,   331,   338,   339,
     341,   343,   345,   347
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      64,     0,    -1,    -1,    84,    65,    66,    70,    84,    -1,
      67,    -1,    66,    67,    -1,    13,    68,    -1,    10,    69,
       8,    -1,    11,     3,     8,    -1,    27,     7,    -1,    32,
       7,    -1,    12,     6,    -1,    33,     6,    -1,    34,     7,
      -1,    35,     7,    -1,    36,     7,    -1,    38,     3,     7,
      -1,    37,     7,    -1,    48,    14,    17,    49,     6,    -1,
      48,    16,    17,    49,     6,    -1,    48,    15,    17,    49,
       6,    -1,    48,    18,    49,     6,    -1,    48,    19,    49,
       6,    -1,     5,    -1,     5,    48,     7,    49,    -1,    69,
      50,     5,    -1,    69,    50,     5,    48,     7,    49,    -1,
      82,     8,    -1,    70,    82,     8,    -1,    51,    -1,    48,
      81,    49,    -1,    73,    -1,    72,    -1,    75,    76,    72,
      -1,    52,    75,    76,    72,    -1,     3,    74,    -1,     5,
      -1,    20,    48,    81,    49,    -1,    21,    48,    81,    49,
      22,    48,    81,    49,    -1,    -1,    23,    -1,     3,    -1,
       3,    53,     3,    -1,    54,    -1,    55,    -1,    71,    56,
      -1,    71,    57,    -1,    71,    -1,    58,    71,    -1,    77,
      -1,    78,    59,    71,    -1,    78,     6,    -1,     6,    -1,
      78,    -1,    79,    78,    -1,    79,    -1,    58,     6,    79,
      -1,    80,    -1,    81,    60,    80,    -1,    81,     4,     3,
       6,    61,    89,    62,    -1,    81,     4,     3,    61,    89,
      62,    84,    -1,    81,     4,     3,    84,    -1,    -1,    83,
      86,    -1,    -1,     6,    -1,    87,    85,    -1,    -1,    43,
      72,    85,    44,     3,    61,    89,    62,    84,    -1,    43,
      72,    85,    44,     3,     6,    61,    89,    62,    -1,    43,
      72,    85,    44,     3,    84,    -1,    39,    88,     9,    45,
      -1,    39,    88,     9,    46,    -1,    42,    88,    88,     9,
      45,    -1,    42,    88,    88,     9,    46,    -1,    40,    88,
       9,    -1,    41,    88,     9,    -1,    47,    88,    72,    88,
      -1,    58,     6,     5,     6,    -1,    58,     6,     5,    -1,
       5,     6,    -1,     5,    -1,    90,    -1,    89,    90,    -1,
      91,    92,    93,     3,    55,     3,    -1,    91,    92,    30,
       3,     8,    -1,    91,    92,    93,    52,     3,    55,     3,
      -1,    91,    92,    30,    52,     3,     8,    -1,    -1,    26,
      -1,    24,    -1,    25,    -1,    28,    -1,    31,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    73,    73,    73,    80,    81,    85,    87,    88,    90,
      92,    94,    96,    98,   100,   102,   104,   106,   111,   113,
     115,   117,   119,   124,   125,   126,   127,   132,   133,   137,
     138,   139,   140,   141,   142,   146,   147,   151,   156,   163,
     164,   168,   169,   178,   179,   183,   184,   185,   186,   190,
     191,   196,   197,   201,   202,   206,   207,   211,   212,   216,
     221,   226,   228,   228,   232,   233,   238,   239,   243,   251,
     259,   270,   271,   272,   273,   274,   275,   276,   280,   281,
     282,   283,   287,   288,   300,   302,   304,   306,   311,   312,
     316,   317,   321,   322
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_IDENTIFIER", "T_ARROW", "T_TERMINAL",
  "T_CODE", "T_STRING", "';'", "T_NUMBER", "T_TOKEN_DECLARATION",
  "T_TOKEN_STREAM_DECLARATION", "T_NAMESPACE_DECLARATION",
  "T_PARSERCLASS_DECLARATION", "T_PUBLIC", "T_PRIVATE", "T_PROTECTED",
  "T_DECLARATION", "T_CONSTRUCTOR", "T_DESTRUCTOR", "T_TRY_RECOVER",
  "T_TRY_ROLLBACK", "T_CATCH", "T_RULE_ARGUMENTS", "T_MEMBER",
  "T_TEMPORARY", "T_ARGUMENT", "T_EXPORT_MACRO", "T_NODE",
  "T_NODE_SEQUENCE", "T_TOKEN", "T_VARIABLE", "T_EXPORT_MACRO_HEADER",
  "T_AST_DECLARATION", "T_PARSER_DECLARATION_HEADER",
  "T_PARSER_BITS_HEADER", "T_AST_HEADER", "T_PARSER_BASE", "T_AST_BASE",
  "T_BIN", "T_PRE", "T_POST", "T_TERN", "T_LOPR", "T_ROPR", "T_LEFT_ASSOC",
  "T_RIGHT_ASSOC", "T_PAREN", "'('", "')'", "','", "'0'", "'#'", "'.'",
  "'='", "':'", "'+'", "'*'", "'?'", "'@'", "'|'", "'['", "']'", "$accept",
  "system", "@1", "declarations", "declaration", "member_declaration_rest",
  "declared_tokens", "rules", "primary_item", "primary_atom", "try_item",
  "rule_arguments_opt", "name", "scope", "unary_item", "postfix_item",
  "item_sequence", "conditional_item", "option_item", "item", "@2",
  "code_opt", "operatorDeclarations", "operatorRule",
  "operatorDeclaration", "operator", "variableDeclarations",
  "variableDeclaration", "declarationType_opt", "storageType",
  "variableType", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,    59,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,    40,    41,
      44,    48,    35,    46,    61,    58,    43,    42,    63,    64,
     124,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    65,    64,    66,    66,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    68,    68,
      68,    68,    68,    69,    69,    69,    69,    70,    70,    71,
      71,    71,    71,    71,    71,    72,    72,    73,    73,    74,
      74,    75,    75,    76,    76,    77,    77,    77,    77,    78,
      78,    78,    78,    79,    79,    80,    80,    81,    81,    82,
      82,    82,    83,    82,    84,    84,    85,    85,    86,    86,
      86,    87,    87,    87,    87,    87,    87,    87,    88,    88,
      88,    88,    89,    89,    90,    90,    90,    90,    91,    91,
      92,    92,    93,    93
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     5,     1,     2,     2,     3,     3,     2,
       2,     2,     2,     2,     2,     2,     3,     2,     5,     5,
       5,     4,     4,     1,     4,     3,     6,     2,     3,     1,
       3,     1,     1,     3,     4,     2,     1,     4,     8,     0,
       1,     1,     3,     1,     1,     2,     2,     1,     2,     1,
       3,     2,     1,     1,     2,     1,     3,     1,     3,     7,
       7,     4,     0,     2,     0,     1,     2,     0,     9,     9,
       6,     4,     4,     5,     5,     3,     3,     4,     4,     3,
       2,     1,     1,     2,     6,     5,     7,     6,     0,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      64,    65,     0,     2,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    62,     4,
      23,     0,     0,    11,     0,     6,     9,    10,    12,    13,
      14,    15,    17,     0,    39,    36,    52,     0,     0,     0,
      29,     0,     0,     5,    62,    47,    32,    31,     0,    49,
      53,    55,    57,     0,     0,     0,     0,     7,     0,     8,
       0,     0,     0,     0,     0,    16,    40,     0,    35,     0,
       0,     0,    41,     0,     0,    48,    52,     0,     3,    45,
      46,    43,    44,     0,    51,     0,     0,    54,     0,     0,
      27,     0,    63,     0,    25,     0,     0,     0,     0,     0,
      42,     0,     0,    30,     0,    56,    28,    39,    33,    50,
      64,    58,    67,    24,     0,     0,     0,     0,    21,    22,
      37,     0,    34,    65,    88,    61,     0,     0,     0,     0,
       0,     0,    67,     0,    18,    20,    19,     0,    88,    89,
      88,    82,     0,    81,     0,     0,     0,     0,     0,     0,
       0,    66,    26,     0,    88,    64,    83,    90,    91,     0,
      80,     0,     0,    75,    76,     0,     0,    64,     0,    59,
      60,    92,     0,    93,     0,    79,    71,    72,     0,    77,
      65,    88,    70,    38,     0,     0,     0,     0,    78,    73,
      74,    88,    88,    85,     0,     0,     0,    88,    64,    87,
      84,     0,    69,    68,    86
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    18,    19,    25,    21,    44,    45,    46,
      47,    68,    48,    83,    49,    50,    51,    52,    53,    54,
      55,     3,   131,    92,   132,   145,   140,   141,   142,   159,
     174
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -138
static const yytype_int16 yypact[] =
{
      18,  -138,    21,  -138,  -138,   153,    29,    25,    35,   -33,
      41,    43,    68,    81,    98,   109,   113,   127,    66,  -138,
      91,    31,   137,  -138,   178,  -138,  -138,  -138,  -138,  -138,
    -138,  -138,  -138,   141,    96,  -138,  -138,   104,   105,    32,
    -138,   157,   107,  -138,     6,    52,  -138,  -138,    67,  -138,
       8,    86,  -138,     1,   154,   129,   164,  -138,   168,  -138,
     159,   165,   166,   132,   135,  -138,  -138,   192,  -138,    32,
      32,   -31,   145,    67,    86,  -138,   199,   193,  -138,  -138,
    -138,  -138,  -138,    42,  -138,   126,   126,     8,   197,    32,
    -138,    42,  -138,   155,   158,   156,   160,   161,   196,   201,
    -138,   -30,   -24,  -138,    42,    86,  -138,   180,  -138,  -138,
      -2,  -138,   128,  -138,   204,   202,   206,   207,  -138,  -138,
    -138,   194,  -138,   162,   188,  -138,    15,    15,    15,    15,
      15,   171,   128,   169,  -138,  -138,  -138,   172,   188,  -138,
      20,  -138,   101,   211,   213,   212,   215,   216,    15,    42,
     219,  -138,  -138,    32,    23,    18,  -138,  -138,  -138,    12,
    -138,   221,    90,  -138,  -138,   218,    15,     2,   -16,  -138,
    -138,  -138,     4,  -138,    10,   222,  -138,  -138,   111,  -138,
     170,   188,  -138,  -138,   224,   226,   175,   230,  -138,  -138,
    -138,   188,    70,  -138,   227,   231,   181,    71,    18,  -138,
    -138,   234,  -138,  -138,  -138
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -138,  -138,  -138,  -138,   220,  -138,  -138,  -138,     9,   -81,
    -138,  -138,   198,   167,  -138,   -35,   173,   152,   -38,   200,
    -138,   -44,   110,  -138,  -138,    13,  -116,  -137,  -138,  -138,
    -138
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -66
static const yytype_int16 yytable[] =
{
      78,    71,   108,   156,   123,    88,   -64,   184,   180,    34,
     112,    35,    76,   186,    84,    24,    87,   156,   103,   120,
     143,     4,   154,   122,     1,   121,    37,    38,    22,    89,
      89,   101,   102,   183,    20,    34,    89,    35,    36,    57,
     171,    23,   172,   173,    89,   107,   139,    35,    26,   139,
      27,    75,    37,    38,    39,   156,   185,    40,    41,   124,
     156,    89,   187,   181,    42,   192,   125,    85,   166,    34,
      87,    35,    36,   144,    28,   197,     6,     7,     8,     9,
      39,    58,   155,    40,    41,   169,    37,    38,    29,    34,
      42,    35,    36,    10,   109,    75,   139,   139,    11,    12,
      13,    14,    15,    16,    17,    30,    37,    38,    79,    80,
      34,   170,    35,    74,    39,   168,    31,    40,    41,    66,
      32,    81,    82,   182,    42,   157,   158,    37,    38,    34,
      33,    35,   198,   202,    39,   176,   177,    40,    41,    56,
     146,   147,   148,   149,    86,    59,    37,    38,    65,    67,
     -41,   -41,    69,    70,   203,    39,   189,   190,    40,    41,
      72,   165,    90,     6,     7,     8,     9,   126,   127,   128,
     129,    93,    91,    94,    39,   130,    95,    40,    41,   179,
      10,    98,    96,    97,    99,    11,    12,    13,    14,    15,
      16,    17,    60,    61,    62,   100,    63,    64,    67,   -65,
     110,   106,   118,    66,   113,   115,   114,   119,   134,   116,
     117,   133,   135,   136,   139,   150,   137,   160,   152,   161,
     153,   162,   167,   138,   163,   164,   175,   178,   188,   194,
     195,   191,   193,   196,   200,   199,   201,   204,    43,    73,
     104,   111,   151,     0,    77,     0,     0,   105
};

static const yytype_int16 yycheck[] =
{
      44,    39,    83,   140,     6,     4,     0,     3,     6,     3,
      91,     5,     6,     3,     6,    48,    51,   154,    49,    49,
       5,     0,   138,   104,     6,    49,    20,    21,     3,    60,
      60,    69,    70,    49,     5,     3,    60,     5,     6,     8,
      28,     6,    30,    31,    60,     3,    26,     5,     7,    26,
       7,    42,    20,    21,    48,   192,    52,    51,    52,    61,
     197,    60,    52,    61,    58,   181,   110,    59,   149,     3,
     105,     5,     6,    58,     6,   191,    10,    11,    12,    13,
      48,    50,    62,    51,    52,    62,    20,    21,     7,     3,
      58,     5,     6,    27,    85,    86,    26,    26,    32,    33,
      34,    35,    36,    37,    38,     7,    20,    21,    56,    57,
       3,   155,     5,     6,    48,   153,     7,    51,    52,    23,
       7,    54,    55,   167,    58,    24,    25,    20,    21,     3,
       3,     5,    62,    62,    48,    45,    46,    51,    52,    48,
     127,   128,   129,   130,    58,     8,    20,    21,     7,    53,
      54,    55,    48,    48,   198,    48,    45,    46,    51,    52,
       3,   148,     8,    10,    11,    12,    13,    39,    40,    41,
      42,     7,    43,     5,    48,    47,    17,    51,    52,   166,
      27,    49,    17,    17,    49,    32,    33,    34,    35,    36,
      37,    38,    14,    15,    16,     3,    18,    19,    53,     0,
       3,     8,     6,    23,    49,    49,    48,     6,     6,    49,
      49,     7,     6,     6,    26,    44,    22,     6,    49,     6,
      48,     9,     3,    61,     9,     9,     5,     9,     6,     3,
      55,    61,     8,     3,     3,     8,    55,     3,    18,    41,
      73,    89,   132,    -1,    44,    -1,    -1,    74
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    64,    84,     0,    65,    10,    11,    12,    13,
      27,    32,    33,    34,    35,    36,    37,    38,    66,    67,
       5,    69,     3,     6,    48,    68,     7,     7,     6,     7,
       7,     7,     7,     3,     3,     5,     6,    20,    21,    48,
      51,    52,    58,    67,    70,    71,    72,    73,    75,    77,
      78,    79,    80,    81,    82,    83,    48,     8,    50,     8,
      14,    15,    16,    18,    19,     7,    23,    53,    74,    48,
      48,    81,     3,    75,     6,    71,     6,    82,    84,    56,
      57,    54,    55,    76,     6,    59,    58,    78,     4,    60,
       8,    43,    86,     7,     5,    17,    17,    17,    49,    49,
       3,    81,    81,    49,    76,    79,     8,     3,    72,    71,
       3,    80,    72,    49,    48,    49,    49,    49,     6,     6,
      49,    49,    72,     6,    61,    84,    39,    40,    41,    42,
      47,    85,    87,     7,     6,     6,     6,    22,    61,    26,
      89,    90,    91,     5,    58,    88,    88,    88,    88,    88,
      44,    85,    49,    48,    89,    62,    90,    24,    25,    92,
       6,     6,     9,     9,     9,    88,    72,     3,    81,    62,
      84,    28,    30,    31,    93,     5,    45,    46,     9,    88,
       6,    61,    84,    49,     3,    52,     3,    52,     6,    45,
      46,    61,    89,     8,     3,    55,     3,    89,    62,     8,
       3,    55,    62,    84,     3
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 73 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.decl = (yyvsp[(1) - (1)].str); ;}
    break;

  case 3:
#line 76 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.bits = (yyvsp[(5) - (5)].str); ;}
    break;

  case 6:
#line 86 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserClassMember((yyvsp[(2) - (2)].item)); ;}
    break;

  case 8:
#line 89 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.tokenStream = (yyvsp[(2) - (3)].str);           ;}
    break;

  case 9:
#line 91 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.exportMacro = (yyvsp[(2) - (2)].str);           ;}
    break;

  case 10:
#line 93 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.exportMacroHeader = (yyvsp[(2) - (2)].str);     ;}
    break;

  case 11:
#line 95 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.namespaceCode = (yyvsp[(2) - (2)].str);         ;}
    break;

  case 12:
#line 97 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.astCode = (yyvsp[(2) - (2)].str);               ;}
    break;

  case 13:
#line 99 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserDeclarationHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 14:
#line 101 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserBitsHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 15:
#line 103 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushAstHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 16:
#line 105 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.astBaseClasses[(yyvsp[(2) - (3)].str)] = (yyvsp[(3) - (3)].str); ;}
    break;

  case 17:
#line 107 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.parserBaseClass = (yyvsp[(2) - (2)].str); ;}
    break;

  case 18:
#line 112 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PublicDeclaration, (yyvsp[(5) - (5)].str));    ;}
    break;

  case 19:
#line 114 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ProtectedDeclaration, (yyvsp[(5) - (5)].str)); ;}
    break;

  case 20:
#line 116 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PrivateDeclaration, (yyvsp[(5) - (5)].str));   ;}
    break;

  case 21:
#line 118 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ConstructorCode, (yyvsp[(4) - (4)].str));      ;}
    break;

  case 22:
#line 120 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::DestructorCode, (yyvsp[(4) - (4)].str));       ;}
    break;

  case 23:
#line 124 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(1) - (1)].str),(yyvsp[(1) - (1)].str)); ;}
    break;

  case 24:
#line 125 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(1) - (4)].str),(yyvsp[(3) - (4)].str)); ;}
    break;

  case 25:
#line 126 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(3) - (3)].str),(yyvsp[(3) - (3)].str)); ;}
    break;

  case 26:
#line 128 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(3) - (6)].str),(yyvsp[(5) - (6)].str)); ;}
    break;

  case 27:
#line 132 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushRule((yyvsp[(1) - (2)].item)); ;}
    break;

  case 28:
#line 133 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushRule((yyvsp[(2) - (3)].item)); ;}
    break;

  case 29:
#line 137 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::globalSystem.zero(); ;}
    break;

  case 30:
#line 138 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(2) - (3)].item); ;}
    break;

  case 31:
#line 139 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 32:
#line 140 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 33:
#line 141 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::annotation((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].item), false, (yyvsp[(2) - (3)].storageType)); ;}
    break;

  case 34:
#line 142 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::annotation((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].item), true, (yyvsp[(3) - (4)].storageType));  ;}
    break;

  case 35:
#line 146 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::nonTerminal(KDevPG::globalSystem.pushSymbol((yyvsp[(1) - (2)].str)), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 36:
#line 147 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::globalSystem.terminal((yyvsp[(1) - (1)].str)); ;}
    break;

  case 37:
#line 152 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[(3) - (4)].item), 0);
        ;}
    break;

  case 38:
#line 157 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[(3) - (8)].item), (yyvsp[(7) - (8)].item));
        ;}
    break;

  case 39:
#line 163 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = const_cast<char*>(""); ;}
    break;

  case 40:
#line 164 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 41:
#line 168 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 42:
#line 170 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.str) = (yyvsp[(3) - (3)].str);
          fprintf(stderr, "** WARNING support for scoped name"
                          " ``%s.%s'' not implemented\n", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
        ;}
    break;

  case 43:
#line 178 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember; ;}
    break;

  case 44:
#line 179 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;  ;}
    break;

  case 45:
#line 183 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::plus((yyvsp[(1) - (2)].item)); ;}
    break;

  case 46:
#line 184 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::star((yyvsp[(1) - (2)].item)); ;}
    break;

  case 47:
#line 185 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 48:
#line 186 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::alternative((yyvsp[(2) - (2)].item), KDevPG::globalSystem.zero()); ;}
    break;

  case 49:
#line 190 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 50:
#line 192 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::CloneTree cl;
          (yyval.item) = KDevPG::cons((yyvsp[(1) - (3)].item), KDevPG::star(KDevPG::cons(cl.clone((yyvsp[(3) - (3)].item)), cl.clone((yyvsp[(1) - (3)].item)))));
        ;}
    break;

  case 51:
#line 196 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::action((yyvsp[(1) - (2)].item), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 52:
#line 197 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::action(0, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 53:
#line 201 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 54:
#line 202 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::cons((yyvsp[(1) - (2)].item), (yyvsp[(2) - (2)].item)); ;}
    break;

  case 55:
#line 206 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 56:
#line 207 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::condition((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].item)); ;}
    break;

  case 57:
#line 211 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 58:
#line 212 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::alternative((yyvsp[(1) - (3)].item), (yyvsp[(3) - (3)].item)); ;}
    break;

  case 59:
#line 217 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.item) = KDevPG::evolve((yyvsp[(1) - (7)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (7)].str)),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(6) - (7)].item), (yyvsp[(4) - (7)].str));
        ;}
    break;

  case 60:
#line 222 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.item) = KDevPG::evolve((yyvsp[(1) - (7)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (7)].str)),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(5) - (7)].item), (yyvsp[(7) - (7)].str));
        ;}
    break;

  case 61:
#line 227 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::evolve((yyvsp[(1) - (4)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (4)].str)), 0, (yyvsp[(4) - (4)].str)); ;}
    break;

  case 62:
#line 228 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode = KDevPG::createNode<KDevPG::Model::OperatorItem>(); ;}
    break;

  case 63:
#line 228 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.needOperatorStack = true; (yyval.item) = (yyvsp[(2) - (2)].item); ;}
    break;

  case 64:
#line 232 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = const_cast<char*>(""); ;}
    break;

  case 65:
#line 233 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 67:
#line 239 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { ; ;}
    break;

  case 68:
#line 244 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (9)].item);
              operatorNode->mName = (yyvsp[(5) - (9)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (9)].str)), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[(7) - (9)].item), (yyvsp[(9) - (9)].str));
            ;}
    break;

  case 69:
#line 252 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (9)].item);
              operatorNode->mName = (yyvsp[(5) - (9)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (9)].str)), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[(8) - (9)].item), (yyvsp[(6) - (9)].str));
            ;}
    break;

  case 70:
#line 260 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (6)].item);
              operatorNode->mName = (yyvsp[(5) - (6)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (6)].str)), 0, (yyvsp[(6) - (6)].str));
            ;}
    break;

  case 71:
#line 270 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushBin(*(yyvsp[(2) - (4)].operatorInformation), true, (yyvsp[(3) - (4)].str)); delete (yyvsp[(2) - (4)].operatorInformation); ;}
    break;

  case 72:
#line 271 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushBin(*(yyvsp[(2) - (4)].operatorInformation), false, (yyvsp[(3) - (4)].str)); delete (yyvsp[(2) - (4)].operatorInformation); ;}
    break;

  case 73:
#line 272 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushTern(*(yyvsp[(2) - (5)].operatorInformation), *(yyvsp[(3) - (5)].operatorInformation), true, (yyvsp[(4) - (5)].str)); delete (yyvsp[(2) - (5)].operatorInformation); delete (yyvsp[(3) - (5)].operatorInformation); ;}
    break;

  case 74:
#line 273 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushTern(*(yyvsp[(2) - (5)].operatorInformation), *(yyvsp[(3) - (5)].operatorInformation), false, (yyvsp[(4) - (5)].str)); delete (yyvsp[(2) - (5)].operatorInformation); delete (yyvsp[(3) - (5)].operatorInformation); ;}
    break;

  case 75:
#line 274 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPre(*(yyvsp[(2) - (3)].operatorInformation), (yyvsp[(3) - (3)].str)); delete (yyvsp[(2) - (3)].operatorInformation); ;}
    break;

  case 76:
#line 275 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPost(*(yyvsp[(2) - (3)].operatorInformation), (yyvsp[(3) - (3)].str)); delete (yyvsp[(2) - (3)].operatorInformation); ;}
    break;

  case 77:
#line 276 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushParen(*(yyvsp[(2) - (4)].operatorInformation), *(yyvsp[(4) - (4)].operatorInformation), (KDevPG::Model::NonTerminalItem*)(yyvsp[(3) - (4)].item)); delete (yyvsp[(2) - (4)].operatorInformation); delete (yyvsp[(4) - (4)].operatorInformation); ;}
    break;

  case 78:
#line 280 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator((yyvsp[(3) - (4)].str), (yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].str)); ;}
    break;

  case 79:
#line 281 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator((yyvsp[(3) - (3)].str), (yyvsp[(2) - (3)].str), ""); ;}
    break;

  case 80:
#line 282 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator((yyvsp[(1) - (2)].str), "", (yyvsp[(2) - (2)].str)); ;}
    break;

  case 81:
#line 283 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator((yyvsp[(1) - (1)].str), "", ""); ;}
    break;

  case 82:
#line 287 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 83:
#line 289 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::Model::VariableDeclarationItem *last = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(1) - (2)].item);
          while (last->mNext != 0) {
            last = last->mNext;
          }
          last->mNext = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(2) - (2)].item);
          (yyval.item) = (yyvsp[(1) - (2)].item);
        ;}
    break;

  case 84:
#line 301 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (6)].declarationType), (yyvsp[(2) - (6)].storageType), (yyvsp[(3) - (6)].variableType), false, (yyvsp[(4) - (6)].str), (yyvsp[(6) - (6)].str)); ;}
    break;

  case 85:
#line 303 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (5)].declarationType), (yyvsp[(2) - (5)].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, false, (yyvsp[(4) - (5)].str), ""); ;}
    break;

  case 86:
#line 305 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (7)].declarationType), (yyvsp[(2) - (7)].storageType), (yyvsp[(3) - (7)].variableType), true, (yyvsp[(5) - (7)].str), (yyvsp[(7) - (7)].str)); ;}
    break;

  case 87:
#line 307 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (6)].declarationType), (yyvsp[(2) - (6)].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, true, (yyvsp[(5) - (6)].str), ""); ;}
    break;

  case 88:
#line 311 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationLocal;     ;}
    break;

  case 89:
#line 312 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationArgument;  ;}
    break;

  case 90:
#line 316 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember;    ;}
    break;

  case 91:
#line 317 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;     ;}
    break;

  case 92:
#line 321 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeNode;             ;}
    break;

  case 93:
#line 322 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeVariable;         ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2120 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 325 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"


