%{

/* C-MINUS PARSER
Feito por: 
    - Guilherme Fabricio Brito da Rosa
    - Harisson de Carvalho Alvarenga
    - Raul Soares de Carvalho
*/  
    #include <stdio.h>
    #include <stdlib.h>

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

%nonassoc ELSE_KEYWORD

%start programa

%%
programa    		:	  declaracao_lista            { printf("Sucesso!\n"); }
            		;

declaracao_lista    	:	  declaracao
				| declaracao_lista declaracao
            		;

declaracao    		:	  var_declaracao
            			| fun_declaracao 
            		;
            
var_declaracao		:	  tipo_especificador IDENTIFIER SEMICOLON
				| tipo_especificador IDENTIFIER OPEN_BRACKET INT_NUMBER CLOSE_BRACKET 					  arranjo_dimensao  SEMICOLON
				| tipo_especificador IDENTIFIER error
				| tipo_especificador IDENTIFIER OPEN_BRACKET INT_NUMBER CLOSE_BRACKET 					  arranjo_dimensao  error
			;
			
arranjo_dimensao		:	
				| arranjo_dimensao OPEN_BRACKET INT_NUMBER CLOSE_BRACKET
			;
				
tipo_especificador	:	  INT_TYPE 
				| FLOAT_TYPE
				| CHAR_TYPE
				| VOID_TYPE
				| STRUCT_TYPE IDENTIFIER OPEN_BRACE atributos_declaracao CLOSE_BRACE	
			;				
            			
atributos_declaracao	:	  var_declaracao
				| atributos_declaracao var_declaracao
			;	
            			
fun_declaracao		:	  tipo_especificador IDENTIFIER OPEN_PAREN params CLOSE_PAREN composto_decl
			;
			
params			:	  param_lista 
				| VOID_TYPE
			;

param_lista		:	  param
				| param_lista COMMA param
			;

param			:	  tipo_especificador IDENTIFIER 
				| tipo_especificador IDENTIFIER OPEN_BRACKET CLOSE_BRACKET
			;
			
composto_decl		:	  OPEN_BRACE local_declaracoes comando_lista CLOSE_BRACE
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
			;
			
selecao_decl		:	  IF_KEYWORD OPEN_PAREN expressao CLOSE_PAREN comando
				| IF_KEYWORD OPEN_PAREN expressao CLOSE_PAREN comando ELSE_KEYWORD comando
			;
			
iteracao_decl		:	  WHILE_KEYWORD OPEN_PAREN expressao CLOSE_PAREN comando
			;
			
retorno_decl		:	  RETURN_KEYWORD SEMICOLON
				| RETURN_KEYWORD expressao SEMICOLON
			;	
			
expressao		:	  var ASSIGN_OP expressao
				| expressao_simples 
			;
			
var			:	  IDENTIFIER
				| IDENTIFIER OPEN_BRACKET expressao CLOSE_BRACKET arranjo_acesso    
			;
			
arranjo_acesso		:	  
				| arranjo_acesso OPEN_BRACKET expressao CLOSE_BRACKET
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
            		;

ativacao		:	  IDENTIFIER OPEN_PAREN args CLOSE_PAREN
			;
			
args			:	  arg_lista
				| 
			;
			
arg_lista		:	  expressao 
				| arg_lista COMMA expressao	
			;
			            			
%%

void yyerror(const char *s){
	fprintf(stderr, "(%d) Erro sintatico na linha %d e coluna %d\n", errors_count++, line_number, 		column_number);
}

extern FILE *yyin;
extern int yydebug;

int main(int argc, char *argv[]) {
    yydebug = 1;
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

    yyparse(); 

    fclose(input_file);

    return 0;
}
