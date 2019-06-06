#include "shuffle.h"

#include "heap.h"
#include "swap.h"


//heapsort
//min heap

int (*g_comp)(void *, void *);

int heap_compare(void *a, void *b) {
	return -g_comp(a, b);
}

void sort(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {

	g_comp = compare;

	build_heap(array, size_a , size_e, heap_compare);

	for(int last = size_a - 1;
	    last > 2;
	    --last) {
		swap(array + last * size_e, array, size_e);
		sink_heap(array, last, size_e, heap_compare);
	}

	//last two elements
	if(size_a > 2)
		swap(array + 2 * size_e, array, size_e);

	if(heap_compare(array, array + size_e))
		swap(array + size_e, array, size_e);

	for(int front = 0, back = size_a - 1; front < back; ++front, --back) {
		swap(array + front * size_e, array + back * size_e, size_e);
	}
}
