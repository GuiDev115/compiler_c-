/* 
 * Teste avançado do sistema de análise semântica
 * Demonstra diferentes aspectos do compilador C-
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c-minus/semantic/symbol_table.h"
#include "c-minus/semantic/semantic.h"
#include "c-minus/semantic/code_generator.h"
#include "c-minus/semantic/utils.h"

void test_advanced_features() {
    printf("=== TESTE AVANÇADO DO COMPILADOR C- ===\n\n");
    
    // Inicializa os subsistemas
    init_semantic_analysis();
    init_code_generation();
    
    printf("1. TESTE DE ESCOPO HIERÁRQUICO:\n");
    
    // Escopo global
    declare_variable("global_x", TYPE_INT, 0, 1);
    declare_variable("global_array", TYPE_FLOAT, 1, 2);
    
    // Adiciona dimensões ao array
    SymbolEntry* array_entry = lookup_symbol(global_symbol_table, "global_array");
    if (array_entry) {
        add_array_dimension(array_entry, 5);
        add_array_dimension(array_entry, 10);  // Array 2D: [5][10]
    }
    
    printf("Entrando no escopo de função...\n");
    enter_scope(global_symbol_table);
    
    // Escopo de função
    declare_variable("local_x", TYPE_INT, 0, 5);
    declare_variable("temp", TYPE_FLOAT, 0, 6);
    
    printf("Entrando no escopo de bloco...\n");
    enter_scope(global_symbol_table);
    
    // Escopo de bloco
    declare_variable("block_var", TYPE_CHAR, 0, 8);
    
    printf("Saindo do escopo de bloco...\n");
    exit_scope(global_symbol_table);
    
    printf("Saindo do escopo de função...\n");
    exit_scope(global_symbol_table);
    
    printf("\n2. TESTE DE ESTRUTURAS (STRUCTS):\n");
    
    // Declara um struct
    declare_struct("Pessoa", 10);
    SymbolEntry* struct_entry = lookup_symbol(global_symbol_table, "Pessoa");
    if (struct_entry) {
        // Adiciona atributos ao struct
        StructAttr* nome_attr = create_struct_attr("nome", TYPE_CHAR, 1);
        StructAttr* idade_attr = create_struct_attr("idade", TYPE_INT, 0);
        StructAttr* altura_attr = create_struct_attr("altura", TYPE_FLOAT, 0);
        
        add_struct_attr(struct_entry, nome_attr);
        add_struct_attr(struct_entry, idade_attr);
        add_struct_attr(struct_entry, altura_attr);
        
        printf("Struct 'Pessoa' criado com 3 atributos\n");
    }
    
    printf("\n3. TESTE DE FUNÇÕES COM PARÂMETROS:\n");
    
    // Declara função com parâmetros
    declare_function("calcular_media", TYPE_FLOAT, 12);
    SymbolEntry* func_entry = lookup_symbol(global_symbol_table, "calcular_media");
    if (func_entry) {
        Parameter* param1 = create_parameter("valores", TYPE_FLOAT, 1);  // array
        Parameter* param2 = create_parameter("count", TYPE_INT, 0);
        
        add_parameter(func_entry, param1);
        add_parameter(func_entry, param2);
        
        printf("Função 'calcular_media' criada com 2 parâmetros\n");
    }
    
    printf("\n4. TESTE DE GERAÇÃO DE CÓDIGO COMPLEXO:\n");
    
    // Simula: for (i = 0; i < 10; i++)
    char* loop_init = new_label();
    char* loop_cond = new_label();
    char* loop_end = new_label();
    
    // Inicialização
    emit_assignment("i", "0");
    emit_label(loop_init);
    
    // Condição
    char* cond_temp = new_temp();
    emit_binary_op("<", "i", "10", cond_temp);
    emit_conditional_goto(cond_temp, loop_cond);
    emit_goto(loop_end);
    
    // Corpo do loop
    emit_label(loop_cond);
    
    // Simula: sum += array[i]
    char* array_access = new_temp();
    char* sum_temp = new_temp();
    emit_array_access("global_array", "i", array_access);
    emit_binary_op("+", "sum", array_access, sum_temp);
    emit_assignment("sum", sum_temp);
    
    // Incremento
    char* inc_temp = new_temp();
    emit_binary_op("+", "i", "1", inc_temp);
    emit_assignment("i", inc_temp);
    emit_goto(loop_init);
    
    // Fim do loop
    emit_label(loop_end);
    
    // Simula: return sum / count
    char* div_temp = new_temp();
    emit_binary_op("/", "sum", "count", div_temp);
    emit_return(div_temp);
    
    printf("\n5. TESTE DE VERIFICAÇÕES SEMÂNTICAS:\n");
    
    // Testa diferentes verificações
    printf("Verificando operação INT * FLOAT:\n");
    DataType mult_type = check_binary_op(TYPE_INT, TYPE_FLOAT, "*", 25);
    printf("Resultado: %s\n", type_to_string(mult_type));
    
    printf("Verificando atribuição CHAR = INT:\n");
    DataType assign_type = check_assignment(TYPE_CHAR, TYPE_INT, 26);
    printf("Resultado: %s\n", type_to_string(assign_type));
    
    printf("Verificando acesso a array:\n");
    DataType array_type = check_array_access("global_array", 27);
    printf("Tipo do elemento: %s\n", type_to_string(array_type));
    
    printf("Verificando chamada de função:\n");
    DataType func_type = check_function_call("calcular_media", 28);
    printf("Tipo de retorno: %s\n", type_to_string(func_type));
    
    printf("\n6. TESTE DE VALIDAÇÕES:\n");
    
    // Testa validações
    printf("Validando identificador 'variavel_valida': %s\n", 
           validate_variable_name("variavel_valida") ? "VÁLIDO" : "INVÁLIDO");
    
    printf("Validando identificador '2invalid': %s\n", 
           validate_variable_name("2invalid") ? "VÁLIDO" : "INVÁLIDO");
    
    printf("Validando tamanho de array '5': %s\n", 
           validate_array_size("5") ? "VÁLIDO" : "INVÁLIDO");
    
    printf("Validando tamanho de array '-1': %s\n", 
           validate_array_size("-1") ? "VÁLIDO" : "INVÁLIDO");
    
    // Finaliza
    finish_semantic_analysis();
    finish_code_generation();
    
    // Libera memória
    free(loop_init);
    free(loop_cond);
    free(loop_end);
    free(cond_temp);
    free(array_access);
    free(sum_temp);
    free(inc_temp);
    free(div_temp);
}

int main() {
    printf("Compilador C- - Teste Avançado do Sistema\n");
    printf("=========================================\n\n");
    
    test_advanced_features();
    
    printf("\n=== TESTE CONCLUÍDO ===\n");
    printf("Sistema testado com sucesso!\n");
    
    return 0;
}
