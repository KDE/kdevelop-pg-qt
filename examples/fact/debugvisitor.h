/* 
 * Copyright 2008 Niko Sams <niko.sams@gmail.com>
 * Based on QMake Parser Copyright 2006 Andreas Pakulat <apaku@gmx.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
 
#ifndef FACTDEBUGVISITOR_H
#define FACTDEBUGVISITOR_H

#include <factdefaultvisitor.h>

namespace fact {
class Parser;

class DebugVisitor : public DefaultVisitor
{
public:
    DebugVisitor(Parser* parser);
    void visitAssignmentStatement(AssignmentStatementAst *node);
    void visitBlockStatement(BlockStatementAst *node);
    void visitBody(BodyAst *node);
    void visitCondition(ConditionAst *node);
    void visitDeclaration(DeclarationAst *node);
    void visitExpression(ExpressionAst *node);
    void visitFunctionDefinition(FunctionDefinitionAst *node);
    void visitIfStatement(IfStatementAst *node);
    void visitMultExpression(MultExpressionAst *node);
    void visitPrimary(PrimaryAst *node);
    void visitProgram(ProgramAst *node);
    void visitReturnStatement(ReturnStatementAst *node);
    void visitStatement(StatementAst *node);
    void visitVariable(VariableAst *node);

    QString getTokenInfo(qint64 idx);
    QString getIndent();
private:
    Parser* m_parser;
    int m_indent;
};

}

#endif

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
