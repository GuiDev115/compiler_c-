%{

/* C-MINUS PARSER
Feito por: 
    - Guilherme Fabricio Brito da Rosa
    - Harisson de Carvalho Alvarenga
    - Raul Soares de Carvalho
*/  
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "../semantic/symbol_table.h"
    #include "../semantic/semantic.h"
    #include "../semantic/code_generator.h"
    #include "../semantic/utils.h"

    // Variáveis globais do lexer
    int line_number = 1;
    int column_number = 1;
    int errors_count = 0;
    int yydebug = 0;
    FILE* yyin;
    
    int yylex(void);
    void yyerror(const char *s);
    
    // Variáveis para análise semântica
    DataType current_type;
    char* current_identifier;
    char* temp_var;
    
    // Implementação simplificada do lexer
    int yylex(void) {
        static int token_index = 0;
        static int tokens[] = {INT_TYPE, IDENTIFIER, OPEN_PAREN, CLOSE_PAREN, 
                              OPEN_BRACE, CLOSE_BRACE, RETURN_KEYWORD, INT_NUMBER, 
                              SEMICOLON, 0};
        
        if (tokens[token_index] == 0) return 0;
        return tokens[token_index++];
    }
%}

%token INT_TYPE FLOAT_TYPE CHAR_TYPE STRUCT_TYPE VOID_TYPE IF_KEYWORD ELSE_KEYWORD WHILE_KEYWORD RETURN_KEYWORD
%token PLUS_OP MINUS_OP MULT_OP DIV_OP MOD_OP ASSIGN_OP EQUAL_OP NE_OP LT_OP LE_OP GT_OP GE_OP
%token OPEN_BRACE CLOSE_BRACE OPEN_PAREN CLOSE_PAREN OPEN_BRACKET CLOSE_BRACKET
%token SEMICOLON COMMA DOT
%token IDENTIFIER
%token INT_NUMBER REAL_NUMBER
%token INVALID_IDENTIFIER
%token LEXICAL_ERROR

%union {
    int intval;
    float floatval;
    char* strval;
    DataType type;
    SymbolEntry* symbol;
}

%type <strval> IDENTIFIER INT_NUMBER REAL_NUMBER
%type <type> tipo_especificador
%type <strval> expressao var fator termo expressao_soma expressao_simples
%type <strval> ativacao args arg_lista

%nonassoc LOWER
%nonassoc ELSE_KEYWORD
%nonassoc ERROR_RECOVERY

%start programa

%%
programa    		:	  declaracao_lista            { 
                        printf("Parsing concluído com sucesso!\n"); 
                        finish_semantic_analysis();
                        finish_code_generation();
                    }
                    ;

declaracao_lista    	:	  declaracao
                | declaracao_lista declaracao
                    ;

declaracao    		:	  var_declaracao
                        | fun_declaracao 
                    ;
            
var_declaracao		:	  tipo_especificador IDENTIFIER SEMICOLON {
                        current_type = $1;
                        current_identifier = $2;
                        declare_variable(current_identifier, current_type, 0, line_number);
                    }
                | tipo_especificador IDENTIFIER OPEN_BRACKET INT_NUMBER CLOSE_BRACKET arranjo_dimensao SEMICOLON {
                        current_type = $1;
                        current_identifier = $2;
                        declare_variable(current_identifier, current_type, 1, line_number);
                        
                        // Adiciona a primeira dimensão do array
                        SymbolEntry* entry = lookup_symbol(global_symbol_table, current_identifier);
                        if (entry) {
                            int size;
                            if (string_to_int($4, &size)) {
                                add_array_dimension(entry, size);
                            }
                        }
                    }
                | tipo_especificador IDENTIFIER error SEMICOLON { yyerror("Erro na declaração de variável"); yyerrok; }
                | tipo_especificador IDENTIFIER OPEN_BRACKET INT_NUMBER error SEMICOLON { yyerror("Esperado ']' após índice do array"); yyerrok; }
                | tipo_especificador IDENTIFIER OPEN_BRACKET error CLOSE_BRACKET SEMICOLON { yyerror("Índice inválido no array"); yyerrok; }
            ;
            
arranjo_dimensao		:	
                | arranjo_dimensao OPEN_BRACKET INT_NUMBER CLOSE_BRACKET
                | arranjo_dimensao OPEN_BRACKET INT_NUMBER error { yyerror("Esperado ']' após dimensão do array"); yyerrok; }
                | arranjo_dimensao OPEN_BRACKET error CLOSE_BRACKET { yyerror("Dimensão inválida no array"); yyerrok; }
            ;
                
