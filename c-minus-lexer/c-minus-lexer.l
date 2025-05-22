%{

/* C-MINUS LEXER
Feito por: 
    - Guilherme Fabricio Brito da Rosa
    - Harisson de Carvalho Alvarenga
    - Raul Soares de Carvalho
*/    
/*-------------------------- Definicoes --------------------------*/
#include<stdio.h>
#include<string.h>

int line_number = 1;
int column_number = 1;
int errors_count = 0;

int open_braces = 0;    // Para rastrear chaves abertas
int open_brackets = 0;  // Para rastrear colchetes abertos
int open_comments = 0;  // Para rastrear comentários não fechados
int open_parentheses = 0;

%}

%x COMMENT

delim                   [ \t]
ws                      {delim}+
newline                 \n
digito                  [0-9]
letra                   [a-z]
num-int                 {digito}+
int                     {digito}+(\.{digito}+)?([E][+-]?{digito}+)?
ident                   {letra}({letra}|{digito})*
array_ident             {ident}"["{num-int}"]"


other                   .

%%

"/*"                    { BEGIN(COMMENT); 
                         fprintf(yyout,"%d(%d): %s",line_number,column_number,yytext);
                         column_number+=yyleng; }
<COMMENT>[^*\n]*       { fprintf(yyout,"%s",yytext); column_number+=yyleng; }
<COMMENT>"*"+[^*/\n]*  { fprintf(yyout,"%s",yytext); column_number+=yyleng; }
<COMMENT>\n            { fprintf(yyout,"%s",yytext); line_number++; column_number=1; }
<COMMENT>"*"+"/"       { fprintf(yyout,"%s (COMENTARIO)\n",yytext); 
                         BEGIN(INITIAL);
                         column_number+=yyleng; }

 /* --- Palavras Reservadas --- */
"int"                   { fprintf(yyout,"%d(%d): %s (PALAVRA RESERVADA int)\n",line_number,column_number,yytext);
                          column_number+=yyleng; }
"float"                 { fprintf(yyout,"%d(%d): %s (PALAVRA RESERVADA float)\n",line_number,column_number,yytext);
                          column_number+=yyleng; }
"struct"                { fprintf(yyout,"%d(%d): %s (PALAVRA RESERVADA struct)\n",line_number,column_number,yytext);
                          column_number+=yyleng; }
"void"                  { fprintf(yyout,"%d(%d): %s (PALAVRA RESERVADA void)\n",line_number,column_number,yytext);
                          column_number+=yyleng; }
"if"                    { fprintf(yyout,"%d(%d): %s (PALAVRA RESERVADA if)\n",line_number,column_number,yytext);
                          column_number+=yyleng; }

 /* --- Operadores --- */

"+"                     { fprintf(yyout,"%d(%d): %s (MAIS +)\n",line_number,column_number,yytext);
                         column_number+=yyleng; }
"-"                     { fprintf(yyout,"%d(%d): %s (MENOS -)\n",line_number,column_number,yytext);
                         column_number+=yyleng; }

