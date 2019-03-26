#include "shuffle.h"
#include "swap.h"
#include "heap.h"

//experimental thing with heap

void sort(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	build_heap(array, size_a, size_e, compare);

	for(int i = size_a - 1; i > 0; --i) {
		array += size_e;
		build_heap(array, i, size_e, compare);
	}
}
