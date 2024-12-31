#include "interpreter.h"
#include <stdio.h>
#include <string.h>

bool is_digit(char c) { return c >= '0' && c <= '9'; }

bool is_number(char *word) {

  int word_len = strlen(word);
  for (int i = 0; i < word_len; i++) {
    if (is_digit(word[i]) || (i == 0 && word[i] == '-')) {

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

bool built_in_dispatch(IntStack *stack, SD_Table *builtin_table, char *word) {

  VoidFunc builtin;
  bool result = get_item_sd_table(builtin_table, word, &builtin);
  if (result) {
    BoolFunc fp = (BoolFunc)builtin;

    bool op_result = fp(stack);
    if (!op_result) {
      printf("INVALID OPERATION OCCURED. EXITING...");
      printf("\n");
      exit(0);
    }
    return true;
  }
  return false;
}

// void define_user_function(StringArray *array, DD_Table *dispatch_table) {

//   // Bounds checking
//   size_t line_len = array->count;
//   bool ends_with_semicolon = strcmp(array->tokens[line_len - 1], ";") == 0;
//   bool has_enough_tokens = line_len >= 4; // : NAME [JUMPS] ;
//   if (!ends_with_semicolon || !has_enough_tokens) {
//     printf("ERROR, EXPECTED: ': NAME [JUMPS] ;'");
//     printf("\n");
//   }

//   // Copy pointers to new array
//   StringArray *copy_array = new_string_array(line_len - 3);
//   for (size_t i = 2; i < line_len - 1; i++) {
//     add_string_to_array(copy_array, array->tokens[i]);
//   }
//   // Insert item into table
//   insert_item_dd_table(dispatch_table, array->tokens[1], copy_array);
//   // print_dd_table_keys(dispatch_table);
//   // print_dd_table_values(dispatch_table);
// }

// bool function_dispatch(IntStack *stack, SD_Table *builtin_table, DD_Table *dispatch_table, char *word) {
//   StringArray *return_item;
//   bool found_function = get_item_dd_table(dispatch_table, word, &return_item);
//   if (found_function) {
//     interpret(stack, return_item, builtin_table, dispatch_table);
//   }
//   return found_function;
// }

void interpret(StringArray *array, VM *vm, IntStack *data_stack, IntStack *call_stack, SD_Table *sd_table, DD_Table *dd_table) {

  // Loop over words
  for (int i = 0; i < array->count; i++) {
    char* word = array->tokens[i];

    U_ByteCode bytecode;

    if (is_number(word)) {
      int number = strtol(word, NULL, 10);
      bytecode.value = number;
      addInstruction(vm, VALUE, bytecode);
    } else if (strcmp(word, ":") == 0) {
      // define_user_function(array, dispatch_table);
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
