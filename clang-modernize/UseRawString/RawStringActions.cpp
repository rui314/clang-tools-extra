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
/// \brief This file contains the definition of the UseRawStringFixer class
/// which is used as an ASTMatcher callback.
///
//===----------------------------------------------------------------------===//

#include "RawStringActions.h"
#include "RawStringMatchers.h"

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/CharInfo.h"
#include "clang/Lex/Lexer.h"
#include "llvm/ADT/Twine.h"

using namespace clang::ast_matchers;
using namespace clang::tooling;
using namespace clang;

namespace {
/// \brief Verifies that the token at \p BeginningOfToken is 'auto_ptr'.
bool checkTokenIsRawString(SourceLocation BeginningOfToken,
                           const SourceManager &SM,
                           const LangOptions &LangOptions) {
  llvm::SmallVector<char, 8> Buffer;
  bool Invalid = false;
  llvm::StringRef Res =
      Lexer::getSpelling(BeginningOfToken, Buffer, SM, LangOptions, &Invalid);
  if (Invalid)
    return false;
  return Res.startswith("R");
}

bool hasCloseParenAndDoubleQuote(StringRef Contents) {
  return Contents.find(")\"") != StringRef::npos;
}

std::string makeRawStringLiteral(StringRef Contents) {
  return (Twine("R\"(") + Contents + ")\"").str();
}

} // end anonymous namespace

void UseRawStringFixer::run(const ast_matchers::MatchFinder::MatchResult &Result) {
  const StringLiteral *Literal = Result.Nodes.getNodeAs<StringLiteral>(StringLiteralId);
  assert(Literal && "Bad Callback. No node provided");

  SourceManager &SM = Result.Context->getSourceManager();
  if (checkTokenIsRawString(Literal->getLocStart(), SM, LangOptions()))
    return;
  if (hasCloseParenAndDoubleQuote(Literal->getString()))
    return;

  CharSourceRange Range(Literal->getSourceRange(), true);
  std::string Replacement = makeRawStringLiteral(Literal->getString());
  Owner.addReplacementForCurrentTU(
      tooling::Replacement(SM, Range, Replacement));
  ++AcceptedChanges;
}
