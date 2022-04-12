#include "passes.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InstIterator.h"

using namespace llvm;

namespace {

using HandlerTy = std::function<llvm::Value*(llvm::Instruction &I)>;

Value* HandleAdd(llvm::Instruction &I) {
  assert(I.getOpcode() == Instruction::Add);
  IRBuilder<> B(&I);

  // TODO: Recover the operands X,Y. See User::getOperand 
  // TODO: For the shift, carefully pick the appropriate function from IRBuilder.
  // You may or may not have to create the constant "one" for it.
  // See ConstantInt::get and Value::getType if needed.
  // TODO: Create an expression which is ((X&Y)<<1 + (X^Y)). see IRBuilder<>

  Value *X = I.getOperand(0);
  Value *Y = I.getOperand(1);
  return B.CreateAdd(
      B.CreateShl(B.CreateAnd(X, Y), 1),
      B.CreateXor(X,Y));
}

Value* HandleSub(Instruction &I) {
  IRBuilder<> B(&I);

  // TODO: Similarly, do ((X&-Y)<<1)+(X^-Y)

  Value *X = I.getOperand(0);
  Value *Y = I.getOperand(1);
  Value *NY = B.CreateNeg(Y);

  return B.CreateAdd(
      B.CreateShl(B.CreateAnd(X, NY), 1),
      B.CreateXor(X, NY));
}

SmallDenseMap<unsigned, HandlerTy> Handlers {
  {Instruction::Add, HandleAdd},
  {Instruction::Sub, HandleSub},
};

auto HasInstructionHandler = [](Instruction &I) {
  return Handlers.count(I.getOpcode()) == 1;
};

} // namespace

#if 1

PreservedAnalyses MBA::run(Function &F, FunctionAnalysisManager &) {
  SmallVector<Instruction *> ToErase;
  // Iterate only over supported instructions
  for (Instruction &I: make_filter_range(instructions(F), HasInstructionHandler)) {
    I.replaceAllUsesWith(Handlers[I.getOpcode()](I));
    ToErase.emplace_back(&I);
  }
  // Cleanup unused instructions
  for_each(ToErase, [](Instruction *I) { I->eraseFromParent(); });
  return PreservedAnalyses::all();
}

#else

// Alternate implementation with a more "plain old C" syntax
PreservedAnalyses MBA::run(Function &F, FunctionAnalysisManager &) {
  SmallVector<Instruction *> ToErase;
  // Iterate only over supported instructions
  for (BasicBlock &BB : F) {
    for (Instruction &I : BB) {
      if (!Handlers.count(I.getOpcode())) {
        continue;
      }
      I.replaceAllUsesWith(Handlers[I.getOpcode()](I));
      ToErase.push_back(&I);
    }
  }

  // Cleanup unused instructions
  for (Instruction *I : ToErase) {
    I->eraseFromParent();
  }
  return PreservedAnalyses::all();
}
#endif
