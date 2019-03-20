#include <stdlib.h>

#include "linked_list.h"

struct list *init_list(void) {
	//make an anchor
	struct list *out = malloc(sizeof(*out));
	out->prev = out;
	out->next = out;
	out->data = NULL;

	return out;
}


//insert after *ll
void append_list(struct list *ll, void *data, int size_e) {
	struct list *new = malloc(sizeof(*new));

	new->next = ll->next;
	new->prev = ll;

	ll->next->prev = new;
	ll->next = new;

	new->data = data;
}


//insert before *ll
void prepend_list(struct list *ll, void *data, int size_e) {
	struct list *new = malloc(sizeof(*new));

	new->next = ll;
	new->prev = ll->prev;

	ll->prev->next = new;
	ll->prev = new;

	new->data = data;
}
