#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para código de três endereços
typedef struct CodeLine {
    char* op;      // Operador
    char* arg1;    // Primeiro argumento
    char* arg2;    // Segundo argumento
    char* result;  // Resultado
    int line_num;  // Número da linha do código fonte
    struct CodeLine* next;
} CodeLine;

// Estrutura para geração de código
typedef struct {
    CodeLine* first;
    CodeLine* last;
    int temp_count;
    int label_count;
    FILE* output_file;
} CodeGenerator;

// Variáveis globais
extern CodeGenerator* global_code_gen;

// Funções principais
CodeGenerator* create_code_generator();
void destroy_code_generator(CodeGenerator* gen);
void init_code_generation();
void finish_code_generation();

// Geração de código
void emit_code(const char* op, const char* arg1, const char* arg2, const char* result);
void emit_assignment(const char* var, const char* value);
void emit_binary_op(const char* op, const char* arg1, const char* arg2, const char* result);
void emit_unary_op(const char* op, const char* arg, const char* result);
void emit_label(const char* label);
void emit_goto(const char* label);
void emit_conditional_goto(const char* condition, const char* label);
void emit_function_call(const char* func_name, const char* result);
void emit_return(const char* value);
void emit_array_access(const char* array, const char* index, const char* result);
void emit_array_assignment(const char* array, const char* index, const char* value);

// Geradores de temporários e labels
char* new_temp();
char* new_label();

// Utilitários
void print_code();
void save_code_to_file(const char* filename);
void optimize_code();

// Funções para expressões
char* generate_expression_code(const char* expr_type, const char* left, const char* op, const char* right);
char* generate_assignment_code(const char* var, const char* value);
char* generate_array_code(const char* array, const char* index);
char* generate_function_call_code(const char* func_name, int param_count);

// Processamento de expressões complexas
char* process_complex_expression(const char* expression);

#endif
