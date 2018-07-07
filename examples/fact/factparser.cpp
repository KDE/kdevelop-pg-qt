// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "factparser.h"


#include "factlexer.h"
#include <QString>
#include <QDebug>

namespace fact
{

void Parser::tokenize( const QString& contents )
{
    m_contents = contents;
    Lexer lexer( this, contents );

    int kind = Parser::Token_EOF;
    do
    {
        kind = lexer.nextTokenKind();

        if ( !kind ) // when the lexer returns 0, the end of file is reached
            kind = Parser::Token_EOF;

        Parser::Token &t = tokenStream->next();
        t.kind = kind;
        if ( t.kind == Parser::Token_EOF )
        {
            t.begin = -1;
            t.end = -1;
        }
        else
        {
            t.begin = lexer.tokenBegin();
            t.end = lexer.tokenEnd();
        }

        if ( m_debug )
        {
            qDebug() << kind << "(" << t.begin << "," << t.end << ")::" << tokenText(t.begin, t.end);
        }

    }
    while ( kind != Parser::Token_EOF );

    this->yylex(); // produce the look ahead token
}

QString Parser::tokenText( qint64 begin, qint64 end ) const
{
    return m_contents.mid((int)begin, (int)end-begin+1);
}

void Parser::reportProblem( Parser::ProblemType type, const QString& message )
{
    if (type == Error)
        qDebug() << "** ERROR:" << message;
    else if (type == Warning)
        qDebug() << "** WARNING:" << message;
    else if (type == Info)
        qDebug() << "** Info:" << message;
}

// custom error recovery
void Parser::expectedToken(int /*expected*/, qint64 /*where*/, const QString& name)
{
    reportProblem(
        Parser::Error,
        QString("Expected token \"%1\"").arg(name));
}

void Parser::expectedSymbol(int /*expected_symbol*/, const QString& name)
{
    qint64 line;
    qint64 col;
    size_t index = tokenStream->index()-1;
    Token &token = tokenStream->token(index);
    qDebug() << "token starts at:" << token.begin;
    qDebug() << "index is:" << index;
    tokenStream->startPosition(index, &line, &col);
    QString tokenValue = tokenText(token.begin, token.end);
    reportProblem(
        Parser::Error,
        QString("Expected symbol \"%1\" (current token: \"%2\" [%3] at line: %4 col: %5)")
        .arg(name)
        .arg(token.kind != 0 ? tokenValue : "EOF")
        .arg(token.kind)
        .arg(line)
        .arg(col));
}

void Parser::setDebug( bool debug )
{
    m_debug = debug;
}

} // end of namespace fact


namespace fact
{

bool Parser::parseAssignmentStatement(AssignmentStatementAst **yynode)
{
    *yynode = create<AssignmentStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->id = -1;

    if (yytoken == Token_IDENTIFIER)
    {
        if (yytoken != Token_IDENTIFIER)
        {
            expectedToken(yytoken, Token_IDENTIFIER, "identifier");
            return false;
        }
        (*yynode)->id = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_ASSIGN)
        {
            expectedToken(yytoken, Token_ASSIGN, "=");
            return false;
        }
        yylex();

        ExpressionAst *__node_0 = 0;
        if (!parseExpression(&__node_0))
        {
            expectedSymbol(AstNode::ExpressionKind, "expression");
            return false;
        }
        (*yynode)->expr = __node_0;

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, ";");
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

bool Parser::parseBlockStatement(BlockStatementAst **yynode)
{
    *yynode = create<BlockStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            expectedToken(yytoken, Token_LBRACE, "{");
            return false;
        }
        yylex();

