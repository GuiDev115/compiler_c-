#include "code_generator.h"

// Variáveis globais
CodeGenerator* global_code_gen = NULL;

// Cria um novo gerador de código
CodeGenerator* create_code_generator() {
    CodeGenerator* gen = (CodeGenerator*)malloc(sizeof(CodeGenerator));
    if (!gen) {
        fprintf(stderr, "Erro: Não foi possível alocar memória para o gerador de código\n");
        return NULL;
    }
    
    gen->first = NULL;
    gen->last = NULL;
    gen->temp_count = 0;
    gen->label_count = 0;
    gen->output_file = NULL;
    
    return gen;
}

// Destrói o gerador de código
void destroy_code_generator(CodeGenerator* gen) {
    if (!gen) return;
    
    CodeLine* current = gen->first;
    while (current) {
        CodeLine* temp = current;
        current = current->next;
        
        free(temp->op);
        free(temp->arg1);
        free(temp->arg2);
        free(temp->result);
        free(temp);
    }
    
    if (gen->output_file) {
        fclose(gen->output_file);
    }
    
    free(gen);
}

// Inicializa a geração de código
void init_code_generation() {
    global_code_gen = create_code_generator();
    if (!global_code_gen) {
        fprintf(stderr, "Erro: Não foi possível inicializar o gerador de código\n");
        exit(1);
    }
    
    printf("\n=== GERAÇÃO DE CÓDIGO INTERMEDIÁRIO ===\n");
}

// Finaliza a geração de código
void finish_code_generation() {
    if (!global_code_gen) return;
    
    printf("\n=== CÓDIGO INTERMEDIÁRIO GERADO ===\n");
    print_code();
    
    // Salva o código em arquivo
    save_code_to_file("codigo_intermediario.txt");
    
    destroy_code_generator(global_code_gen);
    global_code_gen = NULL;
}

// Emite uma linha de código
void emit_code(const char* op, const char* arg1, const char* arg2, const char* result) {
    if (!global_code_gen) return;
    
    CodeLine* line = (CodeLine*)malloc(sizeof(CodeLine));
    if (!line) {
        fprintf(stderr, "Erro: Não foi possível alocar memória para linha de código\n");
        return;
    }
    
    line->op = op ? strdup(op) : NULL;
    line->arg1 = arg1 ? strdup(arg1) : NULL;
    line->arg2 = arg2 ? strdup(arg2) : NULL;
    line->result = result ? strdup(result) : NULL;
    line->line_num = 0; // Pode ser melhorado para incluir número da linha
    line->next = NULL;
    
    if (!global_code_gen->first) {
        global_code_gen->first = line;
        global_code_gen->last = line;
    } else {
        global_code_gen->last->next = line;
        global_code_gen->last = line;
    }
}

// Emite uma atribuição
void emit_assignment(const char* var, const char* value) {
    emit_code("=", value, NULL, var);
}

// Emite uma operação binária
void emit_binary_op(const char* op, const char* arg1, const char* arg2, const char* result) {
    emit_code(op, arg1, arg2, result);
}

// Emite uma operação unária
void emit_unary_op(const char* op, const char* arg, const char* result) {
    emit_code(op, arg, NULL, result);
}

// Emite um label
void emit_label(const char* label) {
    emit_code("label", label, NULL, NULL);
}

// Emite um goto
void emit_goto(const char* label) {
    emit_code("goto", label, NULL, NULL);
}

// Emite um goto condicional
void emit_conditional_goto(const char* condition, const char* label) {
    emit_code("if", condition, label, NULL);
}

// Emite uma chamada de função
void emit_function_call(const char* func_name, const char* result) {
    emit_code("call", func_name, NULL, result);
}

// Emite um return
void emit_return(const char* value) {
    emit_code("return", value, NULL, NULL);
}

// Emite acesso a array
void emit_array_access(const char* array, const char* index, const char* result) {
    emit_code("[]", array, index, result);
}

// Emite atribuição a array
void emit_array_assignment(const char* array, const char* index, const char* value) {
    emit_code("[]=", array, index, value);
}

// Gera um novo temporário
char* new_temp() {
    if (!global_code_gen) return NULL;
    
    char* temp = (char*)malloc(20);
    if (!temp) return NULL;
    
    sprintf(temp, "t%d", global_code_gen->temp_count++);
    return temp;
}

// Gera um novo label
char* new_label() {
    if (!global_code_gen) return NULL;
    
    char* label = (char*)malloc(20);
    if (!label) return NULL;
    
    sprintf(label, "L%d", global_code_gen->label_count++);
    return label;
}

