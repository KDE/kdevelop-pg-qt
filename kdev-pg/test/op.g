[:
#include <QtCore/QString>
#include <kdebug.h>
:]

%parserclass (protected declaration)
[:
void expectedSymbol(Op::AstNode::AstNodeKind kind, const QString& name);
void expectedToken(int kind, enum TokenType tok, const QString& name);
:]

%token PLUS ("+"), MUL ("*"), INV ("-"), NUM ("123"), POW ("^"), BR ("BREAK") ;;

   expr @ BR
-> document ;;

%< number
%bin PLUS 2 %left
%bin MUL 3 %left
%post INV 1
%bin POW 4 %right
%> expr ;;

   NUM
-> number ;;

[:
#include "Optokentext.h"

namespace Op
{

void Parser::expectedSymbol(Op::AstNode::AstNodeKind kind, const QString& name) { kDebug() << "In AstNode " << kind << ": Expected symbol " << name << " Token: " << tokenText(yytoken) << "(" << yytoken << ", \"" << token() << "\"). Position: " << tokenStream->index(); abort();  }
void Parser::expectedToken(int kind, enum TokenType tok, const QString& name) { kDebug() << "Read Token: " << tokenText(kind) << "(" << kind << ", \"" << token() << "\"). Expected token " << name << " (" << tok << ")"; abort(); }

}
:]
