#include "interpreter.h"
#include "stack.h"
#include <stdio.h>

static void repl() {
  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    interpret(line);
  }
}

int main(int argc, const char *argv[]) {

  Stack *stack = new_stack(256);

  repl();

  return 0;
}
