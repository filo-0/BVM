#include <iostream>
#include <vector>
#include <chrono>
#include <stack>
#include <memory>
#include <cmath>
#include <cstring>
#include <cassert>

#include "bvm.hpp"

#define LOG_R(...) printf(__VA_ARGS__) 

#ifdef _DEBUG
#define LOG(...) printf(__VA_ARGS__)
#define ASSERT(x, ...)    \
	if (!(x))             \
	{                     \
		LOG(__VA_ARGS__); \
		while (1);        \
	}
#else
#define LOG(...)
#define ASSERT(x, ...)
#endif // _DEBUG


namespace BVM
{
	/* Contains data on the program stack to return from functions. */
	struct StackState
	{
		u32 ProgramCounter;
		u32 FunctionStackBasePointer;
		u32 OperationStackBasePointer;
	};

	bool Running = true;
	u32 ProgramCounter = 0;
	std::vector<u8> Bytecode;
	std::vector<u32> FunctionPointerPool;
	std::vector<Word> WordConstantPool;
	std::vector<DWord> DWordConstantPool;
	std::stack<StackState> PrevStackStates;

	inline static Byte GetNextByte() { return Bytecode[ProgramCounter++]; }
	inline static HWord GetNextHWord()
	{
		u16 v = *reinterpret_cast<u16*>(Bytecode.data() + ProgramCounter);
		ProgramCounter += sizeof(u16);
		return v;
	}
	inline static Word GetNextWord()
	{
		u32 v = *reinterpret_cast<u32*>(Bytecode.data() + ProgramCounter);
		ProgramCounter += sizeof(u32);
		return v;
	}
	inline static DWord GetNextDWord()
	{
		u64 v = *reinterpret_cast<u64*>(Bytecode.data() + ProgramCounter);
		ProgramCounter += sizeof(u64);
		return v;
	}

	namespace FunctionStack
	{
		constexpr u32 SIZE = 1 << 22;
		Word V[SIZE] = {};
		u32 BasePointer = 0;
		u32 Pointer = 0;

		inline static HWord& GlobalH0(u32 offset) { return V[offset].H.Value0; }
		inline static HWord& GlobalH1(u32 offset) { return V[offset].H.Value1; }

		inline static DWord& LocalD(u8 index)   { return *reinterpret_cast<DWord*>(V + BasePointer + index); }
		inline static Word&  LocalW(u8 index)   { return V[BasePointer + index]; }
		inline static HWord& LocalH0(u8 index)  { return V[BasePointer + index].H.Value0; }
		inline static HWord& LocalH2(u8 index)  { return V[BasePointer + index].H.Value1; }
		inline static Byte&  LocalB0(u8 index)  { return V[BasePointer + index].H.Value0.B.Value0; }
		inline static Byte&  LocalB1(u8 index)  { return V[BasePointer + index].H.Value0.B.Value1; }
		inline static Byte&  LocalB2(u8 index)  { return V[BasePointer + index].H.Value1.B.Value0; }
		inline static Byte&  LocalB3(u8 index)  { return V[BasePointer + index].H.Value1.B.Value1; }

		inline static void PushData(Word* data, u8 count)
		{
			ASSERT(Pointer + count < SIZE && (data || (!data && count == 0)), "FunctionStack overflow!");
			memcpy(V + Pointer, data, sizeof(Word) * count);
		}
		inline static void OnCall(u8 localsCount)
		{
			ASSERT(Pointer + localsCount < SIZE, "FunctionStack overflow!");
			BasePointer = Pointer;
			Pointer += localsCount;
		}
		inline static void OnReturn(u32 PrevBasePointer)
		{
			ASSERT(BasePointer >= PrevBasePointer, "FunctionStack underflow!");
			Pointer = BasePointer;
			BasePointer = PrevBasePointer;
		}

		static void PrintState()
		{
			LOG("\n");
			for (u32 i = 0; i < Pointer; i++)
			{
				LOG("0x%08X\n", V[i].UValue);
			}
		}
	}
	namespace OperationStack
	{
		constexpr u32 SIZE = 1 << 12;
		Word V[SIZE];
		u32 BasePointer = 0;
		u32 Pointer = 0;

		inline static Word& TopW(u32 offset = 0)
		{
			u32 idx = Pointer - offset - 1;
			ASSERT(idx < Pointer, "OperationStack index out of range!");
			return V[idx];
		}
		inline static DWord& TopD(u32 offset = 0)
		{
			u32 idx = Pointer - offset - 2;
			ASSERT(idx < Pointer, "OperationStack index out of range!");
			return *reinterpret_cast<DWord*>(V + idx);
		}
		inline static Word* TopWs(u32 count)
		{
			return V + Pointer - count;
		}

		inline static void PushW(Word w)
		{
			V[Pointer++].UValue = w.UValue;
			ASSERT(Pointer < SIZE, "OperationStack overflow");
		}
		inline static void PushD(DWord d)
		{
			DWord& interpreted64 = *reinterpret_cast<DWord*>(V + Pointer);
			interpreted64.UValue = d.UValue;
			Pointer += 2;
			ASSERT(Pointer < SIZE, "OperationStack overflow");
		}
		inline static void PushWs(Word* v, u32 count)
		{
			memcpy(V + Pointer, v, sizeof(Word) * count);
			Pointer += count;
			ASSERT(Pointer < SIZE, "OperationStack overflow");
		}

		inline static void PopW()
		{
			ASSERT(Pointer > BasePointer, "OperationStack underflow");
			--Pointer;
		}
		inline static void PopD()
		{
			ASSERT(Pointer > BasePointer + 1, "OperationStack underflow");
			Pointer -= 2;
		}
		inline static void PopWs(u32 count)
		{
			ASSERT(Pointer >= BasePointer + count, "OperationStack underflow!")
			Pointer -= count;
		}

		inline static void OnCall()
		{
			BasePointer = Pointer;
		}
		inline static void OnReturn(u32 prevBasePointer)
		{
			ASSERT(BasePointer >= prevBasePointer, "OperationStack underflow!");
			Pointer = BasePointer;
			BasePointer = prevBasePointer;
		}

		inline static void DupW()
		{
			PushW(TopW(0));
		}
		inline static void DupWX1()
		{
			std::swap(TopW(0), TopW(1));
			PushW(TopW(1));
		}
		inline static void DupWX2()
		{
			std::swap(TopW(1), TopW(2));
			std::swap(TopW(0), TopW(2));
			PushW(TopW(2));
		}
		inline static void DupD()
		{
			PushD(TopD(0));
		}
		inline static void DupDX1()
		{
			std::swap(TopW(0), TopW(2));
			std::swap(TopW(1), TopW(2));
			PushD(TopD(1));
		}
		inline static void DupDX2()
		{
			std::swap(TopD(0), TopD(2));
			PushD(TopD(2));
		}
		inline static void SwapW()
		{
			std::swap(TopW(0), TopW(1));
		}
		inline static void SwapD()
		{
			std::swap(TopD(0), TopD(2));
		}

