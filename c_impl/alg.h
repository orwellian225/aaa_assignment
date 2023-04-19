#pragma once

#include <vector>

#include "rectangle.h"
#include "adjacency.h"

namespace generate {
    std::vector<Rectangle> appending(size_t size);
    std::vector<Rectangle> subdivision(size_t size);
}

namespace alg {
    std::vector<Adjacency> brute_force(std::vector<Rectangle>& rects);
    std::vector<Adjacency> optimised(std::vector<Rectangle>& rects);
}
