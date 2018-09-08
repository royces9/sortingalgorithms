#ifndef MERGESORT
#define MERGESORT

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "shuffle.h"

//mergesort
void merge(int *array, int size, int size2) {
	int iter = size + size2;
	int *combinedArray = malloc(sizeof(*combinedArray) * iter);

	int head[2] = {0, size};

	for(int i = 0; i < iter; ++i) {
		if(head[1] >= iter){
			combinedArray[i] = array[head[0]++];
		} else if(head[0] >= size) {
			combinedArray[i] = array[head[1]++];
		} else {
			combinedArray[i] = array[head[array[head[0]] > array[head[1]]]++];
		}
	}
	copyArray(array, combinedArray, iter);
	free(combinedArray);
}

void sort(int *array, int size) {
	int newSize = size / 2;
	int newSize2 = size - newSize;

	if(size > 1) {
		sort(array, newSize);
		sort(array + newSize, newSize2);
		merge(array, newSize, newSize2);
	}
}

#endif //MERGESORT