#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>

#include "bvm.hpp"
#include "assertion.hpp"

namespace BVM
{
	bool                    Running = true;
	u32                     ProgramCounter = 0;
	std::vector<u8>         Bytecode;
	std::vector<u32>        FunctionPointerPool;
	std::vector<Word>       WordConstantPool;
	std::vector<DWord>      DWordConstantPool;
	std::vector<std::string> StringConstantPool;
	std::vector<StackState> PrevStackStates;

	void Exit() { Running = false; }
	constexpr InstructionFunc InstructionTable[256] =
	{
		Exit,
		PushByte0,
		PushByte1,
		PushByte2,
		PushByte3,
		PushHWord0,
		PushHWord2,
		PushWord,
		PushWord0,
		PushWord1,
		PushWord2,
		PushWord3,
		PushDWord,
		PushDWord0,
		PushDWord1,
		PushDWord2,
		PushDWord3,
		PushWords,

		PushWordValue0,
		PushDWordValue0,
		PushI32_1,
		PushI32_2,
		PushI64_1,
		PushI64_2,
		PushF32_1,
		PushF32_2,
		PushF64_1,
		PushF64_2,

		PushI8AsI32,
		PushI8AsI64,
		PushWordFromPool,
		PushWordFromPoolWide,
		PushDWordFromPool,
		PushDWordFromPoolWide,
		PushStringFromPool,
		PushStringFromPoolWide,

		PopByte0,
		PopByte1,
		PopByte2,
		PopByte3,
		PopHWord0,
		PopHWord2,
		PopWord,
		PopWord0,
		PopWord1,
		PopWord2,
		PopWord3,
		PopDWord,
		PopDWord0,
		PopDWord1,
		PopDWord2,
		PopDWord3,
		PopWords,

		DupWord,
		DupWordX1,
		DupWordX2,
		DupDWord,
		DupDWordX1,
		DupDWordX2,
		SwapWord,
		SwapDWord,

		GetAddress,
		LoadByte0,
		LoadByte1,
		LoadByte2,
		LoadByte3,
		LoadHWord0,
		LoadHWord2,
		LoadWord,
		LoadDWord,
		StoreByte0,
		StoreByte1,
		StoreByte2,
		StoreByte3,
		StoreHWord0,
		StoreHWord2,
		StoreWord,
		StoreDWord,

		AddI32,
		AddI64,
		AddF32,
		AddF64,
		IncI32,
		IncI64,
		IncF32,
		IncF64,

		SubI32,
		SubI64,
		SubF32,
		SubF64,
		DecI32,
		DecI64,
		DecF32,
		DecF64,

		MulI32,
		MulU32,
		MulI64,
		MulU64,
		MulF32,
		MulF64,

		DivI32,
		DivU32,
		DivI64,
		DivU64,
		DivF32,
		DivF64,

		ModI32,
		ModU32,
		ModI64,
		ModU64,
		ModF32,
		ModF64,

		NegI32,
		NegI64,
		NegF32,
		NegF64,

		AndWord,
		AndDWord,
		OrWord,
		OrDWord,
		XorWord,
		XorDWord,
		NotWord,
		NotDWord,
		ShlWord,
		ShlDWord,
		ShrI32,
		ShrU32,
		ShrI64,
		ShrU64,

		Jmp,

		JmpI32Eq,
		JmpI32Ne,
		JmpI32Lt,
		JmpI32Gt,
		JmpI32Le,
		JmpI32Ge,

		JmpI64Eq,
		JmpI64Ne,
		JmpI64Lt,
		JmpI64Gt,
		JmpI64Le,
		JmpI64Ge,

		JmpF32Eq,
		JmpF32Ne,
		JmpF32Lt,
		JmpF32Gt,
		JmpF32Le,
		JmpF32Ge,

		JmpF64Eq,
		JmpF64Ne,
		JmpF64Lt,
		JmpF64Gt,
		JmpF64Le,
		JmpF64Ge,

		JmpU32Lt,
		JmpU32Gt,
		JmpU32Le,
		JmpU32Ge,

		JmpU64Lt,
		JmpU64Gt,
		JmpU64Le,
		JmpU64Ge,

		Call,
		Exit, // call ext (not implemented)
		SysCall,
		ReturnVoid,
		ReturnByte,
		ReturnHWord,
		ReturnWord,
		ReturnDWord,
		ReturnWords,

		I32ToI64,
		I32ToF32,
		I32ToF64,
		I64ToI32,
		I64ToF32,
		I64ToF64,
		F32ToI32,
		F32ToI64,
		F32ToF64,
		F64ToI32,
		F64ToI64,
		F64ToF32,

		Alloc,
		Dealloc,

		LoadWords,
		StoreWords,

		LoadBufferByteVal,
		LoadBufferHWordVal,
		LoadBufferWordVal,
		LoadBufferDWordVal,
		LoadBufferWordsVal,

		LoadBufferByteRef,
		LoadBufferHWordRef,
		LoadBufferWordRef,
		LoadBufferDWordRef,
		LoadBufferWordsRef,

		StoreBufferByte,
		StoreBufferHWord,
		StoreBufferWord,
		StoreBufferDWord,
		StoreBufferWords,

		LoadOffsetByte0,
		LoadOffsetByte1,
		LoadOffsetByte2,
		LoadOffsetByte3,
		LoadOffsetHWord0,
		LoadOffsetHWord2,
		LoadOffsetWord,
		LoadOffsetDWord,
		LoadOffsetWords,

		StoreOffsetByte0,
		StoreOffsetByte1,
		StoreOffsetByte2,
		StoreOffsetByte3,
		StoreOffsetHWord0,
		StoreOffsetHWord2,
		StoreOffsetWord,
		StoreOffsetDWord,
		StoreOffsetWords,
	};

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
		u16 StringPoolSize = *reinterpret_cast<u16*>(program.data() + i); i += sizeof(u16);
		u16 FunctionPointerPoolSize = *reinterpret_cast<u16*>(program.data() + i); i += sizeof(u16);

