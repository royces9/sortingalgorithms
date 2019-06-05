#include "shuffle.h"
#include "swap.h"

#define SMALL_SIZE 10
#define RECURSE_LIM

void insertion(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int i = 1; i < size_a; ++i) {
		for(int j = i; (j > 0) && compare(array + (j - 1) * size_e, array + j * size_e); --j) {
			swap(array + (j - 1) * size_e, array + j * size_e, size_e);
		}
	}
}

void sort_r(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {

	if(size_a < SMALL_SIZE) {
		insertion(array, size_a, size_e, compare);
		return;
	}

	int left = 1;
	int right = size_a - 1;

	//choose pivot and put into first slot
	char *pivot = array + (right / 2) * size_e;
	char *end = array + right * size_e;

	int comp = compare(array, pivot);

	if(comp ^ compare(pivot, end)) {
		if(!(compare(array, end) ^ comp))
			swap(array, end, size_e);
	} else {
		swap(array, pivot, size_e);
	}
	
	//partitioning
	while(right > left) {
		for(; (right > left) && compare(array + right * size_e, array); --right);
		for(; (left < right) && compare(array, array + left * size_e); ++left);

		swap(array + left * size_e,
		     array + right * size_e,
		     size_e);

		--right;
	}

	swap(array, array + left * size_e, size_e);

	if(left > 2) {
		sort_r(array, left, size_e, compare);
	} else if(left == 2) {
		if(compare(array, array + size_e))
			swap(array, array + size_e, size_e);
	}

	if((size_a - left - 1) > 2) {
		sort_r(array + (left + 1) * size_e, size_a - left - 1, size_e, compare);
	} else if((size_a - left - 1) == 2) {
		if(compare(array + (left + 1) * size_e, array + (left + 2) * size_e))
			swap(array + (left + 1) * size_e, array + (left + 2) * size_e, size_e);
	}
}


void sort(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	if(size_a > 2) {
		sort_r(array, size_a, size_e, compare);

	} else if(size_a == 2) {
		if(compare(array, array + size_e))
			swap(array, array + size_e, size_e);
	}
}
