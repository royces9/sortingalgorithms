#include "int_compare.h"

int int_compare(void *a, void *b) {
	return *(int *)a > *(int *)b;
}
