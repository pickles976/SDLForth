#include "dd_table.h"
#include "sd_table.h" // get hash function
#include <stdio.h>

DD_Table *new_dd_table(size_t capacity) {
    DD_Table *table = malloc(sizeof(DD_Table));
    table->capacity = capacity;
    table->length = 0;
    table->keys = malloc(sizeof(size_t) * capacity);
    table->strings = malloc(sizeof(char*) * capacity);
    table->values = malloc(sizeof(StringArray*) * capacity);

    for (size_t i = 0; i < capacity; i++) {
        table->keys[i] = EMPTY_KEY;
    }

    return table;
}

void free_dd_table(DD_Table *table) {

    for (int i = 0; i < table->capacity; i++) {
        if (table->keys[i] != EMPTY_KEY) {
            free(table->strings[i]);
            free_string_array(table->values[i]);
        }
    }

    free(table->keys);
    free(table->strings);
    free(table->values);
    free(table);
}

bool insert_item_dd_table(DD_Table *table, char *key, StringArray *value) {


    if (table->capacity == table->length) {
        size_t oldCapacity = table->capacity;
        size_t stringsize = sizeof(char*) * oldCapacity;
        size_t valuesize = sizeof(StringArray*) * oldCapacity;

        char **strings = malloc(stringsize);
        StringArray **values = malloc(valuesize);

        memcpy(strings, table->strings, stringsize);
        memcpy(values, table->values, valuesize);

        free(table->keys);
        free(table->strings);
        free(table->values);
        free(table);
        *table = *new_dd_table(oldCapacity * 2);
        for (size_t i = 0; i < oldCapacity; i++) {
            insert_item_dd_table(table, strings[i], values[i]);
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

bool get_item_dd_table(DD_Table *table, char *key, StringArray **return_item) {
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

void print_dd_table_keys(DD_Table *table) {
    printf("Keys: ");
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->keys[i] != EMPTY_KEY) {
            printf("%s, ", table->strings[i]);
        }
    }
    printf("\n");
}

void print_dd_table_values(DD_Table *table) {
    printf("Values: ");
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->keys[i] != EMPTY_KEY) {
            print_string_array(table->values[i]);
        }
    }
    printf("\n");
}