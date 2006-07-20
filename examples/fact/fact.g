
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
  void tokenize();

  enum problem_type {
    error,
    warning,
    info,
  };
  void report_problem( parser::problem_type type, const char* message );
  void report_problem( parser::problem_type type, std::string message );
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

   (#fun=function_definition)*
-> program ;;

   FUNCTION id=IDENTIFIER
   LPAREN (#param=IDENTIFIER @ COMMA | 0) RPAREN body=body
-> function_definition ;;

   LBRACE (#decl=declaration)* (#stmt=statement)* RBRACE
-> body ;;

   VAR (var=variable @ COMMA) SEMICOLON
-> declaration ;;

   id=IDENTIFIER
-> variable ;;


-- Statement rules
--------------------

   id=IDENTIFIER ASSIGN expr=expression SEMICOLON
-> assignment_statement ;;

   IF LPAREN cond=condition RPAREN if_stmt=statement
   (ELSE else_stmt=statement | 0)
-> if_statement ;;

   LBRACE (#stmt=statement)* RBRACE
-> block_statement ;;

   RETURN expr=expression SEMICOLON
-> return_statement ;;

   assign_stmt=assignment_statement
 | if_stmt=if_statement
 | block_stmt=block_statement
 | return_stmt=return_statement
-> statement ;;


-- Expression rules
--------------------

   num=NUMBER
 | id=IDENTIFIER (LPAREN (#argument=expression @ COMMA) RPAREN | 0)
-> primary ;;

   left_expr=primary (STAR right_expr=primary)*
-> mult_expression ;;

   left_expr=mult_expression (MINUS right_expr=mult_expression)*
-> expression ;;

   left_expr=expression EQUAL right_expr=expression
-> condition ;;