tipo_especificador	:	  INT_TYPE { $$ = TYPE_INT; }
                | FLOAT_TYPE { $$ = TYPE_FLOAT; }
                | CHAR_TYPE { $$ = TYPE_CHAR; }
                | VOID_TYPE { $$ = TYPE_VOID; }
                | STRUCT_TYPE IDENTIFIER OPEN_BRACE atributos_declaracao CLOSE_BRACE {
                    $$ = TYPE_STRUCT;
                    declare_struct($2, line_number);
                }
                | STRUCT_TYPE IDENTIFIER OPEN_BRACE atributos_declaracao error { yyerror("Esperado '}' após declarações do struct"); yyerrok; }
                | STRUCT_TYPE IDENTIFIER OPEN_BRACE error CLOSE_BRACE { yyerror("Declarações inválidas no struct"); yyerrok; }
            ;				
                        
atributos_declaracao	:	  var_declaracao
                | atributos_declaracao var_declaracao
            ;	
                        
fun_declaracao		:	  tipo_especificador IDENTIFIER OPEN_PAREN params CLOSE_PAREN composto_decl {
                        current_type = $1;
                        current_identifier = $2;
                        declare_function(current_identifier, current_type, line_number);
                    }
                | tipo_especificador IDENTIFIER OPEN_PAREN params error composto_decl { yyerror("Esperado ')' após parâmetros da função"); yyerrok; }
                | tipo_especificador IDENTIFIER OPEN_PAREN error CLOSE_PAREN composto_decl { yyerror("Parâmetros inválidos na função"); yyerrok; }
            ;
            
params			:	  param_lista 
                | VOID_TYPE
            ;

param_lista		:	  param
                | param_lista COMMA param
            ;

param			:	  tipo_especificador IDENTIFIER 
                | tipo_especificador IDENTIFIER OPEN_BRACKET CLOSE_BRACKET
                | tipo_especificador IDENTIFIER OPEN_BRACKET error { yyerror("Esperado ']' após '[' no parâmetro array"); yyerrok; }
            ;
            
composto_decl        :      OPEN_BRACE {
                        enter_scope(global_symbol_table);
                    } local_declaracoes comando_lista temp
            ;

temp        :      CLOSE_BRACE {
                    exit_scope(global_symbol_table);
                }
            | error { yyerror("Esperado '}' para fechar bloco de comandos"); yyerrok; }

local_declaracoes	:	  /* empty */
                | local_declaracoes var_declaracao
            ;
            
comando_lista		:	  
                | comando_lista comando
            ;
            
comando			:	  expressao_decl
                | composto_decl	
                | selecao_decl
                | iteracao_decl
                | retorno_decl
            ;

expressao_decl		:	  expressao SEMICOLON
                | SEMICOLON
                | expressao error { yyerror("Esperado ';' após expressão"); yyerrok; }
            ;
            
selecao_decl		:	  IF_KEYWORD OPEN_PAREN expressao CLOSE_PAREN comando %prec LOWER
                | IF_KEYWORD OPEN_PAREN expressao CLOSE_PAREN comando ELSE_KEYWORD comando 
                | IF_KEYWORD OPEN_PAREN expressao error comando { yyerror("Esperado ')' após condição do if"); yyerrok; }
                | IF_KEYWORD OPEN_PAREN error CLOSE_PAREN comando { yyerror("Expressão inválida na condição do if"); yyerrok; }
                | IF_KEYWORD error { yyerror("Esperado '(' após if"); yyerrok; }
            ;
            
iteracao_decl		:	  WHILE_KEYWORD OPEN_PAREN expressao CLOSE_PAREN comando
                | WHILE_KEYWORD OPEN_PAREN expressao error comando { 
                    yyerror("Esperado ')' após condição do while"); 
                    yyerrok; 
                }
                | WHILE_KEYWORD OPEN_PAREN error CLOSE_PAREN comando { 
                    yyerror("Expressão inválida na condição do while"); 
                    yyerrok; 
                }
                | WHILE_KEYWORD error { 
                    yyerror("Esperado '(' após while"); 
                    yyerrok; 
                }
            ;
            
retorno_decl		:	  RETURN_KEYWORD SEMICOLON {
                        emit_return(NULL);
                    }
                | RETURN_KEYWORD expressao SEMICOLON {
                        emit_return($2);
                    }
                | RETURN_KEYWORD expressao error { yyerror("Esperado ';' após return"); yyerrok; }
            ;	
            
expressao		:	  var ASSIGN_OP expressao {
                        // Verifica se a variável foi declarada
                        check_variable_usage($1, line_number);
                        
                        // Verifica compatibilidade de tipos
                        DataType var_type = get_variable_type($1);
                        DataType expr_type = get_variable_type($3);
                        
                        if (var_type != TYPE_ERROR && expr_type != TYPE_ERROR) {
                            check_assignment(var_type, expr_type, line_number);
                        }
                        
                        // Gera código intermediário
                        emit_assignment($1, $3);
                        $$ = $1;
                    }
                | expressao_simples {
                        $$ = $1;
                    }
            ;
            
