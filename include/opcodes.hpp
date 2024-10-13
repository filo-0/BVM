#pragma once

#include "types.hpp"
#include <vector>

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

namespace BVM
{
	typedef u8 opcode;

	namespace OpCodes
	{
		
		constexpr opcode exit = 0x00;

		// Stack operations

		constexpr opcode push_byte_0  = 0x01; // Pushes first byte of local word (u8 local)
		constexpr opcode push_byte_1  = 0x02; // Pushes second byte of local word (u8 local)
		constexpr opcode push_byte_2  = 0x03; // Pushes third byte of local word (u8 local)
		constexpr opcode push_byte_3  = 0x04; // Pushes fourth byte of local word (u8 local)
		constexpr opcode push_hword_0 = 0x05; // Pushes first halfword of local word (u8 local)
		constexpr opcode push_hword_2 = 0x06; // Pushes second halfword of local word (u8 local)
		constexpr opcode push_word    = 0x07; // Pushes local word (u8 local)
		constexpr opcode push_word_0  = 0x08; // Pushes local word 0
		constexpr opcode push_word_1  = 0x09; // Pushes local word 1
		constexpr opcode push_word_2  = 0x0A; // Pushes local word 2
		constexpr opcode push_word_3  = 0x0B; // Pushes local word 3
		constexpr opcode push_dword   = 0x0C; // Pushes local dword (u8 local)	
		constexpr opcode push_dword_0 = 0x0D; // Pushes local dword 0
		constexpr opcode push_dword_1 = 0x0E; // Pushes local dword 1
		constexpr opcode push_dword_2 = 0x0F; // Pushes local dword 2
		constexpr opcode push_dword_3 = 0x10; // Pushes local dword 3
		constexpr opcode push_words   = 0x11; // Pushes local words (u8 local, u8 count)

		constexpr opcode push_word_value_0  = 0x12; // Pushes 0x00000000
		constexpr opcode push_dword_value_0 = 0x13; // Pushes 0x0000000000000000
		constexpr opcode push_i32_1   = 0x14; // Pushes 0x00000001
		constexpr opcode push_i32_2   = 0x15; // Pushes 0x00000002
		constexpr opcode push_i64_1   = 0x16; // Pushes 0x0000000000000001
		constexpr opcode push_i64_2   = 0x17; // Pushes 0x0000000000000002
		constexpr opcode push_f32_1   = 0x18; // Pushes 0x3F800000 (1.0f)
		constexpr opcode push_f32_2   = 0x19; // Pushes 0x40000000 (2.0f)
		constexpr opcode push_f64_1   = 0x1A; // Pushes 0x3FF0000000000000 (1.0)
		constexpr opcode push_f64_2   = 0x1B; // Pushes 0x4000000000000000 (2.0)

		constexpr opcode push_i8_as_i32            = 0x1C; // Pushes an i8 as an i32 (i8 value)
		constexpr opcode push_i8_as_i64            = 0x1D; // Pushes an i8 as an i64 (i8 value)
		constexpr opcode push_word_from_pool       = 0x1E; // Pushes a word from the word constant pool (u8 index)
		constexpr opcode push_word_from_pool_wide  = 0x1F; // Pushes a word from the word constant pool (u16 index)
		constexpr opcode push_dword_from_pool      = 0xAC; // Pushes a dword from the dword constant pool (u8 index)
		constexpr opcode push_dword_from_pool_wide = 0x20; // Pushes a dword from the dword constant pool (u16 index)

		constexpr opcode pop_byte_0  = 0x21; // u8 reg
		constexpr opcode pop_byte_1  = 0x22; // u8 reg
		constexpr opcode pop_byte_2  = 0x23; // u8 reg
		constexpr opcode pop_byte_3  = 0x24; // u8 reg
		constexpr opcode pop_hword_0 = 0x25; // u8 reg
		constexpr opcode pop_hword_2 = 0x26; // u8 reg
		constexpr opcode pop_word    = 0x27; // u8 reg
		constexpr opcode pop_word_0  = 0x28;
		constexpr opcode pop_word_1  = 0x29;
		constexpr opcode pop_word_2  = 0x2A;
		constexpr opcode pop_word_3  = 0x2B;
		constexpr opcode pop_dword   = 0x2C; // u8 reg
		constexpr opcode pop_dword_0 = 0x2D;
		constexpr opcode pop_dword_1 = 0x2E;
		constexpr opcode pop_dword_2 = 0x2F;
		constexpr opcode pop_dword_3 = 0x30;
		constexpr opcode pop_words   = 0x31; // u8 reg, u8 count

