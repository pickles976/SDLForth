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
./forth.exe 
Keys: SWAP, *, +, -, ., /, DROP, DUP, 
> 1     
[1]
> : 2DUP DUP DUP ;
[1]
> 2DUP
[1][1][1]
```

## TODO:

Rewrite as a VM-based interpreter
- [ ] instruction struct and functions
- [ ] vm struct and functions
- [ ] Call stack
- [ ] refactor DD table
- [ ] handle populating VM with builtins
- [ ] handle user-defined words
- [ ] jump and return


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
