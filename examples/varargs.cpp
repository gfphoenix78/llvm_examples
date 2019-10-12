//
// Created by Hao Wu on 7/31/19.
//
#include "common.h"
#include <stdarg.h>

using namespace llvm;
void kprintf(Module *mod, BasicBlock *bb, const char *format, ...)
{
    Function *func_printf = mod->getFunction("printf");
    if (!func_printf) {
        PointerType *Pty = PointerType::get(IntegerType::get(mod->getContext(), 8), 0);
        FunctionType *FuncTy9 = FunctionType::get(IntegerType::get(mod->getContext(), 32), true);

        func_printf = Function::Create(FuncTy9, GlobalValue::ExternalLinkage, "printf", mod);
        func_printf->setCallingConv(CallingConv::C);

//        AttrListPtr func_printf_PAL;
//        func_printf->setAttributes(func_printf_PAL);
    }

    IRBuilder <> builder(mod->getContext());
    builder.SetInsertPoint(bb);

    Value *str = builder.CreateGlobalStringPtr(format);
    std::vector <Value *> int32_call_params;
    int32_call_params.push_back(str);

    va_list ap;
    va_start(ap, format);

    char *str_ptr = va_arg(ap, char*);
    Value *format_ptr = builder.CreateGlobalStringPtr(str_ptr);
    int32_call_params.push_back(format_ptr);

    std::vector<llvm::Value*> extra;
    do {
        llvm::Value *op = va_arg(ap, llvm::Value*);
        if (op) {
            int32_call_params.push_back(op);
        } else {
            break;
        }
    } while (1);
    va_end(ap);

    auto ret = builder.CreateCall(func_printf, int32_call_params, "call");
    builder.CreateRet(ret);

}
void test_printf(llvm::Module &mod)
{
    mod.setModuleIdentifier("varargs");
    Function *func_main = Function::Create(
            FunctionType::get(Type::getInt32Ty(ctx), false),
            GlobalValue::LinkageTypes::AvailableExternallyLinkage, "main", mod
    );
    auto bb = llvm::BasicBlock::Create(ctx, "main_entry", func_main);
    kprintf(&mod, bb, "hello, %s, id = %d\n", "foobar", ConstantInt::get(Type::getInt32Ty(ctx), 78, true), nullptr);

}
void add(llvm::Module &m)
{
    auto typint = Type::getInt32Ty(ctx);
    std::vector<llvm::Type*> types;
    types.push_back(typint);
    FunctionType *ft = FunctionType::get(typint, types, true);
    auto func = Function::Create(ft, GlobalValue::LinkageTypes::ExternalLinkage, "add", m);
    auto blk = llvm::BasicBlock::Create(ctx, "entry", func);
    llvm::IRBuilder<> builder(blk);
    llvm::Value* sum = builder.CreateAlloca(typint, nullptr, "sum");
    builder.CreateStore(sum, ConstantInt::get(typint, 0, true));
    sum = builder.CreateLoad(sum);
    for (auto args = func->arg_begin(); args != func->arg_end(); ++args) {
        sum = builder.CreateAdd(sum, (llvm::Value*)args);
    }

    builder.CreateRet(sum);
}
int main()
{
    add(mod);
    mod.print(llvm::outs(), nullptr);

    return 0;
}