		inline static void LoadB0()
		{
			Byte* ptr = reinterpret_cast<Byte*>(TopD().UValue);
			PopW();
			TopW() = ptr->UValue;
		}
		inline static void LoadB1()
		{
			Byte* ptr = reinterpret_cast<Byte*>(TopD().UValue + 1U);
			PopW();
			TopW() = ptr->UValue;
		}
		inline static void LoadB2()
		{
			Byte* ptr = reinterpret_cast<Byte*>(TopD().UValue + 2U);
			PopW();
			TopW() = ptr->UValue;
		}
		inline static void LoadB3()
		{
			Byte* ptr = reinterpret_cast<Byte*>(TopD().UValue + 3U);
			PopW();
			TopW() = ptr->UValue;
		}
		inline static void LoadH0()
		{
			HWord* ptr = reinterpret_cast<HWord*>(TopD().UValue);
			PopW();
			TopW() = ptr->UValue;
		}
		inline static void LoadH2()
		{
			HWord* ptr = reinterpret_cast<HWord*>(TopD().UValue + 2U);
			PopW();
			TopW() = ptr->UValue;
		}
		inline static void LoadW()
		{
			Word* ptr = reinterpret_cast<Word*>(TopD().UValue);
			PopW();
			TopW() = ptr->UValue;
		}
		inline static void LoadD()
		{
			DWord* ptr = reinterpret_cast<DWord*>(TopD().UValue);
			TopD() = ptr->UValue;
		}

		inline static void StoreB0()
		{
			u8 value = TopW().UValue; PopW();
			reinterpret_cast<Byte*>(TopD().UValue)->UValue = value;
			PopD();
		}
		inline static void StoreB1()
		{
			u8 value = TopW().UValue; PopW();
			reinterpret_cast<Byte*>(TopD().UValue + 1U)->UValue = value;
			PopD();
		}
		inline static void StoreB2()
		{
			u8 value = TopW().UValue; PopW();
			reinterpret_cast<Byte*>(TopD().UValue + 2U)->UValue = value;
			PopD();
		}
		inline static void StoreB3()
		{
			u8 value = TopW().UValue; PopW();
			reinterpret_cast<Byte*>(TopD().UValue + 3U)->UValue = value;
			PopD();
		}
		inline static void StoreH0()
		{
			u16 value = TopW().UValue; PopW();
			reinterpret_cast<HWord*>(TopD().UValue)->UValue = value;
			PopD();
		}
		inline static void StoreH2()
		{
			u16 value = TopW().UValue; PopW();
			reinterpret_cast<HWord*>(TopD().UValue + 2U)->UValue = value;
			PopD();
		}
		inline static void StoreW()
		{
			u32 value = TopW().UValue; PopW();
			reinterpret_cast<Word*>(TopD().UValue)->UValue = value;
			PopD();
		}
		inline static void StoreD()
		{
			u64 value = TopD().UValue; PopD();
			reinterpret_cast<DWord*>(TopD().UValue)->UValue = value;
			PopD();
		}

		inline static void AddI32()
		{
			i32 op = TopW(0).IValue;
			PopW();
			TopW(0).IValue += op;
		}
		inline static void AddI64()
		{
			i64 op = TopD(0).IValue;
			PopD();
			TopD(0).IValue += op;
		}
		inline static void AddF32()
		{
			f32 op = TopW(0).FValue;
			PopW();
			TopW(0).FValue += op;
		}
		inline static void AddF64()
		{
			f64 op = TopD(0).FValue;
			PopD();
			TopD(0).FValue += op;
		}

		inline static void SubI32()
		{
			i32 op = TopW(0).IValue;
			PopW();
			TopW(0).IValue -= op;
		}
		inline static void SubI64()
		{
			i64 op = TopD(0).IValue;
			PopD();
			TopD(0).IValue -= op;
		}
		inline static void SubF32()
		{
			f32 op = TopW(0).FValue;
			PopW();
			TopW(0).FValue -= op;
		}
		inline static void SubF64()
		{
			f64 op = TopD(0).FValue;
			PopD();
			TopD(0).FValue -= op;
		}

		inline static void MulI32()
		{
			i32 op = TopW(0).IValue;
			PopW();
			TopW(0).IValue *= op;
		}
		inline static void MulI64()
		{
			i64 op = TopD(0).IValue;
			PopD();
			TopD(0).IValue *= op;
		}
		inline static void MulU32()
		{
			u32 op = TopW(0).UValue;
			PopW();
			TopW(0).UValue *= op;
		}
		inline static void MulU64()
		{
			u64 op = TopD(0).UValue;
			PopD();
			TopD(0).UValue *= op;
		}
		inline static void MulF32()
		{
			f32 op = TopW(0).FValue;
			PopW();
			TopW(0).FValue *= op;
		}
		inline static void MulF64()
		{
			f64 op = TopD(0).FValue;
			PopD();
			TopD(0).FValue *= op;
		}

		inline static void DivI32()
		{
			i32 op = TopW(0).IValue;
			PopW();
			TopW(0).IValue /= op;
		}
		inline static void DivI64()
		{
			i64 op = TopD(0).IValue;
			PopD();
			TopD(0).IValue /= op;
		}
		inline static void DivU32()
		{
			u32 op = TopW(0).UValue;
			PopW();
			TopW(0).UValue /= op;
		}
		inline static void DivU64()
		{
			u64 op = TopD(0).UValue;
			PopD();
			TopD(0).UValue /= op;
		}
		inline static void DivF32()
		{
			f32 op = TopW(0).FValue;
			PopW();
			TopW(0).FValue /= op;
		}
		inline static void DivF64()
		{
			f64 op = TopD(0).FValue;
			PopD();
			TopD(0).FValue /= op;
		}

		inline static void ModI32()
		{
			i32 op = TopW().IValue;
			PopW();
			TopW().IValue %= op;
		}
		inline static void ModI64()
		{
			i64 op = TopD().IValue;
			PopD();
			TopD().IValue %= op;
		}
		inline static void ModU32()
		{
			u32 op = TopW().UValue;
			PopW();
			TopW().UValue %= op;
		}
		inline static void ModU64()
		{
			u64 op = TopD().UValue;
			PopD();
			TopD().UValue %= op;
		}
		inline static void ModF32()
		{
			f32 op = TopW().FValue;
			PopW();
			TopW().FValue = fmodf(TopW().FValue, op);
		}
		inline static void ModF64()
		{
			f64 op = TopD().FValue;
			PopD();
			TopD().FValue = fmod(TopD().FValue, op);
		}

