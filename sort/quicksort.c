#include "shuffle.h"
#include "swap.h"


void sort_r(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int left = 1;
	int right = size_a - 1;

	void *pivot = array + (right / 2) * size_e;
	void *end = array + right * size_e;

	int comp = compare(array, pivot);

	if(comp ^ compare(pivot, end)) {
		if(!(compare(array, end) ^ comp))
			swap(array, end, size_e);
	} else {
		swap(array, pivot, size_e);
	}
	
	while(right > left) {
		for(; (left < right) && compare(array, array + left * size_e); ++left);
		for(; (right > left) && compare(array + right * size_e, array); --right);

		swap(array + left * size_e,
		     array + right * size_e,
		     size_e);
	}

	swap(array, array + (left - 1) * size_e, size_e);

	if((left - 1) > 2) {
		sort_r(array, left - 1, size_e, compare);
	} else if((left - 1) > 1) {
		if(compare(array, array + size_e))
			swap(array, array + size_e, size_e);
	}

	if((size_a - left) > 2) {
		sort_r(array + left * size_e, size_a - left, size_e, compare);
	} else if((size_a - left) > 1) {
		if(compare(array + left * size_e, array + (left + 1) * size_e))
			swap(array + left * size_e, array + (left + 1) * size_e, size_e);
	}
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	if(size_a != 1)
		sort_r(array, size_a, size_e, compare);
}
