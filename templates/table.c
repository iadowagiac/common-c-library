#include <stdlib.h>
#include <string.h>

typedef struct
{
    short in_use;
    int next_entry;
    const char *key;
    int value;
} table_entry_t;

typedef struct
{
    int (*keycmp)(/* key_t key1, key_t key2 */);
    unsigned long (*hashof)(/* key_t key */);
    int entry_limit,
        entry_count;
    table_entry_t *entries;
} table_t;

#define TABLE_ENTRY_LIMIT(table)  (table)->entry_limit
#define TABLE_ENTRY_COUNT(table)  (table)->entry_count

#define get_table_value(table, key, _value) \
    get_table_value_or(table, key, _value, (table)->entries->value)

void
create_table(table_t *table, table_entry_t *entry_buffer, int entry_limit,
             int (*keycmp)(/* key_t key1, key_t key2 */), 
             unsigned long hashof(/* key_t key */))
{
    table->keycmp = keycmp;
    table->hashof = hashof;
    table->entry_limit = entry_limit;
    table->entry_count = 0;
    table->entries = entry_buffer;
    if (entry_buffer == NULL && entry_limit > 0)
    {
        int size = sizeof(*table->entries) * entry_limit;
        table->entries = malloc(size);
        if (table->entries == NULL)
            table->entry_limit = 0;
        else for (int i = 0; i < table->entry_limit; i++)
            table->entries[i].in_use = 0;
    }
}

void
destroy_table(table_t *table)
{
    table->entry_limit = 0;
    table->entry_count = 0;
    if (table->entries != NULL);
        free(table->entries);
    table->entries = NULL;
}

void set_table_value(table_t *table, const char *key, int value);

void
set_table_entry_limit(table_t *table, int new_entry_limit)
{
    int new_size = sizeof(*table->entries) * new_entry_limit,
        old_entry_limit = table->entry_limit;
    table_entry_t *old_entries = table->entries,
                  *new_entries = malloc(new_size);
    if (new_entries == NULL)
        return;
    for (int i = 0; i < new_entry_limit; i++)
         new_entries[i].in_use = 0;
    table->entries = new_entries;
    table->entry_limit = new_entry_limit;
    if (table->entry_count != 0)
    {
        table->entry_count = 0;
        for (int i = 0; i < old_entry_limit; i++)
        {
            if (old_entries[i].in_use)
            {
                set_table_value(table, old_entries[i].key,
                                old_entries[i].value);
            }
        }
    }
    free(old_entries);
}

void
add_table_entry(table_t *table, const char *key)
{
    table_entry_t *entry, *first_entry;
    int index;
    if (table->entry_limit == 0)
        return;
    index = table->hashof(key) % table->entry_limit;
    first_entry = entry = table->entries + index;
    if (!entry->in_use)
    {
        entry->in_use = 1;
        entry->next_entry = -1;
        entry->key = key;
        table->entry_count++;
        return;
    }
    while (1)
    {
        if (table->keycmp(entry->key, key) == 0)
            return;
        if (entry->next_entry == -1)
        {
            index = entry - table->entries;
            while ((++index % table->entry_limit) != entry - table->entries)
            {
                if (table->entries[index % table->entry_limit].in_use)
                    continue;
                entry->next_entry = index % table->entry_limit;
                entry = table->entries + index % table->entry_limit;
                entry->in_use = 1;
                entry->next_entry = -1;
                entry->key = first_entry->key;
                first_entry->key = key;
                table->entry_count++;
                return;
            }
            return;  // no empty slots. oof.
        }
        entry = table->entries + entry->next_entry;
    }
}

void
get_table_value_or(table_t *table,
                   const char *key, int *value, int other_value)
{
    table_entry_t *entry, *first_entry;
    int index;
    if (table->entry_limit == 0)
    {
        *value = other_value;
        return;
    }
    index = table->hashof(key) % table->entry_limit;
    first_entry = entry = table->entries + index;
    if (!entry->in_use)
    {
        *value = other_value;
        return;
    }
    while (1)
    {
        if (table->keycmp(entry->key, key) == 0)
        {
            *value = entry->value;
            return;
        }
        if (entry->next_entry == -1)
        {
            *value = other_value;
            return;
        }
        entry = table->entries + entry->next_entry;
    }
}

void
set_table_value(table_t *table, const char *key, int value)
{
    table_entry_t *entry, *first_entry;
    int index;
    if (table->entry_limit == 0)
        return;
    index = table->hashof(key) % table->entry_limit;
    first_entry = entry = table->entries + index;
    if (!entry->in_use)
    {
        entry->in_use = 1;
        entry->next_entry = -1;
        entry->key = key;
        entry->value = value;
        table->entry_count++;
        return;
    }
    while (1)
    {
        if (table->keycmp(entry->key, key) == 0)
        {
            entry->value = value;
            return;
        }
        if (entry->next_entry == -1)
        {
            index = entry - table->entries;
            while ((++index % table->entry_limit) != entry - table->entries)
            {
                if (table->entries[index % table->entry_limit].in_use)
                    continue;
                entry->next_entry = index % table->entry_limit;
                entry = table->entries + index % table->entry_limit;
                entry->in_use = 1;
                entry->next_entry = -1;
                entry->key = first_entry->key;
                entry->value = first_entry->value;
                first_entry->key = key;
                first_entry->value = value;
                table->entry_count++;
                return;
            }
            return;  // no empty slots. oof.
        }
        entry = table->entries + entry->next_entry;
    }
}

void
setv_table_value(table_t *table, const char *key, int value)
{
void test_static_tables(void);
    if (0);
    else if (table->entry_count >= 0.75 * table->entry_limit)
        set_table_entry_limit(table, table->entry_limit * 2 + 1);
    set_table_value(table, key, value);
}

