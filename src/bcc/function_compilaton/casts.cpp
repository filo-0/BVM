#include "bcc/function_compilation.hpp"
#include "bcc/compiler.hpp"

namespace BCC::Compiler
{
    const std::unordered_map<std::string, std::unordered_map<std::string, opcode>> CastCodes
    {
        {
            "i32",
            {
                { "i64", OpCodes::i32_to_i64 },
                { "f32", OpCodes::i32_to_f32 },
                { "f64", OpCodes::i32_to_f64 }
            }
        },
        {
            "i64",
            {
                { "i32", OpCodes::i64_to_i32 },
                { "f32", OpCodes::i64_to_f32 },
                { "f64", OpCodes::i64_to_f64 }
            }
        },
        {
            "f32",
            {
                { "i32", OpCodes::f32_to_i32 },
                { "i64", OpCodes::f32_to_i64 },
                { "f64", OpCodes::f32_to_f64 }
            }
        },
        {
            "f64",
            {
                { "i32", OpCodes::f64_to_i32 },
                { "i64", OpCodes::f64_to_i64 },
                { "f32", OpCodes::f64_to_f32 }
            }
        }
    };

    void Cast(std::vector<std::string>& tokens)
    {
        if(tokens.size() != 3)
        {
            PushError("Invalid number of parameters (3)", tokens[0]);
            return;
        }

        std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
        if(CastCodes.contains(tokens[1]))
        {
            auto& table = CastCodes.at(tokens[1]);
            if(table.contains(tokens[2]))
            {
                opcode op = table.at(tokens[2]);
                opcodes.push_back(op);
            }
            else
                PushError("Invalid <g> parameter {i32, i64, f32, f64}", tokens[2]);
        }
        else
            PushError("Invalid <t> parameter {i32, i64, f32, f64}]", tokens[1]);
    }
    
} // namespace BCC::Compiler
