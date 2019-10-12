//
// Created by Hao Wu on 8/27/19.
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

void test(llvm::Module &module)
{
    bool ok;
    auto &ctx = module.getContext();
    auto ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(ctx), false);
    auto func = (llvm::Function*)module.getOrInsertFunction("main", ft);

    auto main_block = llvm::BasicBlock::Create(ctx, "main_entry", func);
    auto b1 = llvm::BasicBlock::Create(ctx);

    llvm::verifyModule(module, &llvm::outs(), &ok);
    printf("module ok = %d\n", (int)ok);
}
int main()
{
    llvm::LLVMContext ctx;
    llvm::Module module("test", ctx);

    test(module);

    module.print(llvm::outs(), nullptr);

    return 0;
}
