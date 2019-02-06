#include <stdlib.h>

#include "shuffle.h"
#include "compare.h"
#include "copy.h"


//mergesort
void merge(void *array, void *scratch, int left_size, int right_size, int size_e, int (*compare)(void *, void*)){
	int total_size = left_size + right_size;
	int head[2] = {0, left_size};

        int i = 0;
	for(; (head[1] < total_size) && (head[0] < left_size); ++i) {
		int index = compare(array + head[0] * size_e, array + head[1] * size_e);
		int src = head[index]++;
		copy(array + src * size_e, scratch + i * size_e, size_e);
	}

	if(head[0] < left_size) {
		for(; i < total_size; ++i)
			copy(array + (head[0]++) * size_e, scratch + i * size_e, size_e);
	}

	for(int j = 0; j < i; ++j)
		copy(scratch + j * size_e, array + j * size_e, size_e);

	/*
	//this is actually faster using -O3
	//only slightly slower or even with -O0/1/2

        int src = 0;
        for(int i = 0; i < total_size; ++i) {
                if(head[1] >= total_size) {
                        src = head[0]++;
                } else if(head[0] >= left_size) {
                        src = head[1]++;
                } else {
                        src = head[compare(array + head[0] * size_e, array + head[1] * size_e)]++;
                }

                copy(array + src * size_e, scratch + i * size_e, size_e);
        }

        for(int j = 0; j < total_size; ++j)
                copy(scratch + j * size_e, array + j * size_e, size_e);
	*/
}


void start_sort(void *array, void *scratch, int size_a, int size_e, int (*compare)(void *, void *)) {
	int left_size = size_a / 2;
	int right_size = size_a - left_size;

	if(left_size > 1)
		start_sort(array, scratch, left_size, size_e, compare);

	if(right_size > 1)
		start_sort(array + left_size * size_e, scratch, right_size, size_e, compare);

	merge(array, scratch, left_size, right_size, size_e, compare);
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	void *scratch = malloc(size_a * size_e);

	start_sort(array, scratch, size_a, size_e, compare);

	free(scratch);
}
