#include "CodeGenerator.h"
#include <llvm/IR/Verifier.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/raw_ostream.h>

CodeGenerator::CodeGenerator() : builder(context) {
    module = new llvm::Module("BrightfieldModule", context);

    // Create the main function
    llvm::FunctionType *mainType = llvm::FunctionType::get(builder.getInt32Ty(), false);
    mainFunction = llvm::Function::Create(mainType, llvm::Function::ExternalLinkage, "main", module);
    
    // Create a basic block for main
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(context, "entry", mainFunction);
    builder.SetInsertPoint(entry);
}

void CodeGenerator::generateCode() {
    // Example of adding a return statement to the main function
    builder.CreateRet(builder.getInt32(0)); // Return 0
}

void CodeGenerator::outputToFile(const std::string& filename) {
    std::error_code EC;
    llvm::raw_fd_ostream dest(filename, EC, llvm::sys::fs::OF_None);
    if (EC) {
        llvm::errs() << "Error opening file: " << EC.message();
        return;
    }

    module->print(dest, nullptr); // Print the LLVM IR to file
}

void CodeGenerator::handleImport(const std::string& libName) {
    // Handle import of C libraries
    std::cout << "Importing C library: " << libName << std::endl;
}

void CodeGenerator::handleExit(int exitCode) {
    std::cout << "Exiting with code: " << exitCode << std::endl;
}

void CodeGenerator::handleIf() {
    std::cout << "Handling If statement" << std::endl;
}

void CodeGenerator::handleWhile() {
    std::cout << "Handling While statement" << std::endl;
}

void CodeGenerator::handleFor() {
    std::cout << "Handling For loop" << std::endl;
}

void CodeGenerator::handleThread() {
    std::cout << "Handling Thread statement" << std::endl;
}
