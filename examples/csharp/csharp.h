// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef csharp_h_INCLUDED
#define csharp_h_INCLUDED

#include "kdev-pg-memory-pool.h"
#include "kdev-pg-allocator.h"
#include "kdev-pg-list.h"
#include "kdev-pg-token-stream.h"
#include <cassert>

struct attribute_ast;
struct attribute_arguments_ast;
struct attribute_section_ast;
struct attribute_target_ast;
struct compilation_unit_ast;
struct expression_ast;
struct extern_alias_directive_ast;
struct global_attribute_section_ast;
struct identifier_ast;
struct keyword_ast;
struct literal_ast;
struct named_argument_ast;
struct namespace_member_declaration_ast;
struct namespace_name_ast;
struct namespace_or_type_name_ast;
struct namespace_or_type_name_part_ast;
struct positional_argument_ast;
struct type_arguments_ast;
struct type_name_ast;
struct using_directive_ast;

struct csharp_ast_node
  {
    enum ast_node_kind_enum {
      Kind_attribute = 1000,
      Kind_attribute_arguments = 1001,
      Kind_attribute_section = 1002,
      Kind_attribute_target = 1003,
      Kind_compilation_unit = 1004,
      Kind_expression = 1005,
      Kind_extern_alias_directive = 1006,
      Kind_global_attribute_section = 1007,
      Kind_identifier = 1008,
      Kind_keyword = 1009,
      Kind_literal = 1010,
      Kind_named_argument = 1011,
      Kind_namespace_member_declaration = 1012,
      Kind_namespace_name = 1013,
      Kind_namespace_or_type_name = 1014,
      Kind_namespace_or_type_name_part = 1015,
      Kind_positional_argument = 1016,
      Kind_type_arguments = 1017,
      Kind_type_name = 1018,
      Kind_using_directive = 1019,
      AST_NODE_KIND_COUNT
    };

    int kind;
    std::size_t start_token;
    std::size_t end_token;
  };

struct attribute_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_attribute
    };

    type_name_ast *name;
    attribute_arguments_ast *arguments;

  };

struct attribute_arguments_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_attribute_arguments
    };

    const list_node<named_argument_ast *> *named_argument_sequence;
    const list_node<positional_argument_ast *> *positional_argument_sequence;

  };

struct attribute_section_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_attribute_section
    };

    attribute_target_ast *target;
    const list_node<attribute_ast *> *attribute_sequence;

  };

struct attribute_target_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_attribute_target
    };

    identifier_ast *identifier;
    keyword_ast *keyword;

  };

struct compilation_unit_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_compilation_unit
    };

    const list_node<extern_alias_directive_ast *> *extern_alias_sequence;
    const list_node<using_directive_ast *> *using_sequence;
    const list_node<global_attribute_section_ast *> *global_attribute_sequence;
    const list_node<namespace_member_declaration_ast *> *namespace_sequence;

  };

struct expression_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_expression
    };


  };

struct extern_alias_directive_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_extern_alias_directive
    };

    identifier_ast *identifier;

  };

struct global_attribute_section_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_global_attribute_section
    };

    attribute_target_ast *target;
    const list_node<attribute_ast *> *attribute_sequence;

  };

struct identifier_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_identifier
    };

    std::size_t ident;

  };

struct keyword_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_keyword
    };

    std::size_t keyword;

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

struct named_argument_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_named_argument
    };

    identifier_ast *argument_name;
    expression_ast *attribute_argument_expression;

  };

struct namespace_member_declaration_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_namespace_member_declaration
    };


  };

struct namespace_name_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_namespace_name
    };


  };

struct namespace_or_type_name_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_namespace_or_type_name
    };

    identifier_ast *qualified_alias_label;
    const list_node<namespace_or_type_name_part_ast *> *name_part_sequence;

  };

struct namespace_or_type_name_part_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_namespace_or_type_name_part
    };

    identifier_ast *identifier;
    type_arguments_ast *type_arguments;

  };

struct positional_argument_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_positional_argument
    };

    expression_ast *attribute_argument_expression;

  };

struct type_arguments_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_type_arguments
    };


  };

struct type_name_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_type_name
    };


  };

