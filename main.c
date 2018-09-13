#include <stdio.h>
#include <stdlib.h>

#include "shuffle.h"

void sort(void *, int, int, int (*)(void *, void *));

int *globalArray;
int globalSize;
int flag;

int main(int argc, char **argv) {
	int size = 10;

	struct timeval start;
	struct timeval end;
  
	if(argc > 1){
		size = atoi(argv[1]);
		if(!size)
			size = 10;
	}

	int *array = shuffledArray(size);

	globalArray = array;
	globalSize = size;

	if(argv[2] != NULL)
		flag = atoi(argv[2]);

	if(flag & 1)
		printArray(array, size);

	gettimeofday(&start, NULL);
	sort(array, size, sizeof(int), &compare);
	gettimeofday(&end, NULL);

	if(flag & 1)
		printArray(array, size);

	if(flag & 2)
		printf("Time elapsed: %lf s\n", timeDifference(start, end));

	if(flag & 4)
		check_array(array, size);
  
	free(array);
	return 0;
}
