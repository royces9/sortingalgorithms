#include <stdlib.h>

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
void merge(void *array, int size, int size2, int size_e, int (*compare)(void *, void *)) {
        int total_size = size + size2;
	void *combinedArray = malloc(size_e * total_size);

	int head[2] = {0, size};

	void *src = NULL;

	int copy_head = 0;
	for(int i = 0; i < total_size; ++i) {
		if(head[1] >= total_size) {
			src = array + size_e * head[0]++;
		} else if(head[0] >= size) {
			src = array + size_e * head[1]++;
		} else {
			src = array + (size_e * head[compare((array + size_e * head[0]), (array + size_e * head[1]))]++);
		}

		copy(src, combinedArray + size_e * i, size_e);
	}

	for(int j = copy_head; j < total_size; ++j)
		copy((combinedArray + size_e * j), (array + size_e * j), size_e);

	free(combinedArray);
}


//bottom up
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
