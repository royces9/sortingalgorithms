#include <stdlib.h>

#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;

int compare(void *a, void *b) {
	return *(int *) a >= *(int *) b;
}


void copy(void *src, void *dest, int size_e) {
        int word_loops = size_e / 4;
	int byte_loops =  size_e % 4;

	for(int i = 0; i < word_loops; ++i)
		*(int *)(dest++) = *(int *)(src++);

	for(int i = 0; i < byte_loops; ++i)
		*(char *)(dest++) = *(char *)(src++);
}

void swap(void *a, void *b, int size_e) {
	int word_loops = size_e / 4;
	int byte_loops = size_e % 4;

	int i_temp = 0;
	for(int i = 0; i < word_loops; ++i) {
		i_temp = *(int *)a;
		*(int *)a++ = *(int *)b;
		*(int *)b++ = i_temp;
	}

	char c_temp = 0;
	for(int i = 0; i < byte_loops; ++i) {
		c_temp  = *(char *)a;
		*(char *)a++ = *(char *)b;
		*(char *)b++ = c_temp;
	}

	if(flag & 8)
		printArray(globalArray, globalSize);
}

void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
        int leftCount = 0;
	int rightCount = size_a - 1;

	void *pivot = compare(array, (array + size_e * (size_a / 2))) ? array : (array + size_e * (size_a / 2));
	void *pivot2 = compare(array, (array + size_e * (size_a - 1))) ? array : (array + size_e * (size_a - 1));
	pivot = compare(pivot, pivot2) ? pivot2 : pivot;

	pivot2 = malloc(size_e);
	copy(pivot, pivot2, size_e);


	for(int i = 0; leftCount != rightCount; ++i) {
		for(;compare(pivot2, (array + size_e * leftCount)); ++leftCount);
		for(;compare((array + size_e * rightCount), pivot2); --rightCount);

		swap((array + size_e * (leftCount)),
		     (array + size_e * (rightCount)),
		     size_e);
	}
	free(pivot2);

	if(rightCount != 1)
		sort(array, rightCount, size_e, compare);
	if((size_a - rightCount) != 1)
 		sort(array + size_e * leftCount, size_a - rightCount, size_e, compare);
}
