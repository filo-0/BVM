#include "bcc/function_compilation.hpp"
#include "bcc/compiler.hpp"

namespace BCC::Compiler
{
    const std::unordered_map<std::string, opcode> AddCodes
    {
        { "i32", OpCodes::add_i32 },
        { "i64", OpCodes::add_i64 },
        { "f32", OpCodes::add_f32 },
        { "f64", OpCodes::add_f64 },
    };
    const std::unordered_map<std::string, opcode> SubCodes
    {
        { "i32", OpCodes::sub_i32 },
        { "i64", OpCodes::sub_i64 },
        { "f32", OpCodes::sub_f32 },
        { "f64", OpCodes::sub_f64 },
    };
    const std::unordered_map<std::string, opcode> MulCodes
    {
        { "i32", OpCodes::mul_i32 },
        { "i64", OpCodes::mul_i64 },
        { "f32", OpCodes::mul_f32 },
        { "f64", OpCodes::mul_f64 },
        { "u32", OpCodes::mul_u64 },
        { "u64", OpCodes::mul_u64 }
    };
    const std::unordered_map<std::string, opcode> DivCodes
    {
        { "i32", OpCodes::div_i32 },
        { "i64", OpCodes::div_i64 },
        { "f32", OpCodes::div_f32 },
        { "f64", OpCodes::div_f64 },
        { "u32", OpCodes::div_u64 },
        { "u64", OpCodes::div_u64 }
    };
    const std::unordered_map<std::string, opcode> NegCodes
    {
        { "i32", OpCodes::neg_i32 },
        { "i64", OpCodes::neg_i64 },
        { "f32", OpCodes::neg_f32 },
        { "f64", OpCodes::neg_f64 }
    };
    const std::unordered_map<std::string, opcode> IncCodes
    {
        { "i32", OpCodes::inc_i32 },
        { "i64", OpCodes::inc_i64 },
        { "f32", OpCodes::inc_f32 },
        { "f64", OpCodes::inc_f64 }
    };
    const std::unordered_map<std::string, opcode> DecCodes
    {
        { "i32", OpCodes::dec_i32 },
        { "i64", OpCodes::dec_i64 },
        { "f32", OpCodes::dec_f32 },
        { "f64", OpCodes::dec_f64 }
    };

    void Add(std::vector<std::string>& tokens)
    {
        if(AddCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(AddCodes.at(tokens[1]));
        else
            PushError("Invalid <t> parameter {i32, i64, f32, f64}", tokens[1]);
    }
    void Sub(std::vector<std::string>& tokens)
    {
        if(SubCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(SubCodes.at(tokens[1]));
        else
            PushError("Invalid <t> parameter {i32, i64, f32, f64}", tokens[1]);
    }
    void Mul(std::vector<std::string>& tokens)
    {
        if(MulCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(MulCodes.at(tokens[1]));
        else
            PushError("Invalid <t> parameter {i32, i64, f32, f64}", tokens[1]);
    }
    void Div(std::vector<std::string>& tokens)
    {
        if(DivCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(DivCodes.at(tokens[1]));
        else
            PushError("Invalid <t> parameter {i32, i64, f32, f64}", tokens[1]);
    }
    void Neg(std::vector<std::string>& tokens)
    {
        if(NegCodes.contains(tokens[1]))
            GetCurrentFunctionOpcodesList().push_back(NegCodes.at(tokens[1]));
        else
            PushError("Invalid <t> parameter {i32, i64, f32, f64}", tokens[1]);
    }
    void Inc(std::vector<std::string>& tokens)
    {
        if(IncCodes.contains(tokens[1]))
        {
            std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
            opcodes.push_back(IncCodes.at(tokens[1]));
            int local;
            try { local = std::stoi(tokens[2]); }
            catch(const std::exception& e)
            {
                PushError("Invalid <l> parameter [0, 255]", tokens[2]);
            }
            if(local > 255 || local < 0)
                PushError("Invalid <l> parameter [0, 255]", tokens[2]);
            opcodes.push_back(local);
        }
        else
            PushError("Invalid <t> parameter {i32, i64, f32, f64}", tokens[1]);
    }
    void Dec(std::vector<std::string>& tokens)
    {
        if(DecCodes.contains(tokens[1]))
        {            
            std::vector<opcode>& opcodes = GetCurrentFunctionOpcodesList();
            opcodes.push_back(DecCodes.at(tokens[1]));
            int local;
            try { local = std::stoi(tokens[2]); }
            catch(const std::exception& e)
            {
                PushError("Invalid local index [0, 255]", tokens[2]);
            }
            if(local > 255 || local < 0)
                PushError("Invalid local index [0, 255]", tokens[2]);
            opcodes.push_back(local);
        }
        else
            PushError("Invalid <t> parameter {i32, i64, f32, f64}", tokens[1]);
    }

} // namespace BCC::Compiler
