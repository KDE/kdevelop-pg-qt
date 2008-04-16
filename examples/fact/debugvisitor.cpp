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

#include "debugvisitor.h"
#include "factparser.h"
#include <QDebug>

namespace fact {

DebugVisitor::DebugVisitor(Parser* parser)
  : m_parser(parser), m_indent(0)
{
}

QString DebugVisitor::getTokenInfo(qint64 idx)
{
    qint64 line,col;
    Parser::Token token = m_parser->tokenStream->token(idx);
    m_parser->tokenStream->startPosition(idx,&line,&col);
    return QString("%1,%2,%3")
        .arg(line)
        .arg(col)
        .arg(m_parser->tokenText(token.begin,token.end).replace("\n","\\n"));
}

QString DebugVisitor::getIndent()
{
  return QString().fill(' ', m_indent*4);
}

void DebugVisitor::visitAssignmentStatement(AssignmentStatementAst *node)
{
    qDebug() << getIndent() << "BEGIN(AssignmentStatement)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    qDebug() << getIndent() << "id: " << node->id;
    DefaultVisitor::visitAssignmentStatement( node );
    m_indent--;
    qDebug() << getIndent() << "END(AssignmentStatement)(" << getTokenInfo(node->startToken) << ")";
}

void DebugVisitor::visitBlockStatement(BlockStatementAst *node)
{
    qDebug() << getIndent() << "BEGIN(BlockStatement)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    DefaultVisitor::visitBlockStatement( node );
    m_indent--;
    qDebug() << getIndent() << "END(BlockStatement)(" << getTokenInfo(node->startToken) << ")";
}

void DebugVisitor::visitBody(BodyAst *node)
{
    qDebug() << getIndent() << "BEGIN(Body)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    DefaultVisitor::visitBody( node );
    m_indent--;
    qDebug() << getIndent() << "END(Body)(" << getTokenInfo(node->startToken) << ")";
}

void DebugVisitor::visitCondition(ConditionAst *node)
{
    qDebug() << getIndent() << "BEGIN(Condition)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    DefaultVisitor::visitCondition( node );
    m_indent--;
    qDebug() << getIndent() << "END(Condition)(" << getTokenInfo(node->startToken) << ")";
}

void DebugVisitor::visitDeclaration(DeclarationAst *node)
{
    qDebug() << getIndent() << "BEGIN(Declaration)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    DefaultVisitor::visitDeclaration( node );
    m_indent--;
    qDebug() << getIndent() << "END(Declaration)(" << getTokenInfo(node->startToken) << ")";
}

void DebugVisitor::visitExpression(ExpressionAst *node)
{
    qDebug() << getIndent() << "BEGIN(Expressin)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    DefaultVisitor::visitExpression( node );
    m_indent--;
    qDebug() << getIndent() << "END(Expressin)(" << getTokenInfo(node->startToken) << ")";
}

void DebugVisitor::visitFunctionDefinition(FunctionDefinitionAst *node)
{
    qDebug() << getIndent() << "BEGIN(FunctionDefinition)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    qDebug() << getIndent() << "id: " << node->id;
    DefaultVisitor::visitFunctionDefinition( node );
    m_indent--;
    qDebug() << getIndent() << "END(FunctionDefinition)(" << getTokenInfo(node->startToken) << ")";
}

void DebugVisitor::visitIfStatement(IfStatementAst *node)
{
    qDebug() << getIndent() << "BEGIN(IfStatement)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    DefaultVisitor::visitIfStatement( node );
    m_indent--;
    qDebug() << getIndent() << "END(IfStatement)(" << getTokenInfo(node->startToken) << ")";
}

void DebugVisitor::visitMultExpression(MultExpressionAst *node)
{
    qDebug() << getIndent() << "BEGIN(MultExpression)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    DefaultVisitor::visitMultExpression( node );
    m_indent--;
    qDebug() << getIndent() << "END(MultExpression)(" << getTokenInfo(node->startToken) << ")";
}

void DebugVisitor::visitPrimary(PrimaryAst *node)
{
    qDebug() << getIndent() << "BEGIN(Primary)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    qDebug() << getIndent() << "id: " << node->id;
    qDebug() << getIndent() << "num: " << node->num;
    DefaultVisitor::visitPrimary( node );
    m_indent--;
    qDebug() << getIndent() << "END(Primary)(" << getTokenInfo(node->startToken) << ")";
}

void DebugVisitor::visitProgram(ProgramAst *node)
{
    qDebug() << getIndent() << "BEGIN(Program)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    DefaultVisitor::visitProgram( node );
    m_indent--;
    qDebug() << getIndent() << "END(Program)(" << getTokenInfo(node->startToken) << ")";
}

void DebugVisitor::visitReturnStatement(ReturnStatementAst *node)
{
    qDebug() << getIndent() << "BEGIN(ReturnStatement)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    DefaultVisitor::visitReturnStatement( node );
    m_indent--;
    qDebug() << getIndent() << "END(ReturnStatement)(" << getTokenInfo(node->startToken) << ")";
}

void DebugVisitor::visitStatement(StatementAst *node)
{
    qDebug() << getIndent() << "BEGIN(Statement)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    DefaultVisitor::visitStatement( node );
    m_indent--;
    qDebug() << getIndent() << "END(Statement)(" << getTokenInfo(node->startToken) << ")";
}

void DebugVisitor::visitVariable(VariableAst *node)
{
    qDebug() << getIndent() << "BEGIN(Variable)(" << getTokenInfo(node->startToken) << ")";
    m_indent++;
    qDebug() << getIndent() << "id: " << node->id;
    DefaultVisitor::visitVariable( node );
    m_indent--;
    qDebug() << getIndent() << "END(Variable)(" << getTokenInfo(node->startToken) << ")";
}

}

// kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
