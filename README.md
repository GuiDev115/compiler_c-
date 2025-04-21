# Analisador Léxico C-Minus

Este projeto implementa um analisador léxico para a linguagem C-Minus utilizando Flex.

## Estrutura do Projeto

*   `c-minus-lexer/`: Contém os arquivos do analisador léxico.
    *   [`c-minus-lexer.l`](c-minus-lexer/c-minus-lexer.l): Arquivo de definição do Flex para o analisador léxico.
    *   [`lex.yy.c`](c-minus-lexer/lex.yy.c): Código C gerado pelo Flex.
    *   [`c-minus-lexer`](c-minus-lexer/c-minus-lexer): Executável compilado do analisador léxico.
*   [`scriptCompileAndRun.sh`](scriptCompileAndRun.sh): Script para compilar e executar o analisador léxico.
*   [`teste.txt`](teste.txt): Arquivo de exemplo para testar o analisador léxico.
*   [`README.md`](README.md): Este arquivo.

## Dependências

*   **Flex**: Ferramenta para gerar analisadores léxicos.
*   **GCC**: Compilador C para compilar o código gerado pelo Flex.

## Como Compilar e Executar

1.  **Certifique-se de ter o Flex e o GCC instalados.**
2.  **Dê permissão de execução ao script:**
    ```sh
    chmod +x scriptCompileAndRun.sh
    ```
3.  **Execute o script:**
    O script [`scriptCompileAndRun.sh`](scriptCompileAndRun.sh) automatiza o processo de compilação e execução. Ele recebe dois argumentos:
    *   O nome do diretório de compilação (que contém o arquivo `.l`).
    *   O caminho para o arquivo de texto de entrada.

    Exemplo de uso:
    ```sh
    ./scriptCompileAndRun.sh c-minus-lexer teste.txt
    ```
    Este comando irá:
    *   Navegar até o diretório `c-minus-lexer`.
    *   Gerar o arquivo `lex.yy.c` usando `flex c-minus-lexer.l`.
    *   Compilar `lex.yy.c` para criar o executável `c-minus-lexer` usando `gcc lex.yy.c -ll -o c-minus-lexer`.
    *   Executar o analisador léxico `./c-minus-lexer` usando o arquivo `../teste.txt` como entrada.

    A saída do analisador léxico (tokens reconhecidos ou erros) será exibida no terminal.

## Funcionamento

O arquivo [`c-minus-lexer.l`](c-minus-lexer/c-minus-lexer.l) define as regras (usando expressões regulares) para reconhecer os tokens da linguagem C-Minus (palavras reservadas, identificadores, números, operadores, pontuação, comentários). Para cada regra, uma ação em C é definida (geralmente imprimir o token encontrado e sua classificação). O script [`scriptCompileAndRun.sh`](scriptCompileAndRun.sh) utiliza o `flex` para gerar o código C correspondente ([`lex.yy.c`](c-minus-lexer/lex.yy.c)) e o `gcc` para compilá-lo, criando o executável [`c-minus-lexer`](c-minus-lexer/c-minus-lexer) que pode processar um arquivo de entrada ([`teste.txt`](teste.txt)).