		inline static void NegI32()
		{
			TopW().IValue = -TopW().IValue;
		}
		inline static void NegI64()
		{
			TopD().IValue = -TopD().IValue;
		}
		inline static void NegF32()
		{
			TopW().FValue = -TopW().FValue;
		}
		inline static void NegF64()
		{
			TopD().FValue = -TopD().FValue;
		}

		inline static void AndW()
		{
			u32 op = TopW().UValue;
			PopW();
			TopW().UValue &= op;
		}
		inline static void AndD()
		{
			u64 op = TopD().UValue;
			PopD();
			TopD().UValue &= op;
		}
		inline static void OrW()
		{
			u32 op = TopW().UValue;
			PopW();
			TopW().UValue |= op;
		}
		inline static void OrD()
		{
			u64 op = TopD().UValue;
			PopD();
			TopD().UValue |= op;
		}
		inline static void XorW()
		{
			u32 op = TopW().UValue;
			PopW();
			TopW().UValue ^= op;
		}
		inline static void XorD()
		{
			u64 op = TopD().UValue;
			PopD();
			TopD().UValue ^= op;
		}
		inline static void NotW()
		{
			TopW().UValue = ~TopW().UValue;
		}
		inline static void NotD()
		{
			TopD().UValue = ~TopD().UValue;
		}
		inline static void ShlW()
		{
			u32 op = TopW().UValue;
			PopW();
			TopW().UValue <<= op;
		}
		inline static void ShlD()
		{
			u64 op = TopD().UValue;
			PopD();
			TopD().UValue <<= op;
		}
		inline static void ShrI32()
		{
			i32 op = TopW().IValue;
			PopW();
			TopW().IValue >>= op;
		}
		inline static void ShrI64()
		{
			i64 op = TopD().IValue;
			PopD();
			TopD().IValue >>= op;
		}
		inline static void ShrU32()
		{
			u32 op = TopW().UValue;
			PopW();
			TopW().UValue >>= op;
		}
		inline static void ShrU64()
		{
			u64 op = TopD().UValue;
			PopD();
			TopD().UValue >>= op;
		}

		inline static bool EqI32()
		{
			i32 b = TopW().IValue; PopW();
			i32 a = TopW().IValue; PopW();
			return a == b;
		}
		inline static bool NeI32()
		{
			i32 b = TopW().IValue; PopW();
			i32 a = TopW().IValue; PopW();
			return a != b;
		}
		inline static bool GtI32()
		{
			i32 b = TopW().IValue; PopW();
			i32 a = TopW().IValue; PopW();
			return a > b;
		}
		inline static bool LtI32()
		{
			i32 b = TopW().IValue; PopW();
			i32 a = TopW().IValue; PopW();
			return a < b;
		}
		inline static bool GeI32()
		{
			i32 b = TopW().IValue; PopW();
			i32 a = TopW().IValue; PopW();
			return a >= b;
		}
		inline static bool LeI32()
		{
			i32 b = TopW().IValue; PopW();
			i32 a = TopW().IValue; PopW();
			return a <= b;
		}
		
		inline static bool EqF32()
		{
			f32 b = TopW().FValue; PopW();
			f32 a = TopW().FValue; PopW();
			return a == b;
		}
		inline static bool NeF32()
		{
			f32 b = TopW().FValue; PopW();
			f32 a = TopW().FValue; PopW();
			return a != b;
		}
		inline static bool GtF32()
		{
			f32 b = TopW().FValue; PopW();
			f32 a = TopW().FValue; PopW();
			return a > b;
		}
		inline static bool LtF32()
		{
			f32 b = TopW().FValue; PopW();
			f32 a = TopW().FValue; PopW();
			return a < b;
		}
		inline static bool GeF32()
		{
			f32 b = TopW().FValue; PopW();
			f32 a = TopW().FValue; PopW();
			return a >= b;
		}
		inline static bool LeF32()
		{
			f32 b = TopW().FValue; PopW();
			f32 a = TopW().FValue; PopW();
			return a <= b;
		}

		inline static bool EqI64()
		{
			i64 b = TopD().IValue; PopD();
			i64 a = TopD().IValue; PopD();
			return a == b;
		}
		inline static bool NeI64()
		{
			i64 b = TopD().IValue; PopD();
			i64 a = TopD().IValue; PopD();
			return a != b;
		}
		inline static bool GtI64()
		{
			i64 b = TopD().IValue; PopD();
			i64 a = TopD().IValue; PopD();
			return a > b;
		}
		inline static bool LtI64()
		{
			i64 b = TopD().IValue; PopD();
			i64 a = TopD().IValue; PopD();
			return a < b;
		}
		inline static bool GeI64()
		{
			i64 b = TopD().IValue; PopD();
			i64 a = TopD().IValue; PopD();
			return a >= b;
		}
		inline static bool LeI64()
		{
			i64 b = TopD().IValue; PopD();
			i64 a = TopD().IValue; PopD();
			return a <= b;
		}

		inline static bool EqF64()
		{
			f64 b = TopD().FValue; PopD();
			f64 a = TopD().FValue; PopD();
			return a == b;
		}
		inline static bool NeF64()
		{
			f64 b = TopD().FValue; PopD();
			f64 a = TopD().FValue; PopD();
			return a != b;
		}
		inline static bool GtF64()
		{
			f64 b = TopD().FValue; PopD();
			f64 a = TopD().FValue; PopD();
			return a > b;
		}
		inline static bool LtF64()
		{
			f64 b = TopD().FValue; PopD();
			f64 a = TopD().FValue; PopD();
			return a < b;
		}
		inline static bool GeF64()
		{
			f64 b = TopD().FValue; PopD();
			f64 a = TopD().FValue; PopD();
			return a >= b;
		}
		inline static bool LeF64()
		{
			f64 b = TopD().FValue; PopD();
			f64 a = TopD().FValue; PopD();
			return a <= b;
		}

		inline static bool GtU32()
		{
			u32 b = TopW().UValue; PopW();
			u32 a = TopW().UValue; PopW();
			return a > b;
		}
		inline static bool LtU32()
		{
			u32 b = TopW().UValue; PopW();
			u32 a = TopW().UValue; PopW();
			return a < b;
		}
		inline static bool GeU32()
		{
			u32 b = TopW().UValue; PopW();
			u32 a = TopW().UValue; PopW();
			return a >= b;
		}
		inline static bool LeU32()
		{
			u32 b = TopW().UValue; PopW();
			u32 a = TopW().UValue; PopW();
			return a <= b;
		}

