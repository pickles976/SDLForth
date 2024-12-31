
#include <stdio.h>
#include "dd_table.h"
#include "string_array.h"

int main(int argc, const char *argv[]) {

  StringArray* a = new_string_array(4);
  StringArray* b = new_string_array(4);

  add_string_to_array(a, "ONE");
  add_string_to_array(a, "TWO");

  add_string_to_array(b, "THREE");
  add_string_to_array(b, "FOUR");

  DD_Table *table = new_dd_table(2);
  insert_item_dd_table(table, "A", a);
  insert_item_dd_table(table, "B", b);
  insert_item_dd_table(table, "C", b);
  insert_item_dd_table(table, "D", a);
  insert_item_dd_table(table, "E", b);
  print_dd_table_keys(table);
  print_dd_table_values(table);

  StringArray *item;
  get_item_dd_table(table, "A", &item);
  print_string_array(item);

  get_item_dd_table(table, "B", &item);
  print_string_array(item);

  get_item_dd_table(table, "C", &item);
  print_string_array(item);

  get_item_dd_table(table, "D", &item);
  print_string_array(item);

  get_item_dd_table(table, "E", &item);
  print_string_array(item);

  return 0;
}
