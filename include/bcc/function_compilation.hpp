#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "bcc/compiler.hpp"

namespace BCC::Compiler
{
    void Push(std::vector<std::string>& tokens);
    void Pop(std::vector<std::string>& tokens);
    void Add(std::vector<std::string>& tokens);
    void Sub(std::vector<std::string>& tokens);
    void Mul(std::vector<std::string>& tokens);
    void Div(std::vector<std::string>& tokens);
    void And(std::vector<std::string>& tokens);
    void Or(std::vector<std::string>& tokens);
    void Xor(std::vector<std::string>& tokens);
    void Not(std::vector<std::string>& tokens);
    void Shl(std::vector<std::string>& tokens);
    void Shr(std::vector<std::string>& tokens);
    void Cast(std::vector<std::string>& tokens);
    void Syscall(std::vector<std::string>& tokens);
    void Return(std::vector<std::string>& tokens);
    void Call(std::vector<std::string>& tokens);
    void Jump(std::vector<std::string>& tokens);
    void Dup(std::vector<std::string>& tokens);
    void Swap(std::vector<std::string>& tokens);
    void Label(std::vector<std::string>& tokens);
    
    void Inc(std::vector<std::string>& tokens);
    void Dec(std::vector<std::string>& tokens);

    void PushConst(std::vector<std::string>& tokens);
    void PushLocal(std::vector<std::string>& tokens);
    void PushAs(std::vector<std::string>& tokens);
    void PushRef(std::vector<std::string>& tokens);

    inline const std::unordered_map<std::string, CompileFlowFuntion> PushFunctions
    {
        { "const", PushConst },
        { "local", PushLocal },
        { "as", PushAs },
        { "ref", PushRef}
    };

    void PushLocalByte(std::vector<std::string>& tokens);
    void PushLocalHWord(std::vector<std::string>& tokens);
    void PushLocalWord(std::vector<std::string>& tokens);
    void PushLocalDword(std::vector<std::string>& tokens);
    void PushLocalWords(std::vector<std::string>& tokens);

    inline const std::unordered_map<std::string, CompileFlowFuntion> PushLocalFunctions
    {
        { "byte", PushLocalByte },
        { "hword", PushLocalHWord },
        { "word", PushLocalWord },
        { "dword", PushLocalDword },
        { "words", PushLocalWords }
    };

    void PushAsI32(std::vector<std::string>& tokens);
    void PushAsI64(std::vector<std::string>& tokens);
    void PushAsF32(std::vector<std::string>& tokens);
    void PushAsF64(std::vector<std::string>& tokens);

    inline const std::unordered_map<std::string, CompileFlowFuntion> PushAsFunctions
    {
        { "i32", PushAsI32 },
        { "i64", PushAsI64 },
        { "f32", PushAsF32 },
        { "f64", PushAsF64 }
    };

    void PopByte(std::vector<std::string>& tokens);
    void PopHWord(std::vector<std::string>& tokens);
    void PopWord(std::vector<std::string>& tokens); 
    void PopDWord(std::vector<std::string>& tokens);
    void PopWords(std::vector<std::string>& tokens);

    inline const std::unordered_map<std::string, CompileFlowFuntion> PopFunctions
    {
        { "byte",  PopByte  },
        { "hword", PopHWord },
        { "word",  PopWord  },
        { "dword", PopDWord },
        { "words", PopWords }
    };

    void Getaddr(std::vector<std::string>& tokens);
    void Load(std::vector<std::string>& tokens);
    void Store(std::vector<std::string>& tokens);

} // namespace BCC
