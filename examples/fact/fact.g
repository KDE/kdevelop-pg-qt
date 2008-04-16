-----------------------------------------------------------
-- Global  declarations
-----------------------------------------------------------


[:

#include <QtCore/QString>

namespace fact
{
    class Lexer;
}

:]

------------------------------------------------------------
-- Parser class members
------------------------------------------------------------

%parserclass (public declaration)
[:
  /**
   * Transform the raw input into tokens.
   * When this method returns, the parser's token stream has been filled
   * and any parse_*() method can be called.
   */
  void tokenize( const QString& contents );

    enum ProblemType {
        Error,
        Warning,
        Info
    };
    void reportProblem( Parser::ProblemType type, const QString& message );

    QString tokenText(qint64 begin, qint64 end) const;

    void setDebug( bool debug );

:]

%parserclass (private declaration)
[:
    QString m_contents;
    bool m_debug;
:]

------------------------------------------------------------
-- List of defined tokens
------------------------------------------------------------

%token FUNCTION ("function"), VAR ("var"), IF ("if"), ELSE ("else"),
       RETURN ("return") ;;

%token LPAREN ("("), RPAREN (")"), LBRACE ("{"), RBRACE ("}"),
       COMMA (","), SEMICOLON (";") ;;

%token ASSIGN ("="), EQUAL ("=="), STAR ("*"), MINUS ("-") ;;

%token IDENTIFIER ("identifier"), NUMBER ("integer literal") ;;

%token INVALID ("invalid token") ;;



------------------------------------------------------------
-- Start of the actual grammar
------------------------------------------------------------

-- Declaration rules
----------------------

   (#fun=functionDefinition)*
-> program ;;

   FUNCTION id=IDENTIFIER
   LPAREN (#param=IDENTIFIER @ COMMA | 0) RPAREN body=body
-> functionDefinition ;;

   LBRACE (#decl=declaration)* (#stmt=statement)* RBRACE
-> body ;;

   VAR (var=variable @ COMMA) SEMICOLON
-> declaration ;;

   id=IDENTIFIER
-> variable ;;


-- Statement rules
--------------------

   id=IDENTIFIER ASSIGN expr=expression SEMICOLON
-> assignmentStatement ;;

   IF LPAREN cond=condition RPAREN ifStmt=statement
   (ELSE elseStmt=statement | 0)
-> ifStatement ;;

   LBRACE (#stmt=statement)* RBRACE
-> blockStatement ;;

   RETURN expr=expression SEMICOLON
-> returnStatement ;;

   assignStmt=assignmentStatement
 | ifStmt=ifStatement
 | blockStmt=blockStatement
 | returnStmt=returnStatement
-> statement ;;


-- Expression rules
--------------------

   num=NUMBER
 | id=IDENTIFIER (LPAREN (#argument=expression @ COMMA) RPAREN | 0)
-> primary ;;

   leftExpr=primary (STAR rightExpr=primary)*
-> multExpression ;;

   leftExpr=multExpression (MINUS rightExpr=multExpression)*
-> expression ;;

   leftExpr=expression EQUAL rightExpr=expression
-> condition ;;




-----------------------------------------------------------------
-- Code segments copied to the implementation (.cpp) file.
-- If existent, kdevelop-pg's current syntax requires this block
-- to occur at the end of the file.
-----------------------------------------------------------------

[:
#include "factlexer.h"
#include <QtCore/QString>
#include <QDebug>

namespace fact
{

void Parser::tokenize( const QString& contents )
{
    m_contents = contents;
    Lexer lexer( this, contents );

    int kind = Parser::Token_EOF;
    do
    {
        kind = lexer.nextTokenKind();

        if ( !kind ) // when the lexer returns 0, the end of file is reached
            kind = Parser::Token_EOF;

        Parser::Token &t = tokenStream->next();
        t.kind = kind;
        if( t.kind == Parser::Token_EOF )
        {
            t.begin = -1;
            t.end = -1;
        }
        else
        {
            t.begin = lexer.tokenBegin();
            t.end = lexer.tokenEnd();
        }

        if( m_debug )
        {
            qDebug() << kind << "(" << t.begin << "," << t.end << ")::" << tokenText(t.begin, t.end);
        }

    }
    while ( kind != Parser::Token_EOF );

    this->yylex(); // produce the look ahead token
}

QString Parser::tokenText( qint64 begin, qint64 end ) const
{
    return m_contents.mid((int)begin, (int)end-begin+1);
}

void Parser::reportProblem( Parser::ProblemType type, const QString& message )
{
    if (type == Error)
        qDebug() << "** ERROR:" << message;
    else if (type == Warning)
        qDebug() << "** WARNING:" << message;
    else if (type == Info)
        qDebug() << "** Info:" << message;
}

// custom error recovery
void Parser::expectedToken(int /*expected*/, qint64 /*where*/, const QString& name)
{
    reportProblem(
        Parser::Error,
        QString("Expected token \"%1\"").arg(name));
}

void Parser::expectedSymbol(int /*expected_symbol*/, const QString& name)
{
    qint64 line;
    qint64 col;
    size_t index = tokenStream->index()-1;
    Token &token = tokenStream->token(index);
    qDebug() << "token starts at:" << token.begin;
    qDebug() << "index is:" << index;
    tokenStream->startPosition(index, &line, &col);
    QString tokenValue = tokenText(token.begin, token.end);
    reportProblem(
        Parser::Error,
        QString("Expected symbol \"%1\" (current token: \"%2\" [%3] at line: %4 col: %5)")
            .arg(name)
            .arg(token.kind != 0 ? tokenValue : "EOF")
            .arg(token.kind)
            .arg(line)
            .arg(col));
}

void Parser::setDebug( bool debug )
{
    m_debug = debug;
}

} // end of namespace fact

:]

-- kate: space-indent on; indent-width 4; tab-width 4; replace-tabs on
