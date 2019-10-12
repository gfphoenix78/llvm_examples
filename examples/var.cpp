#include "common.h"

std::vector<llvm::Constant*> chartov(const char *s, int n)
{
    std::vector<llvm::Constant*> v;
    auto typ8 = llvm::Type::getInt8Ty(ctx);
    while (*s)
        v.push_back(llvm::ConstantInt::get(typ8, (unsigned)*s++, false));
    for(auto i=v.size(); i<n; i++)
        v.push_back(llvm::ConstantInt::get(typ8, 0, false));

    return std::move(v);
}
llvm::Constant* chartov2(llvm::LLVMContext &ctx, llvm::Module &m, const std::string &str)
{
    auto charType = llvm::Type::getInt8Ty(ctx);

    //1. Initialize chars vector
    std::vector<llvm::Constant *> chars(str.size());
    for(unsigned int i = 0; i < str.size(); i++) {
        chars[i] = llvm::ConstantInt::get(charType, str[i], false);
    }

    //1b. add a zero terminator too
    chars.push_back(llvm::ConstantInt::get(charType, 0));


    //2. Initialize the string from the characters
    auto stringType = llvm::ArrayType::get(charType, chars.size());

    printf("size = %u  %u\n", (unsigned)chars.size(), (unsigned)str.size());
    //3. Create the declaration statement
    auto p8 = llvm::PointerType::get(charType, 0);
    p8->print(llvm::outs());
    auto globalDeclaration = (llvm::GlobalVariable*) m.getOrInsertGlobal(".str", p8);
    auto val = llvm::ConstantArray::get(stringType, chars);
    globalDeclaration->setInitializer(llvm::ConstantExpr::getBitCast(val, p8));
    globalDeclaration->setConstant(true);
    globalDeclaration->setLinkage(llvm::GlobalValue::LinkageTypes::PrivateLinkage);
    globalDeclaration->setUnnamedAddr (llvm::GlobalValue::UnnamedAddr::Global);



    //4. Return a cast to an i8*
    return globalDeclaration;
//    return llvm::ConstantExpr::getBitCast(globalDeclaration, charType->getPointerTo());
}


void run_var(llvm::Module &m)
{
    llvm::IRBuilder<> builder(ctx);
    auto tpint = llvm::Type::getInt32Ty(ctx);
    auto tpname = llvm::ArrayType::get(llvm::Type::getInt8Ty(ctx), 16);
    auto tpfoo = llvm::StructType::get(tpint, tpname);
    tpfoo->setName("struct.foo");

    tpfoo->print(llvm::outs(), true, true);

    std::vector<llvm::Constant*> val;
    val.push_back(llvm::ConstantInt::get(tpint, 12, true));
//    val.push_back(llvm::ConstantArray::get(tpname, chartov("hello", 16)));
    val.push_back(llvm::ConstantAggregateZero::get(tpname));
    auto init_val = llvm::ConstantStruct::get(tpfoo, val);
//    auto init_val = llvm::ConstantAggregateZero::get(tpfoo);
    auto f1 = new llvm::GlobalVariable(m, tpfoo, false, llvm::GlobalValue::ExternalLinkage,
                                       init_val, "f1");

}

int main()
{
    run_var(mod);
    chartov2(ctx, mod, "hello, world");

    mod.print(llvm::outs(), nullptr);

    return 0;
}