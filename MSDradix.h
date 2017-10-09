#ifndef MSDRADIX
#define MSDRADIX

#include <math.h>

//MSD radix
void MSDradix(int *array, int size, int msd){
  if(size == 1){
    return;
  }

  if(msd < 1){
    return;
  }

  int i = 0, dupArray[size], copyIndex = size - 1, tempIndex = 0;

  for(i = size-1; i >= 0; i--){
    if((array[i] & msd)){
      dupArray[copyIndex--] = array[i];
    }
    else{
      dupArray[tempIndex++] = array[i];
    }
  }

  copyArray(array, dupArray, size);
  MSDradix(array+tempIndex, (size - 1) - copyIndex, msd / 2);
  MSDradix(array, tempIndex, msd / 2);
}

void sort(int *array, int size){
  int max = 0;
  for(int k = 0; k < size; k++){
    if(array[k] == (size - 1)){
      max = array[k];
      break;
    }
  }
  max = pow(2,floor(log(max)/log(2)));
  
  MSDradix(array, size, max);
}

#endif //MSDRADIX
