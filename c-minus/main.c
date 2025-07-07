/* 
 * Arquivo principal do compilador C-
 * Integra análise léxica, sintática, semântica e geração de código intermediário
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "semantic/symbol_table.h"
#include "semantic/semantic.h"
#include "semantic/code_generator.h"
#include "semantic/utils.h"

// Declarações do parser
extern int yyparse(void);
extern FILE *yyin;
extern int yydebug;
extern int line_number;
extern int column_number;
extern int errors_count;

// Opções do compilador
typedef struct {
    int debug_mode;
    int verbose;
    int only_lexer;
    int only_parser;
    int only_semantic;
    int print_tokens;
    int print_ast;
    int print_symbols;
    int print_code;
    char* output_file;
    char* input_file;
} CompilerOptions;

// Protótipos das funções
void print_usage(const char* program_name);
void print_version(void);
void parse_arguments(int argc, char* argv[], CompilerOptions* options);
int compile_file(const char* filename, CompilerOptions* options);
void setup_compiler(CompilerOptions* options);
void cleanup_compiler(void);

int main(int argc, char* argv[]) {
    CompilerOptions options = {0};
    
    // Configurações padrão
    options.debug_mode = 0;
    options.verbose = 0;
    options.only_lexer = 0;
    options.only_parser = 0;
    options.only_semantic = 0;
    options.print_tokens = 0;
    options.print_ast = 0;
    options.print_symbols = 1;  // Padrão: mostrar tabela de símbolos
    options.print_code = 1;     // Padrão: mostrar código intermediário
    options.output_file = NULL;
    options.input_file = NULL;
    
    // Analisa argumentos da linha de comando
    parse_arguments(argc, argv, &options);
    
    // Verifica se foi fornecido arquivo de entrada
    if (!options.input_file) {
        fprintf(stderr, "Erro: Nenhum arquivo de entrada especificado.\n");
        print_usage(argv[0]);
        return 1;
    }
    
    // Verifica se o arquivo existe
    if (!file_exists(options.input_file)) {
        fprintf(stderr, "Erro: Arquivo '%s' não encontrado.\n", options.input_file);
        return 1;
    }
    
    // Configuração do compilador
    setup_compiler(&options);
    
    // Compila o arquivo
    int result = compile_file(options.input_file, &options);
    
    // Limpeza
    cleanup_compiler();
    
    if (options.output_file) {
        free(options.output_file);
    }
    
    return result;
}

void print_usage(const char* program_name) {
    printf("Uso: %s [opções] arquivo_entrada\n", program_name);
    printf("\nOpções:\n");
    printf("  -h, --help         Mostra esta ajuda\n");
    printf("  -v, --version      Mostra a versão\n");
    printf("  -d, --debug        Ativa modo debug\n");
    printf("  -V, --verbose      Ativa modo verboso\n");
    printf("  -l, --lexer-only   Executa apenas análise léxica\n");
    printf("  -p, --parser-only  Executa apenas análise sintática\n");
    printf("  -s, --semantic-only Executa apenas análise semântica\n");
    printf("  -t, --print-tokens Imprime tokens (análise léxica)\n");
    printf("  -a, --print-ast    Imprime árvore sintática\n");
    printf("  -S, --print-symbols Imprime tabela de símbolos\n");
    printf("  -c, --print-code   Imprime código intermediário\n");
    printf("  -o, --output FILE  Arquivo de saída\n");
    printf("\nExemplos:\n");
    printf("  %s programa.c-           # Compilação completa\n", program_name);
    printf("  %s -l programa.c-        # Apenas análise léxica\n", program_name);
    printf("  %s -p programa.c-        # Apenas análise sintática\n", program_name);
    printf("  %s -d programa.c-        # Compilação com debug\n", program_name);
    printf("  %s -o saida.txt programa.c-  # Salva saída em arquivo\n", program_name);
}

void print_version(void) {
    printf("Compilador C- versão 1.0\n");
    printf("Implementado por:\n");
    printf("  - Guilherme Fabricio Brito da Rosa\n");
    printf("  - Harisson de Carvalho Alvarenga\n");
    printf("  - Raul Soares de Carvalho\n");
    printf("\nCaracterísticas:\n");
    printf("  - Análise léxica com Flex\n");
    printf("  - Análise sintática com Bison\n");
    printf("  - Análise semântica com tabela de símbolos\n");
    printf("  - Geração de código intermediário de 3 endereços\n");
}

void parse_arguments(int argc, char* argv[], CompilerOptions* options) {
    int c;
    
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'},
        {"debug", no_argument, 0, 'd'},
        {"verbose", no_argument, 0, 'V'},
        {"lexer-only", no_argument, 0, 'l'},
        {"parser-only", no_argument, 0, 'p'},
        {"semantic-only", no_argument, 0, 's'},
        {"print-tokens", no_argument, 0, 't'},
        {"print-ast", no_argument, 0, 'a'},
        {"print-symbols", no_argument, 0, 'S'},
        {"print-code", no_argument, 0, 'c'},
        {"output", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };
    
    while ((c = getopt_long(argc, argv, "hvdVlpstaSco:", long_options, NULL)) != -1) {
        switch (c) {
            case 'h':
                print_usage(argv[0]);
                exit(0);
                break;
            case 'v':
                print_version();
                exit(0);
                break;
            case 'd':
                options->debug_mode = 1;
                break;
            case 'V':
                options->verbose = 1;
                break;
            case 'l':
                options->only_lexer = 1;
                break;
            case 'p':
                options->only_parser = 1;
                break;
            case 's':
                options->only_semantic = 1;
                break;
            case 't':
                options->print_tokens = 1;
                break;
            case 'a':
                options->print_ast = 1;
                break;
            case 'S':
                options->print_symbols = 1;
                break;
            case 'c':
                options->print_code = 1;
                break;
            case 'o':
                options->output_file = safe_strdup(optarg);
                break;
            case '?':
                fprintf(stderr, "Opção inválida. Use -h para ajuda.\n");
                exit(1);
                break;
            default:
                abort();
        }
    }
    
    // Arquivo de entrada deve ser o último argumento
    if (optind < argc) {
        options->input_file = argv[optind];
    }
}

int compile_file(const char* filename, CompilerOptions* options) {
    FILE* input_file = fopen(filename, "r");
    if (!input_file) {
        perror("Erro ao abrir arquivo de entrada");
        return 1;
    }
    
    yyin = input_file;
    yydebug = options->debug_mode;
    errors_count = 0;
    line_number = 1;
    column_number = 1;
    
    if (options->verbose) {
        printf("=== COMPILADOR C- ===\n");
        printf("Arquivo de entrada: %s\n", filename);
        if (options->output_file) {
            printf("Arquivo de saída: %s\n", options->output_file);
        }
        printf("Modo debug: %s\n", options->debug_mode ? "Ativado" : "Desativado");
        printf("\n");
    }
    
    // Inicializa subsistemas
    if (!options->only_lexer) {
        init_semantic_analysis();
        init_code_generation();
    }
    
    if (options->verbose) {
        printf("Iniciando análise sintática...\n");
    }
    
    // Executa o parser
    int result = yyparse();
    
    // Relatório final
    if (options->verbose || errors_count > 0) {
        printf("\n=== RELATÓRIO DE COMPILAÇÃO ===\n");
        if (errors_count == 0) {
            printf("✓ Compilação concluída com sucesso!\n");
        } else {
            printf("✗ Compilação concluída com %d erro(s).\n", errors_count);
        }
        
        if (semantic_errors > 0) {
            printf("✗ %d erro(s) semântico(s) encontrado(s).\n", semantic_errors);
        }
    }
    
    fclose(input_file);
    return result;
}

void setup_compiler(CompilerOptions* options) {
    if (options->verbose) {
        log_info("Configurando compilador...");
    }
    
    // Configurações específicas baseadas nas opções
    if (options->debug_mode) {
        log_info("Modo debug ativado");
    }
    
    if (options->verbose) {
        log_info("Compilador configurado com sucesso");
    }
}

void cleanup_compiler(void) {
    // Limpeza de recursos globais se necessário
    // Por enquanto, a limpeza é feita nas funções finish_*
}
