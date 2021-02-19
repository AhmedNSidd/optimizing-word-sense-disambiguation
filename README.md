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

Create an executable using the following command:
`g++ simplified_wsd.cpp -I/usr/local/Cellar/nlohmann-json/3.7.3/include -std=c++11 -o output`

Or alternatively build an object file:
`g++ simplified_wsd.cpp -I/usr/local/Cellar/nlohmann-json/3.7.3/include -std=c++11 -c -o output.o`

And using this object file, you can create a library of the WSD program. 

`ar rcs wsd.a output.o`

Finally, you can use this wsd library to compile with the microbenchmarking
program for microbenchmarking:

`g++ benchmark.cc -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark wsd.a`

And then just run the executable:

`./mybenchmark`