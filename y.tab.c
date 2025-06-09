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

/* ========================================================================== */
/*                      3–ADDRESS–CODE  (3AC)  GENERATOR                      */
/*  Paste this block once, AFTER the existing #include’s, BEFORE the grammar  */
/* ========================================================================== */
#include <stdarg.h>

/* ------------ local instruction list ------------------------------------ */
typedef struct TACInstr {
    char *text;
    struct TACInstr *next;
} TACInstr;

static TACInstr *codeHead = NULL, *codeTail = NULL;
static int       tmpCnt   = 0;
static int       lblCnt   = 1;

static char *newTmp  (void){ char b[32]; sprintf(b,"t%d",tmpCnt++);  return strdup(b); }
static char *newLabel(void){ char b[32]; sprintf(b,"L%d",lblCnt++); return strdup(b); }

static void emit(const char *fmt, ...)
{
    va_list ap;  char buf[128];
    va_start(ap, fmt); vsnprintf(buf,sizeof(buf),fmt,ap); va_end(ap);

    TACInstr *n = malloc(sizeof(*n));
    n->text = strdup(buf);  n->next = NULL;
    if (!codeHead) codeHead = codeTail = n;
    else           codeTail = codeTail->next = n;
}

static void dumpCode(FILE *out)
{
    const char *IND = "    ";
    for (TACInstr *p = codeHead; p; p = p->next) {
        size_t len = strlen(p->text);
        if (len && p->text[len-1]==':')           /* labels flush-left  */
            fprintf(out,"%s\n",p->text);
        else
            fprintf(out,"%s%s\n",IND,p->text);    /* everything else indented */
    }
}

/* ------------ helpers that reuse your existing symbol infrastructure ----- */
static int symExists(const char *name)
{
    if (!name) return 0;
    
    // Check if it's a literal first
    if (!strcmp(name,"TRUE")||!strcmp(name,"FALSE")||!strcmp(name,"null")) return 0;
    
    // Check if it's a number
    char *ep; 
    strtod(name,&ep); 
    if (*ep=='\0') return 0;  // It's a number literal
    
    // Actually check if the symbol exists in the symbol table
    Symbol *sym = find_symbol((char*)name);
    return sym != NULL;
}

/* rough sizeof(T) just for frame-size accounting */
static int sizeofTypeStr(const char *t)
{
    if (!t) return 4;
    if (!strcasecmp(t,"REAL") || !strcasecmp(t,"REALPTR")) return 8;
    if (!strcasecmp(t,"STRING"))                          return 8;
    return 4;
}

/* ---------- temp-byte accounting per function --------------------------- */
static int tmpBytesInFunc = 0;
static int resultSize(Node *e)
{
    if (!e) return 4;
    
    
    /* Fallback if type wasn't set - use token string */
    if (e->token) {
        if (!strcasecmp(e->token, "REAL") || !strcasecmp(e->token, "REALPTR")) return 8;
        if (!strcasecmp(e->token, "STRING")) return 8;
        if (strchr(e->token, '.') != NULL) return 8;  /* Real literal */
    }
    
    return 4; /* Default */
}
static char *tmpFor(Node *e){ tmpBytesInFunc+=resultSize(e); return newTmp(); }

/* ---------- forward declarations (mutual recursion) --------------------- */
static char *genExpr (Node *e);
static void  genStmt (Node *s);

/* ======================  EXPRESSION  ==================================== */
static int isLit(const char *tok)
{
    if (!tok) return 0;
    if (!strcmp(tok,"TRUE")||!strcmp(tok,"FALSE")||!strcmp(tok,"null")) return 1;
    
    // Check if it's a number
    char *ep; 
    strtod(tok,&ep); 
    return *ep=='\0';          /* number */
}
static const char *litVal(Node *n){ return n?n->token:"0"; }


static char *genOperand(Node *e)
{
    if (!e) return strdup("0");
    
    // Check if it's a literal
    if (isLit(e->token)) {
        return strdup(litVal(e));
    }
    
    // Check if it's a simple number literal that we might have missed
    char *endptr;
    strtod(e->token, &endptr);
    if (*endptr == '\0') {
        // It's a number literal
        return strdup(e->token);
    }
    
    // For identifiers, just return the name directly (semantic analysis already validated)
    if (e->left == NULL && e->right == NULL) {
        return strdup(e->token);
    }
    
    // Otherwise, generate a full expression
    return genExpr(e);
}
static char *genExpr(Node *e)
{
    if (!e) return strdup("0");

    printf("DEBUG: genExpr processing: %s\n", e->token);

    /* ---------- literals --------------------------------------------- */
    if (isLit(e->token)){
        char *t = tmpFor(e);
        if (!strcmp(e->token,"TRUE"))      emit("%s = 1", t);
        else if (!strcmp(e->token,"FALSE"))emit("%s = 0", t);
        else if (!strcmp(e->token,"null")) emit("%s = 0", t);
        else                               emit("%s = %s",t,litVal(e));
        return t;
    }
    
    /* ---------- check if it's a simple number literal --------------- */
    char *endptr;
    strtod(e->token, &endptr);
    if (*endptr == '\0') {
        // It's a number literal
        char *t = tmpFor(e);
        emit("%s = %s", t, e->token);
        return t;
    }
    
    if (symExists(e->token))                       /* plain variable   */
        return strdup(e->token);

    /* ---------- unary ops -------------------------------------------- */
    if (!strcmp(e->token,"unary-")){
        char *v = genExpr(e->left), *t = tmpFor(e);
        emit("%s = - %s", t, v); 
        free(v);
        return t;
    }
    if (!strcmp(e->token,"not")){
        char *v = genExpr(e->left), *t = tmpFor(e);
        emit("%s = ! %s", t, v); 
        free(v);
        return t;
    }
    if (!strcmp(e->token,"address")){
        char *v = genExpr(e->left), *t = tmpFor(e);
        emit("%s = & %s", t, v); 
        free(v);
        return t;
    }
    if (!strcmp(e->token,"dereference")){
        char *v = genExpr(e->left), *t = tmpFor(e);
        emit("%s = * %s", t, v); 
        free(v);
        return t;
    }

    /* ---------- binary ops (+,-,*,/,and,or,comp) --------------------- */
if (!strcmp(e->token,"+") || !strcmp(e->token,"-") || 
    !strcmp(e->token,"*") || !strcmp(e->token,"/") ||
    !strcmp(e->token,"and") || !strcmp(e->token,"or") ||
    !strcmp(e->token,"==") || !strcmp(e->token,"!=") ||
    !strcmp(e->token,"<") || !strcmp(e->token,">") ||
    !strcmp(e->token,"<=") || !strcmp(e->token,">=")){
    
    printf("DEBUG: Processing binary op '%s'\n", e->token);
    printf("DEBUG: Left operand: %s\n", e->left ? e->left->token : "NULL");
    printf("DEBUG: Right operand: %s\n", e->right ? e->right->token : "NULL");
    
    char *l = genOperand(e->left);
    char *r = genOperand(e->right);
    char *t = tmpFor(e);
    
    printf("DEBUG: Generated: %s = %s %s %s\n", t, l, e->token, r);
    emit("%s = %s %s %s", t, l, e->token, r);
    
    free(l);
    free(r);
    return t;
}

    /* ---------- array element  s[i] ---------------------------------- */
    if (!strcmp(e->token,"array_element")){
        char *base = genExpr(e->left);
        char *idx  = genExpr(e->right);
        char *t    = tmpFor(e);
        emit("%s = %s [ %s ]", t, base, idx);
        free(base);
        free(idx);
        return t;
    }

    /* ---------- function call ---------------------------------------- */
    if (!strcmp(e->token,"FUNC_CALL") || !strcmp(e->token,"CALL")){
        const char *fname = e->left->token;

        /* collect args into stack (reverse order push) */
        Node *stk[32]; 
        int top = 0;
        int bytes = 0;
        Node *args = e->right;
        
        printf("DEBUG: Processing function call to %s\n", fname);
        
        // Handle arguments - collect them first
        if (args) {
            printf("DEBUG: Function has arguments\n");
            if (!strcmp(args->token,"expr_list")){
                // Multiple arguments - traverse the list
                Node *p = args;
                while (p && !strcmp(p->token,"expr_list")) {
                    stk[top++] = p->left;
                    p = p->right;
                }
                if (p) stk[top++] = p; // Last argument
            } else {
                // Single argument
                stk[top++] = args;
            }
        }
        
        printf("DEBUG: Found %d arguments\n", top);
        
        // Push parameters in reverse order
        for (int i = top - 1; i >= 0; i--) {
            char *val = genExpr(stk[i]);
            emit("PushParam %s", val);
            bytes += resultSize(stk[i]);
            free(val);
        }
        
        char *ret = tmpFor(e);
        emit("%s = LCall %s", ret, fname);
        if (bytes) emit("PopParams %d", bytes);
        return ret;
    }

    /* fallback – treat as identifier */
    printf("DEBUG: Treating '%s' as identifier\n", e->token);
    return strdup(e->token);
}

