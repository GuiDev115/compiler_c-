#include "symbol_table.h"
#include <string.h>

// Variável global para a tabela de símbolos
SymbolTable* global_symbol_table = NULL;

// Cria uma nova tabela de símbolos
SymbolTable* create_symbol_table() {
    SymbolTable* st = (SymbolTable*)malloc(sizeof(SymbolTable));
    if (!st) {
        fprintf(stderr, "Erro: Não foi possível alocar memória para a tabela de símbolos\n");
        return NULL;
    }
    
    // Inicializa a tabela hash
    for (int i = 0; i < HASH_SIZE; i++) {
        st->table[i] = NULL;
    }
    
    st->current_scope = 0;
    st->scope_top = -1;
    st->current_address = 0;
    
    return st;
}

// Destrói a tabela de símbolos
void destroy_symbol_table(SymbolTable* st) {
    if (!st) return;
    
    for (int i = 0; i < HASH_SIZE; i++) {
        SymbolEntry* entry = st->table[i];
        while (entry) {
            SymbolEntry* temp = entry;
            entry = entry->next;
            
            free(temp->name);
            if (temp->struct_name) free(temp->struct_name);
            
            // Libera dimensões do array
            ArrayDim* dim = temp->dimensions;
            while (dim) {
                ArrayDim* temp_dim = dim;
                dim = dim->next;
                free(temp_dim);
            }
            
            // Libera parâmetros
            Parameter* param = temp->parameters;
            while (param) {
                Parameter* temp_param = param;
                param = param->next;
                free(temp_param->name);
                free(temp_param);
            }
            
            // Libera atributos do struct
            StructAttr* attr = temp->struct_attrs;
            while (attr) {
                StructAttr* temp_attr = attr;
                attr = attr->next;
                free(temp_attr->name);
                
                ArrayDim* attr_dim = temp_attr->dimensions;
                while (attr_dim) {
                    ArrayDim* temp_attr_dim = attr_dim;
                    attr_dim = attr_dim->next;
                    free(temp_attr_dim);
                }
                
                free(temp_attr);
            }
            
            free(temp);
        }
    }
    
    free(st);
}

// Função hash simples
unsigned int hash(const char* str) {
    unsigned int hash_value = 0;
    while (*str) {
        hash_value = (hash_value << 5) + *str;
        str++;
    }
    return hash_value % HASH_SIZE;
}

// Entra em um novo escopo
void enter_scope(SymbolTable* st) {
    if (st->scope_top >= MAX_SCOPE_DEPTH - 1) {
        fprintf(stderr, "Erro: Profundidade máxima de escopo excedida\n");
        return;
    }
    
    st->scope_stack[++st->scope_top] = st->current_scope;
    st->address_stack[st->scope_top] = st->current_address;
    st->current_scope++;
    st->current_address = 0;
}

// Sai do escopo atual
void exit_scope(SymbolTable* st) {
    if (st->scope_top < 0) {
        fprintf(stderr, "Erro: Tentativa de sair do escopo global\n");
        return;
    }
    
    // Remove símbolos do escopo atual
    for (int i = 0; i < HASH_SIZE; i++) {
        SymbolEntry* entry = st->table[i];
        SymbolEntry* prev = NULL;
        
        while (entry) {
            if (entry->scope_level == st->current_scope) {
                if (prev) {
                    prev->next = entry->next;
                } else {
                    st->table[i] = entry->next;
                }
                
                SymbolEntry* temp = entry;
                entry = entry->next;
                
                free(temp->name);
                if (temp->struct_name) free(temp->struct_name);
                
                // Libera dimensões do array
                ArrayDim* dim = temp->dimensions;
                while (dim) {
                    ArrayDim* temp_dim = dim;
                    dim = dim->next;
                    free(temp_dim);
                }
                
                // Libera parâmetros
                Parameter* param = temp->parameters;
                while (param) {
                    Parameter* temp_param = param;
                    param = param->next;
                    free(temp_param->name);
                    free(temp_param);
                }
                
                // Libera atributos do struct
                StructAttr* attr = temp->struct_attrs;
                while (attr) {
                    StructAttr* temp_attr = attr;
                    attr = attr->next;
                    free(temp_attr->name);
                    
                    ArrayDim* attr_dim = temp_attr->dimensions;
                    while (attr_dim) {
                        ArrayDim* temp_attr_dim = attr_dim;
                        attr_dim = attr_dim->next;
                        free(temp_attr_dim);
                    }
                    
                    free(temp_attr);
                }
                
                free(temp);
            } else {
                prev = entry;
                entry = entry->next;
            }
        }
    }
    
    st->current_scope = st->scope_stack[st->scope_top];
    st->current_address = st->address_stack[st->scope_top];
    st->scope_top--;
}

// Insere um símbolo na tabela
SymbolEntry* insert_symbol(SymbolTable* st, const char* name, SymbolType symbol_type, 
                          DataType data_type, int line) {
    if (!st || !name) return NULL;
    
    // Verifica se o símbolo já existe no escopo atual
    if (lookup_symbol_current_scope(st, name)) {
        return NULL; // Símbolo já declarado no escopo atual
    }
    
    unsigned int index = hash(name);
    
    SymbolEntry* entry = (SymbolEntry*)malloc(sizeof(SymbolEntry));
    if (!entry) {
        fprintf(stderr, "Erro: Não foi possível alocar memória para entrada da tabela\n");
        return NULL;
    }
    
    entry->name = strdup(name);
    entry->symbol_type = symbol_type;
    entry->data_type = data_type;
    entry->scope_level = st->current_scope;
    entry->line_declared = line;
    entry->address = st->current_address++;
    entry->is_array = 0;
    entry->dimensions = NULL;
    entry->parameters = NULL;
    entry->param_count = 0;
    entry->struct_attrs = NULL;
    entry->struct_name = NULL;
    
    // Insere no início da lista ligada
    entry->next = st->table[index];
    st->table[index] = entry;
    
    return entry;
}

