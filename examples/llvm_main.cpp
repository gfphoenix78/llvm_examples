//
// Created by Hao Wu on 7/1/19.
//

#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/Support/raw_os_ostream.h>

int main0()
{
    printf("llvm...\n");
    llvm::LLVMContext ctx;
    llvm::Module module("The-Module", ctx);

    llvm::IRBuilder<> builder(ctx);
    builder.CreateGlobalString("hello, world");

    module.print(llvm::outs(), nullptr);
    printf("module = %p\n", &module);
    return 0;
}

//#include "llvm/Assembly/PrintModulePass.h"


void makeLLVMModule(llvm::Module &module);

int main(int argc, char**argv) {
    llvm::LLVMContext ctx;
    llvm::Module mod("tut2", ctx);
    makeLLVMModule(mod);

//    verifyModule(*Mod, PrintMessageAction);

//    PassManager<> PM;
//    PM.add(createPrintModulePass(&outs()));
//    PM.run(*Mod);
    mod.print(llvm::outs(), nullptr);
    return 0;
}

void makeLLVMModule(llvm::Module &mod) {

    auto &ctx = mod.getContext();
    llvm::Constant* c = mod.getOrInsertFunction("gcd",
                                           llvm::Type::getInt32Ty(ctx),
                                           llvm::Type::getInt32Ty(ctx),
                                           llvm::Type::getInt32Ty(ctx));
    llvm::Function* gcd = static_cast<llvm::Function*>(c);

    llvm::Function::arg_iterator args = gcd->arg_begin();
    llvm::Value* x = args++;
    x->setName("x");
    llvm::Value* y = args++;
    y->setName("y");
    auto entry = llvm::BasicBlock::Create(ctx, "entry", gcd);
    auto ret = llvm::BasicBlock::Create(ctx, "return", gcd);
    auto cond_false = llvm::BasicBlock::Create(ctx, "cond_false", gcd);
    auto cond_true = llvm::BasicBlock::Create(ctx, "cond_true", gcd);
    auto cond_false_2 = llvm::BasicBlock::Create(ctx, "cond_false", gcd);

    llvm::IRBuilder<> builder(entry);
    llvm::Value* xEqualsY = builder.CreateICmpEQ(x, y, "tmp");
    builder.CreateCondBr(xEqualsY, ret, cond_false);

    builder.SetInsertPoint(ret);
    builder.CreateRet(x);
    builder.SetInsertPoint(cond_false);
    llvm::Value* xLessThanY = builder.CreateICmpULT(x, y, "tmp");
    builder.CreateCondBr(xLessThanY, cond_true, cond_false_2);

    builder.SetInsertPoint(cond_true);
    llvm::Value* yMinusX = builder.CreateSub(y, x, "tmp");
    std::vector<llvm::Value*> args1;
    args1.push_back(x);
    args1.push_back(yMinusX);
    llvm::Value* recur_1 = builder.CreateCall(gcd, args1, "tmp");
    builder.CreateRet(recur_1);

    builder.SetInsertPoint(cond_false_2);
    llvm::Value* xMinusY = builder.CreateSub(x, y, "tmp");
    std::vector<llvm::Value*> args2;
    args2.push_back(xMinusY);
    args2.push_back(y);
    llvm::Value* recur_2 = builder.CreateCall(gcd, args2, "tmp");
    builder.CreateRet(recur_2);

    auto g = new llvm::GlobalVariable(mod, llvm::Type::getInt64Ty(ctx), false, llvm::GlobalValue::ExternalLinkage,
                                      llvm::ConstantInt::get(llvm::Type::getInt64Ty(ctx), 12345, true), "foobarbaz");
    //g->print(llvm::outs(), true);

}
