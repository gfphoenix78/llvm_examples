#include "common.h"
/**
 * func foo(a, b, c, d) {
     if a {
     }

     if a {

     } else {

     }

     if a {
     } else if b {
     } else if c {
     }

     if a {
     } else if b {
     } else if c {
     } else {
     }

 * }
 */
static void run()
{
    auto i32 = llvm::Type::getInt32Ty(ctx);
    auto one = llvm::ConstantInt::get(i32, 1);
    auto two = llvm::ConstantInt::get(i32, 2);
    auto ft = llvm::FunctionType::get(i32, false);
    auto func = llvm::Function::Create(ft, llvm::GlobalValue::LinkageTypes::CommonLinkage, "main", mod);
    auto block = llvm::BasicBlock::Create(ctx, "entry", func);
    llvm::IRBuilder<> builder(block);
    auto b2 = llvm::BasicBlock::Create(ctx, "block2", func);
    auto b3 = llvm::BasicBlock::Create(ctx, "block3", func);
    b3->moveAfter(b2);

    builder.CreateAlloca(i32, llvm::ConstantInt::get(i32, 1));
    builder.SetInsertPoint(b2);
    builder.CreateAlloca(i32, llvm::ConstantInt::get(i32, 1));
    builder.SetInsertPoint(b3);
    auto p = builder.CreateAlloca(i32, llvm::ConstantInt::get(i32, 1), "ptr");

    {
        std::vector<llvm::Type*> args = {{i32, i32}};
        auto f = llvm::Function::Create(llvm::FunctionType::get(i32, args, false),
                llvm::GlobalValue::LinkageTypes::CommonLinkage, "addm", mod);
        auto blk = llvm::BasicBlock::Create(ctx, "", f);
        llvm::IRBuilder<> ir(blk);

        auto a = ir.CreateAlloca(i32, two, "a");
        auto arg = f->arg_begin();
        auto a1 = arg;
        auto a2 = ++arg;
        auto add = ir.CreateAdd(a1, a2);

        std::string lit = "-12";
        auto ap = llvm::APInt(130, lit, 10);
        auto val = llvm::ConstantInt::get(ctx, ap);
        builder.CreateStore(val, p);
        auto delta = ir.CreateAdd(llvm::ConstantInt::get(i32, 3), llvm::ConstantInt::get(i32, 4), "cc");
//        delta = ir.CreateAdd(val, delta);
        add = ir.CreateAdd(add, delta, "watch");
        ir.CreateRet(add);
    }


}

int main(int argc, char**argv) {
    mod.setModuleIdentifier(__FILE__);

    run();

    mod.print(llvm::outs(), nullptr);
    llvm::verifyModule(mod, &llvm::outs(), nullptr);
    return 0;
}
