#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <shuffle.h>

typedef struct {
	void *array;
	int (*compare)(void *, void *);
	int size_a;
	int size_e;
} data;

void copy(void *src, void *dest, int size_e) {
	int word_loops = size_e / 4;
	int byte_loops =  size_e % 4;

	for(int i = 0; i < word_loops; ++i)
		*(int *)(dest++) = *(int *)(src++);

	for(int i = 0; i < byte_loops; ++i)
		*(char *)(dest++) = *(char *)(src++);
}


void merge(void *array, int size, int size2, int size_e, int (*compare)(void *, void *)) {
	int iter = size + size2;
	void *combinedArray = malloc(size_e * iter);
	int head[2] = {0, size};

	for(int i = 0; i < iter; ++i) {
                if(head[1] >= iter){
			copy((array + (size_e * head[0]++)), (combinedArray + size_e * i), size_e);
		} else if(head[0] >= size) {
			copy((array + (size_e * head[1]++)), (combinedArray + size_e * i), size_e);
		} else {
			copy((array + (size_e * head[compare((array + size_e * head[0]), (array + size_e * head[1]))]++)), (combinedArray + size_e * i), size_e);
		}
	}
	for(int j = 0; j < iter; ++j)
		copy((combinedArray + size_e * j), (array + size_e * j), size_e);

	free(combinedArray);
}

void sort_point(void *arg) {
	void *array = (*(data *) arg).array;
	int (*compare)(void *, void *) = (*(data *) arg).compare;
	int size_a = (*(data *) arg).size_a;
	int size_e = (*(data *) arg).size_e;
	int newSize = size_a / 2;
	int newSize2 = size_a - newSize;

	if(size_a > 1) {
		data left = {array, compare, newSize, size_e};
		data right = {array + size_e * newSize, compare, newSize2, size_e};

		sort_point((void *) &left);
		sort_point((void *) &right);

		merge(array, newSize, newSize2, size_e, compare);
	}


}

void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int count = 2;

	int part = size_a / count;
	/*
	pthread_t t1;
	pthread_t t2;

	data data_struct1 = {array, part};
	data data_struct2 = {array + part, part};

	pthread_create(&t1, NULL, (void * (*) (void *)) &sort_point, (void *) &data_struct1);
	pthread_create(&t2, NULL, (void * (*) (void *)) &sort_point, (void *) &data_struct2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	merge(array, part, part);
	*/

	pthread_t *t = malloc(sizeof(*t) * count);

	int i = 0;
	data *data_struct = malloc(sizeof(*data_struct) * count);
	for(; i < count - 1; ++i) {
		data_struct[i].array = array + (i * part);
		data_struct[i].compare = compare;
		data_struct[i].size_a = part;
		data_struct[i].size_e = size_e;
		pthread_create(t + i, NULL, (void * (*) (void *)) &sort_point, (void *) (data_struct + i));
	}

	data_struct[i].array = array + (i * part);
	data_struct[i].size_a = size_a - (i * part);
	pthread_create(t + i, NULL, (void * (*) (void *)) &sort_point, (void *) (data_struct + i));

	int j = 0;
	for(; j < count - 1; ++j) {
		pthread_join(*(t + j), NULL);
	}

	int k = 0;
	for(; k < count - 1; ++k) {
		merge(array, part * (k + 1), part, size_e, compare);
	}
	merge(array, (count - 1) * part, size_a - ((count - 1) * part), size_e, compare);

	free(t);
	free(data_struct);

}
