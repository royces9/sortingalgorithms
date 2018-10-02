import subprocess
import sys

length = len(sys.argv);

algorithms = sys.argv[1:(length - 2)];
no_algs = len(algorithms);

count = int(sys.argv[length - 2]);
size = sys.argv[length - 1];


time = [0] * (no_algs + 1);
average = [0] * (no_algs + 1);


for i in range(0, count):
    for j in range(0, no_algs):
        p = subprocess.Popen(["./" + algorithms[j] + " -f 2 -s " + size], shell = True, stdout = subprocess.PIPE);
        time[j] += float(((p.stdout.read()).decode("utf-8")).split(" ")[2]);


alg_name_length = [0] * (no_algs + 1);
for i in range(0, no_algs):
    alg_name_length[i] = len(algorithms[i]);
    average[i] = time[i] / count;


max_length = max(alg_name_length);
for i in range(0, no_algs):
    padding = max_length - len(algorithms[i]);
    algorithms[i] += (":" + " "  * padding);
    print(algorithms[i], average[i]);
