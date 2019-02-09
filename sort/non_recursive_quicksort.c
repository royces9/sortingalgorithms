#include <stdlib.h>

#include "shuffle.h"
#include "copy.h"
#include "swap.h"


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
        int leftCount = 0;
	int rightCount = size_a - 1;

	void *pivot = compare(array, array + size_e * size_a / 2) ? array : array + size_e * size_a / 2;
	void *pivot2 = compare(array, array + size_e * size_a - 1) ? array : array + size_e * size_a - 1;
	pivot = compare(pivot, pivot2) ? pivot2 : pivot;

	pivot2 = malloc(size_e);
	copy(pivot, pivot2, size_e);


	for(int i = 0; leftCount != rightCount; ++i) {
		for(;compare(pivot2, array + size_e * leftCount); ++leftCount);
		for(;compare(array + size_e * rightCount, pivot2); --rightCount);

		swap(array + size_e * leftCount,
		     array + size_e * rightCount,
		     size_e);
	}
	free(pivot2);

	if(rightCount != 1)
		sort(array, rightCount, size_e, compare);

	if((size_a - rightCount) != 1)
 		sort(array + size_e * leftCount, size_a - rightCount, size_e, compare);
}
