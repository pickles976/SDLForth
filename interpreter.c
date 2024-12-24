#include "interpreter.h"
#include <stdio.h>
#include <string.h>
#include "string_array.h"


static StringArray string_array;

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

void split(char *line) {
  // Split a single line of text on the whitespace
  int begin = 0;
  int end = 0;
  int length = strlen(line);

  while (end < length) {
    end++;

    if (line[end] == ' ' || line[end] == '\n') {

      // Copy the word
      int word_len = end - begin;
      char *word = malloc(sizeof(char) * word_len + 1);
      memcpy(word, &line[begin], word_len * sizeof(char));
      word[word_len] = '\0';

      // Step forward
      begin = end + 1;

      // Copy to the token array
      addWord(&string_array, word);
    }
  }
}

void interpret(char *line) {

  initStringArray(&string_array);

  split(line);
  // printStringArray(&string_array);

  for (int i = 0; i < string_array.count; i++) {
    // printf("%s", string_array.tokens[i]);
    // printf("\n");
    char* word = string_array.tokens[i];
    if (is_number(word)) {
      // TODO: convert to number and push to stack
      int number = strtol(word, NULL, 10);
      printf("Number: %lu", number);
      printf("\n");
    } else {
      printf("Word: %s", word);
      printf("\n");
    }

  }


  freeStringArray(&string_array);
}
