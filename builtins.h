#ifndef BUILTINS_H
#define BUILTINS_H

#include "stack.h"
#include "hash_table.h"
#include <stdio.h>
#include <stdbool.h>

typedef enum {
    DUP,
    DROP,
    SWAP,
    DOT,
    EQUALS,
    LESS_THAN,
    GREATER_THAN,
    ADD,
    SUBTRACT,
    DIVIDE,
    MULTIPLY
} FunctionCode;

bool b_dup(IntStack *stack);
bool b_drop(IntStack *stack);
bool b_swap(IntStack *stack);
bool b_dot(IntStack *stack);
bool b_add(IntStack *stack);
bool b_sub(IntStack *stack);
bool b_mult(IntStack *stack);
bool b_div(IntStack *stack);
bool b_eq(IntStack *stack);
bool b_lt(IntStack *stack);
bool b_gt(IntStack *stack);

bool init_builtin_table(HashTable *table);
void dispatch(FunctionCode code, IntStack *stack);
void printCode(FunctionCode code);

#endif