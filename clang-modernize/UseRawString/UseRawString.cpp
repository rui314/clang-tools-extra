//===-- UseRawString/UseRawString.h - use C++11 raw string ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief This file provides the implementation of the UseRawStringTransform
/// class.
///
//===----------------------------------------------------------------------===//

#include "UseRawString.h"
#include "RawStringActions.h"
#include "RawStringMatchers.h"

#include "clang/Frontend/CompilerInstance.h"

using clang::ast_matchers::MatchFinder;
using namespace clang::tooling;
using namespace clang;
namespace cl = llvm::cl;

int UseRawStringTransform::apply(const CompilationDatabase &Database,
                                 const std::vector<std::string> &SourcePaths) {
  ClangTool UseRawStringTool(Database, SourcePaths);
  unsigned AcceptedChanges = 0;
  MatchFinder Finder;
  UseRawStringFixer Fixer(AcceptedChanges, /*Owner=*/ *this);
  Finder.addMatcher(makeStringLiteralMatcher(), &Fixer);

  if (int result = UseRawStringTool.run(createActionFactory(Finder))) {
    llvm::errs() << "Error encountered during translation.\n";
    return result;
  }

  setAcceptedChanges(AcceptedChanges);
  return 0;
}

struct UseRawStringFactory : TransformFactory {
  UseRawStringFactory() {
    Since.Clang = Version(3, 0);
    Since.Gcc = Version(4, 5);
    Since.Icc = Version(14);
    Since.Msvc = Version(12);
  }

  Transform *createTransform(const TransformOptions &Opts) LLVM_OVERRIDE {
    return new UseRawStringTransform(Opts);
  }
};

// Register the factory using this statically initialized variable.
static TransformFactoryRegistry::Add<UseRawStringFactory>
X("use-raw-string", "Make use of raw string literal where possible");

// This anchor is used to force the linker to link in the generated object file
// and thus register the factory.
volatile int UseRawStringTransformAnchorSource = 0;
