# Summary
 This repository contains the surce code of a bytecode virtual machine and a bytecode compiler.

# BVM
 bvm is the virtual machine application, it takes as argument a path to the bytecode file extracts and executes it.
 It's structured as a stack machine with a increase size of one word (32bit value) :
  ## Function stack
   The function stack contains all local variables of a function, every time a function is called it grows of __N__ words with __N__ a fixed number defined by the function requirements. A function scope cannot be greater than 255 words.
  ## Operation stack
   The operation stack is used to pass arguments for the opcode instructions, evrey time an operation is called __N__ words get popped and __K__ words pushed as defined by the instruction. 

# Types
 i8: 8 bit signed integer (byte)
 i16: 16 bit signed integer (hword)
 i32: 32 bit signed integer (word)
 i64: 64 bit signed integer (dword)
 u8: 8 bit unsigned integer (byte)
 u16: 16 bit unsigned integer (hword)
 u32: 32 bit unsigned integer (word)
 u64: 64 bit unsigned integer (dword)
 f32: 32 bit floating point (word)
 f64: 64 bit floating point (dword)
 
# Bytecode
 All instructions are coded in a byte of information, some instruction require fixed arguments placed immediately aftwerward while the dynamic arguments are passed via the operation stack.
 ## Bytecode set
  The complete set of instructions is defined in __"opcodes.hpp"__, and contains:
   ### Push operations

   push_byte_b, n: pushes __function stack__ local word n byte b [0, 3] to the __operation stack__
   push_hword_h, n: pushes __function stack__ local word n half word h {0, 2} to the __operation stack__
   push_word_w: pushes __function stack__ local word w [0, 4] to the __operation stack__
   push_word, n: pushes __function stack__ local word n [0, 255] to the __operation stack__
   push_dword_d: pushes __function stack__ local double word starting from position d [0, 4] to the __operation stack__
   push_dword, n: pushes __function stack__ local double word starting from position n [0, 254] to the __operation stack__
   push_words, l, n: pushes __function stack__ n [0, 255] words from local word l [0, 255 - n] to the __operation stack__

   push_word_value_0: pushes to the __operation stack__ the value __0x00000000__
   push_dword_value_0: pushes to the __operation stack__ the value __0x0000000000000000__
   push_i8_as_i32, v: pushes v [0, 255] casted to a __i32__ to the __operation stack__ 
   push_i8_as_i32, v: pushes v [0, 255] casted to a __i64__ to the __operation stack__ 
   push_i32_1: pushes to the __operation stack__ the i32 value 1  
   push_i32_2: pushes to the __operation stack__ the i32 value 2
   push_i64_1: pushes to the __operation stack__ the i64 value 1
   push_i64_2: pushes to the __operation stack__ the i64 value 2
   push_f32_1: pushes to the __operation stack__ the f32 value 1
   push_f32_2: pushes to the __operation stack__ the f32 value 2
   push_f64_1: pushes to the __operation stack__ the f64 value 1
   push_f64_2: pushes to the __operation stack__ the f64 value 2

   ### Pop operations
   pop_byte_b, n: pops to __function stack__ local word n byte b [0, 3] from __operation stack__
   pop_hword_h, n: pops to __function stack__ local word n half word h {0, 2} from __operation stack__
   pop_word_w: pops to __function stack__ local word w [0, 4] from __operation stack__
   pop_word, n: pops to __function stack__ local word n [0, 255] from __operation stack__
   pop_dword_d: pops to __function stack__ local double word starting from position d [0, 4] from __operation stack__
   pop_dword, n: pops to __function stack__ local double word starting from position n [0, 254] from __operation stack__
   pop_words, l, n: pops to __function stack__ local word l [0, 255 - n] n [0, 255] words from __operation stack__
   
   ### Operation stack manipulation operations
   dup_word: duplicates the word on top of the __operation stack__
   dup_word_x1: duplicates the word on top of the __operation stack__ and moves the original one word down
   dup_word_x2: duplicates the word on top of the __operation stack__ and moves the original two words down
   dup_dword: duplicates the two words on top of the __operation stack__
   dup_dword_x1: duplicates the two words on top of the __operation stack__ and moves the originals one word down
   dup_dword_x2: duplicates the two words on top of the __operation stack__ and moves the originals two words down
   swap_word: swaps the two words on top of the __operation stack__
   swap_dword: swaps the two top word pairs of the __operation stack__
