import argparse
import math as m
import numpy as np

def main():
    parser = argparse.ArgumentParser(description = 'Generate Test data for AAA Assignment')
    parser.add_argument('data_size', metavar = 'n', type = int, help = 'The number of rectangles to be generated')
    parser.add_argument('adjacency_count', metavar = 'a', type = int, help = 'The number of adjencies to be generated between the rectangles')
    args = parser.parse_args()

    print('Number of rectangles', args.data_size)
    print('Number of adjacencies', args.adjacency_count)

    rectangles = []

    for i in range(args.data_size):
        print(f"\rrectangle {i + 1}/{args.data_size}", end = '')
        rect_id = i
        bl_x = int(m.floor(np.random.uniform(0, 100)))
        tr_y = int(m.floor(np.random.uniform(0, 100)))
        tr_x = int(m.floor(np.random.uniform(bl_x, bl_x + 10)))
        bl_y = int(m.floor(np.random.uniform(tr_y, tr_y + 10)))
        rectangles.append(np.array([rect_id, bl_x, bl_y, tr_x, tr_y]))

    rectangles = np.array(rectangles)
    print()

    for i in range(args.adjacency_count):
        print(f"\radjacency {i + 1}/{args.adjacency_count}", end = '')
    print()


if __name__ == "__main__":
    main()
