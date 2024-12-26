#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdbool.h>
#include "string_array.h"
#include "stack.h"
#include "d_table_static.h"

bool is_digit(char c);
bool is_number(char* word);

void split(char *line, StringArray *array);
void interpret(IntStack *stack, StringArray *array, SD_Table *builtin_table);

#endif
