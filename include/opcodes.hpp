#pragma once

#include "types.hpp"

#define WORDv(b3, b2, b1, b0) (u8)(b0), (u8)(b1), (u8)(b2), (u8)(b3)
#define DWORDv(b7, b6, b5, b4, b3, b2, b1, b0) (u8)(b0), (u8)(b1), (u8)(b2), (u8)(b3), (u8)(b4), (u8)(b5), (u8)(b6), (u8)(b7)
#define HALFv(b1, b0) (u8)(b0), (u8)(b1)
#define BYTEv(b0) (u8)(b0)

#define I32v(v) WORDv(v >> 24, v >> 16, v >> 8, v)
#define I64v(v) DWORDv(v >> 56, v >> 48, v >> 40, v >> 32, v >> 24, v >> 16, v >> 8, v)
#define I8v(v) BYTEv(v)
#define I16v(v) HALFv(v >> 8, v)
#define U8v(v) I8v(v)
#define U16v(v) I16v(v)
#define U32v(v) I32v(v)
#define U64v(v) I64v(v)

#define EOS() 0x00
#define STRb(c0) U8v(c0)
#define STRh(c0, c1) U8v(c0), U8v(c1)
#define STRw(c0, c1, c2, c3) U8v(c0), U8v(c1), U8v(c2), U8v(c3)
#define STRd(c0, c1, c2, c3, c4, c5, c6, c7) U8v(c0), U8v(c1), U8v(c2), U8v(c3), U8v(c4), U8v(c5), U8v(c6), U8v(c7)

typedef u8 opcode;

namespace OpCodes
{
	constexpr opcode exit = 0x00; // Exits the program

	// Stack operations

	constexpr opcode push_word    = 0x07; // Pushes FStack local word (u8 local) to OStack -> value
	constexpr opcode push_word_0  = 0x08; // Pushes FStack local word 0 to OStack -> value
	constexpr opcode push_word_1  = 0x09; // Pushes FStack local word 1 to OStack -> value
	constexpr opcode push_word_2  = 0x0A; // Pushes FStack local word 2 to OStack -> value
	constexpr opcode push_word_3  = 0x0B; // Pushes FStack local word 3 to OStack -> value
	constexpr opcode push_dword   = 0x0C; // Pushes FStack local dword (u8 local) to OStack -> { value_l, value_h }
	constexpr opcode push_dword_0 = 0x0D; // Pushes FStack local dword 0 to OStack -> { value_l, value_h }
	constexpr opcode push_dword_1 = 0x0E; // Pushes FStack local dword 1 to OStack -> { value_l, value_h }
	constexpr opcode push_dword_2 = 0x0F; // Pushes FStack local dword 2 to OStack -> { value_l, value_h }
	constexpr opcode push_dword_3 = 0x10; // Pushes FStack local dword 3 to OStack -> { value_l, value_h }
	constexpr opcode push_words   = 0x11;

	constexpr opcode push_word_value_0  = 0x12; // Pushes 0x00000000 to OStack
	constexpr opcode push_dword_value_0 = 0x13; // Pushes 0x0000000000000000 to OStack
	constexpr opcode push_i32_1   = 0x14; // Pushes 0x00000001 to OStack
	constexpr opcode push_i32_2   = 0x15; // Pushes 0x00000002 to OStack
	constexpr opcode push_i64_1   = 0x16; // Pushes 0x0000000000000001 to OStack
	constexpr opcode push_i64_2   = 0x17; // Pushes 0x0000000000000002 to OStack
	constexpr opcode push_f32_1   = 0x18; // Pushes 0x3F800000 (1.0f) to OStack
	constexpr opcode push_f32_2   = 0x19; // Pushes 0x40000000 (2.0f) to OStack
	constexpr opcode push_f64_1   = 0x1A; // Pushes 0x3FF0000000000000 (1.0) to OStack
	constexpr opcode push_f64_2   = 0x1B; // Pushes 0x4000000000000000 (2.0) to OStack

