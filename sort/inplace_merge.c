#include <stdlib.h>

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


void swap_cycle(void *array, int start_ind, int og_ind, int l_size, int size_e) {
	int cur_ind = divide_two(og_ind);
	int new_ind = start_ind;
	do {
		swap(array + cur_ind * size_e, array + new_ind * size_e, size_e);

		new_ind = cur_ind;
		cur_ind = divide_two(((new_ind - 1) / 2) + l_size);

	} while(new_ind != start_ind);
}


//mergesort
//inplace merge
void merge(void *array, int l_size, int r_size, int size_e, int (*compare)(void *, void *)) {
	int size = l_size + r_size;

	for(int i = l_size - 1; i > 1; --i) {
		int new_ind = i * 2;
		swap(array + i * size_e, array + new_ind * size_e, size_e);
	}

	/*
	int stored_ind = -1;
	void *store = malloc(size_e);
	for(int i = size - 2; i > l_size; --i) {
		//final position of element
		int new_ind = (i - l_size) * 2 + 1;

		//where the element is now
		int cur_ind = divide_two(i);

		if(stored_ind == cur_ind) {
			swap(store, array + new_ind * size_e, size_e);
			stored_ind = new_ind;
		} else {
			copy(array + new_ind * size_e, store, size_e);
			copy(array + cur_ind * size_e, array + new_ind * size_e, size_e);
			stored_ind = new_ind;
		}
	}
	printf("%d %d\n", *(int *) store, stored_ind);
	printArray(array, size);
	printf("\n");
	
	free(store);
	*/




	//for(int i = 0, count = 1; i < size; count += 2) {
		int new_ind = 1;
		int og_ind = (new_ind - 1) / 2 + l_size;
		/*
		int cur_ind = divide_two(og_ind);
		do {
			swap(array + cur_ind * size_e, array + new_ind * size_e, size_e);

			new_ind = cur_ind;
			cur_ind = divide_two(((new_ind - 1) / 2) + l_size);

			++i;
		} while(new_ind != count);
		*/
		swap_cycle(array, new_ind, og_ind, l_size, size_e);
		//}

	insertion(array, size, size_e, compare);



	//if not in place
	/*
	int size = l_size + r_size;
	void *temp = malloc(size * size_e);

	for(int left = 0, i = 0; left < l_size; ++left, i += 2) {
		copy(array + left * size_e, temp + i * size_e, size_e);
	}

	for(int right = l_size, i = 1; right < size; ++right, i += 2) {
		if(i >= size)
			i = (size - 1);

		copy(array + right * size_e, temp + i * size_e, size_e);
	}

	for(int i = 0; i < size; ++i) {
		copy(temp + i * size_e, array + i * size_e, size_e);
	}

	if(size > 100)
		getchar();

	insertion(array, size, size_e, compare);
	*/
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
