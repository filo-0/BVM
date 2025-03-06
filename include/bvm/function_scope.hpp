#pragma once

#include "types.hpp"

namespace BVM::FunctionScope
{
    void SetPointer(Word* pointer);
    #ifdef _DEBUG
    void SetBounds(Word* bottom, Word* top);
    #endif
    /**
     * @brief Gets a local dword.
     * @param index The word index to start from.
     */
    DWord GetLocalD(u8 index);
    /**
     * @brief Gets a local word.
     * @param index The word index
     */
    Word GetLocalW(u8 index);
    HWord GetLocalH(u8 index, u8 hword);
    Byte GetLocalB(u8 index, u8 byte);
    Word* GetLocalRef(u8 index);

    /**
     * @brief Sets local dword.
     * @param index The word index to start from.
     */
    void SetLocalD(u8 index, DWord val);
    /**
     * @brief Sets a local word.
     * @param index The word index
     */
    void SetLocalW(u8 index, Word val);
    void SetLocalH(u8 index, u8 hword, HWord val);
    void SetLocalB(u8 index, u8 byte, Byte val);
}
