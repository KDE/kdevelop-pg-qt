/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

    SPDX-FileCopyrightText: 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation, Inc.

    SPDX-License-Identifier: GPL-3.0-or-later WITH Bison-exception-2.2
*/

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "kdev-pg-parser.yy"

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

KDevPG::Model::OperatorItem *operatorNode = nullptr;
QString r;


#line 105 "kdev-pg-parser.cc"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "kdev-pg-parser.hh"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_IDENTIFIER = 3,               /* T_IDENTIFIER  */
  YYSYMBOL_T_ARROW = 4,                    /* T_ARROW  */
  YYSYMBOL_T_TERMINAL = 5,                 /* T_TERMINAL  */
  YYSYMBOL_T_CODE = 6,                     /* T_CODE  */
  YYSYMBOL_T_STRING = 7,                   /* T_STRING  */
  YYSYMBOL_T_UNQUOTED_STRING = 8,          /* T_UNQUOTED_STRING  */
  YYSYMBOL_T_NUMBER = 9,                   /* T_NUMBER  */
  YYSYMBOL_10_ = 10,                       /* ';'  */
  YYSYMBOL_T_TOKEN_DECLARATION = 11,       /* T_TOKEN_DECLARATION  */
  YYSYMBOL_T_TOKEN_STREAM_DECLARATION = 12, /* T_TOKEN_STREAM_DECLARATION  */
  YYSYMBOL_T_NAMESPACE_DECLARATION = 13,   /* T_NAMESPACE_DECLARATION  */
  YYSYMBOL_T_PARSERCLASS_DECLARATION = 14, /* T_PARSERCLASS_DECLARATION  */
  YYSYMBOL_T_LEXERCLASS_DECLARATION = 15,  /* T_LEXERCLASS_DECLARATION  */
  YYSYMBOL_T_PUBLIC = 16,                  /* T_PUBLIC  */
  YYSYMBOL_T_PRIVATE = 17,                 /* T_PRIVATE  */
  YYSYMBOL_T_PROTECTED = 18,               /* T_PROTECTED  */
  YYSYMBOL_T_DECLARATION = 19,             /* T_DECLARATION  */
  YYSYMBOL_T_BITS = 20,                    /* T_BITS  */
  YYSYMBOL_T_CONSTRUCTOR = 21,             /* T_CONSTRUCTOR  */
  YYSYMBOL_T_DESTRUCTOR = 22,              /* T_DESTRUCTOR  */
  YYSYMBOL_T_TRY_RECOVER = 23,             /* T_TRY_RECOVER  */
  YYSYMBOL_T_TRY_ROLLBACK = 24,            /* T_TRY_ROLLBACK  */
  YYSYMBOL_T_CATCH = 25,                   /* T_CATCH  */
  YYSYMBOL_T_RULE_ARGUMENTS = 26,          /* T_RULE_ARGUMENTS  */
  YYSYMBOL_T_MEMBER = 27,                  /* T_MEMBER  */
  YYSYMBOL_T_TEMPORARY = 28,               /* T_TEMPORARY  */
  YYSYMBOL_T_ARGUMENT = 29,                /* T_ARGUMENT  */
  YYSYMBOL_T_EXPORT_MACRO = 30,            /* T_EXPORT_MACRO  */
  YYSYMBOL_T_NODE = 31,                    /* T_NODE  */
  YYSYMBOL_T_NODE_SEQUENCE = 32,           /* T_NODE_SEQUENCE  */
  YYSYMBOL_T_TOKEN = 33,                   /* T_TOKEN  */
  YYSYMBOL_T_VARIABLE = 34,                /* T_VARIABLE  */
  YYSYMBOL_T_EXPORT_MACRO_HEADER = 35,     /* T_EXPORT_MACRO_HEADER  */
  YYSYMBOL_T_AST_DECLARATION = 36,         /* T_AST_DECLARATION  */
  YYSYMBOL_T_PARSER_DECLARATION_HEADER = 37, /* T_PARSER_DECLARATION_HEADER  */
  YYSYMBOL_T_PARSER_BITS_HEADER = 38,      /* T_PARSER_BITS_HEADER  */
  YYSYMBOL_T_AST_HEADER = 39,              /* T_AST_HEADER  */
  YYSYMBOL_T_LEXER_DECLARATION_HEADER = 40, /* T_LEXER_DECLARATION_HEADER  */
  YYSYMBOL_T_LEXER_BITS_HEADER = 41,       /* T_LEXER_BITS_HEADER  */
  YYSYMBOL_T_PARSER_BASE = 42,             /* T_PARSER_BASE  */
  YYSYMBOL_T_AST_BASE = 43,                /* T_AST_BASE  */
  YYSYMBOL_T_LEXER_BASE = 44,              /* T_LEXER_BASE  */
  YYSYMBOL_T_BIN = 45,                     /* T_BIN  */
  YYSYMBOL_T_PRE = 46,                     /* T_PRE  */
  YYSYMBOL_T_POST = 47,                    /* T_POST  */
  YYSYMBOL_T_TERN = 48,                    /* T_TERN  */
  YYSYMBOL_T_LOPR = 49,                    /* T_LOPR  */
  YYSYMBOL_T_ROPR = 50,                    /* T_ROPR  */
  YYSYMBOL_T_LEFT_ASSOC = 51,              /* T_LEFT_ASSOC  */
  YYSYMBOL_T_RIGHT_ASSOC = 52,             /* T_RIGHT_ASSOC  */
  YYSYMBOL_T_IS_LEFT_ASSOC = 53,           /* T_IS_LEFT_ASSOC  */
  YYSYMBOL_T_IS_RIGHT_ASSOC = 54,          /* T_IS_RIGHT_ASSOC  */
  YYSYMBOL_T_PRIORITY = 55,                /* T_PRIORITY  */
  YYSYMBOL_T_PAREN = 56,                   /* T_PAREN  */
  YYSYMBOL_T_INLINE = 57,                  /* T_INLINE  */
  YYSYMBOL_T_LEXER = 58,                   /* T_LEXER  */
  YYSYMBOL_T_INPUT_STREAM = 59,            /* T_INPUT_STREAM  */
  YYSYMBOL_T_INPUT_ENCODING = 60,          /* T_INPUT_ENCODING  */
  YYSYMBOL_T_TABLE_LEXER = 61,             /* T_TABLE_LEXER  */
  YYSYMBOL_T_SEQUENCE_LEXER = 62,          /* T_SEQUENCE_LEXER  */
  YYSYMBOL_T_NAMED_REGEXP = 63,            /* T_NAMED_REGEXP  */
  YYSYMBOL_T_CONTINUE = 64,                /* T_CONTINUE  */
  YYSYMBOL_T_RANGE = 65,                   /* T_RANGE  */
  YYSYMBOL_T_FAIL = 66,                    /* T_FAIL  */
  YYSYMBOL_T_LOOKAHEAD = 67,               /* T_LOOKAHEAD  */
  YYSYMBOL_T_BARRIER = 68,                 /* T_BARRIER  */
  YYSYMBOL_T_ENTER_RULE_SET = 69,          /* T_ENTER_RULE_SET  */
  YYSYMBOL_T_LEAVE_RULE_SET = 70,          /* T_LEAVE_RULE_SET  */
  YYSYMBOL_71_ = 71,                       /* '('  */
  YYSYMBOL_72_ = 72,                       /* ')'  */
  YYSYMBOL_73_ = 73,                       /* '|'  */
  YYSYMBOL_74_ = 74,                       /* '&'  */
  YYSYMBOL_75_ = 75,                       /* '^'  */
  YYSYMBOL_76_ = 76,                       /* '~'  */
  YYSYMBOL_77_ = 77,                       /* '?'  */
  YYSYMBOL_78_ = 78,                       /* '@'  */
  YYSYMBOL_79_ = 79,                       /* '*'  */
  YYSYMBOL_80_ = 80,                       /* '+'  */
  YYSYMBOL_81_ = 81,                       /* '['  */
  YYSYMBOL_82_ = 82,                       /* ']'  */
  YYSYMBOL_83_ = 83,                       /* '.'  */
  YYSYMBOL_84_ = 84,                       /* ','  */
  YYSYMBOL_85_0_ = 85,                     /* '0'  */
  YYSYMBOL_86_ = 86,                       /* '#'  */
  YYSYMBOL_87_ = 87,                       /* '='  */
  YYSYMBOL_88_ = 88,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 89,                  /* $accept  */
  YYSYMBOL_system = 90,                    /* system  */
  YYSYMBOL_91_1 = 91,                      /* $@1  */
  YYSYMBOL_declarations = 92,              /* declarations  */
  YYSYMBOL_declaration = 93,               /* declaration  */
  YYSYMBOL_94_2 = 94,                      /* $@2  */
  YYSYMBOL_95_3 = 95,                      /* $@3  */
  YYSYMBOL_lexer_declaration_rest = 96,    /* lexer_declaration_rest  */
  YYSYMBOL_97_4 = 97,                      /* $@4  */
  YYSYMBOL_98_5 = 98,                      /* $@5  */
  YYSYMBOL_99_6 = 99,                      /* $@6  */
  YYSYMBOL_100_7 = 100,                    /* $@7  */
  YYSYMBOL_101_8 = 101,                    /* $@8  */
  YYSYMBOL_102_9 = 102,                    /* $@9  */
  YYSYMBOL_103_10 = 103,                   /* $@10  */
  YYSYMBOL_opt_lexer_action = 104,         /* opt_lexer_action  */
  YYSYMBOL_regexp = 105,                   /* regexp  */
  YYSYMBOL_regexp1 = 106,                  /* regexp1  */
  YYSYMBOL_regexp2 = 107,                  /* regexp2  */
  YYSYMBOL_regexp3 = 108,                  /* regexp3  */
  YYSYMBOL_regexp4 = 109,                  /* regexp4  */
  YYSYMBOL_regexp5 = 110,                  /* regexp5  */
  YYSYMBOL_regexp6 = 111,                  /* regexp6  */
  YYSYMBOL_regexp7 = 112,                  /* regexp7  */
  YYSYMBOL_aregexp = 113,                  /* aregexp  */
  YYSYMBOL_aregexp1 = 114,                 /* aregexp1  */
  YYSYMBOL_aregexp2 = 115,                 /* aregexp2  */
  YYSYMBOL_aregexp3 = 116,                 /* aregexp3  */
  YYSYMBOL_aregexp4 = 117,                 /* aregexp4  */
  YYSYMBOL_aregexp5 = 118,                 /* aregexp5  */
  YYSYMBOL_aregexp6 = 119,                 /* aregexp6  */
  YYSYMBOL_aregexp7 = 120,                 /* aregexp7  */
  YYSYMBOL_member_declaration_rest = 121,  /* member_declaration_rest  */
  YYSYMBOL_declared_tokens = 122,          /* declared_tokens  */
  YYSYMBOL_rules = 123,                    /* rules  */
  YYSYMBOL_primary_item = 124,             /* primary_item  */
  YYSYMBOL_primary_atom = 125,             /* primary_atom  */
  YYSYMBOL_try_item = 126,                 /* try_item  */
  YYSYMBOL_rule_arguments_opt = 127,       /* rule_arguments_opt  */
  YYSYMBOL_name = 128,                     /* name  */
  YYSYMBOL_scope = 129,                    /* scope  */
  YYSYMBOL_unary_item = 130,               /* unary_item  */
  YYSYMBOL_postfix_item = 131,             /* postfix_item  */
  YYSYMBOL_item_sequence = 132,            /* item_sequence  */
  YYSYMBOL_conditional_item = 133,         /* conditional_item  */
  YYSYMBOL_option_item = 134,              /* option_item  */
  YYSYMBOL_item = 135,                     /* item  */
  YYSYMBOL_136_11 = 136,                   /* $@11  */
  YYSYMBOL_code_opt = 137,                 /* code_opt  */
  YYSYMBOL_operatorDeclarations = 138,     /* operatorDeclarations  */
  YYSYMBOL_operatorRule = 139,             /* operatorRule  */
  YYSYMBOL_operatorDeclaration = 140,      /* operatorDeclaration  */
  YYSYMBOL_priority = 141,                 /* priority  */
  YYSYMBOL_assoc = 142,                    /* assoc  */
  YYSYMBOL_operator = 143,                 /* operator  */
  YYSYMBOL_variableDeclarations = 144,     /* variableDeclarations  */
  YYSYMBOL_variableDeclaration = 145,      /* variableDeclaration  */
  YYSYMBOL_declarationType_opt = 146,      /* declarationType_opt  */
  YYSYMBOL_storageType = 147,              /* storageType  */
  YYSYMBOL_variableType = 148              /* variableType  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
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
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  350

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    81,    81,    81,    88,    89,    93,    95,    97,    99,
     101,   102,   116,   130,   157,   159,   161,   163,   165,   167,
     169,   171,   173,   175,   177,   179,   181,   183,   185,   185,
     186,   186,   191,   190,   194,   193,   204,   203,   236,   235,
     278,   277,   282,   281,   286,   285,   289,   293,   296,   299,
     303,   304,   308,   309,   313,   314,   318,   319,   320,   324,
     325,   329,   330,   334,   335,   336,   340,   341,   342,   343,
     344,   345,   360,   364,   365,   369,   370,   374,   375,   379,
     380,   381,   385,   386,   390,   391,   395,   396,   397,   401,
     402,   403,   404,   405,   428,   429,   444,   449,   451,   453,
     455,   457,   462,   463,   464,   465,   470,   471,   475,   476,
     477,   478,   479,   480,   481,   485,   486,   490,   495,   502,
     503,   507,   517,   518,   522,   523,   524,   525,   529,   530,
     535,   536,   540,   541,   545,   546,   550,   551,   555,   560,
     565,   567,   567,   577,   578,   583,   584,   588,   596,   604,
     615,   616,   617,   618,   619,   620,   624,   625,   626,   630,
     631,   632,   639,   649,   650,   651,   652,   656,   657,   669,
     671,   673,   675,   680,   681,   685,   686,   690,   691
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_IDENTIFIER",
  "T_ARROW", "T_TERMINAL", "T_CODE", "T_STRING", "T_UNQUOTED_STRING",
  "T_NUMBER", "';'", "T_TOKEN_DECLARATION", "T_TOKEN_STREAM_DECLARATION",
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
  "variableType", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-258)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-145)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
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

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
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

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     2,     5,    27,    28,    66,    49,   111,   274,   277,
     340,   341,   206,   207,   208,   228,   112,   113,   114,   115,
     116,   117,   118,   119,   170,   171,   172,   173,   174,   175,
     176,   177,    34,    30,    53,    78,    79,    80,   121,    81,
     135,    82,    83,    84,    85,    86,    87,    88,     3,   243,
     144,   244,   290,   313,   267,   262,   263,   264,   284,   306
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
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

static const yytype_int16 yycheck[] =
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
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

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
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


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 81 "kdev-pg-parser.yy"
               { KDevPG::globalSystem.decl = QString::fromUtf8((yyvsp[0].str)); }
#line 1504 "kdev-pg-parser.cc"
    break;

  case 3: /* system: code_opt $@1 declarations rules code_opt  */
