# BVM
bvm is the virtual machine application, it takes as argument a path to the bytecode file extracts and executes it.
It's inspired by the java virtual machine and therefore is structured as a stack machine with :

## Types
 - ```byte``` : 8 bit value
 - ```hword``` : 16 bit value
 - ```word``` : 32 bit value
 - ```dword``` : 64 bit value
 - ```i8``` : 8 bit signed integer
 - ```i16``` : 16 bit signed integer
 - ```i32``` : 32 bit signed integer
 - ```i64``` : 64 bit signed integer
 - ```u8``` : 8 bit unsigned integer
 - ```u16``` : 16 bit unsigned integer
 - ```u32``` : 32 bit unsigned integer
 - ```u64``` : 64 bit unsigned integer
 - ```f32``` : 32 bit floating point
 - ```f64``` : 64 bit floating point
 
## Function stack
The function stack contains all local variables of a function, every time a function is called it grows of __N__ words with __N__ a fixed number defined by the function requirements. A function scope cannot be greater than 255 words.

## Operation stack
The operation stack is used to pass arguments for the opcode instructions, every time an operation is called __N__ words get popped and __K__ words pushed as defined by the instruction. 

## Constant pools
The every program has two costant pools, one for __words__ and one for __dwords__. Values in the pools can only be pushed onto the __operation stack__ but cannot be modified during the execution of a program

## Bytecode
All instructions are coded in a byte of information, so the maximum number of instructions is 256.
Instruction have two types of parameters:
 - ```fixed``` : a constant parameters placed immediately after the bytecode
 - ```dynamic``` : values passed via the ```operation stack```
 
## Bytecode set
The complete set of instructions is defined in __"opcodes.hpp"__, and contains:
### Push operations
#### Push local
 - ```push_byte_{b}, l``` : pushes ___function stack___ local word ```l``` byte ```b``` [0, 3] to the ___operation stack___
 - ```push_hword_{h}, l``` : pushes ___function stack___ local word ```l``` half word ```h``` {0, 2} to the ___operation stack___
 - ```push_word_{w}``` : pushes ___function stack___ local word ```w``` [0, 4] to the ___operation stack___
 - ```push_word, l``` : pushes ___function stack___ local word ```l``` [0, 255] to the ___operation stack___
 - ```push_dword_{d}``` : pushes ___function stack___ local double word starting from position ```d``` [0, 4] to the ___operation stack___
 - ```push_dword, l``` : pushes ___function stack___ local double word starting from position ```l``` [0, 254] to the __operation stack__
 - ```push_words, l, n``` : pushes n [0, 255] words from ___function stack___  local word l [0, 255 - n] to the ___operation stack___
 #### Push immediate values
 - ```push_word_value_0``` : pushes to the ___operation stack___ the value __0x00000000__
 - ```push_dword_value_0``` : pushes to the ___operation stack___ the value __0x0000000000000000__
 - ```push_i8_as_i32, v``` : pushes v [-128, 127] casted to a __i32__ to the ___operation stack___ 
 - ```push_i8_as_i64, v``` : pushes v [-128, 127] casted to a __i64__ to the ___operation stack___
 - ```push_i32_1``` : pushes to the ___operation stack___ the i32 value 1
 - ```push_i32_2``` : pushes to the ___operation stack___ the i32 value 2
 - ```push_i64_1``` : pushes to the ___operation stack___ the i64 value 1
 - ```push_i64_2``` : pushes to the ___operation stack___ the i64 value 2
 - ```push_f32_1``` : pushes to the ___operation stack___ the f32 value 1
 - ```push_f32_2``` : pushes to the ___operation stack___ the f32 value 2
 - ```push_f64_1``` : pushes to the ___operation stack___ the f64 value 1
 - ```push_f64_2``` : pushes to the ___operation stack___ the f64 value 2
#### Push from pool
 - ```push_word_from_pool, c``` : pushed to the ___operation stack___ the ___const word pool___ element at index c [0, 255]
 - ```push_word_from_pool_wide, c``` : pushed to the ___operation stack___ the ___const word pool___ element at index c [0, 2<sup>16</sup> - 1]
 - ```push_dword_from_pool, c``` : pushed to the ___operation stack___ the ___const dword pool___ element at index c [0, 255]
 - ```push_dword_from_pool_wide, c``` : pushed to the ___operation stack___ the ___const dword pool___ element at index c [0, 2<sup>16</sup> - 1]
 - ```push_string_from_pool, c``` : pushed to the ___operation stack___ the ___const string pool___ the pointer to element at index c [0, 255]
 - ```push_string_from_pool_wide, c``` : pushed to the ___operation stack___ the ___const string pool___ the pointer to element at index c [0, 2<sup>16</sup> - 1]
