#ifndef VM_H
#define VM_H

typedef void (*VoidFunc)(IntStack*);

typedef struct Instruction;

enum InstructionType {
    VALUE,
    BUILTIN,
    WORD
}

union U_ByteCode {
    int;
    VoidFunc;
    size_t;
}

struct Instrction {
    InstructionType type;
    U_ByteCode bytecode;
};

typedef struct {
    size_t capacity; // max # of instructions
    size_t length; // # of instructions
    size_t ip; // instruction ptr
    Instruction *code;
} VM;

VM *newVM(size_t capacity);
void run(VM *vm, DataStack *data_stack, CallStack *call_stack, SD_Table *sd_table, DD_Table *dd_table);
void addInstruction(InstructionType type, U_ByteCode instruction);

#endif