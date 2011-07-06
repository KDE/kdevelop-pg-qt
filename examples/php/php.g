%token_stream Lexer ;

%input_encoding "latin1"
%sequence_lexer
%input_stream "KDevPG::QByteArrayIterator"

%parser_declaration_header "QtCore/QDebug"

%lexer_bits_header "algorithm"
%lexer_declaration_header "QtCore/QStack"
%lexer_declaration_header "utility" -- pair
%lexerclass(private declaration)
[:
QStack<std::pair<Iterator::PlainIterator, Iterator::PlainIterator> > nowDocStack;
Iterator::PlainIterator hereDocHeaderBegin, hereDocHederEnd;
size_t inStringCounter;
:]

%lexerclass(constructor)
[:
inStringCounter = 0;
:]

-- keywords:
%token ABSTRACT ("abstract"), BREAK ("break"), CASE ("case"), CATCH ("catch"),
       CLASS ("class"), CONST ("const"), CONTINUE ("continue"),
       DEFAULT ("default"), DO ("do"), ELSE ("else"), EXTENDS ("extends"),
       FINAL ("final"), FOR ("for"), IF ("if"),
       IMPLEMENTS ("implements"), INSTANCEOF ("instanceof"), INTERFACE ("interface"),
       NEW ("new"), PRIVATE ("private"), PROTECTED ("protected"), PUBLIC ("public"),
       RETURN ("return"), STATIC ("static"), SWITCH ("switch"), THROW ("throw"),
       TRY ("try"), WHILE ("while"), ECHO ("echo"), PRINT ("print"),
       CLONE ("clone"), EXIT ("exit"), ELSEIF ("elseif"), ENDIF ("endif"),
       ENDWHILE ("endwhile"), ENDFOR ("endfor"), FOREACH ("foreach"), ENDFOREACH ("endforeach"),
       DECLARE ("declare"), ENDDECLARE ("enddeclare"), AS ("as"), ENDSWITCH ("endswitch"),
       FUNCTION ("function"), USE ("use"), GLOBAL ("global"), VAR ("var "), UNSET ("unset"),
       ISSET ("isset"), EMPTY ("empty"), HALT_COMPILER ("halt compiler"),
       DOUBLE_ARROW ("=>"), LIST ("list"), ARRAY ("array"), CLASS_C ("__CLASS__"),
       METHOD_C ("__METHOD__"), FUNC_C ("__FUNCTION__"), LINE ("__LINE__"),
       FILE ("__FILE__"), COMMENT ("comment"), DOC_COMMENT ("doc comment"),  PAAMAYIM_NEKUDOTAYIM ("::"),
       INCLUDE ("include"), INCLUDE_ONCE ("include_once"), EVAL ("eval"), REQUIRE ("require"),
       REQUIRE_ONCE ("require_once"), NAMESPACE ("namespace"), NAMESPACE_C("__NAMESPACE__"), USE("use"),
       GOTO ("goto") ;

-- casts:
%token INT_CAST ("int cast"), DOUBLE_CAST ("double cast"), STRING_CAST ("string cast"),
       ARRAY_CAST ("array cast"), OBJECT_CAST ("object cast"), BOOL_CAST ("bool cast"),
       UNSET_CAST ("unset cast") ;

