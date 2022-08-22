# Matrix Routines

### Table of Contents
* [Introduction](#introduction)
* [Goals](#goals)
* [Build](#build)
* [Tests](#tests)

### Introduction

Implementation of simple matrix processing routines
- Creating a matrix with required sizes
- Removing a matrix
- Comparing matrices
- Sum of matrices
- Subtraction of matrices
- Multiplication of matrices
- Transpose of a matrix
- Determinant of a matrix
- Inverse of a matrix
- Complements matrix

### Goals
- [ ] Learn matrix operations and implementations
- [ ] Object oriented programming
- [ ] Get familiar with CMake
- [ ] Implement tests for the library using gtest

### Build

```
$ git clone https://github.com/bezlant/s21_matrix_cpp
$ cd s21_matrix_routines/src
$ mkdir build && cd build 
$ cmake ..
```

### Tests
* Unit tests are implemented using [googletest](https://google.github.io/googletest/) & coverage report with [llvm-cov](https://llvm.org/docs/CommandGuide/llvm-cov.html)
