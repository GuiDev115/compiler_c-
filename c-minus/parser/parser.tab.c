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


/* C-MINUS PARSER
Feito por: 
    - Guilherme Fabricio Brito da Rosa
    - Harisson de Carvalho Alvarenga
    - Raul Soares de Carvalho
*/  
    #include <stdio.h>
    #include <stdlib.h>

    extern int line_number;
    extern int column_number;
    extern int errors_count;
    
    int yylex(void);
    void yyerror(const char *s);

#line 90 "c-minus/parser/parser.tab.c"

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
  YYSYMBOL_INT_TYPE = 3,                   /* INT_TYPE  */
  YYSYMBOL_FLOAT_TYPE = 4,                 /* FLOAT_TYPE  */
  YYSYMBOL_CHAR_TYPE = 5,                  /* CHAR_TYPE  */
  YYSYMBOL_STRUCT_TYPE = 6,                /* STRUCT_TYPE  */
  YYSYMBOL_VOID_TYPE = 7,                  /* VOID_TYPE  */
  YYSYMBOL_IF_KEYWORD = 8,                 /* IF_KEYWORD  */
  YYSYMBOL_ELSE_KEYWORD = 9,               /* ELSE_KEYWORD  */
  YYSYMBOL_WHILE_KEYWORD = 10,             /* WHILE_KEYWORD  */
  YYSYMBOL_RETURN_KEYWORD = 11,            /* RETURN_KEYWORD  */
  YYSYMBOL_PLUS_OP = 12,                   /* PLUS_OP  */
  YYSYMBOL_MINUS_OP = 13,                  /* MINUS_OP  */
  YYSYMBOL_MULT_OP = 14,                   /* MULT_OP  */
  YYSYMBOL_DIV_OP = 15,                    /* DIV_OP  */
  YYSYMBOL_MOD_OP = 16,                    /* MOD_OP  */
  YYSYMBOL_ASSIGN_OP = 17,                 /* ASSIGN_OP  */
  YYSYMBOL_EQUAL_OP = 18,                  /* EQUAL_OP  */
  YYSYMBOL_NE_OP = 19,                     /* NE_OP  */
  YYSYMBOL_LT_OP = 20,                     /* LT_OP  */
  YYSYMBOL_LE_OP = 21,                     /* LE_OP  */
  YYSYMBOL_GT_OP = 22,                     /* GT_OP  */
  YYSYMBOL_GE_OP = 23,                     /* GE_OP  */
  YYSYMBOL_OPEN_BRACE = 24,                /* OPEN_BRACE  */
  YYSYMBOL_CLOSE_BRACE = 25,               /* CLOSE_BRACE  */
  YYSYMBOL_OPEN_PAREN = 26,                /* OPEN_PAREN  */
  YYSYMBOL_CLOSE_PAREN = 27,               /* CLOSE_PAREN  */
  YYSYMBOL_OPEN_BRACKET = 28,              /* OPEN_BRACKET  */
  YYSYMBOL_CLOSE_BRACKET = 29,             /* CLOSE_BRACKET  */
  YYSYMBOL_SEMICOLON = 30,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 31,                     /* COMMA  */
  YYSYMBOL_DOT = 32,                       /* DOT  */
  YYSYMBOL_IDENTIFIER = 33,                /* IDENTIFIER  */
  YYSYMBOL_INT_NUMBER = 34,                /* INT_NUMBER  */
  YYSYMBOL_REAL_NUMBER = 35,               /* REAL_NUMBER  */
  YYSYMBOL_INVALID_IDENTIFIER = 36,        /* INVALID_IDENTIFIER  */
  YYSYMBOL_LEXICAL_ERROR = 37,             /* LEXICAL_ERROR  */
  YYSYMBOL_LOWER = 38,                     /* LOWER  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_programa = 40,                  /* programa  */
  YYSYMBOL_declaracao_lista = 41,          /* declaracao_lista  */
  YYSYMBOL_declaracao = 42,                /* declaracao  */
  YYSYMBOL_var_declaracao = 43,            /* var_declaracao  */
  YYSYMBOL_arranjo_dimensao = 44,          /* arranjo_dimensao  */
  YYSYMBOL_tipo_especificador = 45,        /* tipo_especificador  */
  YYSYMBOL_atributos_declaracao = 46,      /* atributos_declaracao  */
  YYSYMBOL_fun_declaracao = 47,            /* fun_declaracao  */
  YYSYMBOL_params = 48,                    /* params  */
  YYSYMBOL_param_lista = 49,               /* param_lista  */
  YYSYMBOL_param = 50,                     /* param  */
  YYSYMBOL_composto_decl = 51,             /* composto_decl  */
  YYSYMBOL_local_declaracoes = 52,         /* local_declaracoes  */
  YYSYMBOL_comando_lista = 53,             /* comando_lista  */
  YYSYMBOL_comando = 54,                   /* comando  */
  YYSYMBOL_expressao_decl = 55,            /* expressao_decl  */
  YYSYMBOL_selecao_decl = 56,              /* selecao_decl  */
  YYSYMBOL_iteracao_decl = 57,             /* iteracao_decl  */
  YYSYMBOL_retorno_decl = 58,              /* retorno_decl  */
  YYSYMBOL_expressao = 59,                 /* expressao  */
  YYSYMBOL_var = 60,                       /* var  */
  YYSYMBOL_arranjo_acesso = 61,            /* arranjo_acesso  */
  YYSYMBOL_expressao_simples = 62,         /* expressao_simples  */
  YYSYMBOL_relacional = 63,                /* relacional  */
  YYSYMBOL_expressao_soma = 64,            /* expressao_soma  */
  YYSYMBOL_soma_op = 65,                   /* soma_op  */
  YYSYMBOL_termo = 66,                     /* termo  */
  YYSYMBOL_mult_op = 67,                   /* mult_op  */
  YYSYMBOL_fator = 68,                     /* fator  */
  YYSYMBOL_ativacao = 69,                  /* ativacao  */
  YYSYMBOL_args = 70,                      /* args  */
  YYSYMBOL_arg_lista = 71                  /* arg_lista  */
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
#define YYLAST   222

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  170

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    35,    35,    38,    39,    42,    43,    46,    47,    48,
      49,    50,    53,    54,    55,    56,    59,    60,    61,    62,
      63,    64,    65,    68,    69,    72,    73,    74,    77,    78,
      81,    82,    85,    86,    87,    90,    91,    92,    95,    96,
      99,   100,   103,   104,   105,   106,   107,   110,   111,   112,
     115,   116,   117,   118,   119,   122,   123,   124,   125,   128,
     129,   130,   133,   134,   137,   138,   139,   140,   143,   144,
     145,   146,   149,   150,   153,   154,   155,   156,   157,   158,
     161,   162,   165,   166,   169,   170,   173,   174,   177,   178,
     179,   180,   181,   182,   183,   186,   187,   188,   191,   192,
     195,   196
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
  "\"end of file\"", "error", "\"invalid token\"", "INT_TYPE",
  "FLOAT_TYPE", "CHAR_TYPE", "STRUCT_TYPE", "VOID_TYPE", "IF_KEYWORD",
  "ELSE_KEYWORD", "WHILE_KEYWORD", "RETURN_KEYWORD", "PLUS_OP", "MINUS_OP",
  "MULT_OP", "DIV_OP", "MOD_OP", "ASSIGN_OP", "EQUAL_OP", "NE_OP", "LT_OP",
  "LE_OP", "GT_OP", "GE_OP", "OPEN_BRACE", "CLOSE_BRACE", "OPEN_PAREN",
  "CLOSE_PAREN", "OPEN_BRACKET", "CLOSE_BRACKET", "SEMICOLON", "COMMA",
  "DOT", "IDENTIFIER", "INT_NUMBER", "REAL_NUMBER", "INVALID_IDENTIFIER",
  "LEXICAL_ERROR", "LOWER", "$accept", "programa", "declaracao_lista",
  "declaracao", "var_declaracao", "arranjo_dimensao", "tipo_especificador",
  "atributos_declaracao", "fun_declaracao", "params", "param_lista",
  "param", "composto_decl", "local_declaracoes", "comando_lista",
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

