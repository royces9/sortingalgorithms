#ifndef HEAP
#define HEAP

void swim_heap(void *array, int child, int size_e, int (*compare)(void *, void *));
void sink_heap(void *array, int size_a, int size_e, int (*compare)(void *, void *));
void build_heap(void *array, int size_a, int size_e, int (*compare)(void *, void *));

#endif //HEAP
