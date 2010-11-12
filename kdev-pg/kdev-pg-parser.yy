
%{
/* This file is part of kdev-pg-qt
   Copyright (C) 2005 Roberto Raggi <roberto@kdevelop.org>
   Copyright (C) 2006 Jakob Petsovits <jpetso@gmx.at>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "kdev-pg.h"
#include "kdev-pg-clone-tree.h"
#include "kdev-pg-regexp.h"

#include <QtCore/QFile>
#include <cassert>

extern int yylex();
extern void yyerror(const char* msg);
extern int yyLine;

QString lexerEnv;

namespace KDevPG
{
    extern QFile file;
    extern QTextStream checkOut;
}

KDevPG::Model::OperatorItem *operatorNode = 0;

%}

%union {
    KDevPG::Model::Node *item;
    char* str;
    KDevPG::Model::VariableDeclarationItem::DeclarationType declarationType;
    KDevPG::Model::VariableDeclarationItem::StorageType     storageType;
    KDevPG::Model::VariableDeclarationItem::VariableType    variableType;
    KDevPG::Model::Operator                                *operatorInformation;
    KDevPG::GNFA                                           *nfa;
}

%token T_IDENTIFIER T_ARROW T_TERMINAL T_CODE T_STRING T_NUMBER ';'
%token T_TOKEN_DECLARATION T_TOKEN_STREAM_DECLARATION T_NAMESPACE_DECLARATION
%token T_PARSERCLASS_DECLARATION T_LEXERCLASS_DECLARATION
%token T_PUBLIC T_PRIVATE T_PROTECTED T_DECLARATION T_BITS
%token T_CONSTRUCTOR T_DESTRUCTOR T_TRY_RECOVER T_TRY_ROLLBACK T_CATCH
%token T_RULE_ARGUMENTS T_MEMBER T_TEMPORARY T_ARGUMENT T_EXPORT_MACRO
%token T_NODE T_NODE_SEQUENCE T_TOKEN T_VARIABLE T_EXPORT_MACRO_HEADER
%token T_AST_DECLARATION 
%token T_PARSER_DECLARATION_HEADER T_PARSER_BITS_HEADER T_AST_HEADER
%token T_TOKEN_STREAM_DECLARATION_HEADER T_TOKEN_STREAM_BITS_HEADER
%token T_PARSER_BASE T_AST_BASE T_TOKEN_STREAM_BASE
%token T_BIN T_PRE T_POST T_TERN
%token T_LOPR T_ROPR
%token T_LEFT_ASSOC T_RIGHT_ASSOC T_IS_LEFT_ASSOC T_IS_RIGHT_ASSOC T_PRIORITY
%token T_PAREN
%token T_INLINE
%token T_LEXER T_INPUT_STREAM

%type<str> T_IDENTIFIER T_TERMINAL T_CODE T_STRING T_RULE_ARGUMENTS T_NUMBER
%type<str> name code_opt rule_arguments_opt priority assoc
%type<item> item primary_item try_item primary_atom unary_item
%type<item> postfix_item option_item item_sequence conditional_item
%type<item> member_declaration_rest variableDeclarations variableDeclaration operatorRule
%type<declarationType> declarationType_opt
%type<storageType>     scope storageType
%type<variableType>    variableType
/* %type<void> operatorDeclaration operatorDeclarations operatorRule */
%type<operatorInformation> operator
%type<nfa> regexp

%%

system
    : code_opt { KDevPG::globalSystem.decl = $1; }
      declarations
      rules
      code_opt { KDevPG::globalSystem.bits += $5; }
    ;

declarations
    : declaration
    | declarations declaration
    ;

declaration
    : T_PARSERCLASS_DECLARATION member_declaration_rest
        { KDevPG::globalSystem.pushParserClassMember($2); }
    | T_PARSERCLASS_DECLARATION '(' T_BITS ')' T_CODE
        { KDevPG::globalSystem.bits += $5; }
    | T_LEXERCLASS_DECLARATION member_declaration_rest
        { KDevPG::globalSystem.pushLexerClassMember($2); }
    | T_LEXERCLASS_DECLARATION '(' T_BITS ')' T_CODE
        { KDevPG::globalSystem.lexerBits += $5; }
    | T_TOKEN_DECLARATION declared_tokens ';'
    | T_TOKEN_STREAM_DECLARATION T_IDENTIFIER ';'
        { KDevPG::globalSystem.tokenStream = $2;           }
    | T_EXPORT_MACRO T_STRING
        { KDevPG::globalSystem.exportMacro = $2;           }
    | T_EXPORT_MACRO_HEADER T_STRING
        { KDevPG::globalSystem.exportMacroHeader = $2;     }
    | T_NAMESPACE_DECLARATION T_CODE
        { KDevPG::globalSystem.namespaceCode = $2;         }
    | T_AST_DECLARATION T_CODE
        { KDevPG::globalSystem.astCode = $2;               }
    | T_PARSER_DECLARATION_HEADER T_STRING
        { KDevPG::globalSystem.pushParserDeclarationHeader($2); }
    | T_PARSER_BITS_HEADER T_STRING
        { KDevPG::globalSystem.pushParserBitsHeader($2); }
    | T_AST_HEADER T_STRING
        { KDevPG::globalSystem.pushAstHeader($2); }
    | T_TOKEN_STREAM_DECLARATION_HEADER T_STRING
        { KDevPG::globalSystem.pushTokenStreamDeclarationHeader($2); }
    | T_INPUT_STREAM T_STRING
        { KDevPG::globalSystem.inputStream = $2; }
    | T_TOKEN_STREAM_BITS_HEADER T_STRING
        { KDevPG::globalSystem.pushTokenStreamBitsHeader($2); }
    | T_AST_BASE T_IDENTIFIER T_STRING
        { KDevPG::globalSystem.astBaseClasses[$2] = $3; }
    | T_PARSER_BASE T_STRING
        { KDevPG::globalSystem.parserBaseClass = $2; }
    | T_TOKEN_STREAM_BASE T_STRING
        { KDevPG::globalSystem.tokenStreamBaseClass = $2; }
    | T_LEXER T_STRING { KDevPG::globalSystem.hasLexer = true; lexerEnv = $2; if(KDevPG::globalSystem.lexerActions[lexerEnv].empty()) KDevPG::globalSystem.lexerActions[lexerEnv].push_back("qDebug() << \"error\"; exit(-1);"); } T_ARROW lexer_declaration_rest ';'
    | T_LEXER { KDevPG::globalSystem.hasLexer = true; lexerEnv = "start"; if(KDevPG::globalSystem.lexerActions["start"].empty()) KDevPG::globalSystem.lexerActions["start"].push_back("qDebug() << \"error\"; exit(-1);"); } T_ARROW lexer_declaration_rest ';'
    ;

lexer_declaration_rest
    : regexp code_opt T_TERMINAL T_ARROW T_IDENTIFIER ';'
            { KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back($1);
              KDevPG::globalSystem.lexerActions[lexerEnv].push_back(
                QString($2) + "KDevPG::Token& _t(Base::next()); _t.kind = ::" + KDevPG::globalSystem.ns + "::Parser::Token_" + $3 + ";\n"
              + "_t.begin = spos - Iterator::begin();\n"
              + "_t.end = plain() - Iterator::begin();\n"
              + "return _t;");
              KDevPG::globalSystem.regexpById[$5] = $1;
            } lexer_declaration_rest
    | regexp code_opt T_ARROW T_IDENTIFIER ';'
            { KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back($1);
              KDevPG::globalSystem.lexerActions[lexerEnv].push_back(QString($2));
              KDevPG::globalSystem.regexpById[$4] = $1;
            } lexer_declaration_rest
    | regexp code_opt T_TERMINAL ';'
            { KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back($1);
              KDevPG::globalSystem.lexerActions[lexerEnv].push_back(
                QString($2) + "KDevPG::Token& _t(Base::next()); _t.kind = ::" + KDevPG::globalSystem.ns + "::Parser::Token_" + $3 + ";\n"
              + "_t.begin = spos - Iterator::begin();\n"
              + "_t.end = plain() - Iterator::begin();\n"
              + "return _t;");
            } lexer_declaration_rest
    | regexp code_opt ';'
            { KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back($1);
              KDevPG::globalSystem.lexerActions[lexerEnv].push_back(QString($2));
            } lexer_declaration_rest
    | /* empty */
    ;

regexp
    : '(' regexp ')'        { $$ = new KDevPG::GNFA(*$2); delete $2; }
    | '|' regexp regexp     { $$ = new KDevPG::GNFA(*$2 |= *$3); delete $2; delete $3; }
    | '&' regexp regexp     { $$ = new KDevPG::GNFA(*$2 &= *$3); delete $2; delete $3; }
    | '*' regexp            { $$ = new KDevPG::GNFA(*$2); *$$; delete $2; }
    | T_STRING              { $$ = new KDevPG::GNFA(KDevPG::keyword(QString($1).replace("\\n", "\n"))); }
    | '{' T_IDENTIFIER '}'  { if(KDevPG::globalSystem.regexpById[$2] == 0) { KDevPG::checkOut << "ERROR: no named regexp " << $2 << endl; exit(-1); } $$ = new KDevPG::GNFA(*KDevPG::globalSystem.regexpById[$2]); }
    ;

member_declaration_rest
    : '(' T_PUBLIC T_DECLARATION ')' T_CODE
        { $$ = KDevPG::member(KDevPG::Settings::MemberItem::PublicDeclaration, $5);    }
    | '(' T_PROTECTED T_DECLARATION ')' T_CODE
        { $$ = KDevPG::member(KDevPG::Settings::MemberItem::ProtectedDeclaration, $5); }
    | '(' T_PRIVATE T_DECLARATION ')' T_CODE
        { $$ = KDevPG::member(KDevPG::Settings::MemberItem::PrivateDeclaration, $5);   }
    | '(' T_CONSTRUCTOR ')' T_CODE
        { $$ = KDevPG::member(KDevPG::Settings::MemberItem::ConstructorCode, $4);      }
    | '(' T_DESTRUCTOR ')' T_CODE
        { $$ = KDevPG::member(KDevPG::Settings::MemberItem::DestructorCode, $4);       }
    ;

declared_tokens
    : T_TERMINAL                        { KDevPG::globalSystem.pushTerminal($1,$1); }
    | T_TERMINAL '(' T_STRING ')'       { KDevPG::globalSystem.pushTerminal($1,$3); }
    | declared_tokens ',' T_TERMINAL    { KDevPG::globalSystem.pushTerminal($3,$3); }
    | declared_tokens ',' T_TERMINAL '(' T_STRING ')'
                                        { KDevPG::globalSystem.pushTerminal($3,$5); }
    ;

rules
    : item ';'                          { KDevPG::globalSystem.pushRule($1); }
    | rules item ';'                    { KDevPG::globalSystem.pushRule($2); }
    ;

primary_item
    : '0'                               { $$ = KDevPG::globalSystem.zero(); }
    | '(' option_item ')'               { $$ = $2; }
    | try_item                    { $$ = $1; }
    | primary_atom                      { $$ = $1; }
    | T_INLINE T_IDENTIFIER              { $$ = KDevPG::inlinedNonTerminal(KDevPG::globalSystem.pushSymbol($2)); }
    | name scope primary_atom           { $$ = KDevPG::annotation($1, $3, false, $2); }
    | '#' name scope primary_atom       { $$ = KDevPG::annotation($2, $4, true, $3);  }
    ;

primary_atom
    : T_IDENTIFIER rule_arguments_opt   { $$ = KDevPG::nonTerminal(KDevPG::globalSystem.pushSymbol($1), $2); }
    | T_TERMINAL                        { $$ = KDevPG::globalSystem.terminal($1); }
    ;

try_item
    : T_TRY_RECOVER '(' option_item ')'
        {
          KDevPG::globalSystem.needStateManagement = true;
          $$ = KDevPG::tryCatch($3, 0);
        }
    | T_TRY_ROLLBACK '(' option_item ')' T_CATCH '(' option_item ')'
        {
          KDevPG::globalSystem.needStateManagement = true;
          $$ = KDevPG::tryCatch($3, $7);
        }

rule_arguments_opt
    : /* empty */                       { $$ = const_cast<char*>(""); }
    | T_RULE_ARGUMENTS                  { $$ = $1; }
    ;

name
    : T_IDENTIFIER                      { $$ = $1; }
/*    | T_IDENTIFIER '.' T_IDENTIFIER
        {
          $$ = $3;
          fprintf(stderr, "** WARNING support for scoped name"
                          " ``%s.%s'' not implemented\n", $1, $3);
        }*/
    ;

scope
    : '=' { $$ = KDevPG::Model::VariableDeclarationItem::StorageAstMember; }
    | ':' { $$ = KDevPG::Model::VariableDeclarationItem::StorageTemporary;  }
    ;

unary_item
    : primary_item '+'                  { $$ = KDevPG::plus($1); }
    | primary_item '*'                  { $$ = KDevPG::star($1); }
    | primary_item                      { $$ = $1; }
    | '?' primary_item                   { $$ = KDevPG::alternative($2, KDevPG::globalSystem.zero()); }
    ;

postfix_item
    : unary_item                        { $$ = $1; }
    | postfix_item '@' primary_item
        {
          KDevPG::CloneTree cl;
          $$ = KDevPG::cons($1, KDevPG::star(KDevPG::cons(cl.clone($3), cl.clone($1))));
        }
    | postfix_item T_CODE               { $$ = KDevPG::action($1, $2); }
    | T_CODE                            { $$ = KDevPG::action(0, $1); }
    ;

item_sequence
    : postfix_item                      { $$ = $1; }
    | item_sequence postfix_item        { $$ = KDevPG::cons($1, $2); }
    ;

conditional_item
    : item_sequence                     { $$ = $1; }
    | '?' T_CODE item_sequence          { $$ = KDevPG::condition($2, $3); }
    ;

option_item
    : conditional_item                  { $$ = $1; }
    | option_item '|' conditional_item  { $$ = KDevPG::alternative($1, $3); }
    ;

item
    : option_item T_ARROW T_IDENTIFIER T_CODE '[' variableDeclarations ']'
        {
          $$ = KDevPG::evolve($1, KDevPG::globalSystem.pushSymbol($3),
                          (KDevPG::Model::VariableDeclarationItem*) $6, $4);
        }
    | option_item T_ARROW T_IDENTIFIER '[' variableDeclarations ']' code_opt
        {
          $$ = KDevPG::evolve($1, KDevPG::globalSystem.pushSymbol($3),
                          (KDevPG::Model::VariableDeclarationItem*) $5, $7);
        }
    | option_item T_ARROW T_IDENTIFIER code_opt
        { $$ = KDevPG::evolve($1, KDevPG::globalSystem.pushSymbol($3), 0, $4); }
    | { if(KDevPG::globalSystem.generateAst == false)
        {
          qFatal("Operator-expression-parsing is not yet supported with --no-ast!");
          exit(-1);
        }
        operatorNode = KDevPG::createNode<KDevPG::Model::OperatorItem>();
      } operatorRule { KDevPG::globalSystem.needOperatorStack = true; $$ = $2; }
    ;

code_opt
    : /* empty */                       { $$ = const_cast<char*>(""); }
    | T_CODE                            { $$ = $1; }
    ;


operatorDeclarations
    : operatorDeclaration operatorDeclarations
    | /* empty */   { ; }
    ;

operatorRule
    : T_LOPR primary_atom operatorDeclarations T_ROPR T_IDENTIFIER '[' variableDeclarations ']' code_opt
            {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)$2;
              operatorNode->mName = $5;
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              $$ = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol($5), (KDevPG::Model::VariableDeclarationItem*)$7, $9);
            }
    | T_LOPR primary_atom operatorDeclarations T_ROPR T_IDENTIFIER T_CODE '[' variableDeclarations ']'
            {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)$2;
              operatorNode->mName = $5;
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              $$ = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol($5), (KDevPG::Model::VariableDeclarationItem*)$8, $6);
            }
    | T_LOPR primary_atom operatorDeclarations T_ROPR T_IDENTIFIER code_opt
            {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)$2;
              operatorNode->mName = $5;
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + "Ast";
              $$ = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol($5), 0, $6);
            }
    ;

