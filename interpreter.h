#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdbool.h>
#include "string_array.h"
#include "stack.h"
#include "sd_table.h"
#include "dd_table.h"
#include "vm.h"


bool isDigit(char c);
bool isNumber(char* word);

void split(char *line, StringArray *array);
void interpret(StringArray *array, VM *vm, SD_Table *sd_table, DD_Table *dd_table);
void defineUserFunction(StringArray *array, VM *vm, SD_Table *sd_table, DD_Table *dd_table);
void defineIfStatement(StringArray *array, VM *vm, SD_Table *sd_table, DD_Table *dd_table);

#endif
