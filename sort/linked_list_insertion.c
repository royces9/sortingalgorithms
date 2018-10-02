#include <stdlib.h>

#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;

typedef struct list{
>>>>>>> be0b6872b4ab85884248b870d7735f139598cb35
	struct list *prev;
	struct list *next;
	void *data;
} list;


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

	if(flag & 8)
		printArray(globalArray, globalSize);
}


list *init_list(void) {
	//make an anchor
	list *out = malloc(sizeof(*out));
	out->prev = out;
	out->next = out;
	out->data = NULL;

	return out;
}


//insert after *ll
void append_list(list *ll, void *array, int size_e) {
	list *new = malloc(sizeof(*new));

	new->next = ll->next;
	new->prev = ll;

	ll->next->prev = new;
	ll->next = new;

	new->data = malloc(size_e);
	copy(array, new->data, size_e);
}


//insert before *ll
void prepend_list(list *ll, void *array, int size_e) {
	list *new = malloc(sizeof(*new));

	new->next = ll;
	new->prev = ll->prev;

	ll->prev->next = new;
	ll->prev = new;

	new->data = malloc(size_e);
	copy(array, new->data, size_e);
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	list *data = init_list();

	append_list(data, array, size_e);

	list *curr = data->next;

	for(int i = 1; i < size_a; ++i) {
		while(curr->data) {
			if(compare(array + i * size_e, curr->data)) {
				append_list(curr, array + i * size_e, size_e);
				break;
			} else {
				curr = curr->prev;
				if(!curr->data)
					append_list(curr, array + i * size_e, size_e);
			}
		}

		curr = data->prev;
	}

	curr = data->next;

	for(int i = 0; i < size_a; ++i) {
		copy(curr->data, array + i * size_e, size_e);

		curr = curr->next;

		free(curr->prev->data);
		free(curr->prev);
	}
	free(data);
}