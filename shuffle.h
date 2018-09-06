#ifndef SHUFFLE
#define SHUFFLE

#include <sys/time.h>

int *shuffledArray(int size);
void printArray(int *array, int size);
void copyArray(int *array, int *array2, int size);
double timeDifference(struct timeval start, struct timeval end);

#endif //SHUFFLE