#### Push address
 - ```get_address, l``` : pushes to the ___operation stack___ the dword pointer of the ___function stack___ local word ```l``` [0, 255]

### Pop operations
 - ```pop_byte_{b}, l``` : pops to ___function stack___ local word ```l``` byte b [0, 3] from ___operation stack___
 - ```pop_word_{w}``` : pops to ___function stack___ local word w [0, 4] from ___operation stack___
 - ```pop_word, l``` : pops to ___function stack___ local word ```l``` [0, 255] from __operation stack__
 - ```pop_dword_{d}``` : pops to ___function stack___ local double word starting from position ```d``` [0, 4] from ___operation stack___
 - ```pop_dword, l``` : pops to ___function stack___ local double word starting from position ```l``` [0, 254] from ___operation stack___
 - ```pop_words, l, n``` : pops to ___function stack___ local word ```l``` [0, 255 - n] ```n``` [0, 255] words from ___operation stack___
  
### Operation stack manipulation operations
 - ```dup_word``` : duplicates the word on top of the ___operation stack___
 - ```dup_word_x1``` : duplicates the word on top of the ___operation stack___ and moves the original one word down
 - ```dup_word_x2``` : duplicates the word on top of the ___operation stack___ and moves the original two words down
 - ```dup_dword``` : duplicates the two words on top of the ___operation stack___
 - ```dup_dword_x1``` : duplicates the two words on top of the ___operation stack___ and moves the originals one word down
 - ```dup_dword_x2``` : duplicates the two words on top of the ___operation stack___ and moves the originals two words down
 - ```swap_word``` : swaps the two words on top of the ___operation stack___
 - ```swap_dword``` : swaps the two top word pairs of the ___operation stack___

