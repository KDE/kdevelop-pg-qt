// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef CC_DEFAULT_VISITOR_H_INCLUDED
#define CC_DEFAULT_VISITOR_H_INCLUDED

#include "ccvisitor.h"

namespace cc
{

class  DefaultVisitor: public Visitor
{
public:
    virtual void visitAND_expression(AND_expressionAst *node);
    virtual void visitAbstract_declarator(Abstract_declaratorAst *node);
    virtual void visitAdditive_expression(Additive_expressionAst *node);
    virtual void visitArgument_expression_list(Argument_expression_listAst *node);
    virtual void visitAssignment_expression(Assignment_expressionAst *node);
    virtual void visitAssignment_operator(Assignment_operatorAst *node);
    virtual void visitCast_expression(Cast_expressionAst *node);
    virtual void visitCompound_statement(Compound_statementAst *node);
    virtual void visitConditional_expression(Conditional_expressionAst *node);
    virtual void visitConstant(ConstantAst *node);
    virtual void visitConstant_expression(Constant_expressionAst *node);
    virtual void visitDdeclaration(DdeclarationAst *node);
    virtual void visitDeclaration(DeclarationAst *node);
    virtual void visitDeclaration_header(Declaration_headerAst *node);
    virtual void visitDeclaration_parameter(Declaration_parameterAst *node);
    virtual void visitDeclaration_specifier(Declaration_specifierAst *node);
    virtual void visitDeclarator(DeclaratorAst *node);
    virtual void visitDirect_abstract_declarator(Direct_abstract_declaratorAst *node);
    virtual void visitDirect_declarator(Direct_declaratorAst *node);
    virtual void visitDirect_declarator_rest(Direct_declarator_restAst *node);
    virtual void visitDocument(DocumentAst *node);
    virtual void visitEnum_specifier(Enum_specifierAst *node);
    virtual void visitEnumerator(EnumeratorAst *node);
    virtual void visitEquality_expression(Equality_expressionAst *node);
    virtual void visitExclusive_OR_expression(Exclusive_OR_expressionAst *node);
    virtual void visitExecution_block(Execution_blockAst *node);
    virtual void visitExpression(ExpressionAst *node);
    virtual void visitExpression_statement(Expression_statementAst *node);
    virtual void visitExternal_block(External_blockAst *node);
    virtual void visitFunction_declaration(Function_declarationAst *node);
    virtual void visitFunction_definition(Function_definitionAst *node);
    virtual void visitFunction_pointer_parameter(Function_pointer_parameterAst *node);
    virtual void visitInclusive_OR_expression(Inclusive_OR_expressionAst *node);
    virtual void visitInit_declarator(Init_declaratorAst *node);
    virtual void visitInitializer(InitializerAst *node);
    virtual void visitIteration_statement(Iteration_statementAst *node);
    virtual void visitJump_statement(Jump_statementAst *node);
    virtual void visitLabeled_statement(Labeled_statementAst *node);
    virtual void visitLogical_AND_expression(Logical_AND_expressionAst *node);
    virtual void visitLogical_OR_expression(Logical_OR_expressionAst *node);
    virtual void visitMultiplicative_expression(Multiplicative_expressionAst *node);
    virtual void visitNamed_parameter(Named_parameterAst *node);
    virtual void visitParameter(ParameterAst *node);
    virtual void visitParameter_declaration(Parameter_declarationAst *node);
    virtual void visitParameter_type_list(Parameter_type_listAst *node);
    virtual void visitPointer(PointerAst *node);
    virtual void visitPostfix_expression(Postfix_expressionAst *node);
    virtual void visitPostfix_expression_rest(Postfix_expression_restAst *node);
    virtual void visitPrimary_expression(Primary_expressionAst *node);
    virtual void visitRelational_expression(Relational_expressionAst *node);
    virtual void visitSelection_statement(Selection_statementAst *node);
    virtual void visitShift_expression(Shift_expressionAst *node);
    virtual void visitSpecifier_qualifier(Specifier_qualifierAst *node);
    virtual void visitStatement(StatementAst *node);
    virtual void visitStorage_class_specifier(Storage_class_specifierAst *node);
    virtual void visitStruct_declaration(Struct_declarationAst *node);
    virtual void visitStruct_declarator(Struct_declaratorAst *node);
    virtual void visitStruct_or_union_specifier(Struct_or_union_specifierAst *node);
    virtual void visitType_attribute_identifier(Type_attribute_identifierAst *node);
    virtual void visitType_name(Type_nameAst *node);
    virtual void visitType_qualifier(Type_qualifierAst *node);
    virtual void visitType_specifier(Type_specifierAst *node);
    virtual void visitTyped_identifier(Typed_identifierAst *node);
    virtual void visitTypedef_d(Typedef_dAst *node);
    virtual void visitUnary_expression(Unary_expressionAst *node);
    virtual void visitUnary_operator(Unary_operatorAst *node);
    virtual void visitValue_declaration(Value_declarationAst *node);
    virtual void visitVariable_declaration(Variable_declarationAst *node);
};

} // end of namespace cc

#endif

