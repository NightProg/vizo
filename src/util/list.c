#include <vizo/util/lists.h>

list_t *list_new(void) {
    list_t *list = malloc(sizeof(list_t));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void list_free(list_t *list) {
    if (list == NULL) {
        return;
    }

    list_node_t *current = list->head;
    while (current != NULL) {
        list_node_t *next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

void list_add(list_t *list, void *data) {
    if (list == NULL) {
        return;
    }

    list_node_t *node = malloc(sizeof(list_node_t));
    if (node == NULL) {
        return;
    }

    node->data = data;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;
}

void list_remove(list_t *list, void *data) {
    if (list == NULL) {
        return;
    }

    list_node_t *current = list->head;
    list_node_t *previous = NULL;

    while (current != NULL) {
        if (current->data == data) {
            if (previous == NULL) {
                list->head = current->next;
            } else {
                previous->next = current->next;
            }

            if (current == list->tail) {
                list->tail = previous;
            }

            free(current);
            list->size--;

            return;
        }

        previous = current;
        current = current->next;
    }
}

void list_remove_at(list_t *list, int index) {
    if (list == NULL || index < 0 || index >= list->size) {
        return;
    }

    list_node_t *current = list->head;
    list_node_t *previous = NULL;

    for (int i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        list->head = current->next;
    } else {
        previous->next = current->next;
    }

    if (current == list->tail) {
        list->tail = previous;
    }

    free(current);
    list->size--;
}

void *list_get(list_t *list, int index) {
    if (list == NULL || index < 0 || index >= list->size) {
        return NULL;
    }

    list_node_t *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

int list_index_of(list_t *list, void *data) {
    if (list == NULL) {
        return -1;
    }

    list_node_t *current = list->head;
    int index = 0;
    while (current != NULL) {
        if (current->data == data) {
            return index;
        }

        current = current->next;
        index++;
    }

    return -1;
}

int list_size(list_t *list) {
    if (list == NULL) {
        return -1;
    }

    return list->size;
}

void list_foreach(list_t *list, void (*callback)(void *data)) {
    if (list == NULL || callback == NULL) {
        return;
    }

    list_node_t *current = list->head;
    while (current != NULL) {
        callback(current->data);
        current = current->next;
    }
}