#include "string_array.h"

void initStringArray(StringArray* string_array) {
    string_array->count = 0;
    string_array->capacity = 1024;
    string_array->tokens = malloc(sizeof(char*) * 1024);
}

bool addWord(StringArray* string_array, char* word) {

    if (string_array->count == string_array->capacity) {
        return false;
    }

    string_array->tokens[string_array->count] = word;
    string_array->count++;
    return true;
}

void freeStringArray(StringArray* string_array) {
    for (int i = 0; i < string_array->count; i++) {
        free(string_array->tokens[i]);
    }
    free(string_array->tokens);
}

void printStringArray(StringArray* string_array) {
    printf("[");
    for (int i = 0; i < string_array->count; i++) {
        printf("%s", string_array->tokens[i]);
        if (i < string_array->count - 1) {
            printf(", ");
        }
    }
    printf("]");
    printf("\n");
}