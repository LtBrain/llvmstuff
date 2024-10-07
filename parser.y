%{
#include "ast.hpp"
#include "codegen.hpp"
#include <cstdio>
#include <cstdlib>

extern int yylex();
void yyerror(const char *s, ...);

ProgramAST *root;  // Root of the AST
%}

%union {
    int intVal;
    char *strVal;
    ExprAST *expr;
    VariableExprAST *var;
    PrototypeAST *proto;
    FunctionAST *func;
    ClassAST *classDef;
    std::vector<ExprAST*> *exprList;
    std::vector<VariableExprAST*> *varList;
    std::vector<FunctionAST*> *funcList;
    std::vector<ClassAST*> *classList;
}

%token <intVal> INT_LITERAL
%token <strVal> STRING_LITERAL IDENTIFIER
%token IMPORT FUNC CLASS EXTENDS IF ELSE WHILE FOR RETURN NEW
%token EQ NEQ LEQ GEQ

%type <expr> expression
%type <func> function
%type <classDef> class_def
%type <funcList> func_list
%type <classList> class_list
%type <exprList> expr_list
%type <varList> var_list

%start program

%%

program:
    | program import_statement
    | program function
    | program class_def
    ;

import_statement:
    IMPORT STRING_LITERAL ';'
    ;

function:
    FUNC IDENTIFIER '(' ')' block {
        $$ = new FunctionAST($2, nullptr, $5);
        root->functions.push_back($$);
    }
    ;

class_def:
    CLASS IDENTIFIER inheritance '{' class_body '}' {
        $$ = new ClassAST($2, $3, $5);
        root->classes.push_back($$);
    }
    ;

inheritance:
    /* empty */ { $$ = ""; }
    | EXTENDS IDENTIFIER { $$ = $2; }
    ;

class_body:
    | class_body function
    ;

block:
    '{' statement_list '}'
    ;

statement_list:
    | statement_list statement
    ;

statement:
    expression ';'
    | RETURN expression ';'
    | IF '(' expression ')' block
    | IF '(' expression ')' block ELSE block
    | WHILE '(' expression ')' block
    | FOR '(' expression ';' expression ';' expression ')' block
    ;

expression:
    IDENTIFIER '=' expression { $$ = new BinaryExprAST('=', new VariableExprAST($1), $3); }
    | expression '+' expression { $$ = new BinaryExprAST('+', $1, $3); }
    | expression '-' expression { $$ = new BinaryExprAST('-', $1, $3); }
    | expression '*' expression { $$ = new BinaryExprAST('*', $1, $3); }
    | expression '/' expression { $$ = new BinaryExprAST('/', $1, $3); }
    | '(' expression ')' { $$ = $2; }
    | INT_LITERAL { $$ = new NumberExprAST($1); }
    | IDENTIFIER { $$ = new VariableExprAST($1); }
    | IDENTIFIER '(' ')' { $$ = new CallExprAST($1, {}); }
    | NEW IDENTIFIER '(' ')' { $$ = new NewExprAST($2); }
    ;

%%

void yyerror(const char *s, ...) {
    fprintf(stderr, "Error: %s\n", s);
    exit(1);
}
