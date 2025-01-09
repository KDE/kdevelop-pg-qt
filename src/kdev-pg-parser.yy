
%{
/*
    SPDX-FileCopyrightText: 2005 Roberto Raggi <roberto@kdevelop.org>
    SPDX-FileCopyrightText: 2006 Jakob Petsovits <jpetso@gmx.at>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "kdev-pg.h"
#include "kdev-pg-clone-tree.h"
#include "kdev-pg-regexp.h"
#include "kdev-pg-unicode-loader.h"
#include "kdev-pg-checker.h"

#include <QFile>
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

KDevPG::Model::OperatorItem *operatorNode = nullptr;
QString r;

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

%token T_IDENTIFIER T_ARROW T_TERMINAL T_CODE T_STRING T_UNQUOTED_STRING T_NUMBER ';'
%token T_TOKEN_DECLARATION T_TOKEN_STREAM_DECLARATION T_NAMESPACE_DECLARATION
%token T_PARSERCLASS_DECLARATION T_LEXERCLASS_DECLARATION
%token T_PUBLIC T_PRIVATE T_PROTECTED T_DECLARATION T_BITS
%token T_CONSTRUCTOR T_DESTRUCTOR T_TRY_RECOVER T_TRY_ROLLBACK T_CATCH
%token T_RULE_ARGUMENTS T_MEMBER T_TEMPORARY T_ARGUMENT T_EXPORT_MACRO
%token T_NODE T_NODE_SEQUENCE T_TOKEN T_VARIABLE T_EXPORT_MACRO_HEADER
%token T_AST_DECLARATION 
%token T_PARSER_DECLARATION_HEADER T_PARSER_BITS_HEADER T_AST_HEADER
%token T_LEXER_DECLARATION_HEADER T_LEXER_BITS_HEADER
%token T_PARSER_BASE T_AST_BASE T_LEXER_BASE
%token T_BIN T_PRE T_POST T_TERN
%token T_LOPR T_ROPR
%token T_LEFT_ASSOC T_RIGHT_ASSOC T_IS_LEFT_ASSOC T_IS_RIGHT_ASSOC T_PRIORITY
%token T_PAREN
%token T_INLINE
%token T_LEXER T_INPUT_STREAM T_INPUT_ENCODING T_TABLE_LEXER T_SEQUENCE_LEXER
%token T_NAMED_REGEXP T_CONTINUE T_RANGE T_FAIL T_LOOKAHEAD T_BARRIER
%token T_ENTER_RULE_SET T_LEAVE_RULE_SET

%type<str> T_IDENTIFIER T_TERMINAL T_CODE T_STRING T_UNQUOTED_STRING T_RULE_ARGUMENTS T_NUMBER T_NAMED_REGEXP T_RANGE
%type<str> name code_opt rule_arguments_opt priority assoc opt_lexer_action
%type<item> item primary_item try_item primary_atom unary_item
%type<item> postfix_item option_item item_sequence conditional_item
%type<item> member_declaration_rest variableDeclarations variableDeclaration operatorRule
%type<declarationType> declarationType_opt
%type<storageType>     scope storageType
%type<variableType>    variableType
/* %type<void> operatorDeclaration operatorDeclarations operatorRule */
%type<operatorInformation> operator
%type<nfa> regexp regexp1 regexp2 regexp3 regexp4 regexp5 regexp6 regexp7 aregexp aregexp1 aregexp2 aregexp3 aregexp4 aregexp5 aregexp6 aregexp7

%%

system
    : code_opt { KDevPG::globalSystem.decl = QString::fromUtf8($1); }
      declarations
      rules
      code_opt { KDevPG::globalSystem.bits += QString::fromUtf8($5); }
    ;

declarations
    : declaration
    | declarations declaration
    ;

declaration
    : T_PARSERCLASS_DECLARATION member_declaration_rest
        { KDevPG::globalSystem.pushParserClassMember($2); }
    | T_PARSERCLASS_DECLARATION '(' T_BITS ')' T_CODE
        { KDevPG::globalSystem.bits += QString::fromUtf8($5); }
    | T_LEXERCLASS_DECLARATION member_declaration_rest
        { KDevPG::globalSystem.pushLexerClassMember($2); }
    | T_LEXERCLASS_DECLARATION '(' T_BITS ')' T_CODE
        { KDevPG::globalSystem.lexerBits += QString::fromUtf8($5); }
    | T_TOKEN_DECLARATION declared_tokens ';'
    | T_TABLE_LEXER
      { if(KDevPG::globalSystem.hasLexer)
        { KDevPG::checkOut << "** ERROR you have to specify the lexer-type (%table_lexer) before any lexer rules"; exit(-1); }
        switch(KDevPG::GDFA::type)
        {
          case KDevPG::SAscii: KDevPG::GDFA::type = KDevPG::TAscii; break;
          case KDevPG::SLatin1: KDevPG::GDFA::type = KDevPG::TLatin1; break;
          case KDevPG::SUtf8: KDevPG::GDFA::type = KDevPG::TUtf8; break;
          case KDevPG::SUcs2: KDevPG::GDFA::type = KDevPG::TUcs2; break;
          case KDevPG::SUtf16: KDevPG::GDFA::type = KDevPG::TUtf16; break;
/*           case KDevPG::SUcs4: KDevPG::GDFA::type = KDevPG::TUcs4; break; */
          default: /* empty */;
        }
      }
    | T_SEQUENCE_LEXER
      { if(KDevPG::globalSystem.hasLexer)
      { KDevPG::checkOut << "** ERROR you have to specify the lexer-type (%sequence_lexer) before any lexer rules"; exit(-1); }
      switch(KDevPG::GDFA::type)
      {
        case KDevPG::TAscii: KDevPG::GDFA::type = KDevPG::SAscii; break;
        case KDevPG::TLatin1: KDevPG::GDFA::type = KDevPG::SLatin1; break;
        case KDevPG::TUtf8: KDevPG::GDFA::type = KDevPG::SUtf8; break;
        case KDevPG::TUcs2: KDevPG::GDFA::type = KDevPG::SUcs2; break;
        case KDevPG::TUtf16: KDevPG::GDFA::type = KDevPG::SUtf16; break;
/*         case KDevPG::TUcs4: KDevPG::GDFA::type = KDevPG::SUcs4; break; */
        default: /* empty */;
      }
      }
    | T_INPUT_ENCODING T_STRING
      {
        if(KDevPG::globalSystem.hasLexer)
        { KDevPG::checkOut << "** ERROR you have to specify the lexer-type (%sequence_lexer) before any lexer rules"; exit(-1); }
        int base = (KDevPG::GDFA::type / 4) * 4; // warning: magic constant: number of different codecs
        QString str = QString::fromUtf8($2);
        str = str.toLower();
        str.remove(QLatin1Char('-'));
        if(str == QLatin1String("ascii"))
          /* base += 0*/;
        else if(str == QLatin1String("latin1"))
          base += 1;
        else if(str == QLatin1String("utf8"))
          base += 2;
        else if(str == QLatin1String("ucs2"))
          base += 3;
        else if(str == QLatin1String("utf16"))
          base += 4;
        else if(str == QLatin1String("ucs4") || str == QLatin1String("utf32"))
          base += 5;
        else
        {
          KDevPG::checkOut << "** ERROR unknown codec  ``" << $2 << "''" << Qt::endl;
          exit(-1);
        }
        KDevPG::GDFA::type = KDevPG::AutomatonType(base);
      }
    | T_TOKEN_STREAM_DECLARATION T_IDENTIFIER ';'
        { KDevPG::globalSystem.tokenStream = QString::fromUtf8($2);           }
    | T_EXPORT_MACRO T_STRING
        { KDevPG::globalSystem.exportMacro = QString::fromUtf8($2);           }
    | T_EXPORT_MACRO_HEADER T_STRING
        { KDevPG::globalSystem.exportMacroHeader = QString::fromUtf8($2);     }
    | T_NAMESPACE_DECLARATION T_CODE
        { KDevPG::globalSystem.namespaceCode = QString::fromUtf8($2);         }
    | T_AST_DECLARATION T_CODE
        { KDevPG::globalSystem.astCode = QString::fromUtf8($2);               }
    | T_PARSER_DECLARATION_HEADER T_STRING
        { KDevPG::globalSystem.pushParserDeclarationHeader(QString::fromUtf8($2)); }
    | T_PARSER_BITS_HEADER T_STRING
        { KDevPG::globalSystem.pushParserBitsHeader(QString::fromUtf8($2)); }
    | T_AST_HEADER T_STRING
        { KDevPG::globalSystem.pushAstHeader(QString::fromUtf8($2)); }
    | T_LEXER_DECLARATION_HEADER T_STRING
        { KDevPG::globalSystem.pushLexerDeclarationHeader(QString::fromUtf8($2)); }
    | T_INPUT_STREAM T_STRING
        { KDevPG::globalSystem.inputStream = QString::fromUtf8($2); }
    | T_LEXER_BITS_HEADER T_STRING
        { KDevPG::globalSystem.pushLexerBitsHeader(QString::fromUtf8($2)); }
    | T_AST_BASE T_IDENTIFIER T_STRING
        { KDevPG::globalSystem.astBaseClasses[QString::fromUtf8($2)] = QString::fromUtf8($3); }
    | T_PARSER_BASE T_STRING
        { KDevPG::globalSystem.parserBaseClass = QString::fromUtf8($2); }
    | T_LEXER_BASE T_STRING
        { KDevPG::globalSystem.lexerBaseClass = QString::fromUtf8($2); }
    | T_LEXER T_STRING { KDevPG::globalSystem.hasLexer = true; lexerEnv = QString::fromUtf8($2); if(KDevPG::globalSystem.lexerActions[lexerEnv].empty()) KDevPG::globalSystem.lexerActions[lexerEnv].push_back(QStringLiteral("qDebug() << \"error\"; exit(-1);")); } T_ARROW lexer_declaration_rest ';'
    | T_LEXER { KDevPG::globalSystem.hasLexer = true; KDevPG::loadUnicodeData(); lexerEnv = QStringLiteral("start"); if(KDevPG::globalSystem.lexerActions[QStringLiteral("start")].empty()) KDevPG::globalSystem.lexerActions[QStringLiteral("start")].push_back(QStringLiteral("qDebug() << \"error\"; exit(-1);")); } T_ARROW lexer_declaration_rest ';'
    ;

lexer_declaration_rest
    : regexp T_ARROW T_IDENTIFIER ';'
            { KDevPG::globalSystem.regexpById[QString::fromUtf8($3)] = $1;
            } lexer_declaration_rest
    | regexp code_opt opt_lexer_action ';'
            {
              if($1->acceptsEpsilon())
                KDevPG::checkOut << "** WARNING Lexer rule accepting the empty word at line " << yyLine << Qt::endl;
              else if($1->isEmpty())
                KDevPG::checkOut << "** WARNING Lexer rule not accepting anything at line " << yyLine << Qt::endl;
              QString s = QString::fromUtf8($2) + r;
              KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back($1);
              KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
            } lexer_declaration_rest
    | regexp T_LOOKAHEAD '(' regexp ')' code_opt opt_lexer_action ';'
            {
              if($1->acceptsEpsilon())
                KDevPG::checkOut << "** WARNING Lexer rule accepting the empty word at line " << yyLine << Qt::endl;
              else if($1->isEmpty())
                KDevPG::checkOut << "** WARNING Lexer rule not accepting anything at line " << yyLine << Qt::endl;
              bool ignore = false;
              auto minLen = $4->minLength(), maxLen = $4->maxLength();
              if(minLen == 0)
              {
                KDevPG::checkOut << "** WARNING Lexer rule specifying epsilon-lookahead at line " << yyLine << ", ignore the lookahead." << Qt::endl;
                ignore = true;
              }
              else if(minLen != maxLen)
              {
                KDevPG::checkOut << "** WARNING Invalid lookahead (no fixed length) at line " << yyLine << " (min length: " << (minLen == -1 ? QStringLiteral("none") : QString::number(minLen)) << ", max length: " << (maxLen == -2 ? QStringLiteral("infinity") : (maxLen == -1 ? QStringLiteral("none") : QString::number(maxLen))) << "), ignore the lookahead." << Qt::endl;
                ignore = true;
              }
              if(ignore)
              {
                QString s = QString::fromUtf8($6) + r;
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back($1);
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
              else
              {
                QString s = QLatin1String("Iterator::plain() -= ") + QString::number(minLen) + QLatin1String("; ") + QString::fromUtf8($6) + r;
                *$1 <<= *$4;
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back($1);
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
            } lexer_declaration_rest
    | regexp T_BARRIER '(' regexp ')' code_opt opt_lexer_action ';'
            {
              if($1->acceptsEpsilon())
                KDevPG::checkOut << "** WARNING Lexer rule accepting the empty word at line " << yyLine << Qt::endl;
              else if($1->isEmpty())
                KDevPG::checkOut << "** WARNING Lexer rule not accepting anything at line " << yyLine << Qt::endl;
              bool ignore = false;
              auto minLen = $4->minLength(), maxLen = $4->maxLength();
              if(minLen == 0)
              {
                KDevPG::checkOut << "** WARNING Lexer rule specifying epsilon-barrier at line " << yyLine << ", ignore the barrier." << Qt::endl;
                ignore = true;
              }
              else if(minLen != maxLen)
              {
                KDevPG::checkOut << "** WARNING Invalid barrier (no fixed length) at line " << yyLine << " (min length: " << (minLen == -1 ? QStringLiteral("none") : QString::number(minLen)) << ", max length: " << (maxLen == -2 ? QStringLiteral("infinity") : (maxLen == -1 ? QStringLiteral("none") : QString::number(maxLen))) << "), ignore the barrier." << Qt::endl;
                ignore = true;
              }
              if(ignore)
              {
                QString s = QString::fromUtf8($6) + r;
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back($1);
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
              else
              {
                KDevPG::GNFA exclude = KDevPG::GNFA::anything();
                exclude <<= *$4;
                exclude <<= KDevPG::GNFA::anything();
                KDevPG::GNFA *staying = new KDevPG::GNFA(*$1);
                *staying ^= exclude;
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back(staying);
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(QString::fromUtf8($6) + r);
                // barrier should not get read partially
                exclude <<= KDevPG::GNFA::anyChar();
                *$1 <<= *$4;
                *$1 ^= exclude;
                QString s = QLatin1String("Iterator::plain() -= ") + QString::number(minLen) + QLatin1String("; ") + QString::fromUtf8($6) + r;
                KDevPG::globalSystem.lexerEnvs[lexerEnv].push_back($1);
                KDevPG::globalSystem.lexerActions[lexerEnv].push_back(s);
              }
            } lexer_declaration_rest
    | T_FAIL T_CODE
            {
              KDevPG::globalSystem.lexerActions[lexerEnv][0] = QString::fromUtf8($2);
            } lexer_declaration_rest
    | T_ENTER_RULE_SET T_CODE
            {
              KDevPG::globalSystem.enteringCode[lexerEnv] = QString::fromUtf8($2);
            } lexer_declaration_rest
    | T_LEAVE_RULE_SET T_CODE
            {
              KDevPG::globalSystem.leavingCode[lexerEnv] = QString::fromUtf8($2);
            } lexer_declaration_rest
    | /* empty */
    ;

opt_lexer_action
    : T_TERMINAL {
        r = QLatin1String("\nlxRETURN(") + QString::fromUtf8($1) + QLatin1String(")\n");
      }
    | T_CONTINUE {
        r = QStringLiteral("\nlxCONTINUE;\n");
      }
    | /* empty */ { r = QStringLiteral("\nlxSKIP\n"); }
    ;

regexp
    : regexp '|' regexp1    { $$ = new KDevPG::GNFA(*$1 |= *$3); delete $1; delete $3; }
    | regexp1               { $$ = $1; }
    ;

regexp1
    : regexp1 '&' regexp2   { $$ = new KDevPG::GNFA(*$1 &= *$3); delete $1; delete $3; }
    | regexp2               { $$ = $1; }
    ;

regexp2
    : regexp3 '^' regexp2   { $$ = new KDevPG::GNFA(*$1 ^= *$3); delete $1; delete $3; }
    | regexp3               { $$ = $1; }
    ;

regexp3
    : '~' regexp3           { $$ = new KDevPG::GNFA($2->negate()); delete $2; }
    | '?' regexp3           { $$ = new KDevPG::GNFA(*$2 |= KDevPG::GNFA::emptyWord()); delete $2; }
    | regexp4               { $$ = $1; }
    ;

regexp4
    : regexp4 regexp5       { $$ = new KDevPG::GNFA(*$1 <<= *$2); delete $1; delete $2; }
    | regexp5               { $$ = $1; }
    ;

regexp5
    : regexp5 '@' regexp6   { $$ = new KDevPG::GNFA(*$1); KDevPG::GNFA *tmp = new KDevPG::GNFA(*$3 <<= *$1); **tmp; *$$ <<= *tmp; delete tmp; delete $1; delete $3; }
    | regexp6               { $$ = $1; }
    ;
    
regexp6
    : regexp6 '*'           { $$ = new KDevPG::GNFA(**$1); delete $1; }
    | regexp6 '+'           { $$ = new KDevPG::GNFA(*$1); **$$; *$$ <<= *$1; delete $1; }
    | regexp7               { $$ = $1; }
    ;

regexp7
    : '(' regexp ')'        { $$ = new KDevPG::GNFA(*$2); delete $2; }
    | '[' aregexp ']'       { $$ = $2; }
    | '.'                   { $$ = new KDevPG::GNFA(KDevPG::GNFA::anyChar()); }
    | T_STRING              { $$ = new KDevPG::GNFA(KDevPG::GNFA::word(KDevPG::unescaped(QByteArray($1)))); }
    | T_UNQUOTED_STRING     { $$ = new KDevPG::GNFA(KDevPG::GNFA::word(KDevPG::unescaped(QByteArray($1)))); }
    | T_NAMED_REGEXP        {
                              if(!KDevPG::globalSystem.regexpById.contains(QString::fromUtf8($1)))
                              {
                                KDevPG::checkOut << "** ERROR: no named regexp " << $1 << Qt::endl;
                                exit(-1);
                              }
                              KDevPG::GNFA *regexp = KDevPG::globalSystem.regexpById[QString::fromUtf8($1)];
                              if(!KDevPG::globalSystem.dfaForNfa.contains(regexp))
                              {
                                KDevPG::globalSystem.dfaForNfa[regexp] = new KDevPG::GDFA(regexp->dfa());
                                KDevPG::globalSystem.dfaForNfa[regexp]->minimize();
                                *regexp = KDevPG::globalSystem.dfaForNfa[regexp]->nfa();
                              }
                              $$ = new KDevPG::GNFA(*regexp);
                            }
    | /* empty */           { $$ = new KDevPG::GNFA(KDevPG::GNFA::emptyWord()); }
    ;

aregexp
    : aregexp '|' aregexp1  { $$ = new KDevPG::GNFA(*$1 |= *$3); delete $1; delete $3; }
    | aregexp1              { $$ = $1; }
    ;

aregexp1
    : aregexp1 '&' aregexp2 { $$ = new KDevPG::GNFA(*$1 &= *$3); delete $1; delete $3; }
    | aregexp2              { $$ = $1; }
    ;

aregexp2
    : aregexp3 '^' aregexp2 { $$ = new KDevPG::GNFA(*$1 ^= *$3); delete $1; delete $3; }
    | aregexp3              { $$ = $1; }
    ;

aregexp3
    : '~' aregexp3          { $$ = new KDevPG::GNFA($2->negate()); delete $2; }
    | '?' aregexp3          { $$ = new KDevPG::GNFA(*$2 |= KDevPG::GNFA::emptyWord()); delete $2; }
    | aregexp4              { $$ = $1; }
    ;

aregexp4
    : aregexp4 aregexp5     { $$ = new KDevPG::GNFA(*$1 |= *$2); delete $1; delete $2; }
    | aregexp5
    ;

aregexp5
    : aregexp5 '@' aregexp6 { $$ = new KDevPG::GNFA(*$1); KDevPG::GNFA *tmp = new KDevPG::GNFA(*$3 <<= *$1); **tmp; *$$ <<= *tmp; delete tmp; delete $1; delete $3; }
    | aregexp6              { $$ = $1; }
    ;
    
aregexp6
    : aregexp6 '*'          { $$ = new KDevPG::GNFA(**$1); delete $1; }
    | aregexp6 '+'          { $$ = new KDevPG::GNFA(*$1); **$$; *$$ <<= *$1; delete $1; }
    | aregexp7              { $$ = $1; }
    ;

aregexp7
    : '(' regexp ')'        { $$ = new KDevPG::GNFA(*$2); delete $2; }
    | '[' aregexp ']'       { $$ = $2; }
    | '.'                   { $$ = new KDevPG::GNFA(KDevPG::GNFA::anyChar()); }
    | T_STRING              { $$ = new KDevPG::GNFA(KDevPG::GNFA::word(KDevPG::unescaped(QByteArray($1)))); }
    | T_RANGE               {
      quint32 begin, end;
      QString str = KDevPG::unescaped(QByteArray($1));
      assert(str.size() >= 3 && str.size() <= 5);
      if(str[1] == QLatin1Char('-'))
      {
        begin = str[0].unicode();
        if(str.size() == 3)
          end = str[2].unicode();
        else
          end = QChar::surrogateToUcs4(str[2], str[3]);
      }
      else
      {
        begin = QChar::surrogateToUcs4(str[0], str[1]);
        assert(str[2] == QLatin1Char('-'));
        if(str.size() == 4)
          end = str[3].unicode();
        else
          end = QChar::surrogateToUcs4(str[3], str[4]);
      }
      $$ = new KDevPG::GNFA(KDevPG::GNFA::range(begin, end+1));
    }
    | T_UNQUOTED_STRING     { $$ = new KDevPG::GNFA(KDevPG::GNFA::collection(KDevPG::unescaped(QByteArray($1)))); }
    | T_NAMED_REGEXP        {
                              if(!KDevPG::globalSystem.regexpById.contains(QString::fromUtf8($1)))
                              {
                                KDevPG::checkOut << "** ERROR: no named regexp " << $1 << Qt::endl;
                                exit(-1);
                              }
                              KDevPG::GNFA *regexp = KDevPG::globalSystem.regexpById[QString::fromUtf8($1)];
                              if(!KDevPG::globalSystem.dfaForNfa.contains(regexp))
                              {
                                KDevPG::globalSystem.dfaForNfa[regexp] = new KDevPG::GDFA(regexp->dfa());
                                KDevPG::globalSystem.dfaForNfa[regexp]->minimize();
                                *regexp = KDevPG::globalSystem.dfaForNfa[regexp]->nfa();
                              }
                              $$ = new KDevPG::GNFA(*regexp);
                            }
    | /* empty */           { $$ = new KDevPG::GNFA(KDevPG::GNFA::emptyWord()); }
    ;


member_declaration_rest
    : '(' T_PUBLIC T_DECLARATION ')' T_CODE
        { $$ = KDevPG::member(KDevPG::Settings::MemberItem::PublicDeclaration, QString::fromUtf8($5));    }
    | '(' T_PROTECTED T_DECLARATION ')' T_CODE
        { $$ = KDevPG::member(KDevPG::Settings::MemberItem::ProtectedDeclaration, QString::fromUtf8($5)); }
    | '(' T_PRIVATE T_DECLARATION ')' T_CODE
        { $$ = KDevPG::member(KDevPG::Settings::MemberItem::PrivateDeclaration, QString::fromUtf8($5));   }
    | '(' T_CONSTRUCTOR ')' T_CODE
        { $$ = KDevPG::member(KDevPG::Settings::MemberItem::ConstructorCode, QString::fromUtf8($4));      }
    | '(' T_DESTRUCTOR ')' T_CODE
        { $$ = KDevPG::member(KDevPG::Settings::MemberItem::DestructorCode, QString::fromUtf8($4));       }
    ;

declared_tokens
    : T_TERMINAL                        { KDevPG::globalSystem.pushTerminal(QString::fromUtf8($1), QString::fromUtf8($1)); }
    | T_TERMINAL '(' T_STRING ')'       { KDevPG::globalSystem.pushTerminal(QString::fromUtf8($1), QString::fromUtf8($3)); }
    | declared_tokens ',' T_TERMINAL    { KDevPG::globalSystem.pushTerminal(QString::fromUtf8($3), QString::fromUtf8($3)); }
    | declared_tokens ',' T_TERMINAL '(' T_STRING ')'
                                        { KDevPG::globalSystem.pushTerminal(QString::fromUtf8($3), QString::fromUtf8($5)); }
    ;

rules
    : /* empty */
    | rules item ';'                    { KDevPG::globalSystem.pushRule($2); }
    ;

primary_item
    : '0'                               { $$ = KDevPG::globalSystem.zero(); }
    | '(' option_item ')'               { $$ = $2; }
    | try_item                          { $$ = $1; }
    | primary_atom                      { $$ = $1; }
    | T_INLINE T_IDENTIFIER             { $$ = KDevPG::inlinedNonTerminal(KDevPG::globalSystem.pushSymbol(QString::fromUtf8($2))); }
    | name scope primary_atom           { $$ = KDevPG::annotation(QString::fromUtf8($1), $3, false, $2); }
    | '#' name scope primary_atom       { $$ = KDevPG::annotation(QString::fromUtf8($2), $4, true, $3);  }
    ;

primary_atom
    : T_IDENTIFIER rule_arguments_opt   { $$ = KDevPG::nonTerminal(KDevPG::globalSystem.pushSymbol(QString::fromUtf8($1)), QString::fromUtf8($2)); }
    | T_TERMINAL                        { $$ = KDevPG::globalSystem.terminal(QString::fromUtf8($1)); }
    ;

try_item
    : T_TRY_RECOVER '(' option_item ')'
        {
          KDevPG::globalSystem.needStateManagement = true;
          $$ = KDevPG::tryCatch($3, nullptr);
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
    | '?' primary_item                  { $$ = KDevPG::alternative($2, KDevPG::globalSystem.zero()); }
    ;

postfix_item
    : unary_item                        { $$ = $1; }
    | postfix_item '@' primary_item
        {
          KDevPG::CloneTree cl;
          $$ = KDevPG::cons($1, KDevPG::star(KDevPG::cons(cl.clone($3), cl.clone($1))));
        }
    | postfix_item T_CODE               { $$ = KDevPG::action($1, QString::fromUtf8($2)); }
    | T_CODE                            { $$ = KDevPG::action(nullptr, QString::fromUtf8($1)); }
    ;

item_sequence
    : postfix_item                      { $$ = $1; }
    | item_sequence postfix_item        { $$ = KDevPG::cons($1, $2); }
    ;

conditional_item
    : item_sequence                     { $$ = $1; }
    | '?' T_CODE item_sequence          { $$ = KDevPG::condition(QString::fromUtf8($2), $3); }
    ;

option_item
    : conditional_item                  { $$ = $1; }
    | option_item '|' conditional_item  { $$ = KDevPG::alternative($1, $3); }
    ;

item
    : option_item T_ARROW T_IDENTIFIER T_CODE '[' variableDeclarations ']'
        {
          $$ = KDevPG::evolve($1, KDevPG::globalSystem.pushSymbol(QString::fromUtf8($3)),
                          (KDevPG::Model::VariableDeclarationItem*) $6, QString::fromUtf8($4));
        }
    | option_item T_ARROW T_IDENTIFIER '[' variableDeclarations ']' code_opt
        {
          $$ = KDevPG::evolve($1, KDevPG::globalSystem.pushSymbol(QString::fromUtf8($3)),
                          (KDevPG::Model::VariableDeclarationItem*) $5, QString::fromUtf8($7));
        }
    | option_item T_ARROW T_IDENTIFIER code_opt
        { $$ = KDevPG::evolve($1, KDevPG::globalSystem.pushSymbol(QString::fromUtf8($3)), nullptr, QString::fromUtf8($4)); }
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
              operatorNode->mName = QString::fromUtf8($5);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + QLatin1String("Ast");
              $$ = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol(QString::fromUtf8($5)), (KDevPG::Model::VariableDeclarationItem*)$7, QString::fromUtf8($9));
            }
    | T_LOPR primary_atom operatorDeclarations T_ROPR T_IDENTIFIER T_CODE '[' variableDeclarations ']'
            {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)$2;
              operatorNode->mName = QString::fromUtf8($5);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + QLatin1String("Ast");
              $$ = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol(QString::fromUtf8($5)), (KDevPG::Model::VariableDeclarationItem*)$8, QString::fromUtf8($6));
            }
    | T_LOPR primary_atom operatorDeclarations T_ROPR T_IDENTIFIER code_opt
            {
              operatorNode->mBase = (KDevPG::Model::NonTerminalItem*)$2;
              operatorNode->mName = QString::fromUtf8($5);
              if(!KDevPG::globalSystem.astBaseClasses.contains(operatorNode->mBase->mSymbol->mName))
                KDevPG::globalSystem.astBaseClasses[operatorNode->mBase->mSymbol->mName] = KDevPG::capitalized(operatorNode->mName) + QLatin1String("Ast");
              $$ = KDevPG::evolve(operatorNode, KDevPG::globalSystem.pushSymbol(QString::fromUtf8($5)), nullptr, QString::fromUtf8($6));
            }
    ;

operatorDeclaration
    : T_BIN operator priority assoc              { operatorNode->pushBin(*$2, QString::fromUtf8($4), QString::fromUtf8($3)); free($2); }
    | T_TERN operator operator priority assoc    { operatorNode->pushTern(*$2, *$3, QString::fromUtf8($5), QString::fromUtf8($4)); free($2); free($3); }
    | T_PRE operator priority                    { operatorNode->pushPre(*$2, QString::fromUtf8($3)); free($2); }
    | T_POST operator priority                   { operatorNode->pushPost(*$2, QStringLiteral("0"), QString::fromUtf8($3)); free($2); free($3); }
    | T_POST operator priority assoc             { operatorNode->pushPost(*$2, QString::fromUtf8($4), QString::fromUtf8($3)); free($2); }
    | T_PAREN operator operator                  { operatorNode->pushParen(*$2, *$3); free($2); free($3); }
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
    : '?' T_CODE T_TERMINAL T_CODE { $$ = KDevPG::makeOperator(KDevPG::globalSystem.terminal(QString::fromUtf8($3)), QString::fromUtf8($2), QString::fromUtf8($4)); }
    | '?' T_CODE T_TERMINAL        { $$ = KDevPG::makeOperator(KDevPG::globalSystem.terminal(QString::fromUtf8($3)), QString::fromUtf8($2), QString()); }
    | T_TERMINAL T_CODE            { $$ = KDevPG::makeOperator(KDevPG::globalSystem.terminal(QString::fromUtf8($1)), QString(), QString::fromUtf8($2)); }
    | T_TERMINAL                   { $$ = KDevPG::makeOperator(KDevPG::globalSystem.terminal(QString::fromUtf8($1)), QString(), QString()); }
    ;

variableDeclarations
    : variableDeclaration              { $$ = $1; }
    | variableDeclarations variableDeclaration
        {
          KDevPG::Model::VariableDeclarationItem *last = (KDevPG::Model::VariableDeclarationItem*) $1;
          while (last->mNext != nullptr) {
            last = last->mNext;
          }
          last->mNext = (KDevPG::Model::VariableDeclarationItem*) $2;
          $$ = $1;
        }
    ;

variableDeclaration
    : declarationType_opt storageType variableType T_IDENTIFIER ':' T_IDENTIFIER
        { $$ = KDevPG::variableDeclaration($1, $2, $3, false, QString::fromUtf8($4), QString::fromUtf8($6)); }
    | declarationType_opt storageType T_TOKEN       T_IDENTIFIER ';'
        { $$ = KDevPG::variableDeclaration($1, $2, KDevPG::Model::VariableDeclarationItem::TypeToken, false, QString::fromUtf8($4), QString()); }
    | declarationType_opt storageType variableType '#' T_IDENTIFIER ':' T_IDENTIFIER
        { $$ = KDevPG::variableDeclaration($1, $2, $3, true, QString::fromUtf8($5), QString::fromUtf8($7)); }
    | declarationType_opt storageType T_TOKEN       '#' T_IDENTIFIER ';'
        { $$ = KDevPG::variableDeclaration($1, $2, KDevPG::Model::VariableDeclarationItem::TypeToken, true, QString::fromUtf8($5), QString()); }
    ;

declarationType_opt
    : /* empty */       { $$ = KDevPG::Model::VariableDeclarationItem::DeclarationLocal;     }
    | T_ARGUMENT        { $$ = KDevPG::Model::VariableDeclarationItem::DeclarationArgument;  }
    ;

storageType
    : T_MEMBER          { $$ = KDevPG::Model::VariableDeclarationItem::StorageAstMember;     }
    | T_TEMPORARY       { $$ = KDevPG::Model::VariableDeclarationItem::StorageTemporary;     }
    ;

variableType
    : T_NODE            { $$ = KDevPG::Model::VariableDeclarationItem::TypeNode;             }
    | T_VARIABLE        { $$ = KDevPG::Model::VariableDeclarationItem::TypeVariable;         }
    ;

%%
