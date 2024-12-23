#include "stack.h"
#include <stdbool.h>

#define STACK_MAX 1024

Stack *new_stack(size_t capacity) {
  Stack *stack = malloc(sizeof(Stack));
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

bool push_stack(Stack *stack, int item) {
  if (stack->top == stack->capacity) {
    return false;
  }

  stack->items[stack->top] = item;
  stack->top++;
  return true;
}

bool pop_stack(Stack *stack, int *return_item) {
  if (stack->top == 0) {
    return false;
  }

  stack->top--;
  *return_item = stack->items[stack->top];
  return true;
}