#define YYPACT_NINF (-94)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-100)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     195,   -94,   -94,   -94,   -22,   -94,    23,   195,   -94,   -94,
     -17,   -94,    40,   -94,   -94,    62,   183,    38,   190,     2,
     -94,    58,   -94,    98,   142,   -94,   117,   106,   120,    90,
      42,   -94,   135,    26,   -94,    73,   -94,   -94,   -94,   131,
     152,   131,   131,   195,   146,   155,   -94,    46,   -94,    68,
     -94,   -94,   -94,   -94,   -94,   -10,   167,   195,   -94,   -94,
       6,   -94,   -94,   -94,    74,   174,   101,   -94,   126,   128,
     -20,   -94,     4,   -94,   112,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,    16,   187,   -94,   150,    14,   -94,   -94,
     -94,   -94,   -94,   -94,     8,   -94,    61,   -94,    47,   178,
     114,    32,    85,   -94,   -94,   148,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,   -94,   148,   148,   -94,   -94,   148,   179,
     115,   180,   123,   -94,   -94,   -94,   -94,   -94,   181,   -94,
     124,   182,   185,   104,   -94,   -94,    48,    14,   -94,   102,
     102,   102,   102,   102,   102,   -94,   -94,   -94,   148,   -94,
     -94,   -94,   -94,   -94,   200,   -94,   -94,   -94,   -94,   184,
     184,   184,   102,    88,   -94,   186,   105,   -94,   -94,   -94
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
      32,     0,     0,     0,     0,     0,    12,     0,    27,     0,
      26,    25,    31,    11,    10,     0,     0,    40,    34,    33,
       0,     8,    37,    39,     0,     0,     0,    36,     0,     0,
       0,    35,     0,    48,    64,    92,    91,    43,    41,    42,
      44,    45,    46,     0,    89,    63,    72,    80,    84,    90,
      15,    14,    13,    54,     0,    58,     0,    59,     0,     0,
       0,     0,     0,    49,    47,     0,    82,    83,    78,    79,
      75,    74,    76,    77,     0,     0,    86,    87,     0,     0,
       0,     0,     0,    61,    60,    94,    93,    88,     0,   100,
       0,    98,     0,     0,    62,    89,    73,    81,    85,     0,
       0,     0,     0,     0,     0,    97,    96,    95,     0,    68,
      68,    68,    53,    52,    50,    57,    56,    55,   101,    67,
      66,    65,     0,     0,    51,     0,     0,    71,    70,    69
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -94,   -94,   -94,   203,   -12,   -94,     1,   -94,   -94,   -94,
     -94,   168,   136,   -94,   -94,    17,   -94,   -94,   -94,   -94,
     -70,   -93,    15,   -94,   -94,   103,   -94,   107,   -94,   100,
     -94,   -94,   -94
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     6,     7,     8,     9,    55,    23,    24,    11,    29,
      30,    31,    77,    57,    64,    78,    79,    80,    81,    82,
      83,    84,   159,    85,   114,    86,   115,    87,   118,    88,
      89,   130,   131
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      98,    10,   100,    32,    22,    99,    72,    65,    10,   119,
      97,    12,    38,    74,    75,    76,    15,   103,    60,    28,
      61,   135,   135,    13,   120,   135,   122,    45,   116,   117,
      72,   129,   133,   128,    72,   134,    33,    74,    75,    76,
      66,    74,    75,    76,    28,    63,   104,    56,   123,   -38,
     -38,   -38,   -38,   -38,   -38,    46,   -38,   -38,    72,   -99,
     106,   107,   121,    17,    16,    74,    75,    76,    25,    58,
     -38,   -38,   -38,    43,    17,    67,   -38,   124,   158,   -38,
     -38,   -38,    68,    34,    69,    70,   132,    72,    18,   165,
      19,    41,    20,   166,    74,    75,    76,    59,    47,    71,
      72,    19,    91,    20,    73,   150,   168,    74,    75,    76,
      68,    72,    69,    70,    72,   126,   140,    42,    74,    75,
      76,    74,    75,    76,   143,   146,    47,    93,    72,    95,
      92,    35,    73,   151,   169,    74,    75,    76,   101,   -19,
     102,   127,   141,    36,    39,     1,     2,     3,     4,     5,
     144,   147,    94,    40,    96,    47,   152,   153,   154,   155,
     156,   157,   106,   107,    44,   160,   161,    37,   108,   109,
     110,   111,   112,   113,    72,    48,    53,    50,    51,   164,
      49,    74,    75,    76,    21,    54,     1,     2,     3,     4,
       5,    26,    62,     1,     2,     3,     4,    27,     1,     2,
       3,     4,     5,    90,   105,   125,   139,   142,   145,   162,
      14,    52,   163,   148,   149,   167,     0,   136,   138,     0,
       0,     0,   137
};

