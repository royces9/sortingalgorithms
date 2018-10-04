import os
import numpy
import matplotlib.pyplot
import sys

directory = sys.argv[1];

fig = matplotlib.pyplot.figure();

for file in os.listdir(directory):
    algorithm = os.path.splitext(file)[0];
    data = numpy.loadtxt(directory + file, skiprows = 1);
    matplotlib.pyplot.plot(data[:, 0], data[:, 1], label = algorithm);


matplotlib.pyplot.xlim(data[0, 0], data[-1, 0]);
matplotlib.pyplot.ylabel("Sort time, s");
matplotlib.pyplot.xlabel("List size");
matplotlib.pyplot.legend();
matplotlib.pyplot.show();
