#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "shuffle.h"
#include "MSDradix.h"

int main(int argc, char **argv){
  int size = 10;

  struct timeval start;
  struct timeval end;

  if(argc > 1){
    size = atoi(argv[1]);
  }

  int *array = shuffledArray(size);

  //  printArray(array, size);

  gettimeofday(&start, NULL);
  sort(array, size);
  gettimeofday(&end, NULL);

  printf("Time elapse: %lf s\n", timeDifference(start, end));

  //  printArray(array, size);
  
  free(array);

  return 0;
}
