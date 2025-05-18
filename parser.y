%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_NESTING 32

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


static DataType ret_stack[MAX_NESTING];
static int      ret_flag_stack[MAX_NESTING];  
static int      ret_sp = 0; 



// Global var:
Node *ast_root=NULL;
Scope *current_scope = NULL;
int has_main = 0; // Flag for _main_ function
int current_scope_level = 0;
static DataType current_var_type = TYPE_INVALID;
int expected_param_num = 1; //for check order parameter list

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
void check_main_exists();
void check_type_compatibility(DataType target_type, DataType source_type, char *context);
void semantic_error(const char *message, const char *token);
void add_parameters_to_scope(Node *param_list, DataType *param_types, int param_count);
void print_symbol_table(); // For debugging
void free_tree(Node* tree);
void free_symbol_table(Scope* scope);
int count_arguments(Node *arg_list);
void collect_argument_type(Node *arg_list, DataType *types, int *index);
void verify_argument_type(Node *arg_list, Symbol *func);
void verify_bool(Node *cond_node, const char *context);
void verify_string_index(Node *id_node, Node *index_expr);
void verify_assignment(Node *left, Node *right);
static void add_params_rec(Node *plist, DataType *types, int *idx);
void verify_return(Node *expr_node);


static inline void push_return(DataType t)
{
    if (ret_sp == MAX_NESTING)
        semantic_error("Function nesting too deep", "");
    ret_stack[ret_sp]       = t;
    ret_flag_stack[ret_sp]  = 0;
    ++ret_sp;
}

/* pop, check “all paths return” */
static inline void pop_return(void)
{
    if (ret_sp == 0)
        semantic_error("Internal error: return-stack underflow", "");
    --ret_sp;
    if (ret_stack[ret_sp] != TYPE_VOID && ret_flag_stack[ret_sp] == 0)
        semantic_error("Non-void function may reach end without return", "");
}

/* current function’s expected type */
static inline DataType current_return(void)
{
    return ret_sp ? ret_stack[ret_sp-1] : TYPE_VOID;
}

/* mark that we have executed a return in this function */
static inline void mark_return_found(void)
{
    if (ret_sp) ret_flag_stack[ret_sp-1] = 1;
}



%}

%union
{
char *str;
struct Node *node;
}

%token<str> BOOL CHAR INT REAL STRING INTPTR CHARPTR REALPTR TYPE 
%token<str> IF ELIF ELSE WHILE FOR VAR PAR RETURN NULLL DO RETURNS BEGIN_T END DEF CALL AND NOT OR 
%token<str> DIV ASSIGNMENT EQL GREATER GREATER_EQL LESS LESS_EQL MINUS NOT_EQL PLUS MULTI ADDRESS 
%token<str> LENGTH SEMICOLON COLON COMMA OPENBRACE CLOSEBRACE OPENPAREN CLOSEPAREN OPENBRACKET CLOSEBRACKET 
%token<str> B_TRUE B_FALSE CHAR_LIT STRING_LIT DEC_LIT HEX_LIT REAL_LIT ID MAIN_FUNC

%type<node> program function_list function main_function function_item returns_spec parameter_list param_decl_list 
%type<node> param_decl type opt_var var_decl_list var_decl var_item_list var_item 
%type<node> literal stat_list stat call_stat if_stat while_stat do_while_stat block_stat single_statement
%type<node> for_stat assignment_stat return_stat expression  expression_list for_header update_exp for_body

%left  OR                    /* ||                       */
%left  AND   
%right NOT                   /* unary  not, !            */                /* &&                       */
%nonassoc EQL NOT_EQL        /* ==, !=                   */
%nonassoc LESS LESS_EQL GREATER GREATER_EQL   /* <  <=  >  >=       */
%left  PLUS MINUS            /* +  -                     */
%left  MULTI DIV             /* *  /                     */
%right ADDRESS               /* unary  &, * (dereference)*/

%%

program : function_list
{
    $$ = $1;
    ast_root=$$;
    printtree($$, 0);
};

