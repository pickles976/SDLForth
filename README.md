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
Keys: SWAP, *, +, -, ., /, DROP, DUP, 
> 1
STACK: [1]
VM: [VALUE, 1]
> : 2DUP DUP DUP ;
STACK: [1]
VM: [VALUE, 1][FUNC][FUNC][RETURN]
> 2DUP
STACK: [1][1][1]
VM: [VALUE, 1][FUNC][FUNC][RETURN][JUMP, 1]
> 3
STACK: [1][1][1][3]
VM: [VALUE, 1][FUNC][FUNC][RETURN][JUMP, 1][VALUE, 3]
> : 4DUP 2DUP 2DUP ;
STACK: [1][1][1][3]
VM: [VALUE, 1][FUNC][FUNC][RETURN][JUMP, 1][VALUE, 3][JUMP, 1][JUMP, 1][RETURN]
> 4DUP
STACK: [1][1][1][3][3][3][3][3]
VM: [VALUE, 1][FUNC][FUNC][RETURN][JUMP, 1][VALUE, 3][JUMP, 1][JUMP, 1][RETURN][JUMP, 6]
```

## TODO:

Write some tests

(can we consolidate sd and dd table?)
- [ ] dd table
- [ ] sd table
- [ ] stack
- [ ] vm
- [ ] improve error handling

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
