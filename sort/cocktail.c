#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;

#include "compare.h"
#include "swap.h"


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int j = 0, left_bound = 0, right_bound = size_a;
	    j < size_a/2;
	    ++j) {

		int min = left_bound;
		for(int i = left_bound + 1; i < right_bound; ++i) {
			if(compare(array + min * size_e, array + i * size_e))
				min = i;
		}
		swap(array + left_bound * size_e, array + min * size_e, size_e);
		++left_bound;

		int max = right_bound - 1;
		for(int i = right_bound - 2; i >= left_bound; --i) {
			if(compare(array + i * size_e, array + max * size_e))
				max = i;
		}
		
		swap(array + (right_bound - 1) * size_e, array + max * size_e, size_e);
		--right_bound;
	}
}