struct using_directive_ast: public csharp_ast_node
  {
    enum
    {
      KIND = Kind_using_directive
    };

    identifier_ast *alias;
    namespace_or_type_name_ast *namespace_or_type_name;
    namespace_or_type_name_ast *namespace_name;

  };



#include <string>
#include <set>

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
      Token_COMMA = 1024,
      Token_CONST = 1025,
      Token_CONTINUE = 1026,
      Token_DECIMAL = 1027,
      Token_DECREMENT = 1028,
      Token_DEFAULT = 1029,
      Token_DELEGATE = 1030,
      Token_DO = 1031,
      Token_DOT = 1032,
      Token_DOUBLE = 1033,
      Token_ELSE = 1034,
      Token_ENUM = 1035,
      Token_EOF = 1036,
      Token_EQUAL = 1037,
      Token_EVENT = 1038,
      Token_EXPLICIT = 1039,
      Token_EXTERN = 1040,
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
      Token_PRIVATE = 1088,
      Token_PROTECTED = 1089,
      Token_PUBLIC = 1090,
      Token_QUESTION = 1091,
      Token_QUESTIONQUESTION = 1092,
      Token_RBRACE = 1093,
      Token_RBRACKET = 1094,
      Token_READONLY = 1095,
      Token_REAL_LITERAL = 1096,
      Token_REF = 1097,
      Token_REMAINDER = 1098,
      Token_REMAINDER_ASSIGN = 1099,
      Token_REMOVE = 1100,
      Token_RETURN = 1101,
      Token_RPAREN = 1102,
      Token_RSHIFT = 1103,
      Token_RSHIFT_ASSIGN = 1104,
      Token_SBYTE = 1105,
      Token_SCOPE = 1106,
      Token_SEALED = 1107,
      Token_SEMICOLON = 1108,
      Token_SET = 1109,
      Token_SHORT = 1110,
      Token_SIZEOF = 1111,
      Token_SLASH = 1112,
      Token_SLASH_ASSIGN = 1113,
      Token_STACKALLOC = 1114,
      Token_STAR = 1115,
      Token_STAR_ASSIGN = 1116,
      Token_STATIC = 1117,
      Token_STRING = 1118,
      Token_STRING_LITERAL = 1119,
      Token_STRUCT = 1120,
      Token_STUB_A = 1121,
      Token_STUB_B = 1122,
      Token_STUB_C = 1123,
      Token_STUB_D = 1124,
      Token_STUB_E = 1125,
      Token_STUB_F = 1126,
      Token_STUB_G = 1127,
      Token_STUB_H = 1128,
      Token_STUB_I = 1129,
      Token_STUB_J = 1130,
      Token_STUB_K = 1131,
      Token_STUB_L = 1132,
      Token_STUB_M = 1133,
      Token_STUB_N = 1134,
      Token_STUB_O = 1135,
      Token_STUB_P = 1136,
      Token_SWITCH = 1137,
      Token_THIS = 1138,
      Token_THROW = 1139,
      Token_TILDE = 1140,
      Token_TRUE = 1141,
      Token_TRY = 1142,
      Token_TYPEOF = 1143,
      Token_UINT = 1144,
      Token_ULONG = 1145,
      Token_UNCHECKED = 1146,
      Token_UNSAFE = 1147,
      Token_USHORT = 1148,
      Token_USING = 1149,
      Token_VALUE = 1150,
      Token_VIRTUAL = 1151,
      Token_VOID = 1152,
      Token_VOLATILE = 1153,
      Token_WHERE = 1154,
      Token_WHILE = 1155,
      Token_YIELD = 1156,
      token_type_size
    }; // token_type_enum

    // user defined declarations:
  public:

    /**
     * Transform the raw input into tokens.
     * When this method returns, the parser's token stream has been filled
     * and any parse_*() method can be called.
     */
    void tokenize();

    /**
     * The compatibility_mode status variable tells which version of C#
     * should be checked against.
     */
    enum csharp_compatibility_mode {
      csharp10_compatibility = 100,
      csharp20_compatibility = 200,
    };
    csharp::csharp_compatibility_mode compatibility_mode();
    void set_compatibility_mode( csharp::csharp_compatibility_mode mode );

    void pp_define_symbol( std::string symbol_name );

    enum problem_type {
      error,
      warning,
      info
    };
    void report_problem( csharp::problem_type type, const char* message );
    void report_problem( csharp::problem_type type, std::string message );

  protected:

    friend class csharp_pp_handler_visitor; // calls the pp_*() methods

    /** Called when an #error or #warning directive has been found.
     *  @param type   Either csharp::error or csharp::warning.
     *  @param label  The error/warning text.
     */
    virtual void pp_diagnostic( csharp::problem_type type, std::string message )
    {}
    virtual void pp_diagnostic( csharp::problem_type type )
    {}

  private:

    void pp_undefine_symbol( std::string symbol_name );
    bool pp_is_symbol_defined( std::string symbol_name );

    csharp::csharp_compatibility_mode _M_compatibility_mode;
    std::set<std::string>
    _M_pp_defined_symbols;


  public:
    csharp()
    {
      memory_pool = 0;
      token_stream = 0;
      yytoken = Token_EOF;

      // user defined constructor code:

      _M_compatibility_mode = csharp20_compatibility;

    }

    bool parse_attribute(attribute_ast **yynode);
    bool parse_attribute_arguments(attribute_arguments_ast **yynode);
    bool parse_attribute_section(attribute_section_ast **yynode);
    bool parse_attribute_target(attribute_target_ast **yynode);
    bool parse_compilation_unit(compilation_unit_ast **yynode);
    bool parse_expression(expression_ast **yynode);
    bool parse_extern_alias_directive(extern_alias_directive_ast **yynode);
    bool parse_global_attribute_section(global_attribute_section_ast **yynode);
    bool parse_identifier(identifier_ast **yynode);
    bool parse_keyword(keyword_ast **yynode);
    bool parse_literal(literal_ast **yynode);
    bool parse_named_argument(named_argument_ast **yynode);
    bool parse_namespace_member_declaration(namespace_member_declaration_ast **yynode);
    bool parse_namespace_name(namespace_name_ast **yynode);
    bool parse_namespace_or_type_name(namespace_or_type_name_ast **yynode);
    bool parse_namespace_or_type_name_part(namespace_or_type_name_part_ast **yynode);
    bool parse_positional_argument(positional_argument_ast **yynode);
    bool parse_type_arguments(type_arguments_ast **yynode);
    bool parse_type_name(type_name_ast **yynode);
    bool parse_using_directive(using_directive_ast **yynode);
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
    virtual void visit_attribute(attribute_ast *)
  {}
    virtual void visit_attribute_arguments(attribute_arguments_ast *)
    {}
    virtual void visit_attribute_section(attribute_section_ast *)
    {}
    virtual void visit_attribute_target(attribute_target_ast *)
    {}
    virtual void visit_compilation_unit(compilation_unit_ast *)
    {}
    virtual void visit_expression(expression_ast *)
    {}
    virtual void visit_extern_alias_directive(extern_alias_directive_ast *)
    {}
    virtual void visit_global_attribute_section(global_attribute_section_ast *)
    {}
    virtual void visit_identifier(identifier_ast *)
    {}
    virtual void visit_keyword(keyword_ast *)
    {}
    virtual void visit_literal(literal_ast *)
    {}
    virtual void visit_named_argument(named_argument_ast *)
    {}
    virtual void visit_namespace_member_declaration(namespace_member_declaration_ast *)
    {}
    virtual void visit_namespace_name(namespace_name_ast *)
    {}
    virtual void visit_namespace_or_type_name(namespace_or_type_name_ast *)
    {}
    virtual void visit_namespace_or_type_name_part(namespace_or_type_name_part_ast *)
    {}
    virtual void visit_positional_argument(positional_argument_ast *)
    {}
    virtual void visit_type_arguments(type_arguments_ast *)
    {}
    virtual void visit_type_name(type_name_ast *)
    {}
    virtual void visit_using_directive(using_directive_ast *)
    {}
  }
