#include "string_array.h"

StringArray *new_string_array(size_t capacity) {
    StringArray *array = malloc(sizeof(StringArray));
    array->count = 0;
    array->capacity = capacity;
    array->tokens = malloc(sizeof(char*) * capacity);
}

void clear_string_array(StringArray* array) {
    array->count = 0;
}

bool add_string_to_array(StringArray* array, char* word) {

    if (array->count == array->capacity) {
        return false;
    }

    array->tokens[array->count] = word;
    array->count++;
    return true;
}

void free_string_array(StringArray* array) {
    for (int i = 0; i < array->count; i++) {
        free(array->tokens[i]);
    }
    free(array->tokens);
}

void print_string_array(StringArray* array) {
    printf("[");
    for (int i = 0; i < array->count; i++) {
        printf("%s", array->tokens[i]);
        if (i < array->count - 1) {
            printf(", ");
        }
    }
    printf("]");
    printf("\n");
}