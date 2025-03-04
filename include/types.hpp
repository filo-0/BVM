#pragma once

#include "std.hpp"

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
	constexpr inline Byte(i32 value) : IValue((i8)value) {} // Implicit conversion from int32_t to Byte

	i8 IValue;
	u8 UValue;
};
union HWord
{
	constexpr inline HWord() : IValue(0) {}
	constexpr inline HWord(i16 value) : IValue(value) {}
	constexpr inline HWord(u16 value) : UValue(value) {}
	constexpr inline HWord(i32 value) : IValue((i16)value) {} // Implicit conversion from int32_t to Half
	constexpr inline HWord(Byte value) : IValue(value.UValue) {}

	i16 IValue;
	u16 UValue;
	Byte BValue[2];
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
	HWord HValue[2];
	Byte BValue[4];
};
union DWord
{
	constexpr DWord() : IValue(0) {}
	constexpr DWord(i64 value) : IValue(value) {}
	constexpr DWord(f64 value) : FValue(value) {}
	constexpr DWord(u64 value) : UValue(value) {}
	constexpr DWord(i32 value) : IValue((i64)value) {}
	constexpr DWord(Byte value) : IValue(value.IValue) {}
	constexpr DWord(HWord value) : IValue(value.IValue) {}
	constexpr DWord(Word value) : IValue(value.IValue) {}
	constexpr DWord(void* value) : Pointer(value) {}

	u64 UValue;
	i64 IValue;
	f64 FValue;
	void* Pointer;
	Byte* BPointer;
	HWord* HPointer;
	Word* WPointer;
	DWord* DPointer;
	Word WValue[2];
	HWord HValue[4];
	Byte BValue[8];
};