#include "llvm/IR/IRBuilder.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;


struct AddToSub : PassInfoMixin<AddToSub> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
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
  // Optional, if true will run over optnone.
  static bool isRequired() { return true; }
};

void RegisterPassBuilderCallbacks(PassBuilder &PB) {
  // The callback will run at the very beginning of an optimization pipeline.
  PB.registerPipelineStartEPCallback(
      [](ModulePassManager &MPM, PassBuilder::OptimizationLevel OL) {
        // Use a Module -> Function adaptor
        // It's just for the sake of the example, we could register a callback
        // using a FunctionPassManager!
        MPM.addPass(createModuleToFunctionPassAdaptor(AddToSub()));
      });
  // The callback will be executed when giving "-passes=add2sub" to opt
  // We can pass a callback which uses ModulePassManager&, or FunctionPassManager&, etc
  PB.registerPipelineParsingCallback(
      [](StringRef Name, FunctionPassManager &FPM,
         ArrayRef<PassBuilder::PipelineElement>) {
        if (Name == "add2sub") {
          FPM.addPass(AddToSub());
          return true;
        }
        return false;
      });
}

// This is the entry point called when loading plugins
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "Add2Sub", LLVM_VERSION_STRING,
          RegisterPassBuilderCallbacks};
}
