#include "bcc/function_compilation.hpp"
#include "bcc/compiler.hpp"

namespace BCC::Compiler
{
    const std::unordered_map<std::string, std::unordered_map<std::string, opcode>> JumpCodes
    {
        {
            "eq", 
            {
                { { "i32" }, OpCodes::jmp_i32_eq },
                { { "i64" }, OpCodes::jmp_i64_eq },
                { { "f32" }, OpCodes::jmp_f32_eq },
                { { "f64" }, OpCodes::jmp_f64_eq },
                { { "u32" }, OpCodes::jmp_i32_eq },
                { { "u64" }, OpCodes::jmp_i64_eq }
            } 
        },
        {
            "ne",
            {
                { { "i32" }, OpCodes::jmp_i32_ne },
                { { "i64" }, OpCodes::jmp_i64_ne },
                { { "f32" }, OpCodes::jmp_f32_ne },
                { { "f64" }, OpCodes::jmp_f64_ne },
                { { "u32" }, OpCodes::jmp_i32_ne },
                { { "u64" }, OpCodes::jmp_i64_ne }
            }
        },
        {
            "lt",
            {
                { { "i32" }, OpCodes::jmp_i32_lt },
                { { "i64" }, OpCodes::jmp_i64_lt },
                { { "f32" }, OpCodes::jmp_f32_lt },
                { { "f64" }, OpCodes::jmp_f64_lt },
                { { "u32" }, OpCodes::jmp_u32_lt },
                { { "u64" }, OpCodes::jmp_u64_lt }
            }
        },
        {
            "gt",
            {
                { { "i32" }, OpCodes::jmp_i32_gt },
                { { "i64" }, OpCodes::jmp_i64_gt },
                { { "f32" }, OpCodes::jmp_f32_gt },
                { { "f64" }, OpCodes::jmp_f64_gt },
                { { "u32" }, OpCodes::jmp_u32_gt },
                { { "u64" }, OpCodes::jmp_u64_gt }
            }
        },
        {
            "le",
            {
                { { "i32" }, OpCodes::jmp_i32_le },
                { { "i64" }, OpCodes::jmp_i64_le },
                { { "f32" }, OpCodes::jmp_f32_le },
                { { "f64" }, OpCodes::jmp_f64_le },
                { { "u32" }, OpCodes::jmp_u32_le },
                { { "u64" }, OpCodes::jmp_u64_le }
            }
        },
        {
            "ge",
            {
                { { "i32" }, OpCodes::jmp_i32_ge },
                { { "i64" }, OpCodes::jmp_i64_ge },
                { { "f32" }, OpCodes::jmp_f32_ge },
                { { "f64" }, OpCodes::jmp_f64_ge },
                { { "u32" }, OpCodes::jmp_u32_ge },
                { { "u64" }, OpCodes::jmp_u64_ge }
            }
        }
    };

    void Label(std::vector<std::string>& tokens)
    {
        LabelPointers[tokens[1]] = FunctionsData[FunctionNames.back()].Opcodes.size();
    }
    void Jump(std::vector<std::string>& tokens)
    {
        std::vector<opcode>& opcodes = FunctionsData[FunctionNames.back()].Opcodes;
        if(tokens.size() == 2)
        {
            opcodes.push_back(OpCodes::jmp);
            opcodes.push_back(0);
            opcodes.push_back(0);
            Jumps.emplace_back(tokens[1], opcodes.size());
        }
        else if(tokens.size() == 4)
        {
            if(JumpCodes.contains(tokens[1]))
            {
                auto& table = JumpCodes.at(tokens[1]);
                if(table.contains(tokens[2]))
                {
                    opcode op = table.at(tokens[2]);
                    opcodes.push_back(op);  
                }
                else
                    Errors.emplace_back("Invalid jump " + tokens[1] + " type", tokens[2], LineID);                             
            }
            else
                Errors.emplace_back("Invalid jump coondition", tokens[1], LineID);
            
            opcodes.push_back(0);
            opcodes.push_back(0);
            Jumps.emplace_back(tokens[3], opcodes.size());
        }
        else
            Errors.emplace_back("Label not found", tokens[1], LineID);
    }
} // namespace BCC::Compiler
