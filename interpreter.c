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

void interpret(IntStack *stack, StringArray *array, SD_Table *builtin_table) {

  // Loop over words
  for (int i = 0; i < array->count; i++) {
    char* word = array->tokens[i];

    if (is_number(word)) {
      int number = strtol(word, NULL, 10);
      push_int_to_stack(stack, number);
    } else {
      bool found_builtin = built_in_dispatch(stack, builtin_table, word);

      if (!found_builtin) {
        printf("%s?", word);
        printf("\n");
      } 

    }

  }

}