operatorDeclaration
    : T_BIN operator priority assoc              { operatorNode->pushBin(*$2, $4, $3); delete $2; }
    | T_TERN operator operator priority assoc    { operatorNode->pushTern(*$2, *$3, $5, $4); delete $2; delete $3; }
    | T_PRE operator priority                    { operatorNode->pushPre(*$2, $3); delete $2; }
    | T_POST operator priority                   { operatorNode->pushPost(*$2, "0", $3); delete $2; delete $3; }
    | T_POST operator priority assoc             { operatorNode->pushPost(*$2, $4, $3); delete $2; }
    | T_PAREN operator operator                  { operatorNode->pushParen(*$2, *$3); delete $2; delete $3; }
    ;
    
priority
    : '0'                          { $$ = (char*)"0"; }
    | T_NUMBER                     { $$ = $1; }
    | T_PRIORITY T_CODE            { $$ = $2; }
    ;
    
assoc
    : T_LEFT_ASSOC                 { $$ = (char*)"1"; }
    | T_RIGHT_ASSOC                { $$ = (char*)"0"; }
    | T_IS_LEFT_ASSOC T_CODE       { uint yyleng = strlen($2);
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, $2);
                                     strcpy(tmp+yyleng+6-6+1, "?1:0)");
                                     $$ = tmp;
                                   }
    | T_IS_RIGHT_ASSOC T_CODE      { uint yyleng = strlen($2);
                                     char *tmp = (char*)calloc(yyleng+7, sizeof(char));
                                     tmp[0] = '(';
                                     strcpy(tmp+1, $2);
                                     strcpy(tmp+yyleng+6-6+1, "?0:1)");
                                     $$ = tmp;
                                   }
    ;
    
