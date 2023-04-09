import matplotlib.pyplot as plt
import matplotlib.patches as patches

def draw_rectangle(rectangle, axes):
    x = rectangle[1]
    y = rectangle[2]
    w = rectangle[3] - rectangle[1]
    h = rectangle[4] - rectangle[2]

    rect_patch = patches.Rectangle((x,y), w, h, linewidth=1, edgecolor='r', facecolor='none')
    axes.add_patch(rect_patch)

    

def draw_rectangles(name, rectangles, board_size):

    fig, ax = plt.subplots()
    plt.xlim([0, board_size[0]])
    plt.ylim([0, board_size[1]])
    for rectangle in rectangles:
        draw_rectangle(rectangle, ax)
    
    plt.savefig(f"{name}.pdf")
    plt.close()


