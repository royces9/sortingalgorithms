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

	int i_temp = 0;
	for(int i = 0; i < word_loops; ++i) {
		i_temp = *(int *)a;
		*(int *)a++ = *(int *)b;
		*(int *)b++ = i_temp;
	}

	char c_temp = 0;
	for(int i = 0; i < byte_loops; ++i) {
		c_temp  = *(char *)a;
		*(char *)a++ = *(char *)b;
		*(char *)b++ = c_temp;
	}

	if(flag & 8)
		printArray(globalArray, globalSize);
}


//heapsort
//max heap

//swim the last index in the heap
void swimHeap(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	//index
	int parent = (size_a - 1) / 2;
	int child = size_a;

	//take advantage of -0.5 cast to int goes to 0
	//if child is 0, we've reached the top fo the heap
	while((compare(array + child * size_e, array + parent * size_e)) && child) {
		swap(array + child * size_e, array + parent * size_e, size_e);

		child = parent;
		parent = (child - 1) / 2;
	}
}


void sinkHeap(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int leftChild = 1;

	int child = leftChild + ((leftChild < size_a) && compare(array + size_e * (leftChild + 1), array + size_e * leftChild));
	int parent = 0;

	while((leftChild <= size_a) && compare(array + size_e * child, array + size_e * parent)) {
		swap(array + size_e * child, array + size_e * parent, size_e);

		parent = child;
		leftChild = 2 * parent + 1;

		child = leftChild + ((leftChild < size_a) && (compare(array + size_e * (leftChild + 1), array + size_e * leftChild)));
	}
}


void buildHeap(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int i = 0; i < size_a; ++i)
		swimHeap(array, i, size_e, compare);
}

void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	buildHeap(array, size_a, size_e, compare);

	int lastHeapIndex = size_a - 1;

	for(int i = size_a - 1; i >= 0; --i) {
		swap(array + (lastHeapIndex--) * size_e, array, size_e);
		sinkHeap(array, lastHeapIndex, size_e, compare);
	}
}
