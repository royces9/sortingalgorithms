#include "shuffle.h"
#include "swap.h"

//insertion sort
void sort(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int i = 1; i < size_a; ++i) {
		for(int j = i; (j > 0) && (compare(array + (j - 1) * size_e, array + j * size_e) > 0); --j) {
			swap(array + (j - 1) * size_e, array + j * size_e, size_e);
		}
	}
}
