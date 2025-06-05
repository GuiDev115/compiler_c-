/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_C_MINUS_PARSER_PARSER_TAB_H_INCLUDED
# define YY_YY_C_MINUS_PARSER_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT_TYPE = 258,                /* INT_TYPE  */
    FLOAT_TYPE = 259,              /* FLOAT_TYPE  */
    CHAR_TYPE = 260,               /* CHAR_TYPE  */
    STRUCT_TYPE = 261,             /* STRUCT_TYPE  */
    VOID_TYPE = 262,               /* VOID_TYPE  */
    IF_KEYWORD = 263,              /* IF_KEYWORD  */
    ELSE_KEYWORD = 264,            /* ELSE_KEYWORD  */
    WHILE_KEYWORD = 265,           /* WHILE_KEYWORD  */
    RETURN_KEYWORD = 266,          /* RETURN_KEYWORD  */
    PLUS_OP = 267,                 /* PLUS_OP  */
    MINUS_OP = 268,                /* MINUS_OP  */
    MULT_OP = 269,                 /* MULT_OP  */
    DIV_OP = 270,                  /* DIV_OP  */
    MOD_OP = 271,                  /* MOD_OP  */
    ASSIGN_OP = 272,               /* ASSIGN_OP  */
    EQUAL_OP = 273,                /* EQUAL_OP  */
    NE_OP = 274,                   /* NE_OP  */
    LT_OP = 275,                   /* LT_OP  */
    LE_OP = 276,                   /* LE_OP  */
    GT_OP = 277,                   /* GT_OP  */
    GE_OP = 278,                   /* GE_OP  */
    OPEN_BRACE = 279,              /* OPEN_BRACE  */
    CLOSE_BRACE = 280,             /* CLOSE_BRACE  */
    OPEN_PAREN = 281,              /* OPEN_PAREN  */
    CLOSE_PAREN = 282,             /* CLOSE_PAREN  */
    OPEN_BRACKET = 283,            /* OPEN_BRACKET  */
    CLOSE_BRACKET = 284,           /* CLOSE_BRACKET  */
    SEMICOLON = 285,               /* SEMICOLON  */
    COMMA = 286,                   /* COMMA  */
    DOT = 287,                     /* DOT  */
    IDENTIFIER = 288,              /* IDENTIFIER  */
    INT_NUMBER = 289,              /* INT_NUMBER  */
    REAL_NUMBER = 290,             /* REAL_NUMBER  */
    INVALID_IDENTIFIER = 291,      /* INVALID_IDENTIFIER  */
    LEXICAL_ERROR = 292,           /* LEXICAL_ERROR  */
    LOWER = 293                    /* LOWER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_C_MINUS_PARSER_PARSER_TAB_H_INCLUDED  */
