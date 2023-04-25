#pragma once

#include <string>

class Rectangle {
    private:
        int id;
        int x;
        int y;
        int w;
        int h;

    public:
        Rectangle(int id, int x, int y, int w, int h);  

        int rect_id() const;
        int bot_y() const;
        int top_y() const;
        int left_x() const;
        int right_x() const;
        int width() const;
        int height() const;

        std::string to_string_dimension();
        std::string to_csv_dimension();
        std::string to_string_point();
        std::string to_csv_point();

        bool is_overlapping(Rectangle* other);
        bool is_adjacent(Rectangle& other) const;

        bool operator==(Rectangle& rhs) const;
};
