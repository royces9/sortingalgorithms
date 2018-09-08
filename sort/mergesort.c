#include <stdlib.h>
#include <stdio.h>

#include "shuffle.h"

void copy(void *src, void *dest, int size_e) {
	char *c_src = src;
	char *c_dest = dest;
	for(int i = 0; i < size_e; ++i)
		*(c_dest++) = *(c_src++);
}

//mergesort
void merge(void *array, int size, int size2, int size_e, int (*compare)(void *, void*)){
	int iter = size + size2;
	char *combinedArray = malloc(size_e * iter);
	char *a = array;
	int headOne = 0;
	int headTwo = size;

	for(int i = 0; i < iter; ++i) {
		if(headTwo >= iter) {
			copy((a + size_e * (headOne++)), (combinedArray + i * size_e), size_e);
		} else if(headOne >= size) {
			copy((a + size_e * headTwo++), (combinedArray + i * size_e), size_e);
		} else if(compare((a + size_e * headOne), (array + size_e * headTwo))) {
			copy((a + size_e * headTwo++), (combinedArray + i * size_e), size_e);
		} else {
			copy((a + size_e * headOne++), (combinedArray + i * size_e), size_e);
		}
	}

	for(int j = 0; j < iter; ++j)
		copy((combinedArray + size_e * j), (array + size_e * j), size_e);

	free(combinedArray);
}

void sort(int *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int newSize = size_a / 2;
	int newSize2 = size_a - newSize;

	if(size_a > 1) {
		sort(array, newSize, size_e, compare);
		sort(array+newSize, newSize2, size_e, compare);
		merge(array, newSize, newSize2, size_e, compare);
	}
}
