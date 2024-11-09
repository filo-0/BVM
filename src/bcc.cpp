#include <string>
#include <vector>
#include <iostream>

#include "bcc.hpp"
#include "bvm.hpp"

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        BCC::Compiler::Compile("../bytecodes/test.bs", "../bytecodes/test.be");
    }
    else if(argc == 3)
    {
        BCC::Compiler::Compile(argv[1], argv[2]);
    }
    else
    {
        std::cerr << "Usage: bcc <input_file> <output_file>" << std::endl;
        return 1;
    }
    
}