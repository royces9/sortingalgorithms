#include "shuffle.h"
#include "swap.h"

typedef unsigned int uint;


void insertion(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
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


uint divide_two(uint a) {
	uint pow = a & (~(a - 1));
	pow = __builtin_ctz(pow);
	return a >> pow;
}


int swap_cycle(char *array, uint start_ind, uint cur_ind, uint l_size, int size_e) {
	int out = 1;

	for(uint new_ind = start_ind; cur_ind != start_ind; ++out) {
		swap(array + cur_ind * size_e, array + new_ind * size_e, size_e);

		new_ind = cur_ind;
		cur_ind = divide_two(((new_ind - 1) / 2) + l_size);
	}

	return out;
}


int next_in_order(char *array, uint cur_ind, uint new_ind, int size_e, int (*compare)(void *, void *)) {
	//equivalent to !(compare(cur, new) ^ (cur > new));
	return compare(array + cur_ind * size_e, array + new_ind * size_e) ^ (cur_ind < new_ind);
}


//mergesort
//inplace merge
//alternates the two sub array elements
//then uses insertion sort on the merged list
void merge(char *array, int l_size, int r_size, int size_e, int (*compare)(void *, void *)) {
        uint size = l_size + r_size;

	for(int i = l_size - 1; i > 0; --i) {
		uint new_ind = i * 2;
		swap(array + i * size_e, array + new_ind * size_e, size_e);
	}


	for(uint new_ind = 1, orig_ind = l_size, total = 1;
	    total < size;
	    new_ind += 2, ++orig_ind, total += 2) {
		uint cur_ind = divide_two(orig_ind);

		if(!next_in_order(array, new_ind, cur_ind, size_e, compare))
			total += swap_cycle(array, new_ind, cur_ind, l_size, size_e);
	}

	insertion(array, size, size_e, compare);
}


//bottom up
void sort(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int left = size_a / 2;
	int right = size_a - left;

	if(left > 1)
		sort(array, left, size_e, compare);

	if(right > 1)
		sort(array + left * size_e, right, size_e, compare);

	merge(array, left, right, size_e, compare);
}