		inline static bool GtU64()
		{
			u64 b = TopD().UValue; PopD();
			u64 a = TopD().UValue; PopD();
			return a > b;
		}
		inline static bool LtU64()
		{
			u64 b = TopD().UValue; PopD();
			u64 a = TopD().UValue; PopD();
			return a < b;
		}
		inline static bool GeU64()
		{
			u64 b = TopD().UValue; PopD();
			u64 a = TopD().UValue; PopD();
			return a >= b;
		}
		inline static bool LeU64()
		{
			u64 b = TopD().UValue; PopD();
			u64 a = TopD().UValue; PopD();
			return a <= b;
		}

		static void PrintState()
		{
			for (u32 i = 0; i < Pointer; i++)
			{
				LOG("0x%08X\n", V[i].UValue);
			}
		}
	}

	void Link(std::vector<opcode>& program)
	{
		u32 i = 0;
		FunctionPointerPool.clear();
		WordConstantPool.clear();
		DWordConstantPool.clear();
		Bytecode.clear();

		u16 WordPoolSize = *reinterpret_cast<u16*>(program.data() + i); i += sizeof(u16);
		u16 DWordPoolSize = *reinterpret_cast<u16*>(program.data() + i); i += sizeof(u16);
		u16 FunctionPointerPoolSize = *reinterpret_cast<u16*>(program.data() + i); i += sizeof(u16);

		for (u16 j = 0; j < WordPoolSize; j++)
			WordConstantPool.push_back(*reinterpret_cast<Word*>(program.data() + i + j * sizeof(Word)));
		i += WordPoolSize * sizeof(Word);

		for (u16 j = 0; j < DWordPoolSize; j++)
			DWordConstantPool.push_back(*reinterpret_cast<DWord*>(program.data() + i + j * sizeof(DWord)));
		i += DWordPoolSize * sizeof(DWord);

		for (u16 j = 0; j < FunctionPointerPoolSize; j++)
			FunctionPointerPool.push_back(*reinterpret_cast<u32*>(program.data() + i + j * sizeof(u32)));
		i += FunctionPointerPoolSize * sizeof(u32);

		while (i < program.size())
			Bytecode.push_back(program[i++]);	

	}
	void Execute()
	{
		Running = true;
		ProgramCounter = 0;

		while (Running)
		{
			u8 op = GetNextByte().UValue;
			switch (op)
			{
			case OpCodes::exit:
				Exit();
				break;
			#pragma region Push&Pop
			case OpCodes::push_byte_0:
				PushByte0();
				break;
			case OpCodes::push_byte_1:
				PushByte1();
				break;
			case OpCodes::push_byte_2:
				PushByte2();
				break;
			case OpCodes::push_byte_3:
				PushByte3();
				break;
			case OpCodes::push_hword_0:
				PushHWord0();
				break;
			case OpCodes::push_hword_2:
				PushHWord2();
				break;
			case OpCodes::push_word:
				PushWord();
				break;
			case OpCodes::push_word_0:
				PushWord0();
				break;
			case OpCodes::push_word_1:
				PushWord1();
				break;
			case OpCodes::push_word_2:
				PushWord2();
				break;
			case OpCodes::push_word_3:
				PushWord3();
				break;
			case OpCodes::push_dword:
				PushDWord();
				break;
			case OpCodes::push_dword_0:
				PushDWord0();
				break;
			case OpCodes::push_dword_1:
				PushDWord1();
				break;
			case OpCodes::push_dword_2:
				PushDWord2();
				break;
			case OpCodes::push_dword_3:
				PushDWord3();
				break;
			case OpCodes::push_words:
				PushWords();
				break;
			case OpCodes::pop_byte_0:
				PopByte0();
				break;
			case OpCodes::pop_byte_1:
				PopByte1();
				break;
			case OpCodes::pop_byte_2:
				PopByte2();
				break;
			case OpCodes::pop_byte_3:
				PopByte3();
				break;
			case OpCodes::pop_hword_0:
				PopHWord0();
				break;
			case OpCodes::pop_hword_2:
				PopHWord2();
				break;
			case OpCodes::pop_word:
				PopWord();
				break;
			case OpCodes::pop_word_0:
				PopWord0();
				break;
			case OpCodes::pop_word_1:
				PopWord1();
				break;
			case OpCodes::pop_word_2:
				PopWord2();
				break;
			case OpCodes::pop_word_3:
				PopWord3();
				break;
			case OpCodes::pop_dword:
				PopDWord();
				break;
			case OpCodes::pop_dword_0:
				PopDWord0();
				break;
			case OpCodes::pop_dword_1:
				PopDWord1();
				break;
			case OpCodes::pop_dword_2:
				PopDWord2();
				break;
			case OpCodes::pop_dword_3:
				PopDWord3();
				break;
			case OpCodes::pop_words:
				PopWords();
				break;
			case OpCodes::push_word_value_0:
				PushWordValue0();
				break;
			case OpCodes::push_dword_value_0:
				PushDWordValue0();
				break;
			case OpCodes::push_i32_1:
				PushI32_1();
				break;
			case OpCodes::push_i32_2:
				PushI32_2();
				break;
			case OpCodes::push_i64_1:
				PushI64_1();
				break;
			case OpCodes::push_i64_2:
				PushI64_2();
				break;
			case OpCodes::push_f32_1:
				PushF32_1();
				break;
			case OpCodes::push_f32_2:
				PushF32_2();
				break;
			case OpCodes::push_f64_1:
				PushF64_1();
				break;
			case OpCodes::push_f64_2:
				PushF64_2();
				break;
			case OpCodes::push_i8_as_i32:
				PushI8AsI32();
				break;
			case OpCodes::push_i8_as_i64:
				PushI8AsI64();
				break;
			case OpCodes::push_word_from_pool:
				PushWordFromPool();
				break;
			case OpCodes::push_word_from_pool_wide:
				PushWordFromPoolWide();
				break;
			case OpCodes::push_dword_from_pool:
				PushDWordFromPool();
				break;
			case OpCodes::push_dword_from_pool_wide:
				PushDWordFromPoolWide();
				break;
#pragma endregion
			#pragma region Dup&Swap
			case OpCodes::dup_word:
				DupWord();
				break;
			case OpCodes::dup_word_x1:
				DupWordX1();
				break;
			case OpCodes::dup_word_x2:
				DupWordX2();
				break;
			case OpCodes::dup_dword:
				DupDWord();
				break;
			case OpCodes::dup_dword_x1:
				DupDWordX1();
				break;
			case OpCodes::dup_dword_x2:
				DupDWordX2();
				break;
			case OpCodes::swap_word:
				SwapWord();
				break;
			case OpCodes::swap_dword:
				SwapDWord();
				break;
#pragma endregion
			#pragma region Load&Store
			case OpCodes::get_address:
				GetAddress();
				break;
			case OpCodes::load_byte_0:
				LoadByte0();
				break;
			case OpCodes::load_byte_1:
				LoadByte1();
				break;
			case OpCodes::load_byte_2:
				LoadByte2();
				break;
			case OpCodes::load_byte_3:
				LoadByte3();
				break;
			case OpCodes::load_hword_0:
				LoadHWord0();
				break;
			case OpCodes::load_hword_2:
				LoadHWord2();
				break;
			case OpCodes::load_word:
				LoadWord();
				break;
			case OpCodes::load_dword:
				LoadDWord();
				break;
			case OpCodes::store_byte_0:
				StoreByte0();
				break;
			case OpCodes::store_byte_1:
				StoreByte1();
				break;
			case OpCodes::store_byte_2:
				StoreByte2();
				break;
			case OpCodes::store_byte_3:
				StoreByte3();
				break;
			case OpCodes::store_hword_0:
				StoreHWord0();
				break;
			case OpCodes::store_hword_2:
				StoreHWord2();
				break;
			case OpCodes::store_word:
				StoreWord();
				break;
			case OpCodes::store_dword:
				StoreDWord();
				break;
#pragma endregion
			#pragma region Arithmetics
			case OpCodes::add_i32:
				AddI32();
				break;
			case OpCodes::add_i64:
				AddI64();
				break;
			case OpCodes::add_f32:
				AddF32();
				break;
			case OpCodes::add_f64:
				AddF64();
				break;
			case OpCodes::inc_i32:
				IncI32();
				break;
			case OpCodes::inc_i64:
				IncI64();
				break;
			case OpCodes::inc_f32:
				IncF32();
				break;
			case OpCodes::inc_f64:
				IncF64();
				break;
			case OpCodes::sub_i32:
				SubI32();
				break;
			case OpCodes::sub_i64:
				SubI64();
				break;
			case OpCodes::sub_f32:
				SubF32();
				break;
			case OpCodes::sub_f64:
				SubF64();
				break;
			case OpCodes::dec_i32:
				DecI32();
				break;
			case OpCodes::dec_i64:
				DecI64();
				break;
			case OpCodes::dec_f32:
				DecF32();
				break;
			case OpCodes::dec_f64:
				DecF64();
				break;
			case OpCodes::mul_i32:
				MulI32();
				break;
			case OpCodes::mul_i64:
				MulI64();
				break;
			case OpCodes::mul_u32:
				MulU32();
				break;
			case OpCodes::mul_u64:
				MulU64();
				break;
			case OpCodes::mul_f32:
				MulF32();
				break;
			case OpCodes::mul_f64:
				MulF64();
				break;
			case OpCodes::div_i32:
				DivI32();
				break;
			case OpCodes::div_i64:
				DivI64();
				break;
			case OpCodes::div_u32:
				DivU32();
				break;
			case OpCodes::div_u64:
				DivU64();
				break;
			case OpCodes::div_f32:
				DivF32();
				break;
			case OpCodes::div_f64:
				DivF64();
				break;
			case OpCodes::mod_i32:
				ModI32();
				break;
			case OpCodes::mod_i64:
				ModI64();
				break;
			case OpCodes::mod_u32:
				ModU32();
				break;
			case OpCodes::mod_u64:
				ModU64();
				break;
			case OpCodes::mod_f32:
				ModF32();
				break;
			case OpCodes::mod_f64:
				ModF64();
				break;
			case OpCodes::neg_i32:
				NegI32();
				break;
			case OpCodes::neg_i64:
				NegI64();
				break;
			case OpCodes::neg_f32:
				NegF32();
				break;
			case OpCodes::neg_f64:
				NegF64();
				break;
#pragma endregion
			#pragma region Bitwise
			case OpCodes::and_word:
				AndWord();
				break;
			case OpCodes::and_dword:
				AndDWord();
				break;
			case OpCodes::or_word:
				OrWord();
				break;
			case OpCodes::or_dword:
				OrDWord();
				break;
			case OpCodes::xor_word:
				XorWord();
				break;
			case OpCodes::xor_dword:
				XorDWord();
				break;
			case OpCodes::not_word:
				NotWord();
				break;
			case OpCodes::not_dword:
				NotDWord();
				break;
			case OpCodes::shl_word:
				ShlWord();
				break;
			case OpCodes::shl_dword:
				ShlDWord();
				break;
			case OpCodes::shr_i32:
				ShrI32();
				break;
			case OpCodes::shr_u32:
				ShrU32();
				break;
			case OpCodes::shr_i64:
				ShrI64();
				break;
			case OpCodes::shr_u64:
				ShrU64();
				break;
#pragma endregion
			#pragma region Jumps
			case OpCodes::jmp:
				Jmp();
				break;
			case OpCodes::jmp_i32_eq:
				JmpI32Eq();
				break;
			case OpCodes::jmp_i32_ne:
				JmpI32Ne();
				break;
			case OpCodes::jmp_i32_gt:
				JmpI32Gt();
				break;
			case OpCodes::jmp_i32_lt:
				JmpI32Lt();
				break;
			case OpCodes::jmp_i32_ge:
				JmpI32Ge();
				break;
			case OpCodes::jmp_i32_le:
				JmpI32Le();
				break;
			case OpCodes::jmp_u32_gt:
				JmpU32Gt();
				break;
			case OpCodes::jmp_u32_lt:
				JmpU32Lt();
				break;
			case OpCodes::jmp_u32_ge:
				JmpU32Ge();
				break;
			case OpCodes::jmp_u32_le:
				JmpU32Le();
				break;
			case OpCodes::jmp_i64_eq:
				JmpI64Eq();
				break;
			case OpCodes::jmp_i64_ne:
				JmpI64Ne();
				break;
			case OpCodes::jmp_i64_gt:
				JmpI64Gt();
				break;
			case OpCodes::jmp_i64_lt:
				JmpI64Lt();
				break;
			case OpCodes::jmp_i64_ge:
				JmpI64Ge();
				break;
			case OpCodes::jmp_i64_le:
				JmpI64Le();
				break;
			case OpCodes::jmp_u64_gt:
				JmpU64Gt();
				break;
			case OpCodes::jmp_u64_lt:
				JmpU64Lt();
				break;
			case OpCodes::jmp_u64_ge:
				JmpU64Ge();
				break;
			case OpCodes::jmp_u64_le:
				JmpU64Le();
				break;
#pragma endregion
			#pragma region Calls
			case OpCodes::call:
				Call();
				break;
			case OpCodes::syscall:
				SysCall();
				break;
			case OpCodes::return_void:
				ReturnVoid();
				break;
			case OpCodes::return_byte:
				ReturnByte();
				break;
			case OpCodes::return_hword:
				ReturnHWord();
				break;
			case OpCodes::return_word:
				ReturnWord();
				break;
			case OpCodes::return_dword:
				ReturnDWord();
				break;
			case OpCodes::return_words:
				ReturnWords();
				break;
#pragma endregion
			#pragma region Casts
			case OpCodes::i32_to_i64:
				I32ToI64();
				break;
			case OpCodes::i32_to_f32:
				I32ToF32();
				break;
			case OpCodes::i32_to_f64:
				I32ToF64();
				break;
			case OpCodes::i64_to_i32:
				I64ToI32();
				break;
			case OpCodes::i64_to_f32:
				I64ToF32();
				break;
			case OpCodes::i64_to_f64:
				I64ToF64();
				break;
			case OpCodes::f32_to_i32:
				F32ToI32();
				break;
			case OpCodes::f32_to_i64:
				F32ToI64();
				break;
			case OpCodes::f32_to_f64:
				F32ToF64();
				break;
			case OpCodes::f64_to_i32:
				F64ToI32();
				break;
			case OpCodes::f64_to_i64:
				F64ToI64();
				break;
			case OpCodes::f64_to_f32:
				F64ToF32();
				break;
#pragma endregion
			default:
				ASSERT(false, "Unknown opcode: %d\n", op);
				Exit();
				break;
			}
		}
	}
	
