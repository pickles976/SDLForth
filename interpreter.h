#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdbool.h>
#include "string_array.h"
#include "stack.h"
#include "sd_table.h"
#include "dd_table.h"
#include "vm.h"


bool is_digit(char c);
bool is_number(char* word);

void split(char *line, StringArray *array);
void interpret(StringArray *array, VM *vm, SD_Table *sd_table, DD_Table *dd_table);
void define_user_function(StringArray *array, VM *vm, SD_Table *sd_table, DD_Table *dd_table);

#endif
