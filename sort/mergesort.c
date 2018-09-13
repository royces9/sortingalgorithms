#include <stdlib.h>
#include <stdio.h>

#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;

int compare(void *a, void *b) {
	return *(int *) a > *(int *) b;
}


void copy(void *src, void *dest, int size_e) {
        int word_loops = size_e / 4;
	int byte_loops =  size_e % 4;

	for(int i = 0; i < word_loops; ++i)
		*(int *)(dest++) = *(int *)(src++);

	for(int i = 0; i < byte_loops; ++i)
		*(char *)(dest++) = *(char *)(src++);

	if(flag & 8)
		printArray(globalArray, globalSize);
}

//mergesort
void merge(void *array, int size, int size2, int size_e, int (*compare)(void *, void*)){
	int iter = size + size2;
	void *combinedArray = malloc(size_e * iter);
	int headOne = 0;
	int headTwo = size;

	for(int i = 0; i < iter; ++i) {
		if(headTwo >= iter) {
			copy((array + size_e * (headOne++)), (combinedArray + i * size_e), size_e);
		} else if(headOne >= size) {
			copy((array + size_e * headTwo++), (combinedArray + i * size_e), size_e);
		} else if(compare((array + size_e * headOne), (array + size_e * headTwo))) {
			copy((array + size_e * headTwo++), (combinedArray + i * size_e), size_e);
		} else {
			copy((array + size_e * headOne++), (combinedArray + i * size_e), size_e);
		}
	}

	for(int j = 0; j < iter; ++j)
		copy((combinedArray + size_e * j), (array + size_e * j), size_e);

	free(combinedArray);
}

void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int newSize = size_a / 2;
	int newSize2 = size_a - newSize;

	if(size_a > 1) {
		sort(array, newSize, size_e, compare);
		sort(array + newSize * size_e, newSize2, size_e, compare);
		merge(array, newSize, newSize2, size_e, compare);
	}
}
