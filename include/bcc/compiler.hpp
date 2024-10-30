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
        Word Value;
        u16 Index;
    };
    struct DWordData
    {
        DWord Value;
        u16 Index;
    };
    struct FunctionData
    {
        u8 ArgWordCount;
        u8 LocalWordCount;
        u16 Index;
        std::vector<opcode> Opcodes;
    };
    struct Error
    {
        std::string msg;
        std::string token;
        int line;
    };

    void I32ConstantDefinition(std::vector<std::string>& tokens);
    void I64ConstantDefinition(std::vector<std::string>& tokens);
    void F32ConstantDefinition(std::vector<std::string>& tokens);
    void F64ConstantDefinition(std::vector<std::string>& tokens);
    void U32ConstantDefinition(std::vector<std::string>& tokens);
    void U64ConstantDefinition(std::vector<std::string>& tokens);
    void FunctionDefinition(std::vector<std::string>& tokens);

    extern u32 LineID;
    extern std::vector<std::string> Lines;
    extern std::vector<Error> Errors;
    extern std::vector<std::string> WordConstantNames;
    extern std::vector<std::string> DWordConstantNames;
    extern std::vector<std::string> FunctionNames;
    extern std::unordered_map<std::string, WordData> WordConstantsData;
    extern std::unordered_map<std::string, DWordData> DWordConstantsData;
    extern std::unordered_map<std::string, FunctionData> FunctionsData;
    extern std::unordered_map<std::string, i16> LabelPointers;
    extern std::vector<std::pair<std::string, i16>> Jumps;

    void Compile(const std::string& input_path, const std::string& output_path);
} // namespace BCC::Compiler
