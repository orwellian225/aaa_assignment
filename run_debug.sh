#!/bin/bash

g++ --std=c++11 src/*.cpp -Iinclude -o main.o -g3 -O0
./main.o TEST_DEBUG 100 1 2
