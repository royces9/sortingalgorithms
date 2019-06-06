#include "shuffle.h"
#include "swap.h"


void sort(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int left = 0;
	int right = size_a - 1;

	for(int flag = 1; flag && (left < right); ++left, --right) {
		flag = 0;
		for(int i = left; i < right; ++i) {
			if(compare(array + i * size_e, array + (i + 1) * size_e) > 0) {
				swap(array + i * size_e, array + (i + 1) * size_e, size_e);
				flag = 1;
			}
		}

		if(flag) {
			for(int j = right; j > left; --j) {
				if(compare(array + (j - 1) * size_e, array + j * size_e) > 0) {
					swap(array + (j - 1) * size_e, array + j * size_e, size_e);
					flag = 1;
				}
			}
		}
	}
}
