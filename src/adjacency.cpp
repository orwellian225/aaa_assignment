#include <string>
#include <vector>

#include "adjacency.h"
#include "rectangle.h"

// Converting to string using c++11
template<typename... Args>
std::string Sprintf(const char *fmt, Args... args)
{
    const size_t n = snprintf(nullptr, 0, fmt, args...);
    std::vector<char> buf(n+1);
    snprintf(buf.data(), n+1, fmt, args...);
    return std::string(buf.data());
}

Adjacency::Adjacency(Rectangle* rect) {
    this->rect = rect;
}

void Adjacency::add_adj(Rectangle* adj_rect) {
    adjs.push_back(adj_rect);
}

std::string Adjacency::to_string() {
    std::string result = Sprintf("rect %d with %d adjacencies\n\t", rect->rect_id(), adjs.size());

    for (auto rect: adjs) {
        result += Sprintf("rect %d, x: %d, by: %d, ty: %d\n\t", rect->rect_id(), rect->right_x(), rect->bot_y(), rect->top_y());
    }

    return result;
}

std::string Adjacency::to_csv() {
    std::string result = Sprintf("%d,%d,", rect->rect_id(), adjs.size());

    for (auto rect: adjs) {
        result += Sprintf("%d,%d,%d,%d,", rect->rect_id(), rect->right_x(), rect->bot_y(), rect->top_y());
    }

    return result;
}
