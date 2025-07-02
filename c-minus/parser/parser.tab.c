/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "c-minus/parser/parser.y"


/* C-MINUS PARSER WITH SEMANTIC ANALYSIS
Feito por: 
    - Guilherme Fabricio Brito da Rosa
    - Harisson de Carvalho Alvarenga
    - Raul Soares de Carvalho
*/  
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "../semantic/semantic.h"

    extern int line_number;
    extern int column_number;
    extern int errors_count;
    extern char *yytext;
    
    int yylex(void);
    void yyerror(const char *s);
    
    /* Variáveis globais para análise semântica */
    ASTNode *ast_root = NULL;

#line 96 "c-minus/parser/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_INT_NUMBER = 4,                 /* INT_NUMBER  */
  YYSYMBOL_REAL_NUMBER = 5,                /* REAL_NUMBER  */
  YYSYMBOL_INT_TYPE = 6,                   /* INT_TYPE  */
  YYSYMBOL_FLOAT_TYPE = 7,                 /* FLOAT_TYPE  */
  YYSYMBOL_CHAR_TYPE = 8,                  /* CHAR_TYPE  */
  YYSYMBOL_STRUCT_TYPE = 9,                /* STRUCT_TYPE  */
  YYSYMBOL_VOID_TYPE = 10,                 /* VOID_TYPE  */
  YYSYMBOL_IF_KEYWORD = 11,                /* IF_KEYWORD  */
  YYSYMBOL_ELSE_KEYWORD = 12,              /* ELSE_KEYWORD  */
  YYSYMBOL_WHILE_KEYWORD = 13,             /* WHILE_KEYWORD  */
  YYSYMBOL_RETURN_KEYWORD = 14,            /* RETURN_KEYWORD  */
  YYSYMBOL_PLUS_OP = 15,                   /* PLUS_OP  */
  YYSYMBOL_MINUS_OP = 16,                  /* MINUS_OP  */
  YYSYMBOL_MULT_OP = 17,                   /* MULT_OP  */
  YYSYMBOL_DIV_OP = 18,                    /* DIV_OP  */
  YYSYMBOL_MOD_OP = 19,                    /* MOD_OP  */
  YYSYMBOL_ASSIGN_OP = 20,                 /* ASSIGN_OP  */
  YYSYMBOL_EQUAL_OP = 21,                  /* EQUAL_OP  */
  YYSYMBOL_NE_OP = 22,                     /* NE_OP  */
  YYSYMBOL_LT_OP = 23,                     /* LT_OP  */
  YYSYMBOL_LE_OP = 24,                     /* LE_OP  */
  YYSYMBOL_GT_OP = 25,                     /* GT_OP  */
  YYSYMBOL_GE_OP = 26,                     /* GE_OP  */
  YYSYMBOL_OPEN_BRACE = 27,                /* OPEN_BRACE  */
  YYSYMBOL_CLOSE_BRACE = 28,               /* CLOSE_BRACE  */
  YYSYMBOL_OPEN_PAREN = 29,                /* OPEN_PAREN  */
  YYSYMBOL_CLOSE_PAREN = 30,               /* CLOSE_PAREN  */
  YYSYMBOL_OPEN_BRACKET = 31,              /* OPEN_BRACKET  */
  YYSYMBOL_CLOSE_BRACKET = 32,             /* CLOSE_BRACKET  */
  YYSYMBOL_SEMICOLON = 33,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 34,                     /* COMMA  */
  YYSYMBOL_DOT = 35,                       /* DOT  */
  YYSYMBOL_INVALID_IDENTIFIER = 36,        /* INVALID_IDENTIFIER  */
  YYSYMBOL_LEXICAL_ERROR = 37,             /* LEXICAL_ERROR  */
  YYSYMBOL_LOWER = 38,                     /* LOWER  */
  YYSYMBOL_ERROR_RECOVERY = 39,            /* ERROR_RECOVERY  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_programa = 41,                  /* programa  */
  YYSYMBOL_declaracao_lista = 42,          /* declaracao_lista  */
  YYSYMBOL_declaracao = 43,                /* declaracao  */
  YYSYMBOL_var_declaracao = 44,            /* var_declaracao  */
  YYSYMBOL_arranjo_dimensao = 45,          /* arranjo_dimensao  */
  YYSYMBOL_tipo_especificador = 46,        /* tipo_especificador  */
  YYSYMBOL_atributos_declaracao = 47,      /* atributos_declaracao  */
  YYSYMBOL_fun_declaracao = 48,            /* fun_declaracao  */
  YYSYMBOL_params = 49,                    /* params  */
  YYSYMBOL_param_lista = 50,               /* param_lista  */
  YYSYMBOL_param = 51,                     /* param  */
  YYSYMBOL_composto_decl = 52,             /* composto_decl  */
  YYSYMBOL_temp = 53,                      /* temp  */
  YYSYMBOL_local_declaracoes = 54,         /* local_declaracoes  */
  YYSYMBOL_comando_lista = 55,             /* comando_lista  */
  YYSYMBOL_comando = 56,                   /* comando  */
  YYSYMBOL_expressao_decl = 57,            /* expressao_decl  */
  YYSYMBOL_selecao_decl = 58,              /* selecao_decl  */
  YYSYMBOL_iteracao_decl = 59,             /* iteracao_decl  */
  YYSYMBOL_retorno_decl = 60,              /* retorno_decl  */
  YYSYMBOL_expressao = 61,                 /* expressao  */
  YYSYMBOL_var = 62,                       /* var  */
  YYSYMBOL_arranjo_acesso = 63,            /* arranjo_acesso  */
  YYSYMBOL_expressao_simples = 64,         /* expressao_simples  */
  YYSYMBOL_relacional = 65,                /* relacional  */
  YYSYMBOL_expressao_soma = 66,            /* expressao_soma  */
  YYSYMBOL_soma_op = 67,                   /* soma_op  */
  YYSYMBOL_termo = 68,                     /* termo  */
  YYSYMBOL_mult_op = 69,                   /* mult_op  */
  YYSYMBOL_fator = 70,                     /* fator  */
  YYSYMBOL_ativacao = 71,                  /* ativacao  */
  YYSYMBOL_args = 72,                      /* args  */
  YYSYMBOL_arg_lista = 73                  /* arg_lista  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   197

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  151
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  167

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    63,    63,    94,    95,   101,   102,   105,   109,   115,
     116,   117,   120,   121,   122,   123,   126,   127,   128,   129,
     130,   134,   135,   138,   139,   145,   149,   150,   153,   154,
     157,   158,   164,   167,   172,   175,   178,   179,   181,   182,
     185,   186,   189,   190,   191,   192,   193,   196,   197,   198,
     201,   202,   203,   204,   205,   208,   209,   213,   217,   223,
     224,   225,   228,   231,   234,   237,   244,   245,   248,   249,
     250,   251,   254,   255,   258,   259,   260,   261,   262,   263,
     266,   267,   270,   271,   274,   275,   278,   279,   282,   283,
     284,   285,   289,   293,   294,   297,   300,   303,   304,   307,
     308,   314,   315,   316,   317,   320,   321,   322,   323,   326,
     332,   333,   336,   337,   347,   348,   358,   359,   360,   361,
     362,   365,   366,   367,   370,   374,   378,   379,   380,   383,
     387,   392,   397,   404,   408,   412,   415,   416,   421,   422,
     423,   424,   425,   426,   429,   430,   435,   436,   439,   440,
     445,   446
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "INT_NUMBER", "REAL_NUMBER", "INT_TYPE", "FLOAT_TYPE", "CHAR_TYPE",
  "STRUCT_TYPE", "VOID_TYPE", "IF_KEYWORD", "ELSE_KEYWORD",
  "WHILE_KEYWORD", "RETURN_KEYWORD", "PLUS_OP", "MINUS_OP", "MULT_OP",
  "DIV_OP", "MOD_OP", "ASSIGN_OP", "EQUAL_OP", "NE_OP", "LT_OP", "LE_OP",
  "GT_OP", "GE_OP", "OPEN_BRACE", "CLOSE_BRACE", "OPEN_PAREN",
  "CLOSE_PAREN", "OPEN_BRACKET", "CLOSE_BRACKET", "SEMICOLON", "COMMA",
  "DOT", "INVALID_IDENTIFIER", "LEXICAL_ERROR", "LOWER", "ERROR_RECOVERY",
  "$accept", "programa", "declaracao_lista", "declaracao",
  "var_declaracao", "arranjo_dimensao", "tipo_especificador",
  "atributos_declaracao", "fun_declaracao", "params", "param_lista",
  "param", "composto_decl", "temp", "local_declaracoes", "comando_lista",
  "comando", "expressao_decl", "selecao_decl", "iteracao_decl",
  "retorno_decl", "expressao", "var", "arranjo_acesso",
  "expressao_simples", "relacional", "expressao_soma", "soma_op", "termo",
  "mult_op", "fator", "ativacao", "args", "arg_lista", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-72)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-20)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     121,   -72,   -72,   -72,    27,   -72,    86,   121,   -72,   -72,
      53,   -72,    -7,   -72,   -72,     3,   133,   -19,   170,   114,
     -72,    34,   -72,    69,   116,   -72,    90,   108,   129,    49,
     102,   -72,    59,    14,   -72,     8,   -72,   -72,   -72,   118,
     124,   118,   118,   121,   113,   130,   -72,   -72,   -72,    15,
     -72,   -72,   -72,   -72,   -72,   125,   121,   -72,   -72,   115,
     -72,   -72,    24,   140,    16,   -72,   106,   -72,   -72,    11,
      73,    61,   -72,    72,   -72,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,     9,   153,   -72,   144,    81,   -72,   -72,   -72,
     -72,   -72,     2,    77,   -72,    92,   -72,   104,   -72,    12,
     145,    54,   -72,   -72,     2,   -72,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,     2,     2,   -72,   -72,     2,   -72,    57,
     148,   154,    17,   155,    62,   157,    70,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,    88,    81,   -72,   -72,   -72,     2,
     -72,   -72,   -72,    56,    56,    56,    56,    56,    56,   -72,
     143,   143,   143,   -72,   -72,   176,   -72,   -72,   -72,   109,
      56,   158,    22,   -72,   -72,   -72,   -72
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    16,    17,    18,     0,    19,     0,     2,     3,     5,
       0,     6,     0,     1,     4,     0,     0,     0,     0,     0,
       7,     0,    23,     0,     0,     9,     0,    29,     0,     0,
      28,    30,     0,     0,    22,     0,    21,    20,    24,     0,
      32,     0,     0,     0,     0,     0,    12,    38,    27,     0,
      26,    25,    31,    11,    10,     0,    40,    34,    33,     0,
       8,    39,     0,     0,     0,    37,    64,    92,    91,     0,
       0,     0,    36,     0,    48,    43,    35,    41,    42,    44,
      45,    46,     0,    89,    63,    72,    80,    84,    90,    15,
      14,    13,    97,     0,    54,     0,    58,     0,    59,     0,
       0,     0,    49,    47,     0,    82,    83,    78,    79,    75,
      74,    76,    77,     0,     0,    86,    87,     0,    99,     0,
      98,     0,     0,     0,     0,     0,     0,    61,    60,    94,
      93,    88,    62,    89,    73,    81,    85,    96,    95,     0,
      68,    68,    68,     0,     0,     0,     0,     0,     0,   100,
      67,    66,    65,    53,    52,    50,    57,    56,    55,     0,
       0,     0,     0,    51,    71,    70,    69
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   -72,   182,   -13,   -72,     1,   -72,   -72,   -72,
     -72,   149,   142,   -72,   -72,   -72,     4,   -72,   -72,   -72,
     -72,   -71,    40,    20,   -72,   -72,    78,   -72,    79,   -72,
      80,   -72,   -72,   -72
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     6,     7,     8,     9,    55,    23,    24,    11,    29,
      30,    31,    75,    76,    56,    62,    77,    78,    79,    80,
      81,    82,    83,   150,    84,   113,    85,   114,    86,   117,
      87,    88,   119,   120
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      99,    10,   101,    22,    17,    66,    67,    68,    10,    17,
     102,    38,    94,   127,    25,    45,    57,    90,   141,    28,
      16,   118,   122,   165,   124,    65,   126,    66,    67,    68,
      12,    73,    18,   132,    19,    69,    20,    70,    71,    19,
      95,    20,   103,    61,    28,   128,    46,    58,    91,   142,
      41,    47,    72,    73,   166,   130,    15,    74,   137,    66,
      67,    68,    34,   144,    66,    67,    68,    69,   149,    70,
      71,   147,    35,   100,    96,    66,    67,    68,   121,    42,
      66,    67,    68,    47,   131,    73,    13,   138,   162,    74,
      73,    44,   145,   123,    98,    66,    67,    68,   115,   116,
     148,    73,    97,   105,   106,   125,    73,    66,    67,    68,
     161,   -19,    66,    67,    68,    32,    63,    36,    33,    64,
      39,    73,     1,     2,     3,     4,     5,     1,     2,     3,
       4,     5,    40,    73,    21,    92,    43,    93,    73,     1,
       2,     3,     4,     5,    37,    47,    53,   153,   154,   155,
     156,   157,   158,   133,   133,    49,    59,   133,    60,   105,
     106,   151,   152,    54,   163,   107,   108,   109,   110,   111,
     112,    26,    89,   104,   159,   129,     1,     2,     3,     4,
      27,    48,   139,    50,    51,   143,   140,   146,   160,    14,
     164,   134,    52,   135,     0,     0,     0,   136
};

static const yytype_int16 yycheck[] =
{
      71,     0,    73,    16,     1,     3,     4,     5,     7,     1,
       1,    24,     1,     1,    33,     1,     1,     1,     1,    18,
      27,    92,    93,     1,    95,     1,    97,     3,     4,     5,
       3,    29,    29,   104,    31,    11,    33,    13,    14,    31,
      29,    33,    33,    56,    43,    33,    32,    32,    32,    32,
       1,    27,    28,    29,    32,     1,     3,    33,     1,     3,
       4,     5,    28,     1,     3,     4,     5,    11,   139,    13,
      14,     1,     3,     1,     1,     3,     4,     5,     1,    30,
       3,     4,     5,    27,    30,    29,     0,    30,   159,    33,
      29,    32,    30,     1,    33,     3,     4,     5,    17,    18,
      30,    29,    29,    15,    16,     1,    29,     3,     4,     5,
       1,     3,     3,     4,     5,     1,     1,     1,     4,     4,
      30,    29,     6,     7,     8,     9,    10,     6,     7,     8,
       9,    10,     3,    29,     1,    29,    34,    31,    29,     6,
       7,     8,     9,    10,    28,    27,    33,   143,   144,   145,
     146,   147,   148,   113,   114,    31,    31,   117,    33,    15,
      16,   141,   142,    33,   160,    21,    22,    23,    24,    25,
      26,     1,    32,    20,    31,    30,     6,     7,     8,     9,
      10,    39,    34,    41,    42,    30,    32,    30,    12,     7,
      32,   113,    43,   114,    -1,    -1,    -1,   117
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,     8,     9,    10,    41,    42,    43,    44,
      46,    48,     3,     0,    43,     3,    27,     1,    29,    31,
      33,     1,    44,    46,    47,    33,     1,    10,    46,    49,
      50,    51,     1,     4,    28,     3,     1,    28,    44,    30,
       3,     1,    30,    34,    32,     1,    32,    27,    52,    31,
      52,    52,    51,    33,    33,    45,    54,     1,    32,    31,
      33,    44,    55,     1,     4,     1,     3,     4,     5,    11,
      13,    14,    28,    29,    33,    52,    53,    56,    57,    58,
      59,    60,    61,    62,    64,    66,    68,    70,    71,    32,
       1,    32,    29,    31,     1,    29,     1,    29,    33,    61,
       1,    61,     1,    33,    20,    15,    16,    21,    22,    23,
      24,    25,    26,    65,    67,    17,    18,    69,    61,    72,
      73,     1,    61,     1,    61,     1,    61,     1,    33,    30,
       1,    30,    61,    62,    66,    68,    70,     1,    30,    34,
      32,     1,    32,    30,     1,    30,    30,     1,    30,    61,
      63,    63,    63,    56,    56,    56,    56,    56,    56,    31,
      12,     1,    61,    56,    32,     1,    32
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    44,    44,    44,
      44,    44,    45,    45,    45,    45,    46,    46,    46,    46,
      46,    46,    46,    47,    47,    48,    48,    48,    49,    49,
      50,    50,    51,    51,    51,    52,    53,    53,    54,    54,
      55,    55,    56,    56,    56,    56,    56,    57,    57,    57,
      58,    58,    58,    58,    58,    59,    59,    59,    59,    60,
      60,    60,    61,    61,    62,    62,    62,    62,    63,    63,
      63,    63,    64,    64,    65,    65,    65,    65,    65,    65,
      66,    66,    67,    67,    68,    68,    69,    69,    70,    70,
      70,    70,    70,    70,    70,    71,    71,    72,    72,    73,
      73,    45,    45,    45,    45,    63,    63,    63,    63,    52,
      53,    53,    54,    54,    55,    55,    56,    56,    56,    56,
      56,    57,    57,    57,    58,    58,    58,    58,    58,    59,
      59,    59,    59,    60,    60,    60,    64,    64,    65,    65,
      65,    65,    65,    65,    66,    66,    67,    67,    68,    68,
      69,    69
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     7,     4,
       6,     6,     0,     4,     4,     4,     1,     1,     1,     1,
       5,     5,     5,     1,     2,     6,     6,     6,     1,     1,
       1,     3,     2,     4,     4,     4,     1,     1,     0,     2,
       0,     2,     1,     1,     1,     1,     1,     2,     1,     2,
       5,     7,     5,     5,     2,     5,     5,     5,     2,     2,
       3,     3,     3,     1,     1,     5,     5,     5,     0,     4,
       4,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     3,     1,
       1,     1,     1,     3,     3,     4,     4,     0,     1,     1,
       3,     0,     4,     4,     4,     0,     4,     4,     4,     4,
       1,     1,     0,     2,     0,     2,     1,     1,     1,     1,
       1,     2,     1,     2,     5,     7,     5,     5,     2,     5,
       5,     5,     2,     2,     3,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: declaracao_lista  */
