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
    tiff_io_framework
    tiff_io_framework.c
    ${GSL_FRAMEWORK_SOURCES}
)
set_target_properties(
    tiff_io_framework
    PROPERTIES
    C_CLANG_TIDY
    "${CLANG_TIDY_COMMAND}"
    )
target_compile_features (tiff_io_framework PRIVATE c_std_11)
target_link_libraries (
    tiff_io_framework
    LINK_PRIVATE
    argparse
    gsl
    libtiff
    )