function_list : function_list function_item { $$ = mkNode("Function_list", $1, $2); }
| function_item { $$ = $1; };

function_item : function {$$=$1;}
                | main_function {$$=$1;};

main_function : DEF MAIN_FUNC OPENPAREN
{
    expected_param_num = 1;
} 
parameter_list CLOSEPAREN
{

    if(has_main)
    {
        semantic_error("Multiply definitions of '_main_' function are not allowed",$2);
    }
    has_main=1;

    if(count_parameters($5)!=0){
        semantic_error("_main_ procedure must not accept any parameters",$2);
    }
    add_function("_main_",TYPE_VOID,0,NULL);

    enter_scope();
}
 COLON opt_var BEGIN_T stat_list END
{
    push_return(TYPE_VOID);

    /* create nodes for readability */
    Node *idnode = mkNode("_main_", NULL, NULL);
    Node *parametersnodes = mkNode("PARAMETERS", $5, NULL);
    Node *bodynode = mkNode("BODY", $9, $11);
    $$ = mkNode("PROCEDURE", idnode, mkNode("PROC_PARTS", parametersnodes, bodynode));
    print_symbol_table();
    pop_return();
    exit_scope();
};

function: DEF ID OPENPAREN 
        {
            expected_param_num = 1;
            // Common code from both $@3 and $@5 actions
        }
        parameter_list CLOSEPAREN
        {
            if(find_symbol_in_scope($2,current_scope)){
                semantic_error("Function with the same name already exists in the current scope",$2);
            }
            printf("DEBUG: Entering function definition for '%s'\n", $2);

            DataType *param_types=NULL;
            int param_count=0;
            extract_param_types($5,&param_types,&param_count);
            add_function($2, TYPE_VOID, param_count, param_types);
        }
        COLON 
        returns_spec 
        {
            // Store return type
            Symbol *f = find_function($<str>2);
            if(f) f->return_type = get_type_from_string($9->token);
            
            // Enter scope for function body
            enter_scope();
            
            // Add parameters to scope
            DataType *param_types=NULL;
            int param_count=0;
            extract_param_types($5,&param_types,&param_count);
            add_parameters_to_scope($5,param_types,param_count);
        }
        opt_var BEGIN_T stat_list END
        {
            /* create nodes for readability */
            Node *idnode = mkNode($2, NULL, NULL);
            Node *parametersnodes = mkNode("PARAMETERS", $5, NULL);
            Node *returnsnode = mkNode("RETURNS", $9, NULL);
            Node *body_statements = mkNode("statements", $13, NULL);
            Node *bodynode = mkNode("BODY", $11, body_statements);
            Node *defbody = mkNode("DEF_BODY", returnsnode, bodynode);
            $$ = mkNode("FUNCTION", idnode, mkNode("FUNC_PARTS", parametersnodes, defbody));
            
            print_symbol_table();
            pop_return();
            exit_scope();
        }
        ;

returns_spec : RETURNS type {
                if(strcmp($2->token, "STRING") == 0){
                    semantic_error("Return type of a function cannot be STRING", $2->token);}
                push_return(get_type_from_string($2->token));
                $$ = $2;}
                | {
                    push_return(TYPE_VOID); 
                    $$=mkNode("RETURN VOID",NULL,NULL);};


parameter_list:
{
    $$ = mkNode("PARAM_EMPTY", NULL, NULL);
}
| param_decl_list { $$ = $1; };

param_decl_list : param_decl { $$ = $1; }
| param_decl_list SEMICOLON param_decl { $$ = mkNode("PARAMS_LIST", $1, $3); };

param_decl : PAR
{
    int param_num = 0;
    sscanf($1,"par%d", &param_num);

    
    if (param_num != expected_param_num) {
        char msg[120];
        sprintf(msg, "Parameters must be ordered sequentially (par1, par2, ...). Expected par%d but found %s", expected_param_num, $1);
        semantic_error(msg, $1);
        }
    expected_param_num = param_num+1;
}

type COLON ID { $$ = mkNode("PARAM", $3, mkNode($5, NULL, NULL)); };

