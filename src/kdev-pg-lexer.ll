%{
/*
    SPDX-FileCopyrightText 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <QDebug>

#include "kdev-pg.h"
#include "kdev-pg-parser.hh"

#include <QFile>
#include <QFileInfo>
#include <QTextStream>

int inp();
void appendLineBuffer();
void newline();
void countNewlines(const char*, int);
void yyerror(const char* );
extern int yyLine;
extern int currentOffset;
extern bool yymoreFlag;

namespace KDevPG
{
  extern QFile file;
  extern QFileInfo fileInfo;
  extern QTextStream checkOut;
}

#define YYMORE yymoreFlag = true; yymore();

#define YY_INPUT(buf, result, max_size) \
  { \
    int c = inp(); \
    result = (c == EOF) ? YY_NULL : (buf[0] = (char)c, 1); \
  }

#define YY_USER_ACTION  appendLineBuffer();

#define COPY_TO_YYLVAL(string, len) \
    yylval.str = (char*) calloc(len+1, sizeof(char)); \
    strncpy(yylval.str, string, len); \
    yylval.str[len] = '\0';
#define COPY_CODE_TO_YYLVAL(string, len) \
    if(KDevPG::globalSystem.lineNumberPolicy == KDevPG::World::BeautifulCode) \
    { \
      COPY_TO_YYLVAL(string, len) \
    } \
    else \
    { \
      QByteArray tmp("\n#"); \
      if(KDevPG::globalSystem.lineNumberPolicy == KDevPG::World::CompatibilityLineNumbers) \
        tmp += "line"; \
      tmp += " " + QString::number(firstCodeLine).toLocal8Bit(); \
      tmp += " \"" + KDevPG::fileInfo.absoluteFilePath().toLocal8Bit() + "\""; \
      if(KDevPG::globalSystem.lineNumberPolicy == KDevPG::World::FullLineNumbers) \
        tmp += " 1"; \
      tmp += "\n"; \
      size_t memlen = tmp.size() + firstCodeColumn + len + 16 + 1; \
      yylval.str = (char*) calloc(memlen, sizeof(char)); \
      strncpy(yylval.str, tmp.data(), tmp.size()); \
      memset(yylval.str + tmp.size(), ' ', firstCodeColumn); \
      strncpy(yylval.str + tmp.size() + firstCodeColumn, string, len); \
      yylval.str[memlen-1] = '\0'; \
    }

#define ESCAPE_CHARACTER(chr) \
        yylval.str = (char*) calloc(2, sizeof(char)); yylval.str[0] = chr; yylval.str[1] = '\0'; return T_STRING;

namespace {
  enum RulePosition {
    RuleBody,
    RuleFooter,
    RuleLexer
  };
  RulePosition rulePosition = RuleBody;
  int openBrackets; // for rule arguments and regexp usage
  int firstCodeLine; // where the current code-block begins
  int firstCodeColumn;
}

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

%}

Whitespace  [ \f\t]
Newline     "\r\n"|\r|\n
String      ["]([^\r\n\"]|[\\][^\r\n])*["]
Char        [_a-zA-Z0-9]|\\[xXuU][0-9a-fA-F]{1,6}|\\[oO][0-7][0-7]*|\\[dD][0-9]{1,7}|\\[yY][01]{1,21}|\\[\x20-\x7f]

%x CODE
%x PARSERCLASS
%x RULE_ARGUMENTS
%x RULE_PARAMETERS_HEADER
%x RULE_PARAMETERS_VARNAME
%x RULE_LEXER

%%


{Whitespace}*           /* skip */ ;
{Newline}               newline();
"--"[^\r\n]*            /* line comments, skip */ ;

";"+                    rulePosition = RuleBody; return ';';
"->"                    if(rulePosition == RuleLexer) BEGIN(RULE_LEXER); else rulePosition = RuleFooter; return T_ARROW;
".="                    return T_INLINE;

"("                     return '(';
")"                     return ')';
"{"                     return '{';
"}"                     return '}';
","                     return ',';
"0"                     return '0';
"#"                     return '#';
"."                     return '.';
":"                     return ':';
"="                     return '=';
"+"                     return '+';
"*"                     return '*';
"?"                     return '?';
"@"                     return '@';
"|"                     return '|';
"&"                     return '&';

"try/recover"           return T_TRY_RECOVER;
"try/rollback"          return T_TRY_ROLLBACK;
"catch"                 return T_CATCH;

"%export_macro"         return T_EXPORT_MACRO;
"%export_macro_header"  return T_EXPORT_MACRO_HEADER;
"%token"                return T_TOKEN_DECLARATION;
"%token_stream"         return T_TOKEN_STREAM_DECLARATION;
"%namespace"            return T_NAMESPACE_DECLARATION;
"%parserclass"          BEGIN(PARSERCLASS); return T_PARSERCLASS_DECLARATION;
"%lexerclass"           BEGIN(PARSERCLASS); return T_LEXERCLASS_DECLARATION;
"%input_stream"         return T_INPUT_STREAM;
"%ast_extra_members"    return T_AST_DECLARATION;
"%parser_declaration_header"   return T_PARSER_DECLARATION_HEADER;
"%parser_bits_header"   return T_PARSER_BITS_HEADER;
"%ast_header"           return T_AST_HEADER;
"%lexer_declaration_header"   return T_LEXER_DECLARATION_HEADER;
"%lexer_bits_header" return T_LEXER_BITS_HEADER;
"%input_encoding"       return T_INPUT_ENCODING;
"%table_lexer"          return T_TABLE_LEXER;
"%sequence_lexer"       return T_SEQUENCE_LEXER;
"%ast_base"             return T_AST_BASE;
"%parser_base"          return T_PARSER_BASE;
"%lexer_base"           return T_LEXER_BASE;
"%bin"                  return T_BIN;
"%pre"                  return T_PRE;
"%post"                 return T_POST;
"%tern"                 return T_TERN;
"%paren"                return T_PAREN;
"%priority"             return T_PRIORITY;
"%<"                    rulePosition = RuleBody; return T_LOPR;
"%>"                    rulePosition = RuleFooter; return T_ROPR;
"%left"                 return T_LEFT_ASSOC;
"%right"                return T_RIGHT_ASSOC;
"%isLeft"               return T_IS_LEFT_ASSOC;
"%isRight"              return T_IS_RIGHT_ASSOC;
"%lexer"                rulePosition = RuleLexer; return T_LEXER;

<PARSERCLASS>{
  {Whitespace}*           /* skip */ ;
  {Newline}               newline();
  "("                     return '(';
  "public"                return T_PUBLIC;
  "private"               return T_PRIVATE;
  "protected"             return T_PROTECTED;
  "declaration"           return T_DECLARATION;
  "constructor"           return T_CONSTRUCTOR;
  "destructor"            return T_DESTRUCTOR;
  "bits"                  return T_BITS;
  ")"                     BEGIN(INITIAL); return ')';
  .                       BEGIN(INITIAL); REJECT; /* everything else */
}


"[" {
    if (rulePosition == RuleBody) { /* use the arguments in a rule call */
      firstCodeLine = yyLine;
      openBrackets = 0;
      BEGIN(RULE_ARGUMENTS);
    }
    else if (rulePosition == RuleFooter) { /* declare the arguments */
      BEGIN(RULE_PARAMETERS_HEADER); return '[';
    }
}

<RULE_LEXER>{
  "--"[^\r\n]*            /* line comments, skip */ ;
  {Newline}               newline();
  "{"[a-zA-Z_][a-zA-Z_0-9]*"}"          ++yytext; COPY_TO_YYLVAL(yytext,yyleng-2); return T_NAMED_REGEXP;
  ";"+(("--"[^\r\n]*[\r\n])|[ \f\t\r\n])+/";"+   countNewlines(yytext, yyleng); rulePosition = RuleBody; BEGIN(INITIAL); return ';';
  ";"+                    return ';';
  "["                     ++openBrackets; return '[';
  "]"                     --openBrackets; return ']';
  "("                     ++openBrackets; return '(';
  ")"                     --openBrackets; return ')';
  "?"                     return '?';
  "|"                     return '|';
  "^"                     return '^';
  {Char}"-"{Char}         COPY_TO_YYLVAL(yytext,yyleng); return T_RANGE;
  "&"                     return '&';
  "~"                     return '~';
  "*"                     return '*';
  "+"                     return '+';
  "@"                     return '@';
  "."                     return '.';
  "->"                    return T_ARROW;
  "%continue"             return T_CONTINUE;
  "%fail"                 return T_FAIL;
  "%enter"                return T_ENTER_RULE_SET;
  "%leave"                return T_LEAVE_RULE_SET;
  "%la"                   return T_LOOKAHEAD;
  "%ba"                   return T_BARRIER;
  "[:"                    firstCodeLine = yyLine; firstCodeColumn = currentOffset + 2; BEGIN(CODE);
  [_A-Z]+/[ \f\t\r\n]*";" COPY_TO_YYLVAL(yytext,yyleng); return T_TERMINAL;
  [_a-zA-Z0-9]+/[ \f\t\r\n]*";" COPY_TO_YYLVAL(yytext,yyleng); return T_IDENTIFIER;
  {Char}+ COPY_TO_YYLVAL(yytext,yyleng); return T_UNQUOTED_STRING;
  {Whitespace}            /* skip */
  {String}                yytext++; COPY_TO_YYLVAL(yytext,yyleng-2); return T_STRING;
  
  <<EOF>> {
    BEGIN(INITIAL); // is not set automatically by yyrestart()
    KDevPG::checkOut << "** ERROR Encountered end of file in an unclosed rule lexer definition..." << Qt::endl;
    yyerror("");
    return 0;
  }
}

<RULE_ARGUMENTS>{
  {Newline}               newline(); YYMORE;
  {String}                YYMORE; /* this and... */
  ["]                     YYMORE; /* ...this prevent brackets inside strings to be counted */
  [^\[\]\n\r\"]*          YYMORE; /* gather everything that's not a bracket, and append what comes next */
  "["                     openBrackets++; YYMORE;
  "]" {
      openBrackets--;
      if (openBrackets < 0) {
        COPY_CODE_TO_YYLVAL(yytext,(yyleng-1)); /* cut off the trailing bracket */
        BEGIN(INITIAL);
        return T_RULE_ARGUMENTS;
      }
  }
  <<EOF>> {
      BEGIN(INITIAL); // is not set automatically by yyrestart()
      KDevPG::checkOut << "** ERROR Encountered end of file in an unclosed rule argument specification..." << Qt::endl;
      yyerror("");
      return 0;
  }
}

<RULE_PARAMETERS_HEADER>{
  {Whitespace}*           /* skip */ ;
  {Newline}               newline();
  "--"[^\r\n]*            /* line comments, skip */ ;
  ":"{Whitespace}*        BEGIN(RULE_PARAMETERS_VARNAME); return ':';
  "#"                     return '#';
  "member"                return T_MEMBER;
  "temporary"             return T_TEMPORARY;
  "argument"              return T_ARGUMENT;
  "node"                  return T_NODE;
  "token"                 return T_TOKEN;
  "variable"              return T_VARIABLE;
  ";"                     return ';';  /* only used for "token" types */
  [_a-zA-Z]*[_a-zA-Z0-9]+           COPY_TO_YYLVAL(yytext,yyleng); return T_IDENTIFIER;
  "]"                     BEGIN(INITIAL); return ']';
  .                       BEGIN(INITIAL); REJECT; /* everything else */
}

<RULE_PARAMETERS_VARNAME>{
  {Newline}               newline(); YYMORE;
  [^;\r\n]*               YYMORE; /* gather everything that's not a semicolon, and append what comes next */
  ";" {
      // strip trailing whitespace
      int length = yyleng-1; // and first, the trailing semicolon
      for (int i = length-1; i < 1; i--) {
        switch(yytext[i-1])
        {
          case ' ':
          case '\f':
          case '\t':
            continue;
          default:
            length = i;
            break;
        }
      }
      COPY_TO_YYLVAL(yytext,length);
      BEGIN(RULE_PARAMETERS_HEADER);
      return T_IDENTIFIER;
  }
  .                       BEGIN(INITIAL); REJECT; /* everything else */
}


"[:"                    firstCodeLine = yyLine; firstCodeColumn = currentOffset + 2; BEGIN(CODE);
<CODE>{
  {Newline}               newline(); YYMORE;
  [^:\n\r]*               YYMORE; /* gather everything that's not a colon, and append what comes next */
  ":"+[^:\]\n\r]*         YYMORE; /* also gather colons that are not followed by colons or newlines */
  ":]" {
      COPY_CODE_TO_YYLVAL(yytext, (yyleng-2)); /* cut off the trailing stuff */
      if(rulePosition == RuleLexer)
        BEGIN(RULE_LEXER);
      else
        BEGIN(INITIAL);
      return T_CODE;
  }
  <<EOF>> {
      BEGIN(INITIAL); // is not set automatically by yyrestart()
      KDevPG::checkOut << "** ERROR Encountered end of file in an unclosed code segment..." << Qt::endl;
      yyerror("");
      return 0;
  }
}


[_A-Z]+                 COPY_TO_YYLVAL(yytext,yyleng); return T_TERMINAL;
[_a-zA-Z][_a-zA-Z0-9]*           COPY_TO_YYLVAL(yytext,yyleng); return T_IDENTIFIER;
[0-9]+                  COPY_TO_YYLVAL(yytext,yyleng); return T_NUMBER;


{String} {
   yytext++;                         /* start inside the quotes */
   COPY_TO_YYLVAL(yytext,yyleng-2);  /* cut off the trailing quote */
   return T_STRING;
}

. {
  KDevPG::checkOut << "Unexpected character: ``" << yytext[0] << "''" << Qt::endl;
  yyerror("");
}


%%

char ch;
int yyLine = 1, currentOffset = 0;
bool endOfLine = false, yymoreFlag = false;
int yyTextLineLeng = 1024;
char *yyTextLine = (char*)malloc(yyTextLineLeng);

int inp()
{
  if( KDevPG::file.atEnd() )
    return EOF;
  KDevPG::file.getChar( &ch );
  return ch;
}

void newline()
{
  ++yyLine;
  endOfLine = true;
}

void countNewlines(const char* code, int leng)
{
  for(int i = 0; i != leng; ++i)
    if(code[i] == '\n')
      ++yyLine;
}

/* initialize the line buffer */
void clearLineBuffer()
{
  yyTextLine[0] = '\0';
  currentOffset = 0;
  endOfLine = false;
}

struct InitLineBuffer
{
  InitLineBuffer()
  {
    clearLineBuffer();
  }
} _initLineBuffer;

 /* add the current token to the current line */
void appendLineBuffer()
{
  if (endOfLine == true)
    clearLineBuffer();
  
  static int lastTextLeng = 0;
  
  currentOffset = strlen(yyTextLine); /* start of current */
  
  int newLeng = currentOffset + strlen(yytext) - (yymoreFlag ? lastTextLeng : 0) + 1;
  if(newLeng > yyTextLineLeng)
  {
    do
    {
      yyTextLineLeng *= 2;
    }
    while(newLeng > yyTextLineLeng);
    yyTextLine = (char*)realloc(yyTextLine, yyTextLineLeng);
  }
  
  strcpy(yyTextLine+currentOffset, yytext + (yymoreFlag ? lastTextLeng : 0)); /* append current */
  /* strcpy is faster than strcat */
  
  Q_ASSERT(strlen(yyTextLine) < size_t(yyTextLineLeng));
  
  lastTextLeng = strlen(yytext);
  yymoreFlag = false;
}

void yyerror(const char* msg )
{
  Q_UNUSED(msg);
  KDevPG::checkOut << "** LEXICAL ERROR at line " << yyLine << " column " << currentOffset << Qt::endl;

  char *current_end = yyTextLine + strlen(yyTextLine);
  char *p;

  /* get the rest of the line if we are not already at the end */
  if(!endOfLine)
    {
      p = current_end;
      int c = ch;

      while(c != EOF && c != '\n')
        {
          *p++ = c;
          c = inp();
        }

      *p++ = '\n';
      *p = 0;
    }

  /* yyTextLine[] now has the whole line, with the current token */
  /* at currentOffset */

  /* print error message and current line */
  KDevPG::checkOut << yyTextLine;

  /* print a ^ under the most recent token */
  KDevPG::checkOut << QString(currentOffset, QLatin1Char(' ')).append(QLatin1Char('^')) << Qt::endl; /* currentOffset spaces, then ^ */

  exit(EXIT_FAILURE);
}

int yywrap() { return 1; }

