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


pthread_mutex_t print_lock;

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


void merge(void *array, void * scratch, int left_size, int right_size, int size_e, int (*compare)(void *, void *)) {
	int total_size = left_size + right_size;
	int head[2] = {0, left_size};

	for(int i = 0, src = 0; i < total_size; ++i) {
                if(head[1] >= total_size) {
			src = head[0]++;
		} else if(head[0] >= left_size) {
			src = head[1]++;
		} else {
			src = head[compare(array + size_e * head[0], array + size_e * head[1])]++;
		}

		copy(array + src * size_e, scratch + i * size_e, size_e);
	}

	for(int j = 0; j < total_size; ++j)
		copy(scratch + j * size_e, array + j * size_e, size_e);
}


void merge_all(void *array, void *scratch, int size_a, int size_e, int count, int (*compare)(void *, void *)) {
	int part = size_a / count;

        int layer = 1;
	for(int log = count - 1; log != 1; log /= 2, ++layer);

	//number of merges in layer
	int merge_count = count / 2;

	//remainder of merge_count
	int left_over = count % 2;

	for(int i = 0, size = part, offset = 0; i < layer; ++i, size <<= 1) {

		for(int j = 0; j < merge_count - 1; offset = 2 * size * ++j)
			merge(array + offset * size_e, scratch, size, size, size_e, compare);

		merge(array + offset * size_e, scratch,
		      size, left_over ? size : size_a - offset - size,
		      size_e, compare);

		int temp = (merge_count + left_over) / 2;
		left_over = (merge_count + left_over) % 2;
		merge_count = temp;
	}
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

	void *scratch = malloc(size_e * size_a);

	start_sort(array, scratch, size_a, size_e, compare);

	free(scratch);
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *), void *extra) {
	int count = 2;

	if(extra)
		count = *(int *) extra;

	int part = size_a / count;

	pthread_t *t = malloc(sizeof(*t) * count);

	int i = 0;
	data *data_struct = malloc(sizeof(*data_struct) * count);
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


	for(int j = 0; j < count; ++j) {
		pthread_join(*(t + j), NULL);
	}

	void *scratch = malloc(size_a * size_e);
	merge_all(array, scratch, size_a, size_e, count, compare);

	free(t);
	free(data_struct);
}
