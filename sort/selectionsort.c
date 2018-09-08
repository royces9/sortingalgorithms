#include "shuffle.h"

void swap(void *a, void *b, int size_e) {
	char temp = 0;
	char *c_a = a;
	char *c_b = b;
	for(int i = 0; i < size_e; ++i) {
		temp  = *c_a;
		*c_a++ = *c_b;
		*c_b++ = temp;
	}
}


void sort(int *array, int size_a, int size_e, int (*compare)(void *, void *)) {
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
