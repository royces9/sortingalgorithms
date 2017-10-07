#ifndef LSDRADIX
#define LSDRADIX

#include <math.h>

//LSD radix
void sort(int *array, int size){
  int i = 0, j = 1, dupArray[size], copyIndex, tempIndex, max;

  for(int k = 0; k < size; k++){
    if(array[k] == (size - 1)){
      max = array[k];
      break;
    }
  }

  max = pow(2,floor(log(max)/log(2)));

  for(int k = 0; k <= max; k++){
    copyIndex = 0;
    tempIndex = size - 1;
    for(i = 0; i < size; i++){
      if(!((array[i] & j))){
	dupArray[copyIndex++] = array[i];
      }
      else{
	dupArray[tempIndex--] = array[i];
      }
    }
    copyArray(array, dupArray, copyIndex);
    for(int l = copyIndex; l < size; l++){
      array[l] = dupArray[(size + copyIndex - 1) - l];
    }

    j <<= 1;
  }
}

#endif //LSDRADIX
