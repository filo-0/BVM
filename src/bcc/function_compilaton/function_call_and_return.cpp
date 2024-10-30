#include "bcc/function_compilation.hpp"
#include "bcc/compiler.hpp"

namespace BCC::Compiler
{
    const std::unordered_map<std::string, opcode> ReturnCodes
    {
        { "byte",  OpCodes::return_byte  },
        { "hword",  OpCodes::return_hword  },
        { "word",  OpCodes::return_word  },
        { "dword",  OpCodes::return_dword  }
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
        GetCurrentFunctionOpcodesList().push_back(OpCodes::syscall);
        if(SyscallsCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(SyscallsCodes.at(tokens[1]));
        else
            PushError("Invalid <s> parameter {see syscall list}", tokens[1]);
    }
    void Return(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
            GetCurrentFunctionOpcodesList().push_back(OpCodes::return_void);
        else if(ReturnCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(ReturnCodes.at(tokens[1]));
        else
            PushError("Invalid <t> parameter {byte, hword, word, dword}", tokens[1]);
    }
    void Call(std::vector<std::string>& tokens)
    {
        if(ExistFunction(tokens[1]))
        {
            std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
            opcodes.push_back(OpCodes::call);

            u16 idx = GetFunctionIndex(tokens[1]);
            opcodes.push_back(idx);
            opcodes.push_back(idx >> 8);
        }
        else
            PushError("Function not found", tokens[1]);
    }

} // namespace BCC::Compiler
