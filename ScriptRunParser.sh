#!/bin/bash

# Verifica se o parâmetro foi passado
if [ $# -ne 1 ]; then
  echo "Uso: $0 <nome_arquivo_txt>"
  echo "Exemplo: $0 teste.txt"
  exit 1
fi

NOME_ARQUIVO_BASE="$1" 
PASTA_TESTES="tests/parser" 

if [ -f "$NOME_ARQUIVO_BASE" ]; then
  ARQUIVO_TEXTO_COMPLETO="$NOME_ARQUIVO_BASE"
elif [ -f "$PASTA_TESTES/$NOME_ARQUIVO_BASE" ]; then
  ARQUIVO_TEXTO_COMPLETO="$PASTA_TESTES/$NOME_ARQUIVO_BASE"
else
  echo "Erro: Arquivo '$NOME_ARQUIVO_BASE' não encontrado no diretório raiz ou em '$PASTA_TESTES/'."
  exit 1
fi

echo "Arquivo de teste encontrado em: $ARQUIVO_TEXTO_COMPLETO"

if [ ! -d "c-minus/parser" ]; then
  echo "Erro: Diretório 'c-minus/parser' não encontrado."
  exit 1
fi

if [ ! -d "c-minus/lexer" ]; then
  echo "Erro: Diretório 'c-minus/lexer' não encontrado."
  exit 1
fi

if [ ! -f "c-minus/parser/parser.y" ]; then
  echo "Erro: Arquivo 'c-minus/parser/parser.y' não encontrado."
  exit 1
fi

if [ ! -f "c-minus/lexer/lexer.l" ]; then
  echo "Erro: Arquivo 'c-minus/lexer/lexer.l' não encontrado."
  exit 1
fi

mkdir -p tests/parser

# 1. PRIMEIRO: Gera o parser (cria parser.tab.h e parser.tab.c na pasta c-minus/parser)
bison -d -v -t -o c-minus/parser/parser.tab.c c-minus/parser/parser.y
if [ $? -ne 0 ]; then
    echo "Erro ao executar o bison."
    exit 1
fi

# 2. DEPOIS: Gera o lexer (precisa do parser.tab.h)  
flex -d -o c-minus/lexer/scanner.yy.c c-minus/lexer/lexer.l 
if [ $? -ne 0 ]; then
    echo "Erro ao executar o flex."
    exit 1
fi

# 3. Compila (ajusta os caminhos dos arquivos gerados e cria o executável em tests/parser)
gcc -o tests/parser/c- c-minus/lexer/scanner.yy.c c-minus/parser/parser.tab.c c-minus/semantic/symbol_table.c c-minus/semantic/code_generator.c c-minus/semantic/semantic.c -lfl
if [ $? -ne 0 ]; then
    echo "Erro ao compilar com gcc."
    exit 1
fi

echo -e "\nExecutando o parser com $ARQUIVO_TEXTO_COMPLETO..."
# 4. Habilita debug
export YYDEBUG=1

# 5. Executa (executável e log em tests/parser)
./tests/parser/c- "$ARQUIVO_TEXTO_COMPLETO" 2> tests/parser/log.txt

echo -e "\nScript concluído com sucesso!"
echo "Log de debug salvo em: tests/parser/log.txt"

# 6. Filtra e mostra apenas os erros sintáticos
echo -e "\n=== ERROS SINTÁTICOS ENCONTRADOS ==="
if grep -E "^\([0-9]+\) Erro sintático" tests/parser/log.txt; then
    echo -e "\n=== FIM DOS ERROS SINTÁTICOS ==="
else
    echo "Nenhum erro sintático encontrado!"
fi