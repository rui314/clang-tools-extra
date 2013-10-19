// RUN: grep -Ev "// *[A-Z-]+:" %s > %t.cpp
// RUN: clang-modernize -use-raw-string %t.cpp -- -I %S -std=c++11 \
// RUN:   -Wno-unused-value
// RUN: FileCheck -input-file=%t.cpp %s

void foo() {
  "\\\\t|\\\\n";
  // CHECK: R"(\\t|\\n)"

  "";
  // CHECK: ""

  "abc\\def";
  // CHECK: "abc\\def"

  "\\ \\ \\ \t";
  // CHECK: "\\ \\ \\ \t"

  R"(abc)";
  // CHECK: R"(abc)"

  R"*(\\t|\\n)*";
  // CHECK: R"*(\\t|\\n)*"

  L"\\ \\t \\ \\n";
  // CHECK: L"\\ \\t \\ \\n"
};