	int RunTest()
	{
		Link(OpCodes::PrintSumCast);
		Execute();
		std::cout << "\n";
		return 0;
	}

	void Exit() { Running = false; }
	#pragma region Push&Pop
	void PushByte0() { OperationStack::PushW(FunctionStack::LocalB0(GetNextByte().UValue)); }
	void PushByte1() { OperationStack::PushW(FunctionStack::LocalB1(GetNextByte().UValue)); }
	void PushByte2() { OperationStack::PushW(FunctionStack::LocalB2(GetNextByte().UValue)); }
	void PushByte3() { OperationStack::PushW(FunctionStack::LocalB3(GetNextByte().UValue)); }
	void PushHWord0() { OperationStack::PushW(FunctionStack::LocalH0(GetNextByte().UValue)); }
	void PushHWord2() { OperationStack::PushW(FunctionStack::LocalH2(GetNextByte().UValue)); }
	void PushWord() { OperationStack::PushW(FunctionStack::LocalW(GetNextByte().UValue)); }
	void PushWord0() { OperationStack::PushW(FunctionStack::LocalW(0)); }
	void PushWord1() { OperationStack::PushW(FunctionStack::LocalW(1)); }
	void PushWord2() { OperationStack::PushW(FunctionStack::LocalW(2)); }
	void PushWord3() { OperationStack::PushW(FunctionStack::LocalW(3)); }
	void PushDWord() { OperationStack::PushD(FunctionStack::LocalD(GetNextByte().UValue)); }
	void PushDWord0() { OperationStack::PushD(FunctionStack::LocalD(0)); }
	void PushDWord1() { OperationStack::PushD(FunctionStack::LocalD(1)); }
	void PushDWord2() { OperationStack::PushD(FunctionStack::LocalD(2)); }
	void PushDWord3() { OperationStack::PushD(FunctionStack::LocalD(3)); }
	void PushWords()
	{
		HWord params = GetNextHWord();
		OperationStack::PushWs(&FunctionStack::LocalW(params.B.Value0.UValue), params.B.Value1.UValue);
	}
	void PushWordValue0() { OperationStack::PushW(0); }
	void PushDWordValue0() { OperationStack::PushD(0); }
	void PushI32_1() { OperationStack::PushW(1); }
	void PushI32_2() { OperationStack::PushW(2); }
	void PushI64_1() { OperationStack::PushD(1); }
	void PushI64_2() { OperationStack::PushD(2); }
	void PushF32_1() { OperationStack::PushW(1.0f); }
	void PushF32_2() { OperationStack::PushW(2.0f); }
	void PushF64_1() { OperationStack::PushD(1.0); }
	void PushF64_2() { OperationStack::PushD(2.0); }
	void PushI8AsI32() { OperationStack::PushW(GetNextByte().IValue); }
	void PushI8AsI64() { OperationStack::PushD(GetNextByte().IValue); }
	void PushWordFromPool() { OperationStack::PushW(WordConstantPool[GetNextByte().UValue]); }
	void PushWordFromPoolWide() { OperationStack::PushW(WordConstantPool[GetNextHWord().UValue]); }
	void PushDWordFromPool() { OperationStack::PushD(DWordConstantPool[GetNextByte().UValue]); }
	void PushDWordFromPoolWide() { OperationStack::PushD(DWordConstantPool[GetNextHWord().UValue]); }

