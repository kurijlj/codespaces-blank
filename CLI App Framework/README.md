# CLI Framework Project

**CLI App Framework:** This project is a collection of C code that provides a
versatile framework for constructing command-line interface applications in C.
It leverages the CMake build system for seamless integration and utilizes the
argparse argument parsing library for easy and efficient command-line argument
handling. This framework simplifies the development process, making it easier to
create robust and user-friendly command-line applications in C.

## Table of Contents
 - [Features](#features)
 - [Objectives](#objectives)
 - [Dependencies](#dependencies)
 - [Compiling Instructions](#compiling-instructions)

## Features
 - Command-line argument parsing with argparse.
 - Mathematical operations using the GNU Scientific Library (GSL).
 - Versatile and extensible architecture for building CLI applications in C.

## Objectives
 - To provide a well-formatted and easy-to-use basis for writing
   CLI applications for different platforms.
 - To streamline the process of developing CLI applications in C, enabling
   developers to focus on application logic rather than low-level details.
 - To offer a flexible framework that can be adapted for a wide range of CLI
   application use cases, from simple utilities to complex
   scientific simulations.
 - To promote good coding practices, code reusability, and maintainability in
   CLI application development.

## Dependencies
1. [**argparse**](https://github.com/cofyc/argparse.git) - A command line
   arguments parsing library in C (compatible with C++)
2. [**GSL**](https://github.com/ampl/gsl.git) - The GNU Scientific library with
   CMake build system

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