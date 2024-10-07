#pragma once

#include <string>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/CallingConv.h>

class CodeGenerator {
public:
    CodeGenerator();

    void generateCode();
    void outputToFile(const std::string& filename);
    void handleImport(const std::string& libName);
    void handleExit(int exitCode);
    void handleIf();
    void handleWhile();
    void handleFor();
    void handleThread();

private:
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    llvm::Module* module;
    llvm::Function* mainFunction;
};
