/*
    Static Dispatch Table for built-in functions.
*/
#ifndef D_TABLE_STATIC_H
#define D_TABLE_STATIC_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "stack.h"

#define HASH 5381
#define EMPTY_KEY SIZE_MAX

typedef void (*VoidFunc)(IntStack*);
typedef bool (*BoolFunc)(IntStack*);

typedef struct {
    size_t *keys;
    VoidFunc *values;

    size_t capacity; // capacity
    size_t length; // length
} SD_Table;


size_t hash_string(char *key);

SD_Table* new_sd_table(size_t capacity);
void free_sd_table(SD_Table *table);
bool insert_item_sd_table(SD_Table *table, char *key, VoidFunc item);
bool get_item_sd_table(SD_Table *table, char *key, VoidFunc *return_item);
void print_sd_table_keys(SD_Table *table);

#endif