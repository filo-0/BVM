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
 - ```i32```
 - ```i64```
 - ```u32```
 - ```u64```
 - ```f32```
 - ```f64```

#### Naming
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

#### Naming
Name must not have spaces and cannot be tha same of other functions

#### Arg word count
Arguments word count or __AWC__ is che number of words of the function parameters, for example ```i64 func(i64 d, i32 w)``` has an __AWC__ of __3__

#### Local word count
Local word count or __LWC__ is the total number of words that the function scope require plus the argument parameters, for example
```
i32 func(i32 a, i32 b)
    i32 c
```
This function has an __LWC__ of 3

## Instructions
The compiler will compile all the lines after the function definition until a new type of definition is reached
```
.func func_a 0 1
...
.func func_b 2 3 <--- stops compiling func_a
...
```
every line is translated as a single bytecode instruction.

# Instruction set
## Push and pop
### Push
A push instruction has 4 variants :
 - ```push local```
 - ```push const```
 - ```push as```
 - ```push ref```

#### Push local
```
push local <t> <b*> <l> <n*>
```
 - ```t``` is the value type {byte, hword, word, dword, words}
 - ```b``` is the byte index to start from, it's needed by ```push local byte``` [0, 3] and ```push local hword``` {0, 2}
 - ```l``` is the ___function stack___ local word index [0, 255]
 - ```n``` is the word count needed by ```push local words``` [0, 255 - l]

#### Push const
```
push const <t> <s>
```
 - ```t``` is the value type {word, dword}
 - ```s``` is the variable name

#### Push as
```
push as <t> <v>
```
 - ```t``` is the value type {i32, i64, f32, f64}
 - ```v``` is the value to be pushed as t
##### v
 - if ```t == i32``` [-128, 127]
 - if ```t == i64``` [-128, 127]
 - if ```t == f32``` {0, 1, 2}
 - if ```t == f64``` {0, 1, 2}

#### Push ref
```
push ref <l>
```
 - ```l``` is the ___function stack___ local word to reference

### Pop
```
pop <t> <b*> <l> <n*>
```
 - ```t``` is the value type {byte, hword, word, dword, words}
 - ```b``` is the byte index to start from, it's needed by ```pop byte``` [0, 3] and ```pop hword``` {0, 2}
 - ```l``` is the ___function stack___ local word index [0, 255]
 - ```n``` is the word count needed by ```pop words``` [0, 255 - l]

## Operation stack manipulation
### Dup
```
dup <x*> <t>
```
 - ```x``` is the dup operation specifier {x1, x2}, if no ```x``` is written the operation is a simple dup
 - ```t``` is the value type to duplicate {word, dword}

### Swap
```
swap <t>
```
 - ```t``` is the value type of the swap operation {word, dword}

## Memory access
### Load
```
load <t> <b*>
```
 - ```t``` is the value type {byte, hword, word, dword}
 - ```b``` is the byte index to start from, it's needed by ```load byte``` [0, 3] and ```load hword``` {0, 2}

### Store
```
store <t> <b*>
```
 - ```t``` is the value type {byte, hword, word, dword}
 - ```b``` is the byte index to start from, it's needed by ```store byte``` [0, 3] and ```store hword``` {0, 2}

## Arithmetics

### Add
```
add <t>
```
 - ```t``` is the value type of the operands to add {i32, i64, f32, f64}

### Sub
```
sub <t>
```
 - ```t``` is the value type of the operands to subtract {i32, i64, f32, f64}

### Mul
```
mul <t>
```
 - ```t``` is the value type of the operands to multiply {i32, i64, u32, u64, f32, f64}

### Div
```
div <t>
```
 - ```t``` is the value type of the operands to divide {i32, i64, u32, u64, f32, f64}

### Mod
```
mod <t>
```
 - ```t``` is the value type of the operands to mod {i32, i64, u32, u64, f32, f64}

