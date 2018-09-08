#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "shuffle.h"

int *shuffledArray(int size) {
	//seed rand();
	struct timeval t2;
	gettimeofday(&t2, NULL);
	srand((unsigned) t2.tv_usec);

	
	//make array and populate
	int *array = malloc(sizeof(*array) * size);
	for(int i = 0; i < size; i++)
		array[i] = i;

	//shuffle array
	int temp;
	size_t j;
	for(int i = 0; i < (size - 1); i++) {
		j = i + rand() / (RAND_MAX / (size - i) + 1);
		temp = array[j];
		array[j] = array[i];
		array[i] = temp;
	}

	return array;
}


void printArray(int *array, int size) {
	for(int i = 0; i < size; i++)
		printf("%d ", array[i]);

	printf("\n");
}


void copyArray(void *src, void *dest, int size_a, int size_e) {
	char *c_src = src;
	char *c_dest = dest;
	for(int i = 0; i < size_a; ++i)
		for(int j = 0 ; j < size_e; ++j)
			*(c_dest++) = *(c_src++);
}


double timeDifference(struct timeval start, struct timeval end) {
	return ((double)end.tv_usec - (double)start.tv_usec)/1000000 + ((double)end.tv_sec - (double)start.tv_sec);
}


void check_array(int *array, int size) {
	for(int i = 1; i < size; ++i) {
		if(array[i] != (array[i - 1] + 1)) {
			printf("Sorted incorrectly.\n");
			break;
		}
	}
}

int compare(void *a, void *b) {
	return *(int *) a > *(int *) b;
}
