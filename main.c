#include "interpreter.h"
#include "stack.h"
#include "string_array.h"
#include "builtins.h"
#include <stdio.h>

static void repl() {

  IntStack *stack = new_int_stack(256);
  StringArray *array = new_string_array(256);
  SD_Table *builtin_table = new_sd_table(64);
  init_builtin_table(builtin_table);
  print_sd_table_keys(builtin_table);

  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    split(line, array);
    interpret(stack, array, builtin_table);
    print_stack(stack);
    clear_string_array(array);
    
  }

  free_stack(stack);
  free_string_array(array);
  free_sd_table(builtin_table);

}

int main(int argc, const char *argv[]) {


  repl();

  return 0;
}
