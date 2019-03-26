#include <stdlib.h>

#include "shuffle.h"
#include "copy.h"


struct queue{
	char *array;
	int left;
	int right;
	int occ;
};


void init_queue(char *array, struct queue *qq, int size_e, int (*compare)(void *, void *)) {
	qq->occ = 1;
	if(compare(array, array + size_e)) {
		copy(array,          qq->array, size_e);
		copy(array + size_e, qq->array + qq->right * size_e, size_e);
	} else {
		copy(array + size_e, qq->array, size_e);
		copy(array,          qq->array + qq->right * size_e, size_e);
	}
}


int append_queue(struct queue *qq, void *value, int size_a, int size_e, int (*compare)(void *, void *)) {
	int out = 0;
	if(compare(value, qq->array + qq->left * size_e)) {
		copy(value, qq->array + ++qq->left * size_e, size_e);
		out = 1;
		qq->occ = 1;
	} else if(compare(qq->array + qq->right * size_e, value)){
		copy(value, qq->array + --qq->right * size_e, size_e);
		out = 2;
		qq->occ = 1;
	}

	return out;
}


void merge(char *array, int size, int size2, int size_e, int (*compare)(void *, void*)){
	int total_size = size + size2;
	char *combinedArray = malloc(size_e * total_size);

	int head[2] = {0, size};

	int src = 0;

	int copy_head = 0;
	for(int i = 0; i < total_size; ++i) {
		if(head[1] >= total_size) {
			src = head[0]++;
		} else if(head[0] >= size) {
			src = head[1]++;
		} else {
			src = head[compare(array + head[0] * size_e, array + head[1] * size_e)]++;
		}

		copy(array + src * size_e, combinedArray + i * size_e, size_e);
	}

	for(int j = copy_head; j < total_size; ++j)
		copy(combinedArray + j * size_e, array + j * size_e, size_e);

	free(combinedArray);
}


/*
 * queue elements onto a deque until elements can't be added,
 *
 * enqueue when elements are bigger than the biggest, or 
 * smaller than the smallest element
 *
 * when the next element can not be enqueued, copy elements of queue
 * into array, and start a new queue, then merge all the sorted subarrays
 *
 */
void sort(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {


	struct queue qq;
	int *stack = malloc(size_a * sizeof(*stack));
	qq.array = malloc(size_a * size_e);
	qq.left = 0;
	qq.right = size_a - 1;
	qq.occ = 0;


	/*
	struct queue qq;
	int *stack = NULL;
	qq.array = malloc(size_a * (size_e + sizeof(*stack)));

	qq.left = 0;
	qq.right = size_a - 1;
	qq.occ = 0;

	stack = qq.array + size_a * size_e;
	*/

	stack[0] = 0;
	init_queue(array, &qq, size_e, compare);

	int count = 0;
	for(int i = 2; i < size_a; ++i) {
		if(!append_queue(&qq, array + i * size_e, size_a, size_e, compare)) {
			int m = stack[count];
			stack[++count] = i;

			for(int j = qq.right; j < size_a; ++j, ++m)
				copy(qq.array + j * size_e, array + m * size_e, size_e);

			for(int k = 0; k <= qq.left; ++k, ++m)
				copy(qq.array + k * size_e, array + m * size_e, size_e);

			qq.left = 0;
			qq.right = size_a - 1;
			qq.occ = 0;

			if(i < (size_a - 1)) {
				init_queue(array + i * size_e, &qq, size_e, compare);
				++i;
			}
		}
	}

	if(qq.occ) {
		int m = stack[count];
		for(int j = qq.right; j < size_a; ++j, ++m)
			copy(qq.array + j * size_e, array + m * size_e, size_e);

		for(int k = 0; k <= qq.left; ++k, ++m)
			copy(qq.array + k * size_e, array + m * size_e, size_e);
	}
	
	stack[++count] = size_a;

	for(int merge_count = count / 2;
	    stack[1] != size_a;
	    count = (count + 1) / 2, merge_count = count / 2){

		for(int l = 0; l < merge_count; ++l) {
			merge(array + stack[2 * l] * size_e,
			      stack[2 * l + 1] - stack[2 * l],
			      stack[2 * l + 2] - stack[2 * l + 1],
			      size_e, compare);

			stack[l + 1] = stack[2 * l + 2];
		}
		stack[merge_count + (count % 2)] = size_a;
	}

	free(stack);
	free(qq.array);
}
