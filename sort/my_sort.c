#include <stdlib.h>

#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;


typedef struct{
	void *array;
	int h_left;
	int h_right;
	int l_left;
	int l_right;
} queue;
	      

int compare(void *a, void *b) {
	return *(int *) a > *(int *) b;
}


void copy(void *src, void *dest, int size_e) {
	int word_loops = size_e / 4;
	int byte_loops =  size_e % 4;

	for(int i = 0; i < word_loops; ++i)
		*(int *)(dest++) = *(int *)(src++);

	for(int i = 0; i < byte_loops; ++i)
		*(char *)(dest++) = *(char *)(src++);
}


void init_queue(void *array, queue *qq, int size_e, int (*compare)(void *, void *)) {
	if(compare(array, array + size_e)) {
		copy(array,          qq->array + qq->h_left * size_e,  size_e);
		copy(array + size_e, qq->array + qq->l_right * size_e, size_e);
	} else {
		copy(array + size_e, qq->array + qq->h_left * size_e,  size_e);
		copy(array,          qq->array + qq->l_right * size_e, size_e);
	}
}


int append_queue(queue *qq, void *value, int size_a, int size_e) {
	int out = 0;
	if(compare(qq->array + qq->l_left * size_e, value)) {
		copy(value, qq->array + --qq->l_left * size_e, size_e);
		out = 1;
	} else if(compare(value, qq->array + qq->h_right * size_e)){
		copy(value, qq->array + ++qq->h_right * size_e, size_e);
		out = 2;
	}

	return out;
}


void merge_queue(void *array, queue *qq, int size_a, int size_e, int (*compare)(void *, void *)) {
	int left_max = size_a - qq->l_left;
	int head[2] = {qq->l_left, qq->l_right};

	int src = 0;
	for(int i = 0; i < left_max; ++i) {
		if(head[1] >= size_a) {
			src = head[0]++;
		} else if(head[0] >= qq->l_left) {
			src = head[1]++;
		} else {
			src = head[compare(qq->array + head[0] * size_e, qq->array + head[1] * size_e)]++;
		}

		copy(qq->array + src * size_e, array + i * size_e, size_e);
	}
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	queue *qq = calloc(1, sizeof(queue));
	qq->array = malloc(size_a * size_e);
	qq->l_left = size_a - 1;
	qq->l_right = size_a - 1;
	
	int flag = 0;

	init_queue(array, qq, size_e, compare);
	printArray(qq->array, size_a);

	for(int i = 2; i < size_a; ++i) {
		printf("\n%d\n", i);
		int out = append_queue(qq, array + i * size_e, size_a, size_e);
		printf("%d\n", out);
		if(!out) {
			//init queue again?
			if(!flag) {
				qq->h_left = ++qq->h_right;
				qq->l_right = --qq->l_left;
				init_queue(array + i * size_e, qq, size_e, compare);
				flag = 1;
			} else {
				merge_queue(array, qq, size_a, size_e, compare);
				qq->l_left = size_a - 1;
				qq->l_right = size_a - 1;

				qq->h_left = 0;
				qq->h_right = 0;
				
				flag = 0;
			}
		}
		printArray(qq->array, size_a);
	}
}
