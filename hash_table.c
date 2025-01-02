#include "hash_table.h"
#include <stdio.h>

// WARNING: NOT EVALUATED. idk how rare collisions are with this hash function
size_t hash_string(char *key)
{
    size_t hash = HASH;
    int c;

    while (c = *key++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

HashTable *new_hash_table(size_t capacity) {
    HashTable *table = malloc(sizeof(HashTable));
    table->capacity = capacity;
    table->length = 0;
    table->keys = malloc(sizeof(size_t) * capacity);
    table->strings = malloc(sizeof(char*) * capacity);
    table->values = malloc(sizeof(size_t) * capacity);

    for (size_t i = 0; i < capacity; i++) {
        table->keys[i] = EMPTY_KEY;
    }

    return table;
}

void free_hash_table(HashTable *table) {

    for (int i = 0; i < table->capacity; i++) {
        if (table->keys[i] != EMPTY_KEY) {
            free(table->strings[i]);
        }
    }

    free(table->keys);
    free(table->strings);
    free(table->values);
    free(table);
}

bool insert_item_hash_table(HashTable *table, char *key, int value) {


    if (table->capacity == table->length) {
        size_t oldCapacity = table->capacity;
        size_t stringsize = sizeof(char*) * oldCapacity;
        size_t valuesize = sizeof(size_t) * oldCapacity;

        char **strings = malloc(stringsize);
        size_t *values = malloc(valuesize);

        memcpy(strings, table->strings, stringsize);
        memcpy(values, table->values, valuesize);

        free(table->keys);
        free(table->strings);
        free(table->values);
        free(table);
        *table = *new_hash_table(oldCapacity * 2);
        for (size_t i = 0; i < oldCapacity; i++) {
            insert_item_hash_table(table, strings[i], values[i]);
        }
        // printf("Growing table!\n");
        // printf("Old Capacity: %d, New Capacity: %d\n", oldCapacity, oldCapacity * 2);
    }

    size_t hash = hash_string(key);
    size_t modulo_hash = hash % table->capacity;

    // Linear probe 
    // WARNING: UNTESTED!!!
    // WARNING: DUPLICATE INSERTS WILL LIVE IN DIFFERENT BUCKETS
    size_t offset = 0;
    for (size_t offset = 0; offset < table->capacity; offset++) {
        size_t index = (modulo_hash + offset) % table->capacity;
        if (table->keys[index] == EMPTY_KEY) {
            // printf("Inserted %s @ index %d with hash %d", key, index, hash);
            // printf("\n");
            table->keys[index] = hash;
            table->values[index] = value;
            table->strings[index] = key;
            table->length++;
            return true;
        }
    }

    return false;

}

bool get_item_hash_table(HashTable *table, char *key, int *return_item) {
    size_t hash = hash_string(key);
    size_t modulo_hash = hash % table->capacity;

    // Linear probe
    // WARNING: UNTESTED!!!
    for (size_t offset = 0; offset < table->capacity; offset++) {
        size_t index = (modulo_hash + offset) % table->capacity;
        size_t slot = table->keys[index];

        if (slot == EMPTY_KEY) {
            return false;
        } 
        
        // Slot is not empty, AND hash matches
        if (slot == hash) {
            // printf("Got %s @ index %d with hash %d", key, index, hash);
            // printf("\n");
            *return_item = table->values[index];
            return true;
        }
    }

    return false;
}

void print_hash_table_keys(HashTable *table) {
    printf("Keys: ");
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->keys[i] != EMPTY_KEY) {
            printf("%s, ", table->strings[i]);
        }
    }
    printf("\n");
}

void print_hash_table_values(HashTable *table) {
    printf("Values: ");
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->keys[i] != EMPTY_KEY) {
            printf("%d, ", table->values[i]);
        }
    }
    printf("\n");
}