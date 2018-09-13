#include <math.h>
#include <stdlib.h>

#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;

int compare(void *a, void *b) {
	return *(int *) a & *(int *) b;
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


void copy(void *src, void *dest, int size_e) {
	int word_loops = size_e / 4;
	int byte_loops =  size_e % 4;

	for(int i = 0; i < word_loops; ++i)
		*(int *)(dest++) = *(int *)(src++);

	for(int i = 0; i < byte_loops; ++i)
		*(char *)(dest++) = *(char *)(src++);
}


int highest_bit(void *array, int size_a, int size_e) {
	int out = 1;
	int comp = 0;

	for(int i = 0; i < size_a; ++i) {
		for(int j = size_e; j > 0; --j) {
			for(int k = 7; k >= 0; --k) {
				comp = 1 << k;
				comp <<= (8 * j);
				if(compare(array + size_e * i, &comp)) {
					out = (8 * j) + k;
				}
			}
		}
	}

	return out;
}


//LSD radix
void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	void *dupArray = malloc(size_e * size_a);

	int max = highest_bit(array, size_a, size_e);

	int copyIndex = 0;
	int tempIndex = 0;
	for(int j = 1; j <= max; j <<= 1) {
		copyIndex = 0;
		tempIndex = size_a - 1;
		for(int i = 0; i < size_a; ++i) {
			if(!compare(array + size_e * i, &j)) {
				//swap(a + i, a + copyIndex++, size_e);
				copy(array + size_e * i, dupArray + size_e * copyIndex++, size_e);
			} else {
				//swap(a + i, a + tempIndex-i, size_e);
				copy(array + size_e * i, dupArray + size_e * tempIndex--, size_e);
			}
		}
		copyArray(dupArray, array, size_a, size_e);

		/*
		for(int l = copyIndex; l < size_a; ++l) {
			//swap(a + ((size_a + copyIndex - 1) - l), a + l, size_e);
			a[l] = dupArray[(size_a + copyIndex - 1) - l];
		}
		*/
	}

}
