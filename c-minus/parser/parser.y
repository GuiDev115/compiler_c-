%{

/* C-MINUS PARSER WITH SEMANTIC ANALYSIS
Feito por: 
    - Guilherme Fabricio Brito da Rosa
    - Harisson de Carvalho Alvarenga
    - Raul Soares de Carvalho
*/  
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "../semantic/semantic.h"

    extern int line_number;
    extern int column_number;
    extern int errors_count;
    extern char *yytext;
    
    int yylex(void);
    void yyerror(const char *s);
    
    /* Variáveis globais para análise semântica */
    ASTNode *ast_root = NULL;
%}

%union {
    int int_val;
    float float_val;
    char char_val;
    char *string_val;
    ASTNode *ast_node;
    DataType data_type;
    Operator operator;
}

%token <string_val> IDENTIFIER
%token <int_val> INT_NUMBER 
%token <float_val> REAL_NUMBER
%token <data_type> INT_TYPE FLOAT_TYPE CHAR_TYPE STRUCT_TYPE VOID_TYPE 
%token IF_KEYWORD ELSE_KEYWORD WHILE_KEYWORD RETURN_KEYWORD
%token PLUS_OP MINUS_OP MULT_OP DIV_OP MOD_OP ASSIGN_OP EQUAL_OP NE_OP LT_OP LE_OP GT_OP GE_OP
%token OPEN_BRACE CLOSE_BRACE OPEN_PAREN CLOSE_PAREN OPEN_BRACKET CLOSE_BRACKET
%token SEMICOLON COMMA DOT
%token INVALID_IDENTIFIER
%token LEXICAL_ERROR

%type <ast_node> programa declaracao_lista declaracao var_declaracao fun_declaracao
%type <ast_node> composto_decl local_declaracoes comando_lista comando expressao_decl
%type <ast_node> selecao_decl iteracao_decl retorno_decl expressao var
%type <ast_node> expressao_simples expressao_soma termo fator ativacao
%type <ast_node> params param_lista param args arg_lista atributos_declaracao
%type <ast_node> arranjo_dimensao arranjo_acesso temp
%type <data_type> tipo_especificador
%type <operator> relacional soma_op mult_op

%nonassoc LOWER
%nonassoc ELSE_KEYWORD
%nonassoc ERROR_RECOVERY

%start programa

%%
programa    		:	  declaracao_lista            { 
                        printf("Parsing concluído com sucesso!\n"); 
                        printf(">>> Iniciando análise semântica...\n");
                        
                        /* Inicializa análise semântica */
                        init_semantic_analysis();
                        
                        /* Cria nó raiz da AST */
                        ast_root = create_program_node($1);
                        $$ = ast_root;
                        
                        /* Executa análise semântica */
                        if (check_program(ast_root) != 0) {
                            printf(">>> Análise semântica concluída com sucesso!\n");
                            printf(">>> Iniciando geração de código...\n");
                            
                            /* Imprime tabela de símbolos */
                            printf("\n=== TABELA DE SÍMBOLOS ===\n");
                            print_symbol_table(get_symbol_table());
                            
                            /* Imprime código de três endereços */
                            printf("\n=== CÓDIGO DE TRÊS ENDEREÇOS ===\n");
                            print_instruction_list(get_instruction_list());
                        } else {
                            printf(">>> Análise semântica falhou!\n");
                        }
                        
                        finalize_semantic_analysis();
                    }
                    ;

declaracao_lista    	:	  declaracao                   { $$ = $1; }
                        | declaracao_lista declaracao     { 
                            $1->next = $2; 
                            $$ = $1; 
                        }
                    ;

declaracao    		:	  var_declaracao               { $$ = $1; }
                        | fun_declaracao               { $$ = $1; }
                    ;
            
