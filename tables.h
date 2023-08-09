/**
 * table.h - A Single-Header Library for Generic Tables
 * author:  Isaac Allen Dowagiac, wajideus@gmail.com
 **/
#ifndef TABLES_H
#define TABLES_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_ENTRY_STRUCT_HEADER \
    short in_use; \
    int next_entry;

#define TABLE_STRUCT_HEADER \
    int (*keycmp)(/* key_t key1, key_t key2 */); \
    unsigned long (*hashof)(/* key_t key */); \
    int entry_limit, \
        entry_count, \
        entry_fixup; \

typedef struct
{
    TABLE_ENTRY_STRUCT_HEADER
    /* key_t *key; */
    /* value_t value; */
} _table_entry_t;

typedef struct
{
    TABLE_STRUCT_HEADER
    /* table_entry_t *entries; */
} _table_t;

#define TABLE_ENTRY_LIMIT(table)  (table)->entry_limit
#define TABLE_ENTRY_COUNT(table)  (table)->entry_count

// TODO
//    make this macro work
#define TABLE_HAS_ENTRY(table, key) \
    _table_has_entry(table, key, sizeof_entry, offsetof_entry_key)

#define create_table(table, entry_buffer, _entry_limit, _keycmp, _hashof) do \
{ \
    (table)->keycmp = _keycmp; \
    (table)->hashof = _hashof; \
    (table)->entry_limit = (_entry_limit); \
    (table)->entry_count = 0; \
    (table)->entry_fixup = 0; \
    (table)->entries = entry_buffer; \
    if (entry_buffer == NULL && (_entry_limit) > 0) \
    { \
        int _size = sizeof(*(table)->entries) * (_entry_limit); \
        (table)->entries = malloc(_size); \
        if ((table)->entries == NULL) \
            (table)->entry_limit = 0; \
        else for (int _i = 0; _i < (table)->entry_limit; _i++) \
            (table)->entries[_i].in_use = 0; \
    } \
} while (0)

#define destroy_table(table) do \
{ \
    (table)->entry_limit = 0; \
    (table)->entry_count = 0; \
    if ((table)->entries != NULL); \
        free((char *)(table)->entries - (table)->entry_fixup); \
    (table)->entries = NULL; \
} while (0)

#define set_table_entry_limit(table, new_entry_limit) do \
{ \
    intptr_t _new_entry_index, _old_entry_index; \
    int _new_size = sizeof(*(table)->entries) * (new_entry_limit + 1), \
        _old_entry_limit = (table)->entry_limit; \
    char *_new_entries = malloc(_new_size), \
         *_old_entries = (void *)(table)->entries; \
    if (_new_entries == NULL) \
        break; \
    _new_entry_index = ((intptr_t)_new_entries - (intptr_t)_old_entries) \
                     / sizeof(*(table)->entries) + 1; \
    _old_entry_index = -_new_entry_index; \
    (table)->entries = (table)->entries + _new_entry_index; \
    (table)->entry_limit = (new_entry_limit); \
    for (int _i = 0; _i < (new_entry_limit); _i++) \
         (table)->entries[_i].in_use = 0; \
    if ((table)->entry_count != 0) \
    { \
        (table)->entry_count = 0; \
        for (int _i = 0; _i < _old_entry_limit; _i++) \
        { \
            if ((table)->entries[_old_entry_index + _i].in_use) \
            { \
                set_table_value(table, \
                    (table)->entries[_old_entry_index + _i].key, \
                    (table)->entries[_old_entry_index + _i].value); \
             } \
        } \
    } \
    if (_old_entries != NULL) \
        free((char *)_old_entries - (table)->entry_fixup); \
    (table)->entry_fixup = (intptr_t)(table)->entries \
                         - (intptr_t)_new_entries; \
} while (0)

