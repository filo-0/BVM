#pragma once

#include "std.hpp"
#include "types.hpp"
#include "opcodes.hpp"

namespace BVM
{
    extern bool                      Running;
	extern u32                       ProgramCounter;
	extern std::vector<u8>           Bytecode;
	extern std::vector<u32>          FunctionPointerPool;
	extern std::vector<Word*>		 GlobalVariablePool;
	extern std::vector<Word>         WordConstantPool;
	extern std::vector<DWord>        DWordConstantPool;
	extern std::vector<char*>        StringConstantPool;

	void Run(const std::string& executable_path);

    Byte  GetNextByte();
	HWord GetNextHWord();
	Word  GetNextWord();
} // namespace BVM