### Neg
```
neg <t>
```
 - ```t``` is the value type of the operands to negate {i32, i64, f32, f64}

### Inc
```
inc <t> <l>
```
 - ```t``` is the value type of the operand to increment
 - ```l``` is the index of the ___function stack___ local word {i32, i64, f32, f64}

### Dec
```
dec <t> <l>
```
 - ```t``` is the value type of the operand to decrement
 - ```l``` is the index of the ___function stack___ local word {i32, i64, f32, f64}

## Bitwise
### And
```
and <t>
```
 - ```t``` is the value type of the __AND__ operation {word, dword}

### Or
```
or <t>
```
 - ```t``` is the value type of the __OR__ operation {word, dword}

### Xor
```
xor <t>
```
 - ```t``` is the value type of the __XOR__ operation {word, dword}

### Not
```
not <t>
```
 - ```t``` is the value type of the __NOT__ operation {word, dword}

### Shl
```
shl <t>
```
 - ```t``` is the value type of the __SHIFT_LEFT__ operation {word, dword}

### Shr
```
shr <t>
```
 - ```t``` is the value type of the __SHIFT_RIGHT__ operation {i32, u32, i64, u64}

## Jumps
### Labels
Labels are not instructions, they are code pivot used by jump instructions.
A label is local to a function so a jump cannot be made to a label inside another function.
```
label <s>
```
 - ```s``` is the name of the label

### Unconditional jump
```
jump <o>
```
 - ```l``` is the label to jump to

### Conditional jump
```
jump <c> <t> <l>
```
 - ```c``` is the condition {eq, ne, lt, gt, le, ge}
 - ```t``` is the comparison value type {i32, i64, u32, u64, f32, f64}
 - ```l``` is the label to jump to

## Casts
```
cast <t> <g>
```
 - ```t``` is the value to cast from {i32, i64, u32, u64, f32, f64}
 - ```g``` is the value to cast to {i32, i64, u32, u64, f32, f64}
```t``` must be not the same of ```g```.

## Function call and return
### Call
```
call <s>
```
 - ```s``` is the name of the function to call

### Syscall
```
syscall <s>
```
 - ```s``` is the name of the vm system call to make

```s``` can have the following values
 - ```Print```
 - ```PrintI64```
 - ```PrintF64```
 - ```SqrtF32```
 - ```SqrtF64```
 
### Return 
```
return <t*>
```
 - ```t``` is the return type {byte, hword, word, dword, words} if no return type is set the operation is a ```return void```

# Code examples
Here are some code examples with their high level abstraction

## Integer power
```
.func pow 2 4
    push as i32 1
    pop word 2
    push as i32 0
    pop word 3
    jump for_check
label start_for
    push local word 2
    push local word 0
    mul i32
    pop word 2
    inc i32 3
label for_check
    push local word 3
    push local word 1
    jump lt i32 start_for
    push local word 2
return word

.func main 0 1
    push as i32 2
    push as i32 6
    call pow
    cast i32 i64
    syscall PrintI64
    return
```
```
i32 pow(i32 n, i32 p)
    i32 r = 1
    for(i32 i = 0, i < p, i++)
        r *= n
    return r

void main()
    PrintI64(pow(2, 6))
```

## Lerp
```
.f32 VALUE_0 100
.f32 VALUE_1 120
.f32 COEFFICIENT 0.3

.func lerp 3 3
    push local word 0
    push local word 1
    push local word 0
    sub f32 
    push local word 2
    mul f32
    add f32
    return word

.func main 0 1
    push const word VALUE_0
    push const word VALUE_1
    push const word COEFFICIENT
    call lerp
    pop word 0
    push local word 0
    cast f32 f64
    syscall PrintF64
    return
```
```
f32 lerp(f32 a, f32 b, f32 t)
    return a + (b - a) * t

void main()
    f32 mid = lerp(100, 120, 0.3)
    PrintF64(mid)
```