static const yytype_int16 yycheck[] =
{
      70,     0,    72,     1,    16,     1,    26,     1,     7,     1,
      30,    33,    24,    33,    34,    35,    33,     1,    28,    18,
      30,   114,   115,     0,    94,   118,    96,     1,    14,    15,
      26,   101,   102,     1,    26,   105,    34,    33,    34,    35,
      34,    33,    34,    35,    43,    57,    30,     1,     1,     3,
       4,     5,     6,     7,     8,    29,    10,    11,    26,    27,
      12,    13,     1,     1,    24,    33,    34,    35,    30,     1,
      24,    25,    26,    31,     1,     1,    30,    30,   148,    33,
      34,    35,     8,    25,    10,    11,     1,    26,    26,     1,
      28,     1,    30,   163,    33,    34,    35,    29,    24,    25,
      26,    28,     1,    30,    30,     1,     1,    33,    34,    35,
       8,    26,    10,    11,    26,     1,     1,    27,    33,    34,
      35,    33,    34,    35,     1,     1,    24,     1,    26,     1,
      29,    33,    30,    29,    29,    33,    34,    35,    26,    33,
      28,    27,    27,     1,    27,     3,     4,     5,     6,     7,
      27,    27,    26,    33,    26,    24,   139,   140,   141,   142,
     143,   144,    12,    13,    29,   150,   151,    25,    18,    19,
      20,    21,    22,    23,    26,    39,    30,    41,    42,   162,
      28,    33,    34,    35,     1,    30,     3,     4,     5,     6,
       7,     1,    25,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,    29,    17,    27,    27,    27,    27,     9,
       7,    43,    28,    31,    29,    29,    -1,   114,   118,    -1,
      -1,    -1,   115
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    40,    41,    42,    43,
      45,    47,    33,     0,    42,    33,    24,     1,    26,    28,
      30,     1,    43,    45,    46,    30,     1,     7,    45,    48,
      49,    50,     1,    34,    25,    33,     1,    25,    43,    27,
      33,     1,    27,    31,    29,     1,    29,    24,    51,    28,
      51,    51,    50,    30,    30,    44,     1,    52,     1,    29,
      28,    30,    25,    43,    53,     1,    34,     1,     8,    10,
      11,    25,    26,    30,    33,    34,    35,    51,    54,    55,
      56,    57,    58,    59,    60,    62,    64,    66,    68,    69,
      29,     1,    29,     1,    26,     1,    26,    30,    59,     1,
      59,    26,    28,     1,    30,    17,    12,    13,    18,    19,
      20,    21,    22,    23,    63,    65,    14,    15,    67,     1,
      59,     1,    59,     1,    30,    27,     1,    27,     1,    59,
      70,    71,     1,    59,    59,    60,    64,    66,    68,    27,
       1,    27,    27,     1,    27,    27,     1,    27,    31,    29,
       1,    29,    54,    54,    54,    54,    54,    54,    59,    61,
      61,    61,     9,    28,    54,     1,    59,    29,     1,    29
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    43,    43,    43,
      43,    43,    44,    44,    44,    44,    45,    45,    45,    45,
      45,    45,    45,    46,    46,    47,    47,    47,    48,    48,
      49,    49,    50,    50,    50,    51,    51,    51,    52,    52,
      53,    53,    54,    54,    54,    54,    54,    55,    55,    55,
      56,    56,    56,    56,    56,    57,    57,    57,    57,    58,
      58,    58,    59,    59,    60,    60,    60,    60,    61,    61,
      61,    61,    62,    62,    63,    63,    63,    63,    63,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    68,    68,
      68,    68,    68,    68,    68,    69,    69,    69,    70,    70,
      71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     7,     4,
       6,     6,     0,     4,     4,     4,     1,     1,     1,     1,
       5,     5,     5,     1,     2,     6,     6,     6,     1,     1,
       1,     3,     2,     4,     4,     4,     4,     3,     0,     2,
       0,     2,     1,     1,     1,     1,     1,     2,     1,     2,
       5,     7,     5,     5,     2,     5,     5,     5,     2,     2,
       3,     3,     3,     1,     1,     5,     5,     5,     0,     4,
       4,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     3,     1,
       1,     1,     1,     3,     3,     4,     4,     4,     1,     0,
       1,     3
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
#line 35 "c-minus/parser/parser.y"
                                                              { printf("Parsing concluído com sucesso!\n"); }
#line 1279 "c-minus/parser/parser.tab.c"
    break;

  case 9: /* var_declaracao: tipo_especificador IDENTIFIER error SEMICOLON  */
#line 48 "c-minus/parser/parser.y"
                                                                { yyerror("Erro na declaração de variável"); yyerrok; }
#line 1285 "c-minus/parser/parser.tab.c"
    break;

  case 10: /* var_declaracao: tipo_especificador IDENTIFIER OPEN_BRACKET INT_NUMBER error SEMICOLON  */
#line 49 "c-minus/parser/parser.y"
                                                                                        { yyerror("Esperado ']' após índice do array"); yyerrok; }
#line 1291 "c-minus/parser/parser.tab.c"
    break;

  case 11: /* var_declaracao: tipo_especificador IDENTIFIER OPEN_BRACKET error CLOSE_BRACKET SEMICOLON  */
#line 50 "c-minus/parser/parser.y"
                                                                                           { yyerror("Índice inválido no array"); yyerrok; }
#line 1297 "c-minus/parser/parser.tab.c"
    break;

  case 14: /* arranjo_dimensao: arranjo_dimensao OPEN_BRACKET INT_NUMBER error  */
#line 55 "c-minus/parser/parser.y"
                                                                 { yyerror("Esperado ']' após dimensão do array"); yyerrok; }
#line 1303 "c-minus/parser/parser.tab.c"
    break;

  case 15: /* arranjo_dimensao: arranjo_dimensao OPEN_BRACKET error CLOSE_BRACKET  */
#line 56 "c-minus/parser/parser.y"
                                                                    { yyerror("Dimensão inválida no array"); yyerrok; }
#line 1309 "c-minus/parser/parser.tab.c"
    break;

  case 21: /* tipo_especificador: STRUCT_TYPE IDENTIFIER OPEN_BRACE atributos_declaracao error  */
#line 64 "c-minus/parser/parser.y"
                                                                               { yyerror("Esperado '}' após declarações do struct"); yyerrok; }
#line 1315 "c-minus/parser/parser.tab.c"
    break;

  case 22: /* tipo_especificador: STRUCT_TYPE IDENTIFIER OPEN_BRACE error CLOSE_BRACE  */
#line 65 "c-minus/parser/parser.y"
                                                                      { yyerror("Declarações inválidas no struct"); yyerrok; }
#line 1321 "c-minus/parser/parser.tab.c"
    break;

  case 26: /* fun_declaracao: tipo_especificador IDENTIFIER OPEN_PAREN params error composto_decl  */
#line 73 "c-minus/parser/parser.y"
                                                                                      { yyerror("Esperado ')' após parâmetros da função"); yyerrok; }
#line 1327 "c-minus/parser/parser.tab.c"
    break;

  case 27: /* fun_declaracao: tipo_especificador IDENTIFIER OPEN_PAREN error CLOSE_PAREN composto_decl  */
#line 74 "c-minus/parser/parser.y"
                                                                                           { yyerror("Parâmetros inválidos na função"); yyerrok; }
#line 1333 "c-minus/parser/parser.tab.c"
    break;

  case 34: /* param: tipo_especificador IDENTIFIER OPEN_BRACKET error  */
#line 87 "c-minus/parser/parser.y"
                                                                   { yyerror("Esperado ']' após '[' no parâmetro array"); yyerrok; }
#line 1339 "c-minus/parser/parser.tab.c"
    break;

  case 36: /* composto_decl: OPEN_BRACE local_declaracoes comando_lista error  */
#line 91 "c-minus/parser/parser.y"
                                                                   { yyerror("Esperado '}' para fechar bloco de comandos"); yyerrok; }
#line 1345 "c-minus/parser/parser.tab.c"
    break;

  case 37: /* composto_decl: OPEN_BRACE error CLOSE_BRACE  */
#line 92 "c-minus/parser/parser.y"
                                               { yyerror("Comandos inválidos no bloco"); yyerrok; }
#line 1351 "c-minus/parser/parser.tab.c"
    break;

  case 49: /* expressao_decl: expressao error  */
#line 112 "c-minus/parser/parser.y"
                                  { yyerror("Esperado ';' após expressão"); yyerrok; }
#line 1357 "c-minus/parser/parser.tab.c"
    break;

  case 52: /* selecao_decl: IF_KEYWORD OPEN_PAREN expressao error comando  */
#line 117 "c-minus/parser/parser.y"
                                                                { yyerror("Esperado ')' após condição do if"); yyerrok; }
#line 1363 "c-minus/parser/parser.tab.c"
    break;

  case 53: /* selecao_decl: IF_KEYWORD OPEN_PAREN error CLOSE_PAREN comando  */
#line 118 "c-minus/parser/parser.y"
                                                                  { yyerror("Expressão inválida na condição do if"); yyerrok; }
#line 1369 "c-minus/parser/parser.tab.c"
    break;

  case 54: /* selecao_decl: IF_KEYWORD error  */
#line 119 "c-minus/parser/parser.y"
                                   { yyerror("Esperado '(' após if"); yyerrok; }
#line 1375 "c-minus/parser/parser.tab.c"
    break;

  case 56: /* iteracao_decl: WHILE_KEYWORD OPEN_PAREN expressao error comando  */
#line 123 "c-minus/parser/parser.y"
                                                                   { yyerror("Esperado ')' após condição do while"); yyerrok; }
#line 1381 "c-minus/parser/parser.tab.c"
    break;

  case 57: /* iteracao_decl: WHILE_KEYWORD OPEN_PAREN error CLOSE_PAREN comando  */
#line 124 "c-minus/parser/parser.y"
                                                                     { yyerror("Expressão inválida na condição do while"); yyerrok; }
#line 1387 "c-minus/parser/parser.tab.c"
    break;

  case 58: /* iteracao_decl: WHILE_KEYWORD error  */
#line 125 "c-minus/parser/parser.y"
                                      { yyerror("Esperado '(' após while"); yyerrok; }
#line 1393 "c-minus/parser/parser.tab.c"
    break;

  case 61: /* retorno_decl: RETURN_KEYWORD expressao error  */
#line 130 "c-minus/parser/parser.y"
                                                 { yyerror("Esperado ';' após return"); yyerrok; }
#line 1399 "c-minus/parser/parser.tab.c"
    break;

  case 66: /* var: IDENTIFIER OPEN_BRACKET expressao error arranjo_acesso  */
#line 139 "c-minus/parser/parser.y"
                                                                         { yyerror("Esperado ']' após índice do array"); yyerrok; }
#line 1405 "c-minus/parser/parser.tab.c"
    break;

  case 67: /* var: IDENTIFIER OPEN_BRACKET error CLOSE_BRACKET arranjo_acesso  */
#line 140 "c-minus/parser/parser.y"
                                                                             { yyerror("Índice inválido no array"); yyerrok; }
#line 1411 "c-minus/parser/parser.tab.c"
    break;

  case 70: /* arranjo_acesso: arranjo_acesso OPEN_BRACKET expressao error  */
#line 145 "c-minus/parser/parser.y"
                                                              { yyerror("Esperado ']' após índice do array multidimensional"); yyerrok; }
#line 1417 "c-minus/parser/parser.tab.c"
    break;

  case 71: /* arranjo_acesso: arranjo_acesso OPEN_BRACKET error CLOSE_BRACKET  */
#line 146 "c-minus/parser/parser.y"
                                                                  { yyerror("Índice inválido no array multidimensional"); yyerrok; }
#line 1423 "c-minus/parser/parser.tab.c"
    break;

  case 93: /* fator: OPEN_PAREN expressao error  */
#line 182 "c-minus/parser/parser.y"
                                             { yyerror("Esperado ')' após expressão"); yyerrok; }
#line 1429 "c-minus/parser/parser.tab.c"
    break;

  case 94: /* fator: OPEN_PAREN error CLOSE_PAREN  */
#line 183 "c-minus/parser/parser.y"
                                               { yyerror("Expressão inválida entre parênteses"); yyerrok; }
#line 1435 "c-minus/parser/parser.tab.c"
    break;

  case 96: /* ativacao: IDENTIFIER OPEN_PAREN args error  */
#line 187 "c-minus/parser/parser.y"
                                                   { yyerror("Esperado ')' após argumentos da função"); yyerrok; }
#line 1441 "c-minus/parser/parser.tab.c"
    break;

  case 97: /* ativacao: IDENTIFIER OPEN_PAREN error CLOSE_PAREN  */
#line 188 "c-minus/parser/parser.y"
                                                          { yyerror("Argumentos inválidos na chamada de função"); yyerrok; }
#line 1447 "c-minus/parser/parser.tab.c"
    break;


#line 1451 "c-minus/parser/parser.tab.c"

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

#line 199 "c-minus/parser/parser.y"


void yyerror(const char *s){
    fprintf(stderr, "(%d) Erro sintático na linha %d, coluna %d: %s\n", ++errors_count, line_number, column_number, s);
}

extern FILE *yyin;
extern int yydebug;

int main(int argc, char *argv[]) {
    yydebug = 1;
    errors_count = 0; // Inicializa contador de erros
    
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Não foi possível abrir o arquivo de entrada");
        return 1;
    }

    yyin = input_file;
    
    printf("Iniciando análise sintática...\n");
    
    int result = yyparse();
    
    if (errors_count == 0) {
        printf("Análise sintática concluída sem erros.\n");
    } else {
        printf("Análise sintática concluída com %d erro(s).\n", errors_count);
    }

    fclose(input_file);

    return result;
}
