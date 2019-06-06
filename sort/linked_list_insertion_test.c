#include <stdlib.h>

#include "copy.h"
#include "linked_list.h"
#include "shuffle.h"


void sort(char *array, int size_a, int size_e, int (*compare)(void *, void *)) {
	struct list *data = init_list();

	append_list(data, array, size_e);

	struct list *curr = data->next;

	for(int i = 1; i < size_a; ++i) {
		while(curr->data && (compare(curr->data, array + i * size_e) > 0))
			curr = curr->prev;

		append_list(curr, array + i * size_e, size_e);

		curr = data->prev;
	}

	curr = data->next;

	char *scratch = malloc(size_a * size_e);

	for(int i = 0; i < size_a; ++i) {
		copy(curr->data, scratch + i * size_e, size_e);

		curr = curr->next;
		free(curr->prev);
	}

	for(int i = 0; i < size_a; ++i)
		copy(scratch + i * size_e, array + i * size_e, size_e);

	free(data);
}
