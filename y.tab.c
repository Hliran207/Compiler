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
#include <ctype.h>

int yyerror(char *s);
int yylex();
int yyparse();
extern int yylineno;
extern char *yytext;

typedef enum
{
    TYPE_INT,
    TYPE_BOOL,
    TYPE_CHAR,
    TYPE_REAL,
    TYPE_STRING,
    TYPE_INT_PTR,
    TYPE_CHAR_PTR,
    TYPE_REAL_PTR,
    TYPE_VOID,
    TYPE_INVALID
} DataType;

typedef enum
{
    KIND_VARIABLE,
    KIND_PARAMETER,
    KIND_FUNCTION
} SymbolKind;

typedef struct Symbol Symbol;
typedef struct SymbolList SymbolList;
typedef struct Scope Scope;

struct Symbol
{
    char *name;            // Symbol name
    DataType type;         // Data type
    SymbolKind kind;       // Kind of symbol
    int scope_level;       // Scope level
    int is_array;          // Is it an array?
    int array_size;        // Array size
    int line_number;       // Line where defined
    int param_count;       // Number of parameters (for functions)
    DataType *param_types; // Parameter types (for functions)
    DataType return_type;  // Return type (for functions)
    int is_defined;        // Is function defined?
    struct Symbol *next;   // Next symbol in the same scope
};

struct SymbolList
{
    Symbol *symbol;
    struct SymbolList *next;
};

struct Scope
{
    Symbol *symbols;      // Linked list of symbols in this scope
    int scope_level;      // Scope nesting level
    struct Scope *parent; // Parent scope
};

typedef struct Node
{
    char *token;
    struct Node *left;
    struct Node *right;
} Node;

// Global var:
Node *ast_root=NULL;
Scope *current_scope = NULL;
int has_main = 0; // Flag for _main_ function
int current_scope_level = 0;

Node *mkNode(char *token, Node *left, Node *right);
void printtree(Node * tree, int tab);
void printTabs(int numOfTabs);
void enter_scope();
void exit_scope();
Symbol *find_symbol(char *name);
Symbol *find_symbol_in_scope(char *name, Scope *scope);
Symbol *find_function(char *name);
Symbol *add_symbol(char *name, DataType type, SymbolKind kind);
Symbol *add_function(char *name, DataType return_type, int param_count, DataType *param_types);
DataType get_expression_type(Node * expr);
DataType get_type_from_string(char *type_str);
const char *type_to_string(DataType type);
int is_numeric_type(DataType type);
int is_pointer_type(DataType type);
DataType get_base_type(DataType ptr_type);
DataType get_ptr_type(DataType base_type);
int count_parameters(Node * param_list);
void extract_param_types(Node * param_list, DataType * *types, int *param_count);
void extract_param_types_helper(Node *param_node, DataType *types, int *index);
void check_param_order(Node * param_list);
void check_main_exists();
void check_type_compatibility(DataType target_type, DataType source_type, char *context);
void semantic_error(const char *message, const char *token);
void print_symbol_table(); // For debugging
void free_tree(Node* tree);
void free_symbol_table(Scope* scope);

#line 179 "y.tab.c"

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
    ID = 314,                      /* ID  */
    MAIN_FUNC = 315                /* MAIN_FUNC  */
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
#define MAIN_FUNC 315

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 110 "parser.y"

char *str;
struct Node *node;

#line 357 "y.tab.c"

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
  YYSYMBOL_MAIN_FUNC = 60,                 /* MAIN_FUNC  */
  YYSYMBOL_YYACCEPT = 61,                  /* $accept  */
  YYSYMBOL_program = 62,                   /* program  */
  YYSYMBOL_function_list = 63,             /* function_list  */
  YYSYMBOL_main_function = 64,             /* main_function  */
  YYSYMBOL_function = 65,                  /* function  */
  YYSYMBOL_returns_spec = 66,              /* returns_spec  */
  YYSYMBOL_parameter_list = 67,            /* parameter_list  */
  YYSYMBOL_param_decl_list = 68,           /* param_decl_list  */
  YYSYMBOL_param_decl = 69,                /* param_decl  */
  YYSYMBOL_type = 70,                      /* type  */
  YYSYMBOL_opt_var = 71,                   /* opt_var  */
  YYSYMBOL_var_decl_list = 72,             /* var_decl_list  */
  YYSYMBOL_var_decl = 73,                  /* var_decl  */
  YYSYMBOL_var_item_list = 74,             /* var_item_list  */
  YYSYMBOL_var_item = 75,                  /* var_item  */
  YYSYMBOL_literal = 76,                   /* literal  */
  YYSYMBOL_stat_list = 77,                 /* stat_list  */
  YYSYMBOL_stat = 78,                      /* stat  */
  YYSYMBOL_call_stat = 79,                 /* call_stat  */
  YYSYMBOL_if_stat = 80,                   /* if_stat  */
  YYSYMBOL_while_stat = 81,                /* while_stat  */
  YYSYMBOL_do_while_stat = 82,             /* do_while_stat  */
  YYSYMBOL_for_stat = 83,                  /* for_stat  */
  YYSYMBOL_for_header = 84,                /* for_header  */
  YYSYMBOL_update_exp = 85,                /* update_exp  */
  YYSYMBOL_block_stat = 86,                /* block_stat  */
  YYSYMBOL_assignment_stat = 87,           /* assignment_stat  */
  YYSYMBOL_return_stat = 88,               /* return_stat  */
  YYSYMBOL_expression_list = 89,           /* expression_list  */
  YYSYMBOL_expression = 90                 /* expression  */
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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   520

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  238

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   315


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
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   134,   134,   141,   142,   143,   144,   146,   166,   184,
     198,   201,   204,   206,   207,   209,   211,   212,   213,   214,
     215,   216,   217,   218,   221,   224,   226,   227,   229,   231,
     232,   235,   242,   251,   260,   271,   272,   273,   274,   275,
     276,   277,   278,   281,   284,   285,   287,   288,   289,   290,
     291,   292,   293,   295,   297,   305,   313,   320,   327,   328,
     329,   330,   332,   334,   336,   337,   339,   345,   353,   357,
     366,   374,   381,   392,   399,   407,   415,   424,   426,   427,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   438,
     439,   440,   441,   442,   443,   450,   459,   466,   473,   474,
     481,   489,   497
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
  "HEX_LIT", "REAL_LIT", "ID", "MAIN_FUNC", "$accept", "program",
  "function_list", "main_function", "function", "returns_spec",
  "parameter_list", "param_decl_list", "param_decl", "type", "opt_var",
  "var_decl_list", "var_decl", "var_item_list", "var_item", "literal",
  "stat_list", "stat", "call_stat", "if_stat", "while_stat",
  "do_while_stat", "for_stat", "for_header", "update_exp", "block_stat",
  "assignment_stat", "return_stat", "expression_list", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-161)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      21,   -16,     9,    21,  -161,  -161,     2,     7,  -161,  -161,
    -161,    39,    39,   211,    33,    55,  -161,    48,  -161,  -161,
    -161,  -161,  -161,  -161,  -161,  -161,    58,    72,    39,    75,
      59,    11,  -161,   104,  -161,   111,   211,   104,   103,   106,
     211,   111,  -161,  -161,   107,    -8,    -8,    88,  -161,    -8,
     185,   185,    80,    90,    -8,    76,    77,    78,   -20,  -161,
     115,    -8,  -161,  -161,  -161,  -161,  -161,  -161,  -161,   116,
      82,   125,  -161,    89,   185,   185,    92,    93,    96,   185,
    -161,  -161,  -161,  -161,  -161,  -161,  -161,    99,  -161,   313,
     329,   108,   122,   146,   144,   126,   149,   208,   185,   185,
    -161,  -161,  -161,   -34,   -22,  -161,   185,   159,   140,  -161,
    -161,  -161,   139,   148,   281,   185,   185,   185,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   185,   146,   146,
     160,    -3,   177,  -161,   145,   185,   152,   137,   164,   361,
      54,    74,     6,   168,  -161,    82,   376,  -161,    39,   185,
    -161,  -161,   241,   174,   174,   143,  -161,  -161,  -161,  -161,
    -161,   480,  -161,   480,   143,    66,  -161,   185,   146,  -161,
     185,   186,   181,   299,   391,  -161,   183,   -38,  -161,   201,
     204,  -161,   195,  -161,  -161,   198,   261,  -161,   185,   207,
     406,  -161,   421,  -161,   209,   185,  -161,   105,  -161,    -2,
     185,   210,  -161,  -161,   345,   146,   185,  -161,  -161,  -161,
     212,   220,   214,   215,   216,   436,   217,   146,  -161,   451,
    -161,   239,  -161,  -161,  -161,  -161,  -161,   269,   194,  -161,
     240,   254,   237,   146,   185,  -161,  -161,   466
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     6,     4,     0,     0,     1,     5,
       3,    11,    11,     0,     0,    12,    13,     0,    17,    18,
      16,    19,    20,    21,    22,    23,     0,     0,     0,     0,
       0,    24,    14,    24,    15,     0,     0,    24,     0,     0,
       0,    25,    26,    10,     0,    43,    43,     0,    27,    43,
       0,     0,     0,     0,    43,     0,     0,     0,     0,    46,
       0,    43,    53,    48,    49,    51,    50,    52,    47,     0,
       0,     0,    42,     0,     0,     0,     0,     0,     0,     0,
      36,    37,    38,    39,    35,    40,    41,    99,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       9,    45,     7,    31,     0,    29,     0,     0,     0,    92,
      93,    96,    94,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    68,     0,     0,    42,     0,     0,     0,
       0,     0,     0,     0,    28,     0,     0,     8,    11,     0,
      97,    98,     0,    84,    85,    83,    86,    88,    89,    90,
      91,    81,    87,    80,    82,    58,    62,     0,     0,    64,
       0,     0,     0,    78,     0,    73,     0,    94,    69,     0,
       0,    32,     0,    30,    77,     0,     0,   100,     0,     0,
       0,    65,     0,    57,     0,     0,    71,     0,    72,     0,
       0,    33,   101,    95,     0,     0,     0,    63,    56,    79,
       0,     0,     0,     0,     0,     0,     0,     0,    59,     0,
      55,     0,    70,    75,    74,    76,    34,    60,     0,    54,
       0,     0,     0,     0,     0,    66,    61,    67
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -161,  -161,  -161,   284,    42,  -161,    84,  -161,   274,     0,
     -31,  -161,   248,  -161,   158,   162,   -27,  -161,  -161,  -161,
    -161,  -161,  -161,  -161,  -161,   -90,  -161,  -161,  -160,   -50
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,    59,    37,   185,    15,    16,    26,
      38,    41,    42,   104,   105,    88,    60,    61,    62,    63,
      64,    65,    66,    92,   232,    67,    68,   107,   172,   173
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      89,    90,    39,   132,    50,   198,    44,    51,    52,     8,
     142,    97,   149,    53,    35,    54,   143,    55,    56,    69,
      54,   144,    71,   145,   109,   110,    72,    94,    35,   114,
      98,    99,    57,    36,   101,   209,    43,   211,   165,   166,
      47,   169,     5,     6,     7,    10,     1,   139,   140,   141,
      11,    58,   212,   213,   214,    12,   146,    13,    80,    81,
      82,    83,    84,    85,    86,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   191,   188,
     189,   116,    27,   117,   118,   174,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    14,    17,    29,    28,   186,
     168,   116,    30,   117,   118,   179,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   218,    31,   190,    34,    33,
     192,    35,    40,    13,   180,    72,    45,   227,    91,    46,
      49,    73,    70,    74,    93,     6,    95,    96,   204,   100,
     102,   103,    75,   236,   106,    76,    77,    78,   108,   115,
     215,   111,   112,    79,   210,   113,   219,    80,    81,    82,
      83,    84,    85,    86,    87,    72,   131,   130,   133,    54,
     116,    73,   117,    74,   134,   119,   120,   121,   122,   123,
     135,   125,    75,   147,   237,    76,    77,    78,   148,   149,
     150,   167,   170,    79,   171,   175,   176,    80,    81,    82,
      83,    84,    85,    86,    87,    72,   119,   120,   121,   122,
     123,    73,   125,    74,    18,    19,    20,    21,    22,    23,
      24,    25,    75,   177,   182,    76,    77,    78,   136,   193,
     194,   197,   199,    79,   137,   200,    74,    80,    81,    82,
      83,    84,    85,    86,    87,    75,   201,   202,    76,   138,
      78,   205,   208,   231,   216,   220,    79,   222,   223,   224,
      80,    81,    82,    83,    84,    85,    86,    87,   116,   221,
     117,   118,   226,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   229,   230,   233,   234,   235,     9,   116,    48,
     117,   118,   187,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    32,   183,   181,     0,     0,     0,   116,     0,
     117,   118,   203,   119,   120,   121,   122,   123,   124,   125,
     126,   127,     0,     0,     0,     0,   116,     0,   117,   118,
     151,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     116,     0,   117,   118,   195,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,     0,   116,   128,   117,   118,
       0,   119,   120,   121,   122,   123,   124,   125,   126,   127,
       0,     0,   116,   129,   117,   118,     0,   119,   120,   121,
     122,   123,   124,   125,   126,   127,     0,     0,   116,   217,
     117,   118,     0,   119,   120,   121,   122,   123,   124,   125,
     126,   127,     0,   116,   178,   117,   118,     0,   119,   120,
     121,   122,   123,   124,   125,   126,   127,     0,   116,   184,
     117,   118,     0,   119,   120,   121,   122,   123,   124,   125,
     126,   127,     0,   116,   196,   117,   118,     0,   119,   120,
     121,   122,   123,   124,   125,   126,   127,     0,   116,   206,
     117,   118,     0,   119,   120,   121,   122,   123,   124,   125,
     126,   127,     0,   116,   207,   117,   118,     0,   119,   120,
     121,   122,   123,   124,   125,   126,   127,     0,   116,   225,
     117,   118,     0,   119,   120,   121,   122,   123,   124,   125,
     126,   127,     0,   116,   228,   117,   118,     0,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   116,     0,   117,
     118,     0,   119,   120,   121,   122,   123,     0,   125,     0,
     127
};