var_declaracao		:	  tipo_especificador IDENTIFIER SEMICOLON {
                        printf(">>> Declaração de variável: %s\n", $2);
                        $$ = create_var_declaration_node($2, $1, line_number);
                    }
                | tipo_especificador IDENTIFIER OPEN_BRACKET INT_NUMBER CLOSE_BRACKET arranjo_dimensao SEMICOLON {
                        printf(">>> Declaração de array: %s[%d]\n", $2, $4);
                        ASTNode *node = create_var_declaration_node($2, $1, line_number);
                        node->data.var_decl.array_size = $4;
                        $$ = node;
                    }
                | tipo_especificador IDENTIFIER error SEMICOLON { yyerror("Erro na declaração de variável"); yyerrok; $$ = NULL; }
                | tipo_especificador IDENTIFIER OPEN_BRACKET INT_NUMBER error SEMICOLON { yyerror("Esperado ']' após índice do array"); yyerrok; $$ = NULL; }
                | tipo_especificador IDENTIFIER OPEN_BRACKET error CLOSE_BRACKET SEMICOLON { yyerror("Índice inválido no array"); yyerrok; $$ = NULL; }
            ;
            
arranjo_dimensao		:	
                | arranjo_dimensao OPEN_BRACKET INT_NUMBER CLOSE_BRACKET
                | arranjo_dimensao OPEN_BRACKET INT_NUMBER error { yyerror("Esperado ']' após dimensão do array"); yyerrok; }
                | arranjo_dimensao OPEN_BRACKET error CLOSE_BRACKET { yyerror("Dimensão inválida no array"); yyerrok; }
            ;
                
tipo_especificador	:	  INT_TYPE                    { printf(">>> Tipo: int\n"); $$ = TYPE_INT; }
                        | FLOAT_TYPE                  { printf(">>> Tipo: float\n"); $$ = TYPE_FLOAT; }
                        | CHAR_TYPE                   { printf(">>> Tipo: char\n"); $$ = TYPE_CHAR; }
                        | VOID_TYPE                   { printf(">>> Tipo: void\n"); $$ = TYPE_VOID; }
                        | STRUCT_TYPE IDENTIFIER OPEN_BRACE atributos_declaracao CLOSE_BRACE { 
                            printf(">>> Tipo: struct %s\n", $2); 
                            $$ = TYPE_STRUCT; 
                        }
                        | STRUCT_TYPE IDENTIFIER OPEN_BRACE atributos_declaracao error { yyerror("Esperado '}' após declarações do struct"); yyerrok; $$ = TYPE_ERROR; }
                        | STRUCT_TYPE IDENTIFIER OPEN_BRACE error CLOSE_BRACE { yyerror("Declarações inválidas no struct"); yyerrok; $$ = TYPE_ERROR; }
            ;				
                        
atributos_declaracao	:	  var_declaracao { $$ = $1; }
                | atributos_declaracao var_declaracao { 
                    $1->next = $2; 
                    $$ = $1; 
                }
            ;	
                        
fun_declaracao		:	  tipo_especificador IDENTIFIER OPEN_PAREN params CLOSE_PAREN composto_decl {
                        printf(">>> Declaração de função: %s\n", $2);
                        $$ = create_fun_declaration_node($2, $1, $4, $6, line_number);
                    }
                | tipo_especificador IDENTIFIER OPEN_PAREN params error composto_decl { yyerror("Esperado ')' após parâmetros da função"); yyerrok; $$ = NULL; }
                | tipo_especificador IDENTIFIER OPEN_PAREN error CLOSE_PAREN composto_decl { yyerror("Parâmetros inválidos na função"); yyerrok; $$ = NULL; }
            ;
            
params			:	  param_lista { $$ = $1; }
                | VOID_TYPE { $$ = NULL; }
            ;

param_lista		:	  param { $$ = $1; }
                | param_lista COMMA param { 
                    $1->next = $3; 
                    $$ = $1; 
                }
            ;

param			:	  tipo_especificador IDENTIFIER { 
                    $$ = create_var_declaration_node($2, $1, line_number);
                }
                | tipo_especificador IDENTIFIER OPEN_BRACKET CLOSE_BRACKET {
                    ASTNode *node = create_var_declaration_node($2, $1, line_number);
                    node->data.var_decl.array_size = -1; /* Array parameter */
                    $$ = node;
                }
                | tipo_especificador IDENTIFIER OPEN_BRACKET error { yyerror("Esperado ']' após '[' no parâmetro array"); yyerrok; $$ = NULL; }
            ;
            
composto_decl        :      OPEN_BRACE local_declaracoes comando_lista temp
            ;

temp        :      CLOSE_BRACE
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
            
