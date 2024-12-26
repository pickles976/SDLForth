/*
    Dynamic Dispatch Table for user-defined word

    The simplest solution is just to read in a user definition like:
    `: 2DUP DUP DUP ;`
    And store the word definition and body in a hashmap
    { '2DUP' : ['DUP', 'DUP'] }
    Since our interpreter works on an array of strings (StringArray),
    we can just do a lookup, and pass the result into the interpreter function.

    This is slower than storing function ptrs. 
    In the future, maybe the interpreter loop could save the data as bytecode with function pointers, and we could skip 
    the slower string hashing stuff.
*/
#ifndef D_TABLE_DYNAMIC_H
#define D_TABLE_DYNAMIC_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "stack.h"
#include "string_array.h"

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