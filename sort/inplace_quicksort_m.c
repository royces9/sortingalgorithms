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


void sort_r(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int left = size_e;
	int right = size_a - size_e;

	void *pivot = array + (size_a / (2 * size_e)) * size_e;
	void *end = array + right;

	if(compare(array, pivot) ^ compare(pivot, end))
		pivot = compare(array, end) ? end : array;

	swap(array, pivot, size_e);

	while(right != left) {
		for(; left < right && !compare(array + left, array); left += size_e);
		for(; right > left && !compare(array, array + right); right -= size_e);

		swap(array + left,
		     array + right,
		     size_e);
	}

	if(compare(array, array + left))
		swap(array, array + left, size_e);

	if(left > size_e)
		sort_r(array, left, size_e, compare);


	if((size_a - left) > size_e)
 		sort_r(array + left, size_a - left, size_e, compare);
}



void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	if(size_a == 1)
		return;

	sort_r(array, size_a * size_e, size_e, compare);
}
