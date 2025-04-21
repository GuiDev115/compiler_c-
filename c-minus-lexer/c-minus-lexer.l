%{
/*-------------------------- Definitions --------------------------*/
#include<stdio.h>
#include<string.h>

int line_number = 1;
int column_number = 1;
int errors_count = 0;
%}

%x COMMENT

/*ARRUMA O FLOAT*/

delim                   [ \t]
ws                      {delim}+
newline                 \n
digit                   [0-9]
letter                  [a-zA-Z]
integer_num             {digit}+
identifier              {letter}({letter}|{digit})*
array_identifier        {identifier}"["{integer_num}"]"
float_num               {digit}+(\.{digit}+)?([Ee][+-]?{digit}+)?

other                   .

%%
%{
/*----------------------------- Rules -----------------------------*/
%}


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
"else"                  { fprintf(yyout,"%d(%d): %s (PALAVRA RESERVADA else)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"while"                 { fprintf(yyout,"%d(%d): %s (PALAVRA RESERVADA while)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"return"                { fprintf(yyout,"%d(%d): %s (PALAVRA RESERVADA return)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }

 /* --- Operadores --- */

"+"                     { fprintf(yyout,"%d(%d): %s (MAIS +)\n",line_number,column_number,yytext);
                         column_number+=yyleng; }
"-"                     { fprintf(yyout,"%d(%d): %s (MENOS -)\n",line_number,column_number,yytext);
                         column_number+=yyleng; }

"*"                     { fprintf(yyout,"%d(%d): %s (VEZES *)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"/"                     { fprintf(yyout,"%d(%d): %s (DIVIDIDO /)\n",line_number,column_number,yytext);
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
"&&"                    { fprintf(yyout,"%d(%d): %s (E LOGICO &&)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"||"                    { fprintf(yyout,"%d(%d): %s (OU LOGICO ||)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"!"                     { fprintf(yyout,"%d(%d): %s (NAO LOGICO !)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"++"                    { fprintf(yyout,"%d(%d): %s (INCREMENTO ++)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"--"                    { fprintf(yyout,"%d(%d): %s (DECREMENTO --)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }


 /* --- Pontuação --- */

"("                     { fprintf(yyout,"%d(%d): %s (ABRE PARENTESES ()\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
")"                     { fprintf(yyout,"%d(%d): %s (FECHA PARENTESES )\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"{"                     { fprintf(yyout,"%d(%d): %s (ABRE CHAVES {)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"}"                     { fprintf(yyout,"%d(%d): %s (FECHA CHAVES })\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
";"                     { fprintf(yyout,"%d(%d): %s (PONTO E VIRGULA ;)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
","                     { fprintf(yyout,"%d(%d): %s (VIRGULA ,)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"["                     { fprintf(yyout,"%d(%d): %s (ABRE COLCHETES [)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
"]"                     { fprintf(yyout,"%d(%d): %s (FECHA COLCHETES ]\n",line_number,column_number,yytext);
                            column_number+=yyleng; }


{integer_num}                { fprintf(yyout,"%d(%d): %s (NUMERO INTEIRO)\n",line_number,column_number,yytext); 
                         column_number+=yyleng; }
{letter}                { fprintf(yyout,"%d(%d): %s (CHAR)\n",line_number,column_number,yytext); 
                         column_number+=yyleng; }
{float_num}              { fprintf(yyout,"%d(%d): %s (NUMERO REAL)\n",line_number,column_number,yytext); 
                         column_number+=yyleng; }
{identifier}           { fprintf(yyout,"%d(%d): %s (IDENTIFICADOR)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
{array_identifier}     { fprintf(yyout,"%d(%d): %s (IDENTIFICADOR DE VETOR)\n",line_number,column_number,yytext);
                            column_number+=yyleng; }
{ws}                    { column_number+=yyleng; }
{other}                 { fprintf(yyout, "(%d) Erro léxico na linha %d e na coluna %d. Entrada -> \"%s\"\n", 
                         ++errors_count, line_number, column_number, yytext); } 

%%
/*------------------------ User subrotines ------------------------*/
int main(int argc, char *argv[]){
    yyin = fopen(argv[1], "r");
    yyout=stdout;
    yylex();
    fclose(yyin);
    return 0;
}

int yywrap(){
    return 1;
}