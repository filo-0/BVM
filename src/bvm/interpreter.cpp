
#include "bvm/interpreter.hpp"
#include "bvm/instruction_table.hpp"

namespace BVM
{
	bool                      Running = false;
	u32                       ProgramCounter = 0;
	std::vector<u8>           Bytecode;
	std::vector<u32>          FunctionPointerPool;
	std::vector<Word>         WordConstantPool;
	std::vector<DWord>        DWordConstantPool;
	std::vector<char*>        StringConstantPool;

    std::vector<opcode> GetBytecodeFromFile(const std::string& path);
    void Load(const std::vector<opcode>& program);
    void Execute();

    void Run(const std::string& executable_path)
    {
        std::vector<opcode> bytecode = GetBytecodeFromFile(executable_path);
        Load(bytecode);
        Execute();
    }

	void Exit() { Running = false; }
	void NotImplemented() { std::cout << "Instruction not implemented!\n"; Exit(); }
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
	void Load(const std::vector<opcode>& program)
	{
		u32 i = 0;
		FunctionPointerPool.clear();
		WordConstantPool.clear();
		DWordConstantPool.clear();
		StringConstantPool.clear();
		Bytecode.clear();

		u16 wordPoolSize = *reinterpret_cast<const u16*>(program.data() + i); i += sizeof(u16);
		u16 dWordPoolSize = *reinterpret_cast<const u16*>(program.data() + i); i += sizeof(u16);
		u16 stringPoolSize = *reinterpret_cast<const u16*>(program.data() + i); i += sizeof(u16);
		u16 functionPointerPoolSize = *reinterpret_cast<const u16*>(program.data() + i); i += sizeof(u16);

		WordConstantPool.reserve(wordPoolSize);
		DWordConstantPool.reserve(dWordPoolSize);
		StringConstantPool.reserve(stringPoolSize);
		FunctionPointerPool.reserve(functionPointerPoolSize);

		for (u16 j = 0; j < wordPoolSize; j++)
			WordConstantPool.push_back(*reinterpret_cast<const Word*>(program.data() + i + j * sizeof(Word)));
		i += (u16)(wordPoolSize * sizeof(Word));

		for (u16 j = 0; j < dWordPoolSize; j++)
			DWordConstantPool.push_back(*reinterpret_cast<const DWord*>(program.data() + i + j * sizeof(DWord)));
		i += (u16)(dWordPoolSize * sizeof(DWord));

		for (u16 j = 0; j < stringPoolSize; j++)
		{
			u32 k = 0;
			while(program[i + k] != '\0')
				k++;

			StringConstantPool.push_back((char*)program.data() + i);
			i += k + 1;
		}

		for (u16 j = 0; j < functionPointerPoolSize; j++)
			FunctionPointerPool.push_back(*reinterpret_cast<const u32*>(program.data() + i + j * sizeof(u32)));
		i += (u16)(functionPointerPoolSize * sizeof(u32));

		Bytecode.reserve(program.size() - i);
		while (i < program.size())
			Bytecode.push_back(program[i++]);	

	}
	void Execute()
	{
		Running = true;
		ProgramCounter = 0;

		while (Running)
		{
			u8 op = Bytecode[ProgramCounter++];
			InstructionFunc instruction = InstructionTable[op];
			instruction();
		}
	}

	Byte GetNextByte() { return Bytecode[ProgramCounter++]; }
	HWord GetNextHWord()
	{
		u16 v = Bytecode[ProgramCounter] | (Bytecode[ProgramCounter + 1] << 8);
		ProgramCounter += sizeof(u16);
		return v;
	}
	Word GetNextWord()
	{
		u32 v = Bytecode[ProgramCounter] | (Bytecode[ProgramCounter + 1] << 8) | (Bytecode[ProgramCounter + 2] << 16) | (Bytecode[ProgramCounter + 3] << 24);
		ProgramCounter += sizeof(u32);
		return v;
	}
}