/**
 * list.c - Linked List Template - Intended to be copied and modified.
 * author:  Isaac Allen Dowagiac, wajideus@gmail.com
 **/
#include <stdlib.h>

typedef struct
{
    int previous, next;
    int value;
} list_item_t;

typedef struct
{
    int used_item_count,
        item_limit,
        item_count;
    int first_free,
    list_item_t *items;
} list_t;

#define LIST_ITEM_LIMIT(list)  (list)->item_limit
#define LIST_ITEM_COUNT(list)  (list)->item_count

void
create_list(list_t *list, list_item *item_buffer, int item_limit)
{
    list->used_item_count = 0;
    list->item_limit = item_limit;
    list->item_count = 0;
    list->first_free = -1;
    list->items = item_buffer;
    if (item_buffer == NULL && item_limit > 0)
    {
        int size = sizeof(*list->items) * item_limit;
        list->items = malloc(size);
        if (list->items == NULL)
            list->item_limit = 0;
    }
}

void
destroy_list(list_t *list)
{
    list->used_item_count = 0;
    list->item_limit = 0;
    list->item_count = 0;
    list->first_free = -1;
    if (list->items != NULL)
        free(list->items);
    list->items = NULL;
}

void
clear_list(list_t *list)
{
    list->used_item_count = 0;
    list->item_count = 0;
    list->first_free = -1;
}

