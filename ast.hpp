#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

class ExprAST {
public:
    virtual ~ExprAST() = default;
};

class NumberExprAST : public ExprAST {
public:
    int Val;
    NumberExprAST(int Val) : Val(Val) {}
};

class VariableExprAST : public ExprAST {
public:
    std::string Name;
    VariableExprAST(const std::string &Name) : Name(Name) {}
};

class BinaryExprAST : public ExprAST {
public:
    char Op;
    ExprAST *LHS, *RHS;
    BinaryExprAST(char Op, ExprAST *LHS, ExprAST *RHS) : Op(Op), LHS(LHS), RHS(RHS) {}
};

class CallExprAST : public ExprAST {
public:
    std::string Callee;
    std::vector<ExprAST*> Args;
    CallExprAST(const std::string &Callee, std::vector<ExprAST*> Args) : Callee(Callee), Args(std::move(Args)) {}
};

class NewExprAST : public ExprAST {
public:
    std::string ClassName;
    NewExprAST(const std::string &ClassName) : ClassName(ClassName) {}
};

class PrototypeAST {
public:
    std::string Name;
    PrototypeAST(const std::string &Name) : Name(Name) {}
};

class FunctionAST {
public:
    std::string Name;
    PrototypeAST *Proto;
    ExprAST *Body;
    FunctionAST(const std::string &Name, PrototypeAST *Proto, ExprAST *Body) : Name(Name), Proto(Proto), Body(Body) {}
};

class ClassAST {
public:
    std::string Name;
    std::string BaseClass;
    std::vector<FunctionAST*> Methods;
    ClassAST(const std::string &Name, const std::string &BaseClass, std::vector<FunctionAST*> Methods)
        : Name(Name), BaseClass(BaseClass), Methods(std::move(Methods)) {}
};

class ProgramAST {
public:
    std::vector<FunctionAST*> functions;
    std::vector<ClassAST*> classes;
};
