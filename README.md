# JUCE 6 Beta - Test Project
|                                                            License                                                             |                                                       Linux/macOS                                                       |                                                                   Windows                                                                    |                                                            Coverage                                                           |
| :----------------------------------------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------:|
| [![License](https://img.shields.io/badge/License-BSD%202--Clause-orange.svg)](https://github.com/tobanteAudio/juce-6-demo/blob/master/LICENSE) | [![Build Status](https://travis-ci.org/tobanteAudio/juce-6-demo.svg?branch=master)](https://travis-ci.org/tobanteAudio/juce-6-demo) | | [![codecov](https://codecov.io/gh/tobanteAudio/juce-6-demo/branch/master/graph/badge.svg)](https://codecov.io/gh/tobanteAudio/juce-6-demo) |
Simple project testing the new beta branch of `JUCE` version 6. Reverb plugin based on the `JUCE` dsp classes. Links to unit tests written with `Catch2`. Tested on Windows, macOS & Linux.

## Quick Start

JUCE now uses CMake. Awesome!

```sh
CONFIG=Release make
```

### Or

```sh
cmake -S. -Bbuild
cmake --build build --config Release
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
