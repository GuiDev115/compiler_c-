#include "utils.h"

// Duplica uma string de forma segura
char* safe_strdup(const char* str) {
    if (!str) return NULL;
    
    size_t len = strlen(str);
    char* copy = (char*)malloc(len + 1);
    if (!copy) return NULL;
    
    strcpy(copy, str);
    return copy;
}

// Concatena duas strings de forma segura
char* safe_strcat(const char* str1, const char* str2) {
    if (!str1 && !str2) return NULL;
    if (!str1) return safe_strdup(str2);
    if (!str2) return safe_strdup(str1);
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char* result = (char*)malloc(len1 + len2 + 1);
    if (!result) return NULL;
    
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

// Compara duas strings de forma segura
int safe_strcmp(const char* str1, const char* str2) {
    if (!str1 && !str2) return 0;
    if (!str1) return -1;
    if (!str2) return 1;
    
    return strcmp(str1, str2);
}

// Remove espaços em branco no início e fim da string
char* trim_whitespace(char* str) {
    if (!str) return NULL;
    
    // Remove espaços do início
    while (isspace(*str)) str++;
    
    // Se a string está vazia
    if (*str == 0) return str;
    
    // Remove espaços do final
    char* end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    
    // Adiciona terminador
    end[1] = '\0';
    
    return str;
}

// Verifica se é um identificador válido
int is_valid_identifier(const char* str) {
    if (!str || !*str) return 0;
    
    // Primeiro caractere deve ser letra ou underscore
    if (!isalpha(*str) && *str != '_') return 0;
    
    // Demais caracteres devem ser letras, dígitos ou underscore
    for (int i = 1; str[i]; i++) {
        if (!isalnum(str[i]) && str[i] != '_') return 0;
    }
    
    return 1;
}

// Verifica se é um número
int is_numeric(const char* str) {
    if (!str || !*str) return 0;
    
    int i = 0;
    int has_dot = 0;
    
    // Permite sinal no início
    if (str[0] == '+' || str[0] == '-') i = 1;
    
    if (!str[i]) return 0; // Apenas sinal
    
    for (; str[i]; i++) {
        if (str[i] == '.') {
            if (has_dot) return 0; // Mais de um ponto
            has_dot = 1;
        } else if (!isdigit(str[i])) {
            return 0;
        }
    }
    
    return 1;
}

// Cria uma pilha de strings
StringStack* create_string_stack(int capacity) {
    StringStack* stack = (StringStack*)malloc(sizeof(StringStack));
    if (!stack) return NULL;
    
    stack->items = (char**)malloc(capacity * sizeof(char*));
    if (!stack->items) {
        free(stack);
        return NULL;
    }
    
    stack->top = -1;
    stack->capacity = capacity;
    
    return stack;
}

// Destrói uma pilha de strings
void destroy_string_stack(StringStack* stack) {
    if (!stack) return;
    
    // Libera todas as strings
    for (int i = 0; i <= stack->top; i++) {
        free(stack->items[i]);
    }
    
    free(stack->items);
    free(stack);
}

// Empilha uma string
int push_string(StringStack* stack, const char* str) {
    if (!stack || is_stack_full(stack)) return 0;
    
    char* copy = safe_strdup(str);
    if (!copy) return 0;
    
    stack->items[++stack->top] = copy;
    return 1;
}

// Desempilha uma string
char* pop_string(StringStack* stack) {
    if (!stack || is_stack_empty(stack)) return NULL;
    
    return stack->items[stack->top--];
}

// Retorna o topo da pilha sem remover
char* peek_string(StringStack* stack) {
    if (!stack || is_stack_empty(stack)) return NULL;
    
    return stack->items[stack->top];
}

// Verifica se a pilha está vazia
int is_stack_empty(StringStack* stack) {
    return !stack || stack->top == -1;
}

// Verifica se a pilha está cheia
int is_stack_full(StringStack* stack) {
    return !stack || stack->top == stack->capacity - 1;
}

// Lê o conteúdo de um arquivo
char* read_file_content(const char* filename) {
    if (!filename) return NULL;
    
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* content = (char*)malloc(size + 1);
    if (!content) {
        fclose(file);
        return NULL;
    }
    
    fread(content, 1, size, file);
    content[size] = '\0';
    
    fclose(file);
    return content;
}

// Escreve conteúdo em um arquivo
int write_file_content(const char* filename, const char* content) {
    if (!filename || !content) return 0;
    
    FILE* file = fopen(filename, "w");
    if (!file) return 0;
    
    fputs(content, file);
    fclose(file);
    return 1;
}

// Verifica se um arquivo existe
int file_exists(const char* filename) {
    if (!filename) return 0;
    
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    
    return 0;
}

// Funções de logging
void log_message(const char* level, const char* message) {
    if (!level || !message) return;
    
    printf("[%s] %s\n", level, message);
}

void log_error(const char* message) {
    log_message("ERROR", message);
}

void log_warning(const char* message) {
    log_message("WARNING", message);
}

void log_info(const char* message) {
    log_message("INFO", message);
}

// Converte string para inteiro
int string_to_int(const char* str, int* result) {
    if (!str || !result) return 0;
    
    char* endptr;
    long val = strtol(str, &endptr, 10);
    
    if (endptr == str || *endptr != '\0') return 0;
    
    *result = (int)val;
    return 1;
}

// Converte string para float
int string_to_float(const char* str, float* result) {
    if (!str || !result) return 0;
    
    char* endptr;
    double val = strtod(str, &endptr);
    
    if (endptr == str || *endptr != '\0') return 0;
    
    *result = (float)val;
    return 1;
}

// Converte inteiro para string
char* int_to_string(int value) {
    char* str = (char*)malloc(20);
    if (!str) return NULL;
    
    sprintf(str, "%d", value);
    return str;
}

// Converte float para string
char* float_to_string(float value) {
    char* str = (char*)malloc(30);
    if (!str) return NULL;
    
    sprintf(str, "%.2f", value);
    return str;
}

// Valida tamanho de array
int validate_array_size(const char* size_str) {
    if (!size_str) return 0;
    
    int size;
    if (!string_to_int(size_str, &size)) return 0;
    
    return size > 0;
}

// Valida nome de função
int validate_function_name(const char* name) {
    if (!name) return 0;
    
    // Lista de palavras reservadas
    const char* reserved[] = {
        "int", "float", "char", "void", "struct",
        "if", "else", "while", "return", "for", "do",
        NULL
    };
    
    // Verifica se é um identificador válido
    if (!is_valid_identifier(name)) return 0;
    
    // Verifica se não é palavra reservada
    for (int i = 0; reserved[i]; i++) {
        if (strcmp(name, reserved[i]) == 0) return 0;
    }
    
    return 1;
}

// Valida nome de variável
int validate_variable_name(const char* name) {
    return validate_function_name(name); // Mesmas regras
}
