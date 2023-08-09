#include <check.h>

#include "../queue.c"

START_TEST(can_create_preallocated_queue)
{
    queue_t queue;
    int items[10];

    create_queue(&queue, items, 10);

    ck_assert_int_eq(QUEUE_ITEM_LIMIT(&queue), 10);
    ck_assert_int_eq(QUEUE_ITEM_COUNT(&queue), 0);
    ck_assert_ptr_eq(queue.items, items);
}
END_TEST

START_TEST(can_create_queue)
{
    queue_t queue;

    create_queue(&queue, NULL, 10);

    ck_assert_int_eq(QUEUE_ITEM_LIMIT(&queue), 10);
    ck_assert_int_eq(QUEUE_ITEM_COUNT(&queue), 0);
    ck_assert_ptr_ne(queue.items, NULL);

    destroy_queue(&queue);

    ck_assert_int_eq(QUEUE_ITEM_LIMIT(&queue), 0);
    ck_assert_int_eq(QUEUE_ITEM_COUNT(&queue), 0);
    ck_assert_ptr_eq(queue.items, NULL);
}
END_TEST

START_TEST(can_push_static_queue_items)
{
    queue_t queue;
    int item1, item2, item3, item4 = -1;

    create_queue(&queue, NULL, 3);

    push_queue_item(&queue, 1);
    push_queue_item(&queue, 3);
    push_queue_item(&queue, 5);
//  push_queue_item(&queue, 7);  // this triggers a spinlock

    ck_assert_int_eq(QUEUE_ITEM_COUNT(&queue), 3);
    ck_assert_int_eq(QUEUE_IS_FULL(&queue), 1);

    pull_queue_item(&queue, &item1);
    pull_queue_item(&queue, &item2);
    pull_queue_item(&queue, &item3);
//  pull_queue_item(&queue, &item4);  // this triggers a spinlock

    ck_assert_int_eq(QUEUE_ITEM_COUNT(&queue), 0);
    ck_assert_int_eq(QUEUE_IS_EMPTY(&queue), 1);

    ck_assert_int_eq(item1, 1);
    ck_assert_int_eq(item2, 3);
    ck_assert_int_eq(item3, 5);
    ck_assert_int_eq(item4, -1);

    destroy_queue(&queue);
}
END_TEST

START_TEST(can_push_dynamic_queue_items)
{
    queue_t queue;
    int item1, item2, item3, item4 = -1;

    create_queue(&queue, NULL, 0);

    pushv_queue_item(&queue, 1);
    pushv_queue_item(&queue, 3);
    pushv_queue_item(&queue, 5);
    pushv_queue_item(&queue, 7);

    ck_assert_int_eq(QUEUE_ITEM_COUNT(&queue), 4);

    pull_queue_item(&queue, &item1);
    pull_queue_item(&queue, &item2);
    pull_queue_item(&queue, &item3);
    pull_queue_item(&queue, &item4);

    ck_assert_int_eq(QUEUE_ITEM_COUNT(&queue), 0);
    ck_assert_int_eq(QUEUE_IS_EMPTY(&queue), 1);

    ck_assert_int_eq(item1, 1);
    ck_assert_int_eq(item2, 3);
    ck_assert_int_eq(item3, 5);
    ck_assert_int_eq(item4, 7);

    destroy_queue(&queue);
}
END_TEST

TCase *
create_tcase_for_queues(void)
{
    TCase *tcase = tcase_create("Queues");
    tcase_add_test(tcase, can_create_preallocated_queue);
    tcase_add_test(tcase, can_create_queue);
    tcase_add_test(tcase, can_push_static_queue_items);
    tcase_add_test(tcase, can_push_dynamic_queue_items);
    return tcase;
}
