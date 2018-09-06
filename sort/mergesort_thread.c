#ifndef MERGESORT_THREAD
#define MERGESORT_THREAD

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <shuffle.h>

typedef struct {
	int *array;
	int size;
} data;

void merge(int *array, int size, int size2) {
	int iter = size + size2;
	int *combinedArray = malloc(sizeof(*combinedArray) * iter);
	int head[2] = {0, size};


	for(int i = 0; i < iter; ++i) {
		if(head[1] >= iter){
			combinedArray[i] = array[head[0]++];
		} else if(head[0] >= size) {
			combinedArray[i] = array[head[1]++];
		} else {
			combinedArray[i] = array[head[array[head[0]] > array[head[1]]]++];
		}
	}
	copyArray(array, combinedArray, iter);
	free(combinedArray);
}

void sort_point(void *arg) {
	int *array = (*(data *) arg).array;
	int size = (*(data *) arg).size;

	int newSize = size / 2;
	int newSize2 = size - newSize;

	if(size > 1) {
		data left = {array, newSize};
		data right = {array + newSize, newSize2};

		sort_point((void *) &left);
		sort_point((void *) &right);

		merge(array, newSize, newSize2);
	}


}

void sort(int *array, int size) {
	int count = 2;

	int part = size / count;

	pthread_t *t = malloc(sizeof(*t) * count);

	int i = 0;
	data *data_struct = malloc(sizeof(*data_struct) * count);
	for(; i < count - 1; ++i) {
		data_struct[i].array = array + (i * part);
		data_struct[i].size = part;
		pthread_create(t + i, NULL, (void * (*) (void *)) &sort_point, (void *) (data_struct + i));
	}

	data_struct[i].array = array + (i * part);
	data_struct[i].size = size - (i * part);
	pthread_create(t + i, NULL, (void * (*) (void *)) &sort_point, (void *) (data_struct + i));

	int j = 0;
	for(; j < count - 1; ++j) {
		pthread_join(*(t + j), NULL);
	}
	int k = 0;
	for(; k < count - 1; ++k) {
		merge(array + (k * part), part, part);
	}
	merge(array + (k * part), k * part, size - (k * part));

	free(t);
	free(data_struct);
}


#endif //MERGESORT_THREAD
