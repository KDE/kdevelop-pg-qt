// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "factdefaultvisitor.h"

namespace fact
{

void DefaultVisitor::visitAssignmentStatement(AssignmentStatementAst *node)
{
    visitNode(node->expr);
}

void DefaultVisitor::visitBlockStatement(BlockStatementAst *node)
{
    if (node->stmtSequence)
    {
        const KDevPG::ListNode<StatementAst*> *__it = node->stmtSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitBody(BodyAst *node)
{
    if (node->declSequence)
    {
        const KDevPG::ListNode<DeclarationAst*> *__it = node->declSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->stmtSequence)
    {
        const KDevPG::ListNode<StatementAst*> *__it = node->stmtSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitCondition(ConditionAst *node)
{
    visitNode(node->leftExpr);
    visitNode(node->rightExpr);
}

void DefaultVisitor::visitDeclaration(DeclarationAst *node)
{
    visitNode(node->var);
}

void DefaultVisitor::visitExpression(ExpressionAst *node)
{
    visitNode(node->leftExpr);
    visitNode(node->rightExpr);
}

void DefaultVisitor::visitFunctionDefinition(FunctionDefinitionAst *node)
{
    visitNode(node->body);
}

void DefaultVisitor::visitIfStatement(IfStatementAst *node)
{
    visitNode(node->cond);
    visitNode(node->ifStmt);
    visitNode(node->elseStmt);
}

void DefaultVisitor::visitMultExpression(MultExpressionAst *node)
{
    visitNode(node->leftExpr);
    visitNode(node->rightExpr);
}

void DefaultVisitor::visitPrimary(PrimaryAst *node)
{
    if (node->argumentSequence)
    {
        const KDevPG::ListNode<ExpressionAst*> *__it = node->argumentSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitProgram(ProgramAst *node)
{
    if (node->funSequence)
    {
        const KDevPG::ListNode<FunctionDefinitionAst*> *__it = node->funSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitReturnStatement(ReturnStatementAst *node)
{
    visitNode(node->expr);
}

void DefaultVisitor::visitStatement(StatementAst *node)
{
    visitNode(node->assignStmt);
    visitNode(node->ifStmt);
    visitNode(node->blockStmt);
    visitNode(node->returnStmt);
}

void DefaultVisitor::visitVariable(VariableAst *)
{
}


} // end of namespace fact

