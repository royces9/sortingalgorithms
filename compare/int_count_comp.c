#include "int_count_comp.h"

extern int compare_count;

int int_count_comp(void *a, void *b) {
	++compare_count;
	return *(int *)a > *(int *)b;
}