#line 84 "kdev-pg-parser.yy"
               { KDevPG::globalSystem.bits += QLatin1StringView((yyvsp[0].str)); }
#line 1510 "kdev-pg-parser.cc"
    break;

  case 6: /* declaration: T_PARSERCLASS_DECLARATION member_declaration_rest  */
#line 94 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.pushParserClassMember((yyvsp[0].item)); }
#line 1516 "kdev-pg-parser.cc"
    break;

  case 7: /* declaration: T_PARSERCLASS_DECLARATION '(' T_BITS ')' T_CODE  */
#line 96 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.bits += QLatin1StringView((yyvsp[0].str)); }
#line 1522 "kdev-pg-parser.cc"
    break;

  case 8: /* declaration: T_LEXERCLASS_DECLARATION member_declaration_rest  */
#line 98 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.pushLexerClassMember((yyvsp[0].item)); }
#line 1528 "kdev-pg-parser.cc"
    break;

  case 9: /* declaration: T_LEXERCLASS_DECLARATION '(' T_BITS ')' T_CODE  */
#line 100 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.lexerBits += QLatin1StringView((yyvsp[0].str)); }
#line 1534 "kdev-pg-parser.cc"
    break;

  case 11: /* declaration: T_TABLE_LEXER  */
#line 103 "kdev-pg-parser.yy"
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
#line 1552 "kdev-pg-parser.cc"
    break;

  case 12: /* declaration: T_SEQUENCE_LEXER  */
#line 117 "kdev-pg-parser.yy"
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
#line 1570 "kdev-pg-parser.cc"
    break;

  case 13: /* declaration: T_INPUT_ENCODING T_STRING  */
