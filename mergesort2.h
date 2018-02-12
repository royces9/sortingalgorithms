#ifndef MERGESORT
#define MERGESORT

#include <math.h>
#include <string.h>

#include "file.h"

extern int *global;
extern int globalSize;

//mergesort
void merge(int *array, int size, int size2){
  int iter = size + size2, combinedArray[iter], head[2];
  head[0] = 0;
  head[1] = size;

  if(size2 == 0){
    return;
  }

  for(int i = 0; i < iter; ++i){
    if(head[1] >= iter){
      combinedArray[i] = array[head[0]++];
    }
    else if(head[0] >= size){
      combinedArray[i] = array[head[1]++];
    }
    else{
      combinedArray[i] = array[head[array[head[0]] > array[head[1]]]++];
    }
  }
  copyArray(array, combinedArray, iter);
  //sendToFile(global, globalSize, "mergeSortData");
  //printArray(global, globalSize);
}

void sort(int *array, int size){
  int newSize = floor(size/2), newSize2 = size - newSize;
  if(size > 1){
    sort(array, newSize);
    sort(array+newSize, newSize2);
  }
  else{
    newSize = 1;
    newSize2 = 0;
  }
  merge(array, newSize, newSize2);
}

#endif //MERGESORT
