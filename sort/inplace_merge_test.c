#include "shuffle.h"
#include "swap.h"

typedef unsigned int uint;


void insertion_(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int i = 1; i < size_a; ++i) {
		for(int j = i; (j > 0) && (compare(array + (j - 1) * size_e, array + j * size_e) > 0); --j) {
			swap(array + (j - 1) * size_e, array + j * size_e, size_e);
		}
	}
}


void insertion(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int begin = 0;
	for(int i = 1; i < size_a; ++i) {
		if(compare(array + (i - 1) * size_e, array + i * size_e) > 0) {
			for(; (compare(array + i * size_e, array + begin * size_e) > 0) && (begin < size_a); ++begin);

			for(int k = i; k > begin; --k) {
				swap(array + (k - 1) * size_e, array + k * size_e, size_e);
			}
		}
	}
}


inline uint divide_two(uint a) {
	uint pow = __builtin_ctz(a);
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

//check that the values are in order, indexes can loop
//so pointer values are checked too
int in_order(char *a, char *b, int (*compare)(void *, void *)) {
	return (compare(a, b) > 0) == (a > b);
}

//mergesort
//inplace merge
//alternates the two sub array elements
//then uses insertion sort on the merged list
void merge(char *array, int l_size, int r_size, int size_e, int (*compare)(void *, void *)) {
        uint size = l_size + r_size;

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
