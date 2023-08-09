/**
 * queues.h - A Single-Header Library for Generic Queues
 * author:  Isaac Allen Dowagiac, wajideus@gmail.com
 **/
#ifndef QUEUES_H
#define QUEUES_H

#include <stdlib.h>
#include <string.h>

#define QUEUE_STRUCT_HEADER \
    volatile int item_count; \
    int item_limit, next_item;

typedef struct
{
    QUEUE_STRUCT_HEADER
    /* T *items */
} _queue_t;

#define QUEUE_ITEM_LIMIT(queue)  (queue)->item_limit
#define QUEUE_ITEM_COUNT(queue)  (queue)->item_count

#define QUEUE_IS_EMPTY(queue)  ((queue)->item_count == 0)
#define QUEUE_IS_FULL(queue)   ((queue)->item_count == (queue)->item_limit)

#define create_queue(queue, item_buffer, _item_limit)  do \
{ \
    (queue)->item_limit = (_item_limit); \
    (queue)->item_count = 0; \
    (queue)->next_item = 0; \
    (queue)->items = (item_buffer); \
    if ((item_buffer) == NULL && (_item_limit) > 0) \
    { \
        int _size = sizeof(*(queue)->items) * (_item_limit); \
        (queue)->items = malloc(_size); \
        if ((queue)->items == NULL) \
            (queue)->item_limit = 0; \
    } \
} while (0)

#define destroy_queue(queue)  do \
{ \
    (queue)->item_limit = 0; \
    (queue)->item_count = 0; \
    (queue)->next_item = 0; \
    if ((queue)->items != NULL) \
        free((queue)->items); \
    (queue)->items = NULL; \
} while (0)

#define clear_queue(queue)  do \
{ \
    queue->next_item = 0; \
    queue->item_count = 0; \
} while (0)

#define set_queue_item_limit(queue, new_item_limit)  do \
{ \
    int _new_size = sizeof(*(queue)->items) * (new_item_limit); \
    int *_new_items = malloc(_new_size); \
    if (_new_items == NULL) \
        break; \
    if ((queue)->item_count > 0 && (queue)->items != NULL) \
    { \
        int _part2_item_count = (queue)->next_item \
                              + (queue)->item_count \
                              - (queue)->item_limit, \
            _part1_item_count = (queue)->item_count \
                              - _part2_item_count; \
        memcpy(_new_items, (queue)->items + (queue)->next_item, \
               _part1_item_count * sizeof(*(queue)->items)); \
        if (_part2_item_count > 0) \
        { \
            memcpy(_new_items + _part1_item_count, (queue)->items, \
                   _part2_item_count * sizeof(*(queue)->items)); \
        } \
    } \
    (queue)->item_limit = (new_item_limit); \
    (queue)->next_item = 0; \
    if ((queue)->items != NULL) \
        free((queue)->items); \
    (queue)->items = _new_items; \
} while (0)

#define jam_queue_item(queue, item)  do \
{ \
    while (QUEUE_IS_FULL(queue)) \
        continue; \
    (queue)->next_item = ((queue)->next_item - 1 + (queue)->item_limit) \
                       % (queue)->item_limit; \
    (queue)->items[(queue)->next_item] = (item); \
    (queue)->item_count++; \
} while (0)

#define push_queue_item(queue, item)  do \
{ \
    while (QUEUE_IS_FULL(queue)) \
        continue; \
    (queue)->items[(queue)->next_item + (queue)->item_count] = (item); \
    (queue)->item_count++; \
} while (0)

#define pull_queue_item(queue, item)  do \
{ \
    while (QUEUE_IS_EMPTY(queue)) \
        continue; \
    *item = (queue)->items[(queue)->next_item]; \
    (queue)->next_item = ((queue)->next_item + 1) % (queue)->item_limit; \
    (queue)->item_count--; \
} while (0)

#define jamv_queue_item(queue, item)  do \
{ \
    if (QUEUE_IS_FULL(queue)) \
        set_queue_item_limit(queue, (queue)->item_limit * 2 + 1); \
    jam_queue_item(queue, item); \
} while (0)

#define pushv_queue_item(queue, item)  do \
{ \
    if (QUEUE_IS_FULL(queue)) \
        set_queue_item_limit(queue, (queue)->item_limit * 2 + 1); \
    push_queue_item(queue, item); \
} while (0)

#endif /* ndef QUEUES_H */
