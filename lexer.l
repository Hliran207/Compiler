%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
int yyerror(char *s);
%}

%option yylineno

%%


"bool"          { yylval.str = strdup(yytext); return BOOL; }
"char"          { yylval.str = strdup(yytext); return CHAR; }
"int"           { yylval.str = strdup(yytext); return INT; } 
"real"          { yylval.str = strdup(yytext); return REAL; }
"string"        { yylval.str = strdup(yytext); return STRING; }
"int*"          { yylval.str = strdup(yytext); return INTPTR; }
"char*"         { yylval.str = strdup(yytext); return CHARPTR; }
"real*"         { yylval.str = strdup(yytext); return REALPTR; }
"type"          { yylval.str = strdup(yytext); return TYPE; }


"if"            { yylval.str = strdup(yytext); return IF; }
"elif"          { yylval.str = strdup(yytext); return ELIF; }
"else"          { yylval.str = strdup(yytext); return ELSE; }
"while"         { yylval.str = strdup(yytext); return WHILE; }
"for"           { yylval.str = strdup(yytext); return FOR; }
"var"           { yylval.str = strdup(yytext); return VAR; }
"par"[1-9][0-9]* { yylval.str = strdup(yytext); return PAR; } 
"return"        { yylval.str = strdup(yytext); return RETURN; }
"null"          { yylval.str = strdup(yytext); return NULLL; }
"do"            { yylval.str = strdup(yytext); return DO; }
"returns"       { yylval.str = strdup(yytext); return RETURNS; }
"begin"         { yylval.str = strdup(yytext); return BEGIN_T; }
"end"           { yylval.str = strdup(yytext); return END; }
"def"           { yylval.str = strdup(yytext); return DEF; }
"call"          { yylval.str = strdup(yytext); return CALL; }
"and"           { yylval.str = strdup(yytext); return AND; }
"not"           { yylval.str = strdup(yytext); return NOT; }
"or"            { yylval.str = strdup(yytext); return OR; }


"/"             { yylval.str = strdup(yytext); return DIV; }
"="             { yylval.str = strdup(yytext); return ASSINGMENT; }
"=="            { yylval.str = strdup(yytext); return EQL; }    
">"             { yylval.str = strdup(yytext); return GREATER; }
">="            { yylval.str = strdup(yytext); return GREATER_EQL; }
"<"             { yylval.str = strdup(yytext); return LESS; }
"<="            { yylval.str = strdup(yytext); return LESS_EQL; }
"-"             { yylval.str = strdup(yytext); return MINUS; }
"!="            { yylval.str = strdup(yytext); return NOT_EQL; }
"+"             { yylval.str = strdup(yytext); return PLUS; }
"*"             { yylval.str = strdup(yytext); return MULTI; }
"&"             { yylval.str = strdup(yytext); return ADDRESS; }



"|"             { yylval.str = strdup(yytext); return LENGTH; }
";"             { yylval.str = strdup(yytext); return SEMICOLON; }
":"             { yylval.str = strdup(yytext); return COLON; }
","             { yylval.str = strdup(yytext); return COMMA; }
"{"             { yylval.str = strdup(yytext); return OPENBRACE; }
"}"             { yylval.str = strdup(yytext); return CLOSEBRACE; }
"("             { yylval.str = strdup(yytext); return OPENPAREN; }
")"             { yylval.str = strdup(yytext); return CLOSEPAREN; }
"["             { yylval.str = strdup(yytext); return OPENBRACKET; }
"]"             { yylval.str = strdup(yytext); return CLOSEBRACKET; }



"TRUE"          { yylval.str = strdup(yytext); return B_TRUE; }
"FALSE"         { yylval.str = strdup(yytext); return B_FALSE; }
\'[ -~]\'       { yylval.str = strdup(yytext); return CHAR_LIT; }
\"[^"\n]*\"     { yylval.str = strdup(yytext); return STRING_LIT; }
[0-9]+          { yylval.str = strdup(yytext); return DEC_LIT; }
0[xX][0-9A-F]+  { yylval.str = strdup(yytext); return HEX_LIT; }
[-+]?([0-9]+\.[0-9]*|\.[0-9]+)([eE][-+]?[0-9]+)? { yylval.str = strdup(yytext); return REAL_LIT; }



[a-zA-Z][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return ID; }



"#->"[^<]*"<-#"    { /* Skip comments */ }
[ \t\n\r]+         { /* Skip whitespace */ }
.                  { printf("Unexpected character: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}