"*"                     { fprintf(yyout,"%d(%d): %s (VEZES *)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"/"                     { fprintf(yyout,"%d(%d): %s (DIVISAO /)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"%"                     { fprintf(yyout,"%d(%d): %s (MODULO %%)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"="                     { fprintf(yyout,"%d(%d): %s (ATRIBUICAO =)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"=="                    { fprintf(yyout,"%d(%d): %s (IGUAL ==)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"!="                    { fprintf(yyout,"%d(%d): %s (DIFERENTE !=)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"<"                     { fprintf(yyout,"%d(%d): %s (MENOR <)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"<="                    { fprintf(yyout,"%d(%d): %s (MENOR IGUAL <=)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
">"                     { fprintf(yyout,"%d(%d): %s (MAIOR >)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
">="                    { fprintf(yyout,"%d(%d): %s (MAIOR IGUAL >=)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }

 /* --- Símbolos --- */
"{"                     { open_braces++; 
                          fprintf(yyout,"%d(%d): %s (ABRE CHAVES {)\n",line_number,column_number,yytext);
                          column_number+=yyleng; }
"}"                     { if (open_braces > 0) open_braces--; 
                          else fprintf(yyout, "(%d) Alerta: Chave fechada sem correspondente aberta na linha %d e coluna %d.\n", 
                                       ++errors_count, line_number, column_number);
                          fprintf(yyout,"%d(%d): %s (FECHA CHAVES })\n",line_number,column_number,yytext);
                          column_number+=yyleng; }

"("                     { open_parentheses++; 
                          fprintf(yyout,"%d(%d): %s (ABRE PARENTESES {)\n",line_number,column_number,yytext);
                          column_number+=yyleng; }
")"                     { if (open_parentheses > 0) open_parentheses--; 
                          else fprintf(yyout, "(%d) Alerta: Parenteses fechada sem correspondente aberta na linha %d e coluna %d.\n", 
                                       ++errors_count, line_number, column_number);
                          fprintf(yyout,"%d(%d): %s (FECHA PARENTESES })\n",line_number,column_number,yytext);
                          column_number+=yyleng; }

"["                     { open_brackets++; 
                          fprintf(yyout,"%d(%d): %s (ABRE COLCHETES [)\n",line_number,column_number,yytext);
                          column_number+=yyleng; }
"]"                     { if (open_brackets > 0) open_brackets--; 
                          else fprintf(yyout, "(%d) Alerta: Colchete fechado sem correspondente aberto na linha %d e coluna %d.\n", 
                                       ++errors_count, line_number, column_number);
                          fprintf(yyout,"%d(%d): %s (FECHA COLCHETES ])\n",line_number,column_number,yytext);
                          column_number+=yyleng; }


  /* --- Pontuação --- */
";"                     { fprintf(yyout,"%d(%d): %s (PONTO E VIRGULA ;)\n",line_number,column_number,yytext);
                          column_number+=yyleng; }
","                     { fprintf(yyout,"%d(%d): %s (VIRGULA ,)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"."                     { fprintf(yyout,"%d(%d): %s (PONTO .)\n",line_number,column_number,yytext);
                         column_number+=yyleng; }

 /* --- Identificadores e Números --- */
{digito}+{letra}({letra}|{digito})*   { fprintf(yyout, "(%d) Erro léxico na linha %d e na coluna %d. Identificador inválido -> \"%s\"\n", 
                                        ++errors_count, line_number, column_number, yytext);
                                        column_number+=yyleng; }


{num-int}               { fprintf(yyout,"%d(%d): %s (NUMERO INTEIRO)\n",line_number,column_number,yytext); 
                         column_number+=yyleng; }
{letra}                 { fprintf(yyout,"%d(%d): %s (CHAR)\n",line_number,column_number,yytext); 
                         column_number+=yyleng; }
{int}                   { fprintf(yyout,"%d(%d): %s (NUMERO REAL)\n",line_number,column_number,yytext); 
                         column_number+=yyleng; }
{ident}                 { fprintf(yyout,"%d(%d): %s (IDENTIFICADOR)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
{newline}               { line_number++; column_number = 1; 
                         fprintf(yyout, "\n"); }
{ws}                    { column_number+=yyleng; }
{other}                 { fprintf(yyout, "(%d) Erro léxico na linha %d e na coluna %d. Entrada -> \"%s\"\n", 
                         ++errors_count, line_number, column_number, yytext); } 

%%

int main(int argc, char *argv[]){
    yyin = fopen(argv[1], "r");
    yyout = stdout;
    yylex();
    fclose(yyin);

    if (open_braces > 0) {
        fprintf(yyout, "(%d) Alerta: %d chave(s) aberta(s) não fechada(s).\n", ++errors_count, open_braces);
    }
    if (open_brackets > 0) {
        fprintf(yyout, "(%d) Alerta: %d colchete(s) aberto(s) não fechado(s).\n", ++errors_count, open_brackets);
    }
    if (open_comments > 0) {
        fprintf(yyout, "(%d) Alerta: %d comentário(s) não fechado(s).\n", ++errors_count, open_comments);
    }
    if(open_parentheses > 0){
        fprintf(yyout, "(%d) Alerta: %d Parentese(s) não fechado(s).\n", ++errors_count, open_parentheses);
    }

    return 0;
}