		constexpr opcode dup_word     = 0x32;
		constexpr opcode dup_word_x1  = 0x33;
		constexpr opcode dup_word_x2  = 0x34;
		constexpr opcode dup_dword    = 0x35;
		constexpr opcode dup_dword_x1 = 0x36;
		constexpr opcode dup_dword_x2 = 0x37;
		constexpr opcode swap_word    = 0x38;
		constexpr opcode swap_dword   = 0x39;

		// Memory operations

		constexpr opcode get_address = 0x3A; // u8 reg

		constexpr opcode load_byte_0  = 0x3B;
		constexpr opcode load_byte_1  = 0x3C;
		constexpr opcode load_byte_2  = 0x3D;
		constexpr opcode load_byte_3  = 0x3E;
		constexpr opcode load_hword_0 = 0x3F;
		constexpr opcode load_hword_2 = 0x40;
		constexpr opcode load_word    = 0x41;
		constexpr opcode load_dword   = 0x42;

		constexpr opcode store_byte_0  = 0x43;
		constexpr opcode store_byte_1  = 0x44;
		constexpr opcode store_byte_2  = 0x45;
		constexpr opcode store_byte_3  = 0x46;
		constexpr opcode store_hword_0 = 0x47;
		constexpr opcode store_hword_2 = 0x48;
		constexpr opcode store_word    = 0x49;
		constexpr opcode store_dword   = 0x4A;

		// Arithmetic operations

		constexpr opcode add_i32 = 0x50;
		constexpr opcode add_i64 = 0x51;
		constexpr opcode add_f32 = 0x52;
		constexpr opcode add_f64 = 0x53;
		constexpr opcode inc_i32 = 0x54; // u8 reg
		constexpr opcode inc_i64 = 0x55; // u8 reg
		constexpr opcode inc_f32 = 0x56; // u8 reg
		constexpr opcode inc_f64 = 0x57; // u8 reg

		constexpr opcode sub_i32 = 0x58;
		constexpr opcode sub_i64 = 0x59;
		constexpr opcode sub_f32 = 0x5A;
		constexpr opcode sub_f64 = 0x5B;
		constexpr opcode dec_i32 = 0x5C; // u8 reg
		constexpr opcode dec_i64 = 0x5D; // u8 reg
		constexpr opcode dec_f32 = 0x5E; // u8 reg
		constexpr opcode dec_f64 = 0x5F; // u8 reg

		constexpr opcode mul_i32 = 0x60;
		constexpr opcode mul_i64 = 0x61;
		constexpr opcode mul_u32 = 0x62;
		constexpr opcode mul_u64 = 0x63;
		constexpr opcode mul_f32 = 0x64;
		constexpr opcode mul_f64 = 0x65;

		constexpr opcode div_i32 = 0x66;
		constexpr opcode div_i64 = 0x67;
		constexpr opcode div_u32 = 0x68;
		constexpr opcode div_u64 = 0x69;
		constexpr opcode div_f32 = 0x6A;
		constexpr opcode div_f64 = 0x6B;

		constexpr opcode mod_i32 = 0x6C;
		constexpr opcode mod_i64 = 0x6D;
		constexpr opcode mod_u32 = 0x6E;
		constexpr opcode mod_u64 = 0x6F;
		constexpr opcode mod_f32 = 0x70;
		constexpr opcode mod_f64 = 0x71;

		constexpr opcode neg_i32 = 0x72;
		constexpr opcode neg_i64 = 0x73;
		constexpr opcode neg_f32 = 0x74;
		constexpr opcode neg_f64 = 0x75;

