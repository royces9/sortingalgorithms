import sys
import subprocess
import numpy

import sort_time

def sort_data(alg, prefix, count, left_range, right_range, step_size):
    number_steps = int((right_range - left_range) / step_size) + 1;

    fp = open(prefix + alg + ".dat", "w");
    fp.write("size " + alg + "\n");

    for size in numpy.linspace(left_range, right_range, number_steps):
        size = str(int(size));
        average = sort_time.sort_time(alg, count, size);
        fp.write(size + " " + str(average) + "\n");

    fp.close();


if __name__ == "__main__":
    flag = 0;
    for i, arg in enumerate(sys.argv):
        if arg == "-n":
            flag = 1;
        elif arg == "-r":
            flag = 2;
        elif arg == "-e":
            flag = 3;
        else:

    alg = sys.argv[1];

    prefix = sys.argv[2];
    if prefix == "none":
        prefix = "";

    count = int(sys.argv[3]);
    left_range = int(sys.argv[4]);
    right_range = int(sys.argv[5]);
    step_size = int(sys.argv[6]);

    sort_data(alg, prefix, count, left_range, right_range, step_size);
