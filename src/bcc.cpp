#include "bcc.hpp"

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        BCC::Compile(BYTECODES_DIR"/test.bs", BYTECODES_DIR"/test.be");
    }
    else if(argc == 3)
    {
        BCC::Compile(argv[1], argv[2]);
    }
    else
    {
        std::cerr << "Usage: bcc <input_file> <output_file>" << std::endl;
        return 1;
    }
}