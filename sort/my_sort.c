#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;

void copy(void *src, void *dest, int size_e) {
	int word_loops = size_e / 4;
	int byte_loops =  size_e % 4;

	for(int i = 0; i < word_loops; ++i)
		*(int *)(dest++) = *(int *)(src++);

	for(int i = 0; i < byte_loops; ++i)
		*(char *)(dest++) = *(char *)(src++);
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	void *scratch = malloc(size_a * size_e);

	int start_index = 0;

	int left_break = 0;
	int right_break = 0;

	if(compare(array + size_e, array + 2 * size_e)) {
		copy(array, scratch, size_e);
		copy(array + 2 * size_e, scratch + (size_a - 1) * size_e);
	} else {
		copy(array + 2 * size_e, scratch, size_e); 
		copy(array + size_e, scratch + (size_a - 1) * size_e);
	}

	int left_index = size_a - 1;
	int right_index = 0;

	for(int a = 0; a < 2; ++a) {
		for(int i = start_index; i < size_a; ++i) {
			if(compare(scratch + left_index * size_e, array + i * size_e, size_e)) {
				--left_index;
				copy(array + i * size_e, scratch + left_index * size_e, size_e);
			} else if(array + i * size_e, compare(array + right_index * size_e)){
				++right_index;

				copy(array + i * size_e, scratch + right_index * size_e, size_e);
			} else {
				if(!a) {
					left_break = left_index;
					right_break = right_index;
					start_index = i;
					break;
				} else {
					
				}
			}
		}
	}

	for(int j = start_index; j < size_a; ++j) {
		if(compare(scratch + left_index * size_e, array + i * size_e, size_e)) {
			--left_index;
			copy(array + i * size_e, scratch + left_index * size_e, size_e);
		} else if(compare(array + right_index * size_e, array + i * size_e)){
			++right_index;
			copy(array + i * size_e, scratch + right_index * size_e, size_e);
		} else {
			int left_left = left_index;
			int right_left = left_break;
			for(int k = left_left, l = right_left, m = 0;
			    (k < right_left) && (l < size_a - 1);
			    ) {
				if((l < size_a - 1) && compare(scratch + k * size_e, scratch + l * size_e, size_e)) {
					copy(scratch + l * size_e, array + m * size_e, size_e);
					++l;
				} else if(k < right_left){
					copy(scratch + k * size_e, array + m * size_e, size_e);
					++k
				}
			}
			/*
			for(int j = left_index; j < size_a; ++j, ++copy_index) {
				copy(scratch + j * size_e, array + copy_index * size_e, size_e);
			}

			for(int k = 0; k <= right_index; ++k) {
				copy(scratch + k * size_e, array + copy_index * size_e, size_e);
			}
			*/
		}
	}
}
