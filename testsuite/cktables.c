#include <stdio.h>
#include <string.h>
#include <check.h>
#include <tables.h>

unsigned long
djb2hash(const char *str)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
    return hash;
}

START_TEST(can_create_preallocated_table)
{
    typedef struct
    {
        TABLE_ENTRY_STRUCT_HEADER
        const char *key;
        int value;
    } table_entry_t;
    struct
    {
        TABLE_STRUCT_HEADER
        table_entry_t *entries;
    } table;
    table_entry_t entries[10];

    create_table(&table, entries, 10, strcmp, djb2hash);

    ck_assert_int_eq(TABLE_ENTRY_LIMIT(&table), 10);
    ck_assert_int_eq(TABLE_ENTRY_COUNT(&table), 0);
    ck_assert_ptr_ne(table.entries, NULL);
    ck_assert_ptr_eq(table.keycmp, strcmp);
    ck_assert_ptr_eq(table.hashof, djb2hash);
}
END_TEST

START_TEST(can_create_table)
{
    struct
    {
        TABLE_STRUCT_HEADER
        struct
        {
            TABLE_ENTRY_STRUCT_HEADER
            const char *key;
            int value;
        } *entries;
    } table;

    create_table(&table, NULL, 10, strcmp, djb2hash);

    ck_assert_int_eq(TABLE_ENTRY_LIMIT(&table), 10);
    ck_assert_int_eq(TABLE_ENTRY_COUNT(&table), 0);
    ck_assert_ptr_ne(table.entries, NULL);
    ck_assert_ptr_eq(table.keycmp, strcmp);
    ck_assert_ptr_eq(table.hashof, djb2hash);

    destroy_table(&table);

    ck_assert_int_eq(TABLE_ENTRY_LIMIT(&table), 0);
    ck_assert_int_eq(TABLE_ENTRY_COUNT(&table), 0);
    ck_assert_ptr_eq(table.entries, NULL);
}
END_TEST

START_TEST(can_set_static_table_values)
{
    struct
    {
        TABLE_STRUCT_HEADER
        struct
        {
            TABLE_ENTRY_STRUCT_HEADER
            const char *key;
            int value;
        } *entries;
    } table;
    int item1, item2, item3, item4 = -1;

    create_table(&table, NULL, 3, strcmp, djb2hash);

    set_table_value(&table, "item1", 1);
    set_table_value(&table, "item2", 3);
    set_table_value(&table, "item3", 5);
    set_table_value(&table, "item4", 7);

    ck_assert_int_eq(TABLE_ENTRY_COUNT(&table), 3);

    get_table_value_or(&table, "item1", &item1, item1);
    get_table_value_or(&table, "item2", &item2, item2);
    get_table_value_or(&table, "item3", &item3, item3);
    get_table_value_or(&table, "item4", &item4, item4);

    ck_assert_int_eq(item1, 1);
    ck_assert_int_eq(item2, 3);
    ck_assert_int_eq(item3, 5);
    ck_assert_int_eq(item4, -1);

    destroy_table(&table);
}
END_TEST

START_TEST(can_set_dynamic_table_values)
{
    struct
    {
        TABLE_STRUCT_HEADER
        struct
        {
            TABLE_ENTRY_STRUCT_HEADER
            const char *key;
            int value;
        } *entries;
    } table;
    int item1, item2, item3, item4 = -1;

    create_table(&table, NULL, 0, strcmp, djb2hash);

    setv_table_value(&table, "item1", 1);
    setv_table_value(&table, "item2", 3);
    setv_table_value(&table, "item3", 5);
    setv_table_value(&table, "item4", 7);

    ck_assert_int_eq(TABLE_ENTRY_COUNT(&table), 4);

    get_table_value_or(&table, "item1", &item1, item1);
    get_table_value_or(&table, "item2", &item2, item2);
    get_table_value_or(&table, "item3", &item3, item3);
    get_table_value_or(&table, "item4", &item4, item4);

    ck_assert_int_eq(item1, 1);
    ck_assert_int_eq(item2, 3);
    ck_assert_int_eq(item3, 5);
    ck_assert_int_eq(item4, 7);

    destroy_table(&table);
}
END_TEST

TCase *
create_tcase_for_tables(void)
{
    TCase *tcase = tcase_create("Tables");
    tcase_add_test(tcase, can_create_preallocated_table);
    tcase_add_test(tcase, can_create_table);
    tcase_add_test(tcase, can_set_static_table_values);
    tcase_add_test(tcase, can_set_dynamic_table_values);
    return tcase;
}