### Memory access operations
### Load
 - ```load_byte_{b}``` : pops from the ___operation stack___ a dword pointer __P__ and pushes a word containing the byte ```b``` [0, 3] of the word pointed by __P__
 - ```load_hword_{b}``` : pops from the ___operation stack___ a dword pointer __P__ and pushes a word containing the half word ```b``` {0, 2} of the word pointed by __P__
 - ```load_word``` : pops from the ___operation stack___ a dword pointer __P__ and pushes the word pointed by __P__
 - ```load_dword``` : pops from the ___operation stack___ a dword pointer __P__ and pushes the dword pointed by __P__
 - ```load_words, n``` : pops from the ___operation stack___ a dword pointer __P__ and pushes ```n``` [0, 255] words from the location pointed by __P__
 - ```load_buffer_byte_ref``` : pops from the ___operation stack___ a word index __I__ and a dword pointer __P__ and pushes __P__ offsetted by __I__ bytes (__P'__ = __P__ + __I__ * __sizeof(Byte)__)
 - ```load_buffer_hword_ref``` : pops from the ___operation stack___ a word index __I__ and a dword pointer __P__ and pushes __P__ offsetted by __I__ hwords (__P'__ = __P__ + __I__ * __sizeof(HWord)__)
 - ```load_buffer_word_ref``` : pops from the ___operation stack___ a word index __I__ and a dword pointer __P__ and pushes __P__ offsetted by __I__ words (__P'__ = __P__ + __I__ * __sizeof(Word)__)
 - ```load_buffer_dword_ref``` : pops from the ___operation stack___ a word index __I__ and a dword pointer __P__ and pushes __P__ offsetted by __I__ dwords (__P'__ = __P__ + __I__ * __sizeof(DWord)__)
 - ```load_buffer_words_ref, n``` : pops from the ___operation stack___ a word index __I__ and a dword pointer __P__ and pushes __P__ offsetted by __I__ * ```n``` words (__P'__ = __P__ + __I__ * __sizeof(Word)__ * ```n```)
 - ```load_buffer_byte_val``` : pops from the ___operation stack___ a word index __I__ and a dword pointer __P__ and pushes a word containing the byte pointed by __P__ + __I__
 - ```load_buffer_hword_val``` : pops from the ___operation stack___ a word index __I__ and a dword pointer __P__ and pushes a word containing the hword pointed by __P__ + __I__ * __sizeof(HWord)__
 - ```load_buffer_word_val``` : pops from the ___operation stack___ a word index __I__ and a dword pointer __P__ and pushes the word pointed by __P__ + __I__ * __sizeof(Word)__
 - ```load_buffer_dword_val``` : pops from the ___operation stack___ a word index __I__ and a dword pointer __P__ and pushes the dword pointed by __P__ + __I__ * __sizeof(DWord)__
 - ```load_buffer_words_val, n``` : pops from the ___operation stack___ a word index __I__ and a dword pointer __P__ and pushes the ```n``` [0, 255] words pointed by __P__ + __I__ * __sizeof(Word)__ * ```n```
 - ```load_offset_byte_{b}, o``` : pops from the ___operation stack___ a dword pointer __P__ and pushes a word containing the byte ```b``` [0, 3] of the word pointed by __P__ + ```o``` * __sizeof(Word)__
 - ```load_offset_hword_{b}, o``` : pops from the ___operation stack___ a dword pointer __P__ and pushes a word containing the hword ```b``` {0, 2} of the word pointed by __P__ + ```o``` * __sizeof(Word)__
 - ```load_offset_word, o``` : pops from the ___operation stack___ a dword pointer __P__ and pushes the word pointed by __P__ + ```o``` * __sizeof(Word)__
 - ```load_offset_dword, o``` : pops from the ___operation stack___ a dword pointer __P__ and pushes the dword pointed by __P__ + ```o``` * __sizeof(Word)__
 - ```load_offset_words, o, n``` : pops from the ___operation stack___ a dword pointer __P__ and pushes ```n``` [0, 255] words pointed by __P__ + ```o``` * __sizeof(Word)__
 ### Store
 - ```store_byte_{b}``` : pops from the ___operation stack___ a word value __V__ and a dword pointer __P__ and set the byte ```b``` [0, 3] of the word pointed by __P__ to __V__
 - ```store_hword_{b}``` : pops from the ___operation stack___ a word value __V__ and a dword pointer __P__ and set the hword ```b``` {0, 2} of the word pointed by __P__ to __V__
 - ```store_word``` : pops from the ___operation stack___ a word value __V__ and a dword pointer __P__ and set the word pointed by __P__ to __V__
 - ```store_dword``` : pops from the ___operation stack___ a dword value __V__ and a dword pointer __P__ and set the dword pointed by __P__ to __V__
 - ```store_words, n``` : pops from the ___operation stack___ ```n``` [0, 255] words __V__ and a dword pointer __P__ and set the ```n``` words pointed by __P__ to __V__
 - ```store_buffer_byte``` : pops from the ___operation stack___ a word value __V__, a word index __I__ and a dword pointer __P__ and set the byte pointed by __P__ + __I__ * __sizeof(Byte)__ to __V__
 - ```store_buffer_hword``` : pops from the ___operation stack___ a word value __V__, a word index __I__ and a dword pointer __P__ and set the hword pointed by __P__ + __I__ * __sizeof(HWord)__ to __V__
 - ```store_buffer_word``` : pops from the ___operation stack___ a word value __V__, a word index __I__ and a dword pointer __P__ and set the word pointed by __P__ + __I__ * __sizeof(Word)__ to __V__
 - ```store_buffer_dword``` : pops from the ___operation stack___ a dword value __V__, a word index __I__ and a dword pointer __P__ and set the dword pointed by __P__ + __I__ * __sizeof(DWord)__ to __V__
 - ```store_buffer_words, n``` : pops from the ___operation stack___ ```n``` [0, 255] word value __V__, a word index __I__ and a dword pointer __P__ and set the ```n``` words pointed by __P__ + __I__ * __sizeof(Word)__ * ```n``` to __V__
 - ```store_offset_byte_{b}, o``` : pops from the ___operation stack___ a word value __V__ and a dword pointer __P__ and set the byte ```b``` [0, 3] of the word pointed by __P__ + ```o``` * __sizeof(Word)__ to __V__
 - ```store_offset_hword_{b}, o``` : pops from the ___operation stack___ a word value __V__ and a dword pointer __P__ and set the hword ```b``` {0, 2} of the word pointed by __P__ + ```o``` * __sizeof(Word)__ to __V__
 - ```store_offset_word, o``` : pops from the ___operation stack___ a word value __V__ and a dword pointer __P__ and set the word pointed by __P__ + ```o``` * __sizeof(Word)__ to __V__
 - ```store_offset_dword, o``` : pops from the ___operation stack___ a dword value __V__ and a dword pointer __P__ and set the dword pointed by __P__ + ```o``` * __sizeof(Word)__ to __V__
 - ```store_offset_words, o, n``` : pops from the ___operation stack___ ```n``` [0, 255] words __V__ and a dword pointer __P__ and set the ```n``` words pointed by __P__ + ```o``` * __sizeof(Word)__ to __V__

### Allocations and deallocations
 - ```alloc``` : pops from the ___operation stack___ a word value __N__ and allocates __N__ bytes on the heap, than pushes the pointed to the block onto the ___operation stack___

### Arithmetic operations
 - ```add_{t}``` : pops from the ___operation stack___ the top two words/dwords interpreted as ```t``` {i32, i64, f32, f64} and pushes their sum
 - ```sub_{t}``` : pops from the ___operation stack___ the top two words/dwords interpreted as ```t``` {i32, i64, f32, f64} and pushes their difference
 - ```mul_{t}``` : pops from the ___operation stack___ the top two words/dwords interpreted as ```t``` {i32, i64, f32, f64} and pushes their product
 - ```div_{t}``` : pops from the ___operation stack___ the top two words/dwords interpreted as ```t``` {i32, i64, f32, f64} and pushes their quotient
 - ```inc_{t}, l``` : increments by one the ___function stack___ local word/dword ```l``` [0, 255] of type ```t``` {i32, i64, f32, f64}
 - ```dec_{t}, l``` : decrements by one the ___function stack___ local word/dwords ```l``` [0, 255] of type ```t``` {i32, i64, f32, f64}
 - ```mod_{t}``` : pops from the ___operation stack___ the top two words/dwords interpreted as ```t``` {i32, i64, u32, u64, f32, f64} and pushes the remainder
 - ```neg_{t}``` : pops from the ___operation stack___ the top word/dword interpreted as ```t``` {i32, i64, f32, f64} and pushes its negative

### Bitwise operations
 - ```and_{t}``` : pops from the ___operation stack___ the top two words/dwords and pushes the bitwise __AND__ result
 - ```or_{t}``` : pops from the ___operation stack___ the top two words/dwords and pushes the bitwise __OR__ result 
 - ```xor_{t}``` : pops from the ___operation stack___ the top two words/dwords and pushes the bitwise __XOR__ result 
 - ```not_{t}``` : pops from the ___operation stack___ the top word/dword and pushes the bitwise __NOT__ result
 - ```shl_{t}``` : pops from the ___operation stack___ the top two words/dwords value __S__ and __V__ and pushes __V__ shifted left by __S__
 - ```shr_{t}``` : pops from the __operation stack___ the top two words/dwords value __S__ and __V__ interpreted as ```t``` {i32, i64, u32, u64} and pushes __V__ shifted rightright by __S__

### Jump operations
 - ```jmp, o``` : jumps by  ```o``` [-2<sup>15</sup>, 2<sup>15</sup>-1] instructions
 - ```jmp_{t}_{c}, o``` : jumps by ```o``` [-2<sup>15</sup>, 2<sup>15</sup>-1] instructions if the condition ```c``` {eq, ne, lt, gt, le, ge} is satisfied by the top two words/dwords of the ___operation stack___ interpreted as ```t``` {i32, i64, u32, u64, f32, f64}

Note: The __ne__ and __eq__ comparison between __u__ values is equivalent to comparison between __i__ values so for example ```jmp_u32_eq``` does not exist.

### Function call and return
 - ```call, f``` : looks at the functions table at index ```f``` [0, 65535] and opens a new stack frame on the __function stack__ of __N__ words defined by the function local words count, and pops __K__ words defined by the function input parameters from the __operation stack__ and inserts them in the __function stack__ from local word 0
 - ```syscall, f``` : calls a virtual machine system call pointed by the index ```f``` [0, 255]
 - ```return_void``` : pops the scope of the ___function stack___ and restores the previous ___operation stack___ scope
 - ```return_byte``` : pops the scope of the ___function stack___ and restores the previous ___operation stack___ scope pushing the top word as byte from the previous frame
 - ```return_hword``` : pops the scope of the ___function stack___ and restores the previous ___operation stack___ scope pushing the top word hword from the previous frame
 - ```return_word``` : pops the scope of the ___function stack___ and restores the previous ___operation stack___ scope pushing the top word hword from the previous frame
 - ```return_dword``` : pops the scope of the ___function stack___ and restores the previous ___operation stack___ scope pushing the top word pair from the previous frame
 - ```return_words, n``` : pops the scope of the ___function stack___ and restores the previous ___operation stack___ scope pushing the top ```n``` [0, 255] words from the previous frame

#### System call codes 
       0 (Print): prints a string
       1 (PrintI64): prints an i64 value
       2 (PrintF64): prints an f64 value
       3 (SqrtF32): returns the square root of an f32 value
       4 (SqrtF64): returns the square root of an f64 value

### Cast operations
 - ```{t}_to_{g}``` : casts the top word/dword value of the ___operation stack___ interpreted as ```t``` {i32, i64, f32, f64} to a ```g``` {i32, i64, f32, f64}
