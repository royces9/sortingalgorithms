#include <math.h>
#include <stdlib.h>

#include "shuffle.h"

int compare(void *a, void *b) {
	return *(int *) a & *(int *) b;
}

//MSD radix
void MSDradix(int *array, int size, int msd){
	if(size == 1)
		return;

	if(msd < 1)
		return;

	int i = 0;
	int *dupArray = malloc(sizeof(*dupArray) * size);

	int copyIndex = size - 1;
	int tempIndex = 0;

	for(i = size-1; i >= 0; i--) {
		if((array[i] & msd)) {
			dupArray[copyIndex--] = array[i];
		} else {
			dupArray[tempIndex++] = array[i];
		}
	}

	copyArray(array, dupArray, size, sizeof(int));
	MSDradix(array + tempIndex, (size - 1) - copyIndex, msd / 2);
	MSDradix(array, tempIndex, msd / 2);

	free(dupArray);
}

void sort(int *array, int size_a) {
	int max = 0;
	for(int k = 0; k < size_a; k++) {
		if(array[k] == (size_a - 1)) {
			max = array[k];
			break;
		}
	}
	max = pow(2,floor(log(max)/log(2)));
  
	MSDradix(array, size_a, max);
}
