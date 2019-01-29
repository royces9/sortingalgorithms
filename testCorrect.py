#!/usr/bin/python

import subprocess
import sys

alg = sys.argv[1];
size = sys.argv[2];
count = int(sys.argv[3]);

tally = 0;

for x in range(0, count):
    p = subprocess.Popen(["./"+alg + " -f 4 -s" + size], shell = True, stdout = subprocess.PIPE);
    out = (p.stdout.read()).decode("utf-8");
    if out:
        tally += 1;
        
print("Total failed sorts: ", tally);    