// Busca um símbolo na tabela (todos os escopos)
SymbolEntry* lookup_symbol(SymbolTable* st, const char* name) {
    if (!st || !name) return NULL;
    
    unsigned int index = hash(name);
    SymbolEntry* entry = st->table[index];
    
    while (entry) {
        if (strcmp(entry->name, name) == 0) {
            return entry;
        }
        entry = entry->next;
    }
    
    return NULL;
}

// Busca um símbolo apenas no escopo atual
SymbolEntry* lookup_symbol_current_scope(SymbolTable* st, const char* name) {
    if (!st || !name) return NULL;
    
    unsigned int index = hash(name);
    SymbolEntry* entry = st->table[index];
    
    while (entry) {
        if (strcmp(entry->name, name) == 0 && entry->scope_level == st->current_scope) {
            return entry;
        }
        entry = entry->next;
    }
    
    return NULL;
}

// Imprime a tabela de símbolos
void print_symbol_table(SymbolTable* st) {
    if (!st) return;
    
    printf("\n=== TABELA DE SÍMBOLOS ===\n");
    printf("%-15s %-10s %-10s %-6s %-6s %-10s\n", 
           "Nome", "Tipo", "DataType", "Escopo", "Linha", "Endereço");
    printf("================================================================\n");
    
    for (int i = 0; i < HASH_SIZE; i++) {
        SymbolEntry* entry = st->table[i];
        while (entry) {
            printf("%-15s %-10s %-10s %-6d %-6d %-10d", 
                   entry->name,
                   symbol_type_to_string(entry->symbol_type),
                   type_to_string(entry->data_type),
                   entry->scope_level,
                   entry->line_declared,
                   entry->address);
            
            if (entry->is_array) {
                printf(" [array]");
            }
            
            printf("\n");
            entry = entry->next;
        }
    }
    printf("================================================================\n");
}

// Converte tipo de dado para string
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

// Converte tipo de símbolo para string
const char* symbol_type_to_string(SymbolType type) {
    switch (type) {
        case SYMBOL_VAR: return "var";
        case SYMBOL_FUNC: return "func";
        case SYMBOL_PARAM: return "param";
        case SYMBOL_STRUCT: return "struct";
        default: return "unknown";
    }
}

// Cria uma nova dimensão de array
ArrayDim* create_array_dimension(int size) {
    ArrayDim* dim = (ArrayDim*)malloc(sizeof(ArrayDim));
    if (!dim) return NULL;
    
    dim->size = size;
    dim->next = NULL;
    return dim;
}

// Adiciona uma dimensão ao array
void add_array_dimension(SymbolEntry* entry, int size) {
    if (!entry) return;
    
    ArrayDim* new_dim = create_array_dimension(size);
    if (!new_dim) return;
    
    entry->is_array = 1;
    
    if (!entry->dimensions) {
        entry->dimensions = new_dim;
    } else {
        ArrayDim* current = entry->dimensions;
        while (current->next) {
            current = current->next;
        }
        current->next = new_dim;
    }
}

// Calcula o tamanho total do array
int calculate_array_size(ArrayDim* dimensions) {
    int total_size = 1;
    ArrayDim* current = dimensions;
    
    while (current) {
        total_size *= current->size;
        current = current->next;
    }
    
    return total_size;
}

// Cria um novo parâmetro
Parameter* create_parameter(const char* name, DataType type, int is_array) {
    Parameter* param = (Parameter*)malloc(sizeof(Parameter));
    if (!param) return NULL;
    
    param->name = strdup(name);
    param->type = type;
    param->is_array = is_array;
    param->next = NULL;
    
    return param;
}

// Adiciona um parâmetro à função
void add_parameter(SymbolEntry* func_entry, Parameter* param) {
    if (!func_entry || !param) return;
    
    if (!func_entry->parameters) {
        func_entry->parameters = param;
    } else {
        Parameter* current = func_entry->parameters;
        while (current->next) {
            current = current->next;
        }
        current->next = param;
    }
    
    func_entry->param_count++;
}

// Cria um novo atributo de struct
StructAttr* create_struct_attr(const char* name, DataType type, int is_array) {
    StructAttr* attr = (StructAttr*)malloc(sizeof(StructAttr));
    if (!attr) return NULL;
    
    attr->name = strdup(name);
    attr->type = type;
    attr->is_array = is_array;
    attr->dimensions = NULL;
    attr->offset = 0;
    attr->next = NULL;
    
    return attr;
}

// Adiciona um atributo ao struct
void add_struct_attr(SymbolEntry* struct_entry, StructAttr* attr) {
    if (!struct_entry || !attr) return;
    
    if (!struct_entry->struct_attrs) {
        struct_entry->struct_attrs = attr;
    } else {
        StructAttr* current = struct_entry->struct_attrs;
        while (current->next) {
            current = current->next;
        }
        current->next = attr;
    }
}
