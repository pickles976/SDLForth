
#include <stdio.h>
#include "hash_table.h"
#include "string_array.h"

int main(int argc, const char *argv[]) {

  StringArray* a = new_string_array(4);
  StringArray* b = new_string_array(4);

  add_string_to_array(a, "ONE");
  add_string_to_array(a, "TWO");

  add_string_to_array(b, "THREE");
  add_string_to_array(b, "FOUR");

  HashTable *table = new_hash_table(2);
  insert_item_hash_table(table, "A", a);
  insert_item_hash_table(table, "B", b);
  insert_item_hash_table(table, "C", b);
  insert_item_hash_table(table, "D", a);
  insert_item_hash_table(table, "E", b);
  print_hash_table_keys(table);
  print_hash_table_values(table);

  StringArray *item;
  get_item_hash_table(table, "A", &item);
  print_string_array(item);

  get_item_hash_table(table, "B", &item);
  print_string_array(item);

  get_item_hash_table(table, "C", &item);
  print_string_array(item);

  get_item_hash_table(table, "D", &item);
  print_string_array(item);

  get_item_hash_table(table, "E", &item);
  print_string_array(item);

  return 0;
}
