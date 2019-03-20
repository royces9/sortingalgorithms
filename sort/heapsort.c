#include "shuffle.h"
#include "swap.h"
#include "heap.h"

//heapsort
//max heap

void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	build_heap(array, size_a , size_e, compare);

	for(int last = size_a - 1;
	    last > 2;
	    --last) {
		swap(array + last * size_e, array, size_e);
		sink_heap(array, last, size_e, compare);
	}

	//last two elements
	if(size_a > 2)
		swap(array + 2 * size_e, array, size_e);

	if(compare(array, array + size_e))
		swap(array + size_e, array, size_e);
}
