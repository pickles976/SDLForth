#include "stack.h"
#include "builtins.h"

bool builtin_dup(IntStack *stack) {

    int peeked_value;
    if (peek_int_from_stack(stack, &peeked_value)) {
        return push_int_to_stack(stack, peeked_value);
    }
    return false;

}

bool builtin_drop(IntStack *stack) {
    int popped_value;
    return pop_int_from_stack(stack, &popped_value);
}

bool builtin_swap(IntStack *stack) {
    int first, next;
    if (pop_int_from_stack(stack, &first)) {
        if (pop_int_from_stack(stack, &next)) {
            return push_int_to_stack(stack, first) && push_int_to_stack(stack, next);
        }
    }
    return false;
}

bool builtin_dot(IntStack *stack) {
    int popped_value;
    if (pop_int_from_stack(stack, &popped_value)) {
        printf("%d", popped_value);
        printf("\n");
        return true;
    }
    return false;
}
