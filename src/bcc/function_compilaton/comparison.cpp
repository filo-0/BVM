#include "bcc/functions.hpp"
#include "bcc/compiler.hpp"

namespace BCC
{
    const std::unordered_map<std::string, std::unordered_map<std::string, opcode>> cmpCodes
    {
        {
            "eq", 
            {
                { { "i32" }, OpCodes::cmp_word_eq },
                { { "i64" }, OpCodes::cmp_dword_eq },
                { { "f32" }, OpCodes::cmp_word_eq },
                { { "f64" }, OpCodes::cmp_dword_eq },
                { { "u32" }, OpCodes::cmp_word_eq },
                { { "u64" }, OpCodes::cmp_dword_eq }
            } 
        },
        {
            "lt",
            {
                { { "i32" }, OpCodes::cmp_i32_lt },
                { { "i64" }, OpCodes::cmp_i64_lt },
                { { "f32" }, OpCodes::cmp_f32_lt },
                { { "f64" }, OpCodes::cmp_f64_lt },
                { { "u32" }, OpCodes::cmp_u32_lt },
                { { "u64" }, OpCodes::cmp_u64_lt }
            }
        },
        {
            "le",
            {
                { { "i32" }, OpCodes::cmp_i32_le },
                { { "i64" }, OpCodes::cmp_i64_le },
                { { "f32" }, OpCodes::cmp_f32_le },
                { { "f64" }, OpCodes::cmp_f64_le },
                { { "u32" }, OpCodes::cmp_u32_le },
                { { "u64" }, OpCodes::cmp_u64_le }
            }
        },
    };
    void Cmp(std::vector<std::string>& tokens)
    {
        if(tokens.size() == 1)
        {
            PushError("No parameter <c> found", tokens[0]);
            return;
        }
        else if(tokens.size() == 2)
        {
            PushError("No parameter <t> found", tokens[0]);
            return;
        }
        else if(tokens.size() == 3) 
        {   
            std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
            if(cmpCodes.contains(tokens[1]))
            {
                auto& table = cmpCodes.at(tokens[1]);
                if(table.contains(tokens[2]))
                {
                    opcode op = table.at(tokens[2]);
                    opcodes.push_back(op);  
                }
                else
                    PushError("Invalid <t> parameter {i32, i64, u32, u64, f32, f64", tokens[2]);                             
            }
            else
                PushError("Invalid <c> parameter {eq, lt, le}", tokens[1]);
        }
        else
        {
            PushError("Too many parameters found", tokens[0]);
            return;
        }
    }
}