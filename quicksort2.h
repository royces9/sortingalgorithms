#ifndef QUICKSORT
#define QUICKSORT

#include <stdlib.h>
#include <math.h>

void sort(int *array, int size){
  if(size == 1){
    return;
  }

  int leftCount = 0, rightCount = size - 1;
  int pivot = fmax(array[0], array[(int) floor(size/2)]);
  int pivot2 = fmax(array[0], array[size-1]);
  pivot = fmin(pivot, pivot2);

  for(int i = 0; i < size; ++i){
    for(;leftCount < size; ++leftCount){
      if(array[leftCount] >= pivot){
	break;
      }
    }

    for(;rightCount >= 0; --rightCount){
      if(array[rightCount] <= pivot){
	break;
      }
    }
    int temp = array[leftCount];
    array[leftCount] = array[rightCount];
    array[rightCount] = temp;
  }
  sort(array, rightCount);
  sort(array + leftCount, size - rightCount);
}

#endif //QUICKSORT
