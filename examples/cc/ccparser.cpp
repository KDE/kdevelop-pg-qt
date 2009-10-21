// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "ccparser.h"


namespace cc
{
Parser::ParserState *Parser::copyCurrentState()
{
    ParserState *state = new ParserState();
    state->ltCounter = m_state.ltCounter;
    return state;
}

void Parser::restoreState( Parser::ParserState *state )
{
    m_state.ltCounter = state->ltCounter;
}
};

namespace cc
{

bool Parser::parseAND_expression(AND_expressionAst **yynode)
{
    *yynode = create<AND_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Equality_expressionAst *__node_0 = 0;
        if (!parseEquality_expression(&__node_0))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Equality_expressionKind, "equality_expression");
            }
            return false;
        }
        (*yynode)->equality_expressionSequence = snoc((*yynode)->equality_expressionSequence, __node_0, memoryPool);

        while (yytoken == Token_AND)
        {
            if (yytoken != Token_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_AND, "&");
                }
                return false;
            }
            yylex();

            Equality_expressionAst *__node_1 = 0;
            if (!parseEquality_expression(&__node_1))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Equality_expressionKind, "equality_expression");
                }
                return false;
            }
            (*yynode)->equality_expressionSequence = snoc((*yynode)->equality_expressionSequence, __node_1, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAbstract_declarator(Abstract_declaratorAst **yynode)
{
    *yynode = create<Abstract_declaratorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_STAR)
    {
        if (yytoken == Token_STAR)
        {
            PointerAst *__node_2 = 0;
            if (!parsePointer(&__node_2))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::PointerKind, "pointer");
                }
                return false;
            }
            (*yynode)->pointer = __node_2;

            Direct_abstract_declaratorAst *__node_3 = 0;
            if (!parseDirect_abstract_declarator(&__node_3))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Direct_abstract_declaratorKind, "direct_abstract_declarator");
                }
                return false;
            }
            (*yynode)->direct_abstract_declaratorSequence = snoc((*yynode)->direct_abstract_declaratorSequence, __node_3, memoryPool);

        }
        else if (yytoken == Token_LBRACKET
                 || yytoken == Token_LPAREN)
        {
            Direct_abstract_declaratorAst *__node_4 = 0;
            if (!parseDirect_abstract_declarator(&__node_4))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Direct_abstract_declaratorKind, "direct_abstract_declarator");
                }
                return false;
            }
            (*yynode)->direct_abstract_declaratorSequence = snoc((*yynode)->direct_abstract_declaratorSequence, __node_4, memoryPool);

        }
        else
        {
            return false;
        }
        while (yytoken == Token_LBRACKET
               || yytoken == Token_LPAREN)
        {
            Direct_abstract_declaratorAst *__node_5 = 0;
            if (!parseDirect_abstract_declarator(&__node_5))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Direct_abstract_declaratorKind, "direct_abstract_declarator");
                }
                return false;
            }
            (*yynode)->direct_abstract_declaratorSequence = snoc((*yynode)->direct_abstract_declaratorSequence, __node_5, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAdditive_expression(Additive_expressionAst **yynode)
{
    *yynode = create<Additive_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Multiplicative_expressionAst *__node_6 = 0;
        if (!parseMultiplicative_expression(&__node_6))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Multiplicative_expressionKind, "multiplicative_expression");
            }
            return false;
        }
        (*yynode)->multiplicative_expressionSequence = snoc((*yynode)->multiplicative_expressionSequence, __node_6, memoryPool);

        while (yytoken == Token_MINUS
               || yytoken == Token_PLUS)
        {
            if (yytoken == Token_PLUS)
            {
                if (yytoken != Token_PLUS)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_PLUS, "+");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_MINUS)
            {
                if (yytoken != Token_MINUS)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_MINUS, "-");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            Multiplicative_expressionAst *__node_7 = 0;
            if (!parseMultiplicative_expression(&__node_7))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Multiplicative_expressionKind, "multiplicative_expression");
                }
                return false;
            }
            (*yynode)->multiplicative_expressionSequence = snoc((*yynode)->multiplicative_expressionSequence, __node_7, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseArgument_expression_list(Argument_expression_listAst **yynode)
{
    *yynode = create<Argument_expression_listAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Assignment_expressionAst *__node_8 = 0;
        if (!parseAssignment_expression(&__node_8))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Assignment_expressionKind, "assignment_expression");
            }
            return false;
        }
        (*yynode)->assignment_expressionSequence = snoc((*yynode)->assignment_expressionSequence, __node_8, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            Assignment_expressionAst *__node_9 = 0;
            if (!parseAssignment_expression(&__node_9))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Assignment_expressionKind, "assignment_expression");
                }
                return false;
            }
            (*yynode)->assignment_expressionSequence = snoc((*yynode)->assignment_expressionSequence, __node_9, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAssignment_expression(Assignment_expressionAst **yynode)
{
    *yynode = create<Assignment_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Conditional_expressionAst *__node_10 = 0;
        if (!parseConditional_expression(&__node_10))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Conditional_expressionKind, "conditional_expression");
            }
            return false;
        }
        (*yynode)->conditional_expressionSequence = snoc((*yynode)->conditional_expressionSequence, __node_10, memoryPool);

        while (yytoken == Token_AND_EQUAL
               || yytoken == Token_DIVIDE_EQUAL
               || yytoken == Token_EQUAL
               || yytoken == Token_LSHIFT_EQUAL
               || yytoken == Token_MINUS_EQUAL
               || yytoken == Token_OR_EQUAL
               || yytoken == Token_PLUS_EQUAL
               || yytoken == Token_REMAINDER_EQUAL
               || yytoken == Token_RSHIFT_EQUAL
               || yytoken == Token_STAR_EQUAL
               || yytoken == Token_XOR_EQUAL)
        {
            Assignment_operatorAst *__node_11 = 0;
            if (!parseAssignment_operator(&__node_11))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Assignment_operatorKind, "assignment_operator");
                }
                return false;
            }
            Conditional_expressionAst *__node_12 = 0;
            if (!parseConditional_expression(&__node_12))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Conditional_expressionKind, "conditional_expression");
                }
                return false;
            }
            (*yynode)->conditional_expressionSequence = snoc((*yynode)->conditional_expressionSequence, __node_12, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseAssignment_operator(Assignment_operatorAst **yynode)
{
    *yynode = create<Assignment_operatorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND_EQUAL
        || yytoken == Token_DIVIDE_EQUAL
        || yytoken == Token_EQUAL
        || yytoken == Token_LSHIFT_EQUAL
        || yytoken == Token_MINUS_EQUAL
        || yytoken == Token_OR_EQUAL
        || yytoken == Token_PLUS_EQUAL
        || yytoken == Token_REMAINDER_EQUAL
        || yytoken == Token_RSHIFT_EQUAL
        || yytoken == Token_STAR_EQUAL
        || yytoken == Token_XOR_EQUAL)
    {
        if (yytoken == Token_EQUAL)
        {
            if (yytoken != Token_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EQUAL, "=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_STAR_EQUAL)
        {
            if (yytoken != Token_STAR_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STAR_EQUAL, "*=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_DIVIDE_EQUAL)
        {
            if (yytoken != Token_DIVIDE_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DIVIDE_EQUAL, "/=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_REMAINDER_EQUAL)
        {
            if (yytoken != Token_REMAINDER_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_REMAINDER_EQUAL, "%=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_PLUS_EQUAL)
        {
            if (yytoken != Token_PLUS_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS_EQUAL, "+=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_MINUS_EQUAL)
        {
            if (yytoken != Token_MINUS_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS_EQUAL, "-=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LSHIFT_EQUAL)
        {
            if (yytoken != Token_LSHIFT_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LSHIFT_EQUAL, "<<=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_RSHIFT_EQUAL)
        {
            if (yytoken != Token_RSHIFT_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RSHIFT_EQUAL, ">>=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_AND_EQUAL)
        {
            if (yytoken != Token_AND_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_AND_EQUAL, "&=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_XOR_EQUAL)
        {
            if (yytoken != Token_XOR_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_XOR_EQUAL, "^=");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_OR_EQUAL)
        {
            if (yytoken != Token_OR_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_OR_EQUAL, "|=");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCast_expression(Cast_expressionAst **yynode)
{
    *yynode = create<Cast_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            Type_nameAst *__node_13 = 0;
            if (!parseType_name(&__node_13))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_nameKind, "type_name");
                }
                return false;
            }
            (*yynode)->type_name = __node_13;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            Cast_expressionAst *__node_14 = 0;
            if (!parseCast_expression(&__node_14))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Cast_expressionKind, "cast_expression");
                }
                return false;
            }
            (*yynode)->cast_expression = __node_14;

        }
        else if (yytoken == Token_AND
                 || yytoken == Token_IDENTIFIER
                 || yytoken == Token_LPAREN
                 || yytoken == Token_MINUS
                 || yytoken == Token_MINUS_MINUS
                 || yytoken == Token_NOT
                 || yytoken == Token_PLUS
                 || yytoken == Token_PLUS_PLUS
                 || yytoken == Token_SIZEOF
                 || yytoken == Token_STAR
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_TILDE
                 || yytoken == Token_X_CONSTANT)
        {
            Unary_expressionAst *__node_15 = 0;
            if (!parseUnary_expression(&__node_15))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Unary_expressionKind, "unary_expression");
                }
                return false;
            }
            (*yynode)->unary_expression = __node_15;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseCompound_statement(Compound_statementAst **yynode)
{
    *yynode = create<Compound_statementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        while (yytoken == Token_AUTO
               || yytoken == Token_CHAR
               || yytoken == Token_CONST
               || yytoken == Token_DOUBLE
               || yytoken == Token_ENUM
               || yytoken == Token_EXTERN
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_REGISTER
               || yytoken == Token_SHORT
               || yytoken == Token_SIGNED
               || yytoken == Token_STATIC
               || yytoken == Token_STRUCT
               || yytoken == Token_TYPEDEF
               || yytoken == Token_TYPEDEF_NAME
               || yytoken == Token_UNION
               || yytoken == Token_UNSIGNED
               || yytoken == Token_VOID
               || yytoken == Token_VOLATILE)
        {
            DeclarationAst *__node_16 = 0;
            if (!parseDeclaration(&__node_16))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DeclarationKind, "declaration");
                }
                return false;
            }
            (*yynode)->declarationSequence = snoc((*yynode)->declarationSequence, __node_16, memoryPool);

        }
        while (yytoken == Token_AND
               || yytoken == Token_BREAK
               || yytoken == Token_CASE
               || yytoken == Token_CONTINUE
               || yytoken == Token_DEFAULT
               || yytoken == Token_DO
               || yytoken == Token_FOR
               || yytoken == Token_GOTO
               || yytoken == Token_IDENTIFIER
               || yytoken == Token_IF
               || yytoken == Token_LBRACE
               || yytoken == Token_LPAREN
               || yytoken == Token_MINUS
               || yytoken == Token_MINUS_MINUS
               || yytoken == Token_NOT
               || yytoken == Token_PLUS
               || yytoken == Token_PLUS_PLUS
               || yytoken == Token_RETURN
               || yytoken == Token_SEMICOLON
               || yytoken == Token_SIZEOF
               || yytoken == Token_STAR
               || yytoken == Token_STRING_LITERAL
               || yytoken == Token_SWITCH
               || yytoken == Token_TILDE
               || yytoken == Token_WHILE
               || yytoken == Token_X_CONSTANT)
        {
            StatementAst *__node_17 = 0;
            if (!parseStatement(&__node_17))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statementSequence = snoc((*yynode)->statementSequence, __node_17, memoryPool);

        }
        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseConditional_expression(Conditional_expressionAst **yynode)
{
    *yynode = create<Conditional_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Logical_OR_expressionAst *__node_18 = 0;
        if (!parseLogical_OR_expression(&__node_18))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Logical_OR_expressionKind, "logical_OR_expression");
            }
            return false;
        }
        (*yynode)->logical_OR_expression = __node_18;

        if (yytoken == Token_QUESTION)
        {
            if (yytoken != Token_QUESTION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_QUESTION, "?");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_19 = 0;
            if (!parseExpression(&__node_19))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            Conditional_expressionAst *__node_20 = 0;
            if (!parseConditional_expression(&__node_20))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Conditional_expressionKind, "conditional_expression");
                }
                return false;
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseConstant(ConstantAst **yynode)
{
    *yynode = create<ConstantAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_X_CONSTANT)
    {
        if (yytoken != Token_X_CONSTANT)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_X_CONSTANT, "X_CONSTANT");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseConstant_expression(Constant_expressionAst **yynode)
{
    *yynode = create<Constant_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Conditional_expressionAst *__node_21 = 0;
        if (!parseConditional_expression(&__node_21))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Conditional_expressionKind, "conditional_expression");
            }
            return false;
        }
        (*yynode)->conditional_expression = __node_21;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDdeclaration(DdeclarationAst **yynode)
{
    *yynode = create<DdeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_EXTERN
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        if (yytoken == Token_ENUM)
        {
            Enum_specifierAst *__node_22 = 0;
            if (!parseEnum_specifier(&__node_22))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Enum_specifierKind, "enum_specifier");
                }
                return false;
            }
            (*yynode)->enum_specifier = __node_22;

            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_STRUCT
                 || yytoken == Token_UNION)
        {
            Struct_or_union_specifierAst *__node_23 = 0;
            if (!parseStruct_or_union_specifier(&__node_23))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Struct_or_union_specifierKind, "struct_or_union_specifier");
                }
                return false;
            }
            (*yynode)->struct_or_union_specifier = __node_23;

            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_TYPEDEF)
        {
            if (yytoken != Token_TYPEDEF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TYPEDEF, "typedef");
                }
                return false;
            }
            yylex();

            Typedef_dAst *__node_24 = 0;
            if (!parseTypedef_d(&__node_24))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Typedef_dKind, "typedef_d");
                }
                return false;
            }
            (*yynode)->typedef_d = __node_24;

            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CHAR
                 || yytoken == Token_CONST
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_ENUM
                 || yytoken == Token_EXTERN
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_LONG
                 || yytoken == Token_SHORT
                 || yytoken == Token_SIGNED
                 || yytoken == Token_STRUCT
                 || yytoken == Token_TYPEDEF_NAME
                 || yytoken == Token_UNION
                 || yytoken == Token_UNSIGNED
                 || yytoken == Token_VOID
                 || yytoken == Token_VOLATILE)
        {
            bool blockErrors_1 = blockErrors(true);
            qint64 try_startToken_1 = tokenStream->index() - 1;
            ParserState *try_startState_1 = copyCurrentState();
            {
                External_blockAst *__node_25 = 0;
                if (!parseExternal_block(&__node_25))
                {
                    goto __catch_1;
                }
                (*yynode)->external_block = __node_25;

            }
            blockErrors(blockErrors_1);
            if (try_startState_1)
                delete try_startState_1;

            if (false) // the only way to enter here is using goto
            {
__catch_1:
                if (try_startState_1)
                {
                    restoreState(try_startState_1);
                    delete try_startState_1;
                }
                blockErrors(blockErrors_1);
                rewind(try_startToken_1);

                Value_declarationAst *__node_26 = 0;
                if (!parseValue_declaration(&__node_26))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Value_declarationKind, "value_declaration");
                    }
                    return false;
                }
                (*yynode)->value_declaration = __node_26;

            }

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDeclaration(DeclarationAst **yynode)
{
    *yynode = create<DeclarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AUTO
        || yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_EXTERN
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_REGISTER
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STATIC
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        Declaration_specifierAst *__node_27 = 0;
        if (!parseDeclaration_specifier(&__node_27))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Declaration_specifierKind, "declaration_specifier");
            }
            return false;
        }
        (*yynode)->declaration_specifierSequence = snoc((*yynode)->declaration_specifierSequence, __node_27, memoryPool);

        while (yytoken == Token_AUTO
               || yytoken == Token_CHAR
               || yytoken == Token_CONST
               || yytoken == Token_DOUBLE
               || yytoken == Token_ENUM
               || yytoken == Token_EXTERN
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_REGISTER
               || yytoken == Token_SHORT
               || yytoken == Token_SIGNED
               || yytoken == Token_STATIC
               || yytoken == Token_STRUCT
               || yytoken == Token_TYPEDEF
               || yytoken == Token_TYPEDEF_NAME
               || yytoken == Token_UNION
               || yytoken == Token_UNSIGNED
               || yytoken == Token_VOID
               || yytoken == Token_VOLATILE)
        {
            Declaration_specifierAst *__node_28 = 0;
            if (!parseDeclaration_specifier(&__node_28))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Declaration_specifierKind, "declaration_specifier");
                }
                return false;
            }
            (*yynode)->declaration_specifierSequence = snoc((*yynode)->declaration_specifierSequence, __node_28, memoryPool);

        }
        if (yytoken == Token_IDENTIFIER
            || yytoken == Token_LPAREN
            || yytoken == Token_STAR)
        {
            Init_declaratorAst *__node_29 = 0;
            if (!parseInit_declarator(&__node_29))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Init_declaratorKind, "init_declarator");
                }
                return false;
            }
            (*yynode)->init_declaratorSequence = snoc((*yynode)->init_declaratorSequence, __node_29, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                Init_declaratorAst *__node_30 = 0;
                if (!parseInit_declarator(&__node_30))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Init_declaratorKind, "init_declarator");
                    }
                    return false;
                }
                (*yynode)->init_declaratorSequence = snoc((*yynode)->init_declaratorSequence, __node_30, memoryPool);

            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDeclaration_header(Declaration_headerAst **yynode)
{
    *yynode = create<Declaration_headerAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AUTO
        || yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_EXTERN
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_REGISTER
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STATIC
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        Declaration_specifierAst *__node_31 = 0;
        if (!parseDeclaration_specifier(&__node_31))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Declaration_specifierKind, "declaration_specifier");
            }
            return false;
        }
        (*yynode)->declaration_specifierSequence = snoc((*yynode)->declaration_specifierSequence, __node_31, memoryPool);

        while (yytoken == Token_AUTO
               || yytoken == Token_CHAR
               || yytoken == Token_CONST
               || yytoken == Token_DOUBLE
               || yytoken == Token_ENUM
               || yytoken == Token_EXTERN
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_REGISTER
               || yytoken == Token_SHORT
               || yytoken == Token_SIGNED
               || yytoken == Token_STATIC
               || yytoken == Token_STRUCT
               || yytoken == Token_TYPEDEF
               || yytoken == Token_TYPEDEF_NAME
               || yytoken == Token_UNION
               || yytoken == Token_UNSIGNED
               || yytoken == Token_VOID
               || yytoken == Token_VOLATILE)
        {
            Declaration_specifierAst *__node_32 = 0;
            if (!parseDeclaration_specifier(&__node_32))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Declaration_specifierKind, "declaration_specifier");
                }
                return false;
            }
            (*yynode)->declaration_specifierSequence = snoc((*yynode)->declaration_specifierSequence, __node_32, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDeclaration_parameter(Declaration_parameterAst **yynode)
{
    *yynode = create<Declaration_parameterAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ELLIPSIS
        || yytoken == Token_ENUM
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        if (yytoken == Token_CHAR
            || yytoken == Token_CONST
            || yytoken == Token_DOUBLE
            || yytoken == Token_ENUM
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_SHORT
            || yytoken == Token_SIGNED
            || yytoken == Token_STRUCT
            || yytoken == Token_TYPEDEF_NAME
            || yytoken == Token_UNION
            || yytoken == Token_UNSIGNED
            || yytoken == Token_VOID
            || yytoken == Token_VOLATILE)
        {
            bool blockErrors_2 = blockErrors(true);
            qint64 try_startToken_2 = tokenStream->index() - 1;
            ParserState *try_startState_2 = copyCurrentState();
            {
                Typed_identifierAst *__node_33 = 0;
                if (!parseTyped_identifier(&__node_33))
                {
                    goto __catch_2;
                }
                (*yynode)->typed_identifier = __node_33;

                if (true /*epsilon*/)
                {
                }
                else if (yytoken == Token_EQUAL)
                {
                    if (yytoken != Token_EQUAL)
                        goto __catch_2;
                    yylex();

                    Constant_expressionAst *__node_34 = 0;
                    if (!parseConstant_expression(&__node_34))
                    {
                        goto __catch_2;
                    }
                    (*yynode)->constant_expression = __node_34;

                }
                else
                {
                    goto __catch_2;
                }
            }
            blockErrors(blockErrors_2);
            if (try_startState_2)
                delete try_startState_2;

            if (false) // the only way to enter here is using goto
            {
__catch_2:
                if (try_startState_2)
                {
                    restoreState(try_startState_2);
                    delete try_startState_2;
                }
                blockErrors(blockErrors_2);
                rewind(try_startToken_2);

                Type_nameAst *__node_35 = 0;
                if (!parseType_name(&__node_35))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Type_nameKind, "type_name");
                    }
                    return false;
                }
                (*yynode)->type_name = __node_35;

            }

        }
        else if (yytoken == Token_ELLIPSIS)
        {
            if (yytoken != Token_ELLIPSIS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELLIPSIS, "...");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDeclaration_specifier(Declaration_specifierAst **yynode)
{
    *yynode = create<Declaration_specifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AUTO
        || yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_EXTERN
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_REGISTER
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STATIC
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        if (yytoken == Token_AUTO
            || yytoken == Token_EXTERN
            || yytoken == Token_REGISTER
            || yytoken == Token_STATIC
            || yytoken == Token_TYPEDEF)
        {
            Storage_class_specifierAst *__node_36 = 0;
            if (!parseStorage_class_specifier(&__node_36))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Storage_class_specifierKind, "storage_class_specifier");
                }
                return false;
            }
            (*yynode)->storage_class_specifier = __node_36;

        }
        else if (yytoken == Token_CHAR
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_ENUM
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_LONG
                 || yytoken == Token_SHORT
                 || yytoken == Token_SIGNED
                 || yytoken == Token_STRUCT
                 || yytoken == Token_TYPEDEF_NAME
                 || yytoken == Token_UNION
                 || yytoken == Token_UNSIGNED
                 || yytoken == Token_VOID)
        {
            Type_specifierAst *__node_37 = 0;
            if (!parseType_specifier(&__node_37))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_specifierKind, "type_specifier");
                }
                return false;
            }
            (*yynode)->type_specifier = __node_37;

        }
        else if (yytoken == Token_CONST
                 || yytoken == Token_VOLATILE)
        {
            Type_qualifierAst *__node_38 = 0;
            if (!parseType_qualifier(&__node_38))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_qualifierKind, "type_qualifier");
                }
                return false;
            }
            (*yynode)->type_qualifier = __node_38;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDeclarator(DeclaratorAst **yynode)
{
    *yynode = create<DeclaratorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_STAR)
    {
        if (yytoken == Token_IDENTIFIER
            || yytoken == Token_LPAREN
            || yytoken == Token_STAR)
        {
            if (yytoken == Token_STAR)
            {
                PointerAst *__node_39 = 0;
                if (!parsePointer(&__node_39))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::PointerKind, "pointer");
                    }
                    return false;
                }
                (*yynode)->pointer = __node_39;

                Direct_declaratorAst *__node_40 = 0;
                if (!parseDirect_declarator(&__node_40))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Direct_declaratorKind, "direct_declarator");
                    }
                    return false;
                }
                (*yynode)->direct_declarator = __node_40;

            }
            else if (yytoken == Token_IDENTIFIER
                     || yytoken == Token_LPAREN)
            {
                Direct_declaratorAst *__node_41 = 0;
                if (!parseDirect_declarator(&__node_41))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Direct_declaratorKind, "direct_declarator");
                    }
                    return false;
                }
                (*yynode)->direct_declarator = __node_41;

            }
            else
            {
                return false;
            }
            while (yytoken == Token_LBRACKET
                   || yytoken == Token_LPAREN)
            {
                Direct_declarator_restAst *__node_42 = 0;
                if (!parseDirect_declarator_rest(&__node_42))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Direct_declarator_restKind, "direct_declarator_rest");
                    }
                    return false;
                }
                (*yynode)->direct_declarator_restSequence = snoc((*yynode)->direct_declarator_restSequence, __node_42, memoryPool);

            }
        }
        else if (yytoken == Token_IDENTIFIER
                 || yytoken == Token_LPAREN)
        {
            Direct_declaratorAst *__node_43 = 0;
            if (!parseDirect_declarator(&__node_43))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Direct_declaratorKind, "direct_declarator");
                }
                return false;
            }
            (*yynode)->direct_declarator = __node_43;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDirect_abstract_declarator(Direct_abstract_declaratorAst **yynode)
{
    *yynode = create<Direct_abstract_declaratorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN)
    {
        if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_LBRACKET
                || yytoken == Token_LPAREN
                || yytoken == Token_STAR)
            {
                Abstract_declaratorAst *__node_44 = 0;
                if (!parseAbstract_declarator(&__node_44))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Abstract_declaratorKind, "abstract_declarator");
                    }
                    return false;
                }
                (*yynode)->abstract_declarator = __node_44;

            }
            else if (yytoken == Token_AUTO
                     || yytoken == Token_CHAR
                     || yytoken == Token_CONST
                     || yytoken == Token_DOUBLE
                     || yytoken == Token_ELLIPSIS
                     || yytoken == Token_ENUM
                     || yytoken == Token_EXTERN
                     || yytoken == Token_FLOAT
                     || yytoken == Token_INT
                     || yytoken == Token_LONG
                     || yytoken == Token_REGISTER
                     || yytoken == Token_SHORT
                     || yytoken == Token_SIGNED
                     || yytoken == Token_STATIC
                     || yytoken == Token_STRUCT
                     || yytoken == Token_TYPEDEF
                     || yytoken == Token_TYPEDEF_NAME
                     || yytoken == Token_UNION
                     || yytoken == Token_UNSIGNED
                     || yytoken == Token_VOID
                     || yytoken == Token_VOLATILE)
            {
                Parameter_type_listAst *__node_45 = 0;
                if (!parseParameter_type_list(&__node_45))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Parameter_type_listKind, "parameter_type_list");
                    }
                    return false;
                }
                (*yynode)->parameter_type_list = __node_45;

            }
            else
            {
                return false;
            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LBRACKET)
        {
            if (yytoken != Token_LBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACKET, "[");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_AND
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_LPAREN
                || yytoken == Token_MINUS
                || yytoken == Token_MINUS_MINUS
                || yytoken == Token_NOT
                || yytoken == Token_PLUS
                || yytoken == Token_PLUS_PLUS
                || yytoken == Token_SIZEOF
                || yytoken == Token_STAR
                || yytoken == Token_STRING_LITERAL
                || yytoken == Token_TILDE
                || yytoken == Token_X_CONSTANT)
            {
                Constant_expressionAst *__node_46 = 0;
                if (!parseConstant_expression(&__node_46))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Constant_expressionKind, "constant_expression");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACKET, "]");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDirect_declarator(Direct_declaratorAst **yynode)
{
    *yynode = create<Direct_declaratorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN)
    {
        if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            DeclaratorAst *__node_47 = 0;
            if (!parseDeclarator(&__node_47))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DeclaratorKind, "declarator");
                }
                return false;
            }
            (*yynode)->declarator = __node_47;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDirect_declarator_rest(Direct_declarator_restAst **yynode)
{
    *yynode = create<Direct_declarator_restAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN)
    {
        if (yytoken == Token_LBRACKET)
        {
            if (yytoken != Token_LBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACKET, "[");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_AND
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_LPAREN
                || yytoken == Token_MINUS
                || yytoken == Token_MINUS_MINUS
                || yytoken == Token_NOT
                || yytoken == Token_PLUS
                || yytoken == Token_PLUS_PLUS
                || yytoken == Token_SIZEOF
                || yytoken == Token_STAR
                || yytoken == Token_STRING_LITERAL
                || yytoken == Token_TILDE
                || yytoken == Token_X_CONSTANT)
            {
                Constant_expressionAst *__node_48 = 0;
                if (!parseConstant_expression(&__node_48))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Constant_expressionKind, "constant_expression");
                    }
                    return false;
                }
            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACKET, "]");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_IDENTIFIER)
            {
                if (yytoken != Token_IDENTIFIER)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                    }
                    return false;
                }
                yylex();

                while (yytoken == Token_COMMA)
                {
                    if (yytoken != Token_COMMA)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_COMMA, ",");
                        }
                        return false;
                    }
                    yylex();

                    if (yytoken != Token_IDENTIFIER)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                        }
                        return false;
                    }
                    yylex();

                }
            }
            else if (yytoken == Token_AUTO
                     || yytoken == Token_CHAR
                     || yytoken == Token_CONST
                     || yytoken == Token_DOUBLE
                     || yytoken == Token_ELLIPSIS
                     || yytoken == Token_ENUM
                     || yytoken == Token_EXTERN
                     || yytoken == Token_FLOAT
                     || yytoken == Token_INT
                     || yytoken == Token_LONG
                     || yytoken == Token_REGISTER
                     || yytoken == Token_SHORT
                     || yytoken == Token_SIGNED
                     || yytoken == Token_STATIC
                     || yytoken == Token_STRUCT
                     || yytoken == Token_TYPEDEF
                     || yytoken == Token_TYPEDEF_NAME
                     || yytoken == Token_UNION
                     || yytoken == Token_UNSIGNED
                     || yytoken == Token_VOID
                     || yytoken == Token_VOLATILE)
            {
                Parameter_type_listAst *__node_49 = 0;
                if (!parseParameter_type_list(&__node_49))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Parameter_type_listKind, "parameter_type_list");
                    }
                    return false;
                }
                (*yynode)->parameter_type_list = __node_49;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseDocument(DocumentAst **yynode)
{
    *yynode = create<DocumentAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_EXTERN
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE || yytoken == Token_EOF)
    {
        while (yytoken == Token_CHAR
               || yytoken == Token_CONST
               || yytoken == Token_DOUBLE
               || yytoken == Token_ENUM
               || yytoken == Token_EXTERN
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_SHORT
               || yytoken == Token_SIGNED
               || yytoken == Token_STRUCT
               || yytoken == Token_TYPEDEF
               || yytoken == Token_TYPEDEF_NAME
               || yytoken == Token_UNION
               || yytoken == Token_UNSIGNED
               || yytoken == Token_VOID
               || yytoken == Token_VOLATILE)
        {
            DdeclarationAst *__node_50 = 0;
            if (!parseDdeclaration(&__node_50))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DdeclarationKind, "ddeclaration");
                }
                return false;
            }
            (*yynode)->ddeclarationSequence = snoc((*yynode)->ddeclarationSequence, __node_50, memoryPool);

        }
        if (Token_EOF != yytoken)
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEnum_specifier(Enum_specifierAst **yynode)
{
    *yynode = create<Enum_specifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ENUM)
    {
        if (yytoken != Token_ENUM)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_ENUM, "enum");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            EnumeratorAst *__node_51 = 0;
            if (!parseEnumerator(&__node_51))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EnumeratorKind, "enumerator");
                }
                return false;
            }
            (*yynode)->enumeratorSequence = snoc((*yynode)->enumeratorSequence, __node_51, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                EnumeratorAst *__node_52 = 0;
                if (!parseEnumerator(&__node_52))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::EnumeratorKind, "enumerator");
                    }
                    return false;
                }
                (*yynode)->enumeratorSequence = snoc((*yynode)->enumeratorSequence, __node_52, memoryPool);

            }
            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LBRACE)
        {
            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            EnumeratorAst *__node_53 = 0;
            if (!parseEnumerator(&__node_53))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::EnumeratorKind, "enumerator");
                }
                return false;
            }
            (*yynode)->enumeratorSequence = snoc((*yynode)->enumeratorSequence, __node_53, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                EnumeratorAst *__node_54 = 0;
                if (!parseEnumerator(&__node_54))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::EnumeratorKind, "enumerator");
                    }
                    return false;
                }
                (*yynode)->enumeratorSequence = snoc((*yynode)->enumeratorSequence, __node_54, memoryPool);

            }
            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEnumerator(EnumeratorAst **yynode)
{
    *yynode = create<EnumeratorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER)
    {
        if (yytoken != Token_IDENTIFIER)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_IDENTIFIER, "identifier");
            }
            return false;
        }
        yylex();

        if (yytoken == Token_EQUAL)
        {
            if (yytoken != Token_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EQUAL, "=");
                }
                return false;
            }
            yylex();

            Constant_expressionAst *__node_55 = 0;
            if (!parseConstant_expression(&__node_55))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Constant_expressionKind, "constant_expression");
                }
                return false;
            }
            (*yynode)->constant_expression = __node_55;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseEquality_expression(Equality_expressionAst **yynode)
{
    *yynode = create<Equality_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Relational_expressionAst *__node_56 = 0;
        if (!parseRelational_expression(&__node_56))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Relational_expressionKind, "relational_expression");
            }
            return false;
        }
        (*yynode)->relational_expressionSequence = snoc((*yynode)->relational_expressionSequence, __node_56, memoryPool);

        while (yytoken == Token_EQUAL_EQUAL
               || yytoken == Token_NOT_EQUAL)
        {
            if (yytoken == Token_EQUAL_EQUAL)
            {
                if (yytoken != Token_EQUAL_EQUAL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_EQUAL_EQUAL, "==");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_NOT_EQUAL)
            {
                if (yytoken != Token_NOT_EQUAL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_NOT_EQUAL, "!=");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            Relational_expressionAst *__node_57 = 0;
            if (!parseRelational_expression(&__node_57))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Relational_expressionKind, "relational_expression");
                }
                return false;
            }
            (*yynode)->relational_expressionSequence = snoc((*yynode)->relational_expressionSequence, __node_57, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExclusive_OR_expression(Exclusive_OR_expressionAst **yynode)
{
    *yynode = create<Exclusive_OR_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        AND_expressionAst *__node_58 = 0;
        if (!parseAND_expression(&__node_58))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::AND_expressionKind, "AND_expression");
            }
            return false;
        }
        (*yynode)->AND_expressionSequence = snoc((*yynode)->AND_expressionSequence, __node_58, memoryPool);

        while (yytoken == Token_XOR)
        {
            if (yytoken != Token_XOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_XOR, "^");
                }
                return false;
            }
            yylex();

            AND_expressionAst *__node_59 = 0;
            if (!parseAND_expression(&__node_59))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::AND_expressionKind, "AND_expression");
                }
                return false;
            }
            (*yynode)->AND_expressionSequence = snoc((*yynode)->AND_expressionSequence, __node_59, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExecution_block(Execution_blockAst **yynode)
{
    *yynode = create<Execution_blockAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CONTINUE
        || yytoken == Token_DEFAULT
        || yytoken == Token_DO
        || yytoken == Token_FOR
        || yytoken == Token_GOTO
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_LBRACE
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_RETURN
        || yytoken == Token_SEMICOLON
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_SWITCH
        || yytoken == Token_TILDE
        || yytoken == Token_WHILE
        || yytoken == Token_X_CONSTANT || yytoken == Token_EOF
        || yytoken == Token_RBRACE)
    {
        while (yytoken == Token_AND
               || yytoken == Token_BREAK
               || yytoken == Token_CASE
               || yytoken == Token_CONTINUE
               || yytoken == Token_DEFAULT
               || yytoken == Token_DO
               || yytoken == Token_FOR
               || yytoken == Token_GOTO
               || yytoken == Token_IDENTIFIER
               || yytoken == Token_IF
               || yytoken == Token_LBRACE
               || yytoken == Token_LPAREN
               || yytoken == Token_MINUS
               || yytoken == Token_MINUS_MINUS
               || yytoken == Token_NOT
               || yytoken == Token_PLUS
               || yytoken == Token_PLUS_PLUS
               || yytoken == Token_RETURN
               || yytoken == Token_SEMICOLON
               || yytoken == Token_SIZEOF
               || yytoken == Token_STAR
               || yytoken == Token_STRING_LITERAL
               || yytoken == Token_SWITCH
               || yytoken == Token_TILDE
               || yytoken == Token_WHILE
               || yytoken == Token_X_CONSTANT)
        {
            StatementAst *__node_60 = 0;
            if (!parseStatement(&__node_60))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statementSequence = snoc((*yynode)->statementSequence, __node_60, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpression(ExpressionAst **yynode)
{
    *yynode = create<ExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Assignment_expressionAst *__node_61 = 0;
        if (!parseAssignment_expression(&__node_61))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Assignment_expressionKind, "assignment_expression");
            }
            return false;
        }
        (*yynode)->assignment_expressionSequence = snoc((*yynode)->assignment_expressionSequence, __node_61, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            Assignment_expressionAst *__node_62 = 0;
            if (!parseAssignment_expression(&__node_62))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Assignment_expressionKind, "assignment_expression");
                }
                return false;
            }
            (*yynode)->assignment_expressionSequence = snoc((*yynode)->assignment_expressionSequence, __node_62, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExpression_statement(Expression_statementAst **yynode)
{
    *yynode = create<Expression_statementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        ExpressionAst *__node_63 = 0;
        if (!parseExpression(&__node_63))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::ExpressionKind, "expression");
            }
            return false;
        }
        (*yynode)->expression = __node_63;

        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseExternal_block(External_blockAst **yynode)
{
    *yynode = create<External_blockAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_EXTERN)
    {
        if (yytoken != Token_EXTERN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_EXTERN, "extern");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_STRING_LITERAL)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_STRING_LITERAL, "string literal");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        while (yytoken == Token_CHAR
               || yytoken == Token_CONST
               || yytoken == Token_DOUBLE
               || yytoken == Token_ENUM
               || yytoken == Token_EXTERN
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_SHORT
               || yytoken == Token_SIGNED
               || yytoken == Token_STRUCT
               || yytoken == Token_TYPEDEF
               || yytoken == Token_TYPEDEF_NAME
               || yytoken == Token_UNION
               || yytoken == Token_UNSIGNED
               || yytoken == Token_VOID
               || yytoken == Token_VOLATILE)
        {
            DdeclarationAst *__node_64 = 0;
            if (!parseDdeclaration(&__node_64))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DdeclarationKind, "ddeclaration");
                }
                return false;
            }
            (*yynode)->ddeclarationSequence = snoc((*yynode)->ddeclarationSequence, __node_64, memoryPool);

        }
        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunction_declaration(Function_declarationAst **yynode)
{
    *yynode = create<Function_declarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN)
    {
        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        Declaration_parameterAst *__node_65 = 0;
        if (!parseDeclaration_parameter(&__node_65))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Declaration_parameterKind, "declaration_parameter");
            }
            return false;
        }
        (*yynode)->declaration_parameterSequence = snoc((*yynode)->declaration_parameterSequence, __node_65, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            Declaration_parameterAst *__node_66 = 0;
            if (!parseDeclaration_parameter(&__node_66))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Declaration_parameterKind, "declaration_parameter");
                }
                return false;
            }
            (*yynode)->declaration_parameterSequence = snoc((*yynode)->declaration_parameterSequence, __node_66, memoryPool);

        }
        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunction_definition(Function_definitionAst **yynode)
{
    *yynode = create<Function_definitionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LPAREN)
    {
        if (yytoken != Token_LPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LPAREN, "(");
            }
            return false;
        }
        yylex();

        Named_parameterAst *__node_67 = 0;
        if (!parseNamed_parameter(&__node_67))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Named_parameterKind, "named_parameter");
            }
            return false;
        }
        (*yynode)->named_parameterSequence = snoc((*yynode)->named_parameterSequence, __node_67, memoryPool);

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                }
                return false;
            }
            yylex();

            Named_parameterAst *__node_68 = 0;
            if (!parseNamed_parameter(&__node_68))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Named_parameterKind, "named_parameter");
                }
                return false;
            }
            (*yynode)->named_parameterSequence = snoc((*yynode)->named_parameterSequence, __node_68, memoryPool);

        }
        if (yytoken != Token_RPAREN)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RPAREN, ")");
            }
            return false;
        }
        yylex();

        if (yytoken != Token_LBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_LBRACE, "{");
            }
            return false;
        }
        yylex();

        Execution_blockAst *__node_69 = 0;
        if (!parseExecution_block(&__node_69))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Execution_blockKind, "execution_block");
            }
            return false;
        }
        (*yynode)->execution_block = __node_69;

        if (yytoken != Token_RBRACE)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_RBRACE, "}");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunction_pointer_parameter(Function_pointer_parameterAst **yynode)
{
    *yynode = create<Function_pointer_parameterAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ELLIPSIS
        || yytoken == Token_ENUM
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        if (yytoken == Token_CHAR
            || yytoken == Token_CONST
            || yytoken == Token_DOUBLE
            || yytoken == Token_ENUM
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_SHORT
            || yytoken == Token_SIGNED
            || yytoken == Token_STRUCT
            || yytoken == Token_TYPEDEF_NAME
            || yytoken == Token_UNION
            || yytoken == Token_UNSIGNED
            || yytoken == Token_VOID
            || yytoken == Token_VOLATILE)
        {
            bool blockErrors_3 = blockErrors(true);
            qint64 try_startToken_3 = tokenStream->index() - 1;
            ParserState *try_startState_3 = copyCurrentState();
            {
                Typed_identifierAst *__node_70 = 0;
                if (!parseTyped_identifier(&__node_70))
                {
                    goto __catch_3;
                }
                (*yynode)->typed_identifier = __node_70;

            }
            blockErrors(blockErrors_3);
            if (try_startState_3)
                delete try_startState_3;

            if (false) // the only way to enter here is using goto
            {
__catch_3:
                if (try_startState_3)
                {
                    restoreState(try_startState_3);
                    delete try_startState_3;
                }
                blockErrors(blockErrors_3);
                rewind(try_startToken_3);

                Type_nameAst *__node_71 = 0;
                if (!parseType_name(&__node_71))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Type_nameKind, "type_name");
                    }
                    return false;
                }
                (*yynode)->type_name = __node_71;

            }

        }
        else if (yytoken == Token_ELLIPSIS)
        {
            if (yytoken != Token_ELLIPSIS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELLIPSIS, "...");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseInclusive_OR_expression(Inclusive_OR_expressionAst **yynode)
{
    *yynode = create<Inclusive_OR_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Exclusive_OR_expressionAst *__node_72 = 0;
        if (!parseExclusive_OR_expression(&__node_72))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Exclusive_OR_expressionKind, "exclusive_OR_expression");
            }
            return false;
        }
        (*yynode)->exclusive_OR_expressionSequence = snoc((*yynode)->exclusive_OR_expressionSequence, __node_72, memoryPool);

        while (yytoken == Token_OR)
        {
            if (yytoken != Token_OR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_OR, "|");
                }
                return false;
            }
            yylex();

            Exclusive_OR_expressionAst *__node_73 = 0;
            if (!parseExclusive_OR_expression(&__node_73))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Exclusive_OR_expressionKind, "exclusive_OR_expression");
                }
                return false;
            }
            (*yynode)->exclusive_OR_expressionSequence = snoc((*yynode)->exclusive_OR_expressionSequence, __node_73, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseInit_declarator(Init_declaratorAst **yynode)
{
    *yynode = create<Init_declaratorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_STAR)
    {
        DeclaratorAst *__node_74 = 0;
        if (!parseDeclarator(&__node_74))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::DeclaratorKind, "declarator");
            }
            return false;
        }
        (*yynode)->declarator = __node_74;

        if (yytoken == Token_EQUAL)
        {
            if (yytoken != Token_EQUAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EQUAL, "=");
                }
                return false;
            }
            yylex();

            InitializerAst *__node_75 = 0;
            if (!parseInitializer(&__node_75))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InitializerKind, "initializer");
                }
                return false;
            }
            (*yynode)->initializer = __node_75;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseInitializer(InitializerAst **yynode)
{
    *yynode = create<InitializerAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LBRACE
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        if (yytoken == Token_AND
            || yytoken == Token_IDENTIFIER
            || yytoken == Token_LPAREN
            || yytoken == Token_MINUS
            || yytoken == Token_MINUS_MINUS
            || yytoken == Token_NOT
            || yytoken == Token_PLUS
            || yytoken == Token_PLUS_PLUS
            || yytoken == Token_SIZEOF
            || yytoken == Token_STAR
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_TILDE
            || yytoken == Token_X_CONSTANT)
        {
            Assignment_expressionAst *__node_76 = 0;
            if (!parseAssignment_expression(&__node_76))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Assignment_expressionKind, "assignment_expression");
                }
                return false;
            }
            (*yynode)->assignment_expression = __node_76;

        }
        else if (yytoken == Token_LBRACE)
        {
            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            InitializerAst *__node_77 = 0;
            if (!parseInitializer(&__node_77))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::InitializerKind, "initializer");
                }
                return false;
            }
            (*yynode)->initializerSequence = snoc((*yynode)->initializerSequence, __node_77, memoryPool);

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_AND
                    || yytoken == Token_IDENTIFIER
                    || yytoken == Token_LBRACE
                    || yytoken == Token_LPAREN
                    || yytoken == Token_MINUS
                    || yytoken == Token_MINUS_MINUS
                    || yytoken == Token_NOT
                    || yytoken == Token_PLUS
                    || yytoken == Token_PLUS_PLUS
                    || yytoken == Token_SIZEOF
                    || yytoken == Token_STAR
                    || yytoken == Token_STRING_LITERAL
                    || yytoken == Token_TILDE
                    || yytoken == Token_X_CONSTANT)
                {
                    InitializerAst *__node_78 = 0;
                    if (!parseInitializer(&__node_78))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::InitializerKind, "initializer");
                        }
                        return false;
                    }
                    (*yynode)->initializerSequence = snoc((*yynode)->initializerSequence, __node_78, memoryPool);

                }
                else if (true /*epsilon*/)
                {
                }
                else
                {
                    return false;
                }
            }
            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseIteration_statement(Iteration_statementAst **yynode)
{
    *yynode = create<Iteration_statementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_DO
        || yytoken == Token_FOR
        || yytoken == Token_WHILE)
    {
        if (yytoken == Token_WHILE)
        {
            if (yytoken != Token_WHILE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_WHILE, "while");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_79 = 0;
            if (!parseExpression(&__node_79))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->expression = __node_79;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            StatementAst *__node_80 = 0;
            if (!parseStatement(&__node_80))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statement = __node_80;

        }
        else if (yytoken == Token_DO)
        {
            if (yytoken != Token_DO)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DO, "do");
                }
                return false;
            }
            yylex();

            StatementAst *__node_81 = 0;
            if (!parseStatement(&__node_81))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            if (yytoken != Token_WHILE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_WHILE, "while");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_82 = 0;
            if (!parseExpression(&__node_82))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->expression = __node_82;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FOR)
        {
            if (yytoken != Token_FOR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FOR, "for");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_AND
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_LPAREN
                || yytoken == Token_MINUS
                || yytoken == Token_MINUS_MINUS
                || yytoken == Token_NOT
                || yytoken == Token_PLUS
                || yytoken == Token_PLUS_PLUS
                || yytoken == Token_SIZEOF
                || yytoken == Token_STAR
                || yytoken == Token_STRING_LITERAL
                || yytoken == Token_TILDE
                || yytoken == Token_X_CONSTANT)
            {
                ExpressionAst *__node_83 = 0;
                if (!parseExpression(&__node_83))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                    }
                    return false;
                }
                (*yynode)->for_1 = __node_83;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_AND
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_LPAREN
                || yytoken == Token_MINUS
                || yytoken == Token_MINUS_MINUS
                || yytoken == Token_NOT
                || yytoken == Token_PLUS
                || yytoken == Token_PLUS_PLUS
                || yytoken == Token_SIZEOF
                || yytoken == Token_STAR
                || yytoken == Token_STRING_LITERAL
                || yytoken == Token_TILDE
                || yytoken == Token_X_CONSTANT)
            {
                ExpressionAst *__node_84 = 0;
                if (!parseExpression(&__node_84))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                    }
                    return false;
                }
                (*yynode)->for_2 = __node_84;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_AND
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_LPAREN
                || yytoken == Token_MINUS
                || yytoken == Token_MINUS_MINUS
                || yytoken == Token_NOT
                || yytoken == Token_PLUS
                || yytoken == Token_PLUS_PLUS
                || yytoken == Token_SIZEOF
                || yytoken == Token_STAR
                || yytoken == Token_STRING_LITERAL
                || yytoken == Token_TILDE
                || yytoken == Token_X_CONSTANT)
            {
                ExpressionAst *__node_85 = 0;
                if (!parseExpression(&__node_85))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                    }
                    return false;
                }
                (*yynode)->for_3 = __node_85;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            StatementAst *__node_86 = 0;
            if (!parseStatement(&__node_86))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statement = __node_86;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseJump_statement(Jump_statementAst **yynode)
{
    *yynode = create<Jump_statementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_BREAK
        || yytoken == Token_CONTINUE
        || yytoken == Token_GOTO
        || yytoken == Token_RETURN)
    {
        if (yytoken == Token_GOTO)
        {
            if (yytoken != Token_GOTO)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_GOTO, "goto");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CONTINUE)
        {
            if (yytoken != Token_CONTINUE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CONTINUE, "continue");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_BREAK)
        {
            if (yytoken != Token_BREAK)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_BREAK, "break");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_RETURN)
        {
            if (yytoken != Token_RETURN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RETURN, "return");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_AND
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_LPAREN
                || yytoken == Token_MINUS
                || yytoken == Token_MINUS_MINUS
                || yytoken == Token_NOT
                || yytoken == Token_PLUS
                || yytoken == Token_PLUS_PLUS
                || yytoken == Token_SIZEOF
                || yytoken == Token_STAR
                || yytoken == Token_STRING_LITERAL
                || yytoken == Token_TILDE
                || yytoken == Token_X_CONSTANT)
            {
                ExpressionAst *__node_87 = 0;
                if (!parseExpression(&__node_87))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                    }
                    return false;
                }
                (*yynode)->expression = __node_87;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLabeled_statement(Labeled_statementAst **yynode)
{
    *yynode = create<Labeled_statementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CASE
        || yytoken == Token_DEFAULT)
    {
        if (yytoken == Token_CASE)
        {
            if (yytoken != Token_CASE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CASE, "case");
                }
                return false;
            }
            yylex();

            Constant_expressionAst *__node_88 = 0;
            if (!parseConstant_expression(&__node_88))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Constant_expressionKind, "constant_expression");
                }
                return false;
            }
            (*yynode)->constant_expression = __node_88;

            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            StatementAst *__node_89 = 0;
            if (!parseStatement(&__node_89))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statement = __node_89;

        }
        else if (yytoken == Token_DEFAULT)
        {
            if (yytoken != Token_DEFAULT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DEFAULT, "default");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            StatementAst *__node_90 = 0;
            if (!parseStatement(&__node_90))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statement = __node_90;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLogical_AND_expression(Logical_AND_expressionAst **yynode)
{
    *yynode = create<Logical_AND_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Inclusive_OR_expressionAst *__node_91 = 0;
        if (!parseInclusive_OR_expression(&__node_91))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Inclusive_OR_expressionKind, "inclusive_OR_expression");
            }
            return false;
        }
        (*yynode)->inclusive_OR_expressionSequence = snoc((*yynode)->inclusive_OR_expressionSequence, __node_91, memoryPool);

        while (yytoken == Token_AND_AND)
        {
            if (yytoken != Token_AND_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_AND_AND, "&&");
                }
                return false;
            }
            yylex();

            Inclusive_OR_expressionAst *__node_92 = 0;
            if (!parseInclusive_OR_expression(&__node_92))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Inclusive_OR_expressionKind, "inclusive_OR_expression");
                }
                return false;
            }
            (*yynode)->inclusive_OR_expressionSequence = snoc((*yynode)->inclusive_OR_expressionSequence, __node_92, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseLogical_OR_expression(Logical_OR_expressionAst **yynode)
{
    *yynode = create<Logical_OR_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Logical_AND_expressionAst *__node_93 = 0;
        if (!parseLogical_AND_expression(&__node_93))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Logical_AND_expressionKind, "logical_AND_expression");
            }
            return false;
        }
        (*yynode)->logical_AND_expressionSequence = snoc((*yynode)->logical_AND_expressionSequence, __node_93, memoryPool);

        while (yytoken == Token_OR_OR)
        {
            if (yytoken != Token_OR_OR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_OR_OR, "||");
                }
                return false;
            }
            yylex();

            Logical_AND_expressionAst *__node_94 = 0;
            if (!parseLogical_AND_expression(&__node_94))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Logical_AND_expressionKind, "logical_AND_expression");
                }
                return false;
            }
            (*yynode)->logical_AND_expressionSequence = snoc((*yynode)->logical_AND_expressionSequence, __node_94, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseMultiplicative_expression(Multiplicative_expressionAst **yynode)
{
    *yynode = create<Multiplicative_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Cast_expressionAst *__node_95 = 0;
        if (!parseCast_expression(&__node_95))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Cast_expressionKind, "cast_expression");
            }
            return false;
        }
        (*yynode)->cast_expressionSequence = snoc((*yynode)->cast_expressionSequence, __node_95, memoryPool);

        while (yytoken == Token_DIVIDE
               || yytoken == Token_REMAINDER
               || yytoken == Token_STAR)
        {
            if (yytoken == Token_STAR)
            {
                if (yytoken != Token_STAR)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STAR, "*");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_DIVIDE)
            {
                if (yytoken != Token_DIVIDE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_DIVIDE, "/");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_REMAINDER)
            {
                if (yytoken != Token_REMAINDER)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_REMAINDER, "%");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            Cast_expressionAst *__node_96 = 0;
            if (!parseCast_expression(&__node_96))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Cast_expressionKind, "cast_expression");
                }
                return false;
            }
            (*yynode)->cast_expressionSequence = snoc((*yynode)->cast_expressionSequence, __node_96, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseNamed_parameter(Named_parameterAst **yynode)
{
    *yynode = create<Named_parameterAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ELLIPSIS
        || yytoken == Token_ENUM
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        if (yytoken == Token_CHAR
            || yytoken == Token_CONST
            || yytoken == Token_DOUBLE
            || yytoken == Token_ENUM
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_SHORT
            || yytoken == Token_SIGNED
            || yytoken == Token_STRUCT
            || yytoken == Token_TYPEDEF_NAME
            || yytoken == Token_UNION
            || yytoken == Token_UNSIGNED
            || yytoken == Token_VOID
            || yytoken == Token_VOLATILE)
        {
            Typed_identifierAst *__node_97 = 0;
            if (!parseTyped_identifier(&__node_97))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Typed_identifierKind, "typed_identifier");
                }
                return false;
            }
            (*yynode)->typed_identifier = __node_97;

            if (true /*epsilon*/)
            {
            }
            else if (yytoken == Token_EQUAL)
            {
                if (yytoken != Token_EQUAL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_EQUAL, "=");
                    }
                    return false;
                }
                yylex();

                Constant_expressionAst *__node_98 = 0;
                if (!parseConstant_expression(&__node_98))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Constant_expressionKind, "constant_expression");
                    }
                    return false;
                }
                (*yynode)->constant_expression = __node_98;

            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_ELLIPSIS)
        {
            if (yytoken != Token_ELLIPSIS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_ELLIPSIS, "...");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseParameter(ParameterAst **yynode)
{
    *yynode = create<ParameterAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        bool blockErrors_4 = blockErrors(true);
        qint64 try_startToken_4 = tokenStream->index() - 1;
        ParserState *try_startState_4 = copyCurrentState();
        {
            Typed_identifierAst *__node_99 = 0;
            if (!parseTyped_identifier(&__node_99))
            {
                goto __catch_4;
            }
            (*yynode)->typed_identifier = __node_99;

        }
        blockErrors(blockErrors_4);
        if (try_startState_4)
            delete try_startState_4;

        if (false) // the only way to enter here is using goto
        {
__catch_4:
            if (try_startState_4)
            {
                restoreState(try_startState_4);
                delete try_startState_4;
            }
            blockErrors(blockErrors_4);
            rewind(try_startToken_4);

            Type_nameAst *__node_100 = 0;
            if (!parseType_name(&__node_100))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_nameKind, "type_name");
                }
                return false;
            }
            (*yynode)->type_name = __node_100;

        }

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseParameter_declaration(Parameter_declarationAst **yynode)
{
    *yynode = create<Parameter_declarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AUTO
        || yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_EXTERN
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_REGISTER
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STATIC
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        Declaration_specifierAst *__node_101 = 0;
        if (!parseDeclaration_specifier(&__node_101))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Declaration_specifierKind, "declaration_specifier");
            }
            return false;
        }
        (*yynode)->declaration_specifierSequence = snoc((*yynode)->declaration_specifierSequence, __node_101, memoryPool);

        while (yytoken == Token_AUTO
               || yytoken == Token_CHAR
               || yytoken == Token_CONST
               || yytoken == Token_DOUBLE
               || yytoken == Token_ENUM
               || yytoken == Token_EXTERN
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_REGISTER
               || yytoken == Token_SHORT
               || yytoken == Token_SIGNED
               || yytoken == Token_STATIC
               || yytoken == Token_STRUCT
               || yytoken == Token_TYPEDEF
               || yytoken == Token_TYPEDEF_NAME
               || yytoken == Token_UNION
               || yytoken == Token_UNSIGNED
               || yytoken == Token_VOID
               || yytoken == Token_VOLATILE)
        {
            Declaration_specifierAst *__node_102 = 0;
            if (!parseDeclaration_specifier(&__node_102))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Declaration_specifierKind, "declaration_specifier");
                }
                return false;
            }
            (*yynode)->declaration_specifierSequence = snoc((*yynode)->declaration_specifierSequence, __node_102, memoryPool);

        }
        if (yytoken == Token_IDENTIFIER
            || yytoken == Token_LPAREN
            || yytoken == Token_STAR)
        {
            DeclaratorAst *__node_103 = 0;
            if (!parseDeclarator(&__node_103))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DeclaratorKind, "declarator");
                }
                return false;
            }
            (*yynode)->declarator = __node_103;

        }
        else if (yytoken == Token_LBRACKET
                 || yytoken == Token_LPAREN
                 || yytoken == Token_STAR)
        {
            Abstract_declaratorAst *__node_104 = 0;
            if (!parseAbstract_declarator(&__node_104))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Abstract_declaratorKind, "abstract_declarator");
                }
                return false;
            }
            (*yynode)->abstract_declarator = __node_104;

        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseParameter_type_list(Parameter_type_listAst **yynode)
{
    *yynode = create<Parameter_type_listAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AUTO
        || yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ELLIPSIS
        || yytoken == Token_ENUM
        || yytoken == Token_EXTERN
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_REGISTER
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STATIC
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE || yytoken == Token_EOF
        || yytoken == Token_RPAREN)
    {
        if (yytoken == Token_AUTO
            || yytoken == Token_CHAR
            || yytoken == Token_CONST
            || yytoken == Token_DOUBLE
            || yytoken == Token_ELLIPSIS
            || yytoken == Token_ENUM
            || yytoken == Token_EXTERN
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_REGISTER
            || yytoken == Token_SHORT
            || yytoken == Token_SIGNED
            || yytoken == Token_STATIC
            || yytoken == Token_STRUCT
            || yytoken == Token_TYPEDEF
            || yytoken == Token_TYPEDEF_NAME
            || yytoken == Token_UNION
            || yytoken == Token_UNSIGNED
            || yytoken == Token_VOID
            || yytoken == Token_VOLATILE)
        {
            if (yytoken == Token_AUTO
                || yytoken == Token_CHAR
                || yytoken == Token_CONST
                || yytoken == Token_DOUBLE
                || yytoken == Token_ENUM
                || yytoken == Token_EXTERN
                || yytoken == Token_FLOAT
                || yytoken == Token_INT
                || yytoken == Token_LONG
                || yytoken == Token_REGISTER
                || yytoken == Token_SHORT
                || yytoken == Token_SIGNED
                || yytoken == Token_STATIC
                || yytoken == Token_STRUCT
                || yytoken == Token_TYPEDEF
                || yytoken == Token_TYPEDEF_NAME
                || yytoken == Token_UNION
                || yytoken == Token_UNSIGNED
                || yytoken == Token_VOID
                || yytoken == Token_VOLATILE)
            {
                Parameter_declarationAst *__node_105 = 0;
                if (!parseParameter_declaration(&__node_105))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Parameter_declarationKind, "parameter_declaration");
                    }
                    return false;
                }
                (*yynode)->parameter_declarationSequence = snoc((*yynode)->parameter_declarationSequence, __node_105, memoryPool);

            }
            else if (yytoken == Token_ELLIPSIS)
            {
                if (yytoken != Token_ELLIPSIS)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ELLIPSIS, "...");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                    }
                    return false;
                }
                yylex();

                if (yytoken == Token_AUTO
                    || yytoken == Token_CHAR
                    || yytoken == Token_CONST
                    || yytoken == Token_DOUBLE
                    || yytoken == Token_ENUM
                    || yytoken == Token_EXTERN
                    || yytoken == Token_FLOAT
                    || yytoken == Token_INT
                    || yytoken == Token_LONG
                    || yytoken == Token_REGISTER
                    || yytoken == Token_SHORT
                    || yytoken == Token_SIGNED
                    || yytoken == Token_STATIC
                    || yytoken == Token_STRUCT
                    || yytoken == Token_TYPEDEF
                    || yytoken == Token_TYPEDEF_NAME
                    || yytoken == Token_UNION
                    || yytoken == Token_UNSIGNED
                    || yytoken == Token_VOID
                    || yytoken == Token_VOLATILE)
                {
                    Parameter_declarationAst *__node_106 = 0;
                    if (!parseParameter_declaration(&__node_106))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Parameter_declarationKind, "parameter_declaration");
                        }
                        return false;
                    }
                    (*yynode)->parameter_declarationSequence = snoc((*yynode)->parameter_declarationSequence, __node_106, memoryPool);

                }
                else if (yytoken == Token_ELLIPSIS)
                {
                    if (yytoken != Token_ELLIPSIS)
                    {
                        if (!mBlockErrors)
                        {
                            expectedToken(yytoken, Token_ELLIPSIS, "...");
                        }
                        return false;
                    }
                    yylex();

                }
                else
                {
                    return false;
                }
            }
        }
        else if (true /*epsilon*/)
        {
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePointer(PointerAst **yynode)
{
    *yynode = create<PointerAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STAR)
    {
        if (yytoken != Token_STAR)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_STAR, "*");
            }
            return false;
        }
        yylex();

        while (yytoken == Token_CONST
               || yytoken == Token_STAR
               || yytoken == Token_VOLATILE)
        {
            if (yytoken == Token_CONST
                || yytoken == Token_VOLATILE)
            {
                Type_qualifierAst *__node_107 = 0;
                if (!parseType_qualifier(&__node_107))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Type_qualifierKind, "type_qualifier");
                    }
                    return false;
                }
                (*yynode)->type_qualifierSequence = snoc((*yynode)->type_qualifierSequence, __node_107, memoryPool);

            }
            else if (yytoken == Token_STAR)
            {
                if (yytoken != Token_STAR)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_STAR, "*");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePostfix_expression(Postfix_expressionAst **yynode)
{
    *yynode = create<Postfix_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_X_CONSTANT)
    {
        Primary_expressionAst *__node_108 = 0;
        if (!parsePrimary_expression(&__node_108))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Primary_expressionKind, "primary_expression");
            }
            return false;
        }
        (*yynode)->primary_expression = __node_108;

        while (yytoken == Token_ARROW
               || yytoken == Token_DOT
               || yytoken == Token_LBRACKET
               || yytoken == Token_LPAREN
               || yytoken == Token_MINUS_MINUS
               || yytoken == Token_PLUS_PLUS)
        {
            Postfix_expression_restAst *__node_109 = 0;
            if (!parsePostfix_expression_rest(&__node_109))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Postfix_expression_restKind, "postfix_expression_rest");
                }
                return false;
            }
            (*yynode)->postfix_expression_restSequence = snoc((*yynode)->postfix_expression_restSequence, __node_109, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePostfix_expression_rest(Postfix_expression_restAst **yynode)
{
    *yynode = create<Postfix_expression_restAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_ARROW
        || yytoken == Token_DOT
        || yytoken == Token_LBRACKET
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_PLUS_PLUS)
    {
        if (yytoken == Token_ARROW
            || yytoken == Token_DOT)
        {
            if (yytoken == Token_DOT)
            {
                if (yytoken != Token_DOT)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_DOT, ".");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_ARROW)
            {
                if (yytoken != Token_ARROW)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ARROW, "->");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_PLUS_PLUS)
        {
            if (yytoken != Token_PLUS_PLUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS_PLUS, "++");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_MINUS_MINUS)
        {
            if (yytoken != Token_MINUS_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS_MINUS, "--");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_AND
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_LPAREN
                || yytoken == Token_MINUS
                || yytoken == Token_MINUS_MINUS
                || yytoken == Token_NOT
                || yytoken == Token_PLUS
                || yytoken == Token_PLUS_PLUS
                || yytoken == Token_SIZEOF
                || yytoken == Token_STAR
                || yytoken == Token_STRING_LITERAL
                || yytoken == Token_TILDE
                || yytoken == Token_X_CONSTANT)
            {
                Argument_expression_listAst *__node_110 = 0;
                if (!parseArgument_expression_list(&__node_110))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Argument_expression_listKind, "argument_expression_list");
                    }
                    return false;
                }
                (*yynode)->argument_expression_list = __node_110;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LBRACKET)
        {
            if (yytoken != Token_LBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACKET, "[");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_111 = 0;
            if (!parseExpression(&__node_111))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->expression = __node_111;

            if (yytoken != Token_RBRACKET)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACKET, "]");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePrimary_expression(Primary_expressionAst **yynode)
{
    *yynode = create<Primary_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->identifier = -1;
    (*yynode)->string_literal = -1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_X_CONSTANT)
    {
        if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            (*yynode)->identifier = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_X_CONSTANT)
        {
            ConstantAst *__node_112 = 0;
            if (!parseConstant(&__node_112))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ConstantKind, "constant");
                }
                return false;
            }
            (*yynode)->constant = __node_112;

        }
        else if (yytoken == Token_STRING_LITERAL)
        {
            if (yytoken != Token_STRING_LITERAL)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STRING_LITERAL, "string literal");
                }
                return false;
            }
            (*yynode)->string_literal = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_113 = 0;
            if (!parseExpression(&__node_113))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->expression = __node_113;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseRelational_expression(Relational_expressionAst **yynode)
{
    *yynode = create<Relational_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Shift_expressionAst *__node_114 = 0;
        if (!parseShift_expression(&__node_114))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Shift_expressionKind, "shift_expression");
            }
            return false;
        }
        (*yynode)->shift_expressionSequence = snoc((*yynode)->shift_expressionSequence, __node_114, memoryPool);

        while (yytoken == Token_GREATER
               || yytoken == Token_GREATER_EQUAL
               || yytoken == Token_LESS
               || yytoken == Token_LESS_EQUAL)
        {
            if (yytoken == Token_LESS)
            {
                if (yytoken != Token_LESS)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LESS, "<");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_GREATER)
            {
                if (yytoken != Token_GREATER)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_GREATER, ">");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_LESS_EQUAL)
            {
                if (yytoken != Token_LESS_EQUAL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LESS_EQUAL, "<=");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_GREATER_EQUAL)
            {
                if (yytoken != Token_GREATER_EQUAL)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_GREATER_EQUAL, ">=");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            Shift_expressionAst *__node_115 = 0;
            if (!parseShift_expression(&__node_115))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Shift_expressionKind, "shift_expression");
                }
                return false;
            }
            (*yynode)->shift_expressionSequence = snoc((*yynode)->shift_expressionSequence, __node_115, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSelection_statement(Selection_statementAst **yynode)
{
    *yynode = create<Selection_statementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IF
        || yytoken == Token_SWITCH)
    {
        if (yytoken == Token_IF)
        {
            if (yytoken != Token_IF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IF, "if");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_116 = 0;
            if (!parseExpression(&__node_116))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->expression = __node_116;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            StatementAst *__node_117 = 0;
            if (!parseStatement(&__node_117))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statement = __node_117;

            if (yytoken == Token_ELSE)
            {
                if (yytoken != Token_ELSE)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_ELSE, "else");
                    }
                    return false;
                }
                yylex();

                StatementAst *__node_118 = 0;
                if (!parseStatement(&__node_118))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::StatementKind, "statement");
                    }
                    return false;
                }
                (*yynode)->alternative_statement = __node_118;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_SWITCH)
        {
            if (yytoken != Token_SWITCH)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SWITCH, "switch");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            ExpressionAst *__node_119 = 0;
            if (!parseExpression(&__node_119))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                }
                return false;
            }
            (*yynode)->expression = __node_119;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            StatementAst *__node_120 = 0;
            if (!parseStatement(&__node_120))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::StatementKind, "statement");
                }
                return false;
            }
            (*yynode)->statement = __node_120;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseShift_expression(Shift_expressionAst **yynode)
{
    *yynode = create<Shift_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        Additive_expressionAst *__node_121 = 0;
        if (!parseAdditive_expression(&__node_121))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Additive_expressionKind, "additive_expression");
            }
            return false;
        }
        (*yynode)->additive_expressionSequence = snoc((*yynode)->additive_expressionSequence, __node_121, memoryPool);

        while (yytoken == Token_LSHIFT
               || yytoken == Token_RSHIFT)
        {
            if (yytoken == Token_LSHIFT)
            {
                if (yytoken != Token_LSHIFT)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LSHIFT, "<<");
                    }
                    return false;
                }
                yylex();

            }
            else if (yytoken == Token_RSHIFT)
            {
                if (yytoken != Token_RSHIFT)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RSHIFT, ">>");
                    }
                    return false;
                }
                yylex();

            }
            else
            {
                return false;
            }
            Additive_expressionAst *__node_122 = 0;
            if (!parseAdditive_expression(&__node_122))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Additive_expressionKind, "additive_expression");
                }
                return false;
            }
            (*yynode)->additive_expressionSequence = snoc((*yynode)->additive_expressionSequence, __node_122, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseSpecifier_qualifier(Specifier_qualifierAst **yynode)
{
    *yynode = create<Specifier_qualifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        if (yytoken == Token_CHAR
            || yytoken == Token_DOUBLE
            || yytoken == Token_ENUM
            || yytoken == Token_FLOAT
            || yytoken == Token_INT
            || yytoken == Token_LONG
            || yytoken == Token_SHORT
            || yytoken == Token_SIGNED
            || yytoken == Token_STRUCT
            || yytoken == Token_TYPEDEF_NAME
            || yytoken == Token_UNION
            || yytoken == Token_UNSIGNED
            || yytoken == Token_VOID)
        {
            Type_specifierAst *__node_123 = 0;
            if (!parseType_specifier(&__node_123))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_specifierKind, "type_specifier");
                }
                return false;
            }
            (*yynode)->type_specifier = __node_123;

        }
        else if (yytoken == Token_CONST
                 || yytoken == Token_VOLATILE)
        {
            Type_qualifierAst *__node_124 = 0;
            if (!parseType_qualifier(&__node_124))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_qualifierKind, "type_qualifier");
                }
                return false;
            }
            (*yynode)->type_qualifier = __node_124;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStatement(StatementAst **yynode)
{
    *yynode = create<StatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_BREAK
        || yytoken == Token_CASE
        || yytoken == Token_CONTINUE
        || yytoken == Token_DEFAULT
        || yytoken == Token_DO
        || yytoken == Token_FOR
        || yytoken == Token_GOTO
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_IF
        || yytoken == Token_LBRACE
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_RETURN
        || yytoken == Token_SEMICOLON
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_SWITCH
        || yytoken == Token_TILDE
        || yytoken == Token_WHILE
        || yytoken == Token_X_CONSTANT)
    {
        if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CASE
                 || yytoken == Token_DEFAULT)
        {
            Labeled_statementAst *__node_125 = 0;
            if (!parseLabeled_statement(&__node_125))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Labeled_statementKind, "labeled_statement");
                }
                return false;
            }
            (*yynode)->labeled_statement = __node_125;

        }
        else if (yytoken == Token_LBRACE)
        {
            Compound_statementAst *__node_126 = 0;
            if (!parseCompound_statement(&__node_126))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Compound_statementKind, "compound_statement");
                }
                return false;
            }
            (*yynode)->compound_statement = __node_126;

        }
        else if (yytoken == Token_AND
                 || yytoken == Token_IDENTIFIER
                 || yytoken == Token_LPAREN
                 || yytoken == Token_MINUS
                 || yytoken == Token_MINUS_MINUS
                 || yytoken == Token_NOT
                 || yytoken == Token_PLUS
                 || yytoken == Token_PLUS_PLUS
                 || yytoken == Token_SIZEOF
                 || yytoken == Token_STAR
                 || yytoken == Token_STRING_LITERAL
                 || yytoken == Token_TILDE
                 || yytoken == Token_X_CONSTANT)
        {
            Expression_statementAst *__node_127 = 0;
            if (!parseExpression_statement(&__node_127))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Expression_statementKind, "expression_statement");
                }
                return false;
            }
            (*yynode)->expression_statement = __node_127;

        }
        else if (yytoken == Token_IF
                 || yytoken == Token_SWITCH)
        {
            Selection_statementAst *__node_128 = 0;
            if (!parseSelection_statement(&__node_128))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Selection_statementKind, "selection_statement");
                }
                return false;
            }
            (*yynode)->selection_statement = __node_128;

        }
        else if (yytoken == Token_DO
                 || yytoken == Token_FOR
                 || yytoken == Token_WHILE)
        {
            Iteration_statementAst *__node_129 = 0;
            if (!parseIteration_statement(&__node_129))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Iteration_statementKind, "iteration_statement");
                }
                return false;
            }
            (*yynode)->iteration_statement = __node_129;

        }
        else if (yytoken == Token_BREAK
                 || yytoken == Token_CONTINUE
                 || yytoken == Token_GOTO
                 || yytoken == Token_RETURN)
        {
            Jump_statementAst *__node_130 = 0;
            if (!parseJump_statement(&__node_130))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Jump_statementKind, "jump_statement");
                }
                return false;
            }
            (*yynode)->jump_statement = __node_130;

        }
        else if (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStorage_class_specifier(Storage_class_specifierAst **yynode)
{
    *yynode = create<Storage_class_specifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AUTO
        || yytoken == Token_EXTERN
        || yytoken == Token_REGISTER
        || yytoken == Token_STATIC
        || yytoken == Token_TYPEDEF)
    {
        if (yytoken == Token_TYPEDEF)
        {
            if (yytoken != Token_TYPEDEF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TYPEDEF, "typedef");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_EXTERN)
        {
            if (yytoken != Token_EXTERN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_EXTERN, "extern");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_STATIC)
        {
            if (yytoken != Token_STATIC)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STATIC, "static");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_AUTO)
        {
            if (yytoken != Token_AUTO)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_AUTO, "auto");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_REGISTER)
        {
            if (yytoken != Token_REGISTER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_REGISTER, "register");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStruct_declaration(Struct_declarationAst **yynode)
{
    *yynode = create<Struct_declarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        Specifier_qualifierAst *__node_131 = 0;
        if (!parseSpecifier_qualifier(&__node_131))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Specifier_qualifierKind, "specifier_qualifier");
            }
            return false;
        }
        (*yynode)->specifier_qualifierSequence = snoc((*yynode)->specifier_qualifierSequence, __node_131, memoryPool);

        Specifier_qualifierAst *__node_132 = 0;
        if (!parseSpecifier_qualifier(&__node_132))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Specifier_qualifierKind, "specifier_qualifier");
            }
            return false;
        }
        (*yynode)->specifier_qualifierSequence = snoc((*yynode)->specifier_qualifierSequence, __node_132, memoryPool);

        while (yytoken == Token_CHAR
               || yytoken == Token_CONST
               || yytoken == Token_DOUBLE
               || yytoken == Token_ENUM
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_SHORT
               || yytoken == Token_SIGNED
               || yytoken == Token_STRUCT
               || yytoken == Token_TYPEDEF_NAME
               || yytoken == Token_UNION
               || yytoken == Token_UNSIGNED
               || yytoken == Token_VOID
               || yytoken == Token_VOLATILE)
        {
            Specifier_qualifierAst *__node_133 = 0;
            if (!parseSpecifier_qualifier(&__node_133))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Specifier_qualifierKind, "specifier_qualifier");
                }
                return false;
            }
            (*yynode)->specifier_qualifierSequence = snoc((*yynode)->specifier_qualifierSequence, __node_133, memoryPool);

        }
        while (yytoken == Token_COLON
               || yytoken == Token_IDENTIFIER
               || yytoken == Token_LPAREN
               || yytoken == Token_STAR)
        {
            Struct_declaratorAst *__node_134 = 0;
            if (!parseStruct_declarator(&__node_134))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Struct_declaratorKind, "struct_declarator");
                }
                return false;
            }
            (*yynode)->struct_declaratorSequence = snoc((*yynode)->struct_declaratorSequence, __node_134, memoryPool);

        }
        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStruct_declarator(Struct_declaratorAst **yynode)
{
    *yynode = create<Struct_declaratorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_COLON
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_STAR)
    {
        if (yytoken == Token_IDENTIFIER
            || yytoken == Token_LPAREN
            || yytoken == Token_STAR)
        {
            DeclaratorAst *__node_135 = 0;
            if (!parseDeclarator(&__node_135))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::DeclaratorKind, "declarator");
                }
                return false;
            }
            (*yynode)->declarator = __node_135;

            if (yytoken == Token_AND
                || yytoken == Token_IDENTIFIER
                || yytoken == Token_LPAREN
                || yytoken == Token_MINUS
                || yytoken == Token_MINUS_MINUS
                || yytoken == Token_NOT
                || yytoken == Token_PLUS
                || yytoken == Token_PLUS_PLUS
                || yytoken == Token_SIZEOF
                || yytoken == Token_STAR
                || yytoken == Token_STRING_LITERAL
                || yytoken == Token_TILDE
                || yytoken == Token_X_CONSTANT)
            {
                Constant_expressionAst *__node_136 = 0;
                if (!parseConstant_expression(&__node_136))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Constant_expressionKind, "constant_expression");
                    }
                    return false;
                }
                (*yynode)->constant_expression = __node_136;

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_COLON)
        {
            if (yytoken != Token_COLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_COLON, ":");
                }
                return false;
            }
            yylex();

            Constant_expressionAst *__node_137 = 0;
            if (!parseConstant_expression(&__node_137))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Constant_expressionKind, "constant_expression");
                }
                return false;
            }
            (*yynode)->constant_expression = __node_137;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseStruct_or_union_specifier(Struct_or_union_specifierAst **yynode)
{
    *yynode = create<Struct_or_union_specifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_STRUCT
        || yytoken == Token_UNION)
    {
        if (yytoken == Token_STRUCT)
        {
            if (yytoken != Token_STRUCT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STRUCT, "struct");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_UNION)
        {
            if (yytoken != Token_UNION)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_UNION, "union");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
        if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            while (yytoken == Token_CHAR
                   || yytoken == Token_CONST
                   || yytoken == Token_DOUBLE
                   || yytoken == Token_ENUM
                   || yytoken == Token_FLOAT
                   || yytoken == Token_INT
                   || yytoken == Token_LONG
                   || yytoken == Token_SHORT
                   || yytoken == Token_SIGNED
                   || yytoken == Token_STRUCT
                   || yytoken == Token_TYPEDEF_NAME
                   || yytoken == Token_UNION
                   || yytoken == Token_UNSIGNED
                   || yytoken == Token_VOID
                   || yytoken == Token_VOLATILE)
            {
                Struct_declarationAst *__node_138 = 0;
                if (!parseStruct_declaration(&__node_138))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Struct_declarationKind, "struct_declaration");
                    }
                    return false;
                }
                (*yynode)->struct_declarationSequence = snoc((*yynode)->struct_declarationSequence, __node_138, memoryPool);

            }
            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LBRACE)
        {
            if (yytoken != Token_LBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LBRACE, "{");
                }
                return false;
            }
            yylex();

            while (yytoken == Token_CHAR
                   || yytoken == Token_CONST
                   || yytoken == Token_DOUBLE
                   || yytoken == Token_ENUM
                   || yytoken == Token_FLOAT
                   || yytoken == Token_INT
                   || yytoken == Token_LONG
                   || yytoken == Token_SHORT
                   || yytoken == Token_SIGNED
                   || yytoken == Token_STRUCT
                   || yytoken == Token_TYPEDEF_NAME
                   || yytoken == Token_UNION
                   || yytoken == Token_UNSIGNED
                   || yytoken == Token_VOID
                   || yytoken == Token_VOLATILE)
            {
                Struct_declarationAst *__node_139 = 0;
                if (!parseStruct_declaration(&__node_139))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Struct_declarationKind, "struct_declaration");
                    }
                    return false;
                }
                (*yynode)->struct_declarationSequence = snoc((*yynode)->struct_declarationSequence, __node_139, memoryPool);

            }
            if (yytoken != Token_RBRACE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RBRACE, "}");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseType_attribute_identifier(Type_attribute_identifierAst **yynode)
{
    *yynode = create<Type_attribute_identifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_STAR)
    {
        if (yytoken == Token_LPAREN)
        {
            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            Type_attribute_identifierAst *__node_140 = 0;
            if (!parseType_attribute_identifier(&__node_140))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_attribute_identifierKind, "type_attribute_identifier");
                }
                return false;
            }
            (*yynode)->type_attribute_identifier = __node_140;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

            if (yytoken == Token_LPAREN)
            {
                if (yytoken != Token_LPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_LPAREN, "(");
                    }
                    return false;
                }
                yylex();

                if (true /*epsilon*/)
                {
                }
                else if (yytoken == Token_CHAR
                         || yytoken == Token_CONST
                         || yytoken == Token_DOUBLE
                         || yytoken == Token_ELLIPSIS
                         || yytoken == Token_ENUM
                         || yytoken == Token_FLOAT
                         || yytoken == Token_INT
                         || yytoken == Token_LONG
                         || yytoken == Token_SHORT
                         || yytoken == Token_SIGNED
                         || yytoken == Token_STRUCT
                         || yytoken == Token_TYPEDEF_NAME
                         || yytoken == Token_UNION
                         || yytoken == Token_UNSIGNED
                         || yytoken == Token_VOID
                         || yytoken == Token_VOLATILE)
                {
                    Function_pointer_parameterAst *__node_141 = 0;
                    if (!parseFunction_pointer_parameter(&__node_141))
                    {
                        if (!mBlockErrors)
                        {
                            expectedSymbol(AstNode::Function_pointer_parameterKind, "function_pointer_parameter");
                        }
                        return false;
                    }
                    (*yynode)->function_pointer_parameterSequence = snoc((*yynode)->function_pointer_parameterSequence, __node_141, memoryPool);

                    while (yytoken == Token_COMMA)
                    {
                        if (yytoken != Token_COMMA)
                        {
                            if (!mBlockErrors)
                            {
                                expectedToken(yytoken, Token_COMMA, ",");
                            }
                            return false;
                        }
                        yylex();

                        Function_pointer_parameterAst *__node_142 = 0;
                        if (!parseFunction_pointer_parameter(&__node_142))
                        {
                            if (!mBlockErrors)
                            {
                                expectedSymbol(AstNode::Function_pointer_parameterKind, "function_pointer_parameter");
                            }
                            return false;
                        }
                        (*yynode)->function_pointer_parameterSequence = snoc((*yynode)->function_pointer_parameterSequence, __node_142, memoryPool);

                    }
                }
                else
                {
                    return false;
                }
                if (yytoken != Token_RPAREN)
                {
                    if (!mBlockErrors)
                    {
                        expectedToken(yytoken, Token_RPAREN, ")");
                    }
                    return false;
                }
                yylex();

            }
            else if (true /*epsilon*/)
            {
            }
            else
            {
                return false;
            }
        }
        else if (yytoken == Token_STAR)
        {
            if (yytoken != Token_STAR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STAR, "*");
                }
                return false;
            }
            yylex();

            Type_attribute_identifierAst *__node_143 = 0;
            if (!parseType_attribute_identifier(&__node_143))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_attribute_identifierKind, "type_attribute_identifier");
                }
                return false;
            }
            (*yynode)->type_attribute_identifier = __node_143;

        }
        else if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseType_name(Type_nameAst **yynode)
{
    *yynode = create<Type_nameAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        Specifier_qualifierAst *__node_144 = 0;
        if (!parseSpecifier_qualifier(&__node_144))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Specifier_qualifierKind, "specifier_qualifier");
            }
            return false;
        }
        (*yynode)->specifier_qualifierSequence = snoc((*yynode)->specifier_qualifierSequence, __node_144, memoryPool);

        while (yytoken == Token_CHAR
               || yytoken == Token_CONST
               || yytoken == Token_DOUBLE
               || yytoken == Token_ENUM
               || yytoken == Token_FLOAT
               || yytoken == Token_INT
               || yytoken == Token_LONG
               || yytoken == Token_SHORT
               || yytoken == Token_SIGNED
               || yytoken == Token_STRUCT
               || yytoken == Token_TYPEDEF_NAME
               || yytoken == Token_UNION
               || yytoken == Token_UNSIGNED
               || yytoken == Token_VOID
               || yytoken == Token_VOLATILE)
        {
            Specifier_qualifierAst *__node_145 = 0;
            if (!parseSpecifier_qualifier(&__node_145))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Specifier_qualifierKind, "specifier_qualifier");
                }
                return false;
            }
            (*yynode)->specifier_qualifierSequence = snoc((*yynode)->specifier_qualifierSequence, __node_145, memoryPool);

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseType_qualifier(Type_qualifierAst **yynode)
{
    *yynode = create<Type_qualifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CONST
        || yytoken == Token_VOLATILE)
    {
        if (yytoken == Token_CONST)
        {
            if (yytoken != Token_CONST)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CONST, "const");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_VOLATILE)
        {
            if (yytoken != Token_VOLATILE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_VOLATILE, "volatile");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseType_specifier(Type_specifierAst **yynode)
{
    *yynode = create<Type_specifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID)
    {
        if (yytoken == Token_VOID)
        {
            if (yytoken != Token_VOID)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_VOID, "void");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_CHAR)
        {
            if (yytoken != Token_CHAR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_CHAR, "char");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_SHORT)
        {
            if (yytoken != Token_SHORT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SHORT, "short");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_INT)
        {
            if (yytoken != Token_INT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_INT, "int");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LONG)
        {
            if (yytoken != Token_LONG)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LONG, "long");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_FLOAT)
        {
            if (yytoken != Token_FLOAT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_FLOAT, "float");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_DOUBLE)
        {
            if (yytoken != Token_DOUBLE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_DOUBLE, "double");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_SIGNED)
        {
            if (yytoken != Token_SIGNED)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SIGNED, "signed");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_UNSIGNED)
        {
            if (yytoken != Token_UNSIGNED)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_UNSIGNED, "unsigned");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_STRUCT
                 || yytoken == Token_UNION)
        {
            Struct_or_union_specifierAst *__node_146 = 0;
            if (!parseStruct_or_union_specifier(&__node_146))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Struct_or_union_specifierKind, "struct_or_union_specifier");
                }
                return false;
            }
            (*yynode)->struct_or_union_specifier = __node_146;

        }
        else if (yytoken == Token_ENUM)
        {
            Enum_specifierAst *__node_147 = 0;
            if (!parseEnum_specifier(&__node_147))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Enum_specifierKind, "enum_specifier");
                }
                return false;
            }
            (*yynode)->enum_specifier = __node_147;

        }
        else if (yytoken == Token_TYPEDEF_NAME)
        {
            if (yytoken != Token_TYPEDEF_NAME)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TYPEDEF_NAME, "pre-defined type specification");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTyped_identifier(Typed_identifierAst **yynode)
{
    *yynode = create<Typed_identifierAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        Type_nameAst *__node_148 = 0;
        if (!parseType_name(&__node_148))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Type_nameKind, "type_name");
            }
            return false;
        }
        (*yynode)->type_name = __node_148;

        Type_attribute_identifierAst *__node_149 = 0;
        if (!parseType_attribute_identifier(&__node_149))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Type_attribute_identifierKind, "type_attribute_identifier");
            }
            return false;
        }
        (*yynode)->type_attribute_identifier = __node_149;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseTypedef_d(Typedef_dAst **yynode)
{
    *yynode = create<Typedef_dAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        if (yytoken == Token_STRUCT
            || yytoken == Token_UNION)
        {
            Struct_or_union_specifierAst *__node_150 = 0;
            if (!parseStruct_or_union_specifier(&__node_150))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Struct_or_union_specifierKind, "struct_or_union_specifier");
                }
                return false;
            }
            (*yynode)->struct_or_union_specifier = __node_150;

        }
        else if (yytoken == Token_ENUM)
        {
            Enum_specifierAst *__node_151 = 0;
            if (!parseEnum_specifier(&__node_151))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Enum_specifierKind, "enum_specifier");
                }
                return false;
            }
            (*yynode)->enum_specifier = __node_151;

        }
        else if (yytoken == Token_CHAR
                 || yytoken == Token_CONST
                 || yytoken == Token_DOUBLE
                 || yytoken == Token_ENUM
                 || yytoken == Token_FLOAT
                 || yytoken == Token_INT
                 || yytoken == Token_LONG
                 || yytoken == Token_SHORT
                 || yytoken == Token_SIGNED
                 || yytoken == Token_STRUCT
                 || yytoken == Token_TYPEDEF_NAME
                 || yytoken == Token_UNION
                 || yytoken == Token_UNSIGNED
                 || yytoken == Token_VOID
                 || yytoken == Token_VOLATILE)
        {
            Typed_identifierAst *__node_152 = 0;
            if (!parseTyped_identifier(&__node_152))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Typed_identifierKind, "typed_identifier");
                }
                return false;
            }
            (*yynode)->typed_identifier = __node_152;

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseUnary_expression(Unary_expressionAst **yynode)
{
    *yynode = create<Unary_expressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_LPAREN
        || yytoken == Token_MINUS
        || yytoken == Token_MINUS_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_PLUS_PLUS
        || yytoken == Token_SIZEOF
        || yytoken == Token_STAR
        || yytoken == Token_STRING_LITERAL
        || yytoken == Token_TILDE
        || yytoken == Token_X_CONSTANT)
    {
        if (yytoken == Token_IDENTIFIER
            || yytoken == Token_LPAREN
            || yytoken == Token_STRING_LITERAL
            || yytoken == Token_X_CONSTANT)
        {
            Postfix_expressionAst *__node_153 = 0;
            if (!parsePostfix_expression(&__node_153))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Postfix_expressionKind, "postfix_expression");
                }
                return false;
            }
            (*yynode)->postfix_expression = __node_153;

        }
        else if (yytoken == Token_PLUS_PLUS)
        {
            if (yytoken != Token_PLUS_PLUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS_PLUS, "++");
                }
                return false;
            }
            yylex();

            Unary_expressionAst *__node_154 = 0;
            if (!parseUnary_expression(&__node_154))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Unary_expressionKind, "unary_expression");
                }
                return false;
            }
            (*yynode)->unary_expression = __node_154;

        }
        else if (yytoken == Token_MINUS_MINUS)
        {
            if (yytoken != Token_MINUS_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS_MINUS, "--");
                }
                return false;
            }
            yylex();

            Unary_expressionAst *__node_155 = 0;
            if (!parseUnary_expression(&__node_155))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Unary_expressionKind, "unary_expression");
                }
                return false;
            }
            (*yynode)->unary_expression = __node_155;

        }
        else if (yytoken == Token_AND
                 || yytoken == Token_MINUS
                 || yytoken == Token_NOT
                 || yytoken == Token_PLUS
                 || yytoken == Token_STAR
                 || yytoken == Token_TILDE)
        {
            Unary_operatorAst *__node_156 = 0;
            if (!parseUnary_operator(&__node_156))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Unary_operatorKind, "unary_operator");
                }
                return false;
            }
            Cast_expressionAst *__node_157 = 0;
            if (!parseCast_expression(&__node_157))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Cast_expressionKind, "cast_expression");
                }
                return false;
            }
            (*yynode)->cast_expression = __node_157;

        }
        else if (yytoken == Token_SIZEOF)
        {
            if (yytoken != Token_SIZEOF)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SIZEOF, "sizeof");
                }
                return false;
            }
            yylex();

            if (yytoken != Token_LPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                }
                return false;
            }
            yylex();

            Type_nameAst *__node_158 = 0;
            if (!parseType_name(&__node_158))
            {
                if (!mBlockErrors)
                {
                    expectedSymbol(AstNode::Type_nameKind, "type_name");
                }
                return false;
            }
            (*yynode)->type_name = __node_158;

            if (yytoken != Token_RPAREN)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseUnary_operator(Unary_operatorAst **yynode)
{
    *yynode = create<Unary_operatorAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_AND
        || yytoken == Token_MINUS
        || yytoken == Token_NOT
        || yytoken == Token_PLUS
        || yytoken == Token_STAR
        || yytoken == Token_TILDE)
    {
        if (yytoken == Token_AND)
        {
            if (yytoken != Token_AND)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_AND, "&");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_STAR)
        {
            if (yytoken != Token_STAR)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_STAR, "*");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_PLUS)
        {
            if (yytoken != Token_PLUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_PLUS, "+");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_MINUS)
        {
            if (yytoken != Token_MINUS)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_MINUS, "-");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_TILDE)
        {
            if (yytoken != Token_TILDE)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_TILDE, "~");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_NOT)
        {
            if (yytoken != Token_NOT)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_NOT, "!");
                }
                return false;
            }
            yylex();

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseValue_declaration(Value_declarationAst **yynode)
{
    *yynode = create<Value_declarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        Typed_identifierAst *__node_159 = 0;
        if (!parseTyped_identifier(&__node_159))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Typed_identifierKind, "typed_identifier");
            }
            return false;
        }
        if (yytoken == Token_SEMICOLON)
        {
            if (yytoken != Token_SEMICOLON)
            {
                if (!mBlockErrors)
                {
                    expectedToken(yytoken, Token_SEMICOLON, ";");
                }
                return false;
            }
            yylex();

        }
        else if (yytoken == Token_LPAREN)
        {
            bool blockErrors_5 = blockErrors(true);
            qint64 try_startToken_5 = tokenStream->index() - 1;
            ParserState *try_startState_5 = copyCurrentState();
            {
                Function_definitionAst *__node_160 = 0;
                if (!parseFunction_definition(&__node_160))
                {
                    goto __catch_5;
                }
                (*yynode)->function_definition = __node_160;

            }
            blockErrors(blockErrors_5);
            if (try_startState_5)
                delete try_startState_5;

            if (false) // the only way to enter here is using goto
            {
__catch_5:
                if (try_startState_5)
                {
                    restoreState(try_startState_5);
                    delete try_startState_5;
                }
                blockErrors(blockErrors_5);
                rewind(try_startToken_5);

                Function_declarationAst *__node_161 = 0;
                if (!parseFunction_declaration(&__node_161))
                {
                    if (!mBlockErrors)
                    {
                        expectedSymbol(AstNode::Function_declarationKind, "function_declaration");
                    }
                    return false;
                }
                (*yynode)->function_declaration = __node_161;

            }

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseVariable_declaration(Variable_declarationAst **yynode)
{
    *yynode = create<Variable_declarationAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_CHAR
        || yytoken == Token_CONST
        || yytoken == Token_DOUBLE
        || yytoken == Token_ENUM
        || yytoken == Token_FLOAT
        || yytoken == Token_INT
        || yytoken == Token_LONG
        || yytoken == Token_SHORT
        || yytoken == Token_SIGNED
        || yytoken == Token_STRUCT
        || yytoken == Token_TYPEDEF_NAME
        || yytoken == Token_UNION
        || yytoken == Token_UNSIGNED
        || yytoken == Token_VOID
        || yytoken == Token_VOLATILE)
    {
        Typed_identifierAst *__node_162 = 0;
        if (!parseTyped_identifier(&__node_162))
        {
            if (!mBlockErrors)
            {
                expectedSymbol(AstNode::Typed_identifierKind, "typed_identifier");
            }
            return false;
        }
        (*yynode)->typed_identifier = __node_162;

        if (yytoken != Token_SEMICOLON)
        {
            if (!mBlockErrors)
            {
                expectedToken(yytoken, Token_SEMICOLON, ";");
            }
            return false;
        }
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}


} // end of namespace cc