	void PopByte0()
	{
		FunctionStack::LocalB0(GetNextByte().UValue).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopByte1()
	{
		FunctionStack::LocalB1(GetNextByte().UValue).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopByte2()
	{
		FunctionStack::LocalB2(GetNextByte().UValue).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopByte3()
	{
		FunctionStack::LocalB3(GetNextByte().UValue).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopHWord0()
	{
		FunctionStack::LocalH0(GetNextByte().UValue).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopHWord2()
	{
		FunctionStack::LocalH2(GetNextByte().UValue).UValue = OperationStack::TopW().UValue;
		OperationStack::PopW();
	}
	void PopWord()
	{
		FunctionStack::LocalW(GetNextByte().UValue) = OperationStack::TopW();
		OperationStack::PopW();
	}
	void PopWord0()
	{
		FunctionStack::LocalW(0) = OperationStack::TopW();
		OperationStack::PopW();
	}
	void PopWord1()
	{
		FunctionStack::LocalW(1) = OperationStack::TopW();
		OperationStack::PopW();
	}
	void PopWord2()
	{
		FunctionStack::LocalW(2) = OperationStack::TopW();
		OperationStack::PopW();
	}
	void PopWord3()
	{
		FunctionStack::LocalW(3) = OperationStack::TopW();
		OperationStack::PopW();
	}
	void PopDWord()
	{
		FunctionStack::LocalD(GetNextByte().UValue) = OperationStack::TopD();
		OperationStack::PopD();
	}
	void PopDWord0()
	{
		FunctionStack::LocalD(0) = OperationStack::TopD();
		OperationStack::PopD();
	}
	void PopDWord1()
	{
		FunctionStack::LocalD(1) = OperationStack::TopD();
		OperationStack::PopD();
	}
	void PopDWord2()
	{
		FunctionStack::LocalD(2) = OperationStack::TopD();
		OperationStack::PopD();
	}
	void PopDWord3()
	{
		FunctionStack::LocalD(3) = OperationStack::TopD();
		OperationStack::PopD();
	}
	void PopWords()
	{
		HWord params = GetNextHWord();
		u32 count = params.B.Value1.UValue;
		std::memcpy(&FunctionStack::LocalW(params.B.Value0.UValue), OperationStack::TopWs(count), count * sizeof(Word));
		OperationStack::PopWs(count);
	}
#pragma endregion
	#pragma region Dup&Swap
	void DupWord() { OperationStack::DupW(); }
	void DupWordX1() { OperationStack::DupWX1(); }
	void DupWordX2() { OperationStack::DupWX2(); }
	void DupDWord() { OperationStack::DupD(); }
	void DupDWordX1() { OperationStack::DupDX1(); }
	void DupDWordX2() { OperationStack::DupDX2(); }
	void SwapWord() { OperationStack::SwapW(); }
	void SwapDWord() { OperationStack::SwapD(); }
#pragma endregion
	#pragma region Load&Store
	void GetAddress() { OperationStack::PushD(reinterpret_cast<u64>(&FunctionStack::LocalW(Bytecode[ProgramCounter++]))); }
	void LoadByte0() { OperationStack::LoadB0(); }
	void LoadByte1() { OperationStack::LoadB1(); }
	void LoadByte2() { OperationStack::LoadB2(); }
	void LoadByte3() { OperationStack::LoadB3(); }
	void LoadHWord0() { OperationStack::LoadH0(); }
	void LoadHWord2() { OperationStack::LoadH2(); }
	void LoadWord() { OperationStack::LoadW(); }
	void LoadDWord() { OperationStack::LoadD(); }
	void StoreByte0() { OperationStack::StoreB0(); }
	void StoreByte1() { OperationStack::StoreB1(); }
	void StoreByte2() { OperationStack::StoreB2(); }
	void StoreByte3() { OperationStack::StoreB3(); }
	void StoreHWord0() { OperationStack::StoreH0(); }
	void StoreHWord2() { OperationStack::StoreH2(); }
	void StoreWord() { OperationStack::StoreW(); }
	void StoreDWord() { OperationStack::StoreD(); }
#pragma endregion
	#pragma region Aritmetics
	void AddI32() { OperationStack::AddI32(); }
	void AddI64() { OperationStack::AddI64(); }
	void AddF32() { OperationStack::AddF32(); }
	void AddF64() { OperationStack::AddF64(); }
	void IncI32() 
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalW(reg).IValue++;
	}
	void IncI64()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalD(reg).IValue++;
	}
	void IncF32()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalW(reg).FValue++;
	}
	void IncF64()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalD(reg).FValue++;
	}

	void SubI32() { OperationStack::SubI32(); }
	void SubI64() { OperationStack::SubI64(); }
	void SubF32() { OperationStack::SubF32(); }
	void SubF64() { OperationStack::SubF64(); }
	void DecI32()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalW(reg).IValue--;
	}
	void DecI64()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalD(reg).IValue--;
	}
	void DecF32()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalW(reg).FValue--;
	}
	void DecF64()
	{
		u8 reg = GetNextByte().UValue;
		FunctionStack::LocalD(reg).FValue--;
	}

	void MulI32() { OperationStack::MulI32(); }
	void MulI64() { OperationStack::MulI64(); }
	void MulU32() { OperationStack::MulU32(); }
	void MulU64() { OperationStack::MulU64(); }
	void MulF32() { OperationStack::MulF32(); }
	void MulF64() { OperationStack::MulF64(); }

	void DivI32() { OperationStack::DivI32(); }
	void DivI64() { OperationStack::DivI64(); }
	void DivU32() { OperationStack::DivU32(); }
	void DivU64() { OperationStack::DivU64(); }
	void DivF32() { OperationStack::DivF32(); }
	void DivF64() { OperationStack::DivF64(); }

	void ModI32() { OperationStack::ModI32(); }
	void ModU32() { OperationStack::ModI64(); }
	void ModI64() { OperationStack::ModU32(); }
	void ModU64() { OperationStack::ModU64(); }
	void ModF32() { OperationStack::ModF32(); }
	void ModF64() { OperationStack::ModF64(); }

	void NegI32() { OperationStack::NegI32(); }
	void NegI64() { OperationStack::NegI64(); }
	void NegF32() { OperationStack::NegF32(); }
	void NegF64() { OperationStack::NegF64(); }
