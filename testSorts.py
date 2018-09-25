import subprocess
import sys


alg1 = sys.argv[1];
alg2 = sys.argv[2];
count = int(sys.argv[3]);
size = sys.argv[4];

time1 = 0;
time2 = 0;

for x in range(0, count):
    p1 = subprocess.Popen(["./"+alg1, "-f 2 -s", size], shell = True, stdout = subprocess.PIPE)
    split1 = ((p1.stdout.read()).decode("utf-8")).split(" ")
    time1 += float(split1[2])

    p2 = subprocess.Popen(["./"+alg2, "-f 2 -s", size], shell = True, stdout = subprocess.PIPE)
    split2 = ((p2.stdout.read()).decode("utf-8")).split(" ")
    time2 += float(split2[2])


average1 = time1/count
average2 = time2/count

len1 = len(alg1);
len2 = len(alg2);

diff = abs(len1 - len2);
addition = " " * diff;

if len1 > len2:
    alg2 += addition;
else:
    alg1 += addition;

    
print(alg1 + ": ", average1)
print(alg2 + ": ", average2)
