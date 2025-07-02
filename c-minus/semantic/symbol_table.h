#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tipos de dados suportados */
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

/* Categorias de símbolos */
typedef enum {
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_PARAMETER,
    SYMBOL_STRUCT_TYPE
} SymbolCategory;

/* Estrutura para informações de array */
typedef struct ArrayInfo {
    int dimensions;
    int *sizes;
    DataType element_type;
} ArrayInfo;

/* Estrutura para informações de função */
typedef struct FunctionInfo {
    DataType return_type;
    int param_count;
    DataType *param_types;
    char **param_names;
} FunctionInfo;

/* Estrutura para informações de struct */
typedef struct StructInfo {
    int field_count;
    char **field_names;
    DataType *field_types;
} StructInfo;

/* Entrada da tabela de símbolos */
typedef struct SymbolEntry {
    char *name;
    DataType type;
    SymbolCategory category;
    int scope_level;
    int address;           /* Endereço relativo */
    int line_declared;     /* Linha onde foi declarado */
    
    /* Informações específicas do tipo */
    union {
        ArrayInfo array_info;
        FunctionInfo function_info;
        StructInfo struct_info;
    } info;
    
    struct SymbolEntry *next;  /* Para colisões no hash */
} SymbolEntry;

/* Tabela de símbolos */
typedef struct SymbolTable {
    SymbolEntry **table;
    int size;
    int current_scope;
    int next_address;
} SymbolTable;

/* Protótipos das funções */
SymbolTable* create_symbol_table(int size);
void destroy_symbol_table(SymbolTable *st);
unsigned int hash_function(const char *name, int table_size);
SymbolEntry* create_symbol_entry(const char *name, DataType type, SymbolCategory category, int line);
int insert_symbol(SymbolTable *st, const char *name, DataType type, SymbolCategory category, int line);
SymbolEntry* lookup_symbol(SymbolTable *st, const char *name);
SymbolEntry* lookup_symbol_current_scope(SymbolTable *st, const char *name);
void enter_scope(SymbolTable *st);
void exit_scope(SymbolTable *st);
void print_symbol_table(SymbolTable *st);
const char* type_to_string(DataType type);
const char* category_to_string(SymbolCategory category);

/* Funções para arrays */
void set_array_info(SymbolEntry *entry, int dimensions, int *sizes, DataType element_type);

/* Funções para funções */
void set_function_info(SymbolEntry *entry, DataType return_type, int param_count, 
                      DataType *param_types, char **param_names);

/* Funções para structs */
void set_struct_info(SymbolEntry *entry, int field_count, char **field_names, DataType *field_types);

#endif /* SYMBOL_TABLE_H */
