#ifndef INSERTIONSORT
#define INSERTIONSORT

void sort(int *array, int size){
  for(int i = 0; i < size; i ++){
    for(int j = i; j > 0; j--){
      if(array[j] < array[j-1]){
	int temp = array[j] ;
	array[j] = array[j-1];
	array[j-1] = temp;
      }
      else{
	break;
      }
    }

  }
}

#endif //INSERTIONSORT
