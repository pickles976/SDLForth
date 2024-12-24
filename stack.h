#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    size_t top;
    size_t capacity;
    int *items;
} IntStack;

IntStack *new_int_stack(size_t capacity);
bool push_int_stack(IntStack *stack, int item);
bool pop_int_stack(IntStack *stack, int *return_item);
void free_stack(IntStack *stack);

#endif

