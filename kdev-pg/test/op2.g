[:
#include <QString>
#include <kdebug.h>
:]

%parserclass (public declaration)
[:
QString token(int pos = 1);
:]

%parser_bits_header "Op2tokenstream.h"

%parserclass (protected declaration)
[:
void expectedSymbol(Op2::AstNode::AstNodeKind kind, const QString& name);
void expectedToken(int kind, enum TokenType tok, const QString& name);
:]

%parserclass (private declaration)
[:
QHash<QString, uint> pre;
QHash<QString, QPair<bool, uint> > post;
QHash<QString, QPair<bool, uint> > bin;
QHash<QString, QPair<QString, QPair<bool, uint> > > tern;
QHash<QString, QString> paren;
:]

%token BR, PRE, POST, BIN, PAREN, TERN, LEFT, RIGHT, NUMBER, OPERATOR ;;

   (#line=line BR BR*)*
-> document ;;

   ?(PRE [: op1 = token(); :] OPERATOR [: priority = token().toUInt(); :] NUMBER
      [: pre[op1] = priority; :]
 | POST [: op1 = token(); :] OPERATOR [: priority = token().toUInt(); :] NUMBER
      (LEFT [: isLeft = true; :] | RIGHT [: isLeft = false; :] | 0 [: isLeft = true; :] )
      [: post[op1] = qMakePair(isLeft, priority); :]
 | BIN [: op1 = token(); :] OPERATOR [: priority = token().toUInt(); :] NUMBER
      (LEFT [: isLeft = true; :] | RIGHT [: isLeft = false; :] )
      [: bin[op1] = qMakePair(isLeft, priority); :]
 | TERN [: op1 = token(); :] OPERATOR [: op2 = token(); :] OPERATOR [: priority = token().toUInt(); :] NUMBER
      (LEFT [: isLeft = true; :] | RIGHT [: isLeft = false; :] )
      [: tern[op1] = qMakePair(op2, qMakePair(isLeft, priority)); :]
 | PAREN [: op1 = token(); :] OPERATOR [: op2 = token(); :] OPERATOR
      [: paren[op1] = op2; :]
 | expr=expr)
-> line [
  temporary variable isLeft: bool;
  temporary variable priority: uint;
  temporary variable op1: QString;
  temporary variable op2: QString;
] ;;
  
   NUMBER
-> number ;;

%< number
%pre ?[: pre.contains(op = token()) :] OPERATOR %priority[: pre[op] :]
%post ?[: post.contains(op = token()) :] OPERATOR %priority[: post[op].second :] %isLeft[: post[op].first :]
%bin ?[: bin.contains(op = token()) :] OPERATOR %priority[: bin[op].second :] %isLeft[: bin[op].first :]
%tern ?[: tern.contains(op = token()) :] OPERATOR ?[: tern[op].first == token() :] OPERATOR %priority[: tern[op].second.second :] %isLeft[: tern[op].second.first :]
%paren ?[: paren.contains(op = token()) :] OPERATOR ?[: paren[op] == token() :] OPERATOR
%> expr [
  temporary variable op: QString;
];;

[:
#include "Op2tokentext.h"

namespace Op2
{

void Parser::expectedSymbol(Op2::AstNode::AstNodeKind kind, const QString& name) { kDebug() << "In AstNode " << kind << ": Expected symbol " << name << " Token: " << tokenText(yytoken) << "(" << yytoken << ", \"" << "\"). Position: " << tokenStream->index(); abort();  }
void Parser::expectedToken(int kind, enum TokenType tok, const QString& name) { kDebug() << "Read Token: " << tokenText(kind) << "(" << kind << ", \"" << "\"). Expected token " << name << " (" << tok << ")"; abort(); }
QString Parser::token(int pos)
{
  return reinterpret_cast<Op2::TokenStream*>(tokenStream)
    ->tokenString(tokenStream->index() + pos - 2);
}

}
:]
