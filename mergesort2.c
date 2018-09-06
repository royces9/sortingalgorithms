#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mergesort2.h"

int *global;
int globalSize;

int main(int argc, char **argv){
  int size = 10;

  struct timeval start;
  struct timeval end;

  if(argc > 1){
    size = atoi(argv[1]);
  }

  int *array = shuffledArray(size);
  global = array;
  globalSize = size;
  //printArray(array, size);

  gettimeofday(&start, NULL);
  sort(array, size);
  gettimeofday(&end, NULL);

  //printArray(array, size);
  printf("Time elapse: %lf s\n", timeDifference(start, end));

  free(array);

  return 0;
}
