#include "bcc/function_compilation.hpp"
#include "bcc/compiler.hpp"

namespace BCC::Compiler
{
    const std::unordered_map<std::string, std::unordered_map<std::string, opcode>> DupCodes
    {
        {
            "x0",
            {
                { "word", OpCodes::dup_word },
                { "dword", OpCodes::dup_dword }
            }
        },
        {
            "x1",
            {
                { "word", OpCodes::dup_word_x1 },
                { "dword", OpCodes::dup_dword_x1 }
            }
        },
        {
            "x2",
            {
                { "word", OpCodes::dup_word_x2 },
                { "dword", OpCodes::dup_dword_x2 }
            }
        }
    };

    void Dup(std::vector<std::string>& tokens)
    {
        std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].Opcodes;
        if(tokens.size() == 2)
        {
            auto& table = DupCodes.at("x0");
            if(table.contains(tokens[1]))
            {
                opcode op = table.at(tokens[1]);
                opcodes.push_back(op);
            }
            else
                Errors.emplace_back("Invalid dup parameter [value_type]", tokens[1], LineID);
        }
        else if(tokens.size() == 3)
        {
            if(DupCodes.contains(tokens[1]))
            {
                auto& table = DupCodes.at(tokens[1]);
                if (table.contains(tokens[2]))
                {
                    opcode op = table.at(tokens[2]);
                    opcodes.push_back(op);
                }
                else
                    Errors.emplace_back("Invalid dup " + tokens[1] + " parameter [value_type]", tokens[2], LineID);
            }
            else
                Errors.emplace_back("Invalid dup parameter [dup_type]", tokens[1], LineID);
        }
        else
            Errors.emplace_back("Invalid dup args count", "None", LineID);
    }
    void Swap(std::vector<std::string>& tokens)
    {
        std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].Opcodes;
        if(tokens[1] == "word")
            opcodes.push_back(OpCodes::swap_word);
        else if(tokens[1] == "dword")
            opcodes.push_back(OpCodes::swap_dword);
        else    
            Errors.emplace_back("Invalid swap type", tokens[1], LineID);
    }
} // namespace BCC::Compiler