#line 63 "c-minus/parser/parser.y"
                                                              { 
                        printf("Parsing concluído com sucesso!\n"); 
                        printf(">>> Iniciando análise semântica...\n");
                        
                        /* Inicializa análise semântica */
                        init_semantic_analysis();
                        
                        /* Cria nó raiz da AST */
                        ast_root = create_program_node((yyvsp[0].ast_node));
                        (yyval.ast_node) = ast_root;
                        
                        /* Executa análise semântica */
                        if (check_program(ast_root) != 0) {
                            printf(">>> Análise semântica concluída com sucesso!\n");
                            printf(">>> Iniciando geração de código...\n");
                            
                            /* Imprime tabela de símbolos */
                            printf("\n=== TABELA DE SÍMBOLOS ===\n");
                            print_symbol_table(get_symbol_table());
                            
                            /* Imprime código de três endereços */
                            printf("\n=== CÓDIGO DE TRÊS ENDEREÇOS ===\n");
                            print_instruction_list(get_instruction_list());
                        } else {
                            printf(">>> Análise semântica falhou!\n");
                        }
                        
                        finalize_semantic_analysis();
                    }
#line 1325 "c-minus/parser/parser.tab.c"
    break;

  case 3: /* declaracao_lista: declaracao  */
#line 94 "c-minus/parser/parser.y"
                                                               { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1331 "c-minus/parser/parser.tab.c"
    break;

  case 4: /* declaracao_lista: declaracao_lista declaracao  */
#line 95 "c-minus/parser/parser.y"
                                                          { 
                            (yyvsp[-1].ast_node)->next = (yyvsp[0].ast_node); 
                            (yyval.ast_node) = (yyvsp[-1].ast_node); 
                        }
#line 1340 "c-minus/parser/parser.tab.c"
    break;

  case 5: /* declaracao: var_declaracao  */
#line 101 "c-minus/parser/parser.y"
                                                               { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1346 "c-minus/parser/parser.tab.c"
    break;

  case 6: /* declaracao: fun_declaracao  */
#line 102 "c-minus/parser/parser.y"
                                                       { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1352 "c-minus/parser/parser.tab.c"
    break;

  case 7: /* var_declaracao: tipo_especificador IDENTIFIER SEMICOLON  */
#line 105 "c-minus/parser/parser.y"
                                                                          {
                        printf(">>> Declaração de variável: %s\n", (yyvsp[-1].string_val));
                        (yyval.ast_node) = create_var_declaration_node((yyvsp[-1].string_val), (yyvsp[-2].data_type), line_number);
                    }
#line 1361 "c-minus/parser/parser.tab.c"
    break;

  case 8: /* var_declaracao: tipo_especificador IDENTIFIER OPEN_BRACKET INT_NUMBER CLOSE_BRACKET arranjo_dimensao SEMICOLON  */
#line 109 "c-minus/parser/parser.y"
                                                                                                                 {
                        printf(">>> Declaração de array: %s[%d]\n", (yyvsp[-5].string_val), (yyvsp[-3].int_val));
                        ASTNode *node = create_var_declaration_node((yyvsp[-5].string_val), (yyvsp[-6].data_type), line_number);
                        node->data.var_decl.array_size = (yyvsp[-3].int_val);
                        (yyval.ast_node) = node;
                    }
#line 1372 "c-minus/parser/parser.tab.c"
    break;

  case 9: /* var_declaracao: tipo_especificador IDENTIFIER error SEMICOLON  */
#line 115 "c-minus/parser/parser.y"
                                                                { yyerror("Erro na declaração de variável"); yyerrok; (yyval.ast_node) = NULL; }
#line 1378 "c-minus/parser/parser.tab.c"
    break;

  case 10: /* var_declaracao: tipo_especificador IDENTIFIER OPEN_BRACKET INT_NUMBER error SEMICOLON  */
#line 116 "c-minus/parser/parser.y"
                                                                                        { yyerror("Esperado ']' após índice do array"); yyerrok; (yyval.ast_node) = NULL; }
#line 1384 "c-minus/parser/parser.tab.c"
    break;

  case 11: /* var_declaracao: tipo_especificador IDENTIFIER OPEN_BRACKET error CLOSE_BRACKET SEMICOLON  */
#line 117 "c-minus/parser/parser.y"
                                                                                           { yyerror("Índice inválido no array"); yyerrok; (yyval.ast_node) = NULL; }
#line 1390 "c-minus/parser/parser.tab.c"
    break;

  case 14: /* arranjo_dimensao: arranjo_dimensao OPEN_BRACKET INT_NUMBER error  */
#line 122 "c-minus/parser/parser.y"
                                                                 { yyerror("Esperado ']' após dimensão do array"); yyerrok; }
#line 1396 "c-minus/parser/parser.tab.c"
    break;

  case 15: /* arranjo_dimensao: arranjo_dimensao OPEN_BRACKET error CLOSE_BRACKET  */
#line 123 "c-minus/parser/parser.y"
                                                                    { yyerror("Dimensão inválida no array"); yyerrok; }
#line 1402 "c-minus/parser/parser.tab.c"
    break;

  case 16: /* tipo_especificador: INT_TYPE  */
#line 126 "c-minus/parser/parser.y"
                                                              { printf(">>> Tipo: int\n"); (yyval.data_type) = TYPE_INT; }
#line 1408 "c-minus/parser/parser.tab.c"
    break;

  case 17: /* tipo_especificador: FLOAT_TYPE  */
#line 127 "c-minus/parser/parser.y"
                                                      { printf(">>> Tipo: float\n"); (yyval.data_type) = TYPE_FLOAT; }
#line 1414 "c-minus/parser/parser.tab.c"
    break;

  case 18: /* tipo_especificador: CHAR_TYPE  */
#line 128 "c-minus/parser/parser.y"
                                                      { printf(">>> Tipo: char\n"); (yyval.data_type) = TYPE_CHAR; }
#line 1420 "c-minus/parser/parser.tab.c"
    break;

  case 19: /* tipo_especificador: VOID_TYPE  */
#line 129 "c-minus/parser/parser.y"
                                                      { printf(">>> Tipo: void\n"); (yyval.data_type) = TYPE_VOID; }
#line 1426 "c-minus/parser/parser.tab.c"
    break;

  case 20: /* tipo_especificador: STRUCT_TYPE IDENTIFIER OPEN_BRACE atributos_declaracao CLOSE_BRACE  */
#line 130 "c-minus/parser/parser.y"
                                                                                             { 
                            printf(">>> Tipo: struct %s\n", (yyvsp[-3].string_val)); 
                            (yyval.data_type) = TYPE_STRUCT; 
                        }
#line 1435 "c-minus/parser/parser.tab.c"
    break;

  case 21: /* tipo_especificador: STRUCT_TYPE IDENTIFIER OPEN_BRACE atributos_declaracao error  */
#line 134 "c-minus/parser/parser.y"
                                                                                       { yyerror("Esperado '}' após declarações do struct"); yyerrok; (yyval.data_type) = TYPE_ERROR; }
#line 1441 "c-minus/parser/parser.tab.c"
    break;

  case 22: /* tipo_especificador: STRUCT_TYPE IDENTIFIER OPEN_BRACE error CLOSE_BRACE  */
#line 135 "c-minus/parser/parser.y"
                                                                              { yyerror("Declarações inválidas no struct"); yyerrok; (yyval.data_type) = TYPE_ERROR; }
#line 1447 "c-minus/parser/parser.tab.c"
    break;

  case 23: /* atributos_declaracao: var_declaracao  */
#line 138 "c-minus/parser/parser.y"
                                                 { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1453 "c-minus/parser/parser.tab.c"
    break;

  case 24: /* atributos_declaracao: atributos_declaracao var_declaracao  */
#line 139 "c-minus/parser/parser.y"
                                                      { 
                    (yyvsp[-1].ast_node)->next = (yyvsp[0].ast_node); 
                    (yyval.ast_node) = (yyvsp[-1].ast_node); 
                }
#line 1462 "c-minus/parser/parser.tab.c"
    break;

  case 25: /* fun_declaracao: tipo_especificador IDENTIFIER OPEN_PAREN params CLOSE_PAREN composto_decl  */
#line 145 "c-minus/parser/parser.y"
                                                                                                            {
                        printf(">>> Declaração de função: %s\n", (yyvsp[-4].string_val));
                        (yyval.ast_node) = create_fun_declaration_node((yyvsp[-4].string_val), (yyvsp[-5].data_type), (yyvsp[-2].ast_node), (yyvsp[0].ast_node), line_number);
                    }
#line 1471 "c-minus/parser/parser.tab.c"
    break;

  case 26: /* fun_declaracao: tipo_especificador IDENTIFIER OPEN_PAREN params error composto_decl  */
#line 149 "c-minus/parser/parser.y"
                                                                                      { yyerror("Esperado ')' após parâmetros da função"); yyerrok; (yyval.ast_node) = NULL; }
#line 1477 "c-minus/parser/parser.tab.c"
    break;

  case 27: /* fun_declaracao: tipo_especificador IDENTIFIER OPEN_PAREN error CLOSE_PAREN composto_decl  */
#line 150 "c-minus/parser/parser.y"
                                                                                           { yyerror("Parâmetros inválidos na função"); yyerrok; (yyval.ast_node) = NULL; }
#line 1483 "c-minus/parser/parser.tab.c"
    break;

  case 28: /* params: param_lista  */
#line 153 "c-minus/parser/parser.y"
                                              { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1489 "c-minus/parser/parser.tab.c"
    break;

  case 29: /* params: VOID_TYPE  */
#line 154 "c-minus/parser/parser.y"
                            { (yyval.ast_node) = NULL; }
#line 1495 "c-minus/parser/parser.tab.c"
    break;

  case 30: /* param_lista: param  */
#line 157 "c-minus/parser/parser.y"
                                        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1501 "c-minus/parser/parser.tab.c"
    break;

  case 31: /* param_lista: param_lista COMMA param  */
#line 158 "c-minus/parser/parser.y"
                                          { 
                    (yyvsp[-2].ast_node)->next = (yyvsp[0].ast_node); 
                    (yyval.ast_node) = (yyvsp[-2].ast_node); 
                }
#line 1510 "c-minus/parser/parser.tab.c"
    break;

  case 32: /* param: tipo_especificador IDENTIFIER  */
#line 164 "c-minus/parser/parser.y"
                                                                { 
                    (yyval.ast_node) = create_var_declaration_node((yyvsp[0].string_val), (yyvsp[-1].data_type), line_number);
                }
#line 1518 "c-minus/parser/parser.tab.c"
    break;

  case 33: /* param: tipo_especificador IDENTIFIER OPEN_BRACKET CLOSE_BRACKET  */
#line 167 "c-minus/parser/parser.y"
                                                                           {
                    ASTNode *node = create_var_declaration_node((yyvsp[-2].string_val), (yyvsp[-3].data_type), line_number);
                    node->data.var_decl.array_size = -1; /* Array parameter */
                    (yyval.ast_node) = node;
                }
#line 1528 "c-minus/parser/parser.tab.c"
    break;

  case 34: /* param: tipo_especificador IDENTIFIER OPEN_BRACKET error  */
#line 172 "c-minus/parser/parser.y"
                                                                   { yyerror("Esperado ']' após '[' no parâmetro array"); yyerrok; (yyval.ast_node) = NULL; }
#line 1534 "c-minus/parser/parser.tab.c"
    break;

  case 37: /* temp: error  */
#line 179 "c-minus/parser/parser.y"
                    { yyerror("Esperado '}' para fechar bloco de comandos"); yyerrok; }
#line 1540 "c-minus/parser/parser.tab.c"
    break;

  case 49: /* expressao_decl: expressao error  */
#line 198 "c-minus/parser/parser.y"
                                  { yyerror("Esperado ';' após expressão"); yyerrok; }
#line 1546 "c-minus/parser/parser.tab.c"
    break;

  case 52: /* selecao_decl: IF_KEYWORD OPEN_PAREN expressao error comando  */
#line 203 "c-minus/parser/parser.y"
                                                                { yyerror("Esperado ')' após condição do if"); yyerrok; }
#line 1552 "c-minus/parser/parser.tab.c"
    break;

  case 53: /* selecao_decl: IF_KEYWORD OPEN_PAREN error CLOSE_PAREN comando  */
#line 204 "c-minus/parser/parser.y"
                                                                  { yyerror("Expressão inválida na condição do if"); yyerrok; }
#line 1558 "c-minus/parser/parser.tab.c"
    break;

  case 54: /* selecao_decl: IF_KEYWORD error  */
#line 205 "c-minus/parser/parser.y"
                                   { yyerror("Esperado '(' após if"); yyerrok; }
#line 1564 "c-minus/parser/parser.tab.c"
    break;

  case 56: /* iteracao_decl: WHILE_KEYWORD OPEN_PAREN expressao error comando  */
#line 209 "c-minus/parser/parser.y"
                                                                   { 
                    yyerror("Esperado ')' após condição do while"); 
                    yyerrok; 
                }
#line 1573 "c-minus/parser/parser.tab.c"
    break;

  case 57: /* iteracao_decl: WHILE_KEYWORD OPEN_PAREN error CLOSE_PAREN comando  */
#line 213 "c-minus/parser/parser.y"
                                                                     { 
                    yyerror("Expressão inválida na condição do while"); 
                    yyerrok; 
                }
#line 1582 "c-minus/parser/parser.tab.c"
    break;

  case 58: /* iteracao_decl: WHILE_KEYWORD error  */
#line 217 "c-minus/parser/parser.y"
                                      { 
                    yyerror("Esperado '(' após while"); 
                    yyerrok; 
                }
#line 1591 "c-minus/parser/parser.tab.c"
    break;

  case 61: /* retorno_decl: RETURN_KEYWORD expressao error  */
#line 225 "c-minus/parser/parser.y"
                                                 { yyerror("Esperado ';' após return"); yyerrok; }
#line 1597 "c-minus/parser/parser.tab.c"
    break;

  case 62: /* expressao: var ASSIGN_OP expressao  */
#line 228 "c-minus/parser/parser.y"
                                                                   { 
                    (yyval.ast_node) = create_binary_op_node(OP_ASSIGN, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), line_number);
                }
#line 1605 "c-minus/parser/parser.tab.c"
    break;

  case 63: /* expressao: expressao_simples  */
#line 231 "c-minus/parser/parser.y"
                                                      { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1611 "c-minus/parser/parser.tab.c"
    break;

  case 64: /* var: IDENTIFIER  */
#line 234 "c-minus/parser/parser.y"
                                                                  { 
                    (yyval.ast_node) = create_identifier_node((yyvsp[0].string_val), line_number);
                }
#line 1619 "c-minus/parser/parser.tab.c"
    break;

  case 65: /* var: IDENTIFIER OPEN_BRACKET expressao CLOSE_BRACKET arranjo_acesso  */
#line 237 "c-minus/parser/parser.y"
                                                                                 { 
                    ASTNode *array_node = create_identifier_node((yyvsp[-4].string_val), line_number);
                    array_node->node_type = NODE_ARRAY_ACCESS;
                    array_node->data.var_ref.name = (yyvsp[-4].string_val);
                    array_node->data.var_ref.index = (yyvsp[-2].ast_node);
                    (yyval.ast_node) = array_node;
                }
#line 1631 "c-minus/parser/parser.tab.c"
    break;

  case 66: /* var: IDENTIFIER OPEN_BRACKET expressao error arranjo_acesso  */
#line 244 "c-minus/parser/parser.y"
                                                                         { yyerror("Esperado ']' após índice do array"); yyerrok; (yyval.ast_node) = NULL; }
#line 1637 "c-minus/parser/parser.tab.c"
    break;

  case 67: /* var: IDENTIFIER OPEN_BRACKET error CLOSE_BRACKET arranjo_acesso  */
#line 245 "c-minus/parser/parser.y"
                                                                             { yyerror("Índice inválido no array"); yyerrok; (yyval.ast_node) = NULL; }
#line 1643 "c-minus/parser/parser.tab.c"
    break;

  case 70: /* arranjo_acesso: arranjo_acesso OPEN_BRACKET expressao error  */
#line 250 "c-minus/parser/parser.y"
                                                              { yyerror("Esperado ']' após índice do array multidimensional"); yyerrok; }
#line 1649 "c-minus/parser/parser.tab.c"
    break;

  case 71: /* arranjo_acesso: arranjo_acesso OPEN_BRACKET error CLOSE_BRACKET  */
#line 251 "c-minus/parser/parser.y"
                                                                  { yyerror("Índice inválido no array multidimensional"); yyerrok; }
#line 1655 "c-minus/parser/parser.tab.c"
    break;

  case 88: /* fator: OPEN_PAREN expressao CLOSE_PAREN  */
#line 282 "c-minus/parser/parser.y"
                                                                   { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1661 "c-minus/parser/parser.tab.c"
    break;

  case 89: /* fator: var  */
#line 283 "c-minus/parser/parser.y"
                                                          { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1667 "c-minus/parser/parser.tab.c"
    break;

  case 90: /* fator: ativacao  */
#line 284 "c-minus/parser/parser.y"
                                                          { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1673 "c-minus/parser/parser.tab.c"
    break;

  case 91: /* fator: REAL_NUMBER  */
#line 285 "c-minus/parser/parser.y"
                                                          { 
                            float val = (yyvsp[0].float_val);
                            (yyval.ast_node) = create_constant_node(TYPE_FLOAT, &val, line_number);
                        }
#line 1682 "c-minus/parser/parser.tab.c"
    break;

  case 92: /* fator: INT_NUMBER  */
#line 289 "c-minus/parser/parser.y"
                                                          { 
                            int val = (yyvsp[0].int_val);
                            (yyval.ast_node) = create_constant_node(TYPE_INT, &val, line_number);
                        }
#line 1691 "c-minus/parser/parser.tab.c"
    break;

  case 93: /* fator: OPEN_PAREN expressao error  */
#line 293 "c-minus/parser/parser.y"
                                                     { yyerror("Esperado ')' após expressão"); yyerrok; (yyval.ast_node) = NULL; }
#line 1697 "c-minus/parser/parser.tab.c"
    break;

  case 94: /* fator: OPEN_PAREN error CLOSE_PAREN  */
#line 294 "c-minus/parser/parser.y"
                                                       { yyerror("Expressão inválida entre parênteses"); yyerrok; (yyval.ast_node) = NULL; }
#line 1703 "c-minus/parser/parser.tab.c"
    break;

  case 95: /* ativacao: IDENTIFIER OPEN_PAREN args CLOSE_PAREN  */
#line 297 "c-minus/parser/parser.y"
                                                                         { 
                    (yyval.ast_node) = create_call_node((yyvsp[-3].string_val), (yyvsp[-1].ast_node), line_number);
                }
#line 1711 "c-minus/parser/parser.tab.c"
    break;

  case 96: /* ativacao: IDENTIFIER OPEN_PAREN args error  */
#line 300 "c-minus/parser/parser.y"
                                                   { yyerror("Esperado ')' após argumentos da função"); yyerrok; (yyval.ast_node) = NULL; }
#line 1717 "c-minus/parser/parser.tab.c"
    break;

  case 97: /* args: %empty  */
#line 303 "c-minus/parser/parser.y"
                                                                  { (yyval.ast_node) = NULL; }
#line 1723 "c-minus/parser/parser.tab.c"
    break;

  case 98: /* args: arg_lista  */
#line 304 "c-minus/parser/parser.y"
                                                          { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1729 "c-minus/parser/parser.tab.c"
    break;

  case 99: /* arg_lista: expressao  */
#line 307 "c-minus/parser/parser.y"
                                                                  { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1735 "c-minus/parser/parser.tab.c"
    break;

  case 100: /* arg_lista: arg_lista COMMA expressao  */
#line 308 "c-minus/parser/parser.y"
                                                           { 
                            (yyvsp[-2].ast_node)->next = (yyvsp[0].ast_node); 
                            (yyval.ast_node) = (yyvsp[-2].ast_node); 
                        }
#line 1744 "c-minus/parser/parser.tab.c"
    break;

  case 101: /* arranjo_dimensao: %empty  */
#line 314 "c-minus/parser/parser.y"
                                                      { (yyval.ast_node) = NULL; }
#line 1750 "c-minus/parser/parser.tab.c"
    break;

  case 102: /* arranjo_dimensao: arranjo_dimensao OPEN_BRACKET INT_NUMBER CLOSE_BRACKET  */
#line 315 "c-minus/parser/parser.y"
                                                                         { (yyval.ast_node) = NULL; /* TODO: handle multi-dim arrays */ }
#line 1756 "c-minus/parser/parser.tab.c"
    break;

  case 103: /* arranjo_dimensao: arranjo_dimensao OPEN_BRACKET INT_NUMBER error  */
#line 316 "c-minus/parser/parser.y"
                                                                 { yyerror("Esperado ']' após dimensão do array"); yyerrok; (yyval.ast_node) = NULL; }
#line 1762 "c-minus/parser/parser.tab.c"
    break;

  case 104: /* arranjo_dimensao: arranjo_dimensao OPEN_BRACKET error CLOSE_BRACKET  */
#line 317 "c-minus/parser/parser.y"
                                                                    { yyerror("Dimensão inválida no array"); yyerrok; (yyval.ast_node) = NULL; }
#line 1768 "c-minus/parser/parser.tab.c"
    break;

  case 105: /* arranjo_acesso: %empty  */
#line 320 "c-minus/parser/parser.y"
                                              { (yyval.ast_node) = NULL; }
#line 1774 "c-minus/parser/parser.tab.c"
    break;

  case 106: /* arranjo_acesso: arranjo_acesso OPEN_BRACKET expressao CLOSE_BRACKET  */
#line 321 "c-minus/parser/parser.y"
                                                                      { (yyval.ast_node) = NULL; /* TODO: handle multi-dim access */ }
#line 1780 "c-minus/parser/parser.tab.c"
    break;

  case 107: /* arranjo_acesso: arranjo_acesso OPEN_BRACKET expressao error  */
#line 322 "c-minus/parser/parser.y"
                                                              { yyerror("Esperado ']' após índice do array multidimensional"); yyerrok; (yyval.ast_node) = NULL; }
#line 1786 "c-minus/parser/parser.tab.c"
    break;

  case 108: /* arranjo_acesso: arranjo_acesso OPEN_BRACKET error CLOSE_BRACKET  */
#line 323 "c-minus/parser/parser.y"
                                                                  { yyerror("Índice inválido no array multidimensional"); yyerrok; (yyval.ast_node) = NULL; }
#line 1792 "c-minus/parser/parser.tab.c"
    break;

  case 109: /* composto_decl: OPEN_BRACE local_declaracoes comando_lista temp  */
#line 326 "c-minus/parser/parser.y"
                                                                            { 
                        /* TODO: Create compound statement node */
                        (yyval.ast_node) = (yyvsp[-1].ast_node); /* For now, just return the statement list */
                    }
#line 1801 "c-minus/parser/parser.tab.c"
    break;

  case 110: /* temp: CLOSE_BRACE  */
#line 332 "c-minus/parser/parser.y"
                               { (yyval.ast_node) = NULL; }
#line 1807 "c-minus/parser/parser.tab.c"
    break;

  case 111: /* temp: error  */
#line 333 "c-minus/parser/parser.y"
                    { yyerror("Esperado '}' para fechar bloco de comandos"); yyerrok; (yyval.ast_node) = NULL; }
#line 1813 "c-minus/parser/parser.tab.c"
    break;

  case 112: /* local_declaracoes: %empty  */
#line 336 "c-minus/parser/parser.y"
                                              { (yyval.ast_node) = NULL; }
#line 1819 "c-minus/parser/parser.tab.c"
    break;

  case 113: /* local_declaracoes: local_declaracoes var_declaracao  */
#line 337 "c-minus/parser/parser.y"
                                                   { 
                    if ((yyvsp[-1].ast_node) == NULL) {
                        (yyval.ast_node) = (yyvsp[0].ast_node);
                    } else {
                        (yyvsp[-1].ast_node)->next = (yyvsp[0].ast_node); 
                        (yyval.ast_node) = (yyvsp[-1].ast_node); 
                    }
                }
#line 1832 "c-minus/parser/parser.tab.c"
    break;

  case 114: /* comando_lista: %empty  */
#line 347 "c-minus/parser/parser.y"
                                              { (yyval.ast_node) = NULL; }
#line 1838 "c-minus/parser/parser.tab.c"
    break;

  case 115: /* comando_lista: comando_lista comando  */
#line 348 "c-minus/parser/parser.y"
                                        { 
                    if ((yyvsp[-1].ast_node) == NULL) {
                        (yyval.ast_node) = (yyvsp[0].ast_node);
                    } else {
                        (yyvsp[-1].ast_node)->next = (yyvsp[0].ast_node); 
                        (yyval.ast_node) = (yyvsp[-1].ast_node); 
                    }
                }
#line 1851 "c-minus/parser/parser.tab.c"
    break;

  case 116: /* comando: expressao_decl  */
#line 358 "c-minus/parser/parser.y"
                                                 { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1857 "c-minus/parser/parser.tab.c"
    break;

  case 117: /* comando: composto_decl  */
#line 359 "c-minus/parser/parser.y"
                                { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1863 "c-minus/parser/parser.tab.c"
    break;

  case 118: /* comando: selecao_decl  */
#line 360 "c-minus/parser/parser.y"
                               { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1869 "c-minus/parser/parser.tab.c"
    break;

  case 119: /* comando: iteracao_decl  */
#line 361 "c-minus/parser/parser.y"
                                { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1875 "c-minus/parser/parser.tab.c"
    break;

  case 120: /* comando: retorno_decl  */
#line 362 "c-minus/parser/parser.y"
                               { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1881 "c-minus/parser/parser.tab.c"
    break;

  case 121: /* expressao_decl: expressao SEMICOLON  */
#line 365 "c-minus/parser/parser.y"
                                                      { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1887 "c-minus/parser/parser.tab.c"
    break;

  case 122: /* expressao_decl: SEMICOLON  */
#line 366 "c-minus/parser/parser.y"
                            { (yyval.ast_node) = NULL; }
#line 1893 "c-minus/parser/parser.tab.c"
    break;

  case 123: /* expressao_decl: expressao error  */
#line 367 "c-minus/parser/parser.y"
                                  { yyerror("Esperado ';' após expressão"); yyerrok; (yyval.ast_node) = NULL; }
#line 1899 "c-minus/parser/parser.tab.c"
    break;

  case 124: /* selecao_decl: IF_KEYWORD OPEN_PAREN expressao CLOSE_PAREN comando  */
#line 370 "c-minus/parser/parser.y"
                                                                                                  { 
                    /* TODO: Create selection statement node */
                    (yyval.ast_node) = (yyvsp[0].ast_node);
                }
#line 1908 "c-minus/parser/parser.tab.c"
    break;

  case 125: /* selecao_decl: IF_KEYWORD OPEN_PAREN expressao CLOSE_PAREN comando ELSE_KEYWORD comando  */
#line 374 "c-minus/parser/parser.y"
                                                                                           { 
                    /* TODO: Create if-else statement node */
                    (yyval.ast_node) = (yyvsp[-2].ast_node);
                }
#line 1917 "c-minus/parser/parser.tab.c"
    break;

  case 126: /* selecao_decl: IF_KEYWORD OPEN_PAREN expressao error comando  */
#line 378 "c-minus/parser/parser.y"
                                                                { yyerror("Esperado ')' após condição do if"); yyerrok; (yyval.ast_node) = NULL; }
#line 1923 "c-minus/parser/parser.tab.c"
    break;

  case 127: /* selecao_decl: IF_KEYWORD OPEN_PAREN error CLOSE_PAREN comando  */
#line 379 "c-minus/parser/parser.y"
                                                                  { yyerror("Expressão inválida na condição do if"); yyerrok; (yyval.ast_node) = NULL; }
#line 1929 "c-minus/parser/parser.tab.c"
    break;

  case 128: /* selecao_decl: IF_KEYWORD error  */
#line 380 "c-minus/parser/parser.y"
                                   { yyerror("Esperado '(' após if"); yyerrok; (yyval.ast_node) = NULL; }
#line 1935 "c-minus/parser/parser.tab.c"
    break;

  case 129: /* iteracao_decl: WHILE_KEYWORD OPEN_PAREN expressao CLOSE_PAREN comando  */
#line 383 "c-minus/parser/parser.y"
                                                                                         {
                    /* TODO: Create iteration statement node */
                    (yyval.ast_node) = (yyvsp[0].ast_node);
                }
#line 1944 "c-minus/parser/parser.tab.c"
    break;

  case 130: /* iteracao_decl: WHILE_KEYWORD OPEN_PAREN expressao error comando  */
#line 387 "c-minus/parser/parser.y"
                                                                   { 
                    yyerror("Esperado ')' após condição do while"); 
                    yyerrok; 
                    (yyval.ast_node) = NULL;
                }
#line 1954 "c-minus/parser/parser.tab.c"
    break;

  case 131: /* iteracao_decl: WHILE_KEYWORD OPEN_PAREN error CLOSE_PAREN comando  */
#line 392 "c-minus/parser/parser.y"
                                                                     { 
                    yyerror("Expressão inválida na condição do while"); 
                    yyerrok; 
                    (yyval.ast_node) = NULL;
                }
#line 1964 "c-minus/parser/parser.tab.c"
    break;

  case 132: /* iteracao_decl: WHILE_KEYWORD error  */
#line 397 "c-minus/parser/parser.y"
                                      { 
                    yyerror("Esperado '(' após while"); 
                    yyerrok; 
                    (yyval.ast_node) = NULL;
                }
#line 1974 "c-minus/parser/parser.tab.c"
    break;

  case 133: /* retorno_decl: RETURN_KEYWORD SEMICOLON  */
#line 404 "c-minus/parser/parser.y"
                                                           { 
                    /* TODO: Create return statement node */
                    (yyval.ast_node) = NULL;
                }
#line 1983 "c-minus/parser/parser.tab.c"
    break;

  case 134: /* retorno_decl: RETURN_KEYWORD expressao SEMICOLON  */
#line 408 "c-minus/parser/parser.y"
                                                     {
                    /* TODO: Create return statement node with expression */
                    (yyval.ast_node) = (yyvsp[-1].ast_node);
                }
#line 1992 "c-minus/parser/parser.tab.c"
    break;

  case 135: /* retorno_decl: RETURN_KEYWORD expressao error  */
#line 412 "c-minus/parser/parser.y"
                                                 { yyerror("Esperado ';' após return"); yyerrok; (yyval.ast_node) = NULL; }
#line 1998 "c-minus/parser/parser.tab.c"
    break;

  case 136: /* expressao_simples: expressao_soma  */
#line 415 "c-minus/parser/parser.y"
                                                 { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 2004 "c-minus/parser/parser.tab.c"
    break;

  case 137: /* expressao_simples: expressao_soma relacional expressao_soma  */
#line 416 "c-minus/parser/parser.y"
                                                                   { 
                            (yyval.ast_node) = create_binary_op_node((yyvsp[-1].operator), (yyvsp[-2].ast_node), (yyvsp[0].ast_node), line_number);
                        }
#line 2012 "c-minus/parser/parser.tab.c"
    break;

  case 138: /* relacional: LE_OP  */
#line 421 "c-minus/parser/parser.y"
                                        { (yyval.operator) = OP_LE; }
#line 2018 "c-minus/parser/parser.tab.c"
    break;

  case 139: /* relacional: LT_OP  */
#line 422 "c-minus/parser/parser.y"
                        { (yyval.operator) = OP_LT; }
#line 2024 "c-minus/parser/parser.tab.c"
    break;

  case 140: /* relacional: GT_OP  */
#line 423 "c-minus/parser/parser.y"
                        { (yyval.operator) = OP_GT; }
#line 2030 "c-minus/parser/parser.tab.c"
    break;

  case 141: /* relacional: GE_OP  */
#line 424 "c-minus/parser/parser.y"
                        { (yyval.operator) = OP_GE; }
#line 2036 "c-minus/parser/parser.tab.c"
    break;

  case 142: /* relacional: EQUAL_OP  */
#line 425 "c-minus/parser/parser.y"
                           { (yyval.operator) = OP_EQ; }
#line 2042 "c-minus/parser/parser.tab.c"
    break;

  case 143: /* relacional: NE_OP  */
#line 426 "c-minus/parser/parser.y"
                        { (yyval.operator) = OP_NE; }
#line 2048 "c-minus/parser/parser.tab.c"
    break;

  case 144: /* expressao_soma: termo  */
#line 429 "c-minus/parser/parser.y"
                                        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 2054 "c-minus/parser/parser.tab.c"
    break;

  case 145: /* expressao_soma: expressao_soma soma_op termo  */
#line 430 "c-minus/parser/parser.y"
                                                       { 
                            (yyval.ast_node) = create_binary_op_node((yyvsp[-1].operator), (yyvsp[-2].ast_node), (yyvsp[0].ast_node), line_number);
                        }
#line 2062 "c-minus/parser/parser.tab.c"
    break;

  case 146: /* soma_op: PLUS_OP  */
#line 435 "c-minus/parser/parser.y"
                                          { (yyval.operator) = OP_ADD; }
#line 2068 "c-minus/parser/parser.tab.c"
    break;

  case 147: /* soma_op: MINUS_OP  */
#line 436 "c-minus/parser/parser.y"
                           { (yyval.operator) = OP_SUB; }
#line 2074 "c-minus/parser/parser.tab.c"
    break;

  case 148: /* termo: fator  */
#line 439 "c-minus/parser/parser.y"
                                        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 2080 "c-minus/parser/parser.tab.c"
    break;

  case 149: /* termo: termo mult_op fator  */
#line 440 "c-minus/parser/parser.y"
                                              { 
                            (yyval.ast_node) = create_binary_op_node((yyvsp[-1].operator), (yyvsp[-2].ast_node), (yyvsp[0].ast_node), line_number);
                        }
#line 2088 "c-minus/parser/parser.tab.c"
    break;

  case 150: /* mult_op: MULT_OP  */
#line 445 "c-minus/parser/parser.y"
                                          { (yyval.operator) = OP_MUL; }
#line 2094 "c-minus/parser/parser.tab.c"
    break;

  case 151: /* mult_op: DIV_OP  */
#line 446 "c-minus/parser/parser.y"
                         { (yyval.operator) = OP_DIV; }
#line 2100 "c-minus/parser/parser.tab.c"
    break;


#line 2104 "c-minus/parser/parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 449 "c-minus/parser/parser.y"


void yyerror(const char *s){
    if (strcmp(s, "syntax error") == 0) {
        fprintf(stderr, "(%d) Erro sintático na linha %d, coluna %d: Token inesperado\n", 
            ++errors_count, line_number, column_number);
    } else {
        fprintf(stderr, "(%d) Erro sintático na linha %d, coluna %d: %s\n", 
            ++errors_count, line_number, column_number, s);
    }
}
