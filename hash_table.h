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

#define HASH 5381
#define EMPTY_KEY SIZE_MAX


typedef struct {
    size_t *keys;
    char **strings;
    int *values;

    size_t capacity; // capacity
    size_t length; // length
} HashTable;

size_t hash_string(char *key);
HashTable* new_hash_table(size_t capacity);
void free_hash_table(HashTable *table);
bool insert_item_hash_table(HashTable *table, char *key, int value);
bool get_item_hash_table(HashTable *table, char *key, int *value);
void print_hash_table_keys(HashTable *table);
void print_hash_table_values(HashTable *table);

#endif