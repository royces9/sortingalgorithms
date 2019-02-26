#!/usr/bin/python

import os
import numpy
import matplotlib.pyplot
import sys


def plot_file(file_name):
    data = numpy.loadtxt(file_name);
    matplotlib.pyplot.plot(data[:, 0], data[:, 1], label = file);


if __name__ == "__main__":
    if(len(sys.argv) == 1):
        sys.exit("./plot.py x_label y_label file1 file2 ... fileN");

    xlab = sys.argv[1];
    ylab = sys.argv[2];

    fig = matplotlib.pyplot.figure();

    for f in sys.argv[3:-1]:
        plot_file(f);

    matplotlib.pyplot.xlabel(xlab);
    matplotlib.pyplot.ylabel(ylab);
    matplotlib.pyplot.legend(sys.argv[3:-1]);
    matplotlib.show();
