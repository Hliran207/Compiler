%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
int yyerror(char *s);
%}

%option yylineno

%%


"bool"          {return BOOL; }
"char"          {return CHAR; }
"int"           {return INT; } 
"real"          {return REAL; }
"string"        {return STRING; }
"int*"          {return INTPTR; }
"char*"         {return CHARPTR; }
"real*"         {return REALPTR; }
"type"          {return TYPE; }


"if"            {return IF; }
"elif"          {return ELIF; }
"else"          {return ELSE; }
"while"         {return WHILE; }
"for"           {return FOR; }
"var"           {return VAR; }
"par"[1-9][0-9]* {return PAR; } 
"return"        {return RETURN; }
"null"          {return NULLL; }
"do"            {return DO; }
"returns"       {return RETURNS; }
"begin"         {return BEGIN_T; }
"end"           {return END; }
"def"           {return DEF; }
"call"          {return CALL; }
"and"           {return AND; }
"not"           {return NOT; }
"or"            {return OR; }


"/"             {return DIV; }
"="             {return ASSIGNMENT; }
"=="            {return EQL; }    
">"             {return GREATER; }
">="            {return GREATER_EQL; }
"<"             {return LESS; }
"<="            {return LESS_EQL; }
"-"             {return MINUS; }
"!="            {return NOT_EQL; }
"+"             {return PLUS; }
"*"             {return MULTI; }
"&"             {return ADDRESS; }



"|"             {return LENGTH; }
";"             {return SEMICOLON; }
":"             {return COLON; }
","             {return COMMA; }
"{"             {return OPENBRACE; }
"}"             {return CLOSEBRACE; }
"("             {return OPENPAREN; }
")"             {return CLOSEPAREN; }
"["             {return OPENBRACKET; }
"]"             {return CLOSEBRACKET; }



"TRUE"          { yylval.str = strdup(yytext); return B_TRUE; }
"FALSE"         { yylval.str = strdup(yytext); return B_FALSE; }
\'[ -~]\'       { yylval.str = strdup(yytext); return CHAR_LIT; }
\"[^"\n]*\"     { yylval.str = strdup(yytext); return STRING_LIT; }
[0-9]+          { yylval.str = strdup(yytext); return DEC_LIT; }
0[xX][0-9A-F]+  { yylval.str = strdup(yytext); return HEX_LIT; }
[-+]?([0-9]+\.[0-9]*|\.[0-9]+)([eE][-+]?[0-9]+)? { yylval.str = strdup(yytext); return REAL_LIT; }


"_main_"              {yylval.str=strdup(yytext);    return MAIN_FUNC;}
[a-zA-Z][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return ID; }



"#->"[^<]*"<-#"    { /* Skip comments */ }
[ \t\n\r]+         { /* Skip whitespace */ }
.                  { printf("Unexpected character: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}