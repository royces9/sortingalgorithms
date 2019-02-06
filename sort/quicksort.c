#include "shuffle.h"
#include "compare.h"
#include "swap.h"


void sort_r(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int left = 1;
	int right = size_a - 1;

	void *pivot = array + (size_a / 2) * size_e;
	void *end = array + right * size_e;

	if(compare(array, pivot) ^ compare(pivot, end))
		pivot = compare(array, end) ? end : array;

	swap(array, pivot, size_e);

	while(right > left) {
		for(; (left < right) && compare(array, array + left * size_e); ++left);
		for(; (right > left) && compare(array + right * size_e, array); --right);

		swap(array + left * size_e,
		     array + right * size_e,
		     size_e);
	}

	if(compare(array, array + left * size_e))
		swap(array, array + left * size_e, size_e);

	if(left > 1)
		sort_r(array, left, size_e, compare);

	if((size_a - left) > 1)
 		sort_r(array + left * size_e, size_a - left, size_e, compare);
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	if(size_a != 1)
		sort_r(array, size_a, size_e, compare);
}
