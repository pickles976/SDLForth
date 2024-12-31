#ifndef BUILTINS_H
#define BUILTINS_H

#include "stack.h"
#include "sd_table.h"
#include <stdio.h>
#include <stdbool.h>

bool builtin_dup(IntStack *stack);

bool builtin_drop(IntStack *stack);

bool builtin_swap(IntStack *stack);

bool builtin_dot(IntStack *stack);

bool init_builtin_table(SD_Table *table);

#endif