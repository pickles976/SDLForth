#include "interpreter.h"
#include "stack.h"
#include "string_array.h"
#include <stdio.h>

static void repl() {

  IntStack *stack = new_int_stack(256);
  StringArray *array = new_string_array(256);

  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    split(line, array);
    // print_string_array(array);

    // TODO: interpret on split tokens
    interpret(stack, array);
    print_stack(stack);

    clear_string_array(array);
    
  }
}

int main(int argc, const char *argv[]) {


  repl();

  return 0;
}
