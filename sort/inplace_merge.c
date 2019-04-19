#include "shuffle.h"
#include "swap.h"

//pretty sure this is something like Batcher odd even merge
//or inplace weave merge? idk

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


inline uint divide_two(uint a) {
	//find first 1 bit from the lsb
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


//checkthat the valuesare in order, indexes can loop
//so pointer values are checked too
inline int in_order(char *a, char *b, int (*compare)(void *, void *)) {
	return compare(a, b) == (a > b);
}

//mergesort
//inplace merge
//alternates the two sub array elements
//then uses insertion sort on the merged list
void merge(char *array, int l_size, int r_size, int size_e, int (*compare)(void *, void *)) {
        uint size = l_size + r_size;

	for(int i = (l_size - 1) * size_e; i > 0; i -= size_e)
		swap(array + i, array + i * 2, size_e);

	//how orig_ind is defined
	//orig_ind = (new_ind - 1) / 2 + l_size;
	for(uint new_ind = 1, orig_ind = l_size, total = 1;
	    total < size;
	    new_ind += 2, ++orig_ind, total += 2) {
		uint cur_ind = divide_two(orig_ind);

		if(!in_order(array + new_ind * size_e, array + cur_ind * size_e, compare))
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
