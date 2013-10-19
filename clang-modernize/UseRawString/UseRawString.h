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
/// \brief This file provides the definition of the UseRawStringTransform class
/// which is the main interface to the transform that tries to replace the
/// regular string literal with C++11 raw string if doing so makes code shorter
/// and easier to read.
///
//===----------------------------------------------------------------------===//

#ifndef CLANG_MODERNIZE_USE_RAW_STRING_H
#define CLANG_MODERNIZE_USE_RAW_STRING_H

#include "Core/Transform.h"
#include "llvm/Support/Compiler.h"

class UseRawStringFixer;

/// \brief Subclass of Transform that replaces the regular string literal with
/// C++ raw string.
class UseRawStringTransform : public Transform {
public:
  UseRawStringTransform(const TransformOptions &Options)
      : Transform("UseRawString", Options) {}

  /// \see Transform::run().
  virtual int apply(const clang::tooling::CompilationDatabase &Database,
                    const std::vector<std::string> &SourcePaths) LLVM_OVERRIDE;
};

#endif // CLANG_MODERNIZE_USE_RAW_STRING_H
