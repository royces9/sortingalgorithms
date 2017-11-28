#include <stdio.h>
#include <stdlib.h>

#include "shuffle.h"
#include "insertionsort.h"

int main(int argc, char **argv){
  int size = 10;

  if(argc > 1){
    size = atoi(argv[1]);
  }

  int *array = shuffledArray(size);

  printArray(array, size);
  sort(array, size);
  printArray(array, size);
  
  free(array);

  return 0;
}
