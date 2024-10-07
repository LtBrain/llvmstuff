#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Lexer.h"
#include "Parser.h"
#include "CodeGenerator.h"

extern "C" int yylex();
extern "C" int yyparse();

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: Brightfield <input.bright>" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream file(argv[1]);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    // Initialize lexer and parser
    Tokenizer tokenizer(content);
    Parser parser(tokenizer.tokenize());
    CodeGenerator codeGen;

    // Parse the input and generate code
    parser.parse();
    codeGen.generateCode();

    // Output the LLVM IR to a file
    codeGen.outputToFile("output.ll");

    std::cout << "LLVM IR code generated in output.ll." << std::endl;

    return EXIT_SUCCESS;
}
