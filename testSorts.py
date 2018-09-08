import subprocess
import sys

alg1 = input("Algorithm 1:")
alg2 = input("Algorithm 2:")

count = int(input("Number of tests:"))
size = input("Size of list to sort:")

time1 = 0;
time2 = 0;

for x in range(0, count):
    p1 = subprocess.Popen(["./"+alg1, size, "2"], stdout = subprocess.PIPE)
    split1 = ((p1.stdout.read()).decode("utf-8")).split(" ")
    time1 += float(split1[2])

    p2 = subprocess.Popen(["./"+alg2, size, "2"], stdout = subprocess.PIPE)
    split2 = ((p2.stdout.read()).decode("utf-8")).splite(" ")
    time2 += float(split2[2])
    if float(splitString2[2]) < 0:
        print(float(splitString2[2]))

average1 = time1/count
average2 = time2/count

print("Average1: ", average1)
print("Average2: ", average2)
