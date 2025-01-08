#pragma once

#include "types.hpp"

namespace BVM::FunctionStack
{
    constexpr i32 SIZE = 1 << 20;

    /**
     * @brief Access a local dword.
     * @param index The word index to start from.
     * @return A reference to the local dword.
     */
    DWord& LocalD(u8 index);
    /**
     * @brief Access a local word.
     * @param index The word index
     * @return A reference to the local word.
     */
    Word & LocalW(u8 index);
    /**
     * @brief Access a local hword.
     * @param index The word index.
     * @param hwordOffset The hword offset inside the word.
     * @return A reference to the local hword.
     */
    HWord& LocalH(u8 index, u8 hwordOffset);
    /**
     * @brief Access a local byte.
     * @param index The word index.
     * @param byteOffset The byte offset inside the word.
     * @return A reference to the local byte.
     */
    Byte& LocalB(u8 index, u8 byteOffset);


    void PushData(Word* data, u8 count);
    /**
     * @brief Opens a new function scope.
     * @param localsCount The number of local variables of the new scope.
     */
    void OnCall(u32 programCounter, u8 localsCount);
    /**
     * @brief Pops the last function scope to the previous stack pointer.
     * @return Returns the previous ProgramCounter
     */
    u32 OnReturn();

    void PrintState();
}
