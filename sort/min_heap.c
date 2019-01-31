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
	int leftChild = size_a - 2;

	int child = leftChild - ((leftChild > 0) && compare(array + leftChild * size_e, array + (leftChild  - 1) * size_e));
	int parent = size_a - 1;

	while((leftChild >= 0) && compare(array + parent * size_e, array + child * size_e)) {
		swap(array + parent * size_e, array + child * size_e, size_e);

		parent = child;
		leftChild = 2 * parent - size_a;
		child = leftChild - ((leftChild > 0) && (compare(array + leftChild * size_e, array + (leftChild - 1) * size_e)));
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
