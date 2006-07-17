
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
   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#include "kdev-pg.h"
#include "kdev-pg-clone-tree.h"

#include <cassert>

extern int yylex();
extern void yyerror(char const *msg);

%}

%union {
    model::node *item;
    char* str;
    model::annotation_item::scope_type_enum scope;
}

%token T_IDENTIFIER T_ARROW T_TERMINAL T_CODE T_STRING ';'
%token T_TOKEN_DECLARATION T_TOKEN_STREAM_DECLARATION T_MEMBER_DECLARATION
%token T_PUBLIC T_PRIVATE T_PROTECTED T_DECLARATION T_CONSTRUCTOR T_DESTRUCTOR

%type<str> T_IDENTIFIER T_TERMINAL T_CODE T_STRING name code_opt
%type<item> item primary_item primary_atom unary_item question question_item
%type<item> postfix_item option_item item_sequence conditional_item
%type<item> member_declaration_rest
%type<scope> scope

%%

system
    : code_opt { _G_system.decl = $1; }
      declarations
      rules
      code_opt { _G_system.bits = $5; }
    ;

declarations
    : declaration
    | declarations declaration
    ;

declaration
    : T_MEMBER_DECLARATION '(' T_IDENTIFIER ':' member_declaration_rest { _G_system.push_member($3,$5); }
    | T_TOKEN_DECLARATION declared_tokens ';'
    | T_TOKEN_STREAM_DECLARATION T_IDENTIFIER ';' { _G_system.token_stream = $2; }
    ;

member_declaration_rest
    : T_PUBLIC T_DECLARATION ')' T_CODE
        { $$ = pg::member(settings::member_item::public_declaration, $4); }
    | T_PROTECTED T_DECLARATION ')' T_CODE
        { $$ = pg::member(settings::member_item::protected_declaration, $4); }
    | T_PRIVATE T_DECLARATION ')' T_CODE
        { $$ = pg::member(settings::member_item::private_declaration, $4); }
    | T_CONSTRUCTOR ')' T_CODE
        { $$ = pg::member(settings::member_item::constructor_code, $3); }
    | T_DESTRUCTOR ')' T_CODE
        { $$ = pg::member(settings::member_item::destructor_code, $3); }
    ;

declared_tokens
    : T_TERMINAL                        { _G_system.push_terminal($1,$1); }
    | T_TERMINAL '(' T_STRING ')'       { _G_system.push_terminal($1,$3); }
    | declared_tokens ',' T_TERMINAL    { _G_system.push_terminal($3,$3); }
    | declared_tokens ',' T_TERMINAL '(' T_STRING ')'  { _G_system.push_terminal($3,$5); }
    ;

rules
    : item ';'                          { _G_system.push_rule($1); }
    | rules item ';'                    { _G_system.push_rule($2); }
    ;

primary_item
    : '0'                               { $$ = _G_system.zero(); }
    | '(' option_item ')'               { $$ = $2; }
    | primary_atom                      { $$ = $1; }
    | name scope primary_atom
        { $$ = pg::annotation($1, $3, model::annotation_item::type_node, $2); }
    | '#' name scope primary_atom
        { $$ = pg::annotation($2, $4, model::annotation_item::type_sequence, $3); }
    ;

primary_atom
    : T_IDENTIFIER                      { $$ = _G_system.push_symbol($1); }
    | T_TERMINAL                        { $$ = _G_system.terminal($1); }
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
    : '=' { $$ = model::annotation_item::scope_ast_member; }
    | ':' { $$ = model::annotation_item::scope_local; }
    ;

unary_item
    : primary_item '+'                  { $$ = pg::plus($1); }
    | primary_item '*'                  { $$ = pg::star($1); }
    | primary_item                      { $$ = $1; }
/*    | '?' primary_item                  { $$ = pg::alternative($2, _G_system.zero()); } */
    ;

question
    : question_item                     { $$ = $1; }
    | question question_item            { $$ = pg::cons($1, $2); }
    ;

question_item
    : T_IDENTIFIER                      { $$ = _G_system.push_symbol($1); }
    | T_TERMINAL                        { $$ = _G_system.terminal($1); }
    ;

postfix_item
    : unary_item                        { $$ = $1; }
    | postfix_item '@' primary_item
        {
          clone_tree cl;
          $$ = pg::cons($1, pg::star(pg::cons(cl.clone($3), cl.clone($1))));
        }
    | postfix_item T_CODE               { $$ = pg::action($1, $2); }
    ;

item_sequence
    : postfix_item                      { $$ = $1; }
    | item_sequence postfix_item        { $$ = pg::cons($1, $2); }
    ;

conditional_item
    : item_sequence                     { $$ = $1; }
    | '?' T_CODE item_sequence          { $$ = pg::condition($2, $3); }
    | '?' '(' question ')' item_sequence
        {
          $$ = $5;
          fprintf(stderr, "** WARNING ``question'' not implemented!!\n");
        }
    ;

option_item
    : conditional_item                  { $$ = $1; }
    | option_item '|' conditional_item  { $$ = pg::alternative($1, $3); }
    ;

item
    : option_item T_ARROW T_IDENTIFIER code_opt
        {
          $$ = pg::evolve($1, _G_system.push_symbol($3), $4);
        }
    ;

code_opt
    :                                   { $$ = ""; }
    | T_CODE                            { $$ = $1; }
    ;

%%
