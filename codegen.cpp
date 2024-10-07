#include "codegen.hpp"
#include <iostream>

void CodeGenContext::generateCode(ProgramAST &root) {
    // Generate code for all functions
    for (auto func : root.functions) {
        llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getInt32Ty(), false);
        llvm::Function *function = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, func->Name, module);

        llvm::BasicBlock *block = llvm::BasicBlock::Create(llvmContext, "entry", function);
        builder.SetInsertPoint(block);

        llvm::Value *retVal = generateExpression(func->Body);
        builder.CreateRet(retVal);
    }

    // Output the LLVM IR
    module->print(llvm::outs(), nullptr);
}

llvm::Value *CodeGenContext::generateExpression(ExprAST *expr) {
    if (auto number = dynamic_cast<NumberExprAST*>(expr)) {
        return llvm::ConstantInt::get(builder.getInt32Ty(), number->Val, true);
    } else if (auto variable = dynamic_cast<VariableExprAST*>(expr)) {
        if (namedValues.find(variable->Name) == namedValues.end()) {
            std::cerr << "Unknown variable name: " << variable->Name << std::endl;
            return nullptr;
        }
        return builder.CreateLoad(namedValues[variable->Name], variable->Name.c_str());
    } else if (auto binary = dynamic_cast<BinaryExprAST*>(expr)) {
        llvm::Value *L = generateExpression(binary->LHS);
        llvm::Value *R = generateExpression(binary->RHS);
        if (!L || !R) return nullptr;

        switch (binary->Op) {
            case '+': return builder.CreateAdd(L, R, "addtmp");
            case '-': return builder.CreateSub(L, R, "subtmp");
            case '*': return builder.CreateMul(L, R, "multmp");
            case '/': return builder.CreateSDiv(L, R, "divtmp");
            default:
                std::cerr << "Invalid binary operator" << std::endl;
                return nullptr;
        }
    } else if (auto call = dynamic_cast<CallExprAST*>(expr)) {
        llvm::Function *calleeF = module->getFunction(call->Callee);
        if (!calleeF) {
            std::cerr << "Unknown function referenced: " << call->Callee << std::endl;
            return nullptr;
        }
        std::vector<llvm::Value*> argsV;
        for (auto arg : call->Args) {
            argsV.push_back(generateExpression(arg));
            if (!argsV.back()) return nullptr;
        }
        return builder.CreateCall(calleeF, argsV, "calltmp");
    }
    return nullptr;
}
