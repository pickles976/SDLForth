#include "interpreter.h"
#include "builtins.h"
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

bool built_in_dispatch(IntStack *stack, char *word) {
  if (strcmp(word, "DUP") == 0) {
    builtin_dup(stack);
  } else if (strcmp(word, "DROP") == 0) {
    builtin_drop(stack);
  } else if (strcmp(word, "SWAP") == 0) {
    builtin_swap(stack);
  } else if (strcmp(word, ".") == 0) {
    builtin_dot(stack);
  } else {
    return false;
  }
  return true;
}

void interpret(IntStack *stack, StringArray *array) {

  for (int i = 0; i < array->count; i++) {
    // printf("%s", string_array.tokens[i]);
    // printf("\n");
    char* word = array->tokens[i];

    // SWITCH
    // Look for word
    // check numebr
    // print identifier back to console with question

    if (is_number(word)) {
      int number = strtol(word, NULL, 10);
      push_int_to_stack(stack, number);
    } else {
      bool found_builtin = built_in_dispatch(stack, word);

      if (!found_builtin) {
        printf("%s?", word);
        printf("\n");
      } 

    }

  }

}
