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
#line 164 "parser.y"

char *str;
struct Node *node;

#line 192 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
