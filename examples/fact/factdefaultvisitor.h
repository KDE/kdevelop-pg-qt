// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef FACT_DEFAULT_VISITOR_H_INCLUDED
#define FACT_DEFAULT_VISITOR_H_INCLUDED

#include "factvisitor.h"

namespace fact
{

class  DefaultVisitor: public Visitor
{
public:
    virtual void visitAssignmentStatement(AssignmentStatementAst *node);
    virtual void visitBlockStatement(BlockStatementAst *node);
    virtual void visitBody(BodyAst *node);
    virtual void visitCondition(ConditionAst *node);
    virtual void visitDeclaration(DeclarationAst *node);
    virtual void visitExpression(ExpressionAst *node);
    virtual void visitFunctionDefinition(FunctionDefinitionAst *node);
    virtual void visitIfStatement(IfStatementAst *node);
    virtual void visitMultExpression(MultExpressionAst *node);
    virtual void visitPrimary(PrimaryAst *node);
    virtual void visitProgram(ProgramAst *node);
    virtual void visitReturnStatement(ReturnStatementAst *node);
    virtual void visitStatement(StatementAst *node);
    virtual void visitVariable(VariableAst *node);
};

} // end of namespace fact

#endif

