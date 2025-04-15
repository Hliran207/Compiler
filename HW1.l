
%%

/*KEYWORDS & TYPES*/

"bool"      {return BOOL;}
"char"      {return CHAR;}
"int"       {return INT;}
"real"      {return REAL;}
"string"    {return STRING;}
"int*"      {return INTPTR;}
"char*"     {return CHARPTR;}
"real*"     {return REALPTR;}
"type"      {return TYPE;}

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
"&"     {return ADRESS;}


/* OTHER LEXEMES */

"|"     {return LENGTH;}
"begin" {return BEGIN;}
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
true                    {return TRUE;}
false                   {return FALSE;}
\'[ -~]\'               { yylval.charVal = yytext[1]; return CHAR_LIT; }
0                       { yylval.intVal = 0; return INT_LIT;}
[-+]?[1-9][0-9]*             {yylval.intVal = strtol(yytext,NULL, 10); return INT_LIT;}
0[xX][0-9A-Fa-f]+       {yylval.intVal = strtol(yytext, NULL, 16); return INT_LIT;}
[-+]?([0-9]+(\.[0-9]*)?|\.[0-9]+)([eE][-+]?[0-9]+)? {yylval.realVal = atof(yytext); return REAL_LIT;}
\"[^\\"\n]*\"           {yylval.strVal = strdup(yytext); return STRING_LIT;}
[a-zA-Z][a-zA-Z0-9_]*  {yylval.string = strdup(yytext); return ID;}
%%



 


 
 
 
 