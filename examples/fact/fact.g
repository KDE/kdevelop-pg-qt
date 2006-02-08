------------------------------------------------------------
-- T O K E N   L I S T
------------------------------------------------------------
%token FUNCTION, VAR, IF, ELSE, RETURN ;;
%token LPAREN, RPAREN, LBRACE, RBRACE, COMMA, SEMICOLON ;;
%token EQUAL, EQUAL_EQUAL, STAR, MINUS ;;
%token ID, NUMBER ;;

------------------------------------------------------------
-- D E C L A R A T I O N
------------------------------------------------------------
   (#fun=function_definition)*
-> program ;;

   FUNCTION id=ID LPAREN (#param=ID @ COMMA | 0) RPAREN body=body
-> function_definition ;;

   LBRACE (#decl=declaration)* (#stmt=statement)* RBRACE
-> body ;;

   VAR var=variable @ COMMA SEMICOLON
-> declaration ;;

   id=ID
-> variable ;;

------------------------------------------------------------
-- S T A T E M E N T
------------------------------------------------------------
   id=ID EQUAL expr=expression SEMICOLON
-> assignment_statement ;;

   IF LPAREN cond=condition RPAREN stmt=statement
      (ELSE else_stmt=statement | 0)
-> if_statement ;;

   LBRACE (#stmt=statement)* RBRACE
-> block_statement ;;

   RETURN expr=expression SEMICOLON
-> return_statement ;;

   assgn_stmt=assignment_statement
 | if_stmt=if_statement
 | block_stmt=block_statement
 | ret_stmt=return_statement
-> statement ;;

------------------------------------------------------------
-- E X P R E S S I O N
------------------------------------------------------------
   num=NUMBER
 | id=ID (LPAREN #arg=expression @ COMMA RPAREN | 0)
-> primary ;;

   left_expr=primary (op=STAR right_expr=primary)*
-> mult_expression ;;

   left_expr=mult_expression (op=MINUS right_expr=mult_expression)*
-> expression ;;

   left_expr=expression op=EQUAL_EQUAL right_expr=expression
-> condition ;;

