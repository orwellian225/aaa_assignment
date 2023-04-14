#include <stdio.h>
#include <stdlib.h>

struct Rectangle {
    int id;
    int x;
    int y;
    int w;
    int h;
};
int right_x(const struct Rectangle* rect) { return rect->x + rect->w; }
int top_y(const struct Rectangle* rect) { return rect->y + rect->h; }
void save_points(const struct Rectangle* rect, FILE* file) { fprintf(file, "%d,%d,%d,%d,%d\n", rect->id, rect->x, rect->y, rect->w, rect->h); }
void print_points(const struct Rectangle* rect) { printf("rect_id: %d, lx: %d, by: %d, rx: %d, ty: %d\n", rect->id, rect->x, rect->y, right_x(rect), top_y(rect)); }
void print_dimensions(const struct Rectangle* rect) { printf("rect_id: %d, x: %d, y: %d, w: %d, h: %d\n", rect->id, rect->x, rect->y, rect->w, rect->h); }

struct Adjacencies {
    const struct Rectangle* rect;
    const struct Rectangle** adj_rects;
};
void print_adj(const struct Adjacencies* adj) { 
    printf("%d,%ld", adj->rect->id, sizeof(adj->adj_rects));
}

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

    const struct Rectangle test_rects[11] = {
        {1, 0, 0, 3, 7},
        {2, 1, 8, 2, 3},
        {3, 3, 0, 1, 1},
        {4, 3, 1, 7, 1},
        {5, 3, 6, 2, 3},
        {6, 5, 6, 1, 1},
        {7, 5, 8, 1, 2},
        {8, 6, 9, 2, 2},
        {9, 10, 1, 1, 2},
        {10, 11, 2, 1, 2},
        {11, 12, 3, 1, 2}
    };

    const struct Adjacencies test_adj = {
        &test_rects[0],
        {&test_rects[1], &test_rects[2]}
    };

    print_adj(&test_adj);

    fclose(test_csv);
}