-- seperators:
%token SEMICOLON (";"), DOUBLE_QUOTE ("\""), LBRACKET ("["),
       RBRACKET ("]"),
       LPAREN ("("), RPAREN (")"), LBRACE ("{"), RBRACE ("}"),
       COMMA (","), AT ("@"),
       CURLY_OPEN ("curly open"), -- { in "{$foo}"; not the same as LBRACE
       DOLLAR_OPEN_CURLY_BRACES ("${"),
       START_HEREDOC ("start heredoc"), END_HEREDOC ("end heredoc"),
       BACKTICK ("`"), BACKSLASH ("\\"),
       START_NOWDOC("start nowdoc"), END_NOWDOC("end nowdoc") ;

-- operators:
%token IS_EQUAL ("=="), IS_NOT_EQUAL ("!="), IS_IDENTICAL ("==="),
       IS_NOT_IDENTICAL ("!=="), IS_SMALLER ("<"), IS_GREATER (">"),
       IS_SMALLER_OR_EQUAL ("<="), IS_GREATER_OR_EQUAL (">="),
       BOOLEAN_OR ("||"), BOOLEAN_AND ("&&"), ASSIGN ("="),
       PLUS_ASSIGN ("+="), MINUS_ASSIGN ("-="), MUL_ASSIGN ("*="), DIV_ASSIGN ("/="),
       CONCAT_ASSIGN (".="), MOD_ASSIGN ("%="), AND_ASSIGN ("&="), OR_ASSIGN ("|="),
       XOR_ASSIGN ("^="), SL_ASSIGN ("<<="), SR_ASSIGN (">>="), OBJECT_OPERATOR ("->"),
       PLUS ("+"), MINUS("-"), CONCAT("."),
       INC ("++"), DEC ("--"), BANG ("!"), QUESTION ("?"), COLON (":"),
       BIT_AND ("&"), BIT_OR("|"), BIT_XOR ("^"),
       SL ("<<"), SR (">>"), MUL("*"), DIV("/"), MOD ("%"),
       TILDE ("~"), DOLLAR ("$"),
       LOGICAL_OR ("logical or"), LOGICAL_AND ("logical and"), LOGICAL_XOR ("logical xor") ;

-- literals and identifiers:
%token INLINE_HTML ("inline html"), WHITESPACE ("whitespace"),
       CONSTANT_ENCAPSED_STRING ("constant encapsed string"),
       VARIABLE ("variable"), ENCAPSED_AND_WHITESPACE ("encapsed and whitespace"),
       DNUMBER ("double number"), LNUMBER ("long number"),
       NUM_STRING ("num string"), STRING ("string"),
       STRING_VARNAME ("string varname") ; -- when in "${varname}"

-- open/close tags
%token OPEN_TAG ("<?"), CLOSE_TAG ("?>"), OPEN_TAG_WITH_ECHO ("<?=");

%lexer ->
  "<?"|"<?php"                  [: qDebug() << "blub"; lxSET_RULE_SET(php) qDebug() << "open tag" << lxBEGIN_IDX << " " << lxCURR_IDX << " " << char(*lxCURR_POS);  :] OPEN_TAG ;
  "<?="                         [: lxSET_RULE_SET(php) :] OPEN_TAG_WITH_ECHO ;
  .+ %ba("<?")                  [: qDebug() << "ht " << lxBEGIN_IDX << " " << lxCURR_IDX << " " << char(*lxCURR_POS); :] INLINE_HTML;
  ;

%lexer "php" ->

[{alphabetic}_][{alphabetic}{num}_]* -> identifier ;

"<<<"{identifier}\n               [: lxSET_RULE_SET(nowdoc); nowDocStack.push(make_pair(lxBEGIN_POS + 3, lxCURR_POS - 1)); :] START_NOWDOC;
"<<<'"{identifier}"'"\n           [: lxSET_RULE_SET(heredoc); nowDocStack.push(make_pair(lxBEGIN_POS + 4, lxCURR_POS - 2)); :] START_HEREDOC;

abstract        ABSTRACT ;
break           BREAK ;
case            CASE ;
catch           CATCH ;
class           CLASS ;
const           CONST ;
continue        CONTINUE ;
default         DEFAULT ;
do              DO ;
else            ELSE ;
extends         EXTENDS ;
final           FINAL ;
for             FOR ;
if              IF ;
implements      IMPLEMENTS ;
instanceof      INSTANCEOF ;
interface       INTERFACE ;
new             NEW ;
private         PRIVATE ;
protected       PROTECTED ;
public          PUBLIC ;
return          RETURN ;
static          STATIC ;
switch          SWITCH ;
throw           THROW ;
try             TRY ;
while           WHILE ;
echo            ECHO ;
print           PRINT ;
clone           CLONE ;
exit            EXIT ;
elseif          ELSEIF ;
endif           ENDIF ;
endwhile        ENDWHILE ;
endfor          ENDFOR ;
foreach         FOREACH ;
endforeach      ENDFOREACH ;
declare         DECLARE ;
enddeclare      ENDDECLARE ;
as              AS ;
endswitch       ENDSWITCH ;
function        FUNCTION ;
use             USE ;
global          GLOBAL ;
var             VAR ;
unset           UNSET ;
isset           ISSET ;
empty           EMPTY ;
__halt_compiler HALT_COMPILER ;
"=>"            DOUBLE_ARROW ;
list            LIST ;
array           ARRAY ;
"__CLASS__"     CLASS_C ;
"__METHOD__"    METHOD_C ;
"__FUNCTION__"  FUNC_C ;
"__LINE__"      LINE ;
"__FILE__"      FILE ;
"::"            PAAMAYIM_NEKUDOTAYIM ;
include         INCLUDE ;
include_once    INCLUDE_ONCE ;
eval            EVAL ;
require         REQUIRE ;
require_once    REQUIRE_ONCE ;
namespace       NAMESPACE ;
"__NAMESPACE__" NAMESPACE_C ;
use             USE ;
goto            GOTO ;

"/**"{white_space}(\.*^"*/")"*/"        DOC_COMMENT ;
"/*"(\.*^"*/")"*/"|"//"[.^\n]*          COMMENT ;
"?>"    [: lxSET_RULE_SET(start) :] CLOSE_TAG ;

"("{white_space}*   -> bcast ;
{white_space}*")"   -> ecast ;
{bcast}(int|integer){ecast}     INT_CAST ;
{bcast}(double|real|float){ecast}     DOUBLE_CAST ;
{bcast}(string|binary){ecast}     STRING_CAST ;
{bcast}"array"{ecast}     ARRAY_CAST ;
{bcast}"object"{ecast}     OBJECT_CAST ;
{bcast}(bool|boolean){ecast}     BOOL_CAST ;
{bcast}"unset"{ecast}     UNSET_CAST ;

"=="        IS_EQUAL;
"!="        IS_NOT_EQUAL;
"==="       IS_IDENTICAL;
"!=="       IS_NOT_IDENTICAL;
"<"         IS_SMALLER;
">"         IS_GREATER;
"<="        IS_SMALLER_OR_EQUAL;
">="        IS_GREATER_OR_EQUAL;
"||"        BOOLEAN_OR;
"&&"        BOOLEAN_AND;
"="         ASSIGN;
"+="        PLUS_ASSIGN;
"-="        MINUS_ASSIGN;
"*="        MUL_ASSIGN;
"/="        DIV_ASSIGN;
".="        CONCAT_ASSIGN;
"%="        MOD_ASSIGN;
"&="        AND_ASSIGN;
"|="        OR_ASSIGN;
"^="        XOR_ASSIGN;
"<<="       SL_ASSIGN;
">>="       SR_ASSIGN;
"->"        OBJECT_OPERATOR;
"+"         PLUS;
"-"         MINUS;
"."         CONCAT;
"++"        INC;
"--"        DEC;
"!"         BANG;
"?"         QUESTION;
":"         COLON;
"&"         BIT_AND;
"|"         BIT_OR;
"^"         BIT_XOR;
"<<"        SL;
">>"        SR;
"*"         MUL;
"/"         DIV;
"%"         MOD;
"~"         TILDE;
"$"         DOLLAR;
"or"        LOGICAL_OR;
"and"       LOGICAL_AND;
"xor"       LOGICAL_XOR;

";"         SEMICOLON;
"["         LBRACKET;
"]"         RBRACKET;
"("         LPAREN;
")"         RPAREN;
"{"         LBRACE;
"}"         RBRACE;
","         COMMA;
"@"         AT;

("$"{identifier})    VARIABLE ;
{identifier}         STRING ;

{white_space}+  WHITESPACE ;

;

%lexer "nowdoc" ->
%enter [: ++inStringCounter; qDebug() << "entering nowdoc"; :]
%leave [: --inStringCounter; qDebug() << "leaving nowdoc"; :]
%fail [: qDebug() << "failed in nowdoc"; :]
-- "$"{identifier}   
-- "${"
[.^\na]*\n    [:
              std::size_t topLength = nowDocStack.top().second - nowDocStack.top().first;
              if(lxLENGTH >= topLength && equal(nowDocStack.top().first, nowDocStack.top().second, lxBEGIN_POS))
              {
                  lxCURR_POS = lxBEGIN_POS + topLength;
                  nowDocStack.pop();
                  lxSET_RULE_SET(php);
                  lxRETURN(END_NOWDOC);
              }
            :]
            STRING;
;

%lexer "heredoc" ->
[.^\n]*\n    [:
              std::size_t topLength = nowDocStack.top().second - nowDocStack.top().first;
              if(lxLENGTH >= topLength && equal(nowDocStack.top().first, nowDocStack.top().second, lxBEGIN_POS))
              {
                  lxCURR_POS = lxBEGIN_POS + topLength;
                  nowDocStack.pop();
                  lxSET_RULE_SET(php);
                  lxRETURN(END_NOWDOC);
              }
            :]
            STRING;
;

0 -> start ;
