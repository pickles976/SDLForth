all:
	gcc -o forth.exe main.c stack.c interpreter.c string_array.c builtins.c hash_table.c vm.c

hash_table: 
	gcc -o ./table.exe ./tests/test_table.c hash_table.c string_array.c

clean:
	rm -r main.o
	rm -f forth.exe