var			:	  IDENTIFIER {
                        check_variable_usage($1, line_number);
                        $$ = $1;
                    }
                | IDENTIFIER OPEN_BRACKET expressao CLOSE_BRACKET arranjo_acesso {
                        check_variable_usage($1, line_number);
                        
                        // Gera código para acesso ao array
                        char* temp = new_temp();
                        emit_array_access($1, $3, temp);
                        $$ = temp;
                    }
                | IDENTIFIER OPEN_BRACKET expressao error arranjo_acesso { yyerror("Esperado ']' após índice do array"); yyerrok; }
                | IDENTIFIER OPEN_BRACKET error CLOSE_BRACKET arranjo_acesso { yyerror("Índice inválido no array"); yyerrok; }
            ;
            
arranjo_acesso		:	  
                | arranjo_acesso OPEN_BRACKET expressao CLOSE_BRACKET
                | arranjo_acesso OPEN_BRACKET expressao error { yyerror("Esperado ']' após índice do array multidimensional"); yyerrok; }
                | arranjo_acesso OPEN_BRACKET error CLOSE_BRACKET { yyerror("Índice inválido no array multidimensional"); yyerrok; }
            ;
            
expressao_simples	:	  expressao_soma {
                        $$ = $1;
                    }
                | expressao_soma relacional expressao_soma {
                        // Gera código para operação relacional
                        char* temp = new_temp();
                        emit_binary_op("relop", $1, $3, temp);
                        $$ = temp;
                    }
            ;
            
relacional		:	  LE_OP
                | LT_OP
                | GT_OP
                | GE_OP
                | EQUAL_OP
                | NE_OP
            ;

expressao_soma		:	  termo {
                        $$ = $1;
                    }
                | expressao_soma soma_op termo {
                        // Gera código para operação de soma/subtração
                        char* temp = new_temp();
                        emit_binary_op("+", $1, $3, temp);
                        $$ = temp;
                    }
            ;
            
soma_op			:	  PLUS_OP
                | MINUS_OP	
            ;				
            
termo			:	  fator {
                        $$ = $1;
                    }
                | termo mult_op fator {
                        // Gera código para operação de multiplicação/divisão
                        char* temp = new_temp();
                        emit_binary_op("*", $1, $3, temp);
                        $$ = temp;
                    }
            ;
                            
mult_op			:	  MULT_OP
                | DIV_OP
            ;
                
fator			:	  OPEN_PAREN expressao CLOSE_PAREN {
                        $$ = $2;
                    }
                | var {
                        $$ = $1;
                    }
                | ativacao {
                        $$ = $1;
                    }
                | REAL_NUMBER {
                        $$ = $1;
                    }
                | INT_NUMBER {
                        $$ = $1;
                    }
                | OPEN_PAREN expressao error { yyerror("Esperado ')' após expressão"); yyerrok; }
                | OPEN_PAREN error CLOSE_PAREN { yyerror("Expressão inválida entre parênteses"); yyerrok; }
                    ;

ativacao		:	  IDENTIFIER OPEN_PAREN args CLOSE_PAREN {
                        check_variable_usage($1, line_number);
                        
                        // Gera código para chamada de função
                        char* temp = new_temp();
                        emit_function_call($1, temp);
                        $$ = temp;
                    }
                | IDENTIFIER OPEN_PAREN args error { yyerror("Esperado ')' após argumentos da função"); yyerrok; }
            ;
            
args			:	  /* empty */ {
                        $$ = "";
                    }
                | arg_lista {
                        $$ = $1;
                    }
            ;
            
arg_lista		:	  expressao {
                        $$ = $1;
                    }
                | arg_lista COMMA expressao {
                        // Concatena argumentos (simplificado)
                        $$ = $1;
                    }
            ;
                        			
%%

void yyerror(const char *s){
    if (strcmp(s, "syntax error") == 0) {
        fprintf(stderr, "(%d) Erro sintático na linha %d, coluna %d: Token inesperado\n", 
            ++errors_count, line_number, column_number);
    } else {
        fprintf(stderr, "(%d) Erro sintático na linha %d, coluna %d: %s\n", 
            ++errors_count, line_number, column_number, s);
    }
}

extern FILE *yyin;
extern int yydebug;

int main(int argc, char *argv[]) {
    yydebug = 1;
    errors_count = 0;
    
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Não foi possível abrir o arquivo de entrada");
        return 1;
    }

    yyin = input_file;
    
    // Inicializa análise semântica e geração de código
    init_semantic_analysis();
    init_code_generation();
    
    printf("Iniciando análise sintática...\n");
    
    int result = yyparse();
    
    if (errors_count == 0) {
        printf("Análise sintática concluída sem erros.\n");
    } else {
        printf("Análise sintática concluída com %d erro(s).\n", errors_count);
    }

    fclose(input_file);

    return result;
}