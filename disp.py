import subprocess
import sys

import tkinter

class Rectangle:
    def __init__(self, left_x, rectangle_width, height, board):
        self.width = rectangle_width;
        x1 = left_x * rectangle_width;
        x2 = (left_x + 1) * rectangle_width;

        y1 = 0;
        y2 = height + 1;

        self.rectangle = board.create_rectangle(x1, y1, x2, y2, fill='#ffd1dc');


class Alg_details:
    def __init__(self, algorithm, s_size, args, delay):
        self.algorithm = algorithm;
        self.s_size = s_size;
        self.args = args;
        self.delay = delay;


def update_board(board, string, rect):
    values = [int(i) for i in (string[0:-1])];
    partial_height = board.winfo_height() / len(values);

    for i in range(0, len(values)):
        curr = board.coords(rect[i].rectangle);
        y = board.winfo_height() - (values[i]  + 1) * partial_height;
        dy = y - curr[1];
        board.move(rect[i].rectangle, 0, dy);


def start(f, file_name, alg, root, board, rect):
    filestr = f.readline();
    if not filestr:
        f.close();
        write_to_file(file_name, alg);
        f2 = open(file_name, "r");
        root.after(alg.delay + 100, start, f2, file_name, alg, root, board, rect);
        return;

    split = filestr.split(" ");
    update_board(board, split, rect);
    root.after(alg.delay, start, f, file_name, alg, root, board, rect);

    
def write_to_file(file_name, alg):
    f = open(file_name, "w");
    inputStr = "./" + alg.algorithm + " -f 9 " + alg.args;
    p = subprocess.Popen(inputStr, shell = True, stdout = f);
    f.close();


def new_window():
    root = tkinter.Tk();
    root.attributes('-type', 'dialog');
    root.title("Sorting");
    return root;


def resize_canvas(Canvas):
    def __init__(self,parent,**kwargs):
        Canvas.__init__(self,parent,**kwargs)
        self.bind("<Configure>", self.on_resize)
        self.height = self.winfo_reqheight()
        sel.width = self.winfo_reqwidth()

    def on_resize(self,event):
        # determine the ratio of old width/height to new width/height
        wscale = float(event.width)/self.width
        hscale = float(event.height)/self.height
        self.width = event.width
        self.height = event.height
        # resize the canvas
        self.config(width=self.width, height=self.height)
        # rescale all the objects tagged with the "all" tag
        self.scale("all",0,0,wscale,hscale)

        
def new_canvas(width, height, root):
    """
    frame = tkinter.Frame(root);
    frame.pack(fill = tkinter.BOTH, expand=tkinter.YES);

    board = resize_canvas(frame);
    #board = resize_canvas(frame, background = "#ffffff", highlightthickness = 0);
    board.pack(fill = tkinter.BOTH, expand = tkinter.YES);

    """
    board = tkinter.Canvas(root, width = width, height = height);
    board["bg"] = "#ffffff";
    board["highlightbackground"] = "#ffffff";
    board.pack();
    return board;


def main():
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

    alg = Alg_details(algorithm, s_size, args, delay);

    f = open (file_name, "w");
    write_to_file(file_name, alg);

    root = new_window();

    width = 1920;
    height = 1080;
    board = new_canvas(width, height, root);

    rectangle_width = width / size;
    partial_height = height / size;

    f = open(file_name, "r");

    rect = [];
    for i in range(0, int(s_size)):
        rect.append(Rectangle(i, rectangle_width, height, board));

    root.after(0, start, f, file_name, alg, root, board, rect);
    root.mainloop();



if __name__ == "__main__":
    main();