#pragma endregion
	#pragma region Bitwise
	void AndWord()  { OperationStack::AndW();   }
	void AndDWord() { OperationStack::AndW();   }
	void OrWord()   { OperationStack::OrW();    }
	void OrDWord()  { OperationStack::OrD();    }
	void XorWord()  { OperationStack::XorW();   }
	void XorDWord() { OperationStack::XorD();   }
	void NotWord()  { OperationStack::NotW();   }
	void NotDWord() { OperationStack::NotD();   }
	void ShlWord()  { OperationStack::ShlW();   }
	void ShlDWord() { OperationStack::ShlD();   }
	void ShrI32()   { OperationStack::ShrI32(); }
	void ShrU32()   { OperationStack::ShrU32(); }
	void ShrI64()   { OperationStack::ShrI64(); }
	void ShrU64()   { OperationStack::ShrU64(); }
#pragma endregion	
	#pragma region Jumps
	inline static void Jump(i16 offset)
	{
		ProgramCounter += offset;
	}
	void Jmp()
	{
		i16 offset = GetNextHWord().IValue;
		Jump(offset);
	}

	void JmpI32Eq()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::EqI32())
			Jump(offset);
	}
	void JmpI32Ne()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::NeI32())
			Jump(offset);
	}
	void JmpI32Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtI32())
			Jump(offset);
	}
	void JmpI32Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtI32())
			Jump(offset);
	}
	void JmpI32Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeI32())
			Jump(offset);
	}
	void JmpI32Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeI32())
			Jump(offset);
	}

	void JmpU32Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtU32())
			Jump(offset);
	}
	void JmpU32Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtU32())
			Jump(offset);
	}
	void JmpU32Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeU32())
			Jump(offset);
	}
	void JmpU32Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeU32())
			Jump(offset);
	}

	void JmpI64Eq()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::EqI64())
			Jump(offset);
	}
	void JmpI64Ne()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::NeI64())
			Jump(offset);
	}
	void JmpI64Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtI64())
			Jump(offset);
	}
	void JmpI64Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtI64())
			Jump(offset);
	}
	void JmpI64Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeI64())
			Jump(offset);
	}
	void JmpI64Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeI64())
			Jump(offset);
	}

	void JmpU64Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtU64())
			Jump(offset);
	}
	void JmpU64Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtU64())
			Jump(offset);
	}
	void JmpU64Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeU64())
			Jump(offset);
	}
	void JmpU64Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeU64())
			Jump(offset);
	}

	void JmpF32Eq()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::EqF32())
			Jump(offset);
	}
	void JmpF32Ne()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::NeF32())
			Jump(offset);
	}
	void JmpF32Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtF32())
			Jump(offset);
	}
	void JmpF32Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtF32())
			Jump(offset);
	}
	void JmpF32Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeF32())
			Jump(offset);
	}
	void JmpF32Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeF32())
			Jump(offset);
	}

	void JmpF64Eq()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::EqF64())
			Jump(offset);
	}
	void JmpF64Ne()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::NeF64())
			Jump(offset);
	}
	void JmpF64Gt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GtF64())
			Jump(offset);
	}
	void JmpF64Lt()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LtF64())
			Jump(offset);
	}
	void JmpF64Ge()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::GeF64())
			Jump(offset);
	}
	void JmpF64Le()
	{
		i16 offset = GetNextHWord().IValue;
		if(OperationStack::LeF64())
			Jump(offset);
	}

