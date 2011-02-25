
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



/* Line 189 of yacc.c  */
#line 118 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"

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

/* Line 214 of yacc.c  */
#line 46 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"

    KDevPG::Model::Node *item;
    char* str;
    KDevPG::Model::VariableDeclarationItem::DeclarationType declarationType;
    KDevPG::Model::VariableDeclarationItem::StorageType     storageType;
    KDevPG::Model::VariableDeclarationItem::VariableType    variableType;
    KDevPG::Model::Operator                                *operatorInformation;
    KDevPG::GNFA                                           *nfa;



/* Line 214 of yacc.c  */
#line 226 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 238 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"

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
#define YYLAST   325

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  130
/* YYNRULES -- Number of states.  */
#define YYNSTATES  277

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   315

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    70,     2,     2,     2,     2,
      62,    63,    65,    73,    68,     2,     2,     2,    69,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    72,     9,
       2,    71,     2,    74,    75,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    76,     2,    77,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,    64,    67,     2,     2,     2,     2,
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
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,    10,    12,    15,    18,    24,    27,
      33,    37,    39,    41,    44,    48,    51,    54,    57,    60,
      63,    66,    69,    72,    75,    78,    82,    85,    88,    89,
      96,    97,   103,   104,   113,   114,   122,   123,   130,   131,
     137,   138,   142,   144,   147,   149,   152,   156,   158,   162,
     168,   174,   180,   185,   190,   192,   197,   201,   208,   211,
     215,   217,   221,   223,   225,   228,   232,   237,   240,   242,
     247,   256,   257,   259,   261,   263,   265,   268,   271,   273,
     276,   278,   282,   285,   287,   289,   292,   294,   298,   300,
     304,   312,   320,   325,   326,   329,   330,   332,   335,   336,
     346,   356,   363,   368,   374,   378,   382,   387,   391,   393,
     395,   398,   400,   402,   405,   408,   413,   417,   420,   422,
     424,   427,   434,   440,   448,   455,   456,   458,   460,   462,
     464
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      79,     0,    -1,    -1,   109,    80,    81,    95,   109,    -1,
      82,    -1,    81,    82,    -1,    13,    93,    -1,    13,    62,
      19,    63,     6,    -1,    14,    93,    -1,    14,    62,    19,
      63,     6,    -1,    10,    94,     9,    -1,    60,    -1,    61,
      -1,    59,     7,    -1,    11,     3,     9,    -1,    29,     7,
      -1,    34,     7,    -1,    12,     6,    -1,    35,     6,    -1,
      36,     7,    -1,    37,     7,    -1,    38,     7,    -1,    39,
       7,    -1,    58,     7,    -1,    40,     7,    -1,    42,     3,
       7,    -1,    41,     7,    -1,    43,     7,    -1,    -1,    57,
       7,    83,     4,    85,     9,    -1,    -1,    57,    84,     4,
      85,     9,    -1,    -1,    90,   109,     5,     4,     3,     9,
      86,    85,    -1,    -1,    90,   109,     4,     3,     9,    87,
      85,    -1,    -1,    90,   109,     5,     9,    88,    85,    -1,
      -1,    90,   109,     9,    89,    85,    -1,    -1,    90,    64,
      91,    -1,    91,    -1,    91,    92,    -1,    92,    -1,    65,
      92,    -1,    62,    90,    63,    -1,     7,    -1,    66,     3,
      67,    -1,    62,    15,    18,    63,     6,    -1,    62,    17,
      18,    63,     6,    -1,    62,    16,    18,    63,     6,    -1,
      62,    20,    63,     6,    -1,    62,    21,    63,     6,    -1,
       5,    -1,     5,    62,     7,    63,    -1,    94,    68,     5,
      -1,    94,    68,     5,    62,     7,    63,    -1,   107,     9,
      -1,    95,   107,     9,    -1,    69,    -1,    62,   106,    63,
      -1,    98,    -1,    97,    -1,    56,     3,    -1,   100,   101,
      97,    -1,    70,   100,   101,    97,    -1,     3,    99,    -1,
       5,    -1,    22,    62,   106,    63,    -1,    23,    62,   106,
      63,    24,    62,   106,    63,    -1,    -1,    25,    -1,     3,
      -1,    71,    -1,    72,    -1,    96,    73,    -1,    96,    65,
      -1,    96,    -1,    74,    96,    -1,   102,    -1,   103,    75,
      96,    -1,   103,     6,    -1,     6,    -1,   103,    -1,   104,
     103,    -1,   104,    -1,    74,     6,   104,    -1,   105,    -1,
     106,    64,   105,    -1,   106,     4,     3,     6,    76,   116,
      77,    -1,   106,     4,     3,    76,   116,    77,   109,    -1,
     106,     4,     3,   109,    -1,    -1,   108,   111,    -1,    -1,
       6,    -1,   112,   110,    -1,    -1,    48,    97,   110,    49,
       3,    76,   116,    77,   109,    -1,    48,    97,   110,    49,
       3,     6,    76,   116,    77,    -1,    48,    97,   110,    49,
       3,   109,    -1,    44,   115,   113,   114,    -1,    47,   115,
     115,   113,   114,    -1,    45,   115,   113,    -1,    46,   115,
     113,    -1,    46,   115,   113,   114,    -1,    55,   115,   115,
      -1,    69,    -1,     8,    -1,    54,     6,    -1,    50,    -1,
      51,    -1,    52,     6,    -1,    53,     6,    -1,    74,     6,
       5,     6,    -1,    74,     6,     5,    -1,     5,     6,    -1,
       5,    -1,   117,    -1,   116,   117,    -1,   118,   119,   120,
       3,    72,     3,    -1,   118,   119,    32,     3,     9,    -1,
     118,   119,   120,    70,     3,    72,     3,    -1,   118,   119,
      32,    70,     3,     9,    -1,    -1,    28,    -1,    26,    -1,
      27,    -1,    30,    -1,    33,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    89,    89,    89,    96,    97,   101,   103,   105,   107,
     109,   110,   122,   134,   157,   159,   161,   163,   165,   167,
     169,   171,   173,   175,   177,   179,   181,   183,   185,   185,
     186,   186,   191,   190,   200,   199,   205,   204,   213,   212,
     216,   220,   221,   225,   226,   230,   231,   232,   233,   237,
     239,   241,   243,   245,   250,   251,   252,   253,   258,   259,
     263,   264,   265,   266,   267,   268,   269,   273,   274,   278,
     283,   290,   291,   295,   305,   306,   310,   311,   312,   313,
     317,   318,   323,   324,   328,   329,   333,   334,   338,   339,
     343,   348,   353,   355,   355,   365,   366,   371,   372,   376,
     384,   392,   403,   404,   405,   406,   407,   408,   412,   413,
     414,   418,   419,   420,   427,   437,   438,   439,   440,   444,
     445,   457,   459,   461,   463,   468,   469,   473,   474,   478,
     479
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
  "T_PARSERCLASS_DECLARATION", "T_LEXERCLASS_DECLARATION", "T_PUBLIC",
  "T_PRIVATE", "T_PROTECTED", "T_DECLARATION", "T_BITS", "T_CONSTRUCTOR",
  "T_DESTRUCTOR", "T_TRY_RECOVER", "T_TRY_ROLLBACK", "T_CATCH",
  "T_RULE_ARGUMENTS", "T_MEMBER", "T_TEMPORARY", "T_ARGUMENT",
  "T_EXPORT_MACRO", "T_NODE", "T_NODE_SEQUENCE", "T_TOKEN", "T_VARIABLE",
  "T_EXPORT_MACRO_HEADER", "T_AST_DECLARATION",
  "T_PARSER_DECLARATION_HEADER", "T_PARSER_BITS_HEADER", "T_AST_HEADER",
  "T_TOKEN_STREAM_DECLARATION_HEADER", "T_TOKEN_STREAM_BITS_HEADER",
  "T_PARSER_BASE", "T_AST_BASE", "T_TOKEN_STREAM_BASE", "T_BIN", "T_PRE",
  "T_POST", "T_TERN", "T_LOPR", "T_ROPR", "T_LEFT_ASSOC", "T_RIGHT_ASSOC",
  "T_IS_LEFT_ASSOC", "T_IS_RIGHT_ASSOC", "T_PRIORITY", "T_PAREN",
  "T_INLINE", "T_LEXER", "T_INPUT_STREAM", "T_INPUT_ENCODING",
  "T_TABLE_LEXER", "T_SEQUENCE_LEXER", "'('", "')'", "'|'", "'*'", "'{'",
  "'}'", "','", "'0'", "'#'", "'='", "':'", "'+'", "'?'", "'@'", "'['",
  "']'", "$accept", "system", "$@1", "declarations", "declaration", "$@2",
  "$@3", "lexer_declaration_rest", "$@4", "$@5", "$@6", "$@7", "regexp",
  "regexp1", "regexp2", "member_declaration_rest", "declared_tokens",
  "rules", "primary_item", "primary_atom", "try_item",
  "rule_arguments_opt", "name", "scope", "unary_item", "postfix_item",
  "item_sequence", "conditional_item", "option_item", "item", "$@8",
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
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,    40,    41,   124,    42,   123,   125,    44,    48,
      35,    61,    58,    43,    63,    64,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    80,    79,    81,    81,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    83,    82,
      84,    82,    86,    85,    87,    85,    88,    85,    89,    85,
      85,    90,    90,    91,    91,    92,    92,    92,    92,    93,
      93,    93,    93,    93,    94,    94,    94,    94,    95,    95,
      96,    96,    96,    96,    96,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   101,   101,   102,   102,   102,   102,
     103,   103,   103,   103,   104,   104,   105,   105,   106,   106,
     107,   107,   107,   108,   107,   109,   109,   110,   110,   111,
     111,   111,   112,   112,   112,   112,   112,   112,   113,   113,
     113,   114,   114,   114,   114,   115,   115,   115,   115,   116,
     116,   117,   117,   117,   117,   118,   118,   119,   119,   120,
     120
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     5,     1,     2,     2,     5,     2,     5,
       3,     1,     1,     2,     3,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     2,     2,     0,     6,
       0,     5,     0,     8,     0,     7,     0,     6,     0,     5,
       0,     3,     1,     2,     1,     2,     3,     1,     3,     5,
       5,     5,     4,     4,     1,     4,     3,     6,     2,     3,
       1,     3,     1,     1,     2,     3,     4,     2,     1,     4,
       8,     0,     1,     1,     1,     1,     2,     2,     1,     2,
       1,     3,     2,     1,     1,     2,     1,     3,     1,     3,
       7,     7,     4,     0,     2,     0,     1,     2,     0,     9,
       9,     6,     4,     5,     3,     3,     4,     3,     1,     1,
       2,     1,     1,     2,     2,     4,     3,     2,     1,     1,
       2,     6,     5,     7,     6,     0,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      95,    96,     0,     2,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,     0,     0,    11,    12,    93,     4,    54,
       0,     0,    17,     0,     6,     0,     8,    15,    16,    18,
      19,    20,    21,    22,    24,    26,     0,    27,    28,     0,
      23,    13,    71,    68,    83,     0,     0,     0,     0,    60,
       0,     0,     5,    93,    78,    63,    62,     0,    80,    84,
      86,    88,     0,     0,     0,     0,    10,     0,    14,     0,
       0,     0,     0,     0,     0,     0,    25,     0,    40,    72,
      67,     0,     0,    64,     0,    73,     0,     0,    79,    83,
       0,     3,    77,    76,    74,    75,     0,    82,     0,     0,
      85,     0,     0,    58,     0,    94,     0,    56,     0,     0,
       0,     0,     0,     0,     0,    40,    47,     0,     0,     0,
       0,    95,    42,    44,     0,     0,    61,     0,    87,    59,
      71,    65,    81,    95,    89,    98,    55,     0,     0,     0,
       0,     7,    52,    53,     9,     0,     0,    45,     0,    31,
       0,     0,    43,    69,     0,    66,    96,   125,    92,     0,
       0,     0,     0,     0,     0,    98,     0,    49,    51,    50,
      29,    46,    48,    41,     0,     0,    38,     0,   125,   126,
     125,   119,     0,   118,     0,     0,     0,     0,     0,     0,
       0,    97,    57,     0,     0,    36,    40,     0,   125,    95,
     120,   127,   128,     0,   117,     0,   109,     0,   108,     0,
     104,   105,     0,   107,    95,    34,     0,    40,    39,     0,
      90,    91,   129,     0,   130,     0,   116,   110,   111,   112,
       0,     0,   102,   106,     0,    96,   125,   101,    40,    32,
      37,    70,     0,     0,     0,     0,   115,   113,   114,   103,
     125,   125,    35,    40,   122,     0,     0,     0,   125,    95,
      33,   124,   121,     0,   100,    99,   123
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    27,    28,    87,    49,   130,   263,   248,
     227,   206,   131,   132,   133,    34,    30,    63,    64,    65,
      66,    90,    67,   106,    68,    69,    70,    71,    72,    73,
      74,     3,   174,   115,   175,   219,   242,   195,   190,   191,
     192,   213,   235
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -188
static const yytype_int16 yypact[] =
{
      41,  -188,    53,  -188,  -188,   204,    56,    96,   108,    57,
      77,   159,   164,   172,   184,   185,   197,   198,   205,   213,
     208,   214,   215,   217,   218,  -188,  -188,    95,  -188,   166,
       3,   221,  -188,   128,  -188,   178,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,   225,  -188,  -188,   230,
    -188,  -188,   103,  -188,  -188,   173,   186,   246,    17,  -188,
     247,   167,  -188,     8,   -23,  -188,  -188,   -28,  -188,    13,
     157,  -188,     5,   242,   206,   245,  -188,   248,  -188,   237,
     238,   239,   195,   196,   203,   207,  -188,   256,    50,  -188,
    -188,    17,    17,  -188,    63,  -188,   -28,   157,  -188,   267,
     259,  -188,  -188,  -188,  -188,  -188,    55,  -188,    33,    33,
      13,   266,    17,  -188,    55,  -188,   209,   211,   212,   216,
     219,   265,   268,   270,   271,    50,  -188,    50,    50,   275,
     272,     1,    50,  -188,    78,   104,  -188,    55,   157,  -188,
     255,  -188,  -188,    -1,  -188,   141,  -188,   276,   278,   279,
     280,  -188,  -188,  -188,  -188,   281,   113,  -188,   220,  -188,
      50,    28,  -188,  -188,   264,  -188,   222,   261,  -188,    19,
      19,    19,    19,    19,   243,   141,   228,  -188,  -188,  -188,
    -188,  -188,  -188,    50,   290,    42,  -188,   232,   261,  -188,
     -18,  -188,   132,   289,   291,    -2,    -2,    -2,    19,    19,
     293,  -188,  -188,   292,   296,  -188,    50,    17,   -11,    41,
    -188,  -188,  -188,    90,  -188,   295,  -188,   297,  -188,   150,
    -188,   150,    -2,  -188,     9,  -188,   298,    50,  -188,   144,
    -188,  -188,  -188,    22,  -188,    24,   299,  -188,  -188,  -188,
     300,   302,  -188,  -188,   150,   226,   261,  -188,    50,  -188,
    -188,  -188,   301,   306,   240,   308,  -188,  -188,  -188,  -188,
     261,    20,  -188,    50,  -188,   304,   311,   244,    44,    41,
    -188,  -188,  -188,   312,  -188,  -188,  -188
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -188,  -188,  -188,  -188,   277,  -188,  -188,  -123,  -188,  -188,
    -188,  -188,   190,   158,   -87,   309,  -188,  -188,     2,   -88,
    -188,  -188,   260,   227,  -188,   -54,   224,   210,   -57,   262,
    -188,   -63,   149,  -188,  -188,  -168,  -131,    11,  -184,  -187,
    -188,  -188,  -188
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -97
static const yytype_int16 yytable[] =
{
     101,    94,   155,   210,   208,   166,   216,     1,   -95,   111,
     189,    52,    76,    53,    99,   245,   110,   189,   141,   107,
      52,   210,    53,    54,   193,   252,   145,   254,   220,   221,
      55,    56,   184,   185,   134,   135,    52,   186,    53,    55,
      56,   157,   102,   104,   105,   162,   204,     1,   189,   165,
     103,   205,   217,     4,   244,    55,    56,   126,   140,   209,
      53,    29,   261,    98,    57,   160,   230,   218,   161,   112,
      58,    77,   189,    57,   210,   167,   268,    59,    60,    58,
     168,   210,    61,   228,   110,   246,    59,    60,   108,    57,
     243,    61,   253,   194,   255,    58,   162,   269,    52,    31,
      53,    54,    59,    60,   250,     6,     7,     8,     9,    10,
     142,    98,   127,   259,    32,   128,   129,    55,    56,    33,
     232,   274,   233,   234,    11,   262,   136,   112,    89,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    35,
     270,   163,   112,    79,    80,    81,   231,    82,    83,    84,
     229,    57,    22,    23,    24,    25,    26,    58,   211,   212,
      52,   247,    53,    54,    59,    60,    37,   164,   112,    61,
      52,    38,    53,    97,   -73,   -73,   181,   160,    39,    55,
      56,   196,   197,   198,   199,   169,   170,   171,   172,    55,
      56,    40,    41,    79,    80,    81,   173,    85,    83,    84,
     238,   239,   240,   241,    42,    43,   275,   251,   112,   222,
     223,    46,    44,    57,     6,     7,     8,     9,    10,    58,
      45,    47,    48,    57,    50,    51,    59,    60,    75,    58,
      78,   109,    86,    11,    88,    91,    59,    60,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    92,    93,
      95,   113,   116,   117,   114,   118,   119,   120,   121,   122,
     125,    22,    23,    24,    25,    26,   123,   -96,   139,   143,
     124,   151,   146,   147,   152,   148,   153,   154,   158,   149,
      89,   159,   150,   176,   177,   178,   179,   182,   187,   189,
     180,   202,   200,   203,   207,   214,   224,   215,   188,   226,
     236,   225,   260,   237,    62,   256,   257,   249,   258,   265,
     264,   267,   266,   271,   272,   276,   273,   156,   183,    36,
      96,   138,   144,   137,   201,   100
};

static const yytype_uint16 yycheck[] =
{
      63,    58,   125,   190,   188,     6,     8,     6,     0,     4,
      28,     3,     9,     5,     6,     6,    70,    28,   106,     6,
       3,   208,     5,     6,     5,     3,   114,     3,   196,   197,
      22,    23,     4,     5,    91,    92,     3,     9,     5,    22,
      23,   128,    65,    71,    72,   132,     4,     6,    28,   137,
      73,     9,    54,     0,   222,    22,    23,     7,     3,    77,
       5,     5,   246,    61,    56,    64,    77,    69,   131,    64,
      62,    68,    28,    56,   261,    76,   260,    69,    70,    62,
     143,   268,    74,   206,   138,    76,    69,    70,    75,    56,
     221,    74,    70,    74,    70,    62,   183,    77,     3,     3,
       5,     6,    69,    70,   227,    10,    11,    12,    13,    14,
     108,   109,    62,   244,     6,    65,    66,    22,    23,    62,
      30,    77,    32,    33,    29,   248,    63,    64,    25,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    62,
     263,    63,    64,    15,    16,    17,   209,    19,    20,    21,
     207,    56,    57,    58,    59,    60,    61,    62,    26,    27,
       3,   224,     5,     6,    69,    70,     7,    63,    64,    74,
       3,     7,     5,     6,    71,    72,    63,    64,     6,    22,
      23,   170,   171,   172,   173,    44,    45,    46,    47,    22,
      23,     7,     7,    15,    16,    17,    55,    19,    20,    21,
      50,    51,    52,    53,     7,     7,   269,    63,    64,   198,
     199,     3,     7,    56,    10,    11,    12,    13,    14,    62,
       7,     7,     7,    56,     7,     7,    69,    70,    62,    62,
       9,    74,     7,    29,     4,    62,    69,    70,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    62,     3,
       3,     9,     7,     5,    48,    18,    18,    18,    63,    63,
       4,    57,    58,    59,    60,    61,    63,     0,     9,     3,
      63,     6,    63,    62,     6,    63,     6,     6,     3,    63,
      25,     9,    63,     7,     6,     6,     6,    67,    24,    28,
       9,    63,    49,     3,    62,     6,     3,     6,    76,     3,
       5,     9,    76,     6,    27,     6,     6,     9,     6,     3,
       9,     3,    72,     9,     3,     3,    72,   127,   160,    10,
      60,    97,   112,    96,   175,    63
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    79,   109,     0,    80,    10,    11,    12,    13,
      14,    29,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    57,    58,    59,    60,    61,    81,    82,     5,
      94,     3,     6,    62,    93,    62,    93,     7,     7,     6,
       7,     7,     7,     7,     7,     7,     3,     7,     7,    84,
       7,     7,     3,     5,     6,    22,    23,    56,    62,    69,
      70,    74,    82,    95,    96,    97,    98,   100,   102,   103,
     104,   105,   106,   107,   108,    62,     9,    68,     9,    15,
      16,    17,    19,    20,    21,    19,     7,    83,     4,    25,
      99,    62,    62,     3,   106,     3,   100,     6,    96,     6,
     107,   109,    65,    73,    71,    72,   101,     6,    75,    74,
     103,     4,    64,     9,    48,   111,     7,     5,    18,    18,
      18,    63,    63,    63,    63,     4,     7,    62,    65,    66,
      85,    90,    91,    92,   106,   106,    63,   101,   104,     9,
       3,    97,    96,     3,   105,    97,    63,    62,    63,    63,
      63,     6,     6,     6,     6,    85,    90,    92,     3,     9,
      64,   109,    92,    63,    63,    97,     6,    76,   109,    44,
      45,    46,    47,    55,   110,   112,     7,     6,     6,     6,
       9,    63,    67,    91,     4,     5,     9,    24,    76,    28,
     116,   117,   118,     5,    74,   115,   115,   115,   115,   115,
      49,   110,    63,     3,     4,     9,    89,    62,   116,    77,
     117,    26,    27,   119,     6,     6,     8,    54,    69,   113,
     113,   113,   115,   115,     3,     9,     3,    88,    85,   106,
      77,   109,    30,    32,    33,   120,     5,     6,    50,    51,
      52,    53,   114,   114,   113,     6,    76,   109,    87,     9,
      85,    63,     3,    70,     3,    70,     6,     6,     6,   114,
      76,   116,    85,    86,     9,     3,    72,     3,   116,    77,
      85,     9,     3,    72,    77,   109,     3
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
#line 89 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.decl = (yyvsp[(1) - (1)].str); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 92 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.bits += (yyvsp[(5) - (5)].str); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 102 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserClassMember((yyvsp[(2) - (2)].item)); ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 104 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.bits += (yyvsp[(5) - (5)].str); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 106 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushLexerClassMember((yyvsp[(2) - (2)].item)); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 108 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.lexerBits += (yyvsp[(5) - (5)].str); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 111 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { if(KDevPG::globalSystem.hasLexer)
        { KDevPG::checkOut << "** ERROR you have to specify the lexer-type (%table_lexer) before any lexer rules"; exit(-1); }
        switch(KDevPG::GDFA::type)
        {
          case KDevPG::GDFA::SAscii: KDevPG::GDFA::type = KDevPG::GDFA::TAscii; break;
          case KDevPG::GDFA::SLatin1
: KDevPG::GDFA::type = KDevPG::GDFA::TLatin1
; break;
          case KDevPG::GDFA::SUcs2: KDevPG::GDFA::type = KDevPG::GDFA::TUcs2; break;
/*           case KDevPG::GDFA::SUcs4: KDevPG::GDFA::type = KDevPG::GDFA::TUcs4; break; */
          default: /* empty */;
        }
      ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 123 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { if(KDevPG::globalSystem.hasLexer)
      { KDevPG::checkOut << "** ERROR you have to specify the lexer-type (%sequence_lexer) before any lexer rules"; exit(-1); }
      switch(KDevPG::GDFA::type)
      {
        case KDevPG::GDFA::TAscii: KDevPG::GDFA::type = KDevPG::GDFA::SAscii; break;
        case KDevPG::GDFA::TLatin1
: KDevPG::GDFA::type = KDevPG::GDFA::SLatin1
; break;
        case KDevPG::GDFA::TUcs2: KDevPG::GDFA::type = KDevPG::GDFA::SUcs2; break;
/*         case KDevPG::GDFA::TUcs4: KDevPG::GDFA::type = KDevPG::GDFA::SUcs4; break; */
        default: /* empty */;
      }
      ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 135 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
        if(KDevPG::globalSystem.hasLexer)
        { KDevPG::checkOut << "** ERROR you have to specify the lexer-type (%sequence_lexer) before any lexer rules"; exit(-1); }
        int base = (KDevPG::GDFA::type / 4) * 4; // warning: magic constant: number of different codecs
        QString str = (yyvsp[(2) - (2)].str);
        str = str.toLower();
        str.replace('-', "");
        if(str == "ascii")
          /* base += 0*/;
        else if(str == "utf8" || str == "latin1")
          base += 1;
        else if(str == "ucs2" || str == "utf16")
          base += 2;
        else if(str == "ucs4" || str == "utf32")
          base += 3;
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
#line 158 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.tokenStream = (yyvsp[(2) - (3)].str);           ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 160 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.exportMacro = (yyvsp[(2) - (2)].str);           ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 162 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.exportMacroHeader = (yyvsp[(2) - (2)].str);     ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 164 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.namespaceCode = (yyvsp[(2) - (2)].str);         ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 166 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.astCode = (yyvsp[(2) - (2)].str);               ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 168 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserDeclarationHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 170 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserBitsHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 172 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushAstHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 174 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTokenStreamDeclarationHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 176 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.inputStream = (yyvsp[(2) - (2)].str); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 178 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTokenStreamBitsHeader((yyvsp[(2) - (2)].str)); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 180 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.astBaseClasses[(yyvsp[(2) - (3)].str)] = (yyvsp[(3) - (3)].str); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 182 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.parserBaseClass = (yyvsp[(2) - (2)].str); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 184 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.tokenStreamBaseClass = (yyvsp[(2) - (2)].str); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 185 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.hasLexer = true; lexerEnv = (yyvsp[(2) - (2)].str); if(KDevPG::globalSystem.lexerActions[lexerEnv].empty()) KDevPG::globalSystem.lexerActions[lexerEnv].push_back("qDebug() << \"error\"; exit(-1);"); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 186 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.hasLexer = true; lexerEnv = "start"; if(KDevPG::globalSystem.lexerActions["start"].empty()) KDevPG::globalSystem.lexerActions["start"].push_back("qDebug() << \"error\"; exit(-1);"); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 191 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[(1) - (6)].nfa));
              KDevPG::globalSystem.lexerActions[lexerEnv].push_back(
                QString((yyvsp[(2) - (6)].str)) + "KDevPG::Token& _t(Base::next()); _t.kind = ::" + KDevPG::globalSystem.ns + "::Parser::Token_" + (yyvsp[(3) - (6)].str) + ";\n"
              + "_t.begin = spos - Iterator::begin();\n"
              + "_t.end = plain() - Iterator::begin() - 1;\n"
              + "return _t;");
              KDevPG::globalSystem.regexpById[(yyvsp[(5) - (6)].str)] = (yyvsp[(1) - (6)].nfa);
            ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 200 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[(1) - (5)].nfa));
              KDevPG::globalSystem.lexerActions[lexerEnv].push_back(QString((yyvsp[(2) - (5)].str)) + "return next();");
              KDevPG::globalSystem.regexpById[(yyvsp[(4) - (5)].str)] = (yyvsp[(1) - (5)].nfa);
            ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 205 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[(1) - (4)].nfa));
              KDevPG::globalSystem.lexerActions[lexerEnv].push_back(
                QString((yyvsp[(2) - (4)].str)) + "KDevPG::Token& _t(Base::next()); _t.kind = ::" + KDevPG::globalSystem.ns + "::Parser::Token_" + (yyvsp[(3) - (4)].str) + ";\n"
              + "_t.begin = spos - Iterator::begin();\n"
              + "_t.end = plain() - Iterator::begin() - 1;\n"
              + "return _t;");
            ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 213 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[(1) - (3)].nfa));
              KDevPG::globalSystem.lexerActions[lexerEnv].push_back(QString((yyvsp[(2) - (3)].str)) + "return next();");
            ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 220 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) |= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 221 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 225 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (2)].nfa) &= *(yyvsp[(2) - (2)].nfa)); delete (yyvsp[(1) - (2)].nfa); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 226 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 230 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(**(yyvsp[(2) - (2)].nfa)); delete (yyvsp[(2) - (2)].nfa); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 231 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(2) - (3)].nfa)); delete (yyvsp[(2) - (3)].nfa); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 232 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::keyword(QString::fromUtf8((yyvsp[(1) - (1)].str)).replace("\\n", "\n"))); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 233 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { if(KDevPG::globalSystem.regexpById[(yyvsp[(2) - (3)].str)] == 0) { KDevPG::checkOut << "** ERROR: no named regexp " << (yyvsp[(2) - (3)].str) << endl; exit(-1); } (yyval.nfa) = new KDevPG::GNFA(*KDevPG::globalSystem.regexpById[(yyvsp[(2) - (3)].str)]); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 238 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PublicDeclaration, (yyvsp[(5) - (5)].str));    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 240 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ProtectedDeclaration, (yyvsp[(5) - (5)].str)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 242 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PrivateDeclaration, (yyvsp[(5) - (5)].str));   ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 244 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ConstructorCode, (yyvsp[(4) - (4)].str));      ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 246 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::DestructorCode, (yyvsp[(4) - (4)].str));       ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 250 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(1) - (1)].str),(yyvsp[(1) - (1)].str)); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 251 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(1) - (4)].str),(yyvsp[(3) - (4)].str)); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 252 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(3) - (3)].str),(yyvsp[(3) - (3)].str)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 254 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(3) - (6)].str),(yyvsp[(5) - (6)].str)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 258 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushRule((yyvsp[(1) - (2)].item)); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 259 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushRule((yyvsp[(2) - (3)].item)); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 263 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::globalSystem.zero(); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 264 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(2) - (3)].item); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 265 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 266 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 267 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::inlinedNonTerminal(KDevPG::globalSystem.pushSymbol((yyvsp[(2) - (2)].str))); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 268 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::annotation((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].item), false, (yyvsp[(2) - (3)].storageType)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 269 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::annotation((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].item), true, (yyvsp[(3) - (4)].storageType));  ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 273 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::nonTerminal(KDevPG::globalSystem.pushSymbol((yyvsp[(1) - (2)].str)), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 274 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::globalSystem.terminal((yyvsp[(1) - (1)].str)); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 279 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[(3) - (4)].item), 0);
        ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 284 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[(3) - (8)].item), (yyvsp[(7) - (8)].item));
        ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 290 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = const_cast<char*>(""); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 291 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 295 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 305 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember; ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 306 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;  ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 310 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::plus((yyvsp[(1) - (2)].item)); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 311 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::star((yyvsp[(1) - (2)].item)); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 312 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 313 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::alternative((yyvsp[(2) - (2)].item), KDevPG::globalSystem.zero()); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 317 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 319 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::CloneTree cl;
          (yyval.item) = KDevPG::cons((yyvsp[(1) - (3)].item), KDevPG::star(KDevPG::cons(cl.clone((yyvsp[(3) - (3)].item)), cl.clone((yyvsp[(1) - (3)].item)))));
        ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 323 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::action((yyvsp[(1) - (2)].item), (yyvsp[(2) - (2)].str)); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 324 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::action(0, (yyvsp[(1) - (1)].str)); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 328 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 329 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::cons((yyvsp[(1) - (2)].item), (yyvsp[(2) - (2)].item)); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 333 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 334 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::condition((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].item)); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 338 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 339 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::alternative((yyvsp[(1) - (3)].item), (yyvsp[(3) - (3)].item)); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 344 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.item) = KDevPG::evolve((yyvsp[(1) - (7)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (7)].str)),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(6) - (7)].item), (yyvsp[(4) - (7)].str));
        ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 349 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.item) = KDevPG::evolve((yyvsp[(1) - (7)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (7)].str)),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(5) - (7)].item), (yyvsp[(7) - (7)].str));
        ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 354 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::evolve((yyvsp[(1) - (4)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (4)].str)), 0, (yyvsp[(4) - (4)].str)); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 355 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { if(KDevPG::globalSystem.generateAst == false)
        {
          qFatal("Operator-expression-parsing is not yet supported with --no-ast!");
          exit(-1);
        }
        operatorNode = KDevPG::createNode<KDevPG::Model::OperatorItem>();
      ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 361 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.needOperatorStack = true; (yyval.item) = (yyvsp[(2) - (2)].item); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 365 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = const_cast<char*>(""); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 366 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 372 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { ; ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 377 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (9)].item);
              operatorNode->mName = (yyvsp[(5) - (9)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (9)].str)), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[(7) - (9)].item), (yyvsp[(9) - (9)].str));
            ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 385 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (9)].item);
              operatorNode->mName = (yyvsp[(5) - (9)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (9)].str)), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[(8) - (9)].item), (yyvsp[(6) - (9)].str));
            ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 393 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (6)].item);
              operatorNode->mName = (yyvsp[(5) - (6)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (6)].str)), 0, (yyvsp[(6) - (6)].str));
            ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 403 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushBin(*(yyvsp[(2) - (4)].operatorInformation), (yyvsp[(4) - (4)].str), (yyvsp[(3) - (4)].str)); delete (yyvsp[(2) - (4)].operatorInformation); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 404 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushTern(*(yyvsp[(2) - (5)].operatorInformation), *(yyvsp[(3) - (5)].operatorInformation), (yyvsp[(5) - (5)].str), (yyvsp[(4) - (5)].str)); delete (yyvsp[(2) - (5)].operatorInformation); delete (yyvsp[(3) - (5)].operatorInformation); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 405 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPre(*(yyvsp[(2) - (3)].operatorInformation), (yyvsp[(3) - (3)].str)); delete (yyvsp[(2) - (3)].operatorInformation); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 406 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPost(*(yyvsp[(2) - (3)].operatorInformation), "0", (yyvsp[(3) - (3)].str)); delete (yyvsp[(2) - (3)].operatorInformation); delete (yyvsp[(3) - (3)].str); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 407 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPost(*(yyvsp[(2) - (4)].operatorInformation), (yyvsp[(4) - (4)].str), (yyvsp[(3) - (4)].str)); delete (yyvsp[(2) - (4)].operatorInformation); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 408 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushParen(*(yyvsp[(2) - (3)].operatorInformation), *(yyvsp[(3) - (3)].operatorInformation)); delete (yyvsp[(2) - (3)].operatorInformation); delete (yyvsp[(3) - (3)].operatorInformation); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 412 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"0"; ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 413 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 414 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(2) - (2)].str); ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 418 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"1"; ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 419 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"0"; ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 420 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { uint yyleng = strlen((yyvsp[(2) - (2)].str));
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, (yyvsp[(2) - (2)].str));
                                     strcpy(tmp+yyleng+6-6+1, "?1:0)");
                                     (yyval.str) = tmp;
                                   ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 427 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { uint yyleng = strlen((yyvsp[(2) - (2)].str));
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, (yyvsp[(2) - (2)].str));
                                     strcpy(tmp+yyleng+6-6+1, "?0:1)");
                                     (yyval.str) = tmp;
                                   ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 437 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(3) - (4)].str)), (yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].str)); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 438 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(3) - (3)].str)), (yyvsp[(2) - (3)].str), ""); ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 439 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(1) - (2)].str)), "", (yyvsp[(2) - (2)].str)); ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 440 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(1) - (1)].str)), "", ""); ;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 444 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 446 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::Model::VariableDeclarationItem *last = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(1) - (2)].item);
          while (last->mNext != 0) {
            last = last->mNext;
          }
          last->mNext = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(2) - (2)].item);
          (yyval.item) = (yyvsp[(1) - (2)].item);
        ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 458 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (6)].declarationType), (yyvsp[(2) - (6)].storageType), (yyvsp[(3) - (6)].variableType), false, (yyvsp[(4) - (6)].str), (yyvsp[(6) - (6)].str)); ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 460 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (5)].declarationType), (yyvsp[(2) - (5)].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, false, (yyvsp[(4) - (5)].str), ""); ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 462 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (7)].declarationType), (yyvsp[(2) - (7)].storageType), (yyvsp[(3) - (7)].variableType), true, (yyvsp[(5) - (7)].str), (yyvsp[(7) - (7)].str)); ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 464 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (6)].declarationType), (yyvsp[(2) - (6)].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, true, (yyvsp[(5) - (6)].str), ""); ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 468 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationLocal;     ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 469 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationArgument;  ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 473 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember;    ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 474 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;     ;}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 478 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeNode;             ;}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 479 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeVariable;         ;}
    break;



/* Line 1455 of yacc.c  */
#line 2647 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"
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
#line 482 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"


