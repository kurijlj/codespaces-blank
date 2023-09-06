# TIFF IO Framework

**TIFF IO Framework:**

## Table of Contents
 - [Features](#features)
 - [Objectives](#objectives)
 - [Dependencies](#dependencies)
 - [Compiling Instructions](#compiling-instructions)

## Features

## Objectives
 - Explore how 'libtiff's' API work
 - Devise a minimum viable code to handle file reading, file writing and error
   handling.

## Dependencies
1. [**argparse**](https://github.com/cofyc/argparse.git) - A command line
   arguments parsing library in C (compatible with C++)
2. [**GSL**](https://github.com/ampl/gsl.git) - The GNU Scientific library with
   CMake build system
3. [**libtiff**](https://gitlab.com/libtiff/libtiff) - TIFF Library and Utilities

## Compiling Instructions
Build as a regular CMake project. Create a build directory and `cd` into it.
Then create a directory structure and makefiles using:

### Debug
1. **\*NIX platforms:**
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=False -DBUILD_TESTING=False -DNO_AMPL_BINDINGS=True -S <source-path> -B .
$ cmake --build . --config Debug --target cli_framework
```
or
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=False -DBUILD_TESTING=False -DNO_AMPL_BINDINGS=True -S <source-path> -B .
$ make
```

2. **Win64 platform:**
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=False -DBUILD_TESTING=False -DNO_AMPL_BINDINGS=True -S <source-path> -B .
$ cmake --build . --config Debug --target cli_framework
```
or
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=False -DBUILD_TESTING=False -DNO_AMPL_BINDINGS=True -S <source-path> -B .
$ msbuild.exe cli_framework.sln
```

### Release
1. **\*NIX platforms:**
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Release -DNO_AMPL_BINDINGS=True -S <source-path> -B .
$ cmake --build . --config Release --target cli_framework
```
or
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Release -DNO_AMPL_BINDINGS=True -S <source-path> -B .
$ make
```

2. **Win64 platform:**
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Release -DNO_AMPL_BINDINGS=True -S <source-path> -B .
$ cmake --build . --config Release --target cli_framework
```
or
```
$ cmake -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Release -DNO_AMPL_BINDINGS=True -S <source-path> -B .
$ msbuild.exe cli_framework.sln
```

### Build Options
```
-DCMAKE_C_COMPILER=(clang-c/cl/gcc/...)
-DCMAKE_BUILD_TYPE=(Debug/RelWithDebInfo/Release/MinSizeRel)
-DBUILD_SHARED_LIBS:BOOL=(TRUE/FALSE)
-DBUILD_TESTING:BOOL=(TRUE/FALSE)
-G ("NMake Makefiles"/"Unix Makefiles"/...)
```

### GSL Specific Instructions
For GSL specific build instructions see:
[gsl/README.md](https://github.com/ampl/gsl#readme)