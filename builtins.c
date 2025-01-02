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


bool init_builtin_table(HashTable *table) {

    insert_item_hash_table(table, "DUP", DUP);
    insert_item_hash_table(table, "DROP", DROP);
    insert_item_hash_table(table, "SWAP", SWAP);

    insert_item_hash_table(table, ".", DOT);

    insert_item_hash_table(table, "+", ADD);
    insert_item_hash_table(table, "-", SUBTRACT);
    insert_item_hash_table(table, "*", MULTIPLY);
    insert_item_hash_table(table, "/", DIVIDE);

    insert_item_hash_table(table, "=", EQUALS);
    insert_item_hash_table(table, "<", LESS_THAN);
    insert_item_hash_table(table, ">", GREATER_THAN);

}

void dispatch(FunctionCode code, IntStack *stack) {

    switch (code) {
        case DUP:
            b_dup(stack);
            break;
        case DROP:
            b_drop(stack);
            break;
        case SWAP:
            b_swap(stack);
            break;
        case DOT:
            b_dot(stack);
            break;
        case ADD:
            b_add(stack);
            break;
        case SUBTRACT:
            b_sub(stack);
            break;
        case MULTIPLY:
            b_mult(stack);
            break;
        case DIVIDE:
            b_div(stack);
            break;
        case EQUALS:
            b_eq(stack);
            break;
        case LESS_THAN:
            b_lt(stack);
            break;
        case GREATER_THAN:
            b_gt(stack);
            break;
        default:
            break;
    }
}

void printCode(FunctionCode code) {
    switch (code) {
        case DUP:
            printf("DUP");
            break;
        case DROP:
            printf("DROP");
            break;
        case SWAP:
            printf("SWAP");
            break;
        case DOT:
            printf("DOT");
            break;
        case ADD:
            printf("ADD");
            break;
        case SUBTRACT:
            printf("SUBTRACT");
            break;
        case MULTIPLY:
            printf("MULTIPLY");
            break;
        case DIVIDE:
            printf("DIVIDE");
            break;
        case EQUALS:
            printf("EQUALS");
            break;
        case LESS_THAN:
            printf("LESS_THAN");
            break;
        case GREATER_THAN:
            printf("GREATER_THAN");
            break;
        default:
            break;
    }
}