/* ======================  STATEMENT  ===================================== */
static int isCmp(const char *t){ return !strcmp(t,"==")||!strcmp(t,"!=")||
                                        !strcmp(t,"<" )||!strcmp(t,">" )||
                                        !strcmp(t,"<=")||!strcmp(t,">="); }

static void genStmt(Node *s)
{
    if (!s) return;
    
    printf("DEBUG: genStmt processing node: %s\n", s->token);
    
    if (!strcmp(s->token,"statements")){
        genStmt(s->left); 
        genStmt(s->right); 
        return;
    }
    
    if (!strcmp(s->token,"empty_state_list")){
        return; // Skip empty statement lists
    }
    
    if (!strcmp(s->token,"STATEMENT")){
        genStmt(s->left); // Process the actual statement inside
        return;
    }

    /* ---------- assignments ----------------------------------------- */
    if (!strcmp(s->token,"assign")){
        char *rval = genExpr(s->right);
        emit("%s = %s", s->left->token, rval);
        return;
    }
    if (!strcmp(s->token,"pointer_assign")){
        emit("* %s = %s", genExpr(s->left), genExpr(s->right)); return;
    }
    if (!strcmp(s->token,"array_assign")){
        emit("%s [ %s ] = %s",
             s->left->token,
             genExpr(s->left->right),
             genExpr(s->right));
        return;
    }
    
    /* ---------- ASSIGNMENT (function call result) ------------------- */
    if (!strcmp(s->token,"ASSIGNMENT")){
        char *rval = genExpr(s->right);
        emit("%s = %s", s->left->token, rval);
        return;
    }

    /* ---------- return ---------------------------------------------- */
    if (!strcmp(s->token,"RETURN")){
        if (s->left) {
            char *retval = genExpr(s->left);
            emit("Return %s", retval);
        } else {
            emit("Return");
        }
        return;
    }

    /* ---------- bare function call as statement --------------------- */
    if (!strcmp(s->token,"FUNC_CALL")){ 
        genExpr(s); 
        return; 
    }

    /* ---------- IF / IF-ELSE ---------------------------------------- */
    if (!strcmp(s->token,"if")){
        char *Ltrue=newLabel(), *Lend=newLabel();
        Node *c=s->left;
        if (isCmp(c->token)){
            emit("if %s %s %s goto %s",
                 genOperand(c->left),c->token,genOperand(c->right),Ltrue);
            emit("goto %s", Lend);
        } else {
            emit("if %s == 0 goto %s", genExpr(c), Lend);
            emit("goto %s", Ltrue);
        }
        emit("%s:",Ltrue); 
        genStmt(s->right); 
        emit("%s:",Lend); 
        return;
    }
    if (!strcmp(s->token,"if-else")){
        Node *c=s->left;
        Node *then_part = s->right->left;      // then branch
        Node *else_part = s->right->right->left; // else branch
        
        char *Lthen=newLabel(), *Lelse=newLabel(), *Lend=newLabel();
        if (isCmp(c->token)){
            emit("if %s %s %s goto %s",
                 genOperand(c->left),c->token,genOperand(c->right),Lthen);
            emit("goto %s", Lelse);
        } else {
            emit("if %s != 0 goto %s", genExpr(c), Lthen);
            emit("goto %s", Lelse);
        }
        emit("%s:",Lthen); 
        genStmt(then_part); 
        emit("goto %s",Lend);
        emit("%s:",Lelse); 
        genStmt(else_part);  
        emit("%s:",Lend); 
        return;
    }

    /* ---------- WHILE ----------------------------------------------- */
    if (!strcmp(s->token,"while")){
        char *Lc=newLabel(), *Lb=newLabel(), *Le=newLabel();
        emit("%s:",Lc);
        Node *c=s->left;
        if (isCmp(c->token)){
            emit("if %s %s %s goto %s",
                 genOperand(c->left),c->token,genOperand(c->right),Lb);
            emit("goto %s", Le);
        } else {
            emit("if %s != 0 goto %s", genExpr(c), Lb);
            emit("goto %s", Le);
        }
        emit("%s:",Lb); 
        genStmt(s->right); 
        emit("goto %s",Lc);
        emit("%s:",Le); 
        return;
    }

    /* ---------- FOR -------------------------------------------------- */
    if (!strcmp(s->token,"for")){
        Node *hdr=s->left;
        Node *initVar  = hdr->left->left;
        Node *initExpr = hdr->left->right;
        Node *condExpr = hdr->right->left;
        Node *updExpr  = hdr->right->right;
        char *Lc=newLabel(), *Le=newLabel();
        emit("%s = %s", initVar->token, genExpr(initExpr));
        emit("%s:",Lc);
        emit("if %s == 0 goto %s", genExpr(condExpr), Le);
        genStmt(s->right);
        emit("%s = %s", updExpr->left->token, genExpr(updExpr->right));
        emit("goto %s", Lc); 
        emit("%s:",Le); 
        return;
    }

    /* ---------- BLOCK ------------------------------------------------ */
    if (!strcmp(s->token,"BLOCK")){ 
        genStmt(s->right); 
        return; 
    }
    
    printf("DEBUG: Unhandled statement type: %s\n", s->token);
}

/* ======================  FUNCTION & GLOBAL  ============================ */
static void patchBegin(TACInstr *beginLine,int bytes)
{
    char buf[16]; sprintf(buf,"%d",bytes);
    strcpy(beginLine->text+10,buf);      /* overwrite the '0' */
}

static void genFunction(Node *fn)
{
    if (!fn) return;          

    const char *fname = fn->left->token;
    if (!strcmp(fname,"_main_")) fname="main";

    emit("\n%s:",fname);
    emit("BeginFunc 0");
    TACInstr *beginLine = codeTail;
    tmpBytesInFunc = 0;

    printf("DEBUG: Processing function %s\n", fname);
    printf("DEBUG: Function node type: %s\n", fn->token);

    /* body = either BODY (…) or BODY inside DEF_BODY */
    Node *body = NULL;
    if (!strcmp(fn->token,"FUNCTION")) {
        // FUNC_PARTS → DEF_BODY → BODY
        Node *func_parts = fn->right;
        Node *def_body = func_parts->right;
        body = def_body->right;
    } else if (!strcmp(fn->token,"PROCEDURE")) {
        // PROC_PARTS → BODY  
        Node *proc_parts = fn->right;
        body = proc_parts->right;
    }

    if (!body) {
        printf("DEBUG: No body found for function %s\n", fname);
        emit("EndFunc");
        return;
    }

    printf("DEBUG: Body node type: %s\n", body->token);

    Node *varDecls = body->left;   // VAR_DECL nodes
    Node *stmts = body->right;     // statements

    printf("DEBUG: About to process statements\n");
    genStmt(stmts);

    int locals = 0;
    Node *decl = body ? body->left : NULL;
    if (decl && !strcmp(decl->token, "VAR_DECL")) {
        const char *type = decl->left->token;
        Node *items = decl->right;
        while (items) {
            if (!strcmp(items->token, "VAR_ITEM_LIST")) {
                Node *var = items->left;
                if (var && !strcmp(var->token, "VAR")) {
                    locals += sizeofTypeStr(type);
                }
                items = items->right;
            } else if (!strcmp(items->token, "VAR")) {
                locals += sizeofTypeStr(type);
                break;
            } else {
                break;
            }
        }
    }
    printf("DEBUG: %s --> locals = %d , temp = %d, total = %d\n", fname,locals,tmpBytesInFunc,tmpBytesInFunc+locals);
    patchBegin(beginLine, tmpBytesInFunc + locals);
    emit("EndFunc");
}