retorno_decl		:	  RETURN_KEYWORD SEMICOLON
                | RETURN_KEYWORD expressao SEMICOLON
                | RETURN_KEYWORD expressao error { yyerror("Esperado ';' após return"); yyerrok; }
            ;	
            
expressao		:	  var ASSIGN_OP expressao          { 
                    $$ = create_binary_op_node(OP_ASSIGN, $1, $3, line_number);
                }
                | expressao_simples                   { $$ = $1; }
            ;
            
var			:	  IDENTIFIER                      { 
                    $$ = create_identifier_node($1, line_number);
                }
                | IDENTIFIER OPEN_BRACKET expressao CLOSE_BRACKET arranjo_acesso { 
                    ASTNode *array_node = create_identifier_node($1, line_number);
                    array_node->node_type = NODE_ARRAY_ACCESS;
                    array_node->data.var_ref.name = $1;
                    array_node->data.var_ref.index = $3;
                    $$ = array_node;
                }
                | IDENTIFIER OPEN_BRACKET expressao error arranjo_acesso { yyerror("Esperado ']' após índice do array"); yyerrok; $$ = NULL; }
                | IDENTIFIER OPEN_BRACKET error CLOSE_BRACKET arranjo_acesso { yyerror("Índice inválido no array"); yyerrok; $$ = NULL; }
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
                
fator			:	  OPEN_PAREN expressao CLOSE_PAREN { $$ = $2; }
                        | var                             { $$ = $1; }
                        | ativacao                        { $$ = $1; }
                        | REAL_NUMBER                     { 
                            float val = $1;
                            $$ = create_constant_node(TYPE_FLOAT, &val, line_number);
                        }
                        | INT_NUMBER                      { 
                            int val = $1;
                            $$ = create_constant_node(TYPE_INT, &val, line_number);
                        }
                        | OPEN_PAREN expressao error { yyerror("Esperado ')' após expressão"); yyerrok; $$ = NULL; }
                        | OPEN_PAREN error CLOSE_PAREN { yyerror("Expressão inválida entre parênteses"); yyerrok; $$ = NULL; }
                    ;

ativacao		:	  IDENTIFIER OPEN_PAREN args CLOSE_PAREN { 
                    $$ = create_call_node($1, $3, line_number);
                }
                | IDENTIFIER OPEN_PAREN args error { yyerror("Esperado ')' após argumentos da função"); yyerrok; $$ = NULL; }
            ;
            
args			:	  /* empty */                     { $$ = NULL; }
                        | arg_lista                       { $$ = $1; }
            ;
            
arg_lista		:	  expressao                       { $$ = $1; }
                        | arg_lista COMMA expressao        { 
                            $1->next = $3; 
                            $$ = $1; 
                        }
            ;

arranjo_dimensao		:	  /* empty */ { $$ = NULL; }
                | arranjo_dimensao OPEN_BRACKET INT_NUMBER CLOSE_BRACKET { $$ = NULL; /* TODO: handle multi-dim arrays */ }
                | arranjo_dimensao OPEN_BRACKET INT_NUMBER error { yyerror("Esperado ']' após dimensão do array"); yyerrok; $$ = NULL; }
                | arranjo_dimensao OPEN_BRACKET error CLOSE_BRACKET { yyerror("Dimensão inválida no array"); yyerrok; $$ = NULL; }
            ;

arranjo_acesso		:	  /* empty */ { $$ = NULL; }
                | arranjo_acesso OPEN_BRACKET expressao CLOSE_BRACKET { $$ = NULL; /* TODO: handle multi-dim access */ }
                | arranjo_acesso OPEN_BRACKET expressao error { yyerror("Esperado ']' após índice do array multidimensional"); yyerrok; $$ = NULL; }
                | arranjo_acesso OPEN_BRACKET error CLOSE_BRACKET { yyerror("Índice inválido no array multidimensional"); yyerrok; $$ = NULL; }
            ;

composto_decl        :      OPEN_BRACE local_declaracoes comando_lista temp { 
                        /* TODO: Create compound statement node */
                        $$ = $3; /* For now, just return the statement list */
                    }
            ;

temp        :      CLOSE_BRACE { $$ = NULL; }
            | error { yyerror("Esperado '}' para fechar bloco de comandos"); yyerrok; $$ = NULL; }
            ;

