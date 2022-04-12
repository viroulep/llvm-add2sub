#ifndef PLUGIN_PASSES_H
#define PLUGIN_PASSES_H

#include "llvm/IR/PassManager.h"

struct AddToSub : llvm::PassInfoMixin<AddToSub> {
  llvm::PreservedAnalyses run(llvm::Function &, llvm::FunctionAnalysisManager &);
  // Makes it run even if the function has the "optnone" attribute.
  static inline bool isRequired() { return true; }
};

struct MBA : llvm::PassInfoMixin<MBA> {
  llvm::PreservedAnalyses run(llvm::Function &, llvm::FunctionAnalysisManager &);
  // Makes it run even if the function has the "optnone" attribute.
  static inline bool isRequired() { return true; }
};

#endif
