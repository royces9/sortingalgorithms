#include "shuffle.h"
#include "swap.h"


void insertion(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int begin = 0;
	for(int i = 1; i < size_a; ++i) {
		if(compare(array + (i - 1) * size_e, array + i * size_e)) {
			for(; compare(array + i * size_e, array + begin * size_e) && (begin < size_a); ++begin);

			for(int k = i; k > begin; --k) {
				swap(array + (k - 1) * size_e, array + k * size_e, size_e);
			}
		}
	}
}


int divide_two(int a) {
	while(!(a % 2))
		a /= 2;

	return a;
}


void swap_cycle(void *array, int start_ind, int cur_ind, int l_size, int size_e) {
	//new location
	int new_ind = start_ind;

	while(cur_ind != start_ind) {
		swap(array + cur_ind * size_e, array + new_ind * size_e, size_e);

		new_ind = cur_ind;
		cur_ind = divide_two(((new_ind - 1) / 2) + l_size);
	}
}



int next_in_order(void *array, int cur_ind, int new_ind, int size_e, int (*compare)(void *, void *)) {
	//equivalent to !(compare(cur, new) ^ (cur > new));
	return compare(array + cur_ind * size_e, array + new_ind * size_e) ^ (cur_ind < new_ind);
}


void small(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int log = 0;
	for(int size = size_a; !(size % 2) ; size /= 2, ++log);
	log <<= 1;
	for(int j = 3; j < log; j += 2) {
		for(int i = size_a - 1; i >= j; --i) {
			if(compare(array + (i - j) * size_e, array + i * size_e)) {
				swap(array + (i - j) * size_e, array + i * size_e, size_e);
			}
		}
	}
}

//mergesort
//inplace merge
//alternates the two sub array elements
//then uses insertion sort on the merged list
void merge(void *array, int l_size, int r_size, int size_e, int (*compare)(void *, void *)) {
        int size = l_size + r_size;

	for(int i = l_size - 1; i > 0; --i) {
		int new_ind = i * 2;
		swap(array + i * size_e, array + new_ind * size_e, size_e);
	}

	//how orig_ind is defined
	//orig_ind = (new_ind - 1) / 2 + l_size;
	for(int new_ind = 1, orig_ind = l_size; new_ind < size; new_ind += 2, ++orig_ind) {
		int cur_ind = divide_two(orig_ind);

		if(!next_in_order(array, new_ind, cur_ind, size_e, compare))
			swap_cycle(array, new_ind, cur_ind, l_size, size_e);
	}

	small(array, size, size_e, compare);

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
