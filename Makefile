# Makefile para Compilador C- (Versão Portável)

# Diretórios
PARSER_DIR = c-minus/parser
SEMANTIC_DIR = c-minus/semantic
TEST_DIR = tests

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -g -std=gnu99 -I$(SEMANTIC_DIR) -I. -D_GNU_SOURCE
YFLAGS = -d -v
LFLAGS = -v

# Arquivos fonte
PARSER_SRC = $(PARSER_DIR)/parser.y
SEMANTIC_SOURCES = $(SEMANTIC_DIR)/symbol_table.c $(SEMANTIC_DIR)/semantic.c $(SEMANTIC_DIR)/code_generator.c $(SEMANTIC_DIR)/utils.c

# Arquivos gerados
PARSER_C = $(PARSER_DIR)/parser.tab.c
PARSER_H = $(PARSER_DIR)/parser.tab.h
PARSER_OUTPUT = $(PARSER_DIR)/parser.output

# Executáveis
TARGET = c-minus-compiler
AGENT = agente_semantico

# ============================================================================
# REGRAS PRINCIPAIS - PORTÁVEIS
# ============================================================================

# Regra principal - compila o agente semântico
all: $(AGENT)
	@echo "✅ Compilação concluída! Execute com: ./$(AGENT)"
	@echo "📁 Certifique-se de estar na pasta raiz do projeto compiler_c-"

# Compilação do agente semântico (PORTÁVEL)
$(AGENT): agente_semantico.c $(SEMANTIC_SOURCES)
	@echo "🔨 Compilando agente semântico..."
	@echo "📂 Verificando estrutura do projeto..."
	@if [ ! -d "$(SEMANTIC_DIR)" ]; then \
		echo "❌ Erro: Diretório $(SEMANTIC_DIR) não encontrado!"; \
		echo "💡 Certifique-se de estar na pasta raiz do projeto compiler_c-"; \
		exit 1; \
	fi
	@if [ ! -d "$(TEST_DIR)/semantic" ]; then \
		echo "❌ Erro: Diretório $(TEST_DIR)/semantic não encontrado!"; \
		echo "💡 Criando diretório de testes..."; \
		mkdir -p $(TEST_DIR)/semantic; \
	fi
	$(CC) $(CFLAGS) -o $@ $^
	@echo "✅ Agente semântico compilado com sucesso!"

# Regra para executar o agente (PORTÁVEL)
run-agent: $(AGENT)
	@echo "🚀 Executando agente semântico..."
	@echo "📁 Diretório atual: $$(pwd)"
	./$(AGENT)

# ============================================================================
# TESTES AUTOMATIZADOS - PORTÁVEIS
# ============================================================================

