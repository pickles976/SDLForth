#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdbool.h>

bool is_digit(char c);
bool is_number(char* word);

void interpret(char* line);

#endif