		WordConstantPool.reserve(WordPoolSize);
		DWordConstantPool.reserve(DWordPoolSize);
		StringConstantPool.reserve(StringPoolSize);
		FunctionPointerPool.reserve(FunctionPointerPoolSize);

		for (u16 j = 0; j < WordPoolSize; j++)
			WordConstantPool.push_back(*reinterpret_cast<Word*>(program.data() + i + j * sizeof(Word)));
		i += WordPoolSize * sizeof(Word);

		for (u16 j = 0; j < DWordPoolSize; j++)
			DWordConstantPool.push_back(*reinterpret_cast<DWord*>(program.data() + i + j * sizeof(DWord)));
		i += DWordPoolSize * sizeof(DWord);

		for (u16 j = 0; j < StringPoolSize; j++)
		{
			u32 k = 0;
			while(program[i + k] != '\0')
				k++;

			std::string str(reinterpret_cast<char*>(program.data() + i), k);
			StringConstantPool.emplace_back(std::move(str));
			i += k + 1;
		}

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


		auto start = std::chrono::high_resolution_clock::now();
		while (Running)
		{
			u8 op = Bytecode[ProgramCounter++];
			InstructionFunc func = InstructionTable[op];
			func();
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		std::cout << "Execution time : " << duration.count() << "s\n";
	}
	
	Byte GetNextByte() { return Bytecode[ProgramCounter++]; }
	HWord GetNextHWord()
	{
		u16 v = *reinterpret_cast<u16*>(Bytecode.data() + ProgramCounter);
		ProgramCounter += sizeof(u16);
		return v;
	}
	Word GetNextWord()
	{
		u32 v = *reinterpret_cast<u32*>(Bytecode.data() + ProgramCounter);
		ProgramCounter += sizeof(u32);
		return v;
	}
	DWord GetNextDWord()
	{
		u64 v = *reinterpret_cast<u64*>(Bytecode.data() + ProgramCounter);
		ProgramCounter += sizeof(u64);
		return v;
	}
}


int main(int argc, char** argv)
{
#ifdef _DEBUG
	std::cout << "BVM Debug Build" << std::endl;
#endif

	if(argc == 1)
	{
		std::vector<opcode> bytecode = BVM::GetBytecodeFromFile("../bytecodes/test.be");
		BVM::Load(bytecode);
		BVM::Execute();
	}
	else if (argc == 2)
	{
		std::vector<opcode> bytecode = BVM::GetBytecodeFromFile(argv[1]);
		BVM::Load(bytecode);
		BVM::Execute();
	}
	else
	{
		std::cerr << "Usage: bvm <input_file>" << std::endl;
		return 1;
	}
	return 0;
}