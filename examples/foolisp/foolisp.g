%token_stream Lexer ;

%token LPAREN, RPAREN, FOO, BAR, BAZ, NUMBER, SHEBANG, STRING, IDENTIFIER ;
%token_stream_bits_header "QDebug"
%parser_bits_header "QDebug"
%input_encoding "utf8"
-- %table_lexer
%input_stream "KDevPG::QByteArrayIterator"

%lexer ->
     
  "("                           LPAREN ;
  ")"                           RPAREN ;
  "foo"                         FOO ;
  "bar"                         BAR ;
  "baz"                         BAZ ;
--   "0"|"1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9" -> digit ; -- Should be predefined with unicode character classes
--   "0" | ( {digit}^"0" ) {digit}*    NUMBER ;
--   [{ASCII}&{LETTER}\-{digit}]+ IDENTIFIER ; -- That's how it shold look like
--   [abc\-][abc\-{digit}]*        IDENTIFIER ; -- That's how it is currently working
  [a-\ee A-Y][a-\ee A-Y]*             IDENTIFIER ;
--   "#!foolisp"                   SHEBANG ;
  [\ \n\t\f]+                   [: /* blank */ :] ;
  \" [.(\\.)^x]* \"            STRING ; ;
--   ;

   ?SHEBANG sexp=sexp -> start ;
  
   LPAREN #sexp=sexp* RPAREN
 | foo=FOO | bar=BAR | baz=BAZ | number=NUMBER | string=STRING | identifier=IDENTIFIER
-> sexp ;

[:
void FooLisp::Parser::expectedSymbol(int /*expectedSymbol*/, const QString& name)
{
  qDebug() << "Expected: " << name;
}
void FooLisp::Parser::expectedToken(int /*expected*/, qint64 /*where*/, const QString& name)
{
  qDebug() << "Expected token: " << name;
}
:]
