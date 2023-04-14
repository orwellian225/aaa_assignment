#include <string>
#include <vector>

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

Rectangle::Rectangle(int id, int x, int y, int w, int h) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

int Rectangle::bot_y() { return y; }
int Rectangle::top_y() { return y + h; }
int Rectangle::left_x() { return x; }
int Rectangle::right_x() { return x + w; }
int Rectangle::width() { return w; }
int Rectangle::height() { return h; }

std::string Rectangle::to_string_dimension() {
    return Sprintf("rect %d, x: %d, y: %d, w: %d, h: %d", id, x, y, w, h);
}

std::string Rectangle::to_csv_dimension() {
    return Sprintf("%d,%d,%d,%d,%d", id, x, y, w, h);
}

std::string Rectangle::to_string_point() {
    return Sprintf("rect %d, lx: %d, by: %d, rx: %d, ty: %d", id, x, y, right_x(), top_y());
}

std::string Rectangle::to_csv_point() {
    return Sprintf("%d,%d,%d,%d,%d", id, x, y, right_x(), top_y());
}
