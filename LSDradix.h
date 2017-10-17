#ifndef LSDRADIX
#define LSDRADIX

#include <math.h>

//LSD radix

void sort(int *array, int size){
  int dupArray[size], copyIndex, tempIndex, max;

  for(int j = 0; j < size; j++){
    if(array[j] == (size - 1)){
      max = array[j];
      break;
    }
  }

  max = pow(2,floor(log(max)/log(2)));

  for(int j = 1; j <= max; j <<= 1){
    copyIndex = 0;
    tempIndex = size - 1;
    for(int i = 0; i < size; i++){
      if(!(array[i] & j)){
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
  }


}

#endif //LSDRADIX
