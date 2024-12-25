#include "stack.h"
#include <stdbool.h>

#define STACK_MAX 1024

IntStack *new_int_stack(size_t capacity) {
  IntStack *stack = malloc(sizeof(IntStack));
  if (!stack) {
    return NULL;
  }
  stack->top = 0;
  stack->capacity = capacity;
  stack->items = malloc(sizeof(int) * capacity);

  if (!stack->items) {
    free(stack);
    stack = NULL;
    return NULL;
  }
  return stack;
}

IntStackResult push_int_to_stack(IntStack *stack, int item) {
  if (stack->top == stack->capacity) {
    return STACK_OVERFLOW_ERR;
  }

  stack->items[stack->top] = item;
  stack->top++;
  return OK;
}

IntStackResult pop_int_from_stack(IntStack *stack, int *return_item) {
  if (stack->top == 0) {
    return STACK_UNDERFLOW_ERR;
  }

  stack->top--;
  *return_item = stack->items[stack->top];
  return OK;
}

IntStackResult peek_int_from_stack(IntStack *stack, int *return_item) {
  if (stack->top == 0) {
    return STACK_UNDERFLOW_ERR;
  }
  *return_item = stack->items[stack->top - 1];
  return OK;
}

void print_stack(IntStack *stack) {
  for (int i = 0; i < stack->top; i++) {
    printf("[%d]", stack->items[i]);
  }
  printf("\n");
}

void free_stack(IntStack *stack) {
  free(stack->items);
  free(stack);
}