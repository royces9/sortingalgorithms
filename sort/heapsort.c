#include "shuffle.h"
#include "compare.h"
#include "swap.h"


//heapsort
//max heap

//swim the last index in the heap
void swim(void *array, int child, int size_e, int (*compare)(void *, void *)) {
	//index
	int parent = (child - 1) / 2;

	//take advantage of -0.5 cast to int goes to 0
	//if child is 0, we've reached the top of the heap
	while(child && compare(array + child * size_e, array + parent * size_e)) {
		swap(array + child * size_e, array + parent * size_e, size_e);

		child = parent;
		parent = (child - 1) / 2;
	}
}


void sink(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
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


void build_heap(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int i = 1; i < size_a; ++i)
		swim(array, i, size_e, compare);
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	build_heap(array, size_a , size_e, compare);

	for(int last = size_a - 1;
	    last > 2;
	    --last) {
		swap(array + last * size_e, array, size_e);
		sink(array, last, size_e, compare);
	}

	//last two elements
	swap(array + 2 * size_e, array, size_e);
	if(compare(array, array + size_e))
		swap(array + size_e, array, size_e);
}
