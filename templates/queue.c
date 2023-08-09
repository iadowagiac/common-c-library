/**
 * queue.c - Queue Template - Intended to be copied and modified.
 * author:  Isaac Allen Dowagiac, wajideus@gmail.com
 **/
#include <stdlib.h>
#include <string.h>

typedef struct
{
    volatile int item_count;
    int item_limit,
        next_item;
    int *items;
} queue_t;

#define QUEUE_ITEM_LIMIT(queue)  (queue)->item_limit
#define QUEUE_ITEM_COUNT(queue)  (queue)->item_count

#define QUEUE_IS_EMPTY(queue)  ((queue)->item_count == 0)
#define QUEUE_IS_FULL(queue)   ((queue)->item_count == (queue)->item_limit)

void
create_queue(queue_t *queue, int *item_buffer, int item_limit)
{
    queue->item_limit = item_limit;
    queue->item_count = 0;
    queue->next_item = 0;
    queue->items = item_buffer;
    if (item_buffer == NULL && item_limit > 0)
    {
        int size = sizeof(*queue->items) * item_limit;
        queue->items = malloc(size);
        if (queue->items == NULL)
            queue->item_limit = 0;
    }
}

void
destroy_queue(queue_t *queue)
{
    queue->item_limit = 0;
    queue->item_count = 0;
    queue->next_item = 0;
    if (queue->items != NULL)
        free(queue->items);
    queue->items = NULL;
}

void
clear_queue(queue_t *queue)
{
    queue->next_item = 0;
    queue->item_count = 0;
}

void
set_queue_item_limit(queue_t *queue, int new_item_limit)
{
    int new_size = sizeof(*queue->items) * new_item_limit;
    int *new_items = malloc(new_size);
    if (new_items == NULL)
        return;
    if (queue->item_count > 0)
    {
        int part2_item_count = queue->next_item
                             + queue->item_count
                             - queue->item_limit,
            part1_item_count = queue->item_count
                             - part2_item_count;
        memcpy(new_items, queue->items + queue->next_item,
               part1_item_count * sizeof(*queue->items));
        if (part2_item_count > 0)
        {
            memcpy(new_items + part1_item_count, queue->items,
                   part2_item_count * sizeof(*queue->items));
        }
    }
    queue->item_limit = new_item_limit;
    queue->next_item = 0;
    if (queue->items != NULL)
        free(queue->items);
    queue->items = new_items;
}

void
jam_queue_item(queue_t *queue, int item)
{
    while (QUEUE_IS_FULL(queue))
        continue;
    queue->next_item = (queue->next_item - 1 + queue->item_limit)
                     % queue->item_limit;
    queue->items[queue->next_item] = item;
    queue->item_count++;
}

void
push_queue_item(queue_t *queue, int item)
{
    while (QUEUE_IS_FULL(queue))
        continue;
    queue->items[queue->next_item + queue->item_count] = item;
    queue->item_count++;
}

void
pull_queue_item(queue_t *queue, int *item)
{
    while (QUEUE_IS_EMPTY(queue))
        continue;
    *item = queue->items[queue->next_item];
    queue->next_item = (queue->next_item + 1) % queue->item_limit;
    queue->item_count--;
}

void
jamv_queue_item(queue_t *queue, int item)
{
    if (QUEUE_IS_FULL(queue))
        set_queue_item_limit(queue, queue->item_limit * 2 + 1);
    jam_queue_item(queue, item);
}

void
pushv_queue_item(queue_t *queue, int item)
{
    if (QUEUE_IS_FULL(queue))
        set_queue_item_limit(queue, queue->item_limit * 2 + 1);
    push_queue_item(queue, item);
}