local_declaracoes	:	  /* empty */ { $$ = NULL; }
                | local_declaracoes var_declaracao { 
                    if ($1 == NULL) {
                        $$ = $2;
                    } else {
                        $1->next = $2; 
                        $$ = $1; 
                    }
                }
            ;
            
comando_lista		:	  /* empty */ { $$ = NULL; }
                | comando_lista comando { 
                    if ($1 == NULL) {
                        $$ = $2;
                    } else {
                        $1->next = $2; 
                        $$ = $1; 
                    }
                }
            ;
            
comando			:	  expressao_decl { $$ = $1; }
                | composto_decl	{ $$ = $1; }
                | selecao_decl { $$ = $1; }
                | iteracao_decl { $$ = $1; }
                | retorno_decl { $$ = $1; }
            ;

expressao_decl		:	  expressao SEMICOLON { $$ = $1; }
                | SEMICOLON { $$ = NULL; }
                | expressao error { yyerror("Esperado ';' após expressão"); yyerrok; $$ = NULL; }
            ;
            
selecao_decl		:	  IF_KEYWORD OPEN_PAREN expressao CLOSE_PAREN comando %prec LOWER { 
                    /* TODO: Create selection statement node */
                    $$ = $5;
                }
                | IF_KEYWORD OPEN_PAREN expressao CLOSE_PAREN comando ELSE_KEYWORD comando { 
                    /* TODO: Create if-else statement node */
                    $$ = $5;
                }
                | IF_KEYWORD OPEN_PAREN expressao error comando { yyerror("Esperado ')' após condição do if"); yyerrok; $$ = NULL; }
                | IF_KEYWORD OPEN_PAREN error CLOSE_PAREN comando { yyerror("Expressão inválida na condição do if"); yyerrok; $$ = NULL; }
                | IF_KEYWORD error { yyerror("Esperado '(' após if"); yyerrok; $$ = NULL; }
            ;
            
iteracao_decl		:	  WHILE_KEYWORD OPEN_PAREN expressao CLOSE_PAREN comando {
                    /* TODO: Create iteration statement node */
                    $$ = $5;
                }
                | WHILE_KEYWORD OPEN_PAREN expressao error comando { 
                    yyerror("Esperado ')' após condição do while"); 
                    yyerrok; 
                    $$ = NULL;
                }
                | WHILE_KEYWORD OPEN_PAREN error CLOSE_PAREN comando { 
                    yyerror("Expressão inválida na condição do while"); 
                    yyerrok; 
                    $$ = NULL;
                }
                | WHILE_KEYWORD error { 
                    yyerror("Esperado '(' após while"); 
                    yyerrok; 
                    $$ = NULL;
                }
            ;
            
retorno_decl		:	  RETURN_KEYWORD SEMICOLON { 
                    /* TODO: Create return statement node */
                    $$ = NULL;
                }
                | RETURN_KEYWORD expressao SEMICOLON {
                    /* TODO: Create return statement node with expression */
                    $$ = $2;
                }
                | RETURN_KEYWORD expressao error { yyerror("Esperado ';' após return"); yyerrok; $$ = NULL; }
            ;

expressao_simples	:	  expressao_soma { $$ = $1; }
                        | expressao_soma relacional expressao_soma { 
                            $$ = create_binary_op_node($2, $1, $3, line_number);
                        }
            ;
            
relacional		:	  LE_OP { $$ = OP_LE; }
                | LT_OP { $$ = OP_LT; }
                | GT_OP { $$ = OP_GT; }
                | GE_OP { $$ = OP_GE; }
                | EQUAL_OP { $$ = OP_EQ; }
                | NE_OP { $$ = OP_NE; }
            ;

expressao_soma		:	  termo { $$ = $1; }
                        | expressao_soma soma_op termo { 
                            $$ = create_binary_op_node($2, $1, $3, line_number);
                        }
            ;
            
soma_op			:	  PLUS_OP { $$ = OP_ADD; }
                | MINUS_OP { $$ = OP_SUB; }
            ;				
            
termo			:	  fator { $$ = $1; }
                        | termo mult_op fator { 
                            $$ = create_binary_op_node($2, $1, $3, line_number);
                        }
            ;
                            
mult_op			:	  MULT_OP { $$ = OP_MUL; }
                | DIV_OP { $$ = OP_DIV; }
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