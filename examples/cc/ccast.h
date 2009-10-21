// THIS FILE IS GENERATED
// WARNING! All changes made in this file will be lost!

#ifndef CC_AST_H_INCLUDED
#define CC_AST_H_INCLUDED

#include <QtCore/QList>
#include <kdev-pg-list.h>


#include <QtCore/QString>
#include <kdebug.h>

namespace cc
{

struct AND_expressionAst;
struct Abstract_declaratorAst;
struct Additive_expressionAst;
struct Argument_expression_listAst;
struct Assignment_expressionAst;
struct Assignment_operatorAst;
struct Cast_expressionAst;
struct Compound_statementAst;
struct Conditional_expressionAst;
struct ConstantAst;
struct Constant_expressionAst;
struct DdeclarationAst;
struct DeclarationAst;
struct Declaration_headerAst;
struct Declaration_parameterAst;
struct Declaration_specifierAst;
struct DeclaratorAst;
struct Direct_abstract_declaratorAst;
struct Direct_declaratorAst;
struct Direct_declarator_restAst;
struct DocumentAst;
struct Enum_specifierAst;
struct EnumeratorAst;
struct Equality_expressionAst;
struct Exclusive_OR_expressionAst;
struct Execution_blockAst;
struct ExpressionAst;
struct Expression_statementAst;
struct External_blockAst;
struct Function_declarationAst;
struct Function_definitionAst;
struct Function_pointer_parameterAst;
struct Inclusive_OR_expressionAst;
struct Init_declaratorAst;
struct InitializerAst;
struct Iteration_statementAst;
struct Jump_statementAst;
struct Labeled_statementAst;
struct Logical_AND_expressionAst;
struct Logical_OR_expressionAst;
struct Multiplicative_expressionAst;
struct Named_parameterAst;
struct ParameterAst;
struct Parameter_declarationAst;
struct Parameter_type_listAst;
struct PointerAst;
struct Postfix_expressionAst;
struct Postfix_expression_restAst;
struct Primary_expressionAst;
struct Relational_expressionAst;
struct Selection_statementAst;
struct Shift_expressionAst;
struct Specifier_qualifierAst;
struct StatementAst;
struct Storage_class_specifierAst;
struct Struct_declarationAst;
struct Struct_declaratorAst;
struct Struct_or_union_specifierAst;
struct Type_attribute_identifierAst;
struct Type_nameAst;
struct Type_qualifierAst;
struct Type_specifierAst;
struct Typed_identifierAst;
struct Typedef_dAst;
struct Unary_expressionAst;
struct Unary_operatorAst;
struct Value_declarationAst;
struct Variable_declarationAst;


struct  AstNode
{
    enum AstNodeKind
    {
        AND_expressionKind = 1000,
        Abstract_declaratorKind = 1001,
        Additive_expressionKind = 1002,
        Argument_expression_listKind = 1003,
        Assignment_expressionKind = 1004,
        Assignment_operatorKind = 1005,
        Cast_expressionKind = 1006,
        Compound_statementKind = 1007,
        Conditional_expressionKind = 1008,
        ConstantKind = 1009,
        Constant_expressionKind = 1010,
        DdeclarationKind = 1011,
        DeclarationKind = 1012,
        Declaration_headerKind = 1013,
        Declaration_parameterKind = 1014,
        Declaration_specifierKind = 1015,
        DeclaratorKind = 1016,
        Direct_abstract_declaratorKind = 1017,
        Direct_declaratorKind = 1018,
        Direct_declarator_restKind = 1019,
        DocumentKind = 1020,
        Enum_specifierKind = 1021,
        EnumeratorKind = 1022,
        Equality_expressionKind = 1023,
        Exclusive_OR_expressionKind = 1024,
        Execution_blockKind = 1025,
        ExpressionKind = 1026,
        Expression_statementKind = 1027,
        External_blockKind = 1028,
        Function_declarationKind = 1029,
        Function_definitionKind = 1030,
        Function_pointer_parameterKind = 1031,
        Inclusive_OR_expressionKind = 1032,
        Init_declaratorKind = 1033,
        InitializerKind = 1034,
        Iteration_statementKind = 1035,
        Jump_statementKind = 1036,
        Labeled_statementKind = 1037,
        Logical_AND_expressionKind = 1038,
        Logical_OR_expressionKind = 1039,
        Multiplicative_expressionKind = 1040,
        Named_parameterKind = 1041,
        ParameterKind = 1042,
        Parameter_declarationKind = 1043,
        Parameter_type_listKind = 1044,
        PointerKind = 1045,
        Postfix_expressionKind = 1046,
        Postfix_expression_restKind = 1047,
        Primary_expressionKind = 1048,
        Relational_expressionKind = 1049,
        Selection_statementKind = 1050,
        Shift_expressionKind = 1051,
        Specifier_qualifierKind = 1052,
        StatementKind = 1053,
        Storage_class_specifierKind = 1054,
        Struct_declarationKind = 1055,
        Struct_declaratorKind = 1056,
        Struct_or_union_specifierKind = 1057,
        Type_attribute_identifierKind = 1058,
        Type_nameKind = 1059,
        Type_qualifierKind = 1060,
        Type_specifierKind = 1061,
        Typed_identifierKind = 1062,
        Typedef_dKind = 1063,
        Unary_expressionKind = 1064,
        Unary_operatorKind = 1065,
        Value_declarationKind = 1066,
        Variable_declarationKind = 1067,
        AST_NODE_KIND_COUNT
    };

