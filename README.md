# README

https://skilldrick.github.io/easyforth/

## TODO:

#### User-defined functions
- [ ] create a dynamic dispatch table for user-defined functions
    - [ ] resizable hash table <size_t, char*>
- [ ] parse user-defined functions
- [ ] call user-defined functions

#### Control flow/storage
- [ ] implement conditionals
- [ ] implement variables
- [ ] constants
- [ ] implement cells
- [ ] implement begin until
- [ ] implement input handling

#### Cleanup n stuff
- [ ] read multiple lines
- [ ] read files
- [ ] add all built-ins
- [ ] improve the way of initializing the built-ins table
- [ ] add case-insensitivity
- [ ] improve "error handling" for stack overflow/underflow errors

#### Performance?
- [ ] bytecode interpreter?
- [ ] instead of storing user-defined functions as strings to interpret, store them as a list of bytecode instructions
