import subprocess
import sys

import tkinter

class Rectangle:
    def __init__(self, left_x, rectangle_width, height):
        x1 = left_x * rectangle_width;
        x2 = (left_x + 1) * rectangle_width;

        y1 = 0;
        y2 = height + 1;

        self.rectangle = board.create_rectangle(x1, y1, x2, y2, fill='pink');


def update_board(string, rect):
    values = [int(i) for i in (string[0:-1])];

    for i in range(0, len(values)):
        curr = board.coords(rect[i].rectangle);
        y = height - (values[i]  + 1) * partial_height;
        dy = y - curr[1];
        board.move(rect[i].rectangle, 0, dy);


def start(f, file_name, algorithm, size):
    filestr = f.readline();
    if not filestr:
        f.close();
        write_to_file(file_name, algorithm, size);
        f2 = open(file_name, "r");
        root.after(100, start, f2, file_name, algorithm, size);
        return;

    split = filestr.split(" ");
    update_board(split, rect);
    root.after(delay, start, f, file_name, algorithm, size);

def write_to_file(file_name, algorithm, size):
    f = open(file_name, "w");
    p = subprocess.Popen(["./"+algorithm, size, "9"], stdout = f);
    f.close();


def new_window():
    root = tkinter.Tk();
    root.attributes('-type', 'dialog');
    root.title("Sorting");
    return root;


def new_canvas(width, height, root):
    board = tkinter.Canvas(root, width = width, height = height);
    board.pack();
    return board;


delay = int(sys.argv[1]);
algorithm = sys.argv[2];
s_size = sys.argv[3];
size = int(s_size);

file_name = "Sorting_algo_file"

f = open (file_name, "w");
write_to_file(file_name, algorithm, s_size);

root = new_window();

width = 1280;
height = 720;
board = new_canvas(width, height, root);

rectangle_width = width / size;
partial_height = height / size;

f = open(file_name, "r");

rect = [];
for i in range(0, int(s_size)):
    rect.append(Rectangle(i, rectangle_width, height));

root.after(0, start, f, file_name, algorithm, s_size);
root.mainloop();
