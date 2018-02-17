#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "shuffle.h"

int main(int argc, char **argv){
  int size = 10;

  struct timeval start;
  struct timeval end;
  
  if(argc > 1){
    size = atoi(argv[1]);
  }

  int *array = shuffledArray(size);
  int flag = 0;
  
  if(argv[2] != NULL)
    flag = atoi(argv[2]);

  if(flag & 1)
    printArray(array, size);

  gettimeofday(&start, NULL);
  sort(array, size);
  gettimeofday(&end, NULL);

  if(flag & 1)
    printArray(array, size);

  if(flag & 2)
    printf("Time elapsed: %lf s\n", timeDifference(start, end));
  
  free(array);
  return 0;
}
