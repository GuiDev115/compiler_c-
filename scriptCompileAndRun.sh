#!/bin/bash

# Verifica se os parâmetros foram passados
if [ $# -ne 2 ]; then
  echo "Uso: $0 <nome_compilacao> <arquivo_txt>"
  exit 1
fi

NOME_COMPILACAO="$1"
ARQUIVO_TEXTO="$2"

# Verifica se o arquivo de texto existe
if [ ! -f "$ARQUIVO_TEXTO" ]; then
  echo "Erro: Arquivo '$ARQUIVO_TEXTO' não encontrado."
  exit 1
fi

# Verifica se o diretório de compilação existe
if [ ! -d "$NOME_COMPILACAO" ]; then
  echo "Erro: Diretório '$NOME_COMPILACAO' não encontrado."
  exit 1
fi

# Verifica se o arquivo .l existe
if [ ! -f "$NOME_COMPILACAO/$NOME_COMPILACAO.l" ]; then
  echo "Erro: Arquivo '$NOME_COMPILACAO/$NOME_COMPILACAO.l' não encontrado."
  exit 1
fi

cd "$NOME_COMPILACAO"

# Gera o analisador léxico com flex
echo "Gerando analisador léxico com flex..."
flex "$NOME_COMPILACAO.l"
if [ $? -ne 0 ]; then
    echo "Erro ao executar o flex."
    exit 1
fi

# Compila o código gerado
echo "Compilando o código C gerado..."
gcc lex.yy.c -ll -o "$NOME_COMPILACAO"
if [ $? -ne 0 ]; then
    echo "Erro ao compilar com gcc."
    exit 1
fi

# Executa o programa com o arquivo de entrada
echo "Executando o analisador léxico..."
./"$NOME_COMPILACAO" ../"$ARQUIVO_TEXTO"

cd .. # Volta para o diretório original