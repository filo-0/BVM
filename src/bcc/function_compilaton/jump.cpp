#include "bcc/functions.hpp"
#include "bcc/compiler.hpp"

namespace BCC
{
    void Label(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No name found", tokens[0]);
            return;
        }

        AddLabelPointer(tokens[1], GetCurrentFunctionOpcodesList().size());

        if (tokens.size() > 2)
            PushError("Too many parameters found", tokens[0]);
    }
    void Jump(std::vector<std::string>& tokens)
    {
        std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 1)
        {
            PushError("No parameter <l> found", tokens[0]);
            return;
        }
        else if(tokens.size() == 2)
        {
            opcodes.push_back(OpCodes::jmp);
            opcodes.push_back(0);
            opcodes.push_back(0);
            AddJump(tokens[2], opcodes.size());
        }
        else if(tokens.size() == 3)
        {   
            if(tokens[1] == "if")
                opcodes.push_back(OpCodes::jmp_if);
            else
            {
                PushError("Invalid jump instruction found", tokens[1]);
                return;
            }

            opcodes.push_back(0);
            opcodes.push_back(0);
            AddJump(tokens[2], opcodes.size());
        }
        else
            PushError("Too many parameters found", tokens[0]);
    }
} // namespace BCC::Compiler
