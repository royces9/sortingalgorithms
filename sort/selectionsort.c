#ifndef SELECTION
#define SELECTION

void sort(int *array, int size) {
	int min = 0;
	int i = 0;
	for(int j = 0; j < size; j++) {
		min = j;
		for(i = 0; i < size-j; i++) {
			if(array[i+j] < array[min])
				min = i+j;
		}
		int temp = array[min];
		array[min] = array[j];
		array[j] = temp;
	}
}

#endif //SELECTION
