%{
#include "parser.hpp"
#include "ast.hpp"

extern int yylineno;
void yyerror(const char *s, ...);
%}

%option noyywrap

%%

[ \t\r\n]+           ;  // Ignore whitespace

"//".*              ;  // Ignore comments

"import"            { return IMPORT; }
"func"              { return FUNC; }
"class"             { return CLASS; }
"extends"           { return EXTENDS; }
"if"                { return IF; }
"else"              { return ELSE; }
"while"             { return WHILE; }
"for"               { return FOR; }
"return"            { return RETURN; }
"new"               { return NEW; }

"{"                 { return '{'; }
"}"                 { return '}'; }
"("                 { return '('; }
")"                 { return ')'; }
","                 { return ','; }
";"                 { return ';'; }
"="                 { return '='; }
"=="                { return EQ; }
"!="                { return NEQ; }
"<"                 { return '<'; }
">"                 { return '>'; }
"<="                { return LEQ; }
">="                { return GEQ; }
"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }

[0-9]+              { yylval.intVal = atoi(yytext); return INT_LITERAL; }
\".*\"              { yylval.strVal = strdup(yytext); return STRING_LITERAL; }
[a-zA-Z_][a-zA-Z0-9_]* {
                        yylval.strVal = strdup(yytext);
                        return IDENTIFIER;
                     }

.                   { yyerror("Invalid character: %s", yytext); }

%%

int yywrap() { return 1; }
