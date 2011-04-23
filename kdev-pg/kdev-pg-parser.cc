
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
     T_RANGE = 319
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
#line 233 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 245 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"

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
#define YYLAST   373

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  168
/* YYNRULES -- Number of states.  */
#define YYNSTATES  320

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    81,     2,     2,    69,     2,
      66,    67,    74,    75,    79,     2,    78,     2,    80,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    83,    10,
       2,    82,     2,    72,    73,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    76,     2,    77,    70,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    68,     2,    71,     2,     2,     2,
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
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    10,    12,    15,    18,    24,    27,
      33,    37,    39,    41,    44,    48,    51,    54,    57,    60,
      63,    66,    69,    72,    75,    78,    82,    85,    88,    89,
      96,    97,   103,   104,   112,   113,   120,   121,   123,   125,
     126,   130,   132,   136,   138,   142,   144,   147,   150,   152,
     155,   157,   161,   163,   166,   169,   171,   175,   179,   181,
     183,   185,   187,   188,   192,   194,   198,   200,   204,   206,
     209,   212,   214,   217,   219,   223,   225,   228,   231,   233,
     237,   241,   243,   245,   247,   249,   251,   252,   258,   264,
     270,   275,   280,   282,   287,   291,   298,   299,   303,   305,
     309,   311,   313,   316,   320,   325,   328,   330,   335,   344,
     345,   347,   349,   351,   353,   356,   359,   361,   364,   366,
     370,   373,   375,   377,   380,   382,   386,   388,   392,   400,
     408,   413,   414,   417,   418,   420,   423,   424,   434,   444,
     451,   456,   462,   466,   470,   475,   479,   481,   483,   486,
     488,   490,   493,   496,   501,   505,   508,   510,   512,   515,
     522,   528,   536,   543,   544,   546,   548,   550,   552
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      85,     0,    -1,    -1,   127,    86,    87,   113,   127,    -1,
      88,    -1,    87,    88,    -1,    14,   111,    -1,    14,    66,
      20,    67,     6,    -1,    15,   111,    -1,    15,    66,    20,
      67,     6,    -1,    11,   112,    10,    -1,    61,    -1,    62,
      -1,    60,     7,    -1,    12,     3,    10,    -1,    30,     7,
      -1,    35,     7,    -1,    13,     6,    -1,    36,     6,    -1,
      37,     7,    -1,    38,     7,    -1,    39,     7,    -1,    40,
       7,    -1,    59,     7,    -1,    41,     7,    -1,    43,     3,
       7,    -1,    42,     7,    -1,    44,     7,    -1,    -1,    58,
       7,    89,     4,    91,    10,    -1,    -1,    58,    90,     4,
      91,    10,    -1,    -1,    95,   127,     4,     3,    10,    92,
      91,    -1,    -1,    95,   127,    94,    10,    93,    91,    -1,
      -1,     5,    -1,    64,    -1,    -1,    95,    68,    96,    -1,
      96,    -1,    96,    69,    97,    -1,    97,    -1,    98,    70,
      97,    -1,    98,    -1,    71,    98,    -1,    72,    98,    -1,
      99,    -1,    99,   100,    -1,   100,    -1,   100,    73,   101,
      -1,   101,    -1,   101,    74,    -1,   101,    75,    -1,   102,
      -1,    66,    95,    67,    -1,    76,   103,    77,    -1,    78,
      -1,     7,    -1,     8,    -1,    63,    -1,    -1,   103,    68,
     104,    -1,   104,    -1,   104,    69,   105,    -1,   105,    -1,
     106,    70,   105,    -1,   106,    -1,    71,   106,    -1,    72,
     106,    -1,   107,    -1,   107,   108,    -1,   108,    -1,   108,
      73,   109,    -1,   109,    -1,   109,    74,    -1,   109,    75,
      -1,   110,    -1,    66,    95,    67,    -1,    76,   103,    77,
      -1,    78,    -1,     7,    -1,    65,    -1,     8,    -1,    63,
      -1,    -1,    66,    16,    19,    67,     6,    -1,    66,    18,
      19,    67,     6,    -1,    66,    17,    19,    67,     6,    -1,
      66,    21,    67,     6,    -1,    66,    22,    67,     6,    -1,
       5,    -1,     5,    66,     7,    67,    -1,   112,    79,     5,
      -1,   112,    79,     5,    66,     7,    67,    -1,    -1,   113,
     125,    10,    -1,    80,    -1,    66,   124,    67,    -1,   116,
      -1,   115,    -1,    57,     3,    -1,   118,   119,   115,    -1,
      81,   118,   119,   115,    -1,     3,   117,    -1,     5,    -1,
      23,    66,   124,    67,    -1,    24,    66,   124,    67,    25,
      66,   124,    67,    -1,    -1,    26,    -1,     3,    -1,    82,
      -1,    83,    -1,   114,    75,    -1,   114,    74,    -1,   114,
      -1,    72,   114,    -1,   120,    -1,   121,    73,   114,    -1,
     121,     6,    -1,     6,    -1,   121,    -1,   122,   121,    -1,
     122,    -1,    72,     6,   122,    -1,   123,    -1,   124,    68,
     123,    -1,   124,     4,     3,     6,    76,   134,    77,    -1,
     124,     4,     3,    76,   134,    77,   127,    -1,   124,     4,
       3,   127,    -1,    -1,   126,   129,    -1,    -1,     6,    -1,
     130,   128,    -1,    -1,    49,   115,   128,    50,     3,    76,
     134,    77,   127,    -1,    49,   115,   128,    50,     3,     6,
      76,   134,    77,    -1,    49,   115,   128,    50,     3,   127,
      -1,    45,   133,   131,   132,    -1,    48,   133,   133,   131,
     132,    -1,    46,   133,   131,    -1,    47,   133,   131,    -1,
      47,   133,   131,   132,    -1,    56,   133,   133,    -1,    80,
      -1,     9,    -1,    55,     6,    -1,    51,    -1,    52,    -1,
      53,     6,    -1,    54,     6,    -1,    72,     6,     5,     6,
      -1,    72,     6,     5,    -1,     5,     6,    -1,     5,    -1,
     135,    -1,   134,   135,    -1,   136,   137,   138,     3,    83,
       3,    -1,   136,   137,    33,     3,    10,    -1,   136,   137,
     138,    81,     3,    83,     3,    -1,   136,   137,    33,    81,
       3,    10,    -1,    -1,    29,    -1,    27,    -1,    28,    -1,
      31,    -1,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    93,    93,    93,   100,   101,   105,   107,   109,   111,
     113,   114,   128,   142,   169,   171,   173,   175,   177,   179,
     181,   183,   185,   187,   189,   191,   193,   195,   197,   197,
     198,   198,   203,   202,   206,   205,   216,   220,   223,   226,
     230,   231,   235,   236,   240,   241,   245,   246,   247,   251,
     252,   256,   257,   261,   262,   263,   267,   268,   269,   270,
     271,   272,   286,   290,   291,   295,   296,   300,   301,   305,
     306,   307,   311,   312,   316,   317,   321,   322,   323,   327,
     328,   329,   330,   331,   354,   355,   369,   374,   376,   378,
     380,   382,   387,   388,   389,   390,   394,   396,   400,   401,
     402,   403,   404,   405,   406,   410,   411,   415,   420,   427,
     428,   432,   442,   443,   447,   448,   449,   450,   454,   455,
     460,   461,   465,   466,   470,   471,   475,   476,   480,   485,
     490,   492,   492,   502,   503,   508,   509,   513,   521,   529,
     540,   541,   542,   543,   544,   545,   549,   550,   551,   555,
     556,   557,   564,   574,   575,   576,   577,   581,   582,   594,
     596,   598,   600,   605,   606,   610,   611,   615,   616
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
  "T_RANGE", "'('", "')'", "'|'", "'&'", "'^'", "'~'", "'?'", "'@'", "'*'",
  "'+'", "'['", "']'", "'.'", "','", "'0'", "'#'", "'='", "':'", "$accept",
  "system", "$@1", "declarations", "declaration", "$@2", "$@3",
  "lexer_declaration_rest", "$@4", "$@5", "opt_lexer_action", "regexp",
  "regexp1", "regexp2", "regexp3", "regexp4", "regexp5", "regexp6",
  "regexp7", "aregexp", "aregexp1", "aregexp2", "aregexp3", "aregexp4",
  "aregexp5", "aregexp6", "aregexp7", "member_declaration_rest",
  "declared_tokens", "rules", "primary_item", "primary_atom", "try_item",
  "rule_arguments_opt", "name", "scope", "unary_item", "postfix_item",
  "item_sequence", "conditional_item", "option_item", "item", "$@6",
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
     314,   315,   316,   317,   318,   319,    40,    41,   124,    38,
      94,   126,    63,    64,    42,    43,    91,    93,    46,    44,
      48,    35,    61,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    86,    85,    87,    87,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    89,    88,
      90,    88,    92,    91,    93,    91,    91,    94,    94,    94,
      95,    95,    96,    96,    97,    97,    98,    98,    98,    99,
      99,   100,   100,   101,   101,   101,   102,   102,   102,   102,
     102,   102,   102,   103,   103,   104,   104,   105,   105,   106,
     106,   106,   107,   107,   108,   108,   109,   109,   109,   110,
     110,   110,   110,   110,   110,   110,   110,   111,   111,   111,
     111,   111,   112,   112,   112,   112,   113,   113,   114,   114,
     114,   114,   114,   114,   114,   115,   115,   116,   116,   117,
     117,   118,   119,   119,   120,   120,   120,   120,   121,   121,
     121,   121,   122,   122,   123,   123,   124,   124,   125,   125,
     125,   126,   125,   127,   127,   128,   128,   129,   129,   129,
     130,   130,   130,   130,   130,   130,   131,   131,   131,   132,
     132,   132,   132,   133,   133,   133,   133,   134,   134,   135,
     135,   135,   135,   136,   136,   137,   137,   138,   138
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     5,     1,     2,     2,     5,     2,     5,
       3,     1,     1,     2,     3,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     2,     2,     0,     6,
       0,     5,     0,     7,     0,     6,     0,     1,     1,     0,
       3,     1,     3,     1,     3,     1,     2,     2,     1,     2,
       1,     3,     1,     2,     2,     1,     3,     3,     1,     1,
       1,     1,     0,     3,     1,     3,     1,     3,     1,     2,
       2,     1,     2,     1,     3,     1,     2,     2,     1,     3,
       3,     1,     1,     1,     1,     1,     0,     5,     5,     5,
       4,     4,     1,     4,     3,     6,     0,     3,     1,     3,
       1,     1,     2,     3,     4,     2,     1,     4,     8,     0,
       1,     1,     1,     1,     2,     2,     1,     2,     1,     3,
       2,     1,     1,     2,     1,     3,     1,     3,     7,     7,
       4,     0,     2,     0,     1,     2,     0,     9,     9,     6,
       4,     5,     3,     3,     4,     3,     1,     1,     2,     1,
       1,     2,     2,     4,     3,     2,     1,     1,     2,     6,
       5,     7,     6,     0,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     133,   134,     0,     2,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,     0,     0,    11,    12,    96,     4,    92,
       0,     0,    17,     0,     6,     0,     8,    15,    16,    18,
      19,    20,    21,    22,    24,    26,     0,    27,    28,     0,
      23,    13,     5,   131,     0,    10,     0,    14,     0,     0,
       0,     0,     0,     0,     0,    25,     0,    62,   109,   106,
     121,     0,     0,     0,     0,     0,    98,     0,   116,   101,
     100,     0,   118,   122,   124,   126,     0,     0,     0,     3,
       0,    94,     0,     0,     0,     0,     0,     0,     0,    62,
      59,    60,    61,    62,    62,    62,    86,    58,     0,   133,
      41,    43,    45,    48,    50,    52,    55,   110,   105,     0,
       0,   102,   121,     0,     0,   117,   111,     0,   115,   114,
     112,   113,     0,   120,     0,     0,   123,     0,     0,    97,
       0,   132,    93,     0,     0,     0,     0,     7,    90,    91,
       9,     0,     0,    46,    47,    82,    84,    85,    83,    62,
      86,    86,    86,    81,     0,    64,    66,    68,    71,    73,
      75,    78,    31,    62,    39,    62,    62,    49,    62,    53,
      54,     0,     0,    99,   125,     0,   109,   103,   119,   133,
     127,   136,     0,    87,    89,    88,    29,    56,     0,    69,
      70,     0,    86,    57,    86,    86,    72,    86,    76,    77,
      40,     0,    37,    38,     0,    42,    44,    51,   107,     0,
     104,   134,   163,   130,     0,     0,     0,     0,     0,     0,
     136,    95,    79,    80,    63,    65,    67,    74,     0,    34,
       0,   163,   164,   163,   157,     0,   156,     0,     0,     0,
       0,     0,     0,     0,   135,    32,    62,     0,   163,   133,
     158,   165,   166,     0,   155,     0,   147,     0,   146,     0,
     142,   143,     0,   145,   133,    62,    35,     0,   128,   129,
     167,     0,   168,     0,   154,   148,   149,   150,     0,     0,
     140,   144,     0,   134,   163,   139,    33,   108,     0,     0,
       0,     0,   153,   151,   152,   141,   163,   163,   160,     0,
       0,     0,   163,   133,   162,   159,     0,   138,   137,   161
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    27,    28,    66,    49,   108,   275,   256,
     214,   109,   110,   111,   112,   113,   114,   115,   116,   164,
     165,   166,   167,   168,   169,   170,   171,    34,    30,    53,
      78,    79,    80,   118,    81,   132,    82,    83,    84,    85,
      86,    87,    88,     3,   229,   141,   230,   269,   290,   248,
     243,   244,   245,   263,   283
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -256
static const yytype_int16 yypact[] =
{
      16,  -256,    30,  -256,  -256,   203,    29,    38,    52,    -6,
       0,    84,   130,   129,   133,   153,   162,   169,   174,   179,
     142,   182,   192,   201,   215,  -256,  -256,   203,  -256,   166,
      -4,   227,  -256,   232,  -256,   250,  -256,  -256,  -256,  -256,
    -256,  -256,  -256,  -256,  -256,  -256,   244,  -256,  -256,   255,
    -256,  -256,  -256,     4,   262,  -256,   272,  -256,   271,   273,
     274,   224,   228,   229,   230,  -256,   290,   101,   120,  -256,
     298,   233,   234,   299,     8,    20,  -256,   300,   -22,  -256,
    -256,    61,  -256,    39,    15,  -256,    60,   291,   256,  -256,
     237,   240,   241,   242,   243,   301,   305,   306,   307,   101,
    -256,  -256,  -256,    90,    90,    90,    55,  -256,   304,    34,
     246,  -256,   247,   117,   245,   138,  -256,  -256,  -256,     8,
       8,  -256,  -256,   152,    15,  -256,  -256,    61,  -256,  -256,
    -256,  -256,    68,  -256,    12,    12,    39,   313,     8,  -256,
      68,  -256,  -256,   312,   314,   315,   316,  -256,  -256,  -256,
    -256,   317,   168,  -256,  -256,  -256,  -256,  -256,  -256,    90,
      55,    55,    55,  -256,   -35,   254,  -256,   258,    41,   252,
     181,  -256,  -256,    90,    46,    90,    90,   245,   131,  -256,
    -256,   190,   206,  -256,    15,    68,   303,  -256,  -256,    18,
    -256,   178,   257,  -256,  -256,  -256,  -256,  -256,   208,  -256,
    -256,    -9,    55,  -256,    55,    55,   252,   122,  -256,  -256,
     246,   323,  -256,  -256,   320,  -256,  -256,   138,  -256,   308,
    -256,   259,   302,  -256,    50,    50,    50,    50,    50,   282,
     178,  -256,  -256,  -256,   254,  -256,  -256,   181,   324,  -256,
     270,   302,  -256,   -10,  -256,   251,   331,   332,    -1,    -1,
      -1,    50,    50,   336,  -256,  -256,   101,     8,    94,    16,
    -256,  -256,  -256,   121,  -256,   335,  -256,   337,  -256,   177,
    -256,   177,    -1,  -256,    23,   101,  -256,   213,  -256,  -256,
    -256,     2,  -256,     9,   338,  -256,  -256,  -256,   339,   340,
    -256,  -256,   177,   265,   302,  -256,  -256,  -256,   341,   344,
     266,   345,  -256,  -256,  -256,  -256,   302,   105,  -256,   342,
     347,   275,   134,    16,  -256,  -256,   350,  -256,  -256,  -256
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -256,  -256,  -256,  -256,   327,  -256,  -256,   -97,  -256,  -256,
    -256,   -46,   183,   107,   180,  -256,   248,   164,  -256,   193,
     155,    82,   128,  -256,   191,   156,  -256,   352,  -256,  -256,
       7,    25,  -256,  -256,   283,   238,  -256,   -81,   249,   226,
     -73,  -256,  -256,   -53,   136,  -256,  -256,   -45,  -255,   -77,
    -136,  -111,  -256,  -256,  -256
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -135
static const yytype_int16 yytable[] =
{
      89,   123,   151,   136,  -133,   298,    55,    68,   266,    69,
      70,    68,   300,    69,   122,    68,   291,    69,    68,   242,
      69,   122,     1,    68,   221,    69,   124,    71,    72,   293,
       4,    71,    72,   202,    29,    71,    72,   305,    71,    72,
       1,    31,   203,    71,    72,   133,   181,   182,   155,   156,
     211,   212,   128,   129,   267,   246,   174,   152,    32,   202,
      33,    73,   155,   156,   137,    73,    35,   259,   233,    73,
      74,   186,    73,    69,    74,    56,    75,    73,    74,   268,
      75,    74,   125,   299,    76,    77,    74,   135,    76,    77,
     301,    37,    76,    77,   222,    76,    77,   100,   101,   294,
      76,    77,   173,   136,   157,   258,   158,   159,   100,   101,
     213,   -36,   134,   198,   -86,   -86,   -86,   162,   157,   163,
     158,   159,   247,   242,   100,   101,   160,   161,   138,   155,
     156,   162,   260,   163,   242,    39,   223,    38,   100,   101,
      40,   188,   125,   130,   131,    46,   117,   260,   249,   250,
     251,   252,   280,   102,   281,   282,   103,   187,   307,   276,
      41,   104,   105,   242,   102,   191,   106,   103,   107,    42,
     312,   278,   104,   105,   272,   273,    43,   106,   296,   107,
     102,    44,   313,   103,   277,   157,    45,   158,   159,    47,
     -62,   -62,   -62,   106,   102,   107,   260,   103,   162,    48,
     163,   260,  -111,  -111,   270,   271,   279,   106,    50,   107,
     220,   317,   179,   180,     6,     7,     8,     9,    10,   183,
     138,   295,    51,   224,   225,   226,   227,   292,   286,   287,
     288,   289,    54,    11,   228,   197,   173,    57,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    58,    59,
      60,    65,    61,    62,    63,   208,   209,   218,   138,    67,
     318,    22,    23,    24,    25,    26,    58,    59,    60,    90,
      64,    62,    63,   219,   138,   232,   173,    91,   261,   262,
     297,   138,   215,   216,   153,   154,   235,   236,   199,   200,
      92,    95,    93,    94,    99,    96,    97,    98,  -134,   119,
     120,   139,   121,   126,   142,   140,   143,   147,   144,   145,
     146,   148,   149,   150,   172,   175,   189,   176,   178,   192,
     193,   194,   195,   204,   231,   207,   238,   196,   205,   117,
     239,   242,   253,   240,   255,   241,   257,   264,   265,   274,
     284,   306,   217,   285,   302,   303,   304,   309,   311,   310,
     315,   308,   314,   319,    52,   201,   210,   234,   316,   206,
     127,   177,    36,   237,   190,   185,   254,     0,     0,     0,
       0,     0,     0,   184
};

static const yytype_int16 yycheck[] =
{
      53,    74,    99,    84,     0,     3,    10,     3,     9,     5,
       6,     3,     3,     5,     6,     3,   271,     5,     3,    29,
       5,     6,     6,     3,     6,     5,     6,    23,    24,     6,
       0,    23,    24,    68,     5,    23,    24,   292,    23,    24,
       6,     3,    77,    23,    24,     6,   119,   120,     7,     8,
       4,     5,    74,    75,    55,     5,   109,   103,     6,    68,
      66,    57,     7,     8,     4,    57,    66,    77,    77,    57,
      66,     3,    57,     5,    66,    79,    72,    57,    66,    80,
      72,    66,    75,    81,    80,    81,    66,    72,    80,    81,
      81,     7,    80,    81,    76,    80,    81,     7,     8,    76,
      80,    81,    68,   184,    63,   241,    65,    66,     7,     8,
      64,    10,    73,   159,    73,    74,    75,    76,    63,    78,
      65,    66,    72,    29,     7,     8,    71,    72,    68,     7,
       8,    76,   243,    78,    29,     6,   189,     7,     7,     8,
       7,   134,   135,    82,    83,     3,    26,   258,   225,   226,
     227,   228,    31,    63,    33,    34,    66,   132,   294,   256,
       7,    71,    72,    29,    63,   140,    76,    66,    78,     7,
     306,    77,    71,    72,   251,   252,     7,    76,   275,    78,
      63,     7,    77,    66,   257,    63,     7,    65,    66,     7,
      73,    74,    75,    76,    63,    78,   307,    66,    76,     7,
      78,   312,    82,    83,   249,   250,   259,    76,     7,    78,
     185,    77,    74,    75,    11,    12,    13,    14,    15,    67,
      68,   274,     7,    45,    46,    47,    48,   272,    51,    52,
      53,    54,    66,    30,    56,    67,    68,    10,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    16,    17,
      18,     7,    20,    21,    22,    74,    75,    67,    68,     4,
     313,    58,    59,    60,    61,    62,    16,    17,    18,     7,
      20,    21,    22,    67,    68,    67,    68,     5,    27,    28,
      67,    68,   175,   176,   104,   105,   204,   205,   160,   161,
      19,    67,    19,    19,     4,    67,    67,    67,     0,    66,
      66,    10,     3,     3,    67,    49,    66,     6,    67,    67,
      67,     6,     6,     6,    10,    69,     3,    70,    73,     7,
       6,     6,     6,    69,    67,    73,     3,    10,    70,    26,
      10,    29,    50,    25,    10,    76,    66,     6,     6,     3,
       5,    76,   178,     6,     6,     6,     6,     3,     3,    83,
       3,    10,    10,     3,    27,   162,   173,   202,    83,   168,
      77,   113,    10,   207,   138,   127,   230,    -1,    -1,    -1,
      -1,    -1,    -1,   124
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    85,   127,     0,    86,    11,    12,    13,    14,
      15,    30,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    58,    59,    60,    61,    62,    87,    88,     5,
     112,     3,     6,    66,   111,    66,   111,     7,     7,     6,
       7,     7,     7,     7,     7,     7,     3,     7,     7,    90,
       7,     7,    88,   113,    66,    10,    79,    10,    16,    17,
      18,    20,    21,    22,    20,     7,    89,     4,     3,     5,
       6,    23,    24,    57,    66,    72,    80,    81,   114,   115,
     116,   118,   120,   121,   122,   123,   124,   125,   126,   127,
       7,     5,    19,    19,    19,    67,    67,    67,    67,     4,
       7,     8,    63,    66,    71,    72,    76,    78,    91,    95,
      96,    97,    98,    99,   100,   101,   102,    26,   117,    66,
      66,     3,     6,   124,     6,   114,     3,   118,    74,    75,
      82,    83,   119,     6,    73,    72,   121,     4,    68,    10,
      49,   129,    67,    66,    67,    67,    67,     6,     6,     6,
       6,    91,    95,    98,    98,     7,     8,    63,    65,    66,
      71,    72,    76,    78,   103,   104,   105,   106,   107,   108,
     109,   110,    10,    68,   127,    69,    70,   100,    73,    74,
      75,   124,   124,    67,   122,   119,     3,   115,   114,     3,
     123,   115,     7,     6,     6,     6,    10,    67,    95,   106,
     106,   103,    68,    77,    69,    70,   108,    73,    74,    75,
      96,     4,     5,    64,    94,    97,    97,   101,    67,    67,
     115,     6,    76,   127,    45,    46,    47,    48,    56,   128,
     130,    67,    67,    77,   104,   105,   105,   109,     3,    10,
      25,    76,    29,   134,   135,   136,     5,    72,   133,   133,
     133,   133,   133,    50,   128,    10,    93,    66,   134,    77,
     135,    27,    28,   137,     6,     6,     9,    55,    80,   131,
     131,   131,   133,   133,     3,    92,    91,   124,    77,   127,
      31,    33,    34,   138,     5,     6,    51,    52,    53,    54,
     132,   132,   131,     6,    76,   127,    91,    67,     3,    81,
       3,    81,     6,     6,     6,   132,    76,   134,    10,     3,
      83,     3,   134,    77,    10,     3,    83,    77,   127,     3
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
          case KDevPG::GDFA::SAscii: KDevPG::GDFA::type = KDevPG::GDFA::TAscii; break;
          case KDevPG::GDFA::SLatin1: KDevPG::GDFA::type = KDevPG::GDFA::TLatin1; break;
          case KDevPG::GDFA::SUtf8: KDevPG::GDFA::type = KDevPG::GDFA::TUtf8; break;
          case KDevPG::GDFA::SUcs2: KDevPG::GDFA::type = KDevPG::GDFA::TUcs2; break;
          case KDevPG::GDFA::SUtf16: KDevPG::GDFA::type = KDevPG::GDFA::TUtf16; break;
/*           case KDevPG::GDFA::SUcs4: KDevPG::GDFA::type = KDevPG::GDFA::TUcs4; break; */
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
        case KDevPG::GDFA::TAscii: KDevPG::GDFA::type = KDevPG::GDFA::SAscii; break;
        case KDevPG::GDFA::TLatin1: KDevPG::GDFA::type = KDevPG::GDFA::SLatin1; break;
        case KDevPG::GDFA::TUtf8: KDevPG::GDFA::type = KDevPG::GDFA::SUtf8; break;
        case KDevPG::GDFA::TUcs2: KDevPG::GDFA::type = KDevPG::GDFA::SUcs2; break;
        case KDevPG::GDFA::TUtf16: KDevPG::GDFA::type = KDevPG::GDFA::SUtf16; break;
/*         case KDevPG::GDFA::TUcs4: KDevPG::GDFA::type = KDevPG::GDFA::SUcs4; break; */
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
        KDevPG::GDFA::type = (typeof(KDevPG::GDFA::type))(base);
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
    { KDevPG::globalSystem.regexpById[(yyvsp[(4) - (5)].str)] = (yyvsp[(1) - (5)].nfa);
            ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 206 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              if((yyvsp[(1) - (4)].nfa)->acceptsEpsilon())
              {
                KDevPG::checkOut << "** ERROR Lexer rule accepting the empty word at line " << yyLine << endl;
                KDevPG::ProblemSummaryPrinter::reportError();
              }
              QString s = QString((yyvsp[(2) - (4)].str)) + QString(r); KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[(1) - (4)].nfa));
              KDevPG::globalSystem.lexerActions[lexerEnv].push_back(
                s);
            ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 220 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
        r = "\nRETURN(" + QString((yyvsp[(1) - (1)].str)) + ");\n"
      ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 223 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
        r = "\nCONTINUE;\n"; 
      ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 226 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { r = "\nSKIP\n" ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 230 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) |= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 231 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 235 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) &= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 236 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 240 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) ^= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 241 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 245 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA((yyvsp[(2) - (2)].nfa)->negate()); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 246 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(2) - (2)].nfa) |= KDevPG::GNFA()); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 247 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 251 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (2)].nfa) <<= *(yyvsp[(2) - (2)].nfa)); delete (yyvsp[(1) - (2)].nfa); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 252 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 256 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa)); KDevPG::GNFA *tmp = new KDevPG::GNFA(*(yyvsp[(3) - (3)].nfa) <<= *(yyvsp[(1) - (3)].nfa)); **tmp; *(yyval.nfa) <<= *tmp; delete tmp; delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 257 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 261 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(**(yyvsp[(1) - (2)].nfa)); delete (yyvsp[(1) - (2)].nfa); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 262 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (2)].nfa)); **(yyval.nfa); *(yyval.nfa) <<= *(yyvsp[(1) - (2)].nfa); delete (yyvsp[(1) - (2)].nfa); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 263 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 267 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(2) - (3)].nfa)); delete (yyvsp[(2) - (3)].nfa); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 268 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(2) - (3)].nfa); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 269 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::anyChar()); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 270 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::keyword(KDevPG::unescaped(QByteArray((yyvsp[(1) - (1)].str))))); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 271 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::keyword(KDevPG::unescaped(QByteArray((yyvsp[(1) - (1)].str))))); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 272 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
                              if(KDevPG::globalSystem.regexpById[(yyvsp[(1) - (1)].str)] == 0)
                              {
                                KDevPG::checkOut << "** ERROR: no named regexp " << (yyvsp[(1) - (1)].str) << endl;
                                exit(-1);
                              }
                              KDevPG::GNFA *regexp = KDevPG::globalSystem.regexpById[(yyvsp[(1) - (1)].str)];
                              if(!KDevPG::globalSystem.isMinimizedRegexp.contains(regexp))
                              {
                                regexp->minimize();
                                KDevPG::globalSystem.isMinimizedRegexp.insert(regexp);
                              }
                              (yyval.nfa) = new KDevPG::GNFA(*regexp);
                            ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 286 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::emptyWord()); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 290 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) |= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 291 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 295 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) &= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 296 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 300 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) ^= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 301 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 305 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA((yyvsp[(2) - (2)].nfa)->negate()); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 306 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(2) - (2)].nfa) |= KDevPG::GNFA()); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 307 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 311 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (2)].nfa) |= *(yyvsp[(2) - (2)].nfa)); delete (yyvsp[(1) - (2)].nfa); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 316 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa)); KDevPG::GNFA *tmp = new KDevPG::GNFA(*(yyvsp[(3) - (3)].nfa) <<= *(yyvsp[(1) - (3)].nfa)); **tmp; *(yyval.nfa) <<= *tmp; delete tmp; delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 317 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 321 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(**(yyvsp[(1) - (2)].nfa)); delete (yyvsp[(1) - (2)].nfa); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 322 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (2)].nfa)); **(yyval.nfa); *(yyval.nfa) <<= *(yyvsp[(1) - (2)].nfa); delete (yyvsp[(1) - (2)].nfa); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 323 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 327 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(2) - (3)].nfa)); delete (yyvsp[(2) - (3)].nfa); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 328 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(2) - (3)].nfa); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 329 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::anyChar()); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 330 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::keyword(KDevPG::unescaped(QByteArray((yyvsp[(1) - (1)].str))))); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 331 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
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

  case 84:

