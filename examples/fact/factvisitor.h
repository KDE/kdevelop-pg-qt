// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef FACT_VISITOR_H_INCLUDED
#define FACT_VISITOR_H_INCLUDED

#include "factast.h"

namespace fact
{

class  Visitor
{
    typedef void (Visitor::*ParserFuncType)(AstNode *);
    static ParserFuncType sParserTable[];

public:
    virtual ~Visitor() {}
    virtual void visitNode(AstNode *node)
    {
        if (node) (this->*sParserTable[node->kind - 1000])(node);
    }
    virtual void visitAssignmentStatement(AssignmentStatementAst *) {}
    virtual void visitBlockStatement(BlockStatementAst *) {}
    virtual void visitBody(BodyAst *) {}
    virtual void visitCondition(ConditionAst *) {}
    virtual void visitDeclaration(DeclarationAst *) {}
    virtual void visitExpression(ExpressionAst *) {}
    virtual void visitFunctionDefinition(FunctionDefinitionAst *) {}
    virtual void visitIfStatement(IfStatementAst *) {}
    virtual void visitMultExpression(MultExpressionAst *) {}
    virtual void visitPrimary(PrimaryAst *) {}
    virtual void visitProgram(ProgramAst *) {}
    virtual void visitReturnStatement(ReturnStatementAst *) {}
    virtual void visitStatement(StatementAst *) {}
    virtual void visitVariable(VariableAst *) {}
};

} // end of namespace fact

#endif

