#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quicksort(int array[], int size){
  for(int i = 0; i < size; i++){
    if(array[i] == floor(size/2)){
      int pivotPoint = i;
      int pivot = array[i];
      break;
    }
  }

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

int main(int argc, char **argv){
  int size = 10;

  if(argc > 1){
    size = atoi(argv[1]);
  }


  int array[size];

  time_t t;

  srand((unsigned) t);

  for(int i = 0; i < size; i++){
    array[i] = i;
  }

  int temp;
  for(int i = 0; i < (size - 1); i++){
    size_t j = i + rand() / (RAND_MAX / (size - i) + 1);

    temp = array[j];
    array[j] = array[i];
    array[i] = temp;
  }

  for(int i = 0; i < size; i++){
    printf("%d ", array[i]);
  }
  printf("\n");

  quicksort(array, size);

  for(int i = 0; i < size; i++){
    printf("%d ", array[i]);
  }
  printf("\n");
  
  return 0;
}
