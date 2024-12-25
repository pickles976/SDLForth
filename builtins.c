/*
    These functions are NOT ATOMIC! They will leave a bunch of crap on your 
    stack if they fail halfway through.

    Maybe I will just exit if these fail. Not sure.
*/

#include "stack.h"
#include "builtins.h"

bool builtin_dup(IntStack *stack) {
    int peeked_value;
    HANDLE_UNDERFLOW(peek_int_from_stack(stack, &peeked_value));
    HANDLE_OVERFLOW(push_int_to_stack(stack, peeked_value));
    return true;
}

bool builtin_drop(IntStack *stack) {
    int popped_value;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &popped_value));
    return true;
}

bool builtin_swap(IntStack *stack) {
    int first, next;

    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &first));
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &next));

    HANDLE_OVERFLOW(push_int_to_stack(stack, first));
    HANDLE_OVERFLOW(push_int_to_stack(stack, next));

    return true;
}

bool builtin_dot(IntStack *stack) {
    int popped_value;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &popped_value));
    printf("%d", popped_value);
    printf("\n");
    return true;
}
