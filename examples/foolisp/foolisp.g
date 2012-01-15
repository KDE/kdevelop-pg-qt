%token_stream Lexer ;

%token LPAREN, RPAREN, FOO, BAR, BAZ, NUMBER, SHEBANG, STRING, IDENTIFIER ;
%lexer_bits_header "QDebug"
%parser_bits_header "QDebug"
%input_encoding "utf32"
-- %table_lexer
%input_stream "KDevPG::QUtf8ToUcs4Iterator"

%lexer ->
     
  "("                           LPAREN ;
  ")"                           RPAREN ;
  foo                           FOO ;
  bar                           BAR ;
  baz                           BAZ ;
  qux                           FOO ;
  quux                          BAR ;
  corge                         BAZ ;
  grault                        FOO ;
  garply                        BAR ;
  waldo                         BAZ ;
  fred                          FOO ;
  plugh                         BAR ;
  xyzzy                         BAZ ;
  thud                          FOO ;
  FOOBAR                        FOO ;

--   "0"|"1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9" -> digit ; -- Should be predefined with unicode character classes
  "0" | ( {digit}&{basic_latin}^"0" ) {digit}*    NUMBER ;

(([({alphabetic}&{basic_latin}){greek_and_coptic}]^[a-z \x3b1-\x3b3])&{basic_latin})+        IDENTIFIER ; -- kinda exotic limitations for identifiers ;)


  "#!foolisp"                   SHEBANG ;
  [\ \n\t]+                     [: /* blank */ :] ;
  \" [.(\\.)^\"]* \"             STRING ;
  ;

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