type : INT { $$ = mkNode("INT", NULL, NULL); }
| BOOL { $$ = mkNode("BOOL", NULL, NULL); }
| CHAR { $$ = mkNode("CHAR", NULL, NULL); }
| REAL { $$ = mkNode("REAL", NULL, NULL); }
| STRING { $$ = mkNode("STRING", NULL, NULL); }
| INTPTR { $$ = mkNode("INTPTR", NULL, NULL); }
| CHARPTR { $$ = mkNode("CHARPTR", NULL, NULL); }
| REALPTR { $$ = mkNode("REALPTR", NULL, NULL); };

opt_var:
{
    $$ = mkNode("VAR_EMPTY", NULL, NULL);
}
| VAR var_decl_list { $$ = $2; };

var_decl_list : var_decl { $$ = $1; }
| var_decl_list var_decl { $$ = mkNode("VAR_DECL", $1, $2); };

var_decl : TYPE type COLON 
        {
            current_var_type=get_type_from_string($2->token);
        }
var_item_list SEMICOLON 
{
    current_var_type=TYPE_INVALID;
     $$ = mkNode("VAR_DECL", $2, $5); };

var_item_list : var_item { $$ = $1; }
| var_item_list COMMA var_item { $$ = mkNode("VAR_ITEM_LIST", $1, $3); };

var_item :
 ID { 
        if(find_symbol_in_scope($1,current_scope)){
            semantic_error("Variable already defined in the current scope",$1);
        }
        add_symbol($1,current_var_type,KIND_VARIABLE);
    
        $$ = mkNode("VAR", mkNode($1, NULL, NULL), NULL); }
| ID COLON literal 
{   
    if(find_symbol_in_scope($1,current_scope)){
        semantic_error("Variable already defined in the current scope",$1);
    }
    DataType lit_type=get_expression_type($3);
    add_symbol($1,lit_type,KIND_VARIABLE);

    $$ = mkNode("VAR_ASSIGN", mkNode($1, NULL, NULL), $3); }
| ID OPENBRACKET DEC_LIT CLOSEBRACKET
{
    if(find_symbol_in_scope($1,current_scope)){
        semantic_error("Variable already defined in the current scope",$1);
    }
    add_symbol($1,TYPE_STRING,KIND_VARIABLE);

    $$ = mkNode("STRING_VAR", mkNode($1, NULL, NULL), mkNode($3, NULL, NULL));
}
| ID OPENBRACKET DEC_LIT CLOSEBRACKET COLON STRING_LIT
{
    if(find_symbol_in_scope($1,current_scope)){
        semantic_error("Variable already defined in the current scope",$1);
    }
    add_symbol($1,TYPE_STRING,KIND_VARIABLE);

    $$ = mkNode("STRING_VAL_ASSIGN", mkNode("STRING_VAR", mkNode($1, NULL, NULL), mkNode($3, NULL, NULL)),
                mkNode($6, NULL, NULL));
};

literal : DEC_LIT { $$ = mkNode($1, NULL, NULL); }
| B_TRUE { $$ = mkNode("TRUE", NULL, NULL); }
| B_FALSE { $$ = mkNode("FALSE", NULL, NULL); }
| CHAR_LIT { $$ = mkNode($1, NULL, NULL); }
| STRING_LIT { $$ = mkNode($1, NULL, NULL); }
| HEX_LIT { $$ = mkNode($1, NULL, NULL); }
| REAL_LIT { $$ = mkNode($1, NULL, NULL); }
| NULLL { $$ = mkNode("null", NULL, NULL); }

stat_list:
{
    $$ = mkNode("empty_state_list", NULL, NULL);
}
| stat stat_list { $$ = mkNode("statements", $1, $2); }
;

stat : function { $$ = $1; }
| assignment_stat { $$ = $1; }
| if_stat { $$ = $1; }
| while_stat { $$ = $1; }
| for_stat { $$ = $1; }
| do_while_stat { $$ = $1; }
| block_stat { $$ = $1; }
| return_stat {$$ = $1;}
| call_stat { $$ = $1; };

