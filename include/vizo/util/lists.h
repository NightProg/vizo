#ifndef VIZO_LISTS_H
#define VIZO_LISTS_H

#include <stdlib.h>

typedef struct list_node {
    void *data;
    struct list_node *next;
} list_node_t;

typedef struct list {
    list_node_t *head;
    list_node_t *tail;
    int size;
} list_t;

list_t *list_new(void);

void list_free(list_t *list);

void list_add(list_t *list, void *data);

void list_remove(list_t *list, void *data);

void list_remove_at(list_t *list, int index);

void *list_get(list_t *list, int index);

int list_index_of(list_t *list, void *data);

int list_size(list_t *list);

void list_foreach(list_t *list, void (*callback)(void *data));

#endif //VIZO_LISTS_H
