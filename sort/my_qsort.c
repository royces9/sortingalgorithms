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

	if(compare(array, pivot))
		swap(array, pivot, size_e);

	if(compare(pivot, end))
		swap(pivot, end, size_e);
	else if(compare(array, pivot))
		swap(array, pivot, size_e);
	
	int piv_loc = 0;
	//partitioning
	while(right > left) {
		for(;compare(pivot, array + left * size_e); ++left);
		for(;compare(array + right * size_e, pivot); --right);

		if(pivot == (array + left * size_e)) {
			pivot = array + right * size_e;			
		} else if(pivot == (array + right * size_e)) {
			pivot = array + left * size_e;
		}
		swap(array + left * size_e,
		     array + right * size_e,
		     size_e);
	}


	sort_r(array, piv_loc, size_e, compare);
	sort_r(array + piv_loc * size_e, size_a - piv_loc, size_e, compare);
	/*
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
	*/
}


void sort(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	if(size_a > 2) {
		sort_r(array, size_a, size_e, compare);

	} else if(size_a == 2) {
		if(compare(array, array + size_e))
			swap(array, array + size_e, size_e);
	}
}
