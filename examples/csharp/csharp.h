// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef csharp_h_INCLUDED
#define csharp_h_INCLUDED

#include "kdev-pg-memory-pool.h"
#include "kdev-pg-allocator.h"
#include "kdev-pg-list.h"
#include "kdev-pg-token-stream.h"
#include <cassert>

struct compilation_unit_ast;
struct identifier_ast;
struct literal_ast;

struct csharp_ast_node
  {
    enum ast_node_kind_enum {
      Kind_compilation_unit = 1000,
      Kind_identifier = 1001,
      Kind_literal = 1002,
      AST_NODE_KIND_COUNT
    };

    int kind;
    std::size_t start_token;
    std::size_t end_token;
  };

struct compilation_unit_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_compilation_unit
    };


  };

struct identifier_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_identifier
    };

    std::size_t ident;

  };

struct literal_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_literal
    };

    std::size_t integer_literal;
    std::size_t floating_point_literal;
    std::size_t character_literal;
    std::size_t string_literal;

    // user defined declarations:
  public:

    enum literal_type_enum {
      type_true,
      type_false,
      type_null,
      type_integer,
      type_real,
      type_character,
      type_string
    };
    literal_type_enum literal_type;

  protected:
  private:

  public:

  };



class csharp
  {
  public:
    typedef kdev_pg_token_stream token_stream_type;
    typedef kdev_pg_token_stream::token_type token_type;
    kdev_pg_token_stream *token_stream;
    int yytoken;

    inline token_type LA(std::size_t k = 1) const
      {
        return token_stream->token(token_stream->index() - 1 + k - 1);
      }
    inline int yylex()
    {
      return (yytoken = token_stream->next_token());
    }

    // token stream
    void set_token_stream(kdev_pg_token_stream *s)
    {
      token_stream = s;
    }

    // error recovery
    bool yy_expected_symbol(int kind, char const *name);
    bool yy_expected_token(int kind, std::size_t token, char const *name);

    // memory pool
    typedef kdev_pg_memory_pool memory_pool_type;

    kdev_pg_memory_pool *memory_pool;
    void set_memory_pool(kdev_pg_memory_pool *p)
    {
      memory_pool = p;
    }
    template <class T>
    inline T *create()
    {
      T *node = new (memory_pool->allocate(sizeof(T))) T();
      node->kind = T::KIND;
      return node;
    }

    enum token_type_enum
    {
      Token_ABSTRACT = 1000,
      Token_ADD = 1001,
      Token_ALIAS = 1002,
      Token_ARROW_RIGHT = 1003,
      Token_AS = 1004,
      Token_ASSIGN = 1005,
      Token_BANG = 1006,
      Token_BASE = 1007,
      Token_BIT_AND = 1008,
      Token_BIT_AND_ASSIGN = 1009,
      Token_BIT_OR = 1010,
      Token_BIT_OR_ASSIGN = 1011,
      Token_BIT_XOR = 1012,
      Token_BIT_XOR_ASSIGN = 1013,
      Token_BOOL = 1014,
      Token_BREAK = 1015,
      Token_BYTE = 1016,
      Token_CASE = 1017,
      Token_CATCH = 1018,
      Token_CHAR = 1019,
      Token_CHARACTER_LITERAL = 1020,
      Token_CHECKED = 1021,
      Token_CLASS = 1022,
      Token_COLON = 1023,
      Token_COLONCOLON = 1024,
      Token_COMMA = 1025,
      Token_CONST = 1026,
      Token_CONTINUE = 1027,
      Token_DECIMAL = 1028,
      Token_DECREMENT = 1029,
      Token_DEFAULT = 1030,
      Token_DELEGATE = 1031,
      Token_DO = 1032,
      Token_DOT = 1033,
      Token_DOUBLE = 1034,
      Token_ELSE = 1035,
      Token_ENUM = 1036,
      Token_EOF = 1037,
      Token_EQUAL = 1038,
      Token_EVENT = 1039,
      Token_EXPLICIT = 1040,
      Token_FALSE = 1041,
      Token_FINALLY = 1042,
      Token_FIXED = 1043,
      Token_FLOAT = 1044,
      Token_FOR = 1045,
      Token_FOREACH = 1046,
      Token_GET = 1047,
      Token_GLOBAL = 1048,
      Token_GOTO = 1049,
      Token_GREATER_EQUAL = 1050,
      Token_GREATER_THAN = 1051,
      Token_IDENTIFIER = 1052,
      Token_IF = 1053,
      Token_IMPLICIT = 1054,
      Token_IN = 1055,
      Token_INCREMENT = 1056,
      Token_INT = 1057,
      Token_INTEGER_LITERAL = 1058,
      Token_INTERFACE = 1059,
      Token_INTERNAL = 1060,
      Token_INVALID = 1061,
      Token_IS = 1062,
      Token_LBRACE = 1063,
      Token_LBRACKET = 1064,
      Token_LESS_EQUAL = 1065,
      Token_LESS_THAN = 1066,
      Token_LOCK = 1067,
      Token_LOG_AND = 1068,
      Token_LOG_OR = 1069,
      Token_LONG = 1070,
      Token_LPAREN = 1071,
      Token_LSHIFT = 1072,
      Token_LSHIFT_ASSIGN = 1073,
      Token_MINUS = 1074,
      Token_MINUS_ASSIGN = 1075,
      Token_NAMESPACE = 1076,
      Token_NEW = 1077,
      Token_NOT_EQUAL = 1078,
      Token_NULL = 1079,
      Token_OBJECT = 1080,
      Token_OPERATOR = 1081,
      Token_OUT = 1082,
      Token_OVERRIDE = 1083,
      Token_PARAMS = 1084,
      Token_PARTIAL = 1085,
      Token_PLUS = 1086,
      Token_PLUS_ASSIGN = 1087,
      Token_PP_CONDITIONAL_SYMBOL = 1088,
      Token_PP_DEFINE = 1089,
      Token_PP_ELIF = 1090,
      Token_PP_ELSE = 1091,
      Token_PP_ENDIF = 1092,
      Token_PP_ENDREGION = 1093,
      Token_PP_ERROR = 1094,
      Token_PP_FILE_NAME = 1095,
      Token_PP_IDENTIFIER_OR_KEYWORD = 1096,
      Token_PP_IF = 1097,
      Token_PP_LINE = 1098,
      Token_PP_LINE_NUMBER = 1099,
      Token_PP_MESSAGE = 1100,
      Token_PP_NEW_LINE = 1101,
      Token_PP_PRAGMA = 1102,
      Token_PP_PRAGMA_TEXT = 1103,
      Token_PP_REGION = 1104,
      Token_PP_UNDEF = 1105,
      Token_PP_WARNING = 1106,
      Token_PRIVATE = 1107,
      Token_PROTECTED = 1108,
      Token_PUBLIC = 1109,
      Token_QUESTION = 1110,
      Token_QUESTIONQUESTION = 1111,
      Token_RBRACE = 1112,
      Token_RBRACKET = 1113,
      Token_READONLY = 1114,
      Token_REAL_LITERAL = 1115,
      Token_REF = 1116,
      Token_REMAINDER = 1117,
      Token_REMAINDER_ASSIGN = 1118,
      Token_REMOVE = 1119,
      Token_RETURN = 1120,
      Token_RPAREN = 1121,
      Token_RSHIFT = 1122,
      Token_RSHIFT_ASSIGN = 1123,
      Token_SBYTE = 1124,
      Token_SEALED = 1125,
      Token_SEMICOLON = 1126,
      Token_SET = 1127,
      Token_SHORT = 1128,
      Token_SIZEOF = 1129,
      Token_SLASH = 1130,
      Token_SLASH_ASSIGN = 1131,
      Token_STACKALLOC = 1132,
      Token_STAR = 1133,
      Token_STAR_ASSIGN = 1134,
      Token_STATIC = 1135,
      Token_STRING = 1136,
      Token_STRING_LITERAL = 1137,
      Token_STRUCT = 1138,
      Token_SWITCH = 1139,
      Token_THIS = 1140,
      Token_THROW = 1141,
      Token_TILDE = 1142,
      Token_TRUE = 1143,
      Token_TRY = 1144,
      Token_TYPEOF = 1145,
      Token_UINT = 1146,
      Token_ULONG = 1147,
      Token_UNCHECKED = 1148,
      Token_UNSAFE = 1149,
      Token_USHORT = 1150,
      Token_USING = 1151,
      Token_VALUE = 1152,
      Token_VIRTUAL = 1153,
      Token_VOID = 1154,
      Token_VOLATILE = 1155,
      Token_WHERE = 1156,
      Token_WHILE = 1157,
      Token_YIELD = 1158,
      token_type_size
    }; // token_type_enum

    // user defined declarations:
  public:

    // The compatibility_mode status variable tells which version of Java
    // should be checked against.
    enum csharp_compatibility_mode {
      csharp10_compatibility = 100,
      csharp20_compatibility = 200,
    };

    csharp::csharp_compatibility_mode compatibility_mode();
    void set_compatibility_mode( csharp::csharp_compatibility_mode mode );

  protected:
  private:
    csharp::csharp_compatibility_mode _M_compatibility_mode;

  public:
    csharp()
    {
      memory_pool = 0;
      token_stream = 0;
      yytoken = Token_EOF;

      // user defined constructor code:
      _M_compatibility_mode = csharp20_compatibility;
    }

    bool parse_compilation_unit(compilation_unit_ast **yynode);
    bool parse_identifier(identifier_ast **yynode);
    bool parse_literal(literal_ast **yynode);
  };
class csharp_visitor
  {
    typedef void (csharp_visitor::*parser_fun_t)(csharp_ast_node *);
    static parser_fun_t _S_parser_table[];

  public:
    virtual ~csharp_visitor()
    {}
    virtual void visit_node(csharp_ast_node *node)
    {
      if (node)
        (this->*_S_parser_table[node->kind - 1000])(node);
    }
    virtual void visit_compilation_unit(compilation_unit_ast *)
  {}
    virtual void visit_identifier(identifier_ast *)
    {}
    virtual void visit_literal(literal_ast *)
    {}
  }
;
class csharp_default_visitor: public csharp_visitor
  {
  public:
    virtual void visit_compilation_unit(compilation_unit_ast *node)
    {}

    virtual void visit_identifier(identifier_ast *node)
    {}

    virtual void visit_literal(literal_ast *node)
    {}

  }
;
#endif


