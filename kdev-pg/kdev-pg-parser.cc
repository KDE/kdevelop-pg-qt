/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
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

#include <QtCore/QFile>
#include <cassert>

extern int yylex();
extern void yyerror(const char* msg);
extern int yyLine;

namespace KDevPG
{
    extern QFile file;
}

KDevPG::Model::OperatorItem *operatorNode = 0;



/* Line 189 of yacc.c  */
#line 113 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"

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

/* Line 214 of yacc.c  */
#line 42 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"

    KDevPG::Model::Node *item;
    char* str;
    KDevPG::Model::VariableDeclarationItem::DeclarationType declarationType;
    KDevPG::Model::VariableDeclarationItem::StorageType     storageType;
    KDevPG::Model::VariableDeclarationItem::VariableType    variableType;
    KDevPG::Model::Operator                                *operatorInformation;



/* Line 214 of yacc.c  */
#line 209 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 221 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   251

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNRULES -- Number of states.  */
#define YYNSTATES  213

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    55,     2,     2,     2,     2,
      51,    52,    60,    59,    53,     2,    56,     2,    54,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,     9,
       2,    57,     2,    61,    62,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    64,     2,    65,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    63,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50
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
     249,   256,   261,   267,   271,   275,   280,   284,   286,   288,
     291,   293,   295,   298,   301,   306,   310,   313,   315,   317,
     320,   327,   333,   341,   348,   349,   351,   353,   355,   357
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      67,     0,    -1,    -1,    87,    68,    69,    73,    87,    -1,
      70,    -1,    69,    70,    -1,    13,    71,    -1,    10,    72,
       9,    -1,    11,     3,     9,    -1,    27,     7,    -1,    32,
       7,    -1,    12,     6,    -1,    33,     6,    -1,    34,     7,
      -1,    35,     7,    -1,    36,     7,    -1,    38,     3,     7,
      -1,    37,     7,    -1,    51,    14,    17,    52,     6,    -1,
      51,    16,    17,    52,     6,    -1,    51,    15,    17,    52,
       6,    -1,    51,    18,    52,     6,    -1,    51,    19,    52,
       6,    -1,     5,    -1,     5,    51,     7,    52,    -1,    72,
      53,     5,    -1,    72,    53,     5,    51,     7,    52,    -1,
      85,     9,    -1,    73,    85,     9,    -1,    54,    -1,    51,
      84,    52,    -1,    76,    -1,    75,    -1,    78,    79,    75,
      -1,    55,    78,    79,    75,    -1,     3,    77,    -1,     5,
      -1,    20,    51,    84,    52,    -1,    21,    51,    84,    52,
      22,    51,    84,    52,    -1,    -1,    23,    -1,     3,    -1,
       3,    56,     3,    -1,    57,    -1,    58,    -1,    74,    59,
      -1,    74,    60,    -1,    74,    -1,    61,    74,    -1,    80,
      -1,    81,    62,    74,    -1,    81,     6,    -1,     6,    -1,
      81,    -1,    82,    81,    -1,    82,    -1,    61,     6,    82,
      -1,    83,    -1,    84,    63,    83,    -1,    84,     4,     3,
       6,    64,    94,    65,    -1,    84,     4,     3,    64,    94,
      65,    87,    -1,    84,     4,     3,    87,    -1,    -1,    86,
      89,    -1,    -1,     6,    -1,    90,    88,    -1,    -1,    43,
      75,    88,    44,     3,    64,    94,    65,    87,    -1,    43,
      75,    88,    44,     3,     6,    64,    94,    65,    -1,    43,
      75,    88,    44,     3,    87,    -1,    39,    93,    91,    92,
      -1,    42,    93,    93,    91,    92,    -1,    40,    93,    91,
      -1,    41,    93,    91,    -1,    41,    93,    91,    92,    -1,
      50,    93,    93,    -1,    54,    -1,     8,    -1,    49,     6,
      -1,    45,    -1,    46,    -1,    47,     6,    -1,    48,     6,
      -1,    61,     6,     5,     6,    -1,    61,     6,     5,    -1,
       5,     6,    -1,     5,    -1,    95,    -1,    94,    95,    -1,
      96,    97,    98,     3,    58,     3,    -1,    96,    97,    30,
       3,     9,    -1,    96,    97,    98,    55,     3,    58,     3,
      -1,    96,    97,    30,    55,     3,     9,    -1,    -1,    26,
      -1,    24,    -1,    25,    -1,    28,    -1,    31,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    79,    79,    79,    86,    87,    91,    93,    94,    96,
      98,   100,   102,   104,   106,   108,   110,   112,   117,   119,
     121,   123,   125,   130,   131,   132,   133,   138,   139,   143,
     144,   145,   146,   147,   148,   152,   153,   157,   162,   169,
     170,   174,   175,   184,   185,   189,   190,   191,   192,   196,
     197,   202,   203,   207,   208,   212,   213,   217,   218,   222,
     227,   232,   234,   234,   244,   245,   250,   251,   255,   263,
     271,   282,   283,   284,   285,   286,   287,   291,   292,   293,
     297,   298,   299,   306,   316,   317,   318,   319,   323,   324,
     336,   338,   340,   342,   347,   348,   352,   353,   357,   358
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_IDENTIFIER", "T_ARROW", "T_TERMINAL",
  "T_CODE", "T_STRING", "T_NUMBER", "';'", "T_TOKEN_DECLARATION",
  "T_TOKEN_STREAM_DECLARATION", "T_NAMESPACE_DECLARATION",
  "T_PARSERCLASS_DECLARATION", "T_PUBLIC", "T_PRIVATE", "T_PROTECTED",
  "T_DECLARATION", "T_CONSTRUCTOR", "T_DESTRUCTOR", "T_TRY_RECOVER",
  "T_TRY_ROLLBACK", "T_CATCH", "T_RULE_ARGUMENTS", "T_MEMBER",
  "T_TEMPORARY", "T_ARGUMENT", "T_EXPORT_MACRO", "T_NODE",
  "T_NODE_SEQUENCE", "T_TOKEN", "T_VARIABLE", "T_EXPORT_MACRO_HEADER",
  "T_AST_DECLARATION", "T_PARSER_DECLARATION_HEADER",
  "T_PARSER_BITS_HEADER", "T_AST_HEADER", "T_PARSER_BASE", "T_AST_BASE",
  "T_BIN", "T_PRE", "T_POST", "T_TERN", "T_LOPR", "T_ROPR", "T_LEFT_ASSOC",
  "T_RIGHT_ASSOC", "T_IS_LEFT_ASSOC", "T_IS_RIGHT_ASSOC", "T_PRIORITY",
  "T_PAREN", "'('", "')'", "','", "'0'", "'#'", "'.'", "'='", "':'", "'+'",
  "'*'", "'?'", "'@'", "'|'", "'['", "']'", "$accept", "system", "$@1",
  "declarations", "declaration", "member_declaration_rest",
  "declared_tokens", "rules", "primary_item", "primary_atom", "try_item",
  "rule_arguments_opt", "name", "scope", "unary_item", "postfix_item",
  "item_sequence", "conditional_item", "option_item", "item", "$@2",
  "code_opt", "operatorDeclarations", "operatorRule",
  "operatorDeclaration", "priority", "assoc", "operator",
  "variableDeclarations", "variableDeclaration", "declarationType_opt",
  "storageType", "variableType", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,    59,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,    40,    41,    44,    48,    35,    46,    61,    58,    43,
      42,    63,    64,   124,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    66,    68,    67,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    71,    71,
      71,    71,    71,    72,    72,    72,    72,    73,    73,    74,
      74,    74,    74,    74,    74,    75,    75,    76,    76,    77,
      77,    78,    78,    79,    79,    80,    80,    80,    80,    81,
      81,    81,    81,    82,    82,    83,    83,    84,    84,    85,
      85,    85,    86,    85,    87,    87,    88,    88,    89,    89,
      89,    90,    90,    90,    90,    90,    90,    91,    91,    91,
      92,    92,    92,    92,    93,    93,    93,    93,    94,    94,
      95,    95,    95,    95,    96,    96,    97,    97,    98,    98
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
       6,     4,     5,     3,     3,     4,     3,     1,     1,     2,
       1,     1,     2,     2,     4,     3,     2,     1,     1,     2,
       6,     5,     7,     6,     0,     1,     1,     1,     1,     1
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
      37,     0,    34,    65,    94,    61,     0,     0,     0,     0,
       0,     0,    67,     0,    18,    20,    19,     0,    94,    95,
      94,    88,     0,    87,     0,     0,     0,     0,     0,     0,
       0,    66,    26,     0,    94,    64,    89,    96,    97,     0,
      86,     0,    78,     0,    77,     0,    73,    74,     0,    76,
      64,     0,    59,    60,    98,     0,    99,     0,    85,    79,
      80,    81,     0,     0,    71,    75,     0,    65,    94,    70,
      38,     0,     0,     0,     0,    84,    82,    83,    72,    94,
      94,    91,     0,     0,     0,    94,    64,    93,    90,     0,
      69,    68,    92
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    18,    19,    25,    21,    44,    45,    46,
      47,    68,    48,    83,    49,    50,    51,    52,    53,    54,
      55,     3,   131,    92,   132,   165,   184,   145,   140,   141,
     142,   159,   177
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -140
static const yytype_int16 yypact[] =
{
       9,  -140,    36,  -140,  -140,   138,    37,    43,    68,    59,
     107,   110,   113,   122,   125,   131,   154,   142,    67,  -140,
     112,    40,   172,  -140,   164,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,   182,    84,  -140,  -140,   141,   143,    14,
    -140,   190,    92,  -140,     3,   -30,  -140,  -140,   102,  -140,
      -1,    35,  -140,     0,   186,   153,   191,  -140,   192,  -140,
     183,   184,   185,   147,   151,  -140,  -140,   201,  -140,    14,
      14,    57,   149,   102,    35,  -140,   206,   198,  -140,  -140,
    -140,  -140,  -140,    34,  -140,   103,   103,    -1,   205,    14,
    -140,    34,  -140,   157,   159,   161,   162,   163,   210,   211,
    -140,    64,    81,  -140,    34,    35,  -140,   188,  -140,  -140,
      12,  -140,   127,  -140,   212,   214,   215,   216,  -140,  -140,
    -140,   196,  -140,   148,   197,  -140,    21,    21,    21,    21,
      21,   180,   127,   173,  -140,  -140,  -140,   175,   197,  -140,
     -15,  -140,    20,   221,   222,    76,    76,    76,    21,    21,
     226,  -140,  -140,    14,   -14,     9,  -140,  -140,  -140,   160,
    -140,   225,  -140,   227,  -140,   139,  -140,   139,    76,  -140,
      19,   101,  -140,  -140,  -140,     4,  -140,    30,   228,  -140,
    -140,  -140,   229,   230,  -140,  -140,   139,   167,   197,  -140,
    -140,   223,   234,   181,   235,  -140,  -140,  -140,  -140,   197,
     -13,  -140,   231,   238,   187,   -12,     9,  -140,  -140,   239,
    -140,  -140,  -140
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -140,  -140,  -140,  -140,   232,  -140,  -140,  -140,     6,    48,
    -140,  -140,   202,   171,  -140,   -24,   174,   158,   -38,   207,
    -140,   -44,   114,  -140,  -140,  -125,  -139,     7,  -128,  -138,
    -140,  -140,  -140
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -66
static const yytype_int16 yytable[] =
{
      78,    71,   156,   -64,    88,    84,    34,   191,    35,    76,
     154,   139,   139,   139,   139,     1,   156,    34,   123,    35,
      36,   166,   167,    37,    38,   187,   143,    87,   185,    79,
      80,   101,   102,   193,    37,    38,     4,   107,    34,    35,
      35,    36,    20,   186,   157,   158,    22,   198,    75,    57,
     155,   172,   206,   210,    39,    37,    38,    40,    41,   192,
     200,    85,   156,    89,    42,    39,   125,   156,    40,    41,
      34,   205,    35,    36,    23,    42,   124,     6,     7,     8,
       9,    87,   144,   188,   162,   194,    39,    37,    38,    40,
      41,   109,    75,    58,    10,    34,    86,    35,    74,    11,
      12,    13,    14,    15,    16,    17,    34,    66,    35,   103,
      24,   173,    37,    38,    26,   171,   120,    27,    39,    28,
      89,    40,    41,    37,    38,   163,   189,    89,    42,    29,
     164,   108,    30,   121,   146,   147,   148,   149,    31,   112,
      67,   -41,   -41,    39,    89,    33,    40,    41,     6,     7,
       8,     9,   122,   190,    39,   168,   169,    40,    41,    81,
      82,    32,   211,    56,    89,    10,   126,   127,   128,   129,
      11,    12,    13,    14,    15,    16,    17,   130,    60,    61,
      62,    59,    63,    64,   180,   181,   182,   183,   174,    65,
     175,   176,    69,    72,    70,    90,    91,    94,    93,    98,
      95,    96,    97,    99,   100,    67,   -65,   106,   110,   113,
     114,    66,   138,   115,   116,   117,   118,   119,   137,   133,
     134,   135,   136,   139,   150,   152,   153,   160,   161,   170,
     178,   199,   201,   179,   195,   196,   197,   202,   204,   203,
     207,   208,   212,    73,   104,   209,   151,   111,   105,     0,
      43,    77
};

static const yytype_int16 yycheck[] =
{
      44,    39,   140,     0,     4,     6,     3,     3,     5,     6,
     138,    26,    26,    26,    26,     6,   154,     3,     6,     5,
       6,   146,   147,    20,    21,     6,     5,    51,   167,    59,
      60,    69,    70,     3,    20,    21,     0,     3,     3,     5,
       5,     6,     5,   168,    24,    25,     3,   186,    42,     9,
      65,    65,    65,    65,    51,    20,    21,    54,    55,    55,
     188,    62,   200,    63,    61,    51,   110,   205,    54,    55,
       3,   199,     5,     6,     6,    61,    64,    10,    11,    12,
      13,   105,    61,    64,     8,    55,    51,    20,    21,    54,
      55,    85,    86,    53,    27,     3,    61,     5,     6,    32,
      33,    34,    35,    36,    37,    38,     3,    23,     5,    52,
      51,   155,    20,    21,     7,   153,    52,     7,    51,     6,
      63,    54,    55,    20,    21,    49,   170,    63,    61,     7,
      54,    83,     7,    52,   127,   128,   129,   130,     7,    91,
      56,    57,    58,    51,    63,     3,    54,    55,    10,    11,
      12,    13,   104,    52,    51,   148,   149,    54,    55,    57,
      58,     7,   206,    51,    63,    27,    39,    40,    41,    42,
      32,    33,    34,    35,    36,    37,    38,    50,    14,    15,
      16,     9,    18,    19,    45,    46,    47,    48,    28,     7,
      30,    31,    51,     3,    51,     9,    43,     5,     7,    52,
      17,    17,    17,    52,     3,    56,     0,     9,     3,    52,
      51,    23,    64,    52,    52,    52,     6,     6,    22,     7,
       6,     6,     6,    26,    44,    52,    51,     6,     6,     3,
       5,    64,     9,     6,     6,     6,     6,     3,     3,    58,
       9,     3,     3,    41,    73,    58,   132,    89,    74,    -1,
      18,    44
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    67,    87,     0,    68,    10,    11,    12,    13,
      27,    32,    33,    34,    35,    36,    37,    38,    69,    70,
       5,    72,     3,     6,    51,    71,     7,     7,     6,     7,
       7,     7,     7,     3,     3,     5,     6,    20,    21,    51,
      54,    55,    61,    70,    73,    74,    75,    76,    78,    80,
      81,    82,    83,    84,    85,    86,    51,     9,    53,     9,
      14,    15,    16,    18,    19,     7,    23,    56,    77,    51,
      51,    84,     3,    78,     6,    74,     6,    85,    87,    59,
      60,    57,    58,    79,     6,    62,    61,    81,     4,    63,
       9,    43,    89,     7,     5,    17,    17,    17,    52,    52,
       3,    84,    84,    52,    79,    82,     9,     3,    75,    74,
       3,    83,    75,    52,    51,    52,    52,    52,     6,     6,
      52,    52,    75,     6,    64,    87,    39,    40,    41,    42,
      50,    88,    90,     7,     6,     6,     6,    22,    64,    26,
      94,    95,    96,     5,    61,    93,    93,    93,    93,    93,
      44,    88,    52,    51,    94,    65,    95,    24,    25,    97,
       6,     6,     8,    49,    54,    91,    91,    91,    93,    93,
       3,    84,    65,    87,    28,    30,    31,    98,     5,     6,
      45,    46,    47,    48,    92,    92,    91,     6,    64,    87,
      52,     3,    55,     3,    55,     6,     6,     6,    92,    64,
      94,     9,     3,    58,     3,    94,    65,     9,     3,    58,
      65,    87,     3
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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

/* Line 1464 of yacc.c  */
#line 79 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.decl = (yyvsp[(1) - (1)].str); ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 82 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.bits = (yyvsp[(5) - (5)].str); ;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 92 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserClassMember((yyvsp[(2) - (2)].item)); ;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 95 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.tokenStream = (yyvsp[(2) - (3)].str);           ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 97 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.exportMacro = (yyvsp[(2) - (2)].str);           ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 99 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.exportMacroHeader = (yyvsp[(2) - (2)].str);     ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 101 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.namespaceCode = (yyvsp[(2) - (2)].str);         ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 103 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.astCode = (yyvsp[(2) - (2)].str);               ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 105 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserDeclarationHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 107 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserBitsHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 109 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushAstHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 111 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.astBaseClasses[(yyvsp[(2) - (3)].str)] = (yyvsp[(3) - (3)].str); ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 113 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.parserBaseClass = (yyvsp[(2) - (2)].str); ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 118 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PublicDeclaration, (yyvsp[(5) - (5)].str));    ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 120 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ProtectedDeclaration, (yyvsp[(5) - (5)].str)); ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 122 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PrivateDeclaration, (yyvsp[(5) - (5)].str));   ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 124 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ConstructorCode, (yyvsp[(4) - (4)].str));      ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 126 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::DestructorCode, (yyvsp[(4) - (4)].str));       ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 130 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(1) - (1)].str),(yyvsp[(1) - (1)].str)); ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 131 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(1) - (4)].str),(yyvsp[(3) - (4)].str)); ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 132 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(3) - (3)].str),(yyvsp[(3) - (3)].str)); ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 134 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(3) - (6)].str),(yyvsp[(5) - (6)].str)); ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 138 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushRule((yyvsp[(1) - (2)].item)); ;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 139 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushRule((yyvsp[(2) - (3)].item)); ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 143 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::globalSystem.zero(); ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 144 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(2) - (3)].item); ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 145 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 146 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 147 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::annotation((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].item), false, (yyvsp[(2) - (3)].storageType)); ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 148 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::annotation((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].item), true, (yyvsp[(3) - (4)].storageType));  ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 152 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::nonTerminal(KDevPG::globalSystem.pushSymbol((yyvsp[(1) - (2)].str)), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 153 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::globalSystem.terminal((yyvsp[(1) - (1)].str)); ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 158 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[(3) - (4)].item), 0);
        ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 163 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[(3) - (8)].item), (yyvsp[(7) - (8)].item));
        ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 169 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = const_cast<char*>(""); ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 170 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 174 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 176 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.str) = (yyvsp[(3) - (3)].str);
          fprintf(stderr, "** WARNING support for scoped name"
                          " ``%s.%s'' not implemented\n", (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].str));
        ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 184 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember; ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 185 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;  ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 189 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::plus((yyvsp[(1) - (2)].item)); ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 190 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::star((yyvsp[(1) - (2)].item)); ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 191 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 192 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::alternative((yyvsp[(2) - (2)].item), KDevPG::globalSystem.zero()); ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 196 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 198 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::CloneTree cl;
          (yyval.item) = KDevPG::cons((yyvsp[(1) - (3)].item), KDevPG::star(KDevPG::cons(cl.clone((yyvsp[(3) - (3)].item)), cl.clone((yyvsp[(1) - (3)].item)))));
        ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 202 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::action((yyvsp[(1) - (2)].item), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 203 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::action(0, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 207 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 208 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::cons((yyvsp[(1) - (2)].item), (yyvsp[(2) - (2)].item)); ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 212 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 213 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::condition((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].item)); ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 217 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 218 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::alternative((yyvsp[(1) - (3)].item), (yyvsp[(3) - (3)].item)); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 223 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.item) = KDevPG::evolve((yyvsp[(1) - (7)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (7)].str)),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(6) - (7)].item), (yyvsp[(4) - (7)].str));
        ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 228 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.item) = KDevPG::evolve((yyvsp[(1) - (7)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (7)].str)),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(5) - (7)].item), (yyvsp[(7) - (7)].str));
        ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 233 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::evolve((yyvsp[(1) - (4)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (4)].str)), 0, (yyvsp[(4) - (4)].str)); ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 234 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { if(KDevPG::globalSystem.generateAst == false)
        {
          qFatal("Operator-expression-parsing is not yet supported with --no-ast!");
          exit(-1);
        }
        operatorNode = KDevPG::createNode<KDevPG::Model::OperatorItem>();
      ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 240 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.needOperatorStack = true; (yyval.item) = (yyvsp[(2) - (2)].item); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 244 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = const_cast<char*>(""); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 245 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 251 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { ; ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 256 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (9)].item);
              operatorNode->mName = (yyvsp[(5) - (9)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (9)].str)), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[(7) - (9)].item), (yyvsp[(9) - (9)].str));
            ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 264 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (9)].item);
              operatorNode->mName = (yyvsp[(5) - (9)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (9)].str)), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[(8) - (9)].item), (yyvsp[(6) - (9)].str));
            ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 272 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (6)].item);
              operatorNode->mName = (yyvsp[(5) - (6)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (6)].str)), 0, (yyvsp[(6) - (6)].str));
            ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 282 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushBin(*(yyvsp[(2) - (4)].operatorInformation), (yyvsp[(4) - (4)].str), (yyvsp[(3) - (4)].str)); delete (yyvsp[(2) - (4)].operatorInformation); ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 283 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushTern(*(yyvsp[(2) - (5)].operatorInformation), *(yyvsp[(3) - (5)].operatorInformation), (yyvsp[(5) - (5)].str), (yyvsp[(4) - (5)].str)); delete (yyvsp[(2) - (5)].operatorInformation); delete (yyvsp[(3) - (5)].operatorInformation); ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 284 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPre(*(yyvsp[(2) - (3)].operatorInformation), (yyvsp[(3) - (3)].str)); delete (yyvsp[(2) - (3)].operatorInformation); ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 285 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPost(*(yyvsp[(2) - (3)].operatorInformation), "0", (yyvsp[(3) - (3)].str)); delete (yyvsp[(2) - (3)].operatorInformation); delete (yyvsp[(3) - (3)].str); ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 286 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPost(*(yyvsp[(2) - (4)].operatorInformation), (yyvsp[(4) - (4)].str), (yyvsp[(3) - (4)].str)); delete (yyvsp[(2) - (4)].operatorInformation); ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 287 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushParen(*(yyvsp[(2) - (3)].operatorInformation), *(yyvsp[(3) - (3)].operatorInformation)); delete (yyvsp[(2) - (3)].operatorInformation); delete (yyvsp[(3) - (3)].operatorInformation); ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 291 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"0"; ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 292 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 293 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(2) - (2)].str); ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 297 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"1"; ;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 298 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"0"; ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 299 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { uint yyleng = strlen((yyvsp[(2) - (2)].str));
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, (yyvsp[(2) - (2)].str));
                                     strcpy(tmp+yyleng+6-6+1, "?1:0)");
                                     (yyval.str) = tmp;
                                   ;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 306 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { uint yyleng = strlen((yyvsp[(2) - (2)].str));
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, (yyvsp[(2) - (2)].str));
                                     strcpy(tmp+yyleng+6-6+1, "?0:1)");
                                     (yyval.str) = tmp;
                                   ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 316 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator((yyvsp[(3) - (4)].str), (yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].str)); ;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 317 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator((yyvsp[(3) - (3)].str), (yyvsp[(2) - (3)].str), ""); ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 318 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator((yyvsp[(1) - (2)].str), "", (yyvsp[(2) - (2)].str)); ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 319 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator((yyvsp[(1) - (1)].str), "", ""); ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 323 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 325 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::Model::VariableDeclarationItem *last = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(1) - (2)].item);
          while (last->mNext != 0) {
            last = last->mNext;
          }
          last->mNext = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(2) - (2)].item);
          (yyval.item) = (yyvsp[(1) - (2)].item);
        ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 337 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (6)].declarationType), (yyvsp[(2) - (6)].storageType), (yyvsp[(3) - (6)].variableType), false, (yyvsp[(4) - (6)].str), (yyvsp[(6) - (6)].str)); ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 339 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (5)].declarationType), (yyvsp[(2) - (5)].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, false, (yyvsp[(4) - (5)].str), ""); ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 341 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (7)].declarationType), (yyvsp[(2) - (7)].storageType), (yyvsp[(3) - (7)].variableType), true, (yyvsp[(5) - (7)].str), (yyvsp[(7) - (7)].str)); ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 343 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (6)].declarationType), (yyvsp[(2) - (6)].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, true, (yyvsp[(5) - (6)].str), ""); ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 347 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationLocal;     ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 348 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationArgument;  ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 352 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember;    ;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 353 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;     ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 357 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeNode;             ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 358 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeVariable;         ;}
    break;



/* Line 1464 of yacc.c  */
#line 2348 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"
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
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
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



/* Line 1684 of yacc.c  */
#line 361 "/home/Jonathan/KDESVN/playground/devtools/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"