#line 131 "kdev-pg-parser.yy"
      {
        if(KDevPG::globalSystem.hasLexer)
        { KDevPG::checkOut << "** ERROR you have to specify the lexer-type (%sequence_lexer) before any lexer rules"; exit(-1); }
        int base = (KDevPG::GDFA::type / 4) * 4; // warning: magic constant: number of different codecs
        QString str = QString::fromUtf8((yyvsp[0].str));
        str = str.toLower();
        str.remove(QLatin1Char('-'));
        if(str == QLatin1String("ascii"))
          /* base += 0*/;
        else if(str == QLatin1String("latin1"))
          base += 1;
        else if(str == QLatin1String("utf8"))
          base += 2;
        else if(str == QLatin1String("ucs2"))
          base += 3;
        else if(str == QLatin1String("utf16"))
          base += 4;
        else if(str == QLatin1String("ucs4") || str == QLatin1String("utf32"))
          base += 5;
        else
        {
          KDevPG::checkOut << "** ERROR unknown codec  ``" << (yyvsp[0].str) << "''" << Qt::endl;
          exit(-1);
        }
        KDevPG::GDFA::type = KDevPG::AutomatonType(base);
      }
#line 1601 "kdev-pg-parser.cc"
    break;

  case 14: /* declaration: T_TOKEN_STREAM_DECLARATION T_IDENTIFIER ';'  */
#line 158 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.tokenStream = QString::fromUtf8((yyvsp[-1].str));           }
#line 1607 "kdev-pg-parser.cc"
    break;

  case 15: /* declaration: T_EXPORT_MACRO T_STRING  */
#line 160 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.exportMacro = QString::fromUtf8((yyvsp[0].str));           }
#line 1613 "kdev-pg-parser.cc"
    break;

  case 16: /* declaration: T_EXPORT_MACRO_HEADER T_STRING  */
#line 162 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.exportMacroHeader = QString::fromUtf8((yyvsp[0].str));     }
#line 1619 "kdev-pg-parser.cc"
    break;

  case 17: /* declaration: T_NAMESPACE_DECLARATION T_CODE  */
#line 164 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.namespaceCode = QString::fromUtf8((yyvsp[0].str));         }
#line 1625 "kdev-pg-parser.cc"
    break;

  case 18: /* declaration: T_AST_DECLARATION T_CODE  */
#line 166 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.astCode = QString::fromUtf8((yyvsp[0].str));               }
#line 1631 "kdev-pg-parser.cc"
    break;

  case 19: /* declaration: T_PARSER_DECLARATION_HEADER T_STRING  */
#line 168 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.pushParserDeclarationHeader(QString::fromUtf8((yyvsp[0].str))); }
#line 1637 "kdev-pg-parser.cc"
    break;

  case 20: /* declaration: T_PARSER_BITS_HEADER T_STRING  */
#line 170 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.pushParserBitsHeader(QString::fromUtf8((yyvsp[0].str))); }
#line 1643 "kdev-pg-parser.cc"
    break;

  case 21: /* declaration: T_AST_HEADER T_STRING  */
#line 172 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.pushAstHeader(QString::fromUtf8((yyvsp[0].str))); }
#line 1649 "kdev-pg-parser.cc"
    break;

  case 22: /* declaration: T_LEXER_DECLARATION_HEADER T_STRING  */
#line 174 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.pushLexerDeclarationHeader(QString::fromUtf8((yyvsp[0].str))); }
#line 1655 "kdev-pg-parser.cc"
    break;

  case 23: /* declaration: T_INPUT_STREAM T_STRING  */
#line 176 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.inputStream = QString::fromUtf8((yyvsp[0].str)); }
#line 1661 "kdev-pg-parser.cc"
    break;

  case 24: /* declaration: T_LEXER_BITS_HEADER T_STRING  */
#line 178 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.pushLexerBitsHeader(QString::fromUtf8((yyvsp[0].str))); }
#line 1667 "kdev-pg-parser.cc"
    break;

  case 25: /* declaration: T_AST_BASE T_IDENTIFIER T_STRING  */
#line 180 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.astBaseClasses[QString::fromUtf8((yyvsp[-1].str))] = QString::fromUtf8((yyvsp[0].str)); }
#line 1673 "kdev-pg-parser.cc"
    break;

  case 26: /* declaration: T_PARSER_BASE T_STRING  */
#line 182 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.parserBaseClass = QString::fromUtf8((yyvsp[0].str)); }
#line 1679 "kdev-pg-parser.cc"
    break;

  case 27: /* declaration: T_LEXER_BASE T_STRING  */
#line 184 "kdev-pg-parser.yy"
        { KDevPG::globalSystem.lexerBaseClass = QString::fromUtf8((yyvsp[0].str)); }
#line 1685 "kdev-pg-parser.cc"
    break;

  case 28: /* $@2: %empty  */
#line 185 "kdev-pg-parser.yy"
                       { KDevPG::globalSystem.hasLexer = true; lexerEnv = QString::fromUtf8((yyvsp[0].str)); if(KDevPG::globalSystem.lexerActions[lexerEnv].empty()) KDevPG::globalSystem.lexerActions[lexerEnv].push_back(QStringLiteral("qDebug() << \"error\"; exit(-1);")); }
#line 1691 "kdev-pg-parser.cc"
    break;

  case 30: /* $@3: %empty  */
#line 186 "kdev-pg-parser.yy"
              { KDevPG::globalSystem.hasLexer = true; KDevPG::loadUnicodeData(); lexerEnv = QStringLiteral("start"); if(KDevPG::globalSystem.lexerActions[QStringLiteral("start")].empty()) KDevPG::globalSystem.lexerActions[QStringLiteral("start")].push_back(QStringLiteral("qDebug() << \"error\"; exit(-1);")); }
#line 1697 "kdev-pg-parser.cc"
    break;

  case 32: /* $@4: %empty  */
#line 191 "kdev-pg-parser.yy"
            { KDevPG::globalSystem.regexpById[QString::fromUtf8((yyvsp[-1].str))] = (yyvsp[-3].nfa);
            }
#line 1704 "kdev-pg-parser.cc"
    break;

  case 34: /* $@5: %empty  */
#line 194 "kdev-pg-parser.yy"
            {
              if((yyvsp[-3].nfa)->acceptsEpsilon())
                KDevPG::checkOut << "** WARNING Lexer rule accepting the empty word at line " << yyLine << Qt::endl;
              else if((yyvsp[-3].nfa)->isEmpty())
                KDevPG::checkOut << "** WARNING Lexer rule not accepting anything at line " << yyLine << Qt::endl;
              QString s = QLatin1StringView((yyvsp[-2].str)) + r;
              KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[-3].nfa));
              KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
            }
#line 1718 "kdev-pg-parser.cc"
    break;

  case 36: /* $@6: %empty  */
#line 204 "kdev-pg-parser.yy"
            {
              if((yyvsp[-7].nfa)->acceptsEpsilon())
                KDevPG::checkOut << "** WARNING Lexer rule accepting the empty word at line " << yyLine << Qt::endl;
              else if((yyvsp[-7].nfa)->isEmpty())
                KDevPG::checkOut << "** WARNING Lexer rule not accepting anything at line " << yyLine << Qt::endl;
              bool ignore = false;
              auto minLen = (yyvsp[-4].nfa)->minLength(), maxLen = (yyvsp[-4].nfa)->maxLength();
              if(minLen == 0)
              {
                KDevPG::checkOut << "** WARNING Lexer rule specifying epsilon-lookahead at line " << yyLine << ", ignore the lookahead." << Qt::endl;
                ignore = true;
              }
              else if(minLen != maxLen)
              {
                KDevPG::checkOut << "** WARNING Invalid lookahead (no fixed length) at line " << yyLine << " (min length: " << (minLen == -1 ? QStringLiteral("none") : QString::number(minLen)) << ", max length: " << (maxLen == -2 ? QStringLiteral("infinity") : (maxLen == -1 ? QStringLiteral("none") : QString::number(maxLen))) << "), ignore the lookahead." << Qt::endl;
                ignore = true;
              }
              if(ignore)
              {
                QString s = QLatin1StringView((yyvsp[-2].str)) + r;
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[-7].nfa));
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
              else
              {
                QString s = QLatin1String("Iterator::plain() -= ") + QString::number(minLen) + QLatin1String("; ") + QLatin1StringView((yyvsp[-2].str)) + r;
                *(yyvsp[-7].nfa) <<= *(yyvsp[-4].nfa);
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[-7].nfa));
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
            }
#line 1754 "kdev-pg-parser.cc"
    break;

  case 38: /* $@7: %empty  */
