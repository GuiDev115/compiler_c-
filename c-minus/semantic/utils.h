#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura para pilha de strings
typedef struct StringStack {
    char** items;
    int top;
    int capacity;
} StringStack;

// Funções utilitárias para strings
char* safe_strdup(const char* str);
char* safe_strcat(const char* str1, const char* str2);
int safe_strcmp(const char* str1, const char* str2);
char* trim_whitespace(char* str);
int is_valid_identifier(const char* str);
int is_numeric(const char* str);

// Funções para pilha de strings
StringStack* create_string_stack(int capacity);
void destroy_string_stack(StringStack* stack);
int push_string(StringStack* stack, const char* str);
char* pop_string(StringStack* stack);
char* peek_string(StringStack* stack);
int is_stack_empty(StringStack* stack);
int is_stack_full(StringStack* stack);

// Funções para manipulação de arquivos
char* read_file_content(const char* filename);
int write_file_content(const char* filename, const char* content);
int file_exists(const char* filename);

// Funções para logging
void log_message(const char* level, const char* message);
void log_error(const char* message);
void log_warning(const char* message);
void log_info(const char* message);

// Funções para conversão de tipos
int string_to_int(const char* str, int* result);
int string_to_float(const char* str, float* result);
char* int_to_string(int value);
char* float_to_string(float value);

// Funções para validação
int validate_array_size(const char* size_str);
int validate_function_name(const char* name);
int validate_variable_name(const char* name);

#endif