#define add_table_entry(table, _key) do \
{ \
    int _index, _entry_index, _first_entry_index; \
    if ((table)->entry_limit == 0) \
        break; \
    _index = (table)->hashof(_key) % (table)->entry_limit; \
    _first_entry_index = _entry_index = _index; \
    if (!(table)->entries[_entry_index].in_use) \
    { \
        (table)->entries[_entry_index].in_use = 1; \
        (table)->entries[_entry_index].next_entry = -1; \
        (table)->entries[_entry_index].key = _key; \
        (table)->entry_count++; \
        break; \
    } \
    while (1) \
    { \
        if ((table)->keycmp((table)->entries[_entry_index].key, _key) == 0) \
            break; \
        if ((table)->entries[_entry_index].next_entry == -1) \
        { \
            _index = _entry_index; \
            while ((++_index % (table)->entry_limit) != _entry_index) \
            { \
                if ((table)->entries[_index % (table)->entry_limit].in_use) \
                    continue; \
                (table)->entries[_entry_index].next_entry = \
                    _index % (table)->entry_limit; \
                _entry_index = _index % (table)->entry_limit; \
                (table)->entries[_entry_index].in_use = 1; \
                (table)->entries[_entry_index].next_entry = -1; \
                (table)->entries[_entry_index].key = \
                    (table)->entries[_first_entry_index].key; \
                (table)->entries[_first_entry_index].key = _key; \
                (table)->entry_count++; \
                break; \
            } \
            break;  /* no empty slots. oof. */ \
        } \
        _entry_index = (table)->entries[_entry_index].next_entry; \
    } \
} while (0)

#define get_table_value(table, key, _value) \
    get_table_value_or(table, key, _value, (table)->entries->value)

#define get_table_value_or(table, _key, _value, other_value) do \
{ \
    int _index, _entry_index, _first_entry_index; \
    if ((table)->entry_limit == 0) \
    { \
        *_value = (other_value); \
        break; \
    } \
    _index = (table)->hashof(_key) % (table)->entry_limit; \
    _first_entry_index = _entry_index = _index; \
    if (!(table)->entries[_entry_index].in_use) \
    { \
        *_value = (other_value); \
        break; \
    } \
    while (1) \
    { \
        if ((table)->keycmp((table)->entries[_entry_index].key, _key) == 0) \
        { \
            *_value = (table)->entries[_entry_index].value; \
            break; \
        } \
        if ((table)->entries[_entry_index].next_entry == -1) \
        { \
            *_value = (other_value); \
            break; \
        } \
        _entry_index = (table)->entries[_entry_index].next_entry; \
    } \
} while (0)

#define set_table_value(table, _key, _value) do \
{ \
    int _index, _entry_index, _first_entry_index; \
    if ((table)->entry_limit == 0) \
        break; \
    _index = (table)->hashof(_key) % (table)->entry_limit; \
    _first_entry_index = _entry_index = _index; \
    if (!(table)->entries[_entry_index].in_use) \
    { \
        (table)->entries[_entry_index].in_use = 1; \
        (table)->entries[_entry_index].next_entry = -1; \
        (table)->entries[_entry_index].key = _key; \
        (table)->entries[_entry_index].value = (_value); \
        (table)->entry_count++; \
        break; \
    } \
    while (1) \
    { \
        if ((table)->keycmp((table)->entries[_entry_index].key, _key) == 0) \
        { \
            (table)->entries[_entry_index].value = (_value); \
            break; \
        } \
        if ((table)->entries[_entry_index].next_entry == -1) \
        { \
            _index = _entry_index; \
            while ((++_index % (table)->entry_limit) != _entry_index) \
            { \
                if ((table)->entries[_index % (table)->entry_limit].in_use) \
                    continue; \
                (table)->entries[_entry_index].next_entry = \
                    _index % (table)->entry_limit; \
                _entry_index = _index % (table)->entry_limit; \
                (table)->entries[_entry_index].in_use = 1; \
                (table)->entries[_entry_index].next_entry = -1; \
                (table)->entries[_entry_index].key = \
                    (table)->entries[_first_entry_index].key; \
                (table)->entries[_entry_index].value = \
                    (table)->entries[_first_entry_index].value; \
                (table)->entries[_first_entry_index].key = _key; \
                (table)->entries[_first_entry_index].value = (_value); \
                (table)->entry_count++; \
                break; \
            } \
            break;  /* no empty slots. oof. */ \
        } \
        _entry_index = (table)->entries[_entry_index].next_entry; \
    } \
} while (0)

#define setv_table_value(table, key, value) do \
{ \
    if (0);  \
    else if ((table)->entry_count >= 0.75 * (table)->entry_limit) \
        set_table_entry_limit(table, (table)->entry_limit * 2 + 1); \
    set_table_value(table, key, value); \
} while (0)

#endif /* ndef TABLES_H */
