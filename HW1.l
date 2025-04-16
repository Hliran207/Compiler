%{
    #include <stdio.h>
    #include "y.tab.h"
    int yyerror(char *s)
%}


%%

/*KEYWORDS & TYPES*/

"bool"          {return BOOL;}
"char"          {return CHAR;}
"int"           {return INT;} 
"real"          {return REAL;}
"string"        {return STRING;}
"int\\*"        {return INTPTR;}
"char\\*"       {return CHARPTR;}
"real\\*"       {return REALPTR;}
"type"          {return TYPE;}

/* STATEMENTS & LOOP */

"if"        {return IF;}
"elif"      {return ELIF;}
"else"      {return ELSE;}
"while"     {return WHILE;}
"for"       {return FOR;}
"var"       {return VAR;}
"par"[1-9][0-9]* {return PAR;} 
"return"    {return RETURN;}
"null"      {return NULLL;}
"do"        {return DO;}
"returns"   {return RETURNS;}
"begin"     {return BEGIN;}
"end"       {return END;}
"def"       {return DEF;}
"call"      {return CALL;}
"and"       {return AND;}
"not"       {return NOT;}
"or"        {return OR;}

/*OPERATORS*/

"/"     {return DIV;}
"="     {return ASSINGMENT;}
"=="    {return EQL;}    
">"     {return GREATER;}
">="    {return GREATER_EQL;}
"<"     {return LESS;}
"<="    {return LESS_EQL;}
"-"     {return MINUS;}
"!="    {return NOT_EQL;}
"+"     {return PLUS;}
"*"     {return MULTI;}
"&"     {return ADDRESS;}


/* OTHER LEXEMES */

"|"     {return LENGTH;}
";"     {return SEMICOLON;}
":"     {return COLON;}
","     {return COMMA;}
"{"     {return OPENBRACE;}
"}"     {return CLOSEBRACE;}
"("     {return OPENPAREN;}
")"     {return CLOSEPAREN;}
"["     {return OPENBRACKET;}
"]"     {return CLOSEBRACKET;}


#->([^<]|<(?!-#))*<-#   {/* Skip comment entirely; no token is returned to the parser */}
true                                                {return B_TRUE;}
false                                               {return B_FALSE;}
\'[ -~]\'                                           {yylval.str = yytext[1]; return CHAR_LIT; }
[-+]?[1-9][0-9]*|[0-9]                              {yylval.str = strdup(yytext); return DEC_LIT;}
0[xX][0-9A-F]+                                      {yylval.str = strdup(yytext); return HEX_LIT;}
[-+]?([0-9]+(\.[0-9]*)?|\.[0-9]+)([eE][-+]?[0-9]+)? {yylval.str = strdup(yytext); return REAL_LIT;}
\"[^\\"\n]*\"                                       {yylval.str = strdup(yytext); return STRING_LIT;}
[a-zA-Z][a-zA-Z0-9_]*                               {yylval.str = strdup(yytext); return ID;}
%%



 


 
 
 
 