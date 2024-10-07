#include "ast.hpp"
#include "codegen.hpp"
#include "parser.hpp"

extern int yyparse();
extern ProgramAST *root;

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            printf("Could not open %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }

    root = new ProgramAST();
    yyparse();

    CodeGenContext context;
    context.generateCode(*root);

    return 0;
}
