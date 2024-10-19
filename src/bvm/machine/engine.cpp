#include <iostream>
#include <fstream>

#include "bvm/machine.hpp"
#include "assertion.hpp"

namespace BVM::Machine
{
	bool                    Running = true;
	u32                     ProgramCounter = 0;
	std::vector<u8>         Bytecode;
	std::vector<u32>        FunctionPointerPool;
	std::vector<Word>       WordConstantPool;
	std::vector<DWord>      DWordConstantPool;
	std::vector<StackState> PrevStackStates;

	std::vector<opcode> GetBytecodeFromFile(const std::string& path)
	{
		std::vector<opcode> bytecode;
		std::ifstream file(path);

		if (!file.is_open())
		{
			std::cerr << "Failed to open file: " << path << std::endl;
			return bytecode;
		}

		while (!file.eof())
		{
			opcode op;
			file.read((char*)&op, sizeof(opcode));
			bytecode.push_back(op);
		}

		file.close();
		return bytecode;
	}

	void Load(std::vector<opcode>& program)
	{
		u32 i = 0;
		FunctionPointerPool.clear();
		WordConstantPool.clear();
		DWordConstantPool.clear();
		Bytecode.clear();

		u16 WordPoolSize = *reinterpret_cast<u16*>(program.data() + i); i += sizeof(u16);
		u16 DWordPoolSize = *reinterpret_cast<u16*>(program.data() + i); i += sizeof(u16);
		u16 FunctionPointerPoolSize = *reinterpret_cast<u16*>(program.data() + i); i += sizeof(u16);

		WordConstantPool.reserve(WordPoolSize);
		DWordConstantPool.reserve(DWordPoolSize);
		FunctionPointerPool.reserve(FunctionPointerPoolSize);

		for (u16 j = 0; j < WordPoolSize; j++)
			WordConstantPool.push_back(*reinterpret_cast<Word*>(program.data() + i + j * sizeof(Word)));
		i += WordPoolSize * sizeof(Word);

		for (u16 j = 0; j < DWordPoolSize; j++)
			DWordConstantPool.push_back(*reinterpret_cast<DWord*>(program.data() + i + j * sizeof(DWord)));
		i += DWordPoolSize * sizeof(DWord);

		for (u16 j = 0; j < FunctionPointerPoolSize; j++)
			FunctionPointerPool.push_back(*reinterpret_cast<u32*>(program.data() + i + j * sizeof(u32)));
		i += FunctionPointerPoolSize * sizeof(u32);

		Bytecode.reserve(program.size() - i);
		while (i < program.size())
			Bytecode.push_back(program[i++]);	

	}
	void Execute()
	{
		Running = true;
		ProgramCounter = 0;
		PrevStackStates.clear();
		PrevStackStates.reserve(1 << 12);

		while (Running)
		{
			u8 op = Bytecode[ProgramCounter++];
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
}