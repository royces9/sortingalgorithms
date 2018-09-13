#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;

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

	while(child > 0) {
		if(compare(array + child * size_e, array + parent * size_e)) {
			swap(array + child * size_e, array + parent * size_e, size_e);

			child = parent;
			parent = (child - 1) / 2;
		} else {
			break;
		}
	}
}

//size is 0-indexed
void sinkHeap(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int child = 0;
	int parent = 0;
	int leftChild = 1;
	int rightChild = 2;

	while(rightChild <= size_a + 1) {

		//check that rightChild is less than maximum size, that short circuits, if it is
		//check whether left or right child is bigger
		child = leftChild + ((rightChild <= size_a) && (compare(array + size_e * rightChild, array + size_e * leftChild)));

		if(compare(array + size_e * child, array + size_e * parent)) {
			swap(array + size_e * child, array + size_e * parent, size_e);

			parent = child;
		} else {
			break;
		}
    
		leftChild = 2 * parent + 1;
		rightChild = leftChild + 1; 
	}
}

void buildHeap(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int i = 0; i < size_a; ++i) {
		swimHeap(array, i, size_e, compare);
	}
}

void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	buildHeap(array, size_a, size_e, compare);

	int lastHeapIndex = size_a - 1;

	for(int i = size_a - 1; i >= 0; --i) {
		swap(array + (lastHeapIndex--) * size_e, array, size_e);
		sinkHeap(array, lastHeapIndex, size_e, compare);
	}
}