    int kind;
    qint64 startToken;
    qint64 endToken;

};

struct  AND_expressionAst: public AstNode
{
    enum { KIND = AND_expressionKind };

    const KDevPG::ListNode<Equality_expressionAst *> *equality_expressionSequence;
};

struct  Abstract_declaratorAst: public AstNode
{
    enum { KIND = Abstract_declaratorKind };

    PointerAst *pointer;
    const KDevPG::ListNode<Direct_abstract_declaratorAst *> *direct_abstract_declaratorSequence;
};

struct  Additive_expressionAst: public AstNode
{
    enum { KIND = Additive_expressionKind };

    const KDevPG::ListNode<Multiplicative_expressionAst *> *multiplicative_expressionSequence;
};

struct  Argument_expression_listAst: public AstNode
{
    enum { KIND = Argument_expression_listKind };

    const KDevPG::ListNode<Assignment_expressionAst *> *assignment_expressionSequence;
};

struct  Assignment_expressionAst: public AstNode
{
    enum { KIND = Assignment_expressionKind };

    const KDevPG::ListNode<Conditional_expressionAst *> *conditional_expressionSequence;
};

struct  Assignment_operatorAst: public AstNode
{
    enum { KIND = Assignment_operatorKind };

};

struct  Cast_expressionAst: public AstNode
{
    enum { KIND = Cast_expressionKind };

    Type_nameAst *type_name;
    Cast_expressionAst *cast_expression;
    Unary_expressionAst *unary_expression;
};

struct  Compound_statementAst: public AstNode
{
    enum { KIND = Compound_statementKind };

    const KDevPG::ListNode<DeclarationAst *> *declarationSequence;
    const KDevPG::ListNode<StatementAst *> *statementSequence;
};

struct  Conditional_expressionAst: public AstNode
{
    enum { KIND = Conditional_expressionKind };

    Logical_OR_expressionAst *logical_OR_expression;
};

struct  ConstantAst: public AstNode
{
    enum { KIND = ConstantKind };

};

struct  Constant_expressionAst: public AstNode
{
    enum { KIND = Constant_expressionKind };

    Conditional_expressionAst *conditional_expression;
};

struct  DdeclarationAst: public AstNode
{
    enum { KIND = DdeclarationKind };

