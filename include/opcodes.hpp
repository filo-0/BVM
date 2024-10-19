#pragma once

#include <vector>
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
#define STRw(c0, c1, c2, c3) U8v(c0), U8v(c1), U8v(c2), U8v(c3)


typedef u8 opcode;

namespace OpCodes
{
	constexpr opcode exit = 0x00; // Exits the program

	// Stack operations

	constexpr opcode push_byte_0  = 0x01; // Pushes byte 0 of FStack local word (u8 local) to OStack  -> value 
	constexpr opcode push_byte_1  = 0x02; // Pushes byte 1 of FStack local word (u8 local) to OStack -> value
	constexpr opcode push_byte_2  = 0x03; // Pushes byte 2 of FStack local word (u8 local) to OStack -> value
	constexpr opcode push_byte_3  = 0x04; // Pushes byte 3 of FStack local word (u8 local) to OStack -> value
	constexpr opcode push_hword_0 = 0x05; // Pushes halfword 0 of FStack local word (u8 local) to OStack -> value
	constexpr opcode push_hword_2 = 0x06; // Pushes halfword 2 of FStack local word (u8 local) to OStack -> value
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
	constexpr opcode push_words   = 0x11; // Pushes FStack local words (u8 local, u8 count) -> { value_0, value_1, ..., value_n }

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

	constexpr opcode push_i8_as_i32            = 0x1C; // Pushes an i8 as an i32 (i8 value) to OStack -> value
	constexpr opcode push_i8_as_i64            = 0x1D; // Pushes an i8 as an i64 (i8 value) to OStack -> value
	constexpr opcode push_word_from_pool       = 0x1E; // Pushes a word from the word constant pool (u8 index) to OStack -> value
	constexpr opcode push_word_from_pool_wide  = 0x1F; // Pushes a word from the word constant pool (u16 index) to OStack -> value
	constexpr opcode push_dword_from_pool      = 0xAC; // Pushes a dword from the dword constant pool (u8 index) to OStack -> { value_l, value_h }
	constexpr opcode push_dword_from_pool_wide = 0x20; // Pushes a dword from the dword constant pool (u16 index) to OStack -> { value_l, value_h }

	constexpr opcode pop_byte_0  = 0x21; // Pops from OStack a word to byte 0 of FStack local word (u8 local) value -> 
	constexpr opcode pop_byte_1  = 0x22; // Pops from OStack a word to byte 1 of FStack local word (u8 local) value ->
	constexpr opcode pop_byte_2  = 0x23; // Pops from OStack a word to byte 2 of FStack local word (u8 local) value ->
	constexpr opcode pop_byte_3  = 0x24; // Pops from OStack a word to byte 3 of FStack local word (u8 local) value ->
	constexpr opcode pop_hword_0 = 0x25; // Pops from OStack a word to hword 0 of FStack local word (u8 local) value ->
	constexpr opcode pop_hword_2 = 0x26; // Pops from OStack a word to hword 2 of FStack local word (u8 local) value ->
	constexpr opcode pop_word    = 0x27; // Pops from OStack a word to FStack local word (u8 local) value ->
	constexpr opcode pop_word_0  = 0x28; // Pops from OStack a word to FStack local word 0 value ->
	constexpr opcode pop_word_1  = 0x29; // Pops from OStack a word to FStack local word 1 value ->
	constexpr opcode pop_word_2  = 0x2A; // Pops from OStack a word to FStack local word 2 value ->
	constexpr opcode pop_word_3  = 0x2B; // Pops from OStack a word to FStack local word 3 value ->
	constexpr opcode pop_dword   = 0x2C; // Pops from OStack a dword to FStack local dword (u8 local) { value_l, value_h } ->
	constexpr opcode pop_dword_0 = 0x2D; // Pops from OStack a dword to FStack local dword 0 value ->
	constexpr opcode pop_dword_1 = 0x2E; // Pops from OStack a dword to FStack local dword 1 value ->
	constexpr opcode pop_dword_2 = 0x2F; // Pops from OStack a dword to FStack local dword 2 value ->
	constexpr opcode pop_dword_3 = 0x30; // Pops from OStack a dword to FStack local dword 3 value ->
	constexpr opcode pop_words   = 0x31; // Pops from OStack n words to FStack local word (u8 local, u8 count) { value_0, value_1, ..., value_n } ->

