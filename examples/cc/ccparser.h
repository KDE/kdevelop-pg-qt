// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef CC_H_INCLUDED
#define CC_H_INCLUDED

#include "ccast.h"
#include <kdev-pg-memory-pool.h>
#include <kdev-pg-allocator.h>
#include <kdev-pg-token-stream.h>

namespace cc
{

class  Parser
{
public:
    typedef KDevPG::TokenStream::Token Token;
    KDevPG::TokenStream *tokenStream;
    int yytoken;

    inline Token LA(qint64 k = 1) const
    {
        return tokenStream->token(tokenStream->index() - 1 + k - 1);
    }
    inline int yylex()
    {
        return (yytoken = tokenStream->nextToken());
    }
    inline void rewind(qint64 index)
    {
        tokenStream->rewind(index);
        yylex();
    }

// token stream
    void setTokenStream(KDevPG::TokenStream *s)
    {
        tokenStream = s;
    }

// error handling
    void expectedSymbol(int kind, const QString& name);
    void expectedToken(int kind, qint64 token, const QString& name);

    bool mBlockErrors;
    inline bool blockErrors(bool block)
    {
        bool previous = mBlockErrors;
        mBlockErrors = block;
        return previous;
    }

// memory pool
    typedef KDevPG::MemoryPool memoryPoolType;

    KDevPG::MemoryPool *memoryPool;
    void setMemoryPool(KDevPG::MemoryPool *p)
    {
        memoryPool = p;
    }
    template <class T>
    inline T *create()
    {
        T *node = new (memoryPool->allocate(sizeof(T))) T();
        node->kind = T::KIND;
        return node;
    }

    enum TokenType
    {
        Token_AND = 1000,
        Token_AND_AND = 1001,
        Token_AND_EQUAL = 1002,
        Token_ARROW = 1003,
        Token_ASM = 1004,
        Token_AUTO = 1005,
        Token_BREAK = 1006,
        Token_CASE = 1007,
        Token_CHAR = 1008,
        Token_COLON = 1009,
        Token_COMMA = 1010,
        Token_CONST = 1011,
        Token_CONTINUE = 1012,
        Token_DEFAULT = 1013,
        Token_DIVIDE = 1014,
        Token_DIVIDE_EQUAL = 1015,
        Token_DO = 1016,
        Token_DOT = 1017,
        Token_DOUBLE = 1018,
        Token_ELLIPSIS = 1019,
        Token_ELSE = 1020,
        Token_ENUM = 1021,
        Token_EOF = 1022,
        Token_EQUAL = 1023,
        Token_EQUAL_EQUAL = 1024,
        Token_EXTENSION = 1025,
        Token_EXTERN = 1026,
        Token_FLOAT = 1027,
        Token_FOR = 1028,
        Token_GOTO = 1029,
        Token_GREATER = 1030,
        Token_GREATER_EQUAL = 1031,
        Token_IDENTIFIER = 1032,
        Token_IF = 1033,
        Token_INLINE = 1034,
        Token_INT = 1035,
        Token_LBRACE = 1036,
        Token_LBRACKET = 1037,
        Token_LESS = 1038,
        Token_LESS_EQUAL = 1039,
        Token_LONG = 1040,
        Token_LPAREN = 1041,
        Token_LSHIFT = 1042,
        Token_LSHIFT_EQUAL = 1043,
        Token_MINUS = 1044,
        Token_MINUS_EQUAL = 1045,
        Token_MINUS_MINUS = 1046,
        Token_NOT = 1047,
        Token_NOT_EQUAL = 1048,
        Token_OR = 1049,
        Token_OR_EQUAL = 1050,
        Token_OR_OR = 1051,
        Token_PLUS = 1052,
        Token_PLUS_EQUAL = 1053,
        Token_PLUS_PLUS = 1054,
        Token_QUESTION = 1055,
        Token_RBRACE = 1056,
        Token_RBRACKET = 1057,
        Token_REGISTER = 1058,
        Token_REMAINDER = 1059,
        Token_REMAINDER_EQUAL = 1060,
        Token_RETURN = 1061,
        Token_RPAREN = 1062,
        Token_RSHIFT = 1063,
        Token_RSHIFT_EQUAL = 1064,
        Token_SEMICOLON = 1065,
        Token_SHORT = 1066,
        Token_SIGNED = 1067,
        Token_SIZEOF = 1068,
        Token_STAR = 1069,
        Token_STAR_EQUAL = 1070,
        Token_STATIC = 1071,
        Token_STRING_LITERAL = 1072,
        Token_STRUCT = 1073,
        Token_SWITCH = 1074,
        Token_TILDE = 1075,
        Token_TYPEDEF = 1076,
        Token_TYPEDEF_NAME = 1077,
        Token_UNION = 1078,
        Token_UNSIGNED = 1079,
        Token_VOID = 1080,
        Token_VOLATILE = 1081,
        Token_WHILE = 1082,
        Token_XOR = 1083,
        Token_XOR_EQUAL = 1084,
        Token_X_CONSTANT = 1085,
        TokenTypeSize
    }; // TokenType

// user defined declarations:
protected:

    void expectedSymbol(cc::AstNode::AstNodeKind kind, const QString& name)
    {
        kDebug() << "In AstNode " << kind << ": Expected symbol " << name;
    }
    void expectedToken(int kind, enum TokenType token, const QString& name)
    {
        kDebug() << "In AstNode " << kind << ": Expected token " << name << " (" << token << ")";
    }
    struct ParserState
    {
        int ltCounter;
    };
    ParserState m_state;


public:
// The copyCurrentState() and restoreState() methods are only declared
// if you are using try blocks in your grammar, and have to be
// implemented by yourself, and you also have to define a
// "struct ParserState" inside a %parserclass directive.

// This method should create a new ParserState object and return it,
// or return 0 if no state variables need to be saved.
    ParserState *copyCurrentState();

// This method is only called for ParserState objects != 0
// and should restore the parser state given as argument.
    void restoreState(ParserState *state);
    Parser()
    {
        memoryPool = 0;
        tokenStream = 0;
        yytoken = Token_EOF;
        mBlockErrors = false;
    }

    virtual ~Parser() {}

    bool parseAND_expression(AND_expressionAst **yynode);
    bool parseAbstract_declarator(Abstract_declaratorAst **yynode);
    bool parseAdditive_expression(Additive_expressionAst **yynode);
    bool parseArgument_expression_list(Argument_expression_listAst **yynode);
    bool parseAsm_against_mangling(Asm_against_manglingAst **yynode);
    bool parseAsm_specifier(Asm_specifierAst **yynode);
    bool parseAssignment_expression(Assignment_expressionAst **yynode);
    bool parseAssignment_operator(Assignment_operatorAst **yynode);
    bool parseCast_expression(Cast_expressionAst **yynode);
    bool parseCompound_statement(Compound_statementAst **yynode);
    bool parseConditional_expression(Conditional_expressionAst **yynode);
    bool parseConstant(ConstantAst **yynode);
    bool parseConstant_expression(Constant_expressionAst **yynode);
    bool parseDdeclaration(DdeclarationAst **yynode);
    bool parseDeclaration(DeclarationAst **yynode);
    bool parseDeclaration_header(Declaration_headerAst **yynode);
    bool parseDeclaration_parameter(Declaration_parameterAst **yynode);
    bool parseDeclaration_specifier(Declaration_specifierAst **yynode);
    bool parseDeclarator(DeclaratorAst **yynode);
    bool parseDirect_abstract_declarator(Direct_abstract_declaratorAst **yynode);
    bool parseDirect_declarator(Direct_declaratorAst **yynode);
    bool parseDirect_declarator_rest(Direct_declarator_restAst **yynode);
    bool parseDocument(DocumentAst **yynode);
    bool parseEnum_specifier(Enum_specifierAst **yynode);
    bool parseEnumerator(EnumeratorAst **yynode);
    bool parseEquality_expression(Equality_expressionAst **yynode);
    bool parseExclusive_OR_expression(Exclusive_OR_expressionAst **yynode);
    bool parseExecution_block(Execution_blockAst **yynode);
    bool parseExpression(ExpressionAst **yynode);
    bool parseExpression_statement(Expression_statementAst **yynode);
    bool parseExt_expression(Ext_expressionAst **yynode);
    bool parseExternal_block(External_blockAst **yynode);
    bool parseFunction_declaration(Function_declarationAst **yynode);
    bool parseFunction_definition(Function_definitionAst **yynode);
    bool parseFunction_pointer_parameter(Function_pointer_parameterAst **yynode);
    bool parseInclusive_OR_expression(Inclusive_OR_expressionAst **yynode);
    bool parseInit_declarator(Init_declaratorAst **yynode);
    bool parseInitializer(InitializerAst **yynode);
    bool parseInline_asm(Inline_asmAst **yynode);
    bool parseIteration_statement(Iteration_statementAst **yynode);
    bool parseJump_statement(Jump_statementAst **yynode);
    bool parseLabeled_statement(Labeled_statementAst **yynode);
    bool parseLogical_AND_expression(Logical_AND_expressionAst **yynode);
    bool parseLogical_OR_expression(Logical_OR_expressionAst **yynode);
    bool parseMultiplicative_expression(Multiplicative_expressionAst **yynode);
    bool parseNamed_parameter(Named_parameterAst **yynode);
    bool parseParameter(ParameterAst **yynode);
    bool parseParameter_declaration(Parameter_declarationAst **yynode);
    bool parseParameter_type_list(Parameter_type_listAst **yynode);
    bool parsePointer(PointerAst **yynode);
    bool parsePostfix_expression(Postfix_expressionAst **yynode);
    bool parsePostfix_expression_rest(Postfix_expression_restAst **yynode);
    bool parsePrimary_expression(Primary_expressionAst **yynode);
    bool parseRelational_expression(Relational_expressionAst **yynode);
    bool parseSelection_statement(Selection_statementAst **yynode);
    bool parseShift_expression(Shift_expressionAst **yynode);
    bool parseSpecifier_qualifier(Specifier_qualifierAst **yynode);
    bool parseStatement(StatementAst **yynode);
    bool parseStorage_class_specifier(Storage_class_specifierAst **yynode);
    bool parseStruct_declaration(Struct_declarationAst **yynode);
    bool parseStruct_declarator(Struct_declaratorAst **yynode);
    bool parseStruct_or_union_specifier(Struct_or_union_specifierAst **yynode);
    bool parseType_attribute_identifier(Type_attribute_identifierAst **yynode);
    bool parseType_name(Type_nameAst **yynode);
    bool parseType_qualifier(Type_qualifierAst **yynode);
    bool parseType_specifier(Type_specifierAst **yynode);
    bool parseTyped_identifier(Typed_identifierAst **yynode);
    bool parseTypedef_d(Typedef_dAst **yynode);
    bool parseUnary_expression(Unary_expressionAst **yynode);
    bool parseUnary_operator(Unary_operatorAst **yynode);
    bool parseValue_declaration(Value_declarationAst **yynode);
    bool parseVariable_declaration(Variable_declarationAst **yynode);
};

} // end of namespace cc

#endif

