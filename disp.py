import subprocess
import sys

import tkinter

class Rectangle:
    def __init__(self, left_x, rectangle_width, height):
        x1 = left_x * rectangle_width;
        x2 = (left_x + 1) * rectangle_width;

        y1 = 0;
        y2 = height + 1;

        self.rectangle = board.create_rectangle(x1, y1, x2, y2, fill='#ffd1dc');


def update_board(string, rect):
    values = [int(i) for i in (string[0:-1])];

    for i in range(0, len(values)):
        curr = board.coords(rect[i].rectangle);
        y = height - (values[i]  + 1) * partial_height;
        dy = y - curr[1];
        board.move(rect[i].rectangle, 0, dy);


def start(f, file_name, algorithm, size, args):
    filestr = f.readline();
    if not filestr:
        f.close();
        write_to_file(file_name, algorithm, args);
        f2 = open(file_name, "r");
        root.after(100, start, f2, file_name, algorithm, size, args);
        return;

    split = filestr.split(" ");
    update_board(split, rect);
    root.after(delay, start, f, file_name, algorithm, size, args);

def write_to_file(file_name, algorithm, args):
    f = open(file_name, "w");
    inputStr = "./" + algorithm + " -f 9 " + args;
    p = subprocess.Popen(inputStr, shell = True, stdout = f);
    f.close();


def new_window():
    root = tkinter.Tk();
    root.attributes('-type', 'dialog');
    root.title("Sorting");
    return root;


def new_canvas(width, height, root):
    board = tkinter.Canvas(root, width = width, height = height);
    board["bg"] = "#ffffff";
    board["highlightbackground"] = "#ffffff";
    board.pack();
    return board;


delay = int(sys.argv[1]);
algorithm = sys.argv[2];
size = 100;
s_size = str(size);

args = '';
for i in range(3, len(sys.argv)):
    if(sys.argv[i] == '-s'):
        s_size = sys.argv[i + 1];
        size = int(s_size);
    if(sys.argv[i] == '-f'):
        i += 2;
        continue;

    args = args + " " + sys.argv[i];
        
if "-s" not in args:
    args += ("-s " + s_size);

file_name = "Sorting_algo_file"

f = open (file_name, "w");
write_to_file(file_name, algorithm, args);

root = new_window();

width = 1920;
height = 1080;
board = new_canvas(width, height, root);

rectangle_width = width / size;
partial_height = height / size;

f = open(file_name, "r");

rect = [];
for i in range(0, int(s_size)):
    rect.append(Rectangle(i, rectangle_width, height));

root.after(0, start, f, file_name, algorithm, s_size, args);
root.mainloop();