static void genGlobal(Node *n)
{
    if (!n) return;
    if (!strcmp(n->token,"Function_list")){
        genGlobal(n->left); 
        genGlobal(n->right); 
        return;
    }
    if (!strcmp(n->token,"FUNCTION") || !strcmp(n->token,"PROCEDURE")){
        genFunction(n);
    }
}

void generate_3ac(Node *root)
{
    codeHead=codeTail=NULL; tmpCnt=0; lblCnt=1;
    genGlobal(root);

    FILE *f = fopen("output.ac3","w");
    if (f){ dumpCode(f); fclose(f); }
    printf("3AC written to output.ac3\n");
}
/* ========================================================================== */





#line 756 "y.tab.c"

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
#line 687 "parser.y"

char *str;
struct Node *node;

#line 934 "y.tab.c"

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
  YYSYMBOL_function_item = 64,             /* function_item  */
  YYSYMBOL_main_function = 65,             /* main_function  */
  YYSYMBOL_66_1 = 66,                      /* $@1  */
  YYSYMBOL_67_2 = 67,                      /* $@2  */
  YYSYMBOL_function = 68,                  /* function  */
  YYSYMBOL_69_3 = 69,                      /* $@3  */
  YYSYMBOL_70_4 = 70,                      /* $@4  */
  YYSYMBOL_71_5 = 71,                      /* $@5  */
  YYSYMBOL_returns_spec = 72,              /* returns_spec  */
  YYSYMBOL_parameter_list = 73,            /* parameter_list  */
  YYSYMBOL_param_decl_list = 74,           /* param_decl_list  */
  YYSYMBOL_param_decl = 75,                /* param_decl  */
  YYSYMBOL_76_6 = 76,                      /* $@6  */
  YYSYMBOL_type = 77,                      /* type  */
  YYSYMBOL_opt_var = 78,                   /* opt_var  */
  YYSYMBOL_var_decl_list = 79,             /* var_decl_list  */
  YYSYMBOL_var_decl = 80,                  /* var_decl  */
  YYSYMBOL_81_7 = 81,                      /* $@7  */
  YYSYMBOL_var_item_list = 82,             /* var_item_list  */
  YYSYMBOL_var_item = 83,                  /* var_item  */
  YYSYMBOL_literal = 84,                   /* literal  */
  YYSYMBOL_stat_list = 85,                 /* stat_list  */
  YYSYMBOL_stat = 86,                      /* stat  */
  YYSYMBOL_call_stat = 87,                 /* call_stat  */
  YYSYMBOL_if_stat = 88,                   /* if_stat  */
  YYSYMBOL_while_stat = 89,                /* while_stat  */
  YYSYMBOL_do_while_stat = 90,             /* do_while_stat  */
  YYSYMBOL_for_stat = 91,                  /* for_stat  */
  YYSYMBOL_for_header = 92,                /* for_header  */
  YYSYMBOL_update_exp = 93,                /* update_exp  */
  YYSYMBOL_block_stat = 94,                /* block_stat  */
  YYSYMBOL_95_8 = 95,                      /* $@8  */
  YYSYMBOL_single_statement = 96,          /* single_statement  */
  YYSYMBOL_assignment_stat = 97,           /* assignment_stat  */
  YYSYMBOL_return_stat = 98,               /* return_stat  */
  YYSYMBOL_expression_list = 99,           /* expression_list  */
  YYSYMBOL_expression = 100                /* expression  */
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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   503

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  221

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
       0,   714,   714,   721,   722,   724,   725,   728,   732,   727,
     762,   767,   780,   761,   811,   816,   822,   825,   827,   828,
     831,   830,   846,   847,   848,   849,   850,   851,   852,   853,
     856,   859,   861,   862,   865,   864,   873,   874,   877,   884,
     893,   902,   913,   914,   915,   916,   917,   918,   919,   920,
     923,   926,   929,   930,   931,   932,   933,   934,   935,   936,
     938,   956,   969,   972,   975,   979,   984,   988,   992,   995,
    1003,  1018,  1018,  1029,  1035,  1039,  1048,  1057,  1069,  1071,
    1075,  1078,  1079,  1082,  1083,  1084,  1085,  1086,  1087,  1088,
    1089,  1090,  1091,  1092,  1093,  1094,  1095,  1096,  1103,  1113,
    1115,  1122,  1123,  1130,  1140
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
  "function_list", "function_item", "main_function", "$@1", "$@2",
  "function", "$@3", "$@4", "$@5", "returns_spec", "parameter_list",
  "param_decl_list", "param_decl", "$@6", "type", "opt_var",
  "var_decl_list", "var_decl", "$@7", "var_item_list", "var_item",
  "literal", "stat_list", "stat", "call_stat", "if_stat", "while_stat",
  "do_while_stat", "for_stat", "for_header", "update_exp", "block_stat",
  "$@8", "single_statement", "assignment_stat", "return_stat",
  "expression_list", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-111)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-51)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      12,    19,    89,    12,  -111,  -111,  -111,    45,    46,  -111,
    -111,  -111,  -111,    77,    77,  -111,    47,    54,  -111,    50,
     163,  -111,    77,  -111,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,    56,    57,  -111,    58,    44,    82,    88,  -111,
     163,  -111,    97,    84,  -111,    88,   163,    97,  -111,    -7,
      86,    67,  -111,   160,   160,    66,    96,    71,    59,    61,
      62,   -15,  -111,    93,    -7,  -111,  -111,  -111,  -111,  -111,
    -111,    88,  -111,  -111,  -111,    -7,  -111,  -111,   160,   160,
     160,    63,    64,   160,  -111,  -111,  -111,  -111,  -111,  -111,
    -111,    75,  -111,   285,   301,    69,    85,  -111,   333,   -12,
      78,    99,   137,   160,  -111,  -111,   108,   110,    73,    21,
      21,    21,    90,   100,   253,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   -12,   -12,
     114,   -12,  -111,    -2,   126,   160,   160,    87,   348,   193,
      -7,  -111,   -37,   -21,  -111,   160,  -111,  -111,   213,    21,
     452,  -111,   463,    51,    51,    51,    51,   -19,   463,   -19,
    -111,    32,  -111,   160,  -111,   160,   160,    98,   271,   363,
     111,  -111,   125,   134,   -14,   104,  -111,    73,   233,  -111,
     160,   117,   378,   393,   119,   160,  -111,   160,   160,  -111,
    -111,   124,  -111,  -111,   317,   -12,   160,  -111,  -111,  -111,
     127,   408,   138,   -12,  -111,   423,   140,  -111,   129,   167,
     128,  -111,  -111,   142,   168,   149,   -12,   160,  -111,  -111,
     438
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     4,     6,     5,     0,     0,     1,
       3,    10,     7,    16,    16,    20,     0,    17,    18,     0,
       0,    11,     0,     8,    23,    24,    22,    25,    26,    27,
      28,    29,     0,     0,    19,     0,     0,    15,    30,    21,
       0,    12,     0,     0,    14,    30,     0,    31,    32,    71,
       0,     0,    33,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    52,     0,    71,    59,    53,    54,    56,    55,
      57,    30,    73,    74,    58,    71,    34,    49,     0,     0,
       0,     0,     0,     0,    43,    44,    45,    46,    42,    47,
      48,   102,   104,     0,     0,     0,     0,    79,     0,    71,
       0,     0,     0,     0,     9,    51,     0,     0,     0,    95,
      96,    99,    97,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    71,    71,
       0,    71,    78,     0,     0,    80,     0,     0,     0,     0,
      71,    13,    38,     0,    36,     0,   100,   101,     0,    87,
      88,    86,    89,    91,    92,    93,    94,    84,    90,    83,
      85,    62,    66,     0,    68,     0,     0,     0,    81,     0,
       0,    75,     0,     0,     0,     0,    35,     0,     0,   103,
       0,     0,     0,     0,     0,    80,    76,    80,     0,    72,
      39,     0,    37,    98,     0,    71,     0,    67,    61,    82,
       0,     0,    40,    71,    63,     0,     0,    77,     0,    64,
       0,    60,    41,     0,     0,     0,    71,     0,    69,    65,
      70
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -111,  -111,  -111,   200,  -111,  -111,  -111,    20,  -111,  -111,
    -111,  -111,   190,  -111,   183,  -111,    36,   -35,  -111,   159,
    -111,  -111,    30,    35,   -60,  -111,  -111,  -111,  -111,  -111,
    -111,  -111,  -111,   -97,  -111,  -111,  -111,  -111,  -110,   -53
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,     5,    14,    35,    62,    13,    33,
      45,    41,    16,    17,    18,    20,    32,    43,    47,    48,
     108,   143,   144,    92,    63,    64,    65,    66,    67,    68,
      69,    96,   215,    70,    71,    72,    73,    74,   167,   168
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      93,    94,   134,    98,   105,    53,    77,   174,    54,    55,
      50,   118,    56,   175,    57,   107,   102,   -50,    58,    59,
       6,   127,   176,     6,   177,   109,   110,   111,    60,   165,
     114,   161,   162,    60,   164,   103,   106,     1,    84,    85,
      86,    87,    88,    89,    90,   180,   181,   133,   103,   138,
     139,   118,    61,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   199,    44,   200,     7,     8,
     173,   118,    51,   169,   -51,   -51,   -51,   -51,   124,     9,
     126,   127,   178,    11,    12,    15,    21,    22,   204,    23,
      36,    37,    38,    39,    40,    42,   209,    49,    46,    75,
     182,    76,   138,   183,    95,    99,    77,   104,     7,   219,
     100,   101,   112,   113,    78,   115,   135,   194,   130,   131,
     136,   140,   142,    79,   141,   201,    80,    81,    82,    97,
     145,   166,   146,   205,    83,   163,   170,   184,    84,    85,
      86,    87,    88,    89,    90,    91,   188,    77,   189,   187,
     191,   195,   198,   137,   220,    78,    24,    25,    26,    27,
      28,    29,    30,    31,    79,   202,   206,    80,    81,    82,
      77,   213,   208,   211,   212,    83,   216,   214,    78,    84,
      85,    86,    87,    88,    89,    90,    91,    79,   218,   217,
      80,    81,    82,    10,    19,    34,    52,   192,    83,   190,
       0,     0,    84,    85,    86,    87,    88,    89,    90,    91,
     116,     0,   117,   118,     0,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,     0,     0,     0,     0,     0,
     116,     0,   117,   118,   172,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,     0,     0,     0,     0,     0,
     116,     0,   117,   118,   179,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,     0,     0,     0,     0,     0,
     116,     0,   117,   118,   193,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,     0,     0,     0,   116,     0,
     117,   118,   147,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   116,     0,   117,   118,   185,   119,   120,   121,
     122,   123,   124,   125,   126,   127,     0,     0,   116,   128,
     117,   118,     0,   119,   120,   121,   122,   123,   124,   125,
     126,   127,     0,     0,   116,   129,   117,   118,     0,   119,
     120,   121,   122,   123,   124,   125,   126,   127,     0,     0,
     116,   203,   117,   118,     0,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,   116,   132,   117,   118,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,     0,
     116,   171,   117,   118,     0,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,   116,   186,   117,   118,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,     0,
     116,   196,   117,   118,     0,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,   116,   197,   117,   118,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,     0,
     116,   207,   117,   118,     0,   119,   120,   121,   122,   123,
     124,   125,   126,   127,     0,   116,   210,   117,   118,     0,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   116,
       0,     0,   118,     0,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   118,     0,   -51,   120,   121,   122,   123,
     124,   -51,   126,   127
};

