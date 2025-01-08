
#include "bvm/machine.hpp"
#include "bvm/instruction_table.hpp"

namespace BVM
{
	bool                     Running = true;
	u32                      ProgramCounter = 0;
	std::vector<u8>          Bytecode;
	std::vector<u32>         FunctionPointerPool;
	std::vector<Word>        WordConstantPool;
	std::vector<DWord>       DWordConstantPool;
	std::vector<std::string> StringConstantPool;

    std::vector<opcode> GetBytecodeFromFile(const std::string& path);
    void Load(std::vector<opcode>& program);
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
		i += (u16)(WordPoolSize * sizeof(Word));

		for (u16 j = 0; j < DWordPoolSize; j++)
			DWordConstantPool.push_back(*reinterpret_cast<DWord*>(program.data() + i + j * sizeof(DWord)));
		i += (u16)(DWordPoolSize * sizeof(DWord));

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
		i += (u16)(FunctionPointerPoolSize * sizeof(u32));

		Bytecode.reserve(program.size() - i);
		while (i < program.size())
			Bytecode.push_back(program[i++]);	

	}
	void Execute()
	{
		Running = true;
		ProgramCounter = 0;

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