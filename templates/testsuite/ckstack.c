#include <check.h>

#include "../stack.c"

START_TEST(can_create_preallocated_stack)
{
    stack_t stack;
    int items[10];

    create_stack(&stack, items, 10);

    ck_assert_int_eq(MAXIMUM_STACK_DEPTH(&stack), 10);
    ck_assert_int_eq(STACK_DEPTH(&stack), 0);
    ck_assert_ptr_eq(stack.items, items);
}
END_TEST

START_TEST(can_create_stack)
{
    stack_t stack;

    create_stack(&stack, NULL, 10);

    ck_assert_int_eq(MAXIMUM_STACK_DEPTH(&stack), 10);
    ck_assert_int_eq(STACK_DEPTH(&stack), 0);
    ck_assert_ptr_ne(stack.items, NULL);

    destroy_stack(&stack);

    ck_assert_int_eq(MAXIMUM_STACK_DEPTH(&stack), 0);
    ck_assert_int_eq(STACK_DEPTH(&stack), 0);
    ck_assert_ptr_eq(stack.items, NULL);
}
END_TEST

START_TEST(can_push_static_stack_items)
{
    stack_t stack;
    int item1, item2, item3, item4 = -1;

    create_stack(&stack, NULL, 3);

    push_stack_item(&stack, 1);
    push_stack_item(&stack, 3);
    push_stack_item(&stack, 5);
    push_stack_item(&stack, 7);

    ck_assert_int_eq(STACK_DEPTH(&stack), 3);

    ck_assert_int_eq(TOP_STACK_ITEM(&stack), 5);

    pop_stack_item(&stack, &item1);
    pop_stack_item(&stack, &item2);
    pop_stack_item(&stack, &item3);
    pop_stack_item(&stack, &item4);

    ck_assert_int_eq(STACK_DEPTH(&stack), 0);

    ck_assert_int_eq(item1, 5);
    ck_assert_int_eq(item2, 3);
    ck_assert_int_eq(item3, 1);
    ck_assert_int_eq(item4, -1);

    destroy_stack(&stack);
}
END_TEST


START_TEST(can_push_dynamic_stack_items)
{
    stack_t stack;
    int item1, item2, item3, item4 = -1;

    create_stack(&stack, NULL, 0);

    pushv_stack_item(&stack, 1);
    pushv_stack_item(&stack, 3);
    pushv_stack_item(&stack, 5);
    pushv_stack_item(&stack, 7);

    ck_assert_int_eq(STACK_DEPTH(&stack), 4);

    ck_assert_int_eq(TOP_STACK_ITEM(&stack), 7);

    pop_stack_item(&stack, &item1);
    pop_stack_item(&stack, &item2);
    pop_stack_item(&stack, &item3);
    pop_stack_item(&stack, &item4);

    ck_assert_int_eq(STACK_DEPTH(&stack), 0);

    ck_assert_int_eq(item1, 7);
    ck_assert_int_eq(item2, 5);
    ck_assert_int_eq(item3, 3);
    ck_assert_int_eq(item4, 1);

    destroy_stack(&stack);
}
END_TEST

TCase *
create_tcase_for_stacks(void)
{
    TCase *tcase = tcase_create("Stacks");
    tcase_add_test(tcase, can_create_preallocated_stack);
    tcase_add_test(tcase, can_create_stack);
    tcase_add_test(tcase, can_push_static_stack_items);
    tcase_add_test(tcase, can_push_dynamic_stack_items);
    return tcase;
}
