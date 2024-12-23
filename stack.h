#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    size_t top;
    size_t capacity;
    int *items;
} Stack;

Stack *new_stack(size_t capacity);
bool push_stack(Stack *stack, int item);
bool pop_stack(Stack *stack, int *return_item);
void free_stack(Stack *stack);

#endif

