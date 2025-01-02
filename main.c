#include <stdio.h>
#include "interpreter.h"
#include "stack.h"
#include "string_array.h"
#include "builtins.h"
#include "vm.h"

static void repl() {

  StringArray *array = new_string_array(256);

  VM *vm = newVM(1024);
  IntStack *data_stack = new_int_stack(256);
  IntStack *call_stack = new_int_stack(256);
  HashTable *sd_table = new_hash_table(64);
  HashTable *hash_table = new_hash_table(2);

  init_builtin_table(sd_table);
  print_hash_table_keys(sd_table);

  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    split(line, array);
    interpret(array, vm, sd_table, hash_table);
    run(vm, data_stack, call_stack, sd_table, hash_table);

    printf("STACK: ");
    print_stack(data_stack);
    printf("VM: ");
    printVM(vm);
    clear_string_array(array);
    
  }

  free_stack(data_stack);
  free_stack(call_stack);
  free_string_array(array);
  free_hash_table(sd_table);
  free_hash_table(hash_table);

}

int main(int argc, const char *argv[]) {
  repl();
  return 0;
}
