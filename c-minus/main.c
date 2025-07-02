/* 
 * Programa principal do Compilador C- com Análise Semântica
 * Autores: Guilherme Fabricio, Harisson Alvarenga, Raul Carvalho
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic/semantic.h"

extern FILE *yyin;
extern int yydebug;
extern int yyparse(void);
extern int line_number;
extern int column_number; 
extern int errors_count;

/* Função para simular análise semântica básica */
void simulate_semantic_analysis(const char *filename) {
    printf("\n==================================================\n");
    printf("INICIANDO ANÁLISE SEMÂNTICA\n");
    printf("==================================================\n");
    
    init_semantic_analysis();
    
    if (get_semantic_context() == NULL) {
        printf("Erro: Não foi possível inicializar contexto semântico\n");
        return;
    }
    
    /* Simula algumas declarações para testar */
    SymbolTable *st = get_symbol_table();
    if (st == NULL) {
        printf("Erro: Tabela de símbolos não inicializada\n");
        return;
    }
    
    printf(">>> Inserindo símbolos de teste na tabela...\n");
    
    /* Insere algumas variáveis */
    insert_symbol(st, "x", TYPE_INT, SYMBOL_VARIABLE, 1);
    insert_symbol(st, "y", TYPE_INT, SYMBOL_VARIABLE, 2);
    insert_symbol(st, "z", TYPE_FLOAT, SYMBOL_VARIABLE, 3);
    
    /* Insere uma função */
    insert_symbol(st, "main", TYPE_INT, SYMBOL_FUNCTION, 4);
    insert_symbol(st, "soma", TYPE_INT, SYMBOL_FUNCTION, 10);
    insert_symbol(st, "multiplicacao", TYPE_FLOAT, SYMBOL_FUNCTION, 15);
    
    printf(">>> Símbolos inseridos com sucesso!\n");
    
    /* Simula geração de código */
    InstructionList *code = get_instruction_list();
    if (code == NULL) {
        printf("Erro: Lista de instruções não inicializada\n");
        finalize_semantic_analysis();
        return;
    }
    
    printf(">>> Gerando código de três endereços...\n");
    
    /* x = 10 */
    Address *var_x = create_var_address("x");
    Address *const_10 = create_int_const_address(10);
    emit_assign(code, var_x, const_10);
    
    /* y = x + 5 */
    Address *var_y = create_var_address("y");
    Address *const_5 = create_int_const_address(5);
    int temp1 = get_new_temp(code);
    Address *temp1_addr = create_temp_address(temp1);
    emit_binary_op(code, OP_ADD, temp1_addr, var_x, const_5);
    emit_assign(code, var_y, temp1_addr);
    
    printf(">>> Código gerado com sucesso!\n");
    
    finalize_semantic_analysis();
    
    /* Limpa memória - simplificado */
    printf(">>> Limpando memória...\n");
    
    printf(">>> Análise semântica concluída!\n");
}

int main(int argc, char *argv[]) {
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
    yydebug = 0; /* Desabilita debug do parser por padrão */
    errors_count = 0;
    
    printf("==================================================\n");
    printf("COMPILADOR C- - ETAPA 3: ANÁLISE SEMÂNTICA\n");
    printf("==================================================\n");
    printf("Arquivo de entrada: %s\n", argv[1]);
    printf("\n>>> Iniciando análise sintática...\n");
    
    int result = yyparse();
    
    if (errors_count == 0) {
        printf("\n>>> Análise sintática concluída com sucesso!\n");
        
        /* A análise semântica já é executada durante o parsing */
        /* simulate_semantic_analysis(argv[1]); */
        
    } else {
        printf("\n>>> Análise sintática concluída com %d erro(s).\n", errors_count);
        printf(">>> Pulando análise semântica devido a erros sintáticos.\n");
    }

    fclose(input_file);

    printf("\n==================================================\n");
    printf("COMPILAÇÃO FINALIZADA\n");
    printf("==================================================\n");

    return result;
}
