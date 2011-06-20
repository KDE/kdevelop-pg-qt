
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.4.1"

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
#line 2 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"

/* This file is part of kdev-pg-qt
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
#include "kdev-pg-regexp.h"
#include "kdev-pg-unicode-loader.h"
#include "kdev-pg-checker.h"

#include <QtCore/QFile>
#include <cassert>

extern int yylex();
extern void yyerror(const char* msg);
extern int yyLine;

QString lexerEnv;

namespace KDevPG
{
    extern QFile file;
    extern QTextStream checkOut;
}

KDevPG::Model::OperatorItem *operatorNode = 0;
QString r;



/* Line 189 of yacc.c  */
#line 121 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"

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
     T_TOKEN_STREAM_DECLARATION_HEADER = 294,
     T_TOKEN_STREAM_BITS_HEADER = 295,
     T_PARSER_BASE = 296,
     T_AST_BASE = 297,
     T_TOKEN_STREAM_BASE = 298,
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
     T_BARRIER = 322
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 49 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"

    KDevPG::Model::Node *item;
    char* str;
    KDevPG::Model::VariableDeclarationItem::DeclarationType declarationType;
    KDevPG::Model::VariableDeclarationItem::StorageType     storageType;
    KDevPG::Model::VariableDeclarationItem::VariableType    variableType;
    KDevPG::Model::Operator                                *operatorInformation;
    KDevPG::GNFA                                           *nfa;



