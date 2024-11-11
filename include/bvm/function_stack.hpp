#pragma once

#include "types.hpp"

namespace BVM::FunctionStack
{
    constexpr u32 SIZE = 1 << 20;

    u32 GetBasePointer();

    DWord& LocalD(u8 index);
    Word & LocalW(u8 index);
    HWord& LocalH(u8 index, u8 hword_offset);
    Byte & LocalB(u8 index, u8 byte_offset);

    void PushData(Word* data, u8 count);
    void OnCall(u8 locals_count);
    void OnReturn(u32 Prev_base_pointer);

    void PrintState();
}
