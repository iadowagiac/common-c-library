#include <stdio.h>
#include <check.h>

#include "../array.c"

START_TEST(can_create_preallocated_array)
{
    array_t array;
    int elements[10];

    create_array(&array, elements, 10);

    ck_assert_int_eq(ARRAY_CAPACITY(&array), 10);
    ck_assert_int_eq(ARRAY_LENGTH(&array), 0);
    ck_assert_ptr_eq(array.elements, elements);
}
END_TEST

START_TEST(can_create_array)
{
    array_t array;

    create_array(&array, NULL, 10);

    ck_assert_int_eq(ARRAY_CAPACITY(&array), 10);
    ck_assert_int_eq(ARRAY_LENGTH(&array), 0);
    ck_assert_ptr_ne(array.elements, NULL);

    destroy_array(&array);

    ck_assert_int_eq(ARRAY_CAPACITY(&array), 0);
    ck_assert_int_eq(ARRAY_LENGTH(&array), 0);
    ck_assert_ptr_eq(array.elements, NULL);
}
END_TEST

START_TEST(can_add_static_array_elements)
{
    array_t array;

    create_array(&array, NULL, 3);

    add_array_element(&array, 1);
    add_array_element(&array, 3);
    add_array_element(&array, 5);
    add_array_element(&array, 7);

    ck_assert_int_eq(ARRAY_LENGTH(&array), 3);

    ck_assert_int_eq(ARRAY_ELEMENT(&array, 0), 1);
    ck_assert_int_eq(ARRAY_ELEMENT(&array, 1), 3);
    ck_assert_int_eq(ARRAY_ELEMENT(&array, 2), 5);

    destroy_array(&array);
}
END_TEST

START_TEST(can_add_dynamic_array_elements)
{
    array_t array;

    create_array(&array, NULL, 0);

    addv_array_element(&array, 1);
    addv_array_element(&array, 3);
    addv_array_element(&array, 5);
    addv_array_element(&array, 7);

    ck_assert_int_eq(ARRAY_LENGTH(&array), 4);

    ck_assert_int_eq(ARRAY_ELEMENT(&array, 0), 1);
    ck_assert_int_eq(ARRAY_ELEMENT(&array, 1), 3);
    ck_assert_int_eq(ARRAY_ELEMENT(&array, 2), 5);

    destroy_array(&array);
}
END_TEST

TCase *
create_tcase_for_arrays(void)
{
    TCase *tcase = tcase_create("Arrays");
    tcase_add_test(tcase, can_create_preallocated_array);
    tcase_add_test(tcase, can_create_array);
    tcase_add_test(tcase, can_add_static_array_elements);
    tcase_add_test(tcase, can_add_dynamic_array_elements);
    return tcase;
}
