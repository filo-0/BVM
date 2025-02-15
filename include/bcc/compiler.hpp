#pragma once

#include "std.hpp"
#include "types.hpp"
#include "opcodes.hpp"

namespace BCC
{
    typedef void (*CompileFlowFuntion)(std::vector<std::string>& tokens);
    struct WordData
    {
        Word Value = 0;
        u16 Index  = 0;
    };
    struct DWordData
    {
        DWord Value = 0;
        u16 Index   = 0;
    };
    struct StringData
    {
        std::string Value;
        u16 Index = 0;
    };
    struct FunctionData
    {
        u8 ArgWordCount   = 0;
        u8 LocalWordCount = 0;
        u16 Index         = 0;
        std::vector<opcode> Opcodes;
    };
    struct Error
    {
        std::string msg;
        std::string token;
        int line = 0;
    };

    void GoToNextLine();
    void PushError(const std::string& msg, const std::string& token);
    void AddLabelPointer(const std::string& label, size_t index_from);
    void AddJump(const std::string& label, size_t index_from);
    const std::string& CurrentFunction();
    void Compile(const std::string& input_path, const std::string& output_path);

    bool ExistFunction(const std::string& name);
    bool ExistConstantWord(const std::string& name);
    bool ExistConstantDWord(const std::string& name);
    bool ExistConstantString(const std::string& name);

    u16 GetFunctionIndex(const std::string& name);
    u16 GetConstWordIndex(const std::string& name);
    u16 GetConstDWordIndex(const std::string& name);
    u16 GetConstStringIndex(const std::string& name);

    std::vector<opcode>& GetCurrentFunctionOpcodesList();
} // namespace BCC::Compiler
