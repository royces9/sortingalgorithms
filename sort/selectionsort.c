#include "shuffle.h"
#include "compare.h"
#include "swap.h"


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int j = 0, min = 0;
	    j < size_a;
	    ++j, min = j) {

		for(int i = 0; i < size_a - j; ++i) {
			if(compare(array + min * size_e, array + (i + j) * size_e))
				min = i+j;
		}
		swap(array + min * size_e, array + j * size_e, size_e);
	}
}
