

%{
#include "kdev-pg.h"
#include "kdev-pg-clone-tree.h"

#include <cassert>
#include <iostream>

int yylex();
void yyerror(char const *msg);
%}

%union {
    model::node *item;
    char const *str;
    int ival;
}

%token T_IDENTIFIER T_ARROW T_TERMINAL T_CONDITION T_TOKEN_STREAM

%type<str> T_IDENTIFIER T_TERMINAL T_CONDITION T_TOKEN_STREAM name code_opt
%type<item> rule item primary_item unary_item question question_item
%type<item> postfix_item option_item item_sequence conditional_item
%type<ival> scope

%%

system
    : code_opt { _G_system.decl = $1; } rules code_opt {_G_system.bits = $4; }
    ;

rules
    : rule
    | rules rule
    ;

rule
    : item ';'                          { _G_system.push_rule($1); }
    | T_TOKEN_STREAM T_IDENTIFIER ';'	{ _G_system.token_stream = $2; }
    ;

primary_item
    : '0'                               { $$ = _G_system.zero(); }
    | '(' option_item ')'               { $$ = $2; }
    | T_IDENTIFIER                      { $$ = _G_system.push_symbol($1); }
    | T_TERMINAL                        { $$ = _G_system.push_terminal($1); }
    | name scope T_IDENTIFIER           { $$ = pg::annotation($1, _G_system.push_symbol($3), false, ($2 == ':')); }
    | name scope T_TERMINAL             { $$ = pg::annotation($1, _G_system.push_terminal($3), false, ($2 == ':')); }
    | '#' name scope T_IDENTIFIER       { $$ = pg::annotation($2, _G_system.push_symbol($4), true, ($3 == ':')); }
    | '#' name scope T_TERMINAL         { $$ = pg::annotation($2, _G_system.push_terminal($4), true, ($3 == ':')); }
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
    : primary_item                      { $$ = $1; }
/*    | '?' primary_item                  { $$ = pg::alternative($2, _G_system.zero()); } */
    | '!' primary_item                  { $$ = pg::bang($2); }
    ;

question
    : question_item			{ $$ = $1; }
    | question question_item		{ $$ = pg::cons($1, $2); }
    ;

question_item
    : T_IDENTIFIER			{ $$ = _G_system.push_symbol($1); }
    | T_TERMINAL			{ $$ = _G_system.push_terminal($1); }
    ;

postfix_item
    : unary_item
    | postfix_item '@' primary_item
	{
	  clone_tree cl;
	  $$ = pg::cons($1, pg::alternative (pg::bang(pg::cons(cl.clone($3), cl.clone($1))), _G_system.zero()));
	}
    | postfix_item T_CONDITION               { $$ = pg::action($1, $2); }
    ;

item_sequence
    : postfix_item                      { $$ = $1; }
    | item_sequence postfix_item        { $$ = pg::cons($1, $2); }
    ;

conditional_item
    : item_sequence			{ $$ = $1; }
    | '?' T_CONDITION item_sequence	{ $$ = pg::condition($2, $3); }
    | '?' '(' question ')' item_sequence{
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
    :                                        { $$ = ""; }
    | T_CONDITION                            { $$ = $1; }
    ;

%%

#include <cstdio>

extern FILE *file;

int yytoken = 0, ch = ' ';
int yy_line = 1, yy_column = 1, yy_start_column = 1;
char yybuffer[512 * 1024], *yyptr = yybuffer, *yytext = yyptr;
static char yy_text_line[4 * 1024];

static void inp()
{
  ch = fgetc(file);
  yy_text_line[yy_column - 1] = ch;

  if (ch == '\n')
    {
      ++yy_line;
      yy_column = 1;
    }
  else
    ++yy_column;
}

static bool isid() { return std::isalnum(ch) || ch == '_'; }

int yylex()
{
again:
    while (std::isspace(ch))
        inp();

    yy_start_column = yy_column;

    yytoken = ch;

    if (yytoken == EOF) {
        return (yytoken = 0);
    } else if (std::isalpha(ch)) {
        yytext = yyptr;
        yylval.str = yytext;
        do { *yyptr++ = ch; inp(); } while (isid());
        *yyptr++ = '\0';
	char const *p = yytext;
	while (unsigned char c = *p++)
	  if (c != '_' && (c < 'A' || c > 'Z'))
            return (yytoken = T_IDENTIFIER);
        return (yytoken = T_TERMINAL);
    }

    inp();

    if (yytoken == '%' && std::isalpha(ch)) {
        yytext = yyptr;
        yylval.str = yytext;
        do { *yyptr++ = ch; inp(); } while (isid());
        *yyptr++ = '\0';
	if (!strcmp(yytext, "token_stream"))
	  return T_TOKEN_STREAM;
	assert(0);
	return '%';
    } else if (yytoken == ';' && ch == ';') {
        inp();
        return ';';
    } else if (yytoken == '-' && ch == '-') {
        do { inp(); } while (ch != EOF && ch != '\n');
        goto again;
    } else if (yytoken == '[' && ch == ':') {
        inp();
        yytext = yyptr;
        yylval.str = yytext;
        do
          { *yyptr++ = ch; yytoken = ch; inp(); }
        while (ch != 0 && (yytoken != ':' || ch != ']'));
        assert(ch == ']');
        *(yyptr-1) = '\0';
        inp();
        return (yytoken = T_CONDITION);
    } else if (yytoken == '-' && ch == '>') {
        inp();
        return (yytoken = T_ARROW);
    }

    return yytoken;
}

void yyerror(char const *)
{
  std::cerr << "** SYNTAX ERROR at line " << yy_line << " column " << yy_start_column - 1 << std::endl;

  int saved_yy_start_column = yy_start_column - 1;
  int saved_yy_column = yy_column - 1;
  int line_length = saved_yy_column;

  while (ch != '\n' && ch != EOF)
    inp(), ++line_length;

  yy_text_line[line_length - 1] = '\0';

  std::cerr << yy_text_line << std::endl;

  int c = 1;

  while (c++ < saved_yy_start_column)
    std::cerr << " ";

  std::cerr << "^" << std::endl << std::endl;

  exit(EXIT_FAILURE);
}
