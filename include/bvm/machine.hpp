#pragma once

#include "std.hpp"
#include "types.hpp"
#include "opcodes.hpp"

namespace BVM
{
    /* Contains data on the program stack to return from functions. */
	struct StackState
	{
		u32 ProgramCounter;
		u32 FunctionStackBasePointer;
		u32 OperationStackBasePointer;
	};

    extern bool                     Running;
	extern u32                      ProgramCounter;
	extern std::vector<u8>          Bytecode;
	extern std::vector<u32>         FunctionPointerPool;
	extern std::vector<Word>        WordConstantPool;
	extern std::vector<DWord>       DWordConstantPool;
	extern std::vector<std::string> StringConstantPool;
	extern std::vector<StackState>  PrevStackStates;

	void Run(const std::string& executable_path);

    Byte  GetNextByte();
	HWord GetNextHWord();
	Word  GetNextWord();
    DWord GetNextDWord();
} // namespace BVM