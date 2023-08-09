/**
 * stacks.h - A Single-Header Library for Generic Stacks
 * author:  Isaac Allen Dowagiac, wajideus@gmail.com
 **/
#ifndef STACKS_H
#define STACKS_H

#include <stdlib.h>

#define STACK_STRUCT_HEADER  int maximum_depth, depth;

typedef struct
{
    STACK_STRUCT_HEADER
    /* T *items; */
} _stack_t;

#define MAXIMUM_STACK_DEPTH(stack)  (stack)->maximum_depth
#define STACK_DEPTH(stack)          (stack)->depth

#define TOP_STACK_ITEM(stack)  TOP_STACK_ITEM_OR(stack, *(stack)->items)

#define TOP_STACK_ITEM_OR(stack, other_item) \
    ((stack)->depth > 0 ? (stack)->items[(stack)->depth - 1] : other_item)

#define create_stack(stack, item_buffer, _maximum_depth)  do \
{ \
    (stack)->maximum_depth = (_maximum_depth); \
    (stack)->depth = 0; \
    (stack)->items = item_buffer; \
    if ((item_buffer) == NULL && (_maximum_depth) > 0) \
    { \
        int _size = sizeof(*(stack)->items) * (_maximum_depth); \
        (stack)->items = malloc(_size); \
        if ((stack)->items == NULL) \
            (stack)->maximum_depth = 0; \
    } \
} while (0)

#define destroy_stack(stack)  do \
{ \
    (stack)->maximum_depth = 0; \
    (stack)->depth = 0; \
    if ((stack)->items != NULL) \
        free((stack)->items); \
    (stack)->items = NULL; \
} while (0)

#define clear_stack(stack)  do \
{ \
    (stack)->depth = 0; \
} while (0)

#define set_maximum_stack_depth(stack, new_maximum_depth)  do \
{ \
    int _new_size = sizeof(*(stack)->items) * (new_maximum_depth); \
    void *_new_items = realloc((stack)->items, _new_size); \
    if (_new_items == NULL) \
        break; \
    (stack)->maximum_depth = (new_maximum_depth); \
    if ((stack)->depth > (new_maximum_depth)) \
        (stack)->depth = (new_maximum_depth); \
    (stack)->items = _new_items; \
} while (0)

#define push_stack_item(stack, item)  do \
{ \
    if ((stack)->depth < (stack)->maximum_depth) \
    { \
        (stack)->items[(stack)->depth] = (item); \
        (stack)->depth++; \
    } \
} while (0)

#define pop_stack_item(stack, itemp) do \
{ \
    if ((stack)->depth > 0) \
    { \
        (stack)->depth--; \
        *itemp = (stack)->items[(stack)->depth]; \
    } \
} while (0)

#define pushv_stack_item(stack, item)  do \
{ \
    if ((stack)->depth == (stack)->maximum_depth) \
        set_maximum_stack_depth((stack), (stack)->maximum_depth * 2 + 1); \
    push_stack_item((stack), item); \
} while (0)

#endif /* ndef STACKS_H */
