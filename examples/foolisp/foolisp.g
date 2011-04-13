%token_stream Lexer ;

%token LPAREN, RPAREN, FOO, BAR, BAZ, NUMBER, SHEBANG, STRING, IDENTIFIER ;
%token_stream_bits_header "QDebug"
%parser_bits_header "QDebug"
%input_encoding "ascii"
-- %table_lexer
%input_stream "KDevPG::QUtf8ToUcs4Iterator"

%lexer ->
     
  "("                           LPAREN ;
  ")"                           RPAREN ;
--   foo                           FOO ;
--   bar                           BAR ;
--   baz                           BAZ ;
--   qux                           FOO ;
--   quux                          BAR ;
--   corge                         BAZ ;
--   grault                        FOO ;
--   garply                        BAR ;
--   waldo                         BAZ ;
--   fred                          FOO ;
--   plugh                         BAR ;
--   xyzzy                         BAZ ;
--   thud                          FOO ;

--   "0"|"1"|"2"|"3"|"4"|"5"|"6"|"7"|"8"|"9" -> digit ; -- Should be predefined with unicode character classes
--   "0" | ( {digit}^"0" ) {digit}*    NUMBER ;
--   [{ASCII}&{LETTER}\-{digit}]+ IDENTIFIER ; -- That's how it shold look like
--   [abc\-][abc\-{digit}]*        IDENTIFIER ; -- That's how it is currently working
--   [a-\ee A-Y][a-\ee A-Y]*             IDENTIFIER ;


-- (([({alphabetic}&{basic-latin}){greek-and-coptic}]^[a-z \x3b1-\x3b3])&{basic-latin})+        IDENTIFIER ;
({alphabetic}&{basic-latin})+ IDENTIFIER;
-- [a-zA-Z]+ IDENTIFIER;


--   "#!foolisp"                   SHEBANG ;
--   [\ \n\t][\ \n\t]*                   [: /* blank */ :] ;
--   \" [.(\\.)^x]* \"            STRING ;
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
