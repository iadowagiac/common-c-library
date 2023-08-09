/**
 * arrays.h - A Single-Header Library for Generic Arrays
 * author:  Isaac Allen Dowagiac, wajideus@gmail.com
 **/
#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdlib.h>

#define lengthof(v)  (sizeof(v) / sizeof(*v))

#define sortvals(nvals, val, compar) \
    qsort(val, nvals, sizeof(*val), (int (*)())compar)

#define mapvals(nvals, val, fn) do \
{ \
    for (size_t _i = 0; _i < nvals; _i++) \
        val[_i] = fn(val[_i]); \
} while (0)

#define filtervals(nvals, val, fn) do \
{ \
    int _new_nvals = 0; \
    for (size_t _i = 0; _i < *(nvals); _i++) \
    { \
        if (fn(val[_i])) \
            val[_new_nvals++] = val[_i]; \
    } \
    *(nvals) = _new_nvals; \
} while (0)

#define reducevals(accum, nvals, val, fn) do \
{ \
    for (size_t _i = 0; _i < nvals; _i++) \
        fn(accum, val[_i]); \
} while (0)

#define ARRAY_STRUCT_HEADER  int capacity, length;

typedef struct
{
    ARRAY_STRUCT_HEADER
    /* T *elements; */
} _array_t;

#define ARRAYOF(p)  ((_array_t *)p)

#define ARRAY_ELEMENT(array, i)  (array)->elements[i]

#define ARRAY_CAPACITY(array)  (array)->capacity
#define ARRAY_LENGTH(array)    (array)->length

#define create_array(array, element_buffer, _capacity)  do \
{ \
    (array)->capacity = (_capacity); \
    (array)->length = 0; \
    (array)->elements = element_buffer; \
    if ((element_buffer) == NULL && (_capacity) > 0) \
    { \
        int _size = sizeof(*(array)->elements) * (_capacity); \
        (array)->elements = malloc(_size); \
        if ((array)->elements == NULL) \
            (array)->capacity = 0; \
    } \
} while (0)

#define destroy_array(array)  do \
{ \
    (array)->capacity = 0; \
    (array)->length = 0; \
    if ((array)->elements != NULL) \
        free((array)->elements); \
    (array)->elements = NULL; \
} while (0)

#define clear_array(array)  do \
{ \
    (array)->length = 0; \
} while (0)

#define set_array_capacity(array, new_capacity)  do \
{ \
    int _new_size = sizeof(*(array)->elements) * (new_capacity); \
    void *_new_elements = realloc((array)->elements, _new_size); \
    if (_new_elements == NULL) \
        break; \
    (array)->capacity = (new_capacity); \
    if ((array)->length > (new_capacity)) \
        (array)->length = (new_capacity); \
    (array)->elements = _new_elements; \
} while (0)

#define add_array_element(array, element)  do \
{ \
    if ((array)->length < (array)->capacity) \
    { \
        (array)->elements[(array)->length] = (element); \
        (array)->length++; \
    } \
} while (0)

#define addv_array_element(array, element)  do \
{ \
    if ((array)->length == (array)->capacity) \
        set_array_capacity((array), (array)->capacity * 2 + 1); \
    add_array_element(array, element); \
} while (0)

#define sort_array(array, function) \
    sortvals((array)->length, (array)->elements, function)

#define map_array(array, function) \
    mapvals((array)->length, (array)->elements, function)

#define filter_array(array, function) \
    filtervals(&(array)->length, (array)->elements, function)

#define reduce_array(accumulator, array, function) \
    reducevals(accumulator, (array)->length, (array)->elements, function)

#endif /* ndef ARRAYS_H */