	constexpr opcode dup_word     = 0x32; // Duplicates the word on top of the OStack value -> value, value
	constexpr opcode dup_word_x1  = 0x33; // Duplicates the word on top of the OStack and moves it one down value_0, value_1 -> value_1, value_0, value_1
	constexpr opcode dup_word_x2  = 0x34; // Duplicates the word on top of the OStack and moves it two down value_0, value_1, value_2 -> value_2, value_0, value_1, value_2
	constexpr opcode dup_dword    = 0x35; // Duplicates the dword on top of the OStack { value_l, value_h } -> { value_l, value_h }, { value_l, value_h }
	constexpr opcode dup_dword_x1 = 0x36; // Duplicates the dword on top of the OStack and moves it one down value_0, { value_1, value_2 } -> { value_1, value_2 }, value_0, { value_1, value_2 } 
	constexpr opcode dup_dword_x2 = 0x37; // Duplicates the dword on top of the OStack and moves it two down value_0, value_1, { value_2, value_3 } -> { value_2, value_3 }, value_0, value_1, { value_2, value_3 }
	constexpr opcode swap_word    = 0x38; // Swaps the two words on top of the OStack value_0, value_1 -> value_1, value_0
	constexpr opcode swap_dword   = 0x39; // Swaps the two dwords on top of the OStack { value_0l, value_0h }, { value_1l, value_1h } -> { value_1l, value_1h }, { value_0l, value_0h }

	// Memory operations

	constexpr opcode get_address = 0x3A; // Pushes on the OStack the address of FStack local var (u8 local) -> { ptr_l, ptr_h }

	constexpr opcode load_byte_0  = 0x3B; // Loads byte 0 of the word pointed by OStack top dword.
	constexpr opcode load_byte_1  = 0x3C; // Loads byte 1 of the word pointed by OStack top dword.
	constexpr opcode load_byte_2  = 0x3D; // Loads byte 2 of the word pointed by OStack top dword.
	constexpr opcode load_byte_3  = 0x3E; // Loads byte 3 of the word pointed by OStack top dword.
	constexpr opcode load_hword_0 = 0x3F; // Loads hword 0 of the word pointed by OStack top dword.
	constexpr opcode load_hword_2 = 0x40; // Loads hword 2 of the word pointed by OStack top dword.
	constexpr opcode load_word    = 0x41; // Loads word pointed by OStack top dword.
	constexpr opcode load_dword   = 0x42; // Loads dword pointed by OStack top dword.

	constexpr opcode store_byte_0  = 0x43; // Stores byte 0 of the word pointed by OStack top dword. { ptr_l , ptr_h }, value -> 
	constexpr opcode store_byte_1  = 0x44; // Stores byte 1 of the word pointed by OStack top dword. { ptr_l , ptr_h }, value ->
	constexpr opcode store_byte_2  = 0x45; // Stores byte 2 of the word pointed by OStack top dword. { ptr_l , ptr_h }, value ->
	constexpr opcode store_byte_3  = 0x46; // Stores byte 3 of the word pointed by OStack top dword. { ptr_l , ptr_h }, value ->
	constexpr opcode store_hword_0 = 0x47; // Stores hword 0 of the word pointed by OStack top dword. { ptr_l , ptr_h }, value ->
	constexpr opcode store_hword_2 = 0x48; // Stores hword 2 of the word pointed by OStack top dword. { ptr_l , ptr_h }, value ->
	constexpr opcode store_word    = 0x49; // Stores word pointed by OStack top dword. { ptr_l , ptr_h }, value ->
	constexpr opcode store_dword   = 0x4A; // Stores dword pointed by OStack top dword. { ptr_l , ptr_h }, { value_l, value_h } ->

	// Arithmetic operations

	constexpr opcode add_i32 = 0x50; // Adds two i32 values from OStack value0, value1 -> result
	constexpr opcode add_i64 = 0x51; // Adds two i64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode add_f32 = 0x52; // Adds two f32 values from OStack value0, value1 -> result
	constexpr opcode add_f64 = 0x53; // Adds two f64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode inc_i32 = 0x54; // Increment by one an the i32 value from FStack local word (u8 local) -> value
	constexpr opcode inc_i64 = 0x55; // Increment by one an the i64 value from FStack local dword (u8 local) -> { value_l, value_h }
	constexpr opcode inc_f32 = 0x56; // Increment by one an the f32 value from FStack local word (u8 local) -> value
	constexpr opcode inc_f64 = 0x57; // Increment by one an the f64 value from FStack local dword (u8 local) -> { value_l, value_h }

