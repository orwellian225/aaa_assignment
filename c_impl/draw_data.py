import matplotlib.patches as patches
import matplotlib.pyplot as plt
import csv

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

    def top_y(self):
        return self.y + self.h
    def right_x(self):
        return self.x + self.w

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

def load_rects_from_csv(csv_path):
    rect_csv = open(csv_path, "r")
    rect_reader = csv.reader(rect_csv)

    rects = []

    for row in rect_reader:
        print(rects)
