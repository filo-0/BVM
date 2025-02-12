#pragma once

#include "std.hpp"

namespace BCC
{
    void Push(std::vector<std::string>& tokens);
    void Pop(std::vector<std::string>& tokens);
    
    void Add(std::vector<std::string>& tokens);
    void Sub(std::vector<std::string>& tokens);
    void Mul(std::vector<std::string>& tokens);
    void Div(std::vector<std::string>& tokens);
    void Neg(std::vector<std::string>& tokens);
    void Inc(std::vector<std::string>& tokens);
    void Dec(std::vector<std::string>& tokens);
    
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
    void Label(std::vector<std::string>& tokens);

    void Dup(std::vector<std::string>& tokens);
    void Swap(std::vector<std::string>& tokens);

    void Load(std::vector<std::string>& tokens);
    void Store(std::vector<std::string>& tokens);

    void Alloc(std::vector<std::string>& tokens);
    void Dealloc(std::vector<std::string>& tokens);

    void Cmp(std::vector<std::string>& tokens);
} // namespace BCC
