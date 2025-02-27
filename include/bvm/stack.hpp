#pragma once

#include "types.hpp"

namespace BVM::Stack
{
    void SetDataBlock(Word* data, u32 size);
    void PushScope(const Word* args, u8 argWordCount, u8 localWordCount, u16 stackWordCount, u32 pc);
    u32 PopScope();
} // namespace Stack