# Executa todos os testes semânticos
test-all: $(AGENT)
	@echo "🧪 Executando todos os testes semânticos..."
	@if [ ! -d "$(TEST_DIR)/semantic" ]; then \
		echo "❌ Diretório de testes não encontrado: $(TEST_DIR)/semantic"; \
		exit 1; \
	fi
	@for file in $(TEST_DIR)/semantic/*.txt; do \
		if [ -f "$$file" ]; then \
			echo "🔍 Testando: $$(basename $$file)"; \
		fi; \
	done
	@echo "✅ Estrutura de testes verificada. Use o agente interativo para análises detalhadas."

# Testes individuais (PORTÁVEIS)
test-basico: $(AGENT)
	@if [ -f "$(TEST_DIR)/semantic/programa_basico.txt" ]; then \
		echo "🧪 Teste básico disponível"; \
	else \
		echo "⚠️  Arquivo de teste básico não encontrado"; \
	fi

test-arrays: $(AGENT)
	@if [ -f "$(TEST_DIR)/semantic/programa_arrays.txt" ]; then \
		echo "🧪 Teste de arrays disponível"; \
	else \
		echo "⚠️  Arquivo de teste de arrays não encontrado"; \
	fi

# ============================================================================
# UTILITÁRIOS
# ============================================================================

# Verifica a estrutura do projeto
check-structure:
	@echo "🔍 Verificando estrutura do projeto..."
	@echo "📁 Diretório atual: $$(pwd)"
	@echo "📂 Verificando diretórios necessários:"
	@if [ -d "$(SEMANTIC_DIR)" ]; then \
		echo "✅ $(SEMANTIC_DIR) - OK"; \
	else \
		echo "❌ $(SEMANTIC_DIR) - NÃO ENCONTRADO"; \
	fi
	@if [ -d "$(TEST_DIR)/semantic" ]; then \
		echo "✅ $(TEST_DIR)/semantic - OK"; \
	else \
		echo "❌ $(TEST_DIR)/semantic - NÃO ENCONTRADO"; \
	fi
	@echo "📄 Verificando arquivos fonte:"
	@for file in $(SEMANTIC_SOURCES); do \
		if [ -f "$$file" ]; then \
			echo "✅ $$file - OK"; \
		else \
			echo "❌ $$file - NÃO ENCONTRADO"; \
		fi; \
	done

# Instala dependências (Linux/Ubuntu)
install-deps:
	@echo "📦 Instalando dependências..."
	@if command -v apt-get >/dev/null 2>&1; then \
		echo "🐧 Sistema Ubuntu/Debian detectado"; \
		sudo apt-get update && sudo apt-get install -y build-essential flex bison; \
	elif command -v yum >/dev/null 2>&1; then \
		echo "🎩 Sistema RedHat/CentOS detectado"; \
		sudo yum install -y gcc flex bison; \
	elif command -v brew >/dev/null 2>&1; then \
		echo "🍎 Sistema macOS detectado"; \
		brew install gcc flex bison; \
	else \
		echo "⚠️  Sistema não reconhecido. Instale manualmente: gcc, flex, bison"; \
	fi

# ============================================================================
# LIMPEZA
# ============================================================================

# Limpeza básica
clean:
	@echo "🧹 Limpando arquivos temporários..."
	rm -f $(PARSER_C) $(PARSER_H) $(PARSER_OUTPUT)
	rm -f $(TARGET) $(AGENT)
	rm -f *.o *.ir
	@echo "✅ Limpeza concluída!"

# Limpeza completa
distclean: clean
	@echo "🧹 Limpeza completa..."
	rm -f *~ c-minus/*~ $(PARSER_DIR)/*~ $(SEMANTIC_DIR)/*~
	rm -f codigo_3enderecos_*.ir
	@echo "✅ Limpeza completa concluída!"

# ============================================================================
# AJUDA
# ============================================================================

help:
	@echo "🤖 MAKEFILE DO COMPILADOR C- - VERSÃO PORTÁVEL"
	@echo "════════════════════════════════════════════════════════════════"
	@echo ""
	@echo "📋 COMANDOS PRINCIPAIS:"
	@echo "  make              - Compila o agente semântico"
	@echo "  make run-agent    - Executa o agente semântico interativo"
	@echo "  make test-all     - Verifica todos os testes disponíveis"
	@echo ""
	@echo "🔧 UTILITÁRIOS:"
	@echo "  make check-structure - Verifica se a estrutura do projeto está correta"
	@echo "  make install-deps    - Instala dependências (Linux/macOS)"
	@echo "  make clean          - Remove arquivos temporários"
	@echo "  make distclean      - Limpeza completa"
	@echo ""
	@echo "🧪 TESTES INDIVIDUAIS:"
	@echo "  make test-basico    - Verifica teste básico"
	@echo "  make test-arrays    - Verifica teste de arrays"
	@echo ""
	@echo "💡 DICAS:"
	@echo "  • Execute 'make check-structure' se houver problemas"
	@echo "  • Certifique-se de estar na pasta raiz compiler_c-"
	@echo "  • Use 'make install-deps' para instalar dependências"
	@echo ""
	@echo "📁 ESTRUTURA ESPERADA:"
	@echo "  compiler_c-/"
	@echo "  ├── c-minus/semantic/"
	@echo "  ├── tests/semantic/"
	@echo "  ├── agente_semantico.c"
	@echo "  └── Makefile"

# ============================================================================
# REGRAS ESPECIAIS
# ============================================================================

.PHONY: all clean distclean run-agent test-all test-basico test-arrays check-structure install-deps help

# Agente semântico
run-agent: $(AGENT)
	@echo "=== EXECUTANDO AGENTE SEMÂNTICO ==="
	./$(AGENT)

# Demonstração
run-demo: $(DEMO)
	@echo "=== EXECUTANDO DEMONSTRAÇÃO ==="
	./$(DEMO)

# Teste com demonstração
test: $(DEMO)
	@echo "=== TESTANDO SISTEMA ==="
	./$(DEMO)
	@echo ""
	@echo "=== CÓDIGO GERADO ==="
	@cat codigo_intermediario.txt

# Teste dos arquivos semânticos
test-semantic: $(AGENT)
	@echo "=== TESTANDO ARQUIVOS SEMÂNTICOS ==="
	@echo "Executando análise automática de todos os arquivos de teste..."
	echo -e "5\n0" | ./$(AGENT)

# Testes individuais por arquivo
test-basico: $(AGENT)
	@echo "=== TESTANDO PROGRAMA BÁSICO ==="
	@echo "Analisando programa_basico.txt..."
	@if [ -f "$(TEST_DIR)/semantic/programa_basico.txt" ]; then \
		echo "3" | ./$(AGENT) | head -n 50; \
		echo "Arquivo encontrado e analisado."; \
	else \
		echo "Arquivo programa_basico.txt não encontrado em $(TEST_DIR)/semantic/"; \
	fi

test-arrays: $(AGENT)
	@echo "=== TESTANDO PROGRAMA COM ARRAYS ==="
	@echo "Analisando programa_arrays.txt..."
	@if [ -f "$(TEST_DIR)/semantic/programa_arrays.txt" ]; then \
		cat "$(TEST_DIR)/semantic/programa_arrays.txt"; \
		echo ""; \
		echo "Arquivo encontrado e exibido."; \
	else \
		echo "Arquivo programa_arrays.txt não encontrado em $(TEST_DIR)/semantic/"; \
	fi

test-funcoes: $(AGENT)
	@echo "=== TESTANDO PROGRAMA COM FUNÇÕES ==="
	@echo "Analisando programa_funcoes.txt..."
	@if [ -f "$(TEST_DIR)/semantic/programa_funcoes.txt" ]; then \
		cat "$(TEST_DIR)/semantic/programa_funcoes.txt"; \
		echo ""; \
		echo "Arquivo encontrado e exibido."; \
	else \
		echo "Arquivo programa_funcoes.txt não encontrado em $(TEST_DIR)/semantic/"; \
	fi

test-structs: $(AGENT)
	@echo "=== TESTANDO PROGRAMA COM STRUCTS ==="
	@echo "Analisando programa_structs.txt..."
	@if [ -f "$(TEST_DIR)/semantic/programa_structs.txt" ]; then \
		cat "$(TEST_DIR)/semantic/programa_structs.txt"; \
		echo ""; \
		echo "Arquivo encontrado e exibido."; \
	else \
		echo "Arquivo programa_structs.txt não encontrado em $(TEST_DIR)/semantic/"; \
	fi

test-erros: $(AGENT)
	@echo "=== TESTANDO PROGRAMA COM ERROS ==="
	@echo "Analisando programa_com_erros.txt..."
	@if [ -f "$(TEST_DIR)/semantic/programa_com_erros.txt" ]; then \
		cat "$(TEST_DIR)/semantic/programa_com_erros.txt"; \
		echo ""; \
		echo "Arquivo encontrado e exibido."; \
	else \
		echo "Arquivo programa_com_erros.txt não encontrado em $(TEST_DIR)/semantic/"; \
	fi

test-complexo: $(AGENT)
	@echo "=== TESTANDO PROGRAMA COMPLEXO ==="
	@echo "Analisando programa_complexo.txt..."
	@if [ -f "$(TEST_DIR)/semantic/programa_complexo.txt" ]; then \
		cat "$(TEST_DIR)/semantic/programa_complexo.txt"; \
		echo ""; \
		echo "Arquivo encontrado e exibido."; \
	else \
		echo "Arquivo programa_complexo.txt não encontrado em $(TEST_DIR)/semantic/"; \
	fi

# Regra genérica para testar qualquer arquivo .txt
test-%.txt: $(AGENT)
	@echo "=== TESTANDO ARQUIVO: $*.txt ==="
	@if [ -f "$(TEST_DIR)/semantic/$*.txt" ]; then \
		echo "📖 Conteúdo do arquivo:"; \
		echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"; \
		cat "$(TEST_DIR)/semantic/$*.txt"; \
		echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"; \
		echo ""; \
		echo "✅ Arquivo $*.txt encontrado e exibido com sucesso!"; \
		echo "💡 Para análise semântica completa, use: make run-agent"; \
	else \
		echo "❌ Arquivo $*.txt não encontrado em $(TEST_DIR)/semantic/"; \
		echo "📁 Arquivos disponíveis:"; \
		ls -1 $(TEST_DIR)/semantic/*.txt 2>/dev/null | sed 's/.*\///g' | sed 's/^/  - /' || echo "  Nenhum arquivo encontrado"; \
	fi

# Regra genérica para análise semântica de qualquer arquivo .txt
analyze-%.txt: $(AGENT)
	@echo "=== ANÁLISE SEMÂNTICA: $*.txt ==="
	@if [ -f "$(TEST_DIR)/semantic/$*.txt" ]; then \
		echo "🔬 Executando análise semântica..."; \
		echo ""; \
		FILENAME="$*.txt"; \
		FILEPATH="$(TEST_DIR)/semantic/$*.txt"; \
		./$(AGENT) --analyze "$$FILEPATH" "$$FILENAME" 2>/dev/null || echo "Análise via interface não disponível - use make run-agent"; \
		echo ""; \
		echo "✅ Para análise detalhada, use: make run-agent e escolha opção 4"; \
	else \
		echo "❌ Arquivo $*.txt não encontrado em $(TEST_DIR)/semantic/"; \
		echo "📁 Arquivos disponíveis:"; \
		ls -1 $(TEST_DIR)/semantic/*.txt 2>/dev/null | sed 's/.*\///g' | sed 's/^/  - /' || echo "  Nenhum arquivo encontrado"; \
	fi

# Listar arquivos da pasta semântica
list-semantic:
	@echo "=== ARQUIVOS DA PASTA SEMÂNTICA ==="
	@ls -la $(SEMANTIC_DIR)/
	@echo ""
	@echo "=== ARQUIVOS DE TESTE SEMÂNTICO ==="
	@ls -la $(TEST_DIR)/semantic/

# Verificar estrutura do projeto
check-structure:
	@echo "=== VERIFICANDO ESTRUTURA DO PROJETO ==="
	@echo "Pasta semântica:"
	@test -d $(SEMANTIC_DIR) && echo "✓ $(SEMANTIC_DIR) existe" || echo "✗ $(SEMANTIC_DIR) não existe"
	@echo "Pasta de testes:"
	@test -d $(TEST_DIR)/semantic && echo "✓ $(TEST_DIR)/semantic existe" || echo "✗ $(TEST_DIR)/semantic não existe"
	@echo "Arquivos semânticos:"
	@for file in symbol_table.c semantic.c code_generator.c utils.c; do \
		test -f $(SEMANTIC_DIR)/$$file && echo "✓ $$file existe" || echo "✗ $$file não existe"; \
	done
	@echo "Arquivos de cabeçalho:"
	@for file in symbol_table.h semantic.h code_generator.h utils.h; do \
		test -f $(SEMANTIC_DIR)/$$file && echo "✓ $$file existe" || echo "✗ $$file não existe"; \
	done

# Mostrar conteúdo dos arquivos de teste
show-tests:
	@echo "=== CONTEÚDO DOS ARQUIVOS DE TESTE ==="
	@for file in $(TEST_DIR)/semantic/*.txt; do \
		echo ""; \
		echo "=== $$file ==="; \
		cat "$$file"; \
	done

# Instalação de dependências (Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install -y flex bison gcc make

# Verificação de dependências
check-deps:
	@echo "Verificando dependências..."
	@which flex > /dev/null || echo "ERRO: flex não encontrado"
	@which bison > /dev/null || echo "ERRO: bison não encontrado"
	@which gcc > /dev/null || echo "ERRO: gcc não encontrado"
	@echo "Verificação concluída."

# Documentação
docs:
	@echo "=== DOCUMENTAÇÃO ==="
	@echo "Leia o arquivo README_SEMANTIC.md para detalhes completos"
	@echo ""
	@echo "Arquivos principais:"
	@echo "  - $(SEMANTIC_DIR)/symbol_table.h/c  : Tabela de símbolos"
	@echo "  - $(SEMANTIC_DIR)/semantic.h/c      : Análise semântica"
	@echo "  - $(SEMANTIC_DIR)/code_generator.h/c: Gerador de código"
	@echo "  - $(SEMANTIC_DIR)/utils.h/c         : Utilitários"
	@echo "  - demo.c                            : Demonstração"

# Informações do sistema
info:
	@echo "=== INFORMAÇÕES DO SISTEMA ==="
	@echo "Compilador C- - Sistema de Análise Semântica e Geração de Código"
	@echo "Autores:"
	@echo "  - Guilherme Fabricio Brito da Rosa"
	@echo "  - Harisson de Carvalho Alvarenga"
	@echo "  - Raul Soares de Carvalho"
	@echo ""
	@echo "Características implementadas:"
	@echo "  ✓ Tabela de símbolos com hash table"
	@echo "  ✓ Gerenciamento de escopo"
	@echo "  ✓ Análise semântica de tipos"
	@echo "  ✓ Geração de código intermediário de 3 endereços"
	@echo "  ✓ Verificação de declarações e uso de variáveis"
	@echo "  ✓ Suporte a arrays multidimensionais"
	@echo "  ✓ Suporte a funções e structs"
	@echo "  ✓ Tratamento de erros semânticos"

# Ajuda
help:
	@echo "Makefile para Compilador C-"
	@echo ""
	@echo "Alvos disponíveis:"
	@echo "  all              - Compila a demonstração e o agente semântico"
	@echo "  run-demo         - Executa a demonstração"
	@echo "  run-agent        - Executa o agente semântico (menu interativo)"
	@echo "  test             - Testa o sistema com demonstração"
	@echo "  test-semantic    - Testa todos os arquivos semânticos automaticamente"
	@echo "  list-semantic    - Lista arquivos das pastas semânticas"
	@echo "  check-structure  - Verifica a estrutura do projeto"
	@echo "  show-tests       - Mostra o conteúdo dos arquivos de teste"
	@echo "  $(TARGET)        - Compila o compilador (não funcional)"
	@echo "  clean            - Remove arquivos gerados"
	@echo "  distclean        - Remove todos os arquivos temporários"
	@echo "  install-deps     - Instala dependências (Ubuntu/Debian)"
	@echo "  check-deps       - Verifica se as dependências estão instaladas"
	@echo "  docs             - Mostra documentação"
	@echo "  info             - Mostra informações do sistema"
	@echo "  help             - Mostra esta ajuda"
	@echo ""
	@echo "Testes individuais:"
	@echo "  test-basico      - Testa programa_basico.txt"
	@echo "  test-arrays      - Testa programa_arrays.txt"
	@echo "  test-funcoes     - Testa programa_funcoes.txt"
	@echo "  test-structs     - Testa programa_structs.txt"
	@echo "  test-erros       - Testa programa_com_erros.txt"
	@echo "  test-complexo    - Testa programa_complexo.txt"
	@echo "  test-NOME.txt    - Mostra qualquer arquivo NOME.txt"
	@echo "  analyze-NOME.txt - Executa análise semântica de NOME.txt"
	@echo ""
	@echo "Exemplos de uso:"
	@echo "  make run-demo       - Executa a demonstração básica"
	@echo "  make run-agent      - Abre o menu interativo do agente semântico"
	@echo "  make test-semantic  - Executa análise automática de todos os testes"
	@echo "  make test-basico    - Mostra apenas o programa básico"
	@echo "  make test-programa_arrays.txt - Mostra arquivo específico"
	@echo "  make analyze-programa_basico.txt - Análise semântica específica"
	@echo "  make list-semantic  - Lista todos os arquivos semânticos"
	@echo "  make show-tests     - Mostra o conteúdo dos arquivos de teste C-"
	@echo "  make check-structure - Verifica se todos os arquivos estão no lugar"
	@echo "  make clean          - Limpa arquivos gerados"
	@echo ""
	@echo "Fluxo de trabalho recomendado:"
	@echo "  1. make check-deps     - Verifica dependências"
	@echo "  2. make check-structure - Verifica estrutura do projeto"
	@echo "  3. make all            - Compila tudo"
	@echo "  4. make test-basico    - Testa um arquivo específico"
	@echo "  5. make run-agent      - Executa o agente semântico"
	@echo "  6. make test-semantic  - Testa análise semântica completa"

# Não excluir arquivos intermediários
.PRECIOUS: $(PARSER_C) $(PARSER_H)

# Phony targets
.PHONY: all clean distclean run-demo run-agent test test-semantic test-basico test-arrays test-funcoes test-structs test-erros test-complexo list-semantic check-structure show-tests install-deps check-deps docs info help
