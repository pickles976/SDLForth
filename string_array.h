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

void initStringArray(StringArray* string_array);
bool addWord(StringArray* string_array, char* word);
void freeStringArray(StringArray* string_array);
void printStringArray(StringArray* string_array);

#endif