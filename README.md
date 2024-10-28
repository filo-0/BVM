# Description
This repository contains the surce code of a bytecode virtual machine and a bytecode compiler.

# Build
This project require CMake.
To build the executables go to the __BVM/__ directory, than type from cmd:
Create build folder
```
mkdir build
```
Generate CMake build files
```
cmake ./build
```
to switch between __Debug__ or __Release__ build type add 
```-DCMAKE_BUILD_TYPE:String=Debug``` or ```-DCMAKE_BUILD_TYPE:String=Release```

Than to build the project type
```
cmake --build ./build
```

# Usage
First navigate to the executable directory.
### Bytecode compiler (bcc)
 - Windows : ```./bcc.exe <source_path> <out_path> ```
 - Linux : ```./bcc <source_path> <out_path> ```
### Bytecode vm (bvm)
 - Windows : ``` ./bvm.exe <bytecode_path> ```
 - Linux : ``` ./bvm <bytecode_path> ```

# BVM
bvm is the virtual machine application, it takes as argument a path to the bytecode file extracts and executes it.
It's structured as a stack machine with a increase size of one word (32bit value) :
## Function stack
The function stack contains all local variables of a function, every time a function is called it grows of __N__ words with __N__ a fixed number defined by the function requirements. A function scope cannot be greater than 255 words.
## Operation stack
   The operation stack is used to pass arguments for the opcode instructions, evrey time an operation is called __N__ words get popped and __K__ words pushed as defined by the instruction. 
   
# Types
 - i8: 8 bit signed integer (byte)
 - i16: 16 bit signed integer (hword)
 - i32: 32 bit signed integer (word)
 - i64: 64 bit signed integer (dword)
 - u8: 8 bit unsigned integer (byte)
 - u16: 16 bit unsigned integer (hword)
 - u32: 32 bit unsigned integer (word)
 - u64: 64 bit unsigned integer (dword)
 - f32: 32 bit floating point (word)
 - f64: 64 bit floating point (dword)
 
# Bytecode
All instructions are coded in a byte of information, some instruction require fixed arguments placed immediately aftwerward while the dynamic arguments are passed via the operation stack.
## Bytecode set
The complete set of instructions is defined in __"opcodes.hpp"__, and contains:
### Push operations
 - push_byte_{b}, n: pushes __function stack__ local word n byte b [0, 3] to the __operation stack__
 - push_hword_{h}, n: pushes __function stack__ local word n half word h {0, 2} to the __operation stack__
 - push_word_{w}: pushes __function stack__ local word w [0, 4] to the __operation stack__
 - push_word, n: pushes __function stack__ local word n [0, 255] to the __operation stack__
 - push_dword_d: pushes __function stack__ local double word starting from position d [0, 4] to the __operation stack__
 - push_dword, n: pushes __function stack__ local double word starting from position n [0, 254] to the __operation stack__
 - push_words, l, n: pushes __function stack__ n [0, 255] words from local word l [0, 255 - n] to the __operation stack__
 - push_word_value_0: pushes to the __operation stack__ the value __0x00000000__
 - push_dword_value_0: pushes to the __operation stack__ the value __0x0000000000000000__
 - push_i8_as_i32, v: pushes v [0, 255] casted to a __i32__ to the __operation stack__ 
 - push_i8_as_i64, v: pushes v [0, 255] casted to a __i64__ to the __operation stack__
 - push_i32_1: pushes to the __operation stack__ the i32 value 1
 - push_i32_2: pushes to the __operation stack__ the i32 value 2
 - push_i64_1: pushes to the __operation stack__ the i64 value 1
 - push_i64_2: pushes to the __operation stack__ the i64 value 2
 - push_f32_1: pushes to the __operation stack__ the f32 value 1
 - push_f32_2: pushes to the __operation stack__ the f32 value 2
 - push_f64_1: pushes to the __operation stack__ the f64 value 1
 - push_f64_2: pushes to the __operation stack__ the f64 value 2
 - get_address, l: pushes to the __operation stack__ the dword pointer of the __function stack__ local word l [0, 255]

### Pop operations
 - pop_byte_{b}, n: pops to __function stack__ local word n byte b [0, 3] from __operation stack__
 - pop_hword_{h}, n: pops to __function stack__ local word n half word h {0, 2} from __operation stack__
 - pop_word_{w}: pops to __function stack__ local word w [0, 4] from __operation stack__
 - pop_word, n: pops to __function stack__ local word n [0, 255] from __operation stack__
 - pop_dword_{d}: pops to __function stack__ local double word starting from position d [0, 4] from __operation stack__
 - pop_dword, n: pops to __function stack__ local double word starting from position n [0, 254] from __operation stack__
 - pop_words, l, n: pops to __function stack__ local word l [0, 255 - n] n [0, 255] words from __operation stack__
  