call_stat : ID ASSIGNMENT CALL ID OPENPAREN expression_list CLOSEPAREN SEMICOLON
{
    Symbol *func=find_function($4);
    Symbol *var=find_symbol($1);
    if(!var){
        semantic_error("Variable used before it been declared.",$1);
    }
    if(!func){
        semantic_error("Function called before it was defined or does not exist.",$4);
    }
    verify_argument_type($6, func);
    if (func->return_type == TYPE_VOID) {
        semantic_error("Cannot assign the result of a VOID procedure",
                       func->name);
    }
    check_type_compatibility(var->type, func->return_type, "function-call assignment");
    $$ = mkNode("ASSIGNMENT", mkNode($1, NULL, NULL), mkNode("CALL", mkNode($4, NULL, NULL), $6));
}
| ID ASSIGNMENT CALL ID OPENPAREN CLOSEPAREN SEMICOLON
{
    Symbol *func=find_function($4);
    Symbol *var=find_symbol($1);
    if(!var){
        semantic_error("Variable used before it been declared.",$1);
    }
    if(!func){
        semantic_error("Function called before it was defined or does not exist.",$4);
    }
    verify_argument_type(NULL, func);

      if (func->return_type == TYPE_VOID) {
        semantic_error("Cannot assign the result of a VOID procedure",
                       func->name);
    }
    check_type_compatibility(var->type, func->return_type, "function-call assignment");


    $$ = mkNode("ASSIGNMENT", mkNode($1, NULL, NULL), mkNode("CALL", mkNode($4, NULL, NULL), NULL));
}
| CALL ID OPENPAREN expression_list CLOSEPAREN SEMICOLON
{
    Symbol *func=find_function($2);
    if(!func){
        semantic_error("Function called before it was defined or does not exist.",$2);
    }
    verify_argument_type($4, func);
    $$ = mkNode("FUNC_CALL", mkNode($2, NULL, NULL), $4);
}
| CALL ID OPENPAREN CLOSEPAREN SEMICOLON
{
    Symbol *func=find_function($2);
    if(!func){
        semantic_error("Function called before it was defined or does not exist.",$2);
    }
    verify_argument_type(NULL, func);
    $$ = mkNode("PROC_CALL", mkNode($2, NULL, NULL), NULL);
};
if_stat : IF expression COLON block_stat { 
    verify_bool($2, "IF statement");    
    $$ = mkNode("if", $2, $4); }
| IF expression COLON block_stat ELSE COLON block_stat { 
    verify_bool($2, "IF statement");    
    $$ = mkNode("if-else", $2, mkNode("then", $4, mkNode("else", $7, NULL))); }
| IF expression COLON block_stat ELIF expression COLON block_stat { 
    verify_bool($2, "IF statement");    
    verify_bool($6, "IF statement");    
    $$ = mkNode("if-elif", $2, mkNode("then", $4, mkNode("elif-cond", $6, $8))); }
| IF expression COLON block_stat ELIF expression COLON block_stat ELSE COLON block_stat { 
    verify_bool($2, "IF statement");    
    verify_bool($6, "IF statement");    
    $$ = mkNode("if-elif-else", $2, mkNode("then", $4, mkNode("elif-cond", $6, mkNode("elif-then", $8, mkNode("else", $11, NULL))))); };

while_stat : WHILE expression COLON block_stat { 
    verify_bool($2, "WHILE statement");    
    $$ = mkNode("while", $2, $4); };

do_while_stat : DO COLON block_stat WHILE expression SEMICOLON { 
    verify_bool($5, "DO-WHILE statement");    
    $$ = mkNode("do-while", $3, mkNode("cond", $5, NULL)); };

for_stat : FOR for_header COLON for_body { $$ = mkNode("for", $2, $4); }

for_body: block_stat 
        { 
            $$ = $1; 
        }
        | opt_var block_stat 
        { 
            $$ = mkNode("block", $1, $2); 
        }
        ;