	constexpr opcode push_i8_as_i32             = 0x1C; // Pushes an i8 as an i32 (i8 value) to OStack -> value
	constexpr opcode push_i8_as_i64             = 0x1D; // Pushes an i8 as an i64 (i8 value) to OStack -> value
	constexpr opcode push_word_from_pool        = 0x1E; // Pushes a word from the word constant pool (u8 index) to OStack -> value
	constexpr opcode push_word_from_pool_wide   = 0x1F; // Pushes a word from the word constant pool (u16 index) to OStack -> value
	constexpr opcode push_dword_from_pool       = 0x20; // Pushes a dword from the dword constant pool (u8 index) to OStack -> { value_l, value_h }
	constexpr opcode push_dword_from_pool_wide  = 0x21; // Pushes a dword from the dword constant pool (u16 index) to OStack -> { value_l, value_h }
	constexpr opcode push_string_from_pool      = 0x22; // Pushes a string from the string constant pool (u8 index) to OStack -> { ptr_l, ptr_h }
	constexpr opcode push_string_from_pool_wide = 0x23; // Pushes a string from the string constant pool (u16 index) to OStack -> { ptr_l, ptr_h }

	constexpr opcode pop_word    = 0x2A; // Pops from OStack a word to FStack local word (u8 local) value ->
	constexpr opcode pop_word_0  = 0x2B; // Pops from OStack a word to FStack local word 0 value ->
	constexpr opcode pop_word_1  = 0x2C; // Pops from OStack a word to FStack local word 1 value ->
	constexpr opcode pop_word_2  = 0x2D; // Pops from OStack a word to FStack local word 2 value ->
	constexpr opcode pop_word_3  = 0x2E; // Pops from OStack a word to FStack local word 3 value ->
	
	constexpr opcode pop_dword   = 0x2F; // Pops from OStack a dword to FStack local dword (u8 local) { value_l, value_h } ->
	constexpr opcode pop_dword_0 = 0x30; // Pops from OStack a dword to FStack local dword 0 value ->
	constexpr opcode pop_dword_1 = 0x31; // Pops from OStack a dword to FStack local dword 1 value ->
	constexpr opcode pop_dword_2 = 0x32; // Pops from OStack a dword to FStack local dword 2 value ->
	constexpr opcode pop_dword_3 = 0x33; // Pops from OStack a dword to FStack local dword 3 value ->

	constexpr opcode pop_words   = 0x34;

	
	constexpr opcode dup_word     = 0x35; // Duplicates the word on top of the OStack value -> value, value
	constexpr opcode dup_word_x1  = 0x36; // Duplicates the word on top of the OStack and moves it one down value_0, value_1 -> value_1, value_0, value_1
	constexpr opcode dup_word_x2  = 0x37; // Duplicates the word on top of the OStack and moves it two down value_0, value_1, value_2 -> value_2, value_0, value_1, value_2
	constexpr opcode dup_dword    = 0x38; // Duplicates the dword on top of the OStack { value_l, value_h } -> { value_l, value_h }, { value_l, value_h }
	constexpr opcode dup_dword_x1 = 0x39; // Duplicates the dword on top of the OStack and moves it one down value_0, { value_1, value_2 } -> { value_1, value_2 }, value_0, { value_1, value_2 } 
	constexpr opcode dup_dword_x2 = 0x3A; // Duplicates the dword on top of the OStack and moves it two down value_0, value_1, { value_2, value_3 } -> { value_2, value_3 }, value_0, value_1, { value_2, value_3 }
	constexpr opcode swap_word    = 0x3B; // Swaps the two words on top of the OStack value_0, value_1 -> value_1, value_0
	constexpr opcode swap_dword   = 0x3C; // Swaps the two dwords on top of the OStack { value_0l, value_0h }, { value_1l, value_1h } -> { value_1l, value_1h }, { value_0l, value_0h }

	// Memory operations

	constexpr opcode get_address = 0x3D; // Pushes on the OStack the address of FStack local var (u8 local) -> { ptr_l, ptr_h }

	constexpr opcode load_byte_0  = 0x3E; // Loads byte 0 of the word pointed by OStack top dword.
	constexpr opcode load_byte_1  = 0x3F; // Loads byte 1 of the word pointed by OStack top dword.
	constexpr opcode load_byte_2  = 0x40; // Loads byte 2 of the word pointed by OStack top dword.
	constexpr opcode load_byte_3  = 0x41; // Loads byte 3 of the word pointed by OStack top dword.
	constexpr opcode load_hword_0 = 0x42; // Loads hword 0 of the word pointed by OStack top dword.
	constexpr opcode load_hword_2 = 0x43; // Loads hword 2 of the word pointed by OStack top dword.
	constexpr opcode load_word    = 0x44; // Loads word pointed by OStack top dword.
	constexpr opcode load_dword   = 0x45; // Loads dword pointed by OStack top dword.