#line 236 "kdev-pg-parser.yy"
            {
              if((yyvsp[-7].nfa)->acceptsEpsilon())
                KDevPG::checkOut << "** WARNING Lexer rule accepting the empty word at line " << yyLine << Qt::endl;
              else if((yyvsp[-7].nfa)->isEmpty())
                KDevPG::checkOut << "** WARNING Lexer rule not accepting anything at line " << yyLine << Qt::endl;
              bool ignore = false;
              auto minLen = (yyvsp[-4].nfa)->minLength(), maxLen = (yyvsp[-4].nfa)->maxLength();
              if(minLen == 0)
              {
                KDevPG::checkOut << "** WARNING Lexer rule specifying epsilon-barrier at line " << yyLine << ", ignore the barrier." << Qt::endl;
                ignore = true;
              }
              else if(minLen != maxLen)
              {
                KDevPG::checkOut << "** WARNING Invalid barrier (no fixed length) at line " << yyLine << " (min length: " << (minLen == -1 ? QStringLiteral("none") : QString::number(minLen)) << ", max length: " << (maxLen == -2 ? QStringLiteral("infinity") : (maxLen == -1 ? QStringLiteral("none") : QString::number(maxLen))) << "), ignore the barrier." << Qt::endl;
                ignore = true;
              }
              if(ignore)
              {
                QString s = QLatin1StringView((yyvsp[-2].str)) + r;
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[-7].nfa));
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
              else
              {
                KDevPG::GNFA exclude = KDevPG::GNFA::anything();
                exclude <<= *(yyvsp[-4].nfa);
                exclude <<= KDevPG::GNFA::anything();
                KDevPG::GNFA *staying = new KDevPG::GNFA(*(yyvsp[-7].nfa));
                *staying ^= exclude;
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back(staying);
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(QLatin1StringView((yyvsp[-2].str)) + r);
                // barrier should not get read partially
                exclude <<= KDevPG::GNFA::anyChar();
                *(yyvsp[-7].nfa) <<= *(yyvsp[-4].nfa);
                *(yyvsp[-7].nfa) ^= exclude;
                QString s = QLatin1String("Iterator::plain() -= ") + QString::number(minLen) + QLatin1String("; ") + QLatin1StringView((yyvsp[-2].str)) + r;
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back((yyvsp[-7].nfa));
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
            }
#line 1800 "kdev-pg-parser.cc"
    break;

  case 40: /* $@8: %empty  */
#line 278 "kdev-pg-parser.yy"
            {
              KDevPG::globalSystem.lexerActions[lexerEnv][0] = QString::fromUtf8((yyvsp[0].str));
            }
#line 1808 "kdev-pg-parser.cc"
    break;

  case 42: /* $@9: %empty  */
#line 282 "kdev-pg-parser.yy"
            {
              KDevPG::globalSystem.enteringCode[lexerEnv] = QString::fromUtf8((yyvsp[0].str));
            }
#line 1816 "kdev-pg-parser.cc"
    break;

  case 44: /* $@10: %empty  */
#line 286 "kdev-pg-parser.yy"
            {
              KDevPG::globalSystem.leavingCode[lexerEnv] = QString::fromUtf8((yyvsp[0].str));
            }
#line 1824 "kdev-pg-parser.cc"
    break;

  case 47: /* opt_lexer_action: T_TERMINAL  */
#line 293 "kdev-pg-parser.yy"
                 {
        r = QLatin1String("\nlxRETURN(") + QLatin1StringView((yyvsp[0].str)) + QLatin1String(")\n");
      }
#line 1832 "kdev-pg-parser.cc"
    break;

  case 48: /* opt_lexer_action: T_CONTINUE  */
#line 296 "kdev-pg-parser.yy"
                 {
        r = QStringLiteral("\nlxCONTINUE;\n");
      }
#line 1840 "kdev-pg-parser.cc"
    break;

  case 49: /* opt_lexer_action: %empty  */
#line 299 "kdev-pg-parser.yy"
                  { r = QStringLiteral("\nlxSKIP\n"); }
#line 1846 "kdev-pg-parser.cc"
    break;

  case 50: /* regexp: regexp '|' regexp1  */
#line 303 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-2].nfa) |= *(yyvsp[0].nfa)); delete (yyvsp[-2].nfa); delete (yyvsp[0].nfa); }
#line 1852 "kdev-pg-parser.cc"
    break;

  case 51: /* regexp: regexp1  */
#line 304 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[0].nfa); }
#line 1858 "kdev-pg-parser.cc"
    break;

  case 52: /* regexp1: regexp1 '&' regexp2  */
#line 308 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-2].nfa) &= *(yyvsp[0].nfa)); delete (yyvsp[-2].nfa); delete (yyvsp[0].nfa); }
#line 1864 "kdev-pg-parser.cc"
    break;

  case 53: /* regexp1: regexp2  */
#line 309 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[0].nfa); }
#line 1870 "kdev-pg-parser.cc"
    break;

  case 54: /* regexp2: regexp3 '^' regexp2  */
#line 313 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-2].nfa) ^= *(yyvsp[0].nfa)); delete (yyvsp[-2].nfa); delete (yyvsp[0].nfa); }
#line 1876 "kdev-pg-parser.cc"
    break;

  case 55: /* regexp2: regexp3  */
#line 314 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[0].nfa); }
#line 1882 "kdev-pg-parser.cc"
    break;

  case 56: /* regexp3: '~' regexp3  */
#line 318 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA((yyvsp[0].nfa)->negate()); delete (yyvsp[0].nfa); }
#line 1888 "kdev-pg-parser.cc"
    break;

  case 57: /* regexp3: '?' regexp3  */
#line 319 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[0].nfa) |= KDevPG::GNFA::emptyWord()); delete (yyvsp[0].nfa); }
#line 1894 "kdev-pg-parser.cc"
    break;

  case 58: /* regexp3: regexp4  */
#line 320 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[0].nfa); }
#line 1900 "kdev-pg-parser.cc"
    break;

  case 59: /* regexp4: regexp4 regexp5  */
#line 324 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-1].nfa) <<= *(yyvsp[0].nfa)); delete (yyvsp[-1].nfa); delete (yyvsp[0].nfa); }
#line 1906 "kdev-pg-parser.cc"
    break;

  case 60: /* regexp4: regexp5  */
#line 325 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[0].nfa); }
#line 1912 "kdev-pg-parser.cc"
    break;

  case 61: /* regexp5: regexp5 '@' regexp6  */
#line 329 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-2].nfa)); KDevPG::GNFA *tmp = new KDevPG::GNFA(*(yyvsp[0].nfa) <<= *(yyvsp[-2].nfa)); **tmp; *(yyval.nfa) <<= *tmp; delete tmp; delete (yyvsp[-2].nfa); delete (yyvsp[0].nfa); }
#line 1918 "kdev-pg-parser.cc"
    break;

  case 62: /* regexp5: regexp6  */
#line 330 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[0].nfa); }
#line 1924 "kdev-pg-parser.cc"
    break;

  case 63: /* regexp6: regexp6 '*'  */
#line 334 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(**(yyvsp[-1].nfa)); delete (yyvsp[-1].nfa); }
#line 1930 "kdev-pg-parser.cc"
    break;

  case 64: /* regexp6: regexp6 '+'  */
#line 335 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-1].nfa)); **(yyval.nfa); *(yyval.nfa) <<= *(yyvsp[-1].nfa); delete (yyvsp[-1].nfa); }
#line 1936 "kdev-pg-parser.cc"
    break;

  case 65: /* regexp6: regexp7  */
#line 336 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[0].nfa); }
#line 1942 "kdev-pg-parser.cc"
    break;

  case 66: /* regexp7: '(' regexp ')'  */
#line 340 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-1].nfa)); delete (yyvsp[-1].nfa); }
#line 1948 "kdev-pg-parser.cc"
    break;

  case 67: /* regexp7: '[' aregexp ']'  */
#line 341 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[-1].nfa); }
#line 1954 "kdev-pg-parser.cc"
    break;

  case 68: /* regexp7: '.'  */
#line 342 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::anyChar()); }
#line 1960 "kdev-pg-parser.cc"
    break;

  case 69: /* regexp7: T_STRING  */
#line 343 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::word(KDevPG::unescaped(QByteArray((yyvsp[0].str))))); }
#line 1966 "kdev-pg-parser.cc"
    break;

  case 70: /* regexp7: T_UNQUOTED_STRING  */
#line 344 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::word(KDevPG::unescaped(QByteArray((yyvsp[0].str))))); }
#line 1972 "kdev-pg-parser.cc"
    break;

  case 71: /* regexp7: T_NAMED_REGEXP  */
