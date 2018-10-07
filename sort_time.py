import subprocess
import sys

def sort_time(alg_name, count, size, extra):
    time_sum = 0;
    time = [0] * count;

    if extra:
        extra = " -e " + extra;

    for i in range(0, count):
        input_str  = "./" + alg_name + " -f 2 -s " + size + extra;
        p = subprocess.Popen(input_str, shell = True, stdout = subprocess.PIPE);
        time[i] = float(p.stdout.read().decode("utf-8").split(" ")[2]);
        time_sum += time[i];

    avg = time_sum / count;
    temp = 0;
    for i in range(0, count):
        temp += ((time[i] - avg) ** 2)

    std = temp / (count - 1);

    return [avg, std];


if __name__ == "__main__":
    alg = sys.argv[1];
    count = int(sys.argv[2]);
    size = sys.argv[3];

    if len(sys.argv) == 5:
        extra = sys.argv[4];
    else:
        extra = "";

    average, std = sort_time(alg, count, size, extra);

    print(alg + ": ", average, ", ", std);
