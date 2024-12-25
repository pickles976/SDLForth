

all:
	gcc -o forth.exe main.c stack.c interpreter.c string_array.c builtins.c

clean:
	rm -r main.o
	rm -f forth.exe
