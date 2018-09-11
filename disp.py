import sys
import tkinter

class Rectangle:
    def __init__(self, index, value):
        self.index = index;
        self.value = value;
        x1 = index * rectangle_width;
        y1 = height - ((value + 1) * partial_height);
        x2 = (index + 1) * rectangle_width;
        y2 = height;
        self.rectangle = board.create_rectangle(x1, y1, x2, y2);


def update_board(string, rect):
    values = [int(i) for i in (string[0:-1])];
    
    for r in rect:
        curr = board.coords(r.rectangle);
        index = values.index(r.value);

        x = rectangle_width * index;
        dx = x - curr[0];
        board.move(r.rectangle, dx, 0);
#    input()

def start(file):
    filestr = f.readline();
    split = filestr.split(" ");
    update_board(split, rect);
    root.after(100, start, file);    

size = int(sys.argv[1]);

f = open("test", "r");
root = tkinter.Tk();
root.attributes('-type', 'dialog')

width = 1280;
height = 720;
board = tkinter.Canvas(root, width=width, height=height);
board.pack();

rectangle_width = width / size;
partial_height = height / size;

rect = [];
init = [int(i) for i in f.readline().split(" ")[0:-1]];
for (i, j) in zip(init, range(0,len(init))):
    rect.append(Rectangle(i, j));

root.after(0, start, f);
root.mainloop();