        while (yytoken == Token_IF
               || yytoken == Token_IDENTIFIER
               || yytoken == Token_RETURN
               || yytoken == Token_LBRACE)
        {
            StatementAst *__node_1 = 0;
            if (!parseStatement(&__node_1))
            {
                expectedSymbol(AstNode::StatementKind, "statement");
                return false;
            }
            (*yynode)->stmtSequence = snoc((*yynode)->stmtSequence, __node_1, memoryPool);

        }
        if (yytoken != Token_RBRACE)
        {
            expectedToken(yytoken, Token_RBRACE, "}");
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

bool Parser::parseBody(BodyAst **yynode)
{
    *yynode = create<BodyAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_LBRACE)
    {
        if (yytoken != Token_LBRACE)
        {
            expectedToken(yytoken, Token_LBRACE, "{");
            return false;
        }
        yylex();

        while (yytoken == Token_VAR)
        {
            DeclarationAst *__node_2 = 0;
            if (!parseDeclaration(&__node_2))
            {
                expectedSymbol(AstNode::DeclarationKind, "declaration");
                return false;
            }
            (*yynode)->declSequence = snoc((*yynode)->declSequence, __node_2, memoryPool);

        }
        while (yytoken == Token_IF
               || yytoken == Token_IDENTIFIER
               || yytoken == Token_RETURN
               || yytoken == Token_LBRACE)
        {
            StatementAst *__node_3 = 0;
            if (!parseStatement(&__node_3))
            {
                expectedSymbol(AstNode::StatementKind, "statement");
                return false;
            }
            (*yynode)->stmtSequence = snoc((*yynode)->stmtSequence, __node_3, memoryPool);

        }
        if (yytoken != Token_RBRACE)
        {
            expectedToken(yytoken, Token_RBRACE, "}");
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

bool Parser::parseCondition(ConditionAst **yynode)
{
    *yynode = create<ConditionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_NUMBER
        || yytoken == Token_IDENTIFIER)
    {
        ExpressionAst *__node_4 = 0;
        if (!parseExpression(&__node_4))
        {
            expectedSymbol(AstNode::ExpressionKind, "expression");
            return false;
        }
        (*yynode)->leftExpr = __node_4;

        if (yytoken != Token_EQUAL)
        {
            expectedToken(yytoken, Token_EQUAL, "==");
            return false;
        }
        yylex();

        ExpressionAst *__node_5 = 0;
        if (!parseExpression(&__node_5))
        {
            expectedSymbol(AstNode::ExpressionKind, "expression");
            return false;
        }
        (*yynode)->rightExpr = __node_5;

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

    if (yytoken == Token_VAR)
    {
        if (yytoken != Token_VAR)
        {
            expectedToken(yytoken, Token_VAR, "var");
            return false;
        }
        yylex();

        VariableAst *__node_6 = 0;
        if (!parseVariable(&__node_6))
        {
            expectedSymbol(AstNode::VariableKind, "variable");
            return false;
        }
        (*yynode)->var = __node_6;

        while (yytoken == Token_COMMA)
        {
            if (yytoken != Token_COMMA)
            {
                expectedToken(yytoken, Token_COMMA, ",");
                return false;
            }
            yylex();

            VariableAst *__node_7 = 0;
            if (!parseVariable(&__node_7))
            {
                expectedSymbol(AstNode::VariableKind, "variable");
                return false;
            }
            (*yynode)->var = __node_7;

        }
        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, ";");
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

bool Parser::parseExpression(ExpressionAst **yynode)
{
    *yynode = create<ExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_NUMBER
        || yytoken == Token_IDENTIFIER)
    {
        MultExpressionAst *__node_8 = 0;
        if (!parseMultExpression(&__node_8))
        {
            expectedSymbol(AstNode::MultExpressionKind, "multExpression");
            return false;
        }
        (*yynode)->leftExpr = __node_8;

        while (yytoken == Token_MINUS)
        {
            if (yytoken != Token_MINUS)
            {
                expectedToken(yytoken, Token_MINUS, "-");
                return false;
            }
            yylex();

            MultExpressionAst *__node_9 = 0;
            if (!parseMultExpression(&__node_9))
            {
                expectedSymbol(AstNode::MultExpressionKind, "multExpression");
                return false;
            }
            (*yynode)->rightExpr = __node_9;

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseFunctionDefinition(FunctionDefinitionAst **yynode)
{
    *yynode = create<FunctionDefinitionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->id = -1;

    if (yytoken == Token_FUNCTION)
    {
        if (yytoken != Token_FUNCTION)
        {
            expectedToken(yytoken, Token_FUNCTION, "function");
            return false;
        }
        yylex();

        if (yytoken != Token_IDENTIFIER)
        {
            expectedToken(yytoken, Token_IDENTIFIER, "identifier");
            return false;
        }
        (*yynode)->id = tokenStream->index() - 1;
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "(");
            return false;
        }
        yylex();

        if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                return false;
            }
            (*yynode)->paramSequence = snoc((*yynode)->paramSequence, tokenStream->index() - 1, memoryPool);
            yylex();

            while (yytoken == Token_COMMA)
            {
                if (yytoken != Token_COMMA)
                {
                    expectedToken(yytoken, Token_COMMA, ",");
                    return false;
                }
                yylex();

                if (yytoken != Token_IDENTIFIER)
                {
                    expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                    return false;
                }
                (*yynode)->paramSequence = snoc((*yynode)->paramSequence, tokenStream->index() - 1, memoryPool);
                yylex();

            }
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
            expectedToken(yytoken, Token_RPAREN, ")");
            return false;
        }
        yylex();

        BodyAst *__node_10 = 0;
        if (!parseBody(&__node_10))
        {
            expectedSymbol(AstNode::BodyKind, "body");
            return false;
        }
        (*yynode)->body = __node_10;

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parseIfStatement(IfStatementAst **yynode)
{
    *yynode = create<IfStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IF)
    {
        if (yytoken != Token_IF)
        {
            expectedToken(yytoken, Token_IF, "if");
            return false;
        }
        yylex();

        if (yytoken != Token_LPAREN)
        {
            expectedToken(yytoken, Token_LPAREN, "(");
            return false;
        }
        yylex();

        ConditionAst *__node_11 = 0;
        if (!parseCondition(&__node_11))
        {
            expectedSymbol(AstNode::ConditionKind, "condition");
            return false;
        }
        (*yynode)->cond = __node_11;

        if (yytoken != Token_RPAREN)
        {
            expectedToken(yytoken, Token_RPAREN, ")");
            return false;
        }
        yylex();

        StatementAst *__node_12 = 0;
        if (!parseStatement(&__node_12))
        {
            expectedSymbol(AstNode::StatementKind, "statement");
            return false;
        }
        (*yynode)->ifStmt = __node_12;

        if (yytoken == Token_ELSE)
        {
            if (yytoken != Token_ELSE)
            {
                expectedToken(yytoken, Token_ELSE, "else");
                return false;
            }
            yylex();

            StatementAst *__node_13 = 0;
            if (!parseStatement(&__node_13))
            {
                expectedSymbol(AstNode::StatementKind, "statement");
                return false;
            }
            (*yynode)->elseStmt = __node_13;

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

bool Parser::parseMultExpression(MultExpressionAst **yynode)
{
    *yynode = create<MultExpressionAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_NUMBER
        || yytoken == Token_IDENTIFIER)
    {
        PrimaryAst *__node_14 = 0;
        if (!parsePrimary(&__node_14))
        {
            expectedSymbol(AstNode::PrimaryKind, "primary");
            return false;
        }
        (*yynode)->leftExpr = __node_14;

        while (yytoken == Token_STAR)
        {
            if (yytoken != Token_STAR)
            {
                expectedToken(yytoken, Token_STAR, "*");
                return false;
            }
            yylex();

            PrimaryAst *__node_15 = 0;
            if (!parsePrimary(&__node_15))
            {
                expectedSymbol(AstNode::PrimaryKind, "primary");
                return false;
            }
            (*yynode)->rightExpr = __node_15;

        }
    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}

bool Parser::parsePrimary(PrimaryAst **yynode)
{
    *yynode = create<PrimaryAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->num = -1;
    (*yynode)->id = -1;

    if (yytoken == Token_NUMBER
        || yytoken == Token_IDENTIFIER)
    {
        if (yytoken == Token_NUMBER)
        {
            if (yytoken != Token_NUMBER)
            {
                expectedToken(yytoken, Token_NUMBER, "integer literal");
                return false;
            }
            (*yynode)->num = tokenStream->index() - 1;
            yylex();

        }
        else if (yytoken == Token_IDENTIFIER)
        {
            if (yytoken != Token_IDENTIFIER)
            {
                expectedToken(yytoken, Token_IDENTIFIER, "identifier");
                return false;
            }
            (*yynode)->id = tokenStream->index() - 1;
            yylex();

            if (yytoken == Token_LPAREN)
            {
                if (yytoken != Token_LPAREN)
                {
                    expectedToken(yytoken, Token_LPAREN, "(");
                    return false;
                }
                yylex();

                ExpressionAst *__node_16 = 0;
                if (!parseExpression(&__node_16))
                {
                    expectedSymbol(AstNode::ExpressionKind, "expression");
                    return false;
                }
                (*yynode)->argumentSequence = snoc((*yynode)->argumentSequence, __node_16, memoryPool);

                while (yytoken == Token_COMMA)
                {
                    if (yytoken != Token_COMMA)
                    {
                        expectedToken(yytoken, Token_COMMA, ",");
                        return false;
                    }
                    yylex();

                    ExpressionAst *__node_17 = 0;
                    if (!parseExpression(&__node_17))
                    {
                        expectedSymbol(AstNode::ExpressionKind, "expression");
                        return false;
                    }
                    (*yynode)->argumentSequence = snoc((*yynode)->argumentSequence, __node_17, memoryPool);

                }
                if (yytoken != Token_RPAREN)
                {
                    expectedToken(yytoken, Token_RPAREN, ")");
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

bool Parser::parseProgram(ProgramAst **yynode)
{
    *yynode = create<ProgramAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_FUNCTION || yytoken == Token_EOF)
    {
        while (yytoken == Token_FUNCTION)
        {
            FunctionDefinitionAst *__node_18 = 0;
            if (!parseFunctionDefinition(&__node_18))
            {
                expectedSymbol(AstNode::FunctionDefinitionKind, "functionDefinition");
                return false;
            }
            (*yynode)->funSequence = snoc((*yynode)->funSequence, __node_18, memoryPool);

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

bool Parser::parseReturnStatement(ReturnStatementAst **yynode)
{
    *yynode = create<ReturnStatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_RETURN)
    {
        if (yytoken != Token_RETURN)
        {
            expectedToken(yytoken, Token_RETURN, "return");
            return false;
        }
        yylex();

        ExpressionAst *__node_19 = 0;
        if (!parseExpression(&__node_19))
        {
            expectedSymbol(AstNode::ExpressionKind, "expression");
            return false;
        }
        (*yynode)->expr = __node_19;

        if (yytoken != Token_SEMICOLON)
        {
            expectedToken(yytoken, Token_SEMICOLON, ";");
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

bool Parser::parseStatement(StatementAst **yynode)
{
    *yynode = create<StatementAst>();

    (*yynode)->startToken = tokenStream->index() - 1;

    if (yytoken == Token_IF
        || yytoken == Token_IDENTIFIER
        || yytoken == Token_RETURN
        || yytoken == Token_LBRACE)
    {
        if (yytoken == Token_IDENTIFIER)
        {
            AssignmentStatementAst *__node_20 = 0;
            if (!parseAssignmentStatement(&__node_20))
            {
                expectedSymbol(AstNode::AssignmentStatementKind, "assignmentStatement");
                return false;
            }
            (*yynode)->assignStmt = __node_20;

        }
        else if (yytoken == Token_IF)
        {
            IfStatementAst *__node_21 = 0;
            if (!parseIfStatement(&__node_21))
            {
                expectedSymbol(AstNode::IfStatementKind, "ifStatement");
                return false;
            }
            (*yynode)->ifStmt = __node_21;

        }
        else if (yytoken == Token_LBRACE)
        {
            BlockStatementAst *__node_22 = 0;
            if (!parseBlockStatement(&__node_22))
            {
                expectedSymbol(AstNode::BlockStatementKind, "blockStatement");
                return false;
            }
            (*yynode)->blockStmt = __node_22;

        }
        else if (yytoken == Token_RETURN)
        {
            ReturnStatementAst *__node_23 = 0;
            if (!parseReturnStatement(&__node_23))
            {
                expectedSymbol(AstNode::ReturnStatementKind, "returnStatement");
                return false;
            }
            (*yynode)->returnStmt = __node_23;

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

bool Parser::parseVariable(VariableAst **yynode)
{
    *yynode = create<VariableAst>();

    (*yynode)->startToken = tokenStream->index() - 1;
    (*yynode)->id = -1;

    if (yytoken == Token_IDENTIFIER)
    {
        if (yytoken != Token_IDENTIFIER)
        {
            expectedToken(yytoken, Token_IDENTIFIER, "identifier");
            return false;
        }
        (*yynode)->id = tokenStream->index() - 1;
        yylex();

    }
    else
    {
        return false;
    }

    (*yynode)->endToken = tokenStream->index() - 2;

    return true;
}


} // end of namespace fact

