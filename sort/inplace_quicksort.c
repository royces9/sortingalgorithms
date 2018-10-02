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
}


void swap(void *a, void *b, int size_e) {
	int word_loops = size_e / 4;
	int byte_loops = size_e % 4;

	for(int i = 0; i < word_loops; ++i) {
		int i_temp = *(int *)a;
		*(int *)a++ = *(int *)b;
		*(int *)b++ = i_temp;
	}

	for(int i = 0; i < byte_loops; ++i) {
		char c_temp  = *(char *)a;
		*(char *)a++ = *(char *)b;
		*(char *)b++ = c_temp;
	}

	if(flag & 8)
		printArray(globalArray, globalSize);
}


//if compare function contains equals
void sort_e(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
        int leftHead = 0;
	int rightHead = size_a - 1;

	void *pivot = compare(array, array + (size_a / 2) * size_e) ? array : array + (size_a / 2) * size_e;
	void *pivot2 = compare(array, array + (size_a - 1) * size_e) ? array : array + (size_a - 1) * size_e;
	pivot = compare(pivot, pivot2) ? pivot2 : pivot;

	pivot2 = malloc(size_e);
	copy(pivot, pivot2, size_e);

	while(leftHead != rightHead) {
		for(;(leftHead < size_a) && !compare(array + leftHead * size_e, pivot2); ++leftHead);
		for(;(rightHead >= 0) && !compare(pivot2, array + rightHead * size_e); --rightHead);

		swap(array + leftHead * size_e,
		     array + rightHead * size_e,
		     size_e);
	}

	free(pivot2);

	if(rightHead != 1)
		sort_e(array, rightHead, size_e, compare);

	if((size_a - rightHead) != 1)
 		sort_e(array + leftHead * size_e, size_a - rightHead, size_e, compare);
}


//if compare is only >
void sort_ne(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
        int leftHead = 0;
	int rightHead = size_a - 1;

	void *pivot = compare(array, array + (size_a / 2) * size_e) ? array : array + (size_a / 2) * size_e;
	void *pivot2 = compare(array, array + (size_a - 1) * size_e) ? array : array + (size_a - 1) * size_e;
	pivot = compare(pivot, pivot2) ? pivot2 : pivot;

	pivot2 = malloc(size_e);
	copy(pivot, pivot2, size_e);

	while(leftHead != rightHead) {
		for(;leftHead < size_a && compare(pivot2, array + leftHead * size_e); ++leftHead);
		for(;rightHead >= 0 && compare(array + rightHead * size_e, pivot2); --rightHead);

		swap(array + size_e * leftHead,
		     array + size_e * rightHead,
		     size_e);
	}

	free(pivot2);

	if(rightHead != 1)
		sort_ne(array, rightHead, size_e, compare);

	if((size_a - rightHead) != 1)
 		sort_ne(array + leftHead * size_e, size_a - rightHead, size_e, compare);
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	if(size_a == 1)
		return;

	if(compare(array, array)) {
		sort_e(array, size_a, size_e, compare);
	} else {
		sort_ne(array, size_a, size_e, compare);
	}
	
}
