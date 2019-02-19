#include "copy.h"
#include "shuffle.h"
#include "swap.h"

void insertion(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int i = 0; i < size_a; ++i) {
                for(int j = i; (j >= 1) && compare(array + (j - 1) * size_e, array + j * size_e); --j) {
			swap(array + (j - 1) * size_e, array + j * size_e, size_e);
		}
	}
}
	  

int divide_two(int a) {
	while(!(a % 2))
		a /= 2;

	return a;
}


void swap_cycle(void *array, int start_ind, int orig_ind, int l_size, int size_e) {
	//current location
	int cur_ind = divide_two(orig_ind);

	//new location
	int new_ind = start_ind;
	while(cur_ind != start_ind) {
		swap(array + cur_ind * size_e, array + new_ind * size_e, size_e);

		new_ind = cur_ind;
		cur_ind = divide_two(((new_ind - 1) / 2) + l_size);
	}
}


int next_in_order(void *array, int cur_ind, int new_ind, int size_e, int(*compare)(void *, void *)) {
	return !compare(array + cur_ind * size_e, array + new_ind * size_e) ^ (cur_ind > new_ind);
}


int in_order(void *array, int index, int size, int size_e, int (*compare)(void *, void *)) {
	for(int i = index + 4; i < size; i += 2) {
		if(compare(array + (i - 2) * size_e, array + i * size_e))
			return 0;
	}

	return 1;
}


//mergesort
//inplace merge
void merge(void *array, int l_size, int r_size, int size_e, int (*compare)(void *, void *)) {
        int size = l_size + r_size;

	for(int i = l_size - 1; i > 0; --i) {
		int new_ind = i * 2;
		swap(array + i * size_e, array + new_ind * size_e, size_e);
	}


	//for(int new_ind = 1; new_ind < size ; new_ind += 2) {
	for(int new_ind = 1; (!in_order(array, new_ind, size, size_e, compare)) && (new_ind < size) ; new_ind += 2) {
		int orig_ind = (new_ind - 1) / 2 + l_size;
		if(!next_in_order(array, new_ind, divide_two(orig_ind), size_e, compare)) {
			swap_cycle(array, new_ind, orig_ind, l_size, size_e);
		}
	}

	insertion(array, size, size_e, compare);
}


//bottom up
void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int left = size_a / 2;
	int right = size_a - left;

	if(left > 1)
		sort(array, left, size_e, compare);

	if(right > 1)
		sort(array + left * size_e, right, size_e, compare);

	merge(array, left, right, size_e, compare);
}
