%{
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
%}

%union {
    char *str;
    struct Node *node;
}

%token <str> BOOL CHAR INT REAL STRING INTPTR CHARPTR REALPTR TYPE
%token <str> IF ELIF ELSE WHILE FOR VAR PAR RETURN NULLL DO RETURNS BEGIN_T END DEF CALL AND NOT OR
%token <str> DIV ASSIGNMENT EQL GREATER GREATER_EQL LESS LESS_EQL MINUS NOT_EQL PLUS MULTI ADDRESS
%token <str> LENGTH SEMICOLON COLON COMMA OPENBRACE CLOSEBRACE OPENPAREN CLOSEPAREN OPENBRACKET CLOSEBRACKET
%token <str> B_TRUE B_FALSE CHAR_LIT STRING_LIT DEC_LIT HEX_LIT REAL_LIT ID

%type <node> program function_list function returns_spec parameter_list param_decl_list
%type <node> param_decl type opt_var var_decl_list var_decl var_item_list var_item
%type <node> literal stat_list stat call_stat if_stat while_stat do_while_stat block_stat
%type <node> for_stat assignment_stat return_stat expression condition expression_list for_header update_exp

%left PLUS MINUS
%left MULTI DIV
%left OR AND
%left EQL NOT_EQL GREATER GREATER_EQL LESS LESS_EQL
%right NOT
%right ADDRESS

%%
program : 
            function_list {$$ = $1; printtree($$,0);}
        ;

function_list :
            function_list function {$$ = mkNode("Function_list", $1,$2);}
            | function {$$=$1;}
            ;

function : 
            DEF ID OPENPAREN parameter_list CLOSEPAREN COLON returns_spec opt_var BEGIN_T stat_list return_stat END{ 
            /* create nodes for readability */
            Node *idnode=mkNode($2,NULL,NULL);
            Node *parametersnodes=mkNode("PARAMETERS",$4,NULL);
            Node *returnsnode=mkNode("RETURNS",$7,NULL);
            Node *body_statements = mkNode("statements", $10, $11);
            Node *bodynode=mkNode("BODY",$8,body_statements);
            Node *defbody=mkNode("DEF_BODY",returnsnode,bodynode);
            $$=mkNode("FUNCTION",idnode,mkNode("FUNC_PARTS", parametersnodes,defbody));
            } 
            | DEF ID OPENPAREN parameter_list CLOSEPAREN COLON opt_var BEGIN_T stat_list END{ 
              /* create nodes for readability */
              Node *idnode=mkNode($2,NULL,NULL);
              Node *parametersnodes=mkNode("PARAMETERS",$4,NULL);
              Node *bodynode=mkNode("BODY",$7,$9);
              $$=mkNode("PROCEDURE",idnode,mkNode("PROC_PARTS", parametersnodes,bodynode));
            }
            ;

returns_spec : 
            RETURNS type {$$=$2;};

parameter_list : 
            {$$=mkNode("PARAM_EMPTY",NULL,NULL);}
            | param_decl_list {$$=$1;}
            ;

param_decl_list : 
            param_decl {$$=$1;}
            | param_decl_list SEMICOLON param_decl {$$=mkNode("PARAMS_LIST",$1,$3);}
            ;

param_decl : 
            PAR type COLON ID {$$=mkNode("PARAM",$2,mkNode($4,NULL,NULL));}
            ;

type :
            INT {$$=mkNode("INT", NULL, NULL);}
            |BOOL {$$=mkNode("BOOL", NULL, NULL);}
            |CHAR {$$=mkNode("CHAR", NULL, NULL);}
            |REAL {$$=mkNode("REAL", NULL, NULL);}
            |STRING {$$=mkNode("STRING", NULL, NULL);}
            |INTPTR {$$=mkNode("INTPTR", NULL, NULL);}
            |CHARPTR {$$=mkNode("CHARPTR", NULL, NULL);}
            |REALPTR {$$=mkNode("REALPTR", NULL, NULL);}
            ;

opt_var:
            {$$= mkNode("VAR_EMPTY",NULL,NULL);}
            | VAR var_decl_list {$$=$2;}
            ;

var_decl_list : 
            var_decl {$$=$1;}
            |var_decl_list var_decl {$$=mkNode("VAR_DECL",$1,$2);}
            ;

var_decl : 
            TYPE type COLON var_item_list SEMICOLON {$$=mkNode("VAR_DECL",$2,$4);}
            ;

var_item_list : 
            var_item {$$=$1;}
            | var_item_list COMMA var_item {$$=mkNode("VAR_ITEM_LIST",$1,$3);}
            ;