		// Bitwise operations

		constexpr opcode and_word  = 0x76;
		constexpr opcode and_dword = 0x77;

		constexpr opcode or_word  = 0x78;
		constexpr opcode or_dword = 0x79;

		constexpr opcode xor_word  = 0x7A;
		constexpr opcode xor_dword = 0x7B;

		constexpr opcode not_word  = 0x7C;
		constexpr opcode not_dword = 0x7D;

		constexpr opcode shl_word  = 0x7E;
		constexpr opcode shl_dword = 0x7F;

		constexpr opcode shr_i32 = 0x80;
		constexpr opcode shr_i64 = 0x81;
		constexpr opcode shr_u32 = 0x82;
		constexpr opcode shr_u64 = 0x83;

		// Jump operations

		constexpr opcode jmp        = 0x84;

		constexpr opcode jmp_i32_eq = 0x85;
		constexpr opcode jmp_i32_ne = 0x86;
		constexpr opcode jmp_i32_lt = 0x87;
		constexpr opcode jmp_i32_gt = 0x88;
		constexpr opcode jmp_i32_le = 0x89;
		constexpr opcode jmp_i32_ge = 0x8A;

		constexpr opcode jmp_i64_eq = 0x8B;
		constexpr opcode jmp_i64_ne = 0x8C;
		constexpr opcode jmp_i64_lt = 0x8D;
		constexpr opcode jmp_i64_gt = 0x8E;
		constexpr opcode jmp_i64_le = 0x8F;
		constexpr opcode jmp_i64_ge = 0x90;

		constexpr opcode jmp_f32_eq = 0x91;
		constexpr opcode jmp_f32_ne = 0x92;
		constexpr opcode jmp_f32_lt = 0x93;
		constexpr opcode jmp_f32_gt = 0x94;
		constexpr opcode jmp_f32_le = 0x95;
		constexpr opcode jmp_f32_ge = 0x96;

		constexpr opcode jmp_f64_eq = 0x97;
		constexpr opcode jmp_f64_ne = 0x98;
		constexpr opcode jmp_f64_lt = 0x99;
		constexpr opcode jmp_f64_gt = 0x9A;
		constexpr opcode jmp_f64_le = 0x9B;
		constexpr opcode jmp_f64_ge = 0x9C;

		constexpr opcode jmp_u32_lt = 0x9D;
		constexpr opcode jmp_u32_gt = 0x9E;
		constexpr opcode jmp_u32_le = 0x9F;
		constexpr opcode jmp_u32_ge = 0xA0;

		constexpr opcode jmp_u64_lt = 0xA1;
		constexpr opcode jmp_u64_gt = 0xA2;
		constexpr opcode jmp_u64_le = 0xA3;
		constexpr opcode jmp_u64_ge = 0xA4;

		// Call operations

		constexpr opcode call         = 0xA5;
		constexpr opcode call_ext     = 0xA6;
		constexpr opcode syscall      = 0xA7; // Calls a c++ function (u8 index)
		constexpr opcode return_void  = 0xA8;
		constexpr opcode return_byte  = 0xA9;
		constexpr opcode return_hword = 0xAA;
		constexpr opcode return_word  = 0xAB;
		constexpr opcode return_dword = 0xAD;
		constexpr opcode return_words = 0xAE;

		constexpr opcode i32_to_i64 = 0xAF;
		constexpr opcode i32_to_f32 = 0xB0;
		constexpr opcode i32_to_f64 = 0xB1;
		constexpr opcode i64_to_i32 = 0xB2;
		constexpr opcode i64_to_f32 = 0xB3;
		constexpr opcode i64_to_f64 = 0xB4;
		constexpr opcode f32_to_f64 = 0xB5;
		constexpr opcode f32_to_i32 = 0xB6;
		constexpr opcode f32_to_i64 = 0xB7;
		constexpr opcode f64_to_i32 = 0xB8;
		constexpr opcode f64_to_i64 = 0xB9;
		constexpr opcode f64_to_f32 = 0xBA;

	
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
}