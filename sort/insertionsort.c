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
	for(int i = 0; i < size_a; i ++) {
		for(int j = i; j > 0; j--) {
			if(compare(array + size_e * (j - 1), array + size_e * j)) {
				swap((array + size_e * j), (array + size_e * (j - 1)), size_e);
			} else {
				break;
			}
		}

	}
}