#line 345 "kdev-pg-parser.yy"
                            {
                              if(!KDevPG::globalSystem.regexpById.contains(QString::fromUtf8((yyvsp[0].str))))
                              {
                                KDevPG::checkOut << "** ERROR: no named regexp " << (yyvsp[0].str) << Qt::endl;
                                exit(-1);
                              }
                              KDevPG::GNFA *regexp = KDevPG::globalSystem.regexpById[QString::fromUtf8((yyvsp[0].str))];
                              if(!KDevPG::globalSystem.dfaForNfa.contains(regexp))
                              {
                                KDevPG::globalSystem.dfaForNfa[regexp] = new KDevPG::GDFA(regexp->dfa());
                                KDevPG::globalSystem.dfaForNfa[regexp]->minimize();
                                *regexp = KDevPG::globalSystem.dfaForNfa[regexp]->nfa();
                              }
                              (yyval.nfa) = new KDevPG::GNFA(*regexp);
                            }
#line 1992 "kdev-pg-parser.cc"
    break;

  case 72: /* regexp7: %empty  */
#line 360 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::emptyWord()); }
#line 1998 "kdev-pg-parser.cc"
    break;

  case 73: /* aregexp: aregexp '|' aregexp1  */
#line 364 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-2].nfa) |= *(yyvsp[0].nfa)); delete (yyvsp[-2].nfa); delete (yyvsp[0].nfa); }
#line 2004 "kdev-pg-parser.cc"
    break;

  case 74: /* aregexp: aregexp1  */
#line 365 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[0].nfa); }
#line 2010 "kdev-pg-parser.cc"
    break;

  case 75: /* aregexp1: aregexp1 '&' aregexp2  */
#line 369 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-2].nfa) &= *(yyvsp[0].nfa)); delete (yyvsp[-2].nfa); delete (yyvsp[0].nfa); }
#line 2016 "kdev-pg-parser.cc"
    break;

  case 76: /* aregexp1: aregexp2  */
#line 370 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[0].nfa); }
#line 2022 "kdev-pg-parser.cc"
    break;

  case 77: /* aregexp2: aregexp3 '^' aregexp2  */
#line 374 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-2].nfa) ^= *(yyvsp[0].nfa)); delete (yyvsp[-2].nfa); delete (yyvsp[0].nfa); }
#line 2028 "kdev-pg-parser.cc"
    break;

  case 78: /* aregexp2: aregexp3  */
#line 375 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[0].nfa); }
#line 2034 "kdev-pg-parser.cc"
    break;

  case 79: /* aregexp3: '~' aregexp3  */
#line 379 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA((yyvsp[0].nfa)->negate()); delete (yyvsp[0].nfa); }
#line 2040 "kdev-pg-parser.cc"
    break;

  case 80: /* aregexp3: '?' aregexp3  */
#line 380 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[0].nfa) |= KDevPG::GNFA::emptyWord()); delete (yyvsp[0].nfa); }
#line 2046 "kdev-pg-parser.cc"
    break;

  case 81: /* aregexp3: aregexp4  */
#line 381 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[0].nfa); }
#line 2052 "kdev-pg-parser.cc"
    break;

  case 82: /* aregexp4: aregexp4 aregexp5  */
#line 385 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-1].nfa) |= *(yyvsp[0].nfa)); delete (yyvsp[-1].nfa); delete (yyvsp[0].nfa); }
#line 2058 "kdev-pg-parser.cc"
    break;

  case 84: /* aregexp5: aregexp5 '@' aregexp6  */
#line 390 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-2].nfa)); KDevPG::GNFA *tmp = new KDevPG::GNFA(*(yyvsp[0].nfa) <<= *(yyvsp[-2].nfa)); **tmp; *(yyval.nfa) <<= *tmp; delete tmp; delete (yyvsp[-2].nfa); delete (yyvsp[0].nfa); }
#line 2064 "kdev-pg-parser.cc"
    break;

  case 85: /* aregexp5: aregexp6  */
#line 391 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[0].nfa); }
#line 2070 "kdev-pg-parser.cc"
    break;

  case 86: /* aregexp6: aregexp6 '*'  */
#line 395 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(**(yyvsp[-1].nfa)); delete (yyvsp[-1].nfa); }
#line 2076 "kdev-pg-parser.cc"
    break;

  case 87: /* aregexp6: aregexp6 '+'  */
#line 396 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-1].nfa)); **(yyval.nfa); *(yyval.nfa) <<= *(yyvsp[-1].nfa); delete (yyvsp[-1].nfa); }
#line 2082 "kdev-pg-parser.cc"
    break;

  case 88: /* aregexp6: aregexp7  */
#line 397 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[0].nfa); }
#line 2088 "kdev-pg-parser.cc"
    break;

  case 89: /* aregexp7: '(' regexp ')'  */
#line 401 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(*(yyvsp[-1].nfa)); delete (yyvsp[-1].nfa); }
#line 2094 "kdev-pg-parser.cc"
    break;

  case 90: /* aregexp7: '[' aregexp ']'  */
#line 402 "kdev-pg-parser.yy"
                            { (yyval.nfa) = (yyvsp[-1].nfa); }
#line 2100 "kdev-pg-parser.cc"
    break;

  case 91: /* aregexp7: '.'  */
#line 403 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::anyChar()); }
#line 2106 "kdev-pg-parser.cc"
    break;

  case 92: /* aregexp7: T_STRING  */
#line 404 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::word(KDevPG::unescaped(QByteArray((yyvsp[0].str))))); }
#line 2112 "kdev-pg-parser.cc"
    break;

  case 93: /* aregexp7: T_RANGE  */
#line 405 "kdev-pg-parser.yy"
                            {
      quint32 begin, end;
      QString str = KDevPG::unescaped(QByteArray((yyvsp[0].str)));
      assert(str.size() >= 3 && str.size() <= 5);
      if(str[1] == QLatin1Char('-'))
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
        assert(str[2] == QLatin1Char('-'));
        if(str.size() == 4)
          end = str[3].unicode();
        else
          end = QChar::surrogateToUcs4(str[3], str[4]);
      }
      (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::range(begin, end+1));
    }
#line 2140 "kdev-pg-parser.cc"
    break;

  case 94: /* aregexp7: T_UNQUOTED_STRING  */
#line 428 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::collection(KDevPG::unescaped(QByteArray((yyvsp[0].str))))); }
#line 2146 "kdev-pg-parser.cc"
    break;

  case 95: /* aregexp7: T_NAMED_REGEXP  */
#line 429 "kdev-pg-parser.yy"
                            {
                              if(!KDevPG::globalSystem.regexpById.contains(QString::fromUtf8((yyvsp[0].str))))
                              {
                                KDevPG::checkOut << "** ERROR: no named regexp " << (yyvsp[0].str) << Qt::endl;
                                exit(-1);
                              }
                              KDevPG::GNFA *regexp = KDevPG::globalSystem.regexpById[QString::fromUtf8((yyvsp[0].str))];
                              if(!KDevPG::globalSystem.dfaForNfa.contains(regexp))
                              {
                                KDevPG::globalSystem.dfaForNfa[regexp] = new KDevPG::GDFA(regexp->dfa());
                                KDevPG::globalSystem.dfaForNfa[regexp]->minimize();
                                *regexp = KDevPG::globalSystem.dfaForNfa[regexp]->nfa();
                              }
                              (yyval.nfa) = new KDevPG::GNFA(*regexp);
                            }
#line 2166 "kdev-pg-parser.cc"
    break;

  case 96: /* aregexp7: %empty  */
#line 444 "kdev-pg-parser.yy"
                            { (yyval.nfa) = new KDevPG::GNFA(KDevPG::GNFA::emptyWord()); }
#line 2172 "kdev-pg-parser.cc"
    break;

  case 97: /* member_declaration_rest: '(' T_PUBLIC T_DECLARATION ')' T_CODE  */
#line 450 "kdev-pg-parser.yy"
        { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PublicDeclaration, QString::fromUtf8((yyvsp[0].str)));    }
#line 2178 "kdev-pg-parser.cc"
    break;

  case 98: /* member_declaration_rest: '(' T_PROTECTED T_DECLARATION ')' T_CODE  */
#line 452 "kdev-pg-parser.yy"
        { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ProtectedDeclaration, QString::fromUtf8((yyvsp[0].str))); }
#line 2184 "kdev-pg-parser.cc"
    break;

  case 99: /* member_declaration_rest: '(' T_PRIVATE T_DECLARATION ')' T_CODE  */
