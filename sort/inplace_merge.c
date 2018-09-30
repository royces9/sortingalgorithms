#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;

int compare(void *a, void *b) {
	return *(int *) a > *(int *) b;
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

void copy(void *src, void *dest, int size_e) {
        int word_loops = size_e / 4;
	int byte_loops =  size_e % 4;

	for(int i = 0; i < word_loops; ++i)
		*(int *)(dest++) = *(int *)(src++);

	for(int i = 0; i < byte_loops; ++i)
		*(char *)(dest++) = *(char *)(src++);
}


//mergesort
//inplace merge
void merge(void *array, int l_size, int r_size, int size_e, int (*compare)(void *, void *)) {
	//left_left - left list, left bound
	//left_right - left list, right bound
	//right_left - right list, left bound
	//right_right - right list, right bound

	for(int size_total = l_size + r_size, left_left = 0, left_right = l_size, right_left = l_size, right_right = size_total;
	    left_left < (size_total - 1);
	    ++left_left, --right_right) {

		if(left_left == right_left)
			++right_left;

		if(right_right == left_right)
			--left_right;

		//beginning of each sub array
		if(compare(array + left_left * size_e, array + right_left * size_e)) {
			swap(array + left_left * size_e, array + right_left * size_e, size_e);

			//beginning of the right sub array
			for(int j = right_left;
			    (j < right_right - 1) && compare(array + j * size_e, array + (j + 1) * size_e);
			    ++j) {
				swap(array + j * size_e, array + (j + 1) * size_e, size_e);
			}
		}

		//end of each sub array
		if(compare(array + (left_right - 1) * size_e, array + (right_right - 1) * size_e)) {
			swap(array + (left_right - 1) * size_e, array + (right_right - 1) * size_e, size_e);

			//end of the first sub array
			for(int j = left_right - 1;
			    (j > left_left) && compare(array + (j - 1) * size_e, array + j * size_e);
			    --j) {
				swap(array + (j - 1) * size_e, array + j * size_e, size_e);
			}
		}
	}
}


//bottom up
void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	if(size_a > 1) {
		int newSize = size_a / 2;
		int newSize2 = size_a - newSize;

		sort(array, newSize, size_e, compare);
		sort(array + newSize * size_e, newSize2, size_e, compare);
		merge(array, newSize, newSize2, size_e, compare);
	}
}
