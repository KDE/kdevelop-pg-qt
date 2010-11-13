%token_stream Lexer ;;

%token LPAREN, RPAREN, FOO, BAR, BAZ, NUMBER, SHEBANG ;;
%token_stream_bits_header "QDebug"
%parser_bits_header "QDebug"
%input_encoding "utf16"
%table_lexer
%input_stream "KDevPG::QStringIterator"

%lexer ->
  "(" LPAREN ;;
  ")" RPAREN ;;
  "foo" FOO ;;
  "bar" BAR ;;
  "baz" BAZ ;;
  (|||||||||"0""1""2""3""4""5""6""7""8""9") -> digit ;;
  &(& *{digit} {digit}) (|""(&"."(*{digit}))) NUMBER ;;
  "#!foolisp" SHEBANG ;;
  |(|" ""  ")"\n" ;;
  ;;

  ?SHEBANG sexp=sexp -> start ;;
  
  LPAREN #sexp=sexp* RPAREN
| foo=FOO | bar=BAR | baz=BAZ | number=NUMBER -> sexp ;;

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
