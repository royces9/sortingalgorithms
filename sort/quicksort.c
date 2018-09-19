#include <stdlib.h>

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


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int leftCount = 0;
	int rightCount = size_a - 1;

	void *pivot = compare(array, array + (size_a / 2) * size_e) ? array : array  + (size_a / 2) * size_e;
	void *pivot2 = compare(array, array + (size_a - 1) * size_e) ? array : array + (size_a - 1) * size_e;
	pivot = compare(pivot, pivot2) ? pivot2 : pivot;

	int pivotPosition = 0;
	void *tempArray = malloc(size_e * size_a);

	for(int i = 0; i < size_a; ++i) {
		if(compare(pivot, (array + size_e * i))) {
			copy((array + size_e * i), (tempArray + size_e * leftCount++), size_e);
		} else if(compare((array + size_e * i), pivot)) {
			copy((array + size_e * i), (tempArray + size_e * rightCount--), size_e);
		} else {
			pivotPosition = i;
		}
	}
	copy((array + size_e * pivotPosition), (tempArray + size_e * rightCount), size_e);
	for(int j = 0; j < size_a; ++j)
		copy((tempArray + size_e * j), (array + size_e * j), size_e);

	free(tempArray);

	if(rightCount != 1)
		sort(array, rightCount, size_e, compare);

	if((size_a - rightCount) != 1)
		sort(array + size_e * leftCount, size_a - rightCount, size_e, compare);
}
