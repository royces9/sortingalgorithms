#include <stdlib.h>

void copy(void *src, void *dest, int size_e) {
        int word_loops = size_e / 4;
	int byte_loops =  size_e % 4;

	for(int i = 0; i < word_loops; ++i)
		*(int *)(dest++) = *(int *)(src++);

	for(int i = 0; i < byte_loops; ++i)
		*(char *)(dest++) = *(char *)(src++);
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
}

void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
        int leftCount = 0;
	int rightCount = size_a - 1;

	char *a = array;

	void *pivot = compare(a, (a + size_e * (size_a / 2))) ? a : (a + size_e * (size_a / 2));
	void *pivot2 = compare(a, (a + size_e * (size_a - 1))) ? a : (a + size_e * (size_a - 1));
	pivot = compare(pivot, pivot2) ? pivot2 : pivot;

	pivot2 = malloc(size_e);
	copy(pivot, pivot2, size_e);

	for(int i = 0; i < size_a; ++i) {
		for(;leftCount < size_a; ++leftCount)
			if(compare((a + size_e * leftCount), pivot2))
				break;

		for(;rightCount >= 0; --rightCount)
			if(compare(pivot2, (a + size_e * rightCount)))
				break;

		swap((a + size_e * (leftCount)),
		     (a + size_e * (rightCount)),
		     size_e);
	}
	free(pivot2);

	if(rightCount != 1)
		sort(a, rightCount, size_e, compare);
	if((size_a - rightCount) != 1)
 		sort(a + size_e * leftCount, size_a - rightCount, size_e, compare);
}
