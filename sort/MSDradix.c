#include <stdint.h>

#include "shuffle.h"
#include "swap.h"


int highest_bit(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int out = 0;

	int total_bits = size_e * 8 - 1;
	uint64_t max = 1ULL << total_bits;

	for(int i = 0; i < size_a; ++i) {
		int place_counter = total_bits;

		for(uint64_t j = max; j > 0; j >>= 1, --place_counter) {
			if(compare(&j, array + size_e * i) && (place_counter > out)) {
				out = place_counter;
				break;
			}
		}
	}

	return out;
}


//MSD radix
void MSDradix(void *array, int size_a, int size_e, int bit , int (*compare)(void *, void *)) {
	//uint64_t bit = 1ULL << (uint64_t) max;

	int left = 0;
	int right = size_a - 1;

	while(right > left) {
		for(; (left < right) && compare(&bit, array + left * size_e); ++left);
		for(; (right > left) && !compare(&bit, array + right * size_e); --right);

		swap(array + left * size_e,
		     array + right * size_e,
		     size_e);
	}

	/*
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
	*/

	if(bit > 0) {
		if(right)
			MSDradix(array, right + 1, size_e, bit >> 1, compare);

		if(size_a - right - 1)
			MSDradix(array + (right + 1) * size_e, size_a - right - 1, size_e, bit >> 1, compare);
	}
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int max = highest_bit(array, size_a, size_e, compare);
	int bit = 1ULL << max;
	MSDradix(array, size_a, size_e, bit, compare);
}
