#include "shuffle.h"
#include "swap.h"


void sort(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int begin = 0;
	int end = size_a;

	for(int flag = 1; flag;) {
		flag = 0;
		for(int i = ++begin; i < size_a; ++i) {
			if(compare(array + (i - 1) * size_e, array + i * size_e)) {
				swap(array + (i - 1) * size_e, array + i * size_e, size_e);
				flag = 1;
			}
		}

		for(int j = --end; j > 0; --j) {
			if(compare(array + (j - 1) * size_e, array + j * size_e)) {
				swap(array + (j - 1) * size_e, array + j * size_e, size_e);
				flag = 1;
			}
		}
	}
}