	constexpr opcode store_byte_0  = 0x46; // Stores byte 0 of the word pointed by OStack top dword. { ptr_l , ptr_h }, value -> 
	constexpr opcode store_byte_1  = 0x47; // Stores byte 1 of the word pointed by OStack top dword. { ptr_l , ptr_h }, value ->
	constexpr opcode store_byte_2  = 0x48; // Stores byte 2 of the word pointed by OStack top dword. { ptr_l , ptr_h }, value ->
	constexpr opcode store_byte_3  = 0x49; // Stores byte 3 of the word pointed by OStack top dword. { ptr_l , ptr_h }, value ->
	constexpr opcode store_hword_0 = 0x4A; // Stores hword 0 of the word pointed by OStack top dword. { ptr_l , ptr_h }, value ->
	constexpr opcode store_hword_2 = 0x4B; // Stores hword 2 of the word pointed by OStack top dword. { ptr_l , ptr_h }, value ->
	constexpr opcode store_word    = 0x4C; // Stores word pointed by OStack top dword. { ptr_l , ptr_h }, value ->
	constexpr opcode store_dword   = 0x4D; // Stores dword pointed by OStack top dword. { ptr_l , ptr_h }, { value_l, value_h } ->

	// Arithmetic operations

	constexpr opcode add_i32 = 0x4E; // Adds two i32 values from OStack value0, value1 -> result
	constexpr opcode add_i64 = 0x4F; // Adds two i64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode add_f32 = 0x50; // Adds two f32 values from OStack value0, value1 -> result
	constexpr opcode add_f64 = 0x51; // Adds two f64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode inc_i32 = 0x52; // Increment by one an the i32 value from FStack local word (u8 local) -> value
	constexpr opcode inc_i64 = 0x53; // Increment by one an the i64 value from FStack local dword (u8 local) -> { value_l, value_h }
	constexpr opcode inc_f32 = 0x54; // Increment by one an the f32 value from FStack local word (u8 local) -> value
	constexpr opcode inc_f64 = 0x55; // Increment by one an the f64 value from FStack local dword (u8 local) -> { value_l, value_h }

	constexpr opcode sub_i32 = 0x56; // Subtracts two i32 values from OStack value0, value1 -> result
	constexpr opcode sub_i64 = 0x57; // Subtracts two i64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode sub_f32 = 0x58; // Subtracts two f32 values from OStack value0, value1 -> result
	constexpr opcode sub_f64 = 0x59; // Subtracts two f64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode dec_i32 = 0x5A; // Decrement by one an the i32 value from FStack local word (u8 local) -> value
	constexpr opcode dec_i64 = 0x5B; // Decrement by one an the i64 value from FStack local dword (u8 local) -> { value_l, value_h }
	constexpr opcode dec_f32 = 0x5C; // Decrement by one an the f32 value from FStack local word (u8 local) -> value
	constexpr opcode dec_f64 = 0x5D; // Decrement by one an the f64 value from FStack local dword (u8 local) -> { value_l, value_h }

	constexpr opcode mul_i32 = 0x5E; // Multiplies two i32 values from OStack value0, value1 -> result
	constexpr opcode mul_i64 = 0x5F; // Multiplies two i64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode mul_u32 = 0x60; // Multiplies two u32 values from OStack value0, value1 -> result
	constexpr opcode mul_u64 = 0x61; // Multiplies two u64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode mul_f32 = 0x62; // Multiplies two f32 values from OStack value0, value1 -> result
	constexpr opcode mul_f64 = 0x63; // Multiplies two f64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode div_i32 = 0x64; // Divides two i32 values from OStack value0, value1 -> result
	constexpr opcode div_i64 = 0x65; // Divides two i64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode div_u32 = 0x66; // Divides two u32 values from OStack value0, value1 -> result
	constexpr opcode div_u64 = 0x67; // Divides two u64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h } 
	constexpr opcode div_f32 = 0x68; // Divides two f32 values from OStack value0, value1 -> result
	constexpr opcode div_f64 = 0x69; // Divides two f64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }

	constexpr opcode mod_i32 = 0x6A; // Modulus of two i32 values from OStack value0, value1 -> result
	constexpr opcode mod_i64 = 0x6B; // Modulus of two i64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode mod_u32 = 0x6C; // Modulus of two u32 values from OStack value0, value1 -> result
	constexpr opcode mod_u64 = 0x6D; // Modulus of two u64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode mod_f32 = 0x6E; // Modulus of two f32 values from OStack value0, value1 -> result
	constexpr opcode mod_f64 = 0x6F; // Modulus of two f64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }

	constexpr opcode neg_i32 = 0x70; // Negates the i32 value from FStack local word (u8 local) -> value
	constexpr opcode neg_i64 = 0x71; // Negates the i64 value from FStack local dword (u8 local) -> { value_l, value_h }
	constexpr opcode neg_f32 = 0x72; // Negates the f32 value from FStack local word (u8 local) -> value
	constexpr opcode neg_f64 = 0x73; // Negates the f64 value from FStack local dword (u8 local) -> { value_l, value_h }

	// Bitwise operations

	constexpr opcode and_word  = 0x74; // Bitwise AND two words from OStack value0, value1 -> result
	constexpr opcode and_dword = 0x75; // Bitwise AND two dwords from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }

	constexpr opcode or_word  = 0x76; // Bitwise OR two words from OStack value0, value1 -> result
	constexpr opcode or_dword = 0x77; // Bitwise OR two dwords from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }

	constexpr opcode xor_word  = 0x78; // Bitwise XOR two words from OStack value0, value1 -> result
	constexpr opcode xor_dword = 0x79; // Bitwise XOR two dwords from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }

	constexpr opcode not_word  = 0x7A; // Bitwise NOT a word from OStack value -> result
	constexpr opcode not_dword = 0x7B; // Bitwise NOT a dword from OStack { value_l, value_h } -> { result_l, result_h }

	constexpr opcode shl_word  = 0x7C; // Shift left a word from OStack value, shift -> result
	constexpr opcode shl_dword = 0x7D; // Shift left a dword from OStack { value_l, value_h }, shift -> { result_l, result_h }

	constexpr opcode shr_i32 = 0x7E; // Shift right an i32 value from OStack value, shift -> result
	constexpr opcode shr_i64 = 0x7F; // Shift right an i64 value from OStack { value_l, value_h }, shift -> { result_l, result_h }
	constexpr opcode shr_u32 = 0x80; // Shift right an u32 value from OStack value, shift -> result
	constexpr opcode shr_u64 = 0x81; // Shift right an u64 value from OStack { value_l, value_h }, shift -> { result_l, result_h }

	// Jump operations

	constexpr opcode cmp_word_eq  = 0x82; // Pops two words from OStack and pushes the result of the equal comparison value0, value1  -> value0 == value1
	constexpr opcode cmp_dword_eq = 0x83; // Pops two dwords from OStack and pushes the result of the equal comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 == value1
	constexpr opcode cmp_word_ne  = 0x84; // Pops two words from OStack and pushes the result of the not equal comparison value0, value1  -> value0 != value1
	constexpr opcode cmp_dword_ne = 0x85; // Pops two dwords from OStack and pushes the result of the not equal comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 != value1

	constexpr opcode cmp_i32_lt = 0x86; // Pops two i32 values from OStack and pushes the result of the lower than comparison value0, value1  -> value0 < value1
	constexpr opcode cmp_i32_gt = 0x87; // Pops two i32 values from OStack and pushes the result of the greater than comparison value0, value1  -> value0 > value1
	constexpr opcode cmp_i32_le = 0x88; // Pops two i32 values from OStack and pushes the result of the lower than or equal comparison value0, value1  -> value0 <= value1
	constexpr opcode cmp_i32_ge = 0x89; // Pops two i32 values from OStack and pushes the result of the greater than or equal comparison value0, value1  -> value0 >= value1
	
	constexpr opcode cmp_i64_lt = 0x8A; // Pops two i64 values from OStack and pushes the result of the lower than comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 < value1
	constexpr opcode cmp_i64_gt = 0x8B; // Pops two i64 values from OStack and pushes the result of the greater than comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 > value1
	constexpr opcode cmp_i64_le = 0x8C; // Pops two i64 values from OStack and pushes the result of the lower than or equal comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 <= value1
	constexpr opcode cmp_i64_ge = 0x8D; // Pops two i64 values from OStack and pushes the result of the greater than or equal comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 >= value1