operator
    : '?' T_CODE T_TERMINAL T_CODE { $$ = KDevPG::makeOperator(KDevPG::globalSystem.terminal($3), $2, $4); }
    | '?' T_CODE T_TERMINAL        { $$ = KDevPG::makeOperator(KDevPG::globalSystem.terminal($3), $2, ""); }
    | T_TERMINAL T_CODE            { $$ = KDevPG::makeOperator(KDevPG::globalSystem.terminal($1), "", $2); }
    | T_TERMINAL                   { $$ = KDevPG::makeOperator(KDevPG::globalSystem.terminal($1), "", ""); }
    ;

variableDeclarations
    : variableDeclaration              { $$ = $1; }
    | variableDeclarations variableDeclaration
        {
          KDevPG::Model::VariableDeclarationItem *last = (KDevPG::Model::VariableDeclarationItem*) $1;
          while (last->mNext != 0) {
            last = last->mNext;
          }
          last->mNext = (KDevPG::Model::VariableDeclarationItem*) $2;
          $$ = $1;
        }
    ;

variableDeclaration
    : declarationType_opt storageType variableType T_IDENTIFIER ':' T_IDENTIFIER
        { $$ = KDevPG::variableDeclaration($1, $2, $3, false, $4, $6); }
    | declarationType_opt storageType T_TOKEN       T_IDENTIFIER ';'
        { $$ = KDevPG::variableDeclaration($1, $2, KDevPG::Model::VariableDeclarationItem::TypeToken, false, $4, ""); }
    | declarationType_opt storageType variableType '#' T_IDENTIFIER ':' T_IDENTIFIER
        { $$ = KDevPG::variableDeclaration($1, $2, $3, true, $5, $7); }
    | declarationType_opt storageType T_TOKEN       '#' T_IDENTIFIER ';'
        { $$ = KDevPG::variableDeclaration($1, $2, KDevPG::Model::VariableDeclarationItem::TypeToken, true, $5, ""); }
    ;

declarationType_opt
    : /* empty */       { $$ = KDevPG::Model::VariableDeclarationItem::DeclarationLocal;     }
    | T_ARGUMENT        { $$ = KDevPG::Model::VariableDeclarationItem::DeclarationArgument;  }
    ;

storageType
    : T_MEMBER          { $$ = KDevPG::Model::VariableDeclarationItem::StorageAstMember;    }
    | T_TEMPORARY       { $$ = KDevPG::Model::VariableDeclarationItem::StorageTemporary;     }
    ;

variableType
    : T_NODE            { $$ = KDevPG::Model::VariableDeclarationItem::TypeNode;             }
    | T_VARIABLE        { $$ = KDevPG::Model::VariableDeclarationItem::TypeVariable;         }
    ;

%%
