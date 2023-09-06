
# For more information about using CMake read the documentation on:
#   * https://cmake.org/cmake/help/latest/guide/tutorial/index.html
#   * https://cliutils.gitlab.io/modern-cmake/chapters/basics.html
#   * https://cmake.org/examples/

cmake_minimum_required (VERSION 3.15...3.40)

project (
    CLI_Framework
    VERSION 0.1
    DESCRIPTION "A framework to build CLI applications in C"
    LANGUAGES C
    )

# Only do these if this is the main project, and not if it is included through
# add_subdirectory
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Append custom flags
    if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
        add_compile_options (-v -Wall -Wextra -pedantic -fcolor-diagnostics
            -fdiagnostics-format=vi)
    endif ()

endif ()

# Check if the external dependencies are available
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extern/argparse)
    # We can safely add the subdirectory here, since we know it exists
    add_subdirectory (extern/argparse)
else ()
    message (FATAL_ERROR "External library 'argparse' not found ...")
endif ()
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extern/gsl)
    # We can safely add the subdirectory here, since we know it exists
    add_subdirectory (extern/gsl)
else ()
    message (FATAL_ERROR "External library 'gsl' not found ...")
endif ()
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/extern/libtiff)
    # We can safely add the subdirectory here, since we know it exists
    add_subdirectory (extern/libtiff)
else ()
    message (FATAL_ERROR "External library 'libtiff' not found ...")
endif ()

# Add the source code
add_subdirectory (src)