#pragma endregion	
	#pragma region FunctionCall
	void Call()
	{
		u16 funcID = GetNextHWord().UValue;
		u32 funcPointer = FunctionPointerPool[funcID];

		PrevStackStates.push(
			{
				ProgramCounter,
				FunctionStack::BasePointer,
				OperationStack::BasePointer
			});

		ProgramCounter = funcPointer;
		u8 argSize = GetNextByte().UValue;
		u8 localSize = GetNextByte().UValue;

		Word* data = OperationStack::TopWs(argSize);
		FunctionStack::PushData(data, argSize);
		FunctionStack::OnCall(localSize);
		OperationStack::PopWs(argSize);
		OperationStack::OnCall();

	}
	void SysCall()
	{
		switch (GetNextByte().UValue)
		{
		case 1: PrintString(); break;
		case 2: PrintI64(); break;
		case 3: PrintF64(); break;
		case 4: CallSqrtF32(); break;
		case 5: CallSqrtF64(); break;
		default: ASSERT(true, "System call function not implemented!"); break;
		}
	}
	void ReturnVoid()
	{
		StackState& prevState = PrevStackStates.top();

		FunctionStack::OnReturn(prevState.FunctionStackBasePointer);
		OperationStack::OnReturn(prevState.OperationStackBasePointer);

		ProgramCounter = prevState.ProgramCounter;
		PrevStackStates.pop();
	
	}
	void ReturnByte()
	{
		StackState& prevState = PrevStackStates.top();
		u8 ret = OperationStack::TopW().UValue; OperationStack::PopW();

		FunctionStack::OnReturn(prevState.FunctionStackBasePointer);
		OperationStack::OnReturn(prevState.OperationStackBasePointer);
		OperationStack::PushW(ret);

		ProgramCounter = prevState.ProgramCounter;
		PrevStackStates.pop();
	}
	void ReturnHWord()
	{
		StackState& prevState = PrevStackStates.top();
		u16 ret = OperationStack::TopW().UValue; OperationStack::PopW();

		FunctionStack::OnReturn(prevState.FunctionStackBasePointer);
		OperationStack::OnReturn(prevState.OperationStackBasePointer);
		OperationStack::PushW(ret);

		ProgramCounter = prevState.ProgramCounter;
		PrevStackStates.pop();
	}
	void ReturnWord()
	{
		StackState& prevState = PrevStackStates.top();
		Word ret = OperationStack::TopW(); OperationStack::PopW();

		FunctionStack::OnReturn(prevState.FunctionStackBasePointer);
		OperationStack::OnReturn(prevState.OperationStackBasePointer);
		OperationStack::PushW(ret);

		ProgramCounter = prevState.ProgramCounter;
		PrevStackStates.pop();
	}
	void ReturnDWord()
	{
		StackState& prevState = PrevStackStates.top();
		DWord ret = OperationStack::TopD(); OperationStack::PopD();

		FunctionStack::OnReturn(prevState.FunctionStackBasePointer);
		OperationStack::OnReturn(prevState.OperationStackBasePointer);
		OperationStack::PushD(ret);

		ProgramCounter = prevState.ProgramCounter;
		PrevStackStates.pop();
	}
	void ReturnWords()
	{
		StackState& prevState = PrevStackStates.top();
		u8 count = Bytecode[ProgramCounter++];
		Word* ret = OperationStack::TopWs(count); OperationStack::PopWs(count);

		FunctionStack::OnReturn(prevState.FunctionStackBasePointer);
		OperationStack::OnReturn(prevState.OperationStackBasePointer);
		OperationStack::PushWs(ret, count);

		ProgramCounter = prevState.ProgramCounter;
		PrevStackStates.pop();
	}
#pragma endregion
	#pragma region SystemCalls
	void PrintString()
	{
		std::cout << reinterpret_cast<const char*>(OperationStack::TopD().UValue);
		OperationStack::PopD();
	}
	void PrintI64()
	{
		std::cout << OperationStack::TopD().IValue;
		OperationStack::PopD();
	}
	void PrintF64()
	{
		std::cout << OperationStack::TopD().FValue;
		OperationStack::PopD();
	}
	void CallSqrtF32()
	{
		OperationStack::TopW().FValue = std::sqrt(OperationStack::TopW().FValue);
	}
	void CallSqrtF64()
	{
		OperationStack::TopD().FValue = std::sqrt(OperationStack::TopD().FValue);
	}
#pragma endregion
	#pragma region Casts
	void I32ToI64() { OperationStack::PushW(0); }
	void I32ToF32() { OperationStack::TopW().FValue = static_cast<f32>(OperationStack::TopW().IValue); }
	void I32ToF64() 
	{ 
		i32 v = OperationStack::TopW().IValue; OperationStack::PopW();
		OperationStack::PushD(static_cast<f64>(v));
	}
	void I64ToI32() { OperationStack::PopW(); }
	void I64ToF32()
	{
		OperationStack::TopW(1).FValue = static_cast<f32>(OperationStack::TopD().IValue);
		OperationStack::PopW();
	}
	void I64ToF64() { OperationStack::TopD().FValue = static_cast<f64>(OperationStack::TopD().IValue); }
	void F32ToI32() { OperationStack::TopW().IValue = static_cast<i32>(OperationStack::TopW().FValue); }
	void F32ToI64()
	{
		f32 v = OperationStack::TopW().FValue; OperationStack::PopW();
		OperationStack::PushD(static_cast<i64>(v));
	}
	void F32ToF64()
	{
		f32 v = OperationStack::TopW().FValue; OperationStack::PopW();
		OperationStack::PushD(static_cast<f64>(v));
	}
	void F64ToI32()
	{
		OperationStack::TopW(1).IValue = (i32)OperationStack::TopD().FValue;
		OperationStack::PopW();
	}
	void F64ToI64() { OperationStack::TopD().IValue = static_cast<i64>(OperationStack::TopD().FValue); }
	void F64ToF32()
	{
		f64 v = OperationStack::TopD().FValue; OperationStack::PopW();
		OperationStack::TopW().FValue = static_cast<f32>(v);
	}

#pragma endregion
}