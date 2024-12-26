# README

Attempt at writing a Forth interpreter from scratch, with SDL2 integration for hacking away at small games.

Reference Material:
[Easy Forth](https://skilldrick.github.io/easyforth/)
[Starting Forth](https://www.forth.com/starting-forth)
[Forth C Implementation](https://github.com/tehologist/forthkit)

## TODO:

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

```commandline
./forth.exe 
Keys: SWAP, *, +, -, ., /, DROP, DUP, 
> 1     
[1]
> : 2DUP DUP DUP ;
[1]
> 2DUP
[1][1][1]
```