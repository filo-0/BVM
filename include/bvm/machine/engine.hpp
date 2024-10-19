#pragma once

#include <vector>

#include "types.hpp"
#include "opcodes.hpp"

namespace BVM::Machine
{
    /* Contains data on the program stack to return from functions. */
	struct StackState
	{
		u32 ProgramCounter;
		u32 FunctionStackBasePointer;
		u32 OperationStackBasePointer;
	};

    extern bool                    Running;
	extern u32                     ProgramCounter;
	extern std::vector<u8>         Bytecode;
	extern std::vector<u32>        FunctionPointerPool;
	extern std::vector<Word>       WordConstantPool;
	extern std::vector<DWord>      DWordConstantPool;
	extern std::vector<StackState> PrevStackStates;

	std::vector<opcode> GetBytecodeFromFile(const std::string& path);
    void Load(std::vector<opcode>& program);
    void Execute();
} // namespace BVM::Machine
