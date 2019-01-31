#include <stdlib.h>
#include <pthread.h>

#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;


int compare(void *a, void *b) {
	return *(int *) a > *(int *) b;
}


typedef struct {
	void *array;
	int (*compare)(void *, void *);
	int size_a;
	int size_e;
} data;


struct heap_data {
	void *array;
	void *end;
};


pthread_mutex_t print_lock;


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

	if(flag & 8) {
		pthread_mutex_lock(&print_lock);
		printArray(globalArray, globalSize);
		pthread_mutex_unlock(&print_lock);
	}
}


void swim_heap(struct heap_data *heap, int child, int (*compare)(void *, void *)) {
	int parent = (child - 1) / 2;

	while(!compare(heap[child].array, heap[parent].array) && child) {
		swap(heap + child, heap + parent, sizeof(*heap));

		child = parent;
		parent = (child - 1) / 2;
	}
}


void sink_heap(struct heap_data *heap, int size_a, int (*compare)(void *, void *)) {
	int child = compare(heap[2].array, heap[1].array) ? 2 : 1;
	int parent = 0;

	while((child < size_a) && compare(heap[child].array, heap[parent].array)) {
		swap(heap + child, heap + parent, sizeof(*heap));

		parent = child;
		int leftChild = 2 * parent + 1;
		child = leftChild + (((leftChild + 1) < size_a) && (compare(heap[leftChild + 1].array, heap[leftChild].array)));
	}
}


void build_heap(struct heap_data *heap, int size_a, int (*compare)(void *, void *)) {
	for(int i = 1; i < size_a; ++i)
		swim_heap(heap, i, compare);
}


void merge_all(void *array, void *scratch,
	       int size_a, int size_e,
	       int part, int count,
	       int (*compare)(void *, void *)) {

	struct heap_data *heap = malloc(count * sizeof(*heap));

	int i = 0;
	for(; i < (count - 1); ++i) {
		heap[i].array = array + (i * part) * size_e;
		heap[i].end =  array + ((i + 1) * part) * size_e;
	}

	heap[i].array = array + (i * part) * size_e;
	heap[i].end = array + size_a * size_e;

	build_heap(heap, count, compare);

	for(int a = 0; a < count; ++a) {
		int b = 0;
		for(void *start = heap[a].array; start < heap[a].end; start += size_e, ++b) {
			printf("%d ", ((int *)heap[a].array)[b]);
		}
	}
	printf("\n");

	for(int j = 0; j < size_a; ++j) {
		copy(heap->array, scratch + j * size_e, size_e);
		heap->array += size_e;

		if(heap->array == heap->end) {
			swap(heap, heap + (count - 1), sizeof(*heap));
			--count;
		}
		sink_heap(heap, count, compare);
	}

	for(int k = 0; k < size_a; ++k)
		copy(scratch + k * size_e, array + k * size_e, size_e);
}


void merge(void *array, void * scratch, int left_size, int right_size, int size_e, int (*compare)(void *, void *)) {
	int total_size = left_size + right_size;
	int head[2] = {0, left_size};

        int i = 0;
	for(; (head[1] < total_size) && (head[0] < left_size); ++i) {
		int index = compare(array + head[0] * size_e, array + head[1] * size_e);
		int src = head[index]++;
		copy(array + src * size_e, scratch + i * size_e, size_e);
	}

	if(head[0] < left_size) {
		for(; i < total_size; ++i)
			copy(array + (head[0]++) * size_e, scratch + i * size_e, size_e);
	}

	for(int j = 0; j < i; ++j)
		copy(scratch + j * size_e, array + j * size_e, size_e);
}


void start_sort(void *array, void *scratch, int size_a, int size_e, int (*compare)(void *, void *)) {
	int left_size = size_a / 2;
	int right_size = size_a - left_size;

	if(left_size > 1)
		start_sort(array, scratch, left_size, size_e, compare);

	if(right_size > 1)
		start_sort(array + left_size * size_e, scratch, right_size, size_e, compare);

	merge(array, scratch, left_size, right_size, size_e, compare);
}


void init_sort_thread(void *arg) {
	void *array = (*(data *) arg).array;
	int (*compare)(void *, void *) = (*(data *) arg).compare;
	int size_a = (*(data *) arg).size_a;
	int size_e = (*(data *) arg).size_e;

	void *scratch = malloc(size_a * size_e);

	start_sort(array, scratch, size_a, size_e, compare);

	free(scratch);
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *), void *extra) {
	int count = 2;

	if(extra)
		count = *(int *) extra;

	int part = size_a / count;

	pthread_t *t = malloc(count * sizeof(*t));

	int i = 0;
	data *data_struct = malloc(count * sizeof(*data_struct));
	for(; i < count - 1; ++i) {
		data_struct[i].array = array + (i * part) * size_e;
		data_struct[i].compare = compare;
		data_struct[i].size_a = part;
		data_struct[i].size_e = size_e;
		pthread_create(t + i, NULL, (void * (*) (void *)) &init_sort_thread, (void *) (data_struct + i));
	}

	data_struct[i].array = array + (i * part) * size_e;
	data_struct[i].compare = compare;
	data_struct[i].size_a = size_a - (i * part);
	data_struct[i].size_e = size_e;
	pthread_create(t + i, NULL, (void * (*) (void *)) &init_sort_thread, (void *) (data_struct + i));


	for(int j = 0; j < count; ++j)
		pthread_join(*(t + j), NULL);

	void *scratch = malloc(size_a * size_e);
	merge_all(array, scratch, size_a, size_e, part, count, compare);

	free(t);
	free(data_struct);
	free(scratch);
}
