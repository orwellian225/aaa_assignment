#pragma once

#include <string>
#include <vector>

#include "rectangle.h"

class Adjacency {
    private:
        Rectangle* rect;
        std::vector<Rectangle*> adjs;

    public:
        Adjacency(Rectangle* rect);

        void add_adj(Rectangle* adj_rect);

        std::string to_string();
        std::string to_csv();
};
