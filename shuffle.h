#ifndef SHUFFLE
#define SHUFFLE

#include <sys/time.h>

int *shuffledArray(int size);
void printArray(int *array, int size);
void copyArray(void *src, void *dest, int size_a, int size_e);
double timeDifference(struct timeval start, struct timeval end);
void check_array(int *array, int size);
int compare(void *a, void *b);

#endif //SHUFFLE
