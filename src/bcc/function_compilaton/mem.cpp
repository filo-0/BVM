#include "bcc/functions.hpp"
#include "bcc/compiler.hpp"

namespace BCC
{
    void Alloc(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 1)
            PushError("Too many parameters found", tokens[0]);

        GetCurrentFunctionOpcodesList().push_back(OpCodes::alloc);
    }

    void Dealloc(std::vector<std::string>& tokens)
    {
        std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() != 1)
            PushError("Too many parameters found", tokens[0]);

        opcodes.push_back(OpCodes::dealloc);
    }
} // namespace Compiler
