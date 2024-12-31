#include "interpreter.h"
#include "stack.h"
#include "string_array.h"
#include "builtins.h"
#include <stdio.h>
#include "vm.h"

static void repl() {

  StringArray *array = new_string_array(256);

  VM *vm = newVM(1024);
  IntStack *data_stack = new_int_stack(256);
  IntStack *call_stack = new_int_stack(256);
  SD_Table *sd_table = new_sd_table(64);
  DD_Table *dd_table = new_dd_table(2);

  init_builtin_table(sd_table);
  print_sd_table_keys(sd_table);

  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    split(line, array);
    interpret(array, vm, data_stack, call_stack, sd_table, dd_table);
    run(vm, data_stack, call_stack, sd_table, dd_table);
    // U_ByteCode byte_1;
    // byte_1.builtin = (VoidFunc)builtin_dup;
    // addInstruction(vm, FUNC, byte_1);
    // step(vm, data_stack, call_stack, sd_table, dd_table);
    printf("STACK: ");
    print_stack(data_stack);
    printf("VM: ");
    printVM(vm);
    clear_string_array(array);
    
  }

  free_stack(data_stack);
  free_stack(call_stack);
  free_string_array(array);
  free_sd_table(sd_table);
  free_dd_table(dd_table);

}

int main(int argc, const char *argv[]) {
  repl();
  return 0;
}
