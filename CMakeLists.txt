add_subdirectory(clang-apply-replacements)
add_subdirectory(clang-modernize)
add_subdirectory(clang-tidy)
add_subdirectory(modularize)
add_subdirectory(remove-cstr-calls)
add_subdirectory(tool-template)

# Add the common testsuite after all the tools.
add_subdirectory(test)
add_subdirectory(unittests)
