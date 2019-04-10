#!/usr/bin/python

import matplotlib.pyplot
import numpy
import sys


def plot_file(file_name):
    data = numpy.loadtxt(file_name);
    matplotlib.pyplot.plot(data[:, 0], data[:, 1], label=file_name);


if __name__ == "__main__":
    if(len(sys.argv) < 4):
        sys.exit("./plot x_label y_label file1 file2 ... fileN");

    xlab = sys.argv[1];
    ylab = sys.argv[2];

    fig = matplotlib.pyplot.figure();

    for f in sys.argv[3:]:
        plot_file(f);

    matplotlib.pyplot.xlabel(xlab);
    matplotlib.pyplot.ylabel(ylab);
    matplotlib.pyplot.legend();
    matplotlib.pyplot.show();
