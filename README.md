# wsd-485c

## Overview

This repository contains the implementation and optimization efforts of the
Simplified Sense Word Disambiguation (WSD) algorithm written in C++ as part of
UVic's CSC485C course project. This project belongs to:
[Ahmed Siddiqui](mailto:jesuisahmedn@gmail.com) and
[Jordan Kirchner](mailto:JordanKirchner04@hotmail.com)

## Implementation

The algorithm implementated is based on the simplified version of
[Michael Lesk's algorithm](https://en.wikipedia.org/wiki/Lesk_algorithm#Simplified_Lesk_algorithm)
devised in 1986.

# Running the program 

This project has a Makefile that does a lot of the heavy lifting for you.

If you want to run benchmarks on the implemented algorithm, you will first need
to download the dependencies of this project. Run `make dependencies` and the
appropriate libaries will be installed. Then you need to run `make install_benchmark`
to install google's benchmark library. Then, you will need to build the executable
You can do this simply by either doing `make unoptimized` (in your terminal in
the root of the directory) to build the unoptimized, baseline version of the
implemented algorithm, or you can run `make optimized` to build the optimized
version of your implemented algorithm. After running either of those, just run
`make` or `make run` to run the executable and get the runtime for 100 iterations
of the implemented algorithm. 