#line 454 "kdev-pg-parser.yy"
        { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::PrivateDeclaration, QString::fromUtf8((yyvsp[0].str)));   }
#line 2190 "kdev-pg-parser.cc"
    break;

  case 100: /* member_declaration_rest: '(' T_CONSTRUCTOR ')' T_CODE  */
#line 456 "kdev-pg-parser.yy"
        { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::ConstructorCode, QString::fromUtf8((yyvsp[0].str)));      }
#line 2196 "kdev-pg-parser.cc"
    break;

  case 101: /* member_declaration_rest: '(' T_DESTRUCTOR ')' T_CODE  */
#line 458 "kdev-pg-parser.yy"
        { (yyval.item) = KDevPG::member(KDevPG::Settings::MemberItem::DestructorCode, QString::fromUtf8((yyvsp[0].str)));       }
#line 2202 "kdev-pg-parser.cc"
    break;

  case 102: /* declared_tokens: T_TERMINAL  */
#line 462 "kdev-pg-parser.yy"
                                        { KDevPG::globalSystem.pushTerminal(QString::fromUtf8((yyvsp[0].str)),QString::fromUtf8((yyvsp[0].str))); }
#line 2208 "kdev-pg-parser.cc"
    break;

  case 103: /* declared_tokens: T_TERMINAL '(' T_STRING ')'  */
#line 463 "kdev-pg-parser.yy"
                                        { KDevPG::globalSystem.pushTerminal(QString::fromUtf8((yyvsp[-3].str)),QString::fromUtf8((yyvsp[-1].str))); }
#line 2214 "kdev-pg-parser.cc"
    break;

  case 104: /* declared_tokens: declared_tokens ',' T_TERMINAL  */
#line 464 "kdev-pg-parser.yy"
                                        { KDevPG::globalSystem.pushTerminal(QString::fromUtf8((yyvsp[0].str)),QString::fromUtf8((yyvsp[0].str))); }
#line 2220 "kdev-pg-parser.cc"
    break;

  case 105: /* declared_tokens: declared_tokens ',' T_TERMINAL '(' T_STRING ')'  */
#line 466 "kdev-pg-parser.yy"
                                        { KDevPG::globalSystem.pushTerminal(QString::fromUtf8((yyvsp[-3].str)),QString::fromUtf8((yyvsp[-1].str))); }
#line 2226 "kdev-pg-parser.cc"
    break;

  case 107: /* rules: rules item ';'  */
#line 471 "kdev-pg-parser.yy"
                                        { KDevPG::globalSystem.pushRule((yyvsp[-1].item)); }
#line 2232 "kdev-pg-parser.cc"
    break;

  case 108: /* primary_item: '0'  */
#line 475 "kdev-pg-parser.yy"
                                        { (yyval.item) = KDevPG::globalSystem.zero(); }
#line 2238 "kdev-pg-parser.cc"
    break;

  case 109: /* primary_item: '(' option_item ')'  */
#line 476 "kdev-pg-parser.yy"
                                        { (yyval.item) = (yyvsp[-1].item); }
#line 2244 "kdev-pg-parser.cc"
    break;

  case 110: /* primary_item: try_item  */
#line 477 "kdev-pg-parser.yy"
                                  { (yyval.item) = (yyvsp[0].item); }
#line 2250 "kdev-pg-parser.cc"
    break;

  case 111: /* primary_item: primary_atom  */
#line 478 "kdev-pg-parser.yy"
                                        { (yyval.item) = (yyvsp[0].item); }
#line 2256 "kdev-pg-parser.cc"
    break;

  case 112: /* primary_item: T_INLINE T_IDENTIFIER  */
#line 479 "kdev-pg-parser.yy"
                                         { (yyval.item) = KDevPG::inlinedNonTerminal(KDevPG::globalSystem.pushSymbol(QString::fromUtf8((yyvsp[0].str)))); }
#line 2262 "kdev-pg-parser.cc"
    break;

  case 113: /* primary_item: name scope primary_atom  */
#line 480 "kdev-pg-parser.yy"
                                        { (yyval.item) = KDevPG::annotation(QString::fromUtf8((yyvsp[-2].str)), (yyvsp[0].item), false, (yyvsp[-1].storageType)); }
#line 2268 "kdev-pg-parser.cc"
    break;

  case 114: /* primary_item: '#' name scope primary_atom  */
#line 481 "kdev-pg-parser.yy"
                                        { (yyval.item) = KDevPG::annotation(QString::fromUtf8((yyvsp[-2].str)), (yyvsp[0].item), true, (yyvsp[-1].storageType));  }
#line 2274 "kdev-pg-parser.cc"
    break;

  case 115: /* primary_atom: T_IDENTIFIER rule_arguments_opt  */
#line 485 "kdev-pg-parser.yy"
                                        { (yyval.item) = KDevPG::nonTerminal(KDevPG::globalSystem.pushSymbol(QString::fromUtf8((yyvsp[-1].str))), QString::fromUtf8((yyvsp[0].str))); }
#line 2280 "kdev-pg-parser.cc"
    break;

  case 116: /* primary_atom: T_TERMINAL  */
#line 486 "kdev-pg-parser.yy"
                                        { (yyval.item) = KDevPG::globalSystem.terminal(QString::fromUtf8((yyvsp[0].str))); }
#line 2286 "kdev-pg-parser.cc"
    break;

  case 117: /* try_item: T_TRY_RECOVER '(' option_item ')'  */
#line 491 "kdev-pg-parser.yy"
        {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[-1].item), nullptr);
        }
#line 2295 "kdev-pg-parser.cc"
    break;

  case 118: /* try_item: T_TRY_ROLLBACK '(' option_item ')' T_CATCH '(' option_item ')'  */
#line 496 "kdev-pg-parser.yy"
        {
          KDevPG::globalSystem.needStateManagement = true;
          (yyval.item) = KDevPG::tryCatch((yyvsp[-5].item), (yyvsp[-1].item));
        }
#line 2304 "kdev-pg-parser.cc"
    break;

  case 119: /* rule_arguments_opt: %empty  */
#line 502 "kdev-pg-parser.yy"
                                        { (yyval.str) = const_cast<char*>(""); }
#line 2310 "kdev-pg-parser.cc"
    break;

  case 120: /* rule_arguments_opt: T_RULE_ARGUMENTS  */
#line 503 "kdev-pg-parser.yy"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 2316 "kdev-pg-parser.cc"
    break;

  case 121: /* name: T_IDENTIFIER  */
#line 507 "kdev-pg-parser.yy"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 2322 "kdev-pg-parser.cc"
    break;

  case 122: /* scope: '='  */
#line 517 "kdev-pg-parser.yy"
          { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember; }
#line 2328 "kdev-pg-parser.cc"
    break;

  case 123: /* scope: ':'  */
#line 518 "kdev-pg-parser.yy"
          { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;  }
#line 2334 "kdev-pg-parser.cc"
    break;

  case 124: /* unary_item: primary_item '+'  */
#line 522 "kdev-pg-parser.yy"
                                        { (yyval.item) = KDevPG::plus((yyvsp[-1].item)); }
#line 2340 "kdev-pg-parser.cc"
    break;

  case 125: /* unary_item: primary_item '*'  */
#line 523 "kdev-pg-parser.yy"
                                        { (yyval.item) = KDevPG::star((yyvsp[-1].item)); }
#line 2346 "kdev-pg-parser.cc"
    break;

  case 126: /* unary_item: primary_item  */
#line 524 "kdev-pg-parser.yy"
                                        { (yyval.item) = (yyvsp[0].item); }
#line 2352 "kdev-pg-parser.cc"
    break;

  case 127: /* unary_item: '?' primary_item  */
#line 525 "kdev-pg-parser.yy"
                                         { (yyval.item) = KDevPG::alternative((yyvsp[0].item), KDevPG::globalSystem.zero()); }
#line 2358 "kdev-pg-parser.cc"
    break;

  case 128: /* postfix_item: unary_item  */
#line 529 "kdev-pg-parser.yy"
                                        { (yyval.item) = (yyvsp[0].item); }
#line 2364 "kdev-pg-parser.cc"
    break;

  case 129: /* postfix_item: postfix_item '@' primary_item  */
#line 531 "kdev-pg-parser.yy"
        {
          KDevPG::CloneTree cl;
          (yyval.item) = KDevPG::cons((yyvsp[-2].item), KDevPG::star(KDevPG::cons(cl.clone((yyvsp[0].item)), cl.clone((yyvsp[-2].item)))));
        }
