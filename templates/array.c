/**
 * array.c - Array Template - Intended to be copied and modified.
 * author:  Isaac Allen Dowagiac, wajideus@gmail.com
 **/
#include <stdlib.h>
#define lengthof(v)  (sizeof(v) / sizeof(*v))

// test

typedef struct
{
    int capacity,
        length;
    int *elements;
} array_t;

#define ARRAY_ELEMENT(array, i)  (array)->elements[i]

#define ARRAY_CAPACITY(array)  (array)->capacity
#define ARRAY_LENGTH(array)    (array)->length

void
mapvals(int nvals, int *val, int (*fn)(int val))
{
    for (size_t i = 0; i < nvals; i++)
        val[i] = fn(val[i]);
}

void
filtervals(int nvals, int *val, int (*fn)(int val))
{
    int new_nvals = 0;
    for (size_t i = 0; i < nvals; i++)
    {
        if (fn(val[i]))
            val[new_nvals++] = val[i];
    }
    nvals = new_nvals;
}

void
reducevals(int *accum, int nvals, int *val, void (*fn)(int *accum, int val))
{
    for (size_t i = 0; i < nvals; i++)
        fn(accum, val[i]);
}

void
create_array(array_t *array, int *element_buffer, int capacity)
{
    array->capacity = capacity;
    array->length = 0;
    array->elements = element_buffer;
    if (element_buffer == NULL && capacity > 0)
    {
        int size = sizeof(*array->elements) * capacity;
        array->elements = malloc(size);
        if (array->elements == NULL)
            array->capacity = 0;
    }
}

void
destroy_array(array_t *array)
{
    array->capacity = 0;
    array->length = 0;
    if (array->elements != NULL)
        free(array->elements);
    array->elements = NULL;
}

void
clear_array(array_t *array)
{
    array->length = 0;
}

void
set_array_capacity(array_t *array, int new_capacity)
{
    int new_size = sizeof(*array->elements) * new_capacity;
    int *new_elements = realloc(array->elements, new_size);
    if (new_elements == NULL)
        return;
    array->capacity = new_capacity;
    if (array->length > new_capacity)
        array->length = new_capacity;
    array->elements = new_elements;
}

void
add_array_element(array_t *array, int element)
{
    if (array->length == array->capacity)
        return;
    array->elements[array->length] = element;
    array->length++;
}

void
addv_array_element(array_t *array, int element)
{
    if (array->length == array->capacity)
        set_array_capacity(array, array->capacity * 2 + 1);
    add_array_element(array, element);
}
