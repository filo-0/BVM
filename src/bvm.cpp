#include <iostream>
#include <chrono>
#include "bvm.hpp"

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		std::vector<opcode> bytecode = BVM::Machine::GetBytecodeFromFile("../bytecodes/out/test_out.be");
		BVM::Machine::Load(bytecode);
		BVM::Machine::Execute();
	}
	else if (argc == 2)
	{
		std::vector<opcode> bytecode = BVM::Machine::GetBytecodeFromFile(argv[1]);
		BVM::Machine::Load(bytecode);
		BVM::Machine::Execute();
	}
	else
	{
		std::cerr << "Usage: bvm <input_file>" << std::endl;
		return 1;
	}
	return 0;
}