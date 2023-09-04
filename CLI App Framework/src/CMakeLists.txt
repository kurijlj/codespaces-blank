# Find clang-tidy if available
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

# Set clang-tidy arguments
if(CLANG_TIDY_EXE)
    set(
        CLANG_TIDY_COMMAND
        "${CLANG_TIDY_EXE}"
        "clang-diagnostic-*,clang-analyzer-*,readability-*,performance-*"
        )
endif()

add_executable (
    cli_framework
    cli_framework.c
    ${GSL_FRAMEWORK_SOURCES}
)
set_target_properties(
    cli_framework
    PROPERTIES
    C_CLANG_TIDY
    "${CLANG_TIDY_COMMAND}"
    )
target_compile_features (cli_framework PRIVATE c_std_11)
target_link_libraries (
    cli_framework
    LINK_PRIVATE
    argparse
    gsl
    )
