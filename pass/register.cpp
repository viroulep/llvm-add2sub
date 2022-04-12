#include "passes.h"

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

namespace {
using namespace llvm;
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
        if (Name == "mba") {
          FPM.addPass(MBA());
          return true;
        }
        return false;
      });
}
}

// This is the entry point called when loading plugins
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "MyPlugin", LLVM_VERSION_STRING,
          RegisterPassBuilderCallbacks};
}
