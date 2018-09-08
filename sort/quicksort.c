#include <stdlib.h>

#include "shuffle.h"

void copy(void *src, void *dest, int size_e) {
	char *c_src = src;
	char *c_dest = dest;
	for(int i = 0; i < size_e; ++i)
		*(c_dest++) = *(c_src++);
}

void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int leftCount = 0;
	int rightCount = size_a - 1;
	
	char *a = array;

	void *pivot = compare(a, (a + size_e * (size_a / 2))) ? a : (a  + size_e * (size_a / 2));
	void *pivot2 = compare(a, (a + size_e * (size_a - 1))) ? a : (a + size_e * (size_a - 1));
	pivot = compare(pivot, pivot2) ? pivot2 : pivot;

	int pivotPosition = 0;
	void *tempArray = malloc(size_e * size_a);

	for(int i = 0; i < size_a; ++i) {
		if(compare(pivot2, (a + size_e * i))) {
			copy((a + size_e * i), (tempArray + size_e * leftCount++), size_e);
		} else if(compare((a + size_e * i), pivot2)) {
			copy((a + size_e * i), (tempArray + size_e * rightCount--), size_e);
		} else {
			pivotPosition = i;
		}
	}
	copy((a + size_e * pivotPosition), (tempArray + size_e * rightCount), size_e);
	for(int j = 0; j < size_a; ++j)
		copy((tempArray + size_e * j), (a + size_e * j), size_e);
	free(tempArray);

	if(rightCount != 1)
		sort(a, rightCount, size_e, compare);
	if((size_a - rightCount) != 1)
		sort(a + size_e * leftCount, size_a - rightCount, size_e, compare);
}
