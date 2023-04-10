import math as m
import random
import matplotlib.patches as patches
import matplotlib.pyplot as plt

class Rectangle:
    def __init__(self, rect_id, x, y, w, h):
        self.id = rect_id
        self.x = x
        self.y = y
        self.w = w
        self.h = h
        self.adj_rects = []

    def __str__(self) -> str:
        return f"{self.id} x: {self.x} y: {self.y} w: {self.w} h: {self.h}"

    def __eq__(self, other):
        # return self.tr_x == other.bl_x and ((self.bl_y <= other.tr_y and other.tr_y <= self.tr_y) or (self.tr_y >= other.bl_y and other.bl_y >= self.bl_y))
        return self.right_x() == other.x and ((self.y <= other.top_y() and other.top_y() <= self.top_y()) or (self.top_y() >= other.y and other.y >= self.y))

    def __lt__(self, other):
        return self.x < other.x

    def add_adj(self, adj_rect):
        self.adj_rects.append(adj_rect)

    def adj_to_csv_string(self):
        result = f"{self.id},{len(self.adj_rects)},"

        for rect in self.adj_rects:
            result += f"{rect.id},{rect.x},{rect.y},{rect.top_y()},"

        return result

    def to_string(self, show_dimensions=False):
        if show_dimensions:
            return f"{self.id} x: {self.x} y: {self.y} w: {self.w} h: {self.h}"
        else:
            return f"{self.id} left x: {self.x} bottom y: {self.y} right x: {self.right_x()} top y: {self.top_y()}"

    def as_array(self, show_dimensions=False):
        if show_dimensions:
            return [self.id, self.x, self.y, self.w, self.h]
        else:
            return [self.id, self.x, self.y, self.x + self.w, self.y + self.h]

    def top_y(self):
        return self.y + self.h
    def right_x(self):
        return self.x + self.w

def generate_rect(id, x, y_min, y_max, w_min, w_max, h_min, h_max):
    x = x
    y = random.randint(y_min, y_max)
    w = random.randint(w_min, w_max)
    h = random.randint(h_min, h_max)

    return Rectangle(id, x, y, w, h)

def has_overlap(rectangles, new_rect):
    for rect in rectangles:
        if (rect.right_x() > new_rect.x and new_rect.right_x() > rect.x) and (rect.top_y() > new_rect.y and new_rect.top_y() > rect.y):
            return True

    return False

def draw_rectangle(rectangle, axes):
    rect_patch = patches.Rectangle(
        (rectangle.x, rectangle.y), rectangle.w, rectangle.h,
        linewidth=1, edgecolor='r', facecolor='none'
    )
    axes.add_patch(rect_patch)
    axes.text(rectangle.x + rectangle.w / 2, rectangle.y + rectangle.h / 2, rectangle.id, weight='bold', fontsize=5, ha='center', va='center')

def draw_rectangles(name, rectangles, board_size):
    fig, ax = plt.subplots()
    plt.xlim([0, board_size[0] * 10])
    plt.ylim([0, board_size[1] * 10])
    for rectangle in rectangles:
        draw_rectangle(rectangle, ax)
    
    plt.savefig(f"{name}.pdf")
    plt.close()

def generate_rectangles(board_size, data_size):

    w_min = 5
    w_max = m.floor(board_size[0] / 2)
    h_min = 5
    h_max = m.floor(board_size[0] / 2)

    rectangles = []

    rectangles.append(generate_rect(1, 0, 0, 0, w_min, w_max, h_min, h_max))

    excessive_overlap_flag = False
    for i in range(1, data_size):
        # print(f"\rgenerating rectangle {i + 1}/{data_size}", end = '')
        rect_id = i + 1

        origin_rect_idx = random.randint(0, len(rectangles) - 1)
        origin_rect = rectangles[origin_rect_idx]
        y_min = origin_rect.y
        y_max = origin_rect.top_y() - 1;
        new_rect = generate_rect(rect_id, origin_rect.right_x(), y_min, y_max, w_min, w_max, h_min, h_max)

        overlap_counter = 0
        while has_overlap(rectangles, new_rect):
            origin_rect_idx = random.randint(0, len(rectangles) - 1)
            origin_rect = rectangles[origin_rect_idx]
            y_min = origin_rect.y
            y_max = origin_rect.top_y() - 1
            new_rect = generate_rect(rect_id, origin_rect.right_x(), y_min, y_max, w_min, w_max, h_min, h_max)
            
            overlap_counter += 1
            if overlap_counter == 100000:
                excessive_overlap_flag = True
                break

        if excessive_overlap_flag:
            break
        rectangles.append(new_rect)

    return rectangles

