#ifndef VM_H
#define VM_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "stack.h"
#include "sd_table.h"
#include "dd_table.h"

typedef void (*VoidFunc)(IntStack*);

typedef enum {
    VALUE,
    FUNC,
    JUMP,
    RETURN,
    BRANCH
} InstructionType;

typedef union {
    int value;
    VoidFunc builtin;
    size_t address;
} U_ByteCode;

typedef struct {
    InstructionType type;
    U_ByteCode bytecode;
} Instruction;

typedef struct {
    size_t capacity; // max # of instructions
    size_t length; // # of instructions
    size_t ip; // instruction ptr
    Instruction *code;
} VM;

VM *newVM(size_t capacity);
void step(VM *vm, IntStack *data_stack, IntStack *call_stack, SD_Table *sd_table, DD_Table *dd_table);
void run(VM *vm, IntStack *data_stack, IntStack *call_stack, SD_Table *sd_table, DD_Table *dd_table);
bool addInstruction(VM *vm, InstructionType type, U_ByteCode bytecode);
bool printVM(VM *vm);

#endif