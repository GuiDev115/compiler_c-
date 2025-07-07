#include "semantic.h"
#include "symbol_table.h"

// Variáveis globais (declaradas em symbol_table.c)
extern SymbolTable* global_symbol_table;
int semantic_errors = 0;

// Inicializa a análise semântica
void init_semantic_analysis() {
    global_symbol_table = create_symbol_table();
    if (!global_symbol_table) {
        fprintf(stderr, "Erro: Não foi possível criar a tabela de símbolos\n");
        exit(1);
    }
    semantic_errors = 0;
    
    printf("Análise semântica iniciada...\n");
}

// Finaliza a análise semântica
void finish_semantic_analysis() {
    if (semantic_errors == 0) {
        printf("Análise semântica concluída sem erros.\n");
    } else {
        printf("Análise semântica concluída com %d erro(s) semântico(s).\n", semantic_errors);
    }
    
    print_symbol_table(global_symbol_table);
    destroy_symbol_table(global_symbol_table);
}

// Verifica operações binárias
DataType check_binary_op(DataType left, DataType right, const char* op, int line) {
    // Operações aritméticas
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 || 
        strcmp(op, "*") == 0 || strcmp(op, "/") == 0 || strcmp(op, "%") == 0) {
        
        if (left == TYPE_INT && right == TYPE_INT) {
            return TYPE_INT;
        } else if ((left == TYPE_INT || left == TYPE_FLOAT) && 
                   (right == TYPE_INT || right == TYPE_FLOAT)) {
            return TYPE_FLOAT;
        } else {
            semantic_error("Operação aritmética inválida entre tipos incompatíveis", line);
            return TYPE_ERROR;
        }
    }
    
    // Operações relacionais
    if (strcmp(op, "<") == 0 || strcmp(op, "<=") == 0 || 
        strcmp(op, ">") == 0 || strcmp(op, ">=") == 0 || 
        strcmp(op, "==") == 0 || strcmp(op, "!=") == 0) {
        
        if (are_types_compatible(left, right)) {
            return TYPE_INT; // Resultado booleano (representado como int)
        } else {
            semantic_error("Operação relacional inválida entre tipos incompatíveis", line);
            return TYPE_ERROR;
        }
    }
    
    semantic_error("Operador desconhecido", line);
    return TYPE_ERROR;
}

// Verifica atribuição
DataType check_assignment(DataType left, DataType right, int line) {
    if (are_types_compatible(left, right)) {
        return left;
    } else {
        semantic_error("Atribuição inválida: tipos incompatíveis", line);
        return TYPE_ERROR;
    }
}

// Verifica acesso a array
DataType check_array_access(const char* array_name, int line) {
    SymbolEntry* entry = lookup_symbol(global_symbol_table, array_name);
    
    if (!entry) {
        semantic_error("Variável não declarada", line);
        return TYPE_ERROR;
    }
    
    if (!entry->is_array) {
        semantic_error("Tentativa de acesso a array em variável não-array", line);
        return TYPE_ERROR;
    }
    
    return entry->data_type;
}

// Verifica chamada de função
DataType check_function_call(const char* func_name, int line) {
    SymbolEntry* entry = lookup_symbol(global_symbol_table, func_name);
    
    if (!entry) {
        semantic_error("Função não declarada", line);
        return TYPE_ERROR;
    }
    
    if (entry->symbol_type != SYMBOL_FUNC) {
        semantic_error("Tentativa de chamada de função em variável não-função", line);
        return TYPE_ERROR;
    }
    
    return entry->data_type;
}

// Declara uma variável
void declare_variable(const char* name, DataType type, int is_array, int line) {
    SymbolEntry* entry = insert_symbol(global_symbol_table, name, SYMBOL_VAR, type, line);
    
    if (!entry) {
        semantic_error("Redeclaração de variável", line);
        return;
    }
    
    if (is_array) {
        entry->is_array = 1;
    }
    
    printf("Variável '%s' declarada com tipo %s na linha %d\n", 
           name, type_to_string(type), line);
}

// Declara uma função
void declare_function(const char* name, DataType return_type, int line) {
    SymbolEntry* entry = insert_symbol(global_symbol_table, name, SYMBOL_FUNC, return_type, line);
    
    if (!entry) {
        semantic_error("Redeclaração de função", line);
        return;
    }
    
    printf("Função '%s' declarada com tipo de retorno %s na linha %d\n", 
           name, type_to_string(return_type), line);
}

// Declara um struct
void declare_struct(const char* name, int line) {
    SymbolEntry* entry = insert_symbol(global_symbol_table, name, SYMBOL_STRUCT, TYPE_STRUCT, line);
    
    if (!entry) {
        semantic_error("Redeclaração de struct", line);
        return;
    }
    
    printf("Struct '%s' declarado na linha %d\n", name, line);
}

// Verifica declaração de variável
void check_variable_declaration(const char* name, int line) {
    if (lookup_symbol_current_scope(global_symbol_table, name)) {
        semantic_error("Variável já declarada no escopo atual", line);
    }
}

// Verifica uso de variável
void check_variable_usage(const char* name, int line) {
    if (!lookup_symbol(global_symbol_table, name)) {
        semantic_error("Variável não declarada", line);
    }
}

// Verifica declaração de função
void check_function_declaration(const char* name, int line) {
    if (lookup_symbol_current_scope(global_symbol_table, name)) {
        semantic_error("Função já declarada no escopo atual", line);
    }
}

// Reporta erro semântico
void semantic_error(const char* message, int line) {
    fprintf(stderr, "(%d) Erro semântico na linha %d: %s\n", 
            ++semantic_errors, line, message);
}

// Reporta aviso semântico
void semantic_warning(const char* message, int line) {
    fprintf(stderr, "Aviso semântico na linha %d: %s\n", line, message);
}

// Verifica compatibilidade de tipos
int are_types_compatible(DataType type1, DataType type2) {
    if (type1 == type2) return 1;
    
    // Conversão implícita de int para float
    if ((type1 == TYPE_INT && type2 == TYPE_FLOAT) || 
        (type1 == TYPE_FLOAT && type2 == TYPE_INT)) {
        return 1;
    }
    
    return 0;
}

// Obtém o tipo de uma variável
DataType get_variable_type(const char* name) {
    SymbolEntry* entry = lookup_symbol(global_symbol_table, name);
    
    if (!entry) {
        return TYPE_ERROR;
    }
    
    return entry->data_type;
}

// Converte token para tipo
DataType token_to_type(int token) {
    switch (token) {
        case 257: // INT_TYPE
            return TYPE_INT;
        case 258: // FLOAT_TYPE
            return TYPE_FLOAT;
        case 259: // CHAR_TYPE
            return TYPE_CHAR;
        case 260: // STRUCT_TYPE
            return TYPE_STRUCT;
        case 261: // VOID_TYPE
            return TYPE_VOID;
        default:
            return TYPE_ERROR;
    }
}
