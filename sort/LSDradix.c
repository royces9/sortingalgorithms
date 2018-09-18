#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;

int printf(const char *, ...);

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

	if(flag & 8)
		printArray(globalArray, globalSize);
}


int highest_bit(void *array, int size_a, int size_e) {
	int total_bits = size_e * 8 - 1;
	int place_counter = total_bits;

	int out = 1;
	uint64_t max = 1ULL << total_bits;

	for(int i = 0; i < size_a; ++i) {
		place_counter = total_bits;
		for(uint64_t j = max; j > 0; j >>= 1, --place_counter) {
			if(compare(array + size_e * i, &j)) {
				if(place_counter > out) {
					out = place_counter;
					break;
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

	uint64_t j = 1;
	for(int i = 0; i <= max; ++i, j <<= 1ULL) {
		copyIndex = 0;
		tempIndex = size_a - 1;
		for(int k = 0; k < size_a; ++k) {
			if(!compare(array + size_e * k, &j)) {
				copy(array + size_e * k, dupArray + size_e * copyIndex++, size_e);
			} else {
				copy(array + size_e * k, dupArray + size_e * tempIndex--, size_e);
			}
		}

		for(int l = 0; l < copyIndex; ++l)
			copy(dupArray + size_e * l, array + size_e * l, size_e);

		for(int l = copyIndex; l < size_a; ++l)
			copy(dupArray + size_e * ((size_a - 1) + copyIndex - l), array + size_e * l, size_e);

	}
	free(dupArray);
}
