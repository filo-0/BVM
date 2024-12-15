#include "bvm.hpp"

int main(int argc, char** argv)
{
#ifdef _DEBUG
	std::cout << "BVM Debug Build" << std::endl;
#else
	std::cout << "BVM Release Build" << std::endl;
#endif

	if(argc == 1)
	{
		BVM::Run(BYTECODES_DIR"/test.be");
	}
	else if (argc == 2)
	{
		BVM::Run(argv[1]);
	}
	else
	{
		std::cerr << "Usage: bvm <input_file>" << std::endl;
		return 1;
	}
	return 0;
}