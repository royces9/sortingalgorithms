#include <stdlib.h>
#include <pthread.h>

#include "shuffle.h"
#include "copy.h"

pthread_mutex_t print_lock;

struct thread_data {
	void *array;
	int (*compare)(void *, void *);
	int size_a;
	int size_e;
};


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


void merge_all(void *array, void *scratch, int size_a, int size_e, int count, int (*compare)(void *, void *)) {
	int part = size_a / count;

	//number of merges in layer
	int merge_count = count / 2;

	//remainder of merge_count
	int left_over = count % 2;

	for(int size = part, offset = 0; size < size_a; size <<= 1) {
		for(int j = 0; j < merge_count - 1; offset = 2 * size * ++j) {
			merge(array + offset * size_e, scratch, size, size, size_e, compare);
			offset = 2 * size * j;
		}

		offset = 2 * size * (merge_count - 1);
		merge(array + offset * size_e, scratch, size,
		      left_over ? size : size_a - offset - size,
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
	void *array = (*(struct thread_data *) arg).array;
        int (*compare)(void *, void *) = (*(struct thread_data *) arg).compare;
	int size_a = (*(struct thread_data *) arg).size_a;
	int size_e = (*(struct thread_data *) arg).size_e;

	void *scratch = malloc(size_a * size_e);

	start_sort(array, scratch, size_a, size_e, compare);

	free(scratch);

	/*
	struct thread_data _d = *(struct thread_data *)arg;
	void *scratch = malloc(_d.size_a * _d.size_e);

	start_sort(_d.array, scratch, _d.size_a, _d.size_e, _d.compare);

	free(scratch);
	*/
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *), void *extra) {
	int count = 2;

	if(extra)
		count = *(int *) extra;

	int part = size_a / count;

	pthread_t *t = malloc(count * sizeof(*t));
	struct thread_data *_d = malloc(count * sizeof(*_d));
	
	int i = 0;
	for(; i < count - 1; ++i) {
		_d[i].array = array + (i * part) * size_e;
		_d[i].compare = compare;
		_d[i].size_a = part;
		_d[i].size_e = size_e;
		pthread_create(t + i, NULL, (void * (*) (void *)) &init_sort_thread, (void *) (_d + i));
	}

	_d[i].array = array + (i * part) * size_e;
	_d[i].compare = compare;
	_d[i].size_a = size_a - (i * part);
	_d[i].size_e = size_e;
	pthread_create(t + i, NULL, (void * (*) (void *)) &init_sort_thread, (void *) (_d + i));


	for(int j = 0; j < count; ++j)
		pthread_join(*(t + j), NULL);

	free(t);
	free(_d);
	
	void *scratch = malloc(size_a * size_e);
	merge_all(array, scratch, size_a, size_e, count, compare);

	free(scratch);
}
