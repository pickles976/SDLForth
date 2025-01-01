#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int count;
    int capacity;
    char** tokens;
} StringArray;

StringArray *new_string_array(size_t capacity);
StringArray *get_subarray(StringArray* array, int begin, int end);
void clear_string_array(StringArray* array);
bool add_string_to_array(StringArray* array, char* word);
void free_string_array(StringArray* array);
void print_string_array(StringArray* array);

#endif