### Operation stack manipulation operations
 - dup_word: duplicates the word on top of the __operation stack__
 - dup_word_x1: duplicates the word on top of the __operation stack__ and moves the original one word down
 - dup_word_x2: duplicates the word on top of the __operation stack__ and moves the original two words down
 - dup_dword: duplicates the two words on top of the __operation stack__
 - dup_dword_x1: duplicates the two words on top of the __operation stack__ and moves the originals one word down
 - dup_dword_x2: duplicates the two words on top of the __operation stack__ and moves the originals two words down
 - swap_word: swaps the two words on top of the __operation stack__
 - swap_dword: swaps the two top word pairs of the __operation stack__

### Memory access operations
 - load_byte_{b}: pops from the __operation stack__ a dword pointer __P__ and pushes a word containing the byte __b__ [0, 3] of the word pointed by __P__
 - load_hword_{h}: pops from the __operation stack__ a dword pointer __P__ and pushes a word containing the half word __h__ {0, 2} of the word pointed by __P__
 - load_word: pops from the __operation stack__ a dword pointer __P__ and pushes the word pointed by __P__
 - load_dword: pops from the __operation stack__ a dword pointer __P__ and pushes the dword pointed by __P__
 - store_byte_{b}: pops from the __operation stack__ a dword pointer __P__ and a word value __V__ and set the byte __b__ [0, 3] of the word pointed by __P__ to __V__
 - store_hword_{h}: pops from the __operation stack__ a dword pointer __P__ and a word value __V__ and set the hword __h__ {0, 2} of the word pointed by __P__ to __V__
 - store_word: pops from the __operation stack__ a dword pointer __P__ and a word value __V__ and set the word pointed by __P__ to __V__
 - store_dword: pops from the __operation stack__ a dword pointer __P__ and a dword value __V__ and set the dword pointed by __P__ to __V__

### Arithmetic operations
 - add_{t}32: pops from the __operation stack__ the top two words interpreted as __t__ {i, f} and pushes their sum
 - add_{t}64: pops from the __operation stack__ the top two word pairs interpreted as __t__ {i, f} and pushes their sum
 - sub_{t}32: pops from the __operation stack__ the top two words interpreted as __t__ {i, f} and pushes their difference
 - sub_{t}64: pops from the __operation stack__ the top two word pairs interpreted as __t__ {i, f} and pushes their difference
 - mul_{t}32: pops from the __operation stack__ the top two words interpreted as __t__ {i, f} and pushes their product
 - mul_{t}64: pops from the __operation stack__ the top two word pairs interpreted as __t__ {i, f} and pushes their product
 - div_{t}32: pops from the __operation stack__ the top two words interpreted as __t__ {i, f} and pushes their quotient
 - div_{t}64: pops from the __operation stack__ the top two word pairs interpreted as __t__ {i, f} and pushes their quotient
 - inc_{t}32, l: increments by one the __function stack__ local word __l__ [0, 255]
 - inc_{t}64, l: increments by one the __function stack__ local dword __l__ [0, 254]
 - dec_{t}32, l: decrements by one the __function stack__ local word __l__ [0, 255]
 - dec_{t}64, l: decrements by one the __function stack__ local dword __l__ [0, 254]
 - mod_{t}32: pops from the __operation stack__ the top two words interpreted as __t__ {i, u, f} and pushes the remainder
 - mod_{t}64: pops from the __operation stack__ the top two word pairs interpreted as __t__ {i, u, f} and pushes the remainder
 - neg_{t}32: pops from the __operation stack__ the top word interpreted as __t__ {i, f} and pushes its negative
 - neg_{t}64: pops from the __operation stack__ the top word pair interpreted as __t__ {i, f} and pushes its negative

### Bitwise operations
 - and_word: pops from the __operation stack__ the top two words and pushes the bitwise __AND__ result
 - and_dword: pops from the __operation stack__ the top two word pairs and pushes the bitwise __AND__ result 
 - or_word: pops from the __operation stack__ the top two words and pushes the bitwise __OR__ result 
 - or_dword: pops from the __operation stack__ the top two word pairs and pushes the bitwise __OR__ result 
 - xor_word: pops from the __operation stack__ the top two words and pushes the bitwise __XOR__ result 
 - xor_dword: pops from the __operation stack__ the top two word pairs and pushes the bitwise __XOR__ result
 - not_word: pops from the __operation stack__ the top word and pushes the bitwise __NOT__ result
 - not_dword: pops from the __operation stack__ the top word pair and pushes the bitwise __NOT__ result
 - shl_word: pops from the __operation stack__ a word value __S__ and __V__ and pushes __V__ shifted left by __S__
 - shl_dword: pops from the __operation stack__ a word value __S__ and a dword value __V__ and pushes __V__ shifted left by __S__
 - shr_{t}32: pops from the __operation stack__ a word value __S__ and a word value __V__ interpreted as __t__ {u, i} and pushes __V__ shifted right by __S__
 - shr_{t}64: pops from the __operation stack__ a word value __S__ and a dword value __V__ interpreted as __t__ {u, i} and pushes __V__ shifted right by __S__