	constexpr opcode cmp_f32_lt = 0x8E; // Pops two f32 values from OStack and pushes the result of the lower than comparison value0, value1  -> value0 < value1
	constexpr opcode cmp_f32_gt = 0x8F; // Pops two f32 values from OStack and pushes the result of the greater than comparison value0, value1  -> value0 > value1
	constexpr opcode cmp_f32_le = 0x90; // Pops two f32 values from OStack and pushes the result of the lower than or equal comparison value0, value1  -> value0 < value1
	constexpr opcode cmp_f32_ge = 0x91; // Pops two f32 values from OStack and pushes the result of the greater than or equal comparison value0, value1  -> value0 >= value1
	
	constexpr opcode cmp_f64_lt = 0x92; // Pops two f64 values from OStack and pushes the result of the lower than comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 < value1
	constexpr opcode cmp_f64_gt = 0x93; // Pops two f64 values from OStack and pushes the result of the greater than comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 > value1
	constexpr opcode cmp_f64_le = 0x94; // Pops two f64 values from OStack and pushes the result of the lower than or equal comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 <= value1
	constexpr opcode cmp_f64_ge = 0x95; // Pops two f64 values from OStack and pushes the result of the greater than or equal comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 >= value1

	constexpr opcode cmp_u32_lt = 0x96; // Pops two u32 values from OStack and pushes the result of the lower than comparison value0, value1  -> value0 < value1
	constexpr opcode cmp_u32_gt = 0x97; // Pops two u32 values from OStack and pushes the result of the greater than comparison value0, value1  -> value0 > value1
	constexpr opcode cmp_u32_le = 0x98; // Pops two u32 values from OStack and pushes the result of the lower than or equal comparison value0, value1  -> value0 <= value1
	constexpr opcode cmp_u32_ge = 0x99; // Pops two u32 values from OStack and pushes the result of the greater than or equal comparison value0, value1  -> value0 >= value1
	
	constexpr opcode cmp_u64_lt = 0x9A; // Pops two u64 values from OStack and pushes the result of the lower than comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 < value1
	constexpr opcode cmp_u64_gt = 0x9B; // Pops two u64 values from OStack and pushes the result of the greater than comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 > value1
	constexpr opcode cmp_u64_le = 0x9C; // Pops two u64 values from OStack and pushes the result of the lower than or equal comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 <= value1
	constexpr opcode cmp_u64_ge = 0x9D; // Pops two u64 values from OStack and pushes the result of the greater than or equal comparison { value0_l, value0_h }, { value1_l, value1_h } -> value0 >= value1

	constexpr opcode jmp_if     = 0x9E; // Pops a word from OStack and jumps by a signed offset (i16 offset) if the value is true value ->
	constexpr opcode jmp        = 0x9F; // Jumps by a signed offset (i16 offset)

	// Call operations

	constexpr opcode call         = 0xA3; // Calls a function (u8 index)
	constexpr opcode call_ext     = 0xA4; // Not implemented!
	constexpr opcode syscall      = 0xA5; // Calls a c++ function (u8 index)
	constexpr opcode return_void  = 0xA6; // Returns from a function
	constexpr opcode return_word  = 0xA7; // Returns a word from a function value_0, value_1, ..., value_n -> return_value
	constexpr opcode return_dword = 0xA8; // Returns a dword from a function value_0, value_1, ..., value_n -> return_value
	constexpr opcode return_words = 0xA9; // Returns n words from a function value_0, value_1, ..., value_n -> return_value_0, return_value_1, ..., return_value_n

	// Type conversion operations
	constexpr opcode i32_to_i8  = 0xAA;
	constexpr opcode i32_to_i16 = 0xAB;
	constexpr opcode i32_to_i64 = 0xAC; // Converts an i32 value from OStack to an i64 value value -> { value, 0 }
	constexpr opcode i32_to_f32 = 0xAD; // Converts an i32 value from OStack to an f32 value value -> result
	constexpr opcode i32_to_f64 = 0xAE; // Converts an i32 value from OStack to an f64 value value -> { result_l, result_h }
	constexpr opcode i64_to_i32 = 0xAF; // Converts an i64 value from OStack to an i32 value { value_l, value_h } -> value
	constexpr opcode i64_to_f32 = 0xB0; // Converts an i64 value from OStack to an f32 value { value_l, value_h } -> result
	constexpr opcode i64_to_f64 = 0xB1; // Converts an i64 value from OStack to an f64 value { value_l, value_h } -> { result_l, result_h }
	constexpr opcode f32_to_i32 = 0xB2; // Converts an f32 value from OStack to an i32 value value -> result
	constexpr opcode f32_to_i64 = 0xB3; // Converts an f32 value from OStack to an i64 value value -> { result_l, result_h }
	constexpr opcode f32_to_f64 = 0xB4; // Converts an f32 value from OStack to an f64 value value -> { value, 0 }
	constexpr opcode f64_to_i32 = 0xB5; // Converts an f64 value from OStack to an i32 value { value_l, value_h } -> result
	constexpr opcode f64_to_i64 = 0xB6; // Converts an f64 value from OStack to an i64 value { value_l, value_h } -> { result_l, result_h }
	constexpr opcode f64_to_f32 = 0xB7; // Converts an f64 value from OStack to an f32 value { value_l, value_h } -> result

