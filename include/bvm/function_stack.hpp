#pragma once

#include "types.hpp"

namespace BVM::FunctionStack
{
    constexpr u32 SIZE = 1 << 20;

    u32 GetBasePointer();

    HWord& GlobalH0(u32 offset);
    HWord& GlobalH1(u32 offset);

    DWord& LocalD(u8 index);
    Word&  LocalW(u8 index);
    HWord& LocalH0(u8 index);
    HWord& LocalH2(u8 index);
    Byte&  LocalB0(u8 index);
    Byte&  LocalB1(u8 index);
    Byte&  LocalB2(u8 index);
    Byte&  LocalB3(u8 index);

    void PushData(Word* data, u8 count);
    void OnCall(u8 localsCount);
    void OnReturn(u32 PrevBasePointer);

    void PrintState();
}
