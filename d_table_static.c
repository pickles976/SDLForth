#include "d_table_static.h"

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
    table->values = malloc(sizeof(VoidFunc*) * capacity);

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

bool insert_sd_table(SD_Table *table, char *key, VoidFunc *value) {

    if (table->capacity == table->length) {
        return false;
    }

    size_t hash = hash_string(key);
    size_t modulo_hash = hash % table->capacity;

    // Linear probe
    size_t offset = 0;
    for (size_t offset = 0; offset < table->capacity; offset++) {
        size_t index = (modulo_hash + offset) % table->capacity;
        size_t slot = table->keys[index];
        if (slot == EMPTY_KEY) {
            table->keys[index] = hash;
            table->values[index] = *value;
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
    size_t offset = 0;
    for (size_t offset = 0; offset < table->capacity; offset++) {
        size_t index = (modulo_hash + offset) % table->capacity;
        size_t slot = table->keys[index];

        // Slot is empty
        if (slot == EMPTY_KEY) {
            return false;
        } 
        
        // Slot is not empty, AND keys match
        if (slot == hash) {
            return_item = &table->values[index];
            return true;
        }
    }

    return false;
}