#line 2373 "kdev-pg-parser.cc"
    break;

  case 130: /* postfix_item: postfix_item T_CODE  */
#line 535 "kdev-pg-parser.yy"
                                        { (yyval.item) = KDevPG::action((yyvsp[-1].item), QString::fromUtf8((yyvsp[0].str))); }
#line 2379 "kdev-pg-parser.cc"
    break;

  case 131: /* postfix_item: T_CODE  */
#line 536 "kdev-pg-parser.yy"
                                        { (yyval.item) = KDevPG::action(nullptr, QString::fromUtf8((yyvsp[0].str))); }
#line 2385 "kdev-pg-parser.cc"
    break;

  case 132: /* item_sequence: postfix_item  */
#line 540 "kdev-pg-parser.yy"
                                        { (yyval.item) = (yyvsp[0].item); }
#line 2391 "kdev-pg-parser.cc"
    break;

  case 133: /* item_sequence: item_sequence postfix_item  */
#line 541 "kdev-pg-parser.yy"
                                        { (yyval.item) = KDevPG::cons((yyvsp[-1].item), (yyvsp[0].item)); }
#line 2397 "kdev-pg-parser.cc"
    break;

  case 134: /* conditional_item: item_sequence  */
#line 545 "kdev-pg-parser.yy"
                                        { (yyval.item) = (yyvsp[0].item); }
#line 2403 "kdev-pg-parser.cc"
    break;

  case 135: /* conditional_item: '?' T_CODE item_sequence  */
#line 546 "kdev-pg-parser.yy"
                                        { (yyval.item) = KDevPG::condition(QString::fromUtf8((yyvsp[-1].str)), (yyvsp[0].item)); }
#line 2409 "kdev-pg-parser.cc"
    break;

  case 136: /* option_item: conditional_item  */
#line 550 "kdev-pg-parser.yy"
                                        { (yyval.item) = (yyvsp[0].item); }
#line 2415 "kdev-pg-parser.cc"
    break;

  case 137: /* option_item: option_item '|' conditional_item  */
#line 551 "kdev-pg-parser.yy"
                                        { (yyval.item) = KDevPG::alternative((yyvsp[-2].item), (yyvsp[0].item)); }
#line 2421 "kdev-pg-parser.cc"
    break;

  case 138: /* item: option_item T_ARROW T_IDENTIFIER T_CODE '[' variableDeclarations ']'  */
#line 556 "kdev-pg-parser.yy"
        {
          (yyval.item) = KDevPG::evolve((yyvsp[-6].item), KDevPG::globalSystem.pushSymbol(QString::fromUtf8((yyvsp[-4].str))),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[-1].item), QString::fromUtf8((yyvsp[-3].str)));
        }
#line 2430 "kdev-pg-parser.cc"
    break;

  case 139: /* item: option_item T_ARROW T_IDENTIFIER '[' variableDeclarations ']' code_opt  */
#line 561 "kdev-pg-parser.yy"
        {
          (yyval.item) = KDevPG::evolve((yyvsp[-6].item), KDevPG::globalSystem.pushSymbol(QString::fromUtf8((yyvsp[-4].str))),
                          (KDevPG::Model::VariableDeclarationItem*) (yyvsp[-2].item), QString::fromUtf8((yyvsp[0].str)));
        }
#line 2439 "kdev-pg-parser.cc"
    break;

  case 140: /* item: option_item T_ARROW T_IDENTIFIER code_opt  */
#line 566 "kdev-pg-parser.yy"
        { (yyval.item) = KDevPG::evolve((yyvsp[-3].item), KDevPG::globalSystem.pushSymbol(QString::fromUtf8((yyvsp[-1].str))), nullptr, QString::fromUtf8((yyvsp[0].str))); }
#line 2445 "kdev-pg-parser.cc"
    break;

  case 141: /* $@11: %empty  */
#line 567 "kdev-pg-parser.yy"
      { if(KDevPG::globalSystem.generateAst == false)
        {
          qFatal("Operator-expression-parsing is not yet supported with --no-ast!");
          exit(-1);
        }
        operatorNode = KDevPG::createNode<KDevPG::Model::OperatorItem>();
      }
#line 2457 "kdev-pg-parser.cc"
    break;

  case 142: /* item: $@11 operatorRule  */
#line 573 "kdev-pg-parser.yy"
                     { KDevPG::globalSystem.needOperatorStack = true; (yyval.item) = (yyvsp[0].item); }
#line 2463 "kdev-pg-parser.cc"
    break;

  case 143: /* code_opt: %empty  */
#line 577 "kdev-pg-parser.yy"
                                        { (yyval.str) = const_cast<char*>(""); }
#line 2469 "kdev-pg-parser.cc"
    break;

  case 144: /* code_opt: T_CODE  */
#line 578 "kdev-pg-parser.yy"
                                        { (yyval.str) = (yyvsp[0].str); }
#line 2475 "kdev-pg-parser.cc"
    break;

  case 146: /* operatorDeclarations: %empty  */
#line 584 "kdev-pg-parser.yy"
                    { ; }
#line 2481 "kdev-pg-parser.cc"
    break;

  case 147: /* operatorRule: T_LOPR primary_atom operatorDeclarations T_ROPR T_IDENTIFIER '[' variableDeclarations ']' code_opt  */
#line 589 "kdev-pg-parser.yy"
            {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[-7].item);
              operatorNode->mName = QString::fromUtf8((yyvsp[-4].str));
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + QLatin1String("Ast");
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol(QString::fromUtf8((yyvsp[-4].str))), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[-2].item), QString::fromUtf8((yyvsp[0].str)));
            }
#line 2493 "kdev-pg-parser.cc"
    break;

  case 148: /* operatorRule: T_LOPR primary_atom operatorDeclarations T_ROPR T_IDENTIFIER T_CODE '[' variableDeclarations ']'  */
#line 597 "kdev-pg-parser.yy"
            {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[-7].item);
              operatorNode->mName = QString::fromUtf8((yyvsp[-4].str));
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + QLatin1String("Ast");
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol(QString::fromUtf8((yyvsp[-4].str))), (KDevPG::Model::VariableDeclarationItem*)(yyvsp[-1].item), QString::fromUtf8((yyvsp[-3].str)));
            }
#line 2505 "kdev-pg-parser.cc"
    break;

  case 149: /* operatorRule: T_LOPR primary_atom operatorDeclarations T_ROPR T_IDENTIFIER code_opt  */
#line 605 "kdev-pg-parser.yy"
            {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)(yyvsp[-4].item);
              operatorNode->mName = QString::fromUtf8((yyvsp[-1].str));
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + QLatin1String("Ast");
              (yyval.item) = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol(QString::fromUtf8((yyvsp[-1].str))), nullptr, QString::fromUtf8((yyvsp[0].str)));
            }
#line 2517 "kdev-pg-parser.cc"
    break;

  case 150: /* operatorDeclaration: T_BIN operator priority assoc  */
#line 615 "kdev-pg-parser.yy"
                                                 { operatorNode->pushBin(*(yyvsp[-2].operatorInformation), QString::fromUtf8((yyvsp[0].str)), QString::fromUtf8((yyvsp[-1].str))); free((yyvsp[-2].operatorInformation)); }
#line 2523 "kdev-pg-parser.cc"
    break;

  case 151: /* operatorDeclaration: T_TERN operator operator priority assoc  */
#line 616 "kdev-pg-parser.yy"
                                                 { operatorNode->pushTern(*(yyvsp[-3].operatorInformation), *(yyvsp[-2].operatorInformation), QString::fromUtf8((yyvsp[0].str)), QString::fromUtf8((yyvsp[-1].str))); free((yyvsp[-3].operatorInformation)); free((yyvsp[-2].operatorInformation)); }
#line 2529 "kdev-pg-parser.cc"
    break;

  case 152: /* operatorDeclaration: T_PRE operator priority  */
#line 617 "kdev-pg-parser.yy"
                                                 { operatorNode->pushPre(*(yyvsp[-1].operatorInformation), QString::fromUtf8((yyvsp[0].str))); free((yyvsp[-1].operatorInformation)); }
#line 2535 "kdev-pg-parser.cc"
    break;

  case 153: /* operatorDeclaration: T_POST operator priority  */
#line 618 "kdev-pg-parser.yy"
                                                 { operatorNode->pushPost(*(yyvsp[-1].operatorInformation), QStringLiteral("0"), QString::fromUtf8((yyvsp[0].str))); free((yyvsp[-1].operatorInformation)); free((yyvsp[0].str)); }
