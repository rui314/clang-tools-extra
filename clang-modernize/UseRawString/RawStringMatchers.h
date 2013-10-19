//===-- UseRawString/RawStringMatchers.h - Matchers for string --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief This file contains the declarations for matcher-generating functions
/// and names for bound nodes found by AST matchers.
///
//===----------------------------------------------------------------------===//

#ifndef CLANG_MODERNIZE_RAW_STRING_MATCHERS_H
#define CLANG_MODERNIZE_RAW_STRING_MATCHERS_H

#include "clang/ASTMatchers/ASTMatchers.h"

// Names to bind with matched expressions.
extern const char *StringLiteralId;

/// \brief Create a matcher that finds string literals.
clang::ast_matchers::StatementMatcher makeStringLiteralMatcher();

#endif // CLANG_MODERNIZE_RAW_STRING_MATCHERS_H
