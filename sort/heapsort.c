#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;

int compare(void *a, void *b) {
	return *(int *) a >= *(int *) b;
}


void swap(void *a, void *b, int size_e) {
        int word_loops = size_e / 4;
	int byte_loops = size_e % 4;

	for(int i = 0; i < word_loops; ++i) {
		int i_temp = *(int *)a;
		*(int *)a++ = *(int *)b;
		*(int *)b++ = i_temp;
	}

	for(int i = 0; i < byte_loops; ++i) {
		char c_temp  = *(char *)a;
		*(char *)a++ = *(char *)b;
		*(char *)b++ = c_temp;
	}

	if(flag & 8)
		printArray(globalArray, globalSize);
}


//heapsort
//max heap

//swim the last index in the heap
void swimHeap(void *array, int child, int size_e, int (*compare)(void *, void *)) {
	//index
	int parent = (child - 1) / 2;

	//take advantage of -0.5 cast to int goes to 0
	//if child is 0, we've reached the top of the heap
	while((compare(array + child * size_e, array + parent * size_e)) && child) {
		swap(array + child * size_e, array + parent * size_e, size_e);

		child = parent;
		parent = (child - 1) / 2;
	}
}


void sinkHeap(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int child = compare(array + 2 * size_e, array + size_e) ? 2 : 1;
	int parent = 0;

	while((child < size_a) && compare(array + child * size_e, array + parent * size_e)) {
		swap(array + child * size_e, array + parent * size_e, size_e);

		parent = child;
		int leftChild = 2 * parent + 1;
		child = leftChild + (((leftChild + 1) < size_a) && compare(array + (leftChild + 1) * size_e, array + leftChild * size_e));
	}
}


void buildHeap(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int i = 1; i < size_a; ++i)
		swimHeap(array, i, size_e, compare);
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	buildHeap(array, size_a , size_e, compare);

	for(int lastHeapIndex = size_a - 1;
	    lastHeapIndex > 2;
	    --lastHeapIndex) {
		swap(array + lastHeapIndex * size_e, array, size_e);
		sinkHeap(array, lastHeapIndex, size_e, compare);
	}

	//last two elements
	swap(array + 2 * size_e, array, size_e);
	if(compare(array, array + size_e))
		swap(array + size_e, array, size_e);
}
