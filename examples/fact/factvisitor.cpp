// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "factvisitor.h"

namespace fact
{

Visitor::ParserFuncType Visitor::sParserTable[] =
{
    reinterpret_cast<ParserFuncType>(&Visitor::visitAssignmentStatement),
    reinterpret_cast<ParserFuncType>(&Visitor::visitBlockStatement),
    reinterpret_cast<ParserFuncType>(&Visitor::visitBody),
    reinterpret_cast<ParserFuncType>(&Visitor::visitCondition),
    reinterpret_cast<ParserFuncType>(&Visitor::visitDeclaration),
    reinterpret_cast<ParserFuncType>(&Visitor::visitExpression),
    reinterpret_cast<ParserFuncType>(&Visitor::visitFunctionDefinition),
    reinterpret_cast<ParserFuncType>(&Visitor::visitIfStatement),
    reinterpret_cast<ParserFuncType>(&Visitor::visitMultExpression),
    reinterpret_cast<ParserFuncType>(&Visitor::visitPrimary),
    reinterpret_cast<ParserFuncType>(&Visitor::visitProgram),
    reinterpret_cast<ParserFuncType>(&Visitor::visitReturnStatement),
    reinterpret_cast<ParserFuncType>(&Visitor::visitStatement),
    reinterpret_cast<ParserFuncType>(&Visitor::visitVariable)
}; // sParserTable[]

} // end of namespace fact

