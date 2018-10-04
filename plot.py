import os
import numpy
import matplotlib.pyplot
import sys


def plot_alg(directory, file_names):
    fig = matplotlib.pyplot.figure();

    for file in file_names:
        data = numpy.loadtxt(directory + file + ".dat", skiprows = 1);
        matplotlib.pyplot.plot(data[:, 0], data[:, 1], label = file);


    matplotlib.pyplot.xlim(data[0, 0], data[-1, 0]);
    matplotlib.pyplot.ylabel("Sort time, s");
    matplotlib.pyplot.xlabel("List size");
    matplotlib.pyplot.legend();
    matplotlib.pyplot.show();

if __name__ == "__main__":
    directory = sys.argv[1];

    #without file extension, hardcode .dat
    file_names = sys.argv[2:len(sys.argv)];
    plot_alg(directory, file_names);
