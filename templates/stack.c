/**
 * stack.c - Stack Template - Intended to be copied and modified.
 * author:  Isaac Allen Dowagiac, wajideus@gmail.com
 **/
#include <stdlib.h>

typedef struct
{
    int maximum_depth,
        depth;
    int *items;
} stack_t;

#define MAXIMUM_STACK_DEPTH(stack)  (stack)->maximum_depth
#define STACK_DEPTH(stack)          (stack)->depth

#define TOP_STACK_ITEM(stack)  TOP_STACK_ITEM_OR(stack, *(stack)->items)

#define TOP_STACK_ITEM_OR(stack, other_item) \
    ((stack)->depth > 0 ? (stack)->items[(stack)->depth - 1] : other_item)

#define new_stack()  ((stack_t) { 0, 0, NULL })

void
create_stack(stack_t *stack, int *item_buffer, int maximum_depth)
{
    stack->maximum_depth = maximum_depth;
    stack->depth = 0;
    stack->items = item_buffer;
    if (item_buffer == NULL && maximum_depth > 0)
    {
        int size = sizeof(*stack->items) * maximum_depth;
        stack->items = malloc(size);
        if (stack->items == NULL)
            stack->maximum_depth = 0;
    }
}

void
destroy_stack(stack_t *stack)
{
    stack->maximum_depth = 0;
    stack->depth = 0;
    if (stack->items != NULL)
        free(stack->items);
    stack->items = NULL;
}

void
clear_stack(stack_t *stack)
{
    stack->depth = 0;
}

void
set_maximum_stack_depth(stack_t *stack, int new_maximum_depth)
{
    int new_size = sizeof(*stack->items) * new_maximum_depth;
    void *new_items = realloc(stack->items, new_size);
    if (new_items == NULL)
        return;
    stack->maximum_depth = new_maximum_depth;
    if (stack->depth > new_maximum_depth)
        stack->depth = new_maximum_depth;
    stack->items = new_items;
}

void
push_stack_item(stack_t *stack, int item)
{
    if (stack->depth == stack->maximum_depth)
        return;
    stack->items[stack->depth] = item;
    stack->depth++;
}

void
pop_stack_item(stack_t *stack, int *item)
{
    if (stack->depth <= 0)
        return;
    stack->depth--;
    *item = stack->items[stack->depth];
}

void
pushv_stack_item(stack_t *stack, int item)
{
    if (stack->depth == stack->maximum_depth)
        set_maximum_stack_depth(stack, stack->maximum_depth * 2 + 1);
    push_stack_item(stack, item);
}
