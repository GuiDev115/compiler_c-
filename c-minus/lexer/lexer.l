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
#include "../semantic/utils.h"       // Include utils for str_duplicate
#include "../semantic/semantic.h"     // Include semantic headers first
#include "../parser/parser.tab.h"    // Corrigido: caminho relativo correto

int line_number = 1;
int column_number = 1;
int errors_count = 1;

%}

%x COMMENT

delim                   [ \t]
ws                      {delim}+
newline                 \n
digito                  [0-9]
letra                   [a-z]
num_int                 {digito}+
int                     {digito}+(\.{digito}+)?([E][+-]?{digito}+)?
ident                   {letra}({letra}|{digito})*
array_ident             {ident}"["{num-int}"]"


other                   .

%%

 /* --- Comentários --- */

"/*"                    { BEGIN(COMMENT); fprintf(yyout,"%d(%d): %s",line_number,column_number,yytext); 			column_number+=yyleng; }
<COMMENT>[^*\n]* 	{ fprintf(yyout,"%s",yytext); column_number+=yyleng; }
<COMMENT>"*"+[^*/\n]* 	{ fprintf(yyout,"%s",yytext); column_number+=yyleng; }
<COMMENT>\n            	{ fprintf(yyout,"%s",yytext); line_number++; column_number=1; }
<COMMENT>"*"+"/"       	{ fprintf(yyout,"%s (COMENTARIO)\n",yytext); BEGIN(INITIAL); column_number+=yyleng; }

 /* --- Palavras Reservadas --- */
 
"int"                   { column_number+=yyleng; yylval.data_type = TYPE_INT; return INT_TYPE; }

"float"                 { column_number+=yyleng; yylval.data_type = TYPE_FLOAT; return FLOAT_TYPE; }

"struct"                { column_number+=yyleng; yylval.data_type = TYPE_STRUCT; return STRUCT_TYPE; }

"void"                  { column_number+=yyleng; yylval.data_type = TYPE_VOID; return VOID_TYPE; }

"if"                    { column_number+=yyleng; return IF_KEYWORD; }

"else"                  { column_number+=yyleng; return ELSE_KEYWORD; }
 
"while"                 { column_number+=yyleng; return WHILE_KEYWORD; } 

"return"                { column_number+=yyleng; return RETURN_KEYWORD; } 

"char"                  { column_number+=yyleng; yylval.data_type = TYPE_CHAR; return CHAR_TYPE; }


 /* --- Operadores --- */
 
"+"                     { column_number+=yyleng; return PLUS_OP; }

"-"                     { column_number+=yyleng; return MINUS_OP; }

"*"                     { column_number+=yyleng; return MULT_OP; }

"/"                     { column_number+=yyleng; return DIV_OP; }

"%"                     { column_number+=yyleng; return MOD_OP; }

"="                     { column_number+=yyleng; return ASSIGN_OP; }

"=="                    { column_number+=yyleng; return EQUAL_OP; }

"!="                    { column_number+=yyleng; return NE_OP; }

"<"                     { column_number+=yyleng; return LT_OP; }

"<="                    { column_number+=yyleng; return LE_OP; }

">"                     { column_number+=yyleng; return GT_OP; }

">="                    { column_number+=yyleng; return GE_OP; }

 /* --- Símbolos --- */
 
"{"                     { column_number+=yyleng; return OPEN_BRACE; }

"}"                     { column_number+=yyleng; return CLOSE_BRACE; }

"("                     { column_number+=yyleng; return OPEN_PAREN; }

")"                     { column_number+=yyleng; return CLOSE_PAREN; }

"["                     { column_number+=yyleng; return OPEN_BRACKET; }

"]"                     { column_number+=yyleng; return CLOSE_BRACKET; }


 /* --- Pontuação --- */
  
";"                     { column_number+=yyleng; return SEMICOLON; }

","                     { column_number+=yyleng; return COMMA; }

"."                     { column_number+=yyleng; return DOT; }

 /* --- Identificadores e Números --- */
 
{digito}+{letra}({letra}|{digito})* 	{ fprintf(yyout, "(%d) Erro léxico na linha %d e na coluna %d. 						Identificador inválido -> \"%s\"\n", ++errors_count, line_number, 						column_number, yytext); column_number+=yyleng; return 						INVALID_IDENTIFIER; }

{num_int}               		{ column_number+=yyleng; yylval.int_val = atoi(yytext); return INT_NUMBER; }  

{int}                   		{ column_number+=yyleng; yylval.float_val = atof(yytext); return REAL_NUMBER; } 

{ident}                 		{ column_number+=yyleng; yylval.string_val = my_strdup(yytext); return IDENTIFIER; } 

 /* --- Outros --- */
 
{newline}               { line_number++; column_number = 1; } 

{ws}                    { column_number+=yyleng; } 
 
{other}                 { fprintf(yyout, "(%d) Erro léxico na linha %d e na coluna %d. Entrada -> \"%s\"\n", 				++errors_count, line_number, column_number, yytext); return LEXICAL_ERROR; } 

%%

