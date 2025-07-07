#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE  // Para strdup
#endif
#ifndef _GNU_SOURCE
char* strdup(const char* s);
#endif

#define HASH_SIZE 211
#define MAX_SCOPE_DEPTH 100

// Tipos de dados da linguagem C-
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_VOID,
    TYPE_STRUCT,
    TYPE_ARRAY,
    TYPE_FUNCTION,
    TYPE_ERROR
} DataType;

// Tipos de símbolos
typedef enum {
    SYMBOL_VAR,
    SYMBOL_FUNC,
    SYMBOL_PARAM,
    SYMBOL_STRUCT
} SymbolType;

// Estrutura para dimensões de arrays
typedef struct ArrayDim {
    int size;
    struct ArrayDim* next;
} ArrayDim;

// Estrutura para parâmetros de função
typedef struct Parameter {
    char* name;
    DataType type;
    int is_array;
    struct Parameter* next;
} Parameter;

// Estrutura para atributos de struct
typedef struct StructAttr {
    char* name;
    DataType type;
    int is_array;
    ArrayDim* dimensions;
    int offset;
    struct StructAttr* next;
} StructAttr;

// Entrada da tabela de símbolos
typedef struct SymbolEntry {
    char* name;
    SymbolType symbol_type;
    DataType data_type;
    int scope_level;
    int line_declared;
    int address;  // Endereço relativo
    
    // Para arrays
    int is_array;
    ArrayDim* dimensions;
    
    // Para funções
    Parameter* parameters;
    int param_count;
    
    // Para structs
    StructAttr* struct_attrs;
    char* struct_name;
    
    struct SymbolEntry* next;
} SymbolEntry;

// Tabela de símbolos (hash table)
typedef struct {
    SymbolEntry* table[HASH_SIZE];
    int current_scope;
    int scope_stack[MAX_SCOPE_DEPTH];
    int scope_top;
    int current_address;
    int address_stack[MAX_SCOPE_DEPTH];
} SymbolTable;

// Funções da tabela de símbolos
SymbolTable* create_symbol_table();
void destroy_symbol_table(SymbolTable* st);
unsigned int hash(const char* str);

// Gerenciamento de escopo
void enter_scope(SymbolTable* st);
void exit_scope(SymbolTable* st);

// Operações com símbolos
SymbolEntry* insert_symbol(SymbolTable* st, const char* name, SymbolType symbol_type, 
                          DataType data_type, int line);
SymbolEntry* lookup_symbol(SymbolTable* st, const char* name);
SymbolEntry* lookup_symbol_current_scope(SymbolTable* st, const char* name);

// Funções auxiliares
void print_symbol_table(SymbolTable* st);
const char* type_to_string(DataType type);
const char* symbol_type_to_string(SymbolType type);

// Funções para arrays
ArrayDim* create_array_dimension(int size);
void add_array_dimension(SymbolEntry* entry, int size);
int calculate_array_size(ArrayDim* dimensions);

// Funções para funções
Parameter* create_parameter(const char* name, DataType type, int is_array);
void add_parameter(SymbolEntry* func_entry, Parameter* param);

// Funções para structs
StructAttr* create_struct_attr(const char* name, DataType type, int is_array);
void add_struct_attr(SymbolEntry* struct_entry, StructAttr* attr);

// Função para calcular tamanho de tipos em bytes
int get_type_size(DataType type);

#endif
