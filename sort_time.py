import subprocess
import sys

def sort_time(alg_name, count, size):
    time = 0;

    for i in range(0, count):
        p = subprocess.Popen(["./" + alg_name + " -f 2 -s " + size], shell = True, stdout = subprocess.PIPE);
        split = ((p.stdout.read()).decode("utf-8")).split(" ");
        time += float(split[2]);

    return time / count;


if __name__ == "__main__":
    alg = sys.argv[1];
    count = int(sys.argv[2]);
    size = sys.argv[3];
    average = sort_time(alg, count, size);

    print(alg + ": ", average);
