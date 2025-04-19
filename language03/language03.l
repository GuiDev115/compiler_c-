%{
/*-------------------------- Definitions --------------------------*/
#include<stdio.h>
#include<string.h>

int line_number = 1;
int column_number = 1;
int errors_count = 0;
%}

%x COMMENT

delim                   [ \t\n]
ws                      {delim}+
digit                   [0-9]
number                  {digit}+(\.{digit}+)?
numbers                {number}+
numberwithoutdot        {number}+
numberwithdot          {number}+\.[0-9]+
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

"+"                     { fprintf(yyout,"%d(%d): %s (MAIS +)\n",line_number,column_number,yytext);
                         column_number+=yyleng; }
"-"                     { fprintf(yyout,"%d(%d): %s (MENOS -)\n",line_number,column_number,yytext);
                         column_number+=yyleng; }
"\n"                    { line_number++; column_number=1; }

{number}                { fprintf(yyout,"%d(%d): %s (NUMBER)\n",line_number,column_number,yytext); 
                         column_number+=yyleng; }
{ws}                    { column_number+=yyleng; }
{other}                 { fprintf(yyout, "(%d) Lexical error in line %d and col %d. Input -> \"%s\"\n", 
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