#ifndef LINKEDLIST
#define LINKEDLIST

struct list {
	struct list *prev;
	struct list *next;
	void *data;
};

struct list *init_list(void);
void append_list(struct list *ll, void *data, int size_e);
void prepend_list(struct list *ll, void *dawta, int size_e);

#endif //LINKEDLIST
