%token_stream Lexer ;

%input_encoding "ucs2"
%sequence_lexer
%input_stream "KDevPG::QStringIterator"

%parser_declaration_header "QtCore/QDebug"

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
  "<?"|"<?php"                  [: lxSET_RULE_SET(php) :] OPEN_TAG ;
  "<?="                         [: lxSET_RULE_SET(php) :] OPEN_TAG_WITH_ECHO ;
  .+ %ba("<?")                  INLINE_HTML;
  .+^(.*"<?".*)                 INLINE_HTML;
  ;

%lexer "php" ->
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
{bcast}"int"{ecast}     INT_CAST ;
{bcast}"double"{ecast}     DOUBLE_CAST ;
{bcast}"string"{ecast}     STRING_CAST ;
{bcast}"array"{ecast}     ARRAY_CAST ;
{bcast}"object"{ecast}     OBJECT_CAST ;
{bcast}"bool"{ecast}     BOOL_CAST ;
{bcast}"unset"{ecast}     UNSET_CAST ;



{white_space}+  WHITESPACE ;

;

0 -> start ;
