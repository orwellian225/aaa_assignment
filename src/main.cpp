#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <chrono>
#include <sys/stat.h>
#include <math.h>

#include "rectangle.h"
#include "adjacency.h"
#include "alg.h"

// Converting to string using c++11
template<typename... Args>
std::string Sprintf(const char *fmt, Args... args)
{
    const size_t n = snprintf(nullptr, 0, fmt, args...);
    std::vector<char> buf(n+1);
    snprintf(buf.data(), n+1, fmt, args...);
    return std::string(buf.data());
}

void make_dir(const char* name) {
    #ifdef __linux__
        mkdir(name, 777);
    #elif __APPLE__
        mkdir(name, 777);
    #else
        _mkdir(name);
    #endif
}

bool check_dir(const char* name) {
    struct stat sb;
    return stat(name, &sb) == 0 && S_ISDIR(sb.st_mode);
}

int main(int argc, char* argv[]) {

    // Argument List
    // * Test Name
    // * Test Size - The maximum number of rectangles to create in the test
    // * Test Sampling Rate - The number of times to repeat a time measurement at for a given set of rectangles
    if (argc != 5) {
        printf("Incorrect arguments provided\n");
        return -1;
    } 

    const char* test_name = argv[1];
    const int test_size = atoi(argv[2]);
    const int test_sampling_rate = atoi(argv[3]);
    const int example_count = atoi(argv[4]);

    if (sizeof(test_name) > 128) {
        printf("Invalid test name. Please use less than 256 characters");
        return -1;
    }

    if (example_count > 10 || example_count <= 0) {
        printf("Invalid example count. Please choose a number between 1 and 10\n");
        return -1;
    }

    char test_dir[128];
    snprintf(test_dir, 128, "%s", test_name);
    if (!check_dir(test_dir)) {
        char command[256];
        snprintf(command, 256, "mkdir %s", test_dir);
        system(command);
    }


    printf("Test Details\n");
    printf("============================================\n");
    printf("Name: %s\n", test_name);
    printf("Size: %d\n", test_size);
    printf("Sampling Rate: %d\n", test_sampling_rate);
    printf("Number of Examples: %d\n", example_count);
    printf("============================================\n\n");

    printf("Generating %d examples\n", example_count);
    printf("============================================\n");
    for (int i = 1; i < 1 + example_count; ++i) {
        printf("\rCurrent example: %d / %d - size: %d", i, example_count, (int) floor(pow(10.0, i))); 
        fflush(stdout);

        char filepath_example_data[1024];
        char filepath_example_result[1024];

        snprintf(filepath_example_data, 1024, "./%s/example_%d_data.csv", test_dir, i);
        snprintf(filepath_example_result, 1024, "./%s/example_%d_result.csv", test_dir, i);

        FILE* example_data = fopen(filepath_example_data, "w");
        FILE* example_result = fopen(filepath_example_result, "w");

        std::vector<Rectangle> rects = generate::appending((int) floor(pow(10.0, i)));
        std::vector<Adjacency> bf_result = alg::brute_force(rects);

        for (auto rect: rects) {
            fprintf(example_data, "%s\n", rect.to_csv_point().c_str());
        }

        for(auto adj: bf_result) {
            fprintf(example_result, "%s\n", adj.to_csv().c_str());
        }

        fclose(example_data);
        fclose(example_result);

        // Creating example data visualisation
        char data_vis_command[1024];
        snprintf(data_vis_command, 1024, "python3 util/draw_data.py %s example_%d", test_dir, i);
        system(data_vis_command);
    }
    printf("\n\n");

    printf("Executing Performance Test");
    printf("============================================\n");

    char filepath_test[1024];
    snprintf(filepath_test, 1024, "%s/performance_test_results.csv", test_dir);
    FILE* test_csv = fopen(filepath_test, "w");

    for (int i = 0; i < test_size; ++i) {
        printf("\rCurrent test: %d / %d", i + 1, test_size);
        fflush(stdout);

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
    }
    printf("\n\n");

    fclose(test_csv);
    
    char graph_command_buffer[1024];
    snprintf(graph_command_buffer, 1024, "python3 util/graph_generator.py 1 %s/performance_test_results.csv  %s/performance_test_graph", test_dir, test_dir);
    system(graph_command_buffer);

    return 0;
}
