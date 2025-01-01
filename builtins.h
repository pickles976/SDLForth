#ifndef BUILTINS_H
#define BUILTINS_H

#include "stack.h"
#include "sd_table.h"
#include <stdio.h>
#include <stdbool.h>

bool b_dup(IntStack *stack);

bool b_drop(IntStack *stack);

bool b_swap(IntStack *stack);

bool b_dot(IntStack *stack);

bool b_eq(IntStack *stack);

bool b_lt(IntStack *stack);

bool b_gt(IntStack *stack);

bool init_builtin_table(SD_Table *table);

#endif