#include "shuffle.h"
#include "swap.h"


//insertion sort
void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int i = 0; i < size_a; ++i) {

		for(int j = i; j >= 0; --j) {
			if(compare(array + j * size_e, array + (j + 1) * size_e)) {
				swap(array + j * size_e, array + (j + 1) * size_e, size_e);
			} else {
				break;
			}
		}
	}
}
