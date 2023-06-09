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

int Rectangle::rect_id() const { return id; }
int Rectangle::bot_y() const { return y; }
int Rectangle::top_y() const { return y + h; }
int Rectangle::left_x() const { return x; }
int Rectangle::right_x() const { return x + w; }
int Rectangle::width() const { return w; }
int Rectangle::height() const { return h; }

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

bool Rectangle::is_overlapping(Rectangle* other) {
    return this->right_x() > other->left_x() and other->right_x() > this->left_x() and this->top_y() > other->bot_y() and other->top_y() > this->bot_y();
}

bool Rectangle::is_adjacent(Rectangle& other) const {
    return right_x() == other.left_x() and ((bot_y() <= other.top_y() and other.top_y() <= top_y()) or (top_y() >= other.bot_y() and other.bot_y() >= bot_y()));
}

bool Rectangle::operator==(Rectangle& rhs) const {
    return left_x() == rhs.left_x() && right_x() == rhs.right_x() && bot_y() == rhs.bot_y() && top_y() == rhs.top_y();
}
