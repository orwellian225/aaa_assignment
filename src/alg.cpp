#include <stdio.h>
#include <time.h>
#include <vector>
#include <random>
#include <iostream>
#include <set>
#include <algorithm>

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

        for (int i = 0; i < rects.size(); ++i) {
            Adjacency current_adj(&rects[i]);
            for (int j = 0; j < rects.size(); ++j) {
                if ( rects[i] == rects[j]) { continue; }
                if (rects[i].is_adjacent(rects[j])) { 
                    Rectangle* test = &rects[i];
                    current_adj.add_adj(&rects[j]);
                }
            }

            results.push_back(current_adj);
        }

        return results;
    }

    struct ep_t { // Event point struct
        char type; // 0 = Left x, 1 = Right x
        Rectangle& rect;
    };
    auto rect_cand_compare = [](Rectangle* lhs, Rectangle* rhs) {
        return lhs->bot_y() < rhs->bot_y();
    };

    std::vector<Adjacency> optimised(std::vector<Rectangle>& rects) {

        std::vector<ep_t> event_points;
        for (size_t i = 0; i < rects.size(); ++i) {
            event_points.push_back(ep_t {
                0,
                rects[i]
            });

            event_points.push_back(ep_t {
                1,
                rects[i]
            });
        }

        std::sort(event_points.begin(), event_points.end(), [](ep_t a, ep_t b) {
            return a.rect.left_x() < b.rect.left_x() || a.type < b.type || a.rect.bot_y() < b.rect.bot_y();
        });

        std::vector<Adjacency> results;

        std::set<Rectangle*, decltype(rect_cand_compare)> candidates;
        for (auto ep: event_points) {

            if (ep.type == 0) { // If left x val of rect
                candidates.insert(&ep.rect);
            } else {
                candidates.erase(&ep.rect);
                Adjacency current_adj(&(ep.rect));
                auto first_el = candidates.lower_bound(&ep.rect);

                for (auto el = first_el; el != candidates.end(); ++el) {
                    Rectangle* rect = *el;
                    if (ep.rect.is_adjacent(*rect)) {
                        current_adj.add_adj(rect);
                    }
                }

                results.push_back(current_adj);
            }

        }

        return results;
    }
}
