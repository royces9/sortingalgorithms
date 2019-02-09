#include "shuffle.h"
#include "swap.h"


//heapsort
//max heap

//swim the last index in the heap
void swimHeap(void *array, int last_index, int size_e, int (*compare)(void *, void *)) {
	int child = last_index;
	int parent = (child - size_e) / 2;
	parent -= parent % size_e;
	while((compare(array + child, array + parent)) && child) {
		swap(array + child, array + parent, size_e);

		child = parent;
		parent = (child - size_e) / 2;
		parent -= parent % size_e;
	}
}


void sinkHeap(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int child = compare(array + 2 * size_e, array + size_e) ? 2 * size_e : size_e;
	int parent = 0;

	while((child < size_a) && compare(array + child, array + parent)) {
		swap(array + child, array + parent, size_e);

		parent = child;
		int left = 2 * parent + size_e;
		int right = left + size_e;
		child = ((right < size_a) && compare(array + right, array + left)) ? right : left;
	}
}


void buildHeap(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int i = size_e; i < size_a; i += size_e)
		swimHeap(array, i, size_e, compare);
}

void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	size_a *= size_e;
	buildHeap(array, size_a, size_e, compare);

	for(int lastHeapIndex = size_a - size_e;
	    lastHeapIndex > 2 * size_e;
	    lastHeapIndex -= size_e) {
		swap(array + lastHeapIndex, array, size_e);
		sinkHeap(array, lastHeapIndex, size_e, compare);
	}

	//last two elements
	swap(array + 2 * size_e, array, size_e);
	if(compare(array, array + size_e))
		swap(array + size_e, array, size_e);
}
