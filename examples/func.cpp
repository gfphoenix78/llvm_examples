#include "common.h"
#include <llvm/ADT/StringRef.h>
#include <vector>


static void makeFoo(llvm::Module &m)
{

}
// int main(int argc, char **argv)
// {
//    int a = foo(argc);
//    printf("a = %d\n", a);
//    return 0;
// }
// int ID = 78;

static void makeMain(llvm::Module &m)
{
    auto &ctx = m.getContext();
    auto tyint = llvm::Type::getInt32Ty(ctx);
    auto t0 = llvm::PointerType::get(llvm::Type::getInt8PtrTy(ctx), 0);
    std::vector<llvm::Type*> types;
    types.push_back(tyint);
    types.push_back(t0);
//    types.push_back(llvm::PointerType::get(t0, 0));

    auto ft = llvm::FunctionType::get(tyint, types, false);
    auto func_main = (llvm::Function*)m.getOrInsertFunction("main", ft);
    auto args = func_main->arg_begin();
    llvm::Value *arg0 = args;
    arg0->setName("argc");
    auto entry = llvm::BasicBlock::Create(ctx, "main_entry", func_main);


    auto foo = (llvm::Function*)m.getOrInsertFunction("foo", tyint, tyint);

    {
        llvm::IRBuilder<> builder(entry);
        llvm::Value * a = builder.CreateAlloca(tyint);
        builder.CreateStore(a, llvm::ConstantInt::get(llvm::Type::getInt32Ty(ctx), 123, true));
        std::vector<llvm::Value*> args2;
        args2.push_back(arg0);
//        auto a2 = builder.CreateCall(foo,args2);
//        llvm::Function *print = (llvm::Function*)m.getOrInsertFunction("printf", llvm::Type::getInt8PtrTy(ctx), true);
//        auto fmt = new llvm::StringLiteral("a = %d\n");
//auto fff = new llvm::GlobalVariable(m, llvm::Type::getInt8PtrTy(ctx), true,
//        llvm::GlobalValue::LinkageTypes::InternalLinkage, llvm::StringLiteral("a = %d\n"));
//args2.clear();
//        args2.push_back(fmt);
//        args2.push_back(a2);
//        builder.CreateCall(print, );
        builder.CreateRet(builder.CreateLoad(a));
    }
}

int main(int argc, char**argv) {
    llvm::Module m("main", ctx);
    mod.setModuleIdentifier(__FILE__);

    makeMain(m);
    makeFoo(mod);

//    mod.print(llvm::outs(), nullptr);
//    llvm::verifyModule(mod, &llvm::outs(), nullptr);
    m.print(llvm::outs(), nullptr);
    llvm::verifyModule(m, &llvm::outs(), nullptr);
    return 0;
}
