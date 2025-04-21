#!/bin/bash

# Verifica se os parâmetros foram passados
if [ $# -ne 2 ]; then
  echo "Uso: $0 <nome_compilacao> <nome_arquivo_txt>"
  echo "Exemplo: $0 c-minus-lexer pta_teste.txt"
  exit 1
fi

NOME_COMPILACAO="$1"
NOME_ARQUIVO_BASE="$2" # Agora esperamos apenas o nome do arquivo
PASTA_TESTES="tests" # Define o nome da pasta de testes padrão

# Procura o arquivo de texto no diretório raiz ou na pasta de testes
if [ -f "$NOME_ARQUIVO_BASE" ]; then
  ARQUIVO_TEXTO_COMPLETO="$NOME_ARQUIVO_BASE"
elif [ -f "$PASTA_TESTES/$NOME_ARQUIVO_BASE" ]; then
  ARQUIVO_TEXTO_COMPLETO="$PASTA_TESTES/$NOME_ARQUIVO_BASE"
else
  echo "Erro: Arquivo '$NOME_ARQUIVO_BASE' não encontrado no diretório raiz ou em '$PASTA_TESTES/'."
  exit 1
fi

echo "Arquivo de teste encontrado em: $ARQUIVO_TEXTO_COMPLETO"

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

# Guarda o diretório atual para poder voltar depois
DIR_ATUAL=$(pwd)

cd "$NOME_COMPILACAO"

# Gera o analisador léxico com flex
echo "Gerando analisador léxico com flex..."
flex "$NOME_COMPILACAO.l"
if [ $? -ne 0 ]; then
    echo "Erro ao executar o flex."
    cd "$DIR_ATUAL" # Volta para o diretório original em caso de erro
    exit 1
fi

# Compila o código gerado
echo "Compilando o código C gerado..."
gcc lex.yy.c -ll -o "$NOME_COMPILACAO"
if [ $? -ne 0 ]; then
    echo "Erro ao compilar com gcc."
    cd "$DIR_ATUAL" # Volta para o diretório original em caso de erro
    exit 1
fi

# Executa o programa com o arquivo de entrada (usando o caminho completo)
echo "Executando o analisador léxico com $ARQUIVO_TEXTO_COMPLETO..."
# O caminho para o arquivo de texto agora é relativo ao diretório original (DIR_ATUAL)
# Por isso usamos ../ mais o caminho completo que encontramos
./"$NOME_COMPILACAO" "$DIR_ATUAL/$ARQUIVO_TEXTO_COMPLETO"

cd "$DIR_ATUAL" # Volta para o diretório original
echo "Script concluído."