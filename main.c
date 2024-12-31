#include "interpreter.h"
#include "stack.h"
#include "string_array.h"
#include "builtins.h"
#include <stdio.h>
#include "vm.h"

// static void repl() {

//   IntStack *stack = new_int_stack(256);
//   StringArray *array = new_string_array(256);
//   SD_Table *builtin_table = new_sd_table(64);
//   DD_Table *dispatch_table = new_dd_table(2);

//   init_builtin_table(builtin_table);
//   print_sd_table_keys(builtin_table);

//   char line[1024];
//   for (;;) {
//     printf("> ");

//     if (!fgets(line, sizeof(line), stdin)) {
//       printf("\n");
//       break;
//     }

//     split(line, array);
//     interpret(stack, array, builtin_table, dispatch_table);
//     print_stack(stack);
//     clear_string_array(array);
    
//   }

//   free_stack(stack);
//   free_string_array(array);
//   free_sd_table(builtin_table);

// }

int main(int argc, const char *argv[]) {

  VM *vm = newVM(1024);
  IntStack *data_stack = new_int_stack(256);
  IntStack *call_stack = new_int_stack(256);
  SD_Table *sd_table = new_sd_table(64);
  DD_Table *dd_table = new_dd_table(2);

  init_builtin_table(sd_table);
  print_sd_table_keys(sd_table);

  U_ByteCode byte_0;
  byte_0.value = 123;
  addInstruction(vm, VALUE, byte_0);
  step(vm, data_stack, call_stack, sd_table, dd_table);

  printf("STACK: ");
  print_stack(data_stack);

  printf("VM: ");
  printVM(vm);

  U_ByteCode byte_1;
  byte_1.builtin = (VoidFunc)builtin_dup;
  addInstruction(vm, BUILTIN, byte_1);
  step(vm, data_stack, call_stack, sd_table, dd_table);

  printf("STACK: ");
  print_stack(data_stack);

  printf("VM: ");
  printVM(vm);


  return 0;
}