/* Line 1455 of yacc.c  */
#line 354 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::collection(KDevPG::unescaped(QByteArray((yyvsp[(1) - (1)].str))))); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 355 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
                              if(KDevPG::globalSystem.regexpById[(yyvsp[(1) - (1)].str)] == 0)
                              {
                                KDevPG::checkOut << "** ERROR: no named regexp " << (yyvsp[(1) - (1)].str) << endl;
                                exit(-1);
                              }
                              KDevPG::GNFA *regexp = KDevPG::globalSystem.regexpById[(yyvsp[(1) - (1)].str)];
                              if(!KDevPG::globalSystem.isMinimizedRegexp.contains(regexp))
                              {
                                regexp->minimize();
                                KDevPG::globalSystem.isMinimizedRegexp.insert(regexp);
                              }
                              (yyval.nfa) = new KDevPG::GNFA(*regexp);
                            ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 369 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::emptyWord()); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 375 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PublicDeclaration, (yyvsp[(5) - (5)].str));    ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 377 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ProtectedDeclaration, (yyvsp[(5) - (5)].str)); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 379 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PrivateDeclaration, (yyvsp[(5) - (5)].str));   ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 381 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ConstructorCode, (yyvsp[(4) - (4)].str));      ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 383 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::DestructorCode, (yyvsp[(4) - (4)].str));       ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 387 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(1) - (1)].str),(yyvsp[(1) - (1)].str)); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 388 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(1) - (4)].str),(yyvsp[(3) - (4)].str)); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 389 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(3) - (3)].str),(yyvsp[(3) - (3)].str)); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 391 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(3) - (6)].str),(yyvsp[(5) - (6)].str)); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 396 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushRule((yyvsp[(2) - (3)].item)); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 400 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::globalSystem.zero(); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 401 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(2) - (3)].item); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 402 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 403 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 404 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::inlinedNonTerminal(KDevPG::globalSystem.pushSymbol((yyvsp[(2) - (2)].str))); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 405 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::annotation((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].item), false, (yyvsp[(2) - (3)].storageType)); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 406 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::annotation((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].item), true, (yyvsp[(3) - (4)].storageType));  ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 410 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::nonTerminal(KDevPG::globalSystem.pushSymbol((yyvsp[(1) - (2)].str)), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 411 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::globalSystem.terminal((yyvsp[(1) - (1)].str)); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 416 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[(3) - (4)].item), 0);
        ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 421 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[(3) - (8)].item), (yyvsp[(7) - (8)].item));
        ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 427 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = const_cast<char*>(""); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 428 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 432 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 442 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember; ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 443 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;  ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 447 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::plus((yyvsp[(1) - (2)].item)); ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 448 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::star((yyvsp[(1) - (2)].item)); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 449 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 450 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::alternative((yyvsp[(2) - (2)].item), KDevPG::globalSystem.zero()); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 454 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 456 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::CloneTree cl;
          (yyval.item) = KDevPG::cons((yyvsp[(1) - (3)].item), KDevPG::star(KDevPG::cons(cl.clone((yyvsp[(3) - (3)].item)), cl.clone((yyvsp[(1) - (3)].item)))));
        ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 460 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::action((yyvsp[(1) - (2)].item), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 461 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::action(0, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 465 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 466 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::cons((yyvsp[(1) - (2)].item), (yyvsp[(2) - (2)].item)); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 470 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 471 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::condition((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].item)); ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 475 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 476 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::alternative((yyvsp[(1) - (3)].item), (yyvsp[(3) - (3)].item)); ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 481 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.item) = KDevPG::evolve((yyvsp[(1) - (7)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (7)].str)),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(6) - (7)].item), (yyvsp[(4) - (7)].str));
        ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 486 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.item) = KDevPG::evolve((yyvsp[(1) - (7)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (7)].str)),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(5) - (7)].item), (yyvsp[(7) - (7)].str));
        ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 491 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::evolve((yyvsp[(1) - (4)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (4)].str)), 0, (yyvsp[(4) - (4)].str)); ;}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 492 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { if(KDevPG::globalSystem.generateAst == false)
        {
          qFatal("Operator-expression-parsing is not yet supported with --no-ast!");
          exit(-1);
        }
        operatorNode = KDevPG::createNode<KDevPG::Model::OperatorItem>();
      ;}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 498 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.needOperatorStack = true; (yyval.item) = (yyvsp[(2) - (2)].item); ;}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 502 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = const_cast<char*>(""); ;}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 503 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 509 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { ; ;}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 514 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (9)].item);
              operatorNode->mName = (yyvsp[(5) - (9)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (9)].str)), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[(7) - (9)].item), (yyvsp[(9) - (9)].str));
            ;}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 522 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (9)].item);
              operatorNode->mName = (yyvsp[(5) - (9)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (9)].str)), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[(8) - (9)].item), (yyvsp[(6) - (9)].str));
            ;}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 530 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (6)].item);
              operatorNode->mName = (yyvsp[(5) - (6)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (6)].str)), 0, (yyvsp[(6) - (6)].str));
            ;}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 540 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushBin(*(yyvsp[(2) - (4)].operatorInformation), (yyvsp[(4) - (4)].str), (yyvsp[(3) - (4)].str)); free((yyvsp[(2) - (4)].operatorInformation)); ;}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 541 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushTern(*(yyvsp[(2) - (5)].operatorInformation), *(yyvsp[(3) - (5)].operatorInformation), (yyvsp[(5) - (5)].str), (yyvsp[(4) - (5)].str)); free((yyvsp[(2) - (5)].operatorInformation)); free((yyvsp[(3) - (5)].operatorInformation)); ;}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 542 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPre(*(yyvsp[(2) - (3)].operatorInformation), (yyvsp[(3) - (3)].str)); free((yyvsp[(2) - (3)].operatorInformation)); ;}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 543 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPost(*(yyvsp[(2) - (3)].operatorInformation), "0", (yyvsp[(3) - (3)].str)); free((yyvsp[(2) - (3)].operatorInformation)); free((yyvsp[(3) - (3)].str)); ;}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 544 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPost(*(yyvsp[(2) - (4)].operatorInformation), (yyvsp[(4) - (4)].str), (yyvsp[(3) - (4)].str)); free((yyvsp[(2) - (4)].operatorInformation)); ;}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 545 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushParen(*(yyvsp[(2) - (3)].operatorInformation), *(yyvsp[(3) - (3)].operatorInformation)); free((yyvsp[(2) - (3)].operatorInformation)); free((yyvsp[(3) - (3)].operatorInformation)); ;}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 549 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"0"; ;}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 550 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 551 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(2) - (2)].str); ;}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 555 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"1"; ;}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 556 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"0"; ;}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 557 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { uint yyleng = strlen((yyvsp[(2) - (2)].str));
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, (yyvsp[(2) - (2)].str));
                                     strcpy(tmp+yyleng+6-6+1, "?1:0)");
                                     (yyval.str) = tmp;
                                   ;}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 564 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { uint yyleng = strlen((yyvsp[(2) - (2)].str));
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, (yyvsp[(2) - (2)].str));
                                     strcpy(tmp+yyleng+6-6+1, "?0:1)");
                                     (yyval.str) = tmp;
                                   ;}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 574 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(3) - (4)].str)), (yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].str)); ;}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 575 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(3) - (3)].str)), (yyvsp[(2) - (3)].str), ""); ;}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 576 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(1) - (2)].str)), "", (yyvsp[(2) - (2)].str)); ;}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 577 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(1) - (1)].str)), "", ""); ;}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 581 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 583 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::Model::VariableDeclarationItem *last = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(1) - (2)].item);
          while (last->mNext != 0) {
            last = last->mNext;
          }
          last->mNext = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(2) - (2)].item);
          (yyval.item) = (yyvsp[(1) - (2)].item);
        ;}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 595 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (6)].declarationType), (yyvsp[(2) - (6)].storageType), (yyvsp[(3) - (6)].variableType), false, (yyvsp[(4) - (6)].str), (yyvsp[(6) - (6)].str)); ;}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 597 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (5)].declarationType), (yyvsp[(2) - (5)].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, false, (yyvsp[(4) - (5)].str), ""); ;}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 599 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (7)].declarationType), (yyvsp[(2) - (7)].storageType), (yyvsp[(3) - (7)].variableType), true, (yyvsp[(5) - (7)].str), (yyvsp[(7) - (7)].str)); ;}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 601 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (6)].declarationType), (yyvsp[(2) - (6)].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, true, (yyvsp[(5) - (6)].str), ""); ;}
    break;

  case 163:

/* Line 1455 of yacc.c  */
#line 605 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationLocal;     ;}
    break;

  case 164:

/* Line 1455 of yacc.c  */
#line 606 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationArgument;  ;}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 610 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember;    ;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 611 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;     ;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 615 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeNode;             ;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 616 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeVariable;         ;}
    break;



/* Line 1455 of yacc.c  */
#line 3022 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"
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
#line 619 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"


