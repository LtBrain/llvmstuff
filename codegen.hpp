#pragma once

#include "ast.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

class CodeGenContext {
public:
    llvm::LLVMContext llvmContext;
    llvm::IRBuilder<> builder;
    llvm::Module *module;
    std::map<std::string, llvm::Value*> namedValues;

    CodeGenContext() : builder(llvmContext) {
        module = new llvm::Module("Brightfield", llvmContext);
    }

    void generateCode(ProgramAST &root);
    llvm::Value *generateExpression(ExprAST *expr);
};
