
%{
#include "kdev-pg.h"
#include "kdev-pg-clone-tree.h"

#include <cassert>

extern int yylex();
extern void yyerror(char const *msg);

%}

%union {
    model::node *item;
    char* str;
    int ival;
}

%token T_IDENTIFIER T_ARROW T_TERMINAL T_CODE T_STRING ';'
%token T_TOKEN_DECLARATION T_TOKEN_STREAM_DECLARATION T_MEMBER_DECLARATION
%token T_PUBLIC T_PRIVATE T_PROTECTED T_DECLARATION T_CONSTRUCTOR T_DESTRUCTOR

%type<str> T_IDENTIFIER T_TERMINAL T_CODE T_STRING name code_opt
%type<item> item primary_item unary_item question question_item
%type<item> postfix_item option_item item_sequence conditional_item
%type<item> member_declaration_rest
%type<ival> scope

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
    :  T_PUBLIC T_DECLARATION ')' T_CODE
        { $$ = pg::member(settings::member_item::public_declaration, $4); }
    |  T_PROTECTED T_DECLARATION ')' T_CODE
        { $$ = pg::member(settings::member_item::protected_declaration, $4); }
    |  T_PRIVATE T_DECLARATION ')' T_CODE
        { $$ = pg::member(settings::member_item::private_declaration, $4); }
    |  T_CONSTRUCTOR ')' T_CODE
        { $$ = pg::member(settings::member_item::constructor_code, $3); }
    |  T_DESTRUCTOR ')' T_CODE
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
    | T_IDENTIFIER                      { $$ = _G_system.push_symbol($1); }
    | T_TERMINAL                        { $$ = _G_system.terminal($1); }
    | name scope T_IDENTIFIER           { $$ = pg::annotation($1, _G_system.push_symbol($3), false, ($2 == ':')); }
    | name scope T_TERMINAL             { $$ = pg::annotation($1, _G_system.terminal($3), false, ($2 == ':')); }
    | '#' name scope T_IDENTIFIER       { $$ = pg::annotation($2, _G_system.push_symbol($4), true, ($3 == ':')); }
    | '#' name scope T_TERMINAL         { $$ = pg::annotation($2, _G_system.terminal($4), true, ($3 == ':')); }
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
    : '=' { $$ = '='; }
    | ':' { $$ = ':'; }
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
