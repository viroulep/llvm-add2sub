#include "passes.h"

#include "llvm/IR/IRBuilder.h"
// For llvm::instructions(Function &)
#include "llvm/IR/InstIterator.h"


using namespace llvm;

PreservedAnalyses AddToSub::run(Function &F, FunctionAnalysisManager &) {
  IRBuilder<> Builder{&F.getEntryBlock()};
  SmallVector<Instruction *> ToErase;
  // Iterate only over Add-s.
  auto IsAdd = [](Instruction &I) { return I.getOpcode() == Instruction::Add; };
  for (Instruction &I: make_filter_range(instructions(F), IsAdd)) {
    // Move the insertion point and replace the Add by a Sub.
    Builder.SetInsertPoint(&I);
    I.replaceAllUsesWith(Builder.CreateSub(I.getOperand(0), I.getOperand(1)));
    ToErase.emplace_back(&I);
  }
  // Cleanup unused instructions
  for_each(ToErase, [](Instruction *I) { I->eraseFromParent(); });
  return PreservedAnalyses::all();
}
