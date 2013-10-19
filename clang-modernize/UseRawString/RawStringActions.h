//===-- UseRawString/RawStringActions.h - Matcher callback ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declaration of the UseRawStringFixer class
/// which is used as a ASTMatcher callback.
///
//===----------------------------------------------------------------------===//

#ifndef CLANG_MODERNIZE_RAW_STRING_ACTIONS_H
#define CLANG_MODERNIZE_RAW_STRING_ACTIONS_H

#include "Core/Transform.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Tooling/Refactoring.h"

/// \brief The callback to be used for raw string matchers.
class UseRawStringFixer : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
  UseRawStringFixer(unsigned &AcceptedChanges, Transform &Owner)
      : AcceptedChanges(AcceptedChanges), Owner(Owner) {}

  /// \brief Entry point to the callback called when matches are made.
  virtual void run(const clang::ast_matchers::MatchFinder::MatchResult &Result);

private:
  unsigned &AcceptedChanges;
  Transform &Owner;
};

#endif // CLANG_MODERNIZE_RAW_STRING_ACTIONS_H
