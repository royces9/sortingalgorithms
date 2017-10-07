#ifndef MERGESORT
#define MERGESORT

#include <math.h>
#include <string.h>

//mergesort
void merge(int *array, int size, int size2){
  int iter = size + size2, combinedArray[iter], headOne = 0, headTwo = 0;

  if(size2 == 0){
    return;
  }

  for(int i = 0; i < iter; i++){
    if(headTwo >= size2){
      combinedArray[i] = *(array+headOne++);
      continue;
    }

    if(headOne >= size){
      combinedArray[i] = *(array+size+headTwo++);
      continue;
    }

    if(*(array+headOne) > *(array+size+headTwo)){
      combinedArray[i] = *(array+size+headTwo++);
    }
    else{
      combinedArray[i] = *(array+headOne++);
    }
  }

  copyArray(array, combinedArray, iter);
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
