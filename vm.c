#include "vm.h"

VM *newVM(size_t capacity) {
    VM *vm = malloc(sizeof(VM));
    vm->capacity = capacity;
    vm->length = 0;
    vm->ip = 0;
    vm->code = malloc(sizeof(Instruction) * capacity);
    return vm;
}

bool addInstruction(VM *vm, InstructionType type, U_ByteCode bytecode) {

    if (vm->length == vm->capacity) return false;

    vm->code[vm->length] = (Instruction){ .type = type, .bytecode = bytecode};
    vm->length++;
    return true;

}

void step(VM *vm, IntStack *data_stack, IntStack *call_stack, SD_Table *sd_table, DD_Table *dd_table) {
    
    Instruction ins = vm->code[vm->ip++];
    switch(ins.type) {
        case VALUE:
            push_int_to_stack(data_stack, (int)ins.bytecode.value);
            break;
        case FUNC:
            // call our builtin function
            ins.bytecode.builtin(data_stack);
            break;
        case JUMP:
            // Push current address to call stack so we dont forget it, and jump the IP to the specified address
            push_int_to_stack(call_stack, vm->ip);
            vm->ip = (size_t)ins.bytecode.address;
            break;
        case RETURN:
            int return_int;
            pop_int_from_stack(call_stack, &return_int);
            vm->ip = (size_t)return_int;
            break;
        default:
            break;
    }
}

void run(VM *vm, IntStack *data_stack, IntStack *call_stack, SD_Table *sd_table, DD_Table *dd_table) {
    while (vm->ip < vm->length) {
        step(vm, data_stack, call_stack, sd_table, dd_table);
    }
}

bool printVM(VM *vm) {
    for (int i = 0; i < vm->length; i++) {
        Instruction instruction = vm->code[i];
        switch (instruction.type) {
            case VALUE:
                printf("[VALUE, %d]", instruction.bytecode.value);
                break;
            case FUNC:
                printf("[FUNC]");
                break;
            case JUMP:
                printf("[JUMP, %zd]", instruction.bytecode.address);
                break;
            case RETURN:
                printf("[RETURN]");
                break;
            default:
                printf("ERROR");
                break;
        }
    }
    printf("\n");
}