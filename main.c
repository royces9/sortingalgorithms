#include <stdio.h>
#include <stdlib.h>

#include "shuffle.h"

void sort(void *, int, int, int (*)(void *, void *), void *);

int *globalArray;
int globalSize;
int flag;

int compare(void *a, void *b);

int main(int argc, char **argv) {
	int size = 10;
	int *extra = NULL;
	struct timeval start;
	struct timeval end;
  
	int *array = shuffledArray(size);

	if(argc > 1) {
		for(int i = 1; i < argc; i += 2) {
			switch(*(argv[i] + 1)) {
			case 'f':
				flag = atoi(argv[i + 1]);
				break;
				
			case 's':
				free(array);
				size = atoi(argv[i + 1]);
				array  = shuffledArray(size);
				break;

			case 'e':
				extra = malloc(sizeof(*extra));
				*extra = atoi(argv[i + 1]);
				break;

			case 'r':
				for(int k = size - 1, j = 0; k >= 0; --k, ++j)
					array[k] = j;
				
				--i;
				break;

			default:
				break;
			}
		}
	} else {
		flag = 7;
	}

	globalArray = array;
	globalSize = size;


	if(flag & 1)
		printArray(array, size);

	gettimeofday(&start, NULL);
	sort(array, size, sizeof(*array), &compare, extra);
	gettimeofday(&end, NULL);

	if(flag & 1)
		printArray(array, size);

	if(flag & 2)
		printf("Time elapsed: %lf s\n", timeDifference(start, end));

	if(flag & 4)
		check_array(array, size);
  
	free(array);
	free(extra);
	return 0;
}