static const yytype_int16 yycheck[] =
{
      53,    54,    99,    56,    64,    12,    20,    44,    15,    16,
      45,    30,    19,    50,    21,    75,    31,    24,    25,    26,
       0,    40,    43,     3,    45,    78,    79,    80,    40,    31,
      83,   128,   129,    40,   131,    50,    71,    25,    52,    53,
      54,    55,    56,    57,    58,    13,    14,    59,    50,   102,
     103,    30,    59,    32,    33,    34,    35,    36,    37,    38,
      39,    40,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   185,    40,   187,    59,    60,
     140,    30,    46,   136,    33,    34,    35,    36,    37,     0,
      39,    40,   145,    48,    48,    18,    49,    43,   195,    49,
      44,    44,    44,    59,    22,    17,   203,    23,    11,    23,
     163,    44,   165,   166,    48,    44,    20,    24,    59,   216,
      59,    59,    59,    59,    28,    50,    48,   180,    59,    44,
      31,    23,    59,    37,    24,   188,    40,    41,    42,    43,
      50,    15,    42,   196,    48,    31,    59,    49,    52,    53,
      54,    55,    56,    57,    58,    59,    31,    20,    24,    48,
      56,    44,    43,    26,   217,    28,     3,     4,     5,     6,
       7,     8,     9,    10,    37,    51,    49,    40,    41,    42,
      20,    14,    44,    43,    55,    48,    44,    59,    28,    52,
      53,    54,    55,    56,    57,    58,    59,    37,    49,    31,
      40,    41,    42,     3,    14,    22,    47,   177,    48,   174,
      -1,    -1,    52,    53,    54,    55,    56,    57,    58,    59,
      27,    -1,    29,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    29,    30,    51,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    29,    30,    51,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    29,    30,    51,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    -1,    27,    -1,
      29,    30,    49,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    27,    -1,    29,    30,    45,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    -1,    -1,    27,    44,
      29,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    -1,    27,    44,    29,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    -1,
      27,    44,    29,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    27,    43,    29,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      27,    43,    29,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    27,    43,    29,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      27,    43,    29,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    27,    43,    29,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    -1,
      27,    43,    29,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    27,    43,    29,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    27,
      -1,    -1,    30,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    25,    62,    63,    64,    65,    68,    59,    60,     0,
      64,    48,    48,    69,    66,    18,    73,    74,    75,    73,
      76,    49,    43,    49,     3,     4,     5,     6,     7,     8,
       9,    10,    77,    70,    75,    67,    44,    44,    44,    59,
      22,    72,    17,    78,    77,    71,    11,    79,    80,    23,
      78,    77,    80,    12,    15,    16,    19,    21,    25,    26,
      40,    59,    68,    85,    86,    87,    88,    89,    90,    91,
      94,    95,    96,    97,    98,    23,    44,    20,    28,    37,
      40,    41,    42,    48,    52,    53,    54,    55,    56,    57,
      58,    59,    84,   100,   100,    48,    92,    43,   100,    44,
      59,    59,    31,    50,    24,    85,    78,    85,    81,   100,
     100,   100,    59,    59,   100,    50,    27,    29,    30,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    44,    44,
      59,    44,    43,    59,    94,    48,    31,    26,   100,   100,
      23,    24,    59,    82,    83,    50,    42,    49,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,    94,    94,    31,    94,    31,    15,    99,   100,   100,
      59,    43,    51,    85,    44,    50,    43,    45,   100,    51,
      13,    14,   100,   100,    49,    45,    43,    48,    31,    24,
      84,    56,    83,    51,   100,    44,    43,    43,    43,    99,
      99,   100,    51,    44,    94,   100,    49,    43,    44,    94,
      43,    43,    55,    14,    59,    93,    44,    31,    49,    94,
     100
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    61,    62,    63,    63,    64,    64,    66,    67,    65,
      69,    70,    71,    68,    72,    72,    73,    73,    74,    74,
      76,    75,    77,    77,    77,    77,    77,    77,    77,    77,
      78,    78,    79,    79,    81,    80,    82,    82,    83,    83,
      83,    83,    84,    84,    84,    84,    84,    84,    84,    84,
      85,    85,    86,    86,    86,    86,    86,    86,    86,    86,
      87,    87,    88,    88,    88,    88,    89,    90,    91,    92,
      93,    95,    94,    94,    96,    97,    97,    97,    98,    98,
      99,    99,    99,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     0,     0,    12,
       0,     0,     0,    14,     2,     0,     0,     1,     1,     3,
       0,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     2,     1,     2,     0,     6,     1,     3,     1,     3,
       4,     6,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       8,     6,     4,     7,     8,    11,     4,     6,     4,     9,
       3,     0,     5,     1,     1,     4,     5,     7,     3,     2,
       0,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     5,     2,
       3,     3,     1,     4,     1
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
#line 715 "parser.y"
{
    (yyval.node) = (yyvsp[0].node);
    ast_root=(yyval.node);
    printtree((yyval.node), 0);
}
#line 2226 "y.tab.c"
    break;

  case 3: /* function_list: function_list function_item  */
#line 721 "parser.y"
                                            { (yyval.node) = mkNode("Function_list", (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2232 "y.tab.c"
    break;

  case 4: /* function_list: function_item  */
#line 722 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2238 "y.tab.c"
    break;

  case 5: /* function_item: function  */
#line 724 "parser.y"
                         {(yyval.node)=(yyvsp[0].node);}
#line 2244 "y.tab.c"
    break;

  case 6: /* function_item: main_function  */
#line 725 "parser.y"
                                {(yyval.node)=(yyvsp[0].node);}
#line 2250 "y.tab.c"
    break;

  case 7: /* $@1: %empty  */
#line 728 "parser.y"
{
    expected_param_num = 1;
}
#line 2258 "y.tab.c"
    break;

  case 8: /* $@2: %empty  */
#line 732 "parser.y"
{

    if(has_main)
    {
        semantic_error("Multiply definitions of '_main_' function are not allowed",(yyvsp[-4].str));
    }
    has_main=1;

    if(count_parameters((yyvsp[-1].node))!=0){
        semantic_error("_main_ procedure must not accept any parameters",(yyvsp[-4].str));
    }
    add_function("_main_",TYPE_VOID,0,NULL);

    enter_scope();
}
#line 2278 "y.tab.c"
    break;

  case 9: /* main_function: DEF MAIN_FUNC OPENPAREN $@1 parameter_list CLOSEPAREN $@2 COLON opt_var BEGIN_T stat_list END  */
#line 748 "parser.y"
{
    push_return(TYPE_VOID);

    /* create nodes for readability */
    Node *idnode = mkNode("_main_", NULL, NULL);
    Node *parametersnodes = mkNode("PARAMETERS", (yyvsp[-7].node), NULL);
    Node *bodynode = mkNode("BODY", (yyvsp[-3].node), (yyvsp[-1].node));
    (yyval.node) = mkNode("PROCEDURE", idnode, mkNode("PROC_PARTS", parametersnodes, bodynode));
    print_symbol_table();
    pop_return();
    exit_scope();
}
#line 2295 "y.tab.c"
    break;

  case 10: /* $@3: %empty  */
#line 762 "parser.y"
        {
            expected_param_num = 1;
            // Common code from both $@3 and $@5 actions
        }
#line 2304 "y.tab.c"
    break;

  case 11: /* $@4: %empty  */
#line 767 "parser.y"
        {
            if(find_symbol_in_scope((yyvsp[-4].str),current_scope)){
                semantic_error("Function with the same name already exists in the current scope",(yyvsp[-4].str));
            }
            printf("DEBUG: Entering function definition for '%s'\n", (yyvsp[-4].str));

            DataType *param_types=NULL;
            int param_count=0;
            extract_param_types((yyvsp[-1].node),&param_types,&param_count);
            add_function((yyvsp[-4].str), TYPE_VOID, param_count, param_types);
        }
#line 2320 "y.tab.c"
    break;

  case 12: /* $@5: %empty  */
#line 780 "parser.y"
        {
            // Store return type
            Symbol *f = find_function((yyvsp[-7].str));
            if(f) f->return_type = get_type_from_string((yyvsp[0].node)->token);
            
            // Enter scope for function body
            enter_scope();
            
            // Add parameters to scope
            DataType *param_types=NULL;
            int param_count=0;
            extract_param_types((yyvsp[-4].node),&param_types,&param_count);
            add_parameters_to_scope((yyvsp[-4].node),param_types,param_count);
        }
#line 2339 "y.tab.c"
    break;

  case 13: /* function: DEF ID OPENPAREN $@3 parameter_list CLOSEPAREN $@4 COLON returns_spec $@5 opt_var BEGIN_T stat_list END  */
#line 795 "parser.y"
        {
            /* create nodes for readability */
            Node *idnode = mkNode((yyvsp[-12].str), NULL, NULL);
            Node *parametersnodes = mkNode("PARAMETERS", (yyvsp[-9].node), NULL);
            Node *returnsnode = mkNode("RETURNS", (yyvsp[-5].node), NULL);
            Node *body_statements = mkNode("statements", (yyvsp[-1].node), NULL);
            Node *bodynode = mkNode("BODY", (yyvsp[-3].node), body_statements);
            Node *defbody = mkNode("DEF_BODY", returnsnode, bodynode);
            (yyval.node) = mkNode("FUNCTION", idnode, mkNode("FUNC_PARTS", parametersnodes, defbody));
            
            print_symbol_table();
            pop_return();
            exit_scope();
        }
#line 2358 "y.tab.c"
    break;

  case 14: /* returns_spec: RETURNS type  */
#line 811 "parser.y"
                            {
                if(strcmp((yyvsp[0].node)->token, "STRING") == 0){
                    semantic_error("Return type of a function cannot be STRING", (yyvsp[0].node)->token);}
                push_return(get_type_from_string((yyvsp[0].node)->token));
                (yyval.node) = (yyvsp[0].node);}
#line 2368 "y.tab.c"
    break;

  case 15: /* returns_spec: %empty  */
#line 816 "parser.y"
                  {
                    push_return(TYPE_VOID); 
                    (yyval.node)=mkNode("RETURN VOID",NULL,NULL);}
#line 2376 "y.tab.c"
    break;

  case 16: /* parameter_list: %empty  */
#line 822 "parser.y"
{
    (yyval.node) = mkNode("PARAM_EMPTY", NULL, NULL);
}
#line 2384 "y.tab.c"
    break;

  case 17: /* parameter_list: param_decl_list  */
#line 825 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2390 "y.tab.c"
    break;

  case 18: /* param_decl_list: param_decl  */
#line 827 "parser.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 2396 "y.tab.c"
    break;

  case 19: /* param_decl_list: param_decl_list SEMICOLON param_decl  */
#line 828 "parser.y"
                                       { (yyval.node) = mkNode("PARAMS_LIST", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2402 "y.tab.c"
    break;

  case 20: /* $@6: %empty  */
#line 831 "parser.y"
{
    int param_num = 0;
    sscanf((yyvsp[0].str),"par%d", &param_num);

    
    if (param_num != expected_param_num) {
        char msg[120];
        sprintf(msg, "Parameters must be ordered sequentially (par1, par2, ...). Expected par%d but found %s", expected_param_num, (yyvsp[0].str));
        semantic_error(msg, (yyvsp[0].str));
        }
    expected_param_num = param_num+1;
}
#line 2419 "y.tab.c"
    break;

  case 21: /* param_decl: PAR $@6 type COLON ID  */
#line 844 "parser.y"
              { (yyval.node) = mkNode("PARAM", (yyvsp[-2].node), mkNode((yyvsp[0].str), NULL, NULL)); }
#line 2425 "y.tab.c"
    break;

  case 22: /* type: INT  */
#line 846 "parser.y"
           { (yyval.node) = mkNode("INT", NULL, NULL); }
#line 2431 "y.tab.c"
    break;

  case 23: /* type: BOOL  */
#line 847 "parser.y"
       { (yyval.node) = mkNode("BOOL", NULL, NULL); }
#line 2437 "y.tab.c"
    break;

  case 24: /* type: CHAR  */
#line 848 "parser.y"
       { (yyval.node) = mkNode("CHAR", NULL, NULL); }
#line 2443 "y.tab.c"
    break;

  case 25: /* type: REAL  */
#line 849 "parser.y"
       { (yyval.node) = mkNode("REAL", NULL, NULL); }
#line 2449 "y.tab.c"
    break;

  case 26: /* type: STRING  */
#line 850 "parser.y"
         { (yyval.node) = mkNode("STRING", NULL, NULL); }
#line 2455 "y.tab.c"
    break;

  case 27: /* type: INTPTR  */
#line 851 "parser.y"
         { (yyval.node) = mkNode("INTPTR", NULL, NULL); }
#line 2461 "y.tab.c"
    break;

  case 28: /* type: CHARPTR  */
#line 852 "parser.y"
          { (yyval.node) = mkNode("CHARPTR", NULL, NULL); }
#line 2467 "y.tab.c"
    break;

  case 29: /* type: REALPTR  */
#line 853 "parser.y"
          { (yyval.node) = mkNode("REALPTR", NULL, NULL); }
#line 2473 "y.tab.c"
    break;

  case 30: /* opt_var: %empty  */
#line 856 "parser.y"
{
    (yyval.node) = mkNode("VAR_EMPTY", NULL, NULL);
}
#line 2481 "y.tab.c"
    break;

  case 31: /* opt_var: VAR var_decl_list  */
#line 859 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2487 "y.tab.c"
    break;

  case 32: /* var_decl_list: var_decl  */
#line 861 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2493 "y.tab.c"
    break;

  case 33: /* var_decl_list: var_decl_list var_decl  */
#line 862 "parser.y"
                         { (yyval.node) = mkNode("VAR_DECL", (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2499 "y.tab.c"
    break;

  case 34: /* $@7: %empty  */
#line 865 "parser.y"
        {
            current_var_type=get_type_from_string((yyvsp[-1].node)->token);
        }
#line 2507 "y.tab.c"
    break;

  case 35: /* var_decl: TYPE type COLON $@7 var_item_list SEMICOLON  */
#line 869 "parser.y"
{
    current_var_type=TYPE_INVALID;
     (yyval.node) = mkNode("VAR_DECL", (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 2515 "y.tab.c"
    break;

  case 36: /* var_item_list: var_item  */
#line 873 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2521 "y.tab.c"
    break;

  case 37: /* var_item_list: var_item_list COMMA var_item  */
#line 874 "parser.y"
                               { (yyval.node) = mkNode("VAR_ITEM_LIST", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2527 "y.tab.c"
    break;

  case 38: /* var_item: ID  */
#line 877 "parser.y"
    { 
        if(find_symbol_in_scope((yyvsp[0].str),current_scope)){
            semantic_error("Variable already defined in the current scope",(yyvsp[0].str));
        }
        add_symbol((yyvsp[0].str),current_var_type,KIND_VARIABLE);
    
        (yyval.node) = mkNode("VAR", mkNode((yyvsp[0].str), NULL, NULL), NULL); }
#line 2539 "y.tab.c"
    break;

  case 39: /* var_item: ID COLON literal  */
#line 885 "parser.y"
{   
    if(find_symbol_in_scope((yyvsp[-2].str),current_scope)){
        semantic_error("Variable already defined in the current scope",(yyvsp[-2].str));
    }
    DataType lit_type=get_expression_type((yyvsp[0].node));
    add_symbol((yyvsp[-2].str),lit_type,KIND_VARIABLE);

    (yyval.node) = mkNode("VAR_ASSIGN", mkNode((yyvsp[-2].str), NULL, NULL), (yyvsp[0].node)); }
#line 2552 "y.tab.c"
    break;

  case 40: /* var_item: ID OPENBRACKET DEC_LIT CLOSEBRACKET  */
#line 894 "parser.y"
{
    if(find_symbol_in_scope((yyvsp[-3].str),current_scope)){
        semantic_error("Variable already defined in the current scope",(yyvsp[-3].str));
    }
    add_symbol((yyvsp[-3].str),TYPE_STRING,KIND_VARIABLE);

    (yyval.node) = mkNode("STRING_VAR", mkNode((yyvsp[-3].str), NULL, NULL), mkNode((yyvsp[-1].str), NULL, NULL));
}
#line 2565 "y.tab.c"
    break;

  case 41: /* var_item: ID OPENBRACKET DEC_LIT CLOSEBRACKET COLON STRING_LIT  */
#line 903 "parser.y"
{
    if(find_symbol_in_scope((yyvsp[-5].str),current_scope)){
        semantic_error("Variable already defined in the current scope",(yyvsp[-5].str));
    }
    add_symbol((yyvsp[-5].str),TYPE_STRING,KIND_VARIABLE);

    (yyval.node) = mkNode("STRING_VAL_ASSIGN", mkNode("STRING_VAR", mkNode((yyvsp[-5].str), NULL, NULL), mkNode((yyvsp[-3].str), NULL, NULL)),
                mkNode((yyvsp[0].str), NULL, NULL));
}
#line 2579 "y.tab.c"
    break;

  case 42: /* literal: DEC_LIT  */
#line 913 "parser.y"
                  { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 2585 "y.tab.c"
    break;

  case 43: /* literal: B_TRUE  */
#line 914 "parser.y"
         { (yyval.node) = mkNode("TRUE", NULL, NULL); }
#line 2591 "y.tab.c"
    break;

  case 44: /* literal: B_FALSE  */
#line 915 "parser.y"
          { (yyval.node) = mkNode("FALSE", NULL, NULL); }
#line 2597 "y.tab.c"
    break;

  case 45: /* literal: CHAR_LIT  */
#line 916 "parser.y"
           { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 2603 "y.tab.c"
    break;

  case 46: /* literal: STRING_LIT  */
#line 917 "parser.y"
             { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 2609 "y.tab.c"
    break;

  case 47: /* literal: HEX_LIT  */
#line 918 "parser.y"
          { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 2615 "y.tab.c"
    break;

  case 48: /* literal: REAL_LIT  */
#line 919 "parser.y"
           { (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 2621 "y.tab.c"
    break;

  case 49: /* literal: NULLL  */
#line 920 "parser.y"
        { (yyval.node) = mkNode("null", NULL, NULL); }
#line 2627 "y.tab.c"
    break;

  case 50: /* stat_list: %empty  */
#line 923 "parser.y"
{
    (yyval.node) = mkNode("empty_state_list", NULL, NULL);
}
#line 2635 "y.tab.c"
    break;

  case 51: /* stat_list: stat stat_list  */
#line 926 "parser.y"
                 { (yyval.node) = mkNode("statements", (yyvsp[-1].node), (yyvsp[0].node)); }
#line 2641 "y.tab.c"
    break;

  case 52: /* stat: function  */
#line 929 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2647 "y.tab.c"
    break;

  case 53: /* stat: if_stat  */
#line 930 "parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 2653 "y.tab.c"
    break;

  case 54: /* stat: while_stat  */
#line 931 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2659 "y.tab.c"
    break;

  case 55: /* stat: for_stat  */
#line 932 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2665 "y.tab.c"
    break;

  case 56: /* stat: do_while_stat  */
#line 933 "parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 2671 "y.tab.c"
    break;

  case 57: /* stat: block_stat  */
#line 934 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2677 "y.tab.c"
    break;

  case 58: /* stat: return_stat  */
#line 935 "parser.y"
              {(yyval.node) = (yyvsp[0].node);}
#line 2683 "y.tab.c"
    break;

  case 59: /* stat: call_stat  */
#line 936 "parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 2689 "y.tab.c"
    break;

  case 60: /* call_stat: ID ASSIGNMENT CALL ID OPENPAREN expression_list CLOSEPAREN SEMICOLON  */
#line 939 "parser.y"
{
    Symbol *func=find_function((yyvsp[-4].str));
    Symbol *var=find_symbol((yyvsp[-7].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-7].str));
    }
    if(!func){
        semantic_error("Function called before it was defined or does not exist.",(yyvsp[-4].str));
    }
    verify_argument_type((yyvsp[-2].node), func);
    if (func->return_type == TYPE_VOID) {
        semantic_error("Cannot assign the result of a VOID procedure",
                       func->name);
    }
    check_type_compatibility(var->type, func->return_type, "function-call assignment");
    (yyval.node) = mkNode("ASSIGNMENT", mkNode((yyvsp[-7].str), NULL, NULL), mkNode("CALL", mkNode((yyvsp[-4].str), NULL, NULL), (yyvsp[-2].node)));
}
#line 2711 "y.tab.c"
    break;

  case 61: /* call_stat: CALL ID OPENPAREN expression_list CLOSEPAREN SEMICOLON  */
#line 957 "parser.y"
{
    Symbol *func=find_function((yyvsp[-4].str));
    if(!func){
        semantic_error("Function called before it was defined or does not exist.",(yyvsp[-4].str));
    }
    verify_argument_type((yyvsp[-2].node), func);
    (yyval.node) = mkNode("FUNC_CALL", mkNode((yyvsp[-4].str), NULL, NULL), (yyvsp[-2].node));
}
#line 2724 "y.tab.c"
    break;

  case 62: /* if_stat: IF expression COLON block_stat  */
#line 969 "parser.y"
                                         { 
    verify_bool((yyvsp[-2].node), "IF statement");    
    (yyval.node) = mkNode("if", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2732 "y.tab.c"
    break;

  case 63: /* if_stat: IF expression COLON block_stat ELSE COLON block_stat  */
#line 972 "parser.y"
                                                       { 
    verify_bool((yyvsp[-5].node), "IF statement");    
    (yyval.node) = mkNode("if-else", (yyvsp[-5].node), mkNode("then", (yyvsp[-3].node), mkNode("else", (yyvsp[0].node), NULL))); }
#line 2740 "y.tab.c"
    break;

  case 64: /* if_stat: IF expression COLON block_stat ELIF expression COLON block_stat  */
#line 975 "parser.y"
                                                                  { 
    verify_bool((yyvsp[-6].node), "IF statement");    
    verify_bool((yyvsp[-2].node), "IF statement");    
    (yyval.node) = mkNode("if-elif", (yyvsp[-6].node), mkNode("then", (yyvsp[-4].node), mkNode("elif-cond", (yyvsp[-2].node), (yyvsp[0].node)))); }
#line 2749 "y.tab.c"
    break;

  case 65: /* if_stat: IF expression COLON block_stat ELIF expression COLON block_stat ELSE COLON block_stat  */
#line 979 "parser.y"
                                                                                        { 
    verify_bool((yyvsp[-9].node), "IF statement");    
    verify_bool((yyvsp[-5].node), "IF statement");    
    (yyval.node) = mkNode("if-elif-else", (yyvsp[-9].node), mkNode("then", (yyvsp[-7].node), mkNode("elif-cond", (yyvsp[-5].node), mkNode("elif-then", (yyvsp[-3].node), mkNode("else", (yyvsp[0].node), NULL))))); }
#line 2758 "y.tab.c"
    break;

  case 66: /* while_stat: WHILE expression COLON block_stat  */
#line 984 "parser.y"
                                               { 
    verify_bool((yyvsp[-2].node), "WHILE statement");    
    (yyval.node) = mkNode("while", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2766 "y.tab.c"
    break;

  case 67: /* do_while_stat: DO COLON block_stat WHILE expression SEMICOLON  */
#line 988 "parser.y"
                                                               { 
    verify_bool((yyvsp[-1].node), "DO-WHILE statement");    
    (yyval.node) = mkNode("do-while", (yyvsp[-3].node), mkNode("cond", (yyvsp[-1].node), NULL)); }
#line 2774 "y.tab.c"
    break;

  case 68: /* for_stat: FOR for_header COLON block_stat  */
#line 992 "parser.y"
                                           { (yyval.node) = mkNode("for", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2780 "y.tab.c"
    break;

  case 69: /* for_header: OPENPAREN ID ASSIGNMENT expression SEMICOLON expression SEMICOLON update_exp CLOSEPAREN  */
#line 996 "parser.y"
{
    verify_assignment(mkNode((yyvsp[-7].str),NULL,NULL), (yyvsp[-5].node));
    verify_bool((yyvsp[-3].node), "FOR statement");    
    (yyval.node) = mkNode("for-header", mkNode("init", mkNode((yyvsp[-7].str), NULL, NULL), (yyvsp[-5].node)),
                mkNode("loop", (yyvsp[-3].node), (yyvsp[-1].node)));
}
#line 2791 "y.tab.c"
    break;

  case 70: /* update_exp: ID ASSIGNMENT expression  */
#line 1003 "parser.y"
                                      {
    verify_assignment(mkNode((yyvsp[-2].str),NULL,NULL), (yyvsp[0].node));
    (yyval.node) = mkNode("update", mkNode((yyvsp[-2].str), NULL, NULL), (yyvsp[0].node)); }
#line 2799 "y.tab.c"
    break;

  case 71: /* $@8: %empty  */
#line 1018 "parser.y"
           {
               /* Enter new scope before processing opt_var */
               enter_scope();
           }
#line 2808 "y.tab.c"
    break;

  case 72: /* block_stat: $@8 opt_var BEGIN_T stat_list END  */
#line 1023 "parser.y"
           {
               /* Exit scope when block ends */
               
               (yyval.node) = mkNode("BLOCK", (yyvsp[-3].node), (yyvsp[-1].node));
               exit_scope();
           }
#line 2819 "y.tab.c"
    break;

  case 73: /* block_stat: single_statement  */
#line 1030 "parser.y"
          {
               (yyval.node) = (yyvsp[0].node);
          }
#line 2827 "y.tab.c"
    break;

  case 74: /* single_statement: assignment_stat  */
#line 1035 "parser.y"
                                  { (yyval.node) = mkNode("STATEMENT", (yyvsp[0].node), NULL); }
#line 2833 "y.tab.c"
    break;

  case 75: /* assignment_stat: ID ASSIGNMENT expression SEMICOLON  */
#line 1040 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[-3].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-3].str));
    }
    verify_assignment(mkNode((yyvsp[-3].str),NULL,NULL), (yyvsp[-1].node));
    (yyval.node) = mkNode("assign", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node)); 
}
#line 2846 "y.tab.c"
    break;

  case 76: /* assignment_stat: MULTI ID ASSIGNMENT expression SEMICOLON  */
#line 1049 "parser.y"
{ 
    Symbol *var=find_symbol((yyvsp[-3].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-3].str));
    }
    Node *point   = mkNode("dereference", mkNode((yyvsp[-3].str),NULL,NULL), NULL);
    verify_assignment(point, (yyvsp[-1].node));
    (yyval.node) = mkNode("pointer_assign", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node)); }
#line 2859 "y.tab.c"
    break;

  case 77: /* assignment_stat: ID OPENBRACKET expression CLOSEBRACKET ASSIGNMENT expression SEMICOLON  */
#line 1058 "parser.y"
{
    verify_string_index(mkNode((yyvsp[-6].str),NULL,NULL), (yyvsp[-4].node));
    Symbol *var=find_symbol((yyvsp[-6].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-6].str));
    }
     verify_assignment(mkNode("array_element", mkNode((yyvsp[-6].str),NULL,NULL), (yyvsp[-4].node)),(yyvsp[-1].node));
    (yyval.node) = mkNode("array_assign", mkNode((yyvsp[-6].str), (yyvsp[-4].node), NULL), (yyvsp[-1].node));
}
#line 2873 "y.tab.c"
    break;

  case 78: /* return_stat: RETURN expression SEMICOLON  */
#line 1070 "parser.y"
      { verify_return((yyvsp[-1].node)); (yyval.node) = mkNode("RETURN", (yyvsp[-1].node), NULL); }
#line 2879 "y.tab.c"
    break;

  case 79: /* return_stat: RETURN SEMICOLON  */
#line 1072 "parser.y"
      { verify_return(NULL); (yyval.node) = mkNode("RETURN", NULL, NULL); }
#line 2885 "y.tab.c"
    break;

  case 80: /* expression_list: %empty  */
#line 1075 "parser.y"
{
    (yyval.node) = NULL; /* Empty expression list */
}
#line 2893 "y.tab.c"
    break;

  case 81: /* expression_list: expression  */
#line 1078 "parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2899 "y.tab.c"
    break;

  case 82: /* expression_list: expression COMMA expression_list  */
#line 1079 "parser.y"
                                   { (yyval.node) = mkNode("expr_list", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2905 "y.tab.c"
    break;

  case 83: /* expression: expression PLUS expression  */
#line 1082 "parser.y"
                                        { (yyval.node) = mkNode("+", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2911 "y.tab.c"
    break;

  case 84: /* expression: expression MINUS expression  */
#line 1083 "parser.y"
                              { (yyval.node) = mkNode("-", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2917 "y.tab.c"
    break;

  case 85: /* expression: expression MULTI expression  */
#line 1084 "parser.y"
                              { (yyval.node) = mkNode("*", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2923 "y.tab.c"
    break;

  case 86: /* expression: expression DIV expression  */
#line 1085 "parser.y"
                            { (yyval.node) = mkNode("/", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2929 "y.tab.c"
    break;

  case 87: /* expression: expression AND expression  */
#line 1086 "parser.y"
                            { (yyval.node) = mkNode("and", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2935 "y.tab.c"
    break;

  case 88: /* expression: expression OR expression  */
#line 1087 "parser.y"
                           { (yyval.node) = mkNode("or", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2941 "y.tab.c"
    break;

  case 89: /* expression: expression EQL expression  */
#line 1088 "parser.y"
                            { (yyval.node) = mkNode("==", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2947 "y.tab.c"
    break;

  case 90: /* expression: expression NOT_EQL expression  */
#line 1089 "parser.y"
                                { (yyval.node) = mkNode("!=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2953 "y.tab.c"
    break;

  case 91: /* expression: expression GREATER expression  */
#line 1090 "parser.y"
                                { (yyval.node) = mkNode(">", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2959 "y.tab.c"
    break;

  case 92: /* expression: expression GREATER_EQL expression  */
#line 1091 "parser.y"
                                    { (yyval.node) = mkNode(">=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2965 "y.tab.c"
    break;

  case 93: /* expression: expression LESS expression  */
#line 1092 "parser.y"
                             { (yyval.node) = mkNode("<", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2971 "y.tab.c"
    break;

  case 94: /* expression: expression LESS_EQL expression  */
#line 1093 "parser.y"
                                 { (yyval.node) = mkNode("<=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2977 "y.tab.c"
    break;

  case 95: /* expression: NOT expression  */
#line 1094 "parser.y"
                           { (yyval.node) = mkNode("not", (yyvsp[0].node), NULL); }
#line 2983 "y.tab.c"
    break;

  case 96: /* expression: MINUS expression  */
#line 1095 "parser.y"
                             { (yyval.node) = mkNode("unary-", (yyvsp[0].node), NULL); }
#line 2989 "y.tab.c"
    break;

  case 97: /* expression: ADDRESS ID  */
#line 1097 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[0].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[0].str));
    }
    (yyval.node) = mkNode("address", mkNode((yyvsp[0].str), NULL, NULL), NULL); }
#line 3000 "y.tab.c"
    break;

  case 98: /* expression: ADDRESS ID OPENBRACKET expression CLOSEBRACKET  */
#line 1104 "parser.y"
{
    verify_string_index(mkNode((yyvsp[-3].str),NULL,NULL), (yyvsp[-1].node));
    Symbol *var=find_symbol((yyvsp[-3].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-3].str));
    }
    Node *array_elem = mkNode("array_element", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node));
    (yyval.node) = mkNode("address", array_elem, NULL);
}
#line 3014 "y.tab.c"
    break;

  case 99: /* expression: MULTI expression  */
#line 1114 "parser.y"
    { (yyval.node) = mkNode("dereference", (yyvsp[0].node), NULL); }
#line 3020 "y.tab.c"
    break;

  case 100: /* expression: LENGTH ID LENGTH  */
#line 1116 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[-1].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-1].str));
    }
    (yyval.node) = mkNode("length", mkNode((yyvsp[-1].str), NULL, NULL), NULL); }
#line 3031 "y.tab.c"
    break;

  case 101: /* expression: OPENPAREN expression CLOSEPAREN  */
#line 1122 "parser.y"
                                  { (yyval.node) = (yyvsp[-1].node); }
#line 3037 "y.tab.c"
    break;

  case 102: /* expression: ID  */
#line 1124 "parser.y"
{
    Symbol *var=find_symbol((yyvsp[0].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[0].str));
    }
    (yyval.node) = mkNode((yyvsp[0].str), NULL, NULL); }
#line 3048 "y.tab.c"
    break;

  case 103: /* expression: ID OPENBRACKET expression CLOSEBRACKET  */
#line 1131 "parser.y"
{
    verify_string_index(mkNode((yyvsp[-3].str),NULL,NULL), (yyvsp[-1].node));
    Symbol *var=find_symbol((yyvsp[-3].str));
    if(!var){
        semantic_error("Variable used before it been declared.",(yyvsp[-3].str));
    }
    (yyval.node) = mkNode("array_element", mkNode((yyvsp[-3].str), NULL, NULL), (yyvsp[-1].node));
}
#line 3061 "y.tab.c"
    break;

  case 104: /* expression: literal  */
#line 1140 "parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 3067 "y.tab.c"
    break;


#line 3071 "y.tab.c"

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

#line 1142 "parser.y"


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

    // Add debug output to see what we're processing
    printf("DEBUG: get_expression_type called with token: '%s'\n", expr->token);

    // Literals
    if (strcmp(expr->token, "TRUE") == 0 || strcmp(expr->token, "FALSE") == 0)
    {
        printf("DEBUG: Returning TYPE_BOOL for '%s'\n", expr->token);
        return TYPE_BOOL;
    }

    if (expr->token[0] == '\'' && expr->token[strlen(expr->token) - 1] == '\'')
    {
        printf("DEBUG: Returning TYPE_CHAR for '%s'\n", expr->token);
        return TYPE_CHAR;
    }

    // String literal
    if (strcmp(expr->token, "STRING_LIT") == 0 ||
        (expr->token[0] == '"' && expr->token[strlen(expr->token) - 1] == '"'))
    {
        printf("DEBUG: Returning TYPE_STRING for '%s'\n", expr->token);
        return TYPE_STRING;
    }

    // Integer literal
    if (isdigit(expr->token[0]) ||
        (expr->token[0] == '-' && isdigit(expr->token[1])))
    {
        if (strchr(expr->token, '.') != NULL)
        {
            printf("DEBUG: Returning TYPE_REAL for numeric literal '%s'\n", expr->token);
            return TYPE_REAL; // Real number
        }
        printf("DEBUG: Returning TYPE_INT for numeric literal '%s'\n", expr->token);
        return TYPE_INT;
    }

    // Hexadecimal literal
    if (expr->token[0] == '0' && (expr->token[1] == 'x' || expr->token[1] == 'X'))
    {
        printf("DEBUG: Returning TYPE_INT for hex literal '%s'\n", expr->token);
        return TYPE_INT;
    }

    // Real literal
    if (strchr(expr->token, '.') != NULL)
    {
        printf("DEBUG: Returning TYPE_REAL for real literal '%s'\n", expr->token);
        return TYPE_REAL;
    }

    // Null
    if (strcmp(expr->token, "null") == 0)
    {
        printf("DEBUG: Returning TYPE_INVALID for null\n");
        return TYPE_INVALID; // Special case for null
    }

    // Binary arithmetic operators (+, -, *, /)
    if (strcmp(expr->token, "+") == 0 || strcmp(expr->token, "-") == 0 ||
        strcmp(expr->token, "*") == 0 || strcmp(expr->token, "/") == 0){

        printf("DEBUG: Processing binary operator '%s'\n", expr->token);
        DataType left_type = get_expression_type(expr->left);
        DataType right_type = get_expression_type(expr->right);

        printf("DEBUG: Binary op '%s' - left_type: %s, right_type: %s\n", 
               expr->token, type_to_string(left_type), type_to_string(right_type));

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
            char error_msg[200];
            sprintf(error_msg, "Operator '%s' requires numeric operands, got '%s' and '%s'",
                    expr->token, type_to_string(left_type), type_to_string(right_type));
            semantic_error(error_msg, "");
            return TYPE_INVALID; // Error case
        }

        // If either operand is real, result is real
        if (left_type == TYPE_REAL || right_type == TYPE_REAL)
        {
            printf("DEBUG: Binary op '%s' returning TYPE_REAL\n", expr->token);
            return TYPE_REAL;
        }

        // Otherwise, result is integer
        printf("DEBUG: Binary op '%s' returning TYPE_INT\n", expr->token);
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

    // Variable lookup - this is the critical part
    printf("DEBUG: Looking up variable '%s' in current scope %d\n", expr->token, current_scope_level);
    Symbol *var_sym = find_symbol(expr->token);
    if (var_sym)
    {
        printf("DEBUG: Found variable '%s' with type %s in scope %d\n", 
               expr->token, type_to_string(var_sym->type), var_sym->scope_level);
        return var_sym->type;
    }
    else
    {
        printf("DEBUG: Variable '%s' not found in any visible scope\n", expr->token);
        
        // Check if this is a simple decimal number that we missed earlier
        char *endptr;
        double val = strtod(expr->token, &endptr);
        if (*endptr == '\0') {
            // It's a valid number
            if (strchr(expr->token, '.') != NULL) {
                printf("DEBUG: Late recognition of REAL literal '%s'\n", expr->token);
                return TYPE_REAL;
            } else {
                printf("DEBUG: Late recognition of INT literal '%s'\n", expr->token);
                return TYPE_INT;
            }
        }
        
        printf("DEBUG: '%s' is not a number and not found as variable - semantic error\n", expr->token);
        semantic_error("Undefined variable", expr->token);
        return TYPE_INVALID;
    }
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
        printf("----------------------------------------3AC-----------------------------------.\n");
        generate_3ac(ast_root);
    } else{
        printf("Parsing failed due to syntax or semantic erros.\n");
    }
    
    // Free memory (simplified version)
    if(ast_root) free_tree(ast_root);
    free_symbol_table(current_scope);
    
    return 0;
}
