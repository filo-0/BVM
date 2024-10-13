#pragma once

#include <stdint.h>

namespace BVM
{
	typedef int8_t i8;
	typedef uint8_t u8;
	typedef int16_t i16;
	typedef uint16_t u16;
	typedef int32_t i32;
	typedef uint32_t u32;
	typedef int64_t i64;
	typedef uint64_t u64;
	typedef float f32;
	typedef double f64;

	union Byte
	{
		constexpr inline Byte() : IValue(0) {}
		constexpr inline Byte(i8 value) : IValue(value) {}
		constexpr inline  Byte(u8 value) : UValue(value) {}
		constexpr inline Byte(i32 value) : IValue(value) {} // Implicit conversion from int32_t to Byte

		i8 IValue;
		u8 UValue;
	};
	union HWord
	{
		constexpr inline HWord() : IValue(0) {}
		constexpr inline HWord(i16 value) : IValue(value) {}
		constexpr inline HWord(u16 value) : UValue(value) {}
		constexpr inline HWord(i32 value) : IValue(value) {} // Implicit conversion from int32_t to Half
		constexpr inline HWord(Byte value) : IValue(value.UValue) {}

		i16 IValue;
		u16 UValue;
		struct Bytes
		{
			Byte Value0;
			Byte Value1;
		} B;
	};
	union Word
	{
		constexpr inline Word() : IValue(0) {}
		constexpr inline Word(i32 value) : IValue(value) {}
		constexpr inline Word(f32 value) : FValue(value) {}
		constexpr inline Word(u32 value) : UValue(value) {}
		constexpr inline Word(Byte value) : IValue(value.IValue) {}
		constexpr inline Word(HWord value) : IValue(value.IValue) {}

		u32 UValue;
		i32 IValue;
		f32 FValue;
		struct HWords
		{
			HWord Value0;
			HWord Value1;
		} H;
	};
	union DWord
	{
		constexpr DWord() : IValue(0) {}
		constexpr DWord(i64 value) : IValue(value) {}
		constexpr DWord(f64 value) : FValue(value) {}
		constexpr DWord(u64 value) : UValue(value) {}
		constexpr DWord(i32 value) : IValue(value) {}
		constexpr DWord(Byte value) : IValue(value.IValue) {}
		constexpr DWord(HWord value) : IValue(value.IValue) {}
		constexpr DWord(Word value) : IValue(value.IValue) {}

		u64 UValue;
		i64 IValue;
		f64 FValue;
		struct Words
		{
			Word Value0;
			Word Value1;
		} W;
	};
}