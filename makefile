

all:
	gcc -o forth.exe main.c stack.c interpreter.c string_array.c builtins.c dtable_static.c dtable_dynamic.c

dynamic_table: 
	gcc -o ./table.exe test_table.c dtable_dynamic.c string_array.c

clean:
	rm -r main.o
	rm -f forth.exe