#line 2541 "kdev-pg-parser.cc"
    break;

  case 154: /* operatorDeclaration: T_POST operator priority assoc  */
#line 619 "kdev-pg-parser.yy"
                                                 { operatorNode->pushPost(*(yyvsp[-2].operatorInformation), QString::fromUtf8((yyvsp[0].str)), QString::fromUtf8((yyvsp[-1].str))); free((yyvsp[-2].operatorInformation)); }
#line 2547 "kdev-pg-parser.cc"
    break;

  case 155: /* operatorDeclaration: T_PAREN operator operator  */
#line 620 "kdev-pg-parser.yy"
                                                 { operatorNode->pushParen(*(yyvsp[-1].operatorInformation), *(yyvsp[0].operatorInformation)); free((yyvsp[-1].operatorInformation)); free((yyvsp[0].operatorInformation)); }
#line 2553 "kdev-pg-parser.cc"
    break;

  case 156: /* priority: '0'  */
#line 624 "kdev-pg-parser.yy"
                                   { (yyval.str) = (char*)"0"; }
#line 2559 "kdev-pg-parser.cc"
    break;

  case 157: /* priority: T_NUMBER  */
#line 625 "kdev-pg-parser.yy"
                                   { (yyval.str) = (yyvsp[0].str); }
#line 2565 "kdev-pg-parser.cc"
    break;

  case 158: /* priority: T_PRIORITY T_CODE  */
#line 626 "kdev-pg-parser.yy"
                                   { (yyval.str) = (yyvsp[0].str); }
#line 2571 "kdev-pg-parser.cc"
    break;

  case 159: /* assoc: T_LEFT_ASSOC  */
#line 630 "kdev-pg-parser.yy"
                                   { (yyval.str) = (char*)"1"; }
#line 2577 "kdev-pg-parser.cc"
    break;

  case 160: /* assoc: T_RIGHT_ASSOC  */
#line 631 "kdev-pg-parser.yy"
                                   { (yyval.str) = (char*)"0"; }
#line 2583 "kdev-pg-parser.cc"
    break;

  case 161: /* assoc: T_IS_LEFT_ASSOC T_CODE  */
#line 632 "kdev-pg-parser.yy"
                                   { uint yyleng = strlen((yyvsp[0].str));
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, (yyvsp[0].str));
                                     strcpy(tmp+yyleng+6-6+1, "?1:0)");
                                     (yyval.str) = tmp;
                                   }
#line 2595 "kdev-pg-parser.cc"
    break;

  case 162: /* assoc: T_IS_RIGHT_ASSOC T_CODE  */
#line 639 "kdev-pg-parser.yy"
                                   { uint yyleng = strlen((yyvsp[0].str));
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, (yyvsp[0].str));
                                     strcpy(tmp+yyleng+6-6+1, "?0:1)");
                                     (yyval.str) = tmp;
                                   }
#line 2607 "kdev-pg-parser.cc"
    break;

  case 163: /* operator: '?' T_CODE T_TERMINAL T_CODE  */
#line 649 "kdev-pg-parser.yy"
                                   { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal(QString::fromUtf8((yyvsp[-1].str))), QString::fromUtf8((yyvsp[-2].str)), QString::fromUtf8((yyvsp[0].str))); }
#line 2613 "kdev-pg-parser.cc"
    break;

  case 164: /* operator: '?' T_CODE T_TERMINAL  */
#line 650 "kdev-pg-parser.yy"
                                   { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal(QString::fromUtf8((yyvsp[0].str))), QString::fromUtf8((yyvsp[-1].str)), QString()); }
#line 2619 "kdev-pg-parser.cc"
    break;

  case 165: /* operator: T_TERMINAL T_CODE  */
#line 651 "kdev-pg-parser.yy"
                                   { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal(QString::fromUtf8((yyvsp[-1].str))), QString(), QString::fromUtf8((yyvsp[0].str))); }
#line 2625 "kdev-pg-parser.cc"
    break;

  case 166: /* operator: T_TERMINAL  */
#line 652 "kdev-pg-parser.yy"
                                   { (yyval.operatorInformation) = KDevPG::makeOperator(KDevPG::globalSystem.terminal(QString::fromUtf8((yyvsp[0].str))), QString(), QString()); }
#line 2631 "kdev-pg-parser.cc"
    break;

  case 167: /* variableDeclarations: variableDeclaration  */
#line 656 "kdev-pg-parser.yy"
                                       { (yyval.item) = (yyvsp[0].item); }
#line 2637 "kdev-pg-parser.cc"
    break;

  case 168: /* variableDeclarations: variableDeclarations variableDeclaration  */
#line 658 "kdev-pg-parser.yy"
        {
          KDevPG::Model::VariableDeclarationItem *last = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[-1].item);
          while (last->mNext != nullptr) {
            last = last->mNext;
          }
          last->mNext = (KDevPG::Model::VariableDeclarationItem*) (yyvsp[0].item);
          (yyval.item) = (yyvsp[-1].item);
        }
#line 2650 "kdev-pg-parser.cc"
    break;

  case 169: /* variableDeclaration: declarationType_opt storageType variableType T_IDENTIFIER ':' T_IDENTIFIER  */
#line 670 "kdev-pg-parser.yy"
        { (yyval.item) = KDevPG::variableDeclaration((yyvsp[-5].declarationType), (yyvsp[-4].storageType), (yyvsp[-3].variableType), false, QString::fromUtf8((yyvsp[-2].str)), QString::fromUtf8((yyvsp[0].str))); }
#line 2656 "kdev-pg-parser.cc"
    break;

  case 170: /* variableDeclaration: declarationType_opt storageType T_TOKEN T_IDENTIFIER ';'  */
#line 672 "kdev-pg-parser.yy"
        { (yyval.item) = KDevPG::variableDeclaration((yyvsp[-4].declarationType), (yyvsp[-3].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, false, QString::fromUtf8((yyvsp[-1].str)), QString()); }
#line 2662 "kdev-pg-parser.cc"
    break;

  case 171: /* variableDeclaration: declarationType_opt storageType variableType '#' T_IDENTIFIER ':' T_IDENTIFIER  */
#line 674 "kdev-pg-parser.yy"
        { (yyval.item) = KDevPG::variableDeclaration((yyvsp[-6].declarationType), (yyvsp[-5].storageType), (yyvsp[-4].variableType), true, QString::fromUtf8((yyvsp[-2].str)), QString::fromUtf8((yyvsp[0].str))); }
#line 2668 "kdev-pg-parser.cc"
    break;

  case 172: /* variableDeclaration: declarationType_opt storageType T_TOKEN '#' T_IDENTIFIER ';'  */
#line 676 "kdev-pg-parser.yy"
        { (yyval.item) = KDevPG::variableDeclaration((yyvsp[-5].declarationType), (yyvsp[-4].storageType), KDevPG::Model::VariableDeclarationItem::TypeToken, true, QString::fromUtf8((yyvsp[-1].str)), QString()); }
#line 2674 "kdev-pg-parser.cc"
    break;

  case 173: /* declarationType_opt: %empty  */
#line 680 "kdev-pg-parser.yy"
                        { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationLocal;     }
#line 2680 "kdev-pg-parser.cc"
    break;

  case 174: /* declarationType_opt: T_ARGUMENT  */
#line 681 "kdev-pg-parser.yy"
                        { (yyval.declarationType) = KDevPG::Model::VariableDeclarationItem::DeclarationArgument;  }
#line 2686 "kdev-pg-parser.cc"
    break;

  case 175: /* storageType: T_MEMBER  */
#line 685 "kdev-pg-parser.yy"
                        { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageAstMember;    }
#line 2692 "kdev-pg-parser.cc"
    break;

  case 176: /* storageType: T_TEMPORARY  */
#line 686 "kdev-pg-parser.yy"
                        { (yyval.storageType) = KDevPG::Model::VariableDeclarationItem::StorageTemporary;     }
#line 2698 "kdev-pg-parser.cc"
    break;

  case 177: /* variableType: T_NODE  */
#line 690 "kdev-pg-parser.yy"
                        { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeNode;             }
#line 2704 "kdev-pg-parser.cc"
    break;

  case 178: /* variableType: T_VARIABLE  */
#line 691 "kdev-pg-parser.yy"
                        { (yyval.variableType) = KDevPG::Model::VariableDeclarationItem::TypeVariable;         }
#line 2710 "kdev-pg-parser.cc"
    break;


#line 2714 "kdev-pg-parser.cc"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 694 "kdev-pg-parser.yy"

