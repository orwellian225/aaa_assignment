#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "rectangle.h"
#include "adjacency.h"
#include "alg.h"

int main(int argc, char* argv[]) {

    // Argument List
    // * Test Name
    // * Test Size - The maximum number of rectangles to create in the test
    // * Test Sampling Rate - The number of times to repeat a time measurement at for a given set of rectangles
    if (argc != 4) {
        printf("Incorrect arguments provided\n");
        return -1;
    } 

    const char* test_name = argv[1];
    const int test_size = atoi(argv[2]);
    const int test_sampling_rate = atoi(argv[3]);

    if (sizeof(test_name) > 256) {
        printf("Invalid test name. Please use less than 256 characters");
        return -1;
    }

    char filename_buffer[260];
    sprintf(filename_buffer, "%s.csv", test_name);
    FILE* test_csv = fopen(filename_buffer, "w");

    printf("Test Details\n============================================\n");
    printf("Name: %s\n", test_name);
    printf("Size: %d\n", test_size);
    printf("Sampling Rate: %d\n", test_sampling_rate);
    printf("============================================\n");

    std::vector<Rectangle> rects = generate::appending(test_size);
    // for (auto rect: rects) {
    //     printf("%s\n", rect.to_string_point().c_str());
    // }

    std::vector<Adjacency> bf_result = alg::brute_force(rects);
    for(auto adj: bf_result) {
        printf("%s\n", adj.to_string().c_str());
    }

    fclose(test_csv);
}