	constexpr opcode sub_i32 = 0x58; // Subtracts two i32 values from OStack value0, value1 -> result
	constexpr opcode sub_i64 = 0x59; // Subtracts two i64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode sub_f32 = 0x5A; // Subtracts two f32 values from OStack value0, value1 -> result
	constexpr opcode sub_f64 = 0x5B; // Subtracts two f64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode dec_i32 = 0x5C; // Decrement by one an the i32 value from FStack local word (u8 local) -> value
	constexpr opcode dec_i64 = 0x5D; // Decrement by one an the i64 value from FStack local dword (u8 local) -> { value_l, value_h }
	constexpr opcode dec_f32 = 0x5E; // Decrement by one an the f32 value from FStack local word (u8 local) -> value
	constexpr opcode dec_f64 = 0x5F; // Decrement by one an the f64 value from FStack local dword (u8 local) -> { value_l, value_h }

	constexpr opcode mul_i32 = 0x60; // Multiplies two i32 values from OStack value0, value1 -> result
	constexpr opcode mul_i64 = 0x61; // Multiplies two i64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode mul_u32 = 0x62; // Multiplies two u32 values from OStack value0, value1 -> result
	constexpr opcode mul_u64 = 0x63; // Multiplies two u64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode mul_f32 = 0x64; // Multiplies two f32 values from OStack value0, value1 -> result
	constexpr opcode mul_f64 = 0x65; // Multiplies two f64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }

	constexpr opcode div_i32 = 0x66; // Divides two i32 values from OStack value0, value1 -> result
	constexpr opcode div_i64 = 0x67; // Divides two i64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode div_u32 = 0x68; // Divides two u32 values from OStack value0, value1 -> result
	constexpr opcode div_u64 = 0x69; // Divides two u64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h } 
	constexpr opcode div_f32 = 0x6A; // Divides two f32 values from OStack value0, value1 -> result
	constexpr opcode div_f64 = 0x6B; // Divides two f64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }

	constexpr opcode mod_i32 = 0x6C; // Modulus of two i32 values from OStack value0, value1 -> result
	constexpr opcode mod_i64 = 0x6D; // Modulus of two i64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode mod_u32 = 0x6E; // Modulus of two u32 values from OStack value0, value1 -> result
	constexpr opcode mod_u64 = 0x6F; // Modulus of two u64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }
	constexpr opcode mod_f32 = 0x70; // Modulus of two f32 values from OStack value0, value1 -> result
	constexpr opcode mod_f64 = 0x71; // Modulus of two f64 values from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }

	constexpr opcode neg_i32 = 0x72; // Negates the i32 value from FStack local word (u8 local) -> value
	constexpr opcode neg_i64 = 0x73; // Negates the i64 value from FStack local dword (u8 local) -> { value_l, value_h }
	constexpr opcode neg_f32 = 0x74; // Negates the f32 value from FStack local word (u8 local) -> value
	constexpr opcode neg_f64 = 0x75; // Negates the f64 value from FStack local dword (u8 local) -> { value_l, value_h }

	// Bitwise operations

	constexpr opcode and_word  = 0x76; // Bitwise AND two words from OStack value0, value1 -> result
	constexpr opcode and_dword = 0x77; // Bitwise AND two dwords from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }

	constexpr opcode or_word  = 0x78; // Bitwise OR two words from OStack value0, value1 -> result
	constexpr opcode or_dword = 0x79; // Bitwise OR two dwords from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }

	constexpr opcode xor_word  = 0x7A; // Bitwise XOR two words from OStack value0, value1 -> result
	constexpr opcode xor_dword = 0x7B; // Bitwise XOR two dwords from OStack { value0_l, value0_h }, { value1_l, value1_h } -> { result_l, result_h }

	constexpr opcode not_word  = 0x7C; // Bitwise NOT a word from OStack value -> result
	constexpr opcode not_dword = 0x7D; // Bitwise NOT a dword from OStack { value_l, value_h } -> { result_l, result_h }

	constexpr opcode shl_word  = 0x7E; // Shift left a word from OStack value, shift -> result
	constexpr opcode shl_dword = 0x7F; // Shift left a dword from OStack { value_l, value_h }, shift -> { result_l, result_h }

