%{
/*-------------------------- Definitions --------------------------*/
#include <stdio.h>
#include <string.h>

int line_number = 1;
int column_number = 1;
int errors_count = 0;

// Função auxiliar para imprimir tokens
void print_token(const char* token_type) {
    fprintf(yyout, "%d(%d): %s (%s)\n", line_number, column_number, yytext, token_type);
    column_number += yyleng;
}

%}

%x COMMENT

delim                   [ \t]
ws                      {delim}+
newline                 \n
digit                   [0-9]
letter                  [a-zA-Z]
identifier              {letter}({letter}|{digit})*
integer_num             {digit}+
float_num               {digit}+(\.{digit}+)?([Ee][+-]?{digit}+)? | {digit}*\.{digit}+([Ee][+-]?{digit}+)?
// Note: A definição de <num> na gramática é um pouco ambígua sobre números como .5 ou 1.
// Esta definição tenta cobrir números inteiros, decimais e com notação científica.
// A definição de <num-int> é coberta por integer_num.

other                   .

%%
%{
/*----------------------------- Rules -----------------------------*/
%}

"/*"                    { BEGIN(COMMENT);
                         // Não imprime o início do comentário, apenas ajusta a coluna
                         column_number += yyleng; }
<COMMENT>[^*\n]+       { /* Ignora conteúdo do comentário */ column_number += yyleng; }
<COMMENT>"*"+[^*/\n]*  { /* Ignora conteúdo do comentário */ column_number += yyleng; }
<COMMENT>{newline}     { /* Ignora nova linha no comentário */ line_number++; column_number = 1; }
<COMMENT>"*"+"/"       { BEGIN(INITIAL);
                         // Não imprime o fim do comentário, apenas ajusta a coluna
                         column_number += yyleng; }

 /* --- Palavras Reservadas --- */
"int"                   { print_token("PALAVRA_RESERVADA_INT"); }
"float"                 { print_token("PALAVRA_RESERVADA_FLOAT"); }
"char"                  { print_token("PALAVRA_RESERVADA_CHAR"); } // Adicionado 'char'
"struct"                { print_token("PALAVRA_RESERVADA_STRUCT"); }
"if"                    { print_token("PALAVRA_RESERVADA_IF"); }
"else"                  { print_token("PALAVRA_RESERVADA_ELSE"); }
"while"                 { print_token("PALAVRA_RESERVADA_WHILE"); }
"void"                  { print_token("PALAVRA_RESERVADA_VOID"); }
"return"                { print_token("PALAVRA_RESERVADA_RETURN"); }

 /* --- Operadores --- */
"+"                     { print_token("OPERADOR_SOMA"); }
"-"                     { print_token("OPERADOR_SUBTRACAO"); }
"*"                     { print_token("OPERADOR_MULTIPLICACAO"); }
"/"                     { print_token("OPERADOR_DIVISAO"); }
"<="                    { print_token("OPERADOR_MENOR_IGUAL"); }
"<"                     { print_token("OPERADOR_MENOR"); }
">"                     { print_token("OPERADOR_MAIOR"); }
">="                    { print_token("OPERADOR_MAIOR_IGUAL"); }
"=="                    { print_token("OPERADOR_IGUAL"); }
"!="                    { print_token("OPERADOR_DIFERENTE"); }
"="                     { print_token("OPERADOR_ATRIBUICAO"); }

 /* --- Pontuação --- */
";"                     { print_token("PONTUACAO_PV"); }
","                     { print_token("PONTUACAO_VIRGULA"); }
"("                     { print_token("PONTUACAO_ABRE_PARENTESES"); }
")"                     { print_token("PONTUACAO_FECHA_PARENTESES"); }
"["                     { print_token("PONTUACAO_ABRE_COLCHETES"); }
"]"                     { print_token("PONTUACAO_FECHA_COLCHETES"); }
"{"                     { print_token("PONTUACAO_ABRE_CHAVES"); }
"}"                     { print_token("PONTUACAO_FECHA_CHAVES"); }

 /* --- Números --- */
{float_num}             { print_token("NUM_FLOAT"); } // Deve vir antes de integer_num
{integer_num}           { print_token("NUM_INT"); }

 /* --- Identificadores --- */
{identifier}            { print_token("IDENTIFICADOR"); }

 /* --- Whitespace e Nova Linha --- */
{ws}                    { /* Ignora whitespace */ column_number += yyleng; }
{newline}               { line_number++; column_number = 1; /* Ignora nova linha */ }

 /* --- Erros --- */
{other}                 { fprintf(stderr, "(%d) Erro léxico na linha %d e coluna %d. Caractere inesperado -> \"%s\"\n",
                         ++errors_count, line_number, column_number, yytext);
                         column_number += yyleng; // Avança a coluna mesmo em erro
                       }

%%
/*------------------------ User subrotines ------------------------*/
int main(int argc, char *argv[]){
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }
    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }
    yyin = inputFile; // Define a entrada do Flex
    yyout = stdout;   // Define a saída padrão para os prints dos tokens

    yylex(); // Executa o analisador léxico

    fclose(yyin);

    if (errors_count > 0) {
        fprintf(stderr, "\nAnálise léxica concluída com %d erro(s).\n", errors_count);
        return 1; // Retorna erro se houver erros léxicos
    } else {
        printf("\nAnálise léxica concluída com sucesso.\n");
    }

    return 0;
}

int yywrap(){
    // Indica ao Flex que não há mais arquivos para processar
    return 1;
}
