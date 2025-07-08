#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include "c-minus/semantic/symbol_table.h"
#include "c-minus/semantic/semantic.h"
#include "c-minus/semantic/code_generator.h"
#include "c-minus/semantic/utils.h"

#define MAX_FILES 100
#define MAX_PATH_LENGTH 256
#define MAX_BUFFER_SIZE 8192

// Declaração de função 
void detect_function_declaration(char *line, int line_num);

// Estrutura para armazenar informações sobre arquivos
typedef struct {
    char filename[MAX_PATH_LENGTH];
    char filepath[MAX_PATH_LENGTH];
    long size;
    int is_test_file;
} FileInfo;

// Estrutura para o agente semântico
typedef struct {
    char base_path[MAX_PATH_LENGTH];
    char semantic_path[MAX_PATH_LENGTH];
    char tests_path[MAX_PATH_LENGTH];
    FileInfo files[MAX_FILES];
    int file_count;
} SemanticAgent;

// Função para inicializar o agente semântico
void init_semantic_agent(SemanticAgent *agent, const char *base_path) {
    strcpy(agent->base_path, base_path);
    snprintf(agent->semantic_path, MAX_PATH_LENGTH, "%s/c-minus/semantic", base_path);
    snprintf(agent->tests_path, MAX_PATH_LENGTH, "%s/tests/semantic", base_path);
    agent->file_count = 0;
}

// Função para verificar se um arquivo é um arquivo de teste válido
int is_test_file(const char *filename) {
    int len = strlen(filename);
    return (len > 4 && strcmp(filename + len - 4, ".txt") == 0);
}

// Função para obter o tamanho de um arquivo
long get_file_size(const char *filepath) {
    struct stat st;
    if (stat(filepath, &st) == 0) {
        return st.st_size;
    }
    return -1;
}

// Função para escanear a pasta semântica
void scan_semantic_directory(SemanticAgent *agent) {
    DIR *dir;
    struct dirent *entry;
    
    printf("🔍 Escaneando pasta semântica: %s\n", agent->semantic_path);
    printf("═══════════════════════════════════════════════════════════════\n");
    
    dir = opendir(agent->semantic_path);
    if (dir == NULL) {
        printf("❌ Erro ao abrir pasta semântica: %s\n", agent->semantic_path);
        return;
    }
    
    int semantic_files = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Arquivo regular
            char filepath[MAX_PATH_LENGTH];
            int ret = snprintf(filepath, MAX_PATH_LENGTH, "%s/%s", agent->semantic_path, entry->d_name);
            if (ret >= MAX_PATH_LENGTH) {
                printf("⚠️  Caminho muito longo para %s\n", entry->d_name);
                continue;
            }
            
            long size = get_file_size(filepath);
            printf("📄 %s (%.2f KB)\n", entry->d_name, size / 1024.0);
            
            if (agent->file_count < MAX_FILES) {
                strcpy(agent->files[agent->file_count].filename, entry->d_name);
                strcpy(agent->files[agent->file_count].filepath, filepath);
                agent->files[agent->file_count].size = size;
                agent->files[agent->file_count].is_test_file = 0;
                agent->file_count++;
            }
            semantic_files++;
        }
    }
    
    closedir(dir);
    printf("📊 Total de arquivos semânticos encontrados: %d\n\n", semantic_files);
}

// Função para escanear a pasta de testes
void scan_tests_directory(SemanticAgent *agent) {
    DIR *dir;
    struct dirent *entry;
    
    printf("🧪 Escaneando pasta de testes: %s\n", agent->tests_path);
    printf("═══════════════════════════════════════════════════════════════\n");
    
    dir = opendir(agent->tests_path);
    if (dir == NULL) {
        printf("❌ Erro ao abrir pasta de testes: %s\n", agent->tests_path);
        return;
    }
    
    int test_files = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && is_test_file(entry->d_name)) {
            char filepath[MAX_PATH_LENGTH];
            int ret = snprintf(filepath, MAX_PATH_LENGTH, "%s/%s", agent->tests_path, entry->d_name);
            if (ret >= MAX_PATH_LENGTH) {
                printf("⚠️  Caminho muito longo para %s\n", entry->d_name);
                continue;
            }
            
            long size = get_file_size(filepath);
            printf("🧪 %s (%.2f KB)\n", entry->d_name, size / 1024.0);
            
            if (agent->file_count < MAX_FILES) {
                strcpy(agent->files[agent->file_count].filename, entry->d_name);
                strcpy(agent->files[agent->file_count].filepath, filepath);
                agent->files[agent->file_count].size = size;
                agent->files[agent->file_count].is_test_file = 1;
                agent->file_count++;
            }
            test_files++;
        }
    }
    
    closedir(dir);
    printf("📊 Total de arquivos de teste encontrados: %d\n\n", test_files);
}

// Função para ler e exibir o conteúdo de um arquivo
void display_file_content(const char *filepath, const char *filename) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("❌ Erro ao abrir arquivo: %s\n", filepath);
        return;
    }
    
    printf("📖 Conteúdo do arquivo: %s\n", filename);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    char buffer[MAX_BUFFER_SIZE];
    int line_number = 1;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%3d: %s", line_number, buffer);
        line_number++;
    }
    
    fclose(file);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}

