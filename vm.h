#ifndef VM_H
#define VM_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "stack.h"
#include "builtins.h"
#include "hash_table.h"

typedef enum {
    VALUE,
    FUNC,
    JUMP,
    RETURN,
    BRANCH
} InstructionType;

typedef struct {
    InstructionType type;
    int bytecode;
} Instruction;

typedef struct {
    size_t capacity; // max # of instructions
    size_t length; // # of instructions
    size_t ip; // instruction ptr
    Instruction *code;
} VM;

VM *newVM(size_t capacity);
void step(VM *vm, IntStack *data_stack, IntStack *call_stack, HashTable *sd_table, HashTable *hash_table);
void run(VM *vm, IntStack *data_stack, IntStack *call_stack, HashTable *sd_table, HashTable *hash_table);
bool addInstruction(VM *vm, InstructionType type, int bytecode);
bool printVM(VM *vm);

#endif