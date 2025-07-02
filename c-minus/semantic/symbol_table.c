#include "symbol_table.h"
#include "utils.h"
#define _GNU_SOURCE
#include <string.h>

#define HASH_SIZE 211  /* Número primo para melhor distribuição */

/* Tabela de símbolos global */
static SymbolTable *global_symbol_table = NULL;

/**
 * Cria uma nova tabela de símbolos
 */
SymbolTable* create_symbol_table(int size) {
    SymbolTable *st = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (!st) {
        fprintf(stderr, "Erro: Não foi possível alocar memória para tabela de símbolos\n");
        return NULL;
    }
    
    st->table = (SymbolEntry**)calloc(size, sizeof(SymbolEntry*));
    if (!st->table) {
        fprintf(stderr, "Erro: Não foi possível alocar memória para entradas da tabela\n");
        free(st);
        return NULL;
    }
    
    st->size = size;
    st->current_scope = 0;
    st->next_address = 0;
    
    return st;
}

/**
 * Destrói a tabela de símbolos e libera memória
 */
void destroy_symbol_table(SymbolTable *st) {
    if (!st) return;
    
    for (int i = 0; i < st->size; i++) {
        SymbolEntry *current = st->table[i];
        while (current) {
            SymbolEntry *temp = current;
            current = current->next;
            
            /* Libera memória específica do tipo */
            if (temp->category == SYMBOL_FUNCTION && temp->info.function_info.param_count > 0) {
                free(temp->info.function_info.param_types);
                for (int j = 0; j < temp->info.function_info.param_count; j++) {
                    free(temp->info.function_info.param_names[j]);
                }
                free(temp->info.function_info.param_names);
            }
            
            if (temp->type == TYPE_ARRAY && temp->info.array_info.dimensions > 0) {
                free(temp->info.array_info.sizes);
            }
            
            if (temp->category == SYMBOL_STRUCT_TYPE && temp->info.struct_info.field_count > 0) {
                for (int j = 0; j < temp->info.struct_info.field_count; j++) {
                    free(temp->info.struct_info.field_names[j]);
                }
                free(temp->info.struct_info.field_names);
                free(temp->info.struct_info.field_types);
            }
            
            free(temp->name);
            free(temp);
        }
    }
    
    free(st->table);
    free(st);
}

/**
 * Função hash simples
 */
unsigned int hash_function(const char *name, int table_size) {
    unsigned int hash = 0;
    while (*name) {
        hash = (hash * 31 + *name++) % table_size;
    }
    return hash;
}

/**
 * Cria uma nova entrada na tabela de símbolos
 */
SymbolEntry* create_symbol_entry(const char *name, DataType type, SymbolCategory category, int line) {
    SymbolEntry *entry = (SymbolEntry*)malloc(sizeof(SymbolEntry));
    if (!entry) {
        fprintf(stderr, "Erro: Não foi possível alocar memória para entrada de símbolo\n");
        return NULL;
    }
    
    entry->name = strdup(name);
    entry->type = type;
    entry->category = category;
    entry->scope_level = global_symbol_table ? global_symbol_table->current_scope : 0;
    entry->address = -1;  /* Será definido posteriormente */
    entry->line_declared = line;
    entry->next = NULL;
    
    /* Inicializa informações específicas */
    memset(&entry->info, 0, sizeof(entry->info));
    
    return entry;
}

/**
 * Insere um símbolo na tabela
 */
int insert_symbol(SymbolTable *st, const char *name, DataType type, SymbolCategory category, int line) {
    if (!st || !name) return 0;
    
    /* Verifica se o símbolo já existe no escopo atual */
    SymbolEntry *existing = lookup_symbol_current_scope(st, name);
    if (existing) {
        fprintf(stderr, "Erro semântico na linha %d: Identificador '%s' já declarado na linha %d\n", 
                line, name, existing->line_declared);
        return 0;
    }
    
    /* Cria nova entrada */
    SymbolEntry *entry = create_symbol_entry(name, type, category, line);
    if (!entry) return 0;
    
    /* Define endereço para variáveis */
    if (category == SYMBOL_VARIABLE || category == SYMBOL_PARAMETER) {
        entry->address = st->next_address++;
    }
    
    /* Insere na tabela hash */
    unsigned int index = hash_function(name, st->size);
    entry->next = st->table[index];
    st->table[index] = entry;
    
    return 1;
}

/**
 * Busca um símbolo na tabela (todos os escopos)
 */
