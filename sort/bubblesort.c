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


//bubblesort
void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)){
	int flag = 1;
	while(flag) {
		flag = 0;
		for(int i = 0; i < (size_a - 1); i++) {
			if(compare((array + size_e * i), (array + size_e * (i + 1)))) {
				swap((array + size_e * (i + 1)), (array + size_e * i), size_e);
				flag = 1;
			}
		}
	}
}
