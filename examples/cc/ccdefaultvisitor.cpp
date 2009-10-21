// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#include "ccdefaultvisitor.h"

namespace cc
{

void DefaultVisitor::visitAND_expression(AND_expressionAst *node)
{
    if (node->equality_expressionSequence)
    {
        const KDevPG::ListNode<Equality_expressionAst*> *__it = node->equality_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitAbstract_declarator(Abstract_declaratorAst *node)
{
    visitNode(node->pointer);
    if (node->direct_abstract_declaratorSequence)
    {
        const KDevPG::ListNode<Direct_abstract_declaratorAst*> *__it = node->direct_abstract_declaratorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitAdditive_expression(Additive_expressionAst *node)
{
    if (node->multiplicative_expressionSequence)
    {
        const KDevPG::ListNode<Multiplicative_expressionAst*> *__it = node->multiplicative_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitArgument_expression_list(Argument_expression_listAst *node)
{
    if (node->assignment_expressionSequence)
    {
        const KDevPG::ListNode<Assignment_expressionAst*> *__it = node->assignment_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitAssignment_expression(Assignment_expressionAst *node)
{
    if (node->conditional_expressionSequence)
    {
        const KDevPG::ListNode<Conditional_expressionAst*> *__it = node->conditional_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitAssignment_operator(Assignment_operatorAst *)
{
}

void DefaultVisitor::visitCast_expression(Cast_expressionAst *node)
{
    visitNode(node->type_name);
    visitNode(node->cast_expression);
    visitNode(node->unary_expression);
}

void DefaultVisitor::visitCompound_statement(Compound_statementAst *node)
{
    if (node->declarationSequence)
    {
        const KDevPG::ListNode<DeclarationAst*> *__it = node->declarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->statementSequence)
    {
        const KDevPG::ListNode<StatementAst*> *__it = node->statementSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitConditional_expression(Conditional_expressionAst *node)
{
    visitNode(node->logical_OR_expression);
}

void DefaultVisitor::visitConstant(ConstantAst *)
{
}

void DefaultVisitor::visitConstant_expression(Constant_expressionAst *node)
{
    visitNode(node->conditional_expression);
}

void DefaultVisitor::visitDdeclaration(DdeclarationAst *node)
{
    visitNode(node->enum_specifier);
    visitNode(node->struct_or_union_specifier);
    visitNode(node->typedef_d);
    visitNode(node->external_block);
    visitNode(node->value_declaration);
}

void DefaultVisitor::visitDeclaration(DeclarationAst *node)
{
    if (node->declaration_specifierSequence)
    {
        const KDevPG::ListNode<Declaration_specifierAst*> *__it = node->declaration_specifierSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->init_declaratorSequence)
    {
        const KDevPG::ListNode<Init_declaratorAst*> *__it = node->init_declaratorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitDeclaration_header(Declaration_headerAst *node)
{
    if (node->declaration_specifierSequence)
    {
        const KDevPG::ListNode<Declaration_specifierAst*> *__it = node->declaration_specifierSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitDeclaration_parameter(Declaration_parameterAst *node)
{
    visitNode(node->typed_identifier);
    visitNode(node->constant_expression);
    visitNode(node->type_name);
}

void DefaultVisitor::visitDeclaration_specifier(Declaration_specifierAst *node)
{
    visitNode(node->storage_class_specifier);
    visitNode(node->type_specifier);
    visitNode(node->type_qualifier);
}

void DefaultVisitor::visitDeclarator(DeclaratorAst *node)
{
    visitNode(node->pointer);
    visitNode(node->direct_declarator);
    if (node->direct_declarator_restSequence)
    {
        const KDevPG::ListNode<Direct_declarator_restAst*> *__it = node->direct_declarator_restSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitDirect_abstract_declarator(Direct_abstract_declaratorAst *node)
{
    visitNode(node->abstract_declarator);
    visitNode(node->parameter_type_list);
}

void DefaultVisitor::visitDirect_declarator(Direct_declaratorAst *node)
{
    visitNode(node->declarator);
}

void DefaultVisitor::visitDirect_declarator_rest(Direct_declarator_restAst *node)
{
    visitNode(node->parameter_type_list);
}

void DefaultVisitor::visitDocument(DocumentAst *node)
{
    if (node->ddeclarationSequence)
    {
        const KDevPG::ListNode<DdeclarationAst*> *__it = node->ddeclarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitEnum_specifier(Enum_specifierAst *node)
{
    if (node->enumeratorSequence)
    {
        const KDevPG::ListNode<EnumeratorAst*> *__it = node->enumeratorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitEnumerator(EnumeratorAst *node)
{
    visitNode(node->constant_expression);
}

void DefaultVisitor::visitEquality_expression(Equality_expressionAst *node)
{
    if (node->relational_expressionSequence)
    {
        const KDevPG::ListNode<Relational_expressionAst*> *__it = node->relational_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitExclusive_OR_expression(Exclusive_OR_expressionAst *node)
{
    if (node->AND_expressionSequence)
    {
        const KDevPG::ListNode<AND_expressionAst*> *__it = node->AND_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitExecution_block(Execution_blockAst *node)
{
    if (node->statementSequence)
    {
        const KDevPG::ListNode<StatementAst*> *__it = node->statementSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitExpression(ExpressionAst *node)
{
    if (node->assignment_expressionSequence)
    {
        const KDevPG::ListNode<Assignment_expressionAst*> *__it = node->assignment_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitExpression_statement(Expression_statementAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitExternal_block(External_blockAst *node)
{
    if (node->ddeclarationSequence)
    {
        const KDevPG::ListNode<DdeclarationAst*> *__it = node->ddeclarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitFunction_declaration(Function_declarationAst *node)
{
    if (node->declaration_parameterSequence)
    {
        const KDevPG::ListNode<Declaration_parameterAst*> *__it = node->declaration_parameterSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitFunction_definition(Function_definitionAst *node)
{
    if (node->named_parameterSequence)
    {
        const KDevPG::ListNode<Named_parameterAst*> *__it = node->named_parameterSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->execution_block);
}

void DefaultVisitor::visitFunction_pointer_parameter(Function_pointer_parameterAst *node)
{
    visitNode(node->typed_identifier);
    visitNode(node->type_name);
}

void DefaultVisitor::visitInclusive_OR_expression(Inclusive_OR_expressionAst *node)
{
    if (node->exclusive_OR_expressionSequence)
    {
        const KDevPG::ListNode<Exclusive_OR_expressionAst*> *__it = node->exclusive_OR_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitInit_declarator(Init_declaratorAst *node)
{
    visitNode(node->declarator);
    visitNode(node->initializer);
}

void DefaultVisitor::visitInitializer(InitializerAst *node)
{
    visitNode(node->assignment_expression);
    if (node->initializerSequence)
    {
        const KDevPG::ListNode<InitializerAst*> *__it = node->initializerSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitIteration_statement(Iteration_statementAst *node)
{
    visitNode(node->expression);
    visitNode(node->statement);
    visitNode(node->for_1);
    visitNode(node->for_2);
    visitNode(node->for_3);
}

void DefaultVisitor::visitJump_statement(Jump_statementAst *node)
{
    visitNode(node->expression);
}

void DefaultVisitor::visitLabeled_statement(Labeled_statementAst *node)
{
    visitNode(node->constant_expression);
    visitNode(node->statement);
}

void DefaultVisitor::visitLogical_AND_expression(Logical_AND_expressionAst *node)
{
    if (node->inclusive_OR_expressionSequence)
    {
        const KDevPG::ListNode<Inclusive_OR_expressionAst*> *__it = node->inclusive_OR_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitLogical_OR_expression(Logical_OR_expressionAst *node)
{
    if (node->logical_AND_expressionSequence)
    {
        const KDevPG::ListNode<Logical_AND_expressionAst*> *__it = node->logical_AND_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitMultiplicative_expression(Multiplicative_expressionAst *node)
{
    if (node->cast_expressionSequence)
    {
        const KDevPG::ListNode<Cast_expressionAst*> *__it = node->cast_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitNamed_parameter(Named_parameterAst *node)
{
    visitNode(node->typed_identifier);
    visitNode(node->constant_expression);
}

void DefaultVisitor::visitParameter(ParameterAst *node)
{
    visitNode(node->typed_identifier);
    visitNode(node->type_name);
}

void DefaultVisitor::visitParameter_declaration(Parameter_declarationAst *node)
{
    if (node->declaration_specifierSequence)
    {
        const KDevPG::ListNode<Declaration_specifierAst*> *__it = node->declaration_specifierSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    visitNode(node->declarator);
    visitNode(node->abstract_declarator);
}

void DefaultVisitor::visitParameter_type_list(Parameter_type_listAst *node)
{
    if (node->parameter_declarationSequence)
    {
        const KDevPG::ListNode<Parameter_declarationAst*> *__it = node->parameter_declarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitPointer(PointerAst *node)
{
    if (node->type_qualifierSequence)
    {
        const KDevPG::ListNode<Type_qualifierAst*> *__it = node->type_qualifierSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitPostfix_expression(Postfix_expressionAst *node)
{
    visitNode(node->primary_expression);
    if (node->postfix_expression_restSequence)
    {
        const KDevPG::ListNode<Postfix_expression_restAst*> *__it = node->postfix_expression_restSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitPostfix_expression_rest(Postfix_expression_restAst *node)
{
    visitNode(node->argument_expression_list);
    visitNode(node->expression);
}

void DefaultVisitor::visitPrimary_expression(Primary_expressionAst *node)
{
    visitNode(node->constant);
    visitNode(node->expression);
}

void DefaultVisitor::visitRelational_expression(Relational_expressionAst *node)
{
    if (node->shift_expressionSequence)
    {
        const KDevPG::ListNode<Shift_expressionAst*> *__it = node->shift_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitSelection_statement(Selection_statementAst *node)
{
    visitNode(node->expression);
    visitNode(node->statement);
    visitNode(node->alternative_statement);
}

void DefaultVisitor::visitShift_expression(Shift_expressionAst *node)
{
    if (node->additive_expressionSequence)
    {
        const KDevPG::ListNode<Additive_expressionAst*> *__it = node->additive_expressionSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitSpecifier_qualifier(Specifier_qualifierAst *node)
{
    visitNode(node->type_specifier);
    visitNode(node->type_qualifier);
}

void DefaultVisitor::visitStatement(StatementAst *node)
{
    visitNode(node->labeled_statement);
    visitNode(node->compound_statement);
    visitNode(node->expression_statement);
    visitNode(node->selection_statement);
    visitNode(node->iteration_statement);
    visitNode(node->jump_statement);
}

void DefaultVisitor::visitStorage_class_specifier(Storage_class_specifierAst *)
{
}

void DefaultVisitor::visitStruct_declaration(Struct_declarationAst *node)
{
    if (node->specifier_qualifierSequence)
    {
        const KDevPG::ListNode<Specifier_qualifierAst*> *__it = node->specifier_qualifierSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
    if (node->struct_declaratorSequence)
    {
        const KDevPG::ListNode<Struct_declaratorAst*> *__it = node->struct_declaratorSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitStruct_declarator(Struct_declaratorAst *node)
{
    visitNode(node->declarator);
    visitNode(node->constant_expression);
}

void DefaultVisitor::visitStruct_or_union_specifier(Struct_or_union_specifierAst *node)
{
    if (node->struct_declarationSequence)
    {
        const KDevPG::ListNode<Struct_declarationAst*> *__it = node->struct_declarationSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitType_attribute_identifier(Type_attribute_identifierAst *node)
{
    visitNode(node->type_attribute_identifier);
    if (node->function_pointer_parameterSequence)
    {
        const KDevPG::ListNode<Function_pointer_parameterAst*> *__it = node->function_pointer_parameterSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitType_name(Type_nameAst *node)
{
    if (node->specifier_qualifierSequence)
    {
        const KDevPG::ListNode<Specifier_qualifierAst*> *__it = node->specifier_qualifierSequence->front(), *__end = __it;
        do
        {
            visitNode(__it->element);
            __it = __it->next;
        }
        while (__it != __end);
    }
}

void DefaultVisitor::visitType_qualifier(Type_qualifierAst *)
{
}

void DefaultVisitor::visitType_specifier(Type_specifierAst *node)
{
    visitNode(node->struct_or_union_specifier);
    visitNode(node->enum_specifier);
}

void DefaultVisitor::visitTyped_identifier(Typed_identifierAst *node)
{
    visitNode(node->type_name);
    visitNode(node->type_attribute_identifier);
}

void DefaultVisitor::visitTypedef_d(Typedef_dAst *node)
{
    visitNode(node->struct_or_union_specifier);
    visitNode(node->enum_specifier);
    visitNode(node->typed_identifier);
}

void DefaultVisitor::visitUnary_expression(Unary_expressionAst *node)
{
    visitNode(node->postfix_expression);
    visitNode(node->unary_expression);
    visitNode(node->cast_expression);
    visitNode(node->type_name);
}

void DefaultVisitor::visitUnary_operator(Unary_operatorAst *)
{
}

void DefaultVisitor::visitValue_declaration(Value_declarationAst *node)
{
    visitNode(node->function_definition);
    visitNode(node->function_declaration);
}

void DefaultVisitor::visitVariable_declaration(Variable_declarationAst *node)
{
    visitNode(node->typed_identifier);
}


} // end of namespace cc

