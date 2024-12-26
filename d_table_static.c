#include "d_table_static.h"
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

SD_Table *new_sd_table(size_t capacity) {
    SD_Table *table = malloc(sizeof(SD_Table));
    table->capacity = capacity;
    table->length = 0;
    table->keys = malloc(sizeof(size_t) * capacity);
    table->values = malloc(sizeof(VoidFunc) * capacity);

    for (size_t i = 0; i < capacity; i++) {
        table->keys[i] = EMPTY_KEY;
    }

    return table;
}

void free_sd_table(SD_Table *table) {
    free(table->keys);
    free(table->values);
    free(table);
}

bool insert_item_sd_table(SD_Table *table, char *key, VoidFunc value) {

    if (table->capacity == table->length) {
        return false;
    }

    size_t hash = hash_string(key);
    size_t modulo_hash = hash % table->capacity;

    // Linear probe 
    // WARNING: UNTESTED!!!
    size_t offset = 0;
    for (size_t offset = 0; offset < table->capacity; offset++) {
        size_t index = (modulo_hash + offset) % table->capacity;
        if (table->keys[index] == EMPTY_KEY) {
            // printf("Inserted %s @ index %d with hash %d", key, index, hash);
            // printf("\n");
            table->keys[index] = hash;
            table->values[index] = value;
            table->length++;
            return true;
        }
    }

    return false;

}

bool get_item_sd_table(SD_Table *table, char *key, VoidFunc *return_item) {
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

void print_sd_table_keys(SD_Table *table) {
    printf("Keys: ");
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->keys[i] != EMPTY_KEY) {
            printf("%d, ", table->keys[i]);
        }
    }
    printf("\n");
}