/* Line 214 of yacc.c  */
#line 236 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 248 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"

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
#define YYLAST   388

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  174
/* YYNRULES -- Number of states.  */
#define YYNSTATES  343

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   322

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    84,     2,     2,    72,     2,
      69,    70,    77,    78,    82,     2,    81,     2,    83,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    86,    10,
       2,    85,     2,    75,    76,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    79,     2,    80,    73,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    71,     2,    74,     2,     2,     2,
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
       5,     6,     7,     8,     9,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    10,    12,    15,    18,    24,    27,
      33,    37,    39,    41,    44,    48,    51,    54,    57,    60,
      63,    66,    69,    72,    75,    78,    82,    85,    88,    89,
      96,    97,   103,   104,   111,   112,   119,   120,   131,   132,
     143,   144,   150,   151,   153,   155,   156,   160,   162,   166,
     168,   172,   174,   177,   180,   182,   185,   187,   191,   193,
     196,   199,   201,   205,   209,   211,   213,   215,   217,   218,
     222,   224,   228,   230,   234,   236,   239,   242,   244,   247,
     249,   253,   255,   258,   261,   263,   267,   271,   273,   275,
     277,   279,   281,   282,   288,   294,   300,   305,   310,   312,
     317,   321,   328,   329,   333,   335,   339,   341,   343,   346,
     350,   355,   358,   360,   365,   374,   375,   377,   379,   381,
     383,   386,   389,   391,   394,   396,   400,   403,   405,   407,
     410,   412,   416,   418,   422,   430,   438,   443,   444,   447,
     448,   450,   453,   454,   464,   474,   481,   486,   492,   496,
     500,   505,   509,   511,   513,   516,   518,   520,   523,   526,
     531,   535,   538,   540,   542,   545,   552,   558,   566,   573,
     574,   576,   578,   580,   582
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      88,     0,    -1,    -1,   133,    89,    90,   119,   133,    -1,
      91,    -1,    90,    91,    -1,    14,   117,    -1,    14,    69,
      20,    70,     6,    -1,    15,   117,    -1,    15,    69,    20,
      70,     6,    -1,    11,   118,    10,    -1,    61,    -1,    62,
      -1,    60,     7,    -1,    12,     3,    10,    -1,    30,     7,
      -1,    35,     7,    -1,    13,     6,    -1,    36,     6,    -1,
      37,     7,    -1,    38,     7,    -1,    39,     7,    -1,    40,
       7,    -1,    59,     7,    -1,    41,     7,    -1,    43,     3,
       7,    -1,    42,     7,    -1,    44,     7,    -1,    -1,    58,
       7,    92,     4,    94,    10,    -1,    -1,    58,    93,     4,
      94,    10,    -1,    -1,   101,     4,     3,    10,    95,    94,
      -1,    -1,   101,   133,   100,    10,    96,    94,    -1,    -1,
     101,    67,    69,     7,    70,   133,   100,    10,    97,    94,
      -1,    -1,   101,    68,    69,     7,    70,   133,   100,    10,
      98,    94,    -1,    -1,    66,     6,    10,    99,    94,    -1,
      -1,     5,    -1,    64,    -1,    -1,   101,    71,   102,    -1,
     102,    -1,   102,    72,   103,    -1,   103,    -1,   104,    73,
     103,    -1,   104,    -1,    74,   104,    -1,    75,   104,    -1,
     105,    -1,   105,   106,    -1,   106,    -1,   106,    76,   107,
      -1,   107,    -1,   107,    77,    -1,   107,    78,    -1,   108,
      -1,    69,   101,    70,    -1,    79,   109,    80,    -1,    81,
      -1,     7,    -1,     8,    -1,    63,    -1,    -1,   109,    71,
     110,    -1,   110,    -1,   110,    72,   111,    -1,   111,    -1,
     112,    73,   111,    -1,   112,    -1,    74,   112,    -1,    75,
     112,    -1,   113,    -1,   113,   114,    -1,   114,    -1,   114,
      76,   115,    -1,   115,    -1,   115,    77,    -1,   115,    78,
      -1,   116,    -1,    69,   101,    70,    -1,    79,   109,    80,
      -1,    81,    -1,     7,    -1,    65,    -1,     8,    -1,    63,
      -1,    -1,    69,    16,    19,    70,     6,    -1,    69,    18,
      19,    70,     6,    -1,    69,    17,    19,    70,     6,    -1,
      69,    21,    70,     6,    -1,    69,    22,    70,     6,    -1,
       5,    -1,     5,    69,     7,    70,    -1,   118,    82,     5,
      -1,   118,    82,     5,    69,     7,    70,    -1,    -1,   119,
     131,    10,    -1,    83,    -1,    69,   130,    70,    -1,   122,
      -1,   121,    -1,    57,     3,    -1,   124,   125,   121,    -1,
      84,   124,   125,   121,    -1,     3,   123,    -1,     5,    -1,
      23,    69,   130,    70,    -1,    24,    69,   130,    70,    25,
      69,   130,    70,    -1,    -1,    26,    -1,     3,    -1,    85,
      -1,    86,    -1,   120,    78,    -1,   120,    77,    -1,   120,
      -1,    75,   120,    -1,   126,    -1,   127,    76,   120,    -1,
     127,     6,    -1,     6,    -1,   127,    -1,   128,   127,    -1,
     128,    -1,    75,     6,   128,    -1,   129,    -1,   130,    71,
     129,    -1,   130,     4,     3,     6,    79,   140,    80,    -1,
     130,     4,     3,    79,   140,    80,   133,    -1,   130,     4,
       3,   133,    -1,    -1,   132,   135,    -1,    -1,     6,    -1,
     136,   134,    -1,    -1,    49,   121,   134,    50,     3,    79,
     140,    80,   133,    -1,    49,   121,   134,    50,     3,     6,
      79,   140,    80,    -1,    49,   121,   134,    50,     3,   133,
      -1,    45,   139,   137,   138,    -1,    48,   139,   139,   137,
     138,    -1,    46,   139,   137,    -1,    47,   139,   137,    -1,
      47,   139,   137,   138,    -1,    56,   139,   139,    -1,    83,
      -1,     9,    -1,    55,     6,    -1,    51,    -1,    52,    -1,
      53,     6,    -1,    54,     6,    -1,    75,     6,     5,     6,
      -1,    75,     6,     5,    -1,     5,     6,    -1,     5,    -1,
     141,    -1,   140,   141,    -1,   142,   143,   144,     3,    86,
       3,    -1,   142,   143,    33,     3,    10,    -1,   142,   143,
     144,    84,     3,    86,     3,    -1,   142,   143,    33,    84,
       3,    10,    -1,    -1,    29,    -1,    27,    -1,    28,    -1,
      31,    -1,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    93,    93,    93,   100,   101,   105,   107,   109,   111,
     113,   114,   128,   142,   169,   171,   173,   175,   177,   179,
     181,   183,   185,   187,   189,   191,   193,   195,   197,   197,
     198,   198,   203,   202,   206,   205,   216,   215,   248,   247,
     284,   283,   287,   291,   294,   297,   301,   302,   306,   307,
     311,   312,   316,   317,   318,   322,   323,   327,   328,   332,
     333,   334,   338,   339,   340,   341,   342,   343,   358,   362,
     363,   367,   368,   372,   373,   377,   378,   379,   383,   384,
     388,   389,   393,   394,   395,   399,   400,   401,   402,   403,
     426,   427,   442,   447,   449,   451,   453,   455,   460,   461,
     462,   463,   467,   469,   473,   474,   475,   476,   477,   478,
     479,   483,   484,   488,   493,   500,   501,   505,   515,   516,
     520,   521,   522,   523,   527,   528,   533,   534,   538,   539,
     543,   544,   548,   549,   553,   558,   563,   565,   565,   575,
     576,   581,   582,   586,   594,   602,   613,   614,   615,   616,
     617,   618,   622,   623,   624,   628,   629,   630,   637,   647,
     648,   649,   650,   654,   655,   667,   669,   671,   673,   678,
     679,   683,   684,   688,   689
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_IDENTIFIER", "T_ARROW", "T_TERMINAL",
  "T_CODE", "T_STRING", "T_UNQUOTED_STRING", "T_NUMBER", "';'",
  "T_TOKEN_DECLARATION", "T_TOKEN_STREAM_DECLARATION",
  "T_NAMESPACE_DECLARATION", "T_PARSERCLASS_DECLARATION",
  "T_LEXERCLASS_DECLARATION", "T_PUBLIC", "T_PRIVATE", "T_PROTECTED",
  "T_DECLARATION", "T_BITS", "T_CONSTRUCTOR", "T_DESTRUCTOR",
  "T_TRY_RECOVER", "T_TRY_ROLLBACK", "T_CATCH", "T_RULE_ARGUMENTS",
  "T_MEMBER", "T_TEMPORARY", "T_ARGUMENT", "T_EXPORT_MACRO", "T_NODE",
  "T_NODE_SEQUENCE", "T_TOKEN", "T_VARIABLE", "T_EXPORT_MACRO_HEADER",
  "T_AST_DECLARATION", "T_PARSER_DECLARATION_HEADER",
  "T_PARSER_BITS_HEADER", "T_AST_HEADER",
  "T_TOKEN_STREAM_DECLARATION_HEADER", "T_TOKEN_STREAM_BITS_HEADER",
  "T_PARSER_BASE", "T_AST_BASE", "T_TOKEN_STREAM_BASE", "T_BIN", "T_PRE",
  "T_POST", "T_TERN", "T_LOPR", "T_ROPR", "T_LEFT_ASSOC", "T_RIGHT_ASSOC",
  "T_IS_LEFT_ASSOC", "T_IS_RIGHT_ASSOC", "T_PRIORITY", "T_PAREN",
  "T_INLINE", "T_LEXER", "T_INPUT_STREAM", "T_INPUT_ENCODING",
  "T_TABLE_LEXER", "T_SEQUENCE_LEXER", "T_NAMED_REGEXP", "T_CONTINUE",
  "T_RANGE", "T_FAIL", "T_LOOKAHEAD", "T_BARRIER", "'('", "')'", "'|'",
  "'&'", "'^'", "'~'", "'?'", "'@'", "'*'", "'+'", "'['", "']'", "'.'",
  "','", "'0'", "'#'", "'='", "':'", "$accept", "system", "$@1",
  "declarations", "declaration", "$@2", "$@3", "lexer_declaration_rest",
  "$@4", "$@5", "$@6", "$@7", "$@8", "opt_lexer_action", "regexp",
  "regexp1", "regexp2", "regexp3", "regexp4", "regexp5", "regexp6",
  "regexp7", "aregexp", "aregexp1", "aregexp2", "aregexp3", "aregexp4",
  "aregexp5", "aregexp6", "aregexp7", "member_declaration_rest",
  "declared_tokens", "rules", "primary_item", "primary_atom", "try_item",
  "rule_arguments_opt", "name", "scope", "unary_item", "postfix_item",
  "item_sequence", "conditional_item", "option_item", "item", "$@9",
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
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
      59,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,    40,
      41,   124,    38,    94,   126,    63,    64,    42,    43,    91,
      93,    46,    44,    48,    35,    61,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    89,    88,    90,    90,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    92,    91,
      93,    91,    95,    94,    96,    94,    97,    94,    98,    94,
      99,    94,    94,   100,   100,   100,   101,   101,   102,   102,
     103,   103,   104,   104,   104,   105,   105,   106,   106,   107,
     107,   107,   108,   108,   108,   108,   108,   108,   108,   109,
     109,   110,   110,   111,   111,   112,   112,   112,   113,   113,
     114,   114,   115,   115,   115,   116,   116,   116,   116,   116,
     116,   116,   116,   117,   117,   117,   117,   117,   118,   118,
     118,   118,   119,   119,   120,   120,   120,   120,   120,   120,
     120,   121,   121,   122,   122,   123,   123,   124,   125,   125,
     126,   126,   126,   126,   127,   127,   127,   127,   128,   128,
     129,   129,   130,   130,   131,   131,   131,   132,   131,   133,
     133,   134,   134,   135,   135,   135,   136,   136,   136,   136,
     136,   136,   137,   137,   137,   138,   138,   138,   138,   139,
     139,   139,   139,   140,   140,   141,   141,   141,   141,   142,
     142,   143,   143,   144,   144
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     5,     1,     2,     2,     5,     2,     5,
       3,     1,     1,     2,     3,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     2,     2,     0,     6,
       0,     5,     0,     6,     0,     6,     0,    10,     0,    10,
       0,     5,     0,     1,     1,     0,     3,     1,     3,     1,
       3,     1,     2,     2,     1,     2,     1,     3,     1,     2,
       2,     1,     3,     3,     1,     1,     1,     1,     0,     3,
       1,     3,     1,     3,     1,     2,     2,     1,     2,     1,
       3,     1,     2,     2,     1,     3,     3,     1,     1,     1,
       1,     1,     0,     5,     5,     5,     4,     4,     1,     4,
       3,     6,     0,     3,     1,     3,     1,     1,     2,     3,
       4,     2,     1,     4,     8,     0,     1,     1,     1,     1,
       2,     2,     1,     2,     1,     3,     2,     1,     1,     2,
       1,     3,     1,     3,     7,     7,     4,     0,     2,     0,
       1,     2,     0,     9,     9,     6,     4,     5,     3,     3,
       4,     3,     1,     1,     2,     1,     1,     2,     2,     4,
       3,     2,     1,     1,     2,     6,     5,     7,     6,     0,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     139,   140,     0,     2,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,     0,     0,    11,    12,   102,     4,    98,
       0,     0,    17,     0,     6,     0,     8,    15,    16,    18,
      19,    20,    21,    22,    24,    26,     0,    27,    28,     0,
      23,    13,     5,   137,     0,    10,     0,    14,     0,     0,
       0,     0,     0,     0,     0,    25,     0,    68,   115,   112,
     127,     0,     0,     0,     0,     0,   104,     0,   122,   107,
     106,     0,   124,   128,   130,   132,     0,     0,     0,     3,
       0,   100,     0,     0,     0,     0,     0,     0,     0,    68,
      65,    66,    67,     0,    68,    68,    68,    92,    64,     0,
     139,    47,    49,    51,    54,    56,    58,    61,   116,   111,
       0,     0,   108,   127,     0,     0,   123,   117,     0,   121,
     120,   118,   119,     0,   126,     0,     0,   129,     0,     0,
     103,     0,   138,    99,     0,     0,     0,     0,     7,    96,
      97,     9,     0,     0,     0,    52,    53,    88,    90,    91,
      89,    68,    92,    92,    92,    87,     0,    70,    72,    74,
      77,    79,    81,    84,    31,     0,     0,     0,    68,    45,
      68,    68,    55,    68,    59,    60,     0,     0,   105,   131,
       0,   115,   109,   125,   139,   133,   142,     0,    93,    95,
      94,    29,    40,    62,     0,    75,    76,     0,    92,    63,
      92,    92,    78,    92,    82,    83,     0,     0,     0,    46,
      43,    44,     0,    48,    50,    57,   113,     0,   110,   140,
     169,   136,     0,     0,     0,     0,     0,     0,   142,   101,
      68,    85,    86,    69,    71,    73,    80,    32,     0,     0,
      34,     0,   169,   170,   169,   163,     0,   162,     0,     0,
       0,     0,     0,     0,     0,   141,    41,    68,   139,   139,
      68,     0,   169,   139,   164,   171,   172,     0,   161,     0,
     153,     0,   152,     0,   148,   149,     0,   151,   139,    33,
      45,    45,    35,     0,   134,   135,   173,     0,   174,     0,
     160,   154,   155,   156,     0,     0,   146,   150,     0,   140,
     169,   145,     0,     0,   114,     0,     0,     0,     0,   159,
     157,   158,   147,   169,   169,    36,    38,   166,     0,     0,
       0,   169,   139,    68,    68,   168,   165,     0,   144,   143,
      37,    39,   167
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    27,    28,    66,    49,   109,   267,   270,
     333,   334,   240,   222,   110,   111,   112,   113,   114,   115,
     116,   117,   166,   167,   168,   169,   170,   171,   172,   173,
      34,    30,    53,    78,    79,    80,   119,    81,   133,    82,
      83,    84,    85,    86,    87,    88,     3,   237,   142,   238,
     283,   306,   259,   254,   255,   256,   277,   299
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -256
static const yytype_int16 yypact[] =
{
      16,  -256,    26,  -256,  -256,   246,    50,    31,    38,    32,
      47,   123,   125,   154,   127,   147,   155,   159,   165,   178,
     186,   187,   192,   194,   196,  -256,  -256,   246,  -256,   112,
      30,   211,  -256,   230,  -256,   250,  -256,  -256,  -256,  -256,
    -256,  -256,  -256,  -256,  -256,  -256,   218,  -256,  -256,   224,
    -256,  -256,  -256,     4,   227,  -256,   238,  -256,   234,   236,
     256,   199,   210,   231,   232,  -256,   245,    52,   -10,  -256,
     303,   240,   241,   308,     8,    40,  -256,   309,    -7,  -256,
    -256,    65,  -256,    18,    15,  -256,    33,   304,   264,  -256,
     247,   249,   251,   252,   253,   310,   313,   314,   318,    52,
    -256,  -256,  -256,   319,   148,   148,   148,   121,  -256,   305,
     174,   254,  -256,   255,   128,   257,    60,  -256,  -256,  -256,
       8,     8,  -256,  -256,    88,    15,  -256,  -256,    65,  -256,
    -256,  -256,  -256,    51,  -256,    12,    12,    18,   324,     8,
    -256,    51,  -256,  -256,   322,   325,   326,   328,  -256,  -256,
    -256,  -256,   320,   327,   117,  -256,  -256,  -256,  -256,  -256,
    -256,   148,   121,   121,   121,  -256,   -29,   263,  -256,   265,
      98,   260,    91,  -256,  -256,   336,   271,   272,   148,    14,
     148,   148,   257,   175,  -256,  -256,   122,   142,  -256,    15,
      51,   316,  -256,  -256,     6,  -256,   101,   273,  -256,  -256,
    -256,  -256,  -256,  -256,   169,  -256,  -256,   -13,   121,  -256,
     121,   121,   260,   145,  -256,  -256,   334,   338,   339,   254,
    -256,  -256,   337,  -256,  -256,    60,  -256,   323,  -256,   270,
     321,  -256,    28,    28,    28,    28,    28,   301,   101,  -256,
      52,  -256,  -256,   263,  -256,  -256,    91,  -256,   282,   283,
    -256,   285,   321,  -256,    37,  -256,   191,   349,   350,    -3,
      -3,    -3,    28,    28,   354,  -256,  -256,    52,    16,    16,
      52,     8,    39,    16,  -256,  -256,  -256,   111,  -256,   353,
    -256,   355,  -256,   179,  -256,   179,    -3,  -256,    23,  -256,
      14,    14,  -256,   203,  -256,  -256,  -256,     2,  -256,     5,
     356,  -256,  -256,  -256,   357,   358,  -256,  -256,   179,   280,
     321,  -256,   359,   360,  -256,   361,   362,   274,   363,  -256,
    -256,  -256,  -256,   321,    45,  -256,  -256,  -256,   364,   365,
     281,    84,    16,    52,    52,  -256,  -256,   369,  -256,  -256,
    -256,  -256,  -256
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -256,  -256,  -256,  -256,   346,  -256,  -256,   -97,  -256,  -256,
    -256,  -256,  -256,     3,   -79,   197,    97,   190,  -256,   262,
     195,  -256,   213,   171,    87,   137,  -256,   212,   167,  -256,
     371,  -256,  -256,   -25,   -19,  -256,  -256,   306,   258,  -256,
     -81,   259,   248,   -73,  -256,  -256,   -53,   150,  -256,  -256,
    -121,  -255,    29,  -203,  -231,  -256,  -256,  -256
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -141
static const yytype_int16 yytable[] =
{
      89,   124,   152,   137,  -139,   315,   280,    68,   317,    69,
      70,    68,   229,    69,   123,    68,   118,    69,    68,   220,
      69,   123,     1,   274,   134,   154,     4,    71,    72,   309,
     307,    71,    72,   257,    31,    71,    72,   138,    71,    72,
      55,   274,   208,    68,    32,    69,   125,   186,   187,   272,
     126,   209,   281,   322,   191,    29,    69,   179,   208,   100,
     101,    73,   -42,    71,    72,    73,   253,   242,   253,    73,
     129,   130,    73,    74,   253,  -117,  -117,    74,   221,    75,
     282,    74,   204,    75,    74,   230,   316,    76,    77,   318,
     136,    76,    77,   274,   135,    76,    77,    73,    76,    77,
     274,    33,   310,   258,   139,   157,   158,   324,   137,    74,
     193,   126,    56,   253,   192,   102,    35,   273,   103,   294,
     331,   104,   196,    76,    77,   332,   105,   106,   157,   158,
      37,   107,    38,   108,    40,   100,   101,   184,   185,   284,
     285,   231,   296,   266,   297,   298,   232,   233,   234,   235,
     131,   132,   157,   158,    41,   100,   101,   236,   188,   139,
      39,   159,    42,   160,   338,   308,    43,   161,   214,   215,
     289,   228,    44,   292,   -92,   -92,   -92,   164,   175,   165,
       1,    54,   100,   101,   159,    45,   160,   203,   178,    46,
     161,   102,   226,   139,    47,   162,   163,   104,   293,    48,
     164,    50,   165,    51,   -68,   -68,   -68,   107,   159,   108,
     160,   102,   227,   139,   161,   290,   291,   104,   275,   276,
     295,    57,   105,   106,   164,    65,   165,   107,    67,   108,
     302,   303,   304,   305,    90,   311,   340,   341,   102,   241,
     178,   176,   177,    91,   104,   178,    58,    59,    60,    99,
      61,    62,    63,    92,   107,    93,   108,     6,     7,     8,
       9,    10,   260,   261,   262,   263,    58,    59,    60,    95,
      64,    62,    63,   314,   139,    94,    11,   223,   224,   339,
      96,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,   286,   287,   312,   313,   155,   156,   244,   245,   205,
     206,    97,    98,  -140,    22,    23,    24,    25,    26,   120,
     121,   122,   127,   141,   140,   174,   148,   143,   144,   149,
     150,   145,   146,   147,   151,   153,   180,   194,   181,   197,
     201,   198,   199,   183,   200,   210,   213,   202,   211,   216,
     217,   218,   118,   239,   247,   248,   249,   250,   251,   252,
     253,   264,   268,   269,   271,   278,   279,   288,   300,   323,
     329,   301,   319,   320,   321,   328,   330,   337,   336,   325,
     326,   327,   342,    52,   335,   219,   182,   207,   225,   243,
     246,    36,   212,   128,   189,     0,   190,   195,   265
};

static const yytype_int16 yycheck[] =
{
      53,    74,    99,    84,     0,     3,     9,     3,     3,     5,
       6,     3,     6,     5,     6,     3,    26,     5,     3,     5,
       5,     6,     6,   254,     6,   104,     0,    23,    24,     6,
     285,    23,    24,     5,     3,    23,    24,     4,    23,    24,
      10,   272,    71,     3,     6,     5,     6,   120,   121,   252,
      75,    80,    55,   308,     3,     5,     5,   110,    71,     7,
       8,    57,    10,    23,    24,    57,    29,    80,    29,    57,
      77,    78,    57,    69,    29,    85,    86,    69,    64,    75,
      83,    69,   161,    75,    69,    79,    84,    83,    84,    84,
      75,    83,    84,   324,    76,    83,    84,    57,    83,    84,
     331,    69,    79,    75,    71,     7,     8,   310,   189,    69,
     135,   136,    82,    29,   133,    63,    69,    80,    66,    80,
     323,    69,   141,    83,    84,    80,    74,    75,     7,     8,
       7,    79,     7,    81,     7,     7,     8,    77,    78,   260,
     261,   194,    31,   240,    33,    34,    45,    46,    47,    48,
      85,    86,     7,     8,     7,     7,     8,    56,    70,    71,
       6,    63,     7,    65,    80,   286,     7,    69,    77,    78,
     267,   190,     7,   270,    76,    77,    78,    79,     4,    81,
       6,    69,     7,     8,    63,     7,    65,    70,    71,     3,
      69,    63,    70,    71,     7,    74,    75,    69,   271,     7,
      79,     7,    81,     7,    76,    77,    78,    79,    63,    81,
      65,    63,    70,    71,    69,   268,   269,    69,    27,    28,
     273,    10,    74,    75,    79,     7,    81,    79,     4,    81,
      51,    52,    53,    54,     7,   288,   333,   334,    63,    70,
      71,    67,    68,     5,    69,    71,    16,    17,    18,     4,
      20,    21,    22,    19,    79,    19,    81,    11,    12,    13,
      14,    15,   233,   234,   235,   236,    16,    17,    18,    70,
      20,    21,    22,    70,    71,    19,    30,   180,   181,   332,
      70,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,   262,   263,   290,   291,   105,   106,   210,   211,   162,
     163,    70,    70,     0,    58,    59,    60,    61,    62,    69,
      69,     3,     3,    49,    10,    10,     6,    70,    69,     6,
       6,    70,    70,    70,     6,     6,    72,     3,    73,     7,
      10,     6,     6,    76,     6,    72,    76,    10,    73,     3,
      69,    69,    26,    70,    10,     7,     7,    10,    25,    79,
      29,    50,    70,    70,    69,     6,     6,     3,     5,    79,
      86,     6,     6,     6,     6,     3,     3,    86,     3,    10,
      10,    10,     3,    27,    10,   178,   114,   164,   183,   208,
     213,    10,   170,    77,   125,    -1,   128,   139,   238
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    88,   133,     0,    89,    11,    12,    13,    14,
      15,    30,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    58,    59,    60,    61,    62,    90,    91,     5,
     118,     3,     6,    69,   117,    69,   117,     7,     7,     6,
       7,     7,     7,     7,     7,     7,     3,     7,     7,    93,
       7,     7,    91,   119,    69,    10,    82,    10,    16,    17,
      18,    20,    21,    22,    20,     7,    92,     4,     3,     5,
       6,    23,    24,    57,    69,    75,    83,    84,   120,   121,
     122,   124,   126,   127,   128,   129,   130,   131,   132,   133,
       7,     5,    19,    19,    19,    70,    70,    70,    70,     4,
       7,     8,    63,    66,    69,    74,    75,    79,    81,    94,
     101,   102,   103,   104,   105,   106,   107,   108,    26,   123,
      69,    69,     3,     6,   130,     6,   120,     3,   124,    77,
      78,    85,    86,   125,     6,    76,    75,   127,     4,    71,
      10,    49,   135,    70,    69,    70,    70,    70,     6,     6,
       6,     6,    94,     6,   101,   104,   104,     7,     8,    63,
      65,    69,    74,    75,    79,    81,   109,   110,   111,   112,
     113,   114,   115,   116,    10,     4,    67,    68,    71,   133,
      72,    73,   106,    76,    77,    78,   130,   130,    70,   128,
     125,     3,   121,   120,     3,   129,   121,     7,     6,     6,
       6,    10,    10,    70,   101,   112,   112,   109,    71,    80,
      72,    73,   114,    76,    77,    78,     3,    69,    69,   102,
       5,    64,   100,   103,   103,   107,    70,    70,   121,     6,
      79,   133,    45,    46,    47,    48,    56,   134,   136,    70,
      99,    70,    80,   110,   111,   111,   115,    10,     7,     7,
      10,    25,    79,    29,   140,   141,   142,     5,    75,   139,
     139,   139,   139,   139,    50,   134,    94,    95,    70,    70,
      96,    69,   140,    80,   141,    27,    28,   143,     6,     6,
       9,    55,    83,   137,   137,   137,   139,   139,     3,    94,
     133,   133,    94,   130,    80,   133,    31,    33,    34,   144,
       5,     6,    51,    52,    53,    54,   138,   138,   137,     6,
      79,   133,   100,   100,    70,     3,    84,     3,    84,     6,
       6,     6,   138,    79,   140,    10,    10,    10,     3,    86,
       3,   140,    80,    97,    98,    10,     3,    86,    80,   133,
      94,    94,     3
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

/* Line 1455 of yacc.c  */
#line 93 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.decl = (yyvsp[(1) - (1)].str); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 96 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.bits += (yyvsp[(5) - (5)].str); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 106 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserClassMember((yyvsp[(2) - (2)].item)); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 108 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.bits += (yyvsp[(5) - (5)].str); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 110 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushLexerClassMember((yyvsp[(2) - (2)].item)); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 112 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.lexerBits += (yyvsp[(5) - (5)].str); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 115 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { if(KDevPG::globalSystem.hasLexer)
        { KDevPG::checkOut << "** ERROR you have to specify the lexer-type (%table_lexer) before any lexer rules"; exit(-1); }
        switch(KDevPG::GDFA::type)
        {
          case KDevPG::SAscii: KDevPG::GDFA::type = KDevPG::TAscii; break;
          case KDevPG::SLatin1: KDevPG::GDFA::type = KDevPG::TLatin1; break;
          case KDevPG::SUtf8: KDevPG::GDFA::type = KDevPG::TUtf8; break;
          case KDevPG::SUcs2: KDevPG::GDFA::type = KDevPG::TUcs2; break;
          case KDevPG::SUtf16: KDevPG::GDFA::type = KDevPG::TUtf16; break;
/*           case KDevPG::SUcs4: KDevPG::GDFA::type = KDevPG::TUcs4; break; */
          default: /* empty */;
        }
      ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 129 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { if(KDevPG::globalSystem.hasLexer)
      { KDevPG::checkOut << "** ERROR you have to specify the lexer-type (%sequence_lexer) before any lexer rules"; exit(-1); }
      switch(KDevPG::GDFA::type)
      {
        case KDevPG::TAscii: KDevPG::GDFA::type = KDevPG::SAscii; break;
        case KDevPG::TLatin1: KDevPG::GDFA::type = KDevPG::SLatin1; break;
        case KDevPG::TUtf8: KDevPG::GDFA::type = KDevPG::SUtf8; break;
        case KDevPG::TUcs2: KDevPG::GDFA::type = KDevPG::SUcs2; break;
        case KDevPG::TUtf16: KDevPG::GDFA::type = KDevPG::SUtf16; break;
/*         case KDevPG::TUcs4: KDevPG::GDFA::type = KDevPG::SUcs4; break; */
        default: /* empty */;
      }
      ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 143 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
        if(KDevPG::globalSystem.hasLexer)
        { KDevPG::checkOut << "** ERROR you have to specify the lexer-type (%sequence_lexer) before any lexer rules"; exit(-1); }
        int base = (KDevPG::GDFA::type / 4) * 4; // warning: magic constant: number of different codecs
        QString str = (yyvsp[(2) - (2)].str);
        str = str.toLower();
        str.replace('-', "");
        if(str == "ascii")
          /* base += 0*/;
        else if(str == "latin1")
          base += 1;
        else if(str == "utf8")
          base += 2;
        else if(str == "ucs2")
          base += 3;
        else if(str == "utf16")
          base += 4;
        else if(str == "ucs4" || str == "utf32")
          base += 5;
        else
        {
          KDevPG::checkOut << "** ERROR unknown codec  ``" << (yyvsp[(2) - (2)].str) << "''" << endl;
          exit(-1);
        }
        KDevPG::GDFA::type = KDevPG::AutomatonType(base);
      ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 170 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.tokenStream = (yyvsp[(2) - (3)].str);           ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 172 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.exportMacro = (yyvsp[(2) - (2)].str);           ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 174 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.exportMacroHeader = (yyvsp[(2) - (2)].str);     ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 176 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.namespaceCode = (yyvsp[(2) - (2)].str);         ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 178 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.astCode = (yyvsp[(2) - (2)].str);               ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 180 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserDeclarationHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 182 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserBitsHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 184 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushAstHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 186 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTokenStreamDeclarationHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 188 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.inputStream = (yyvsp[(2) - (2)].str); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 190 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTokenStreamBitsHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 192 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.astBaseClasses[(yyvsp[(2) - (3)].str)] = (yyvsp[(3) - (3)].str); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 194 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.parserBaseClass = (yyvsp[(2) - (2)].str); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 196 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.tokenStreamBaseClass = (yyvsp[(2) - (2)].str); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 197 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.hasLexer = true; lexerEnv = (yyvsp[(2) - (2)].str); if(KDevPG::globalSystem.lexerActions[lexerEnv].empty()) KDevPG::globalSystem.lexerActions[lexerEnv].push_back("qDebug() << \"error\"; exit(-1);"); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 198 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.hasLexer = true; KDevPG::loadUnicodeData(); lexerEnv = "start"; if(KDevPG::globalSystem.lexerActions["start"].empty()) KDevPG::globalSystem.lexerActions["start"].push_back("qDebug() << \"error\"; exit(-1);"); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 203 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.regexpById[(yyvsp[(3) - (4)].str)] = (yyvsp[(1) - (4)].nfa);
            ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 206 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              if((yyvsp[(1) - (4)].nfa)->acceptsEpsilon())
                KDevPG::checkOut << "** WARNING Lexer rule accepting the empty word at line " << yyLine << endl;
              else if((yyvsp[(1) - (4)].nfa)->isEmpty())
                KDevPG::checkOut << "** WARNING Lexer rule not accepting anything at line " << yyLine << endl;
              QString s = QString((yyvsp[(2) - (4)].str)) + QString(r);
              KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[(1) - (4)].nfa));
              KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
            ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 216 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              if((yyvsp[(1) - (8)].nfa)->acceptsEpsilon())
                KDevPG::checkOut << "** WARNING Lexer rule accepting the empty word at line " << yyLine << endl;
              else if((yyvsp[(1) - (8)].nfa)->isEmpty())
                KDevPG::checkOut << "** WARNING Lexer rule not accepting anything at line " << yyLine << endl;
              bool ignore = false;
              if(strlen((yyvsp[(4) - (8)].str)) == 0)
              {
                KDevPG::checkOut << "** WARNING Lexer rule specifying epsilon-barrier at line " << yyLine << endl;
                ignore = true;
              }
              KDevPG::GNFA delim = KDevPG::GNFA::keyword(KDevPG::unescaped(QByteArray((yyvsp[(4) - (8)].str))));
              if(delim.isEmpty())
              {
                KDevPG::checkOut << "** WARNING Invalid barrier for the specified encoding at line " << yyLine << endl;
                ignore = true;
              }
              if(ignore)
              {
                QString s = QString((yyvsp[(6) - (8)].str)) + QString(r);
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[(1) - (8)].nfa));
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
              else
              {
                QString s = "Iterator::plain() -= " + QString::number(delim.minLength()) + "; " + QString((yyvsp[(6) - (8)].str)) + QString(r);
                *(yyvsp[(1) - (8)].nfa) <<= delim;
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[(1) - (8)].nfa));
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
            ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 248 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              if((yyvsp[(1) - (8)].nfa)->acceptsEpsilon())
                KDevPG::checkOut << "** WARNING Lexer rule accepting the empty word at line " << yyLine << endl;
              else if((yyvsp[(1) - (8)].nfa)->isEmpty())
                KDevPG::checkOut << "** WARNING Lexer rule not accepting anything at line " << yyLine << endl;
              bool ignore = false;
              if(strlen((yyvsp[(4) - (8)].str)) == 0)
              {
                KDevPG::checkOut << "** WARNING Lexer rule specifying epsilon-barrier at line " << yyLine << endl;
                ignore = true;
              }
              KDevPG::GNFA delim = KDevPG::GNFA::keyword(KDevPG::unescaped(QByteArray((yyvsp[(4) - (8)].str))));
              if(delim.isEmpty())
              {
                KDevPG::checkOut << "** WARNING Invalid barrier for the specified encoding at line " << yyLine << endl;
                ignore = true;
              }
              if(ignore)
              {
                QString s = QString((yyvsp[(6) - (8)].str)) + QString(r);
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[(1) - (8)].nfa));
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
              else
              {
                KDevPG::GNFA exclude = KDevPG::GNFA::anything();
                exclude <<= delim;
                exclude <<= KDevPG::GNFA::anyChar();
                *(yyvsp[(1) - (8)].nfa) <<= delim;
                *(yyvsp[(1) - (8)].nfa) ^= exclude;
                QString s = "Iterator::plain() -= " + QString::number(delim.minLength()) + "; " + QString((yyvsp[(6) - (8)].str)) + QString(r);
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[(1) - (8)].nfa));
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
            ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 284 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              KDevPG::globalSystem.lexerActions[lexerEnv][0] = QString((yyvsp[(2) - (3)].str));
            ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 291 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
        r = "\nlxRETURN(" + QString((yyvsp[(1) - (1)].str)) + ");\n"
      ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 294 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
        r = "\nlxCONTINUE;\n"; 
      ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 297 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { r = "\nlxSKIP\n" ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 301 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) |= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 302 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 306 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) &= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 307 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 311 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) ^= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 312 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 316 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA((yyvsp[(2) - (2)].nfa)->negate()); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 317 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(2) - (2)].nfa) |= KDevPG::GNFA()); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 318 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 322 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (2)].nfa) <<= *(yyvsp[(2) - (2)].nfa)); delete (yyvsp[(1) - (2)].nfa); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 323 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 327 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa)); KDevPG::GNFA *tmp = new KDevPG::GNFA(*(yyvsp[(3) - (3)].nfa) <<= *(yyvsp[(1) - (3)].nfa)); **tmp; *(yyval.nfa) <<= *tmp; delete tmp; delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 328 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 332 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(**(yyvsp[(1) - (2)].nfa)); delete (yyvsp[(1) - (2)].nfa); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 333 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (2)].nfa)); **(yyval.nfa); *(yyval.nfa) <<= *(yyvsp[(1) - (2)].nfa); delete (yyvsp[(1) - (2)].nfa); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 334 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 338 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(2) - (3)].nfa)); delete (yyvsp[(2) - (3)].nfa); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 339 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(2) - (3)].nfa); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 340 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::anyChar()); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 341 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::keyword(KDevPG::unescaped(QByteArray((yyvsp[(1) - (1)].str))))); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 342 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::keyword(KDevPG::unescaped(QByteArray((yyvsp[(1) - (1)].str))))); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 343 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
                              if(!KDevPG::globalSystem.regexpById.contains((yyvsp[(1) - (1)].str)))
                              {
                                KDevPG::checkOut << "** ERROR: no named regexp " << (yyvsp[(1) - (1)].str) << endl;
                                exit(-1);
                              }
                              KDevPG::GNFA *regexp = KDevPG::globalSystem.regexpById[(yyvsp[(1) - (1)].str)];
                              if(!KDevPG::globalSystem.dfaForNfa.contains(regexp))
                              {
                                KDevPG::globalSystem.dfaForNfa[regexp] = new KDevPG::GDFA(regexp->dfa());
                                KDevPG::globalSystem.dfaForNfa[regexp]->minimize();
                                *regexp = KDevPG::globalSystem.dfaForNfa[regexp]->nfa();
                              }
                              (yyval.nfa) = new KDevPG::GNFA(*regexp);
                            ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 358 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::emptyWord()); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 362 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) |= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 363 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 367 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) &= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 368 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 372 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) ^= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 373 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 377 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA((yyvsp[(2) - (2)].nfa)->negate()); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 378 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(2) - (2)].nfa) |= KDevPG::GNFA()); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 379 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 383 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (2)].nfa) |= *(yyvsp[(2) - (2)].nfa)); delete (yyvsp[(1) - (2)].nfa); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 388 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa)); KDevPG::GNFA *tmp = new KDevPG::GNFA(*(yyvsp[(3) - (3)].nfa) <<= *(yyvsp[(1) - (3)].nfa)); **tmp; *(yyval.nfa) <<= *tmp; delete tmp; delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 389 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 393 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(**(yyvsp[(1) - (2)].nfa)); delete (yyvsp[(1) - (2)].nfa); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 394 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (2)].nfa)); **(yyval.nfa); *(yyval.nfa) <<= *(yyvsp[(1) - (2)].nfa); delete (yyvsp[(1) - (2)].nfa); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 395 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 399 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(2) - (3)].nfa)); delete (yyvsp[(2) - (3)].nfa); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 400 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(2) - (3)].nfa); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 401 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::anyChar()); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 402 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::keyword(KDevPG::unescaped(QByteArray((yyvsp[(1) - (1)].str))))); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 403 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
      quint32 begin, end;
      QString str = KDevPG::unescaped(QByteArray((yyvsp[(1) - (1)].str)));
      assert(str.size() >= 3 && str.size() <= 5);
      if(str[1] == '-')
      {
        begin = str[0].unicode();
        if(str.size() == 3)
          end = str[2].unicode();
        else
          end = QChar::surrogateToUcs4(str[2], str[3]);
      }
      else
      {
        begin = QChar::surrogateToUcs4(str[0], str[1]);
        assert(str[2] == '-');
        if(str.size() == 4)
          end = str[3].unicode();
        else
          end = QChar::surrogateToUcs4(str[3], str[4]);
      }
      (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::range(begin, end+1));
    ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 426 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::collection(KDevPG::unescaped(QByteArray((yyvsp[(1) - (1)].str))))); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 427 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
                              if(!KDevPG::globalSystem.regexpById.contains((yyvsp[(1) - (1)].str)))
                              {
                                KDevPG::checkOut << "** ERROR: no named regexp " << (yyvsp[(1) - (1)].str) << endl;
                                exit(-1);
                              }
                              KDevPG::GNFA *regexp = KDevPG::globalSystem.regexpById[(yyvsp[(1) - (1)].str)];
                              if(!KDevPG::globalSystem.dfaForNfa.contains(regexp))
                              {
                                KDevPG::globalSystem.dfaForNfa[regexp] = new KDevPG::GDFA(regexp->dfa());
                                KDevPG::globalSystem.dfaForNfa[regexp]->minimize();
                                *regexp = KDevPG::globalSystem.dfaForNfa[regexp]->nfa();
                              }
                              (yyval.nfa) = new KDevPG::GNFA(*regexp);
                            ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 442 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::emptyWord()); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 448 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PublicDeclaration, (yyvsp[(5) - (5)].str));    ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 450 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ProtectedDeclaration, (yyvsp[(5) - (5)].str)); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 452 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PrivateDeclaration, (yyvsp[(5) - (5)].str));   ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 454 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ConstructorCode, (yyvsp[(4) - (4)].str));      ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 456 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::DestructorCode, (yyvsp[(4) - (4)].str));       ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 460 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(1) - (1)].str),(yyvsp[(1) - (1)].str)); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 461 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(1) - (4)].str),(yyvsp[(3) - (4)].str)); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 462 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(3) - (3)].str),(yyvsp[(3) - (3)].str)); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 464 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(3) - (6)].str),(yyvsp[(5) - (6)].str)); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 469 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushRule((yyvsp[(2) - (3)].item)); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 473 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::globalSystem.zero(); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 474 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(2) - (3)].item); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 475 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 476 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 477 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::inlinedNonTerminal(KDevPG::globalSystem.pushSymbol((yyvsp[(2) - (2)].str))); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 478 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::annotation((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].item), false, (yyvsp[(2) - (3)].storageType)); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 479 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::annotation((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].item), true, (yyvsp[(3) - (4)].storageType));  ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 483 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::nonTerminal(KDevPG::globalSystem.pushSymbol((yyvsp[(1) - (2)].str)), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 484 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::globalSystem.terminal((yyvsp[(1) - (1)].str)); ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 489 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[(3) - (4)].item), 0);
        ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 494 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[(3) - (8)].item), (yyvsp[(7) - (8)].item));
        ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 500 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = const_cast<char*>(""); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 501 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 505 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 515 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember; ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 516 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;  ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 520 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::plus((yyvsp[(1) - (2)].item)); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 521 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::star((yyvsp[(1) - (2)].item)); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 522 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 523 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::alternative((yyvsp[(2) - (2)].item), KDevPG::globalSystem.zero()); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 527 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 529 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::CloneTree cl;
          (yyval.item) = KDevPG::cons((yyvsp[(1) - (3)].item), KDevPG::star(KDevPG::cons(cl.clone((yyvsp[(3) - (3)].item)), cl.clone((yyvsp[(1) - (3)].item)))));
        ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 533 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::action((yyvsp[(1) - (2)].item), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 534 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::action(0, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 538 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 539 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::cons((yyvsp[(1) - (2)].item), (yyvsp[(2) - (2)].item)); ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 543 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 544 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::condition((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].item)); ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 548 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 549 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::alternative((yyvsp[(1) - (3)].item), (yyvsp[(3) - (3)].item)); ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 554 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.item) = KDevPG::evolve((yyvsp[(1) - (7)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (7)].str)),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(6) - (7)].item), (yyvsp[(4) - (7)].str));
        ;}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 559 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.item) = KDevPG::evolve((yyvsp[(1) - (7)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (7)].str)),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(5) - (7)].item), (yyvsp[(7) - (7)].str));
        ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 564 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::evolve((yyvsp[(1) - (4)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (4)].str)), 0, (yyvsp[(4) - (4)].str)); ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 565 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { if(KDevPG::globalSystem.generateAst == false)
        {
          qFatal("Operator-expression-parsing is not yet supported with --no-ast!");
          exit(-1);
        }
        operatorNode = KDevPG::createNode<KDevPG::Model::OperatorItem>();
      ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 571 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.needOperatorStack = true; (yyval.item) = (yyvsp[(2) - (2)].item); ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 575 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = const_cast<char*>(""); ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 576 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 582 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { ; ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 587 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (9)].item);
              operatorNode->mName = (yyvsp[(5) - (9)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (9)].str)), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[(7) - (9)].item), (yyvsp[(9) - (9)].str));
            ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 595 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (9)].item);
              operatorNode->mName = (yyvsp[(5) - (9)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (9)].str)), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[(8) - (9)].item), (yyvsp[(6) - (9)].str));
            ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 603 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (6)].item);
              operatorNode->mName = (yyvsp[(5) - (6)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (6)].str)), 0, (yyvsp[(6) - (6)].str));
            ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 613 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushBin(*(yyvsp[(2) - (4)].operatorInformation), (yyvsp[(4) - (4)].str), (yyvsp[(3) - (4)].str)); free((yyvsp[(2) - (4)].operatorInformation)); ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 614 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushTern(*(yyvsp[(2) - (5)].operatorInformation), *(yyvsp[(3) - (5)].operatorInformation), (yyvsp[(5) - (5)].str), (yyvsp[(4) - (5)].str)); free((yyvsp[(2) - (5)].operatorInformation)); free((yyvsp[(3) - (5)].operatorInformation)); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 615 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPre(*(yyvsp[(2) - (3)].operatorInformation), (yyvsp[(3) - (3)].str)); free((yyvsp[(2) - (3)].operatorInformation)); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 616 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPost(*(yyvsp[(2) - (3)].operatorInformation), "0", (yyvsp[(3) - (3)].str)); free((yyvsp[(2) - (3)].operatorInformation)); free((yyvsp[(3) - (3)].str)); ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 617 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPost(*(yyvsp[(2) - (4)].operatorInformation), (yyvsp[(4) - (4)].str), (yyvsp[(3) - (4)].str)); free((yyvsp[(2) - (4)].operatorInformation)); ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 618 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushParen(*(yyvsp[(2) - (3)].operatorInformation), *(yyvsp[(3) - (3)].operatorInformation)); free((yyvsp[(2) - (3)].operatorInformation)); free((yyvsp[(3) - (3)].operatorInformation)); ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 622 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"0"; ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 623 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 624 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(2) - (2)].str); ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 628 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"1"; ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 629 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"0"; ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 630 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { uint yyleng = strlen((yyvsp[(2) - (2)].str));
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, (yyvsp[(2) - (2)].str));
                                     strcpy(tmp+yyleng+6-6+1, "?1:0)");
                                     (yyval.str) = tmp;
                                   ;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 637 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { uint yyleng = strlen((yyvsp[(2) - (2)].str));
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, (yyvsp[(2) - (2)].str));
                                     strcpy(tmp+yyleng+6-6+1, "?0:1)");
                                     (yyval.str) = tmp;
                                   ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 647 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(3) - (4)].str)), (yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].str)); ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 648 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(3) - (3)].str)), (yyvsp[(2) - (3)].str), ""); ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 649 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(1) - (2)].str)), "", (yyvsp[(2) - (2)].str)); ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 650 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(1) - (1)].str)), "", ""); ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 654 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 656 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::Model::VariableDeclarationItem *last = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(1) - (2)].item);
          while (last->mNext != 0) {
            last = last->mNext;
          }
          last->mNext = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(2) - (2)].item);
          (yyval.item) = (yyvsp[(1) - (2)].item);
        ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 668 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (6)].declarationType), (yyvsp[(2) - (6)].storageType), (yyvsp[(3) - (6)].variableType), false, (yyvsp[(4) - (6)].str), (yyvsp[(6) - (6)].str)); ;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 670 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (5)].declarationType), (yyvsp[(2) - (5)].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, false, (yyvsp[(4) - (5)].str), ""); ;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 672 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (7)].declarationType), (yyvsp[(2) - (7)].storageType), (yyvsp[(3) - (7)].variableType), true, (yyvsp[(5) - (7)].str), (yyvsp[(7) - (7)].str)); ;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 674 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (6)].declarationType), (yyvsp[(2) - (6)].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, true, (yyvsp[(5) - (6)].str), ""); ;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 678 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationLocal;     ;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 679 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationArgument;  ;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 683 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember;    ;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 684 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;     ;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 688 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeNode;             ;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 689 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeVariable;         ;}
    break;



/* Line 1455 of yacc.c  */
#line 3133 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"
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



/* Line 1675 of yacc.c  */
#line 692 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"