	constexpr opcode alloc    = 0xB8; // Allocates a new buffer bytes -> { ptr_l, ptr_h }
	constexpr opcode free     = 0xB9; // Deallocates a buffer { ptr_l, ptr_h } ->

	constexpr opcode load_words  = 0xBA; // Loads n words (u8) from the buffer pointed by OStack top dword { ptr_l, ptr_h } -> { value_0, value_1, ..., value_n }
	constexpr opcode store_words = 0xBB; // Stores n words (u8) to the buffer pointed by OStack top dword { ptr_l, ptr_h }, { value_0, value_1, ..., value_n } ->

	constexpr opcode load_buffer_byte_val = 0xBC;
	constexpr opcode load_buffer_hword_val = 0xBD;
	constexpr opcode load_buffer_word_val = 0xBE;
	constexpr opcode load_buffer_dword_val = 0xBF;
	constexpr opcode load_buffer_words_val = 0xC0;

	constexpr opcode load_buffer_byte_ref = 0xC1;
	constexpr opcode load_buffer_hword_ref = 0xC2;
	constexpr opcode load_buffer_word_ref = 0xC3;
	constexpr opcode load_buffer_dword_ref = 0xC4;
	constexpr opcode load_buffer_words_ref = 0xC5;

	constexpr opcode store_buffer_byte = 0xC6;
	constexpr opcode store_buffer_hword = 0xC7;
	constexpr opcode store_buffer_word = 0xC8;
	constexpr opcode store_buffer_dword = 0xC9;
	constexpr opcode store_buffer_words = 0xCA;

	constexpr opcode load_offset_byte_0 = 0xCB; // Pushes to OStack the byte 0 of the word pointed by OStack top dword offsetted by offset (u8) { ptr_l, ptr_h } -> value
	constexpr opcode load_offset_byte_1 = 0xCC;
	constexpr opcode load_offset_byte_2 = 0xCD;
	constexpr opcode load_offset_byte_3 = 0xCE;
	constexpr opcode load_offset_hword_0 = 0xCF;
	constexpr opcode load_offset_hword_2 = 0xD0;
	constexpr opcode load_offset_word = 0xD1;
	constexpr opcode load_offset_dword = 0xD2;
	constexpr opcode load_offset_words = 0xD3;

	constexpr opcode store_offset_byte_0 = 0xD4;
	constexpr opcode store_offset_byte_1 = 0xD5;
	constexpr opcode store_offset_byte_2 = 0xD6;
	constexpr opcode store_offset_byte_3 = 0xD7;
	constexpr opcode store_offset_hword_0 = 0xD8;
	constexpr opcode store_offset_hword_2 = 0xD9;
	constexpr opcode store_offset_word = 0xDA;
	constexpr opcode store_offset_dword = 0xDB;
	constexpr opcode store_offset_words = 0xDC;

	namespace Syscall
	{
		constexpr opcode Print    = 0x01; // Prints a string
		constexpr opcode PrintI64 = 0x02; // Prints an i64 value
		constexpr opcode PrintF64 = 0x03; // Prints an f64 value
		constexpr opcode SqrtF32  = 0x04; // Calculates the square root of an f32 value
		constexpr opcode SqrtF64  = 0x05; // Calculates the square root of an f64 value
		constexpr opcode Scan     = 0x06; // Get a line from console
		constexpr opcode ScanI64  = 0x07; // Get an int from console
		constexpr opcode ScanF64  = 0x08; // Get a float from console
		constexpr opcode MemCopy  = 0x09; // Copy N bytes from dest to source MemCopy(dest, src, n)
		constexpr opcode NanoTime     = 0x0A; // Get current time in nanoseconds 
	}
}