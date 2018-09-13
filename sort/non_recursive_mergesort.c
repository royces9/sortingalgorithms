#include <stdlib.h>

#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;

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

void copy(void *src, void *dest, int size_e) {
        int word_loops = size_e / 4;
	int byte_loops =  size_e % 4;

	for(int i = 0; i < word_loops; ++i)
		*(int *)(dest++) = *(int *)(src++);

	for(int i = 0; i < byte_loops; ++i)
		*(char *)(dest++) = *(char *)(src++);
}


//mergesort
void merge(void *array, int size, int size2, int size_e, int (*compare)(void *, void *)) {
	int size_total = size + size2;
	int size_count = size_total;

	for(int left = 0, right = size; left < (size_total - 1); ++left, --size_count) {
		if(left == right)
			++right;

		if(size_count == size)
			--size;

		//beginning of each sub array
		if(compare(array + size_e * left, array + size_e * right)) {
			swap(array + size_e * left, array + size_e * right, size_e);

			//beginning of the right sub array
			for(int j = right;
			    (j < size_total - 1) && compare(array + size_e * j, array + size_e * (j + 1));
			    ++j) {
				swap(array + size_e * j, array + size_e * (j + 1), size_e);
			}
		}

		//end of each sub array
		if(compare(array + size_e * (size - 1), array + size_e * (size_count - 1))) {
			swap(array + size_e * (size - 1), array + size_e * (size_count - 1), size_e);

			//end of the first sub array
			for(int j = size - 1;
			    (j > left) && compare(array + size_e * (j-1), array + size_e * j);
			    --j) {
				swap(array + size_e * (j - 1), array + size_e * j, size_e);
			}
		}
	}
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int counter = 1;
	for(int log = size_a - 1; log != 1; log /= 2, ++counter);

	//count number of tiers of merges
	int layer = counter;

	//number of merges in layer
	int merge_count = size_a / 2;

	//remainder of merge_count
	int left_over = size_a % 2;

	int offset = 0;

	int size = 1;
	int temp = 0;
	for(int i = 0; i < layer; ++i) {
		for(int j = 0; j < merge_count - 1; ++j) {
			offset = 2 * size * j;
			merge(array + offset * size_e, size, size, size_e, compare);
		}

		offset = 2 * size * (merge_count - 1);

		if(left_over) {
			merge(array + offset * size_e, size, size, size_e, compare);
		} else {
			merge(array + offset * size_e, size, size_a - offset - size, size_e, compare);
		}

		temp = (merge_count + left_over) / 2;
		left_over = (merge_count + left_over) % 2;
		merge_count = temp;

		size <<= 1;
	}
}
