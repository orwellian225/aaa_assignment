import argparse

from rectangle_mod import draw_rectangles, generate_rectangles

def main():
    parser = argparse.ArgumentParser(description = 'Generate Test data for AAA Assignment')
    parser.add_argument('data_name', metavar = 'name', help = 'The name of the generated rectangle set' )
    parser.add_argument('data_size', metavar = 'n', type = int, help = 'The number of rectangles to be generated')
    args = parser.parse_args()

    print('Name of data set', args.data_name)
    print('Number of rectangles', args.data_size)

    board_size = [args.data_size * 2, args.data_size * 2]
    rectangles = generate_rectangles(board_size, args.data_size)
    draw_rectangles(args.data_name, rectangles, board_size)

if __name__ == "__main__":
    main()
