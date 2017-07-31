# SDL2 Modular Concurrent Graphical Toolkit

### Description

This project is a work in progress; it is an attempt to make a concurrent
graphical toolkit that is fully modular. In the file `src/modular.cpp`, an
example currently shows the use of two 'tasks', Frame (a window container with
a monotonic signal progression from 'start' to 'pass', 'error', and 'quit')
and Driver (which supplements monotonic tasks with loops and inserts delay via
callback). In the future, tasks will be categorized by concern
(model/view/control, etc.) and by dependence so that independent tasks can be
run concurrently. The plan is to use a hierarchy of timed mutexes with
contingencies for timeouts, simulating the 'thread pool' design pattern.

### Requirements

Strict requirements:
<ul>
	<li>SDL2 (Simple DirectMedia Layer, 2.0 or greater)
	<li>A compiler with support for C++11
</ul>
Extra requirements:
<ul>
	<li>Doxygen - for generating documentation from formatted comments
</ul>

The compiler used for development and testing is GCC 5.4.0 with POSIX threads
for x86_64-linux-gnu. Clang will almost certainly work as an alternative.
32-bit Linux, Mac OS, Windows, and other environments are not tested
whatsoever. Cross-platform development and testing is premature but
portability is certainly a goal even this early in development.

### Structure

```
Makefile             Template definitions and rules for core project
Makefile.conf        Parameters for Makefile
Doxygen.mk           Parameters for Makefile and Doxygen
.clang_complete      Clang Complete autocomplete flags
include              Header declarations
    `-- *.hpp
impl                 Header implementations, specializations, etc.
    `-- *.tpp
src                  Source implementations 
    `-- *.cpp
release              Release build destination
|-- bin              Executable destination
|   |-- modular
|   |-- README.md
|-- dep              Generated ependency files
|   |-- *.d
|   |-- README.md
|-- lib              Shared libraries
|   |-- lib*.so
|   |-- lib*.a
|   |-- *.o
|   |-- README.md
|-- obj              Executable and non-shared object files
|   |-- *.o
|   `-- README.md
`-- doc              Documentation destination
    |-- html         HTML output
    |-- man          Man page output
    |-- latex        Latex output
    `-- Doxyfile     Generated Doxygen config file
```

### Makefile
Basic usage:

`make` -> default target (release/bin/modular)

`make clean` -> remove .so, .a, .o, .d

`make doc` -> doc/Doxyfile and documents if missing
