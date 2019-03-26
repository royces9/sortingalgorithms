#include "heap.h"
#include "swap.h"

void swim_heap(char *array, int child, int size_e, int (*compare)(void *, void *)) {
	//index
	int parent = (child - 1) / 2;

	while(child && compare(array + child * size_e, array + parent * size_e)) {
		swap(array + child * size_e, array + parent * size_e, size_e);

		child = parent;
		parent = (child - 1) / 2;
	}
}


void sink_heap(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int child = compare(array + 2 * size_e, array + size_e) ? 2 : 1;
	int parent = 0;

	while((child < size_a) && compare(array + child * size_e, array + parent * size_e)) {
		swap(array + child * size_e, array + parent * size_e, size_e);

		parent = child;
		child = 2 * (parent + 1);

		if((child < size_a) && compare(array + (child - 1) * size_e, array + child * size_e))
			--child;
	}
}


void build_heap(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int i = 1; i < size_a; ++i)
		swim_heap(array, i, size_e, compare);
}

