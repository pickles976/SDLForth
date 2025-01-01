#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define HANDLE_OVERFLOW(result)             \
    do                                      \
    {                                       \
        if (result == STACK_OVERFLOW_ERR)   \
        {                                   \
            printf("STACK OVERFLOW ERROR"); \
            printf("\n");                   \
            return false;                   \
        }                                   \
    } while (0)

#define HANDLE_UNDERFLOW(result)             \
    do                                       \
    {                                        \
        if (result == STACK_UNDERFLOW_ERR)   \
        {                                    \
            printf("STACK UNDERFLOW ERROR"); \
            printf("\n");                    \
            return false;                    \
        }                                    \
    } while (0)

typedef enum
{
    OK,
    STACK_OVERFLOW_ERR,
    STACK_UNDERFLOW_ERR
} IntStackResult;

typedef struct
{
    size_t top;
    size_t capacity;
    int *items;
} IntStack;

// TODO: change names
IntStack *new_int_stack(size_t capacity);
IntStackResult push_int_to_stack(IntStack *stack, int item);
IntStackResult pop_int_from_stack(IntStack *stack, int *return_item);
IntStackResult peek_int_from_stack(IntStack *stack, int *return_item);
void print_stack(IntStack *stack);
void free_stack(IntStack *stack);

#endif