for_header : OPENPAREN ID ASSIGNMENT expression SEMICOLON expression SEMICOLON update_exp CLOSEPAREN
{
    verify_assignment(mkNode($2,NULL,NULL), $4);
    verify_bool($6, "FOR statement");    
    $$ = mkNode("for-header", mkNode("init", mkNode($2, NULL, NULL), $4),
                mkNode("loop", $6, $8));
};

update_exp : ID ASSIGNMENT expression {
    verify_assignment(mkNode($1,NULL,NULL), $3);
    $$ = mkNode("update", mkNode($1, NULL, NULL), $3); };

/*condition : expression { $$ = $1; }
| NOT condition { $$ = mkNode("not", $2, NULL); }
| OPENPAREN condition CLOSEPAREN { $$ = $2; }
| B_TRUE { $$ = mkNode("true", NULL, NULL); }
| B_FALSE { $$ = mkNode("false", NULL, NULL); };
*/
block_stat: opt_var BEGIN_T stat_list END
          | single_statement
          ;

single_statement: assignment_stat { $$ = mkNode("STATEMENT", $1, NULL); }
                ;


assignment_stat : ID ASSIGNMENT expression SEMICOLON 
{
    Symbol *var=find_symbol($1);
    if(!var){
        semantic_error("Variable used before it been declared.",$1);
    }
    verify_assignment(mkNode($1,NULL,NULL), $3);
    $$ = mkNode("assign", mkNode($1, NULL, NULL), $3); 
}
| ID OPENBRACKET expression CLOSEBRACKET ASSIGNMENT CHAR_LIT SEMICOLON
{
    verify_string_index(mkNode($1,NULL,NULL), $3); 
    Symbol *var=find_symbol($1);
    if(!var){
        semantic_error("Variable used before it been declared.",$1);
    }
    verify_assignment(mkNode("array_element", mkNode($1,NULL,NULL), $3), mkNode($6,NULL,NULL));
    $$ = mkNode("array_assign", mkNode($1, $3, NULL), mkNode($6, NULL, NULL));
}
| MULTI ID ASSIGNMENT expression SEMICOLON 
{ 
    Symbol *var=find_symbol($2);
    if(!var){
        semantic_error("Variable used before it been declared.",$2);
    }
    Node *point   = mkNode("dereference", mkNode($2,NULL,NULL), NULL);
    verify_assignment(point, $4);
    $$ = mkNode("pointer_assign", mkNode($2, NULL, NULL), $4); }
| ID ASSIGNMENT ADDRESS ID SEMICOLON 
{
    Symbol *var1=find_symbol($1);
    Symbol *var4=find_symbol($4);
    if(!var1){
        semantic_error("Variable used before it been declared.",$1);
    }
    if(!var4){
        semantic_error("Variable used before it been declared.",$4);
    }
    verify_assignment(mkNode($1,NULL,NULL), mkNode("address", mkNode($4,NULL,NULL), NULL));
    $$ = mkNode("ref_assign", mkNode($1, NULL, NULL), mkNode($4, NULL, NULL)); }
| ID ASSIGNMENT NULLL SEMICOLON 
{
    Symbol *var=find_symbol($1);
    if(!var){
        semantic_error("Variable used before it been declared.",$1);
    }
    if(!is_pointer_type(var->type)){
                       semantic_error("null may be assigned only to pointer variables", "");
                   }
                   $$ = mkNode("null_assign", mkNode($1, NULL, NULL), mkNode("null", NULL, NULL)); }
| ID OPENBRACKET expression CLOSEBRACKET ASSIGNMENT expression SEMICOLON
{
    verify_string_index(mkNode($1,NULL,NULL), $3);
    Symbol *var=find_symbol($1);
    if(!var){
        semantic_error("Variable used before it been declared.",$1);
    }
     verify_assignment(mkNode("array_element", mkNode($1,NULL,NULL), $3),$6);
    $$ = mkNode("array_assign", mkNode($1, $3, NULL), $6);
};

return_stat
    : RETURN expression SEMICOLON
      { verify_return($2); $$ = mkNode("RETURN", $2, NULL); }
    | RETURN SEMICOLON
      { verify_return(NULL); $$ = mkNode("RETURN", NULL, NULL); } ; 