;
class csharp_default_visitor: public csharp_visitor
  {
  public:
    virtual void visit_attribute(attribute_ast *node)
    {
      visit_node(node->name);
      visit_node(node->arguments);
    }

    virtual void visit_attribute_arguments(attribute_arguments_ast *node)
    {
      if (node->named_argument_sequence)
        {
          const list_node<named_argument_ast*> *__it = node->named_argument_sequence->to_front(), *__end = __it;
          do
            {
              visit_node(__it->element);
              __it = __it->next;
            }
          while (__it != __end);
        }
      if (node->positional_argument_sequence)
        {
          const list_node<positional_argument_ast*> *__it = node->positional_argument_sequence->to_front(), *__end = __it;
          do
            {
              visit_node(__it->element);
              __it = __it->next;
            }
          while (__it != __end);
        }
    }

    virtual void visit_attribute_section(attribute_section_ast *node)
    {
      visit_node(node->target);
      if (node->attribute_sequence)
        {
          const list_node<attribute_ast*> *__it = node->attribute_sequence->to_front(), *__end = __it;
          do
            {
              visit_node(__it->element);
              __it = __it->next;
            }
          while (__it != __end);
        }
    }

    virtual void visit_attribute_target(attribute_target_ast *node)
    {
      visit_node(node->identifier);
      visit_node(node->keyword);
    }

    virtual void visit_compilation_unit(compilation_unit_ast *node)
    {
      if (node->extern_alias_sequence)
        {
          const list_node<extern_alias_directive_ast*> *__it = node->extern_alias_sequence->to_front(), *__end = __it;
          do
            {
              visit_node(__it->element);
              __it = __it->next;
            }
          while (__it != __end);
        }
      if (node->using_sequence)
        {
          const list_node<using_directive_ast*> *__it = node->using_sequence->to_front(), *__end = __it;
          do
            {
              visit_node(__it->element);
              __it = __it->next;
            }
          while (__it != __end);
        }
      if (node->global_attribute_sequence)
        {
          const list_node<global_attribute_section_ast*> *__it = node->global_attribute_sequence->to_front(), *__end = __it;
          do
            {
              visit_node(__it->element);
              __it = __it->next;
            }
          while (__it != __end);
        }
      if (node->namespace_sequence)
        {
          const list_node<namespace_member_declaration_ast*> *__it = node->namespace_sequence->to_front(), *__end = __it;
          do
            {
              visit_node(__it->element);
              __it = __it->next;
            }
          while (__it != __end);
        }
    }

    virtual void visit_expression(expression_ast *node)
  {}

    virtual void visit_extern_alias_directive(extern_alias_directive_ast *node)
    {
      visit_node(node->identifier);
    }

    virtual void visit_global_attribute_section(global_attribute_section_ast *node)
    {
      visit_node(node->target);
      if (node->attribute_sequence)
        {
          const list_node<attribute_ast*> *__it = node->attribute_sequence->to_front(), *__end = __it;
          do
            {
              visit_node(__it->element);
              __it = __it->next;
            }
          while (__it != __end);
        }
    }

    virtual void visit_identifier(identifier_ast *node)
  {}

    virtual void visit_keyword(keyword_ast *node)
    {}

    virtual void visit_literal(literal_ast *node)
    {}

    virtual void visit_named_argument(named_argument_ast *node)
    {
      visit_node(node->argument_name);
      visit_node(node->attribute_argument_expression);
    }

    virtual void visit_namespace_member_declaration(namespace_member_declaration_ast *node)
    {}

    virtual void visit_namespace_name(namespace_name_ast *node)
    {}

    virtual void visit_namespace_or_type_name(namespace_or_type_name_ast *node)
    {
      visit_node(node->qualified_alias_label);
      if (node->name_part_sequence)
        {
          const list_node<namespace_or_type_name_part_ast*> *__it = node->name_part_sequence->to_front(), *__end = __it;
          do
            {
              visit_node(__it->element);
              __it = __it->next;
            }
          while (__it != __end);
        }
    }

    virtual void visit_namespace_or_type_name_part(namespace_or_type_name_part_ast *node)
    {
      visit_node(node->identifier);
      visit_node(node->type_arguments);
    }

    virtual void visit_positional_argument(positional_argument_ast *node)
    {
      visit_node(node->attribute_argument_expression);
    }

    virtual void visit_type_arguments(type_arguments_ast *node)
    {}

    virtual void visit_type_name(type_name_ast *node)
    {}

    virtual void visit_using_directive(using_directive_ast *node)
    {
      visit_node(node->alias);
      visit_node(node->namespace_or_type_name);
      visit_node(node->namespace_name);
    }

  };
#endif


