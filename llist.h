#ifndef LLIST_H
#define LLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _list_item {
    struct _list_item* next;
    struct _list_item* prev;
    void* data;
} list_item_t;

list_item_t* list_item_new(void*);
list_item_t* list_first(list_item_t*);
list_item_t* list_last(list_item_t*);
list_item_t* list_insert(list_item_t*, list_item_t*);
list_item_t* list_append(list_item_t*, list_item_t*);
list_item_t* list_prepend(list_item_t*, list_item_t*);
void list_unlist(list_item_t*);
void* list_free(list_item_t*);

#endif
