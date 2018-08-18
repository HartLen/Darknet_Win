#ifndef LIST_H
#define LIST_H
#include "darknet.h"

linked_list *make_list();
int list_find(linked_list *l, void *val);

void list_insert(linked_list *, void *);


void free_list_contents(linked_list *l);

#endif
