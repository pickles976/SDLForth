#include "vm.h"

VM *newVM(size_t capacity) {
    VM *vm = malloc(sizeof(VM));
    vm->capacity = capacity;
    vm->length = 0;
    vm->ip = 0;
    vm->code = malloc(sizeof(int) * capacity);
    return vm;
}

bool addInstruction(VM *vm, InstructionType type, int bytecode) {

    if (vm->length == vm->capacity) return false;

    vm->code[vm->length] = (Instruction){.type = type, .bytecode = bytecode };
    vm->length++;
    return true;

}

void step(VM *vm, IntStack *data_stack, IntStack *call_stack, HashTable *sd_table, HashTable *hash_table) {
    
    Instruction ins = vm->code[vm->ip++];
    switch(ins.type) {
        case VALUE:
            push_int_to_stack(data_stack, ins.bytecode);
            break;
        case FUNC:
            // call our builtin function
            dispatch(ins.bytecode, data_stack);
            break;
        case JUMP:
            // Push current address to call stack so we dont forget it, and jump the IP to the specified address
            push_int_to_stack(call_stack, vm->ip);
            vm->ip = (size_t)ins.bytecode;
            break;
        case RETURN:
            int return_address;
            pop_int_from_stack(call_stack, &return_address);
            vm->ip = (size_t)return_address;
            break;
        case BRANCH:
            int truth_value;
            pop_int_from_stack(data_stack, &truth_value);
            if (truth_value == 0) { // If false, skip to THEN
                vm->ip = (size_t)ins.bytecode;
            }
            break;
        default:
            break;
    }
}

void run(VM *vm, IntStack *data_stack, IntStack *call_stack, HashTable *sd_table, HashTable *hash_table) {
    while (vm->ip < vm->length) {
        step(vm, data_stack, call_stack, sd_table, hash_table);
    }
}

bool printVM(VM *vm) {
    for (int i = 0; i < vm->length; i++) {
        Instruction instruction = vm->code[i];
        switch (instruction.type) {
            case VALUE:
                printf("[%d: %d]", i, instruction.bytecode);
                break;
            case FUNC:
                printf("[%d: ", i);
                printCode(instruction.bytecode);
                printf("]");
                break;
            case JUMP:
                printf("[%d: JMP(%d)]", i, instruction.bytecode);
                break;
            case RETURN:
                printf("[%d: RET]", i);
                break;
            case BRANCH:
                printf("[%d: BRANCH(%d)]", i, instruction.bytecode);
                break;
            default:
                printf("ERROR");
                break;
        }
    }
    printf("\n");
}