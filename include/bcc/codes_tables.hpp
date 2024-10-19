#pragma once

#include <unordered_map>
#include <string>

#include "opcodes.hpp"

struct StringPairHash {
    std::size_t operator()(const std::pair<std::string, std::string> &x) const
    {
        return std::hash<std::string>()(x.first) ^ std::hash<std::string>()(x.second);
    }
};

namespace BCC
{

#pragma region Arithmetic
    inline const std::unordered_map<std::string, opcode> AddCodes
    {
        { "i32", OpCodes::add_i32 },
        { "i64", OpCodes::add_i64 },
        { "f32", OpCodes::add_f32 },
        { "f64", OpCodes::add_f64 },
    };
    inline const std::unordered_map<std::string, opcode> SubCodes
    {
        { "i32", OpCodes::sub_i32 },
        { "i64", OpCodes::sub_i64 },
        { "f32", OpCodes::sub_f32 },
        { "f64", OpCodes::sub_f64 },
    };
    inline const std::unordered_map<std::string, opcode> MulCodes
    {
        { "i32", OpCodes::mul_i32 },
        { "i64", OpCodes::mul_i64 },
        { "f32", OpCodes::mul_f32 },
        { "f64", OpCodes::mul_f64 },
        { "u32", OpCodes::mul_u64 },
        { "u64", OpCodes::mul_u64 }
    };
    inline const std::unordered_map<std::string, opcode> DivCodes
    {
        { "i32", OpCodes::div_i32 },
        { "i64", OpCodes::div_i64 },
        { "f32", OpCodes::div_f32 },
        { "f64", OpCodes::div_f64 },
        { "u32", OpCodes::div_u64 },
        { "u64", OpCodes::div_u64 }
    };
#pragma endregion
#pragma region Casts
    inline const std::unordered_map<std::pair<std::string, std::string>, opcode, StringPairHash> CastCodes
    {
        { { "i32", "i64" }, OpCodes::i32_to_i64 },
        { { "i32", "f32" }, OpCodes::i32_to_f32 },
        { { "i32", "f64" }, OpCodes::i32_to_f64 },
        { { "i64", "i32" }, OpCodes::i64_to_i32 },
        { { "i64", "f32" }, OpCodes::i64_to_f32 },
        { { "i64", "f64" }, OpCodes::i64_to_f64 },
        { { "f32", "i32" }, OpCodes::f32_to_i32 },
        { { "f32", "i64" }, OpCodes::f32_to_i64 },
        { { "f32", "f64" }, OpCodes::f32_to_f64 },
        { { "f64", "i32" }, OpCodes::f64_to_i32 },
        { { "f64", "i64" }, OpCodes::f64_to_i64 },
        { { "f64", "f32" }, OpCodes::f64_to_f32 }
    };
#pragma endregion 
#pragma region Calls
    inline std::unordered_map<std::string, opcode> ReturnCodes
    {
        { "byte",  OpCodes::return_byte  },
        { "hword",  OpCodes::return_hword  },
        { "word",  OpCodes::return_word  },
        { "dword",  OpCodes::return_dword  }
    };
#pragma region Syscalls
    inline const std::unordered_map<std::string, opcode> SyscallsCodes
    {
        { "Print",    OpCodes::Syscall::Print    },
        { "PrintI64", OpCodes::Syscall::PrintI64 },
        { "PrintF64", OpCodes::Syscall::PrintF64 },
        { "SqrtF32",  OpCodes::Syscall::SqrtF32  },
        { "SqrtF64",  OpCodes::Syscall::SqrtF64  }
    };
#pragma endregion
#pragma region Bitwise
    inline const std::unordered_map<std::string, opcode> AndCodes
    {
        { "word", OpCodes::and_word },
        { "dword", OpCodes::and_dword }
    };
    inline const std::unordered_map<std::string, opcode> OrCodes
    {
        { "word", OpCodes::or_word },
        { "dword", OpCodes::or_dword }
    };
    inline const std::unordered_map<std::string, opcode> XorCodes
    {
        { "word", OpCodes::xor_word },
        { "dword", OpCodes::xor_dword }
    };
    inline const std::unordered_map<std::string, opcode> NotCodes
    {
        { "word", OpCodes::not_word },
        { "dword", OpCodes::not_dword }
    };
    inline const std::unordered_map<std::string, opcode> ShlCodes
    {
        { "word", OpCodes::shl_word },
        { "dword", OpCodes::shl_dword }
    };
    inline const std::unordered_map<std::string, opcode> ShrCodes
    {
        { "i32", OpCodes::shr_i32 },
        { "i64", OpCodes::shr_i64 },
        { "u32", OpCodes::shr_u32 },
        { "u64", OpCodes::shr_u64 }
    };
#pragma endregion
} // namespace BCC
