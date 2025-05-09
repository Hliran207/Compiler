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
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yyerror(char *s);
int yylex();
int yyparse();
extern int yylineno;
extern char* yytext;

typedef struct Node {
    char *token;
    struct Node *left;
    struct Node *right;
} Node;

Node *mkNode(char *token, Node *left, Node *right);
void printtree(Node *tree, int tab);
void printTabs(int numOfTabs);

#line 93 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
    BOOL = 258,                    /* BOOL  */
    CHAR = 259,                    /* CHAR  */
    INT = 260,                     /* INT  */
    REAL = 261,                    /* REAL  */
    STRING = 262,                  /* STRING  */
    INTPTR = 263,                  /* INTPTR  */
    CHARPTR = 264,                 /* CHARPTR  */
    REALPTR = 265,                 /* REALPTR  */
    TYPE = 266,                    /* TYPE  */
    IF = 267,                      /* IF  */
    ELIF = 268,                    /* ELIF  */
    ELSE = 269,                    /* ELSE  */
    WHILE = 270,                   /* WHILE  */
    FOR = 271,                     /* FOR  */
    VAR = 272,                     /* VAR  */
    PAR = 273,                     /* PAR  */
    RETURN = 274,                  /* RETURN  */
    NULLL = 275,                   /* NULLL  */
    DO = 276,                      /* DO  */
    RETURNS = 277,                 /* RETURNS  */
    BEGIN_T = 278,                 /* BEGIN_T  */
    END = 279,                     /* END  */
    DEF = 280,                     /* DEF  */
    CALL = 281,                    /* CALL  */
    AND = 282,                     /* AND  */
    NOT = 283,                     /* NOT  */
    OR = 284,                      /* OR  */
    DIV = 285,                     /* DIV  */
    ASSIGNMENT = 286,              /* ASSIGNMENT  */
    EQL = 287,                     /* EQL  */
    GREATER = 288,                 /* GREATER  */
    GREATER_EQL = 289,             /* GREATER_EQL  */
    LESS = 290,                    /* LESS  */
    LESS_EQL = 291,                /* LESS_EQL  */
    MINUS = 292,                   /* MINUS  */
    NOT_EQL = 293,                 /* NOT_EQL  */
    PLUS = 294,                    /* PLUS  */
    MULTI = 295,                   /* MULTI  */
    ADDRESS = 296,                 /* ADDRESS  */
    LENGTH = 297,                  /* LENGTH  */
    SEMICOLON = 298,               /* SEMICOLON  */
    COLON = 299,                   /* COLON  */
    COMMA = 300,                   /* COMMA  */
    OPENBRACE = 301,               /* OPENBRACE  */
    CLOSEBRACE = 302,              /* CLOSEBRACE  */
    OPENPAREN = 303,               /* OPENPAREN  */
    CLOSEPAREN = 304,              /* CLOSEPAREN  */
    OPENBRACKET = 305,             /* OPENBRACKET  */
    CLOSEBRACKET = 306,            /* CLOSEBRACKET  */
    B_TRUE = 307,                  /* B_TRUE  */
    B_FALSE = 308,                 /* B_FALSE  */
    CHAR_LIT = 309,                /* CHAR_LIT  */
    STRING_LIT = 310,              /* STRING_LIT  */
    DEC_LIT = 311,                 /* DEC_LIT  */
    HEX_LIT = 312,                 /* HEX_LIT  */
    REAL_LIT = 313,                /* REAL_LIT  */
    ID = 314                       /* ID  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define BOOL 258
#define CHAR 259
#define INT 260
#define REAL 261
#define STRING 262
#define INTPTR 263
#define CHARPTR 264
#define REALPTR 265
#define TYPE 266
#define IF 267
#define ELIF 268
#define ELSE 269
#define WHILE 270
#define FOR 271
#define VAR 272
#define PAR 273
#define RETURN 274
#define NULLL 275
#define DO 276
#define RETURNS 277
#define BEGIN_T 278
#define END 279
#define DEF 280
#define CALL 281
#define AND 282
#define NOT 283
#define OR 284
#define DIV 285
#define ASSIGNMENT 286
#define EQL 287
#define GREATER 288
#define GREATER_EQL 289
#define LESS 290
#define LESS_EQL 291
#define MINUS 292
#define NOT_EQL 293
#define PLUS 294
#define MULTI 295
#define ADDRESS 296
#define LENGTH 297
#define SEMICOLON 298
#define COLON 299
#define COMMA 300
#define OPENBRACE 301
#define CLOSEBRACE 302
#define OPENPAREN 303
#define CLOSEPAREN 304
#define OPENBRACKET 305
#define CLOSEBRACKET 306
#define B_TRUE 307
#define B_FALSE 308
#define CHAR_LIT 309
#define STRING_LIT 310
#define DEC_LIT 311
#define HEX_LIT 312
#define REAL_LIT 313
#define ID 314

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "parser.y"

    char *str;
    struct Node *node;

#line 269 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_BOOL = 3,                       /* BOOL  */
  YYSYMBOL_CHAR = 4,                       /* CHAR  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_REAL = 6,                       /* REAL  */
  YYSYMBOL_STRING = 7,                     /* STRING  */
  YYSYMBOL_INTPTR = 8,                     /* INTPTR  */
  YYSYMBOL_CHARPTR = 9,                    /* CHARPTR  */
  YYSYMBOL_REALPTR = 10,                   /* REALPTR  */
  YYSYMBOL_TYPE = 11,                      /* TYPE  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELIF = 13,                      /* ELIF  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_FOR = 16,                       /* FOR  */
  YYSYMBOL_VAR = 17,                       /* VAR  */
  YYSYMBOL_PAR = 18,                       /* PAR  */
  YYSYMBOL_RETURN = 19,                    /* RETURN  */
  YYSYMBOL_NULLL = 20,                     /* NULLL  */
  YYSYMBOL_DO = 21,                        /* DO  */
  YYSYMBOL_RETURNS = 22,                   /* RETURNS  */
  YYSYMBOL_BEGIN_T = 23,                   /* BEGIN_T  */
  YYSYMBOL_END = 24,                       /* END  */
  YYSYMBOL_DEF = 25,                       /* DEF  */
  YYSYMBOL_CALL = 26,                      /* CALL  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_NOT = 28,                       /* NOT  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_DIV = 30,                       /* DIV  */
  YYSYMBOL_ASSIGNMENT = 31,                /* ASSIGNMENT  */
  YYSYMBOL_EQL = 32,                       /* EQL  */
  YYSYMBOL_GREATER = 33,                   /* GREATER  */
  YYSYMBOL_GREATER_EQL = 34,               /* GREATER_EQL  */
  YYSYMBOL_LESS = 35,                      /* LESS  */
  YYSYMBOL_LESS_EQL = 36,                  /* LESS_EQL  */
  YYSYMBOL_MINUS = 37,                     /* MINUS  */
  YYSYMBOL_NOT_EQL = 38,                   /* NOT_EQL  */
  YYSYMBOL_PLUS = 39,                      /* PLUS  */
  YYSYMBOL_MULTI = 40,                     /* MULTI  */
  YYSYMBOL_ADDRESS = 41,                   /* ADDRESS  */
  YYSYMBOL_LENGTH = 42,                    /* LENGTH  */
  YYSYMBOL_SEMICOLON = 43,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 44,                     /* COLON  */
  YYSYMBOL_COMMA = 45,                     /* COMMA  */
  YYSYMBOL_OPENBRACE = 46,                 /* OPENBRACE  */
  YYSYMBOL_CLOSEBRACE = 47,                /* CLOSEBRACE  */
  YYSYMBOL_OPENPAREN = 48,                 /* OPENPAREN  */
  YYSYMBOL_CLOSEPAREN = 49,                /* CLOSEPAREN  */
  YYSYMBOL_OPENBRACKET = 50,               /* OPENBRACKET  */
  YYSYMBOL_CLOSEBRACKET = 51,              /* CLOSEBRACKET  */
  YYSYMBOL_B_TRUE = 52,                    /* B_TRUE  */
  YYSYMBOL_B_FALSE = 53,                   /* B_FALSE  */
  YYSYMBOL_CHAR_LIT = 54,                  /* CHAR_LIT  */
  YYSYMBOL_STRING_LIT = 55,                /* STRING_LIT  */
  YYSYMBOL_DEC_LIT = 56,                   /* DEC_LIT  */
  YYSYMBOL_HEX_LIT = 57,                   /* HEX_LIT  */
  YYSYMBOL_REAL_LIT = 58,                  /* REAL_LIT  */
  YYSYMBOL_ID = 59,                        /* ID  */
  YYSYMBOL_YYACCEPT = 60,                  /* $accept  */
  YYSYMBOL_program = 61,                   /* program  */
  YYSYMBOL_function_list = 62,             /* function_list  */
  YYSYMBOL_function = 63,                  /* function  */
  YYSYMBOL_returns_spec = 64,              /* returns_spec  */
  YYSYMBOL_parameter_list = 65,            /* parameter_list  */
  YYSYMBOL_param_decl_list = 66,           /* param_decl_list  */
  YYSYMBOL_param_decl = 67,                /* param_decl  */
  YYSYMBOL_type = 68,                      /* type  */
  YYSYMBOL_opt_var = 69,                   /* opt_var  */
  YYSYMBOL_var_decl_list = 70,             /* var_decl_list  */
  YYSYMBOL_var_decl = 71,                  /* var_decl  */
  YYSYMBOL_var_item_list = 72,             /* var_item_list  */
  YYSYMBOL_var_item = 73,                  /* var_item  */
  YYSYMBOL_literal = 74,                   /* literal  */
  YYSYMBOL_stat_list = 75,                 /* stat_list  */
  YYSYMBOL_stat = 76,                      /* stat  */
  YYSYMBOL_call_stat = 77,                 /* call_stat  */
  YYSYMBOL_if_stat = 78,                   /* if_stat  */
  YYSYMBOL_while_stat = 79,                /* while_stat  */
  YYSYMBOL_do_while_stat = 80,             /* do_while_stat  */
  YYSYMBOL_for_stat = 81,                  /* for_stat  */
  YYSYMBOL_for_header = 82,                /* for_header  */
  YYSYMBOL_update_exp = 83,                /* update_exp  */
  YYSYMBOL_block_stat = 84,                /* block_stat  */
  YYSYMBOL_assignment_stat = 85,           /* assignment_stat  */
  YYSYMBOL_return_stat = 86,               /* return_stat  */
  YYSYMBOL_expression_list = 87,           /* expression_list  */
  YYSYMBOL_expression = 88                 /* expression  */
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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   536

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  226

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   314


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    48,    48,    52,    53,    57,    67,    77,    80,    81,
      85,    86,    90,    94,    95,    96,    97,    98,    99,   100,
     101,   105,   106,   110,   111,   115,   119,   120,   124,   125,
     126,   128,   135,   136,   137,   138,   139,   140,   141,   142,
     145,   146,   147,   151,   152,   153,   154,   155,   156,   157,
     159,   163,   167,   171,   174,   179,   180,   181,   182,   186,
     190,   194,   195,   199,   205,   218,   224,   225,   229,   230,
     231,   232,   235,   238,   246,   251,   252,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   275,   276,   277,   278,   279,   282,   285
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
  "\"end of file\"", "error", "\"invalid token\"", "BOOL", "CHAR", "INT",
  "REAL", "STRING", "INTPTR", "CHARPTR", "REALPTR", "TYPE", "IF", "ELIF",
  "ELSE", "WHILE", "FOR", "VAR", "PAR", "RETURN", "NULLL", "DO", "RETURNS",
  "BEGIN_T", "END", "DEF", "CALL", "AND", "NOT", "OR", "DIV", "ASSIGNMENT",
  "EQL", "GREATER", "GREATER_EQL", "LESS", "LESS_EQL", "MINUS", "NOT_EQL",
  "PLUS", "MULTI", "ADDRESS", "LENGTH", "SEMICOLON", "COLON", "COMMA",
  "OPENBRACE", "CLOSEBRACE", "OPENPAREN", "CLOSEPAREN", "OPENBRACKET",
  "CLOSEBRACKET", "B_TRUE", "B_FALSE", "CHAR_LIT", "STRING_LIT", "DEC_LIT",
  "HEX_LIT", "REAL_LIT", "ID", "$accept", "program", "function_list",
  "function", "returns_spec", "parameter_list", "param_decl_list",
  "param_decl", "type", "opt_var", "var_decl_list", "var_decl",
  "var_item_list", "var_item", "literal", "stat_list", "stat", "call_stat",
  "if_stat", "while_stat", "do_while_stat", "for_stat", "for_header",
  "update_exp", "block_stat", "assignment_stat", "return_stat",
  "expression_list", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-93)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,   -48,    43,    -4,   -93,     1,   -93,   -93,    26,    51,
      50,    66,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,    67,    71,    26,    35,    11,   -93,   -93,    64,    51,
      93,    89,    51,    64,   -93,   -93,    95,    -8,    72,   -93,
      -8,   182,   182,    73,    79,    -8,    65,    70,   -26,   -93,
     103,    -8,   -93,   -93,   -93,   -93,   -93,   -93,   -93,    74,
     107,   -93,    75,   182,   182,    77,    78,    81,   182,   -93,
     -93,   -93,   -93,   -93,   -93,   -93,    82,   -93,   329,   345,
      86,    87,   115,   122,   100,   118,   205,   182,   182,   -93,
     -93,   -38,     5,   -93,   182,   128,   116,   -93,   -93,   -93,
     113,   123,   297,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   182,   182,   182,   115,   115,   135,    -7,
     156,   -93,   142,   182,   134,   121,   126,   377,    68,   278,
      32,   130,   -93,    74,   392,   -93,    26,   182,   -93,   -93,
     238,    45,    45,   140,   -93,   -93,   -93,   -93,   -93,   496,
     -93,   496,   140,    16,   -93,   182,   115,   -93,   182,   144,
     139,   315,   407,   -93,   141,   -24,   -93,   161,   162,   -93,
     152,   -93,   -93,   155,   258,   -93,   182,   163,   422,   -93,
     437,   -93,   166,   182,   -93,   102,   -93,   -14,   182,   167,
     -93,   -93,   361,   115,   182,   -93,   -93,   -93,   169,   157,
     170,   171,   172,   452,   150,   115,   -93,   467,   -93,   173,
     -93,   -93,   -93,   -93,   -93,   203,   159,   -93,   176,   190,
     177,   115,   182,   -93,   -93,   482
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     4,     0,     1,     3,     8,     0,
       0,     9,    10,    14,    15,    13,    16,    17,    18,    19,
      20,     0,     0,     0,     0,    21,    11,    12,     0,     0,
      21,     0,     0,    22,    23,     7,     0,    40,     0,    24,
      40,     0,     0,     0,     0,    40,     0,     0,     0,    43,
       0,    40,    50,    45,    46,    48,    47,    49,    44,     0,
       0,    39,     0,     0,     0,     0,     0,     0,     0,    33,
      34,    35,    36,    32,    37,    38,    96,    99,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     6,
      42,    28,     0,    26,     0,     0,     0,    89,    90,    93,
      91,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    65,     0,     0,    39,     0,     0,     0,     0,     0,
       0,     0,    25,     0,     0,     5,     8,     0,    94,    95,
       0,    81,    82,    80,    83,    85,    86,    87,    88,    78,
      84,    77,    79,    55,    59,     0,     0,    61,     0,     0,
       0,    75,     0,    70,     0,    91,    66,     0,     0,    29,
       0,    27,    74,     0,     0,    97,     0,     0,     0,    62,
       0,    54,     0,     0,    68,     0,    69,     0,     0,    30,
      98,    92,     0,     0,     0,    60,    53,    76,     0,     0,
       0,     0,     0,     0,     0,     0,    56,     0,    52,     0,
      67,    72,    71,    73,    31,    57,     0,    51,     0,     0,
       0,     0,     0,    63,    58,    64
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -93,   -93,   -93,    31,   -93,   219,   -93,   206,     6,   -27,
     -93,   195,   -93,    99,   114,   -31,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,   -80,   -93,   -93,   -92,   -41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,    49,    30,   173,    11,    12,    21,    31,
      33,    34,    92,    93,    77,    50,    51,    52,    53,    54,
      55,    56,    81,   220,    57,    58,    95,   160,   161
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      78,    79,   120,    36,    41,    86,   130,    42,    43,    60,
      28,     5,   131,    44,    83,    45,    45,     1,    46,   186,
      90,     1,    97,    98,    87,    88,   137,   102,    28,   176,
     177,     4,    47,    29,     7,    35,   153,   154,    38,   157,
     200,   201,   202,     6,     9,   127,   128,   129,   132,     8,
     133,    48,    61,   134,    13,    14,    15,    16,    17,    18,
      19,    20,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,    32,   179,   107,   108,   109,
     110,   111,   162,   113,    69,    70,    71,    72,    73,    74,
      75,   197,   156,   199,    27,   104,   174,   105,   106,    22,
     107,   108,   109,   110,   111,   112,   113,   114,   115,    23,
      28,    24,    37,   206,   178,    25,    59,   180,    40,   167,
       9,    80,    61,    82,    84,   215,    94,    89,    62,    85,
      63,   119,   103,    91,    96,   192,    99,   100,    45,    64,
     101,   224,    65,    66,    67,   118,   121,   203,   122,   123,
      68,   198,   135,   207,    69,    70,    71,    72,    73,    74,
      75,    76,    61,   137,   136,   138,   155,   104,    62,   105,
      63,   158,   107,   108,   109,   110,   111,   163,   113,    64,
     164,   225,    65,    66,    67,   165,   170,   181,   182,   185,
      68,   159,   187,   188,    69,    70,    71,    72,    73,    74,
      75,    76,    61,   189,   190,   214,   209,   193,    62,   196,
      63,   204,   208,   210,   211,   212,   217,   218,   219,    64,
     221,   222,    65,    66,    67,   124,   223,    10,    39,    26,
      68,   125,   171,    63,    69,    70,    71,    72,    73,    74,
      75,    76,    64,     0,   169,    65,   126,    67,     0,     0,
       0,     0,     0,    68,     0,     0,     0,    69,    70,    71,
      72,    73,    74,    75,    76,   104,     0,   105,   106,     0,
     107,   108,   109,   110,   111,   112,   113,   114,   115,     0,
       0,     0,     0,     0,     0,   104,     0,   105,   106,   175,
     107,   108,   109,   110,   111,   112,   113,   114,   115,     0,
       0,     0,     0,     0,     0,   104,     0,   105,   106,   191,
     107,   108,   109,   110,   111,   112,   113,   114,   115,     0,
       0,     0,     0,     0,   104,     0,   105,   106,   168,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     0,     0,
       0,     0,   104,     0,   105,   106,   139,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   104,     0,   105,   106,
     183,   107,   108,   109,   110,   111,   112,   113,   114,   115,
       0,     0,   104,   116,   105,   106,     0,   107,   108,   109,
     110,   111,   112,   113,   114,   115,     0,     0,   104,   117,
     105,   106,     0,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     0,     0,   104,   205,   105,   106,     0,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     0,   104,
     166,   105,   106,     0,   107,   108,   109,   110,   111,   112,
     113,   114,   115,     0,   104,   172,   105,   106,     0,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     0,   104,
     184,   105,   106,     0,   107,   108,   109,   110,   111,   112,
     113,   114,   115,     0,   104,   194,   105,   106,     0,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     0,   104,
     195,   105,   106,     0,   107,   108,   109,   110,   111,   112,
     113,   114,   115,     0,   104,   213,   105,   106,     0,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     0,   104,
     216,   105,   106,     0,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   104,     0,   105,   106,     0,   107,   108,
     109,   110,   111,     0,   113,     0,   115
};

