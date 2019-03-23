#include "swap.h"


void cycle(int *array, int ind) {
	while(ind != array[ind]) {
		int swap_ind = array[ind];
		swap((char *)&array[ind], (char *)&array[swap_ind], sizeof(int));
	}
}


void sort(int *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int i = 0; i < size_a; ++i) {
		if(i != array[i]) {
			cycle(array, i);
		}
	}
}
