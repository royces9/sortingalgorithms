import subprocess
import sys

alg1 = input("Algorithm 1:")
alg2 = input("Algorithm 2:")

count = input("Number of tests:")
intCount = int(count)
size = input("Size of list to sort:")

time1 = 0;
time2 = 0;

for x in range(0, intCount):
    p1 = subprocess.Popen(["./"+alg1, size], stdout = subprocess.PIPE)
    out1 = p1.stdout.read()
    out1 = out1.decode("utf-8")
    splitString1 = out1.split(" ")
    time1 += float(splitString1[2])

    p2 = subprocess.Popen(["./"+alg2, size], stdout = subprocess.PIPE)
    out2 = p2.stdout.read()
    out2 = out2.decode("utf-8")
    splitString2 = out2.split(" ")
    time2 += float(splitString2[2])
    if float(splitString2[2]) < 0:
        print(float(splitString2[2]))

average1 = time1/intCount
average2 = time2/intCount

print("Average1: ", average1)
print("Average2: ", average2)