// Função para analisar semanticamente um arquivo de teste
void analyze_test_file(const char *filepath, const char *filename) {
    printf("🔬 Análise semântica do arquivo: %s\n", filename);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // Inicializar subsistemas
    init_semantic_analysis();
    init_code_generation();
    
    // Ler o conteúdo do arquivo para análise real
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("❌ Erro ao abrir arquivo para análise: %s\n", filepath);
        return;
    }
    
    char buffer[MAX_BUFFER_SIZE];
    char content[MAX_BUFFER_SIZE * 4] = "";
    
    // Ler todo o conteúdo do arquivo
    while (fgets(buffer, sizeof(buffer), file)) {
        strcat(content, buffer);
    }
    fclose(file);
    
    printf("📋 Inicializando tabela de símbolos real...\n");
    
    // Análise semântica baseada no conteúdo real
    int has_errors = 0;
    int var_declarations = 0;
    int functions = 0;
    int arrays = 0;
    int structs = 0;
    int line_counter = 1;
    
    // === CRIAÇÃO REAL DA TABELA DE SÍMBOLOS ===
    global_symbol_table = create_symbol_table();
    
    printf("🔍 Construindo tabela de símbolos...\n");
    
    // Stack para rastrear blocos aninhados
    int brace_count = 0;
    int in_function = 0;
    
    // Analisar linha por linha para construir tabela de símbolos
    char *line = strtok(content, "\n");
    while (line != NULL) {
        char line_copy[1000];
        strcpy(line_copy, line);
        
        // Detectar abertura de bloco
        if (strstr(line_copy, "{")) {
            brace_count++;
            enter_scope(global_symbol_table);
            printf("   ➡️  Entrando em novo escopo (nível %d) - linha %d\n", 
                   global_symbol_table->current_scope, line_counter);
        }
        
        // Detectar fechamento de bloco
        if (strstr(line_copy, "}")) {
            if (brace_count > 0) {
                printf("   ⬅️  Saindo do escopo (nível %d) - linha %d\n", 
                       global_symbol_table->current_scope, line_counter);
                exit_scope_keep_symbols(global_symbol_table);
                brace_count--;
                
                if (in_function && brace_count == 0) {
                    in_function = 0;
                    printf("   🔚 Fim da função - linha %d\n", line_counter);
                }
            }
        }
        
        // Detectar função main (entrada em escopo de função)
        if (strstr(line_copy, "main") && strstr(line_copy, "(")) {
            in_function = 1;
            printf("   🚀 Início da função main - linha %d\n", line_counter);
        }
        
        // Detectar estruturas de controle que podem criar novos escopos
        if (strstr(line_copy, "if ") && strstr(line_copy, "(")) {
            printf("   🔀 Estrutura condicional 'if' detectada - linha %d\n", line_counter);
        }
        
        if (strstr(line_copy, "while ") && strstr(line_copy, "(")) {
            printf("   🔄 Estrutura de repetição 'while' detectada - linha %d\n", line_counter);
        }
        
        if (strstr(line_copy, "for ") && strstr(line_copy, "(")) {
            printf("   🔁 Estrutura de repetição 'for' detectada - linha %d\n", line_counter);
        }
        
        // Detectar arrays bidimensionais primeiro (para evitar conflito)
        if (strstr(line_copy, "][") && strstr(line_copy, "[")) {
            // Arrays bidimensionais como int matriz[5][3]
            char *type_start = NULL;
            DataType array_type = TYPE_INT;
            
            if (strstr(line_copy, "int ")) {
                type_start = strstr(line_copy, "int ") + 4;
                array_type = TYPE_INT;
            } else if (strstr(line_copy, "float ")) {
                type_start = strstr(line_copy, "float ") + 6;
                array_type = TYPE_FLOAT;
            } else if (strstr(line_copy, "char ")) {
                type_start = strstr(line_copy, "char ") + 5;
                array_type = TYPE_CHAR;
            }
            
            if (type_start) {
                while (*type_start == ' ') type_start++; // pular espaços
                
                char var_name[100] = "";
                int i = 0;
                while (type_start[i] && type_start[i] != '[' && type_start[i] != ' ') {
                    var_name[i] = type_start[i];
                    i++;
                }
                var_name[i] = '\0';
                
                // Extrair dimensões [dim1][dim2]
                char *first_bracket = strstr(type_start, "[");
                char *first_close = strstr(first_bracket, "]");
                char *second_bracket = strstr(first_close, "[");
                char *second_close = strstr(second_bracket, "]");
                
                if (first_bracket && first_close && second_bracket && second_close && strlen(var_name) > 0) {
                    // Primeira dimensão
                    char dim1_str[20] = "";
                    int dim1_len = first_close - first_bracket - 1;
                    if (dim1_len > 0 && dim1_len < 20) {
                        strncpy(dim1_str, first_bracket + 1, dim1_len);
                        dim1_str[dim1_len] = '\0';
                    }
                    
                    // Segunda dimensão
                    char dim2_str[20] = "";
                    int dim2_len = second_close - second_bracket - 1;
                    if (dim2_len > 0 && dim2_len < 20) {
                        strncpy(dim2_str, second_bracket + 1, dim2_len);
                        dim2_str[dim2_len] = '\0';
                    }
                    
                    int dim1 = atoi(dim1_str);
                    int dim2 = atoi(dim2_str);
                    
                    if (dim1 > 0 && dim2 > 0) {
                        declare_variable(var_name, array_type, 1, line_counter);
                        SymbolEntry* entry = lookup_symbol(global_symbol_table, var_name);
                        if (entry) {
                            add_array_dimension(entry, dim1);
                            add_array_dimension(entry, dim2);
                        }
                        printf("   ✓ Array bidimensional '%s[%d][%d]' (%s) inserido na tabela - linha %d\n", 
                               var_name, dim1, dim2, type_to_string(array_type), line_counter);
                        var_declarations++;
                        arrays++;
                    }
                }
            }
        }
        // Detectar arrays unidimensionais (só se não for bidimensional)
        else if (strstr(line_copy, "[") && strstr(line_copy, "]") && !strstr(line_copy, "][")) {
            DataType array_type = TYPE_INT;
            char *token = NULL;
            
            if (strstr(line_copy, "int ")) {
                token = strstr(line_copy, "int ") + 4;
                array_type = TYPE_INT;
            } else if (strstr(line_copy, "float ")) {
                token = strstr(line_copy, "float ") + 6;
                array_type = TYPE_FLOAT;
            } else if (strstr(line_copy, "char ")) {
                token = strstr(line_copy, "char ") + 5;
                array_type = TYPE_CHAR;
            }
            
            if (token) {
                while (*token == ' ') token++; // pular espaços
                
                char var_name[100] = "";
                int i = 0;
                while (token[i] && token[i] != '[' && token[i] != ' ') {
                    var_name[i] = token[i];
                    i++;
                }
                var_name[i] = '\0';
                
                // Extrair tamanho do array
                char *bracket_start = strstr(token, "[");
                char *bracket_end = strstr(token, "]");
                if (bracket_start && bracket_end && strlen(var_name) > 0) {
                    char size_str[20] = "";
                    int size_len = bracket_end - bracket_start - 1;
                    if (size_len > 0 && size_len < 20) {
                        strncpy(size_str, bracket_start + 1, size_len);
                        size_str[size_len] = '\0';
                        
                        int array_size = atoi(size_str);
                        if (array_size > 0) {
                            declare_variable(var_name, array_type, 1, line_counter);
                            SymbolEntry* entry = lookup_symbol(global_symbol_table, var_name);
                            if (entry) {
                                add_array_dimension(entry, array_size);
                            }
                            printf("   ✓ Array '%s[%d]' (%s) inserido na tabela - linha %d\n", 
                                   var_name, array_size, type_to_string(array_type), line_counter);
                            var_declarations++;
                            arrays++;
                        }
                    }
                }
            }
        }
        // Detectar declarações de variáveis int simples
        else if (strstr(line_copy, "int ") && strstr(line_copy, ";") && !strstr(line_copy, "[")) {
            char *token = strstr(line_copy, "int ");
            if (token) {
                token += 4; // pular "int "
                while (*token == ' ') token++; // pular espaços
                
                char var_name[100] = "";
                int i = 0;
                while (token[i] && token[i] != ';' && token[i] != '[' && token[i] != ' ') {
                    var_name[i] = token[i];
                    i++;
                }
                var_name[i] = '\0';
                
                if (strlen(var_name) > 0) {
                    declare_variable(var_name, TYPE_INT, 0, line_counter);
                    printf("   ✓ Variável '%s' (int) inserida na tabela - linha %d\n", var_name, line_counter);
                    var_declarations++;
                }
            }
        }
        
        // Detectar declarações float simples
        else if (strstr(line_copy, "float ") && strstr(line_copy, ";") && !strstr(line_copy, "[")) {
            char *token = strstr(line_copy, "float ");
            if (token) {
                token += 6; // pular "float "
                while (*token == ' ') token++; // pular espaços
                
                char var_name[100] = "";
                int i = 0;
                while (token[i] && token[i] != ';' && token[i] != '[' && token[i] != ' ') {
                    var_name[i] = token[i];
                    i++;
                }
                var_name[i] = '\0';
                
                if (strlen(var_name) > 0) {
                    declare_variable(var_name, TYPE_FLOAT, 0, line_counter);
                    printf("   ✓ Variável '%s' (float) inserida na tabela - linha %d\n", var_name, line_counter);
                    var_declarations++;
                }
            }
        }
        
        // Detectar declarações char simples
        else if (strstr(line_copy, "char ") && strstr(line_copy, ";") && !strstr(line_copy, "[")) {
            char *token = strstr(line_copy, "char ");
            if (token) {
                token += 5; // pular "char "
                while (*token == ' ') token++; // pular espaços
                
                char var_name[100] = "";
                int i = 0;
                while (token[i] && token[i] != ';' && token[i] != '[' && token[i] != ' ') {
                    var_name[i] = token[i];
                    i++;
                }
                var_name[i] = '\0';
                
                if (strlen(var_name) > 0) {
                    declare_variable(var_name, TYPE_CHAR, 0, line_counter);
                    printf("   ✓ Variável '%s' (char) inserida na tabela - linha %d\n", var_name, line_counter);
                    var_declarations++;
                }
            }
        }
        
        // Detectar structs
        else if (strstr(line_copy, "struct ")) {
            structs++;
            printf("   ✓ Struct detectado - linha %d\n", line_counter);
        }
        
        // Detectar declarações de função usando a função corrigida
        detect_function_declaration(line_copy, line_counter);
        
        // Contar funções declaradas para estatísticas
        if (strstr(line_copy, "(") && strstr(line_copy, ")") && 
            (strstr(line_copy, "void ") || strstr(line_copy, "int ") || 
             strstr(line_copy, "float ") || strstr(line_copy, "char "))) {
            functions++;
        }
        
        line = strtok(NULL, "\n");
        line_counter++;
    }
    
    printf("\n📊 Tabela de símbolos construída:\n");
    printf("   • %d variáveis declaradas\n", var_declarations);
    printf("   • %d funções declaradas\n", functions);
    printf("   • %d arrays detectados\n", arrays);
    printf("   • %d structs detectados\n", structs);
    
    // === GERAÇÃO REAL DE CÓDIGO DE TRÊS ENDEREÇOS ===
    printf("\n🏗️  Gerando código de três endereços...\n");
    
    // Reinicializar para segunda passada - geração de código
    strcpy(content, ""); // limpar content
    file = fopen(filepath, "r");
    if (file) {
        while (fgets(buffer, sizeof(buffer), file)) {
            strcat(content, buffer);
        }
        fclose(file);
    }
    
    line_counter = 1;
    char *code_line = strtok(content, "\n");
    while (code_line != NULL) {
        char line_copy[1000];
        strcpy(line_copy, code_line);
        
        // Gerar código para atribuições
        if (strstr(line_copy, " = ") && strstr(line_copy, ";")) {
            char *eq_pos = strstr(line_copy, " = ");
            if (eq_pos) {
                char var_name[100] = "";
                char value[100] = "";
                
                // Extrair nome da variável
                char *start = line_copy;
                while (*start == ' ' || *start == '\t') start++; // pular espaços iniciais
                
                int i = 0;
                while (start[i] && start[i] != ' ' && start[i] != '=') {
                    var_name[i] = start[i];
                    i++;
                }
                var_name[i] = '\0';
                
                // Extrair valor
                char *val_start = eq_pos + 3; // pular " = "
                while (*val_start == ' ') val_start++; // pular espaços
                
                i = 0;
                while (val_start[i] && val_start[i] != ';' && val_start[i] != '\n') {
                    value[i] = val_start[i];
                    i++;
                }
                value[i] = '\0';
                
                // Remover espaços no final do valor
                i = strlen(value) - 1;
                while (i >= 0 && (value[i] == ' ' || value[i] == '\t')) {
                    value[i] = '\0';
                    i--;
                }
                
                if (strlen(var_name) > 0 && strlen(value) > 0) {
                    // Processar expressão complexa e gerar código de três endereços
                    char* final_result = process_complex_expression(value);
                    if (final_result) {
                        emit_assignment(var_name, final_result);
                        printf("   ✓ Código gerado: %s := %s\n", var_name, final_result);
                        if (strcmp(final_result, value) != 0) {
                            free(final_result);
                        }
                    } else {
                        emit_assignment(var_name, value);
                        printf("   ✓ Código gerado: %s := %s\n", var_name, value);
                    }
                }
            }
        }
        
        // Gerar código para expressões aritméticas
        if ((strstr(line_copy, " + ") || strstr(line_copy, " - ") || 
             strstr(line_copy, " * ") || strstr(line_copy, " / ")) && 
            strstr(line_copy, " = ")) {
            
            char *temp = new_temp();
            printf("   ✓ Temporário '%s' gerado para expressão aritmética\n", temp);
            free(temp);
        }
        
        // Gerar labels para estruturas de controle
        if (strstr(line_copy, "if ") || strstr(line_copy, "while ")) {
            char *label = new_label();
            printf("   ✓ Label '%s' gerado para estrutura de controle\n", label);
            free(label);
        }
        
        code_line = strtok(NULL, "\n");
        line_counter++;
    }
    
    // === VERIFICAÇÃO DETALHADA DE ERROS SEMÂNTICOS ===
    printf("\n🔍 Verificando erros semânticos...\n");
    
    int error_count = 0;
    
    // Reinicializar para terceira passada - verificação de erros
    strcpy(content, "");
    file = fopen(filepath, "r");
    if (file) {
        while (fgets(buffer, sizeof(buffer), file)) {
            strcat(content, buffer);
        }
        fclose(file);
    }
    
    line_counter = 1;
    char content_error_copy[MAX_BUFFER_SIZE * 4];
    strcpy(content_error_copy, content);
    char *error_line = strtok(content_error_copy, "\n");
    
    while (error_line != NULL) {
        char line_copy[1000];
        strcpy(line_copy, error_line);
        
        // 1. Verificar variáveis não declaradas na linha "z = x + y;"
        if (strstr(line_copy, " = ") && !strstr(line_copy, "int ") && 
            !strstr(line_copy, "float ") && !strstr(line_copy, "char ") &&
            !strstr(line_copy, "/*") && !strstr(line_copy, "return")) {
            
            char *eq_pos = strstr(line_copy, " = ");
            if (eq_pos) {
                // Verificar variável do lado esquerdo da atribuição
                char var_name[100] = "";
                char *start = line_copy;
                while (*start == ' ' || *start == '\t') start++; // pular espaços iniciais
                
                int i = 0;
                while (start[i] && start[i] != ' ' && start[i] != '=' && start[i] != '[') {
                    var_name[i] = start[i];
                    i++;
                }
                var_name[i] = '\0';
                
                if (strlen(var_name) > 0) {
                    SymbolEntry* entry = lookup_symbol(global_symbol_table, var_name);
                    if (!entry) {
                        printf("   ❌ ERRO SEMÂNTICO linha %d: Variável '%s' usada sem declaração\n", 
                               line_counter, var_name);
                        error_count++;
                        has_errors = 1;
                    }
                }
                
                // Verificar variáveis do lado direito da atribuição
                char *value_start = eq_pos + 3;
                while (*value_start == ' ') value_start++;
                
                // Extrair tokens do lado direito
                char value_copy[500];
                strcpy(value_copy, value_start);
                
                // Remover ; e espaços no final
                char *semicolon = strchr(value_copy, ';');
                if (semicolon) *semicolon = '\0';
                
                // Parse tokens mais cuidadoso
                char *saveptr;
                char *token = strtok_r(value_copy, " +*/-()&|!", &saveptr);
                while (token != NULL) {
                    // Ignorar números, strings, operadores e palavras-chave
                    if (token[0] != '"' && !isdigit(token[0]) && strlen(token) > 0 && 
                        strcmp(token, "+") != 0 && strcmp(token, "-") != 0 && 
                        strcmp(token, "*") != 0 && strcmp(token, "/") != 0 &&
                        strcmp(token, "(") != 0 && strcmp(token, ")") != 0 &&
                        !isdigit(token[0]) && strchr(token, '.') == NULL) {
                        
                        // Limpar token de caracteres especiais
                        char clean_token[100] = "";
                        int j = 0;
                        for (int k = 0; k < strlen(token); k++) {
                            if (isalnum(token[k]) || token[k] == '_') {
                                clean_token[j++] = token[k];
                            }
                        }
                        clean_token[j] = '\0';
                        
                        if (strlen(clean_token) > 0) {
                            SymbolEntry* entry = lookup_symbol(global_symbol_table, clean_token);
                            if (!entry) {
                                printf("   ❌ ERRO SEMÂNTICO linha %d: Variável '%s' usada sem declaração\n", 
                                       line_counter, clean_token);
                                error_count++;
                                has_errors = 1;
                            }
                        }
                    }
                    token = strtok_r(NULL, " +*/-()&|!", &saveptr);
                }
            }
        }
        
        // 2. Verificar incompatibilidade de tipos (string para numérico)
        if (strstr(line_copy, " = ") && strstr(line_copy, "\"")) {
            char *eq_pos = strstr(line_copy, " = ");
            if (eq_pos) {
                char var_name[100] = "";
                char *start = line_copy;
                while (*start == ' ' || *start == '\t') start++;
                
                int i = 0;
                while (start[i] && start[i] != ' ' && start[i] != '=') {
                    var_name[i] = start[i];
                    i++;
                }
                var_name[i] = '\0';
                
                if (strlen(var_name) > 0) {
                    SymbolEntry* entry = lookup_symbol(global_symbol_table, var_name);
                    if (entry && (entry->data_type == TYPE_INT || entry->data_type == TYPE_FLOAT)) {
                        printf("   ❌ ERRO SEMÂNTICO linha %d: Atribuição de string à variável '%s' do tipo %s\n", 
                               line_counter, var_name, type_to_string(entry->data_type));
                        error_count++;
                        has_errors = 1;
                    }
                }
            }
        }
        
        // 3. Verificar chamadas de função não declaradas
        // Primeiro, verificar chamadas em atribuições (var = funcao(params))
        if (strstr(line_copy, "(") && strstr(line_copy, ")") && strstr(line_copy, "=")) {
            char *paren_pos = strstr(line_copy, "(");
            if (paren_pos) {
                // Extrair nome da função
                char *func_start = paren_pos;
                while (func_start > line_copy && (isalnum(*(func_start-1)) || *(func_start-1) == '_')) {
                    func_start--;
                }
                
                char func_name[100] = "";
                int i = 0;
                while (func_start[i] && func_start[i] != '(' && func_start[i] != ' ') {
                    func_name[i] = func_start[i];
                    i++;
                }
                func_name[i] = '\0';
                
                // Ignorar palavras-chave e funções conhecidas
                if (strlen(func_name) > 0 && strcmp(func_name, "main") != 0 && 
                    strcmp(func_name, "if") != 0 && strcmp(func_name, "while") != 0 && 
                    strcmp(func_name, "for") != 0 && strcmp(func_name, "printf") != 0 && 
                    strcmp(func_name, "scanf") != 0) {
                    
                    SymbolEntry* entry = lookup_symbol(global_symbol_table, func_name);
                    if (!entry) {
                        printf("   ❌ ERRO SEMÂNTICO linha %d: Função '%s' não declarada\n", 
                               line_counter, func_name);
                        error_count++;
                        has_errors = 1;
                    } else if (entry->symbol_type != SYMBOL_FUNC) {
                        printf("   ❌ ERRO SEMÂNTICO linha %d: '%s' não é uma função\n", 
                               line_counter, func_name);
                        error_count++;
                        has_errors = 1;
                    } else {
                        printf("   ✅ Função '%s' encontrada na tabela de símbolos - linha %d\n", 
                               func_name, line_counter);
                    }
                }
            }
        }
        
        // Verificar chamadas de função em linhas próprias (como imprime_numero)
        if (strstr(line_copy, "(") && strstr(line_copy, ")") && 
            !strstr(line_copy, "{") && // Não é declaração de função
            !strstr(line_copy, "=") &&  // Não é atribuição
            !strstr(line_copy, "if") && !strstr(line_copy, "while")) { // Não é estrutura de controle
            
            char *paren_pos = strstr(line_copy, "(");
            char *func_start = paren_pos;
            while (func_start > line_copy && (isalnum(*(func_start-1)) || *(func_start-1) == '_')) {
                func_start--;
            }
            
            char func_name[100] = "";
            int i = 0;
            while (func_start[i] && func_start[i] != '(' && func_start[i] != ' ') {
                func_name[i] = func_start[i];
                i++;
            }
            func_name[i] = '\0';
            
            if (strlen(func_name) > 0 && strcmp(func_name, "main") != 0 && 
                strcmp(func_name, "printf") != 0 && strcmp(func_name, "scanf") != 0) {
                SymbolEntry* entry = lookup_symbol(global_symbol_table, func_name);
                if (!entry) {
                    printf("   ❌ ERRO SEMÂNTICO linha %d: Função '%s' não declarada\n", 
                           line_counter, func_name);
                    error_count++;
                    has_errors = 1;
                } else if (entry->symbol_type != SYMBOL_FUNC) {
                    printf("   ❌ ERRO SEMÂNTICO linha %d: '%s' não é uma função\n", 
                           line_counter, func_name);
                    error_count++;
                    has_errors = 1;
                } else {
                    printf("   ✅ Função '%s' encontrada na tabela de símbolos - linha %d\n", 
                           func_name, line_counter);
                }
            }
        }
        
        // 4. Verificar acesso a arrays não declarados
        if (strstr(line_copy, "[") && strstr(line_copy, "]")) {
            char *bracket_pos = strstr(line_copy, "[");
            if (bracket_pos) {
                // Extrair nome da variável antes do [
                char *var_start = bracket_pos;
                while (var_start > line_copy && (isalnum(*(var_start-1)) || *(var_start-1) == '_')) {
                    var_start--;
                }
                
                char var_name[100] = "";
                int i = 0;
                while (var_start[i] && var_start[i] != '[' && var_start[i] != ' ') {
                    var_name[i] = var_start[i];
                    i++;
                }
                var_name[i] = '\0';
                
                if (strlen(var_name) > 0 && !strstr(line_copy, "int ") && 
                    !strstr(line_copy, "float ") && !strstr(line_copy, "char ")) {
                    // É um uso de array, não uma declaração
                    SymbolEntry* entry = lookup_symbol(global_symbol_table, var_name);
                    if (!entry) {
                        printf("   ❌ ERRO SEMÂNTICO linha %d: Array '%s' não declarado\n", 
                               line_counter, var_name);
                        error_count++;
                        has_errors = 1;
                    } else if (!entry->is_array) {
                        printf("   ❌ ERRO SEMÂNTICO linha %d: '%s' não é um array\n", 
                               line_counter, var_name);
                        error_count++;
                        has_errors = 1;
                    }
                }
            }
        }
        
        error_line = strtok(NULL, "\n");
        line_counter++;
    }
    
    // Resumo da verificação de erros
    if (error_count > 0) {
        printf("\n   📊 RESUMO: %d erro(s) semântico(s) detectado(s)\n", error_count);
    } else {
        printf("   ✅ Nenhum erro semântico detectado - código válido!\n");
    }
    
    // Exibir tabela de símbolos final
    printf("\n📋 TABELA DE SÍMBOLOS FINAL:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    print_symbol_table(global_symbol_table);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // Salvar código de três endereços em arquivo específico
    char output_file[500];
    snprintf(output_file, sizeof(output_file), "codigo_3enderecos_%s", filename);
    // Remover .txt e adicionar .ir
    char *dot = strstr(output_file, ".txt");
    if (dot) {
        strcpy(dot, ".ir");
    }
    
    // Salvar código intermediário em arquivo específico
    save_code_to_file(output_file);
    printf("\n💾 Código de três endereços salvo em: %s\n", output_file);
    
    // Cleanup
    finish_semantic_analysis();
    finish_code_generation();
    // global_symbol_table já é liberada pelo finish_semantic_analysis()
    
    if (has_errors) {
        printf("⚠️  Análise semântica concluída com %d erro(s) detectado(s)\n", has_errors);
    } else {
        printf("✅ Análise semântica concluída com sucesso - código válido!\n");
    }
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}

