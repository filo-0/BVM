#include "bcc/function_compilation.hpp"
#include "bcc/compiler.hpp"

namespace BCC::Compiler
{
    const std::unordered_map<std::string, opcode> AndCodes
    {
        { "word", OpCodes::and_word },
        { "dword", OpCodes::and_dword }
    };
    const std::unordered_map<std::string, opcode> OrCodes
    {
        { "word", OpCodes::or_word },
        { "dword", OpCodes::or_dword }
    };
    const std::unordered_map<std::string, opcode> XorCodes
    {
        { "word", OpCodes::xor_word },
        { "dword", OpCodes::xor_dword }
    };
    const std::unordered_map<std::string, opcode> NotCodes
    {
        { "word", OpCodes::not_word },
        { "dword", OpCodes::not_dword }
    };
    const std::unordered_map<std::string, opcode> ShlCodes
    {
        { "word", OpCodes::shl_word },
        { "dword", OpCodes::shl_dword }
    };
    const std::unordered_map<std::string, opcode> ShrCodes
    {
        { "i32", OpCodes::shr_i32 },
        { "i64", OpCodes::shr_i64 },
        { "u32", OpCodes::shr_u32 },
        { "u64", OpCodes::shr_u64 }
    };

    void And(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 2)
        {
            PushError("Invalid number of parameters {1}", tokens[0]);
            return;
        }

        if(AndCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(AndCodes.at(tokens[1]));
        else
            PushError("Invalid <t> patameter {word, dword}", tokens[1]);
    }
    void Or(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 2)
        {
            PushError("Invalid number of parameters {1}", tokens[0]);
            return;
        }

        if(OrCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(OrCodes.at(tokens[1]));
        else
            PushError("Invalid <t> patameter {word, dword}", tokens[1]);
    }
    void Xor(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 2)
        {
            PushError("Invalid number of parameters {1}", tokens[0]);
            return;
        }

        if(XorCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(XorCodes.at(tokens[1]));
        else
            PushError("Invalid <t> patameter {word, dword}", tokens[1]);
    }
    void Not(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 2)
        {
            PushError("Invalid number of parameters {1}", tokens[0]);
            return;
        }
        
        if(NotCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(NotCodes.at(tokens[1]));
        else
            PushError("Invalid <t> patameter {word, dword}", tokens[1]);
    }
    void Shl(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 2)
        {
            PushError("Invalid number of parameters {1}", tokens[0]);
            return;
        }

        if(ShlCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(ShlCodes.at(tokens[1]));
        else
            PushError("Invalid <t> patameter {word, dword}", tokens[1]);
    }
    void Shr(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 2)
        {
            PushError("Invalid number of parameters {1}", tokens[0]);
            return;
        }
        
        if(ShrCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(ShrCodes.at(tokens[1]));
        else
            PushError("Invalid <t> patameter {i32, u32, f32, f64}", tokens[1]);
    }
} // namespace BCC::Compiler