static const yytype_int16 yycheck[] =
{
      41,    42,    82,    30,    12,    31,    44,    15,    16,    40,
      17,    59,    50,    21,    45,    23,    23,    25,    26,    43,
      51,    25,    63,    64,    50,    51,    50,    68,    17,    13,
      14,     0,    40,    22,     3,    29,   116,   117,    32,   119,
      54,    55,    56,     0,    18,    86,    87,    88,    43,    48,
      45,    59,    20,    94,     3,     4,     5,     6,     7,     8,
       9,    10,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,    11,   156,    32,    33,    34,
      35,    36,   123,    38,    52,    53,    54,    55,    56,    57,
      58,   183,   119,   185,    59,    27,   137,    29,    30,    49,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    43,
      17,    44,    23,   193,   155,    44,    44,   158,    23,    51,
      18,    48,    20,    44,    59,   205,    19,    24,    26,    59,
      28,    44,    50,    59,    59,   176,    59,    59,    23,    37,
      59,   221,    40,    41,    42,    59,    24,   188,    48,    31,
      48,    49,    24,   194,    52,    53,    54,    55,    56,    57,
      58,    59,    20,    50,    48,    42,    31,    27,    26,    29,
      28,    15,    32,    33,    34,    35,    36,    43,    38,    37,
      59,   222,    40,    41,    42,    59,    56,    43,    49,    48,
      48,    49,    31,    31,    52,    53,    54,    55,    56,    57,
      58,    59,    20,    51,    49,    55,    49,    44,    26,    43,
      28,    44,    43,    43,    43,    43,    43,    14,    59,    37,
      44,    31,    40,    41,    42,    20,    49,     8,    33,    23,
      48,    26,   133,    28,    52,    53,    54,    55,    56,    57,
      58,    59,    37,    -1,   130,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    52,    53,    54,
      55,    56,    57,    58,    59,    27,    -1,    29,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    -1,    29,    30,    51,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    -1,    29,    30,    51,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      -1,    -1,    -1,    -1,    27,    -1,    29,    30,    50,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    -1,    27,    -1,    29,    30,    49,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    27,    -1,    29,    30,
      45,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      -1,    -1,    27,    44,    29,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    -1,    -1,    27,    44,
      29,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    27,    44,    29,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    27,
      43,    29,    30,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    27,    43,    29,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    27,
      43,    29,    30,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    27,    43,    29,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    27,
      43,    29,    30,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    -1,    27,    43,    29,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    27,
      43,    29,    30,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    27,    -1,    29,    30,    -1,    32,    33,
      34,    35,    36,    -1,    38,    -1,    40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    25,    61,    62,    63,    59,     0,    63,    48,    18,
      65,    66,    67,     3,     4,     5,     6,     7,     8,     9,
      10,    68,    49,    43,    44,    44,    67,    59,    17,    22,
      64,    69,    11,    70,    71,    68,    69,    23,    68,    71,
      23,    12,    15,    16,    21,    23,    26,    40,    59,    63,
      75,    76,    77,    78,    79,    80,    81,    84,    85,    44,
      75,    20,    26,    28,    37,    40,    41,    42,    48,    52,
      53,    54,    55,    56,    57,    58,    59,    74,    88,    88,
      48,    82,    44,    75,    59,    59,    31,    50,    51,    24,
      75,    59,    72,    73,    19,    86,    59,    88,    88,    59,
      59,    59,    88,    50,    27,    29,    30,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    44,    44,    59,    44,
      84,    24,    48,    31,    20,    26,    41,    88,    88,    88,
      44,    50,    43,    45,    88,    24,    48,    50,    42,    49,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    84,    84,    31,    69,    84,    15,    49,
      87,    88,    88,    43,    59,    59,    43,    51,    50,    74,
      56,    73,    43,    65,    88,    51,    13,    14,    88,    84,
      88,    43,    49,    45,    43,    48,    43,    31,    31,    51,
      49,    51,    88,    44,    43,    43,    43,    87,    49,    87,
      54,    55,    56,    88,    44,    44,    84,    88,    43,    49,
      43,    43,    43,    43,    55,    84,    43,    43,    14,    59,
      83,    44,    31,    49,    84,    88
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    63,    64,    65,    65,
      66,    66,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    69,    70,    70,    71,    72,    72,    73,    73,
      73,    73,    74,    74,    74,    74,    74,    74,    74,    74,
      75,    75,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    77,    77,    77,    77,    78,    78,    78,    78,    79,
      80,    81,    81,    82,    83,    84,    85,    85,    85,    85,
      85,    85,    85,    85,    86,    87,    87,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,    12,    10,     2,     0,     1,
       1,     3,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     2,     1,     2,     5,     1,     3,     1,     3,
       4,     6,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     8,     7,     6,     5,     4,     7,     8,    11,     4,
       6,     4,     5,     9,     3,     3,     4,     7,     5,     5,
       4,     7,     7,     7,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     5,     2,     3,     3,     1,     4,     5,     1
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
  case 2: /* program: function_list  */
#line 48 "parser.y"
                          {(yyval.node) = (yyvsp[0].node); printtree((yyval.node),0);}
#line 1544 "y.tab.c"
    break;

  case 3: /* function_list: function_list function  */
#line 52 "parser.y"
                                   {(yyval.node) = mkNode("Function_list", (yyvsp[-1].node),(yyvsp[0].node));}
#line 1550 "y.tab.c"
    break;

  case 4: /* function_list: function  */
#line 53 "parser.y"
                       {(yyval.node)=(yyvsp[0].node);}
#line 1556 "y.tab.c"
    break;

  case 5: /* function: DEF ID OPENPAREN parameter_list CLOSEPAREN COLON returns_spec opt_var BEGIN_T stat_list return_stat END  */
#line 57 "parser.y"
                                                                                                                   { 
            /* create nodes for readability */
            Node *idnode=mkNode((yyvsp[-10].str),NULL,NULL);
            Node *parametersnodes=mkNode("PARAMETERS",(yyvsp[-8].node),NULL);
            Node *returnsnode=mkNode("RETURNS",(yyvsp[-5].node),NULL);
            Node *body_statements = mkNode("statements", (yyvsp[-2].node), (yyvsp[-1].node));
            Node *bodynode=mkNode("BODY",(yyvsp[-4].node),body_statements);
            Node *defbody=mkNode("DEF_BODY",returnsnode,bodynode);
            (yyval.node)=mkNode("FUNCTION",idnode,mkNode("FUNC_PARTS", parametersnodes,defbody));
            }
#line 1571 "y.tab.c"
    break;

  case 6: /* function: DEF ID OPENPAREN parameter_list CLOSEPAREN COLON opt_var BEGIN_T stat_list END  */
#line 67 "parser.y"
                                                                                            { 
              /* create nodes for readability */
              Node *idnode=mkNode((yyvsp[-8].str),NULL,NULL);
              Node *parametersnodes=mkNode("PARAMETERS",(yyvsp[-6].node),NULL);
              Node *bodynode=mkNode("BODY",(yyvsp[-3].node),(yyvsp[-1].node));
              (yyval.node)=mkNode("PROCEDURE",idnode,mkNode("PROC_PARTS", parametersnodes,bodynode));
            }
#line 1583 "y.tab.c"
    break;

  case 7: /* returns_spec: RETURNS type  */
#line 77 "parser.y"
                         {(yyval.node)=(yyvsp[0].node);}
#line 1589 "y.tab.c"
    break;

  case 8: /* parameter_list: %empty  */
#line 80 "parser.y"
            {(yyval.node)=mkNode("PARAM_EMPTY",NULL,NULL);}
#line 1595 "y.tab.c"
    break;

  case 9: /* parameter_list: param_decl_list  */
#line 81 "parser.y"
                              {(yyval.node)=(yyvsp[0].node);}
#line 1601 "y.tab.c"
    break;

  case 10: /* param_decl_list: param_decl  */
#line 85 "parser.y"
                       {(yyval.node)=(yyvsp[0].node);}
#line 1607 "y.tab.c"
    break;

  case 11: /* param_decl_list: param_decl_list SEMICOLON param_decl  */
#line 86 "parser.y"
                                                   {(yyval.node)=mkNode("PARAMS_LIST",(yyvsp[-2].node),(yyvsp[0].node));}
#line 1613 "y.tab.c"
    break;

  case 12: /* param_decl: PAR type COLON ID  */
#line 90 "parser.y"
                              {(yyval.node)=mkNode("PARAM",(yyvsp[-2].node),mkNode((yyvsp[0].str),NULL,NULL));}
#line 1619 "y.tab.c"
    break;

  case 13: /* type: INT  */
#line 94 "parser.y"
                {(yyval.node)=mkNode("INT", NULL, NULL);}
#line 1625 "y.tab.c"
    break;

  case 14: /* type: BOOL  */
#line 95 "parser.y"
                  {(yyval.node)=mkNode("BOOL", NULL, NULL);}
#line 1631 "y.tab.c"
    break;

  case 15: /* type: CHAR  */
#line 96 "parser.y"
                  {(yyval.node)=mkNode("CHAR", NULL, NULL);}
#line 1637 "y.tab.c"
    break;

  case 16: /* type: REAL  */
#line 97 "parser.y"
                  {(yyval.node)=mkNode("REAL", NULL, NULL);}
#line 1643 "y.tab.c"
    break;

  case 17: /* type: STRING  */
#line 98 "parser.y"
                    {(yyval.node)=mkNode("STRING", NULL, NULL);}
#line 1649 "y.tab.c"
    break;

  case 18: /* type: INTPTR  */
#line 99 "parser.y"
                    {(yyval.node)=mkNode("INTPTR", NULL, NULL);}
#line 1655 "y.tab.c"
    break;

  case 19: /* type: CHARPTR  */
#line 100 "parser.y"
                     {(yyval.node)=mkNode("CHARPTR", NULL, NULL);}
#line 1661 "y.tab.c"
    break;

  case 20: /* type: REALPTR  */
#line 101 "parser.y"
                     {(yyval.node)=mkNode("REALPTR", NULL, NULL);}
#line 1667 "y.tab.c"
    break;

  case 21: /* opt_var: %empty  */
#line 105 "parser.y"
            {(yyval.node)= mkNode("VAR_EMPTY",NULL,NULL);}
#line 1673 "y.tab.c"
    break;

  case 22: /* opt_var: VAR var_decl_list  */
#line 106 "parser.y"
                                {(yyval.node)=(yyvsp[0].node);}
#line 1679 "y.tab.c"
    break;

  case 23: /* var_decl_list: var_decl  */
#line 110 "parser.y"
                     {(yyval.node)=(yyvsp[0].node);}
#line 1685 "y.tab.c"
    break;

  case 24: /* var_decl_list: var_decl_list var_decl  */
#line 111 "parser.y"
                                    {(yyval.node)=mkNode("VAR_DECL",(yyvsp[-1].node),(yyvsp[0].node));}
#line 1691 "y.tab.c"
    break;

  case 25: /* var_decl: TYPE type COLON var_item_list SEMICOLON  */
#line 115 "parser.y"
                                                    {(yyval.node)=mkNode("VAR_DECL",(yyvsp[-3].node),(yyvsp[-1].node));}
#line 1697 "y.tab.c"
    break;

  case 26: /* var_item_list: var_item  */
#line 119 "parser.y"
                     {(yyval.node)=(yyvsp[0].node);}
#line 1703 "y.tab.c"
    break;

  case 27: /* var_item_list: var_item_list COMMA var_item  */
#line 120 "parser.y"
                                           {(yyval.node)=mkNode("VAR_ITEM_LIST",(yyvsp[-2].node),(yyvsp[0].node));}
#line 1709 "y.tab.c"
    break;

  case 28: /* var_item: ID  */
#line 124 "parser.y"
               {(yyval.node)=mkNode("VAR",mkNode((yyvsp[0].str),NULL,NULL),NULL);}
#line 1715 "y.tab.c"
    break;

  case 29: /* var_item: ID COLON literal  */
#line 125 "parser.y"
                               {(yyval.node)=mkNode("VAR_ASSIGN",mkNode((yyvsp[-2].str),NULL,NULL),(yyvsp[0].node));}
#line 1721 "y.tab.c"
    break;

  case 30: /* var_item: ID OPENBRACKET DEC_LIT CLOSEBRACKET  */
#line 126 "parser.y"
                                                 { 
                (yyval.node) = mkNode("STRING_VAR", mkNode((yyvsp[-3].str), NULL, NULL), mkNode((yyvsp[-1].str),NULL,NULL));}
#line 1728 "y.tab.c"
    break;

  case 31: /* var_item: ID OPENBRACKET DEC_LIT CLOSEBRACKET COLON STRING_LIT  */
#line 128 "parser.y"
                                                                   {
                (yyval.node) = mkNode("STRING_VAL_ASSIGN",mkNode("STRING_VAR",mkNode((yyvsp[-5].str), NULL, NULL), mkNode((yyvsp[-3].str), NULL,NULL)),
                mkNode((yyvsp[0].str), NULL,NULL));   
            }
#line 1737 "y.tab.c"
    break;

  case 32: /* literal: DEC_LIT  */
#line 135 "parser.y"
                  { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 1743 "y.tab.c"
    break;

  case 33: /* literal: B_TRUE  */
#line 136 "parser.y"
                    { (yyval.node) = mkNode("TRUE", NULL, NULL); }
#line 1749 "y.tab.c"
    break;

  case 34: /* literal: B_FALSE  */
#line 137 "parser.y"
                    { (yyval.node) = mkNode("FALSE", NULL, NULL); }
#line 1755 "y.tab.c"
    break;

  case 35: /* literal: CHAR_LIT  */
#line 138 "parser.y"
                      { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 1761 "y.tab.c"
    break;

  case 36: /* literal: STRING_LIT  */
#line 139 "parser.y"
                      { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 1767 "y.tab.c"
    break;

  case 37: /* literal: HEX_LIT  */
#line 140 "parser.y"
                  { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 1773 "y.tab.c"
    break;

  case 38: /* literal: REAL_LIT  */
#line 141 "parser.y"
                   { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 1779 "y.tab.c"
    break;

  case 39: /* literal: NULLL  */
#line 142 "parser.y"
                { (yyval.node) = mkNode("null", NULL, NULL); }
#line 1785 "y.tab.c"
    break;

  case 40: /* stat_list: %empty  */
#line 145 "parser.y"
            {(yyval.node) = mkNode("empty_state_list", NULL,NULL);}
#line 1791 "y.tab.c"
    break;

  case 41: /* stat_list: stat  */
#line 146 "parser.y"
                   {(yyval.node) = (yyvsp[0].node);}
#line 1797 "y.tab.c"
    break;

  case 42: /* stat_list: stat stat_list  */
#line 147 "parser.y"
                             {(yyval.node) = mkNode("statements", (yyvsp[-1].node), (yyvsp[0].node));}
#line 1803 "y.tab.c"
    break;

  case 43: /* stat: function  */
#line 151 "parser.y"
                     {(yyval.node)=(yyvsp[0].node);}
#line 1809 "y.tab.c"
    break;

  case 44: /* stat: assignment_stat  */
#line 152 "parser.y"
                              {(yyval.node) = (yyvsp[0].node);}
#line 1815 "y.tab.c"
    break;

  case 45: /* stat: if_stat  */
#line 153 "parser.y"
                      {(yyval.node) = (yyvsp[0].node);}
#line 1821 "y.tab.c"
    break;

  case 46: /* stat: while_stat  */
#line 154 "parser.y"
                         {(yyval.node) = (yyvsp[0].node);}
#line 1827 "y.tab.c"
    break;

  case 47: /* stat: for_stat  */
#line 155 "parser.y"
                       {(yyval.node) = (yyvsp[0].node);}
#line 1833 "y.tab.c"
    break;

  case 48: /* stat: do_while_stat  */
#line 156 "parser.y"
                            {(yyval.node) = (yyvsp[0].node);}
#line 1839 "y.tab.c"
    break;

  case 49: /* stat: block_stat  */
#line 157 "parser.y"
                         {(yyval.node) = (yyvsp[0].node);}
#line 1845 "y.tab.c"
    break;

  case 50: /* stat: call_stat  */
#line 159 "parser.y"
                        {(yyval.node) = (yyvsp[0].node);}
#line 1851 "y.tab.c"
    break;

  case 51: /* call_stat: ID ASSIGNMENT CALL ID OPENPAREN expression_list CLOSEPAREN SEMICOLON  */
#line 164 "parser.y"
            {
                (yyval.node) = mkNode( "ASSIGNMENT", mkNode((yyvsp[-7].str), NULL, NULL), mkNode("CALL", mkNode((yyvsp[-4].str),NULL,NULL),(yyvsp[-2].node)));
            }
#line 1859 "y.tab.c"
    break;

  case 52: /* call_stat: ID ASSIGNMENT CALL ID OPENPAREN CLOSEPAREN SEMICOLON  */
#line 168 "parser.y"
            {
                (yyval.node) = mkNode( "ASSIGNMENT", mkNode((yyvsp[-6].str), NULL, NULL), mkNode("CALL", mkNode((yyvsp[-3].str),NULL,NULL),NULL));
            }
#line 1867 "y.tab.c"
    break;

  case 53: /* call_stat: CALL ID OPENPAREN expression_list CLOSEPAREN SEMICOLON  */
#line 171 "parser.y"
                                                                     {
                (yyval.node) = mkNode("PROC_CALL", mkNode((yyvsp[-4].str),NULL,NULL), (yyvsp[-2].node));
            }
#line 1875 "y.tab.c"
    break;

  case 54: /* call_stat: CALL ID OPENPAREN CLOSEPAREN SEMICOLON  */
#line 174 "parser.y"
                                                     {
                (yyval.node) = mkNode("PROC_CALL", mkNode((yyvsp[-3].str),NULL,NULL), NULL);
            }
#line 1883 "y.tab.c"
    break;

  case 55: /* if_stat: IF expression COLON block_stat  */
#line 179 "parser.y"
                                           {(yyval.node) = mkNode("if", (yyvsp[-2].node), (yyvsp[0].node));}
#line 1889 "y.tab.c"
    break;

  case 56: /* if_stat: IF expression COLON block_stat ELSE COLON block_stat  */
#line 180 "parser.y"
                                                                   {(yyval.node) = mkNode("if-else", (yyvsp[-5].node), mkNode("then", (yyvsp[-3].node), mkNode("else", (yyvsp[0].node), NULL)));}
#line 1895 "y.tab.c"
    break;

  case 57: /* if_stat: IF expression COLON block_stat ELIF expression COLON block_stat  */
#line 181 "parser.y"
                                                                              {(yyval.node) = mkNode("if-elif", (yyvsp[-6].node), mkNode("then", (yyvsp[-4].node), mkNode("elif-cond", (yyvsp[-2].node), (yyvsp[0].node))));}
#line 1901 "y.tab.c"
    break;

  case 58: /* if_stat: IF expression COLON block_stat ELIF expression COLON block_stat ELSE COLON block_stat  */
#line 182 "parser.y"
                                                                                                    {(yyval.node) = mkNode("if-elif-else", (yyvsp[-9].node), mkNode("then", (yyvsp[-7].node), mkNode("elif-cond", (yyvsp[-5].node), mkNode("elif-then", (yyvsp[-3].node), mkNode("else", (yyvsp[0].node), NULL)))));}
#line 1907 "y.tab.c"
    break;

  case 59: /* while_stat: WHILE expression COLON block_stat  */
#line 186 "parser.y"
                                              {(yyval.node) = mkNode("while", (yyvsp[-2].node), (yyvsp[0].node));}
#line 1913 "y.tab.c"
    break;

  case 60: /* do_while_stat: DO COLON block_stat WHILE expression SEMICOLON  */
#line 190 "parser.y"
                                                           {(yyval.node) = mkNode("do-while", (yyvsp[-3].node), mkNode("cond", (yyvsp[-1].node), NULL));}
#line 1919 "y.tab.c"
    break;

  case 61: /* for_stat: FOR for_header COLON block_stat  */
#line 194 "parser.y"
                                            {(yyval.node) = mkNode("for", (yyvsp[-2].node), (yyvsp[0].node));}
#line 1925 "y.tab.c"
    break;

  case 62: /* for_stat: FOR for_header COLON opt_var block_stat  */
#line 195 "parser.y"
                                                      {(yyval.node) = mkNode("for", (yyvsp[-3].node), mkNode("block", (yyvsp[0].node), (yyvsp[-1].node)));}
#line 1931 "y.tab.c"
    break;

  case 63: /* for_header: OPENPAREN ID ASSIGNMENT expression SEMICOLON expression SEMICOLON update_exp CLOSEPAREN  */
#line 200 "parser.y"
            {(yyval.node) = mkNode("for-header", mkNode("init", mkNode((yyvsp[-7].str), NULL, NULL), (yyvsp[-5].node)), 
                                    mkNode("loop", (yyvsp[-3].node), (yyvsp[-1].node)));}
#line 1938 "y.tab.c"
    break;

  case 64: /* update_exp: ID ASSIGNMENT expression  */
#line 205 "parser.y"
                                     {(yyval.node) = mkNode("update", mkNode((yyvsp[-2].str), NULL, NULL), (yyvsp[0].node));}
#line 1944 "y.tab.c"
    break;

  case 65: /* block_stat: BEGIN_T stat_list END  */
#line 218 "parser.y"
                                  {(yyval.node) = mkNode("block", (yyvsp[-1].node), NULL);}
#line 1950 "y.tab.c"
    break;

  case 66: /* assignment_stat: ID ASSIGNMENT expression SEMICOLON  */
#line 224 "parser.y"
                                                   {(yyval.node) = mkNode("assign", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node));}
#line 1956 "y.tab.c"
    break;

  case 67: /* assignment_stat: ID OPENBRACKET expression CLOSEBRACKET ASSIGNMENT CHAR_LIT SEMICOLON  */
#line 225 "parser.y"
                                                                                       {
                    
                    (yyval.node) = mkNode("array_assign", mkNode((yyvsp[-6].str), (yyvsp[-4].node), NULL), mkNode((yyvsp[-1].str), NULL, NULL));
                }
#line 1965 "y.tab.c"
    break;

  case 68: /* assignment_stat: MULTI ID ASSIGNMENT expression SEMICOLON  */
#line 229 "parser.y"
                                                          {(yyval.node) = mkNode("pointer_assign", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node));}
#line 1971 "y.tab.c"
    break;

  case 69: /* assignment_stat: ID ASSIGNMENT ADDRESS ID SEMICOLON  */
#line 230 "parser.y"
                                                    {(yyval.node) = mkNode("ref_assign", mkNode((yyvsp[-4].str), NULL, NULL), mkNode((yyvsp[-1].str), NULL, NULL));}
#line 1977 "y.tab.c"
    break;

  case 70: /* assignment_stat: ID ASSIGNMENT NULLL SEMICOLON  */
#line 231 "parser.y"
                                               {(yyval.node) = mkNode("null_assign", mkNode((yyvsp[-3].str), NULL, NULL), mkNode("null", NULL, NULL));}
#line 1983 "y.tab.c"
    break;

  case 71: /* assignment_stat: ID OPENBRACKET expression CLOSEBRACKET ASSIGNMENT DEC_LIT SEMICOLON  */
#line 232 "parser.y"
                                                                                     {
                    (yyval.node) = mkNode("array_assign", mkNode((yyvsp[-6].str), (yyvsp[-4].node), NULL), mkNode((yyvsp[-1].str), NULL, NULL));
                }
#line 1991 "y.tab.c"
    break;

  case 72: /* assignment_stat: ID OPENBRACKET expression CLOSEBRACKET ASSIGNMENT STRING_LIT SEMICOLON  */
#line 235 "parser.y"
                                                                                         {
                    (yyval.node) = mkNode("array_assign", mkNode((yyvsp[-6].str), (yyvsp[-4].node), NULL), mkNode((yyvsp[-1].str), NULL, NULL));
                }
#line 1999 "y.tab.c"
    break;

  case 73: /* assignment_stat: ID CLOSEBRACKET expression OPENBRACKET ASSIGNMENT expression SEMICOLON  */
#line 238 "parser.y"
                                                                                         {
                    (yyval.node) = mkNode("array_assign", mkNode((yyvsp[-6].str), (yyvsp[-4].node), NULL), (yyvsp[-1].node));
                }
#line 2007 "y.tab.c"
    break;

  case 74: /* return_stat: RETURN expression SEMICOLON  */
#line 246 "parser.y"
                                            {(yyval.node) = mkNode("RETURN", (yyvsp[-1].node), NULL);}
#line 2013 "y.tab.c"
    break;

  case 75: /* expression_list: expression  */
#line 251 "parser.y"
               {(yyval.node) = (yyvsp[0].node);}
#line 2019 "y.tab.c"
    break;

  case 76: /* expression_list: expression COMMA expression_list  */
#line 252 "parser.y"
                                       {(yyval.node) = mkNode("expr_list", (yyvsp[-2].node), (yyvsp[0].node));}
#line 2025 "y.tab.c"
    break;

  case 77: /* expression: expression PLUS expression  */
#line 256 "parser.y"
                                           { (yyval.node) = mkNode("+", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2031 "y.tab.c"
    break;

  case 78: /* expression: expression MINUS expression  */
#line 257 "parser.y"
                                              { (yyval.node) = mkNode("-", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2037 "y.tab.c"
    break;

  case 79: /* expression: expression MULTI expression  */
#line 258 "parser.y"
                                              { (yyval.node) = mkNode("*", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2043 "y.tab.c"
    break;

  case 80: /* expression: expression DIV expression  */
#line 259 "parser.y"
                                            { (yyval.node) = mkNode("/", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2049 "y.tab.c"
    break;

  case 81: /* expression: expression AND expression  */
#line 260 "parser.y"
                                            { (yyval.node) = mkNode("and", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2055 "y.tab.c"
    break;

  case 82: /* expression: expression OR expression  */
#line 261 "parser.y"
                                           { (yyval.node) = mkNode("or", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2061 "y.tab.c"
    break;

  case 83: /* expression: expression EQL expression  */
#line 262 "parser.y"
                                            { (yyval.node) = mkNode("==", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2067 "y.tab.c"
    break;

  case 84: /* expression: expression NOT_EQL expression  */
#line 263 "parser.y"
                                                { (yyval.node) = mkNode("!=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2073 "y.tab.c"
    break;

  case 85: /* expression: expression GREATER expression  */
#line 264 "parser.y"
                                                { (yyval.node) = mkNode(">", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2079 "y.tab.c"
    break;

  case 86: /* expression: expression GREATER_EQL expression  */
#line 265 "parser.y"
                                                    { (yyval.node) = mkNode(">=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2085 "y.tab.c"
    break;

  case 87: /* expression: expression LESS expression  */
#line 266 "parser.y"
                                             { (yyval.node) = mkNode("<", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2091 "y.tab.c"
    break;

  case 88: /* expression: expression LESS_EQL expression  */
#line 267 "parser.y"
                                                 { (yyval.node) = mkNode("<=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2097 "y.tab.c"
    break;

  case 89: /* expression: NOT expression  */
#line 268 "parser.y"
                                 { (yyval.node) = mkNode("not", (yyvsp[0].node), NULL); }
#line 2103 "y.tab.c"
    break;

  case 90: /* expression: MINUS expression  */
#line 269 "parser.y"
                                             { (yyval.node) = mkNode("unary-", (yyvsp[0].node), NULL); }
#line 2109 "y.tab.c"
    break;

  case 91: /* expression: ADDRESS ID  */
#line 270 "parser.y"
                             { (yyval.node) = mkNode("address", mkNode((yyvsp[0].str), NULL, NULL), NULL); }
#line 2115 "y.tab.c"
    break;

  case 92: /* expression: ADDRESS ID OPENBRACKET expression CLOSEBRACKET  */
#line 271 "parser.y"
                                                                 { 
                    Node *array_elem = mkNode("array_element", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node));
                    (yyval.node) = mkNode("address", array_elem, NULL); 
                }
#line 2124 "y.tab.c"
    break;

  case 93: /* expression: MULTI ID  */
#line 275 "parser.y"
                                     { (yyval.node) = mkNode("dereference", mkNode((yyvsp[0].str), NULL, NULL), NULL);  }
#line 2130 "y.tab.c"
    break;

  case 94: /* expression: LENGTH ID LENGTH  */
#line 276 "parser.y"
                                   { (yyval.node) = mkNode("length", mkNode((yyvsp[-1].str), NULL, NULL), NULL); }
#line 2136 "y.tab.c"
    break;

  case 95: /* expression: OPENPAREN expression CLOSEPAREN  */
#line 277 "parser.y"
                                                  { (yyval.node) = (yyvsp[-1].node); }
#line 2142 "y.tab.c"
    break;

  case 96: /* expression: ID  */
#line 278 "parser.y"
                     { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 2148 "y.tab.c"
    break;

  case 97: /* expression: ID OPENBRACKET expression CLOSEBRACKET  */
#line 279 "parser.y"
                                                         { 
                    (yyval.node) = mkNode("array_element", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node)); 
                }
#line 2156 "y.tab.c"
    break;

  case 98: /* expression: CALL ID OPENPAREN parameter_list CLOSEPAREN  */
#line 282 "parser.y"
                                                              { 
                    (yyval.node) = mkNode("function_call", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node)); 
                }
#line 2164 "y.tab.c"
    break;

  case 99: /* expression: literal  */
#line 285 "parser.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 2170 "y.tab.c"
    break;


#line 2174 "y.tab.c"

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

#line 288 "parser.y"



Node *mkNode(char *token, Node *left, Node *right) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        yyerror("Out of memory");
        exit(1);
    }
    newNode->token = strdup(token);
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

void printTabs(int numOfTabs) {
    for (int i = 0; i < numOfTabs; i++) printf("\t");
}

void printtree(Node *tree, int tab) {
    if (tree == NULL) return;
    printTabs(tab);
    printf("(%s", tree->token);
    if (tree->left || tree->right) printf("\n");
    if (tree->left) printtree(tree->left, tab + 1);
    if (tree->right) printtree(tree->right, tab);
    if (tree->left || tree->right) printTabs(tab);
    printf(")\n");
}

int yyerror(char *s) {
    printf("syntax error: line %d - unexpected %s\n", yylineno, yytext);
    return 0;
}

int main() {
    return yyparse();
}