// Função para detectar declarações de função conforme BNF
// <fun-declaracao> ::= <tipo-especificador> <ident> ( <params> ) <composto-decl>
void detect_function_declaration(char *line, int line_num) {
    // Verifica se é uma declaração de função (tipo + nome + parênteses)
    if (strstr(line, "(") && strstr(line, ")")) {
        // Verificar se há um tipo antes dos parênteses
        char func_name[100] = "";
        DataType return_type = TYPE_VOID;
        
        // Detectar tipo de retorno (ordem importa!)
        if (strstr(line, "void ")) {
            return_type = TYPE_VOID;
        } else if (strstr(line, "int ")) {
            return_type = TYPE_INT;
        } else if (strstr(line, "float ")) {
            return_type = TYPE_FLOAT;
        } else if (strstr(line, "char ")) {
            return_type = TYPE_CHAR;
        }
        
        // Extrair nome da função (ordem importa!)
        char *type_end = NULL;
        if (strstr(line, "void ")) type_end = strstr(line, "void ") + 5;
        else if (strstr(line, "int ")) type_end = strstr(line, "int ") + 4;
        else if (strstr(line, "float ")) type_end = strstr(line, "float ") + 6;
        else if (strstr(line, "char ")) type_end = strstr(line, "char ") + 5;
        
        if (type_end) {
            while (*type_end == ' ') type_end++; // pular espaços
            
            char *paren_pos = strstr(type_end, "(");
            if (paren_pos) {
                int name_len = paren_pos - type_end;
                if (name_len > 0 && name_len < 100) {
                    strncpy(func_name, type_end, name_len);
                    func_name[name_len] = '\0';
                    
                    // Remover espaços no final
                    int i = strlen(func_name) - 1;
                    while (i >= 0 && func_name[i] == ' ') {
                        func_name[i] = '\0';
                        i--;
                    }
                    
                    if (strlen(func_name) > 0 && 
                        strcmp(func_name, "if") != 0 && 
                        strcmp(func_name, "while") != 0 && 
                        strcmp(func_name, "for") != 0) {
                        declare_function(func_name, return_type, line_num);
                        printf("   ✓ Função '%s' (%s) declarada - linha %d\n", 
                               func_name, type_to_string(return_type), line_num);
                    }
                }
            }
        }
    }
}

