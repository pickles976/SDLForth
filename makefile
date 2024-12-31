

all:
	gcc -o forth.exe main.c stack.c interpreter.c string_array.c builtins.c dd_table.c sd_table.c

vm:
	gcc -o vm.exe main.c stack.c interpreter.c string_array.c builtins.c dd_table.c sd_table.c vm.c


dynamic_table: 
	gcc -o ./table.exe test_table.c dd_table.c string_array.c

clean:
	rm -r main.o
	rm -f forth.exe
