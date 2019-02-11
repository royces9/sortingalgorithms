#include "compare.h"

int compare(void *a, void *b) {
	return *(int *) a > *(int *) b;
}
