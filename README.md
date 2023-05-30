# Advanced Analysis of Algorithms Assignment

## Executing Code

### Requirements

* GCC Compiler
* c++ 11 standard library

### Compiling 

```
g++ --std=c++11 -g src/*.cpp -Iinclude -o main.o
```

### Running
```
./main.o <TEST_NAME> <TEST_SIZE> <TEST_SAMPLING> <TEST_EXAMPLES>
```

* <TEST_NAME> - The name of the test
* <TEST_SIZE> - The max size to run the performance tests up to
* <TEST_SAMPLING> - The number of times to execute a performance test and calculate and average from
* <TEST_EXAMPLES> - The number of examples to generate, each subsequent example is an order of magnitude greater in size

## Data

A set of rectangles in a 2D environment.

### Generation

1. Create a rectangle at origin (0,0) with random dimensions
2. Select a random rectangle that already exists
3. Create a new rectangle constrained to be right side adjacent to the selected rectangle
4. Check if the newly created rectangle overlaps with any other rectangles
    1. If the new rectangle overlaps, go to step 2 without incrementing the number of rectangles counter
    2. If the new rectangle doesn't overlap
        1. Save the rectangle
        2. Increment rectangle counter
5. If the desired number of rectangles has be created then stop, else go to step 2

## Algorithm

### Brute force / Naive

2. Iterate through each rectangle as rect1
3. Iterate through each other rectangle as rect2
4. if rect2 is adjacent to rect1's right side, then add rect2 to rect1's adjacencies
