#!/bin/bash

# 1. PRIMEIRO: Gera o parser (cria parser.tab.h e parser.tab.c na pasta c-minus/parser)
bison -d -v -t -o c-minus/parser/parser.tab.c c-minus/parser/parser.y

# 2. DEPOIS: Gera o lexer (precisa do parser.tab.h)  
flex -d -o c-minus/lexer/scanner.yy.c c-minus/lexer/lexer.l 

# 3. Compila (ajusta os caminhos dos arquivos gerados e cria o executável em tests/parser)
gcc -o tests/parser/c- c-minus/lexer/scanner.yy.c c-minus/parser/parser.tab.c -lfl

# 4. Habilita debug
export YYDEBUG=1

# 5. Executa (agora o executável está em tests/parser)
./tests/parser/c- tests/parser/teste.txt 2> log.txt