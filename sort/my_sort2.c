#include "swap.h"

void sort(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int j = (size_a - 1); j >= 0; --j) {
		for(int i = size_a - 1; i >= j; --i) {
			if(compare(array + (i - j) * size_e, array + i * size_e)) {
				swap(array + (i - j) * size_e, array + i * size_e, size_e);
			}
		}
	}
}
