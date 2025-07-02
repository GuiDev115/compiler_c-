# Makefile para o Compilador C-
# Autores: Guilherme Fabricio, Harisson Alvarenga, Raul Carvalho

CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
SRCDIR = c-minus
LEXER_DIR = $(SRCDIR)/lexer
PARSER_DIR = $(SRCDIR)/parser
SEMANTIC_DIR = $(SRCDIR)/semantic
TESTDIR = tests/parser

# Arquivos fonte
LEXER_SRC = $(LEXER_DIR)/lexer.l
PARSER_SRC = $(PARSER_DIR)/parser.y
MAIN_SRC = $(SRCDIR)/main.c
SEMANTIC_SRCS = $(SEMANTIC_DIR)/symbol_table.c $(SEMANTIC_DIR)/code_generator.c $(SEMANTIC_DIR)/semantic.c $(SEMANTIC_DIR)/utils.c

# Arquivos gerados
LEXER_OUTPUT = $(LEXER_DIR)/scanner.yy.c
PARSER_OUTPUT = $(PARSER_DIR)/parser.tab.c
PARSER_HEADER = $(PARSER_DIR)/parser.tab.h

# Executável final
TARGET = $(TESTDIR)/c-

.PHONY: all clean test test-correct test-errors

all: $(TARGET)

# Gera o parser (deve vir primeiro para criar o .h)
$(PARSER_OUTPUT) $(PARSER_HEADER): $(PARSER_SRC)
	@echo "Gerando parser com Bison..."
	bison -d -v -t -o $(PARSER_OUTPUT) $(PARSER_SRC)

# Gera o lexer (precisa do parser.tab.h)
$(LEXER_OUTPUT): $(LEXER_SRC) $(PARSER_HEADER)
	@echo "Gerando lexer com Flex..."
	flex -d -o $(LEXER_OUTPUT) $(LEXER_SRC)

# Compila o executável final
$(TARGET): $(LEXER_OUTPUT) $(PARSER_OUTPUT) $(MAIN_SRC) $(SEMANTIC_SRCS)
	@echo "Compilando executável..."
	@mkdir -p $(TESTDIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_SRC) $(LEXER_OUTPUT) $(PARSER_OUTPUT) $(SEMANTIC_SRCS) -lfl

# Testa com programa correto
test-correct: $(TARGET)
	@echo "=== Testando programa correto ==="
	./$(TARGET) $(TESTDIR)/programa_correto.txt

# Testa com programa com erros
test-errors: $(TARGET)
	@echo "=== Testando programa com erros ==="
	./$(TARGET) $(TESTDIR)/programa_com_erros.txt

# Testa ambos
test: test-correct test-errors

# Limpa arquivos gerados
clean:
	@echo "Limpando arquivos gerados..."
	rm -f $(LEXER_OUTPUT)
	rm -f $(PARSER_OUTPUT)
	rm -f $(PARSER_HEADER)
	rm -f $(PARSER_DIR)/parser.output
	rm -f $(TARGET)
	rm -f $(TESTDIR)/log.txt

# Mostra ajuda
help:
	@echo "Uso do Makefile:"
	@echo "  make all         - Compila o compilador C-"
	@echo "  make test        - Executa todos os testes"
	@echo "  make test-correct - Testa programa correto"
	@echo "  make test-errors - Testa programa com erros"
	@echo "  make clean       - Remove arquivos gerados"
	@echo "  make help        - Mostra esta ajuda"
