#include "shuffle.h"
#include "swap.h"


//bubblesort
void sort(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	for(int flag = 0; flag;) {
		flag = 0;
		for(int i = 0; i < (size_a - 1); ++i) {
			if(compare(array + i * size_e, array + (i + 1) * size_e)) {
				swap(array + i * size_e, array + (i + 1) * size_e, size_e);
				flag = 1;
			}
		}
	}
}
