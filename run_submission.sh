#!/bin/bash

g++ --std=c++11 src/*.cpp -Iinclude -o main.o -g3 -O0
./main.o SUBMISSION 1000 100 3
