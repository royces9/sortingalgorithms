#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "shuffle.h"

int main(int argc, char **argv){
  //argv[0] = func
  //1 = algorithm name
  //2 = print and timing flags
  //3 = number of elements

  int size = 10;

  struct timeval start;
  struct timeval end;
  
  if(argc > 3){
    size = atoi(argv[3]);
  }

  int *array = shuffledArray(size);
  int flag = 0;
  
  void (*sort)(int *, int);
  sort = pickFunction(argv[1]);

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
