/*
    These functions are NOT ATOMIC! They will leave a bunch of crap on your 
    stack if they fail halfway through.

    Maybe I will just exit if these fail. Not sure.
*/

#include "stack.h"
#include "builtins.h"

bool b_dup(IntStack *stack) {
    int peeked_value;
    HANDLE_UNDERFLOW(peek_int_from_stack(stack, &peeked_value));
    HANDLE_OVERFLOW(push_int_to_stack(stack, peeked_value));
    return true;
}

bool b_drop(IntStack *stack) {
    int popped_value;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &popped_value));
    return true;
}

bool b_swap(IntStack *stack) {
    int first, next;

    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &first));
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &next));

    HANDLE_OVERFLOW(push_int_to_stack(stack, first));
    HANDLE_OVERFLOW(push_int_to_stack(stack, next));

    return true;
}

bool b_dot(IntStack *stack) {
    int popped_value;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &popped_value));
    printf("%d", popped_value);
    printf("\n");
    return true;
}

bool b_add(IntStack *stack) {
    int augend, addend;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &augend));
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &addend));
    HANDLE_OVERFLOW(push_int_to_stack(stack, augend + addend));
    return true;
}

bool b_sub(IntStack *stack) {
    int subtrahend, minuend;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &subtrahend));
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &minuend));
    HANDLE_OVERFLOW(push_int_to_stack(stack, minuend - subtrahend));
    return true;
}

bool b_mult(IntStack *stack) {
    int multiplicand, multiplier;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &multiplicand));
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &multiplier));
    HANDLE_OVERFLOW(push_int_to_stack(stack, multiplicand * multiplier));
    return true;
}

bool b_div(IntStack *stack) {
    int divisor, dividend;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &divisor));
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &dividend));
    // TODO: handle div by zero
    HANDLE_OVERFLOW(push_int_to_stack(stack, dividend / divisor));
    return true;
}

bool b_eq(IntStack *stack) {
    int first, second;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &first));
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &second));
    int result = first == second ? 1 : 0;
    HANDLE_OVERFLOW(push_int_to_stack(stack, result));
    return true;
}

bool b_lt(IntStack *stack) {
    int first, second;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &first));
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &second));
    int result = first < second ? 1 : 0;
    HANDLE_OVERFLOW(push_int_to_stack(stack, result));
    return true;
}

bool b_gt(IntStack *stack) {
    int first, second;
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &first));
    HANDLE_UNDERFLOW(pop_int_from_stack(stack, &second));
    int result = first > second ? 1 : 0;
    HANDLE_OVERFLOW(push_int_to_stack(stack, result));
    return true;
}


bool init_builtin_table(SD_Table *table) {

    insert_item_sd_table(table, "DUP", (VoidFunc)b_dup);
    insert_item_sd_table(table, "DROP", (VoidFunc)b_drop);
    insert_item_sd_table(table, "SWAP", (VoidFunc)b_swap);

    insert_item_sd_table(table, ".", (VoidFunc)b_dot);
    insert_item_sd_table(table, "+", (VoidFunc)b_add);
    insert_item_sd_table(table, "-", (VoidFunc)b_sub);
    insert_item_sd_table(table, "*", (VoidFunc)b_mult);
    insert_item_sd_table(table, "/", (VoidFunc)b_div);

    insert_item_sd_table(table, "=", (VoidFunc)b_eq);
    insert_item_sd_table(table, "<", (VoidFunc)b_lt);
    insert_item_sd_table(table, ">", (VoidFunc)b_gt);

}