    Enum_specifierAst *enum_specifier;
    Struct_or_union_specifierAst *struct_or_union_specifier;
    Typedef_dAst *typedef_d;
    External_blockAst *external_block;
    Value_declarationAst *value_declaration;
};

struct  DeclarationAst: public AstNode
{
    enum { KIND = DeclarationKind };

    const KDevPG::ListNode<Declaration_specifierAst *> *declaration_specifierSequence;
    const KDevPG::ListNode<Init_declaratorAst *> *init_declaratorSequence;
};

struct  Declaration_headerAst: public AstNode
{
    enum { KIND = Declaration_headerKind };

    const KDevPG::ListNode<Declaration_specifierAst *> *declaration_specifierSequence;
};

struct  Declaration_parameterAst: public AstNode
{
    enum { KIND = Declaration_parameterKind };

    Typed_identifierAst *typed_identifier;
    Constant_expressionAst *constant_expression;
    Type_nameAst *type_name;
};

struct  Declaration_specifierAst: public AstNode
{
    enum { KIND = Declaration_specifierKind };

    Storage_class_specifierAst *storage_class_specifier;
    Type_specifierAst *type_specifier;
    Type_qualifierAst *type_qualifier;
};

struct  DeclaratorAst: public AstNode
{
    enum { KIND = DeclaratorKind };

    PointerAst *pointer;
    Direct_declaratorAst *direct_declarator;
    const KDevPG::ListNode<Direct_declarator_restAst *> *direct_declarator_restSequence;
};

struct  Direct_abstract_declaratorAst: public AstNode
{
    enum { KIND = Direct_abstract_declaratorKind };

    Abstract_declaratorAst *abstract_declarator;
    Parameter_type_listAst *parameter_type_list;
};

struct  Direct_declaratorAst: public AstNode
{
    enum { KIND = Direct_declaratorKind };

    DeclaratorAst *declarator;
};

struct  Direct_declarator_restAst: public AstNode
{
    enum { KIND = Direct_declarator_restKind };

    Parameter_type_listAst *parameter_type_list;
};

struct  DocumentAst: public AstNode
{
    enum { KIND = DocumentKind };

    const KDevPG::ListNode<DdeclarationAst *> *ddeclarationSequence;
};

struct  Enum_specifierAst: public AstNode
{
    enum { KIND = Enum_specifierKind };

    const KDevPG::ListNode<EnumeratorAst *> *enumeratorSequence;
};

struct  EnumeratorAst: public AstNode
{
    enum { KIND = EnumeratorKind };

    Constant_expressionAst *constant_expression;
};

struct  Equality_expressionAst: public AstNode
{
    enum { KIND = Equality_expressionKind };

    const KDevPG::ListNode<Relational_expressionAst *> *relational_expressionSequence;
};

struct  Exclusive_OR_expressionAst: public AstNode
{
    enum { KIND = Exclusive_OR_expressionKind };

    const KDevPG::ListNode<AND_expressionAst *> *AND_expressionSequence;
};

struct  Execution_blockAst: public AstNode
{
    enum { KIND = Execution_blockKind };

    const KDevPG::ListNode<StatementAst *> *statementSequence;
};

struct  ExpressionAst: public AstNode
{
    enum { KIND = ExpressionKind };

    const KDevPG::ListNode<Assignment_expressionAst *> *assignment_expressionSequence;
};

struct  Expression_statementAst: public AstNode
{
    enum { KIND = Expression_statementKind };

    ExpressionAst *expression;
};

struct  External_blockAst: public AstNode
{
    enum { KIND = External_blockKind };

    const KDevPG::ListNode<DdeclarationAst *> *ddeclarationSequence;
};

struct  Function_declarationAst: public AstNode
{
    enum { KIND = Function_declarationKind };

    const KDevPG::ListNode<Declaration_parameterAst *> *declaration_parameterSequence;
};

struct  Function_definitionAst: public AstNode
{
    enum { KIND = Function_definitionKind };