var_item : 
            ID {$$=mkNode("VAR",mkNode($1,NULL,NULL),NULL);}
            | ID COLON literal {$$=mkNode("VAR_ASSIGN",mkNode($1,NULL,NULL),$3);}
            | ID OPENBRACKET DEC_LIT CLOSEBRACKET{ 
                $$ = mkNode("STRING_VAR", mkNode($1, NULL, NULL), mkNode($3,NULL,NULL));}
            | ID OPENBRACKET DEC_LIT CLOSEBRACKET COLON STRING_LIT {
                $$ = mkNode("STRING_VAL_ASSIGN",mkNode("STRING_VAR",mkNode($1, NULL, NULL), mkNode($3, NULL,NULL)),
                mkNode($6, NULL,NULL));   
            }
            ;

literal :
          DEC_LIT { $$ = mkNode($1, NULL, NULL); }
        | B_TRUE    { $$ = mkNode("TRUE", NULL, NULL); }
        | B_FALSE   { $$ = mkNode("FALSE", NULL, NULL); }
        | CHAR_LIT    { $$ = mkNode($1, NULL, NULL); }
        | STRING_LIT  { $$ = mkNode($1, NULL, NULL); }
        | HEX_LIT { $$ = mkNode($1, NULL, NULL); }
        | REAL_LIT { $$ = mkNode($1, NULL, NULL); }
        | NULLL { $$ = mkNode("null", NULL, NULL); }  
                
stat_list:
            {$$ = mkNode("empty_state_list", NULL,NULL);}
            | stat {$$ = $1;}
            | stat stat_list {$$ = mkNode("statements", $1, $2);}
            ;

stat:
            function {$$=$1;}
            | assignment_stat {$$ = $1;}
            | if_stat {$$ = $1;}
            | while_stat {$$ = $1;}
            | for_stat {$$ = $1;}
            | do_while_stat {$$ = $1;}
            | block_stat {$$ = $1;}
            /* | return_stat {$$ = $1;} */
            | call_stat {$$ = $1;}
        ;

call_stat:
            ID ASSIGNMENT CALL ID OPENPAREN expression_list CLOSEPAREN SEMICOLON
            {
                $$ = mkNode( "ASSIGNMENT", mkNode($1, NULL, NULL), mkNode("CALL", mkNode($4,NULL,NULL),$6));
            }
            | ID ASSIGNMENT CALL ID OPENPAREN CLOSEPAREN SEMICOLON
            {
                $$ = mkNode( "ASSIGNMENT", mkNode($1, NULL, NULL), mkNode("CALL", mkNode($4,NULL,NULL),NULL));
            }
            | CALL ID OPENPAREN expression_list CLOSEPAREN SEMICOLON {
                $$ = mkNode("PROC_CALL", mkNode($2,NULL,NULL), $4);
            }
            | CALL ID OPENPAREN CLOSEPAREN SEMICOLON {
                $$ = mkNode("PROC_CALL", mkNode($2,NULL,NULL), NULL);
            }
            ;
if_stat:
            IF expression COLON block_stat {$$ = mkNode("if", $2, $4);}
            | IF expression COLON block_stat ELSE COLON block_stat {$$ = mkNode("if-else", $2, mkNode("then", $4, mkNode("else", $7, NULL)));}
            | IF expression COLON block_stat ELIF expression COLON block_stat {$$ = mkNode("if-elif", $2, mkNode("then", $4, mkNode("elif-cond", $6, $8)));}
            | IF expression COLON block_stat ELIF expression COLON block_stat ELSE COLON block_stat {$$ = mkNode("if-elif-else", $2, mkNode("then", $4, mkNode("elif-cond", $6, mkNode("elif-then", $8, mkNode("else", $11, NULL)))));}
            ;

while_stat:
            WHILE expression COLON block_stat {$$ = mkNode("while", $2, $4);}
            ;

do_while_stat:
            DO COLON block_stat WHILE expression SEMICOLON {$$ = mkNode("do-while", $3, mkNode("cond", $5, NULL));}
            ;

for_stat:
            FOR for_header COLON block_stat {$$ = mkNode("for", $2, $4);}
            | FOR for_header COLON opt_var block_stat {$$ = mkNode("for", $2, mkNode("block", $5, $4));}
            ;

for_header:
            OPENPAREN ID ASSIGNMENT expression SEMICOLON expression SEMICOLON update_exp CLOSEPAREN 
            {$$ = mkNode("for-header", mkNode("init", mkNode($2, NULL, NULL), $4), 
                                    mkNode("loop", $6, $8));}
            ;   

update_exp:
            ID ASSIGNMENT expression {$$ = mkNode("update", mkNode($1, NULL, NULL), $3);}
            ;