SymbolEntry* lookup_symbol(SymbolTable *st, const char *name) {
    if (!st || !name) return NULL;
    
    unsigned int index = hash_function(name, st->size);
    SymbolEntry *current = st->table[index];
    
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

/**
 * Busca um símbolo apenas no escopo atual
 */
SymbolEntry* lookup_symbol_current_scope(SymbolTable *st, const char *name) {
    if (!st || !name) return NULL;
    
    unsigned int index = hash_function(name, st->size);
    SymbolEntry *current = st->table[index];
    
    while (current) {
        if (strcmp(current->name, name) == 0 && current->scope_level == st->current_scope) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

/**
 * Entra em um novo escopo
 */
void enter_scope(SymbolTable *st) {
    if (st) {
        st->current_scope++;
        printf(">>> Entrando no escopo %d\n", st->current_scope);
    }
}

/**
 * Sai do escopo atual e remove símbolos do escopo
 */
void exit_scope(SymbolTable *st) {
    if (!st || st->current_scope <= 0) return;
    
    printf(">>> Saindo do escopo %d\n", st->current_scope);
    
    /* Remove símbolos do escopo atual */
    for (int i = 0; i < st->size; i++) {
        SymbolEntry **current = &st->table[i];
        
        while (*current) {
            if ((*current)->scope_level == st->current_scope) {
                SymbolEntry *to_remove = *current;
                *current = (*current)->next;
                
                /* Libera memória da entrada removida */
                free(to_remove->name);
                free(to_remove);
            } else {
                current = &(*current)->next;
            }
        }
    }
    
    st->current_scope--;
}

/**
 * Imprime a tabela de símbolos
 */
void print_symbol_table(SymbolTable *st) {
    if (!st) return;
    
    printf("\n=== TABELA DE SÍMBOLOS ===\n");
    printf("%-15s %-10s %-12s %-8s %-8s %-8s\n", 
           "Nome", "Tipo", "Categoria", "Escopo", "Endereço", "Linha");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < st->size; i++) {
        SymbolEntry *current = st->table[i];
        while (current) {
            printf("%-15s %-10s %-12s %-8d %-8d %-8d\n",
                   current->name,
                   type_to_string(current->type),
                   category_to_string(current->category),
                   current->scope_level,
                   current->address,
                   current->line_declared);
            current = current->next;
        }
    }
    printf("=========================\n\n");
}

/**
 * Converte tipo de dados para string
 */
const char* type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_CHAR: return "char";
        case TYPE_VOID: return "void";
        case TYPE_STRUCT: return "struct";
        case TYPE_ARRAY: return "array";
        case TYPE_FUNCTION: return "function";
        case TYPE_ERROR: return "error";
        default: return "unknown";
    }
}

/**
 * Converte categoria de símbolo para string
 */
const char* category_to_string(SymbolCategory category) {
    switch (category) {
        case SYMBOL_VARIABLE: return "variable";
        case SYMBOL_FUNCTION: return "function";
        case SYMBOL_PARAMETER: return "parameter";
        case SYMBOL_STRUCT_TYPE: return "struct_type";
        default: return "unknown";
    }
}

/**
 * Define informações de array
 */
void set_array_info(SymbolEntry *entry, int dimensions, int *sizes, DataType element_type) {
    if (!entry || dimensions <= 0) return;
    
    entry->info.array_info.dimensions = dimensions;
    entry->info.array_info.element_type = element_type;
    entry->info.array_info.sizes = (int*)malloc(dimensions * sizeof(int));
    
    if (entry->info.array_info.sizes && sizes) {
        memcpy(entry->info.array_info.sizes, sizes, dimensions * sizeof(int));
    }
}

/**
 * Define informações de função
 */
void set_function_info(SymbolEntry *entry, DataType return_type, int param_count, 
                      DataType *param_types, char **param_names) {
    if (!entry) return;
    
    entry->info.function_info.return_type = return_type;
    entry->info.function_info.param_count = param_count;
    
    if (param_count > 0 && param_types) {
        entry->info.function_info.param_types = (DataType*)malloc(param_count * sizeof(DataType));
        memcpy(entry->info.function_info.param_types, param_types, param_count * sizeof(DataType));
        
        if (param_names) {
            entry->info.function_info.param_names = (char**)malloc(param_count * sizeof(char*));
            for (int i = 0; i < param_count; i++) {
                entry->info.function_info.param_names[i] = param_names[i] ? strdup(param_names[i]) : NULL;
            }
        }
    }
}

/**
 * Define informações de struct
 */
void set_struct_info(SymbolEntry *entry, int field_count, char **field_names, DataType *field_types) {
    if (!entry || field_count <= 0) return;
    
    entry->info.struct_info.field_count = field_count;
    
    if (field_names) {
        entry->info.struct_info.field_names = (char**)malloc(field_count * sizeof(char*));
        for (int i = 0; i < field_count; i++) {
            entry->info.struct_info.field_names[i] = field_names[i] ? strdup(field_names[i]) : NULL;
        }
    }
    
    if (field_types) {
        entry->info.struct_info.field_types = (DataType*)malloc(field_count * sizeof(DataType));
        memcpy(entry->info.struct_info.field_types, field_types, field_count * sizeof(DataType));
    }
}

/**
 * Inicializa a tabela de símbolos global
 */
void init_symbol_table(void) {
    global_symbol_table = create_symbol_table(HASH_SIZE);
    if (!global_symbol_table) {
        fprintf(stderr, "Erro fatal: Não foi possível criar tabela de símbolos\n");
        exit(1);
    }
}

/**
 * Finaliza a tabela de símbolos global
 */
void finalize_symbol_table(void) {
    if (global_symbol_table) {
        destroy_symbol_table(global_symbol_table);
        global_symbol_table = NULL;
    }
}

/**
 * Obtém a tabela de símbolos global
 */
SymbolTable* get_symbol_table(void) {
    return global_symbol_table;
}
