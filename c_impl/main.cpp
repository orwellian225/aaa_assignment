#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <chrono>

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
    snprintf(filename_buffer, 260, "%s.csv", test_name);
    FILE* test_csv = fopen(filename_buffer, "w");

    printf("Test Details\n============================================\n");
    printf("Name: %s\n", test_name);
    printf("Size: %d\n", test_size);
    printf("Sampling Rate: %d\n", test_sampling_rate);
    printf("============================================\n");

    std::vector<Rectangle> rects = generate::appending(test_size);
    for (auto rect: rects) {
        printf("%s\n", rect.to_string_point().c_str());
    }

    std::vector<Adjacency> bf_result = alg::brute_force(rects);
    for(auto adj: bf_result) {
        printf("%s\n", adj.to_string().c_str());
    }

    for (int i = 0; i < test_size; ++i) {

        std::chrono::duration<double, std::milli> sum_time = std::chrono::seconds(0);
        for (int j = 0; j < test_sampling_rate; ++j) {
            std::vector<Rectangle> rects = generate::appending(i);

            auto start_time = std::chrono::high_resolution_clock::now();
            std::vector<Adjacency> result = alg::brute_force(rects);
            auto end_time = std::chrono::high_resolution_clock::now();
            sum_time += end_time - start_time;
        }

        std::chrono::duration<double, std::milli> average_time = sum_time / test_sampling_rate;
        fprintf(test_csv, "%d,%f\n", i, average_time.count());
        printf("\rCurrent Size: %d", i);
    }
    printf("\n");

    fclose(test_csv);
}
