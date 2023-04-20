#include <stdio.h>
#include <time.h>
#include <vector>
#include <random>
#include <iostream>

#include "rectangle.h"
#include "adjacency.h"

bool has_overlap(std::vector<Rectangle>& rects, Rectangle* new_rect) {
    bool result = false;

    for (auto rect: rects) {
        result = result || new_rect->is_overlapping(&rect);

        if (result) 
            break;
    }

    return result;
}

namespace generate {
    std::vector<Rectangle> appending(std::size_t size) {

        std::mt19937 rng_engine;
        rng_engine.seed((unsigned)time(NULL));

        // The range of values possible for any dimension (x & y)
        uint8_t dim_min = 5;
        uint8_t dim_max = 200;
        std::uniform_int_distribution<uint8_t> rect_dims(dim_min, dim_max);

        std::vector<Rectangle> rects;

        // Create a random rectangle at origin
        Rectangle origin_rect = Rectangle(0, 0, 0, rect_dims(rng_engine), rect_dims(rng_engine));
        rects.push_back(origin_rect);

        // Start at 1 as first rectangle has already been made
        size_t i = 1;
        while (i < size) {
            // printf("\rGenerating rectangle %ld / %ld", i + 1, size);
            size_t rect_id = i;

            std::uniform_int_distribution<size_t> spawn_rect_dist(0, rects.size() - 1);
            Rectangle* spawn_rect = &rects[spawn_rect_dist(rng_engine)];

            std::uniform_int_distribution<uint16_t> possible_y(spawn_rect->bot_y(), spawn_rect->top_y() - 1);
            Rectangle new_rect = Rectangle(rect_id, spawn_rect->right_x(), possible_y(rng_engine), rect_dims(rng_engine), rect_dims(rng_engine));

            if (!has_overlap(rects, &new_rect)) {
                ++i;
                rects.push_back(new_rect);
            }
        }

        // printf("\n");
        return rects;
    }
}

namespace alg {
    std::vector<Adjacency> brute_force(std::vector<Rectangle>& rects) {

        std::vector<Adjacency> results;

        for (auto r1: rects) {
            Adjacency current_adj(&r1);
            for (auto r2: rects) {
                if (r1 == r2) { continue; }
                if (r1.is_adjacent(r2)) { 
                    Rectangle* test = &r1;
                    // printf("%d : %s\n", r1.rect_id(), r2.to_string_point().c_str());
                    current_adj.add_adj(&r2);
                }
            }

            results.push_back(current_adj);
        }

        return results;
    }
}
