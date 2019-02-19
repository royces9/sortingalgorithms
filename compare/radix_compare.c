#include <stdint.h>
#include "radix_compare.h"

int radix_compare(void *a, void *b) {
	return *(uint64_t *)a & *(uint64_t *)b;
}
