#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variáveis globais para análise semântica
extern SymbolTable* global_symbol_table;
extern int semantic_errors;
extern int line_number;

// Estrutura para informações de expressão
typedef struct {
    DataType type;
    int is_array;
    int is_lvalue;
    char* temp_var;  // Para geração de código intermediário
} ExprInfo;

// Funções de análise semântica
void init_semantic_analysis();
void finish_semantic_analysis();

// Verificação de tipos
DataType check_binary_op(DataType left, DataType right, const char* op, int line);
DataType check_assignment(DataType left, DataType right, int line);
DataType check_array_access(const char* array_name, int line);
DataType check_function_call(const char* func_name, int line);

// Declarações
void declare_variable(const char* name, DataType type, int is_array, int line);
void declare_function(const char* name, DataType return_type, int line);
void declare_struct(const char* name, int line);

// Verificações de escopo
void check_variable_declaration(const char* name, int line);
void check_variable_usage(const char* name, int line);
void check_function_declaration(const char* name, int line);

// Utilitários
void semantic_error(const char* message, int line);
void semantic_warning(const char* message, int line);
int are_types_compatible(DataType type1, DataType type2);
DataType get_variable_type(const char* name);

// Funções para conversão de tokens para tipos
DataType token_to_type(int token);

#endif
