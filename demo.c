/* 
 * Demonstração do Compilador C-
 * Sistema de Análise Semântica e Geração de Código Intermediário
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c-minus/semantic/symbol_table.h"
#include "c-minus/semantic/semantic.h"
#include "c-minus/semantic/code_generator.h"
#include "c-minus/semantic/utils.h"

// Simula uma análise sintática básica
void demonstrate_compiler() {
    printf("=== DEMONSTRAÇÃO DO COMPILADOR C- ===\n\n");
    
    // Inicializa os subsistemas
    init_semantic_analysis();
    init_code_generation();
    
    printf("1. DECLARAÇÕES DE VARIÁVEIS:\n");
    // Simula: int x;
    declare_variable("x", TYPE_INT, 0, 1);
    
    // Simula: float y[10];
    declare_variable("y", TYPE_FLOAT, 1, 2);
    SymbolEntry* array_entry = lookup_symbol(global_symbol_table, "y");
    if (array_entry) {
        add_array_dimension(array_entry, 10);
    }
    
    // Simula: char nome;
    declare_variable("nome", TYPE_CHAR, 0, 3);
    
    printf("\n2. DECLARAÇÕES DE FUNÇÕES:\n");
    // Simula: int main()
    declare_function("main", TYPE_INT, 4);
    
    // Simula: float calcular(int a, float b)
    declare_function("calcular", TYPE_FLOAT, 5);
    
    printf("\n3. GERAÇÃO DE CÓDIGO INTERMEDIÁRIO:\n");
    
    // Simula: x = 42;
    emit_assignment("x", "42");
    
    // Simula: y[0] = 3.14;
    emit_array_assignment("y", "0", "3.14");
    
    // Simula: temp1 = x + 10;
    char* temp1 = new_temp();
    emit_binary_op("+", "x", "10", temp1);
    
    // Simula: temp2 = y[0] * 2.0;
    char* temp2 = new_temp();
    char* temp_array = new_temp();
    emit_array_access("y", "0", temp_array);
    emit_binary_op("*", temp_array, "2.0", temp2);
    
    // Simula: if (x > 0) goto L1;
    char* label1 = new_label();
    char* temp_cond = new_temp();
    emit_binary_op(">", "x", "0", temp_cond);
    emit_conditional_goto(temp_cond, label1);
    
    // Simula: goto L2;
    char* label2 = new_label();
    emit_goto(label2);
    
    // Simula: L1:
    emit_label(label1);
    
    // Simula: result = calcular(x, y[0]);
    char* temp_result = new_temp();
    emit_function_call("calcular", temp_result);
    
    // Simula: return result;
    emit_return(temp_result);
    
    // Simula: L2:
    emit_label(label2);
    
    // Simula: return 0;
    emit_return("0");
    
    printf("\n4. VERIFICAÇÕES SEMÂNTICAS:\n");
    
    // Verifica uso de variável não declarada
    printf("Verificando variável não declarada 'z':\n");
    check_variable_usage("z", 10);
    
    // Verifica tipos em operação
    printf("Verificando operação aritmética INT + FLOAT:\n");
    DataType result_type = check_binary_op(TYPE_INT, TYPE_FLOAT, "+", 11);
    printf("Resultado da operação: %s\n", type_to_string(result_type));
    
    // Verifica atribuição
    printf("Verificando atribuição INT = FLOAT:\n");
    DataType assign_type = check_assignment(TYPE_INT, TYPE_FLOAT, 12);
    printf("Tipo após atribuição: %s\n", type_to_string(assign_type));
    
    // Finaliza e mostra resultados
    finish_semantic_analysis();
    finish_code_generation();
    
    // Libera memória
    free(temp1);
    free(temp2);
    free(temp_array);
    free(temp_cond);
    free(temp_result);
    free(label1);
    free(label2);
}

int main() {
    printf("Compilador C- - Sistema de Análise Semântica e Geração de Código\n");
    printf("================================================================\n\n");
    
    demonstrate_compiler();
    
    printf("\n=== DEMONSTRAÇÃO CONCLUÍDA ===\n");
    printf("O sistema implementa:\n");
    printf("✓ Tabela de símbolos com hash table\n");
    printf("✓ Gerenciamento de escopo\n");
    printf("✓ Análise semântica de tipos\n");
    printf("✓ Geração de código intermediário de 3 endereços\n");
    printf("✓ Verificação de declarações e uso de variáveis\n");
    printf("✓ Suporte a arrays multidimensionais\n");
    printf("✓ Suporte a funções e structs\n");
    printf("✓ Tratamento de erros semânticos\n");
    
    return 0;
}
