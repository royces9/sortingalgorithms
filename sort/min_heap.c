#include "shuffle.h"

#include "heap.h"
#include "swap.h"


//heapsort
//min heap
/*
//swim the last index in the heap
void swimHeap(void *array, int child, int size_a, int size_e, int (*compare)(void *, void *)) {
	//index
	int parent = (size_a + 1 + child) / 2;

	while((child < (size_a - 1) && (compare(array + parent * size_e, array + child * size_e)))) {
		swap(array + parent * size_e, array + child * size_e, size_e);

		child = parent;
		parent = (size_a + 1 + child) / 2;
	}
}


void sinkHeap(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int child = size_a - 2;

	if((child > 0) && compare(array + child * size_e, array + (child  - 1) * size_e))
		--child;

	int parent = size_a - 1;

	while((child >= 0) && compare(array + parent * size_e, array + child * size_e)) {
		swap(array + parent * size_e, array + child * size_e, size_e);

		parent = child;
		child = 2 * parent - size_a;

		if((child > 0) && compare(array + child * size_e, array + (child  - 1) * size_e))
			--child;
	}


}


void buildHeap(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int i = size_a - 2; i >= 0; --i)
		swimHeap(array, i, size_a, size_e, compare);
}
*/

int (*g_comp)(void *, void *);

int heap_compare(void *a, void *b) {
	return !g_comp(a, b);
}

void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	/*
	g_comp = compare;

	build_heap(array, size_a , size_e, g_comp);

	for(int last = size_a - 1;
	    last > 2;
	    --last) {
		swap(array + last * size_e, array, size_e);
		sink_heap(array, last, size_e, g_comp);
	}

	//last two elements
	if(size_a > 2)
		swap(array + 2 * size_e, array, size_e);

	if(g_comp(array, array + size_e))
		swap(array + size_e, array, size_e);
	*/

	/*
	build_heap(array, size_a, size_e, g_comp);

	for(int last = 0;
	    last < (size_a - 3);
	    ++last) {

		swap(array + last * size_e, array + (size_a - 1) * size_e, size_e);
		sink_heap(array + (last + 1) * size_e, size_a - (last + 1), size_e, g_comp);
	}

	swap(array + (size_a - 3) * size_e, array + (size_a - 1) * size_e, size_e);

	if(g_comp(array + (size_a - 2) * size_e, array + (size_a - 1) * size_e))
		swap(array + (size_a - 2) * size_e, array + (size_a - 1) * size_e, size_e);
	*/
}
