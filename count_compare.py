#!/usr/bin/python

import subprocess
import sys
import numpy

def avg_comparison(alg, size, count):
    comp = 0;
    for i in range(0, count):
        p = subprocess.Popen("./" + alg + " -f 32 -s " + size, shell = True, stdout = subprocess.PIPE);
        comp += float(p.stdout.read().decode("utf-8"));

    return comp / count;

if __name__ == "__main__":
    if(len(sys.argv) == 1):
        sys.exit("./count_compare.py alg count output_file left_range right_range step_size");
    
    alg = sys.argv[1];
    count = int(sys.argv[2]);
    outfile = sys.argv[3];

    left = int(sys.argv[4]);
    right = int(sys.argv[5]);
    stepsize = int(sys.argv[6]);
    step = int((right - left) / stepsize) + 1;

    with open(outfile, "w+") as fp:
        for size in numpy.linspace(left, right, step):
            avg = avg_comparison(alg, str(int(size)), count);
            fp.write(str(int(size)) + " " + str(avg) + "\n");        
