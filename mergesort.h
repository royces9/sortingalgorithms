#ifndef MERGESORT
#define MERGESORT

#include <math.h>
#include <string.h>

//#include "file.h"

extern int *global;
extern int globalSize;

//mergesort
void merge(int *array, int size, int size2){
	int iter = size + size2;
	int *combinedArray = malloc(sizeof(*combinedArray) * iter);;
	int headOne = 0;
	int headTwo = size;

	if(size2) {
		for(int i = 0; i < iter; ++i){
			if(headTwo >= iter){
				combinedArray[i] = array[headOne++];
			}
			else if(headOne >= size){
				combinedArray[i] = array[headTwo++];
			}
			else if(array[headOne] > array[headTwo]){
				combinedArray[i] = array[headTwo++];
			}
			else{
				combinedArray[i] = array[headOne++];
			}
		}
		copyArray(array, combinedArray, iter);
	}
	free(combinedArray);
	//sendToFile(global, globalSize, "mergeSortData");
	//printArray(global, globalSize);
}

void sort(int *array, int size){
	int newSize = floor(size/2), newSize2 = size - newSize;
	if(size > 1){
		sort(array, newSize);
		sort(array+newSize, newSize2);
	}

	merge(array, newSize, newSize2);
}

#endif //MERGESORT