expression_list : expression { $$ = $1; }
| expression COMMA expression_list { $$ = mkNode("expr_list", $1, $3); };

expression : expression PLUS expression { $$ = mkNode("+", $1, $3); }
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
| NOT expression %prec NOT { $$ = mkNode("not", $2, NULL); }
| MINUS expression %prec NOT { $$ = mkNode("unary-", $2, NULL); }
| ADDRESS ID 
{
    Symbol *var=find_symbol($2);
    if(!var){
        semantic_error("Variable used before it been declared.",$2);
    }
    $$ = mkNode("address", mkNode($2, NULL, NULL), NULL); }
| ADDRESS ID OPENBRACKET expression CLOSEBRACKET
{
    verify_string_index(mkNode($2,NULL,NULL), $4);
    Symbol *var=find_symbol($2);
    if(!var){
        semantic_error("Variable used before it been declared.",$2);
    }
    Node *array_elem = mkNode("array_element", mkNode($2, NULL, NULL), $4);
    $$ = mkNode("address", array_elem, NULL);
}
| MULTI expression   %prec NOT      /* *expr */
    { $$ = mkNode("dereference", $2, NULL); }
| LENGTH ID LENGTH 
{
    Symbol *var=find_symbol($2);
    if(!var){
        semantic_error("Variable used before it been declared.",$2);
    }
    $$ = mkNode("length", mkNode($2, NULL, NULL), NULL); }
| OPENPAREN expression CLOSEPAREN { $$ = $2; }
| ID 
{
    Symbol *var=find_symbol($1);
    if(!var){
        semantic_error("Variable used before it been declared.",$1);
    }
    $$ = mkNode($1, NULL, NULL); }
| ID OPENBRACKET expression CLOSEBRACKET
{
    verify_string_index(mkNode($1,NULL,NULL), $3);
    Symbol *var=find_symbol($1);
    if(!var){
        semantic_error("Variable used before it been declared.",$1);
    }
    $$ = mkNode("array_element", mkNode($1, NULL, NULL), $3);
}
| CALL ID OPENPAREN parameter_list CLOSEPAREN
{
    Symbol *func=find_function($2);
    if(!func){
        semantic_error("Function called before it was defined or does not exist.",$2);
    }
    int actual_param_count=count_parameters($4);
    if(func->param_count!=actual_param_count){
        char msg[100];
        sprintf(msg,"Function '%s' expect %d parameters, but %d parameters provided",$2,func->param_count,actual_param_count);
        semantic_error(msg,$2);
    }
    $$ = mkNode("function_call", mkNode($2, NULL, NULL), $4);
}
| literal { $$ = $1; };

