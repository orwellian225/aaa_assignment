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

        int rect_id();
        int bot_y();
        int top_y();
        int left_x();
        int right_x();
        int width();
        int height();

        std::string to_string_dimension();
        std::string to_csv_dimension();
        std::string to_string_point();
        std::string to_csv_point();
};
