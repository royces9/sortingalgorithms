#include <stdint.h>

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


int highest_bit(void *array, int size_a, int size_e) {
	int out = 0;

	int total_bits = size_e * 8 - 1;
	int place_counter = total_bits;

	uint64_t max = 1ULL << total_bits;

	for(int i = 0; i < size_a; ++i) {
		place_counter = total_bits;

		for(uint64_t j = max; j > 0; j >>= 1, --place_counter) {
			if(compare(array + size_e * i, &j) && (place_counter > out)) {
				out = place_counter;
				break;
			}
		}
	}

	return out;
}


//MSD radix
void MSDradix(void *array, int size_a, int size_e, int max, int (*compare)(void *, void *)) {
	uint64_t bit = 1ULL << (uint64_t) max;

	int writeHead = size_a - 1;
	for(int readHead = size_a - 1; readHead >= 0; --readHead) {
		if(compare(&bit, array + readHead * size_e)) {
			swap(array + readHead * size_e,
			     array + writeHead * size_e,
			     size_e);
			--writeHead;
		}
	}

	if(max > 0) {
		if(writeHead)
			MSDradix(array, writeHead + 1, size_e, max - 1, compare);

		if(size_a - writeHead - 1)
			MSDradix(array + (writeHead + 1) * size_e, size_a - writeHead - 1, size_e, max - 1, compare);
	}
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int max = highest_bit(array, size_a, size_e);

	MSDradix(array, size_a, size_e, max, compare);
}
