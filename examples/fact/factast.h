// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef FACT_AST_H_INCLUDED
#define FACT_AST_H_INCLUDED

#include <QList>
#include <kdev-pg-list.h>



#include <QString>

namespace fact
{
class Lexer;
}


namespace fact
{

struct AssignmentStatementAst;
struct BlockStatementAst;
struct BodyAst;
struct ConditionAst;
struct DeclarationAst;
struct ExpressionAst;
struct FunctionDefinitionAst;
struct IfStatementAst;
struct MultExpressionAst;
struct PrimaryAst;
struct ProgramAst;
struct ReturnStatementAst;
struct StatementAst;
struct VariableAst;


struct  AstNode
{
    enum AstNodeKind
    {
        AssignmentStatementKind = 1000,
        BlockStatementKind = 1001,
        BodyKind = 1002,
        ConditionKind = 1003,
        DeclarationKind = 1004,
        ExpressionKind = 1005,
        FunctionDefinitionKind = 1006,
        IfStatementKind = 1007,
        MultExpressionKind = 1008,
        PrimaryKind = 1009,
        ProgramKind = 1010,
        ReturnStatementKind = 1011,
        StatementKind = 1012,
        VariableKind = 1013,
        AST_NODE_KIND_COUNT
    };

    int kind;
    qint64 startToken;
    qint64 endToken;
};

struct  AssignmentStatementAst: public AstNode
{
    enum { KIND = AssignmentStatementKind };

    qint64 id;
    ExpressionAst *expr;
};

struct  BlockStatementAst: public AstNode
{
    enum { KIND = BlockStatementKind };

    const KDevPG::ListNode<StatementAst *> *stmtSequence;
};

struct  BodyAst: public AstNode
{
    enum { KIND = BodyKind };

    const KDevPG::ListNode<DeclarationAst *> *declSequence;
    const KDevPG::ListNode<StatementAst *> *stmtSequence;
};

struct  ConditionAst: public AstNode
{
    enum { KIND = ConditionKind };

    ExpressionAst *leftExpr;
    ExpressionAst *rightExpr;
};

struct  DeclarationAst: public AstNode
{
    enum { KIND = DeclarationKind };

    VariableAst *var;
};

struct  ExpressionAst: public AstNode
{
    enum { KIND = ExpressionKind };

    MultExpressionAst *leftExpr;
    MultExpressionAst *rightExpr;
};

struct  FunctionDefinitionAst: public AstNode
{
    enum { KIND = FunctionDefinitionKind };

    qint64 id;
    const KDevPG::ListNode<qint64 > *paramSequence;
    BodyAst *body;
};

struct  IfStatementAst: public AstNode
{
    enum { KIND = IfStatementKind };

    ConditionAst *cond;
    StatementAst *ifStmt;
    StatementAst *elseStmt;
};

struct  MultExpressionAst: public AstNode
{
    enum { KIND = MultExpressionKind };

    PrimaryAst *leftExpr;
    PrimaryAst *rightExpr;
};

struct  PrimaryAst: public AstNode
{
    enum { KIND = PrimaryKind };

    qint64 num;
    qint64 id;
    const KDevPG::ListNode<ExpressionAst *> *argumentSequence;
};

struct  ProgramAst: public AstNode
{
    enum { KIND = ProgramKind };

    const KDevPG::ListNode<FunctionDefinitionAst *> *funSequence;
};

struct  ReturnStatementAst: public AstNode
{
    enum { KIND = ReturnStatementKind };

    ExpressionAst *expr;
};

struct  StatementAst: public AstNode
{
    enum { KIND = StatementKind };

    AssignmentStatementAst *assignStmt;
    IfStatementAst *ifStmt;
    BlockStatementAst *blockStmt;
    ReturnStatementAst *returnStmt;
};

struct  VariableAst: public AstNode
{
    enum { KIND = VariableKind };

    qint64 id;
};



} // end of namespace fact

#endif