    const KDevPG::ListNode<Named_parameterAst *> *named_parameterSequence;
    Execution_blockAst *execution_block;
};

struct  Function_pointer_parameterAst: public AstNode
{
    enum { KIND = Function_pointer_parameterKind };

    Typed_identifierAst *typed_identifier;
    Type_nameAst *type_name;
};

struct  Inclusive_OR_expressionAst: public AstNode
{
    enum { KIND = Inclusive_OR_expressionKind };

    const KDevPG::ListNode<Exclusive_OR_expressionAst *> *exclusive_OR_expressionSequence;
};

struct  Init_declaratorAst: public AstNode
{
    enum { KIND = Init_declaratorKind };

    DeclaratorAst *declarator;
    InitializerAst *initializer;
};

struct  InitializerAst: public AstNode
{
    enum { KIND = InitializerKind };

    Assignment_expressionAst *assignment_expression;
    const KDevPG::ListNode<InitializerAst *> *initializerSequence;
};

struct  Iteration_statementAst: public AstNode
{
    enum { KIND = Iteration_statementKind };

    ExpressionAst *expression;
    StatementAst *statement;
    ExpressionAst *for_1;
    ExpressionAst *for_2;
    ExpressionAst *for_3;
};

struct  Jump_statementAst: public AstNode
{
    enum { KIND = Jump_statementKind };

    ExpressionAst *expression;
};

struct  Labeled_statementAst: public AstNode
{
    enum { KIND = Labeled_statementKind };

    Constant_expressionAst *constant_expression;
    StatementAst *statement;
};

struct  Logical_AND_expressionAst: public AstNode
{
    enum { KIND = Logical_AND_expressionKind };

    const KDevPG::ListNode<Inclusive_OR_expressionAst *> *inclusive_OR_expressionSequence;
};

struct  Logical_OR_expressionAst: public AstNode
{
    enum { KIND = Logical_OR_expressionKind };

    const KDevPG::ListNode<Logical_AND_expressionAst *> *logical_AND_expressionSequence;
};

struct  Multiplicative_expressionAst: public AstNode
{
    enum { KIND = Multiplicative_expressionKind };

    const KDevPG::ListNode<Cast_expressionAst *> *cast_expressionSequence;
};

struct  Named_parameterAst: public AstNode
{
    enum { KIND = Named_parameterKind };

    Typed_identifierAst *typed_identifier;
    Constant_expressionAst *constant_expression;
};

struct  ParameterAst: public AstNode
{
    enum { KIND = ParameterKind };

    Typed_identifierAst *typed_identifier;
    Type_nameAst *type_name;
};

struct  Parameter_declarationAst: public AstNode
{
    enum { KIND = Parameter_declarationKind };

    const KDevPG::ListNode<Declaration_specifierAst *> *declaration_specifierSequence;
    DeclaratorAst *declarator;
    Abstract_declaratorAst *abstract_declarator;
};

struct  Parameter_type_listAst: public AstNode
{
    enum { KIND = Parameter_type_listKind };

    const KDevPG::ListNode<Parameter_declarationAst *> *parameter_declarationSequence;
};

struct  PointerAst: public AstNode
{
    enum { KIND = PointerKind };

    const KDevPG::ListNode<Type_qualifierAst *> *type_qualifierSequence;
};

struct  Postfix_expressionAst: public AstNode
{
    enum { KIND = Postfix_expressionKind };

    Primary_expressionAst *primary_expression;
    const KDevPG::ListNode<Postfix_expression_restAst *> *postfix_expression_restSequence;
};

struct  Postfix_expression_restAst: public AstNode
{
    enum { KIND = Postfix_expression_restKind };

    Argument_expression_listAst *argument_expression_list;
    ExpressionAst *expression;
};

struct  Primary_expressionAst: public AstNode
{
    enum { KIND = Primary_expressionKind };

    qint64 identifier;
    ConstantAst *constant;
    qint64 string_literal;
    ExpressionAst *expression;
};

struct  Relational_expressionAst: public AstNode
{
    enum { KIND = Relational_expressionKind };

