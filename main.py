import argparse
import time 
import copy
import csv

from rectangle_mod import generate_rectangles

def brute_algorithm(rectangles):
    rectangles.sort()    
    for i in range(len(rectangles)):
        for j in range(i + 1, len(rectangles)):
            if rectangles[i].right_x() == rectangles[j].x:
                rectangles[i].add_adj(rectangles[j])

def main():
    parser = argparse.ArgumentParser(description = 'AAA Assignment testing code')
    parser.add_argument('data_name', metavar = 'name', help = 'The name of the test' )
    parser.add_argument('data_size', metavar = 'n', type = int, help = 'The maximum number of rectangles to be generated for the test')
    parser.add_argument('sampling_rate', metavar = 'sampling rate', type = int, help = 'The number of times to rerun each iteration of 1 -> n, and calculate an average as the recorded time')
    args = parser.parse_args()

    print('Name of test:', args.data_name)
    print('Maximum number of rectangles:', args.data_size)
    print('Sampling rate per n:', args.sampling_rate)

    bf_csv = open(f"{args.data_name}_bf_results.csv", "w", newline='')
    # o_csv = open(f"{args.data_name}_o_results.csv", "w", newline='')

    bf_writer = csv.writer(bf_csv)
    # o_writer = csv.writer(o_csv)

    for n in range(args.data_size):
        board_size = [max(20, n * 2), max(20, n * 2)]
        rectangles = generate_rectangles(board_size, n)
        bf_rects = copy.deepcopy(rectangles)
        # o_rects = copy.deepcopy(rectangles)

        bf_sum = 0
        # o_sum = 0

        for _j in range(args.sampling_rate):
            # Brute Force Timing
            bf_start = time.time()
            brute_algorithm(bf_rects)
            bf_end = time.time()
            bf_sum += (bf_end - bf_start) * 1e3 # seconds to milliseconds

            # Optimised Timing
            # o_start = time.time_ns()
            # # Optimsed Algorithm goes here
            # o_end = time.time_ns()
            # o_sum += (o_end - o_start) * 1e6 # nanoseconds to microseconds

        bf_ave = bf_sum / args.sampling_rate
        # o_ave = o_sum / args.sampling_rate

        print(f"\raverage time for {n + 1}: {bf_ave} ms", end='')
        bf_writer.writerow([n + 1, bf_ave])
        # o_writer.writerow([n + 1, o_ave])

    print()

if __name__ == "__main__":
    main()