condition:
            expression {$$ = $1;}
            | NOT condition {$$ = mkNode("not", $2, NULL);}
            | OPENPAREN condition CLOSEPAREN {$$ = $2;}
            | B_TRUE {$$ = mkNode("true", NULL, NULL);}
            | B_FALSE {$$ = mkNode("false", NULL, NULL);}
            ;


block_stat:
            BEGIN_T stat_list END {$$ = mkNode("block", $2, NULL);}
            /* | opt_var BEGIN_T stat_list END {$$ = mkNode("block", $3, $1);} */
            ;


assignment_stat:
                ID ASSIGNMENT expression SEMICOLON {$$ = mkNode("assign", mkNode($1, NULL, NULL), $3);}
                | ID OPENBRACKET expression CLOSEBRACKET ASSIGNMENT CHAR_LIT SEMICOLON {
                    
                    $$ = mkNode("array_assign", mkNode($1, $3, NULL), mkNode($6, NULL, NULL));
                }
                |MULTI ID ASSIGNMENT expression SEMICOLON {$$ = mkNode("pointer_assign", mkNode($2, NULL, NULL), $4);}
                |ID ASSIGNMENT ADDRESS ID SEMICOLON {$$ = mkNode("ref_assign", mkNode($1, NULL, NULL), mkNode($4, NULL, NULL));}
                |ID ASSIGNMENT NULLL SEMICOLON {$$ = mkNode("null_assign", mkNode($1, NULL, NULL), mkNode("null", NULL, NULL));}
                |ID OPENBRACKET expression CLOSEBRACKET ASSIGNMENT DEC_LIT SEMICOLON {
                    $$ = mkNode("array_assign", mkNode($1, $3, NULL), mkNode($6, NULL, NULL));
                }
                | ID OPENBRACKET expression CLOSEBRACKET ASSIGNMENT STRING_LIT SEMICOLON {
                    $$ = mkNode("array_assign", mkNode($1, $3, NULL), mkNode($6, NULL, NULL));
                }
                | ID CLOSEBRACKET expression OPENBRACKET ASSIGNMENT expression SEMICOLON {
                    $$ = mkNode("array_assign", mkNode($1, $3, NULL), $6);
                }
                ;

                

return_stat:
                RETURN expression SEMICOLON {$$ = mkNode("RETURN", $2, NULL);}

                ;

expression_list: 
    expression {$$ = $1;}
    | expression COMMA expression_list {$$ = mkNode("expr_list", $1, $3);}
    ;

expression:     
                expression PLUS expression { $$ = mkNode("+", $1, $3); }
                | expression MINUS expression { $$ = mkNode("-", $1, $3); }
                | expression MULTI expression { $$ = mkNode("*", $1, $3); }
                | expression DIV expression { $$ = mkNode("/", $1, $3); }
                | expression AND expression { $$ = mkNode("and", $1, $3); }
                | expression OR expression { $$ = mkNode("or", $1, $3); }
                | expression EQL expression { $$ = mkNode("==", $1, $3); }
                | expression NOT_EQL expression { $$ = mkNode("!=", $1, $3); }
                | expression GREATER expression { $$ = mkNode(">", $1, $3); }
                | expression GREATER_EQL expression { $$ = mkNode(">=", $1, $3); }
                | expression LESS expression { $$ = mkNode("<", $1, $3); }
                | expression LESS_EQL expression { $$ = mkNode("<=", $1, $3); }
                | NOT expression { $$ = mkNode("not", $2, NULL); }
                | MINUS expression %prec NOT { $$ = mkNode("unary-", $2, NULL); }
                | ADDRESS ID { $$ = mkNode("address", mkNode($2, NULL, NULL), NULL); }
                | ADDRESS ID OPENBRACKET expression CLOSEBRACKET { 
                    Node *array_elem = mkNode("array_element", mkNode($2, NULL, NULL), $4);
                    $$ = mkNode("address", array_elem, NULL); 
                }
                | MULTI ID %prec NOT { $$ = mkNode("dereference", mkNode($2, NULL, NULL), NULL);  }
                | LENGTH ID LENGTH { $$ = mkNode("length", mkNode($2, NULL, NULL), NULL); }
                | OPENPAREN expression CLOSEPAREN { $$ = $2; }
                | ID { $$ = mkNode($1, NULL, NULL); }
                | ID OPENBRACKET expression CLOSEBRACKET { 
                    $$ = mkNode("array_element", mkNode($1, NULL, NULL), $3); 
                }
                | CALL ID OPENPAREN parameter_list CLOSEPAREN { 
                    $$ = mkNode("function_call", mkNode($2, NULL, NULL), $4); 
                }
                | literal { $$ = $1; }
                ;

%%


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