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
        int word_loops = (size_e * size_a) / 4;
	int byte_loops =  (size_e * size_a) % 4;

	for(int i = 0; i < word_loops; ++i) {
		*(int *)(dest++) = *(int *)(src++);
	}

	for(int i = 0; i < byte_loops; ++i)
		*(char *)(dest++) = *(char *)(src++);
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
