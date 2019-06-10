#include <stdlib.h>

void sort(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	qsort(array, size_a, size_e, compare);
}
