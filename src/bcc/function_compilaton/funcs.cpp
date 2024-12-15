#include "bcc/functions.hpp"
#include "bcc/compiler.hpp"

namespace BCC
{
    const std::unordered_map<std::string, opcode> ReturnCodes
    {
        { "byte",  OpCodes::return_byte  },
        { "hword",  OpCodes::return_hword  },
        { "word",  OpCodes::return_word  },
        { "dword",  OpCodes::return_dword  },
        { "words", OpCodes::return_words  }
    };
    const std::unordered_map<std::string, opcode> SyscallsCodes
    {
        { "Print",    OpCodes::Syscall::Print    },
        { "PrintI64", OpCodes::Syscall::PrintI64 },
        { "PrintF64", OpCodes::Syscall::PrintF64 },
        { "SqrtF32",  OpCodes::Syscall::SqrtF32  },
        { "SqrtF64",  OpCodes::Syscall::SqrtF64  }
    };

    void Syscall(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 2)
        {
            PushError("Invalid number of parameters {1}", tokens[0]);
            return;
        }

        GetCurrentFunctionOpcodesList().push_back(OpCodes::syscall);
        if(SyscallsCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(SyscallsCodes.at(tokens[1]));
        else
            PushError("Invalid <s> parameter {see syscall list}", tokens[1]);
    }
    void Return(std::vector<std::string>& tokens)
    {
        auto& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 1)
        {
            opcodes.push_back(OpCodes::return_void);
            return;
        }
        
        if(ReturnCodes.contains(tokens[1]))
        {
            opcodes.push_back(ReturnCodes.at(tokens[1]));
            
            if(tokens[1] == "words")
            {
                int count;
                try { count = std::stoi(tokens[2]); }
                catch(std::exception& e)
                {
                    (void)e;
                    PushError("Invalid <n> parameter [0, 255]", tokens[2]);
                    return;
                }
                if(count < 0 || count > 255)
                    PushError("Invalid <n> parameter [0, 255]", tokens[2]);

                opcodes.push_back((opcode)count);

                if(tokens.size() > 3)
                    PushError("Too many parameters found", tokens[0]);
            }
            else if(tokens.size() > 2)
                PushError("Too many parameters found", tokens[0]);
        }
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword}", tokens[1]);
    }
    void Call(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No parameter <f> found {function_name}", tokens[0]);
            return;
        }

        if(ExistFunction(tokens[1]))
        {
            std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
            opcodes.push_back(OpCodes::call);

            u16 idx = GetFunctionIndex(tokens[1]);
            opcodes.push_back((opcode)idx);
            opcodes.push_back((opcode)(idx >> 8));
        }
        else
            PushError("Function not found", tokens[1]);

        if(tokens.size() > 2)
            PushError("Too many parameters found", tokens[0]);
    }
} // namespace BCC::Compiler
