#include "shuffle.h"

extern int *globalArray;
extern int globalSize;
extern int flag;

typedef struct{
	struct list *prev;
	struct list *next;
	void *data;
} list;

int compare(void *a, void *b) {
	return *(int *) a > *(int *) b;
}

void swap(void *a, void *b, int size_e) {
	int word_loops = size_e / 4;
	int byte_loops = size_e % 4;

	for(int i = 0; i < word_loops; ++i) {
		int i_temp = *(int *)a;
		*(int *)a++ = *(int *)b;
		*(int *)b++ = i_temp;
	}

	for(int i = 0; i < byte_loops; ++i) {
		char c_temp  = *(char *)a;
		*(char *)a++ = *(char *)b;
		*(char *)b++ = c_temp;
	}

	if(flag & 8)
		printArray(globalArray, globalSize);
}





list *init_list(void) {
	//make an anchor
	list *out = malloc(sizeof(*out));
	out->prev = out;
	out->next = out;
	data = NULL;

	return out;
}


//insert after *ll
void append_list(list *ll, void *array) {
	list *new = malloc(sizeof(*new));
	new->prev = ll;
	new->next = ll->next;

	ll->next = new;
	new->next->prev = new;

	new->data = array;
}


//insert before *ll
void prepend_list(list *ll, void *array) {
	list *new = malloc(sizeof(*new));
	new->next = ll;
	new->prev = ll->prev;

	ll->prev = new;
	new->prev->next = new;

	new->data = array;
}


list *binary_search() {
}


void sort(void *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	list *data = init_list();



	if(compare(array, array + size_e)) {
		append_list(data, array);
		append_list(data, array + size_e);
	} else {
		append_list(data, array + size_e);
		append_list(data, array);
	}

	list *middle = data->next;

	for(int i = 2; i < size_a; ++i) {

	}

	for(int i = 1; i < size_a; ++i) {

		for(int j = i; j > 0; --j) {
			if(compare(array + (j - 1) * size_e, array + j * size_e)) {
				swap((array + (j - 1) * size_e), (array + j * size_e), size_e);
			} else {
				break;
			}
		}
	}
}