// Imprime o código gerado
void print_code() {
    if (!global_code_gen) return;
    
    CodeLine* current = global_code_gen->first;
    int line_num = 1;
    
    while (current) {
        printf("%3d: ", line_num++);
        
        if (current->op) {
            if (strcmp(current->op, "label") == 0) {
                printf("%s:\n", current->arg1);
            } else if (strcmp(current->op, "goto") == 0) {
                printf("goto %s\n", current->arg1);
            } else if (strcmp(current->op, "if") == 0) {
                printf("if %s goto %s\n", current->arg1, current->arg2);
            } else if (strcmp(current->op, "return") == 0) {
                if (current->arg1) {
                    printf("return %s\n", current->arg1);
                } else {
                    printf("return\n");
                }
            } else if (strcmp(current->op, "call") == 0) {
                if (current->result) {
                    printf("%s = call %s\n", current->result, current->arg1);
                } else {
                    printf("call %s\n", current->arg1);
                }
            } else if (strcmp(current->op, "[]") == 0) {
                printf("%s = %s[%s]\n", current->result, current->arg1, current->arg2);
            } else if (strcmp(current->op, "[]=") == 0) {
                printf("%s[%s] = %s\n", current->arg1, current->arg2, current->result);
            } else if (strcmp(current->op, "=") == 0) {
                printf("%s = %s\n", current->result, current->arg1);
            } else {
                // Operação binária
                if (current->arg2) {
                    printf("%s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
                } else {
                    printf("%s = %s %s\n", current->result, current->op, current->arg1);
                }
            }
        }
        
        current = current->next;
    }
}

// Salva o código em arquivo
void save_code_to_file(const char* filename) {
    if (!global_code_gen) return;
    
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Erro: Não foi possível criar o arquivo %s\n", filename);
        return;
    }
    
    CodeLine* current = global_code_gen->first;
    int line_num = 1;
    
    fprintf(file, "=== CÓDIGO INTERMEDIÁRIO DE TRÊS ENDEREÇOS ===\n\n");
    
    while (current) {
        fprintf(file, "%3d: ", line_num++);
        
        if (current->op) {
            if (strcmp(current->op, "label") == 0) {
                fprintf(file, "%s:\n", current->arg1);
            } else if (strcmp(current->op, "goto") == 0) {
                fprintf(file, "goto %s\n", current->arg1);
            } else if (strcmp(current->op, "if") == 0) {
                fprintf(file, "if %s goto %s\n", current->arg1, current->arg2);
            } else if (strcmp(current->op, "return") == 0) {
                if (current->arg1) {
                    fprintf(file, "return %s\n", current->arg1);
                } else {
                    fprintf(file, "return\n");
                }
            } else if (strcmp(current->op, "call") == 0) {
                if (current->result) {
                    fprintf(file, "%s = call %s\n", current->result, current->arg1);
                } else {
                    fprintf(file, "call %s\n", current->arg1);
                }
            } else if (strcmp(current->op, "[]") == 0) {
                fprintf(file, "%s = %s[%s]\n", current->result, current->arg1, current->arg2);
            } else if (strcmp(current->op, "[]=") == 0) {
                fprintf(file, "%s[%s] = %s\n", current->arg1, current->arg2, current->result);
            } else if (strcmp(current->op, "=") == 0) {
                fprintf(file, "%s = %s\n", current->result, current->arg1);
            } else {
                // Operação binária
                if (current->arg2) {
                    fprintf(file, "%s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
                } else {
                    fprintf(file, "%s = %s %s\n", current->result, current->op, current->arg1);
                }
            }
        }
        
        current = current->next;
    }
    
    fclose(file);
    printf("Código intermediário salvo em %s\n", filename);
}

// Gera código para expressão
char* generate_expression_code(const char* expr_type __attribute__((unused)), const char* left, const char* op, const char* right) {
    if (!op) {
        // Expressão simples (identificador ou número)
        return strdup(left);
    }
    
    char* temp = new_temp();
    if (!temp) return NULL;
    
    emit_binary_op(op, left, right, temp);
    return temp;
}

// Gera código para atribuição
char* generate_assignment_code(const char* var, const char* value) {
    emit_assignment(var, value);
    return strdup(var);
}

// Gera código para acesso a array
char* generate_array_code(const char* array, const char* index) {
    char* temp = new_temp();
    if (!temp) return NULL;
    
    emit_array_access(array, index, temp);
    return temp;
}

// Gera código para chamada de função
char* generate_function_call_code(const char* func_name, int param_count __attribute__((unused))) {
    char* temp = new_temp();
    if (!temp) return NULL;
    
    emit_function_call(func_name, temp);
    return temp;
}

// Otimização simples de código (placeholder)
void optimize_code() {
    // Implementação futura de otimizações:
    // - Eliminação de código morto
    // - Propagação de constantes
    // - Eliminação de subexpressões comuns
    printf("Otimização de código não implementada nesta versão.\n");
}
