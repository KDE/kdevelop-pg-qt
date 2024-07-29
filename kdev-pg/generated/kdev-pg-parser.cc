/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C

    SPDX-FileCopyrightText: 1984, 1989-1990, 2000-2011 Free Software Foundation Inc.

    SPDX-License-Identifier: GPL-3.0-or-later WITH Bison-exception-2.2
*/

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
#define YYBISON_VERSION "2.5"

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

/* Line 268 of yacc.c  */
#line 2 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"

/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg.h"
#include "kdev-pg-clone-tree.h"
#include "kdev-pg-regexp.h"
#include "kdev-pg-unicode-loader.h"
#include "kdev-pg-checker.h"

#include <QFile>
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



/* Line 268 of yacc.c  */
#line 119 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"

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

/* Line 293 of yacc.c  */
#line 49 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"

    KDevPG::Model::Node *item;
    char* str;
    KDevPG::Model::VariableDeclarationItem::DeclarationType declarationType;
    KDevPG::Model::VariableDeclarationItem::StorageType     storageType;
    KDevPG::Model::VariableDeclarationItem::VariableType    variableType;
    KDevPG::Model::Operator                                *operatorInformation;
    KDevPG::GNFA                                           *nfa;



/* Line 293 of yacc.c  */
#line 236 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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

