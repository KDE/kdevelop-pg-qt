
%{
/* This file is part of kdev-pg
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

#include <cassert>

extern int yylex();
extern void yyerror(const char* msg);

%}

%union {
    KDevPG::Model::Node *item;
    char* str;
    KDevPG::Model::VariableDeclarationItem::DeclarationType declarationType;
    KDevPG::Model::VariableDeclarationItem::StorateType     storageType;
    KDevPG::Model::VariableDeclarationItem::VariableType    variableType;
}

%token T_IDENTIFIER T_ARROW T_TERMINAL T_CODE T_STRING ';'
%token T_TOKEN_DECLARATION T_TOKEN_STREAM_DECLARATION T_NAMESPACE_DECLARATION
%token T_PARSERCLASS_DECLARATION T_PUBLIC T_PRIVATE T_PROTECTED T_DECLARATION
%token T_CONSTRUCTOR T_DESTRUCTOR T_TRY_RECOVER T_TRY_ROLLBACK T_CATCH
%token T_RULE_ARGUMENTS T_MEMBER T_TEMPORARY T_ARGUMENT T_EXPORT_MACRO
%token T_NODE T_NODE_SEQUENCE T_TOKEN T_VARIABLE T_EXPORT_MACRO_HEADER

%type<str> T_IDENTIFIER T_TERMINAL T_CODE T_STRING T_RULE_ARGUMENTS
%type<str> name code_opt rule_arguments_opt
%type<item> item primary_item try_item primary_atom unary_item
%type<item> postfix_item option_item item_sequence conditional_item
%type<item> member_declaration_rest variableDeclarations variableDeclaration
%type<declarationType> declarationType_opt
%type<storageType>     scope storageType
%type<variableType>    variableType

%%

system
    : code_opt { globalSystem.decl = $1; }
      declarations
      rules
      code_opt { globalSystem.bits = $5; }
    ;

declarations
    : declaration
    | declarations declaration
    ;

declaration
    : T_PARSERCLASS_DECLARATION member_declaration_rest
        { globalSystem.pushParserClassMember($2); }
    | T_TOKEN_DECLARATION declared_tokens ';'
    | T_TOKEN_STREAM_DECLARATION T_IDENTIFIER ';'
        { globalSystem.tokenStream = $2;           }
    | namespace_declaration
    | T_EXPORT_MACRO T_STRING
        { globalSystem.exportMacro = $2;           }
    | T_EXPORT_MACRO_HEADER T_STRING
        { globalSystem.exportMacroHeader = $2;   }
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

namespace_declaration
    : T_NAMESPACE_DECLARATION T_IDENTIFIER T_CODE
        { globalSystem.pushNamespace($2, $3); }
    ;

declared_tokens
    : T_TERMINAL                        { globalSystem.pushTerminal($1,$1); }
    | T_TERMINAL '(' T_STRING ')'       { globalSystem.pushTerminal($1,$3); }
    | declared_tokens ',' T_TERMINAL    { globalSystem.pushTerminal($3,$3); }
    | declared_tokens ',' T_TERMINAL '(' T_STRING ')'
                                        { globalSystem.pushTerminal($3,$5); }
    ;

rules
    : item ';'                          { globalSystem.pushRule($1); }
    | rules item ';'                    { globalSystem.pushRule($2); }
    | rules namespace_declaration
    ;

primary_item
    : '0'                               { $$ = globalSystem.zero(); }
    | '(' option_item ')'               { $$ = $2; }
    | try_item                    { $$ = $1; }
    | primary_atom                      { $$ = $1; }
    | name scope primary_atom           { $$ = KDevPG::annotation($1, $3, false, $2); }
    | '#' name scope primary_atom       { $$ = KDevPG::annotation($2, $4, true, $3);  }
    ;

primary_atom
    : T_IDENTIFIER rule_arguments_opt   { $$ = KDevPG::nonTerminal(globalSystem.pushSymbol($1), $2); }
    | T_TERMINAL                        { $$ = globalSystem.terminal($1); }
    ;

try_item
    : T_TRY_RECOVER '(' option_item ')'
        {
          globalSystem.needStateManagement = true;
          $$ = KDevPG::tryCatch($3, 0);
        }
    | T_TRY_ROLLBACK '(' option_item ')' T_CATCH '(' option_item ')'
        {
          globalSystem.needStateManagement = true;
          $$ = KDevPG::tryCatch($3, $7);
        }

rule_arguments_opt
    : /* empty */                       { $$ = ""; }
    | T_RULE_ARGUMENTS                  { $$ = $1; }
    ;

name
    : T_IDENTIFIER                      { $$ = $1; }
    | T_IDENTIFIER '.' T_IDENTIFIER
        {
          $$ = $3;
          fprintf(stderr, "** WARNING support for scoped name"
                          " ``%s.%s'' not implemented\n", $1, $3);
        }
    ;

scope
    : '=' { $$ = KDevPG::Model::VariableDeclarationItem::StorageAstMember; }
    | ':' { $$ = KDevPG::Model::VariableDeclarationItem::StorageTemporary;  }
    ;

unary_item
    : primary_item '+'                  { $$ = KDevPG::plus($1); }
    | primary_item '*'                  { $$ = KDevPG::star($1); }
    | primary_item                      { $$ = $1; }
/*    | '?' primary_item                  { $$ = KDevPG::alternative($2, globalSystem.zero()); } */
    ;

postfix_item
    : unary_item                        { $$ = $1; }
    | postfix_item '@' primary_item
        {
          KDevPG::CloneTree cl;
          $$ = KDevPG::cons($1, KDevPG::star(KDevPG::cons(cl.clone($3), cl.clone($1))));
        }
    | postfix_item T_CODE               { $$ = KDevPG::action($1, $2); }
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
          $$ = KDevPG::evolve($1, globalSystem.pushSymbol($3),
                          (KDevPG::Model::VariableDeclarationItem*) $6, $4);
        }
    | option_item T_ARROW T_IDENTIFIER '[' variableDeclarations ']' code_opt
        {
          $$ = KDevPG::evolve($1, globalSystem.pushSymbol($3),
                          (KDevPG::Model::VariableDeclarationItem*) $5, $7);
        }
    | option_item T_ARROW T_IDENTIFIER code_opt
        { $$ = KDevPG::evolve($1, globalSystem.pushSymbol($3), 0, $4); }
    ;

code_opt
    : /* empty */                       { $$ = ""; }
    | T_CODE                            { $$ = $1; }
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