    const KDevPG::ListNode<Shift_expressionAst *> *shift_expressionSequence;
};

struct  Selection_statementAst: public AstNode
{
    enum { KIND = Selection_statementKind };

    ExpressionAst *expression;
    StatementAst *statement;
    StatementAst *alternative_statement;
};

struct  Shift_expressionAst: public AstNode
{
    enum { KIND = Shift_expressionKind };

    const KDevPG::ListNode<Additive_expressionAst *> *additive_expressionSequence;
};

struct  Specifier_qualifierAst: public AstNode
{
    enum { KIND = Specifier_qualifierKind };

    Type_specifierAst *type_specifier;
    Type_qualifierAst *type_qualifier;
};

struct  StatementAst: public AstNode
{
    enum { KIND = StatementKind };

    Labeled_statementAst *labeled_statement;
    Compound_statementAst *compound_statement;
    Expression_statementAst *expression_statement;
    Selection_statementAst *selection_statement;
    Iteration_statementAst *iteration_statement;
    Jump_statementAst *jump_statement;
};

struct  Storage_class_specifierAst: public AstNode
{
    enum { KIND = Storage_class_specifierKind };

};

struct  Struct_declarationAst: public AstNode
{
    enum { KIND = Struct_declarationKind };

    const KDevPG::ListNode<Specifier_qualifierAst *> *specifier_qualifierSequence;
    const KDevPG::ListNode<Struct_declaratorAst *> *struct_declaratorSequence;
};

struct  Struct_declaratorAst: public AstNode
{
    enum { KIND = Struct_declaratorKind };

    DeclaratorAst *declarator;
    Constant_expressionAst *constant_expression;
};

struct  Struct_or_union_specifierAst: public AstNode
{
    enum { KIND = Struct_or_union_specifierKind };

    const KDevPG::ListNode<Struct_declarationAst *> *struct_declarationSequence;
};

struct  Type_attribute_identifierAst: public AstNode
{
    enum { KIND = Type_attribute_identifierKind };

    Type_attribute_identifierAst *type_attribute_identifier;
    const KDevPG::ListNode<Function_pointer_parameterAst *> *function_pointer_parameterSequence;
};

struct  Type_nameAst: public AstNode
{
    enum { KIND = Type_nameKind };

    const KDevPG::ListNode<Specifier_qualifierAst *> *specifier_qualifierSequence;
};

struct  Type_qualifierAst: public AstNode
{
    enum { KIND = Type_qualifierKind };

};

struct  Type_specifierAst: public AstNode
{
    enum { KIND = Type_specifierKind };

    Struct_or_union_specifierAst *struct_or_union_specifier;
    Enum_specifierAst *enum_specifier;
};

struct  Typed_identifierAst: public AstNode
{
    enum { KIND = Typed_identifierKind };

    Type_nameAst *type_name;
    Type_attribute_identifierAst *type_attribute_identifier;
};

struct  Typedef_dAst: public AstNode
{
    enum { KIND = Typedef_dKind };

    Struct_or_union_specifierAst *struct_or_union_specifier;
    Enum_specifierAst *enum_specifier;
    Typed_identifierAst *typed_identifier;
};

struct  Unary_expressionAst: public AstNode
{
    enum { KIND = Unary_expressionKind };

    Postfix_expressionAst *postfix_expression;
    Unary_expressionAst *unary_expression;
    Cast_expressionAst *cast_expression;
    Type_nameAst *type_name;
};

struct  Unary_operatorAst: public AstNode
{
    enum { KIND = Unary_operatorKind };

};

struct  Value_declarationAst: public AstNode
{
    enum { KIND = Value_declarationKind };

    Function_definitionAst *function_definition;
    Function_declarationAst *function_declaration;
};

struct  Variable_declarationAst: public AstNode
{
    enum { KIND = Variable_declarationKind };

    Typed_identifierAst *typed_identifier;
};



} // end of namespace cc

#endif