# define YYCOPY_NEEDED 1

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

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   394

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  89
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  178
/* YYNRULES -- Number of states.  */
#define YYNSTATES  350

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   324

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    86,     2,     2,    74,     2,
      71,    72,    79,    80,    84,     2,    83,     2,    85,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    88,    10,
       2,    87,     2,    77,    78,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    81,     2,    82,    75,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    73,     2,    76,     2,     2,     2,
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
      66,    67,    68,    69,    70
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
     143,   144,   149,   150,   155,   156,   161,   162,   164,   166,
     167,   171,   173,   177,   179,   183,   185,   188,   191,   193,
     196,   198,   202,   204,   207,   210,   212,   216,   220,   222,
     224,   226,   228,   229,   233,   235,   239,   241,   245,   247,
     250,   253,   255,   258,   260,   264,   266,   269,   272,   274,
     278,   282,   284,   286,   288,   290,   292,   293,   299,   305,
     311,   316,   321,   323,   328,   332,   339,   340,   344,   346,
     350,   352,   354,   357,   361,   366,   369,   371,   376,   385,
     386,   388,   390,   392,   394,   397,   400,   402,   405,   407,
     411,   414,   416,   418,   421,   423,   427,   429,   433,   441,
     449,   454,   455,   458,   459,   461,   464,   465,   475,   485,
     492,   497,   503,   507,   511,   516,   520,   522,   524,   527,
     529,   531,   534,   537,   542,   546,   549,   551,   553,   556,
     563,   569,   577,   584,   585,   587,   589,   591,   593
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      90,     0,    -1,    -1,   137,    91,    92,   123,   137,    -1,
      93,    -1,    92,    93,    -1,    14,   121,    -1,    14,    71,
      20,    72,     6,    -1,    15,   121,    -1,    15,    71,    20,
      72,     6,    -1,    11,   122,    10,    -1,    61,    -1,    62,
      -1,    60,     7,    -1,    12,     3,    10,    -1,    30,     7,
      -1,    35,     7,    -1,    13,     6,    -1,    36,     6,    -1,
      37,     7,    -1,    38,     7,    -1,    39,     7,    -1,    40,
       7,    -1,    59,     7,    -1,    41,     7,    -1,    43,     3,
       7,    -1,    42,     7,    -1,    44,     7,    -1,    -1,    58,
       7,    94,     4,    96,    10,    -1,    -1,    58,    95,     4,
      96,    10,    -1,    -1,   105,     4,     3,    10,    97,    96,
      -1,    -1,   105,   137,   104,    10,    98,    96,    -1,    -1,
     105,    67,    71,   105,    72,   137,   104,    10,    99,    96,
      -1,    -1,   105,    68,    71,   105,    72,   137,   104,    10,
     100,    96,    -1,    -1,    66,     6,   101,    96,    -1,    -1,
      69,     6,   102,    96,    -1,    -1,    70,     6,   103,    96,
      -1,    -1,     5,    -1,    64,    -1,    -1,   105,    73,   106,
      -1,   106,    -1,   106,    74,   107,    -1,   107,    -1,   108,
      75,   107,    -1,   108,    -1,    76,   108,    -1,    77,   108,
      -1,   109,    -1,   109,   110,    -1,   110,    -1,   110,    78,
     111,    -1,   111,    -1,   111,    79,    -1,   111,    80,    -1,
     112,    -1,    71,   105,    72,    -1,    81,   113,    82,    -1,
      83,    -1,     7,    -1,     8,    -1,    63,    -1,    -1,   113,
      73,   114,    -1,   114,    -1,   114,    74,   115,    -1,   115,
      -1,   116,    75,   115,    -1,   116,    -1,    76,   116,    -1,
      77,   116,    -1,   117,    -1,   117,   118,    -1,   118,    -1,
     118,    78,   119,    -1,   119,    -1,   119,    79,    -1,   119,
      80,    -1,   120,    -1,    71,   105,    72,    -1,    81,   113,
      82,    -1,    83,    -1,     7,    -1,    65,    -1,     8,    -1,
      63,    -1,    -1,    71,    16,    19,    72,     6,    -1,    71,
      18,    19,    72,     6,    -1,    71,    17,    19,    72,     6,
      -1,    71,    21,    72,     6,    -1,    71,    22,    72,     6,
      -1,     5,    -1,     5,    71,     7,    72,    -1,   122,    84,
       5,    -1,   122,    84,     5,    71,     7,    72,    -1,    -1,
     123,   135,    10,    -1,    85,    -1,    71,   134,    72,    -1,
     126,    -1,   125,    -1,    57,     3,    -1,   128,   129,   125,
      -1,    86,   128,   129,   125,    -1,     3,   127,    -1,     5,
      -1,    23,    71,   134,    72,    -1,    24,    71,   134,    72,
      25,    71,   134,    72,    -1,    -1,    26,    -1,     3,    -1,
      87,    -1,    88,    -1,   124,    80,    -1,   124,    79,    -1,
     124,    -1,    77,   124,    -1,   130,    -1,   131,    78,   124,
      -1,   131,     6,    -1,     6,    -1,   131,    -1,   132,   131,
      -1,   132,    -1,    77,     6,   132,    -1,   133,    -1,   134,
      73,   133,    -1,   134,     4,     3,     6,    81,   144,    82,
      -1,   134,     4,     3,    81,   144,    82,   137,    -1,   134,
       4,     3,   137,    -1,    -1,   136,   139,    -1,    -1,     6,
      -1,   140,   138,    -1,    -1,    49,   125,   138,    50,     3,
      81,   144,    82,   137,    -1,    49,   125,   138,    50,     3,
       6,    81,   144,    82,    -1,    49,   125,   138,    50,     3,
     137,    -1,    45,   143,   141,   142,    -1,    48,   143,   143,
     141,   142,    -1,    46,   143,   141,    -1,    47,   143,   141,
      -1,    47,   143,   141,   142,    -1,    56,   143,   143,    -1,
      85,    -1,     9,    -1,    55,     6,    -1,    51,    -1,    52,
      -1,    53,     6,    -1,    54,     6,    -1,    77,     6,     5,
       6,    -1,    77,     6,     5,    -1,     5,     6,    -1,     5,
      -1,   145,    -1,   144,   145,    -1,   146,   147,   148,     3,
      88,     3,    -1,   146,   147,    33,     3,    10,    -1,   146,
     147,   148,    86,     3,    88,     3,    -1,   146,   147,    33,
      86,     3,    10,    -1,    -1,    29,    -1,    27,    -1,    28,
      -1,    31,    -1,    34,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    94,    94,    94,   101,   102,   106,   108,   110,   112,
     114,   115,   129,   143,   170,   172,   174,   176,   178,   180,
     182,   184,   186,   188,   190,   192,   194,   196,   198,   198,
     199,   199,   204,   203,   207,   206,   217,   216,   249,   248,
     291,   290,   295,   294,   299,   298,   302,   306,   309,   312,
     316,   317,   321,   322,   326,   327,   331,   332,   333,   337,
     338,   342,   343,   347,   348,   349,   353,   354,   355,   356,
     357,   358,   373,   377,   378,   382,   383,   387,   388,   392,
     393,   394,   398,   399,   403,   404,   408,   409,   410,   414,
     415,   416,   417,   418,   441,   442,   457,   462,   464,   466,
     468,   470,   475,   476,   477,   478,   482,   484,   488,   489,
     490,   491,   492,   493,   494,   498,   499,   503,   508,   515,
     516,   520,   530,   531,   535,   536,   537,   538,   542,   543,
     548,   549,   553,   554,   558,   559,   563,   564,   568,   573,
     578,   580,   580,   590,   591,   596,   597,   601,   609,   617,
     628,   629,   630,   631,   632,   633,   637,   638,   639,   643,
     644,   645,   652,   662,   663,   664,   665,   669,   670,   682,
     684,   686,   688,   693,   694,   698,   699,   703,   704
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
  "T_PARSER_BITS_HEADER", "T_AST_HEADER", "T_LEXER_DECLARATION_HEADER",
  "T_LEXER_BITS_HEADER", "T_PARSER_BASE", "T_AST_BASE", "T_LEXER_BASE",
  "T_BIN", "T_PRE", "T_POST", "T_TERN", "T_LOPR", "T_ROPR", "T_LEFT_ASSOC",
  "T_RIGHT_ASSOC", "T_IS_LEFT_ASSOC", "T_IS_RIGHT_ASSOC", "T_PRIORITY",
  "T_PAREN", "T_INLINE", "T_LEXER", "T_INPUT_STREAM", "T_INPUT_ENCODING",
  "T_TABLE_LEXER", "T_SEQUENCE_LEXER", "T_NAMED_REGEXP", "T_CONTINUE",
  "T_RANGE", "T_FAIL", "T_LOOKAHEAD", "T_BARRIER", "T_ENTER_RULE_SET",
  "T_LEAVE_RULE_SET", "'('", "')'", "'|'", "'&'", "'^'", "'~'", "'?'",
  "'@'", "'*'", "'+'", "'['", "']'", "'.'", "','", "'0'", "'#'", "'='",
  "':'", "$accept", "system", "$@1", "declarations", "declaration", "$@2",
  "$@3", "lexer_declaration_rest", "$@4", "$@5", "$@6", "$@7", "$@8",
  "$@9", "$@10", "opt_lexer_action", "regexp", "regexp1", "regexp2",
  "regexp3", "regexp4", "regexp5", "regexp6", "regexp7", "aregexp",
  "aregexp1", "aregexp2", "aregexp3", "aregexp4", "aregexp5", "aregexp6",
  "aregexp7", "member_declaration_rest", "declared_tokens", "rules",
  "primary_item", "primary_atom", "try_item", "rule_arguments_opt", "name",
  "scope", "unary_item", "postfix_item", "item_sequence",
  "conditional_item", "option_item", "item", "$@11", "code_opt",
  "operatorDeclarations", "operatorRule", "operatorDeclaration",
  "priority", "assoc", "operator", "variableDeclarations",
  "variableDeclaration", "declarationType_opt", "storageType",
  "variableType", 0
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
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,    40,    41,   124,    38,    94,   126,    63,    64,    42,
      43,    91,    93,    46,    44,    48,    35,    61,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    89,    91,    90,    92,    92,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    94,    93,
      95,    93,    97,    96,    98,    96,    99,    96,   100,    96,
     101,    96,   102,    96,   103,    96,    96,   104,   104,   104,
     105,   105,   106,   106,   107,   107,   108,   108,   108,   109,
     109,   110,   110,   111,   111,   111,   112,   112,   112,   112,
     112,   112,   112,   113,   113,   114,   114,   115,   115,   116,
     116,   116,   117,   117,   118,   118,   119,   119,   119,   120,
     120,   120,   120,   120,   120,   120,   120,   121,   121,   121,
     121,   121,   122,   122,   122,   122,   123,   123,   124,   124,
     124,   124,   124,   124,   124,   125,   125,   126,   126,   127,
     127,   128,   129,   129,   130,   130,   130,   130,   131,   131,
     131,   131,   132,   132,   133,   133,   134,   134,   135,   135,
     135,   136,   135,   137,   137,   138,   138,   139,   139,   139,
     140,   140,   140,   140,   140,   140,   141,   141,   141,   142,
     142,   142,   142,   143,   143,   143,   143,   144,   144,   145,
     145,   145,   145,   146,   146,   147,   147,   148,   148
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     5,     1,     2,     2,     5,     2,     5,
       3,     1,     1,     2,     3,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     2,     2,     0,     6,
       0,     5,     0,     6,     0,     6,     0,    10,     0,    10,
       0,     4,     0,     4,     0,     4,     0,     1,     1,     0,
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

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
     143,   144,     0,     2,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,     0,     0,    11,    12,   106,     4,   102,
       0,     0,    17,     0,     6,     0,     8,    15,    16,    18,
      19,    20,    21,    22,    24,    26,     0,    27,    28,     0,
      23,    13,     5,   141,     0,    10,     0,    14,     0,     0,
       0,     0,     0,     0,     0,    25,     0,    72,   119,   116,
     131,     0,     0,     0,     0,     0,   108,     0,   126,   111,
     110,     0,   128,   132,   134,   136,     0,     0,     0,     3,
       0,   104,     0,     0,     0,     0,     0,     0,     0,    72,
      69,    70,    71,     0,     0,     0,    72,    72,    72,    96,
      68,     0,   143,    51,    53,    55,    58,    60,    62,    65,
     120,   115,     0,     0,   112,   131,     0,     0,   127,   121,
       0,   125,   124,   122,   123,     0,   130,     0,     0,   133,
       0,     0,   107,     0,   142,   103,     0,     0,     0,     0,
       7,   100,   101,     9,     0,    40,    42,    44,     0,    56,
      57,    92,    94,    95,    93,    72,    96,    96,    96,    91,
       0,    74,    76,    78,    81,    83,    85,    88,    31,     0,
       0,     0,    72,    49,    72,    72,    59,    72,    63,    64,
       0,     0,   109,   135,     0,   119,   113,   129,   143,   137,
     146,     0,    97,    99,    98,    29,    72,    72,    72,    66,
       0,    79,    80,     0,    96,    67,    96,    96,    82,    96,
      86,    87,     0,    72,    72,    50,    47,    48,     0,    52,
      54,    61,   117,     0,   114,   144,   173,   140,     0,     0,
       0,     0,     0,     0,   146,   105,    41,    43,    45,    89,
      90,    73,    75,    77,    84,    32,     0,     0,    34,     0,
     173,   174,   173,   167,     0,   166,     0,     0,     0,     0,
       0,     0,     0,   145,    72,   143,   143,    72,     0,   173,
     143,   168,   175,   176,     0,   165,     0,   157,     0,   156,
       0,   152,   153,     0,   155,   143,    33,    49,    49,    35,
       0,   138,   139,   177,     0,   178,     0,   164,   158,   159,
     160,     0,     0,   150,   154,     0,   144,   173,   149,     0,
       0,   118,     0,     0,     0,     0,   163,   161,   162,   151,
     173,   173,    36,    38,   170,     0,     0,     0,   173,   143,
      72,    72,   172,   169,     0,   148,   147,    37,    39,   171
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    27,    28,    66,    49,   111,   274,   277,
     340,   341,   206,   207,   208,   228,   112,   113,   114,   115,
     116,   117,   118,   119,   170,   171,   172,   173,   174,   175,
     176,   177,    34,    30,    53,    78,    79,    80,   121,    81,
     135,    82,    83,    84,    85,    86,    87,    88,     3,   243,
     144,   244,   290,   313,   267,   262,   263,   264,   284,   306
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -258
static const yytype_int16 yypact[] =
{
      12,  -258,    21,  -258,  -258,   236,    19,    28,    51,     9,
      15,    59,    63,    72,    91,   125,   133,   155,   164,   166,
     119,   169,   184,   200,   205,  -258,  -258,   236,  -258,    56,
      34,   142,  -258,   267,  -258,   283,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,   221,  -258,  -258,   139,
    -258,  -258,  -258,     6,   238,  -258,   194,  -258,   170,   206,
     295,   185,   230,   243,   244,  -258,   313,    65,    42,  -258,
     318,   248,   249,   319,    10,    22,  -258,   320,    88,  -258,
    -258,   116,  -258,    26,    17,  -258,    43,   311,   275,  -258,
     253,   255,   256,   257,   258,   321,   325,   326,   327,    65,
    -258,  -258,  -258,   328,   329,   330,   143,   143,   143,    98,
    -258,   331,   192,   263,  -258,   264,   130,   260,   136,  -258,
    -258,  -258,    10,    10,  -258,  -258,   145,    17,  -258,  -258,
     116,  -258,  -258,  -258,  -258,    50,  -258,    14,    14,    26,
     337,    10,  -258,    50,  -258,  -258,   335,   338,   339,   340,
    -258,  -258,  -258,  -258,   333,  -258,  -258,  -258,   162,  -258,
    -258,  -258,  -258,  -258,  -258,   143,    98,    98,    98,  -258,
     -34,   273,  -258,   274,   107,   270,   157,  -258,  -258,   347,
     280,   281,   143,     0,   143,   143,   260,   158,  -258,  -258,
     180,   182,  -258,    17,    50,   332,  -258,  -258,    20,  -258,
     108,   282,  -258,  -258,  -258,  -258,    65,    65,    65,  -258,
     191,  -258,  -258,   -17,    98,  -258,    98,    98,   270,   175,
    -258,  -258,   343,   143,   143,   263,  -258,  -258,   345,  -258,
    -258,   136,  -258,   334,  -258,   276,   336,  -258,     5,     5,
       5,     5,     5,   306,   108,  -258,  -258,  -258,  -258,  -258,
    -258,   273,  -258,  -258,   157,  -258,   195,   197,  -258,   289,
     336,  -258,     7,  -258,   254,   355,   356,    -1,    -1,    -1,
       5,     5,   360,  -258,    65,    12,    12,    65,    10,   115,
      12,  -258,  -258,  -258,   161,  -258,   359,  -258,   361,  -258,
     106,  -258,   106,    -1,  -258,    36,  -258,     0,     0,  -258,
     218,  -258,  -258,  -258,     4,  -258,    11,   362,  -258,  -258,
    -258,   363,   364,  -258,  -258,   106,   285,   336,  -258,   365,
     366,  -258,   367,   368,   284,   370,  -258,  -258,  -258,  -258,
     336,   118,  -258,  -258,  -258,   369,   371,   290,   120,    12,
      65,    65,  -258,  -258,   377,  -258,  -258,  -258,  -258,  -258
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -258,  -258,  -258,  -258,   354,  -258,  -258,   -97,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,    -5,  -103,   202,   122,   201,
    -258,   266,   196,  -258,   217,   172,    94,   146,  -258,   213,
     171,  -258,   378,  -258,  -258,   -14,   -10,  -258,  -258,   312,
     261,  -258,   -80,   265,   252,   -73,  -258,  -258,   -53,   150,
    -258,  -258,  -217,  -257,    -9,  -191,  -219,  -258,  -258,  -258
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -145
static const yytype_int16 yytable[] =
{
      89,   126,   154,   158,   139,   226,  -143,   322,   287,    68,
     265,    69,    70,    68,   324,    69,   125,    68,     1,    69,
      68,     4,    69,   125,    29,    68,   235,    69,   127,    71,
      72,    31,   136,    71,    72,   314,   261,    71,    72,   214,
      71,    72,   316,   281,    55,    71,    72,   140,   215,   190,
     191,   291,   292,   195,   288,    69,   214,    32,   329,   183,
     281,   128,   210,    73,   227,   250,    37,    73,   120,   279,
      38,    73,   100,   101,    73,   -46,   315,    74,    39,    73,
      33,    74,   266,    75,   289,    74,    35,    75,    74,   280,
     323,    76,    77,    74,   138,    76,    77,   325,    40,    76,
      77,   236,    76,    77,   137,   161,   162,    76,    77,   246,
     247,   248,   281,   139,   161,   162,   141,   317,    56,   281,
     256,   257,    46,   197,   128,   196,   331,    54,   102,  -121,
    -121,   103,    41,   200,   104,   105,   106,   100,   101,   338,
      42,   107,   108,    67,   261,   237,   109,   261,   110,   261,
     100,   101,    57,   238,   239,   240,   241,   309,   310,   311,
     312,   163,    43,   164,   242,   100,   101,   131,   132,   165,
     163,    44,   164,    45,   166,   167,    47,   296,   165,   168,
     299,   169,   161,   162,   234,   -96,   -96,   -96,   168,    92,
     169,    48,   303,   102,   304,   305,   179,   301,     1,    91,
     339,   106,   345,   133,   134,   300,   102,    50,   -72,   -72,
     -72,   109,    51,   110,   106,   188,   189,   192,   141,   107,
     108,   102,   297,   298,   109,    93,   110,   302,    65,   106,
     268,   269,   270,   271,   209,   182,   220,   221,   163,   109,
     164,   110,   318,   347,   348,    90,   165,     6,     7,     8,
       9,    10,   232,   141,   233,   141,   168,    95,   169,   180,
     181,   293,   294,   249,   182,   182,    11,   275,   182,   276,
     182,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,   282,   283,    58,    59,    60,   346,    61,    62,    63,
     321,   141,   319,   320,    22,    23,    24,    25,    26,    58,
      59,    60,    96,    64,    62,    63,   229,   230,   159,   160,
     252,   253,   211,   212,    94,    97,    98,    99,  -144,   122,
     123,   142,   124,   129,   143,   145,   146,   150,   147,   148,
     149,   151,   152,   153,   155,   156,   157,   184,   187,   185,
     198,   178,   201,   205,   202,   203,   204,   216,   219,   217,
     222,   223,   224,   255,   245,   258,   272,   260,   120,   259,
     278,   285,   286,   295,   307,   261,   330,   308,   326,   327,
     328,   335,   336,   337,   343,   332,   333,   334,   344,   342,
     349,    52,   186,   231,   225,   213,   251,   218,    36,   130,
     254,   194,   193,   199,   273
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-258))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_uint16 yycheck[] =
{
      53,    74,    99,   106,    84,     5,     0,     3,     9,     3,
       5,     5,     6,     3,     3,     5,     6,     3,     6,     5,
       3,     0,     5,     6,     5,     3,     6,     5,     6,    23,
      24,     3,     6,    23,    24,   292,    29,    23,    24,    73,
      23,    24,     6,   262,    10,    23,    24,     4,    82,   122,
     123,   268,   269,     3,    55,     5,    73,     6,   315,   112,
     279,    75,   165,    57,    64,    82,     7,    57,    26,   260,
       7,    57,     7,     8,    57,    10,   293,    71,     6,    57,
      71,    71,    77,    77,    85,    71,    71,    77,    71,    82,
      86,    85,    86,    71,    77,    85,    86,    86,     7,    85,
      86,    81,    85,    86,    78,     7,     8,    85,    86,   206,
     207,   208,   331,   193,     7,     8,    73,    81,    84,   338,
     223,   224,     3,   137,   138,   135,   317,    71,    63,    87,
      88,    66,     7,   143,    69,    70,    71,     7,     8,   330,
       7,    76,    77,     4,    29,   198,    81,    29,    83,    29,
       7,     8,    10,    45,    46,    47,    48,    51,    52,    53,
      54,    63,     7,    65,    56,     7,     8,    79,    80,    71,
      63,     7,    65,     7,    76,    77,     7,   274,    71,    81,
     277,    83,     7,     8,   194,    78,    79,    80,    81,    19,
      83,     7,    31,    63,    33,    34,     4,    82,     6,     5,
      82,    71,    82,    87,    88,   278,    63,     7,    78,    79,
      80,    81,     7,    83,    71,    79,    80,    72,    73,    76,
      77,    63,   275,   276,    81,    19,    83,   280,     7,    71,
     239,   240,   241,   242,    72,    73,    79,    80,    63,    81,
      65,    83,   295,   340,   341,     7,    71,    11,    12,    13,
      14,    15,    72,    73,    72,    73,    81,    72,    83,    67,
      68,   270,   271,    72,    73,    73,    30,    72,    73,    72,
      73,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    27,    28,    16,    17,    18,   339,    20,    21,    22,
      72,    73,   297,   298,    58,    59,    60,    61,    62,    16,
      17,    18,    72,    20,    21,    22,   184,   185,   107,   108,
     216,   217,   166,   167,    19,    72,    72,     4,     0,    71,
      71,    10,     3,     3,    49,    72,    71,     6,    72,    72,
      72,     6,     6,     6,     6,     6,     6,    74,    78,    75,
       3,    10,     7,    10,     6,     6,     6,    74,    78,    75,
       3,    71,    71,    10,    72,    10,    50,    81,    26,    25,
      71,     6,     6,     3,     5,    29,    81,     6,     6,     6,
       6,     3,    88,     3,     3,    10,    10,    10,    88,    10,
       3,    27,   116,   187,   182,   168,   214,   174,    10,    77,
     219,   130,   127,   141,   244
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    90,   137,     0,    91,    11,    12,    13,    14,
      15,    30,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    58,    59,    60,    61,    62,    92,    93,     5,
     122,     3,     6,    71,   121,    71,   121,     7,     7,     6,
       7,     7,     7,     7,     7,     7,     3,     7,     7,    95,
       7,     7,    93,   123,    71,    10,    84,    10,    16,    17,
      18,    20,    21,    22,    20,     7,    94,     4,     3,     5,
       6,    23,    24,    57,    71,    77,    85,    86,   124,   125,
     126,   128,   130,   131,   132,   133,   134,   135,   136,   137,
       7,     5,    19,    19,    19,    72,    72,    72,    72,     4,
       7,     8,    63,    66,    69,    70,    71,    76,    77,    81,
      83,    96,   105,   106,   107,   108,   109,   110,   111,   112,
      26,   127,    71,    71,     3,     6,   134,     6,   124,     3,
     128,    79,    80,    87,    88,   129,     6,    78,    77,   131,
       4,    73,    10,    49,   139,    72,    71,    72,    72,    72,
       6,     6,     6,     6,    96,     6,     6,     6,   105,   108,
     108,     7,     8,    63,    65,    71,    76,    77,    81,    83,
     113,   114,   115,   116,   117,   118,   119,   120,    10,     4,
      67,    68,    73,   137,    74,    75,   110,    78,    79,    80,
     134,   134,    72,   132,   129,     3,   125,   124,     3,   133,
     125,     7,     6,     6,     6,    10,   101,   102,   103,    72,
     105,   116,   116,   113,    73,    82,    74,    75,   118,    78,
      79,    80,     3,    71,    71,   106,     5,    64,   104,   107,
     107,   111,    72,    72,   125,     6,    81,   137,    45,    46,
      47,    48,    56,   138,   140,    72,    96,    96,    96,    72,
      82,   114,   115,   115,   119,    10,   105,   105,    10,    25,
      81,    29,   144,   145,   146,     5,    77,   143,   143,   143,
     143,   143,    50,   138,    97,    72,    72,    98,    71,   144,
      82,   145,    27,    28,   147,     6,     6,     9,    55,    85,
     141,   141,   141,   143,   143,     3,    96,   137,   137,    96,
     134,    82,   137,    31,    33,    34,   148,     5,     6,    51,
      52,    53,    54,   142,   142,   141,     6,    81,   137,   104,
     104,    72,     3,    86,     3,    86,     6,     6,     6,   142,
      81,   144,    10,    10,    10,     3,    88,     3,   144,    82,
      99,   100,    10,     3,    88,    82,   137,    96,    96,     3
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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
  if (yypact_value_is_default (yyn))
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
      if (yytable_value_is_error (yyn))
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

/* Line 1806 of yacc.c  */
#line 94 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.decl = (yyvsp[(1) - (1)].str); }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 97 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.bits += (yyvsp[(5) - (5)].str); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 107 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserClassMember((yyvsp[(2) - (2)].item)); }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 109 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.bits += (yyvsp[(5) - (5)].str); }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 111 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushLexerClassMember((yyvsp[(2) - (2)].item)); }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 113 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.lexerBits += (yyvsp[(5) - (5)].str); }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 116 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
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
      }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 130 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
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
      }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 144 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
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
          KDevPG::checkOut << "** ERROR unknown codec  ``" << (yyvsp[(2) - (2)].str) << "''" << Qt::endl;
          exit(-1);
        }
        KDevPG::GDFA::type = KDevPG::AutomatonType(base);
      }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 171 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.tokenStream = (yyvsp[(2) - (3)].str);           }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 173 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.exportMacro = (yyvsp[(2) - (2)].str);           }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 175 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.exportMacroHeader = (yyvsp[(2) - (2)].str);     }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 177 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.namespaceCode = (yyvsp[(2) - (2)].str);         }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 179 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.astCode = (yyvsp[(2) - (2)].str);               }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 181 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserDeclarationHeader((yyvsp[(2) - (2)].str)); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 183 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushParserBitsHeader((yyvsp[(2) - (2)].str)); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 185 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushAstHeader((yyvsp[(2) - (2)].str)); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 187 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushLexerDeclarationHeader((yyvsp[(2) - (2)].str)); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 189 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.inputStream = (yyvsp[(2) - (2)].str); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 191 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushLexerBitsHeader((yyvsp[(2) - (2)].str)); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 193 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.astBaseClasses[(yyvsp[(2) - (3)].str)] = (yyvsp[(3) - (3)].str); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 195 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.parserBaseClass = (yyvsp[(2) - (2)].str); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 197 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.lexerBaseClass = (yyvsp[(2) - (2)].str); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 198 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.hasLexer = true; lexerEnv = (yyvsp[(2) - (2)].str); if(KDevPG::globalSystem.lexerActions[lexerEnv].empty()) KDevPG::globalSystem.lexerActions[lexerEnv].push_back("qDebug() << \"error\"; exit(-1);"); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 199 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.hasLexer = true; KDevPG::loadUnicodeData(); lexerEnv = "start"; if(KDevPG::globalSystem.lexerActions["start"].empty()) KDevPG::globalSystem.lexerActions["start"].push_back("qDebug() << \"error\"; exit(-1);"); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 204 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.regexpById[(yyvsp[(3) - (4)].str)] = (yyvsp[(1) - (4)].nfa);
            }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 207 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              if((yyvsp[(1) - (4)].nfa)->acceptsEpsilon())
                KDevPG::checkOut << "** WARNING Lexer rule accepting the empty word at line " << yyLine << Qt::endl;
              else if((yyvsp[(1) - (4)].nfa)->isEmpty())
                KDevPG::checkOut << "** WARNING Lexer rule not accepting anything at line " << yyLine << Qt::endl;
              QString s = QString((yyvsp[(2) - (4)].str)) + QString(r);
              KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[(1) - (4)].nfa));
              KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
            }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 217 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              if((yyvsp[(1) - (8)].nfa)->acceptsEpsilon())
                KDevPG::checkOut << "** WARNING Lexer rule accepting the empty word at line " << yyLine << Qt::endl;
              else if((yyvsp[(1) - (8)].nfa)->isEmpty())
                KDevPG::checkOut << "** WARNING Lexer rule not accepting anything at line " << yyLine << Qt::endl;
              bool ignore = false;
              auto minLen = (yyvsp[(4) - (8)].nfa)->minLength(), maxLen = (yyvsp[(4) - (8)].nfa)->maxLength();
              if(minLen == 0)
              {
                KDevPG::checkOut << "** WARNING Lexer rule specifying epsilon-lookahead at line " << yyLine << ", ignore the lookahead." << Qt::endl;
                ignore = true;
              }
              else if(minLen != maxLen)
              {
                KDevPG::checkOut << "** WARNING Invalid lookahead (no fixed length) at line " << yyLine << " (min length: " << (minLen == -1 ? "none" : QString::number(minLen)) << ", max length: " << (maxLen == -2 ? "infinity" : (maxLen == -1 ? "none" : QString::number(maxLen))) << "), ignore the lookahead." << Qt::endl;
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
                QString s = "Iterator::plain() -= " + QString::number(minLen) + "; " + QString((yyvsp[(6) - (8)].str)) + QString(r);
                *(yyvsp[(1) - (8)].nfa) <<= *(yyvsp[(4) - (8)].nfa);
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[(1) - (8)].nfa));
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
            }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 249 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              if((yyvsp[(1) - (8)].nfa)->acceptsEpsilon())
                KDevPG::checkOut << "** WARNING Lexer rule accepting the empty word at line " << yyLine << Qt::endl;
              else if((yyvsp[(1) - (8)].nfa)->isEmpty())
                KDevPG::checkOut << "** WARNING Lexer rule not accepting anything at line " << yyLine << Qt::endl;
              bool ignore = false;
              auto minLen = (yyvsp[(4) - (8)].nfa)->minLength(), maxLen = (yyvsp[(4) - (8)].nfa)->maxLength();
              if(minLen == 0)
              {
                KDevPG::checkOut << "** WARNING Lexer rule specifying epsilon-barrier at line " << yyLine << ", ignore the barrier." << Qt::endl;
                ignore = true;
              }
              else if(minLen != maxLen)
              {
                KDevPG::checkOut << "** WARNING Invalid barrier (no fixed length) at line " << yyLine << " (min length: " << (minLen == -1 ? "none" : QString::number(minLen)) << ", max length: " << (maxLen == -2 ? "infinity" : (maxLen == -1 ? "none" : QString::number(maxLen))) << "), ignore the barrier." << Qt::endl;
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
                exclude <<= *(yyvsp[(4) - (8)].nfa);
                exclude <<= KDevPG::GNFA::anything();
                KDevPG::GNFA *staying = new KDevPG::GNFA(*(yyvsp[(1) - (8)].nfa));
                *staying ^= exclude;
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back(staying);
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(QString((yyvsp[(6) - (8)].str)) + QString(r));
                // barrier should not get read partially
                exclude <<= KDevPG::GNFA::anyChar();
                *(yyvsp[(1) - (8)].nfa) <<= *(yyvsp[(4) - (8)].nfa);
                *(yyvsp[(1) - (8)].nfa) ^= exclude;
                QString s = "Iterator::plain() -= " + QString::number(minLen) + "; " + QString((yyvsp[(6) - (8)].str)) + QString(r);
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[(1) - (8)].nfa));
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
            }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 291 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              KDevPG::globalSystem.lexerActions[lexerEnv][0] = QString((yyvsp[(2) - (2)].str));
            }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 295 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              KDevPG::globalSystem.enteringCode[lexerEnv] = QString((yyvsp[(2) - (2)].str));
            }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 299 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              KDevPG::globalSystem.leavingCode[lexerEnv] = QString((yyvsp[(2) - (2)].str));
            }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 306 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
        r = "\nlxRETURN(" + QString((yyvsp[(1) - (1)].str)) + ")\n";
      }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 309 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
        r = "\nlxCONTINUE;\n";
      }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 312 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { r = "\nlxSKIP\n"; }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 316 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) |= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 317 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 321 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) &= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 322 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 326 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) ^= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 327 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 331 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA((yyvsp[(2) - (2)].nfa)->negate()); delete (yyvsp[(2) - (2)].nfa); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 332 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(2) - (2)].nfa) |= KDevPG::GNFA::emptyWord()); delete (yyvsp[(2) - (2)].nfa); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 333 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 337 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (2)].nfa) <<= *(yyvsp[(2) - (2)].nfa)); delete (yyvsp[(1) - (2)].nfa); delete (yyvsp[(2) - (2)].nfa); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 338 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 342 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa)); KDevPG::GNFA *tmp = new KDevPG::GNFA(*(yyvsp[(3) - (3)].nfa) <<= *(yyvsp[(1) - (3)].nfa)); **tmp; *(yyval.nfa) <<= *tmp; delete tmp; delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 343 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 347 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(**(yyvsp[(1) - (2)].nfa)); delete (yyvsp[(1) - (2)].nfa); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 348 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (2)].nfa)); **(yyval.nfa); *(yyval.nfa) <<= *(yyvsp[(1) - (2)].nfa); delete (yyvsp[(1) - (2)].nfa); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 349 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 353 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(2) - (3)].nfa)); delete (yyvsp[(2) - (3)].nfa); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 354 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(2) - (3)].nfa); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 355 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::anyChar()); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 356 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::word(KDevPG::unescaped(QByteArray((yyvsp[(1) - (1)].str))))); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 357 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::word(KDevPG::unescaped(QByteArray((yyvsp[(1) - (1)].str))))); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 358 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
                              if(!KDevPG::globalSystem.regexpById.contains((yyvsp[(1) - (1)].str)))
                              {
                                KDevPG::checkOut << "** ERROR: no named regexp " << (yyvsp[(1) - (1)].str) << Qt::endl;
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
                            }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 373 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::emptyWord()); }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 377 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) |= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 378 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 382 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) &= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 383 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 387 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa) ^= *(yyvsp[(3) - (3)].nfa)); delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 388 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 392 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA((yyvsp[(2) - (2)].nfa)->negate()); delete (yyvsp[(2) - (2)].nfa); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 393 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(2) - (2)].nfa) |= KDevPG::GNFA::emptyWord()); delete (yyvsp[(2) - (2)].nfa); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 394 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 398 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (2)].nfa) |= *(yyvsp[(2) - (2)].nfa)); delete (yyvsp[(1) - (2)].nfa); delete (yyvsp[(2) - (2)].nfa); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 403 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (3)].nfa)); KDevPG::GNFA *tmp = new KDevPG::GNFA(*(yyvsp[(3) - (3)].nfa) <<= *(yyvsp[(1) - (3)].nfa)); **tmp; *(yyval.nfa) <<= *tmp; delete tmp; delete (yyvsp[(1) - (3)].nfa); delete (yyvsp[(3) - (3)].nfa); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 404 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 408 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(**(yyvsp[(1) - (2)].nfa)); delete (yyvsp[(1) - (2)].nfa); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 409 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(1) - (2)].nfa)); **(yyval.nfa); *(yyval.nfa) <<= *(yyvsp[(1) - (2)].nfa); delete (yyvsp[(1) - (2)].nfa); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 410 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(1) - (1)].nfa); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 414 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[(2) - (3)].nfa)); delete (yyvsp[(2) - (3)].nfa); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 415 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = (yyvsp[(2) - (3)].nfa); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 416 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::anyChar()); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 417 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::word(KDevPG::unescaped(QByteArray((yyvsp[(1) - (1)].str))))); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 418 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
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
    }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 441 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::collection(KDevPG::unescaped(QByteArray((yyvsp[(1) - (1)].str))))); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 442 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
                              if(!KDevPG::globalSystem.regexpById.contains((yyvsp[(1) - (1)].str)))
                              {
                                KDevPG::checkOut << "** ERROR: no named regexp " << (yyvsp[(1) - (1)].str) << Qt::endl;
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
                            }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 457 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::emptyWord()); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 463 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PublicDeclaration, (yyvsp[(5) - (5)].str));    }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 465 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ProtectedDeclaration, (yyvsp[(5) - (5)].str)); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 467 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PrivateDeclaration, (yyvsp[(5) - (5)].str));   }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 469 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ConstructorCode, (yyvsp[(4) - (4)].str));      }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 471 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::DestructorCode, (yyvsp[(4) - (4)].str));       }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 475 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(1) - (1)].str),(yyvsp[(1) - (1)].str)); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 476 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(1) - (4)].str),(yyvsp[(3) - (4)].str)); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 477 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(3) - (3)].str),(yyvsp[(3) - (3)].str)); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 479 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushTerminal((yyvsp[(3) - (6)].str),(yyvsp[(5) - (6)].str)); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 484 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.pushRule((yyvsp[(2) - (3)].item)); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 488 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::globalSystem.zero(); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 489 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(2) - (3)].item); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 490 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 491 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 492 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::inlinedNonTerminal(KDevPG::globalSystem.pushSymbol((yyvsp[(2) - (2)].str))); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 493 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::annotation((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].item), false, (yyvsp[(2) - (3)].storageType)); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 494 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::annotation((yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].item), true, (yyvsp[(3) - (4)].storageType));  }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 498 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::nonTerminal(KDevPG::globalSystem.pushSymbol((yyvsp[(1) - (2)].str)), (yyvsp[(2) - (2)].str)); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 499 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::globalSystem.terminal((yyvsp[(1) - (1)].str)); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 504 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[(3) - (4)].item), 0);
        }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 509 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[(3) - (8)].item), (yyvsp[(7) - (8)].item));
        }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 515 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = const_cast<char*>(""); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 516 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 520 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 530 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember; }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 531 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;  }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 535 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::plus((yyvsp[(1) - (2)].item)); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 536 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::star((yyvsp[(1) - (2)].item)); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 537 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 538 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::alternative((yyvsp[(2) - (2)].item), KDevPG::globalSystem.zero()); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 542 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 544 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::CloneTree cl;
          (yyval.item) = KDevPG::cons((yyvsp[(1) - (3)].item), KDevPG::star(KDevPG::cons(cl.clone((yyvsp[(3) - (3)].item)), cl.clone((yyvsp[(1) - (3)].item)))));
        }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 548 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::action((yyvsp[(1) - (2)].item), (yyvsp[(2) - (2)].str)); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 549 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::action(0, (yyvsp[(1) - (1)].str)); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 553 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 554 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::cons((yyvsp[(1) - (2)].item), (yyvsp[(2) - (2)].item)); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 558 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 559 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::condition((yyvsp[(2) - (3)].str), (yyvsp[(3) - (3)].item)); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 563 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 564 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::alternative((yyvsp[(1) - (3)].item), (yyvsp[(3) - (3)].item)); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 569 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.item) = KDevPG::evolve((yyvsp[(1) - (7)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (7)].str)),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(6) - (7)].item), (yyvsp[(4) - (7)].str));
        }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 574 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          (yyval.item) = KDevPG::evolve((yyvsp[(1) - (7)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (7)].str)),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(5) - (7)].item), (yyvsp[(7) - (7)].str));
        }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 579 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::evolve((yyvsp[(1) - (4)].item), KDevPG::globalSystem.pushSymbol((yyvsp[(3) - (4)].str)), 0, (yyvsp[(4) - (4)].str)); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 580 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { if(KDevPG::globalSystem.generateAst == false)
        {
          qFatal("Operator-expression-parsing is not yet supported with --no-ast!");
          exit(-1);
        }
        operatorNode = KDevPG::createNode<KDevPG::Model::OperatorItem>();
      }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 586 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { KDevPG::globalSystem.needOperatorStack = true; (yyval.item) = (yyvsp[(2) - (2)].item); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 590 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = const_cast<char*>(""); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 591 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 597 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { ; }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 602 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (9)].item);
              operatorNode->mName = (yyvsp[(5) - (9)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (9)].str)), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[(7) - (9)].item), (yyvsp[(9) - (9)].str));
            }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 610 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (9)].item);
              operatorNode->mName = (yyvsp[(5) - (9)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (9)].str)), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[(8) - (9)].item), (yyvsp[(6) - (9)].str));
            }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 618 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[(2) - (6)].item);
              operatorNode->mName = (yyvsp[(5) - (6)].str);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol((yyvsp[(5) - (6)].str)), 0, (yyvsp[(6) - (6)].str));
            }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 628 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushBin(*(yyvsp[(2) - (4)].operatorInformation), (yyvsp[(4) - (4)].str), (yyvsp[(3) - (4)].str)); free((yyvsp[(2) - (4)].operatorInformation)); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 629 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushTern(*(yyvsp[(2) - (5)].operatorInformation), *(yyvsp[(3) - (5)].operatorInformation), (yyvsp[(5) - (5)].str), (yyvsp[(4) - (5)].str)); free((yyvsp[(2) - (5)].operatorInformation)); free((yyvsp[(3) - (5)].operatorInformation)); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 630 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPre(*(yyvsp[(2) - (3)].operatorInformation), (yyvsp[(3) - (3)].str)); free((yyvsp[(2) - (3)].operatorInformation)); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 631 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPost(*(yyvsp[(2) - (3)].operatorInformation), "0", (yyvsp[(3) - (3)].str)); free((yyvsp[(2) - (3)].operatorInformation)); free((yyvsp[(3) - (3)].str)); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 632 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushPost(*(yyvsp[(2) - (4)].operatorInformation), (yyvsp[(4) - (4)].str), (yyvsp[(3) - (4)].str)); free((yyvsp[(2) - (4)].operatorInformation)); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 633 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { operatorNode->pushParen(*(yyvsp[(2) - (3)].operatorInformation), *(yyvsp[(3) - (3)].operatorInformation)); free((yyvsp[(2) - (3)].operatorInformation)); free((yyvsp[(3) - (3)].operatorInformation)); }
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 637 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"0"; }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 638 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(1) - (1)].str); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 639 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (yyvsp[(2) - (2)].str); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 643 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"1"; }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 644 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.str) = (char*)"0"; }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 645 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { uint yyleng = strlen((yyvsp[(2) - (2)].str));
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, (yyvsp[(2) - (2)].str));
                                     strcpy(tmp+yyleng+6-6+1, "?1:0)");
                                     (yyval.str) = tmp;
                                   }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 652 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { uint yyleng = strlen((yyvsp[(2) - (2)].str));
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, (yyvsp[(2) - (2)].str));
                                     strcpy(tmp+yyleng+6-6+1, "?0:1)");
                                     (yyval.str) = tmp;
                                   }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 662 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(3) - (4)].str)), (yyvsp[(2) - (4)].str), (yyvsp[(4) - (4)].str)); }
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 663 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(3) - (3)].str)), (yyvsp[(2) - (3)].str), ""); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 664 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(1) - (2)].str)), "", (yyvsp[(2) - (2)].str)); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 665 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal((yyvsp[(1) - (1)].str)), "", ""); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 669 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = (yyvsp[(1) - (1)].item); }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 671 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    {
          KDevPG::Model::VariableDeclarationItem *last = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(1) - (2)].item);
          while (last->mNext != 0) {
            last = last->mNext;
          }
          last->mNext = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[(2) - (2)].item);
          (yyval.item) = (yyvsp[(1) - (2)].item);
        }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 683 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (6)].declarationType), (yyvsp[(2) - (6)].storageType), (yyvsp[(3) - (6)].variableType), false, (yyvsp[(4) - (6)].str), (yyvsp[(6) - (6)].str)); }
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 685 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (5)].declarationType), (yyvsp[(2) - (5)].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, false, (yyvsp[(4) - (5)].str), ""); }
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 687 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (7)].declarationType), (yyvsp[(2) - (7)].storageType), (yyvsp[(3) - (7)].variableType), true, (yyvsp[(5) - (7)].str), (yyvsp[(7) - (7)].str)); }
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 689 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.item) = KDevPG::variableDeclaration((yyvsp[(1) - (6)].declarationType), (yyvsp[(2) - (6)].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, true, (yyvsp[(5) - (6)].str), ""); }
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 693 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationLocal;     }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 694 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationArgument;  }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 698 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember;    }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 699 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;     }
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 703 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeNode;             }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 704 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"
    { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeVariable;         }
    break;



/* Line 1806 of yacc.c  */
#line 3192 "/home/jonathan/gitKDE/kdevelop-pg-qt/build/kdev-pg/kdev-pg-parser.cc"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
      if (!yypact_value_is_default (yyn))
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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



/* Line 2067 of yacc.c  */
#line 707 "/home/jonathan/gitKDE/kdevelop-pg-qt/kdev-pg/kdev-pg-parser.yy"


