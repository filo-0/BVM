#pragma once

#include "types.hpp"

namespace BVM::FunctionStack
{
    constexpr i32 SIZE = 1 << 20;

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
