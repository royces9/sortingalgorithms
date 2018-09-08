#ifndef LSDRADIX
#define LSDRADIX

#include <math.h>
#include <stdlib.h>

#include "shuffle.h"

//LSD radix
void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int *a = array;
	int *dupArray = malloc(sizeof(*dupArray) * size_a);
	int max = 0;

	for(int j = 0; j < size_a; j++) {
		if(a[j] == (size_a - 1)) {
			max = a[j];
			break;
		}
	}

	max = pow(2,floor(log(max)/log(2)));

	int copyIndex = 0;
	int tempIndex = 0;
	for(int j = 1; j <= max; j <<= 1) {
		copyIndex = 0;
		tempIndex = size_a - 1;
		for(int i = 0; i < size_a; i++) {
			if(!(a[i] & j)) {
				dupArray[copyIndex++] = a[i];
			} else {
				dupArray[tempIndex--] = a[i];
			}
		}

		copyArray(a, dupArray, copyIndex, sizeof(int));

		for(int l = copyIndex; l < size_a; l++) {
			a[l] = dupArray[(size_a + copyIndex - 1) - l];
		}
	}

}

#endif //LSDRADIX
