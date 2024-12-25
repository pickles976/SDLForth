#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define HASH 5381
#define EMPTY_KEY SIZE_MAX

typedef void (*VoidFunc)(void);
// typedef int (*IntFunc)(void);

// typedef enum {
//     VOID_FUNC,
//     INT_FUNC
// } FuncType;

// typedef struct {
//     char *key;
//     VoidFunc voidFunc; // Function pointer for void functions
// } FunctionItem;

typedef struct {
    size_t *keys;
    VoidFunc *values;

    size_t capacity; // capacity
    size_t length; // length
} SD_Table;

// FunctionItem* create_void_func_item(char *key, VoidFunc func);

size_t hash_string(char *key);

SD_Table* new_sd_table(size_t capacity);
void free_sd_table(SD_Table *table);
bool insert_sd_table(SD_Table *table, char *key, VoidFunc *item);
bool get_item_sd_tabe(SD_Table *table, char *key, VoidFunc *return_item);