static const yytype_int16 yycheck[] =
{
      50,    51,    33,    93,    12,    43,    37,    15,    16,     0,
      44,    31,    50,    21,    17,    23,    50,    25,    26,    46,
      23,    43,    49,    45,    74,    75,    20,    54,    17,    79,
      50,    51,    40,    22,    61,   195,    36,   197,   128,   129,
      40,   131,     0,    59,    60,     3,    25,    97,    98,    99,
      48,    59,    54,    55,    56,    48,   106,    18,    52,    53,
      54,    55,    56,    57,    58,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   168,    13,
      14,    27,    49,    29,    30,   135,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    11,    12,    49,    43,   149,
     131,    27,    44,    29,    30,    51,    32,    33,    34,    35,
      36,    37,    38,    39,    40,   205,    44,   167,    59,    44,
     170,    17,    11,    18,    50,    20,    23,   217,    48,    23,
      23,    26,    44,    28,    44,    59,    59,    59,   188,    24,
      24,    59,    37,   233,    19,    40,    41,    42,    59,    50,
     200,    59,    59,    48,    49,    59,   206,    52,    53,    54,
      55,    56,    57,    58,    59,    20,    44,    59,    24,    23,
      27,    26,    29,    28,    48,    32,    33,    34,    35,    36,
      31,    38,    37,    24,   234,    40,    41,    42,    48,    50,
      42,    31,    15,    48,    49,    43,    59,    52,    53,    54,
      55,    56,    57,    58,    59,    20,    32,    33,    34,    35,
      36,    26,    38,    28,     3,     4,     5,     6,     7,     8,
       9,    10,    37,    59,    56,    40,    41,    42,    20,    43,
      49,    48,    31,    48,    26,    31,    28,    52,    53,    54,
      55,    56,    57,    58,    59,    37,    51,    49,    40,    41,
      42,    44,    43,    59,    44,    43,    48,    43,    43,    43,
      52,    53,    54,    55,    56,    57,    58,    59,    27,    49,
      29,    30,    55,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    43,    14,    44,    31,    49,     3,    27,    41,
      29,    30,    51,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    28,   145,   142,    -1,    -1,    -1,    27,    -1,
      29,    30,    51,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    27,    -1,    29,    30,
      49,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      27,    -1,    29,    30,    45,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    -1,    27,    44,    29,    30,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      -1,    -1,    27,    44,    29,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    -1,    -1,    27,    44,
      29,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    27,    43,    29,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    27,    43,
      29,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    27,    43,    29,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    27,    43,
      29,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    27,    43,    29,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    27,    43,
      29,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    27,    43,    29,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    27,    -1,    29,
      30,    -1,    32,    33,    34,    35,    36,    -1,    38,    -1,
      40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    25,    62,    63,    64,    65,    59,    60,     0,    64,
      65,    48,    48,    18,    67,    68,    69,    67,     3,     4,
       5,     6,     7,     8,     9,    10,    70,    49,    43,    49,
      44,    44,    69,    44,    59,    17,    22,    66,    71,    71,
      11,    72,    73,    70,    71,    23,    23,    70,    73,    23,
      12,    15,    16,    21,    23,    25,    26,    40,    59,    65,
      77,    78,    79,    80,    81,    82,    83,    86,    87,    77,
      44,    77,    20,    26,    28,    37,    40,    41,    42,    48,
      52,    53,    54,    55,    56,    57,    58,    59,    76,    90,
      90,    48,    84,    44,    77,    59,    59,    31,    50,    51,
      24,    77,    24,    59,    74,    75,    19,    88,    59,    90,
      90,    59,    59,    59,    90,    50,    27,    29,    30,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    44,    44,
      59,    44,    86,    24,    48,    31,    20,    26,    41,    90,
      90,    90,    44,    50,    43,    45,    90,    24,    48,    50,
      42,    49,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    86,    86,    31,    71,    86,
      15,    49,    89,    90,    90,    43,    59,    59,    43,    51,
      50,    76,    56,    75,    43,    67,    90,    51,    13,    14,
      90,    86,    90,    43,    49,    45,    43,    48,    43,    31,
      31,    51,    49,    51,    90,    44,    43,    43,    43,    89,
      49,    89,    54,    55,    56,    90,    44,    44,    86,    90,
      43,    49,    43,    43,    43,    43,    55,    86,    43,    43,
      14,    59,    85,    44,    31,    49,    86,    90
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    61,    62,    63,    63,    63,    63,    64,    65,    65,
      66,    67,    67,    68,    68,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    72,    72,    73,    74,
      74,    75,    75,    75,    75,    76,    76,    76,    76,    76,
      76,    76,    76,    77,    77,    77,    78,    78,    78,    78,
      78,    78,    78,    78,    79,    79,    79,    79,    80,    80,
      80,    80,    81,    82,    83,    83,    84,    85,    86,    87,
      87,    87,    87,    87,    87,    87,    87,    88,    89,    89,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,    10,    12,    10,
       2,     0,     1,     1,     3,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     2,     1,     2,     5,     1,
       3,     1,     3,     4,     6,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     8,     7,     6,     5,     4,     7,
       8,    11,     4,     6,     4,     5,     9,     3,     3,     4,
       7,     5,     5,     4,     7,     7,     7,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     5,     2,     3,     3,     1,
       4,     5,     1
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
#line 135 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
    ast_root=(yyval.node);
    printtree((yyval.node), 0);
}
#line 1642 "y.tab.c"
    break;

  case 3: /* function_list: function_list function  */