// Função para exibir menu interativo
void display_menu() {
    printf("\n🤖 AGENTE SEMÂNTICO - C- COMPILER\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("1. 📁 Escanear pasta semântica\n");
    printf("2. 🧪 Escanear pasta de testes\n");
    printf("3. 📖 Ler arquivo específico\n");
    printf("4. 🔬 Analisar arquivo de teste\n");
    printf("5. 🚀 Executar análise completa\n");
    printf("6. 📊 Exibir estatísticas\n");
    printf("7. 🔄 Atualizar escaneamento\n");
    printf("0. 🚪 Sair\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("Escolha uma opção: ");
}

// Função para listar arquivos disponíveis
void list_available_files(SemanticAgent *agent) {
    printf("\n📁 Arquivos disponíveis:\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    
    int test_count = 0, semantic_count = 0;
    
    for (int i = 0; i < agent->file_count; i++) {
        if (agent->files[i].is_test_file) {
            printf("🧪 %d. %s (%.2f KB)\n", i + 1, agent->files[i].filename, 
                   agent->files[i].size / 1024.0);
            test_count++;
        } else {
            printf("📄 %d. %s (%.2f KB)\n", i + 1, agent->files[i].filename, 
                   agent->files[i].size / 1024.0);
            semantic_count++;
        }
    }
    
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("Total: %d arquivos (%d semânticos, %d testes)\n", 
           agent->file_count, semantic_count, test_count);
}

// Função para executar análise completa
void run_complete_analysis(SemanticAgent *agent) {
    printf("\n🚀 EXECUTANDO ANÁLISE COMPLETA\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    
    for (int i = 0; i < agent->file_count; i++) {
        if (agent->files[i].is_test_file) {
            printf("\n🔍 Analisando: %s\n", agent->files[i].filename);
            analyze_test_file(agent->files[i].filepath, agent->files[i].filename);
        }
    }
    
    printf("✅ Análise completa finalizada!\n");
}

// Função para exibir estatísticas
void display_statistics(SemanticAgent *agent) {
    printf("\n📊 ESTATÍSTICAS DO AGENTE SEMÂNTICO\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    
    int test_files = 0, semantic_files = 0;
    long total_size = 0;
    
    for (int i = 0; i < agent->file_count; i++) {
        if (agent->files[i].is_test_file) {
            test_files++;
        } else {
            semantic_files++;
        }
        total_size += agent->files[i].size;
    }
    
    printf("📁 Pasta base: %s\n", agent->base_path);
    printf("📄 Arquivos semânticos: %d\n", semantic_files);
    printf("🧪 Arquivos de teste: %d\n", test_files);
    printf("📊 Total de arquivos: %d\n", agent->file_count);
    printf("💾 Tamanho total: %.2f KB\n", total_size / 1024.0);
    printf("═══════════════════════════════════════════════════════════════\n");
}

// Função para obter o diretório atual do programa
char* get_current_directory() {
    static char current_dir[MAX_PATH_LENGTH];
    if (getcwd(current_dir, sizeof(current_dir)) != NULL) {
        return current_dir;
    }
    return "."; // fallback para diretório atual
}

// Função para verificar se os diretórios necessários existem
int verify_project_structure(const char* base_path) {
    char semantic_path[MAX_PATH_LENGTH];
    char tests_path[MAX_PATH_LENGTH];
    
    snprintf(semantic_path, MAX_PATH_LENGTH, "%s/c-minus/semantic", base_path);
    snprintf(tests_path, MAX_PATH_LENGTH, "%s/tests/semantic", base_path);
    
    struct stat st;
    
    // Verificar se o diretório semântico existe
    if (stat(semantic_path, &st) != 0 || !S_ISDIR(st.st_mode)) {
        printf("❌ Diretório semântico não encontrado: %s\n", semantic_path);
        return 0;
    }
    
    // Verificar se o diretório de testes existe
    if (stat(tests_path, &st) != 0 || !S_ISDIR(st.st_mode)) {
        printf("❌ Diretório de testes não encontrado: %s\n", tests_path);
        return 0;
    }
    
    return 1;
}

// Função principal
int main() {
    SemanticAgent agent;
    char* base_path = get_current_directory();
    
    printf("🔍 Detectando diretório do projeto: %s\n", base_path);
    
    // Verificar se a estrutura do projeto está correta
    if (!verify_project_structure(base_path)) {
        printf("\n⚠️  Estrutura do projeto não encontrada no diretório atual.\n");
        printf("💡 Certifique-se de que você está executando o programa na pasta raiz do projeto compiler_c-\n");
        printf("📁 A estrutura esperada é:\n");
        printf("   compiler_c-/\n");
        printf("   ├── c-minus/semantic/\n");
        printf("   ├── tests/semantic/\n");
        printf("   └── agente_semantico.c\n\n");
        
        printf("🔄 Deseja especificar manualmente o caminho? (s/n): ");
        char choice;
        scanf(" %c", &choice);
        
        if (choice == 's' || choice == 'S') {
            printf("📝 Digite o caminho completo para a pasta compiler_c-: ");
            static char manual_path[MAX_PATH_LENGTH];
            scanf("%s", manual_path);
            
            if (verify_project_structure(manual_path)) {
                base_path = manual_path;
                printf("✅ Estrutura do projeto verificada com sucesso!\n");
            } else {
                printf("❌ Estrutura inválida no caminho especificado. Encerrando...\n");
                return 1;
            }
        } else {
            printf("❌ Não é possível continuar sem a estrutura correta do projeto.\n");
            return 1;
        }
    } else {
        printf("✅ Estrutura do projeto verificada com sucesso!\n");
    }
    
    init_semantic_agent(&agent, base_path);
    
    printf("🤖 Agente Semântico Inicializado\n");
    printf("📁 Pasta base: %s\n", agent.base_path);
    
    // Escaneamento inicial
    scan_semantic_directory(&agent);
    scan_tests_directory(&agent);
    
    int choice;
    do {
        display_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                scan_semantic_directory(&agent);
                break;
                
            case 2:
                scan_tests_directory(&agent);
                break;
                
            case 3: {
                list_available_files(&agent);
                printf("\nDigite o número do arquivo (0 para voltar): ");
                int file_num;
                scanf("%d", &file_num);
                
                if (file_num > 0 && file_num <= agent.file_count) {
                    display_file_content(agent.files[file_num - 1].filepath, 
                                    agent.files[file_num - 1].filename);
                }
                break;
            }
            
            case 4: {
                printf("\n🧪 Arquivos de teste disponíveis:\n");
                printf("═══════════════════════════════════════════════════════════════\n");
                int test_num = 1;
                for (int i = 0; i < agent.file_count; i++) {
                    if (agent.files[i].is_test_file) {
                        printf("%d. %s\n", test_num, agent.files[i].filename);
                        test_num++;
                    }
                }
                
                printf("\nDigite o número do teste (0 para voltar): ");
                int test_choice;
                scanf("%d", &test_choice);
                
                if (test_choice > 0) {
                    int current_test = 1;
                    for (int i = 0; i < agent.file_count; i++) {
                        if (agent.files[i].is_test_file) {
                            if (current_test == test_choice) {
                                display_file_content(agent.files[i].filepath, agent.files[i].filename);
                                analyze_test_file(agent.files[i].filepath, agent.files[i].filename);
                                break;
                            }
                            current_test++;
                        }
                    }
                }
                break;
            }
            
            case 5:
                run_complete_analysis(&agent);
                break;
                
            case 6:
                display_statistics(&agent);
                break;
                
            case 7:
                agent.file_count = 0;
                scan_semantic_directory(&agent);
                scan_tests_directory(&agent);
                break;
                
            case 0:
                printf("🚪 Saindo do agente semântico...\n");
                break;
                
            default:
                printf("❌ Opção inválida! Tente novamente.\n");
        }
        
    } while (choice != 0);
    
    return 0;
}
