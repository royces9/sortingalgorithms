#include "shuffle.h"

//bubblesort
void sort(int array[], int size){
  int flag = 1;
  int temp;
  
  while(flag == 1){
    flag = 0;
    for(int i = 0; i < (size-1); i++){
      if(array[i+1] < array[i]){
	temp = array[i+1];
	array[i+1] = array[i];
	array[i] = temp;
	flag = 1;
      }
    }
  }
}
