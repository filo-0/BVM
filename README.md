# Summary
 This repository contains the surce code of a bytecode virtual machine and a bytecode compiler.

# BVM
 bvm is the virtual machine application, it takes as argument a path to the bytecode file extracts and executes it.
 It's structured as a stack machine with a increase size of one word (32bit value) :
  ## Function stack
   The function stack contains all local variables of a function, every time a function is called it grows of __N__ words with __N__ a fixed number defined by the function requirements. 
  ## Operation stack
   The operation stack is used to pass arguments for the opcode instructions, evrey time an operation is called __N__ words get popped and __K__ words pushed as defined by the instruction. 
   
# Bytecode
 All instructions are coded in a byte of information, some instruction require fixed arguments placed immediately aftwerward while the dynamic arguments are passed via the operation stack.
 ## Bytecode set
  The complete set of instructions is defined in __"opcodes.hpp"__, and contains:
   ### Push operations
    A __push__ instruction gets as fixed parameter the local __FunctionStack__ word to get and pushes on the operation stack the value (byte, hword, word, dword, words)
