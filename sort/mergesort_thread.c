#ifndef MERGESORT_THREAD
#define MERGESORT_THREAD

extern int *global;
extern int globalSize;

typedef struct {
	int *array;
	int size;
} data;

void merge(int *array, int size, int size2) {
	int iter = size+ size2;
	int *combinedArray = malloc(sizeof(*combinedArray) * iter);

	int head[2] = {0, size};

	if(size2 == 0){
		return;
	}

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
}

void sort_point(void *arg) {
}

void sort(int *array, int size) {
	int count = 2;

	int part = size / count;

	pthread_t *t = malloc(sizeof(*t) * count);
	int i = 0;
	data a = {NULL, 0};
	for(; i < count - 1; ++i) {
		a.array = array + (i * part);
		a.size = part;

		pthread_create(t + i, NULL, (void * (*) (void *)) &sort_point, (void *) a);
	}

	a.array = array + (i * count);
	pthread_create(t + count, NULL, (void * (*) (void *)) &sort_point, (void *) a)



	merge(array, newSize, newSize2);
}


#endif //MERGESORT_THREAD
