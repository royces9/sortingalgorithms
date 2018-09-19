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

	if(flag & 8)
		printArray(globalArray, globalSize);
}


//bubblesort
void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int flag = 1;
	while(flag) {
		flag = 0;
		for(int i = 0; i < (size_a - 1); ++i) {
			if(compare(array + i * size_e, array + (i + 1) * size_e)) {
				swap(array + i * size_e, array + (i + 1) * size_e, size_e);
				flag = 1;
			}
		}
	}
}
