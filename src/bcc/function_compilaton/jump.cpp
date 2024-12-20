#include "bcc/functions.hpp"
#include "bcc/compiler.hpp"

namespace BCC
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
        if(tokens.size() == 1)
        {
            PushError("No parameter <l> found", tokens[0]);
            return;
        }

        std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
        if(tokens.size() == 2)
        {
            opcodes.push_back(OpCodes::jmp);
            opcodes.push_back(0);
            opcodes.push_back(0);
            AddJump(tokens[1], opcodes.size());
        }
        else 
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
                    PushError("Invalid <t> parameter {i32, i64, u32, u64, f32, f64", tokens[2]);                             
            }
            else
                PushError("Invalid <c> parameter {eq, ne, lt, gt, le, ge}", tokens[1]);
            
            if(tokens.size() == 3)
            {
                PushError("No parameter <l> found", tokens[0]);
                return;
            }

            opcodes.push_back(0);
            opcodes.push_back(0);
            AddJump(tokens[3], opcodes.size());
        }

        if(tokens.size() > 4)
            PushError("Too many parameters found", tokens[0]);
    }
} // namespace BCC::Compiler