	constexpr opcode shr_i32 = 0x80; // Shift right an i32 value from OStack value, shift -> result
	constexpr opcode shr_i64 = 0x81; // Shift right an i64 value from OStack { value_l, value_h }, shift -> { result_l, result_h }
	constexpr opcode shr_u32 = 0x82; // Shift right an u32 value from OStack value, shift -> result
	constexpr opcode shr_u64 = 0x83; // Shift right an u64 value from OStack { value_l, value_h }, shift -> { result_l, result_h }

	// Jump operations

	constexpr opcode jmp        = 0x84; // Jumps by a signed offset (i16 offset)

	constexpr opcode jmp_i32_eq = 0x85; // Jumps by a signed offset (i16 offset) if two i32 values from OStack are equal value0, value1  ->
	constexpr opcode jmp_i32_ne = 0x86; // Jumps by a signed offset (i16 offset) if two i32 values from OStack are not equal value0, value1  ->
	constexpr opcode jmp_i32_lt = 0x87; // Jumps by a signed offset (i16 offset) if the first i32 value from OStack is less than the second value0, value1  ->
	constexpr opcode jmp_i32_gt = 0x88; // Jumps by a signed offset (i16 offset) if the first i32 value from OStack is greater than the second value0, value1  ->
	constexpr opcode jmp_i32_le = 0x89; // Jumps by a signed offset (i16 offset) if the first i32 value from OStack is less or equal than the second value0, value1  ->
	constexpr opcode jmp_i32_ge = 0x8A; // Jumps by a signed offset (i16 offset) if the first i32 value from OStack is greater or equal than the second value0, value1  ->

	constexpr opcode jmp_i64_eq = 0x8B; // Jumps by a signed offset (i16 offset) if two i64 values from OStack are equal { value0_l, value0_h }, { value1_l, value1_h } ->
	constexpr opcode jmp_i64_ne = 0x8C; // Jumps by a signed offset (i16 offset) if two i64 values from OStack are not equal { value0_l, value0_h }, { value1_l, value1_h } ->
	constexpr opcode jmp_i64_lt = 0x8D; // Jumps by a signed offset (i16 offset) if the first i64 value from OStack is less than the second { value0_l, value0_h }, { value1_l, value1_h } ->
	constexpr opcode jmp_i64_gt = 0x8E; // Jumps by a signed offset (i16 offset) if the first i64 value from OStack is greater than the second { value0_l, value0_h }, { value1_l, value1_h } ->
	constexpr opcode jmp_i64_le = 0x8F; // Jumps by a signed offset (i16 offset) if the first i64 value from OStack is less or equal than the second { value0_l, value0_h }, { value1_l, value1_h } ->
	constexpr opcode jmp_i64_ge = 0x90; // Jumps by a signed offset (i16 offset) if the first i64 value from OStack is greater or equal than the second { value0_l, value0_h }, { value1_l, value1_h } ->

	constexpr opcode jmp_f32_eq = 0x91; // Jumps by a signed offset (i16 offset) if two f32 values from OStack are equal value0, value1  ->
	constexpr opcode jmp_f32_ne = 0x92; // Jumps by a signed offset (i16 offset) if two f32 values from OStack are not equal value0, value1  ->
	constexpr opcode jmp_f32_lt = 0x93; // Jumps by a signed offset (i16 offset) if the first f32 value from OStack is less than the second value0, value1  ->
	constexpr opcode jmp_f32_gt = 0x94; // Jumps by a signed offset (i16 offset) if the first f32 value from OStack is greater than the second value0, value1  ->
	constexpr opcode jmp_f32_le = 0x95; // Jumps by a signed offset (i16 offset) if the first f32 value from OStack is less or equal than the second value0, value1  ->
	constexpr opcode jmp_f32_ge = 0x96; // Jumps by a signed offset (i16 offset) if the first f32 value from OStack is greater or equal than the second value0, value1  ->

