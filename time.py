import subprocess
import sys

alg = sys.argv[1];
count = int(sys.argv[2]);
size = sys.argv[3];

time = 0;

for x in range(0, count):
    p = subprocess.Popen(["./" + alg + " -f 2 -s " + size], shell = True, stdout = subprocess.PIPE);
    split = ((p.stdout.read()).decode("utf-8")).split(" ");
    time += float(split[2]);


average = time / count;
    
print(alg + ": ", average);
