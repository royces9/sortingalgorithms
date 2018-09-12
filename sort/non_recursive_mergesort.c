#include <stdlib.h>

#include "shuffle.h"

extern int *globalArray;
extern int globalSize;

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

	//printArray(globalArray, globalSize);
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

	int left = 0;
	int right = size;
	for(int i = 0; i < size_total; ++i) {
		//printf("%d %d %d %d\n", size, size2, left, right);
		//printf("%d %d\n", *(int *) array + size_e * left, *(int *) array + size_e * right);
		if(compare(array + size_e * left, array + size_e * right)) {
			swap(array + size_e * i, array + size_e * right, size_e);
			if(i == left) {
				left = right;
			}
			++right;

		} else {
			if(i == left) {
				++left;
			} else {
				swap(array + size_e * left, array + size_e * i, size_e);

				if(compare(array + size_e * (i + 1), compare + size_e * i)) {
					left = i;
				}
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
			printf("%d %d\n", size, size_a - (offset - 1));
			merge(array + offset * size_e, size, size_a - (offset - 1), size_e, compare);
		}

		temp = (merge_count + left_over) / 2;
		left_over = (merge_count + left_over) % 2;
		merge_count = temp;

		size <<= 1;
	}
}
