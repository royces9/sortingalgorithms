import subprocess
import sys

def compare_sorts(algorithms, no_algs, count, size):
    avg = [0] * (no_algs);

    for j, alg in enumerate(algorithms):
        time = 0;
        for i in range(0, count):
            p = subprocess.Popen(["./" + alg + " -f 2 -s " + size], shell = True, stdout = subprocess.PIPE);
            time += float(((p.stdout.read()).decode("utf-8")).split(" ")[2]);

        avg[j] = time / count;

    return avg;


if __name__ == "__main__":

    length = len(sys.argv);

    algorithms = sys.argv[1:(length - 2)];
    no_algs = len(algorithms);

    count = int(sys.argv[length - 2]);
    size = sys.argv[length - 1];

    avg = compare_sorts(algorithms, no_algs, count, size);

    alg_name_length = [0] * (no_algs + 1);

    for i, alg in enumerate(algorithms):
        alg_name_length[i] = len(alg);

    max_length = max(alg_name_length);

    for i, a in enumerate(avg):
        padding = max_length - alg_name_length[i];
        print(algorithms[i] + ":" + " " * padding, a);

