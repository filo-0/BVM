#include "bcc/functions.hpp"
#include "bcc/compiler.hpp"

namespace BCC
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
        std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 1)
        {
            PushError("No parameter <t> found {word, dword}", tokens[0]);
            return;
        }

        if(tokens.size() == 2)
        {
            auto& table = DupCodes.at("x0");
            if(table.contains(tokens[1]))
            {
                opcode op = table.at(tokens[1]);
                opcodes.push_back(op);
            }
            else
                PushError("Invalid <t> parameter {word, dword}", tokens[1]);

            if(tokens.size() > 2)
                PushError("Too many parameters found", tokens[0]);
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
                    PushError("Invalid <t> parameter {word, dword}", tokens[2]);
            }
            else
                PushError("Invalid <x> parameter {x1, x2}", tokens[1]);
            
            if(tokens.size() > 3)
                PushError("Too many parameters found", tokens[0]);
        }
        else
            PushError("Invalid number of parameters {1, 2}", tokens[0]);
    }
    void Swap(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No parameter <t> found {word, dword}", tokens[0]);
            return;
        }
        std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens[1] == "word")
            opcodes.push_back(OpCodes::swap_word);
        else if(tokens[1] == "dword")
            opcodes.push_back(OpCodes::swap_dword);
        else    
            PushError("Invalid swap type", tokens[1]);

        if(tokens.size() > 2)
            PushError("Too many parameters found", tokens[0]);
    }
} // namespace BCC::Compiler
