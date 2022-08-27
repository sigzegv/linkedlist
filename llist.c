#include "llist.h"

list_item_t*
list_item_new(void* data) {
    list_item_t* i = malloc(sizeof(list_item_t));
    i->data = data;
    return i;
}

/**
 * Dynamically search for first element from any list member
 */
list_item_t*
list_first(list_item_t* member) {
    if (NULL == member) {
        return NULL;
    }

    list_item_t* current = member;

    while(NULL != current->prev) {
        current = current->prev;

        // Avoid infinite rotation if list is cyclic
        if (current == member) {
            return member;
        }
    }

    return current;
}

/**
 * Dynamically search for last element from any list member
 */
list_item_t*
list_last(list_item_t* member) {
    if (NULL == member) {
        return NULL;
    }

    list_item_t* current = member;

    while(NULL != current->next) {
        current = current->next;

        // Avoid infinite rotation if list is cyclic
        if (current == member) {
            return member;
        }
    }

    return current;
}

list_item_t*
list_insert(list_item_t* member, list_item_t* elem) {
    if (NULL == elem) {
        return NULL;
    }

    if (NULL != member) {
        elem->prev = member->prev;
        elem->next = member;
        member->prev = elem;

        if (NULL != elem->prev->next) {
            elem->prev->next = elem;
        }
    }

    return elem;
}

list_item_t*
list_append(list_item_t* member, list_item_t* elem) {
    if (NULL == elem) {
        return NULL;
    }

    // look for last elem in member's list
    if (NULL != member) {
        member = list_last(member);
        member->next = elem;
    }

    elem->prev = member;

    return elem;
}

list_item_t*
list_prepend(list_item_t* member, list_item_t* elem) {
    return list_insert(list_first(member), elem);
}

/**
 * Removes a list_item from its current list.
 * This list_item can be reused.
 */
void
list_unlist(list_item_t* elem) {
    if (NULL == elem) {
        return;
    }

    if (NULL != elem->next) {
        elem->next->prev = elem->prev;
    }

    if (NULL != elem->prev) {
        elem->prev->next = elem->next;
    }

    elem->prev = NULL;
    elem->next = NULL;
}

/**
 * Completely removes a list_item from its list, and returns its data field.
 */
void*
list_delete(list_item_t* elem) {
    list_unlist(elem);

    void* data = elem->data;
    free(elem);

    return data;
}
