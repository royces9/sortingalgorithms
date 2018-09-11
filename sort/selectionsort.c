#include "shuffle.h"

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


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int min = 0;
	int i = 0;
	for(int j = 0; j < size_a; j++) {
		min = j;
		for(i = 0; i < size_a - j; i++) {
			if(compare((array + size_e * min), (array + size_e * (i + j))))
				min = i+j;
		}
		swap(array + size_e * min, array + size_e * j, size_e);
	}
}
