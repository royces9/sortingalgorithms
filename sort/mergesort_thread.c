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


void merge(void *array, int size, int size2, int size_e, int (*compare)(void *, void *)) {
	int total_size = size + size2;
	void *combinedArray = malloc(size_e * total_size);
	int head[2] = {0, size};

	void *src = NULL;

	for(int i = 0; i < total_size; ++i) {
                if(head[1] >= total_size) {
			src = array + head[0]++ * size_e;
		} else if(head[0] >= size) {
			src = array + head[1]++ * size_e;
		} else {
			src = array + head[compare(array + size_e * head[0], array + size_e * head[1])]++ * size_e;
		}

		copy(src, combinedArray + i * size_e, size_e);
	}

	for(int j = 0; j < total_size; ++j)
		copy(combinedArray + j * size_e, array + j * size_e, size_e);

	free(combinedArray);
}


void merge_all(void *array, int size_a, int size_e, int count, int (*compare)(void *, void *)) {
	int part = size_a / count;

        int counter = 1;
	for(int log = count - 1; log != 1; log /= 2, ++counter);

	//count number of tiers of merges
	int layer = counter;

	//number of merges in layer
	int merge_count = count / 2;

	//remainder of merge_count
	int left_over = count % 2;

	int offset = 0;

	int size = part;
	int temp = 0;
	for(int i = 0; i < layer; ++i) {

		for(int j = 0; j < merge_count - 1; ++j) {
			offset = 2 * size * j;
			merge(array + offset * size_e, size, size, size_e, compare);
		}

		offset = 2 * size * (merge_count - 1);

		if(left_over) {
			merge(array + offset * size_e, size, size, size_e, compare);
		} else {
			merge(array + offset * size_e, size, size_a - offset - size, size_e, compare);
		}

		temp = (merge_count + left_over) / 2;
		left_over = (merge_count + left_over) % 2;
		merge_count = temp;

		size <<= 1;
	}
}


void sort_point(void *arg) {
	int size_a = (*(data *) arg).size_a;
	if(size_a > 1) {
		void *array = (*(data *) arg).array;
		int (*compare)(void *, void *) = (*(data *) arg).compare;
		int size_e = (*(data *) arg).size_e;
		int newSize = size_a / 2;
		int newSize2 = size_a - newSize;

		data left = {array, compare, newSize, size_e};
		data right = {array + newSize * size_e, compare, newSize2, size_e};

		sort_point((void *) &left);
		sort_point((void *) &right);

		merge(array, newSize, newSize2, size_e, compare);
	}
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
		pthread_create(t + i, NULL, (void * (*) (void *)) &sort_point, (void *) (data_struct + i));
	}

	data_struct[i].array = array + (i * part) * size_e;
	data_struct[i].compare = compare;
	data_struct[i].size_a = size_a - (i * part);
	data_struct[i].size_e = size_e;
	pthread_create(t + i, NULL, (void * (*) (void *)) &sort_point, (void *) (data_struct + i));


	for(int j = 0; j < count; ++j) {
		pthread_join(*(t + j), NULL);
	}

	merge_all(array, size_a, size_e, count, compare);

	free(t);
	free(data_struct);
}
