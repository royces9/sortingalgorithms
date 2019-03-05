#include <stdlib.h>
#include <pthread.h>

#include "shuffle.h"
#include "swap.h"

pthread_mutex_t lock;

struct thread_data {
	void *array;
	int (*compare)(void *, void *);
	int size_a;
	int size_e;
	int count;
};

#if 1
#define pthread_mutex_lock no_op
#define pthread_mutex_unlock no_op
#endif

void no_op(pthread_mutex_t *a) {
}


void sort_n(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	int left = 1;
	int right = size_a - 1;

	void *pivot = array + (right / 2) * size_e;
	void *end = array + right * size_e;

	int comp = compare(array, pivot);

	if(comp ^ compare(pivot, end)) {
		if(!(compare(array, end) ^ comp)) {
			swap(array, end, size_e);
		}
	} else {
		swap(array, pivot, size_e);

	}

	while(right > left) {
		for(; (left < right) && compare(array, array + left * size_e); ++left);
		for(; (right > left) && compare(array + right * size_e, array); --right);

		swap(array + left * size_e,
		     array + right * size_e,
		     size_e);
	}

	swap(array, array + (left - 1) * size_e, size_e);


	if((left - 1) > 2) {
		sort_n(array, left - 1, size_e, compare);
	} else if((left - 1) > 1) {
		if(compare(array, array + size_e)) {
			swap(array, array + size_e, size_e);
		}
	}

	if((size_a - left) > 2) {
		sort_n(array + left * size_e, size_a - left, size_e, compare);
	} else if((size_a - left) > 1) {
		if(compare(array + left * size_e, array + (left + 1) * size_e)) {
			swap(array + left * size_e, array + (left + 1) * size_e, size_e);
		}
	}
}

void sort_r(void *arg) {
	struct thread_data data = *(struct thread_data *) arg;

	void *array = data.array;
	int (*compare)(void *, void *) = data.compare;
	int size_a = data.size_a;
	int size_e = data.size_e;
	int count = data.count;

	int left = 1;
	int right = size_a - 1;

	void *pivot = array + (right / 2) * size_e;
	void *end = array + right * size_e;

	int comp = compare(array, pivot);

	if(comp ^ compare(pivot, end)) {
		if(!(compare(array, end) ^ comp)) {
			pthread_mutex_lock(&lock);
			swap(array, end, size_e);
			pthread_mutex_unlock(&lock);
		}
	} else {
		pthread_mutex_lock(&lock);
		swap(array, pivot, size_e);
		pthread_mutex_unlock(&lock);
	}

	while(right > left) {
		for(; (left < right) && compare(array, array + left * size_e); ++left);
		for(; (right > left) && compare(array + right * size_e, array); --right);

		pthread_mutex_lock(&lock);
		swap(array + left * size_e,
		     array + right * size_e,
		     size_e);
		pthread_mutex_unlock(&lock);
	}

	pthread_mutex_lock(&lock);
	swap(array, array + (left - 1) * size_e, size_e);
	pthread_mutex_unlock(&lock);

	pthread_t tt[2];
	char thread_f[2] = {0, 0};

	struct thread_data left_d = {array, compare, left - 1, size_e, count - 1};
	if((left - 1) > 2) {
		if(count > 0) {
			thread_f[0] = 1;
			pthread_create(tt, NULL, (void * (*) (void *))&sort_r, (void *)&left_d);
		} else {
			sort_n(array, left - 1, size_e, compare);
		}
	} else if((left - 1) > 1) {
		if(compare(array, array + size_e)) {
			pthread_mutex_lock(&lock);
			swap(array, array + size_e, size_e);
			pthread_mutex_unlock(&lock);
		}
	}

	struct thread_data right_d = {array + left * size_e, compare, size_a - left, size_e, count - 1};
	if((size_a - left) > 2) {
		if(count > 0) {
			thread_f[1] = 1;
			pthread_create(tt + 1, NULL, (void * (*)(void *))&sort_r, (void *)&right_d);
		} else {
			sort_n(array + left * size_e, size_a - left, size_e, compare);
		}
	} else if((size_a - left) > 1) {
		if(compare(array + left * size_e, array + (left + 1) * size_e)) {
			pthread_mutex_lock(&lock);
			swap(array + left * size_e, array + (left + 1) * size_e, size_e);
			pthread_mutex_unlock(&lock);
		}
	}

	for(int i = 0; i < 2; ++i) 
		if(thread_f[i])
			pthread_join(tt[i], NULL);
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *), void *extra) {
	int count = 1;
	if(extra)
		count = *(int *) extra;
	
	if(size_a != 1) {
		struct thread_data data = {array, compare, size_a, size_e, count};
		sort_r(&data);
	}
}


