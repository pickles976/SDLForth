#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    size_t top;
    size_t capacity;
    int *items;
} IntStack;

IntStack *new_int_stack(size_t capacity);
bool push_int_to_stack(IntStack *stack, int item);
bool push_int_from_stack(IntStack *stack, int *return_item);
void print_stack(IntStack *stack);
void free_stack(IntStack *stack);

#endif