%%

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
    printf("param_count=%d \n",param_count);
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

        if (is_pointer_type(left_type) && right_type == TYPE_INT)
            return left_type;                      /* ptr ± int */
        if (is_pointer_type(right_type) && left_type == TYPE_INT &&
            strcmp(expr->token, "+") == 0)         /* int + ptr */
            return right_type;
        if (is_pointer_type(left_type) && is_pointer_type(right_type) &&
            strcmp(expr->token, "-") == 0)
            return TYPE_INT;


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
        // Comparison operators (>, >=, <, <=)
    if (strcmp(expr->token, ">") == 0 || strcmp(expr->token, ">=") == 0 ||
        strcmp(expr->token, "<") == 0 || strcmp(expr->token, "<=") == 0) {
        
        DataType left_type = get_expression_type(expr->left);
        DataType right_type = get_expression_type(expr->right);
        
        if(!is_numeric_type(left_type)||!is_numeric_type(right_type)){
             semantic_error("Relational operators require INT or REAL operands","");
        }
            return TYPE_BOOL;
       
    }

    if (strcmp(expr->token,"==")==0 || strcmp(expr->token,"!=")==0) {

        DataType left_type = get_expression_type(expr->left);
        DataType right_type = get_expression_type(expr->right);

        /* primitive exact match */
        if (left_type == right_type &&
            (left_type==TYPE_INT || left_type==TYPE_BOOL || left_type==TYPE_REAL || left_type==TYPE_CHAR))
            return TYPE_BOOL;

        /* pointer-to-same-base */
        if (is_pointer_type(left_type) && left_type == right_type)
            return TYPE_BOOL;

        /* pointer vs null */
        if ((is_pointer_type(left_type) && strcmp(expr->right->token,"null")==0) ||
            (is_pointer_type(right_type) && strcmp(expr->left->token,"null")==0))
            return TYPE_BOOL;

        semantic_error("Operands of ==/!= must be two INT, BOOL, REAL, CHAR, "
                    "or matching pointers","");
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

    /* 1.  Get the type of the operand expression (whatever it is) */
    DataType ptr_type = get_expression_type(expr->left);

    /* 2.  Make sure it is really a pointer                           */
    if (!is_pointer_type(ptr_type)) {
        semantic_error("Cannot dereference a non-pointer expression", "");
        /* semantic_error exits, but return keeps the compiler happy  */
        return TYPE_INVALID;
    }

    /* 3.  Dereferencing gives the base type of that pointer          */
    return get_base_type(ptr_type);
}

    // Length operator
    if (strcmp(expr->token, "length") == 0)            
    {
        
        DataType op_type = get_expression_type(expr->left);

        if (op_type != TYPE_STRING) {
            semantic_error("| | operator can only be applied to STRING values", "");
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
    if (strcmp(param_list->token, "PARAMS_LIST") == 0 || strcmp(param_list->token, "expr_list") == 0) {
        // Process left side
        count += count_parameters(param_list->left);
        // Process right side
        count += count_parameters(param_list->right);
    } else if (strcmp(param_list->token, "PARAM") == 0 || param_list->token !=NULL) {
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

    printf("DEBUG: Visiting node with token: %s\n", param_node->token);

    if (strcmp(param_node->token, "PARAMS_LIST") == 0) {
        extract_param_types_helper(param_node->left, types, index);
        extract_param_types_helper(param_node->right, types, index);
    } else if (strcmp(param_node->token, "PARAM") == 0) {
        printf("DEBUG: Extracting type from: %s\n", param_node->left->token);
        types[(*index)++] = get_type_from_string(param_node->left->token);
    }
}


/*calculate the arg_list by counting commas*/
int count_arguments(Node *arg_list){
    if(!arg_list) return 0;

    if(strcmp(arg_list->token, "expr_list") == 0){
        return count_arguments(arg_list->left) + count_arguments(arg_list->right);
    }

    return 1;
}


/*collect the types of each argument by order*/
void collect_argument_types(Node *arg_list, DataType *types, int *index)
{
    if (!arg_list) return;

    if (strcmp(arg_list->token, "expr_list") == 0) {
        collect_argument_types(arg_list->left,  types, index);
        collect_argument_types(arg_list->right, types, index);
    } else {
        types[(*index)++] = get_expression_type(arg_list);
    }
}

void verify_argument_type(Node *arg_list, Symbol *func)
{
    /* ---------- arity ---------- */
    int argc = count_arguments(arg_list);
    if (argc != func->param_count) {
        char msg[120];
        sprintf(msg,
                "Function '%s' expects %d parameters, but %d provided",
                func->name, func->param_count, argc);
        semantic_error(msg, func->name);
    }
    if (argc == 0) return;                 /* nothing to compare */

    /* ---------- collect actual types ---------- */
    DataType *actual = malloc(argc * sizeof(DataType));
    if (!actual) { perror("malloc"); exit(1); }

    int idx = 0;
    collect_argument_types(arg_list, actual, &idx);

    /* ---------- pairwise compatibility ---------- */
    for (int i = 0; i < argc; ++i) {
        DataType expected = func->param_types[i];
        DataType got = actual[i];

        check_type_compatibility(expected, got,
                                 "function call argument");
    }

    free(actual);
}

void verify_bool(Node *cond_node, const char *context){
    DataType cond = get_expression_type(cond_node);
    if(cond != TYPE_BOOL){
        char msg[120];
        sprintf(msg, "Condition in %s must be BOOL, got '%s'",
                context, type_to_string(cond));
        semantic_error(msg, "");
    }
}

void verify_string_index(Node *id_node, Node *index_expr){
    Symbol *sym = find_symbol(id_node->token);
    if(!sym){
        semantic_error("Variable used before it was declared", id_node->token);
    } 

    if(sym->type!=TYPE_STRING) 
    {
        char msg[120];
        sprintf(msg,
           "Bracket operator [] may be used only with STRING variables, "
           "but '%s' is of type '%s'",
           sym->name, type_to_string(sym->type));
        semantic_error(msg, sym->name);
    }

    DataType index_type = get_expression_type(index_expr);
    if(index_type!=TYPE_INT){
         char msg[120];
        sprintf(msg,
           "Index inside [] must be INT, got '%s'",
           type_to_string(index_type));
        semantic_error(msg, "");
    }
}

void verify_assignment(Node *left, Node *right)
{
    DataType left_type = TYPE_INVALID;

    /* 1. array element  s[i] = … */
    if (strcmp(left->token, "array_element") == 0) {
        Node *id    = left->left;
        Node *index = left->right;
        verify_string_index(id, index);
        left_type = TYPE_CHAR;
    }

    /* 2. pointer dereference  *p = … */
    else if (strcmp(left->token, "dereference") == 0) {
        Node *id = left->left;                 /* pointer variable node */
        if (!id)
            semantic_error("Invalid dereference node", "");

        Symbol *sym = find_symbol(id->token);
        if (!sym)
            semantic_error("Variable used before it was declared", id->token);

        if (!is_pointer_type(sym->type))
            semantic_error("Can only dereference a pointer variable", sym->name);

        left_type = get_base_type(sym->type);  /* INT_PTR → INT, etc. */
    }

    /* 3. plain identifier  x = … */
    else {
        Symbol *sym = find_symbol(left->token);
        if (!sym)
            semantic_error("Variable used before it was declared", left->token);
        left_type = sym->type;
    }

    /* -------- right-hand side checks stay the same -------- */
    DataType right_type = get_expression_type(right);

    if (strcmp(right->token, "null") == 0) {
        if (!is_pointer_type(left_type))
            semantic_error("null may be assigned only to pointer variables", "");
        return;
    }

    check_type_compatibility(left_type, right_type, "Assignment");
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

void add_parameters_to_scope(Node *param_list, DataType *param_types, int param_count) {
    (void)param_count;              /* not needed here */
    int idx = 0;                    /* fresh counter for this function */
    add_params_rec(param_list, param_types, &idx);
}

static void add_params_rec(Node *plist,
                           DataType *types,
                           int *idx)
{
    if (!plist) return;

    if (strcmp(plist->token, "PARAMS_LIST") == 0) {
        add_params_rec(plist->left,  types, idx);
        add_params_rec(plist->right, types, idx);
    } else if (strcmp(plist->token, "PARAM") == 0) {
        const char *name = plist->right->token;
        DataType    tp   = types[*idx];          /* take current slot   */
        printf("DEBUG: Adding parameter '%s' of type '%s' to scope %d\n",
               name, type_to_string(tp), current_scope_level);
        add_symbol((char *)name, tp, KIND_PARAMETER);
        (*idx)++;                                /* advance for next one */
    }
}


void verify_return(Node *expr_node)
{
    DataType expected = current_return();   

    /* 1. VOID procedure rules */
    if (expected == TYPE_VOID)
    {
        if (expr_node)
            semantic_error("VOID procedure cannot return a value", "");
        mark_return_found();                /* bare return is OK */
        return;
    }

    /* 2. Non-void function rules */
    if (!expr_node)
        semantic_error("Function must return a value", "");

    DataType delivered = get_expression_type(expr_node);
    check_type_compatibility(expected, delivered, "return statement");

    mark_return_found();                    /* type is fine */
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
                   type_to_string(sym->kind == KIND_FUNCTION? sym->return_type: sym->type),
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