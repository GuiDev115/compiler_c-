%{
#include <stdio.h>
#include <stdlib.h>
#include "c-minus-lexer.h" // Include the header for the lexer

extern int yylex();
extern int line_number;
extern int column_number;
extern int errors_count;

void yyerror(const char *s);
%}

%token INT FLOAT STRUCT VOID IF
%token IDENT NUM_INT NUM_REAL
%token PLUS MINUS TIMES DIVIDE MODULO
%token ASSIGN EQUAL NOT_EQUAL LESS LESS_EQUAL GREATER GREATER_EQUAL
%token SEMICOLON COMMA DOT
%token OPEN_BRACE CLOSE_BRACE OPEN_PAREN CLOSE_PAREN OPEN_BRACKET CLOSE_BRACKET

%%

// Grammar rules
program:
    program declaration
    | /* empty */
    ;

declaration:
    var_declaration SEMICOLON
    | fun_declaration
    ;

var_declaration:
    type IDENT SEMICOLON
    ;

fun_declaration:
    type IDENT OPEN_PAREN params CLOSE_PAREN compound_stmt
    ;

params:
    param_list
    | VOID
    ;

param_list:
    param_list COMMA param
    | param
    ;

param:
    type IDENT
    ;

compound_stmt:
    OPEN_BRACE local_declarations statement_list CLOSE_BRACE
    ;

local_declarations:
    local_declarations var_declaration
    | /* empty */
    ;

statement_list:
    statement_list statement
    | /* empty */
    ;

statement:
    expression_stmt
    | compound_stmt
    | selection_stmt
    | iteration_stmt
    | return_stmt
    ;

expression_stmt:
    expression SEMICOLON
    | SEMICOLON
    ;

selection_stmt:
    IF OPEN_PAREN expression CLOSE_PAREN statement
    | IF OPEN_PAREN expression CLOSE_PAREN statement ELSE statement
    ;

iteration_stmt:
    WHILE OPEN_PAREN expression CLOSE_PAREN statement
    ;

return_stmt:
    RETURN SEMICOLON
    | RETURN expression SEMICOLON
    ;

expression:
    IDENT ASSIGN expression
    | simple_expression
    ;

simple_expression:
    additive_expression
    | simple_expression LESS additive_expression
    | simple_expression LESS_EQUAL additive_expression
    | simple_expression GREATER additive_expression
    | simple_expression GREATER_EQUAL additive_expression
    | simple_expression EQUAL additive_expression
    | simple_expression NOT_EQUAL additive_expression
    ;

additive_expression:
    additive_expression PLUS term
    | additive_expression MINUS term
    | term
    ;

term:
    term TIMES factor
    | term DIVIDE factor
    | term MODULO factor
    | factor
    ;

factor:
    IDENT
    | NUM_INT
    | NUM_REAL
    | OPEN_PAREN expression CLOSE_PAREN
    ;

type:
    INT
    | FLOAT
    | STRUCT
    ;

%%

// Error handling
void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe: %s na linha %d, coluna %d\n", s, line_number, column_number);
    errors_count++;
}

int main(void) {
    return yyparse();
}