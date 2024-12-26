/*
    Dynamic Dispatch Table for user-defined functions
*/
#ifndef D_TABLE_DYNAMIC_H
#define D_TABLE_DYNAMIC_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "stack.h"
#include "string_array.h"

#define HASH 5381
#define EMPTY_KEY SIZE_MAX

typedef struct {
    size_t *keys;
    char **strings;
    StringArray **values;

    size_t capacity; // capacity
    size_t length; // length
} DD_Table;

DD_Table* new_dd_table(size_t capacity);
void free_dd_table(DD_Table *table);
bool insert_item_dd_table(DD_Table *table, char *key, StringArray *value);
bool get_item_dd_table(DD_Table *table, char *key, StringArray **value);
void print_dd_table_keys(DD_Table *table);
void print_dd_table_values(DD_Table *table);

#endif