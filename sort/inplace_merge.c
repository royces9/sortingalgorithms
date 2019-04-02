#include "shuffle.h"
#include "swap.h"

typedef unsigned int uint;


void small(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int log = 0;
	for(int size = size_a; size; size >>= 1, ++log);

	log /= 8;
	++log;
	log *= 2;
	
	for(int gap = log + 1; gap > 1; gap -= 2) {
		for(int i = size_a - 1; i >= gap; --i) {
			if(compare(array + (i - gap) * size_e, array + i * size_e)) {
				swap(array + (i - gap) * size_e, array + i * size_e, size_e);
			}
		}
	}
}


void cocktail(char *array, int size_a, int size_e, int (*compare)(void *, void*)) {
	int left = 0;
	int right = size_a - 1;

	for(int i = 0; left < right; ++i, ++left, --right) {
		if(compare(array + left * size_e, array + (left + 1) * size_e))
			swap(array + left * size_e, array + (left + 1) * size_e, size_e);

		if(compare(array + (right - 1) * size_e, array + right * size_e))
			swap(array + (right - 1) * size_e, array + right * size_e, size_e);
	}
}


void odd_even(char *array, int size_a, int size_e, int (*compare)(void *, void*)) {
        int flag = 1;
	for(int i = 0; (i < size_a) && flag; ++i) {
		flag = 0;
		for(int j = (i % 2) + 1; j < size_a; j +=2) {
			if(compare(array + (j - 1) * size_e, array + j * size_e)) {
				swap(array + (j - 1) * size_e, array + j * size_e, size_e);
				flag = 1;
			}
		}
	}
}


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
	uint count = a & (~(a - 1));

	return a / count;
}


int swap_cycle(char *array, uint start_ind, uint cur_ind, uint l_size, int size_e) {
	int out = 0;

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

	//how orig_ind is defined
	//orig_ind = (new_ind - 1) / 2 + l_size;
	for(uint new_ind = 1, orig_ind = l_size, total = 1;
	    total < size;
	    new_ind += 2, ++orig_ind, total += 2) {
		uint cur_ind = divide_two(orig_ind);

		if(!next_in_order(array, new_ind, cur_ind, size_e, compare))
			total += swap_cycle(array, new_ind, cur_ind, l_size, size_e);
	}

	//small(array, size, size_e, compare);

	//odd_even(array, size, size_e, compare);

	//cocktail(array, size, size_e, compare);
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