	constexpr opcode jmp_f64_eq = 0x97; // Jumps by a signed offset (i16 offset) if two f64 values from OStack are equal { value0_l, value0_h }, { value1_l, value1_h } ->
	constexpr opcode jmp_f64_ne = 0x98; // Jumps by a signed offset (i16 offset) if two f64 values from OStack are not equal { value0_l, value0_h }, { value1_l, value1_h } ->
	constexpr opcode jmp_f64_lt = 0x99; // Jumps by a signed offset (i16 offset) if the first f64 value from OStack is less than the second { value0_l, value0_h }, { value1_l, value1_h } ->
	constexpr opcode jmp_f64_gt = 0x9A; // Jumps by a signed offset (i16 offset) if the first f64 value from OStack is greater than the second { value0_l, value0_h }, { value1_l, value1_h } ->
	constexpr opcode jmp_f64_le = 0x9B; // Jumps by a signed offset (i16 offset) if the first f64 value from OStack is less or equal than the second { value0_l, value0_h }, { value1_l, value1_h } ->
	constexpr opcode jmp_f64_ge = 0x9C; // Jumps by a signed offset (i16 offset) if the first f64 value from OStack is greater or equal than the second { value0_l, value0_h }, { value1_l, value1_h } ->

	constexpr opcode jmp_u32_lt = 0x9D; // Jumps by a signed offset (i16 offset) if the first u32 value from OStack is less than the second value0, value1  ->
	constexpr opcode jmp_u32_gt = 0x9E; // Jumps by a signed offset (i16 offset) if the first u32 value from OStack is greater than the second value0, value1  ->
	constexpr opcode jmp_u32_le = 0x9F; // Jumps by a signed offset (i16 offset) if the first u32 value from OStack is less or equal than the second value0, value1  ->
	constexpr opcode jmp_u32_ge = 0xA0; // Jumps by a signed offset (i16 offset) if the first u32 value from OStack is greater or equal than the second value0, value1  ->

	constexpr opcode jmp_u64_lt = 0xA1; // Jumps by a signed offset (i16 offset) if the first u64 value from OStack is less than the second { value0_l, value0_h }, { value1_l, value1_h } ->
	constexpr opcode jmp_u64_gt = 0xA2; // Jumps by a signed offset (i16 offset) if the first u64 value from OStack is greater than the second { value0_l, value0_h }, { value1_l, value1_h } ->
	constexpr opcode jmp_u64_le = 0xA3; // Jumps by a signed offset (i16 offset) if the first u64 value from OStack is less or equal than the second { value0_l, value0_h }, { value1_l, value1_h } ->
	constexpr opcode jmp_u64_ge = 0xA4; // Jumps by a signed offset (i16 offset) if the first u64 value from OStack is greater or equal than the second { value0_l, value0_h }, { value1_l, value1_h } ->

	// Call operations

	constexpr opcode call         = 0xA5; // Calls a function (u8 index)
	constexpr opcode call_ext     = 0xA6; // Not implemented!
	constexpr opcode syscall      = 0xA7; // Calls a c++ function (u8 index)
	constexpr opcode return_void  = 0xA8; // Returns from a function
	constexpr opcode return_byte  = 0xA9; // Returns a byte from a function value_0, value_1, ..., value_n -> return_value
	constexpr opcode return_hword = 0xAA; // Returns a hword from a function value_0, value_1, ..., value_n -> return_value
	constexpr opcode return_word  = 0xAB; // Returns a word from a function value_0, value_1, ..., value_n -> return_value
	constexpr opcode return_dword = 0xAD; // Returns a dword from a function value_0, value_1, ..., value_n -> return_value
	constexpr opcode return_words = 0xAE; // Returns n words from a function value_0, value_1, ..., value_n -> return_value_0, return_value_1, ..., return_value_n

	// Type conversion operations

	constexpr opcode i32_to_i64 = 0xAF; // Converts an i32 value from OStack to an i64 value value -> { value, 0 }
	constexpr opcode i32_to_f32 = 0xB0; // Converts an i32 value from OStack to an f32 value value -> result
	constexpr opcode i32_to_f64 = 0xB1; // Converts an i32 value from OStack to an f64 value value -> { result_l, result_h }
	constexpr opcode i64_to_i32 = 0xB2; // Converts an i64 value from OStack to an i32 value { value_l, value_h } -> value
	constexpr opcode i64_to_f32 = 0xB3; // Converts an i64 value from OStack to an f32 value { value_l, value_h } -> result
	constexpr opcode i64_to_f64 = 0xB4; // Converts an i64 value from OStack to an f64 value { value_l, value_h } -> { result_l, result_h }
	constexpr opcode f32_to_f64 = 0xB5; // Converts an f32 value from OStack to an f64 value value -> { value, 0 }
	constexpr opcode f32_to_i32 = 0xB6; // Converts an f32 value from OStack to an i32 value value -> result
	constexpr opcode f32_to_i64 = 0xB7; // Converts an f32 value from OStack to an i64 value value -> { result_l, result_h }
	constexpr opcode f64_to_i32 = 0xB8; // Converts an f64 value from OStack to an i32 value { value_l, value_h } -> result
	constexpr opcode f64_to_i64 = 0xB9; // Converts an f64 value from OStack to an i64 value { value_l, value_h } -> { result_l, result_h }
	constexpr opcode f64_to_f32 = 0xBA; // Converts an f64 value from OStack to an f32 value { value_l, value_h } -> result

