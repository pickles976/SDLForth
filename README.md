# README

Attempt at writing a Forth interpreter from scratch, with SDL2 integration for hacking away at small games.
I am aware that having resizable hash tables is overkill for a Forth. This is really just to learn to write 
*an* interpreter for what is probably the easiest language to interpret. I hope for this to be a stepping 
stone to writing something like a Scheme interpreter, as well as having an excuse to write some data structures in C. 

Reference Material:  
[Easy Forth](https://skilldrick.github.io/easyforth/)  
[Starting Forth](https://www.forth.com/starting-forth)  
[Forth C Implementation](https://github.com/tehologist/forthkit)  
[VM Stuff](https://www.andreinc.net/2021/12/01/writing-a-simple-vm-in-less-than-125-lines-of-c)   
[Forth Fundamentals](https://archive.org/details/forthfundamental0001mcca)  
[Thinking Forth](https://www.forth.com/wp-content/uploads/2018/11/thinking-forth-color.pdf)  

## Example

```commandline
Keys: SWAP, *, +, -, ., /, DROP, <, =, >, DUP, 
> : ZERO? 0 = IF 13 . THEN ;
STACK: 
VM: [0: 0][1: EQUALS][2: BRANCH(5)][3: 13][4: DOT][5: RET]
> 0 ZERO?
13
STACK: 
VM: [0: 0][1: EQUALS][2: BRANCH(5)][3: 13][4: DOT][5: RET][6: 0][7: JMP(0)]
```

## TODO:
- [ ] implement "ELSE"
- [ ] add strings (disallow spaces for simplicity)

Add more builtins
- [x] =
- [x] >
- [x] <
- [ ] OVER
- [ ] ROT
- [ ] MOD
- [ ] /MOD

#### Tests
- [ ] stack
- [ ] vm
- [ ] improve error handling

Read Starting Forth Ch 4
https://www.forth.com/starting-forth/4-conditional-if-then-statements/

#### Control flow/storage
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
