#ifndef QUICKSORT
#define QUICKSORT

#include <stdlib.h>
#include <math.h>

#include "shuffle.h"

void sort(int *array, int size) {
	if(size == 1)
		return;

	int leftCount = 0;
	int rightCount = size - 1;
	
	int pivot = fmax(array[0], array[(int) size/2]);
	int pivot2 = fmax(array[0], array[size-1]);
	pivot = fmin(pivot, pivot2);

	int pivotPosition = 0;
	int *tempArray = malloc(sizeof(*tempArray) * size);

	for(int i = 0; i < size; ++i) {
		if(array[i] < pivot) {
			tempArray[leftCount++] = array[i];
		} else if(array[i] > pivot) {
			tempArray[rightCount--] = array[i];
		} else {
			pivotPosition = i;
		}
	}

	tempArray[rightCount] = array[pivotPosition];
	copyArray(array, tempArray, size);
	sort(array, rightCount);
	sort(array + leftCount, size - rightCount);
}

#endif //QUICKSORT