	namespace Syscall
	{
		constexpr opcode Print    = 0x01; // Prints a string
		constexpr opcode PrintI64 = 0x02; // Prints an i64 value
		constexpr opcode PrintF64 = 0x03; // Prints an f64 value
		constexpr opcode SqrtF32  = 0x04; // Calculates the square root of an f32 value
		constexpr opcode SqrtF64  = 0x05; // Calculates the square root of an f64 value
	}

	inline std::vector<opcode> RecursiveSumProgram =
	{
		U16v(1), // word constant pool size
		U16v(0), // dword constant pool size
		U16v(2), // function pointers constant pool size
		// WORD CONSTANT POOL 
		U32v(1000),
		// DWORD CONSTANT POOL (empty)
		// FUNCTION POINTERS
		U32v(4), 
		U32v(15),


		//FUNCTION DEFS
		call, U16v(0), // call main
		exit,

		// main()->()
		U8v(0), U8v(0), // arg size, local size
		push_word_from_pool, I8v(0),
		call, U16v(1), // call rec(i32)->(i32)
		i32_to_i64,
		syscall, U8v(2), // Print(i32)
		return_void,

		// rec(i32)->(i32)

		U8v(1), U8v(1), // arg size, local size
		push_word_0,
		dup_word,
		push_i32_1,
		dup_dword,
		jmp_i32_le, U16v(5),
		sub_i32,
		call, U16v(1), // call rec+(i32)->(i32)
		add_i32,
		return_word,
	};

	inline std::vector<opcode> HelloWorldProgram =
	{
		U16v(4), // word constant pool size
		U16v(0), // dword constant pool size
		U16v(1), // function pointers constant pool size
		// WORD CONSTANT POOL 
		STRw('H', 'e', 'l', 'l'),
		STRw('o', ' ', 'W', 'o'),
		STRw('r', 'l', 'd', '!'),
		STRw('\n', '\0', '\0', '\0'),
		// DWORD CONSTANT POOL (empty)
		// FUNCTION POINTERS
		U32v(4),

		call, U16v(0), // call main
		exit,

		// main()->()
		U8v(0), U8v(4), // arg size, local size
		push_word_from_pool, I8v(0),
		push_word_from_pool, I8v(1),
		push_word_from_pool, I8v(2),
		push_word_from_pool, I8v(3),
		pop_word_3,
		pop_word_2,
		pop_word_1,
		pop_word_0,
		get_address, U8v(0),
		syscall, U8v(1), // Print(const char* str)
		return_void
	};

	inline std::vector<opcode> SqrtProgram =
	{
		U16v(1), // word constant pool size
		U16v(0), // dword constant pool size
		U16v(1), // function pointers constant pool size

		// WORD CONSTANT POOL
		U32v(0x44020000), // 520.f

		// FUNCTION POINTERS
		U32v(4),

		call, U16v(0), // call main
		exit,

		// main()->()
		U8v(0), U8v(1), // arg size, local size
		push_word_from_pool, I8v(0),
		syscall, U8v(4), // Sqrt(520.f)
		pop_word_0,
		return_void
	};

	inline std::vector<opcode> PrintSumCast = 
	{
		U16v(0), // word constant pool size
		U16v(0), // dword constant pool size
		U16v(1), // function pointers constant pool size

		// FUNCTION POINTERS
		U32v(4),

		call, U16v(0), // call main
		exit,

		// main()->()
		U8v(0), U8v(1), // arg size, local size
		push_i8_as_i32, I8v(20),
		i32_to_f32,
		push_i8_as_i32, I8v(42),
		i32_to_f32,
		add_f32,
		f32_to_f64,
		syscall, U8v(5), // SqrtF64(f64)
		syscall, U8v(3), // PrintF64(f64)
		return_void
	};
}