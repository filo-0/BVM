# Summary
 This repository contains the surce code of a bytecode virtual machine and a bytecode compiler.

# BVM
 bvm is the virtual machine application, it takes as argument a path to the bytecode file extracts and executes it.
 It's structured as a stack machine:
  ## Function stack
   The function stack contains all local variables of a function, every time a function is called it grows of 'n' words with 'n' a fixed number defined by the function requirements. 
  ## Operation stack
   The operation stack is used to pass arguments for the opcode instructions, evrey time an operation is called 'n' words get popped or pushed as defined by the instruction. 
   
# Bytecode
 All instructions are coded in a byte of information, some instruction require fixed arguments placed immediately aftwerward while the dynamic arguments are passed via the operation stack.
