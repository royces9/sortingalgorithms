#include <stdlib.h>

#include "shuffle.h"
#include "compare.h"
#include "copy.h"


//mergesort
void merge(void *array, void *scratch, int left_size, int right_size, int size_e, int (*compare)(void *, void *)) {
        int total_size = left_size + right_size;
	int head[2] = {0, left_size};

	int i = 0;
	//keeps iterating until one of the sub lists is exhausted of elements
	for(; (head[1] < total_size) && (head[0] < left_size); ++i) {
                int index = compare(array + head[0] * size_e, array + head[1] * size_e);
		int src = head[index]++;
		copy(array + src * size_e, scratch + i * size_e, size_e);
	}

	//check if the left list still has elements to be merged
	if(head[0] < left_size) {
		for(; i < total_size; ++i)
			copy(array + (head[0]++) * size_e, scratch + i * size_e, size_e);
	}

	for(int j = 0; j < i; ++j)
		copy(scratch + j * size_e, array + j * size_e, size_e);
}


//bottom up
void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	//number of merges in layer
	int merge_count = size_a / 2;

	//remainder of merge_count
	int left_over = size_a % 2;

	int offset = 0;
	void *scratch = malloc(size_a * size_e);

	for(int size = 1; size < size_a; size <<= 1) {

		for(int j = 0; j < merge_count - 1; ++j) {
			offset = 2 * size * j;
			merge(array + offset * size_e, scratch, size, size, size_e, compare);
		}

		offset = 2 * size * (merge_count - 1);
		merge(array + offset * size_e, scratch, size,
		      left_over ? size : size_a - offset - size,
		      size_e, compare);
		

		int temp = (merge_count + left_over) / 2;
		left_over = (merge_count + left_over) % 2;
		merge_count = temp;
	}

	free(scratch);
}
