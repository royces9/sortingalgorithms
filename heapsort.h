#ifndef HEAPSORT
#define HEAPSORT

#include <stdlib.h>
#include <math.h>

void checkHeap(int *array, int size){
  //i, 2i+1, 2i+2
  int ind, temp, flag = 1;
  while(flag){
    flag = 0;
    for(int i = 0; i < size; ++i){
      ind = 2*i+((array[2*i+1] > array[2*i+2])+1);
      if(array[i] < array[ind]){
	flag = 1;
	temp = array[i];
	array[i] = array[ind];
	array[ind] = temp;
      }
    }
  }
}

void sort(int *array, int size){
  if(size == 1){
    return;
  }
  checkHeap(array, size);

}


#endif //HEAPSORT
