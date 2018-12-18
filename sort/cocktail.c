#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;

int compare(void *a, void *b) {
	return *(int *) a > *(int *) b;
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


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int j = 0, left_bound = 0, right_bound = size_a;
	    j < size_a/2;
	    ++j) {

		int min = left_bound;
		for(int i = left_bound + 1; i < right_bound; ++i) {
			if(compare(array + min * size_e, array + i * size_e))
				min = i;
		}
		swap(array + left_bound * size_e, array + min * size_e, size_e);
		++left_bound;

		int max = right_bound - 1;
		for(int i = right_bound - 2; i >= left_bound; --i) {
			if(compare(array + i * size_e, array + max * size_e))
				max = i;
		}
		
		swap(array + (right_bound - 1) * size_e, array + max * size_e, size_e);
		--right_bound;
	}
}
