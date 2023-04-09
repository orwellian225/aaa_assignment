import argparse
import math as m
import numpy as np
import random

from draw_rectangles import draw_rectangles

class Rectangle:
    def __init__(self, rect_id, x, y, w, h):
        self.id = rect_id
        self.x = x
        self.y = y
        self.w = w
        self.h = h

    def print_rectangle(self, show_dimensions=False):
        if show_dimensions:
            print(self.id, "x:", self.x, "y:", self.y, "w:", self.w, "h:", self.h)
        else:
            print(self.id, "left x:", self.x, "bottom y:", self.y, "right x:", self.x + self.w, "top y:", self.y + self.h)

    def as_array(self, show_dimensions=False):
        if show_dimensions:
            return np.array([self.id, self.x, self.y, self.w, self.h])
        else:
            return np.array([self.id, self.x, self.y, self.x + self.w, self.y + self.h])

    def top_y(self):
        return self.y + self.h
    def right_x(self):
        return self.x + self.w

def has_overlap(rectangles, new_rect):
    for rect in rectangles:
        if (rect.right_x() > new_rect.x and new_rect.right_x() > rect.x) and (rect.top_y() > new_rect.y and new_rect.top_y() > rect.y):
            return True

    return False

def build_adjacencies_brute(rectangles):
    pass
    # for rect in rectangles:
    #     for other_rect in rectangles:

def main():
    parser = argparse.ArgumentParser(description = 'Generate Test data for AAA Assignment')
    parser.add_argument('data_name', metavar = 'name', help = 'The name of the generated rectangle set' )
    parser.add_argument('data_size', metavar = 'n', type = int, help = 'The number of rectangles to be generated')
    args = parser.parse_args()

    print('Name of data set', args.data_name)
    print('Number of rectangles', args.data_size)

    rectangles = []

    board_size = [args.data_size * 2, args.data_size * 2]

    x = 0
    y = 0
    w = random.randint(1, m.floor(board_size[0] / 2))
    h = random.randint(1, m.floor(board_size[1] / 2))
    rectangles.append(Rectangle(1, x, y, w, h))

    excessive_overlap_flag = False
    for i in range(1, args.data_size):
        print(f"\rrectangle {i + 1}/{args.data_size}", end = '')
        rect_id = i + 1

        origin_rect_idx = random.randint(0, len(rectangles) - 1)
        origin_rect = rectangles[origin_rect_idx]

        y_range = [origin_rect.y, origin_rect.top_y()]

        x = origin_rect.x
        y = random.randint(y_range[0], y_range[1])
        w = random.randint(1, m.floor(board_size[0] / 2))
        h = random.randint(1, m.floor(board_size[1] / 2))
        new_rect = Rectangle(rect_id, x, y, w, h)

        overlap_counter = 0
        while has_overlap(rectangles, new_rect):
            origin_rect_idx = random.randint(0, len(rectangles) - 1)
            origin_rect = rectangles[origin_rect_idx]
            x = origin_rect.right_x()
            y = random.randint(y_range[0], y_range[1])
            w = random.randint(1, m.floor(board_size[0] / 2))
            h = random.randint(1, m.floor(board_size[1] / 2))
            new_rect = Rectangle(rect_id, x, y, w, h)
            
            overlap_counter += 1
            if overlap_counter == 100000:
                excessive_overlap_flag = True
                break

        if excessive_overlap_flag:
            break
        rectangles.append(new_rect)

    rect_array = []
    for rect in rectangles:
        rect_array.append(rect.as_array())

    print()
    draw_rectangles(args.data_name, np.array(rect_array), board_size)
    

if __name__ == "__main__":
    main()
