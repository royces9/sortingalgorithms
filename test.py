import sys
import subprocess
import numpy

length = len(sys.argv);

algorithms = sys.argv[1:(length - 4)];
no_algs = len(algorithms);

count = int(sys.argv[length - 4]);
left_range = int(sys.argv[length - 3]);
right_range = int(sys.argv[length - 2]);
step_size = int(sys.argv[length - 1]);
number_steps = int((right_range - left_range + 1) / step_size);


fp = open("data.dat", "w");

fp.write("size ");

for name in algorithms:
    fp.write(name + " ");

fp.write("\n");

for size in numpy.linspace(left_range, right_range, number_steps):

    size = int(size);
    time = [0] * (no_algs + 1);

    for i in range(0, count):
        for j  in range(0, no_algs):
            p = subprocess.Popen(["./" + algorithms[j] + " -f 2 -s " + str(size)], shell = True, stdout = subprocess.PIPE);
            #split = p.stdout.read().decode("utf-8").split(" ");                    
            #time[j] += float(split[2]);

            time[j] += float( (p.stdout.read().decode("utf-8").split(" "))[2]);

    fp.write(str(size) + " ");
    for k in range(0, no_algs):
        fp.write(str(time[k] / count) + " ");

    fp.write("\n");

fp.close();