#line 141 "parser.y"
                                       { (yyval.node) = mkNode("Function_list", (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1648 "y.tab.c"
    break;

  case 4: /* function_list: function  */
#line 142 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1654 "y.tab.c"
    break;

  case 5: /* function_list: function_list main_function  */
#line 143 "parser.y"
                              { (yyval.node) = mkNode("Function_list", (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1660 "y.tab.c"
    break;

  case 6: /* function_list: main_function  */
#line 144 "parser.y"
                {(yyval.node)=(yyvsp[0].node);}
#line 1666 "y.tab.c"
    break;

  case 7: /* main_function: DEF MAIN_FUNC OPENPAREN parameter_list CLOSEPAREN COLON opt_var BEGIN_T stat_list END  */
#line 147 "parser.y"
{
    if(has_main)
    {
        semantic_error("Multiply definitions of '_main_' function are not allowed",(yyvsp[-8].str));
    }
    has_main=1;

    if(count_parameters((yyvsp[-6].node))!=0){
        semantic_error("_main_ procedure must not accept any parameters",(yyvsp[-8].str));
    }
    add_function("_main_",TYPE_VOID,0,NULL);

    /* create nodes for readability */
    Node *idnode = mkNode("_main_", NULL, NULL);
    Node *parametersnodes = mkNode("PARAMETERS", (yyvsp[-6].node), NULL);
    Node *bodynode = mkNode("BODY", (yyvsp[-3].node), (yyvsp[-1].node));
    (yyval.node) = mkNode("PROCEDURE", idnode, mkNode("PROC_PARTS", parametersnodes, bodynode));
}
#line 1689 "y.tab.c"
    break;

  case 8: /* function: DEF ID OPENPAREN parameter_list CLOSEPAREN COLON returns_spec opt_var BEGIN_T stat_list return_stat END  */
#line 167 "parser.y"
{
    if(find_symbol_in_scope((yyvsp[-10].str),current_scope)){
        semantic_error("Function with the same name already exists in the current scope",(yyvsp[-10].str));
    }

    DataType return_type=get_type_from_string((yyvsp[-5].node)->token);
    add_function((yyvsp[-10].str),return_type,count_parameters((yyvsp[-8].node)),NULL);

    /* create nodes for readability */
    Node *idnode = mkNode((yyvsp[-10].str), NULL, NULL);
    Node *parametersnodes = mkNode("PARAMETERS", (yyvsp[-8].node), NULL);
    Node *returnsnode = mkNode("RETURNS", (yyvsp[-5].node), NULL);
    Node *body_statements = mkNode("statements", (yyvsp[-2].node), (yyvsp[-1].node));
    Node *bodynode = mkNode("BODY", (yyvsp[-4].node), body_statements);
    Node *defbody = mkNode("DEF_BODY", returnsnode, bodynode);
    (yyval.node) = mkNode("FUNCTION", idnode, mkNode("FUNC_PARTS", parametersnodes, defbody));
}
#line 1711 "y.tab.c"
    break;

  case 9: /* function: DEF ID OPENPAREN parameter_list CLOSEPAREN COLON opt_var BEGIN_T stat_list END  */
#line 185 "parser.y"
{
    if(find_symbol_in_scope((yyvsp[-8].str),current_scope)){
        semantic_error("Procedure with the same name already exists in the current scope",(yyvsp[-8].str));
    }
    add_function((yyvsp[-8].str),TYPE_VOID,count_parameters((yyvsp[-6].node)),NULL);

    /* create nodes for readability */
    Node *idnode = mkNode((yyvsp[-8].str), NULL, NULL);
    Node *parametersnodes = mkNode("PARAMETERS", (yyvsp[-6].node), NULL);
    Node *bodynode = mkNode("BODY", (yyvsp[-3].node), (yyvsp[-1].node));
    (yyval.node) = mkNode("PROCEDURE", idnode, mkNode("PROC_PARTS", parametersnodes, bodynode));
}
#line 1728 "y.tab.c"
    break;

  case 10: /* returns_spec: RETURNS type  */
#line 198 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1734 "y.tab.c"
    break;

  case 11: /* parameter_list: %empty  */
#line 201 "parser.y"
{
    (yyval.node) = mkNode("PARAM_EMPTY", NULL, NULL);
}
#line 1742 "y.tab.c"
    break;

  case 12: /* parameter_list: param_decl_list  */
#line 204 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1748 "y.tab.c"
    break;

  case 13: /* param_decl_list: param_decl  */
#line 206 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 1754 "y.tab.c"
    break;

  case 14: /* param_decl_list: param_decl_list SEMICOLON param_decl  */
#line 207 "parser.y"
                                       { (yyval.node) = mkNode("PARAMS_LIST", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1760 "y.tab.c"
    break;

  case 15: /* param_decl: PAR type COLON ID  */
#line 209 "parser.y"
                               { (yyval.node) = mkNode("PARAM", (yyvsp[-2].node), mkNode((yyvsp[0].str), NULL, NULL)); }
#line 1766 "y.tab.c"
    break;

  case 16: /* type: INT  */
#line 211 "parser.y"
           { (yyval.node) = mkNode("INT", NULL, NULL); }
#line 1772 "y.tab.c"
    break;

  case 17: /* type: BOOL  */
#line 212 "parser.y"
       { (yyval.node) = mkNode("BOOL", NULL, NULL); }
#line 1778 "y.tab.c"
    break;

  case 18: /* type: CHAR  */
#line 213 "parser.y"
       { (yyval.node) = mkNode("CHAR", NULL, NULL); }
#line 1784 "y.tab.c"
    break;

  case 19: /* type: REAL  */
#line 214 "parser.y"
       { (yyval.node) = mkNode("REAL", NULL, NULL); }
#line 1790 "y.tab.c"
    break;

  case 20: /* type: STRING  */
#line 215 "parser.y"
         { (yyval.node) = mkNode("STRING", NULL, NULL); }
#line 1796 "y.tab.c"
    break;

  case 21: /* type: INTPTR  */
#line 216 "parser.y"
         { (yyval.node) = mkNode("INTPTR", NULL, NULL); }
#line 1802 "y.tab.c"
    break;

  case 22: /* type: CHARPTR  */
#line 217 "parser.y"
          { (yyval.node) = mkNode("CHARPTR", NULL, NULL); }
#line 1808 "y.tab.c"
    break;

  case 23: /* type: REALPTR  */
#line 218 "parser.y"
          { (yyval.node) = mkNode("REALPTR", NULL, NULL); }
#line 1814 "y.tab.c"
    break;

  case 24: /* opt_var: %empty  */
#line 221 "parser.y"
{
    (yyval.node) = mkNode("VAR_EMPTY", NULL, NULL);
}
#line 1822 "y.tab.c"
    break;

  case 25: /* opt_var: VAR var_decl_list  */
#line 224 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1828 "y.tab.c"
    break;

  case 26: /* var_decl_list: var_decl  */
#line 226 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1834 "y.tab.c"
    break;

  case 27: /* var_decl_list: var_decl_list var_decl  */
#line 227 "parser.y"
                         { (yyval.node) = mkNode("VAR_DECL", (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1840 "y.tab.c"
    break;

  case 28: /* var_decl: TYPE type COLON var_item_list SEMICOLON  */
#line 229 "parser.y"
                                                   { (yyval.node) = mkNode("VAR_DECL", (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1846 "y.tab.c"
    break;

  case 29: /* var_item_list: var_item  */
#line 231 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1852 "y.tab.c"
    break;

  case 30: /* var_item_list: var_item_list COMMA var_item  */
#line 232 "parser.y"
                               { (yyval.node) = mkNode("VAR_ITEM_LIST", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1858 "y.tab.c"
    break;

  case 31: /* var_item: ID  */
#line 235 "parser.y"
    { 
        if(find_symbol_in_scope((yyvsp[0].str),current_scope)){
            semantic_error("Variable already defined in the current scope",(yyvsp[0].str));
        }
        add_symbol((yyvsp[0].str),TYPE_INVALID,KIND_VARIABLE);
    
        (yyval.node) = mkNode("VAR", mkNode((yyvsp[0].str), NULL, NULL), NULL); }
#line 1870 "y.tab.c"
    break;

  case 32: /* var_item: ID COLON literal  */
#line 243 "parser.y"
{   
    if(find_symbol_in_scope((yyvsp[-2].str),current_scope)){
        semantic_error("Variable already defined in the current scope",(yyvsp[-2].str));
    }
    DataType lit_type=get_expression_type((yyvsp[0].node));
    add_symbol((yyvsp[-2].str),lit_type,KIND_VARIABLE);

    (yyval.node) = mkNode("VAR_ASSIGN", mkNode((yyvsp[-2].str), NULL, NULL), (yyvsp[0].node)); }
#line 1883 "y.tab.c"
    break;

  case 33: /* var_item: ID OPENBRACKET DEC_LIT CLOSEBRACKET  */
#line 252 "parser.y"
{
    if(find_symbol_in_scope((yyvsp[-3].str),current_scope)){
        semantic_error("Variable already defined in the current scope",(yyvsp[-3].str));
    }
    add_symbol((yyvsp[-3].str),TYPE_STRING,KIND_VARIABLE);

    (yyval.node) = mkNode("STRING_VAR", mkNode((yyvsp[-3].str), NULL, NULL), mkNode((yyvsp[-1].str), NULL, NULL));
}
#line 1896 "y.tab.c"
    break;

  case 34: /* var_item: ID OPENBRACKET DEC_LIT CLOSEBRACKET COLON STRING_LIT  */
#line 261 "parser.y"
{
    if(find_symbol_in_scope((yyvsp[-5].str),current_scope)){
        semantic_error("Variable already defined in the current scope",(yyvsp[-5].str));
    }
    add_symbol((yyvsp[-5].str),TYPE_STRING,KIND_VARIABLE);

    (yyval.node) = mkNode("STRING_VAL_ASSIGN", mkNode("STRING_VAR", mkNode((yyvsp[-5].str), NULL, NULL), mkNode((yyvsp[-3].str), NULL, NULL)),
                mkNode((yyvsp[0].str), NULL, NULL));
}
#line 1910 "y.tab.c"
    break;

  case 35: /* literal: DEC_LIT  */
#line 271 "parser.y"
                  { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 1916 "y.tab.c"
    break;

  case 36: /* literal: B_TRUE  */
#line 272 "parser.y"
         { (yyval.node) = mkNode("TRUE", NULL, NULL); }
#line 1922 "y.tab.c"
    break;

  case 37: /* literal: B_FALSE  */
#line 273 "parser.y"
          { (yyval.node) = mkNode("FALSE", NULL, NULL); }
#line 1928 "y.tab.c"
    break;

  case 38: /* literal: CHAR_LIT  */
#line 274 "parser.y"
           { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 1934 "y.tab.c"
    break;

  case 39: /* literal: STRING_LIT  */
#line 275 "parser.y"
             { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 1940 "y.tab.c"
    break;

  case 40: /* literal: HEX_LIT  */
#line 276 "parser.y"
          { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 1946 "y.tab.c"
    break;

  case 41: /* literal: REAL_LIT  */
#line 277 "parser.y"
           { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 1952 "y.tab.c"
    break;

  case 42: /* literal: NULLL  */
#line 278 "parser.y"
        { (yyval.node) = mkNode("null", NULL, NULL); }
#line 1958 "y.tab.c"
    break;

  case 43: /* stat_list: %empty  */
#line 281 "parser.y"
{
    (yyval.node) = mkNode("empty_state_list", NULL, NULL);
}
#line 1966 "y.tab.c"
    break;

  case 44: /* stat_list: stat  */
#line 284 "parser.y"
       { (yyval.node) = (yyvsp[0].node); }
#line 1972 "y.tab.c"
    break;

  case 45: /* stat_list: stat stat_list  */
#line 285 "parser.y"
                 { (yyval.node) = mkNode("statements", (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1978 "y.tab.c"
    break;

  case 46: /* stat: function  */
#line 287 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1984 "y.tab.c"
    break;

  case 47: /* stat: assignment_stat  */
#line 288 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1990 "y.tab.c"
    break;

  case 48: /* stat: if_stat  */
#line 289 "parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 1996 "y.tab.c"
    break;

  case 49: /* stat: while_stat  */
#line 290 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2002 "y.tab.c"
    break;

  case 50: /* stat: for_stat  */
#line 291 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2008 "y.tab.c"
    break;

  case 51: /* stat: do_while_stat  */
#line 292 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2014 "y.tab.c"
    break;

  case 52: /* stat: block_stat  */
#line 293 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2020 "y.tab.c"
    break;

  case 53: /* stat: call_stat  */
#line 295 "parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 2026 "y.tab.c"
    break;

  case 54: /* call_stat: ID ASSIGNMENT CALL ID OPENPAREN expression_list CLOSEPAREN SEMICOLON  */
#line 298 "parser.y"
{
    if(!(find_function((yyvsp[-4].str)))){
        semantic_error("Function called before it was defined or does not exist.",(yyvsp[-4].str));
    }
    
    (yyval.node) = mkNode("ASSIGNMENT", mkNode((yyvsp[-7].str), NULL, NULL), mkNode("CALL", mkNode((yyvsp[-4].str), NULL, NULL), (yyvsp[-2].node)));
}
#line 2038 "y.tab.c"
    break;

  case 55: /* call_stat: ID ASSIGNMENT CALL ID OPENPAREN CLOSEPAREN SEMICOLON  */
#line 306 "parser.y"
{
    if(!(find_function((yyvsp[-3].str)))){
        semantic_error("Function called before it was defined or does not exist.",(yyvsp[-3].str));
    }

    (yyval.node) = mkNode("ASSIGNMENT", mkNode((yyvsp[-6].str), NULL, NULL), mkNode("CALL", mkNode((yyvsp[-3].str), NULL, NULL), NULL));
}
#line 2050 "y.tab.c"
    break;

  case 56: /* call_stat: CALL ID OPENPAREN expression_list CLOSEPAREN SEMICOLON  */
#line 314 "parser.y"
{
    if(!(find_function((yyvsp[-4].str)))){
        semantic_error("Function called before it was defined or does not exist.",(yyvsp[-4].str));
    }
    (yyval.node) = mkNode("PROC_CALL", mkNode((yyvsp[-4].str), NULL, NULL), (yyvsp[-2].node));
}
#line 2061 "y.tab.c"
    break;

  case 57: /* call_stat: CALL ID OPENPAREN CLOSEPAREN SEMICOLON  */
#line 321 "parser.y"
{
    if(!(find_function((yyvsp[-3].str)))){
        semantic_error("Function called before it was defined or does not exist.",(yyvsp[-3].str));
    }
    (yyval.node) = mkNode("PROC_CALL", mkNode((yyvsp[-3].str), NULL, NULL), NULL);
}
#line 2072 "y.tab.c"
    break;

  case 58: /* if_stat: IF expression COLON block_stat  */
#line 327 "parser.y"
                                         { (yyval.node) = mkNode("if", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2078 "y.tab.c"
    break;

  case 59: /* if_stat: IF expression COLON block_stat ELSE COLON block_stat  */
#line 328 "parser.y"
                                                       { (yyval.node) = mkNode("if-else", (yyvsp[-5].node), mkNode("then", (yyvsp[-3].node), mkNode("else", (yyvsp[0].node), NULL))); }
#line 2084 "y.tab.c"
    break;

  case 60: /* if_stat: IF expression COLON block_stat ELIF expression COLON block_stat  */
#line 329 "parser.y"
                                                                  { (yyval.node) = mkNode("if-elif", (yyvsp[-6].node), mkNode("then", (yyvsp[-4].node), mkNode("elif-cond", (yyvsp[-2].node), (yyvsp[0].node)))); }
#line 2090 "y.tab.c"
    break;

  case 61: /* if_stat: IF expression COLON block_stat ELIF expression COLON block_stat ELSE COLON block_stat  */
#line 330 "parser.y"
                                                                                        { (yyval.node) = mkNode("if-elif-else", (yyvsp[-9].node), mkNode("then", (yyvsp[-7].node), mkNode("elif-cond", (yyvsp[-5].node), mkNode("elif-then", (yyvsp[-3].node), mkNode("else", (yyvsp[0].node), NULL))))); }
#line 2096 "y.tab.c"
    break;

  case 62: /* while_stat: WHILE expression COLON block_stat  */
#line 332 "parser.y"
                                               { (yyval.node) = mkNode("while", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2102 "y.tab.c"
    break;

  case 63: /* do_while_stat: DO COLON block_stat WHILE expression SEMICOLON  */
#line 334 "parser.y"
                                                               { (yyval.node) = mkNode("do-while", (yyvsp[-3].node), mkNode("cond", (yyvsp[-1].node), NULL)); }
#line 2108 "y.tab.c"
    break;

  case 64: /* for_stat: FOR for_header COLON block_stat  */
#line 336 "parser.y"
                                           { (yyval.node) = mkNode("for", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2114 "y.tab.c"
    break;

  case 65: /* for_stat: FOR for_header COLON opt_var block_stat  */
#line 337 "parser.y"
                                          { (yyval.node) = mkNode("for", (yyvsp[-3].node), mkNode("block", (yyvsp[0].node), (yyvsp[-1].node))); }
#line 2120 "y.tab.c"
    break;

  case 66: /* for_header: OPENPAREN ID ASSIGNMENT expression SEMICOLON expression SEMICOLON update_exp CLOSEPAREN  */
#line 340 "parser.y"
{
    (yyval.node) = mkNode("for-header", mkNode("init", mkNode((yyvsp[-7].str), NULL, NULL), (yyvsp[-5].node)),
                mkNode("loop", (yyvsp[-3].node), (yyvsp[-1].node)));
}
#line 2129 "y.tab.c"
    break;

  case 67: /* update_exp: ID ASSIGNMENT expression  */
#line 345 "parser.y"
                                      { (yyval.node) = mkNode("update", mkNode((yyvsp[-2].str), NULL, NULL), (yyvsp[0].node)); }
#line 2135 "y.tab.c"
    break;

  case 68: /* block_stat: BEGIN_T stat_list END  */
#line 353 "parser.y"
                                   { (yyval.node) = mkNode("block", (yyvsp[-1].node), NULL); }
#line 2141 "y.tab.c"
    break;

  case 69: /* assignment_stat: ID ASSIGNMENT expression SEMICOLON  */
#line 358 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[-3].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-3].str));
    }

     (yyval.node) = mkNode("assign", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node)); 
}
#line 2154 "y.tab.c"
    break;

  case 70: /* assignment_stat: ID OPENBRACKET expression CLOSEBRACKET ASSIGNMENT CHAR_LIT SEMICOLON  */
#line 367 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[-6].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-6].str));
    }
    (yyval.node) = mkNode("array_assign", mkNode((yyvsp[-6].str), (yyvsp[-4].node), NULL), mkNode((yyvsp[-1].str), NULL, NULL));
}
#line 2166 "y.tab.c"
    break;

  case 71: /* assignment_stat: MULTI ID ASSIGNMENT expression SEMICOLON  */
#line 375 "parser.y"
{ 
    Symbol *var=find_symbol((yyvsp[-3].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-3].str));
    }
    (yyval.node) = mkNode("pointer_assign", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node)); }
#line 2177 "y.tab.c"
    break;

  case 72: /* assignment_stat: ID ASSIGNMENT ADDRESS ID SEMICOLON  */
#line 382 "parser.y"
{
    Symbol *var1=find_symbol((yyvsp[-4].str));
    Symbol *var4=find_symbol((yyvsp[-1].str));
    if(!var1){
        semantic_error("Variable used before it been declared.",(yyvsp[-4].str));
    }
    if(!var4){
        semantic_error("Variable used before it been declared.",(yyvsp[-1].str));
    }
    (yyval.node) = mkNode("ref_assign", mkNode((yyvsp[-4].str), NULL, NULL), mkNode((yyvsp[-1].str), NULL, NULL)); }
#line 2192 "y.tab.c"
    break;

  case 73: /* assignment_stat: ID ASSIGNMENT NULLL SEMICOLON  */
#line 393 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[-2].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-2].str));
    }
    (yyval.node) = mkNode("null_assign", mkNode((yyvsp[-3].str), NULL, NULL), mkNode("null", NULL, NULL)); }
#line 2203 "y.tab.c"
    break;

  case 74: /* assignment_stat: ID OPENBRACKET expression CLOSEBRACKET ASSIGNMENT DEC_LIT SEMICOLON  */
#line 400 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[-5].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-5].str));
    }
    (yyval.node) = mkNode("array_assign", mkNode((yyvsp[-6].str), (yyvsp[-4].node), NULL), mkNode((yyvsp[-1].str), NULL, NULL));
}
#line 2215 "y.tab.c"
    break;

  case 75: /* assignment_stat: ID OPENBRACKET expression CLOSEBRACKET ASSIGNMENT STRING_LIT SEMICOLON  */
#line 408 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[-5].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-5].str));
    }
    (yyval.node) = mkNode("array_assign", mkNode((yyvsp[-6].str), (yyvsp[-4].node), NULL), mkNode((yyvsp[-1].str), NULL, NULL));
}
#line 2227 "y.tab.c"
    break;

  case 76: /* assignment_stat: ID CLOSEBRACKET expression OPENBRACKET ASSIGNMENT expression SEMICOLON  */
#line 416 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[-5].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-5].str));
    }
    (yyval.node) = mkNode("array_assign", mkNode((yyvsp[-6].str), (yyvsp[-4].node), NULL), (yyvsp[-1].node));
}
#line 2239 "y.tab.c"
    break;

  case 77: /* return_stat: RETURN expression SEMICOLON  */
#line 424 "parser.y"
                                          { (yyval.node) = mkNode("RETURN", (yyvsp[-1].node), NULL); }
#line 2245 "y.tab.c"
    break;

  case 78: /* expression_list: expression  */
#line 426 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 2251 "y.tab.c"
    break;

  case 79: /* expression_list: expression COMMA expression_list  */
#line 427 "parser.y"
                                   { (yyval.node) = mkNode("expr_list", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2257 "y.tab.c"
    break;

  case 80: /* expression: expression PLUS expression  */
#line 429 "parser.y"
                                        { (yyval.node) = mkNode("+", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2263 "y.tab.c"
    break;

  case 81: /* expression: expression MINUS expression  */
#line 430 "parser.y"
                              { (yyval.node) = mkNode("-", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2269 "y.tab.c"
    break;

  case 82: /* expression: expression MULTI expression  */
#line 431 "parser.y"
                              { (yyval.node) = mkNode("*", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2275 "y.tab.c"
    break;

  case 83: /* expression: expression DIV expression  */
#line 432 "parser.y"
                            { (yyval.node) = mkNode("/", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2281 "y.tab.c"
    break;

  case 84: /* expression: expression AND expression  */
#line 433 "parser.y"
                            { (yyval.node) = mkNode("and", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2287 "y.tab.c"
    break;

  case 85: /* expression: expression OR expression  */
#line 434 "parser.y"
                           { (yyval.node) = mkNode("or", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2293 "y.tab.c"
    break;

  case 86: /* expression: expression EQL expression  */
#line 435 "parser.y"
                            { (yyval.node) = mkNode("==", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2299 "y.tab.c"
    break;

  case 87: /* expression: expression NOT_EQL expression  */
#line 436 "parser.y"
                                { (yyval.node) = mkNode("!=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2305 "y.tab.c"
    break;

  case 88: /* expression: expression GREATER expression  */
#line 437 "parser.y"
                                { (yyval.node) = mkNode(">", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2311 "y.tab.c"
    break;

  case 89: /* expression: expression GREATER_EQL expression  */
#line 438 "parser.y"
                                    { (yyval.node) = mkNode(">=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2317 "y.tab.c"
    break;

  case 90: /* expression: expression LESS expression  */
#line 439 "parser.y"
                             { (yyval.node) = mkNode("<", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2323 "y.tab.c"
    break;

  case 91: /* expression: expression LESS_EQL expression  */
#line 440 "parser.y"
                                 { (yyval.node) = mkNode("<=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2329 "y.tab.c"
    break;

  case 92: /* expression: NOT expression  */
#line 441 "parser.y"
                 { (yyval.node) = mkNode("not", (yyvsp[0].node), NULL); }
#line 2335 "y.tab.c"
    break;

  case 93: /* expression: MINUS expression  */
#line 442 "parser.y"
                             { (yyval.node) = mkNode("unary-", (yyvsp[0].node), NULL); }
#line 2341 "y.tab.c"
    break;

  case 94: /* expression: ADDRESS ID  */
#line 444 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[0].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[0].str));
    }
    (yyval.node) = mkNode("address", mkNode((yyvsp[0].str), NULL, NULL), NULL); }
#line 2352 "y.tab.c"
    break;

  case 95: /* expression: ADDRESS ID OPENBRACKET expression CLOSEBRACKET  */
#line 451 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[-3].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-3].str));
    }
    Node *array_elem = mkNode("array_element", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node));
    (yyval.node) = mkNode("address", array_elem, NULL);
}
#line 2365 "y.tab.c"
    break;

  case 96: /* expression: MULTI ID  */
#line 460 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[0].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[0].str));
    }
    (yyval.node) = mkNode("dereference", mkNode((yyvsp[0].str), NULL, NULL), NULL); }
#line 2376 "y.tab.c"
    break;

  case 97: /* expression: LENGTH ID LENGTH  */
#line 467 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[-1].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-1].str));
    }
    (yyval.node) = mkNode("length", mkNode((yyvsp[-1].str), NULL, NULL), NULL); }
#line 2387 "y.tab.c"
    break;

  case 98: /* expression: OPENPAREN expression CLOSEPAREN  */
#line 473 "parser.y"
                                  { (yyval.node) = (yyvsp[-1].node); }
#line 2393 "y.tab.c"
    break;

  case 99: /* expression: ID  */
#line 475 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[0].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[0].str));
    }
    (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 2404 "y.tab.c"
    break;

  case 100: /* expression: ID OPENBRACKET expression CLOSEBRACKET  */
#line 482 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[-3].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-3].str));
    }
    (yyval.node) = mkNode("array_element", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node));
}
#line 2416 "y.tab.c"
    break;

  case 101: /* expression: CALL ID OPENPAREN parameter_list CLOSEPAREN  */
#line 490 "parser.y"
{
    Symbol *func=find_function((yyvsp[-3].str));
    if(!func){
        semantic_error("Function called before it was defined or does not exist.",(yyvsp[-3].str));
    }
    (yyval.node) = mkNode("function_call", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node));
}
#line 2428 "y.tab.c"
    break;

  case 102: /* expression: literal  */
#line 497 "parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 2434 "y.tab.c"
    break;


#line 2438 "y.tab.c"

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

#line 499 "parser.y"


Node *mkNode(char *token, Node *left, Node *right)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        yyerror("Out of memory");
        exit(1);
    }
    newNode->token = strdup(token);
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

void printTabs(int numOfTabs)
{
    for (int i = 0; i < numOfTabs; i++)
        printf("\t");
}

void printtree(Node *tree, int tab)
{
    if (tree == NULL)
        return;
    printTabs(tab);
    printf("(%s", tree->token);
    if (tree->left || tree->right)
        printf("\n");
    if (tree->left)
        printtree(tree->left, tab + 1);
    if (tree->right)
        printtree(tree->right, tab);
    if (tree->left || tree->right)
        printTabs(tab);
    printf(")\n");
}

int yyerror(char *s)
{
    printf("syntax error: line %d - unexpected %s\n", yylineno, yytext);
    return 0;
}

// Report semantic error
void semantic_error(const char *message, const char *token)
{
    if (token && strlen(token) > 0)
    {
        fprintf(stderr, "Semantic error (line %d): %s '%s'\n", yylineno, message, token);
    }
    else
    {
        fprintf(stderr, "Semantic error (line %d): %s\n", yylineno, message);
    }
    exit(1);
}

// Enter a new scope
void enter_scope()
{
    Scope *new_scope = (Scope *)malloc(sizeof(Scope));
    if (!new_scope)
    {
        fprintf(stderr, "Error: Memory allocation failed for scope\n");
        exit(1);
    }

    new_scope->symbols = NULL;
    new_scope->parent = current_scope;
    new_scope->scope_level = ++current_scope_level;
    current_scope = new_scope;
}

// Exit the current scope
void exit_scope()
{
    if (!current_scope)
    {
        fprintf(stderr, "Error: Cannot exit non-existent scope\n");
        return;
    }

    // We're not freeing symbols because we need to keep function information
    // available for later checks - in a production compiler, we would have a
    // more sophisticated mechanism for this.

    Scope *old_scope = current_scope;
    current_scope = current_scope->parent;
    current_scope_level--;

    // Free the scope structure (but not the symbols in it)
    free(old_scope);
}

// Find a symbol by name in any visible scope
Symbol *find_symbol(char *name)
{
    Scope *scope = current_scope;
    while (scope)
    {
        Symbol *sym = scope->symbols;
        while (sym)
        {
            if (strcmp(sym->name, name) == 0)
            {
                return sym;
            }
            sym = sym->next;
        }
        scope = scope->parent;
    }
    return NULL;
}

// Find a symbol by name in a specific scope
Symbol *find_symbol_in_scope(char *name, Scope *scope)
{
    if (!scope)
        return NULL;

    Symbol *sym = scope->symbols;
    while (sym)
    {
        if (strcmp(sym->name, name) == 0)
        {
            return sym;
        }
        sym = sym->next;
    }
    return NULL;
}

// Find a function by name, redundant, should we delete?

Symbol *find_function(char *name)
{
    Scope *scope = current_scope;
    while (scope)
    {
        Symbol *sym = scope->symbols;
        while (sym)
        {
            if (sym->kind == KIND_FUNCTION && strcmp(sym->name, name) == 0)
            {
                return sym;
            }
            sym = sym->next;
        }
        scope = scope->parent;
    }
    return NULL;
}

// Add a symbol to the symbol table
Symbol *add_symbol(char *name, DataType type, SymbolKind kind)
{
    // Check if symbol already exists in the current scope
    if (find_symbol_in_scope(name, current_scope))
    {
        return NULL; // Symbol already defined
    }

    // Create new symbol
    Symbol *sym = (Symbol *)malloc(sizeof(Symbol));
    if (!sym)
    {
        fprintf(stderr, "Error: Memory allocation failed for symbol\n");
        exit(1);
    }

    sym->name = strdup(name);
    sym->type = type;
    sym->kind = kind;
    sym->scope_level = current_scope_level;
    sym->is_array = 0;
    sym->array_size = 0;
    sym->line_number = yylineno;
    sym->param_count = 0;
    sym->param_types = NULL;
    sym->return_type = TYPE_VOID;
    sym->is_defined = 1;
    sym->next = NULL;

    // Add to current scope
    if (!current_scope->symbols)
    {
        current_scope->symbols = sym;
    }
    else
    {
        sym->next = current_scope->symbols;
        current_scope->symbols = sym;
    }

    return sym;
}

// Add a function to the symbol table
Symbol *add_function(char *name, DataType return_type, int param_count, DataType *param_types)
{
    // Check if function already exists in the current scope
    if (find_symbol_in_scope(name, current_scope))
    {
        return NULL; // Function already defined
    }

    // Create new symbol
    Symbol *sym = (Symbol *)malloc(sizeof(Symbol));
    if (!sym)
    {
        fprintf(stderr, "Error: Memory allocation failed for function symbol\n");
        exit(1);
    }

    sym->name = strdup(name);
    sym->type = TYPE_VOID; // Type is not used for functions
    sym->kind = KIND_FUNCTION;
    sym->scope_level = current_scope_level;
    sym->is_array = 0;
    sym->array_size = 0;
    sym->line_number = yylineno;
    sym->param_count = param_count;
    sym->return_type = return_type;
    sym->is_defined = 1;
    sym->next = NULL;

    // Copy parameter types
    if (param_count > 0 && param_types)
    {
        sym->param_types = (DataType *)malloc(param_count * sizeof(DataType));
        if (!sym->param_types)
        {
            fprintf(stderr, "Error: Memory allocation failed for parameter types\n");
            free(sym->name);
            free(sym);
            exit(1);
        }
        for (int i = 0; i < param_count; i++)
        {
            sym->param_types[i] = param_types[i];
        }
    }
    else
    {
        sym->param_types = NULL;
    }

    // Add to current scope
    if (!current_scope->symbols)
    {
        current_scope->symbols = sym;
    }
    else
    {
        sym->next = current_scope->symbols;
        current_scope->symbols = sym;
    }

    // Check for _main_ function
    if (strcmp(name, "_main_") == 0)
    {
        has_main = 1;
    }

    return sym;
}

// Determine the type of an expression
DataType get_expression_type(Node *expr)
{
    if (!expr)
        return TYPE_INVALID;

    // Literals
    if (strcmp(expr->token, "TRUE") == 0 || strcmp(expr->token, "FALSE") == 0)
    {
        return TYPE_BOOL;
    }

    if (expr->token[0] == '\'' && expr->token[strlen(expr->token) - 1] == '\'')
    {
        return TYPE_CHAR;
    }

    // String literal
    if (strcmp(expr->token, "STRING_LIT") == 0 ||
        (expr->token[0] == '"' && expr->token[strlen(expr->token) - 1] == '"'))
    {
        return TYPE_STRING;
    }

    // Integer literal
    if (isdigit(expr->token[0]) ||
        (expr->token[0] == '-' && isdigit(expr->token[1])))
    {
        if (strchr(expr->token, '.') != NULL)
        {
            return TYPE_REAL; // Real number
        }
        return TYPE_INT;
    }

    // Hexadecimal literal
    if (expr->token[0] == '0' && (expr->token[1] == 'x' || expr->token[1] == 'X'))
    {
        return TYPE_INT;
    }

    // Real literal
    if (strchr(expr->token, '.') != NULL)
    {
        return TYPE_REAL;
    }

    // Null
    if (strcmp(expr->token, "null") == 0)
    {
        return TYPE_INVALID; // Special case for null
    }

    // Binary arithmetic operators (+, -, *, /)
    if (strcmp(expr->token, "+") == 0 || strcmp(expr->token, "-") == 0 ||
        strcmp(expr->token, "*") == 0 || strcmp(expr->token, "/") == 0){

        DataType left_type = get_expression_type(expr->left);
        DataType right_type = get_expression_type(expr->right);

        // Check that both operands are numeric types (INT or REAL)
        if (!is_numeric_type(left_type) || !is_numeric_type(right_type))
        {
            char error_msg[100];
            sprintf(error_msg, "Operator '%s' requires numeric operands, got '%s' and '%s'",
                    expr->token, type_to_string(left_type), type_to_string(right_type));
            semantic_error(error_msg, "");
            return TYPE_INVALID; // Error case
        }

        // If either operand is real, result is real
        if (left_type == TYPE_REAL || right_type == TYPE_REAL)
        {
            return TYPE_REAL;
        }

        // Otherwise, result is integer
        return TYPE_INT;
    }

    // Logical operators (and, or)
    if (strcmp(expr->token, "and") == 0 || strcmp(expr->token, "or") == 0) {
        DataType left_type = get_expression_type(expr->left);
        DataType right_type = get_expression_type(expr->right);
        
        // Both operands must be boolean
        if (left_type != TYPE_BOOL || right_type != TYPE_BOOL) {
            char error_msg[100];
            sprintf(error_msg, "Operator '%s' requires boolean operands, got '%s' and '%s'", 
                    expr->token, type_to_string(left_type), type_to_string(right_type));
            semantic_error(error_msg, "");
        }
        
        return TYPE_BOOL;
    }
        // Comparison operators (==, !=, >, >=, <, <=)
    if (strcmp(expr->token, "==") == 0 || strcmp(expr->token, "!=") == 0 ||
        strcmp(expr->token, ">") == 0 || strcmp(expr->token, ">=") == 0 ||
        strcmp(expr->token, "<") == 0 || strcmp(expr->token, "<=") == 0) {
        
        DataType left_type = get_expression_type(expr->left);
        DataType right_type = get_expression_type(expr->right);
        
        // For equality operators (== and !=)
        if (strcmp(expr->token, "==") == 0 || strcmp(expr->token, "!=") == 0) {
            // Types must be compatible
            if (left_type != right_type && 
                !(is_pointer_type(left_type) && strcmp(expr->right->token, "null") == 0) &&
                !(is_pointer_type(right_type) && strcmp(expr->left->token, "null") == 0)) {
                
                char error_msg[100];
                sprintf(error_msg, "Operator '%s' requires compatible operands, got '%s' and '%s'", 
                        expr->token, type_to_string(left_type), type_to_string(right_type));
                semantic_error(error_msg, "");
            }
        }
        // For relational operators (>, <, >=, <=)
        else {
            // Both operands must be numeric
            if (!is_numeric_type(left_type) || !is_numeric_type(right_type)) {
                char error_msg[100];
                sprintf(error_msg, "Operator '%s' requires numeric operands, got '%s' and '%s'", 
                        expr->token, type_to_string(left_type), type_to_string(right_type));
                semantic_error(error_msg, "");
            }
        }
        
        return TYPE_BOOL;
    }

    // Logical not
    if (strcmp(expr->token, "not") == 0) {
        DataType operand_type = get_expression_type(expr->left);
        
        // Operand must be boolean
        if (operand_type != TYPE_BOOL) {
            char error_msg[100];
            sprintf(error_msg, "Operator 'not' requires a boolean operand, got '%s'", 
                    type_to_string(operand_type));
            semantic_error(error_msg, "");
        }
        
        return TYPE_BOOL;
    }

    // Unary minus
    if (strcmp(expr->token, "unary-") == 0) {
        DataType operand_type = get_expression_type(expr->left);
        
        // Operand must be numeric (INT or REAL)
        if (!is_numeric_type(operand_type)) {
            char error_msg[100];
            sprintf(error_msg, "Unary minus operator requires a numeric operand, got '%s'", 
                    type_to_string(operand_type));
            semantic_error(error_msg, "");
        }
        
        return operand_type; // Type doesn't change
    }

        // Address operator
    if (strcmp(expr->token, "address") == 0) {
        Node *var_node = expr->left;
        if (!var_node)
            return TYPE_INVALID;

        // If this is an array element
        if (strcmp(var_node->token, "array_element") == 0) {
            // Get the array variable and check its type
            Node *array_node = var_node->left;
            Node *index_node = var_node->right;
            
            if (!array_node || !index_node)
                return TYPE_INVALID;
            
            Symbol *array_sym = find_symbol(array_node->token);
            if (!array_sym) {
                semantic_error("Undefined array variable", array_node->token);
                return TYPE_INVALID;
            }
            
            // Verify the array is a string
            if (array_sym->type != TYPE_STRING) {
                char error_msg[100];
                sprintf(error_msg, "Array indexing can only be used with strings, got '%s'", 
                        type_to_string(array_sym->type));
                semantic_error(error_msg, array_node->token);
                return TYPE_INVALID;
            }
            
            // Verify the index is an integer
            DataType index_type = get_expression_type(index_node);
            if (index_type != TYPE_INT) {
                char error_msg[100];
                sprintf(error_msg, "Array index must be of type INT, got '%s'", 
                        type_to_string(index_type));
                semantic_error(error_msg, "");
                return TYPE_INVALID;
            }
            
            return TYPE_CHAR_PTR; // Address of string element is char*
        }

        // Regular variable
        Symbol *var_sym = find_symbol(var_node->token);
        if (!var_sym) {
            semantic_error("Undefined variable", var_node->token);
            return TYPE_INVALID;
        }

        // Check if the type is valid for address operator
        switch (var_sym->type) {
        case TYPE_INT:
            return TYPE_INT_PTR;
        case TYPE_CHAR:
            return TYPE_CHAR_PTR;
        case TYPE_REAL:
            return TYPE_REAL_PTR;
        case TYPE_STRING:
            return TYPE_CHAR_PTR; // Address of string is char*
        default:
            char error_msg[100];
            sprintf(error_msg, "Cannot take address of variable of type '%s'", 
                    type_to_string(var_sym->type));
            semantic_error(error_msg, var_node->token);
            return TYPE_INVALID;
        }
    }

    // Dereference operator
    if (strcmp(expr->token, "dereference") == 0) {
        Node *var_node = expr->left;
        if (!var_node)
            return TYPE_INVALID;

        Symbol *var_sym = find_symbol(var_node->token);
        if (!var_sym)
            return TYPE_INVALID;

        // Check that the variable is a pointer type
        if (!is_pointer_type(var_sym->type)) {
            char error_msg[100];
            sprintf(error_msg, "Cannot dereference non-pointer variable of type '%s'", 
                    type_to_string(var_sym->type));
            semantic_error(error_msg, var_node->token);
            return TYPE_INVALID;
        }

        // Return base type of pointer
        return get_base_type(var_sym->type);
    }

    // Length operator
    if (strcmp(expr->token, "length") == 0) {
        Node* operand_node = expr->left;
        if (!operand_node)
            return TYPE_INVALID;
            
        // Check if it's a variable
        Symbol* var_sym = find_symbol(operand_node->token);
        if (!var_sym) {
            // If it's not a variable name directly, check if it's an expression
            DataType operand_type = get_expression_type(operand_node);
            
            // Only strings can have length
            if (operand_type != TYPE_STRING) {
                char error_msg[100];
                sprintf(error_msg, "Length operator can only be applied to strings, got '%s'", 
                        type_to_string(operand_type));
                semantic_error(error_msg, "");
            }
        } else {
            // It's a variable - check its type
            if (var_sym->type != TYPE_STRING) {
                char error_msg[100];
                sprintf(error_msg, "Length operator can only be applied to strings, got '%s'", 
                        type_to_string(var_sym->type));
                semantic_error(error_msg, var_sym->name);
            }
        }
        
        return TYPE_INT;
    }

        // Array element
    if (strcmp(expr->token, "array_element") == 0) {
        // Get the array variable node and index expression node
        Node* array_node = expr->left;
        Node* index_node = expr->right;
        
        if (!array_node || !index_node) {
            semantic_error("Invalid array element access", "");
            return TYPE_INVALID;
        }
        
        // Check that the array variable exists
        Symbol* array_sym = find_symbol(array_node->token);
        if (!array_sym) {
            semantic_error("Undefined array variable", array_node->token);
            return TYPE_INVALID;
        }
        
        // Verify that the variable is a string (only strings can be indexed in this language)
        if (array_sym->type != TYPE_STRING) {
            char error_msg[100];
            sprintf(error_msg, "Array indexing can only be used with strings, got '%s'", 
                    type_to_string(array_sym->type));
            semantic_error(error_msg, array_node->token);
            return TYPE_INVALID;
        }
        
        // Verify that the index is an integer
        DataType index_type = get_expression_type(index_node);
        if (index_type != TYPE_INT) {
            char error_msg[100];
            sprintf(error_msg, "Array index must be of type INT, got '%s'", 
                    type_to_string(index_type));
            semantic_error(error_msg, "");
            return TYPE_INVALID;
        }
        
        // If all checks pass, return CHAR as the type of the array element
        // (In this language, strings are arrays of characters)
        return TYPE_CHAR;
    }


    // Function call
    if (strcmp(expr->token, "function_call") == 0)
    {
        Node *func_node = expr->left;
        if (!func_node)
            return TYPE_INVALID;

        Symbol *func_sym = find_symbol(func_node->token);
        if (!func_sym || func_sym->kind != KIND_FUNCTION)
            return TYPE_INVALID;

        return func_sym->return_type;
    }

    // Variable
    Symbol *var_sym = find_symbol(expr->token);
    if (var_sym)
    {
        return var_sym->type;
    }

    return TYPE_INVALID;
}

// Convert string to DataType
DataType get_type_from_string(char *type_str) {
    if (strcmp(type_str, "INT") == 0) return TYPE_INT;
    if (strcmp(type_str, "BOOL") == 0) return TYPE_BOOL;
    if (strcmp(type_str, "CHAR") == 0) return TYPE_CHAR;
    if (strcmp(type_str, "REAL") == 0) return TYPE_REAL;
    if (strcmp(type_str, "STRING") == 0) return TYPE_STRING;
    if (strcmp(type_str, "INTPTR") == 0) return TYPE_INT_PTR;
    if (strcmp(type_str, "CHARPTR") == 0) return TYPE_CHAR_PTR;
    if (strcmp(type_str, "REALPTR") == 0) return TYPE_REAL_PTR;
    return TYPE_INVALID;
}

// Convert DataType to string
const char* type_to_string(DataType type) {
    switch (type) {
        case TYPE_INT: return "INT";
        case TYPE_BOOL: return "BOOL";
        case TYPE_CHAR: return "CHAR";
        case TYPE_REAL: return "REAL";
        case TYPE_STRING: return "STRING";
        case TYPE_INT_PTR: return "INTPTR";
        case TYPE_CHAR_PTR: return "CHARPTR";
        case TYPE_REAL_PTR: return "REALPTR";
        case TYPE_VOID: return "VOID";
        case TYPE_INVALID: return "INVALID";
        default: return "UNKNOWN";
    }
}

int is_numeric_type(DataType type) {
    return type == TYPE_INT || type == TYPE_REAL;
}

// Check if type is a pointer
int is_pointer_type(DataType type) {
    return type == TYPE_INT_PTR || type == TYPE_CHAR_PTR || type == TYPE_REAL_PTR;
}

// Get base type from pointer type
DataType get_base_type(DataType ptr_type) {
    switch (ptr_type) {
        case TYPE_INT_PTR: return TYPE_INT;
        case TYPE_CHAR_PTR: return TYPE_CHAR;
        case TYPE_REAL_PTR: return TYPE_REAL;
        default: return TYPE_INVALID;
    }
}

// Get pointer type from base type
DataType get_ptr_type(DataType base_type) {
    switch (base_type) {
        case TYPE_INT: return TYPE_INT_PTR;
        case TYPE_CHAR: return TYPE_CHAR_PTR;
        case TYPE_REAL: return TYPE_REAL_PTR;
        case TYPE_STRING: return TYPE_CHAR_PTR; // Special case: address of string is char*
        default: return TYPE_INVALID;
    }
}

// Count parameters in parameter list
int count_parameters(Node *param_list) {
    if (!param_list) return 0;
    if (strcmp(param_list->token, "PARAM_EMPTY") == 0) return 0;
    
    int count = 0;
    if (strcmp(param_list->token, "PARAMS_LIST") == 0) {
        // Process left side
        count += count_parameters(param_list->left);
        // Process right side
        count += count_parameters(param_list->right);
    } else if (strcmp(param_list->token, "PARAM") == 0) {
        count = 1;
    }
    
    return count;
}

// Extract parameter types from parameter list
void extract_param_types(Node *param_list, DataType **types, int *param_count) {
    // First count parameters
    int count = count_parameters(param_list);
    *param_count = count;
    
    // Allocate array for types
    if (count > 0) {
        *types = (DataType *)malloc(count * sizeof(DataType));
        if (!*types) {
            fprintf(stderr, "Error: Memory allocation failed for parameter types\n");
            exit(1);
        }
        
        // Extract types
        int index = 0;
        extract_param_types_helper(param_list, *types, &index);
    } else {
        *types = NULL;
    }
}

// Helper function for extracting parameter types
void extract_param_types_helper(Node *param_node, DataType *types, int *index) {
    if (!param_node) return;
    
    if (strcmp(param_node->token, "PARAMS_LIST") == 0) {
        extract_param_types_helper(param_node->left, types, index);
        extract_param_types_helper(param_node->right, types, index);
    } else if (strcmp(param_node->token, "PARAM") == 0) {
        types[(*index)++] = get_type_from_string(param_node->left->token);
    }
}

// Check parameter ordering
void check_param_order(Node *param_list) {
    // This is a simplified version that just checks that parameters have the format "parX"
    // A more robust implementation would check that they are sequential (par1, par2, etc.)
    
    if (!param_list) return;
    
    if (strcmp(param_list->token, "PARAMS_LIST") == 0) {
        check_param_order(param_list->left);
        check_param_order(param_list->right);
    } else if (strcmp(param_list->token, "PARAM") == 0) {
        // Get parameter token from PAR token (should start with "par")
        char *param_token = param_list->right->token;
        // Could add checks here
    }
}

void check_main_exists() {
    if (!has_main) {
        fprintf(stderr, "Semantic error: Missing '_main_' function\n");
        exit(1);
    }
}

// Check type compatibility
void check_type_compatibility(DataType target_type, DataType source_type, char *context) {
    // Same types are always compatible
    if (target_type == source_type) return;
    
    // Null can be assigned to any pointer type
    if (source_type == TYPE_INVALID && is_pointer_type(target_type)) return;
    
    // INT can be assigned to REAL
    if (target_type == TYPE_REAL && source_type == TYPE_INT) return;
    
    // Types are not compatible
    fprintf(stderr, "Semantic error (line %d): Type mismatch in %s - cannot convert from '%s' to '%s'\n",
            yylineno, context, type_to_string(source_type), type_to_string(target_type));
    exit(1);
}

void print_symbol_table() {
    printf("\n=== Symbol Table ===\n");
    printf("%-20s %-10s %-10s %-8s %-8s\n", "Name", "Type", "Kind", "Scope", "Line");
    printf("------------------------------------------------\n");
    
    Scope *scope = current_scope;
    while (scope) {
        Symbol *sym = scope->symbols;
        while (sym) {
            char *kind_str;
            switch (sym->kind) {
                case KIND_VARIABLE: kind_str = "Variable"; break;
                case KIND_PARAMETER: kind_str = "Parameter"; break;
                case KIND_FUNCTION: kind_str = "Function"; break;
                default: kind_str = "Unknown";
            }
            
            printf("%-20s %-10s %-10s %-8d %-8d\n", 
                   sym->name, 
                   type_to_string(sym->type),
                   kind_str,
                   sym->scope_level,
                   sym->line_number);
            
            sym = sym->next;
        }
        scope = scope->parent;
    }
    printf("------------------------------------------------\n");
}

void free_tree(Node* tree){
    if(!tree) return;
    free_tree(tree->left);
    free_tree(tree->right);
    if(tree->token) free(tree->token);
    free(tree);
}

void free_symbol_table(Scope* scope){
    while(scope){
        Symbol *sym=scope->symbols;
        while(sym){
            Symbol *next_sym=sym->next;
            if(sym->name) free(sym->name);
            if(sym->param_types) free(sym->param_types);
            free(sym);
            sym=next_sym;
        }
        Scope *parent=scope->parent;
        free(scope);
        scope=parent;
    }
}

// Main function
int main() {
    // Initialize symbol table
    current_scope = NULL;
    current_scope_level = 0;
    has_main = 0;
    
    // Create global scope
    enter_scope();
    
    // Parse the input
    if (yyparse() == 0) {
        check_main_exists();
        printf("Parsing and semantic analysis completed successfully.\n");
    } else{
        printf("Parsing failed due to syntax or semantic erros.\n");
    }
    
    // Free memory (simplified version)
    if(ast_root) free_tree(ast_root);
    free_symbol_table(current_scope);
    
    return 0;
}
