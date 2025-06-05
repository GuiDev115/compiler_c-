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

    extern int line_number;
    extern int column_number;
    extern int errors_count;
    
    int yylex(void);
    void yyerror(const char *s);
%}

%token INT_TYPE FLOAT_TYPE CHAR_TYPE STRUCT_TYPE VOID_TYPE IF_KEYWORD ELSE_KEYWORD WHILE_KEYWORD RETURN_KEYWORD
%token PLUS_OP MINUS_OP MULT_OP DIV_OP MOD_OP ASSIGN_OP EQUAL_OP NE_OP LT_OP LE_OP GT_OP GE_OP
%token OPEN_BRACE CLOSE_BRACE OPEN_PAREN CLOSE_PAREN OPEN_BRACKET CLOSE_BRACKET
%token SEMICOLON COMMA DOT
%token IDENTIFIER
%token INT_NUMBER REAL_NUMBER
%token INVALID_IDENTIFIER
%token LEXICAL_ERROR

%nonassoc LOWER
%nonassoc ELSE_KEYWORD

%start programa

%%
programa    		:	  declaracao_lista            { printf("Parsing concluído com sucesso!\n"); }
                    ;

declaracao_lista    	:	  declaracao
                | declaracao_lista declaracao
                    ;

declaracao    		:	  var_declaracao
                        | fun_declaracao 
                    ;
            
var_declaracao		:	  tipo_especificador IDENTIFIER SEMICOLON
                | tipo_especificador IDENTIFIER OPEN_BRACKET INT_NUMBER CLOSE_BRACKET arranjo_dimensao SEMICOLON
                | tipo_especificador IDENTIFIER error SEMICOLON { yyerror("Erro na declaração de variável"); yyerrok; }
                | tipo_especificador IDENTIFIER OPEN_BRACKET INT_NUMBER error SEMICOLON { yyerror("Esperado ']' após índice do array"); yyerrok; }
                | tipo_especificador IDENTIFIER OPEN_BRACKET error CLOSE_BRACKET SEMICOLON { yyerror("Índice inválido no array"); yyerrok; }
            ;
            
arranjo_dimensao		:	
                | arranjo_dimensao OPEN_BRACKET INT_NUMBER CLOSE_BRACKET
                | arranjo_dimensao OPEN_BRACKET INT_NUMBER error { yyerror("Esperado ']' após dimensão do array"); yyerrok; }
                | arranjo_dimensao OPEN_BRACKET error CLOSE_BRACKET { yyerror("Dimensão inválida no array"); yyerrok; }
            ;
                
tipo_especificador	:	  INT_TYPE 
                | FLOAT_TYPE
                | CHAR_TYPE
                | VOID_TYPE
                | STRUCT_TYPE IDENTIFIER OPEN_BRACE atributos_declaracao CLOSE_BRACE
                | STRUCT_TYPE IDENTIFIER OPEN_BRACE atributos_declaracao error { yyerror("Esperado '}' após declarações do struct"); yyerrok; }
                | STRUCT_TYPE IDENTIFIER OPEN_BRACE error CLOSE_BRACE { yyerror("Declarações inválidas no struct"); yyerrok; }
            ;				
                        
atributos_declaracao	:	  var_declaracao
                | atributos_declaracao var_declaracao
            ;	
                        
fun_declaracao		:	  tipo_especificador IDENTIFIER OPEN_PAREN params CLOSE_PAREN composto_decl
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
            
composto_decl		:	  OPEN_BRACE local_declaracoes comando_lista CLOSE_BRACE
                | OPEN_BRACE local_declaracoes comando_lista error { yyerror("Esperado '}' para fechar bloco de comandos"); yyerrok; }
                | OPEN_BRACE error CLOSE_BRACE { yyerror("Comandos inválidos no bloco"); yyerrok; }
            ;

local_declaracoes	:	  
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
            
retorno_decl		:	  RETURN_KEYWORD SEMICOLON
                | RETURN_KEYWORD expressao SEMICOLON
                | RETURN_KEYWORD expressao error { yyerror("Esperado ';' após return"); yyerrok; }
            ;	
            
expressao		:	  var ASSIGN_OP expressao
                | expressao_simples 
            ;
            
var			:	  IDENTIFIER
                | IDENTIFIER OPEN_BRACKET expressao CLOSE_BRACKET arranjo_acesso
                | IDENTIFIER OPEN_BRACKET expressao error arranjo_acesso { yyerror("Esperado ']' após índice do array"); yyerrok; }
                | IDENTIFIER OPEN_BRACKET error CLOSE_BRACKET arranjo_acesso { yyerror("Índice inválido no array"); yyerrok; }
            ;
            
arranjo_acesso		:	  
                | arranjo_acesso OPEN_BRACKET expressao CLOSE_BRACKET
                | arranjo_acesso OPEN_BRACKET expressao error { yyerror("Esperado ']' após índice do array multidimensional"); yyerrok; }
                | arranjo_acesso OPEN_BRACKET error CLOSE_BRACKET { yyerror("Índice inválido no array multidimensional"); yyerrok; }
            ;
            
expressao_simples	:	  expressao_soma 
                | expressao_soma relacional expressao_soma
            ;
            
relacional		:	  LE_OP
                | LT_OP
                | GT_OP
                | GE_OP
                | EQUAL_OP
                | NE_OP
            ;

expressao_soma		:	  termo
                | expressao_soma soma_op termo
            ;
            
soma_op			:	  PLUS_OP
                | MINUS_OP	
            ;				
            
termo			:	  fator 
                | termo mult_op fator
            ;
                            
mult_op			:	  MULT_OP
                | DIV_OP
            ;
                
fator			:	  OPEN_PAREN expressao CLOSE_PAREN
                | var
                | ativacao
                | REAL_NUMBER
                | INT_NUMBER
                | OPEN_PAREN expressao error { yyerror("Esperado ')' após expressão"); yyerrok; }
                | OPEN_PAREN error CLOSE_PAREN { yyerror("Expressão inválida entre parênteses"); yyerrok; }
                    ;

ativacao		:	  IDENTIFIER OPEN_PAREN args CLOSE_PAREN
                | IDENTIFIER OPEN_PAREN args error { yyerror("Esperado ')' após argumentos da função"); yyerrok; }
                | IDENTIFIER OPEN_PAREN error CLOSE_PAREN { yyerror("Argumentos inválidos na chamada de função"); yyerrok; }
            ;
            
args			:	  arg_lista
                | 
            ;
            
arg_lista		:	  expressao 
                | arg_lista COMMA expressao	
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