### Jump operations
 - jmp, o: jumps by  __o__ [-32768, 32767] instructions
 - jmp_{t}32_{c}, o: jumps by __o__ [-32768, 32767] instructions if the condition __c__ {eq, ne, lt, gt, le, ge} is satisfied by the top two words of the __operation stack__ interpreted as t {i, u, f}

Note: The __ne__ and __eq__ comparison between __u__ values is equivalent to comparison between __i__ values so for example __jmp_u32_eq__ does not exist.

### Function call and return
 - call, f: looks at the functions table at index __f__ [0, 65535] and opens a new stack frame on the __function stack__ of __N__ words defined by the function local words count, and pops __K__ words defined by the function input parameters from the __operation stack__ and inserts them in the __function stack__ from local word 0
 - syscall, f: calls a virtual machine system call pointed by the index __f__ [0, 255]
 - return_void: pops the scope of the __function stack__ and restores the previous __operation stack__ scope
 - return_byte: pops the scope of the __function stack__ and restores the previous __operation stack__ scope pushing the top word as byte from the previous frame
 - return_hword: pops the scope of the __function stack__ and restores the previous __operation stack__ scope pushing the top word hword from the previous frame
 - return_word: pops the scope of the __function stack__ and restores the previous __operation stack__ scope pushing the top word hword from the previous frame
 - return_dword: pops the scope of the __function stack__ and restores the previous __operation stack__ scope pushing the top word pair from the previous frame
 - return_words, n: pops the scope of the __function stack__ and restores the previous __operation stack__ scope pushing the top __n__ [0, 255] words from the previous frame

#### System call codes 
       0 (Print): prints a string
       1 (PrintI64): prints an i64 value
       2 (PrintF64): prints an f64 value
       3 (SqrtF32): returns the square root of an f32 value
       4 (SqrtF64): returns the square root of an f64 value

### Cast operations
 - {tA}{bA}_to_{tB}{bB}: casts the top word/dword value of the __operation stack__ interpreted as __tA__ {i, f} of bA {32, 64} bits to a __tB__ {i, f} to __bB__ {32, 64} bits

# BCC
bcc is a simple bytecode compiler it gets as input a text file and translates it to a bytecode binary file.

## Definitions
In bcc every word that starts with a dot (.) represent a definition. 
Definitions can be of two types:
 - __constant definition__
 - __function definition__

### Constant definitions
A constant definition is written like this : ```.<type> <name> <value>```

#### Type
Type must be one of the following
 - i32
 - i64
 - u32
 - u64
 - f32
 - f64
#### Name
Name must not have spaces and cannot be the same for constants of the same size, for example an i32 and an f32 cannot have the same name.
#### Value
Value must be valid, an u32 cannot have a negative value assigned, ecc. This could cause the compiler to crash (will be fixed next)

### Function definitions
A function definition is the written like this : 
```
.func <name> <arg word count> <local word count>
...
#function body
...
```

#### Name
Name must not have spaces and cannot be tha same of other functions

#### Arg word count
Arguments word count or __AWC__ is che number of words of the function parameters, for example ```i64 func(i64 d, i32 w)``` has an __AWC__ of __3__

#### Local word count
Local word count or __LWC__ is the total number of words that the function scope require plus the argument parameters, for example
```
i32 func(i32 a, i32 b)
{
    i32 c;
}
```
This function has an __LWC__ of 3

## Instructions
The compiler will compile all the lines after the function definition until a new type of definition is reached
```
.func func_a 0 1
...
#body
...
.func func_b 2 3 <--- stops compiling func_b
...
```
evry line is translated as a single bytecode instruction.
## Instruction set
### Push
A push instruction can is written as ```push <push variant> <push variant args...>```
Push variants are:
 - local
 - const
 - as
 - ref
#### Push local
A push local instruction translates to a push from __function stack__ local word to __operation stack__, it has the following syntax : 
``` 
push local <type> <local>
```






   






