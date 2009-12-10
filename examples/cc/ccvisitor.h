// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef CC_VISITOR_H_INCLUDED
#define CC_VISITOR_H_INCLUDED

#include "ccast.h"

namespace cc
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
    virtual void visitAND_expression(AND_expressionAst *) {}
    virtual void visitAbstract_declarator(Abstract_declaratorAst *) {}
    virtual void visitAdditive_expression(Additive_expressionAst *) {}
    virtual void visitArgument_expression_list(Argument_expression_listAst *) {}
    virtual void visitAsm_against_mangling(Asm_against_manglingAst *) {}
    virtual void visitAsm_specifier(Asm_specifierAst *) {}
    virtual void visitAssignment_expression(Assignment_expressionAst *) {}
    virtual void visitAssignment_operator(Assignment_operatorAst *) {}
    virtual void visitCast_expression(Cast_expressionAst *) {}
    virtual void visitCompound_statement(Compound_statementAst *) {}
    virtual void visitConditional_expression(Conditional_expressionAst *) {}
    virtual void visitConstant(ConstantAst *) {}
    virtual void visitConstant_expression(Constant_expressionAst *) {}
    virtual void visitDdeclaration(DdeclarationAst *) {}
    virtual void visitDeclaration(DeclarationAst *) {}
    virtual void visitDeclaration_header(Declaration_headerAst *) {}
    virtual void visitDeclaration_parameter(Declaration_parameterAst *) {}
    virtual void visitDeclaration_specifier(Declaration_specifierAst *) {}
    virtual void visitDeclarator(DeclaratorAst *) {}
    virtual void visitDirect_abstract_declarator(Direct_abstract_declaratorAst *) {}
    virtual void visitDirect_declarator(Direct_declaratorAst *) {}
    virtual void visitDirect_declarator_rest(Direct_declarator_restAst *) {}
    virtual void visitDocument(DocumentAst *) {}
    virtual void visitEnum_specifier(Enum_specifierAst *) {}
    virtual void visitEnumerator(EnumeratorAst *) {}
    virtual void visitEquality_expression(Equality_expressionAst *) {}
    virtual void visitExclusive_OR_expression(Exclusive_OR_expressionAst *) {}
    virtual void visitExecution_block(Execution_blockAst *) {}
    virtual void visitExpression(ExpressionAst *) {}
    virtual void visitExpression_statement(Expression_statementAst *) {}
    virtual void visitExt_expression(Ext_expressionAst *) {}
    virtual void visitExternal_block(External_blockAst *) {}
    virtual void visitFunction_declaration(Function_declarationAst *) {}
    virtual void visitFunction_definition(Function_definitionAst *) {}
    virtual void visitFunction_pointer_parameter(Function_pointer_parameterAst *) {}
    virtual void visitInclusive_OR_expression(Inclusive_OR_expressionAst *) {}
    virtual void visitInit_declarator(Init_declaratorAst *) {}
    virtual void visitInitializer(InitializerAst *) {}
    virtual void visitInline_asm(Inline_asmAst *) {}
    virtual void visitIteration_statement(Iteration_statementAst *) {}
    virtual void visitJump_statement(Jump_statementAst *) {}
    virtual void visitLabeled_statement(Labeled_statementAst *) {}
    virtual void visitLogical_AND_expression(Logical_AND_expressionAst *) {}
    virtual void visitLogical_OR_expression(Logical_OR_expressionAst *) {}
    virtual void visitMultiplicative_expression(Multiplicative_expressionAst *) {}
    virtual void visitNamed_parameter(Named_parameterAst *) {}
    virtual void visitParameter(ParameterAst *) {}
    virtual void visitParameter_declaration(Parameter_declarationAst *) {}
    virtual void visitParameter_type_list(Parameter_type_listAst *) {}
    virtual void visitPointer(PointerAst *) {}
    virtual void visitPostfix_expression(Postfix_expressionAst *) {}
    virtual void visitPostfix_expression_rest(Postfix_expression_restAst *) {}
    virtual void visitPrimary_expression(Primary_expressionAst *) {}
    virtual void visitRelational_expression(Relational_expressionAst *) {}
    virtual void visitSelection_statement(Selection_statementAst *) {}
    virtual void visitShift_expression(Shift_expressionAst *) {}
    virtual void visitSpecifier_qualifier(Specifier_qualifierAst *) {}
    virtual void visitStatement(StatementAst *) {}
    virtual void visitStorage_class_specifier(Storage_class_specifierAst *) {}
    virtual void visitStruct_declaration(Struct_declarationAst *) {}
    virtual void visitStruct_declarator(Struct_declaratorAst *) {}
    virtual void visitStruct_or_union_specifier(Struct_or_union_specifierAst *) {}
    virtual void visitType_attribute_identifier(Type_attribute_identifierAst *) {}
    virtual void visitType_name(Type_nameAst *) {}
    virtual void visitType_qualifier(Type_qualifierAst *) {}
    virtual void visitType_specifier(Type_specifierAst *) {}
    virtual void visitTyped_identifier(Typed_identifierAst *) {}
    virtual void visitTypedef_d(Typedef_dAst *) {}
    virtual void visitUnary_expression(Unary_expressionAst *) {}
    virtual void visitUnary_operator(Unary_operatorAst *) {}
    virtual void visitValue_declaration(Value_declarationAst *) {}
    virtual void visitVariable_declaration(Variable_declarationAst *) {}
};

} // end of namespace cc

#endif

