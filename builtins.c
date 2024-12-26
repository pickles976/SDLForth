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

bool builtin_add(IntStack *stack) {
    int augend, addend;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &augend));
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &addend));
    HANDLE_OVERFLOW(push_int_to_stack(stack, augend + addend));
    return true;
}

bool builtin_subtract(IntStack *stack) {
    int subtrahend, minuend;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &subtrahend));
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &minuend));
    HANDLE_OVERFLOW(push_int_to_stack(stack, minuend - subtrahend));
    return true;
}

bool builtin_multiply(IntStack *stack) {
    int multiplicand, multiplier;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &multiplicand));
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &multiplier));
    HANDLE_OVERFLOW(push_int_to_stack(stack, multiplicand * multiplier));
    return true;
}

bool builtin_divide(IntStack *stack) {
    int divisor, dividend;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &divisor));
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &dividend));
    // TODO: handle div by zero
    HANDLE_OVERFLOW(push_int_to_stack(stack, dividend / divisor));
    return true;
}


bool init_builtin_table(SD_Table *table) {

    insert_item_sd_table(table, "DUP", (VoidFunc)builtin_dup);
    insert_item_sd_table(table, "DROP", (VoidFunc)builtin_drop);
    insert_item_sd_table(table, "SWAP", (VoidFunc)builtin_swap);
    insert_item_sd_table(table, ".", (VoidFunc)builtin_dot);
    insert_item_sd_table(table, "+", (VoidFunc)builtin_add);
    insert_item_sd_table(table, "-", (VoidFunc)builtin_subtract);
    insert_item_sd_table(table, "*", (VoidFunc)builtin_multiply);
    insert_item_sd_table(table, "/", (VoidFunc)builtin_divide);

}