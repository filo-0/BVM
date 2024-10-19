#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "types.hpp"
#include "opcodes.hpp"

namespace BCC::Compiler
{
    typedef void (*CompileFlowFuntion)(std::vector<std::string>& tokens);
    struct WordData
    {
        Word value;
        u16 index;
    };
    struct DWordData
    {
        DWord value;
        u16 index;
    };
    struct FunctionData
    {
        u8 arg_size;
        u8 local_size;
        u16 index;
        std::vector<opcode> opcodes;
    };
    struct Error
    {
        std::string msg;
        std::string token;
        int line;
    };

    extern u32 LineID;
    extern std::vector<std::string> Lines;
    extern std::vector<Error> Errors;
    extern std::vector<std::string> WordConstantNames;
    extern std::vector<std::string> DWordConstantNames;
    extern std::vector<std::string> FunctionNames;
    extern std::unordered_map<std::string, WordData> WordConstantsData;
    extern std::unordered_map<std::string, DWordData> DWordConstantsData;
    extern std::unordered_map<std::string, FunctionData> FunctionsData;

    void Compile(const std::string& input_path, const std::string& output_path);
} // namespace BCC::Compiler
