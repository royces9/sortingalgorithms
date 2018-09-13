import subprocess
import sys

alg = input("Testing:");

count = int(input("Number of test:"));
size = input("Size of list to sort:");

tally = 0;

for x in range(0, count):
    p = subprocess.Popen(["./"+alg, size, "4"], stdout = subprocess.PIPE);
    out = (p.stdout.read()).decode("utf-8");
    if out:
        tally += 1;
        
print("Total failed sorts: ", tally);    
