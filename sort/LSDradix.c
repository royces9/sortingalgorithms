#include <math.h>
#include <stdlib.h>

#include "shuffle.h"

extern int *globalArray;
extern int globalSize;

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

	printArray(globalArray, globalSize);
}


//LSD radix
void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int *a = array;
	int *dupArray = malloc(size_e * size_a);
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
		for(int i = 0; i < size_a; ++i) {
			if(!(a[i] & j)) {
				//swap(a + i, a + copyIndex++, size_e);
				dupArray[copyIndex++] = a[i];
			} else {
				//swap(a + i, a + tempIndex-i, size_e);
				dupArray[tempIndex--] = a[i];
			}
		}
		copyArray(dupArray, a, size_a, sizeof(int));

		printf("dup: ");
		printArray(dupArray, size_a);

		printf("a  : ");
		printArray(a, size_a);


		/*
		for(int l = copyIndex; l < size_a; ++l) {
			//swap(a + ((size_a + copyIndex - 1) - l), a + l, size_e);
			a[l] = dupArray[(size_a + copyIndex - 1) - l];
		}
		*/
	}

}
