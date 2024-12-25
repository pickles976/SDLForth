# README

https://skilldrick.github.io/easyforth/


### TODO:
- [x] write scanner for REPL
- [x] break into tokens?
- [x] show tokens
- [x] refactor data structures
- [x] iterate over tokens
- [x] push numeric tokens onto stack
- [x] if statements to run built-in functions 
    - [x] DUP
    - [x] DROP
    - [x] SWAP
    - [x] .
- [ ] static dispatch table for built-in functions
- [ ] refactor built-ins to use dispatch table
- [ ] create a dynamic dispatch table for user-defined functions { string: list[Token] }
- [ ] allow user-defined functions
- [ ] get user-defined functions working

- [ ] bytecode interpreter?
- [ ] instead of storing user-defined functions as strings, store them as a list of bytecode instructions
ex: 
```C
Function { f_ptr }
```

1. Read line
2. Break line into words
3. Iterate over words
4. strcmp over words
5. central interpreter loop