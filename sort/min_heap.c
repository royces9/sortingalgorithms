#include "shuffle.h"

#include "swap.h"


//heapsort
//min heap

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

void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	buildHeap(array, size_a, size_e, compare);

	for(int lastHeapIndex = 0;
	    lastHeapIndex < (size_a - 3);
	    ++lastHeapIndex) {

		swap(array + lastHeapIndex * size_e, array + (size_a - 1) * size_e, size_e);
		sinkHeap(array + (lastHeapIndex + 1) * size_e, size_a - (lastHeapIndex + 1), size_e, compare);
	}

	swap(array + (size_a - 3) * size_e, array + (size_a - 1) * size_e, size_e);
	if(compare(array + (size_a - 2) * size_e, array + (size_a - 1) * size_e))
		swap(array + (size_a - 2) * size_e, array + (size_a - 1) * size_e, size_e);
}
