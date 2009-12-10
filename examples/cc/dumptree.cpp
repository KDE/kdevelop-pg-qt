/*
   (C) Copyright 2009 Jonathan Schmidt-Dominé <devel@the-user.org>
   Derived from the KDevelop-Java-Parser

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "dumptree.h"
#include "ccast.h"
#include "kdev-pg-token-stream.h"

#include <QtCore/QString>

#include <iostream>

static char const * const names[] = {
  "AND_expression",
  "Abstract_declarator",
  "Additive_expression",
  "Argument_expression_list",
  "Asm_against_mangling",
  "Asm_specifier",
  "Assignment_expression",
  "Assignment_operator",
  "Cast_expression",
  "Compound_statement",
  "Conditional_expression",
  "Constant",
  "Constant_expression",
  "Ddeclaration",
  "Declaration",
  "Declaration_header",
  "Declaration_parameter",
  "Declaration_specifier",
  "Declarator",
  "Direct_abstract_declarator",
  "Direct_declarator",
  "Direct_declarator_rest",
  "Document",
  "Enum_specifier",
  "Enumerator",
  "Equality_expression",
  "Exclusive_OR_expression",
  "Execution_block",
  "Expression",
  "Expression_statement",
  "Ext_expression",
  "External_Block",
  "External_declaration",
  "Function_declaration",
  "Function_definition",
  "Inclusive_OR_expression",
  "Init_declarator",
  "Initializer",
  "Inline_asm",
  "Iteration_statement",
  "Jump_statement",
  "Labeled_statement",
  "Logical_AND_expression",
  "Logical_OR_expression",
  "Multiplicative_expression",
  "Named_parameter",
  "Parameter",
  "Parameter_declaration",
  "Parameter_type_list",
  "Pointer",
  "Postfix_expression",
  "Postfix_expression_rest",
  "Primary_expression",
  "Relational_expression",
  "Selection_statement",
  "Shift_expression",
  "Specifier_qualifier",
  "Statement",
  "Storage_class_specifier",
  "Struct_declaration",
  "Struct_declarator",
  "Struct_or_union_specifier",
  "Translation_unit",
  "Type_name",
  "Type_name_d",
  "Type_qualifier",
  "Type_specifier",
  "Typed_identifier",
  "Typedef_d",
  "Unary_expression",
  "Unary_operator",
  "Value_Declaration",
  "Variable_declaration",
  "Variable_or_function"
};


using namespace cc;

DumpTree::DumpTree()
  : indent(0)
{
}

void DumpTree::dump( AstNode * node )
{
  visitNode(node);
}

void DumpTree::visitNode(AstNode *node)
{
  QString nodeText;
  if (node)
  {
    std::cout << QString(indent * 2, ' ').toLatin1().constData() << names[node->kind - 1000]
             <<  "[" << node->startToken << "," << node->endToken << "]" << nodeText.toLatin1().constData() << std::endl;
  }

  ++indent;
  DefaultVisitor::visitNode(node);
  --indent;

  if (node)
  {
    std::cout << QString(indent * 2, ' ').toLatin1().constData() << names[node->kind - 1000] << std::endl;
  }
}

DumpTree::~DumpTree( )
{
}

