#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "shuffle.h"

int *shuffledArray(int size){
  struct timeval t2;
  gettimeofday(&t2, NULL);
  srand((unsigned) t2.tv_usec);

  int *array = malloc(sizeof(*array) * size);

  for(int i = 0; i < size; i++){
    array[i] = i;
  }

  int temp;
  size_t j;
  for(int i = 0; i < (size - 1); i++){
    j = i + rand() / (RAND_MAX / (size - i) + 1);
    temp = array[j];
    array[j] = array[i];
    array[i] = temp;
  }

  return array;
}

void printArray(int *array, int size){
  for(int i = 0; i < size; i++){
    printf("%d ", array[i]);
  }
  printf("\n");
}

void copyArray(int *dest, int *src, int size){
  for(int i = 0; i < size; i++){
    dest[i] = src[i];
  }
}

double timeDifference(struct timeval start, struct timeval end){
  double elapse = ((double) end.tv_usec - (double) start.tv_usec)/100000;
  return  elapse += (end.tv_sec - start.tv_sec);
}
