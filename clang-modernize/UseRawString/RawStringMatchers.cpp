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
/// \brief This file contains the definitions for matcher-generating functions
/// and a custom AST_MATCHER for identifying string literals.
///
//===----------------------------------------------------------------------===//

#include "RawStringMatchers.h"
#include "clang/AST/ASTContext.h"
#include "clang/Lex/Lexer.h"
#include "llvm/ADT/SmallVector.h"

#include <cctype>

using namespace clang;
using namespace clang::ast_matchers;

const char *StringLiteralId = "string-literal";

namespace clang {
namespace ast_matchers {
AST_MATCHER(StringLiteral, isAscii) {
  return Node.isAscii();
}

AST_MATCHER(StringLiteral, isPrint) {
  StringRef Str = Node.getString();
  for (int i = 0, e = Str.size(); i != e; ++i)
    if (!isprint(Str[i]))
      return false;
  return true;
}

AST_MATCHER(StringLiteral, containsThreeOrMoreBackslahses) {
  StringRef Str = Node.getString();
  int Count = 0;
  for (int i = 0, e = Str.size(); i != e; ++i)
    if (Str[i] == '\\')
      ++Count;
  return Count >= 2;
}
}
}

StatementMatcher makeStringLiteralMatcher() {
  return stringLiteral(allOf(
      isAscii(), isPrint(), containsThreeOrMoreBackslahses()))
      .bind(StringLiteralId);
}
