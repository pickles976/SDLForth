#include "interpreter.h"
#include <stdio.h>
#include <string.h>

bool isDigit(char c) { return c >= '0' && c <= '9'; }

bool isNumber(char *word) {

  int word_len = strlen(word);
  for (int i = 0; i < word_len; i++) {
    if (isDigit(word[i]) || (i == 0 && word[i] == '-')) {

    } else {
      return false;
    }
  }
  return true;
}

void split(char *line, StringArray *array) {
  /*
    Splits a single line of text on space.

    Splitting the string: ' 1 \n\0':
    
       [  ][1 ][  ][\n][\0]
    0. [be][  ][  ][  ][  ] e - b == 0, skip
    1. [  ][be][  ][  ][  ] 
    2. [  ][b ][e ][  ][  ] e - b == 1, copy '1'
    3. [  ][  ][  ][be][  ] e - b == 0, skip
  */
  int begin = 0;
  int end = 0;
  int length = strlen(line);

  while (end < length) {

    if (line[end] == ' ' || line[end] == '\n') {

      // Copy the word
      int word_len = end - begin;
      if (word_len > 0) {

        // Copy the string
        char *word = malloc(sizeof(char) * word_len + 1);
        memcpy(word, &line[begin], word_len * sizeof(char));
        word[word_len] = '\0';

        // Copy to the token array
        add_string_to_array(array, word);
      }

      // Step forward
      begin = end + 1;

    }

    end++;
  }
}

void defineUserFunction(StringArray *array, VM *vm, SD_Table *sd_table, DD_Table *dd_table) {
  /**
   * Example Input: [":", "2DUP", "DUP", "DUP", ";"]
   * 
   * ----------> ip
   * VM: [PREV][*DUP][*DUP][RETURN]
   * 
   * DD_TABLE: { 2DUP : ip }
   * 
   * Now when the interpreter reads "2DUP", it will add a JUMP instruction with the address ip.
   */

  // Bounds checking
  size_t line_len = array->count;
  bool ends_with_semicolon = strcmp(array->tokens[line_len - 1], ";") == 0;
  bool has_enough_tokens = line_len >= 4; // : NAME [WORDS] ;
  if (!ends_with_semicolon || !has_enough_tokens) {
    printf("ERROR, EXPECTED: ': NAME [WORDS] ;'");
    printf("\n");
  }

  // Copy pointers to new array
  StringArray *copy_array = new_string_array(line_len - 3);
  for (size_t i = 2; i < line_len - 1; i++) {
    add_string_to_array(copy_array, array->tokens[i]);
  }

  // TODO: might need to modify this bit of code to allow of re-definition of functions
  // Insert current address into table
  insert_item_dd_table(dd_table, array->tokens[1], vm->length);

  // Add instructions into vm (requires recursion)
  interpret(copy_array, vm, sd_table, dd_table);

  // Add return instruction
  U_ByteCode bytecode;
  addInstruction(vm, RETURN, bytecode);

  // skip over function definition
  vm->ip = vm->length;
}

void defineIfStatement(StringArray *array, VM *vm, SD_Table *sd_table, DD_Table *dd_table) {
    /**
   * Example Input: [":", "ZERO?", "=", "0", "IF", "1", ".", "THEN", "0", ".", ";"]
   * 
   * ip ---> |                               | <----------------------branch address
   * VM: [*EQUALS][BRANCH][VALUE(1)][DOT][VALUE(0)][DOT][RETURN]
   * 
   * 
   * BRANCH will jump to the address of the bytecode that executes after "THEN"
   * Otherwise, the interpreter will just continue to run.
   */

  // Look for "THEN"
  int i = 0;
  int index = -1;
  while (i < array->count) {
    if (strcmp(array->tokens[i], "THEN") == 0) {
      index = i;
      break;
    } 
    i++;
  }

  print_string_array(array);

  // "THEN" not found
  if (index == -1) {
    printf("EXPECTED ': WORD ___ IF ___ THEN ___ ;");
    printf("\n");
    return;
  }

  // TODO: handle else

  // add BRANCH instruction with no address (we don't know it yet)
  U_ByteCode bytecode;
  int branch_position = vm->length;
  addInstruction(vm, BRANCH, bytecode);

  // Assemble bytecode to be executed on IF
  StringArray *if_array = new_string_array(index);
  for (size_t i = 1; i < index; i++) { // Start at 1 to exclude IF
    add_string_to_array(if_array, array->tokens[i]);
  }
  interpret(if_array, vm, sd_table, dd_table);

  // Set BRANCH address to code executed by THEN
  vm->code[branch_position].bytecode.address = vm->length;

  // Assemble bytecode to be executed on THEN
  size_t then_length = array->count - index;
  StringArray *then_array = new_string_array(then_length);
  for (size_t i = 1; i < then_length - 1; i++) { // start at 1 to skip "THEN"
    add_string_to_array(then_array, array->tokens[i]);
  }
  interpret(then_array, vm, sd_table, dd_table);

}


void interpret(StringArray *array, VM *vm, SD_Table *sd_table, DD_Table *dd_table) {

  // Loop over words
  for (int i = 0; i < array->count; i++) {
    char* word = array->tokens[i];

    U_ByteCode bytecode;

    if (isNumber(word)) {
      // Add constant number to bytecode array
      int number = strtol(word, NULL, 10);
      bytecode.value = number;
      addInstruction(vm, VALUE, bytecode);
    } else if (strcmp(word, ":") == 0) {
      defineUserFunction(array, vm, sd_table, dd_table);
      break;
    } else if (strcmp(word, "IF") == 0) {
      // TODO: handle when "IF" is not the first word on the line
      // TODO: function to copy sublist from StringArray
      defineIfStatement(array, vm, sd_table, dd_table);
      break;
    } else {

      // Add function ptr to vm
      VoidFunc builtin;
      bool result = get_item_sd_table(sd_table, word, &builtin);
      if (result) {
        bytecode.builtin = (VoidFunc)builtin;
        addInstruction(vm, FUNC, bytecode);
        continue;
      }

      // Add instruction ptr JUMP to 
      size_t address;
      result = get_item_dd_table(dd_table, word, &address);
      if (result) {
        bytecode.address = address;
        addInstruction(vm, JUMP, bytecode);
        continue;
      }
      
      printf("%s?", word);
      printf("\n");

    }

  }

}
