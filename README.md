# JUCE 6 Beta - Test Project

|                                                                    License                                                                     |                                                              Linux                                                              |                                                                macOS                                                                |                                                                                     Windows                                                                                      |                                                                  Coverage                                                                  |
| :--------------------------------------------------------------------------------------------------------------------------------------------: | :-----------------------------------------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------: |
| [![License](https://img.shields.io/badge/License-BSD%202--Clause-orange.svg)](https://github.com/tobanteAudio/juce-6-demo/blob/master/LICENSE) | [![CircleCi](https://circleci.com/gh/tobanteAudio/juce-6-demo.svg?style=svg)](https://circleci.com/gh/tobanteAudio/juce-6-demo) | [![Build Status](https://travis-ci.org/tobanteAudio/juce-6-demo.svg?branch=master)](https://travis-ci.org/tobanteAudio/juce-6-demo) | [![Build status](https://ci.appveyor.com/api/projects/status/oiu6ftj6oneneoro/branch/master?svg=true)](https://ci.appveyor.com/project/tobiashienzsch/juce-6-demo/branch/master) | [![codecov](https://codecov.io/gh/tobanteAudio/juce-6-demo/branch/master/graph/badge.svg)](https://codecov.io/gh/tobanteAudio/juce-6-demo) |

- [JUCE 6 Beta - Test Project](#juce-6-beta---test-project)
  - [Features](#features)
    - [ToDo](#todo)
  - [Quick Start](#quick-start)
  - [Tested On](#tested-on)
    - [Windows](#windows)
      - [Windows Issues](#windows-issues)
    - [Apple](#apple)
      - [Apple Issues](#apple-issues)
    - [Linux](#linux)
      - [Linux Issues](#linux-issues)
    - [General Issues](#general-issues)
  - [Suggestions](#suggestions)
    - [Split shared code cmake target](#split-shared-code-cmake-target)
      - [Example](#example)
      - [Fix](#fix)

## Features

- CMake build
- Catch2 unit tests
- Sanitizers
- Code coverage (lcov)
- CI (travis, appveyor & circleci)
- clang-format

### ToDo

- clang-tidy
- automatic packaging & signing

## Quick Start

Simple project testing the new beta branch of `JUCE` version 6. Reverb plugin based on the `JUCE` dsp classes. Links to unit tests written with `Catch2`. Tested on Windows, macOS & Linux.

JUCE now uses CMake. Awesome!

```sh
CONFIG=Release make
```

or:

```sh
cmake -S. -Bbuild
cmake --build build --config Release
cd build
ctest -C Release
```

## Tested On

### Windows

- Version 10.0.18362 Build 18362
- Visual Studio 2019 (16.5.3)
- CMake 3.16.2

#### Windows Issues

- **None**

### Apple

- Version 10.15.2
- Xcode 10.4
- CMake 3.16.4
  - Generators: Xcode, Ninja

#### Apple Issues

Setting LTO in cmake breaks build:

```cmake
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
```

### Linux

- PopOS (Ubuntu)
- GCC 9.2, Clang 9, Clang trunk
- CMake 3.17.2
  - Generators: Makefile, Ninja

#### Linux Issues

- **None**

### General Issues

- Linking test target to shared code does **not**:
  - set juce module include path
  - set NDEBUG or DEBUG (macOS)

## Suggestions

### Split shared code cmake target

Currently `JUCE` library code & user code are build in one CMake library target.
This becomes a problem using certain CMake features.

#### Example

Adding an interface target for compiler warnings will enable those warnings
on library code too. This makes the build output very noisy.

```cmake
add_library(compiler_warnings INTERFACE)
add_library(tobanteAudio::CompilerWarnings ALIAS compiler_warnings)
target_compile_options(compiler_warnings INTERFACE -Wall -Wextra -Wpedantic)
juce_add_plugin(Juce6DemoPlugin ...)
target_link_libraries(Juce6DemoPlugin PRIVATE tobanteAudio::CompilerOptions ...)
```

#### Fix

Split into 2 CMake targets:

- `JUCE` library code
- User shared code
